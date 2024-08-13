/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the DMA to transfer 
  *          continuously converted data.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "main.h"

#define DMA_TEST_BUFFER_LEN (10)

volatile Bool dma_transfer_flag = FALSE;

static void dma_test(void);
static void dma_config(void);
static void system_clock_init(void);
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
  
    /* Initial clock */
    system_clock_init();
  
    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    dma_config();
    dma_test();

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

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN, ENABLE);
   
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

static void dma_config(void)
{
    DMA_InitTypeDef dma_init_type;
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN,ENABLE);
    
    /* Initial interrupt */
    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);
    
    /* Initial dma from memory to memory */
    DMA_Clear_All_Interrupt_Cmd(DMA);
    dma_init_type.llp_src_en = DISABLE;
    dma_init_type.llp_dst_en = DISABLE;
    dma_init_type.reload_src_en = DISABLE;
    dma_init_type.reload_dst_en = DISABLE;
    dma_init_type.direction = MEM_TO_MEM_FLOW_CTOL_DMA;
    dma_init_type.src_msize = DMA_MSIZE1;
    dma_init_type.dst_msize = DMA_MSIZE1;
    dma_init_type.src_addr_type = DMA_ADDRESS_INCREASE;
    dma_init_type.dst_addr_type = DMA_ADDRESS_INCREASE;
    dma_init_type.src_width = DMA_WIDTH8;
    dma_init_type.dst_width = DMA_WIDTH8;
    dma_init_type.src_per = OTHER_REQ;
    dma_init_type.dst_per = OTHER_REQ;
    dma_init_type.fifo_mode_en = DISABLE;
    dma_init_type.max_abrst = 0;
    dma_init_type.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_init_type.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_init_type.chanel_priority = DMA_PRIORITY0;
    dma_init_type.int_en = ENABLE;
    DMA_Init(DMA, DMA_CHANNEL0, &dma_init_type);

    /* DMA is enabled */
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    /* DMA transfer finished interrupt is enabled */
    DMA_Set_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0, ENABLE);
}

static void dma_test(void)
{
    int err = 0;
    uint8_t *dmarxdata = (uint8_t *)(mmap_to_sys((uint32_t)malloc(DMA_TEST_BUFFER_LEN)));
    uint8_t *dmatxdata = (uint8_t *)(mmap_to_sys((uint32_t)malloc(DMA_TEST_BUFFER_LEN)));

    for (int i = 0; i < DMA_TEST_BUFFER_LEN; i++)
    {
        dmatxdata[i] = 255 - i;
    }

    DMA_Set_Addr(DMA, DMA_CHANNEL0, (uint32_t)dmatxdata, (uint32_t)dmarxdata, DMA_TEST_BUFFER_LEN, 0);
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL0, ENABLE);

    while (!dma_transfer_flag);
    dma_transfer_flag = FALSE;
    for (int i = 0; i < DMA_TEST_BUFFER_LEN; i++) 
    {
        if (dmarxdata[i] != 255 - i) {
            err++;
            printf("dma value:%d:index:%d\r\n",dmarxdata[i],i);
        }
    }
    if (err == 0)
    {
        printf("test succeed\r\n");
    }
    free(dmarxdata);
    free(dmatxdata);
}

void DMA_IRQHandler(void)
{
    uint8_t transfer_int_flag = 0;
    transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);
    if (transfer_int_flag & DMA_CHANNEL0_INT_FLAG) {
        DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0);
        dma_transfer_flag = TRUE;
    }
}