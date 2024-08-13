/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the spi DMA to transfer 
  *          continuously converted data.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"

static void system_clock_init(void);
static void spi_master_config(void);
static void spi_slave_config(void);
static void spi_master_send_dma_cfg(uint8_t chlx);
static void spi_master_receive_dma_cfg(uint8_t chlx);
static int spi_dma_test(void);
static void uart0_config(void);

#define TEST_BUF_SIZE (16)
void main(void)
{
    /* retarget printf to NONE */
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();

    /* config system clock */
    system_clock_init();

    /* config uart0 for print */
    uart0_config();

    /* retarget printf to uart0 */
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* config spi master */
    spi_master_config();
    /* config spi slave */
    spi_slave_config();

    /* enable RCC DMA CLK */
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);
    /* enable spi master send dma mode */
    SPI_Dma_Send_Cmd(SPIM, ENABLE);
    /* config dma channel0 to spi master */
    spi_master_send_dma_cfg(DMA_CHANNEL0);
    /* enable spi master receive dma mode */
    SPI_Dma_Receive_Cmd(SPIM, ENABLE);
    /* config dma channel1 to spi master */
    spi_master_receive_dma_cfg(DMA_CHANNEL1);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);

    /* Application entry */
    spi_dma_test();

    while(1){};
}

static void spi_master_send_dma_cfg(uint8_t chlx)
{
    DMA_InitTypeDef dma_inittypedef;

    /* dma clear all interrupt flag */
    DMA_Clear_All_Interrupt_Cmd(DMA);
    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;

    /* spi send from mem to pre */
    dma_inittypedef.direction = MEM_TO_PER_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE1;
    dma_inittypedef.dst_msize = DMA_MSIZE1;

    dma_inittypedef.src_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_NO_CHANGE;

    dma_inittypedef.src_width = DMA_WIDTH8;
    dma_inittypedef.dst_width = DMA_WIDTH8;

    dma_inittypedef.dst_per = DMA_SPIM_TX_REQ;
    dma_inittypedef.src_per = DMA_SPIM_TX_REQ;

    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;
    dma_inittypedef.int_en = DISABLE;

    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Init(DMA, chlx, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
}

static void spi_master_receive_dma_cfg(uint8_t chlx)
{
    DMA_InitTypeDef dma_inittypedef;

    /* dma clear all interrupt flag */
    DMA_Clear_All_Interrupt_Cmd(DMA);
    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;

    /* spi receive from pre to mem */
    dma_inittypedef.direction = PER_TO_MEM_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE1;
    dma_inittypedef.dst_msize = DMA_MSIZE1;

    dma_inittypedef.src_addr_type = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_INCREASE;

    dma_inittypedef.src_width = DMA_WIDTH8;
    dma_inittypedef.dst_width = DMA_WIDTH8;

    dma_inittypedef.dst_per = DMA_SPIM_RX_REQ;
    dma_inittypedef.src_per = DMA_SPIM_RX_REQ;

    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;
    dma_inittypedef.int_en = DISABLE;

    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Init(DMA, chlx, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
}

static void spi_master_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef spi_init_type;

    SPI_Uninit(SPIM);
    RCC_CLK_EN_Ctl(RCC_SPIM_PCLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;    /* spi master pin config */
    GPIO_InitStructure.Alternate = GPIO_AF0_SPI0 | GPIO_AF1_SPI0 | GPIO_AF2_SPI0 | GPIO_AF3_SPI0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    spi_init_type.cpol = SPI_CPOL_0;                /* cpol 0*/
    spi_init_type.cpha = SPI_CPHA_0;                /* cpha 0*/
    spi_init_type.datasize = SPI_DATASIZE_8B;       /* spi data width 8 bit */
    spi_init_type.clk_div = 12;                     /* spi speed = AHB / 12 */
    spi_init_type.nss = SPI_HARDWARE_NSS0;
    SPI_Init(SPIM, &spi_init_type);
    SPI_Set_Tx_Fifo_Threshold(SPIM, 1);
    SPI_Set_Rx_Fifo_Threshold(SPIM, 1);
    SPI_Cmd(SPIM, ENABLE);
}

static void spi_slave_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef spi_init_type;

    SPI_Uninit(SPIS);
    RCC_CLK_EN_Ctl(RCC_SPIS_PCLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17;    /* spi slave pin config */
    GPIO_InitStructure.Alternate = GPIO_AF14_SPIS | GPIO_AF15_SPIS | GPIO_AF16_SPIS | GPIO_AF17_SPIS;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    spi_init_type.cpol = SPI_CPOL_0;             /* cpol 0*/
    spi_init_type.cpha = SPI_CPHA_0;             /* cpha 0*/
    spi_init_type.datasize = SPI_DATASIZE_8B;    /* spi data width 8 bit */
    SPI_Init(SPIS, &spi_init_type);

    SPI_Cmd(SPIS, ENABLE);
}

static int spi_dma_test(void)
{
    int ret = 0;

    /* spi receive fifo depth 16 */
    uint8_t master_send[TEST_BUF_SIZE] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    uint8_t receive[TEST_BUF_SIZE] = {0};
    uint8_t master_receive[TEST_BUF_SIZE] = {0};
    uint8_t master_receive_dummy_data[TEST_BUF_SIZE] = {0};
    uint8_t send_transfer_int_flag = 0;
    uint8_t recv_transfer_int_flag = 0;
    uint8_t transfer_int_flag = 0;

    /* spi master receive dummy data use DMA to clear fifo */
    DMA_Set_Addr(DMA, DMA_CHANNEL1, (uint32_t)&SPIM->DR, mmap_to_sys((uint32_t)&master_receive_dummy_data), sizeof(master_receive_dummy_data), 0);
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL1, ENABLE);

    /* spi master send data to slave use dma */
    DMA_Set_Addr(DMA, DMA_CHANNEL0, mmap_to_sys((uint32_t)&master_send), (uint32_t)&SPIM->DR, sizeof(master_send), 0);
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL0, ENABLE);

    /* wait dma send complete */
    while(1) 
    {
        transfer_int_flag = DMA_Get_Raw_Transfer_Interrupt_Status(DMA);
        if (transfer_int_flag & DMA_CHANNEL0_INT_FLAG) 
        {
            send_transfer_int_flag = 1;
        }

        if (transfer_int_flag & DMA_CHANNEL1_INT_FLAG) 
        {
            recv_transfer_int_flag = 1;
        }

        if (recv_transfer_int_flag == 1 && send_transfer_int_flag == 1) 
        {
            DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0);
            break;
        }
    }
    /* spi slave read data from fifo*/
    SPI_Send_Receive(SPIS, 1, NULL, 0, receive, sizeof(receive));
    /* spi slave write data to fifo*/
    SPI_Send_Receive(SPIS, 1, receive, sizeof(receive),NULL,0);

    recv_transfer_int_flag = 0;
    send_transfer_int_flag = 0;
    /* spi master receive data from slave use dma */
    DMA_Set_Addr(DMA, DMA_CHANNEL1, (uint32_t)&SPIM->DR, mmap_to_sys((uint32_t)&master_receive), sizeof(master_receive), 0);
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL1, ENABLE);

    /* spi master send dummy data to slave use dma */
    DMA_Set_Addr(DMA, DMA_CHANNEL0, mmap_to_sys((uint32_t)&master_receive_dummy_data), (uint32_t)&SPIM->DR, sizeof(master_receive_dummy_data), 0);
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL0, ENABLE);

    /* wait dma send complete */
    while(1) 
    {
        transfer_int_flag = DMA_Get_Raw_Transfer_Interrupt_Status(DMA);
        if (transfer_int_flag & DMA_CHANNEL0_INT_FLAG) 
        {
            DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0);
            send_transfer_int_flag = 1;
        }

        if (transfer_int_flag & DMA_CHANNEL1_INT_FLAG) 
        {
            DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL1);
            recv_transfer_int_flag = 1;
        }

        if (recv_transfer_int_flag == 1 && send_transfer_int_flag == 1) 
        {
            /* wait spi dma send && recv completed */
            break;
        }
    }

    for (int i = 0; i < sizeof(master_receive); i++) 
    {
        if (master_send[i] != master_receive[i]) 
        {
            ret = 1;
        }
    }

    if (ret) 
    {
        printf("failed\r\n");
    } 
    else 
    {
        printf("pass\r\n");
    }

    return ret;
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

static void uart0_config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;    /* uart0 pin config */
    GPIO_InitStructure.Alternate = GPIO_AF4_UART0 | GPIO_AF5_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);

    UART_IT_Cfg(UART0, UART_IT_ERBFI, DISABLE);
}

