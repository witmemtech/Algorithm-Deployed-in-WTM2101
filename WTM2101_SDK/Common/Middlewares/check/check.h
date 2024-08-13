#ifndef _CHECK_H
#define _CHECK_H

#ifdef  __cplusplus
extern "C" {
#endif	

#include "stdint.h"

/**
* @brief  Compute the crc32 value with software loop
* @param  p_data: the data buffer 
* @param  size: the data buffer size
* @param  p_crc: the previous or initial crc32 value 
* @retval The result of crc32 value
*/ 
extern	uint32_t crc32_compute(uint8_t const * p_data, uint32_t size, uint32_t const * p_crc);

/**
* @brief  Compute the crc32 value with table look-up
* @param  p_data: the data buffer 
* @param  size: the data buffer size 
* @retval The result of crc32 value
*/ 
extern  uint32_t crc32_compute_table_lookup(uint8_t const *p_data, uint32_t length);

/**
* @brief  Compute the crc16 value with software loop
* @param  p_data: the data buffer 
* @param  size: the data buffer size
* @param  p_crc: the previous or initial crc32 value 
* @retval The result of crc32 value
*/
extern  uint16_t crc16_compute(uint8_t const * p_data, uint32_t size, uint16_t const * p_crc);

/**
* @brief  Compute the checksum value
* @param  data: the data buffer 
* @param  size: the data buffer size 
* @retval The result of checksum value
*/ 
extern  uint32_t check_sum(uint8_t *data,uint32_t size);

#ifdef __cplusplus
}
#endif

#endif  