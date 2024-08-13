/**
  ******************************************************************************
  * @file    main.c
  * @brief   This example describes how to use the afc calibration
  *          by external oscillator.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "main.h"

/* wdt rsm mode */
typedef enum
{
    WDT_RSM0 = 0,
    WDT_RSM2 = 1
} RSM_MODE_SEL;

static void led_on(void);
static void led_off(void);
static void gpio_config(void);
static void wdt_config(void);
static void uart_init(void);
static void rsm_mode_sel(uint8_t mode);
static void system_clock_init(void);

void WDG_IRQHandler(void)
{
    WDT_Clear_Int_Cmd(WDT);
}

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
    system_clock_init();

    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);
    gpio_config();
    wdt_config();

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* led will flash fast if reset */
    for(int i = 0;i < 5;i++)
    {
        led_on();
        system_delay_ms(200);
        led_off();
        system_delay_ms(200);
    }

    /* enter rsm mode*/
    rsm_mode_sel(WDT_RSM0);

    while(1)
    {
        led_on();
        system_delay_ms(1000);
        led_off();
        system_delay_ms(1000);
    }

}

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    /*the gpio4,gpio5*/
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
    ret = hal_clock_init(hal_clock_instance, HAL_CLOCK_24MOSC | HAL_CLOCK_320KOSC, HAL_CLOCK_24MOSC, &hal_clock_24mosc_Configuration, 0, 1, 1);
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

static void led_on(void)
{
    /* Pull down GPIO0 to turn on the led  */
    GPIO_OutputLo(GPIOA, GPIO_PIN_0);
}

static void led_off(void)
{
    /* Pull up GPIO0 to turn off the led */
    GPIO_OutputHi(GPIOA, GPIO_PIN_0);
}

static void gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN | RCC_DB_CLKEN, ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_0;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate = GPIO_AF0_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void wdt_config(void)
{
    RCC_CLK_EN_Ctl(RCC_WDT_PCLKEN,ENABLE);

    /* interrupt init */
    ECLIC_ClearPendingIRQ(WDG_IRQn);
    ECLIC_SetPriorityIRQ(WDG_IRQn, 1);
    ECLIC_SetTrigIRQ(WDG_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(WDG_IRQn);

    PMU_Set_Wdt_Clock_Source(PMU, PMU_CLK_WDT_SWITCH_160KHZ);

    /* the mask bit is enabled */
    PMU_Set_Ie_Msk(PMU, PMU_WDT_IMSK, ENABLE);
    PMU_Set_Ie_Msk(PMU, PMU_WDT_EMSK, ENABLE);

    /* the max interval to feed dog*/
    WDT_Set_Timeout_Value(WDT, 1);

    /* wtd is enabled.firstly you must call WDT_Feed_Dog function before enable the wdt */
    WDT_Feed_Dog(WDT);
    WDT_Set_Enable_Cmd(WDT, ENABLE);
}

static void rsm_mode_sel(uint8_t mode)
{
    switch(mode)
    {
        case WDT_RSM0:
            /* Retain sram in rsm0 mode */
            PMU_Set_Sram_Retain_In_Rsm_Mode_Cmd(PMU,PMU_SRAM0,ENABLE);

            PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_ALL,DISABLE);
            PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_KEEP_WDT,ENABLE);
            PMU_Rsm_Mode_Cmd(PMU);
            __WFI();
            break;
        case WDT_RSM2:
            PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_ALL,DISABLE);
            PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_KEEP_VDD | PMU_RSM_MODE_KEEP_WDT,ENABLE);
            PMU_Rsm_Mode_Cmd(PMU);
            __WFI();
            break;
        default:
            break;
    }
}
