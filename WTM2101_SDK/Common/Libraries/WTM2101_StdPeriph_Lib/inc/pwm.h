/**
  ******************************************************************************
  * @file    pwm.h
  * @brief   Header for pwm.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
  
/** Define to Prevent Recursive Inclusion */
#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "WTM2101_PWM_register.h"
/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWM
  * @{
  */
  
/** @defgroup PWM_Exported_Types PWM Exported Types 
  * @{
  */
   
/**
  * @brief PWM Init Structure Definition
  */   
typedef struct 
{
  uint16_t Period;                /*!< This member configures the PWM max count value.
                                       This parameter can be a value <=0xFFFF*/

  uint32_t Mode;                  /*!< Specifies PWM work mode.
                                       This parameter can be a value of @ref PWM_Mode*/

  uint32_t CountMode;             /*!< Specifies PWM Count mode.
                                       This parameter can be a value of @ref PWM_Count_Mode*/

}PWM_InitTypeDef;   

/**
  * @brief PWM Channel Init Structure Definition
  */ 
typedef struct 
{
  uint32_t CH_Mode;                /*!< Specifies PWM channel work mode.
                                        This parameter can be a value of @ref PWM_Channel_Mode*/

  uint32_t OUT_SIG;                /*!< Specifies PWM channel output Signal Direction.
                                        This parameter can be a value of @ref PWM_Init_Output_Value*/

  uint32_t IN_SIG;                 /*!< Specifies PWM channel input Signal Direction.
                                        This parameter can be a value of @ref PWM_Input_Signal_Direction*/

  uint32_t Init_Out_Val;           /*!< Specifies PWM channel Init Output Value.
                                        This parameter can be a value of @ref PWM_Init_Output_Value*/

  FunctionalState CH_En;           /*!< Enables or disables the channel work.
                                        This parameter can be a value of @ref FunctionalState */

}PWM_CH_InitTypeDef;


/**
  * @brief PWM Channel Parameter Init Structure Definition
  */ 
typedef struct 
{
  uint16_t Dead_Zone;              /*!< This member configures the PWM dead zone.
                                        This parameter can be a value <=0xFFFF*/

  uint16_t Cmp_Val;                /*!< This member configures the PWM compare value.
                                        This parameter can be a value <=0xFFFF*/

}PWM_CH_ParamTypeDef;


/**
  * @brief PWM Channel Init Structure Definition
  */ 
typedef struct 
{
  uint16_t Cycle_Num;              /*!< This member is input signal cycle value.
                                        This parameter can be a value <=0xFFFF*/

  uint16_t HL_Cycle_Num;           /*!< This member is input signal high level cycle value.
                                        This parameter can be a value <=0xFFFF*/

}PWM_CH_CapParamTypeDef;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/   

/** @defgroup PWM_Exported_Constants PWM Exported Constants
  * @{
  */

/** @defgroup PWM_Channel PWM Channel
  * @brief PWM Channel select 
  * @{
  */
#define PWM_CH0                         0U  /*!< PWM channel0        */
#define PWM_CH1                         1U  /*!< PWM channel1        */
#define PWM_CH2                         2U  /*!< PWM channel2        */
#define PWM_CH3                         3U  /*!< PWM channel3        */
/**
  * @}
  */

/** @defgroup PWM_Mode PWM Mode
  * @brief PWM mode select 
  * @{
  */
#define PWM_MODE_CAP                    (0U<<PWM_PWM_CTL_PWM_CAP_SW_Pos)  /*!< Capture mode        */
#define PWM_MODE_PWM                    (1U<<PWM_PWM_CTL_PWM_CAP_SW_Pos)  /*!< PWM mode            */
/**
  * @}
  */


/** @defgroup PWM_Count_Mode PWM Count Mode
  * @brief PWM count mode select 
  * @{
  */
#define PWM_COUNT_UP                    (0U<<PWM_PWM_CTL_PWM_CNT_MODE_Pos)  /*!< Count up mode       */
#define PWM_COUNT_DOWN                  (1U<<PWM_PWM_CTL_PWM_CNT_MODE_Pos)  /*!< Count down mode     */
#define PWM_COUNT_MID                   (2U<<PWM_PWM_CTL_PWM_CNT_MODE_Pos)  /*!< Count middle mode   */
/**
  * @}
  */

/** @defgroup PWM_Channel_Mode PWM Channel Mode
  * @brief PWM Channel mode select 
  * @{
  */
#define PWM_CH_MODE_ONE_SHOT            (1U<<PWM_PWM_CH_CTL_PWM_0_ONE_SHOT_EN_Pos)  /*!< one shot mode       */
#define PWM_CH_MODE_CONT                (0U<<PWM_PWM_CH_CTL_PWM_0_ONE_SHOT_EN_Pos)  /*!< continuous mode     */
/**
  * @}
  */

/** @defgroup PWM_Input_Signal_Direction PWM Input Signal Direction
  * @brief PWM input signal direction select 
  * @{
  */                                    
#define PWM_IN_SIG_FWD                  (1U<<PWM_PWM_CH_CTL_PWM_I_0_SW_Pos)  /*!< Input forward direction  */
#define PWM_IN_SIG_INV                  (0U<<PWM_PWM_CH_CTL_PWM_I_0_SW_Pos)  /*!< Input inverse direction  */
/**
  * @}
  */

/** @defgroup PWM_Output_Signal_Direction PWM Output Signal Direction
  * @brief PWM output signal direction select 
  * @{
  */
#define PWM_OUT_SIG_FWD                 (1U<<PWM_PWM_CH_CTL_PWM_O_0_SW_Pos)  /*!< Output forward direction  */
#define PWM_OUT_SIG_INV                 (0U<<PWM_PWM_CH_CTL_PWM_O_0_SW_Pos)  /*!< Output inverse direction  */
/**
  * @}
  */

/** @defgroup PWM_Init_Output_Value PWM Init Output Value
  * @brief PWM Init Output Value select 
  * @{
  */
#define PWM_INIT_OUT_HI                 (1U<<PWM_PWM_CH_CTL_PWM_O_0_INIT_Pos)  /*!< Initial output value HIG  */
#define PWM_INIT_OUT_LO                 (0U<<PWM_PWM_CH_CTL_PWM_O_0_INIT_Pos)  /*!< Initial output value LOW  */
/**
  * @}
  */


/** @defgroup PWM_Interrupt_Source PWM Interrupt Source
  * @brief PWM Interrupt Source select 
  * @{
  */
#define PWM_IT_CNT_OVERFLOW              PWM_INT_SR_PENDING_PWM_OVERFLOW_INT_Msk   /*!< Overflow interrupt                                        */
#define PWM_IT_CNT_UNDERFLOW             PWM_INT_SR_PENDING_PWM_UNDERFLOW_INT_Msk  /*!< Underflow interrupt                                       */
#define PWM_IT_CH3_BIKE_IN               PWM_INT_SR_PENDING_PWM_3_BKIN_Msk         /*!< Channel3 input signal bike in interrupt                   */
#define PWM_IT_CH3_CYCLE_NUM_CAP         PWM_INT_SR_PENDING_PWM_I_3_CYCLE_INT_Msk  /*!< Channel3 input signal cycle capture interrupt             */
#define PWM_IT_CH3_HI_CYCLE_NUM_CAP      PWM_INT_SR_PENDING_PWM_I_3_H_INT_Msk      /*!< Channel3 input signal high level cycle capture interrupt  */
#define PWM_IT_CH2_BIKE_IN               PWM_INT_SR_PENDING_PWM_2_BKIN_Msk         /*!< Channel2 input signal bike in interrupt                   */
#define PWM_IT_CH2_CYCLE_NUM_CAP         PWM_INT_SR_PENDING_PWM_I_2_CYCLE_INT_Msk  /*!< Channel2 input signal cycle capture interrupt             */
#define PWM_IT_CH2_HI_CYCLE_NUM_CAP      PWM_INT_SR_PENDING_PWM_I_2_H_INT_Msk      /*!< Channel2 input signal high level cycle capture interrupt  */
#define PWM_IT_CH1_BIKE_IN               PWM_INT_SR_PENDING_PWM_1_BKIN_Msk         /*!< Channel1 input signal bike in interrupt                   */
#define PWM_IT_CH1_CYCLE_NUM_CAP         PWM_INT_SR_PENDING_PWM_I_1_CYCLE_INT_Msk  /*!< Channel1 input signal cycle capture interrupt             */
#define PWM_IT_CH1_HI_CYCLE_NUM_CAP      PWM_INT_SR_PENDING_PWM_I_1_H_INT_Msk      /*!< Channel1 input signal high level cycle capture interrupt  */
#define PWM_IT_CH0_BIKE_IN               PWM_INT_SR_PENDING_PWM_0_BKIN_Msk         /*!< Channel0 input signal bike in interrupt                   */
#define PWM_IT_CH0_CYCLE_NUM_CAP         PWM_INT_SR_PENDING_PWM_I_0_CYCLE_INT_Msk  /*!< Channel0 input signal cycle capture interrupt             */
#define PWM_IT_CH0_HI_CYCLE_NUM_CAP      PWM_INT_SR_PENDING_PWM_I_0_H_INT_Msk      /*!< Channel0 input signal high level cycle capture interrupt  */
#define PWM_IT_ALL                       0x00003FFFU                               /*!< All interrupt                                             */
/**
  * @}
  */


/**
  * @}
  */

/** @defgroup PWM_Functions_Prototypes PWM Functions Prototypes
  * @{
  */

/* Initialization and Configuration functions *********************************/

/**
* @brief  Initializes the PWMx peripheral basic functions according to
*         the specified parameters in the PWM_InitStruct.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @note
* @param  PWM_InitStruct: pointer to a PWM_InitTypeDef structure that contains
*         the basic configuration information for the specified PWM peripheral.
* @retval None
*/
extern void PWM_Init(PWM_TypeDef* PWMx, PWM_InitTypeDef* PWM_InitStruct);

/**
* @brief  Initializes the PWMx peripheral channel basic functions according to
*         the specified parameters in the PWM_CH_InitTypeDef.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @note
* @param  PWM_CHx: select the PWM channel,This parameter can be a value of 
*         @ref PWM_Channel.
* @param  PWM_CHInitStruct: pointer to a PWM_CH_InitTypeDef structure that contains
*         the basic configuration information for the specified PWM channel.
* @retval None
*/
extern void PWM_CH_Init(PWM_TypeDef* PWMx, uint32_t PWM_CHx, PWM_CH_InitTypeDef* PWM_CHInitStruct);

/* operation functions *****************************************************/
/**
* @brief  Set the PWMx peripheral channel dead zone and compare value according to
*         the specified parameters in the PWM_CH_ParamTypeDef.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @note
* @param  PWM_CHx: select the PWM channel,This parameter can be a value of 
*         @ref PWM_Channel.
* @param  CH_Param: pointer to a PWM_CH_ParamTypeDef structure that contains
*         the dead zone and compare value information for the specified PWM channel.
* @retval None
*/
extern void PWM_CH_SetParam(PWM_TypeDef* PWMx, uint32_t PWM_CHx, PWM_CH_ParamTypeDef* CH_Param);

/**
* @brief  Get the PWMx peripheral channel input signal cycle and high level 
*         cycle value.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @note
* @param  PWM_CHx: select the PWM channel,This parameter can be a value of 
*         @ref PWM_Channel.
* @param  CH_CapParam: use PWM_CH_CapParamTypeDef* type pointer to get the input 
*         signal cycle and high level cycle value.
* @retval None
*/
extern void PWM_CH_GetCapParam(PWM_TypeDef* PWMx, uint32_t PWM_CHx, PWM_CH_CapParamTypeDef* CH_CapParam);

/* Interrupts and flags management functions **********************************/
/**
* @brief  Enable or disable the selected PWMx interrupt mask function.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @note
* @param  IT_Msk: Interrupt source selected,This parameter can be a value of 
*         @ref PWM_Interrupt_Source.
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void PWM_IT_MskCtl(PWM_TypeDef* PWMx, uint32_t IT_Msk, FunctionalState NewState);

/**
* @brief  Get the selected PWMx interrupt status.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @param  PWM_IT: Interrupt source selected,This parameter can be a value of 
*         @ref PWM_Interrupt_Source.
* @retval selected interrupt status
*/
extern FlagStatus PWM_IT_GetStatBit(PWM_TypeDef* PWMx, uint32_t PWM_IT);

/**
* @brief  Get the PWMx interrupt status.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @retval Interrupt status
*/
extern uint32_t PWM_IT_GetStat(PWM_TypeDef* PWMx);

/**
* @brief  Clear interrupt Status.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @param  PWM_IT: Interrupt source selected,This parameter can be a value of 
*         @ref PWM_Interrupt_Source.
* @retval None.
*/
extern void PWM_IT_ClrStat(PWM_TypeDef* PWMx, uint32_t PWM_IT);

/**
* @brief  Bike in release.
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @param  PWM_CHx: select the PWM channel,This parameter can be a value of 
*         @ref PWM_Channel.
* @retval None.
*/
extern void PWM_BK_Rel(PWM_TypeDef* PWMx, uint32_t PWM_CHx);

/**
* @brief  Enable initial the Channel output value .
* @param  PWMx: to select the PWM peripheral, where x can  be 0 or 1.
* @param  PWM_CHx: select the PWM channel,This parameter can be a value of 
*         @ref PWM_Channel.
* @retval None.
*/
extern void PWM_Ch_Init_Out_Val_Enable(PWM_TypeDef* PWMx, uint32_t PWM_CHx);
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup PWM_Private_Macros PWM Private Macros
  * @{
  */
#define IS_PWM_CH(CH)              (((CH) == PWM_CH0)               ||\
                                    ((CH) == PWM_CH1)               ||\
                                    ((CH) == PWM_CH2)               ||\
                                    ((CH) == PWM_CH3))
#define IS_PWM_MODE(MODE)          (((MODE) == PWM_MODE_CAP)        ||\
                                    ((MODE) == PWM_MODE_PWM))   
#define IS_PWM_CNTMODE(MODE)       (((MODE) == PWM_COUNT_UP)        ||\
                                    ((MODE) == PWM_COUNT_DOWN)      ||\
                                    ((MODE) == PWM_COUNT_MID))
#define IS_PWM_CHMODE(MODE)        (((MODE) == PWM_CH_MODE_ONE_SHOT)||\
                                    ((MODE) == PWM_CH_MODE_CONT))
#define IS_PWM_INSIG(DIR)          (((DIR) == PWM_IN_SIG_FWD)       ||\
                                    ((DIR) == PWM_IN_SIG_INV))
#define IS_PWM_OUTSIG(DIR)         (((DIR) == PWM_OUT_SIG_FWD)      ||\
                                    ((DIR) == PWM_OUT_SIG_INV))
#define IS_PWM_INITVAL(VAL)        (((VAL) == PWM_INIT_OUT_HI)      ||\
                                    ((VAL) == PWM_INIT_OUT_LO))
#define IS_PWM_VALUE(VAL)          ((VAL) <= 0xFFFFU) 
#define IS_PWM_INT(INT)            (((INT) == PWM_IT_CNT_OVERFLOW)         ||\
                                    ((INT) == PWM_IT_CNT_UNDERFLOW)        ||\
                                    ((INT) == PWM_IT_CH3_BIKE_IN)          ||\
                                    ((INT) == PWM_IT_CH3_CYCLE_NUM_CAP)    ||\
                                    ((INT) == PWM_IT_CH3_HI_CYCLE_NUM_CAP) ||\
                                    ((INT) == PWM_IT_CH2_BIKE_IN)          ||\
                                    ((INT) == PWM_IT_CH2_CYCLE_NUM_CAP)    ||\
                                    ((INT) == PWM_IT_CH2_HI_CYCLE_NUM_CAP) ||\
                                    ((INT) == PWM_IT_CH1_BIKE_IN)          ||\
                                    ((INT) == PWM_IT_CH1_CYCLE_NUM_CAP)    ||\
                                    ((INT) == PWM_IT_CH1_HI_CYCLE_NUM_CAP) ||\
                                    ((INT) == PWM_IT_CH0_BIKE_IN)          ||\
                                    ((INT) == PWM_IT_CH0_CYCLE_NUM_CAP)    ||\
                                    ((INT) == PWM_IT_CH0_HI_CYCLE_NUM_CAP) ||\
                                    ((INT) == PWM_IT_ALL))
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
