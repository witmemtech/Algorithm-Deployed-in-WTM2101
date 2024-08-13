/**
  ******************************************************************************
  * @file    wtm2101_system.h
  * @brief   Header for wtm2101_system.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef WTM2101_SYSTEM_H
#define WTM2101_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "wtm2101_config.h"

/*!< the chip id  */
extern uint32_t __WTM2101_RevID;     

/**
* @brief  init the heap 
* @param  None
* @retval None
*/ 
extern void heap_init(void);

/**
 * \brief      Function to Initialize the system.
 * \details
 * Initializes the microcontroller system. This function enables minimal clocks and 
 * get the chip id and pull up gpio
 */
extern void SystemInit(void);

/**
 * \brief early init function before main
 * \details
 * This function is executed right before main function.
 * For RISC-V gnu toolchain, _init function might not be called
 * by __libc_init_array function, so we defined a new function
 * to do initialization
 */
extern void _premain_init(void);

/**
 * \brief finish function after main
 * \param [in]  status  status code return from main
 * \details
 * This function is executed right after main function.
 * For RISC-V gnu toolchain, _fini function might not be called
 * by __libc_fini_array function, so we defined a new function
 * to do initialization
 */
extern void _postmain_fini(int status);
 
#ifdef __cplusplus
}
#endif

#endif 

