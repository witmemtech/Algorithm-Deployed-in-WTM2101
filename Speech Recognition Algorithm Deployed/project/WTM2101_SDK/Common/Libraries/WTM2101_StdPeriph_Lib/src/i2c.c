/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   The Source Codes for the I2C Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "i2c.h"
#include "rcc.h"

static uint32_t i2c_timeout_period = 0xFFF0;

I2C_Set_State I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
    I2C_Set_State res = I2C_SET_OK;
    uint32_t temp = 0x00,tmpclk = 0x00;
    uint32_t numclk = 0x00;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_MODE(I2C_InitStruct->Mode));
    assert_param(IS_I2C_SPEED(I2C_InitStruct->Speed));
    assert_param(IS_I2C_ADDRMODE(I2C_InitStruct->AddrMode));
    assert_param(IS_I2C_ADDR(I2C_InitStruct->Address));
    assert_param(IS_I2C_RST(I2C_InitStruct->Restart));

    tmpclk = RCC_Get_SYSClk();
    temp = RCC_AHB_Get_ClkDiv() + 1;
    tmpclk = tmpclk / temp;
    I2C_Ctl(I2Cx,DISABLE);
    I2Cx->CON = I2C_InitStruct->Mode | I2C_InitStruct->Speed | I2C_InitStruct->Restart;
    if (I2C_InitStruct->Mode == I2C_MODE_MASTER)
    {
        I2Cx->TAR &= ~(I2C_IC_TAR_IC_10BITADDR_MASTER_Msk | I2C_IC_TAR_IC_TAR_Msk);
        I2Cx->TAR |= I2C_InitStruct->AddrMode;
        I2Cx->TAR |= I2C_InitStruct->Address;
        if (tmpclk > 12288000)
        {
            I2C_InitStruct->Rate = I2C_InitStruct->Rate + (I2C_InitStruct->Rate * 15 / 1000) * I2C_InitStruct->Rate / 100000;
        }
        else
        {
            I2C_InitStruct->Rate = I2C_InitStruct->Rate + (I2C_InitStruct->Rate * 10 / 1000) * I2C_InitStruct->Rate / 100000;
        }
        temp = (tmpclk * 10 / I2C_InitStruct->Rate + 5) / 10;
        if (temp >= (3 * I2C_InitStruct->SpkLen + 22))
        {
            numclk = temp - 8 - I2C_InitStruct->SpkLen;
            if (numclk > 131070)
            {
                res = I2C_SET_ERROR;
                return res;
            }
            if ((numclk / 2) > (I2C_InitStruct->SpkLen + 7))
            {
                temp = numclk / 2;
            }
            else
            {
                temp = I2C_InitStruct->SpkLen + 8;
            }
            if (I2C_InitStruct->Speed == I2C_SPEED_STD)
            {
                I2C_Set_SS_HCNT(I2Cx,temp);
                I2C_Set_SS_LCNT(I2Cx,numclk - temp);
            }
            else if (I2C_InitStruct->Speed == I2C_SPEED_FAST)
            {
                I2C_Set_FS_HCNT(I2Cx,temp);
                I2C_Set_FS_LCNT(I2Cx,numclk - temp);
            }
            I2C_Set_FS_SPKLEN(I2Cx,I2C_InitStruct->SpkLen);
            I2C_Set_SDA_RX_HOLD(I2Cx,3);
            I2C_Set_SDA_TX_HOLD(I2Cx,6);
            I2C_Ctl(I2Cx,ENABLE);
        }
        else
        {
            res = I2C_SET_ERROR;
        }
    }
    else if (I2C_InitStruct->Mode == I2C_MODE_SLAVE)
    {
        I2Cx->CON &= ~I2C_IC_CON_IC_10BITADDR_SLAVE_Msk;
        I2Cx->CON |= I2C_InitStruct->AddrMode;
        I2Cx->SAR = I2C_InitStruct->Address;
    }
    return res;
}

void I2C_TarAddr_Set(I2C_TypeDef* I2Cx, uint32_t Addr)
{
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_ADDR(Addr));

    I2Cx->TAR &= ~I2C_IC_TAR_IC_TAR_Msk;
    I2Cx->TAR |= Addr&I2C_IC_TAR_IC_TAR_Msk;
}

void I2C_TimeOutPeriod_Set(uint32_t Time)
{
    assert_param(IS_I2C_TIMEOUT(Time));

    i2c_timeout_period = Time;
    return;
}

void I2C_Ctl(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->ENABLE |= I2C_IC_ENABLE_ENABLE_Msk;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->ENABLE &= ~I2C_IC_ENABLE_ENABLE_Msk;
    }
}

void I2C_TX_EmptyCtl(I2C_TypeDef* I2Cx, uint32_t Mode)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_TX_EMPTY_MODE(Mode));

    I2Cx->CON &= ~I2C_IC_CON_TX_EMPTY_CTR_Msk;
    I2Cx->CON |= Mode;
}

void I2C_Ack_GenCallCtl(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Cx->ACK_GEN_CALL |= I2C_IC_ACK_GENERAL_CALL_ACK_GEN_CALL_Msk;
    }
    else
    {
        I2Cx->ACK_GEN_CALL &= ~I2C_IC_ACK_GENERAL_CALL_ACK_GEN_CALL_Msk;
    }
}

void I2C_DMACtl(I2C_TypeDef* I2Cx, uint32_t DMADir, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_DMADIR(DMADir));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Cx->DMA_CR |= DMADir;
    }
    else
    {
        I2Cx->DMA_CR &= ~DMADir;
    }
}

void I2C_IT_MskCtl(I2C_TypeDef* I2Cx, uint32_t IT_Msk, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_INT(IT_Msk));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Cx->INTR_MSK &= ~IT_Msk;    /*!< active low! */
    }
    else
    {
        I2Cx->INTR_MSK |= IT_Msk;
    }
}

uint32_t I2C_IT_ReadMsk(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    return I2Cx->INTR_MSK;
}

void I2C_Set_SS_HCNT(I2C_TypeDef* I2Cx, uint16_t HCNT)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->SS_SCL_HCNT = HCNT;
}

void I2C_Set_SS_LCNT(I2C_TypeDef* I2Cx, uint16_t LCNT)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->SS_SCL_LCNT = LCNT;
}

void I2C_Set_FS_HCNT(I2C_TypeDef* I2Cx, uint16_t HCNT)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->FS_SCL_HCNT = HCNT;
}

void I2C_Set_FS_LCNT(I2C_TypeDef* I2Cx, uint16_t LCNT)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->FS_SCL_LCNT = LCNT;
}

void I2C_Set_RX_TL(I2C_TypeDef* I2Cx, uint8_t RxTL)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->RX_TL = RxTL;
}

void I2C_Set_TX_TL(I2C_TypeDef* I2Cx, uint8_t TxTL)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->TX_TL = TxTL;
}

void I2C_Set_FS_SPKLEN(I2C_TypeDef* I2Cx, uint8_t Spklen)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->FS_SPKLEN = Spklen;
}

void I2C_Set_SDA_RX_HOLD(I2C_TypeDef* I2Cx, uint8_t HoldTime)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    tmpreg = I2Cx->SDA_HOLD&I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_Msk;
    tmpreg |= (HoldTime << I2C_IC_SDA_HOLD_IC_SDA_RX_HOLD_Pos);
    I2Cx->SDA_HOLD = tmpreg;
}

void I2C_Set_SDA_TX_HOLD(I2C_TypeDef* I2Cx, uint16_t HoldTime)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    tmpreg = I2Cx->SDA_HOLD&I2C_IC_SDA_HOLD_IC_SDA_RX_HOLD_Msk;
    tmpreg |= HoldTime;
    I2Cx->SDA_HOLD = tmpreg;
}

void I2C_Set_DMA_TDLR(I2C_TypeDef* I2Cx, uint8_t Level)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->DMA_TDLR = Level&I2C_IC_DMA_TDLR_DMATDL_Msk;
}

void I2C_Set_DMA_RDLR(I2C_TypeDef* I2Cx, uint8_t Level)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->DMA_RDLR = Level&I2C_IC_DMA_RDLR_DMARDL_Msk;
}

void I2C_Write_Cmd(I2C_TypeDef* I2Cx, uint8_t Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->DATA_CMD = (uint16_t)Cmd;
}

void I2C_Read_Cmd(I2C_TypeDef* I2Cx, uint8_t Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->DATA_CMD = (uint16_t)Cmd | I2C_IC_DATA_CMD_CMD_Msk;
}

void I2C_Write_Data(I2C_TypeDef* I2Cx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    I2Cx->DATA_CMD = (uint16_t)Data;
}

uint8_t I2C_Read_Data(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    return (uint8_t)I2C->DATA_CMD;
}

ITStatus I2C_IT_GetStatBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_INT(I2C_IT));

    if (I2Cx->INTR_STAT & I2C_IT)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

ITStatus I2C_IT_GetRAWStatBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_INT(I2C_IT));

    if (I2Cx->RAW_INTR_STAT & I2C_IT)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

uint32_t I2C_IT_GetRAWStat(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    return  I2Cx->RAW_INTR_STAT;
}

ITStatus I2C_Flag_GetStatBit(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_FLAG(I2C_FLAG));

    if ((I2Cx->STAT & I2C_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

uint32_t I2C_Flag_GetStat(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    return I2Cx->STAT;
}

uint8_t I2C_GetTXFlr(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    return I2Cx->TXFLR & I2C_IC_TXFLR_TXFLR_Msk;           /*!< TX_ABW = 3 */
}

uint8_t I2C_GetRXFlr(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    return I2Cx->RXFLR & I2C_IC_RXFLR_RXFLR_Msk;           /*!< RX_ABW = 3 */
}

uint32_t I2C_GetTXABRT_Src(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));

    return  I2Cx->TX_ABRT_SRC;
}

void I2C_IT_ClrStat(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_INSTANCE(I2Cx));
    assert_param(IS_I2C_INT(I2C_IT));

    switch (I2C_IT)
    {
        case I2C_IT_RX_UNDER:
            tmpreg = I2Cx->CLR_RX_UNDER;
            break;
        case I2C_IT_RX_OVER:
            tmpreg = I2Cx->CLR_RX_OVER;
            break;
        case I2C_IT_TX_OVER:
            tmpreg = I2Cx->CLR_TX_OVER;
            break;
        case I2C_IT_RD_REQ:
            tmpreg = I2Cx->CLR_RD_REQ;
            break;
        case I2C_IT_TX_ABRT:
            tmpreg = I2Cx->CLR_TX_ABRT;
            break;
        case I2C_IT_RX_DONE:
            tmpreg = I2Cx->CLR_RX_DONE;
            break;
        case I2C_IT_ACT:
            tmpreg = I2Cx->CLR_ACTIVITY;
            break;
        case I2C_IT_STOP_DET:
            tmpreg = I2Cx->CLR_STOP_DET;
            break;
        case I2C_IT_START_DET:
            tmpreg = I2Cx->CLR_START_DET;
            break;
        case I2C_IT_GEN_CALL:
            tmpreg = I2Cx->CLR_GEN_CALL;
            break;
        case I2C_IT_ALL:
            tmpreg = I2Cx->CLR_INTR;
            break;
        default:
            break;
    }
    tmpreg = tmpreg;       /*!< avoid warning */
}

I2C_State WriteByte(uint16_t addr, uint8_t addr_byte_num, uint8_t data)
{
    uint32_t tim_cnt = 0;

    /* releases the Tx FIFO from the flushed/reset state */
    I2C_IT_ClrStat(I2C,I2C_IT_TX_ABRT);

    if (addr_byte_num == 1)
    {
        I2C_Write_Data(I2C,addr & 0xFF);
    }
    else if (addr_byte_num == 2)
    {
        I2C_Write_Data(I2C,addr & 0xFF);
        I2C_Write_Data(I2C,(addr >> 8) & 0xFF);
    }
    else
    {
        return I2C_ADDR_BYTE_NUM_ERROR;
    }

    I2C_Write_Data(I2C,data);
    while ((I2C_Flag_GetStatBit(I2C,I2C_FLAG_TFE) == RESET) && (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == RESET) && (tim_cnt < i2c_timeout_period))
    {
        tim_cnt++;
    }

    if (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == SET)
    {
        return I2C_TX_ABORT_ERROR;
    }

    if (tim_cnt >= i2c_timeout_period)
    {
        return I2C_TIMEOUT_ERROR;
    }
    else
    {
        return I2C_OK;
    }
}

I2C_State WriteBytes(uint16_t addr, uint8_t addr_byte_num, uint8_t *buffer, uint16_t num)
{
    uint16_t i,cnt = 0;
    uint16_t cnt_temp;
    uint32_t tim_cnt = 0;

    /* releases the Tx FIFO from the flushed/reset state */
    I2C_IT_ClrStat(I2C,I2C_IT_TX_ABRT);

    if (addr_byte_num == 1)
    {
        I2C_Write_Data(I2C,addr & 0xFF);
    }
    else if (addr_byte_num == 2)
    {
        I2C_Write_Data(I2C,addr & 0xFF);
        I2C_Write_Data(I2C,(addr >> 8) & 0xFF);
    }
    else
    {
        return I2C_ADDR_BYTE_NUM_ERROR;
    }

    cnt_temp = num / 4;

    for (i = 0;i < cnt_temp;i++)
    {
        while ((I2C_GetTXFlr(I2C) >= 3) && (tim_cnt < i2c_timeout_period))
        {
            if (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == SET)
            {
                return I2C_TX_ABORT_ERROR;
            }
            tim_cnt++;
        }
        if (tim_cnt >= i2c_timeout_period)
        {
            return I2C_TIMEOUT_ERROR;
        }
        I2C_Write_Data(I2C,*(buffer+cnt));
        cnt++;
        I2C_Write_Data(I2C,*(buffer+cnt));
        cnt++;
        I2C_Write_Data(I2C,*(buffer+cnt));
        cnt++;
        I2C_Write_Data(I2C,*(buffer+cnt));
        cnt++;
        tim_cnt = 0;
    }

    cnt_temp = num % 4;

    for (i = 0;i < cnt_temp; i++)
    {
        while ((I2C_GetTXFlr(I2C) >= 3) && (tim_cnt < i2c_timeout_period))
        {
            tim_cnt++;
        }
        if (tim_cnt >= i2c_timeout_period)
        {
            return I2C_TIMEOUT_ERROR;
        }
        I2C_Write_Data(I2C,*(buffer+cnt));
        cnt++;
        tim_cnt = 0;
    }

    while ((I2C_Flag_GetStatBit(I2C,I2C_FLAG_TFE) == RESET) && (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == RESET) && (tim_cnt < i2c_timeout_period))
    {
        tim_cnt++;
    }

    if (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == SET)
    {
        return I2C_TX_ABORT_ERROR;
    }

    if (tim_cnt >= i2c_timeout_period)
    {
        return I2C_TIMEOUT_ERROR;
    }
    else
    {
        return I2C_OK;
    }
}

I2C_State ReadByte(uint16_t addr, uint8_t addr_byte_num, uint8_t *recv)
{
    uint32_t tim_cnt = 0;

    /* releases the Tx FIFO from the flushed/reset state */
    I2C_IT_ClrStat(I2C,I2C_IT_TX_ABRT);

    if (addr_byte_num == 1)
    {
        I2C_Write_Data(I2C,addr & 0xFF);
    }
    else if (addr_byte_num == 2)
    {
        I2C_Write_Data(I2C,addr & 0xFF);
        I2C_Write_Data(I2C,(addr >> 8) & 0xFF);
    }
    else
    {
        return I2C_ADDR_BYTE_NUM_ERROR;
    }

    I2C_Read_Cmd(I2C,0);

    while ((I2C_Flag_GetStatBit(I2C,I2C_FLAG_RFNE) == RESET) && (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == RESET) && (tim_cnt < i2c_timeout_period))
    {
        tim_cnt++;
    }

    if (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == SET)
    {
        return I2C_TX_ABORT_ERROR;
    }

    if (tim_cnt >= i2c_timeout_period)
    {
        return I2C_TIMEOUT_ERROR;
    }
    else
    {
        *recv = I2C_Read_Data(I2C);
        return I2C_OK;
    }
}

I2C_State ReadBytes(uint16_t addr, uint8_t addr_byte_num, uint8_t *recv, uint16_t num)
{
    uint16_t i,cnt = 0;
    uint16_t cnt_temp;
    uint32_t tim_cnt = 0;

    /* releases the Tx FIFO from the flushed/reset state */
    I2C_IT_ClrStat(I2C,I2C_IT_TX_ABRT);

    if (addr_byte_num == 1)
    {
        I2C_Write_Data(I2C,addr & 0xFF);
    }
    else if (addr_byte_num == 2)
    {
        I2C_Write_Data(I2C,addr & 0xFF);
        I2C_Write_Data(I2C,(addr >> 8) & 0xFF);
    }
    else
    {
        return I2C_ADDR_BYTE_NUM_ERROR;
    }

    cnt_temp = num / 4;

    for (i = 0;i < cnt_temp;i++)
    {
        while ((I2C_GetTXFlr(I2C) >= 3) && (tim_cnt < i2c_timeout_period))
        {
            if (I2C_Flag_GetStatBit(I2C,I2C_FLAG_RFNE) == SET)
            {
                *recv = I2C_Read_Data(I2C);
                recv++;
                cnt++;
            }
            if (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == SET)
            {
                return I2C_TX_ABORT_ERROR;
            }
            tim_cnt++;
        }
        if (tim_cnt >= i2c_timeout_period)
        {
            return I2C_TIMEOUT_ERROR;
        }

        I2C_Read_Cmd(I2C,0);
        I2C_Read_Cmd(I2C,0);
        I2C_Read_Cmd(I2C,0);
        I2C_Read_Cmd(I2C,0);
        tim_cnt = 0;
    }

    cnt_temp = num % 4;

    for (i = 0;i < cnt_temp; i++)
    {
        while ((I2C_GetTXFlr(I2C) >= 3) && (tim_cnt < i2c_timeout_period))
        {
            if (I2C_Flag_GetStatBit(I2C,I2C_FLAG_RFNE) == SET)
            {
                *recv = I2C_Read_Data(I2C);
                recv++;
                cnt++;
            }
            tim_cnt++;
        }
        if (tim_cnt >= i2c_timeout_period)
        {
            return I2C_TIMEOUT_ERROR;
        }
        I2C_Read_Cmd(I2C,0);
        tim_cnt = 0;
    }

    while ((cnt != num) && (tim_cnt < i2c_timeout_period))
    {
        if (I2C_Flag_GetStatBit(I2C,I2C_FLAG_RFNE) == SET)
        {
            *recv = I2C_Read_Data(I2C);
            recv++;
            cnt++;
        }
        if (I2C_IT_GetRAWStatBit(I2C,I2C_IT_TX_ABRT) == SET)
        {
            return I2C_TX_ABORT_ERROR;
        }
        tim_cnt++;
    }

    if (tim_cnt >= i2c_timeout_period)
    {
        return I2C_TIMEOUT_ERROR;
    }
    else
    {
        return I2C_OK;
    }
}
