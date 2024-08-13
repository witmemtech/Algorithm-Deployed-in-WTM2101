/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the spi to control flash 
  *          continuously converted data.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"

static void spi_master_config(void);
static void system_clock_init(void);
static void uart0_config(void);

void main(void)
{
    uint8_t flash_id[FLASH_ID_SIZE];
    uint8_t read_data[FLASH_PAGE_SIZE] = {0};
    uint8_t write_data[FLASH_PAGE_SIZE] = {0};
    uint32_t addr = 0;
    int ret = 0;

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

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);

    /* Application entry */
    spi_read_flash_id(flash_id);
    spi_flash_global_block_unlock();
    spi_flash_write_enable();
    printf("read ID 0x%x 0x%x\r\n", flash_id[0], flash_id[1]);

    printf("page erase\r\n");
    spi_flash_page_erase(addr);
    spi_flash_read(read_data, addr, sizeof(read_data));

    for (int i = 0;i < sizeof(read_data);i++)
    {
        if (read_data[i] != 0xFF) 
        {
            printf("erase failed addr %d 0x%x\r\n", i, read_data[i]);
            ret = 1;
        }
    }

    if (ret == 0) 
    {
        printf("page erase succeed\r\n");
    }

    for (int i = 0;i < sizeof(write_data);i++) 
    {
        write_data[i] = i;
    }

    spi_flash_write_enable();
    spi_flash_page_prog(write_data, addr, sizeof(write_data));

    spi_flash_read(read_data, addr, sizeof(read_data));
    for (int i = 0;i < sizeof(read_data);i++) 
    {
        if (read_data[i] != write_data[i]) 
        {
            printf("write failed addr %d 0x%x\r\n", i, read_data[i]);
            ret = 1;
        }
    }

    if (ret == 0) 
    {
        printf("check data pass\r\n");
    } 
    else
    {
        printf("check data failed\r\n");
    }

    while(1){};
}


static void spi_master_config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef spi_init_type;
    RCC_CLK_EN_Ctl(RCC_SPIM_PCLKEN,ENABLE);

    SPI_Uninit(SPIM);

    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3;    /* spi master pin config */
    GPIO_InitStructure.Alternate = GPIO_AF0_SPI0 | GPIO_AF2_SPI0 | GPIO_AF3_SPI0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* init cs io gpio1 */
    GPIO_InitStructure.Pin = GPIO_PIN_1;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate = GPIO_AF1_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    spi_cs_high();

    spi_init_type.cpol = SPI_CPOL_0;                /* cpol 0 */
    spi_init_type.cpha = SPI_CPHA_0;                /* cpha 0 */
    spi_init_type.datasize = SPI_DATASIZE_8B;       /* spi data width 8 bit */
    spi_init_type.clk_div = 12;                     /* spi speed = AHB / 12 */
    spi_init_type.nss = SPI_SOFTWARE_NSS;           /* cs pin sofewave control */
    SPI_Init(SPIM, &spi_init_type);

    SPI_Cmd(SPIM, ENABLE);
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

static void uart0_config()
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

