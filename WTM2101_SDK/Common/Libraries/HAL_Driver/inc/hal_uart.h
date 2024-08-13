/**
  ******************************************************************************
  * @file    hal_uart.h
  * @brief   Header for hal_uart.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef HAL_UART_H
#define HAL_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "wtm2101_config.h"

#include "stddef.h"
#include <stdarg.h>
#include "string.h"

#include "wtm2101_hal.h"
#include "wtm2101_mmap.h"
#include "ring_cache.h"
#include "LibNPU.h"
#include "heap.h"

#define HAL_UART_SEND_DMA_DEFAULT_CHANNEL DMA_CHANNEL4
#define HAL_UART_RECEIVE_RING_BUFFER_DEFAULT_SIZE (1.5 * 1024)

struct Hal_Uart_InitTypeDef;
typedef int(*async_handler)(struct Hal_Uart_InitTypeDef *i2s_instance);

typedef enum{
  HAL_UART_MODE_SWITCH_COMMAND     = (1 << 0),                      /*the hal uart mode switch command*/
}Hal_Uart_Control_Command;

typedef enum
{
    HAL_UART_INSTANCE0 = 0,                                         /*the hal uart instance number0*/  
    HAL_UART_INSTANCE1,                                             /*the hal uart instance number1*/  
}Hal_Uart_Instance_Typedef; 

typedef enum
{
    HAL_UART_RECEIVE_SYNC = 0,                                      /*sync mode*/  
    HAL_UART_RECEIVE_ASYNC,                                         /*async mode*/  
}Hal_Uart_Receive_Mode_Typedef; 

typedef struct
{
    FunctionalState enable;             /*the dma enable flag*/  
    uint32_t dma_channel;               /*the dma channel*/
    DMA_InitTypeDef config;             /*the dma configuration struct parameter*/
    DMA_LlpTypeDef *llp_cfg;            /*the dma link script configuration struct parameter*/
    volatile uint32_t finish_flag;    
}Hal_Uart_Dma_Typedef;

typedef struct
{
    uint32_t uart_tx,uart_rx;                         /*the gpio*/
    uint32_t uart_tx_af,uart_rx_af;                   /*the gpio_af*/
}Hal_Uart_Gpio_Typedef; 

typedef struct
{
    void(*async_receive_handler)(struct Hal_Uart_InitTypeDef *i2s_instance);
    void(*send_dma_finish_handler)(struct Hal_Uart_InitTypeDef *i2s_instance);
    void(*uart_timeout_handler)(struct Hal_Uart_InitTypeDef *i2s_instance);
}Hal_Uart_Data_handle;

typedef struct
{
    Ring_Cache ring_buffer;                         /*ring buffer*/
}Hal_Uart_CacheTypeDef;

typedef struct Hal_Uart_InitTypeDef
{
    FunctionalState enable;                         /*init flag*/
    UART_TypeDef *instance;                         /*the hardware address*/
    TMR_TypeDef *timer_instance;                    /*uart-timer timerout*/
    UART_InitTypeDef initstructure;                 /*uart initstructure*/
    Hal_Uart_Gpio_Typedef io;                       /*the gpio*/
    Hal_Uart_Receive_Mode_Typedef sync_async_flag;  /*work mode*/
    Bool sync_receive_flag;                         /*sync mode,receive flag*/
    async_handler async_callback;                   /*async mode,callback function*/   
    Hal_Uart_Data_handle data_handle_info;          /*inter function*/
    Hal_Uart_CacheTypeDef cache;                    /*cache*/
    Hal_Uart_Dma_Typedef send_dma;                  /*send dma*/  
}Hal_Uart_InitTypeDef;

/**
* @brief  Get the hal uart instance 
* @param  number:the hal uart instance number
* @retval the hal uart instance
*/ 
extern Hal_Uart_InitTypeDef* hal_uart_instance_get(Hal_Uart_Instance_Typedef number);

/**
* @brief  Init the hal uart instance 
* @param  uart_instance: the hal uart instance
* @param  address: the hardware address
* @param  initstructure: the uart initstructure
* @param  flag: sync or async mode
* @param  async_callback: async mode callback
* @param  send_dma_enable_flag: send dma enaled or disabled flag
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int hal_uart_init(Hal_Uart_InitTypeDef *uart_instance,UART_TypeDef *address,UART_InitTypeDef *initstructure,Hal_Uart_Receive_Mode_Typedef flag,async_handler async_callback,FunctionalState send_dma_enable_flag);

/**
* @brief  Open the actual related uart hardware 
* @param  uart_instance: the uart clock instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_uart_open(Hal_Uart_InitTypeDef *uart_instance);

/**
* @brief  Control the hal uart instance and hradware
* @param  uart_instance: the hal uart instance
* @param  command: the related command with Hal_Uart_Control_Command
* @param  ...: the attach value about the parameter command
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_uart_ctl(Hal_Uart_InitTypeDef *uart_instance,int command, ...);

/**
* @brief  Sync Read data from the hal uart buffer
* @param  uart_instance: the hal uart instance
* @param  buffer: the data buffer
* @param  size: the data buffer sizes
* @param  read_size: read data size
* @param  timeout_ms: timeout ms,value 0xffffffff forever 
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_uart_read(Hal_Uart_InitTypeDef *uart_instance,uint8_t *buffer,uint32_t size,uint32_t *read_size,uint32_t timeout_ms);

/**
* @brief  Write data to the hal uart buffer
* @param  uart_instance: the hal uart instance
* @param  buffer: the data buffer
* @param  size: the data buffer sizes
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_uart_write(Hal_Uart_InitTypeDef *uart_instance,uint8_t *buffer,uint32_t size);

/**
* @brief  Close the hal uart instance and related hardware
* @param  uart_instance: the hal uart instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_uart_close(struct Hal_Uart_InitTypeDef *uart_instance);


#ifdef __cplusplus
}
#endif

#endif
