/**
  ******************************************************************************  
  * @file    audio.h
  * @brief   Header for audio.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************  
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __AUDIO_H__
#define __AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "stddef.h"
#include "riscv_encoding.h"
#include "WTM2101_AUDIO_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup AUDIO
  * @{
  */ 
  
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup AUDIO_Exported_Constants
  * @{
  */ 

/** @defgroup AUDIO_Pdm
  * @{
  */
#define AUDIO_PDM0                                    (0x00)
#define AUDIO_PDM1                                    (0x01)
#define IS_AUDIO_PDM(channel)                        (((channel) == AUDIO_PDM0) || \
                                                      ((channel) == AUDIO_PDM1))

/**
  * @}
  */

/** @defgroup AUDIO_Channel
  * @{
  */
#define AUDIO_CHANNEL0                                (0x01)
#define AUDIO_CHANNEL1                                (0x02)
#define AUDIO_CHANNEL2                                (0x04)
#define IS_AUDIO_CHANNEL(channel)                    (((channel) == AUDIO_CHANNEL0) || \
                                                      ((channel) == AUDIO_CHANNEL1) || \
                                                      ((channel) == AUDIO_CHANNEL2))

/**
  * @}
  */

/** @defgroup AUDIO_Channel_Transmit_Mode
  * @{
  */
#define AUDIO_CHANNEL_TRANSMIT_FIFO_MODE              (0x00)
#define AUDIO_CHANNEL_TRANSMIT_RAM_MODE               (0x02)
#define AUDIO_CHANNEL_TRANSMIT_FBANK_MODE             (0x03)
#define IS_AUDIO_CHANNEL_TRANSMIT_MODE(mode)         (((mode) == AUDIO_CHANNEL_TRANSMIT_FIFO_MODE) || \
                                                      ((mode) == AUDIO_CHANNEL_TRANSMIT_RAM_MODE)  || \
                                                      ((mode) == AUDIO_CHANNEL_TRANSMIT_FBANK_MODE))

/**
  * @}
  */

/** @defgroup  AUDIO_Channel_Input_Select
  * @{
  */
#define AUDIO_CHANNEL_INPUT_FROM_DIGITAL              (0x00)
#define AUDIO_CHANNEL_INPUT_FROM_ANALOG               (0x01)
#define IS_AUDIO_Channel_INPUT_SELECT(input)         (((input) == AUDIO_CHANNEL_INPUT_FROM_DIGITAL) || \
                                                      ((input) == AUDIO_CHANNEL_INPUT_FROM_ANALOG))

/**
  * @}
  */

/** @defgroup  AUDIO_Channel_Capture_Clock_Edge
  * @{
  */
#define AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE           (0x00)
#define AUDIO_CHANNEL_FALL_CLOCK_EDGE_CAPTURE           (0x01)
#define IS_AUDIO_CHANNEL_CAPTURE_CLOCK_EDGE(edge)      (((edge) == AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE) || \
                                                        ((edge) == AUDIO_CHANNEL_FALL_CLOCK_EDGE_CAPTURE))

/**
  * @}
  */

/** @defgroup  AUDIO_Biquad_Source_Select
  * @{
  */
#define AUDIO_BIQUAD_SOURCE_SELECT_FROM_SINC_FILTER     (0x00)
#define AUDIO_BIQUAD_SOURCE_SELECT_FROM_SINC_COMPENSATE (0x01)
#define IS_AUDIO_BIQUAD_SOURCE_SELECT(select)          (((select) == AUDIO_Biquad_Source_Select_From_Sinc_Filter) || \
                                                        ((select) == AUDIO_Biquad_Source_Select_From_Sinc_Compensate))

/**
  * @}
  */

/** @defgroup AUDIO_Channel0_Pcm_Zeropadding
  * @{
  */
#define AUDIO_CHANNEL0_PCM_ZEROPADDING_NO               (0x00)
#define AUDIO_CHANNEL0_PCM_ZEROPADDING_1                (0x01)
#define AUDIO_CHANNEL0_PCM_ZEROPADDING_2                (0x02)
#define AUDIO_CHANNEL0_PCM_ZEROPADDING_3                (0x03)
#define AUDIO_CHANNEL0_PCM_ZEROPADDING_4                (0x04)
#define IS_AUDIO_CHANNEL0_PCM_ZEROPADDING(value)       (((value) == AUDIO_CHANNEL0_PCM_ZEROPADDING_NO) || \
                                                        ((value) == AUDIO_CHANNEL0_PCM_ZEROPADDING_1)  || \
                                                        ((value) == AUDIO_CHANNEL0_PCM_ZEROPADDING_2)  || \
                                                        ((value) == AUDIO_CHANNEL0_PCM_ZEROPADDING_3)  || \
                                                        ((value) == AUDIO_CHANNEL0_PCM_ZEROPADDING_4))

/**
  * @}
  */

/** @defgroup  AUDIO_Ram_Fifo_Vad_Interrupt
  * @{
  */
#define AUDIO_RAM_FRAME_VLD_INTERRUPT                   (0X01)
#define AUDIO_FIFO_FULL_INTERRUPT                       (0X02)
#define AUDIO_FIFO_HALF_FULL_INTERRUPT                  (0X04)
#define AUDIO_FIFO_EMPTY_INTERRUPT                      (0X08)
#define AUDIO_FIFO_OVERFLOW_INTERRUPT                   (0X10)
#define AUDIO_FIFO_UNDERFLOW_INTERRUPT                  (0X20)
#define AUDIO_FIFO_WRITE_INTERRUPT                      (0X40)
#define AUDIO_FIFO_READ_INTERRUPT                       (0X80)
#define AUDIO_VAD_ACT_INTERRUPT                         (0X100)
#define AUDIO_RAM_INTERRUPT                             (0X200)
#define AUDIO_RAM_READ_INTERRUPT                        (0X400)
#define IS_AUDIO_RAM_FIFO_VAD_INTERRUPT(interrupt)     (((interrupt) == AUDIO_RAM_FRAME_VLD_INTERRUPT)  || \
                                                        ((interrupt) == AUDIO_FIFO_FULL_INTERRUPT)      || \
                                                        ((interrupt) == AUDIO_FIFO_HALF_FULL_INTERRUPT) || \
                                                        ((interrupt) == AUDIO_FIFO_EMPTY_INTERRUPT)     || \
                                                        ((interrupt) == AUDIO_FIFO_OVERFLOW_INTERRUPT)  || \
                                                        ((interrupt) == AUDIO_FIFO_UNDERFLOW_INTERRUPT) || \
                                                        ((interrupt) == AUDIO_FIFO_WRITE_INTERRUPT)     || \
                                                        ((interrupt) == AUDIO_FIFO_READ_INTERRUPT)      || \
                                                        ((interrupt) == AUDIO_VAD_ACT_INTERRUPT)        || \
                                                        ((interrupt) == AUDIO_RAM_INTERRUPT)            || \
                                                        ((interrupt) == AUDIO_RAM_READ_INTERRUPT))
/**
  * @}
  */


/** @defgroup  AUDIO_Digital_Comp_Channel_Interrupt 
 * @{
 */
#define AUDIO_DIGITAL_CMPA_INTERRUPT                        (0x01)
#define AUDIO_DIGITAL_CMPB_INTERRUPT                        (0x02)
#define AUDIO_COMP_WAKEUP_INTERRUPT                         (0x04)
#define AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT               (0x08)
#define AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT                (0x10)
#define AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT             (0x20)
#define IS_AUDIO_DIGITAL_COMP_CHANNEL_INTERRUPT(interrupt) (((interrupt) == AUDIO_DIGITAL_CMPA_INTERRUPT)          || \
                                                            ((interrupt) == AUDIO_DIGITAL_CMPB_INTERRUPT)          || \
                                                            ((interrupt) == AUDIO_COMP_WAKEUP_INTERRUPT)           || \
                                                            ((interrupt) == AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT) || \
                                                            ((interrupt) == AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT)  || \
                                                            ((interrupt) == AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT))

/**
  * @}
  */

/** @defgroup AUDIO_Clock_SWitch_Configuration
  * @{
  */
#define AUDIO_AHB_CLOCK                                     (0x00)
#define AUDIO_FBANK_CLOCK                                   (0x01)
#define AUDIO_AUDOI_CLOCK                                   (0x02) 
#define IS_AUDIO_CLOCK_SWITCH_CONFIGURATION(clock)         (((clock) == AUDIO_AHB_CLOCK)   || \
                                                            ((clock) == AUDIO_FBANK_CLOCK) || \
                                                            ((clock) == AUDIO_AUDOI_CLOCK))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup AUDIO_Functions_Prototypes AUDIO Functions Prototypes
* @{
*/

/**
* @brief  The audio gets channel transmit enabled-status
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval ENABLE or DISABLE
*/
extern FunctionalState AUDIO_Get_Channel_Transmit_Enabledstatus(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets channel transmit command
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Channel_Transmit_Cmd(AUD_TypeDef *audio, uint8_t channel, FunctionalState newstatus);

/**
* @brief  The audio gets channel transmit mode
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval This can be one value of @ref AUDIO_Channel_Transmit_Mode
*/
extern uint8_t AUDIO_Get_Channel_Transmit_Mode(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets channel transmit mode
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  mode: This parameter can be one value of @ref AUDIO_Channel_Transmit_Mode
* @retval None
*/
extern void AUDIO_Set_Channel_Transmit_Mode(AUD_TypeDef *audio, uint8_t channel, uint8_t mode);

/**
* @brief  The audio gets channel input-select
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval This can be one value of @ref AUDIO_Channel_Input_Select
*/
extern uint8_t AUDIO_Get_Channel_Input_Select(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets channel input-select
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  select: This parameter can be one value of @ref AUDIO_Channel_Input_Select
* @retval None
*/
extern void AUDIO_Set_Channel_Input_Select(AUD_TypeDef *audio, uint8_t channel, uint8_t select);

/**
* @brief  The audio gets channel clock divider 
* @param  audio: audio base address: @ref AUD
* @retval the divider value
*/
extern uint8_t AUDIO_Get_Channel_Clock_Divider(AUD_TypeDef *audio);

/**
* @brief  The audio sets channel clock divider 
* @param  audio: audio base address: @ref AUD
* @param  divider: This parameter can be value between 0 and 7 
* @retval None
*/
extern void AUDIO_Set_Channel_Clock_Divider(AUD_TypeDef *audio, uint8_t divider);

/**
* @brief  The audio gets channel edge capture way
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval This can be one value of @ref AUDIO_Channel_Capture_Clock_Edge
*/
extern uint8_t AUDIO_Get_Channel_Edge_Capture_Select(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets channel edge capture way
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  edge: This parameter can be one value of @ref AUDIO_Channel_Capture_Clock_Edge
* @retval None
*/
extern void AUDIO_Set_Channel_Edge_Capture_Select(AUD_TypeDef *audio, uint8_t channel, uint8_t edge);

/**
* @brief  The audio gets biquad selecting channel
* @param  audio: audio base address: @ref AUD
* @retval This can be one value of @ref AUDIO_Channel,but just for AUDIO_Channel0 and AUDIO_Channel1
*/
extern uint8_t AUDIO_Get_Biquad_Select_Channel(AUD_TypeDef *audio);

/**
* @brief  The audio sets biquad selecting channel
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel,but just for AUDIO_Channel0 and AUDIO_Channel1
* @retval None
*/
extern void AUDIO_Set_Biquad_Select_Channel(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio gets biquad selecting source
* @param  audio: audio base address: @ref AUD
* @retval This can be one value of @ref AUDIO_Biquad_Source_Select
*/
extern uint8_t AUDIO_Get_Biquad_SelectSource(AUD_TypeDef *audio);

/**
* @brief  The audio sets biquad selecting source
* @param  audio: audio base address: @ref AUD
* @param  source: This parameter can be one value of @ref AUDIO_Biquad_Source_Select
* @retval None
*/
extern void AUDIO_Set_Biquad_SelectSource(AUD_TypeDef *audio, uint8_t source);

/**
* @brief  The audio gets sinc5d2 bypass enabled status
* @param  audio: audio base address: @ref AUD
* @retval ENABLE or DISABLE
*/
extern FunctionalState AUDIO_Get_Sinc5d2_Bypass_EnabledStatus(AUD_TypeDef *audio);

/**
* @brief  The audio sets sinc5d2 bypass enabled status
* @param  audio: audio base address: @ref AUD
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Sinc5d2_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus);

/**
* @brief  The audio gets halfband bypass enabled status
* @param  audio: audio base address: @ref AUD
* @retval ENABLE or DISABLE
*/
extern FunctionalState AUDIO_Get_Halfband_Bypass_EnabledStatus(AUD_TypeDef *audio);

/**
* @brief  The audio sets halfband bypass enabled status
* @param  audio: audio base address: @ref AUD
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Halfband_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus);

/**
* @brief  The audio gets highpass bypass enabled status
* @param  audio: audio base address: @ref AUD
* @retval ENABLE or DISABLE
*/
extern FunctionalState AUDIO_Get_Highpass_Bypass_EnabledStatus(AUD_TypeDef *audio);

/**
* @brief  The audio sets highpass bypass enabled status
* @param  audio: audio base address: @ref AUD
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Highpass_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus);

/**
* @brief  The audio gets biquad bypass enabled status
* @param  audio: audio base address: @ref AUD
* @retval ENABLE or DISABLE
*/
extern FunctionalState AUDIO_Get_Biquad_Bypass_EnabledStatus(AUD_TypeDef *audio);

/**
* @brief  The audio sets biquad bypass enabled status
* @param  audio: audio base address: @ref AUD
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Biquad_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus);

/**
* @brief  The audio gets channel high bypass enabled status
* @param  audio: audio base address: @ref AUD
* @retval ENABLE or DISABLE
*/
extern FunctionalState AUDIO_Get_Channel2_High_Bypass_EnabledStatus(AUD_TypeDef *audio);

/**
* @brief  The audio sets channel high bypass enabled status
* @param  audio: audio base address: @ref AUD
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Channel2_High_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus);

/**
* @brief  The audio gets channel0,s pdm select
* @param  audio: audio base address: @ref AUD
* @retval This can be one value of @ref AUDIO_Pdm,but just for AUDIO_PDM0 and AUDIO_PDM1
*/
extern uint8_t AUDIO_Get_Channel0_Select_Pdm(AUD_TypeDef *audio);

/**
* @brief  The audio sets channel0,s pdm select
* @param  audio: audio base address: @ref AUD
* @param  pdm: This parameter can be one value of @ref AUDIO_Pdm,but just for AUDIO_PDM0 and AUDIO_PDM1
* @retval None
*/
extern void AUDIO_Set_Channel0_Select_Pdm(AUD_TypeDef *audio, uint8_t pdm);

/**
* @brief  The audio gets channel1,s pdm select
* @param  audio: audio base address: @ref AUD
* @retval This can be one value of @ref AUDIO_Pdm,but just for AUDIO_PDM0 and AUDIO_PDM1
*/
extern uint8_t AUDIO_Get_Channel1_Select_Pdm(AUD_TypeDef *audio);

/**
* @brief  The audio sets channel1,s pdm select
* @param  audio: audio base address: @ref AUD
* @param  pdm: This parameter can be one value of @ref AUDIO_Pdm,but just for AUDIO_PDM0 and AUDIO_PDM1
* @retval None
*/
extern void AUDIO_Set_Channel1_Select_Pdm(AUD_TypeDef *audio, uint8_t pdm);

/**
* @brief  The audio reset vad
* @param  audio: audio base address: @ref AUD
* @retval None
*/
extern void AUDIO_Reset_Vad(AUD_TypeDef *audio);

/**
* @brief  The audio set channel0 12bit pcm enabled command
* @param  audio: audio base address: @ref AUD
* @retval None
*/
extern void AUDIO_Channel0_12bit_Pcm_Cmd(AUD_TypeDef *audio, FunctionalState newstatus);

/**
* @brief  The audio get channel0 pcm zeropadding
* @param  audio: audio base address: @ref AUD
* @retval This can be one value of @ref AUDIO_Channel0_Pcm_Zeropadding
*/
extern uint8_t AUDIO_Get_CHANNEL0_PCM_ZEROPADDING(AUD_TypeDef *audio);

/**
* @brief  The audio set channel0 pcm zeropadding
* @param  audio: audio base address: @ref AUD
* @param  value: This parameter can be one value of @ref AUDIO_Channel0_Pcm_Zeropadding
* @retval None
*/
extern void AUDIO_Set_CHANNEL0_PCM_ZEROPADDING(AUD_TypeDef *audio, uint8_t value);

/**
* @brief  The audio get pre-emphasis-bypass enabled status
* @param  audio: audio base address: @ref AUD
* @retval void
*/
extern FunctionalState AUDIO_Get_Pre_Emphasis_Bypass_EnabledStatus(AUD_TypeDef *audio);

/**
* @brief  The audio set pre-emphasis-bypass enabled command
* @param  audio: audio base address: @ref AUD
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Pre_Emphasis_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus);

/**
* @brief  The audio get analog-emphasis enabled status
* @param  audio: audio base address: @ref AUD
* @retval void
*/
extern FunctionalState AUDIO_Get_Analog_Emphasis_EnabledStatus(AUD_TypeDef *audio);

/**
* @brief  The audio set analog-emphasis enabled command
* @param  audio: audio base address: @ref AUD
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Analog_Emphasis_Cmd(AUD_TypeDef *audio, FunctionalState newstatus);

/**
* @brief  The audio clear fifo interrupt
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  interrupt: This parameter can be one or more value of @ref AUDIO_Ram_Fifo_Vad_Interrupt ,
*         but only for AUDIO_FIFO_UNDERFLOW_INTERRUPT or AUDIO_FIFO_OVERFLOW_INTERRUPT or AUDIO_FIFO_WRITE_INTERRUPT or AUDIO_FIFO_WRITE_INTERRUPT
* @retval None
*/
extern void AUDIO_Clear_Fifo_Interrupt(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt);

/**
* @brief  The audio read fifo data
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval Fifo data
*/
extern uint32_t AUDIO_Read_Fifo_Data(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio gets ram depth
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval the depth value
*/
extern uint32_t AUDIO_Get_RAM_Depth(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets ram depth
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  depth: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_RAM_Depth(AUD_TypeDef *audio, uint8_t channel, uint32_t depth);

/**
* @brief  The audio gets ram frame-move
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval the frame-move value
*/
extern uint32_t AUDIO_Get_RAM_Frame_Move(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets ram frame-move
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  frame_move: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_RAM_Frame_Move(AUD_TypeDef *audio, uint8_t channel, uint32_t frame_move);

/**
* @brief  The audio gets ram length
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval the length value
*/
extern uint32_t AUDIO_Get_RAM_Length(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets ram length
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  length: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_RAM_Length(AUD_TypeDef *audio, uint8_t channel, uint32_t length);

/**
* @brief  The audio clear ram interrupt
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  interrupt: This parameter can be one value of @ref AUDIO_Ram_Fifo_Vad_Interrupt ,but only for AUDIO_RAM_FRAME_VLD_INTERRUPT or AUDIO_RAM_INTERRUPT or AUDIO_RAM_READ_INTERRUPT
* @retval None
*/
extern void AUDIO_Clear_Ram_Interrupt(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt);

/**
* @brief  The audio read ram data
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval Ram data
*/
extern uint32_t AUDIO_Read_Ram_Data(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio gets bq_b0_configuration
* @param  audio: audio base address: @ref AUD
* @retval the bq_b0_configuration value
*/
extern uint32_t AUDIO_Get_Bq_B0_Configuration(AUD_TypeDef *audio);

/**
* @brief  The audio sets bq_b0_configuration
* @param  audio: audio base address: @ref AUD
* @param  value: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Bq_B0_Configuration(AUD_TypeDef *audio, int16_t value);

/**
* @brief  The audio gets bq_b1_configuration
* @param  audio: audio base address: @ref AUD
* @retval the bq_b1_configuration value
*/
extern uint32_t AUDIO_Get_Bq_B1_Configuration(AUD_TypeDef *audio);

/**
* @brief  The audio sets bq_b1_configuration
* @param  audio: audio base address: @ref AUD
* @param  value: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Bq_B1_Configuration(AUD_TypeDef *audio, int16_t value);

/**
* @brief  The audio gets bq_b2_configuration
* @param  audio: audio base address: @ref AUD
* @retval the bq_b2_configuration value
*/
extern uint32_t AUDIO_Get_Bq_B2_Configuration(AUD_TypeDef *audio);

/**
* @brief  The audio sets bq_b2_configuration
* @param  audio: audio base address: @ref AUD
* @param  value: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Bq_B2_Configuration(AUD_TypeDef *audio, uint16_t value);

/**
* @brief  The audio gets bq_a0_configuration
* @param  audio: audio base address: @ref AUD
* @retval the bq_a0_configuration value
*/
extern uint32_t AUDIO_Get_Bq_A0_Configuration(AUD_TypeDef *audio);

/**
* @brief  The audio sets bq_a0_configuration
* @param  audio: audio base address: @ref AUD
* @param  value: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Bq_A0_Configuration(AUD_TypeDef *audio, uint16_t value);

/**
* @brief  The audio gets bq_a1_configuration
* @param  audio: audio base address: @ref AUD
* @retval the bq_a1_configuration value
*/
extern uint32_t AUDIO_Get_Bq_A1_Configuration(AUD_TypeDef *audio);

/**
* @brief  The audio sets bq_a1_configuration
* @param  audio: audio base address: @ref AUD
* @param  value: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Bq_A1_Configuration(AUD_TypeDef *audio, int16_t value);

/**
* @brief  The audio gets channel gain value
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval the channel gain value
*/
extern uint32_t AUDIO_Get_Channel_Gain_Configuration(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets channel gain value
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  value: This parameter can be value between 0x0 and 0xff
* @retval None
*/
extern void AUDIO_Set_Channel_Gain_Configuration(AUD_TypeDef *audio, uint8_t channel, uint8_t value);

/**
* @brief  The audio get pcm received-count
* @param  audio: audio base address: @ref AUD
* @retval the received-count value
*/
extern uint32_t AUDIO_Get_Pcm_Data_Number(AUD_TypeDef *audio);

/**
* @brief  The audio gets short term power threshold
* @param  audio: audio base address: @ref AUD
* @retval the short term power threshold 
*/
extern uint32_t AUDIO_Get_Short_Term_Power_Threshold(AUD_TypeDef *audio);

/**
* @brief  The audio sets short term power threshold
* @param  audio: audio base address: @ref AUD
* @param  threshold: This parameter can be value between 0x0 and 0xffffffff
* @retval None
*/
extern void AUDIO_Set_Short_Term_Power_Threshold(AUD_TypeDef *audio, uint32_t threshold);

/**
* @brief  The audio gets long term power threshold
* @param  audio: audio base address: @ref AUD
* @retval the long term power threshold 
*/
extern uint32_t AUDIO_Get_Long_Term_Power_Threshold(AUD_TypeDef *audio);

/**
* @brief  The audio sets long term power threshold
* @param  audio: audio base address: @ref AUD
* @param  threshold: This parameter can be value between 0x0 and 0xffffffff
* @retval None
*/
extern void AUDIO_Set_Long_Term_Power_Threshold(AUD_TypeDef *audio, uint32_t threshold);

/**
* @brief  The audio gets deviation threshold
* @param  audio: audio base address: @ref AUD
* @retval the deviation threshold 
*/
extern uint32_t AUDIO_Get_Deviation_Threshold(AUD_TypeDef *audio);

/**
* @brief  The audio sets deviation threshold
* @param  audio: audio base address: @ref AUD
* @param  threshold: This parameter can be value between 0x0 and 0xffffffff
* @retval None
*/
extern void AUDIO_Set_Deviation_Threshold(AUD_TypeDef *audio, uint32_t threshold);

/**
* @brief  The audio gets short term attack window length threshold
* @param  audio: audio base address: @ref AUD
* @retval the short term attack window length threshold 
*/
extern uint32_t AUDIO_Get_Short_Term_Attack_Window_Length_Threshold(AUD_TypeDef *audio);

/**
* @brief  The audio sets short term attack window length threshold
* @param  audio: audio base address: @ref AUD
* @param  threshold: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Short_Term_Attack_Window_Length_Threshold(AUD_TypeDef *audio, uint16_t threshold);

/**
* @brief  The audio gets short term attack window length shift
* @param  audio: audio base address: @ref AUD
* @retval the short term attack window length shift
*/
extern uint32_t AUDIO_Get_Short_Term_Attack_Window_Length_Shift(AUD_TypeDef *audio);

/**
* @brief  The audio sets short term attack window length shift
* @param  audio: audio base address: @ref AUD
* @param  threshold: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Short_Term_Attack_Window_Length_Shift(AUD_TypeDef *audio, uint16_t shift);

/**
* @brief  The audio gets long term attack window length threshold
* @param  audio: audio base address: @ref AUD
* @retval the long term attack window length threshold
*/
extern uint32_t AUDIO_Get_Long_Term_Attack_Window_Length_Threshold(AUD_TypeDef *audio);

/**
* @brief  The audio sets long term attack window length threshold
* @param  audio: audio base address: @ref AUD
* @param  threshold: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Long_Term_Attack_Window_Length_Threshold(AUD_TypeDef *audio, uint16_t threshold);

/**
* @brief  The audio gets long term attack window length shift
* @param  audio: audio base address: @ref AUD
* @retval the long term attack window length shift
*/
extern uint32_t AUDIO_Get_Long_Term_Attack_Window_Length_Shift(AUD_TypeDef *audio);

/**
* @brief  The audio sets long term attack window length shift
* @param  audio: audio base address: @ref AUD
* @param  threshold: This parameter can be value between 0x0 and 0xffff
* @retval None
*/
extern void AUDIO_Set_Long_Term_Attack_Window_Length_Shift(AUD_TypeDef *audio, uint16_t shift);

/**
* @brief  The audio gets ram interrupt status
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval This can be only value of @ref AUDIO_Ram_Fifo_Vad_Interrupt,but only for AUDIO_RAM_FRAME_VLD_INTERRUPT
*/
extern uint32_t AUDIO_Get_Ram_Interrupt_Status(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio gets fifo interrupt status
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval This can be one or more value of @ref AUDIO_Ram_Fifo_Vad_Interrupt, but only for AUDIO_FIFO_FULL_INTERRUPT or AUDIO_FIFO_HALF_FULL_INTERRUPT or AUDIO_FIFO_EMPTY_INTERRUPT
            AUDIO_FIFO_OVERFLOW_INTERRUPT or AUDIO_FIFO_UNDERFLOW_INTERRUPT
*/
extern uint32_t AUDIO_Get_FIFO_Interrupt_Status(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio gets vad interrupt status
* @param  audio: audio base address: @ref AUD
* @retval This can be only value of @ref AUDIO_Ram_Fifo_Vad_Interrupt, but only for AUDIO_VAD_ACT_INTERRUPT
*/
extern uint32_t AUDIO_Get_Vad_Interrupt_Status(AUD_TypeDef *audio);

/**
* @brief  The audio sets ram interrupt mask
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  interrupt: This can be only value of @ref AUDIO_Ram_Fifo_Vad_Interrupt, but only for AUDIO_RAM_FRAME_VLD_INTERRUPT
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Ram_Interrupt_Mask(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt, FunctionalState newstatus);

/**
* @brief  The audio sets fifo interrupt mask
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  interrupt: This can be one or more value of @ref AUDIO_Ram_Fifo_Vad_Interrupt, but only for AUDIO_FIFO_FULL_INTERRUPT or AUDIO_FIFO_HALF_FULL_INTERRUPT or AUDIO_FIFO_EMPTY_INTERRUPT
                     AUDIO_FIFO_OVERFLOW_INTERRUPT or AUDIO_FIFO_UNDERFLOW_INTERRUPT
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_FIFO_Interrupt_Mask(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt, FunctionalState newstatus);

/**
* @brief  The audio sets vad interrupt mask
* @param  audio: audio base address: @ref AUD
* @param  interrupt: This can be only value of @ref AUDIO_Ram_Fifo_Vad_Interrupt, but only for AUDIO_VAD_ACT_INTERRUPT
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Vad_Interrupt_Mask(AUD_TypeDef *audio, uint32_t interrupt, FunctionalState newstatus);

/**
* @brief  The audio gets digitalcompa or digitalcompb or compwakeup interrupt status
* @param  audio: audio base address: @ref AUD
* @retval This can be one or more value of @ref AUDIO_Digital_Comp_Channel_Interrupt, but only for AUDIO_DIGITAL_CMPA_INTERRUPT or AUDIO_DIGITAL_CMPB_INTERRUPT or AUDIO_COMP_WAKEUP_INTERRUPT
*/
extern uint32_t AUDIO_Get_DigitalCompa_or_DigitalCompa_or_Compwakeup_Interrupt_Status(AUD_TypeDef *audio);

/**
* @brief  The audio sets digitalcompa or digitalcompb or compwakeup interrupt mask
* @param  audio: audio base address: @ref AUD
* @param  interrupt:This can be one or more value of @ref AUDIO_Digital_Comp_Channel_Interrupt, but only for AUDIO_DIGITAL_CMPA_INTERRUPT or AUDIO_DIGITAL_CMPB_INTERRUPT or AUDIO_COMP_WAKEUP_INTERRUPT
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_DigitalCompa_or_DigitalCompa_or_Compwakeup_Interrupt_Status(AUD_TypeDef *audio, uint32_t interrupt, FunctionalState newstatus);

/**
* @brief  The audio gets channel interrupt status
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @retval This can be one or more value of @ref AUDIO_Digital_Comp_Channel_Interrupt, but only for AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT or AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT or AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT
*/
extern uint32_t AUDIO_Get_Channel_Interrupt_Status(AUD_TypeDef *audio, uint8_t channel);

/**
* @brief  The audio sets channel interrupt mask
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  interrupt: This can be one or more value of @ref AUDIO_Digital_Comp_Channel_Interrupt, but only for AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT or AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT or AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Channel_Interrupt_Status(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt, FunctionalState newstatus);

/**
* @brief  The audio sets channel clock switch
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  clock_switch: This can be one or more value of @AUDIO_Clock_SWitch_Configuration
* @retval None
*/
extern void AUDIO_Set_Clock_Switch_Configuration(AUD_TypeDef *audio, uint8_t channel, uint8_t clock_switch);

/**
* @brief  The audio sets hardware dma request enabled command
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AUDIO_Set_Hardware_Request_Dma_Cmd(AUD_TypeDef *audio, uint8_t channel, FunctionalState newstatus);

/**
* @brief  The audio sets dma request level value
* @param  audio: audio base address: @ref AUD
* @param  channel: This parameter can be one value of @ref AUDIO_Channel
* @param  level: dma level from 1 to 8
* @retval None
*/
extern void AUDIO_Set_Dma_Level(AUD_TypeDef *audio, uint8_t channel, uint8_t level);

/**
* @brief  VAD_Config
* @param  None
* @retval None
*/
void VAD_Config(void);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
