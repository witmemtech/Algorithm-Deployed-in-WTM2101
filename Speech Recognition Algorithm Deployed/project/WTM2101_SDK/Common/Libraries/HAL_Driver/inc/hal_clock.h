/**
  ******************************************************************************
  * @file    hal_clock.h
  * @brief   Header for hal_clock.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef HAL_CLOCK_H
#define HAL_CLOCK_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "WTM2101.h"
#include "pmu.h"
#include "rcc.h"
#include "npu.h"

#include "stddef.h"
#include <stdarg.h>
#include "string.h"

#include "wtm2101_hal.h"

#include "LibNPU.h"
#include "osc_clock_calibration.h"

typedef enum{
  HAL_CLOCK_SWITCH_SYSTEM_CLOCK_COMMAND     = (1 << 0),     /*the hal clock switch system clock command*/
}Hal_Clock_Control_Command;

typedef enum
{
  HAL_CLOCK_24MOSC = _24M,                                  /*the system 24Mosc clock*/
  HAL_CLOCK_PLL    = PLL,                                   /*the system PLL clock*/
  HAL_CLOCK_10KOSC = OSC_10K,                               /*the system 10K clock*/
  HAL_CLOCK_320KOSC = OSC_320K,                             /*the system 320K clock*/
  HAL_CLOCK_XTL32K = XTL32K,                                /*the system XTAL32K clock*/
}Hal_Clock_SelectTypeDef;

typedef enum
{
  HAL_CLOCK_24MOSC_INTERNAL = 0,                            /*the system 24Mosc clock is from inner*/
  HAL_CLOCK_24MOSC_EXTERNAL = 1,                            /*the system 24Mosc clock is from outer*/
}Hal_Clock_24Mosc_ModeTypeDef;

typedef enum
{
  HAL_CLOCK_24MOSC_USE_NPU_CALIBRATION_PARAMETER = 0,       /*the system 24Mosc clock uses calibration parameters that are saved in the NPU*/
  HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER = 1,    /*the system 24Mosc clock is calibrated by the xtal 32k*/
}Hal_Clock_24Mosc_CalibrationTypeDef;

typedef struct
{
  Hal_Clock_24Mosc_ModeTypeDef use_24mosc_way;              /*the internal or external clock*/
  int clock_hz;                                             /*the actual clock about the system 24Mosc clock */
  int clock320k_hz;                                         /*the actual clock about the system 320kosc clock */
  int clock_divider;                                        /*the clock divider about the value clock_hz,the value clock_divider must be 1,2,4,6,12*/
  FunctionalState internal_24mosc_calibration_flag;         /*the flag if calibration*/
  Hal_Clock_24Mosc_CalibrationTypeDef calibration_way;      /*the calibration way*/
}Hal_Clock_24mosc_Configuration;

typedef struct
{
  int need_use_clock;                                      /*the system clock is used all the time */
  Hal_Clock_SelectTypeDef system_clock_select_source;      /*the system clock source*/
  Hal_Clock_24mosc_Configuration _24mosc_configuration;    /*the system 24mosc clock configuration parameter,if the value system_clock_select_source is HAL_CLOCK_24MOSC or HAL_CLOCK_PLL*/
  int pllclock_upfrequency_coefficient;                    /*the system PLL clock up frequency coefficient*/
  int ahbbus_downfrequency_coefficient;                    /*the system AHB bus down frequency coefficient*/
  int apbbus_downfrequency_coefficient;                    /*the system APB bus down frequency coefficient*/
  int system_clock_frequency;                              /*the system clock frequency before using the ahbbus_downfrequency_coefficient and apbbus_downfrequency_coefficient parameter */
  int _24m_coarse,_24m_fine;                               /*the 24mosc calibration value is from NPU*/
  int _320k_coarse,_320k_fine;                             /*the 320k calibration value is from NPU*/
}Hal_Clock_InitTypeDef;

/**
* @brief  Get the hal clock instance
* @param  none
* @retval the hal clock instance
*/
extern Hal_Clock_InitTypeDef* hal_clock_instance_get(void);

/**
* @brief  Init the hal clock instance
* @param  clock_instance: the hal clock instance
* @param  used_clock: the system clock is used all the time
* @param  system_clock: the system actual clock source
* @param  _24moc_config: the system 24mosc clock configuration parameter
* @param  pll_factor: the PLL up frequency coefficient
* @param  ahb_divider: the AHB bus down frequency coefficient
* @param  apb_divider: the APB bus down frequency coefficient
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_clock_init(Hal_Clock_InitTypeDef *clock_instance,int used_clock,Hal_Clock_SelectTypeDef system_clock,Hal_Clock_24mosc_Configuration *_24moc_config,int pll_factor,int ahb_divider,int apb_divider);

/**
* @brief  Control the hal clock instance 
* @param  clock_instance: the hal clock instance
* @param  command: the related command with Hal_Clock_Control_Command
* @param  ...: the attach value about the parameter command
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_clock_ctl(Hal_Clock_InitTypeDef *clock_instance,int command, ...);

/**
* @brief  Open the actual related clock hardware
* @param  clock_instance: the hal clock instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_clock_open(Hal_Clock_InitTypeDef *clock_instance);

/**
* @brief  Close the hal clock instance and related hardware,currently not implemented
* @param  clock_instance: the hal clock instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int hal_clock_close(Hal_Clock_InitTypeDef *clock_instance);

#ifdef __cplusplus
}
#endif

#endif
