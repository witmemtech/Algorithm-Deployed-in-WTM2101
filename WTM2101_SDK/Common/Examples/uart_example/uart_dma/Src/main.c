/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the uart to transfer 
  *          continuously converted data.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"
static void uart0_config(void);
static void uart1_config(void);
static void system_clock_init(void);
static void uart0_dma_tx_init(uint8_t chx);
static void uart0_dma_rx_init(uint8_t chx);

#define TEST_BUF_SIZE (8)
void main(void)
{
    uint8_t uart0_send[TEST_BUF_SIZE] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    uint8_t uart0_recv[TEST_BUF_SIZE] = {0};
    uint8_t uart1_recv[TEST_BUF_SIZE] = {0};
    uint8_t transfer_int_flag = 0;

    /* retarget printf to segger rtt */
    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();
    
    /* config system clock */
    system_clock_init();

    uart0_config();
    /* config uart0 tx to DMA channel 0 */
    uart0_dma_tx_init(DMA_CHANNEL0);
    /* config uart0 rx to DMA channel 1 */
    uart0_dma_rx_init(DMA_CHANNEL1);
    uart1_config();

 
    /*  Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);

    /* Application entry */
    /* uart0 send data use dma */
    DMA_Set_Addr(DMA, DMA_CHANNEL0, mmap_to_sys((uint32_t)uart0_send), (uint32_t)(&(UART0->DR_DLL)), sizeof(uart0_send), 0);
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL0, ENABLE);

    /* uart1 read data from receive fifo */
    for (int i = 0;i < sizeof(uart1_recv);i++)
    {
        while (UART_Flag_GetStatBit(UART1,UART_FLAG_DR) == RESET);
        uart1_recv[i] =  UART_ReceiveData(UART1);
    }

    /* uart0 receive data use dma */
    DMA_Set_Addr(DMA, DMA_CHANNEL1, (uint32_t)(&(UART0->DR_DLL)), mmap_to_sys((uint32_t)uart0_recv), sizeof(uart0_recv), 0);
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL1, ENABLE);

    /* uart1 write data to send fifo */
    for (int i = 0;i < sizeof(uart1_recv);i++) 
    {
        while (UART_Flag_GetStatBit(UART1,UART_FLAG_TEMT) == RESET);
        UART_SendData(UART1, uart1_recv[i]);
    }

    /* wait dma receive data complete */
    while(1) 
    {
        transfer_int_flag = DMA_Get_Raw_Transfer_Interrupt_Status(DMA);

        if (transfer_int_flag & DMA_CHANNEL1_INT_FLAG) 
        {
            DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL1);
            break;
        }
    }

    /* check data */
    if (memcmp(uart0_send, uart0_recv, sizeof(uart0_recv)) == 0) 
    {
        printf("pass\r\n");
    } 
    else 
    {
        printf("failed\r\n");
    }

    while(1){};
}

static void uart0_config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;    /* uart0 pin config */
    GPIO_InitStructure.Alternate = GPIO_AF4_UART0 | GPIO_AF5_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 115200;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = ENABLE;    /* enable fifo */
    UART_Init(UART0, &USART_InitStructure);
    UART_RxFIFO_LevelCfg(UART0, UART_RX_FIFO_1);
    UART_IT_Cfg(UART0, UART_IT_ERBFI, DISABLE);
}

static void uart1_config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART1_CLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15;    /* uart0 pin config */
    GPIO_InitStructure.Alternate = GPIO_AF14_UART1 | GPIO_AF15_UART1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 115200;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = ENABLE;    /* enable fifo */
    UART_Init(UART1, &USART_InitStructure);

    UART_IT_Cfg(UART1, UART_IT_ERBFI, DISABLE);
}

static void uart0_dma_tx_init(uint8_t chx)
{
    DMA_InitTypeDef dma_inittypedef;
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);

    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;

    dma_inittypedef.direction = MEM_TO_PER_FLOW_CTOL_DMA;  /* DMA flow mem to peripheral */
    dma_inittypedef.src_msize = DMA_MSIZE1;
    dma_inittypedef.dst_msize = DMA_MSIZE1;

    dma_inittypedef.src_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_NO_CHANGE;

    dma_inittypedef.src_width = DMA_WIDTH8;
    dma_inittypedef.dst_width = DMA_WIDTH8;

    dma_inittypedef.dst_per = DMA_UART0_TX_REQ_OR_AUDIO_CH1;
    dma_inittypedef.src_per = DMA_UART0_TX_REQ_OR_AUDIO_CH1;

    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;    /* DMA channel priority 0 */
    dma_inittypedef.int_en = DISABLE;

    DMA_Init(DMA, chx, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
}

static void uart0_dma_rx_init(uint8_t chx)
{
    DMA_InitTypeDef dma_inittypedef;
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);

    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;

    dma_inittypedef.direction = PER_TO_MEM_FLOW_CTOL_DMA;    /* DMA flow mem to peripheral */
    dma_inittypedef.src_msize = DMA_MSIZE1;
    dma_inittypedef.dst_msize = DMA_MSIZE1;

    dma_inittypedef.src_addr_type = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_INCREASE;

    dma_inittypedef.src_width = DMA_WIDTH8;
    dma_inittypedef.dst_width = DMA_WIDTH8;

    dma_inittypedef.dst_per = DMA_UART0_RX_REQ_OR_AUDIO_CH2;
    dma_inittypedef.src_per = DMA_UART0_RX_REQ_OR_AUDIO_CH2;

    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;    /* DMA channel priority 0 */
    dma_inittypedef.int_en = DISABLE;

    DMA_Init(DMA, chx, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
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


