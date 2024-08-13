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

Bool rdsr_flag = FALSE;
static QSPI_CtlInitTypeDef qspi_init;

static void uart_init(void);
static void qspi_config(void);
static void w25q64jv_qspi_test(void);
static void system_clock_init(void);

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
    w25q64jv_qspi_test();

    while(1){};
}

void QSPI_IRQHandler(void)
{
    if(QSPI_Get_Int_Pending_Status(QSPI) & QSPI_INT_POLLING_MATCH)
    {    
        QSPI_Set_Stop_Cmd(QSPI);
        QSPI_Clear_Int_Pending_Cmd(QSPI,QSPI_INT_POLLING_MATCH);
        rdsr_flag = TRUE;
    }
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

static void qspi_gpio_config(void)
{
    GPIO_InitTypeDef Qspi_InitStructure;

    Qspi_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17 | GPIO_PIN_18 | GPIO_PIN_19;
    Qspi_InitStructure.Alternate = GPIO_AF14_QSPI | GPIO_AF15_QSPI | GPIO_AF16_QSPI | GPIO_AF17_QSPI | GPIO_AF18_QSPI | GPIO_AF19_QSPI;
    GPIO_Init(GPIOA, &Qspi_InitStructure);
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

void w25q64jv_qspi_test(void)
{
    uint8_t test_value[100] = {0},read_buffer[512];
    uint8_t write_buffer[] = {0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb,0xaa,0xee,0xee,0x11,0x22,0x33,0x44
    ,0x11,0x22,0x33,0x44,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb,0xaa,0xee,0xee,0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb
    ,0x11,0x22,0x33,0x44,0x11,0x22,0x33,0x44,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88
    ,0x11,0x22,0x33,0x44,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb,0xaa,0xee,0xee,0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb
    ,0x11,0x22,0x33,0x44,0x11,0x22,0x33,0x44,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88
    ,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb,0xaa,0xee,0xee,0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb
    ,0x11,0x22,0x33,0x44,0x11,0x22,0x33,0x44,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88
    ,0x11,0x22,0x33,0x44,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb,0xaa,0xee,0xee,0xaa,0xaa,0xaa,0xaa,0xee,0xee,0xdd,0xcc,0xbb
    ,0x11,0x22,0x33,0x44,0x11,0x22,0x33,0x44,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};  

    int ret = 0;
    int i = 0;
    uint8_t id[3] = {0};
    uint8_t status = 0;
    int address = 0,write_length = 0,buff_length = 0,read_address = 0,read_length = 0,test_length = 0;
    uint16_t crc16 = 0,crc16__= 0;

    W25q64jv W25q64jv_hd;
    w25q64jv_qspi_init(&W25q64jv_hd);
    W25q64jv_hd.send_dma_flag = 0;
    W25q64jv_hd.receive_dma_flag = 0;
    W25q64jv_hd.qspi_ctl->sph = QSPI_SPH_0;
    W25q64jv_hd.qspi_ctl->spo = QSPI_SPO_0;

    memset(read_buffer, 0x0, sizeof(read_buffer));

    ret = w25q64jv_open(&W25q64jv_hd, QSPI, W25Q64JV_QSPI_1LINE);
    if (ret == 0)
        printf("w25q64jv open succeed\r\n");
    else
        printf("w25q64jv open failed\r\n");

    w25q64jv_read_jedec_id(&W25q64jv_hd, id);
    printf("read JEDEC ID SUCCEED 0x%x 0x%x 0x%x\r\n", id[0], id[1], id[2]);

    ret = w25q64jv_sector_erase(&W25q64jv_hd, SECTOR_ERASE_CMD, 0x0);
    if (ret < 0)
        printf("w25q64jv_chip_erase is failure\r\n");
    else
        printf("w25q64jv_chip_erase is succeed\r\n");

    test_length = 256;
    for (address = 0; address < test_length;)
    {
        write_length = 256;
        printf("write_length:%d\r\n", write_length);

        ret = w25q64jv_page_program(&W25q64jv_hd,address,write_buffer,write_length);
        if (ret < 0) 
        {
            printf("W25q64jv_write is failure:%d\r\n",ret);
        }

        crc16 = crc16check_calc(write_buffer, write_length, &crc16);
        address+=write_length; 
    }
    crc16__  = crc16;

    crc16 = 0;
    for (read_address = 0; read_address < test_length;)
    {
        memset(read_buffer,0,sizeof(read_buffer));
        read_length = rand() % 512 + 200;
        read_length = (read_length > sizeof(read_buffer))?sizeof(read_buffer):read_length;
        read_length = ((read_address + read_length - test_length) > 0)?(test_length - read_address):read_length;
        
        printf("read_length:%d\r\n", read_length);

        ret = w25q64jv_read(&W25q64jv_hd,read_address,read_buffer,read_length);
        if (ret < 0)
            printf("W25q64jv_read is failure\r\n");
        crc16 = crc16check_calc(read_buffer, read_length, &crc16);
        read_address+=read_length;
    }
    if (crc16__ == crc16){
        printf("The crc check passed\r\n");
    }
    else{
        printf("The crc check failed\r\n");
    }

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
