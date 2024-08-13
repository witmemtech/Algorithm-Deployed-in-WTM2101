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

static void led_on(void);
static void led_off(void);

static void system_clock_init(void);
static void gpio_config(void);
static void sbm_config(void);
static void sbm_mode(void);
static void gpio_config(void);
static void uart_init(void);

void GPIO_WAKEUP_IRQHandler(void)
{
    GPIO_IT_ClrWakeUpPending(GPIOA, GPIO_IT_GetWakeupStat(GPIOA));
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

    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();
    
    /* GPIO sbm config */
    gpio_config();
    sbm_config();
    /* led will flash fast if reset */
    for(int i = 0;i < 5;i++)
    {
        led_on();
        system_delay_ms(200);
        led_off();
        system_delay_ms(200);
    }
    /* enter sbm mode*/ 
    sbm_mode();

    while(1) 
    {
        led_on();
        system_delay_ms(1000);
        led_off();
        system_delay_ms(1000);
    }
   
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
    /* GPIO WAKEUP init */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_PIN_10;
    GPIO_InitStructure.Mode = GPIO_MODE_INPU;
    GPIO_InitStructure.Alternate = GPIO_AF10_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* GPIO watch init */
    GPIO_InitStructure.Pin = GPIO_PIN_0 ;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate = GPIO_AF0_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_IT_InitTypeDef IT_InitTypeDef;
    IT_InitTypeDef.Pin = GPIO_PIN_10;
    IT_InitTypeDef.Trig = GPIO_IT_TRIG_RISING;
    IT_InitTypeDef.State = ENABLE;
    GPIO_IT_Cfg(GPIOA, &IT_InitTypeDef);
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

static void sbm_config(void)
{

    PMU_Set_Ldo_Voltage_Value(PMU, PMU_LDO_VOLTAGE_1_1V);
    PMU_Set_Ldo_Voltage_Cmd(PMU);

    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    
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

static void sbm_mode(void)
{
    /* fall asleep */
    PMU_Standby_Mode_Cmd(PMU);
    __WFI();
}

