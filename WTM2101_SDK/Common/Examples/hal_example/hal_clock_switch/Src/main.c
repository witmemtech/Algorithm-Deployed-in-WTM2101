/**
* @file    main.c
* @brief   The Source Codes for the main Functions
* @date    2023-03-20
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

#include "main.h"

static void uart_init(void);
static void led_on(void);
static void led_off(void);
static void led_config(void);
static void led_flash(uint32_t count, uint32_t tick);
static void clock_init(void);
static void switch_system_clk_to_48M(void);
static void switch_system_clk_to_72M(void);
static void switch_system_clk_to_96M(void);
static void switch_system_clk_to_120M(void);
static void switch_system_clk_to_144M(void);

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
    led_config();
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);
    printf("/**** 24M clock ****/\n\r");
    system_config_dump();
    led_flash(10, 24000000);    /* AHB clock 24M, 24000000 tick / 24000000 clk = delay 1s */

    switch_system_clk_to_48M();
    /* AHB clock changed, initiate related peripheral again */
    uart_init();
    printf("/**** 48M clock ****/\n\r");
    system_config_dump();
    /* AHB clock 48M, 24000000 tick / 48000000 clk = delay 500ms */
    led_flash(10, 24000000);

    switch_system_clk_to_72M();
    /* AHB clock changed, initiate related peripheral again */
    uart_init();
    printf("/**** 72M clock ****/\n\r");
    system_config_dump();
    /* AHB clock 72M, 24000000 tick / 72000000 clk = delay 333ms */
    led_flash(10, 24000000);

    switch_system_clk_to_96M();
    /* AHB clock changed, initiate related peripheral again */
    uart_init();
    printf("/**** 96M clock ****/\n\r");
    system_config_dump();
    /* AHB clock 96M, 24000000 tick / 96000000 clk = delay 250ms */
    led_flash(10, 24000000);

    switch_system_clk_to_120M();
    /* AHB clock changed, initiate related peripheral again */
    uart_init();
    printf("/**** 120M clock ****/\n\r");
    system_config_dump();
    /* AHB clock 120M, 24000000 tick / 120000000 clk = delay 200ms */
    led_flash(10, 24000000);

    switch_system_clk_to_144M();
    /* AHB clock changed, initiate related peripheral again */
    uart_init();
    printf("/**** 144M clock ****/\n\r");
    system_config_dump();
    /* AHB clock 144M, 24000000 tick / 1440000000 clk = delay 166ms */
    led_flash(10, 24000000);

    while(1){};
}

static void uart_init(void)
{
    /* init uart */
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    /* the gpio16, gpio17 */
    GPIO_InitStructure.Pin = GPIO_PIN_16 | GPIO_PIN_17;
    GPIO_InitStructure.Alternate = GPIO_AF16_UART0 | GPIO_AF17_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);
}

static void led_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* enable GPIOA clock */
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN,ENABLE);

    /* init the PA0 pin with output mode */
    GPIO_InitStructure.Pin = GPIO_PIN_0;
    GPIO_InitStructure.Alternate = GPIO_AF0_GPIO;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void led_on(void)
{
    /* set the PA0 bit 0 to turn on the led */
    GPIO_OutputLo(GPIOA, GPIO_PIN_0);
}

static void led_off(void)
{
    /* set the PA0 bit 1 to turn off the led */
    GPIO_OutputHi(GPIOA, GPIO_PIN_0);
}

static void led_flash(uint32_t count, uint32_t tick) {
    for (int i = 0; i < count; i++)
    {
        led_on();
        system_delay_tick(tick);
        led_off();
        system_delay_tick(tick);
    }
}

static void clock_init(void)
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

static void switch_system_clk_to_48M(void)
{
    int ret = 0;
    /* The clock instance */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();

    /* modify the parameters of hal_clock_instance */
    hal_clock_instance->pllclock_upfrequency_coefficient = 2;

    /* switch system clock to new configuration */
    ret = hal_clock_ctl(hal_clock_instance, HAL_CLOCK_SWITCH_SYSTEM_CLOCK_COMMAND, HAL_CLOCK_PLL);
    if(ret <= 0)
    {
        printf("hal_clock_ctl error:%d\r\n", ret);
    }
}

static void switch_system_clk_to_72M(void)
{
    int ret = 0;
    /* The clock instance */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();

    /* modify the parameters of hal_clock_instance */
    hal_clock_instance->pllclock_upfrequency_coefficient = 3;

    /* switch system clock to new configuration */
    ret = hal_clock_ctl(hal_clock_instance, HAL_CLOCK_SWITCH_SYSTEM_CLOCK_COMMAND, HAL_CLOCK_PLL);
    if(ret <= 0)
    {
        printf("hal_clock_ctl error:%d\r\n", ret);
    }
}

static void switch_system_clk_to_96M(void)
{
    int ret = 0;
    /* The clock instance */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();

    /* modify the parameters of hal_clock_instance */
    hal_clock_instance->pllclock_upfrequency_coefficient = 4;

    /* switch system clock to new configuration */
    ret = hal_clock_ctl(hal_clock_instance, HAL_CLOCK_SWITCH_SYSTEM_CLOCK_COMMAND, HAL_CLOCK_PLL);
    if(ret <= 0)
    {
        printf("hal_clock_ctl error:%d\r\n", ret);
    }
}

static void switch_system_clk_to_120M(void)
{
    int ret = 0;
    /* The clock instance */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();

    /* modify the parameters of hal_clock_instance */
    hal_clock_instance->pllclock_upfrequency_coefficient = 5;

    /* switch system clock to new configuration */
    ret = hal_clock_ctl(hal_clock_instance, HAL_CLOCK_SWITCH_SYSTEM_CLOCK_COMMAND, HAL_CLOCK_PLL);
    if(ret <= 0)
    {
        printf("hal_clock_ctl error:%d\r\n", ret);
    }
}

static void switch_system_clk_to_144M(void)
{
    int ret = 0;
    /* The clock instance */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();

    /* modify the parameters of hal_clock_instance */
    hal_clock_instance->pllclock_upfrequency_coefficient = 6;

    /* switch system clock to new configuration */
    ret = hal_clock_ctl(hal_clock_instance, HAL_CLOCK_SWITCH_SYSTEM_CLOCK_COMMAND, HAL_CLOCK_PLL);
    if(ret <= 0)
    {
        printf("hal_clock_ctl error:%d\r\n", ret);
    }
}