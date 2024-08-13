/**
  ******************************************************************************
  * @file    hal_i2s.h
  * @brief   Header for hal_i2s.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef HAL_I2S_H
#define HAL_I2S_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "WTM2101.h"
#include "i2s.h"
#include "gpio.h"
#include "dma.h"
#include "pmu.h"
#include "rcc.h"

#include "stddef.h"
#include <stdarg.h>
#include "string.h"
#include <stdlib.h>

#include "ring_cache.h"
#include "wtm2101_mmap.h"
struct Hal_I2s_InitTypeDef;

extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );
#define  HAL_I2S_MALLOC(size)  pvPortMalloc(size)
#define  HAL_I2S_FREE(p)       vPortFree(p)

typedef enum{
  HAL_I2S_CHANNEL_ENABLE_COMMAND     = (1 << 0),                 /*the hal i2s enabled or disabled command*/
  HAL_I2S_CHANNEL_UPDATA_CLOCK_COMMAND = (1 << 1),               /*the hal i2s updata clock command*/
}Hal_I2s_Control_Command;
 
typedef enum{
  HAL_I2S_INSTANCE0 = 0,                                         /*the hal i2s instance number0*/  
  HAL_I2S_INSTANCE1,                                             /*the hal i2s instance number1*/  
}Hal_I2s_Instance_Typedef; 

//typedef enum{
//  HAL_I2S0_ADDRESS = (uint32_t)(AUD_TypeDef*)I2S0,
//  HAL_I2S1_ADDRESS = (uint32_t)(AUD_TypeDef*)I2S1,
//}Hal_I2s_Address_Typedef; 

typedef enum{
  HAL_I2S_ONLY_RECEIVE = 0,                                     /*only receive mode*/  
  HAL_I2S_ONLY_SEND,                                            /*only send mode*/  
  HAL_I2S_RECEIVE_AND_SEND,                                     /*send and receive mode*/
}Hal_I2s_Type_Typedef; 

typedef enum{ 
  HAL_I2S_MASTER = I2S_MASTER,                                  /*master mode*/
  HAL_I2S_SLAVE = I2S_SLAVE,                                    /*slave mode*/
}Hal_I2s_Work_Mode_Typedef;

typedef enum{
  HAL_I2S_16BITS_WIDTH_WORD = 2,                                /*16bits width word*/      
  HAL_I2S_32BITS_WIDTH_WORD = 4,                                /*32bits width word*/
}Hal_I2s_Width_Word_Typedef;

typedef struct{
  uint32_t sdo_io,sdi_io,bclk_io,lrclk_io;                        /*the gpio*/
  uint32_t sdo_io_af,sdi_io_af,bclk_io_af,lrclk_io_af;            /*the gpio_af*/
}Hal_I2s_Gpio_Typedef; 

typedef struct{
  int lr_channel_need_sizes_by_width_counts;        /*the buffer size,it is some timers of the parameter lr_channel_need_sizes_by_width by default*/
  uint8_t *buffer;        /*the data buffer*/
  int read_index;         /*the read index of data buffer*/
  int write_index;        /*the write index of data buffer*/
}Hal_I2s_Cache_Typedef; 

typedef struct{
  FunctionalState enable;             /*the dma enable flag*/  
  uint32_t dma_channel;               /*the dma channel*/
  DMA_InitTypeDef config;             /*the dma configuration struct parameter*/
  DMA_LlpTypeDef llp_cfg[2];          /*the dma link script configuration struct parameter*/
  uint8_t cache_buffer[16 * 4 * 2];   /*the data cache buffer for dma used*/
  uint32_t dma_cnt;                   /*the dma count flag*/
}Hal_I2s_Dma_Typedef;

typedef struct
{
  void(*transfer_and_receive_handler)(struct Hal_I2s_InitTypeDef *i2s_instance);
}Data_handle;

typedef struct Hal_I2s_InitTypeDef{
  FunctionalState enable;                         /*init flag*/
  I2S_TypeDef *instance;                          /*the hardware address*/
  Hal_I2s_Gpio_Typedef io;                        /*the gpio*/
  Hal_I2s_Type_Typedef type;                      /*the work type*/
  Hal_I2s_Work_Mode_Typedef mode;                 /*the work mode*/
  Hal_I2s_Width_Word_Typedef width_word;          /*the width word*/
  int lrclk_frequency;                            /*the lrclk frequency*/
  int lr_channel_need_sizes_by_width;             /*the cached data sizes by the width word with the left and right channel need to be handled by the application*/         
  Hal_I2s_Cache_Typedef send_buffer;              /*the send buffer to cache the hal i2s data*/
  Hal_I2s_Cache_Typedef receive_buffer;           /*the receive buffer to cache the hal i2s data*/
  Data_handle Data_handle_info;                   /*the buffer handle call*/
  Hal_I2s_Dma_Typedef dma;                        /*the dma configuration*/             
}Hal_I2s_InitTypeDef;

/**
* @brief  Get the hal i2s instance 
* @param  number:the hal i2s instance number
* @retval the hal i2s instance
*/ 
extern Hal_I2s_InitTypeDef* hal_i2s_instance_get(Hal_I2s_Instance_Typedef number);

/**
* @brief  Init the hal i2s instance 
* @param  i2s_instance: the hal i2s instance
* @param  address: the hardware address
* @param  type: the work type
* @param  mode: the work mode
* @param  width: the width word
* @param  lr_channel_need_sizes_by_width: the cached data sizes by the width word with the left and right channel need to be handled by the application
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int hal_i2s_init(Hal_I2s_InitTypeDef *i2s_instance,I2S_TypeDef *address,Hal_I2s_Type_Typedef type,Hal_I2s_Work_Mode_Typedef mode,Hal_I2s_Width_Word_Typedef width,int lr_channel_need_sizes_by_width);

/**
* @brief  Open the actual related i2s hardware 
* @param  i2s_instance: the i2s clock instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_i2s_open(Hal_I2s_InitTypeDef *i2s_instance);

/**
* @brief  Control the hal i2s instance and hradware
* @param  i2s_instance: the hal i2s instance
* @param  command: the related command with Hal_I2s_Control_Command
* @param  ...: the attach value about the parameter command
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_i2s_ctl(Hal_I2s_InitTypeDef *i2s_instance,int command, ...);

/**
* @brief  Write data to the hal i2s buffer
* @param  i2s_instance: the hal i2s instance
* @param  left_data: the left channel data
* @param  right_data: the right channel data
* @param  size_by_data: the single channel data sizes
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_i2s_write(Hal_I2s_InitTypeDef *i2s_instance,void *left_data,void *right_data,int size_by_data);

/**
* @brief  Read data from the hal i2s buffer
* @param  i2s_instance: the hal i2s instance
* @param  left_data: the left channel data
* @param  right_data: the right channel data
* @param  size_by_data: the single channel data sizes
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_i2s_read(Hal_I2s_InitTypeDef *i2s_instance,void *left_data,void *right_data,int size_by_data);

/**
* @brief  Close the hal i2s instance and related hardware
* @param  i2s_instance: the hal i2s instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_i2s_close(Hal_I2s_InitTypeDef *i2s_instance);

#ifdef __cplusplus
}
#endif

#endif
