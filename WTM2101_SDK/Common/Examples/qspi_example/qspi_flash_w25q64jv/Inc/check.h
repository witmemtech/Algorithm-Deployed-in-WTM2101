/**
  ******************************************************************************
  * @file    check.h
  * @brief   Header for check.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef _CHECK_H
#define _CHECK_H

#include "stdint.h"

extern uint32_t check_sum32(const void *_data, uint32_t len);
extern uint8_t check_sum(const void * data, uint32_t len);
extern uint16_t check_crc16_modbus(uint8_t *data, uint32_t len);
extern uint16_t crc16check_calc(uint8_t const * p_data, uint32_t size, uint16_t const * p_crc);

#endif
