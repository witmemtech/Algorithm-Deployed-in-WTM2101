/**
  ******************************************************************************
  * @file    WTM2101_assert.h
  * @brief   Header for WTM2101 func param assert.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __WTM2101_ASSERT_H
#define __WTM2101_ASSERT_H

//#define USE_ASSERT            1U



#ifdef  USE_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr)   ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_ASSERT */


#endif /* __WTM2101_CONF_H */

/******************************* 	End Of File	 ******************************/
