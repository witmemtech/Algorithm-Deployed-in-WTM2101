/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the QSPI.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"

#define FLASH_DMA_TEST_LEN (200)
#define FLASH_WRITE_ENABLE_CMD() send_cmd(0x06)

static QSPI_CtlInitTypeDef qspi_init;

static int qspi_send_dma_init(uint8_t dma_channel);
static int qspi_receive_dma_init(uint8_t dma_channel);
static void qspi_config(void);
static void system_clock_init(void);
static void qspi_dma_test(void);
static void uart_init(void);

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Reset all peripherals except PMU and GPIO*/
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
    system_config_dump();


    /* Application entry */
    qspi_config();
    qspi_send_dma_init(DMA_CHANNEL0);
    qspi_receive_dma_init(DMA_CHANNEL1);
    qspi_dma_test();

    while(1){};
}

static void qspi_gpio_config(void)
{
    GPIO_InitTypeDef Qspi_InitStructure;

    Qspi_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17 | GPIO_PIN_18 | GPIO_PIN_19;
    Qspi_InitStructure.Alternate = GPIO_AF14_QSPI | GPIO_AF15_QSPI | GPIO_AF16_QSPI | GPIO_AF17_QSPI | GPIO_AF18_QSPI | GPIO_AF19_QSPI;
    GPIO_Init(GPIOA, &Qspi_InitStructure);
}

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN, ENABLE);
   
    /*the gpio4,gpio5*/
    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.Alternate = GPIO_AF4_UART0 | GPIO_AF5_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);
}

void qspi_config(void)
{
    RCC_QSPI_Set_ClkDiv(1);
    RCC_CLK_EN_Ctl(RCC_QSPI_PCLKEN,ENABLE);

    qspi_gpio_config();
    
    qspi_init.sph = QSPI_SPH_0;
    qspi_init.spo = QSPI_SPO_0;
    qspi_init.sample_clk_sel = QSPI_SAMPLE_NO_REVERSE_CLOCK;
    qspi_init.read_delay_time = 0;
    qspi_init.dummy_cycle = 0;
}

static void send_cmd(uint8_t cmd)
{
    qspi_init.instructionmode = QSPI_INSTRUCTION_1_LINE;

    qspi_init.alternatebytessize = QSPI_ALTERNATE_BYTES_32_BITS;
    qspi_init.alternatebytemode = QSPI_ALTERNATE_BYTES_NONE;

    qspi_init.addressmode = QSPI_ADDRESS_NONE;
    qspi_init.addresssize = QSPI_ADDRESS_24_BITS;

    qspi_init.dmode_sel = QSPI_WRITE_DATA_MODE;
    qspi_init.datamode = QSPI_DATA_NONE;

    QSPI_Ctl_Init(QSPI, &qspi_init);

    QSPI_Set_Instrction(QSPI, cmd);
    QSPI_Set_Dummy_cycle(QSPI, 0x00);
    QSPI_Set_Start_Cmd(QSPI);
    while (QSPI_Get_Status(QSPI));
}

static uint16_t dual_read_mid_did(void)
{
    uint32_t mid_did = 0;
    qspi_init.instructionmode = QSPI_INSTRUCTION_1_LINE;

    qspi_init.alternatebytessize = QSPI_ALTERNATE_BYTES_32_BITS;
    qspi_init.alternatebytemode = QSPI_ALTERNATE_BYTES_NONE;

    qspi_init.addressmode = QSPI_ADDRESS_2_LINES;
    qspi_init.addresssize = QSPI_ADDRESS_32_BITS;

    qspi_init.dmode_sel = QSPI_READ_DATA_MODE;
    qspi_init.datamode = QSPI_DATA_2_LINES;

    QSPI_Ctl_Init(QSPI, &qspi_init);

    QSPI_Set_Instrction(QSPI, 0x92);
    QSPI_Set_Address(QSPI, 0xffffffff);
    QSPI_Set_Alternatebyte(QSPI, 0x00);
    QSPI_Set_Dummy_cycle(QSPI, 0);

    QSPI_Receive(QSPI, &mid_did, 2);
    return (mid_did >> 8) | (mid_did << 8);
}

static int qspi_dma_receive(QSPI_TypeDef *QSPIx, uint32_t *data, int length_bytes, uint8_t dma_channel)
{
    int block_size = 0;

    QSPIx->QSPI_CTRL |= QSPI_QSPI_CTRL_DMODE_SEL_Msk;
    QSPIx->QSPI_DATA_NUM = length_bytes - 1;
    QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_INDIRECT_ACT_Msk;

    block_size = length_bytes % 4 ? length_bytes / 4 + 1 : length_bytes / 4;
    DMA_Set_Addr(DMA, dma_channel, (uint32_t) & (QSPIx->AFIFO_RDATA), (uint32_t)mmap_to_sys((uint32_t)data), block_size, 0);
   
    while ((QSPIx->AFIFO_STATUS & QSPI_READ_AFIFO_EMPTY));

    DMA_Set_Channel_Enable_Cmd(DMA, dma_channel, ENABLE);

    while (0 == (DMA_Get_Transfer_Interrupt_Status(DMA) & DMA_CHANNEL1_INT_FLAG));

    DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL1);

    return length_bytes;
}

static uint16_t flash_read(uint32_t *p_buff, uint32_t addr, uint32_t len_bytes, uint8_t io_num)
{
    uint8_t cmd = 0xbb;
    if (io_num > 1)
    {
        qspi_init.instructionmode = QSPI_INSTRUCTION_1_LINE;

        qspi_init.alternatebytessize = QSPI_ALTERNATE_BYTES_8_BITS;
        qspi_init.alternatebytemode = QSPI_ALTERNATE_BYTES_2_LINES;

        qspi_init.addressmode = QSPI_ADDRESS_2_LINES;
        qspi_init.addresssize = QSPI_ADDRESS_24_BITS;

        qspi_init.dmode_sel = QSPI_READ_DATA_MODE;
        qspi_init.datamode = QSPI_DATA_2_LINES;
    }
    else
    {
        cmd = 0x03;
        qspi_init.instructionmode = QSPI_INSTRUCTION_1_LINE;

        qspi_init.alternatebytessize = QSPI_ALTERNATE_BYTES_8_BITS;
        qspi_init.alternatebytemode = QSPI_ALTERNATE_BYTES_NONE;

        qspi_init.addressmode = QSPI_ADDRESS_1_LINE;
        qspi_init.addresssize = QSPI_ADDRESS_24_BITS;

        qspi_init.dmode_sel = QSPI_READ_DATA_MODE;
        qspi_init.datamode = QSPI_DATA_1_LINE;
    }

    QSPI_Ctl_Init(QSPI, &qspi_init);

    QSPI_Set_Instrction(QSPI, cmd);
    QSPI_Set_Address(QSPI, addr);
    QSPI_Set_Alternatebyte(QSPI, 0x00);
    QSPI_Set_Dummy_cycle(QSPI, 0);
    qspi_dma_receive(QSPI, p_buff, len_bytes, DMA_CHANNEL1);
    return 0;
}

static uint8_t read_status_register(void)
{
    uint32_t ret = 0xff;
    qspi_init.instructionmode = QSPI_INSTRUCTION_1_LINE;

    qspi_init.alternatebytessize = QSPI_ALTERNATE_BYTES_32_BITS;
    qspi_init.alternatebytemode = QSPI_ALTERNATE_BYTES_NONE;

    qspi_init.addressmode = QSPI_ADDRESS_NONE;
    qspi_init.addresssize = QSPI_ADDRESS_24_BITS;

    qspi_init.dmode_sel = QSPI_WRITE_DATA_MODE;
    qspi_init.datamode = QSPI_DATA_1_LINE;

    QSPI_Ctl_Init(QSPI, &qspi_init);

    QSPI_Set_Instrction(QSPI, 0x05);
    QSPI_Set_Dummy_cycle(QSPI, 0x00);
    QSPI_Receive(QSPI, &ret, 1);

    return ret;
}

static uint8_t flash_is_busy(void)
{
    return read_status_register() & 0x01;
}

static int32_t sector_erase(uint32_t addr)
{
    int ret = 0;
    FLASH_WRITE_ENABLE_CMD();
    qspi_init.instructionmode = QSPI_INSTRUCTION_1_LINE;

    qspi_init.alternatebytessize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_init.alternatebytemode = QSPI_ALTERNATE_BYTES_NONE;

    qspi_init.addressmode = QSPI_ADDRESS_1_LINE;
    qspi_init.addresssize = QSPI_ADDRESS_24_BITS;

    qspi_init.dmode_sel = QSPI_READ_DATA_MODE;
    qspi_init.datamode = QSPI_DATA_NONE;

    QSPI_Ctl_Init(QSPI, &qspi_init);
    QSPI_Set_Instrction(QSPI, 0x20);
    QSPI_Set_Address(QSPI, addr);
    QSPI_Set_Dummy_cycle(QSPI, 0);
    QSPI_Set_Start_Cmd(QSPI);

    while (flash_is_busy() != 0);

    return 0;
}

static int qspi_dma_transimit(QSPI_TypeDef *QSPIx, uint32_t *data, int length_bytes, uint8_t dma_channel)
{
    int index_size = 0, block_size = 0, total_size = 0, flag = 0;
    assert_param(QSPIx != NULL);
    assert_param(data != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_DMODE_SEL_Msk;
    QSPIx->QSPI_DATA_NUM = length_bytes - 1;

    total_size = length_bytes;
    while (total_size > 0)
    {
        block_size = total_size > 32 ? 32 : total_size;
        total_size -= block_size;
        block_size = (block_size == 32) ? 8 : block_size / 4 + 1;
        DMA_Set_Addr(DMA, dma_channel, (uint32_t)mmap_to_sys((uint32_t)(data + index_size)), (uint32_t) & (QSPIx->AFIFO_WDATA), block_size, 0);
        DMA_Set_Channel_Enable_Cmd(DMA, dma_channel, ENABLE);
        if (!flag)
        {
            flag = 1;
            QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_INDIRECT_ACT_Msk;
        }

        while ((QSPIx->AFIFO_STATUS & QSPI_WRITE_AFIFO_EMPTY));

        while (!(QSPIx->AFIFO_STATUS & QSPI_WRITE_AFIFO_EMPTY));

        index_size += block_size;
    }

    while (!(QSPIx->AFIFO_STATUS & QSPI_WRITE_AFIFO_EMPTY));

    return length_bytes;
}

static int page_program(uint32_t *p_buff, uint32_t addr, uint32_t len_bytes, uint8_t io_num)
{
    uint32_t cmd = 0xa2;
    FLASH_WRITE_ENABLE_CMD();
    qspi_init.instructionmode = QSPI_INSTRUCTION_1_LINE;

    qspi_init.alternatebytessize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_init.alternatebytemode = QSPI_ALTERNATE_BYTES_NONE;

    qspi_init.addressmode = QSPI_ADDRESS_1_LINE;
    qspi_init.addresssize = QSPI_ADDRESS_24_BITS;
    if (io_num > 1)
    {
        qspi_init.datamode = QSPI_DATA_2_LINES;
    }
    else
    {
        qspi_init.datamode = QSPI_DATA_1_LINE;
        cmd = 0x02;
    }

    QSPI_Ctl_Init(QSPI, &qspi_init);
    QSPI_Set_Instrction(QSPI, cmd);
    QSPI_Set_Address(QSPI, addr);
    QSPI_Set_Dummy_cycle(QSPI, 0);
    qspi_dma_transimit(QSPI, p_buff, len_bytes, DMA_CHANNEL0);
    while (flash_is_busy() != 0)
    ;
    return 0;
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

void qspi_dma_test(void)
{
    int err = 0;
    uint8_t write_buff[FLASH_DMA_TEST_LEN];
    uint8_t read_buff[FLASH_DMA_TEST_LEN];

    sector_erase(0);

    for (uint8_t i = 0; i < FLASH_DMA_TEST_LEN; i++)
    {
        write_buff[i] = i + 10;
    }
    page_program((uint32_t *)write_buff, 0, FLASH_DMA_TEST_LEN, 1);
    flash_read((uint32_t *)read_buff, 0, FLASH_DMA_TEST_LEN, 1);
    for (uint8_t i = 0; i < FLASH_DMA_TEST_LEN; i++)
    {
        if (write_buff[i] != read_buff[i])
        {
            err++;
        }
    }
    if (err > 0)
    {
        printf("----------------------------------------1 line err = %d\r\n", err);
    }
    else
    {
        printf("QSPI OK(1 line)\r\n\r\n");
    }

    err = 0;
    sector_erase(0x01 << 20);
    for (uint8_t i = 0; i < FLASH_DMA_TEST_LEN; i++)
    {
        write_buff[i] = i;
    }
    page_program((uint32_t *)write_buff, 0x01 << 20, FLASH_DMA_TEST_LEN, 2);
    flash_read((uint32_t *)read_buff, 0x01 << 20, FLASH_DMA_TEST_LEN, 2);
    for (uint8_t i = 0; i < FLASH_DMA_TEST_LEN; i++)
    {
        if (write_buff[i] != read_buff[i])
        {
            err++;
        }
    }
    if (err > 0)
    {
        printf("--------------------------------------------2 line err = %d\r\n", err);
    }
    else
    {
        printf("QSPI OK(2 line)\r\n");
    }
}
static int qspi_send_dma_init(uint8_t dma_channel)
{
    DMA_InitTypeDef dam_init_str = {0};

    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN,ENABLE);
    QSPI_Set_Send_Dma_Cmd(QSPI, 1, ENABLE);

    dam_init_str.llp_src_en = DISABLE;
    dam_init_str.llp_dst_en = DISABLE;
    dam_init_str.reload_src_en = DISABLE;
    dam_init_str.reload_dst_en = DISABLE;
    dam_init_str.direction = MEM_TO_PER_FLOW_CTOL_DMA;
    dam_init_str.src_msize = DMA_MSIZE1;
    dam_init_str.dst_msize = DMA_MSIZE1;
    dam_init_str.src_addr_type = DMA_ADDRESS_INCREASE;
    dam_init_str.dst_addr_type = DMA_ADDRESS_NO_CHANGE;
    dam_init_str.src_width = DMA_WIDTH32;
    dam_init_str.dst_width = DMA_WIDTH32;
    dam_init_str.dst_per = DMA_QSPI_TX_REQ;
    dam_init_str.src_per = DMA_QSPI_TX_REQ;

    dam_init_str.fifo_mode_en = DISABLE;
    dam_init_str.max_abrst = 0;
    dam_init_str.src_handshaking_type = DMA_HW_HANDSHAKE;
    dam_init_str.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dam_init_str.chanel_priority = DMA_PRIORITY0;
    dam_init_str.int_en = DISABLE;

    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Init(DMA, dma_channel, &dam_init_str);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    return 0;
}

static int qspi_receive_dma_init(uint8_t dma_channel)
{
    DMA_InitTypeDef dam_init_str = {0};

    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN,ENABLE);
    QSPI_Set_Receive_Dma_Cmd(QSPI, 1, ENABLE);

    dam_init_str.llp_src_en = DISABLE;
    dam_init_str.llp_dst_en = DISABLE;
    dam_init_str.reload_src_en = DISABLE;
    dam_init_str.reload_dst_en = DISABLE;
    dam_init_str.direction = PER_TO_MEM_FLOW_CTOL_DMA;
    dam_init_str.src_msize = DMA_MSIZE1;
    dam_init_str.dst_msize = DMA_MSIZE1;
    dam_init_str.src_addr_type = DMA_ADDRESS_NO_CHANGE;
    dam_init_str.dst_addr_type = DMA_ADDRESS_INCREASE;
    dam_init_str.src_width = DMA_WIDTH32;
    dam_init_str.dst_width = DMA_WIDTH32;
    dam_init_str.dst_per = DMA_QSPI_RX_REQ;
    dam_init_str.src_per = DMA_QSPI_RX_REQ;

    dam_init_str.fifo_mode_en = DISABLE;
    dam_init_str.max_abrst = 0;
    dam_init_str.src_handshaking_type = DMA_HW_HANDSHAKE;
    dam_init_str.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dam_init_str.chanel_priority = DMA_PRIORITY0;
    dam_init_str.int_en = ENABLE;

    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Init(DMA, dma_channel, &dam_init_str);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, dma_channel, ENABLE);

    return 1;
}