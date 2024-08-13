/**
  ******************************************************************************  
  * @file    afc.h
  * @brief   Header for afc.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************  
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __AFC_H__
#define __AFC_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Includes */
#include "WTM2101.h"
#include "stddef.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup AFC
  * @{
  */

/* Exported constants --------------------------------------------------------*/
 
/** @defgroup AFC_Exported_Constants
  * @{
  */

/** @defgroup AFC_Interrupt_TypeDef
* @{
*/
#define AFC_TRIM_ACK_INTERRUPT              (0X800)
#define AFC_FRE_DET_DONE_INTERRUPT          (0X400)
#define AFC_FINE_STEP0_OP_INTERRUPT         (0X200)
#define AFC_FINE_STEP1_OP_INTERRUPT         (0X100)
#define AFC_COARSE_OVER_INTERRUPT           (0X80)
#define AFC_COARSE_DEC_INTERRUPT            (0X40)
#define AFC_COARSE_INC_INTERRUPT            (0X20)
#define AFC_CALB_FINISH_INTERRUPT           (0X10)
#define AFC_FINE_ERROR_INTERRUPT            (0X08)
#define AFC_FINE_STEP0_DONE_INTERRUPT       (0X04)
#define AFC_FINE_STEP1_DONE_INTERRUPT       (0X02)
#define AFC_FINE_STEP2_DONE_INTERRUPT       (0X01)
#define AFC_ALL_INTERRUPT                   (0XFFF)
#define IS_AFC_INTERRUPT_MODE(INT)         (((INT) == AFC_FINE_STEP2_DONE_INTERRUPT) || \
                                            ((INT) == AFC_FINE_STEP1_DONE_INTERRUPT) || \
                                            ((INT) == AFC_FINE_STEP0_DONE_INTERRUPT) || \
                                            ((INT) == AFC_FINE_ERROR_INTERRUPT)      || \
                                            ((INT) == AFC_CALB_FINISH_INTERRUPT)     || \
                                            ((INT) == AFC_COARSE_INC_INTERRUPT)      || \
                                            ((INT) == AFC_COARSE_DEC_INTERRUPT)      || \
                                            ((INT) == AFC_COARSE_OVER_INTERRUPT)     || \
                                            ((INT) == AFC_FINE_STEP1_OP_INTERRUPT)   || \
                                            ((INT) == AFC_FINE_STEP0_OP_INTERRUPT)   || \
                                            ((INT) == AFC_FRE_DET_DONE_INTERRUPT)    || \
                                            ((INT == AFC_TRIM_ACK_INTERRUPT))
/**                                         
* @}
*/

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup AFC_Functions_Prototypes AFC Functions Prototypes
* @{
*/

/**
* @brief  The AFC get the test time
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the test value
*/
extern uint16_t AFC_Get_Test_Time(AFC_TypeDef *afc);

/**
* @brief  The AFC set the test time
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @param  value: the test value
* @retval None
*/
extern void AFC_Set_Test_Time(AFC_TypeDef *afc, uint16_t value);

/**
* @brief  The AFC get frequency target
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the frequency target
*/
extern uint16_t AFC_Get_Frequency_Target(AFC_TypeDef *afc);

/**
* @brief  The AFC set the frequency target
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @param  value: frequency target
* @retval None
*/
extern void AFC_Set_Frequency_Target(AFC_TypeDef *afc, uint16_t value);

/**
* @brief  The AFC set the enabled command
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @param  newstatus: ENABLE or DISABLE
* @retval None
*/
extern void AFC_Set_Enable_Cmd(AFC_TypeDef *afc, FunctionalState newstatus);

/**
* @brief  The AFC set the divison result
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @param  value: the divison result
* @retval None
*/
extern void AFC_Set_Divison_Result(AFC_TypeDef *afc, uint16_t value);

/**
* @brief  The AFC set the remain value
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @param  value: the remain value
* @retval None
*/
extern void AFC_Set_Remain_Value(AFC_TypeDef *afc, uint16_t value);

/**
* @brief  The AFC get the frequency calibration cycle count
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the frequency calibration cycle count
*/
extern uint32_t AFC_Get_Frequency_Calibration_Cycle_Count(AFC_TypeDef *afc);

/**
* @brief  The AFC get the core trim fine
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the core trim fine
*/
extern uint16_t AFC_Get_Core_Trim_Fine(AFC_TypeDef *afc);

/**
* @brief  The AFC get the core trim coarse
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the core trim coarse
*/
extern uint16_t AFC_Get_Core_Trim_Coarse(AFC_TypeDef *afc);

/**
* @brief  The AFC set the trim enabled singal
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval Trim enabled singal
*/
extern uint16_t AFC_Get_Trim_Enabled_Singal(AFC_TypeDef *afc);

/**
* @brief  The AFC get the frequency count diffreence
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the frequency count diffreence
*/
extern uint16_t AFC_Get_Frequency_Count_Difference(AFC_TypeDef *afc);

/**
* @brief  The AFC get the last frequency count diffreence
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the last frequency count diffreence
*/
extern uint16_t AFC_Get_Last_Frequency_Count_Difference(AFC_TypeDef *afc);

/**
* @brief  The AFC get the fine trim signal compare status
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the fine trim signal compare status
*/
extern uint16_t AFC_Get_Fine_Trim_Signal_Compare_Status(AFC_TypeDef *afc);

/**
* @brief  The AFC set pulse command
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval None
*/
extern void AFC_Set_Pulse_Cmd(AFC_TypeDef *afc);

/**
* @brief  The AFC set interrupt mask
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @param  interrupt: the value can be one or more of AFC_Interrupt_TypeDef
* @retval None
*/
extern void AFC_Set_Interrupt_Mask(AFC_TypeDef *afc, uint32_t interrupt);

/**
* @brief  The AFC set interrupt clear
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @param  interrupt: the value can be one or more of AFC_Interrupt_TypeDef
* @retval None
*/
extern void AFC_Set_Interrupt_Clear(AFC_TypeDef *afc, uint32_t interrupt);

/**
* @brief  The AFC get interrupt status
* @param  afc: the afc address.@ref AFC320k,AFC24M
* @retval the value can be one or more of AFC_Interrupt_TypeDef
*/
extern uint32_t AFC_Get_Interrupt_Status(AFC_TypeDef *afc);

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
