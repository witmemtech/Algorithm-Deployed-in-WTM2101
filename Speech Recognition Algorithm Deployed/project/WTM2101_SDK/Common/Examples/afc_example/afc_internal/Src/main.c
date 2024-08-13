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

static void system_clock_init(void);
static void afc_clk_watch_init(void);
static void uart_init(void);

#define CLOCK_EXAMPLE 6

#define OSC_CLK_WATCH  

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGET_NONE);
    /* Reset all peripherals except PMU and GPIO*/
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));  

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();

    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);
    
    /* Initial basic system:osc calibration by internal oscillator */
    system_clock_init();

    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);
        
    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Watch osc calibration by gpio4 */  
#ifdef  OSC_CLK_WATCH 
    afc_clk_watch_init();
#endif

    while(1){};   
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
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_NPU_CALIBRATION_PARAMETER;

    /* Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc uses calibration parameters that are saved in the NPU */
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

static void afc_clk_watch_init(void)
{    
    /* The clock enable */
    RCC_CLK_EN_Ctl(RCC_AUD_CLKEN, ENABLE);
    RCC_CLK_EN_Ctl(RCC_AUD_PCLKEN, ENABLE);
    PMU_Set_Audio_Clock_Cmd(PMU, ENABLE);
    
    /* The GPIO watch pad init */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_PIN_4;         
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate = GPIO_AF4_PDM0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* The osc divider is 10=(4+1)*(1+1) */
    PMU_Set_Audio_Clock_Div_Num(PMU, 4);         
    AUDIO_Set_Channel_Clock_Divider(AUD, 1);     
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, ENABLE);    
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
  
    /*configure different baud rates according to the main frequency of the example*/
  #if (CLOCK_EXAMPLE == 1) || (CLOCK_EXAMPLE == 2) || (CLOCK_EXAMPLE == 5) || (CLOCK_EXAMPLE == 8)
    USART_InitStructure.BaudRate = 115200;
  #elif  (CLOCK_EXAMPLE == 3) || (CLOCK_EXAMPLE == 4) || (CLOCK_EXAMPLE == 7) 
    USART_InitStructure.BaudRate = 921600;
  #elif  (CLOCK_EXAMPLE == 6)
    USART_InitStructure.BaudRate = 9600;
  #endif
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);
}