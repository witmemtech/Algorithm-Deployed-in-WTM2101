/**
  ******************************************************************************
  * @file    main.c
  * @brief   This example describes how to use the afc calibration
  *          by external oscillator.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "main.h"

static int audio_init(void);
static int audio_start(void);

static void rsm2_mode(void);
static void uart_init(void);
static void system_clock_init(void);

void VAD_IRQHandler(void)
{
    AUDIO_Reset_Vad(AUD);
}

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Reset all peripherals except PMU */
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();

    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);

    /* Initial clock */
    system_clock_init();

    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);
    audio_init();

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /*start audio*/
    audio_start();

    while(1)
    {
        printf("sleep\r\n");
        rsm2_mode();
        printf("vad wakeup:\r\n");
    }
}

static void hal_audio_with_dma_interrupt_handle(void)
{
    uint16_t transfer_int_flag = 0;
    /* The hal audio instance */
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);

    do
    {
        /* The hal audio instance handle the data */
        if (transfer_int_flag & hal_audio_instance->dma_channel)
        {
            DMA_Clear_Transfer_Interrupt_Cmd(DMA,hal_audio_instance->dma_channel);
            hal_audio_instance->Data_handle_info.dma_receive_handler(hal_audio_instance);
        }
        /* Get the dma interrupt status */
        transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);
    }while(transfer_int_flag);
}

static void hal_audio_interrupt_handle(void)
{
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    /* if the audio ram buffer is used,as below */
    if (AUDIO_Get_Ram_Interrupt_Status(hal_audio_instance->instance,hal_audio_instance->channel.ChannelNumber) & HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT)
    {
        /* the interrupt is clear */
        AUDIO_Clear_Ram_Interrupt(hal_audio_instance->instance,hal_audio_instance->channel.ChannelNumber,HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT);
        /* data handle */
        hal_audio_instance->Data_handle_info.audio_receive_handler(hal_audio_instance);
    }
}

static int audio_init(void)
{
    int ret = 0;
    /* The hal audio instance */
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    if (!hal_audio_instance)
    {
        printf("hal_audio_instance is null,this is a  error\r\n");
        return -1;
    }

    /* Init hal audio instance,using the input  dmic */
    ret = hal_audio_init(hal_audio_instance,HAL_AUDIO_MIC_INPUT_DMIC);
    if (ret <= 0)
    {
        printf("hal_audio_init is error:%d\r\n",ret);
        return -2;
    }
    hal_audio_instance->interrupt.enable = DISABLE;
    hal_audio_instance->vad_flag = ENABLE;

    /* Open the audio hardware with the hal audio instance */
    ret = hal_audio_open(hal_audio_instance);
    if (ret <= 0)
    {
        printf("hal_audio_open is error:%d\r\n",ret);
        return -3;
    }

    return 1;
}

static int audio_start(void)
{
    int ret = 0;
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    /* Enable the audio interrupt with the hal audio instance */
    ret = hal_audio_ctl(hal_audio_instance,HAL_AUDIO_INTERRUPT_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -1;
    }

    /* Start the audio with the hal audio instance */
    ret = hal_audio_ctl(hal_audio_instance,HAL_AUDIO_CHANNEL_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -2;
    }

    return 1;
}

static void rsm2_mode(void)
{
    PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_ALL,DISABLE);
    PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_KEEP_VDD | PMU_RSM_MODE_KEEP_AUDIO | PMU_RSM_MODE_KEEP_OSC2M,ENABLE);
    PMU_Rsm_Mode_Cmd(PMU);
    __WFI();
}

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    /*the gpio4,gpio5*/
    GPIO_InitStructure.Pin = GPIO_PIN_16 | GPIO_PIN_17;
    GPIO_InitStructure.Alternate = GPIO_AF16_UART0 | GPIO_AF17_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);
}

static void system_clock_init(void)
{
    int ret = 0;
    /* The clock instance */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /* Construct 24mosc related configuration parameters */
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_INTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = ENABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /* Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc is calibrated by the xtal 32k */
    ret = hal_clock_init(hal_clock_instance, HAL_CLOCK_24MOSC, HAL_CLOCK_24MOSC, &hal_clock_24mosc_Configuration, 0, 1, 1);
    if (ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /* According to the clock instance, initialize the hardware */
    ret = hal_clock_open(hal_clock_instance);
    if (ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}
