/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to config audio
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"

#define AUDIO_BUFF_SIZE (15000)
uint32_t audio_buff_out[AUDIO_BUFF_SIZE];


volatile Bool audio_buff_ok = FALSE;
volatile Bool audio_dma_completed = FALSE;


void AUDIO_IRQHandler(void);
static void audio_gpio_config(void);
static void audio_config(void);
static void audio_start(void);
static void system_clock_init(void);
static void uart_init(void);

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

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);

    /* Initial audio */
    audio_config();

    /* Application entry */
    audio_start();

    int idx=0;
    while (1)
    {
        if (audio_buff_ok != FALSE)
        {
            audio_buff_ok = FALSE;
            for (uint8_t i = 0; i < 4; i++)
            {
                audio_buff_out[idx+i] = AUDIO_Read_Fifo_Data(AUD, AUDIO_CHANNEL0);
            }
            idx=idx+4;
             if(idx==AUDIO_BUFF_SIZE)
            {
                AUDIO_Set_FIFO_Interrupt_Mask(AUD, AUDIO_CHANNEL0, AUDIO_FIFO_HALF_FULL_INTERRUPT, DISABLE);
                for(uint32_t i=0; i<AUDIO_BUFF_SIZE; i++)
                {
                    printf("%04x %04x ",  audio_buff_out[i] & 0xffff, (audio_buff_out[i]& 0xffff0000) >> 16);
                }
            }
        }
        else
        {
        }
    }
}


static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);
   
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
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /* According to the clock instance, initialize the hardware */
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

void AUDIO_IRQHandler(void)
{
    if (AUDIO_Get_FIFO_Interrupt_Status(AUD, AUDIO_CHANNEL0) & AUDIO_FIFO_HALF_FULL_INTERRUPT)
    {
        audio_buff_ok = TRUE;
        ECLIC_ClearPendingIRQ(AUDIO_IRQn);
        AUDIO_Clear_Fifo_Interrupt(AUD, AUDIO_CHANNEL0, AUDIO_FIFO_HALF_FULL_INTERRUPT);
    }
}

static void audio_gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN, ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_4; /* pdm_clkout */
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate = GPIO_AF4_PDM0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_5; /* pdm_datain */
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate = GPIO_AF5_PDM0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


static void audio_config(void)
{
    /* initial audio gpio */
    audio_gpio_config();

    /* initial audio rcc and pmu*/
    RCC_CLK_EN_Ctl(RCC_AUD_PCLKEN | RCC_AUD_CLKEN, ENABLE);
    RCC_Peri_Rst(RCC_AUD_PRSTN);
    RCC_Peri_Rst(RCC_AUD_RSTN);
    PMU_Set_Audio_Clock_Cmd(PMU, ENABLE);

    AUDIO_Set_Channel_Clock_Divider(AUD, 3); /* 4m/2=1mhz */
    PMU_Set_Audio_Clock_Div_Num(PMU, 5);     /* 24/6=4mhz */

    AUDIO_Channel0_12bit_Pcm_Cmd(AUD, DISABLE);

    AUDIO_Set_Channel_Transmit_Mode(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_TRANSMIT_FIFO_MODE);
    AUDIO_Set_Channel_Input_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_INPUT_FROM_DIGITAL);
    AUDIO_Set_Channel0_Select_Pdm(AUD, AUDIO_PDM0);

    /* filter config */
    AUDIO_Set_Pre_Emphasis_Bypass_Cmd(AUD, ENABLE);
    AUDIO_Set_Sinc5d2_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Halfband_Bypass_Cmd(AUD, ENABLE);
    AUDIO_Set_Highpass_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Channel2_High_Bypass_Cmd(AUD, DISABLE);

    AUDIO_Set_Channel_Edge_Capture_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE);

    /* audio interrupt config */
    ECLIC_ClearPendingIRQ(AUDIO_IRQn);
    ECLIC_SetPriorityIRQ(AUDIO_IRQn, 2);
    ECLIC_SetTrigIRQ(AUDIO_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(AUDIO_IRQn);

    /* audio gain config */
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, ENABLE);
    AUDIO_Set_Channel_Gain_Configuration(AUD, AUDIO_CHANNEL0, 10);
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, DISABLE);
}

static void audio_start(void)
{
    AUDIO_Set_FIFO_Interrupt_Mask(AUD, AUDIO_CHANNEL0, AUDIO_FIFO_HALF_FULL_INTERRUPT, ENABLE);
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, ENABLE);
}


