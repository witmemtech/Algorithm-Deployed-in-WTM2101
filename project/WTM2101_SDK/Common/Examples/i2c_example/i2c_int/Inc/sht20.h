/**
  ******************************************************************************
  * @file    sht20.h
  * @brief   Header for sht20.c driver.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <stdio.h>
#include "i2c.h"
#include "gpio.h"
#include "rcc.h"

#define SHT20_ADDRESS               0x40
#define SHT20_Measurement_RH_HM     0xE5
#define SHT20_Measurement_T_HM      0xE3
#define SHT20_Measurement_RH_NHM    0xF5
#define SHT20_Measurement_T_NHM     0xF3
#define SHT20_READ_REG              0xE7
#define SHT20_WRITE_REG             0xE6
#define SHT20_SOFT_RESET            0xFE

typedef struct {
    uint16_t temprature;
    uint16_t relative_humidity;
    uint8_t  user_register;
} SHT20_TypeDef;

void SHT20_init(void);
void SHT20_reset(void);
void SHT20_value_update(void);
void SHT20_get_user_reg(uint8_t *value);
void SHT20_CalcT_C(float *value);
void SHT20_CalcRH(float *value);

#define SHT20_USING_I2C_INTERRUPT