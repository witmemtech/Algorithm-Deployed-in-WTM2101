/**
  ******************************************************************************
  * @file    main.c
  * @brief   This example describes how to use the I2C to request data
  *          from a sencor.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "main.h"

static void system_clock_init(void);
static void uart0_config(void);

void main(void)
{
    float t, h;

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

    SHT20_init();
    I2C_TimeOutPeriod_Set(0xFFFFF);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    SHT20_value_update();
    SHT20_CalcT_C(&t);
    SHT20_CalcRH(&h);
    printf("T:  %f\r\nHR: %f\r\n", t, h);

    while(1) {}
}

static void system_clock_init(void)
{
    int ret = 0;
    /* The clock instance. */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /* Construct 24mosc related configuration parameters */
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_EXTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = DISABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /* Initialize the clock instance */
    ret = hal_clock_init(hal_clock_instance, HAL_CLOCK_24MOSC | HAL_CLOCK_PLL, HAL_CLOCK_PLL, &hal_clock_24mosc_Configuration, 4, 3, 1);

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