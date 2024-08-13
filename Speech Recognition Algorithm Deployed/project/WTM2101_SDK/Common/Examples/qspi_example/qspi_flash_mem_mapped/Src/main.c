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

#define READ8(addr) (uint8_t)(*(volatile uint8_t *)(addr))
#define READ16(addr) *(volatile short unsigned int *)(addr)
#define READ32(addr) (uint32_t)(*(volatile uint32_t *)(addr))

#define FLASH_MEM_ADDR_BASE  (0x60000000)

static void uart_init(void);
static void qspi_config(void);
static void system_clock_init(void);
static int qspi_flash_mem_mapped_test(void);

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
    qspi_flash_mem_mapped_test();
    
    printf("end\r\n");

    while(1){};
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

    GPIO_InitTypeDef Qspi_InitStructure;

    Qspi_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17 | GPIO_PIN_18 | GPIO_PIN_19;
    Qspi_InitStructure.Alternate = GPIO_AF14_QSPI | GPIO_AF15_QSPI | GPIO_AF16_QSPI | GPIO_AF17_QSPI | GPIO_AF18_QSPI | GPIO_AF19_QSPI;
    GPIO_Init(GPIOA, &Qspi_InitStructure);
}

int qspi_flash_mem_mapped_test(void)
{
    uint8_t read_buff[10] = {0};
    for( int i = 0; i <sizeof(read_buff) / sizeof(read_buff[0]); i++){

        read_buff[i] = READ8(FLASH_MEM_ADDR_BASE+i);
        printf("0x%08x : 0x%08x\r\n", FLASH_MEM_ADDR_BASE+i, read_buff[i]);
    }

    return 1;
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
