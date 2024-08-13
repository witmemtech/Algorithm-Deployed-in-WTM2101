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

static Mtd_Info mtd =
{
    .type = MTD_TYPE_NORFLASH,
    .name = "zd25wqinfo",
    .flags = MTD_FLAGS_WRITEABLE,
    .mit = MIT_SPI_CORE,
    .met = MET_HARDWARE,
    .mit_path = NULL,
    .blockstart = 1,
    .blocksize = 1,
    .blockcount = 64,   /*当前大小64 * pagesize * blocksize * zoneofblocks = 128K */
    .pageszie = 4096,
    .erasesize = 4096,
    .writesize = 4096,
    .oobsize = 0,
    .zoneofblocks = 1,
    .userdata = NULL,
    .nor_base = 0x00,

    .init = zd25wq_mtd_init,
    .exit = zd25wq_mtd_exit,
    .protect = zd25wq_mtd_protect,
    .erase = zd25wq_mtd_erase,
    .pread = zd25wq_mtd_pread,
    .pwrite = zd25wq_mtd_pwrite,
};


static void uart_init(void);
static void clock_init(void);
static void mtd_zd25wq_flash_example(void);

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
   
    /* Tset the mtd zd25wq flash*/
    mtd_zd25wq_flash_example();

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

void mtd_zd25wq_flash_example(void)
{
    volatile int ret = 0,k = 0;
    uint8_t read_buff[256] = {0},write_buff[512] = {0};
    ZD25WQ zd25wq_hd;
    uint16_t write_crc16 = 0,read_crc16 = 0;
    for(int i = 0;i < sizeof(write_buff);i++)
    {
        write_buff[i] = i;
    }
    printf("mtd test start\r\n");

    /*init the mtd device*/    
    mtd.userdata = &zd25wq_hd;
    ret = mtd_init(&mtd);
    if (ret <= 0) printf("mtd_init fail:%d\r\n", ret);
    
    /* back to front*/
    ret = mtd_lseek(&mtd, 0, 0, MTD_SET);
    if (ret < 0) printf("mtd_lseek fail:%d\r\n", ret);

    /* chip protect */
    ret = mtd_protect(&mtd,DISABLE);
    if (ret < 0) printf("mtd_protect fail:%d\r\n", ret);
      
    printf("mtd write test start\r\n");
    /*write data*/
    k = 0;
    write_crc16 = 0;
    for(int i= 0;i < mtd.blockcount * mtd.pageszie;)
    {
       k = rand() % 256;
       if((i+k) > mtd.blockcount * mtd.pageszie)
          k = mtd.blockcount * mtd.pageszie - i;
       write_crc16 = crc16_compute(write_buff + k, k, &write_crc16);
       ret = mtd_write(&mtd,0,write_buff + k,k);
       if (ret <= 0) printf("mtd_write fail:%d\r\n", ret);
       i+=k;
    }
    printf("mtd write crc16:%d\r\n",write_crc16);

    /* back to front*/
    ret = mtd_lseek(&mtd, 0, 0, MTD_SET);
    if (ret < 0) printf("mtd_lseek fail:%d\r\n", ret);
    
    printf("mtd read test start\r\n");
    /*read data*/
    k = 0;
    read_crc16 = 0;
    for(int i= 0;i < mtd.blockcount * mtd.pageszie;)
    {
       k = rand() % 256;
       if((i+k) > mtd.blockcount * mtd.pageszie)
          k = mtd.blockcount * mtd.pageszie - i;
       ret = mtd_read(&mtd,0,read_buff,k);
       if (ret <= 0) printf("mtd_lseek fail:%d\r\n", ret);
       read_crc16 = crc16_compute(read_buff, k, &read_crc16);
       i+=k;
    }
    printf("mtd read crc16:%d\r\n",read_crc16);

    if(read_crc16 == write_crc16)
        printf("mtd ZD25WQ flash test success\r\n");
    else 
        printf("mtd ZD25WQ flash test failure,write crc16 value :%d---read crc16 value :%d\r\n",write_crc16,read_crc16);

    /*close*/
    mtd_exit(&mtd);
}
