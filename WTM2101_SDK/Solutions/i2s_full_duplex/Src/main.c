/**
* @file    main.c
* @brief   The Source Codes for the main Functions
* @date    2023-02-09
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

#include "main.h"

static void dma_interrupt_handle_example(void);

static void i2s_init(void);
static void i2s_start(void);
static void i2s_data_handle(void);

static void uart_init(void);
static void clock_init(void);

void DMA_IRQHandler(void)
{
    dma_interrupt_handle_example();
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
    i2s_init(); 

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry*/
    i2s_start();

    while(1)
    {
        i2s_data_handle();
    }
}

static void dma_interrupt_handle_example(void)
{
    uint16_t block_int_flag = 0;
    /*The hal i2s instance*/
    Hal_I2s_InitTypeDef* hal_i2s_instance= hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    Hal_I2s_InitTypeDef* hal_i2s_instance1= hal_i2s_instance_get(HAL_I2S_INSTANCE1);
    block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
  
    do
    {
        /*The hal i2s instance handle the data*/
        if(block_int_flag & hal_i2s_instance->dma.dma_channel)
        {
            DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance->dma.dma_channel);
            hal_i2s_instance->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance);
        }
        /*The hal i2s instance1 handle the data*/
        if(block_int_flag & hal_i2s_instance1->dma.dma_channel)
        {
            DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance1->dma.dma_channel);
            hal_i2s_instance->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance1);
        }
        /*Get the dma interrupt status*/
        block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
    }while(block_int_flag);
}

static int init_example(void)
{
    int ret = 0;

    /*The hal i2s instance*/
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    if(!hal_i2s_instance)
    {
        printf("hal_i2s_instance is null,this is a error\r\n");
        return -1;
    }

    /*Init hal i2s instance,using I2S1,send and receive,master,32bits width word,320 words data of left and right channel is handled application*/
    ret = hal_i2s_init(hal_i2s_instance,I2S1,HAL_I2S_RECEIVE_AND_SEND,HAL_I2S_MASTER,HAL_I2S_32BITS_WIDTH_WORD,320);
    if(ret <= 0)
    {
        printf("hal_i2s_init is error:%d\r\n",ret);
        return -2;
    }  

    /*Open the hal i2s hardware with the hal i2s instance*/  
    ret = hal_i2s_open(hal_i2s_instance);
    if(ret <= 0)
    {
        printf("hal_i2s_open is error:%d\r\n",ret);
        return -3;
    }  

    /*The hal i2s instance1*/
    Hal_I2s_InitTypeDef* hal_i2s_instance1 = hal_i2s_instance_get(HAL_I2S_INSTANCE1);
    if(!hal_i2s_instance1)
    {
        printf("hal_i2s_instance1 is null,this is a error\r\n");
        return -4;
    }

    /*Init hal i2s instance1,using I2S0,only receiving,master,32bits width word,320 words data of left and right channel is handled application*/
    ret = hal_i2s_init(hal_i2s_instance1,I2S0,HAL_I2S_ONLY_RECEIVE,HAL_I2S_MASTER,HAL_I2S_32BITS_WIDTH_WORD,320);
    if(ret <= 0)
    {
        printf("hal_i2s_init is error:%d\r\n",ret);
        return -5;
    }  
    /*The hal i2s instance1 uses the dma channel3*/
    hal_i2s_instance1->dma.dma_channel = DMA_CHANNEL3;

    /*Open the hal i2s hardware with the hal i2s instance1*/
    ret = hal_i2s_open(hal_i2s_instance1);
    if(ret <= 0)
    {
        printf("hal_i2s_open is error:%d\r\n",ret);
        return -6;
    } 

    return 1;  
}

static int start_example(void)
{
    int ret = 0;
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    Hal_I2s_InitTypeDef* hal_i2s_instance1 = hal_i2s_instance_get(HAL_I2S_INSTANCE1);

    /*Start the i2s with the hal i2s instance*/
    ret = hal_i2s_ctl(hal_i2s_instance,HAL_I2S_CHANNEL_ENABLE_COMMAND,ENABLE);
    if(ret <= 0)
    {
        printf("hal_i2s_ctl is error:%d\r\n",ret);
        return -1;
    }  
    /*Start the i2s with the hal i2s instance1*/
    ret = hal_i2s_ctl(hal_i2s_instance1,HAL_I2S_CHANNEL_ENABLE_COMMAND,ENABLE);
    if(ret <= 0)
    {
        printf("hal_i2s_ctl is error:%d\r\n",ret);
        return -2;
    }  

    return 1;
}

static int data_handle_example(void)
{
    static int data_flag1 = 0,data_flag2 = 0;
    static uint32_t temp1[160] = {0}, temp2[160] = {0};
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    Hal_I2s_InitTypeDef* hal_i2s_instance1 = hal_i2s_instance_get(HAL_I2S_INSTANCE1);
    
    /*Wait for enough data with the hal i2s instance*/
    if(hal_i2s_read(hal_i2s_instance,temp1,NULL,hal_i2s_instance->lr_channel_need_sizes_by_width / 2) > 0)
    {
        data_flag1 = 1;
    }
    /*Wait for enough data with the hal i2s instance1*/
    if(hal_i2s_read(hal_i2s_instance1,temp2,NULL,hal_i2s_instance1->lr_channel_need_sizes_by_width / 2) > 0)
    {
        data_flag2 = 1;
    }

    /*Wait for enough data with the hal i2s instance*/
    if(data_flag1 && data_flag2)
    {
        data_flag1 = 0;
        data_flag2 = 0;

        /*Write the data to i2s with the hal i2s instance*/  
        hal_i2s_write(hal_i2s_instance,temp1,temp2,hal_i2s_instance->lr_channel_need_sizes_by_width / 2);
    }
}

static void i2s_init(void)
{
    init_example();
}

static void i2s_start(void)
{
    start_example();
}

static void i2s_data_handle(void)
{
    data_handle_example();
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
