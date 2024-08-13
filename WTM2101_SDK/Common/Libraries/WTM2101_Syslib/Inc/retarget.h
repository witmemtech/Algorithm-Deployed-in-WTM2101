/**
  ******************************************************************************
  * @file    retarget.h
  * @brief   Header for retarget.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef RETARGET_H
#define RETARGET_H

#include <stdio.h>
#include "wtm2101_config.h"

#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

typedef enum
{
  PRINTF_RETARGET_NONE = 0,
  PRINTF_RETARGET_UART0 = 1,
  PRINTF_RETARGET_UART1 = 2,
  PRINTF_RETARGET_SEGGER = 3, 
}Retaget_Typedef; 

/**
* @brief  Set ouput redirect 
* @param  type: redirect type
* @retval None
*/ 
extern void printf_output_redirect_set(Retaget_Typedef type);

#endif






