/**
  ******************************************************************************
  * @file    sht20.c
  * @brief   The source code of the SHT20 sensor driver.
  * @date    2023-02-10
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "sht20.h"

SHT20_TypeDef sht20;
#ifdef SHT20_USING_I2C_INTERRUPT
volatile uint8_t stop_det_flag = 0;
#endif

#ifdef SHT20_USING_I2C_INTERRUPT
void I2C_IRQHandler(void)
{
    ECLIC_ClearPendingIRQ(I2C_IRQn);
    I2C_IT_ClrStat(I2C, I2C_IT_STOP_DET);
    printf("Stop signal detected on SDA.\r\n");
    stop_det_flag = 0;
}
#endif

void SHT20_init(void)
{
    I2C_InitTypeDef I2C_InitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_CLK_EN_Ctl(RCC_I2C_PCLKEN | RCC_GPIO_HCLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPU;
    GPIO_InitStructure.Alternate = GPIO_AF4_I2C | GPIO_AF5_I2C;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    I2C_InitStruct.Mode = I2C_MODE_MASTER;
    I2C_InitStruct.Speed = I2C_SPEED_FAST;
    I2C_InitStruct.AddrMode = I2C_ADDR_7BITS_MASTER;
    I2C_InitStruct.Restart = I2C_RESTART_ENABLE;
    I2C_InitStruct.Address = (((uint8_t)0x80)>>1) ;
    I2C_InitStruct.Rate = 100000;
    I2C_InitStruct.SpkLen = 1;
    I2C_Init(I2C, &I2C_InitStruct);
}

void SHT20_reset(void)
{
    I2C_IT_ClrStat(I2C, I2C_IT_STOP_DET);
    I2C_IT_ClrStat(I2C, I2C_IT_TX_ABRT);
    I2C_Write_Data(I2C, SHT20_SOFT_RESET);
    while (!I2C_IT_GetRAWStatBit(I2C, I2C_IC_RAW_INTR_STAT_STOP_DET_Msk)) {};
}

void SHT20_value_update(void)
{
    uint16_t reg;

#ifdef SHT20_USING_I2C_INTERRUPT
    stop_det_flag = 1;
#else
    I2C_IT_ClrStat(I2C, I2C_IT_STOP_DET);
    I2C_IT_ClrStat(I2C, I2C_IT_TX_ABRT);
#endif
    ReadBytes(SHT20_Measurement_T_HM, 1, (uint8_t *)&reg, 2);
#ifdef SHT20_USING_I2C_INTERRUPT
    while (stop_det_flag) {}
#else
    while (!I2C_IT_GetRAWStatBit(I2C, I2C_IC_RAW_INTR_STAT_STOP_DET_Msk)) {}
#endif

    sht20.temprature  = reg >> 8;
    sht20.temprature |= reg << 8;

#ifdef SHT20_USING_I2C_INTERRUPT
    stop_det_flag = 1;
#else
    I2C_IT_ClrStat(I2C, I2C_IT_STOP_DET);
    I2C_IT_ClrStat(I2C, I2C_IT_TX_ABRT);
#endif
    ReadBytes(SHT20_Measurement_RH_HM, 1, (uint8_t *)&reg, 2);
#ifdef SHT20_USING_I2C_INTERRUPT
    while (stop_det_flag) {}
#else
    while (!I2C_IT_GetRAWStatBit(I2C, I2C_IC_RAW_INTR_STAT_STOP_DET_Msk)) {}
#endif

    sht20.relative_humidity  = reg >> 8;
    sht20.relative_humidity |= reg << 8;

#ifdef SHT20_USING_I2C_INTERRUPT
    stop_det_flag = 1;
#else
    I2C_IT_ClrStat(I2C, I2C_IT_STOP_DET);
    I2C_IT_ClrStat(I2C, I2C_IT_TX_ABRT);
#endif
    ReadBytes(SHT20_READ_REG, 1, (uint8_t *)&reg, 1);
#ifdef SHT20_USING_I2C_INTERRUPT
    while (stop_det_flag) {}
#else
    while (!I2C_IT_GetRAWStatBit(I2C, I2C_IC_RAW_INTR_STAT_STOP_DET_Msk)) {}
#endif

    sht20.user_register = (uint8_t)reg;

    return;
}


void SHT20_get_user_reg(uint8_t *value)
{
    *value = sht20.user_register;
    return;
}

void SHT20_CalcT_C(float *value)
{
    *value = - 46.85 + 175.72 / 65536 * (float)(sht20.temprature & ~0x3);
    return;
}

void SHT20_CalcRH(float *value)
{
    *value = (((float)(sht20.relative_humidity & ~0x3)) * 0.00190735) - 6;
    return;
}