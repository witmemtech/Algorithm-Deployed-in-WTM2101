/**
  ******************************************************************************
  * @file    wtm2101_mmap.h
  * @brief   Header for wtm2101_mmap.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef WTM2101_MMAP_H
#define WTM2101_MMAP_H

#include <stdint.h>

/**
* @brief  map system address to corresponding offset address 0x30000000
* @param  addr: the address 
* @retval corresponding offset address
*/ 
extern uint32_t mmap_to_sys(uint32_t addr);

#endif

