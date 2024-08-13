/**
  ******************************************************************************
  * @file    rtc.h
  * @brief   Header for rtc.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __RTC_H__
#define __RTC_H__

#ifdef  __cplusplus
extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "pmu.h"
#include "rcc.h"
#include "stddef.h"
#include "WTM2101_RTC_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/** @defgroup RTC_Functions_Prototypes RTC Functions Prototypes
* @{
*/

/**
* @brief  The RTC transfers second to tick.
* @param  rtc: RTC base address.@ref RTC
* @param  second: second of time
* @retval tick of RTC
*/
extern uint32_t RTC_Transfer_second_to_tick(RTC_TypeDef *rtc, uint32_t second);

/**
* @brief  The RTC transfers millisecond to tick.
* @param  rtc: RTC base address.@ref RTC
* @param  millisecond: millisecond of time
* @retval tick of RTC
*/
extern uint32_t RTC_Transfer_millisecond_to_tick(RTC_TypeDef *rtc, uint32_t millisecond);

/**
* @brief  The RTC transfers microsecond to tick.
* @param  rtc: RTC base address.@ref RTC
* @param  microsecond: microsecond of time
* @retval tick of RTC
*/
extern uint32_t RTC_Transfer_microsecond_to_tick(RTC_TypeDef *rtc, uint32_t microsecond);

/**
* @brief  The RTC gets current counter register value
* @param  rtc: RTC base address.@ref RTC
* @retval current counter register tick value
*/
extern uint32_t RTC_Get_Counter_Value(RTC_TypeDef *rtc);

/**
* @brief  The RTC gets the compare tick value
* @param  rtc: RTC base address.@ref RTC
* @retval the compare tick value
*/
extern uint32_t RTC_Get_Compare_Time_Value(RTC_TypeDef *rtc);

/**
* @brief  The RTC sets the compare tick value
* @note   The timeout time is calculated from the time difference between RTC_Set_Compare_Time_Value() and RTC_Set_Initial_Time_Value() function.
* @note   The RTC is always running,if the RTC_Set_Compare_Time_Value() or RTC_Set_Initial_Time_Value() function is set.
* @param  rtc: RTC base address.@ref RTC
* @param  timeout:  the compare tick value. The user can call the RTC_Transfer_second_to_tick() and RTC_Transfer_millisecond_to_tick() and 
*         RTC_Transfer_microsecond_to_tick() function to transfer time to tick.
* @retval None
*/
extern void RTC_Set_Compare_Time_Value(RTC_TypeDef *rtc, uint32_t timeout);

/**
* @brief  The RTC gets the initial tick value
* @param  rtc: RTC base address.@ref RTC
* @retval the initial tick value
*/
extern uint32_t RTC_Get_Initial_Time_Value(RTC_TypeDef *rtc);

/**
* @brief  The RTC sets the initial tick value
* @note   The timeout time is calculated from the time difference between RTC_Set_Compare_Time_Value() and RTC_Set_Initial_Time_Value() function.
* @note   The RTC is always running,if the RTC_Set_Compare_Time_Value() or RTC_Set_Initial_Time_Value() function is set.
* @param  rtc: RTC base address.@ref RTC
* @param  timeout:  the initial tick value. The user can call the RTC_Transfer_second_to_tick() and RTC_Transfer_millisecond_to_tick() and
*         RTC_Transfer_microsecond_to_tick() function to transfer time to tick.
* @retval None
*/
extern void RTC_Set_Initial_Time_Value(RTC_TypeDef *rtc, uint32_t timeout);

/**
* @brief  The RTC gets interrupt enabled status
* @param  rtc: RTC base address.@ref RTC
* @retval ENABLE or DISABLE
*/
extern FunctionalState RTC_Get_Interrupt_Enable_Status(RTC_TypeDef *rtc);

/**
* @brief  The RTC sets interrupt enabled or disabled command
* @param  rtc: RTC base address.@ref RTC
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void RTC_Set_Interrupt_Cmd(RTC_TypeDef *rtc, FunctionalState NewState);

/**
* @brief  The RTC gets interrupt unmasked status
* @param  rtc: RTC base address.@ref RTC
* @retval ENABLE or DISABLE
*/
extern FunctionalState RTC_Get_Interrupt_Unmask_Status(RTC_TypeDef *rtc);

/**
* @brief  The RTC sets interrupt unmasked command
* @param  rtc: RTC base address.@ref RTC
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void RTC_Set_Interrupt_Unmask_Cmd(RTC_TypeDef *rtc, FunctionalState NewState);

/**
* @brief  The RTC gets wrap status
* @param  rtc: RTC base address.@ref RTC
* @retval ENABLE or DISABLE
*/
extern FunctionalState RTC_Get_Wrap_Status(RTC_TypeDef *rtc);

/**
* @brief  The RTC sets wrap command.If the wrap is enabled,when the interrupt happen,the counter register will reach the initial tick value.
* @param  rtc: RTC base address.@ref RTC
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void RTC_Set_Wrap_Cmd(RTC_TypeDef *rtc, FunctionalState NewState);

/**
* @brief  The RTC gets interrupt status after the interrupt is enabled
* @param  rtc: RTC base address.@ref RTC
* @retval ENABLE or DISABLE
*/
extern FunctionalState RTC_Get_Interrupt_Status(RTC_TypeDef *rtc);

/**
* @brief  The RTC gets raw interrupt status before the interrupt is enabled
* @param  rtc: RTC base address.@ref RTC
* @retval ENABLE or DISABLE
*/
extern FunctionalState RTC_Get_Raw_Interrupt_Status(RTC_TypeDef *rtc);

/**
* @brief  The RTC clear the interrupt
* @param  rtc: RTC base address.@ref RTC
* @retval None
*/
extern void RTC_Clear_Int_Cmd(RTC_TypeDef *rtc);

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
