/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes the use of PDM to read the data collected by 
             digital MIC, and AUDIO channel 0 RAM to print the read data through 
             UART.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
 
#include "main.h"

#define FRAME_LEN (120)
#define AUDIO_TRANSFER_DMA

uint16_t audio_buff[FRAME_LEN * 2];
uint8_t  uart_buff[FRAME_LEN * 4];


volatile Bool audio_buff_ok = FALSE;
volatile Bool audio_dma_completed = FALSE;
volatile Bool uart_dma_completed = FALSE;



void DMA_IRQHandler(void);
void AUDIO_IRQHandler(void);
static void audio_gpio_config(void);
static void audio_dma_init(void);
static void audio_config(void);
static void audio_start(void);
static void uart_dma_init(void);
static void uart_config(void);
static void system_clock_init(void);


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

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);

    /* Initial periphral */
    audio_config();
    uart_config();

    /* Application entry */
    audio_start();
    uint32_t tmp;
    while (1)
    {
        if (audio_buff_ok != FALSE)
        {
            audio_buff_ok = FALSE;

#if defined(AUDIO_TRANSFER_DMA)

            DMA_Set_Addr(DMA, DMA_CHANNEL0, (uint32_t) & (AUD->RAM0DATA), mmap_to_sys((uint32_t)audio_buff), FRAME_LEN, 0);
            DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL0, ENABLE);
            while (audio_dma_completed == FALSE);
            audio_dma_completed = FALSE;
#else
            uint32_t tmp = 0;
            for (uint16_t i = 0; i < FRAME_LEN; i++)
            {
                tmp = AUDIO_Read_Ram_Data(AUD, AUDIO_CHANNEL0);
                audio_buff[i << 1] = tmp;
                audio_buff[(i << 1) + 1] = tmp >> 16;
            }
#endif

           for (uint16_t i = 0; i < FRAME_LEN * 2; i++)
           {
                uart_buff[2*i] = audio_buff[i];
                uart_buff[2*i+1]=audio_buff[i]>>8;
           }

           while (UART_Flag_GetStatBit(UART0, UART_FLAG_TEMT) != SET);

           DMA_Set_Addr(DMA, DMA_CHANNEL1, mmap_to_sys((uint32_t)uart_buff), (uint32_t)(&(UART0->DR_DLL)), FRAME_LEN*2, 0);
           DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL1, ENABLE);
           while (uart_dma_completed == FALSE);
           uart_dma_completed = FALSE;

        }
        else
        {
        }
    }
}

void DMA_IRQHandler(void)
{
    uint8_t transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);

    if (transfer_int_flag & DMA_CHANNEL0_INT_FLAG)
    {
        audio_dma_completed = TRUE;
        DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0);
    }

    if (transfer_int_flag & DMA_CHANNEL1_INT_FLAG)
    {
        uart_dma_completed = TRUE;
        DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL1);
    }

}


void AUDIO_IRQHandler(void)
{
    if (AUDIO_Get_Ram_Interrupt_Status(AUD, AUDIO_CHANNEL0) & AUDIO_RAM_FRAME_VLD_INTERRUPT)
    {
        audio_buff_ok = TRUE;
        ECLIC_ClearPendingIRQ(AUDIO_IRQn);
        AUDIO_Clear_Ram_Interrupt(AUD, AUDIO_CHANNEL0, AUDIO_RAM_FRAME_VLD_INTERRUPT);
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


static void audio_dma_init(void)
{
    DMA_InitTypeDef dma_inittypedef;
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);
    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Clear_All_Interrupt_Cmd(DMA);
    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);

    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;
    dma_inittypedef.direction = MEM_TO_MEM_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE8;
    dma_inittypedef.dst_msize = DMA_MSIZE8;
    dma_inittypedef.src_addr_type = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.src_width = DMA_WIDTH32;
    dma_inittypedef.dst_width = DMA_WIDTH16;
    dma_inittypedef.src_per = DMA_AUDIO_CH0_REQ;
    dma_inittypedef.dst_per = DMA_AUDIO_CH0_REQ;
    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;
    dma_inittypedef.int_en = ENABLE;
    DMA_Init(DMA, DMA_CHANNEL0, &dma_inittypedef);

    /* DMA is enabled */
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    /* DMA transfer finished interrupt is enabled */
    DMA_Set_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0, ENABLE);
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

    /* initial audio dma */
    audio_dma_init();

    /* audio clk */
    AUDIO_Set_Channel_Clock_Divider(AUD, 3); /* 4m/4=1mhz */
    PMU_Set_Audio_Clock_Div_Num(PMU, 5);     /* 24/6=4mhz */

    /* initial audio */
    AUDIO_Channel0_12bit_Pcm_Cmd(AUD, DISABLE);

    AUDIO_Set_Channel_Transmit_Mode(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_TRANSMIT_RAM_MODE);
    AUDIO_Set_Channel_Input_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_INPUT_FROM_DIGITAL);
    AUDIO_Set_Channel0_Select_Pdm(AUD, AUDIO_PDM0);

    /* audio filter config */
    AUDIO_Set_Pre_Emphasis_Bypass_Cmd(AUD, ENABLE);
    AUDIO_Set_Sinc5d2_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Halfband_Bypass_Cmd(AUD, ENABLE);
    AUDIO_Set_Highpass_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Channel2_High_Bypass_Cmd(AUD, DISABLE);

    AUDIO_Set_Channel_Edge_Capture_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE);

    /* ram config */
    AUDIO_Set_RAM_Depth(AUD, AUDIO_CHANNEL0, FRAME_LEN * 2 - 1);
    AUDIO_Set_RAM_Frame_Move(AUD, AUDIO_CHANNEL0, FRAME_LEN - 1);
    AUDIO_Set_RAM_Length(AUD, AUDIO_CHANNEL0, FRAME_LEN - 1);

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
    AUDIO_Set_Ram_Interrupt_Mask(AUD, AUDIO_CHANNEL0, AUDIO_RAM_FRAME_VLD_INTERRUPT, ENABLE);
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, ENABLE);
}


static void uart_dma_init(void)
{
    DMA_InitTypeDef dma_inittypedef;
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);

    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);
    DMA_Clear_All_Interrupt_Cmd(DMA);

    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;

    dma_inittypedef.direction = MEM_TO_PER_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE1;
    dma_inittypedef.dst_msize = DMA_MSIZE1;

    dma_inittypedef.src_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_NO_CHANGE;

    dma_inittypedef.src_width = DMA_WIDTH16;
    dma_inittypedef.dst_width = DMA_WIDTH8;

    dma_inittypedef.dst_per = DMA_UART0_TX_REQ_OR_AUDIO_CH1;
    dma_inittypedef.src_per = DMA_UART0_TX_REQ_OR_AUDIO_CH1;

    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;
    dma_inittypedef.int_en = ENABLE;

    DMA_Init(DMA, DMA_CHANNEL1, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL1, ENABLE);
}


static void uart_config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN, ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_16 | GPIO_PIN_17;
    GPIO_InitStructure.Alternate = GPIO_AF16_UART0  | GPIO_AF17_UART0 ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    uart_dma_init();
    USART_InitStructure.BaudRate = 460800;
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

    /* Initialize the clock instance.the system clock is from PLL.the 24mosc is calibrated by the xtal 32k */
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_PLL,HAL_CLOCK_PLL,&hal_clock_24mosc_Configuration,6,1,1);
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