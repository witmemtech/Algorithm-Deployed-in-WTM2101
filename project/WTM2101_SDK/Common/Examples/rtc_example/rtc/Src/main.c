/**
* @file    main.c
* @brief    This example describes how to use the RTC to count and wakeup from RSM mode.
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

#include "main.h"

static void system_clock_init(void);
static void led_config(void);
static void led_on(void);
static void led_off(void);
static void rtc_config(uint8_t pmu_clk);

void RTC_IRQHandler(void)
{
    static int led_status = 0;
	
    RTC_Clear_Int_Cmd(RTC);
	
    if(led_status) 
    {
        led_on();
    } 
    else 
    {
        led_off();
    }

    led_status = !led_status;	
}

void main(void)
{
    /* retarget printf to segger rtt */      
    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);
 
    /* Reset all peripherals except PMU */
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();

    /* Initial clock */
    system_clock_init();
 
    /* Config led and rtc */
    led_config();
    rtc_config(PMU_CLK_RTC_SWITCH_160KHZ);

    while(1) {};
}

static void led_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Enable GPIOA clock */
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN,ENABLE);

    /* Init the GPIO0 pin with output mode */
    GPIO_InitStructure.Pin = GPIO_PIN_0;
    GPIO_InitStructure.Alternate = GPIO_AF0_GPIO;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
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

static int rtc_get_tick_count_s(uint8_t pmu_clk)
{
    int count = 0;
    switch (pmu_clk)
    {
        case PMU_CLK_RTC_SWITCH_SYSCLK_DIV_32:
              count = 750000;
              break;
        case PMU_CLK_RTC_SWITCH_10KHZ:
              count = 10000;
              break;
        case PMU_CLK_RTC_SWITCH_32KHZ:
              count = 32000;
              break;
        case PMU_CLK_RTC_SWITCH_160KHZ:
              count = 160000;
              break;
        default:
              break;
    }
    return count;
}

static void rtc_config(uint8_t pmu_clk)
{
    RCC_CLK_EN_Ctl(RCC_RTC_PCLKEN,ENABLE);

    /* Initial interrupt */
    ECLIC_ClearPendingIRQ(RTC_IRQn);
    ECLIC_SetPriorityIRQ(RTC_IRQn, 1);
    ECLIC_SetTrigIRQ(RTC_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(RTC_IRQn);

    PMU_Set_Ie_Msk(PMU, PMU_RTC_IMSK, ENABLE);
    PMU_Set_Ie_Msk(PMU, PMU_RTC_EMSK, ENABLE);

    RTC_Set_Interrupt_Unmask_Cmd(RTC, ENABLE);
    RTC_Set_Interrupt_Cmd(RTC,ENABLE);

    /* Initial loop-back mode */
    RTC_Set_Wrap_Cmd(RTC, ENABLE);

    /* Initial the rtc time */
    PMU_Set_Rtc_Clock_Source(PMU, pmu_clk);
    RTC_Set_Initial_Time_Value(RTC,0);
    RTC_Set_Compare_Time_Value(RTC,rtc_get_tick_count_s(pmu_clk));
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

    /* Initialize the clock instance.the system clock is from external 24576000 crystal oscillator */
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_10KOSC | HAL_CLOCK_320KOSC | HAL_CLOCK_XTL32K,  HAL_CLOCK_24MOSC, &hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /* According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}