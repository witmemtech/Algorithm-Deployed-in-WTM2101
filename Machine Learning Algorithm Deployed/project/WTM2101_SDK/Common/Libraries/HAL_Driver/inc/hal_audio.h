/**
  ******************************************************************************
  * @file    hal_audio.h
  * @brief   Header for hal_audio.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef HAL_AUDIO_H
#define HAL_AUDIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "WTM2101.h"
#include "audio.h"
#include "gpio.h"
#include "dma.h"
#include "pmu.h"
#include "rcc.h"

#include "stddef.h"
#include <stdarg.h>

#include "wtm2101_mmap.h"
#include "ring_cache.h"

struct Audio_InitTypeDef;

extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );
#define  HAL_AUDIO_MALLOC(size)  pvPortMalloc(size)
#define  HAL_AUDIO_FREE(p)       vPortFree(p)

typedef enum{
  HAL_AUDIO_CHANNEL_ENABLE_COMMAND     = (1 << 0),                 /*audio channel enabled or disabled command*/
  HAL_AUDIO_INTERRUPT_ENABLE_COMMAND   = (1 << 1),                 /*audio channel interrupt enabled or disabled command*/
  HAL_AUDIO_CHANNEL_DATA_WIDTH16BITS_COMMAND  = (1 << 2),          /*audio channel data width update command*/
  HAL_AUDIO_CLOCK_SWITCH_COMMAND       = (1 << 3),                 /*audio channel clock switch command*/
  HAL_VAD_INTERRUPT_ENABLE_COMMAND     = (1 << 4),                 /*vad interrupt enabled or disabled command*/
}Hal_Audio_Control_Command;
 
typedef enum{
  HAL_AUDIO_INSTANCE1 = 0,               /*the hal audio instance number1*/  
  HAL_AUDIO_INSTANCE2,                   /*the hal audio instance number2*/  
  HAL_AUDIO_INSTANCE3,                   /*the hal audio instance number3*/  
}Hal_Audio_Instance_Typedef; 

typedef enum{
  HAL_AUDIO_MIC_INPUT_AMIC = 0,          /*the input type is amic*/
  HAL_AUDIO_MIC_INPUT_DMIC,              /*the input type is dmic*/
  HAL_AUDIO_MIC_INPUT_LINEIN,            /*the input type is linein*/ /*NOTE,the input linein only use in the HAL_AUDIO_CHANNEL2_NUMBER*/
}Audio_Mic_Input_TypeDef;                

typedef enum {                           
  HAL_AUDIO_CHANNEL0_NUMBER = AUDIO_CHANNEL0,      /*the hal audio channel0*/  
  HAL_AUDIO_CHANNEL1_NUMBER = AUDIO_CHANNEL1,      /*the hal audio channel1*/  
  HAL_AUDIO_CHANNEL2_NUMBER = AUDIO_CHANNEL2,      /*the hal audio channel2*/  
}Audio_Channel_Number_TypeDef;

typedef enum {
  HAL_AUDIO_CHANNEL_WIDTH_12BITS = 0,              /*using pcm 12bits*/  
  HAL_AUDIO_CHANNEL_WIDTH_16BITS,                  /*using pdm 16bits*/      
}Audio_Channel_Width_TypeDef;

typedef enum {
  HAL_AUDIO_CONNECT_PDM0 = AUDIO_PDM0,             /*the hal audio pdm0*/ 
  HAL_AUDIO_CONNECT_PDM1 = AUDIO_PDM1,             /*the hal audio pdm1*/ 
}Audio_Connect_Pdm_Number_TypeDef;

typedef enum{
  HAL_AUDIO_BUFFER_FIFO_MODE  = AUDIO_CHANNEL_TRANSMIT_FIFO_MODE,   /*the hal audio using fifo buffer*/ 
  HAL_AUDIO_BUFFER_RAM_MODE = AUDIO_CHANNEL_TRANSMIT_RAM_MODE,      /*the hal audio using ram buffer*/ 
}Audio_Buffer_Mode_TypeDef;

typedef enum{
  HAL_AUDIO_BUFFER_DATE_FROM_DIGITAL = AUDIO_CHANNEL_INPUT_FROM_DIGITAL,   /*the hal audio buffer data from digital*/ 
  HAL_AUDIO_BUFFER_DATE_FROM_ANALOG  = AUDIO_CHANNEL_INPUT_FROM_ANALOG,    /*the hal audio buffer data from analog*/ 
}Audio_Buffer_Date_Source_TypeDef;

typedef enum{
  HAL_AUDIO_CLK_EDGE_CAPTURE_RISE  = AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE, /*the hal audio rise edge capture data*/ 
  HAL_AUDIO_CLK_EDGE_CAPTURE_FAIL = AUDIO_CHANNEL_FALL_CLOCK_EDGE_CAPTURE,  /*the hal audio fail edge capture data*/ 
}Audio_Clk_Edge_Capture_TypeDef;

typedef enum{
  HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT = AUDIO_RAM_FRAME_VLD_INTERRUPT,         /*the hal audio ram buffer vld interrupt*/  
  HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT = AUDIO_FIFO_HALF_FULL_INTERRUPT, /*the hal audio fifo half full buffer interrupt*/ 
}Audio_Interrupt_TypeDef; 

typedef enum{
  HAL_AUDIO_CLOCK_FROM_AHB = AUDIO_AHB_CLOCK,
  HAL_AUDIO_CLOCK_FROM_FBANK = AUDIO_FBANK_CLOCK,
  HAL_AUDIO_CLOCK_FROM_AUDIO = AUDIO_AUDOI_CLOCK,      /*NOTE,in low power mode with RSM2,the HAL_AUDIO_CLOCK_FROM_AUDIO must updata before it is entered \
                                                        the HAL_AUDIO_CLOCK_FROM_AHB must updata after it is returned*/
}Audio_Clock_Switch_TypeDef; 

typedef enum{
  HAL_AUDIO_ANALOG_MIC_BOOST_20DB = 0,                       
  HAL_AUDIO_ANALOG_MIC_BOOST_12DB,
  HAL_AUDIO_ANALOG_MIC_BOOST_0DB,
}Audio_Analog_Mic_Boost_TypeDef;

typedef enum{
  HAL_AUDIO_ANALOG_LIN_BOOST_M12DB = 0,    // -12dB
  HAL_AUDIO_ANALOG_LIN_BOOST_M6DB,         // -6dB
  HAL_AUDIO_ANALOG_LIN_BOOST_0DB,
  HAL_AUDIO_ANALOG_LIN_BOOST_6DB,
  HAL_AUDIO_ANALOG_LIN_BOOST_12DB,
  HAL_AUDIO_ANALOG_LIN_BOOST_18DB,
  HAL_AUDIO_ANALOG_LIN_BOOST_24DB,
}Audio_Analog_Lin_Boost_TypeDef;

typedef struct {
  //------ Boost config ----------------------------------
  Audio_Analog_Mic_Boost_TypeDef  MicBoostGain;                 
  Audio_Analog_Lin_Boost_TypeDef  LinBoostGain;
  //------ PGA config ------------------------------------
  uint32_t                        PGAGainDefault;
  uint32_t                        PGAGainMinmal;
  uint32_t                        PGAGainMaximal;
  //------ AGC config ------------------------------------

  FunctionalState                 AGC_Enable;
  uint32_t                        AGCOverSampling;
  uint32_t                        AGCTargetThreshold;
  uint32_t                        AGCMaximalThreshold;
  int32_t                         AGCShortTermAttack;
  int32_t                         AGCLongTermAttack;
  int32_t                         AGCLongTermRelease;
}Audio_Analog_InitConfig;

typedef struct{
  FunctionalState enable;                                         /*the pdm enabled flag*/
  Audio_Connect_Pdm_Number_TypeDef PdmNumber;                     /*the audio channel was connect with which the pdm*/
  uint32_t Pdm_Clk_Io,Pdm_Data_Io;                                /*the gpio of pdm data and clock*/
  uint32_t Pdm_Clk_IO_AF,Pdm_Data_Io_AF;                          /*the gpio_af of pdm data and clock*/
}Audio_Connect_Pdm_Typedef; 

typedef struct
{ 
  FunctionalState           FuncAnalogPreEmphasis;                  
  FunctionalState           FuncSinc5D2;                         
  FunctionalState           FuncHalfBandD2;                       
  FunctionalState           FuncHighPass;                         
  FunctionalState           FuncPreEmphasis;                     
}Audio_Filter_Parameter_Typedef; 

typedef struct{
  Audio_Channel_Number_TypeDef    ChannelNumber;                   /*the audio channel number*/
  Audio_Channel_Width_TypeDef     ChannelWidth;                    /*the data width of audio channel,the HAL_AUDIO_CHANNEL_WIDTH_12BITS only use in the HAL_AUDIO_CHANNEL0_NUMBER*/
  Audio_Buffer_Mode_TypeDef       BufferMode;                      /*the data buffer mode of audio channel,the HAL_AUDIO_BUFFER_RAM_MODE only use in the HAL_AUDIO_CHANNEL0_NUMBER*/
  Audio_Buffer_Date_Source_TypeDef Source;                         /*the data source of audio channel.if the input type is the HAL_AUDIO_MIC_INPUT_DMIC,the HAL_AUDIO_BUFFER_DATE_FROM_DIGITAL is used,otherwise the HAL_AUDIO_BUFFER_DATE_FROM_ANALOG is used*/
  uint32_t                        ChannelGain;                     /*the channel gain,from 0 to 16,it is 16 by default*/
  Audio_Clk_Edge_Capture_TypeDef  Clk_Edge;                        /*the data was captured in clock edge*/
  Audio_Filter_Parameter_Typedef  Filter;                          /*the filter parameter of audio channel*/
  uint32_t                        Buffer_Ram_Depth,Buffer_Ram_Frame_Move,Buffer_Ram_Length;        /*the ram data buffer parameter of audio channel,the Buffer_Ram_Depth is max buffer size,the Buffer_Ram_Frame_Move is data-point need move size,the Buffer_Ram_Length is data received size*/
}Audio_Channel_InitTypeDef;

typedef struct{
  FunctionalState enable;                            /*the audio interrupt enable flag*/
  Audio_Interrupt_TypeDef type;                      /*the audio interrupt type*/
}Audio_Interrupt_Config_TypeDef;

typedef struct{
  union{
    struct{
      volatile uint8_t sram_data_flag;                /*the audio channel data flag in HAL_AUDIO_BUFFER_RAM_MODE mode*/
      uint8_t *sram_data;                             /*the audio channel data address malloced by special area in HAL_AUDIO_BUFFER_RAM_MODE mode*/
    }sram;
    Ring_Cache                    ring;               /*the ring buffer to cache the audio data in HAL_AUDIO_BUFFER_FIFO_MODE mode*/
  }cache;
}HAL_AUDIO_CACHE; 

typedef struct
{
  void(*dma_receive_handler)(struct Audio_InitTypeDef *audio_instance);
  void(*audio_receive_handler)(struct Audio_InitTypeDef *audio_instance);
}Hal_Audio_Data_handle;

typedef struct Audio_InitTypeDef{
  FunctionalState enable;                             /*init flag with hal audio*/
  AUD_TypeDef                     *instance;          /*hardware address with audio module*/
  FunctionalState                 audio_rst;          /*the audio hardware reset flag*/
  uint32_t                        prescale;           /*the prescale of audio clock*/
  uint32_t                        divider;            /*the divider of audio module,the audio real clock = system clock / prescale / divider*/
                                                      /*the system clock can be internal or external.the system clock is 24mhz by default*/
  Audio_Mic_Input_TypeDef         InputType;          /*the audio channel input type*/
  Audio_Connect_Pdm_Typedef       Pdm;                /*if the audio channel input type is the HAL_AUDIO_MIC_INPUT_DMIC,the gpio must be configurated*/
                                                      /*please you make sure use right gpio number*/
  Audio_Channel_InitTypeDef       channel;            /*the audio channel parameter*/
  Audio_Analog_InitConfig         Analog;             /*the analog configuration of audio channel,it is not recommended to modify the general simulation parameters*/
  Audio_Interrupt_Config_TypeDef  interrupt;          /*the interrupt configuration of audio channel*/  
   
  FunctionalState                 dma_enable;         /*the dma enable flag*/ 
  uint32_t                        dma_channel;        /*the dma channel is used*/
  volatile uint32_t               dma_finish_flag;    /*the dma finished flag*/
  DMA_InitTypeDef                 dma;                /*the dma configuration parameter*/

  FunctionalState                 vad_flag;           /*the vad enabled flag*/
  
  HAL_AUDIO_CACHE                 audio_cache;        /*the audio channel data cache*/ 
  Hal_Audio_Data_handle           Data_handle_info;   /*the buffer handle call*/
}Audio_InitTypeDef;

/**
* @brief  Get the hal audio instance 
* @param  number:the hal audio instance number
* @retval the hal audio instance
*/ 
extern Audio_InitTypeDef* hal_audio_instance_get(Hal_Audio_Instance_Typedef number);

/**
* @brief  Init the hal audio instance 
* @param  audio_instance: the hal audio instance
* @param  type: the audio input type with Audio_Mic_Input_TypeDef
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int hal_audio_init(Audio_InitTypeDef *audio_instance,Audio_Mic_Input_TypeDef type);

/**
* @brief  Open the actual related audio hardware 
* @param  audio_instance: the hal audio instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_audio_open(Audio_InitTypeDef *audio_instance);

/**
* @brief  Control the hal audio instance and hradware
* @param  audio_instance: the hal audio instance
* @param  command: the related command with Hal_Audio_Control_Command
* @param  ...: the attach value about the parameter command
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_audio_ctl(Audio_InitTypeDef *audio_instance,int command, ...);

/**
* @brief  Read data from the hal audio buffer
* @param  audio_instance: the hal audio instance
* @param  buffer: the data buffer.Note if the hal audio buffer mode is HAL_AUDIO_BUFFER_RAM_MODE,the parameter buffer must be NULL.
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_audio_read(Audio_InitTypeDef *audio_instance,uint8_t *buffer);

/**
* @brief  Close the hal audio instance and related hardware
* @param  audio_instance: the hal audio instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_audio_close(Audio_InitTypeDef *audio_instance);

//////////////////////////////yxp/////////////
extern int hal_audio_ana_init(Audio_InitTypeDef *audio_instance);

#ifdef __cplusplus
}
#endif

#endif
