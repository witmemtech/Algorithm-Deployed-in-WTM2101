/**
  ******************************************************************************
  * @file    main.c
  * @brief   This example describes how to use DMA to control a transfer
  *          between memory and I2C.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "main.h"

#define BUFFER_SIZE     (8)

static void system_clock_init(void);
static void i2c_config(void);
static void mem_to_i2c_init(uint8_t chlx);
static void i2c_to_mem_init(uint8_t chlx);
static void write_dma(uint8_t *pbuffer, uint8_t addr, uint8_t numbyte);
static void read_dma(uint8_t *pbuffer, uint8_t addr, uint8_t numbyte);
static int  i2c_test(void);
static void uart0_config(void);

static uint8_t writeBuff[BUFFER_SIZE];
static uint8_t readBuff[sizeof(writeBuff)];

void main(void)
{
    int led_status = 0;

    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Reset all peripherals except PMU */
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));

    /* N307 interrupt enable */
    __enable_irq();
    __enable_mcycle_counter();

    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);

    /* Initialize basic system: Clock and GPIO */
    system_clock_init();

    /* Initialize periphral */
    uart0_config();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    i2c_config();

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    if (0 == i2c_test())
    {
        printf("i2c_test ok\r\n");
    }
    else
    {
        printf("i2c_test err\r\n");
    }

    while(1) {}
}

static void system_clock_init(void)
{
    int ret = 0;
    /* The clock instance */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /* Construct 24mosc related configuration parameters */
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_EXTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = DISABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /* Initialize the clock instance */
    ret = hal_clock_init(hal_clock_instance, HAL_CLOCK_24MOSC, HAL_CLOCK_24MOSC, &hal_clock_24mosc_Configuration, 0, 1, 1);

    if (ret <= 0)
    {
        printf("hal_clock_init error: %d\r\n", ret);
    }

    /* According to the clock instance, initialize the hardware */
    ret = hal_clock_open(hal_clock_instance);
    if (ret <= 0)
    {
        printf("hal_clock_init error: %d\r\n", ret);
    }
}

static void i2c_config(void)
{
    I2C_InitTypeDef I2C_InitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_CLK_EN_Ctl(RCC_I2C_PCLKEN | RCC_GPIO_HCLKEN, ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPU;
    GPIO_InitStructure.Alternate = GPIO_AF4_I2C | GPIO_AF5_I2C;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    I2C_Ctl(I2C, DISABLE);
    I2C_InitStruct.Mode = I2C_MODE_MASTER;
    I2C_InitStruct.Speed = I2C_SPEED_STD;
    I2C_InitStruct.AddrMode = I2C_ADDR_7BITS_MASTER;
    I2C_InitStruct.Restart = I2C_RESTART_ENABLE;
    I2C_InitStruct.Address = (((uint8_t)0xA0) >> 1);
    I2C_Init(I2C, &I2C_InitStruct);

    I2C_IT_MskCtl(I2C, I2C_IT_ALL, DISABLE);
    I2C_TX_EmptyCtl(I2C, I2C_TX_EMPTY_MODE1);
    I2C_Set_SS_HCNT(I2C, 85);
    I2C_Set_SS_LCNT(I2C, 165);
    I2C_Set_SDA_RX_HOLD(I2C, 6);
    I2C_Set_SDA_TX_HOLD(I2C, 10);
    I2C_Set_RX_TL(I2C, 6);
    I2C_Set_TX_TL(I2C, 4);
    I2C_Set_FS_SPKLEN(I2C, 1);
    I2C_Ctl(I2C, ENABLE);
}

static void mem_to_i2c_init(uint8_t chlx)
{
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);

    DMA_InitTypeDef dma_inittypedef;
    DMA_Clear_All_Interrupt_Cmd(DMA);

    dma_inittypedef.llp_src_en           = DISABLE;
    dma_inittypedef.llp_dst_en           = DISABLE;
    dma_inittypedef.reload_src_en        = DISABLE;
    dma_inittypedef.reload_dst_en        = DISABLE;
    dma_inittypedef.direction            = MEM_TO_PER_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize            = DMA_MSIZE4;
    dma_inittypedef.dst_msize            = DMA_MSIZE4;
    dma_inittypedef.src_addr_type        = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_addr_type        = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.src_width            = DMA_WIDTH8;
    dma_inittypedef.dst_width            = DMA_WIDTH8;
    dma_inittypedef.dst_per              = DMA_I2C_TX_REQ;
    dma_inittypedef.src_per              = DMA_I2C_TX_REQ;
    dma_inittypedef.fifo_mode_en         = DISABLE;
    dma_inittypedef.max_abrst            = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority      = DMA_PRIORITY0;
    dma_inittypedef.int_en               = DISABLE;

    DMA_Init(DMA, chlx, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
}

static void i2c_to_mem_init(uint8_t chlx)
{
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);

    DMA_InitTypeDef dma_inittypedef;
    DMA_Clear_All_Interrupt_Cmd(DMA);

    dma_inittypedef.llp_src_en           = DISABLE;
    dma_inittypedef.llp_dst_en           = DISABLE;
    dma_inittypedef.reload_src_en        = DISABLE;
    dma_inittypedef.reload_dst_en        = DISABLE;
    dma_inittypedef.direction            = PER_TO_MEM_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize            = DMA_MSIZE4;
    dma_inittypedef.dst_msize            = DMA_MSIZE4;
    dma_inittypedef.src_addr_type        = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.dst_addr_type        = DMA_ADDRESS_INCREASE;
    dma_inittypedef.src_width            = DMA_WIDTH8;
    dma_inittypedef.dst_width            = DMA_WIDTH8;
    dma_inittypedef.dst_per              = DMA_I2C_RX_REQ;
    dma_inittypedef.src_per              = DMA_I2C_RX_REQ;
    dma_inittypedef.fifo_mode_en         = DISABLE;
    dma_inittypedef.max_abrst            = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority      = DMA_PRIORITY0;
    dma_inittypedef.int_en               = DISABLE;

    DMA_Init(DMA, chlx, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
}

static void write_dma(uint8_t *pbuffer, uint8_t addr, uint8_t numbyte)
{
    I2C_Write_Data(I2C, addr);

    while (I2C_Flag_GetStatBit(I2C, I2C_FLAG_TFE) == RESET) {}

    I2C_DMACtl(I2C, I2C_TX_DMA_EN, ENABLE);
    I2C_Set_DMA_TDLR(I2C, 4);

    mem_to_i2c_init(DMA_CHANNEL0);
    DMA_Set_Addr(DMA, DMA_CHANNEL0, (uint32_t)mmap_to_sys((uint32_t)pbuffer), (uint32_t)(&(I2C->DATA_CMD)), numbyte, 0);

    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL0, ENABLE);
}

static void read_dma(uint8_t *pbuffer, uint8_t addr, uint8_t numbyte)
{
    I2C_DMACtl(I2C, I2C_RX_DMA_EN, ENABLE);
    I2C_Set_DMA_RDLR(I2C, 3);

    i2c_to_mem_init(DMA_CHANNEL1);
    DMA_Set_Addr(DMA, DMA_CHANNEL1, (uint32_t)(&(I2C->DATA_CMD)), (uint32_t)mmap_to_sys((uint32_t)pbuffer), numbyte, 0);

    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL1, ENABLE);

    I2C_Write_Data(I2C, addr);

    while (I2C_Flag_GetStatBit(I2C, I2C_FLAG_TFE) == RESET) {}
    for (uint8_t i = 0; i < numbyte; i++)
    {
        I2C_Read_Cmd(I2C, 0);
        while (I2C_Flag_GetStatBit(I2C, I2C_FLAG_TFNF) == RESET) {}
    }
}

static int i2c_test(void)
{
    for(uint8_t i = 0; i < sizeof(writeBuff); i++)
    {
        writeBuff[i] = i + 0xC0;
    }

    memset(readBuff, 0, sizeof(readBuff));

    write_dma(writeBuff, 0x00, sizeof(writeBuff));
    system_delay_ms(100);
    read_dma(readBuff, 0x00, sizeof(readBuff));
    system_delay_ms(100);

    return memcmp(readBuff, writeBuff, sizeof(writeBuff));
}

static void uart0_config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_16 | GPIO_PIN_17;    /* uart0 pin config */
    GPIO_InitStructure.Alternate = GPIO_AF16_UART0 | GPIO_AF17_UART0;
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