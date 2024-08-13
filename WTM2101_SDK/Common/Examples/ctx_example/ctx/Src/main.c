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

static ucontext_t ctx_example1;
static ucontext_t ctx_example2;

#define  CTX_EXAMPLE1_SIZE_BYTES 1024
#define  CTX_EXAMPLE2_SIZE_BYTES 1024
uint32_t ctx_example1_stack[CTX_EXAMPLE1_SIZE_BYTES];
uint32_t ctx_example2_stack[CTX_EXAMPLE2_SIZE_BYTES];

static void uart_init(void);
static void clock_init(void);

void ctx_example1_function(void)
{
    printf("ctx_example1_function is running\r\n");
    system_delay_s(1);
    swapcontext(&ctx_example1,&ctx_example2);
}

void ctx_example2_function(void)
{
    printf("ctx_example2_function is running\r\n");
    system_delay_s(1);
    swapcontext(&ctx_example2,&ctx_example1);
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
    clock_init();

    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* constrcut the context1 */
    getcontext(&ctx_example1);
    ctx_example1.uc_stack.ss_sp    = (void*)(ctx_example1_stack);
    ctx_example1.uc_stack.ss_size  = CTX_EXAMPLE1_SIZE_BYTES;
    makecontext(&ctx_example1, ctx_example1_function, 0);

    /* constrcut the context2 */
    getcontext(&ctx_example2);
    ctx_example2.uc_stack.ss_sp    = (void*)(ctx_example2_stack);
    ctx_example2.uc_stack.ss_size  = CTX_EXAMPLE2_SIZE_BYTES;
    makecontext(&ctx_example2, ctx_example2_function, 0);

    /* start the context1 */
    setcontext(&ctx_example1);

    while(1)
    {
        /* The program will not run here */
        system_delay_s(1);
        printf("hello world witmem\r\n");
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

static void clock_init(void)
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

    /* Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc is calibrated by the xtal 32k */
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
