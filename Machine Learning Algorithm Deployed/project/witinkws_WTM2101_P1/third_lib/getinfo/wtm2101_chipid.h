#ifndef _WTM2101_CHIPID_H_
#define _WTM2101_CHIPID_H_


#include "stdint.h"
#include "stdio.h"


typedef struct {
    uint64_t chipid;
    uint8_t tag_len;
    uint8_t tag[15];
    uint8_t name[8];
    uint8_t bootloader_name[8];
}wtm2101_chipinfo;

int get_wtm2101_chipinfo(uint16_t *trim_buffer, wtm2101_chipinfo *chipinfo);

#endif