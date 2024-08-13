/**
  ******************************************************************************
  * @file    wdt.h
  * @brief   Header for wdt.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __WDT_H__
#define __WDT_H__

#ifdef  __cplusplus
extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "stddef.h"
#include "WTM2101_WDT_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup WDT
  * @{
  */

/* Exported constants --------------------------------------------------------*/
 
/** @defgroup WDT_Exported_Constants
  * @{
  */

/** @defgroup WDTFeedDog_TypeDef
* @{
*/
#define WDT_FEED_DOG_VALUE   (0X76)
/**
* @}
*/

/**
* @}
*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup WDT_Functions_Prototypes WDT Functions Prototypes
* @{
*/

/**
* @brief  The WDT gets enable status
* @param  wdt: Watch dog base address.@ref WDT
* @retval ENABLE or DISABLE
*/
extern FunctionalState WDT_Get_Enable_Status(WDT_TypeDef *wdt);

/**
* @brief  The WDT sets enable command
* @note   You must call wdt_feed_dog() function before firstly using it to prevent accidental restarts.
* @param  wdt: Watch dog base address.@ref WDT
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void WDT_Set_Enable_Cmd(WDT_TypeDef *wdt, FunctionalState NewState);

/**
* @brief  The WDT sets the timeout value 
* @param  wdt: Watch dog base address.@ref WDT
* @param  value: This parameter can be a number between 0x00 and 0x0f
* @note   The interrupt time can be calculate by this.
*         time(s)=2^(16 + value) / WDT_CLOCK),WDT_CLOCK is determined by the function PMU_Set_Wdt_Clock_Source().
* @retval None
*/
extern void WDT_Set_Timeout_Value(WDT_TypeDef *wdt, uint8_t value);

/**
* @brief  The WDT gets current counter register value
* @param  wdt: Watch dog base address.@ref WDT
* @retval current counter register value
*/
extern int WDT_Get_Current_Counter_Value(WDT_TypeDef *wdt);

/**
* @brief  The WDT feeds dog 
* @param  wdt: Watch dog base address.@ref WDT
* @retval None
*/
extern void WDT_Feed_Dog(WDT_TypeDef *wdt);

/**
* @brief  The WDT clears interrupt 
* @param  wdt: Watch dog base address.@ref WDT
* @retval None
*/
extern void WDT_Clear_Int_Cmd(WDT_TypeDef *wdt);
 
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
