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

#define RSM_MODE_NUM     (0)

static void gpio_config(void);
static void system_clock_init(void);
static void rsm_mode_sel(uint8_t mode);
static void rsm_config(void);
static void led_switch(uint32_t led_num, Bool state);

void GPIO_WAKEUP_IRQHandler(void)
{
    GPIO_IT_ClrWakeUpPending(GPIOA, GPIO_PIN_10);
    GPIO_IT_ClrPending(GPIOA, GPIO_PIN_10);
}

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Reset all peripherals except PMU and GPIO*/
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();

    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);

    /* Initial basic system:osc calibration by external oscillator */
    system_clock_init();

    /* GPIO sbm config */
    gpio_config();
    rsm_config();

    /* led will flash fast if reset */
    for(int i = 0; i < 3; i++)
    {
        led_switch(LED_PIN_0, ENABLE);
        system_delay_ms(100);
        led_switch(LED_PIN_0, DISABLE);
        system_delay_ms(100);
    }

    rsm_mode_sel(RSM_MODE_NUM);

    while(1) {
        led_switch(LED_PIN_1, ENABLE);
        system_delay_ms(100);
        led_switch(LED_PIN_1, DISABLE);
        system_delay_ms(100);
    }
}

void system_clock_init(void)
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

void gpio_config(void)
{
    /* The GPIO init */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_PIN_10;
    GPIO_InitStructure.Mode = GPIO_MODE_INPU;
    GPIO_InitStructure.Alternate = GPIO_AF10_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate = GPIO_AF0_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_IT_InitTypeDef IT_InitTypeDef;

    IT_InitTypeDef.Pin = GPIO_PIN_10;
    IT_InitTypeDef.Trig = GPIO_IT_TRIG_RISING;
    IT_InitTypeDef.State = ENABLE;
    GPIO_IT_Cfg(GPIOA, &IT_InitTypeDef);
    GPIO_OutputHi(GPIOA, GPIO_PIN_0);
    GPIO_OutputHi(GPIOA, GPIO_PIN_1);
}

static void rsm_config(void)
{
    /* interrupt init */
    ECLIC_ClearPendingIRQ(GPIO_WAKEUP_IRQn);
    ECLIC_SetPriorityIRQ(GPIO_WAKEUP_IRQn, 1);
    ECLIC_SetTrigIRQ(GPIO_WAKEUP_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(GPIO_WAKEUP_IRQn);

    /* the mask bit is ebabled */
    PMU_Set_Ie_Msk(PMU, PMU_GPIO_IMSK, ENABLE);
    PMU_Set_Ie_Msk(PMU, PMU_GPIO_EMSK, ENABLE);
    PMU_Set_Npu_Poweron_Cmd(PMU, DISABLE);
}

static void rsm_mode_sel(uint8_t mode)
{
    switch(mode)
    {
        case 0:
             /* Retain sram in rsm0 mode */
            PMU_Set_Sram_Retain_In_Rsm_Mode_Cmd(PMU,PMU_SRAM0,ENABLE);
            PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_ALL,DISABLE);
            PMU_Rsm_Mode_Cmd(PMU);
            __WFI();
            break;
        case 2:
            PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_ALL,DISABLE);
            PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_KEEP_VDD,ENABLE);
            PMU_Rsm_Mode_Cmd(PMU);
            __WFI();
            break;
        default:
            break;
    }
}

static void led_switch(uint32_t led_num, Bool state)
{
    if (led_num != LED_PIN_0 && led_num != LED_PIN_1)
    {
        return;
    }

    if (state)
    {
        GPIO_OutputLo(GPIOA, led_num);
    }
    else
    {
        GPIO_OutputHi(GPIOA, led_num);
    }
}