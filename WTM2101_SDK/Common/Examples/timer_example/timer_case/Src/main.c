/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the Timer.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "main.h"

void led_config(void);
void timer_config(void);
void system_clock_init(void);

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

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    led_config();
    
    timer_config();

    while(1) 
    {
        printf("run\r\n");
    }
}

static void led_on(void)
{
    /* set the PA4 bit 0 to turn on the led */
    GPIO_OutputLo(GPIOA, GPIO_PIN_0);
}

static void led_off(void)
{
    /* set the PA4 bit 1 to turn on the led */
    GPIO_OutputHi(GPIOA, GPIO_PIN_0);
}

void led_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* enable GPIOA clock */
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN,ENABLE);

    /* init the PA4 pin with output mode */
    GPIO_InitStructure.Pin = GPIO_PIN_0;
    GPIO_InitStructure.Alternate = GPIO_AF0_GPIO;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
    led_off();
}

void timer_config(void)
{
    uint32_t tick = 0;
    TIMER_InitTypeDef timer_inittypedef = { 0, 0, 0 };

    RCC_CLK_EN_Ctl(RCC_TIME_CLKEN, ENABLE);

    ECLIC_ClearPendingIRQ(TIMER0_IRQn);
    ECLIC_SetPriorityIRQ(TIMER0_IRQn, 1);
    ECLIC_SetTrigIRQ(TIMER0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(TIMER0_IRQn);

    RCC_TIM0_Set_ClkDiv(0x0f);
    tick = TIMER_Transfer_second_to_tick(TIMER0,1);
    timer_inittypedef.period = tick;
    timer_inittypedef.mode = TIMER_USER_DEFINED_MODE;
    timer_inittypedef.pwm_period = 0;
    TIMER_Init(TIMER0, &timer_inittypedef);

    TIMER_Set_Enable_Cmd(TIMER0, ENABLE);
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

void TIMER0_IRQHandler(void)
{
    static int led_status = 0;
    TIMER_Clear_Interrupt_Cmd(TIMER0);

    if(led_status) {
        led_on();
    } else {
        led_off();
    }

    led_status = !led_status;
}
