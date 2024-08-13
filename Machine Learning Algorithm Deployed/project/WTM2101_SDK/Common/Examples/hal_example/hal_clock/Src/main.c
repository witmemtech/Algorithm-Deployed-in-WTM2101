/**
* @file    main.c
* @brief   The Source Codes for the main Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

#include "main.h"

#define CLOCK_EXAMPLE 5

static void clock_init(void);
static void uart_init(void);
static void i2S_mclk_out(void);

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
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);
    i2S_mclk_out();
  
    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    while(1){
        printf("imok\r\n");
        system_delay_s(2);
    };
}

static void system_clock_init_example1(void)
{
    int ret = 0; 
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_INTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = ENABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /*Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc is calibrated by the xtal 32k*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void system_clock_init_example2(void)
{
    int ret = 0;
    /*The clock instance*/   
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_INTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = ENABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_NPU_CALIBRATION_PARAMETER;

    /*Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc uses calibration parameters that are saved in the NPU */
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void system_clock_init_example3(void)
{
    int ret = 0;
    /*The clock instance*/ 
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_INTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = ENABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /*Initialize the clock instance.the system clock is from PLL.the 24mosc is calibrated by the xtal 32k*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_PLL,HAL_CLOCK_PLL,&hal_clock_24mosc_Configuration,6,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void system_clock_init_example4(void)
{
    int ret = 0;
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_INTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = ENABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_NPU_CALIBRATION_PARAMETER;

    /*Initialize the clock instance.the system clock is from PLL.the 24mosc uses calibration parameters that are saved in the NPU */
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_PLL,HAL_CLOCK_PLL,&hal_clock_24mosc_Configuration,6,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void system_clock_init_example5(void)
{
    int ret = 0;
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_EXTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = DISABLE;
    hal_clock_24mosc_Configuration.calibration_way = 0;

    /*Initialize the clock instance.the system clock is from external 24576000 crystal oscillator.*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void system_clock_init_example6(void)
{
    int ret = 0;
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_EXTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 12288000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = DISABLE;
    hal_clock_24mosc_Configuration.calibration_way = 0;

    /*Initialize the clock instance.the system clock is from external 12288000 crystal oscillator.*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void system_clock_init_example7(void)
{
    int ret = 0;
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_EXTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = DISABLE;
    hal_clock_24mosc_Configuration.calibration_way = 0;

    /*Initialize the clock instance.the system clock uses the external 24576000 crystal oscillator.the system clock is from PLL.*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_PLL,HAL_CLOCK_PLL,&hal_clock_24mosc_Configuration,6,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void system_clock_init_example8(void)
{
    int ret = 0;

    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_EXTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 12288000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = DISABLE;
    hal_clock_24mosc_Configuration.calibration_way = 0;

    /*Initialize the clock instance.the system clock uses the external 12288000 crystal oscillator.the system clock is from PLL.*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_PLL,HAL_CLOCK_PLL,&hal_clock_24mosc_Configuration,6,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    } 
}

static void clock_init(void)
{
#if CLOCK_EXAMPLE == 1
    system_clock_init_example1();
#elif CLOCK_EXAMPLE == 2
    system_clock_init_example2();
#elif CLOCK_EXAMPLE == 3
    system_clock_init_example3();
#elif CLOCK_EXAMPLE == 4
    system_clock_init_example4();
#elif CLOCK_EXAMPLE == 5
    system_clock_init_example5();
#elif CLOCK_EXAMPLE == 6
   system_clock_init_example6();
#elif CLOCK_EXAMPLE == 7
    system_clock_init_example7();
#elif CLOCK_EXAMPLE == 8
   system_clock_init_example8();
#endif
}

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);
   
    /*the gpio4,gpio5*/
    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.Alternate = GPIO_AF4_UART0 | GPIO_AF5_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);
}

static void i2S_mclk_out(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  
    RCC_CLK_EN_Ctl(RCC_CLK_EN_GPIO_HCLKEN_Msk, ENABLE);
    /*the gpio9*/
    GPIO_InitStructure.Pin = GPIO_PIN_9;
    GPIO_InitStructure.Alternate = GPIO_AF9_I2S;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_CLK_EN_Ctl(RCC_I2S_MCLKEN, ENABLE);
    /*the ouput clock is half of system clock*/
#if (CLOCK_EXAMPLE == 3) || (CLOCK_EXAMPLE == 4) || (CLOCK_EXAMPLE == 7)
    RCC_I2S_M_Set_ClkDiv(13); 
#elif (CLOCK_EXAMPLE == 8)
    RCC_I2S_M_Set_ClkDiv(7); 
#else
    RCC_I2S_M_Set_ClkDiv(1); 
#endif
}

