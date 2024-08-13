/**
* @file    main.c
* @brief   The Source Codes for the main Functions
* @date    2023-04-12
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

#include "main.h"

static void uart_init(void);
static void clock_init(void);
static void zd25wq_flash_example(void);

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
    clock_init();

    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();
   
    /* Tset the zd25wq flash*/
    zd25wq_flash_example();

    while(1)
    {
        /* The program will not run here */
        system_delay_s(1);
        printf("hello world witmem\r\n");
    }
}

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

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

static void clock_init(void)
{
    int ret = 0;
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
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

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

void zd25wq_flash_example(void)
{
    volatile int ret = 0,k = 0;
    uint8_t read_buff[256] = {0},write_buff[300] = {0};
    ZD25WQ zd25wq_hd;
    uint16_t write_crc16 = 0,read_crc16 = 0;
    for(int i = 0;i < sizeof(write_buff);i++)
    {
        write_buff[i] = i;
    }
        
    /* init the zd25wq_hd*/
    ret = ZD25WQ_qspi_init(&zd25wq_hd);
    if(ret < 0)
    {
        printf("ZD25WQ_qspi_init error:%d\r\n",ret);
    }

    /* open the zd25wq flash */
    zd25wq_hd.clock_divider = 1; 
    ret = ZD25WQ_open(&zd25wq_hd,QSPI,ZD25WQ_QSPI_1LINE,DISABLE,0,DISABLE,0);
    if(ret < 0)
    {
        printf("ZD25WQ_open error:%d\r\n",ret);
    }
   
    /* chip protect */
    ret = ZD25WQ_chip_write_protect(&zd25wq_hd,DISABLE);
    printf("ZD25WQ_chip_write_protect finish:%d\r\n",ret);

    /*chip is erased*/
    ret = ZD25WQ_chip_erase(&zd25wq_hd);
    printf("ZD25WQ_chip_erase finish:%d\r\n",ret);

    /*write data*/
    k = 0;
    write_crc16 = 0;
    for(int i= 0;i < zd25wq_hd.flash_size;i+=zd25wq_hd.page_size)
    {
       write_crc16 = crc16_compute(write_buff + k, zd25wq_hd.page_size, &write_crc16);
       ZD25WQ_write(&zd25wq_hd,i,write_buff+k,zd25wq_hd.page_size);
       k = (++k) % 32;
    }
    printf("ZD25WQ write crc16:%d\r\n",write_crc16);
 
    /*read data*/
    read_crc16 = 0;
    for(int i= 0;i < zd25wq_hd.flash_size;i+=zd25wq_hd.page_size)
    {
       ZD25WQ_read(&zd25wq_hd,i,read_buff,zd25wq_hd.page_size);
       read_crc16 = crc16_compute(read_buff, zd25wq_hd.page_size, &read_crc16);
    }
    printf("ZD25WQ read crc16:%d\r\n",read_crc16);

    if(read_crc16 == write_crc16)
        printf("ZD25WQ flash test success\r\n");
    else 
        printf("ZD25WQ flash test failure,write crc16 value :%d---read crc16 value :%d\r\n",write_crc16,read_crc16);

    /*close*/
    ZD25WQ_close(&zd25wq_hd);
}
