/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the uart to transfer 
  *          continuously converted data.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"

static void system_clock_init(void);
static void UART0_Config(void);
static void UART1_Config(void);

#define TEST_BUF_SIZE (8)
uint8_t uart0_send[TEST_BUF_SIZE] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
uint8_t uart0_recv[TEST_BUF_SIZE] = {0};
uint8_t uart1_recv[TEST_BUF_SIZE] = {0};
volatile uint8_t uart0_send_index = 0;
volatile uint8_t uart0_recv_index = 0;

void main(void)
{
    uart0_send_index = 0;
    uart0_recv_index = 0;

    /* retarget printf to segger rtt */
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();

    /* config system clock */
    system_clock_init();

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);

    /* Disable N307 Interrupt */
    __disable_irq();

    /* uart0 send data and receive data use int */
    UART0_Config();
    UART1_Config();

    /* Enable N307 Interrupt */
    __enable_irq();

    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* Application entry */
    for (int i = 0;i < sizeof(uart1_recv);i++) 
    {
        while(UART_Flag_GetStatBit(UART1,UART_FLAG_DR) == RESET);
        uart1_recv[i] =  UART_ReceiveData(UART1);
    }

    for (int i = 0;i < sizeof(uart1_recv);i++) 
    {
        while(UART_Flag_GetStatBit(UART1,UART_FLAG_TEMT) == RESET);
        UART_SendData(UART1, uart1_recv[i]);
    }

    while (uart0_recv_index < sizeof(uart0_recv));

    if (memcmp(uart0_send, uart0_recv, sizeof(uart0_recv)) == 0) 
    {
        printf("pass\r\n");
    }
    else 
    {
        printf("failed\r\n");
    }

    while(1){};
}


void UART0_IRQHandler(void)
{
    uint32_t status = 0;

    status = UART_Flag_GetStat(UART0);
    if(status & UART_LSR_THRE_Msk) 
    {
        if(uart0_send_index < sizeof(uart0_send)) 
        {
            UART_SendData(UART0, uart0_send[uart0_send_index]);
            uart0_send_index++;

            if(uart0_send_index == sizeof(uart0_send)) 
            {
                UART_IT_Cfg(UART0, UART_IT_ETBEI, DISABLE);
            }
       }
    }

    if((status & UART_LSR_DR_Msk)) 
    {
        uart0_recv[uart0_recv_index] =  UART_ReceiveData(UART0);
        uart0_recv_index++;

        if(uart0_recv_index == sizeof(uart0_recv)) 
        {
            UART_IT_Cfg(UART0, UART_IT_ERBFI, DISABLE);
        }
    }
}

static void UART0_Config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;    /* uart0 pin config */
    GPIO_InitStructure.Alternate = GPIO_AF4_UART0 | GPIO_AF5_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 115200;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;    /* enable fifo */
    UART_Init(UART0, &USART_InitStructure);

    UART_IT_Cfg(UART0, UART_IT_ERBFI | UART_IT_ETBEI, DISABLE);
    ECLIC_ClearPendingIRQ(UART0_IRQn);
    ECLIC_SetPriorityIRQ(UART0_IRQn, 1);
    ECLIC_SetTrigIRQ(UART0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(UART0_IRQn);
    UART_IT_Cfg(UART0, UART_IT_ERBFI | UART_IT_ETBEI, ENABLE);  /* enable uart receive interrupt and send interrupt*/
}

static void UART1_Config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART1_CLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15;    /* uart1 pin config */
    GPIO_InitStructure.Alternate = GPIO_AF14_UART1 | GPIO_AF15_UART1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 115200;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;    /* enable fifo */
    UART_Init(UART1, &USART_InitStructure);

    UART_IT_Cfg(UART1, UART_IT_ERBFI | UART_IT_ETBEI, DISABLE);
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
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /* According to the clock instance, initialize the hardware */
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

