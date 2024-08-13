/**
  ******************************************************************************
  * @file    check.c 
  * @brief   The Source Codes for the check Functions.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "check.h"

#ifndef CHECK32_SEED    
#define CHECK32_SEED    0X3312A087
#endif


uint32_t check_sum32(const void *_data, uint32_t len)
{
	uint32_t index = 0x00;
	uint32_t sum = CHECK32_SEED;
	uint8_t *data = (uint8_t *)_data;
	if (data == 0 || len == 0x00 || len > 1024 * 1024)
		return 0;

	while (index < len)
	{
		sum += data[index++];
	}
	return sum;
}

uint8_t check_sum(const void * _data, uint32_t len)
{
	int index = 0x00;
	uint8_t sum = 0x00;
	uint8_t *data = (uint8_t *)_data;
	if (data == 0 || len == 0x00 || len > 1024 * 1024)
		return 0;

	while (index < len)
	{
		sum += data[index];
		index++;
	}
	return sum;
}

uint16_t check_crc16_modbus(uint8_t *data, uint32_t len)
{
	uint32_t crc = 0xFFFF;
	uint32_t i, j;
	
	if (data == 0 || len == 0)
		return 0;
	for (j = 0; j < len; j++)
	{
		crc = crc ^*(data + j);
		for (i = 0; i < 8; i++)
		{
			if ((crc & 0x0001) > 0)
			{
				crc = crc >> 1;
				crc = crc ^ 0xa001;
			}
			else
				crc = crc >> 1;
		}
	}
	i = (crc >> 8) & 0xff;
	j = (crc & 0xff) << 8;
	return i | j;
}

uint16_t crc16check_calc(uint8_t const * p_data, uint32_t size, uint16_t const * p_crc)
{
	uint16_t crc = (p_crc == 0) ? 0xFFFF : *p_crc;

	for (uint32_t i = 0; i < size; i++)
	{
		crc = (uint8_t)(crc >> 8) | (crc << 8);
		crc ^= p_data[i];
		crc ^= (uint8_t)(crc & 0xFF) >> 4;
		crc ^= (crc << 8) << 4;
		crc ^= ((crc & 0xFF) << 4) << 1;
	}

	return crc;
}
