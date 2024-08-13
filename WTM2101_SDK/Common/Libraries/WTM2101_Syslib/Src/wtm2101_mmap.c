/**
* @file    wtm2101_mmap.c
* @brief   The Source Codes for the wtm2101_mmap Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

/*
 * CODE, 192K
 *    0x0000_0000 - 0x0001_FFFF, RAM0, 128K (select)
 *    0x0002_0000 - 0x0002_7FFF, RAM4,  32K
 *    0x0002_8000 - 0x0002_FFFF, RAM3,  32K
 *    0x0003_0000 - 0x0003_FFFF, RAM2,  64K
 *
 * DATA, 128K
 *    0x2000_0000 - 0x2000_FFFF, RAM1,  64K (select)
 *    0x2001_0000 - 0x2001_FFFF, RAM2,  64K
 *    0x2002_0000 - 0x2002_7FFF, RAM3,  32K
 *    0x2002_8000 - 0x2002_FFFF, RAM4,  32K
 *
 * SYS (FULL Accessible)
 *    0x3000_0000 - 0x3001_FFFF, RAM0, 128K
 *    0x3002_0000 - 0x3002_FFFF, RAM1,  64K
 *    0x3003_0000 - 0x3003_FFFF, RAM2,  64K
 *    0x3004_0000 - 0x3004_7FFF, RAM3,  32K
 *    0x3004_8000 - 0x3004_FFFF, RAM4,  32K
 *    
 */
#include "wtm2101_mmap.h"
#define RESERVED_ADDRESS    0x00000000

typedef struct {
    const char* name;
    uint32_t    start;
    uint32_t    end;
    uint32_t    target;
}memory_mapping_t;


const memory_mapping_t MMAP_LUT[] = {
    // ILM
#ifdef QSPI_BOOT
    { "RAM0", 0x00200000, 0x0021FFFF, 0x30000000 },
    { "RAM4", 0x00220000, 0x00227FFF, 0x30048000 },
    { "RAM3", 0x00228000, 0x0022FFFF, 0x30040000 },
    { "RAM2", 0x00230000, 0x0023FFFF, 0x30030000 },
#else
    { "RAM0", 0x00000000, 0x0001FFFF, 0x30000000 },
    { "RAM4", 0x00020000, 0x00027FFF, 0x30048000 },
    { "RAM3", 0x00028000, 0x0002FFFF, 0x30040000 },
    { "RAM2", 0x00030000, 0x0003FFFF, 0x30030000 },
#endif
    // DLM
    { "RAM1", 0x20000000, 0x2000FFFF, 0x30020000 },
    { "RAM2", 0x20010000, 0x2001FFFF, 0x30030000 },
    { "RAM3", 0x20020000, 0x20027FFF, 0x30040000 },
    { "RAM4", 0x20028000, 0x2002FFFF, 0x30048000 },
};

uint32_t mmap_to_sys(uint32_t addr)
{
    const int n = sizeof(MMAP_LUT)/sizeof(MMAP_LUT[0]);
    int i;

    if (addr == RESERVED_ADDRESS) {
        return addr;
    }

    for (i = 0;i < n;i++) {
        if ((MMAP_LUT[i].start <= addr) && (addr <= MMAP_LUT[i].end)) {
            return addr - MMAP_LUT[i].start + MMAP_LUT[i].target;
        }
    }

    return addr;
}


