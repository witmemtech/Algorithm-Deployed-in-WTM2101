/**
  ******************************************************************************
  * @file    heap.h
  * @brief   Header for heap.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __HEAP__H
#define __HEAP__H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

void *pvPortMalloc(size_t xWantedSize);
void vPortFree(void *pv);

#ifdef __cplusplus
}
#endif

#endif
