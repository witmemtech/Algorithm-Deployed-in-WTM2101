/**
  ******************************************************************************
  * @file    main.h
  * @brief   Header for main.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */


#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "wtm2101_config.h"
#include "WTM2101_hal.h"

#include "hal_clock.h"

#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

#define LED_PIN_0    GPIO_PIN_0
#define LED_PIN_1    GPIO_PIN_1
#define LED_ON       TRUE
#define LED_OFF      FALSE

#ifdef __cplusplus
}
#endif


#endif
