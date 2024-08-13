/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the key to change the LED status. 
  *          continuously converted data.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"

/* RISING EDGE and FALLING EDGE flag */
Bool falling_flag = FALSE;
Bool rising_flag = FALSE;

static void system_clock_init(void);
void GPIO_IRQHandler(void);
void TIMER0_IRQHandler(void);
static void timer_config(void);
static void led_config(void);
static void led_on(void);
static void led_off(void);
static void key_config(void);
static void uart_init(void);

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Reset all peripherals except PMU */
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();
  
    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);

    /* Initial Basic System: OSC and GPIO */
    system_clock_init();

    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);
    led_config();
    key_config();
    timer_config();
    led_on();

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    while(1);
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

    /*Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc is calibrated by the xtal 32k*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
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
 
void GPIO_IRQHandler(void)
{     
    
    GPIO_IT_ClrPending(GPIOA, GPIO_PIN_2);
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
    {
        rising_flag = FALSE;
        falling_flag = TRUE;
    }
    else
    {
        rising_flag = TRUE;
        falling_flag = FALSE;
    }
    ECLIC_EnableIRQ(TIMER0_IRQn);
}

void TIMER0_IRQHandler(void)
{
    /* led_status :FALSE led off,TRUE led on;  */
    static Bool led_status = FALSE;
    /* key_status :FALSE key raise,TRUE key press;  */
    static Bool key_status = FALSE;
    TIMER_Clear_Interrupt_Cmd(TIMER0);
    ECLIC_DisableIRQ(TIMER0_IRQn);
    if (falling_flag  == TRUE)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
        {
            key_status = TRUE;
        }
    }
    if (rising_flag == TRUE && key_status == TRUE)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET)
        {
            if (led_status == TRUE)
            {
                led_on();
                led_status = FALSE;
            }
            else
            {
                led_off();
                led_status = TRUE;
            }
            key_status = FALSE;
        } 
    }
}

static void timer_config(void)
{
    uint32_t tick = 0;
    TIMER_InitTypeDef timer_inittypedef = { 0,0,0 };

    RCC_CLK_EN_Ctl(RCC_TIME_CLKEN,ENABLE);

    ECLIC_ClearPendingIRQ(TIMER0_IRQn);
    ECLIC_SetPriorityIRQ(TIMER0_IRQn, 2);
    ECLIC_SetTrigIRQ(TIMER0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    TIMER_Set_Enable_Cmd(TIMER0, DISABLE);
    RCC_TIM0_Set_ClkDiv(0x0f);
    tick = TIMER_Transfer_millisecond_to_tick(TIMER0,10);
    timer_inittypedef.period = tick;
    timer_inittypedef.mode = TIMER_USER_DEFINED_MODE;
    timer_inittypedef.pwm_period = 0;
    TIMER_Init(TIMER0, &timer_inittypedef);
    TIMER_Set_Enable_Cmd(TIMER0, ENABLE);
}

static void led_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

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

static void key_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_IT_InitTypeDef GPIO_IT_InitStructure;

    /* enable debounce */
    RCC_CLK_EN_Ctl(RCC_DB_CLKEN,ENABLE);

    /* init the PA2 pin with input_pull mode */
    GPIO_InitStructure.Pin = GPIO_PIN_2;
    GPIO_InitStructure.Alternate = GPIO_AF2_GPIO;
    GPIO_InitStructure.Mode = GPIO_MODE_INPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* init the PA2 pin with level interrupt */
    ECLIC_ClearPendingIRQ(GPIO_IRQn);
    ECLIC_SetPriorityIRQ(GPIO_IRQn, 1);
    ECLIC_SetTrigIRQ(GPIO_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(GPIO_IRQn);
    
    GPIO_IT_MskCfg(DISABLE);
    GPIO_IT_PinMskCfg(GPIOA,GPIO_PIN_2, DISABLE);
    PMU_Set_Ie_Msk(PMU,PMU_GPIO_IMSK | PMU_GPIO_EMSK,ENABLE);

    GPIO_IT_InitStructure.Pin = GPIO_PIN_2;
    GPIO_IT_InitStructure.Trig = GPIO_IT_TRIG_RISING_FALLING;
    GPIO_IT_InitStructure.State = ENABLE;
    GPIO_IT_Cfg(GPIOA, &GPIO_IT_InitStructure);
}

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);
   
    /*the gpio16,gpio17*/
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