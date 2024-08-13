/**
  ******************************************************************************
  * @file    wtm2101_hal.h
  * @brief   Header for wtm2101_hal.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef WTM2101_HAL_H
#define WTM2101_HAL_H

#include "wtm2101_config.h"
#include "hal_clock.h"
#include "retarget.h"

/**
* @brief  delay second
* @param  time: the second
* @retval None
*/ 
extern void system_delay_s(uint32_t time);

/**
* @brief  delay millisecond
* @param  time: the millisecond
* @retval None
*/ 
extern void system_delay_ms(uint32_t time);

/**
* @brief  delay microsecond
* @param  time: the microsecond
* @retval None
*/ 
extern void system_delay_us(uint32_t time);

/**
* @brief  delay system tick
* @param  time: system tick value
* @retval None
*/ 
extern void system_delay_tick(uint32_t time);

/**
* @brief  delay system tick
* @param  time: system tick value
* @retval None
*/ 
extern void system_config_dump(void);

#endif


