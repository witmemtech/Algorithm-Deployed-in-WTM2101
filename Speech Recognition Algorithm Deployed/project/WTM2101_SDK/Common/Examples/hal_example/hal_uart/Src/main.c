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

#define UART_EXAMPLE 1

#define  BUFFER_SIZE 100
uint8_t receive_buffer[BUFFER_SIZE] = {0};
uint8_t send_buffer[BUFFER_SIZE] ={0};
volatile int receive_count = 0;
volatile Bool async_receive_flag = FALSE;

static void clock_init(void);
static void uart_init(void);
static void uart_data_handler(void);
static int application_uart_async_callbac(struct Hal_Uart_InitTypeDef *i2s_instance);

void DMA_IRQHandler(void)
{
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
    if(DMA_Get_Transfer_Interrupt_Status(DMA) & hal_uart_instance->send_dma.dma_channel)
    {
        DMA_Clear_Transfer_Interrupt_Cmd(DMA,hal_uart_instance->send_dma.dma_channel);
        /* data handle */
        hal_uart_instance->data_handle_info.send_dma_finish_handler(hal_uart_instance);
    }
}
     
void UART0_IRQHandler(void)
{
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
    /* uart interrput handle */
    hal_uart_instance->data_handle_info.async_receive_handler(hal_uart_instance);
}

void TIMER0_IRQHandler(void)
{
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
        
    TIMER_Clear_Interrupt_Cmd(hal_uart_instance->timer_instance);
    TIMER_Set_Enable_Cmd(hal_uart_instance->timer_instance,DISABLE);
    /* receive timeout handle */
    hal_uart_instance->data_handle_info.uart_timeout_handler(hal_uart_instance);
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
    
    while(1)
    {
       uart_data_handler();
    }
}

static void uart_init_example1(void)
{
    int ret = 0;
    UART_InitTypeDef USART_InitStructure;
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
        
    /* Construct uart related configuration parameters */
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;

    /* Initialize the uart instance.sync receive mode */
    ret = hal_uart_init(hal_uart_instance,UART0,&USART_InitStructure,HAL_UART_RECEIVE_SYNC,NULL,DISABLE);
    if(ret <= 0)
    {
        printf("hal_uart_init error:%d\r\n", ret);
    }

    /* According to the uart instance, initialize the hardware */
    ret = hal_uart_open(hal_uart_instance);
    if(ret <= 0)
    {
        printf("hal_uart_init error:%d\r\n", ret);
    }
}

static void uart_init_example3(void)
{
    int ret = 0;
    UART_InitTypeDef USART_InitStructure;
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
       
    /* Construct uart related configuration parameters */
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;

    /* Initialize the uart instance.async receive mode */
    ret = hal_uart_init(hal_uart_instance,UART0,&USART_InitStructure,HAL_UART_RECEIVE_ASYNC,application_uart_async_callbac,DISABLE);
    if(ret <= 0)
    {
        printf("hal_uart_init error:%d\r\n", ret);
    }

    /* According to the uart instance, initialize the hardware */
    ret = hal_uart_open(hal_uart_instance);
    if(ret <= 0)
    {
        printf("hal_uart_init error:%d\r\n", ret);
    }
}

static void uart_init_example4(void)
{
    int ret = 0;
    UART_InitTypeDef USART_InitStructure;
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
        
    /* Construct uart related configuration parameters */
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;

    /* Initialize the uart instance.async receive mode,enable send dma */
    ret = hal_uart_init(hal_uart_instance,UART0,&USART_InitStructure,HAL_UART_RECEIVE_ASYNC,application_uart_async_callbac,ENABLE);
    if(ret <= 0)
    {
        printf("hal_uart_init error:%d\r\n", ret);
    }

    /* According to the uart instance, initialize the hardware */
    ret = hal_uart_open(hal_uart_instance);
    if(ret <= 0)
    {
        printf("hal_uart_init error:%d\r\n", ret);
    }
}

static void uart_init(void)
{
#if UART_EXAMPLE == 1 || UART_EXAMPLE == 2
    uart_init_example1();
#elif UART_EXAMPLE == 3
    uart_init_example3();
#elif UART_EXAMPLE == 4
    uart_init_example4();
#endif
}


static void uart_data_handler_example1(void)
{
    int ret = 0;
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);

    /* write data */
    ret = hal_uart_write(hal_uart_instance,"hello word witmem\r\n",strlen("hello word witmem\r\n"));
    if(ret <= 0)
    {
        printf("hal_uart_write error:%d\r\n", ret);
    }
    
    /* Synchronous block reading data, until buffer data size is satisfied */
    receive_count = 0;
    ret = hal_uart_read(hal_uart_instance,receive_buffer,10,(uint32_t *)(&receive_count),0xffffffff);
    if(ret <= 0)
    {
        printf("hal_uart_read error:%d\r\n", ret);
    }

    /* output the buffer data */
    printf("receive length:%d\r\n", receive_count);
    printf("receive data\r\n");
    for(int i = 0 ;i < receive_count;i++)
        printf(" %c\r\n", receive_buffer[i]);
}

static void uart_data_handler_example2(void)
{
    int ret = 0;
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);

    /* write data */
    ret = hal_uart_write(hal_uart_instance,"hello word witmem\r\n",strlen("hello word witmem\r\n"));
    if(ret <= 0)
    {
        printf("hal_uart_write error:%d\r\n", ret);
    }
    
    /* Synchronous block reading data, timeout 1s */
    receive_count = 0;
    ret = hal_uart_read(hal_uart_instance,receive_buffer,10,(uint32_t *)(&receive_count),1000);
    if(ret <= 0)
    {
        printf("hal_uart_read error:%d\r\n", ret);
    }

    /* output the buffer data */
    printf("receive length:%d\r\n", receive_count);
    if(receive_count > 0)
    {
        printf("receive data\r\n");
        for(int i = 0 ;i < receive_count;i++)
            printf(" %c\r\n", receive_buffer[i]);
    }
}

static void uart_data_handler_example3(void)
{
    /* ASynchronous get data */
    if(async_receive_flag == TRUE)
    {
        async_receive_flag = FALSE;
        printf("receive length:%d\r\n", receive_count);
        printf("receive data\r\n");
        for(int i = 0 ;i < receive_count;i++)
            printf(" %c\r\n", receive_buffer[i]);
    }
}

static void uart_data_handler_example4(void)
{
    int ret = 0;
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);

    /* write data by dma*/
    memcpy(send_buffer,"hello world witmem\r\n",strlen("hello world witmem\r\n"));
    ret = hal_uart_write(hal_uart_instance,send_buffer,strlen("hello world witmem\r\n"));
    if(ret <= 0)
    {
        printf("hal_uart_write error:%d\r\n", ret);
    }

    /* ASynchronous get data */
    if(async_receive_flag == TRUE)
    {
        async_receive_flag = FALSE;
        printf("receive length:%d\r\n", receive_count);
        printf("receive data\r\n");
        for(int i = 0 ;i < receive_count;i++)
            printf(" %c\r\n", receive_buffer[i]);
    }
    system_delay_ms(100);
}

static void uart_data_handler(void)
{
#if UART_EXAMPLE == 1
    uart_data_handler_example1();
#elif UART_EXAMPLE == 2
    uart_data_handler_example2();
#elif UART_EXAMPLE == 3
    uart_data_handler_example3();
#elif UART_EXAMPLE == 4
    uart_data_handler_example4();
#endif    
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

static int application_uart_async_callbac(struct Hal_Uart_InitTypeDef *i2s_instance)
{
    /* get data from ring buffer */
    receive_count = 0;
    receive_count = Ring_Cache_Pop(&(i2s_instance->cache.ring_buffer),receive_buffer,sizeof(receive_buffer));
    async_receive_flag = TRUE;
}
