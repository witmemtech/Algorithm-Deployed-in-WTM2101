#ifndef _CRC32_H
#define _CRC32_H

#ifdef  __cplusplus
extern "C" {
#endif	

#include "stdint.h"

#define INIT_FLAG 0xa5c8f2d7
#define CALIBRATION_METHOD 2

#pragma pack(push)
#pragma pack(1)
typedef  struct Check_head
{
    int init_flag;
    int calibration_method;
    int calibration_result_value;
    int raw_file_size;
}Check_head; 
#pragma pack(pop) 

extern  uint32_t crc32_compute_table_lookup(uint8_t const *p_data, uint32_t length);
extern	uint32_t crc32_compute(uint8_t const * p_data, uint32_t size, uint32_t const * p_crc);
extern  uint32_t check_sum(uint8_t *data,uint32_t size);

#ifdef __cplusplus
}
#endif

#endif  