/**
  ******************************************************************************  
  * @file    ring_cache.h  
  * @brief   Header for ring_cache.c module.  
  * @date    2023-02-07  
  * Copyright (c) 2023 Witmem Technology Co., Ltd  
  * All rights reserved. 
  * 
  ******************************************************************************
  */

#ifndef __RING__CACHE__H
#define __RING__CACHE__H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stdint.h"

#define Enable_Stack_Malloc 0x01 
#define RING_CACHE_SIZE (1024 * 2)

#pragma pack(push) 
#pragma pack(1)  
typedef struct
{
    #if Enable_Stack_Malloc == 0x00
    uint8_t data[RING_CACHE_SIZE];
    #else
    uint8_t *data;
    #endif
    uint16_t ring_size;
    uint16_t current_size;
    uint16_t start;
    uint16_t end;
    void (*Critical_Section_Entry)();
    void (*Critical_Section_Leave)();
}Ring_Cache;
#pragma pack(pop) 

int Ring_Cache_Init(Ring_Cache * ring, uint16_t size);
int Ring_Cache_Clear(Ring_Cache * ring);
int Ring_Cache_Push(Ring_Cache * ring, uint8_t data);
int Ring_Cache_Push_String(Ring_Cache *ring, uint8_t *data, uint16_t len);
int Ring_Cache_Pop(Ring_Cache * ring, uint8_t * data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif
