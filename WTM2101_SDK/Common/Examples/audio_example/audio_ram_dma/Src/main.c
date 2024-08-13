/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes the use of PDM to read the data collected by 
             the digital MIC, and the AUDIO channel 0 RAM to send the read data 
             in real time through I2S1.
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
uint32_t iis_buff[FRAME_LEN * 2];

volatile Bool audio_buff_ok = FALSE;
volatile Bool audio_dma_completed = FALSE;
volatile Bool i2s_dma_completed = FALSE;

static void iis_dma_config(void);
static void i2s1_config(void);
void DMA_IRQHandler(void);
void AUDIO_IRQHandler(void);
static void audio_gpio_config(void);
static void audio_dma_init(void);
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

    /* Initial audio and i2s */
    audio_config();
    i2s1_config();

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
            for (uint8_t i = 0; i < FRAME_LEN; i++)
            {
                tmp = AUDIO_Read_Ram_Data(AUD, AUDIO_CHANNEL0);
                audio_buff[i << 1] = tmp;
                audio_buff[(i << 1) + 1] = tmp >> 16;
            }
#endif

            for (int i = 0; i < FRAME_LEN * 2; i++)
            {

                /*left channel data*/
                iis_buff[i] = audio_buff[i];
                /*right channel data*/
                iis_buff[i] &= 0x0000ffff;
            }

            DMA_Set_Addr(DMA, DMA_CHANNEL1, mmap_to_sys((uint32_t)iis_buff), (uint32_t) & (I2S1->TXDMA), FRAME_LEN * 2, 0);
            DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL1, ENABLE);
            while (i2s_dma_completed == FALSE);
            i2s_dma_completed = FALSE;
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

static void i2s1_config(void)
{

    uint32_t clk_num = 0;
    GPIO_InitTypeDef GPIO_Uart1InitStructure;

    /* initial gpio */
    GPIO_Uart1InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_Uart1InitStructure.Alternate = GPIO_AF10_I2S1 | GPIO_AF11_I2S1 | GPIO_AF12_I2S1 | GPIO_AF13_I2S1;
    GPIO_Init(GPIOA, &GPIO_Uart1InitStructure);

    /* initial i2s */
    RCC_CLK_EN_Ctl(RCC_I2S1_CLKEN, ENABLE);
    I2S_Ctl(I2S1, DISABLE);

    I2S_Mode_Sel(I2S1, I2S_MASTER);
    I2S_ClkCfg(I2S1, I2S_SCLKNUM_16, I2S_GATESCLKNUM_NONE);
    RCC_I2S1_Set_ClkDiv(48 - 1); /* 48 = 512k / (16k*16*2) */

    I2S_TxCfg(I2S1, I2S_RES_LEN_16);
    I2S_TxFIFO_LVLCfg(I2S1, 1);
    I2S_TxFIFO_Flush(I2S1);

    I2S_IT_MskCtl(I2S1, I2S_IT_TXFE, DISABLE); 

    I2S_Ctl(I2S1, ENABLE);
    I2S_TxBlkCtl(I2S1, ENABLE);
    I2S_RxChlCtl(I2S1, DISABLE);
    I2S_TxChlCtl(I2S1, ENABLE);
    I2S_ClkCtl(I2S1, ENABLE);

    /* initial i2s dma */
    iis_dma_config();
}

static void iis_dma_config(void)
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
    dma_inittypedef.direction = MEM_TO_PER_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE8;
    dma_inittypedef.dst_msize = DMA_MSIZE8;
    dma_inittypedef.src_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.src_width = DMA_WIDTH32;
    dma_inittypedef.dst_width = DMA_WIDTH16;
    dma_inittypedef.src_per = DMA_I2S1_REQ;
    dma_inittypedef.dst_per = DMA_I2S1_REQ;
    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY1;
    dma_inittypedef.int_en = ENABLE;
    DMA_Init(DMA, DMA_CHANNEL1, &dma_inittypedef);

    DMA_Set_Enable_Cmd(DMA, ENABLE);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL1, ENABLE);
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
        i2s_dma_completed = TRUE;
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

    DMA_Set_Enable_Cmd(DMA, ENABLE);
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

    /* audio clk 4M/(3+1)=1MHz */
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
    AUDIO_Set_Channel_Gain_Configuration(AUD, AUDIO_CHANNEL0, 16);
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, DISABLE);
}

static void audio_start(void)
{
    AUDIO_Set_Ram_Interrupt_Mask(AUD, AUDIO_CHANNEL0, AUDIO_RAM_FRAME_VLD_INTERRUPT, ENABLE);
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, ENABLE);
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