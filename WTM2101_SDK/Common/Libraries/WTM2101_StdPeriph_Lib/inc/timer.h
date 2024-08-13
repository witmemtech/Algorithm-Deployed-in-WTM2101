/**
  ******************************************************************************
  * @file    timer.h
  * @brief   Header for timer.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif 

/* Includes */
#include "WTM2101.h"
#include "rcc.h"
#include "stddef.h"
#include "WTM2101_TIMER_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIMER
  * @{
  */

/* Exported constants --------------------------------------------------------*/
 
/** @defgroup TIMER_Exported_Constants
  * @{
  */

/** @defgroup TimerMode_TypeDef
* @{
*/
#define TIMER_FREE_RUNING_MODE  (0x00)
#define TIMER_USER_DEFINED_MODE (0x01)
#define IS_TIMER_MODE(MODE)     (((MODE) == TIMER_USER_DEFINED_MODE) || \
                                ((MODE) == TIMER_FREE_RUNING_MODE))
/**
* @}
*/

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup TIMER_Exported_Types TIMER Exported Types 
  * @{
  */

/**
 * @brief  Timer Init Structure Definition
 */
typedef struct
{
    uint32_t mode;                  /*!< Specifies the counter mode.
                                        This parameter can be a value of @ref TimerMode_TypeDef 
                                        If TIMER_FREE_RUNING_MODE parameter is used,TIMER interrupt happens when the maximum tick is reached in TimerNCurrentValue register.
                                        That has nothing to do with period and pwm_period parameter.The TimerNCurrentValue register of TIMER is total 24bits */

    uint32_t period;                /*!< Specifies the repeated period tick of TIMER.
                                        The developer can use the TIMER_Transfer_second_to_tick() and TIMER_Transfer_millisecond_to_tick() and TIMER_Transfer_microsecond_to_tick() to transfer
                                        the time to tick. */

    uint32_t pwm_period;            /*!< Specifies the second repeated period of TIMER.
                                        The developer can use the TIMER_Transfer_second_to_tick() and TIMER_Transfer_millisecond_to_tick() and TIMER_Transfer_microsecond_to_tick() to transfer
                                        the time to tick. */

}TIMER_InitTypeDef;
/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/

/** @defgroup TIMER_Functions_Prototypes TIMER Functions Prototypes
* @{
*/

/**
* @brief  The TIMER transfers second to tick.
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  second: second of time
* @retval tick of TIMER
*/
extern uint32_t TIMER_Transfer_second_to_tick(TMR_TypeDef* TIMERx, float second);

/**
* @brief  The TIMER transfers millisecond to tick.
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  millisecond: millisecond of time
* @retval tick of TIMER
*/
extern uint32_t TIMER_Transfer_millisecond_to_tick(TMR_TypeDef* TIMERx, float millisecond);

/**
* @brief  The TIMER transfers microsecond to tick.
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  microsecond: microsecond of time
* @retval tick of TIMER
*/
extern uint32_t TIMER_Transfer_microsecond_to_tick(TMR_TypeDef* TIMERx, float microsecond);

/**
* @brief  The TIMER initializes peripheral according to
*         the specified parameters in the TIMER_InitTypeDef structure.
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  TIM_InitStruct: pointer to a TIMER_InitTypeDef
*         structure that contains the configuration information for
*         the specified TIMER peripheral.
* @retval None
*/
extern void TIMER_Init(TMR_TypeDef* TIMERx, TIMER_InitTypeDef* TIM_InitStruct);

/**
* @brief  The TIMER gets the loadcounter tick value
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval tick of TIMER
*/
extern uint32_t TIMER_Get_LoadCounter_Value(TMR_TypeDef* TIMERx);

/**
* @brief  The TIMER Sets the loadcounter tick value
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  loadcounter: loadcounter tick value
* @retval None
*/
extern void TIMER_Set_LoadCounter_Value(TMR_TypeDef* TIMERx, uint32_t loadcounter);

/**
* @brief  The TIMER gets the loadcounter2 tick value
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval tick of TIMER
*/
extern uint32_t TIMER_Get_LoadCounter2_Value(TMR_TypeDef* TIMERx);

/**
* @brief  The TIMER Sets the loadcounter2 tick value
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  loadcounter: loadcounter2 tick value
* @retval None
*/
extern void TIMER_Set_LoadCounter2_Value(TMR_TypeDef* TIMERx, uint32_t loadcounter);

/**
* @brief  The TIMER gets current counter value 
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval current counter value 
*/
extern int TIMER_Get_Current_Counter_Value(TMR_TypeDef* TIMERx);

/**
* @brief  The TIMER gets the enable status
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval ENABLE or DISABLE
*/
extern FunctionalState TIMER_Get_Enable_Status(TMR_TypeDef* TIMERx);

/**
* @brief  The TIMER sets enabled or disabled command
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void TIMER_Set_Enable_Cmd(TMR_TypeDef* TIMERx, FunctionalState NewState);

/**
* @brief  The TIMER gets the running mode
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval The only one value of the TimerMode_TypeDef structure
*/
extern uint8_t TIMER_Get_Running_Mode(TMR_TypeDef* TIMERx);

/**
* @brief  The TIMER sets the running mode
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  mode: The only one value of the TimerMode_TypeDef structure
* @retval None
*/
extern void TIMER_Set_Running_Mode(TMR_TypeDef* TIMERx, uint8_t mode);

/**
* @brief  The TIMER gets the interrupt enabled status
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval ENABLE or DISABLE
*/
extern FunctionalState TIMER_Get_Interrupt_Enable_Status(TMR_TypeDef* TIMERx);

/**
* @brief  The TIMER sets interrupt enabled or disabled command
* @note   The interrupt is disabled by default
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void TIMER_Set_Interrupt_Enable_Cmd(TMR_TypeDef* TIMERx, FunctionalState NewState);

/**
* @brief  The TIMER gets the PWM-MODE enabled status
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval ENABLE or DISABLE
*/
extern FunctionalState TIMER_Get_Pwm_Enable_Status(TMR_TypeDef* TIMERx);

/**
* @brief  The TIMER sets PWM-MODE enabled or disabled command
* @note   The PWM-MODE is disabled by default
* @note   When only TIMER_USER_DEFINED_MODE parameter is enabled,the PWM-MODE is valid.
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void TIMER_Set_Pwm_Enable_Cmd(TMR_TypeDef* TIMERx, FunctionalState NewState);

/**
* @brief  The TIMER clears interrupt 
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval None
*/
extern void TIMER_Clear_Interrupt_Cmd(TMR_TypeDef* TIMERx);

/**
* @brief  The TIMER gets interrupt active status
* @param  TIMERx: where x can be 0, 1, 2, 3.@ref TIMER0,TIMER1,TIMER2.TIMER3
* @retval ENABLE or DISABLE
*/
extern FunctionalState TIMER_Get_Interrupt_Status(TMR_TypeDef* TIMERx);

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
