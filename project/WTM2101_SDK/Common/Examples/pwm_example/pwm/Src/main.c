/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to generate pwm wave, set capture mode, 
             encounter break event pwm stop output.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"

static void system_clock_init(void);
static void key_action(void);
static void key_config(void);
static void gpio_config(void);
static void pwm_config(void);
static void pwm_cap_config(void);
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
    gpio_config();
    pwm_config();
    pwm_cap_config();
    key_config();
   
    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    while(1)
    {
        key_action();
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
 
static void key_action(void)
{  
    static Bool pwm_status = FALSE;
    system_delay_ms(80);
    if (GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_2) == GPIO_PIN_RESET)
    {
        system_delay_ms(80);
        if (GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_2) == GPIO_PIN_RESET)
        {
            if (pwm_status == FALSE)
            {
                GPIO_OutputHi(GPIOA, GPIO_PIN_4);
                printf("break\n");
                system_delay_ms(100);
                GPIO_OutputLo(GPIOA, GPIO_PIN_4);
                pwm_status = TRUE;
            }
            else
            {
                PWM_BK_Rel(PWM0, PWM_CH1);
                printf("bk_rel\n");
                pwm_status = FALSE;
            }
        }
    }
    if (GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_3) == GPIO_PIN_RESET)
    {
        system_delay_ms(80);
        if (GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_3) == GPIO_PIN_RESET)
        {
            system_delay_ms(100);
            /* PWM Channel Init Structure */
            PWM_CH_CapParamTypeDef PWM_CH_CapParamStructure;
            PWM_CH_CapParamStructure.Cycle_Num = 0;
            PWM_CH_CapParamStructure.HL_Cycle_Num = 0;
            /* run PWM1_CH0_CAPTURE */
            PWM_CH_GetCapParam(PWM1, PWM_CH0, &PWM_CH_CapParamStructure);
            printf("Cycle_Num:    %d;\nHL_Cycle_Num: %d;\n\n", 
                    PWM_CH_CapParamStructure.Cycle_Num, PWM_CH_CapParamStructure.HL_Cycle_Num);
        }
    }
}

static void key_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_IT_InitTypeDef GPIO_IT_InitStructure;

    /* enable debounce */
    RCC_CLK_EN_Ctl(RCC_DB_CLKEN,ENABLE);

    /* init the PA2 PA3 pin with input_pull mode */
    GPIO_InitStructure.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStructure.Alternate = GPIO_AF2_GPIO | GPIO_AF3_GPIO;
    GPIO_InitStructure.Mode = GPIO_MODE_INPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* init the PA4 pin with output mode */
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    GPIO_InitStructure.Alternate = GPIO_AF4_GPIO;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_OutputLo(GPIOA, GPIO_PIN_4);
}

static void pwm_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    PWM_InitTypeDef PWM_InitStructure;
    PWM_CH_ParamTypeDef PWM_CHParaInitStructure;
    PWM_CH_InitTypeDef PWM_CHInitStructure;

    /* enable PWM0 clock */
    RCC_CLK_EN_Ctl(RCC_PWM0_CLKEN,ENABLE);

    /* init the PA1 pin with pwm */
    GPIO_InitStructure.Pin = GPIO_PIN_1;
    GPIO_InitStructure.Alternate = GPIO_AF1_PWM0;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* initial pwm */
    PWM_InitStructure.Period = 9999 ;
    PWM_InitStructure.CountMode = PWM_COUNT_UP;
    PWM_InitStructure.Mode = PWM_MODE_PWM;
    PWM_Init(PWM0, &PWM_InitStructure);

    /* initial period */
    PWM_CHParaInitStructure.Dead_Zone = 10;
    PWM_CHParaInitStructure.Cmp_Val = 1989; 
    PWM_CH_SetParam(PWM0, PWM_CH1, &PWM_CHParaInitStructure);
    
    /* initial parameter and start the pwm */
    PWM_CHInitStructure.CH_Mode = PWM_CH_MODE_CONT;
    PWM_CHInitStructure.IN_SIG = PWM_IN_SIG_FWD;
    PWM_CHInitStructure.OUT_SIG = PWM_OUT_SIG_FWD;
    PWM_CHInitStructure.Init_Out_Val = PWM_INIT_OUT_LO;
    PWM_CHInitStructure.CH_En = ENABLE;
    PWM_CH_Init(PWM0, PWM_CH1, &PWM_CHInitStructure);

    /* init the PA11 pin with pwm_break */
    GPIO_InitStructure.Pin = GPIO_PIN_11;
    GPIO_InitStructure.Alternate = GPIO_AF11_PWM0_BK1;
    GPIO_InitStructure.Mode = GPIO_MODE_IN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void pwm_cap_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    PWM_InitTypeDef PWM_InitStructure;
    PWM_CH_InitTypeDef PWM_CHInitStructure;

    /* enable PWM1 and GPIOA clock */
    RCC_CLK_EN_Ctl(RCC_PWM1_CLKEN | RCC_DB_CLKEN,ENABLE);

    /* init the PA10 pin with pwm_cap */
    GPIO_InitStructure.Pin = GPIO_PIN_10;
    GPIO_InitStructure.Alternate = GPIO_AF10_PWM1;
    GPIO_InitStructure.Mode = GPIO_MODE_IN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    PWM_InitStructure.Mode = PWM_MODE_CAP;
    PWM_Init(PWM1, &PWM_InitStructure);

    PWM_CHInitStructure.CH_Mode = PWM_CH_MODE_CONT;
    PWM_CHInitStructure.IN_SIG = PWM_IN_SIG_FWD;
    PWM_CHInitStructure.OUT_SIG = PWM_OUT_SIG_FWD;
    PWM_CHInitStructure.Init_Out_Val = PWM_INIT_OUT_LO;
    PWM_CHInitStructure.CH_En = ENABLE;
    PWM_CH_Init(PWM1, PWM_CH0, &PWM_CHInitStructure);
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
