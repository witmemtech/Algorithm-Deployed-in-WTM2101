/**
  ******************************************************************************
  * @file    pmu.h
  * @brief   Header for pmu.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __PMU_H__
#define __PMU_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "stddef.h"
#include "riscv_encoding.h"
#include "WTM2101_PMU_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup PMU
  * @{
  */
  
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PMU_Exported_Constants
  * @{
  */

/** @defgroup PMU_WORK_ON_MODE 
  * @{
  */
#define NORMAL_MODE    (0X1U)
#define STANDBY_MODE   (0X2U)
#define RSM_MODE       (0X4U)    
#define DSM_MODE       (0X8U) 
#define IS_PMU_WORK_ON_MODE(mode) (((mode) == NORMAL_MODE)  || \
                                   ((mode) == STANDBY_MODE) || \
                                   ((mode) == RSM_MODE)     || \
                                   ((mode) == DSM_MODE))
/**
  * @}
  */

/** @defgroup PMU_Clock_24Mhz_Select 
  * @{
  */
#define OSC_INTERNAL_24M (0X00U)
#define XTL_EXTERNAL_24M (0X01U)
#define IS_PMU_CLOCK_24MHZ_SELECT(clock)  (((clock) == OSC_INTERNAL_24M)  || \
                                           ((clock) == XTL_EXTERNAL_24M))
/**
  * @}
  */

/** @defgroup PMU_Clock_Souce 
  * @{
  */

#define _24M        (0X01U)
#define PLL         (0X02U)
#define OSC_10K     (0X04U)
#define OSC_320K    (0X08U)
#define XTL32K      (0X10U)
#define IS_PMU_CLOCK_SOUCE(clock) (((clock) == _24M)     || \
                                   ((clock) == PLL)      || \
                                   ((clock) == OSC_10K)  || \
                                   ((clock) == OSC_320K) || \
                                   ((clock) == XTL32K))
/**
  * @}
  */


/** @defgroup PMU_Rsm_Mode_Parameter 
  * @{
  */
#define PMU_RSM_MODE_KEEP_AUDIO     (0x01U << PMU_RSM_CTL_KEEP_AUDIO_Pos)
#define PMU_RSM_MODE_KEEP_OSC10K    (0x01U << PMU_RSM_CTL_KEEP_OSC10K_Pos)
#define PMU_RSM_MODE_KEEP_XTL32K    (0x01U << PMU_RSM_CTL_KEEP_XTL32K_Pos)
#define PMU_RSM_MODE_KEEP_OSC2M     (0x01U << PMU_RSM_CTL_KEEP_OSC2M_Pos)
#define PMU_RSM_MODE_KEEP_FLASH     (0x01U << PMU_RSM_CTL_FLASH_KEEP_Pos)
#define PMU_RSM_MODE_KEEP_WDT       (0x01U << PMU_RSM_CTL_WDT_KEEP_Pos)
#define PMU_RSM_MODE_KEEP_VDD3      (0x01U << PMU_RSM_CTL_VDD3_KEEP_Pos)
#define PMU_RSM_MODE_KEEP_VDD       (0x01U << PMU_RSM_CTL_VDD_KEEP_Pos)
#define PMU_RSM_MODE_ALL            (PMU_RSM_MODE_KEEP_AUDIO | PMU_RSM_MODE_KEEP_OSC10K | PMU_RSM_MODE_KEEP_XTL32K | PMU_RSM_MODE_KEEP_OSC2M | \
                                    PMU_RSM_MODE_KEEP_FLASH | PMU_RSM_MODE_KEEP_WDT | PMU_RSM_MODE_KEEP_VDD3 | PMU_RSM_MODE_KEEP_VDD)
#define IS_PMU_RSM_MODE_PARAMETER(parameter)    (((parameter) == PMU_RSM_MODE_KEEP_AUDIO) || \
                                                ((parameter) == PMU_RSM_MODE_KEEP_OSC10K) || \
                                                ((parameter) == PMU_RSM_MODE_KEEP_XTL32K) || \
                                                ((parameter) == PMU_RSM_MODE_KEEP_OSC2M)  || \
                                                ((parameter) == PMU_RSM_MODE_KEEP_FLASH)  || \
                                                ((parameter) == PMU_RSM_MODE_KEEP_WDT)    || \
                                                ((parameter) == PMU_RSM_MODE_KEEP_VDD3)   || \
                                                ((parameter) == PMU_RSM_MODE_KEEP_VDD)    || \
                                                ((parameter) == PMU_RSM_MODE_ALL))
/**
  * @}
  */

/** @defgroup PMU_Reset_Flag 
  * @{
  */
#define PMU_PORB_RST_FLAG       (0x01U << PMU_FLAG_CTL_PORB_RST_FLAG_Pos)
#define PMU_PIN_WU_FLAG         (0x01U << PMU_FLAG_CTL_PIN_WU_FLAG_Pos)
#define PMU_RSM0_WU_FLAG        (0x01U << PMU_FLAG_CTL_RSM0_WU_FLAG_Pos)
#define PMU_RSM1_WU_FLAG        (0x01U << PMU_FLAG_CTL_RSM1_WU_FLAG_Pos)
#define PMU_PIN_RST_FLAG        (0x01U << PMU_FLAG_CTL_PIN_RST_FLAG_Pos)
#define PMU_WDT_RST_FLAG        (0x01U << PMU_FLAG_CTL_WDT_RST_FLAG_Pos)
#define IS_PMU_RESET_FLAG(flag)        (((flag) == PMU_PORB_RST_FLAG) || \
                                        ((flag) == PMU_PIN_WU_FLAG)   || \
                                        ((flag) == PMU_RSM0_WU_FLAG)  || \
                                        ((flag) == PMU_RSM1_WU_FLAG)  || \
                                        ((flag) == PMU_PIN_RST_FLAG)  || \
                                        ((flag) == PMU_WDT_RST_FLAG))
/**
  * @}
  */


/** @defgroup PMU_WDT_Clock_Select  
  * @{
  */ 
#define PMU_CLK_WDT_SWITCH_SYSCLK_DIV_32  (0x0U << PMU_PMU_CLK_WDTCLK_SEL_Pos)
#define PMU_CLK_WDT_SWITCH_10KHZ          (0x1U << PMU_PMU_CLK_WDTCLK_SEL_Pos)
#define PMU_CLK_WDT_SWITCH_32KHZ          (0x2U << PMU_PMU_CLK_WDTCLK_SEL_Pos)
#define PMU_CLK_WDT_SWITCH_160KHZ         (0x3U << PMU_PMU_CLK_WDTCLK_SEL_Pos)
#define IS_PMU_RTC_CLOCK_SELECT(clock)   (((clock) == PMU_CLK_WDT_SWITCH_SYSCLK_DIV_32) || \
                                                ((clock) == PMU_CLK_WDT_SWITCH_10KHZ)   || \
                                                ((clock) == PMU_CLK_WDT_SWITCH_32KHZ)   || \
                                                ((clock) == PMU_CLK_WDT_SWITCH_160KHZ))
/**
  * @}
  */


/** @defgroup PMU_RTC_Clock_Select 
  * @{
  */ 
#define PMU_CLK_RTC_SWITCH_SYSCLK_DIV_32  (0x0U << PMU_PMU_CLK_RTCCLK_SEL_Pos)
#define PMU_CLK_RTC_SWITCH_10KHZ          (0x1U << PMU_PMU_CLK_RTCCLK_SEL_Pos)
#define PMU_CLK_RTC_SWITCH_32KHZ          (0x2U << PMU_PMU_CLK_RTCCLK_SEL_Pos)
#define PMU_CLK_RTC_SWITCH_160KHZ         (0x3U << PMU_PMU_CLK_RTCCLK_SEL_Pos)
#define IS_PMU_WDT_CLOCK_SELECT(clock)   (((clock) == PMU_CLK_RTC_SWITCH_SYSCLK_DIV_32) || \
                                          ((clock) == PMU_CLK_RTC_SWITCH_10KHZ)         || \
                                          ((clock) == PMU_CLK_RTC_SWITCH_32KHZ)         || \
                                          ((clock) == PMU_CLK_RTC_SWITCH_160KHZ))
/**
  * @}
  */


/** @defgroup PMU_Interrupt_Or_Event_Mask
  * @{
  */
#define PMU_VAD_IMSK    (0x1U << PMU_IE_MSK_VAD_IMSK_Pos)
#define PMU_RTC_IMSK    (0x1U << PMU_IE_MSK_RTC_IMSK_Pos)
#define PMU_WDT_IMSK    (0x1U << PMU_IE_MSK_WDT_IMSK_Pos)
#define PMU_GPIO_IMSK   (0x1U << PMU_IE_MSK_GPIO_IMSK_Pos)
#define PMU_VAD_EMSK    (0x1U << PMU_IE_MSK_VAD_EMSK_Pos)
#define PMU_RTC_EMSK    (0x1U << PMU_IE_MSK_RTC_EMSK_Pos)
#define PMU_WDT_EMSK    (0x1U << PMU_IE_MSK_WDT_EMSK_Pos)
#define PMU_GPIO_EMSK   (0x1U << PMU_IE_MSK_GPIO_EMSK_Pos)
#define IS_PMU_INTERRUPT_OR_EVENT_MASK(mask) (((mask) == PMU_VAD_IMSK)  || \
                                              ((mask) == PMU_RTC_IMSK)  || \
                                              ((mask) == PMU_WDT_IMSK)  || \
                                              ((mask) == PMU_GPIO_IMSK) || \
                                              ((mask) == PMU_VAD_EMSK)  || \
                                              ((mask) == PMU_RTC_EMSK)  || \
                                              ((mask) == PMU_WDT_EMSK)  || \
                                              ((mask) == PMU_GPIO_EMSK))
/**
  * @}
  */

/** @defgroup PMU_Ldo_Voltage_Value 
  * @{
  */
#define PMU_LDO_VOLTAGE_0_9V    (0x1U)
#define PMU_LDO_VOLTAGE_1_1V    (0x2U)
#define IS_PMU_Ldo_Voltage_Value(value) (((value) == PMU_LDO_VOLTAGE_0_9V) || \
                                         ((value) == PMU_LDO_VOLTAGE_1_1V))
/**
  * @}
  */


/** @defgroup PMU_Sram_Address 
  * @{
  */ 
#define PMU_SRAM0               (PMU_SRAM_PD_SRAM0_PD_Msk)
#define PMU_SRAM1_FIRST_32K     (PMU_SRAM_PD_SRAM1_0_PD_Msk)
#define PMU_SRAM1_SECOND_32K    (PMU_SRAM_PD_SRAM1_1_PD_Msk)
#define PMU_SRAM2_FIRST_32K     (PMU_SRAM_PD_SRAM2_0_PD_Msk)
#define PMU_SRAM2_SECOND_32K    (PMU_SRAM_PD_SRAM2_1_PD_Msk)
#define PMU_DSP_SRAM_RTN        (PMU_SRAM_RTN_DSP_SRAM_Msk)
#define PMU_SRAM_ALL            (PMU_SRAM0 | PMU_SRAM1_FIRST_32K | PMU_SRAM1_SECOND_32K | PMU_SRAM2_FIRST_32K | PMU_SRAM2_SECOND_32K | PMU_DSP_SRAM_RTN)
#define IS_PMU_Sram_Address(address)  (((address) == PMU_SRAM0)           || \
                                      ((address) == PMU_SRAM1_FIRST_32K)  || \
                                      ((address) == PMU_SRAM1_SECOND_32K) || \
                                      ((address) == PMU_SRAM2_FIRST_32K)  || \
                                      ((address) == PMU_SRAM2_SECOND_32K) || \
                                      ((address) == PMU_DSP_SRAM_RTN)     || \
                                      ((address) == PMU_SRAM_ALL))
/**
  * @}
  */

/** @defgroup PMU_Software_Reset_Value 
  * @{
  */
#define PMU_SOFTWARE_RESET_VALUE           (0x55)
/**
  * @}
  */

/** @defgroup PMU_24M_Trim_Source 
  * @{
  */
#define PMU_24M_TRIM_SOURCE_FROM_OTHER     (0x00)
#define PMU_24M_TRIM_SOURCE_FROM_CPU       (0x01)
#define PMU_24M_TRIM_SOURCE_FROM_MOUDLE    (0x02)
/**
  * @}
  */

/** @defgroup PMU_320K_Trim_Source 
  * @{
  */
#define PMU_320K_TRIM_SOURCE_FROM_OTHER    (0x00)
#define PMU_320K_TRIM_SOURCE_FROM_CPU      (0x01)
#define PMU_320K_TRIM_SOURCE_FROM_MOUDLE   (0x02)
/**
  * @}
  */

/**
  * @}
  */
  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


/** @defgroup PMU_Functions_Prototypes PMU Functions Prototypes
* @{
*/

/**
* @brief  The pmu set rsm mode
* @note   Firstly you should configurate the wakeup source , and configurate some parameter by calling the PMU_Set_Rsm_Mode_Parameter() function ,
*         then call this function,finally you should call __WFI() or __WFE() function
* @param  pmu: pmu base address:@ref PMU
* @retval None
*/
extern void PMU_Rsm_Mode_Cmd(PMU_TypeDef *pmu);

/**
* @brief  The pmu set dsm mode
* @note   Finally you should call __WFI() or __WFE() function
* @param  pmu: pmu base address:@ref PMU
* @retval None
*/
extern void PMU_Dsm_Mode_Cmd(PMU_TypeDef *pmu);

/**
* @brief  The pmu set standby mode
* @note   Finally you should call __WFI() or __WFE() function
* @param  pmu: pmu base address:@ref PMU
* @retval None
*/
extern void PMU_Standby_Mode_Cmd(PMU_TypeDef *pmu);

/**
* @brief  The pmu enable the external clock.If you want to use the external clock,you must call this function in firstly.
* @param  pmu: pmu base address:@ref PMU
* @param  NewState: ENABLE or DISABLE 
* @retval None
*/
extern void PMU_Enable_External_Clock(PMU_TypeDef *pmu, FunctionalState NewState);

/**
* @brief  The pmu get 24mhz clock source
* @param  pmu: pmu base address:@ref PMU
* @retval This value can be only one of @ref PMU_Clock_24Mhz_Select
*/
extern uint8_t PMU_Get_24Mhz_Clock_Source(PMU_TypeDef *pmu);

/**
* @brief  The pmu select 24mhz clock source
* @note   The internal clock source(OSC_INTERNAL_24M) is used by default.
* @param  pmu: pmu base address:@ref PMU
* @param  clock_select: This parameter can be only one of @ref PMU_Clock_24Mhz_Select
* @retval None
*/
extern void PMU_Select_24Mhz_Clock_Cmd(PMU_TypeDef *pmu, uint8_t clock_select);

/**
* @brief  The pmu get 24mhz clock source divide number
* @param  pmu: pmu base address:@ref PMU
* @retval divide number
*/
extern uint8_t PMU_Get_24M_Clock_Source_div(PMU_TypeDef *pmu);

/**
* @brief  The pmu set 24mhz clock source divide number
* @param  pmu: pmu base address:@ref PMU
* @param  div: this value only can be 1,2,4,6,12.other value is invalid.
* @retval None
*/
extern void PMU_Set_24M_Clock_Source_div(PMU_TypeDef *pmu, uint8_t div);

/**
* @brief  The pmu set systerm clock source.
* @note   If you want to use external 24mhz clock,you must call the PMU_Select_24Mhz_Clock_Cmd() function before using this funciton
* @note   You can open or close one or more clock source
* @param  pmu: pmu base address:@ref PMU
* @param  clock_souce: This parameter can be one or more value of @ref PMU_Clock_Souce
* @param  NewState: ENABLE or DISABLE 
* @retval None
*/
extern void PMU_Set_Clock_Source_Cmd(PMU_TypeDef *pmu, uint8_t clock_souce, FunctionalState NewState);

/**
* @brief  The pmu set audio clock enabled or disabled command
* @param  pmu: pmu base address:@ref PMU
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Set_Audio_Clock_Cmd(PMU_TypeDef *pmu, FunctionalState NewState);

/**
* @brief  The pmu set the parameter about rsm mode
* @param  pmu: pmu base address:@ref PMU
* @param  parameter: This parameter can be one or more value of @ref PMU_Rsm_Mode_Parameter
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Set_Rsm_Mode_Parameter(PMU_TypeDef *pmu, uint8_t parameter, FunctionalState NewState);

/**
* @brief  The pmu get reset flag
* @param  pmu: pmu base address:@ref PMU
* @retval This parameter can be one or more value of @ref PMU_Reset_Flag
*/
extern uint8_t PMU_Get_Reset_Flag(PMU_TypeDef *pmu);

/**
* @brief  The pmu clear reset flag
* @param  pmu: pmu base address:@ref PMU
* @retval None
*/
extern void PMU_Clear_Reset_Flag(PMU_TypeDef *pmu);

/**
* @brief  The pmu get rtc and wdt enabled_status about high clock
* @param  pmu: pmu base address:@ref PMU
* @retval ENABLE or DISABLE
*/
extern FunctionalState PMU_Get_High_Clock_For_Rtc_And_Wdt_EnableStatus(PMU_TypeDef *pmu);

/**
* @brief  The pmu set rtc and wdt command about high clock
* @param  pmu: pmu base address:@ref PMU
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Enable_High_Clock_For_Rtc_And_Wdt(PMU_TypeDef *pmu, FunctionalState NewState);

/**
* @brief  The pmu get rtc clock source
* @param  pmu: pmu base address:@ref PMU
* @retval This parameter can be one value of @ref PMU_RTC_Clock_Select
*/
extern uint8_t PMU_Get_Rtc_Clock_Source(PMU_TypeDef *pmu);

/**
* @brief  The pmu set rtc clock source
* @param  pmu: pmu base address:@ref PMU
* @param  select_rtc_clock : This parameter can be one value of @ref PMU_RTC_Clock_Select
* @retval None
*/
extern void PMU_Set_Rtc_Clock_Source(PMU_TypeDef *pmu, uint8_t select_rtc_clock);

/**
* @brief  The pmu get wdt clock source
* @param  pmu: pmu base address:@ref PMU
* @retval This parameter can be one value of @ref PMU_WDT_Clock_Select
*/
extern uint8_t PMU_Get_Wdt_Clock_Source(PMU_TypeDef *pmu);

/**
* @brief  The pmu set wdt clock source
* @param  pmu: pmu base address:@ref PMU
* @param  select_wdt_clock : This parameter can be one value of @ref PMU_WDT_Clock_Select
* @retval None
*/
extern void PMU_Set_Wdt_Clock_Source(PMU_TypeDef *pmu, uint8_t select_wdt_clock);

/**
* @brief  The pmu set the interrupt or event mask
* @param  pmu: pmu base address:@ref PMU
* @retval This parameter can be one or more value of @ref PMU_Interrupt_Or_Event_Mask
*/
extern uint8_t PMU_Get_Ie_Msk(PMU_TypeDef *pmu);

/**
* @brief  The pmu set the interrupt or event mask
* @param  pmu: pmu base address:@ref PMU
* @param  ie_msk : This parameter can be one or more value of @ref PMU_Interrupt_Or_Event_Mask
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Set_Ie_Msk(PMU_TypeDef *pmu, uint8_t ie_msk, FunctionalState NewState);

/**
* @brief  The pmu get npu poweron status
* @param  pmu: pmu base address:@ref PMU
* @retval ENABLE or DISABLE
*/
extern FunctionalState PMU_Get_Npu_Poweron_Cmd_Status(PMU_TypeDef *pmu);

/**
* @brief  The pmu set npu poweron command
* @param  pmu: pmu base address:@ref PMU
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Set_Npu_Poweron_Cmd(PMU_TypeDef *pmu, FunctionalState NewState);

/**
* @brief  The pmu get npu reset status
* @param  pmu: pmu base address:@ref PMU
* @retval npu reset status
*/
extern FunctionalState PMU_Get_Npu_Reset_Status(PMU_TypeDef *pmu);

/**
* @brief  The pmu reset npu module
* @param  pmu: pmu base address:@ref PMU
* @retval None
*/
extern void PMU_Set_Npu_Reset(PMU_TypeDef *pmu);

/**
* @brief  The pmu get npu clock status
* @param  pmu: pmu base address:@ref PMU
* @retval ENABLE or DISABLE
*/
extern FunctionalState PMU_Get_Npu_Clock_Cmd_Status(PMU_TypeDef *pmu);

/**
* @brief  The pmu set npu clock command
* @param  pmu: pmu base address:@ref PMU
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Set_Npu_Clock_Cmd(PMU_TypeDef *pmu, FunctionalState NewState);

/**
* @brief  The pmu get periphral power status
* @param  pmu: pmu base address:@ref PMU
* @retval ENABLE or DISABLE
*/
extern FunctionalState PMU_Get_Periphral_Poweron_Cmd_Status(PMU_TypeDef *pmu);

/**
* @brief  The pmu set periphral power enabled or disabled command
* @param  pmu: pmu base address:@ref PMU
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Set_Periphral_Poweron_Cmd(PMU_TypeDef *pmu, FunctionalState NewState);

/**
* @brief  The pmu get audio clock divide number
* @param  pmu: pmu base address:@ref PMU
* @retval the divide number
*/
extern uint8_t PMU_Get_Audio_Clock_Div_Num(PMU_TypeDef *pmu);

/**
* @brief  The pmu set audio clock divide number
* @param  pmu: pmu base address:@ref PMU
* @param  div_num: the adc clock divide number
* @retval None
*/
extern void PMU_Set_Audio_Clock_Div_Num(PMU_TypeDef *pmu, uint8_t div_num);

/**
* @brief  The pmu get npu clock divide number
* @param  pmu: pmu base address:@ref PMU
* @retval the divide number
*/
extern uint8_t PMU_Get_NPU_Clock_Div_Num(PMU_TypeDef *pmu);

/**
* @brief  The pmu set npu clock divide number
* @param  pmu: pmu base address:@ref PMU
* @param  div_num: the npu clock divide number
* @retval None
*/
extern void PMU_Set_NPU_Clock_Div_Num(PMU_TypeDef *pmu, uint8_t div_num);

/**
* @brief  The pmu get ldo voltage value
* @param  pmu: pmu base address:@ref PMU
* @retval the one value of @ref PMU_Ldo_Voltage_Value
*/
extern uint8_t PMU_Get_Ldo_Voltage_Value(PMU_TypeDef *pmu);

/**
* @brief  The pmu set ldo voltage value
* @param  pmu: pmu base address:@ref PMU
* @param  ldo_voltage: this parameter can be one value of @ref PMU_Ldo_Voltage_Value
* @retval None
*/
extern void PMU_Set_Ldo_Voltage_Value(PMU_TypeDef *pmu, uint8_t ldo_voltage);

/**
* @brief  The pmu set the ldo voltage update signal
* @param  pmu: pmu base address:@ref PMU
* @retval None
*/
extern void PMU_Set_Ldo_Voltage_Cmd(PMU_TypeDef *pmu);

/**
* @brief  The pmu get sram power status
* @param  pmu: pmu base address:@ref PMU
* @retval the one or more value of @ref PMU_Sram_Address
*/
extern uint8_t PMU_Get_Sram_Poweron_Status(PMU_TypeDef *pmu);

/**
* @brief  The pmu set sram power enabled or disabled command
* @param  pmu: pmu base address:@ref PMU
* @param  sram_region: This parameter can be one or more value of @ref PMU_Sram_Address
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Set_Sram_Poweron_Cmd(PMU_TypeDef *pmu, uint8_t sram_region, FunctionalState NewState);

/**
* @brief  The pmu set sram retain in rsm mode
* @param  pmu: pmu base address:@ref PMU
* @param  sram_region: This parameter can be one or more value of @ref PMU_Sram_Address
* @param  NewState: This parameter can be ENABLE or DISABLE
* @retval None
*/
extern void PMU_Set_Sram_Retain_In_Rsm_Mode_Cmd(PMU_TypeDef *pmu, uint8_t sram_region, FunctionalState NewState);

/**
* @brief  The pmu get pll clock divide number
* @param  pmu: pmu base address:@ref PMU
* @retval the divide number
*/
extern uint8_t PMU_Get_Pll_Division(PMU_TypeDef *pmu);

/**
* @brief  The pmu set pll clock divide number
* @param  pmu: pmu base address:@ref PMU
* @param  division: the pll clock divide number from 0 to 31.
* @retval None
*/
extern void PMU_Set_Pll_Division(PMU_TypeDef *pmu, uint8_t division);

/**
* @brief  The pmu set software reset
* @param  pmu: pmu base address:@ref PMU
* @retval None
*/
extern void PMU_Software_Reset(PMU_TypeDef *pmu);

/**
* @brief  The pmu set osc24m clock calibration signal source
* @param  pmu: pmu base address:@ref PMU
* @param  source: calibration signal source:@ref PMU_24M_Trim_Source
* @retval None
*/
extern void PMU_Set_24M_Trim_Source(PMU_TypeDef *pmu, uint8_t source);

/**
* @brief  The pmu set osc320k clock calibration signal source
* @param  pmu: pmu base address:@ref PMU
* @param  source: calibration signal source:@ref PMU_320K_Trim_Source
* @retval None
*/
extern void PMU_Set_320K_Trim_Source(PMU_TypeDef *pmu, uint8_t source);

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
