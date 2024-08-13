/**
  ******************************************************************************
  * @file    main.c
  * @brief   This file is a template project for IDE users.
  * @date    2023-02-10
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "main.h"

static void check_links(void);
static void check_mcycle(void);
static void puthex(uint8_t v);
static void memdbg(const void* buf, int nr_bytes);
static void uart0_config(void);
static void system_clock_init(void);

void main(void)
{
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

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    check_links();

    while(1) {};
}

void check_links(void)
{
    extern uint32_t __vectors_start__;
    extern uint32_t __vectors_end__;
    extern uint32_t __text_start__;
    extern uint32_t __text_end__;
    extern uint32_t __text_load_start__;
    extern uint32_t __rodata_load_start__;
    extern uint32_t __rodata_start__;
    extern uint32_t __rodata_end__;
    extern uint32_t __srodata_start__;
    extern uint32_t __srodata_end__;
    extern uint32_t __srodata_load_start__;
    extern uint32_t __tdata_start__;
    extern uint32_t __tdata_end__;
    extern uint32_t __tdata_load_start__;
    extern uint32_t __data_start__;
    extern uint32_t __data_end__;
    extern uint32_t __data_load_start__;
    extern uint32_t __bss_start__;
    extern uint32_t __bss_end__;
    extern uint32_t __bss_load_start__;
    extern uint32_t __sbss_start__;
    extern uint32_t __sbss_end__;
    extern uint32_t __sbss_load_start__;

    printf(".vectors: %p - %p\r\n", &__vectors_start__, &__vectors_end__);
    printf("\n");

    printf(".text   : %p - %p, load %p\r\n", &__text_start__, &__text_end__, &__text_load_start__);
    memdbg(&__text_start__, 16);
    printf("\r\n");

    printf(".rodata : %p - %p, load %p\r\n", &__rodata_start__, &__rodata_end__, &__rodata_load_start__);
    printf(" @start\r\n");
    memdbg(&__rodata_start__, 16);
    printf(" @end-16\r\n");
    memdbg((char*)&__rodata_end__ - 16, 16);
    printf("\r\n");

    printf(".data   : %p - %p, load %p\r\n", &__data_start__, &__data_end__, &__data_load_start__);
    printf(" @load_start\r\n");
    memdbg(&__data_load_start__, 16);
    printf(" @start\r\n");
    memdbg(&__data_start__, 16);
    printf(" @end-16\r\n");
    memdbg((char*)&__data_end__ - 16, 16);
    printf("\r\n");

    printf(".tdata  : %p - %p, load %p\r\n", &__tdata_start__, &__tdata_end__, &__tdata_load_start__);
    printf(".bss    : %p - %p, load %p\r\n", &__bss_start__, &__bss_end__, &__bss_load_start__);
    printf(".sbss   : %p - %p, load %p\r\n", &__sbss_start__, &__sbss_end__, &__sbss_load_start__);
    printf("\r\n");
}

void check_mcycle(void)
{
    uint64_t cycle1;
    uint64_t cycle2;
    uint64_t cycles_per_sec;

    cycle1 = __get_rv_cycle();
    system_delay_ms(1000);

    cycle2 = __get_rv_cycle();

    cycles_per_sec = (cycle2 - cycle1) / 1000 / 1000;
    printf("Info: %d Mcycles/s\r\n", (int)cycles_per_sec);
}

void puthex(uint8_t v)
{
    uint8_t ch;

    ch = (v >> 4) & 0xF;
    if (ch < 10)
    {
        putchar('0' + ch);
    }
    else
    {
        putchar('A' + ch - 10);
    }

    ch = v & 0xF;
    if (ch < 10)
    {
        putchar('0' + ch);
    }
    else
    {
        putchar('A' + ch - 10);
    }
}

void memdbg(const void* buf, int nr_bytes)
{
    const uint8_t* p = (const uint8_t*)buf;
    int i;

    for (i = 0; i < nr_bytes; i++)
    {
        printf(" ");
        puthex(p[i] & 0xFF);
        if ((i % 8) == 7)
        {
            printf("\r\n");
        }
    }

    if ((i % 8) != 0)
    {
        printf("\r\n");
    }
}

void memdbg16(const void* buf, int nr_bytes)
{
    const uint16_t* p = (const uint16_t*)buf;
    int i;

    for (i = 0; i < nr_bytes/2; i++)
    {
        printf(" ");
        puthex((p[i] >> 8) & 0xFF);
        puthex(p[i] & 0xFF);

        if ((i % 4) == 3)
        {
            printf("\r\n");
        }
    }

    if ((i % 4) != 0)
    {
        printf("\r\n");
    }
}

void system_clock_init(void)
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

static void uart0_config()
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