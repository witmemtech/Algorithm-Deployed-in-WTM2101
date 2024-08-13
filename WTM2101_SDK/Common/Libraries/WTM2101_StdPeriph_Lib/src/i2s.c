/**
  ******************************************************************************
  * @file    i2s.c
  * @brief   The Source Codes for the I2S Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "i2s.h"
#include "rcc.h"

void I2S_Mode_Sel(I2S_TypeDef* I2Sx, I2S_Mode Mode)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    if (Mode == I2S_MASTER)
    {
        I2Sx->M_L_SW = I2S_MASTER;
    }
    else if (Mode == I2S_SLAVE)
    {
        I2Sx->M_L_SW = I2S_SLAVE;
    }
}

void I2S_Ctl(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Sx->IER |= I2S_IER_IEN_Msk;
    }
    else
    {
        I2Sx->IER &= ~I2S_IER_IEN_Msk;
    }
}

I2S_Set_State I2S_SplRate_Set(I2S_TypeDef* I2Sx, uint16_t Rate)
{
    I2S_Set_State res = I2S_SET_OK;
    uint32_t temp = 0,tmpclk = 0;
    uint8_t num = 0;

    tmpclk = RCC_Get_SYSClk();
    temp = RCC_AHB_Get_ClkDiv() + 1;
    tmpclk = tmpclk / temp;

    if ((I2Sx->CCR&I2S_CCR_WSS_Msk) == I2S_SCLKNUM_16)
    {
        num = 32;
    }
    else if ((I2Sx->CCR&I2S_CCR_WSS_Msk) == I2S_SCLKNUM_24)
    {
        num = 48;
    }
    else if ((I2Sx->CCR&I2S_CCR_WSS_Msk) == I2S_SCLKNUM_32)
    {
        num = 64;
    }
    else
    {
        res = I2S_SET_ERROR;
        return res;
    }
    if (tmpclk >= num * Rate)
    {
        temp = (tmpclk * 10 / num / Rate + 5) / 10 - 1;
        if (temp > 4096)
        {
            res = I2S_SET_ERROR;
            return res;
        }
    }
    else
    {
        res = I2S_SET_ERROR;
        return res;
    }
    if (I2Sx == I2S0)
    {
        RCC_I2S0_Set_ClkDiv(temp);
    }
    else if (I2Sx == I2S1)
    {
        RCC_I2S1_Set_ClkDiv(temp);
    }
    else
    {
        res = I2S_SET_ERROR;
    }
    return res;
}

void I2S_RxBlkCtl(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Sx->IRER |= I2S_IRER_RXEN_Msk;
    }
    else
    {
        I2Sx->IRER &= ~I2S_IRER_RXEN_Msk;
    }
}

void I2S_TxBlkCtl(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Sx->ITER |= I2S_ITER_TXEN_Msk;
    }
    else
    {
        I2Sx->ITER &= ~I2S_ITER_TXEN_Msk;
    }
}

void I2S_ClkCtl(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Sx->CER |= I2S_CER_CLKEN_Msk;
    }
    else
    {
        I2Sx->CER &= ~I2S_CER_CLKEN_Msk;
    }
}

void I2S_ClkCfg(I2S_TypeDef* I2Sx, uint32_t SclkNum, uint32_t SclkGate)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_SCLKNUM(SclkNum));
    assert_param(IS_I2S_GATESCLKNUM(SclkGate));

    tmpreg = I2Sx->CER;
    I2Sx->CER = (0U << I2S_CER_CLKEN_Pos);
    I2Sx->CCR &= ~(I2S_CCR_WSS_Msk | I2S_CCR_SCLKG_Msk);
    I2Sx->CCR |= SclkNum;
    I2Sx->CCR |= SclkGate;
    I2Sx->CER = tmpreg;
}

void I2S_RxBlk_FIFO_Rst(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    I2Sx->RXFFR = I2S_RXFFR_RXFFR_Msk;
}

void I2S_TxBlk_FIFO_Rst(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    I2Sx->TXFFR = I2S_TXFFR_TXFFR_Msk;
}

void I2S_RxChlCtl(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Sx->RER |= I2S_RER0_RXCHEN0_Msk;
    }
    else
    {
        I2Sx->RER &= ~I2S_RER0_RXCHEN0_Msk;
    }
}

void I2S_TxChlCtl(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Sx->TER |= I2S_TER0_TXCHEN0_Msk;
    }
    else
    {
        I2Sx->TER &= ~I2S_TER0_TXCHEN0_Msk;
    }
}

void I2S_RxCfg(I2S_TypeDef* I2Sx, uint32_t ResLen)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_RESLEN(ResLen));

    I2Sx->RCR = ResLen;
}

void I2S_TxCfg(I2S_TypeDef* I2Sx, uint32_t ResLen)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_RESLEN(ResLen));

    I2Sx->TCR = ResLen;
}

ITStatus I2S_IT_GetStatBit(I2S_TypeDef* I2Sx, uint32_t I2S_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_INT(I2S_IT));

    if (I2Sx->ISR&I2S_IT)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

uint32_t I2S_IT_GetStat(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    return I2Sx->ISR;
}

void I2S_IT_MskCtl(I2S_TypeDef* I2Sx, uint32_t IT_Msk, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_INT(IT_Msk));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        I2Sx->IMR |= IT_Msk;
    }
    else
    {
        I2Sx->IMR &= ~IT_Msk;
    }
}

void I2S_IT_RORClr(I2S_TypeDef* I2Sx)
{
    uint32_t temp;
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    temp = I2Sx->ROR;
}

void I2S_IT_TORClr(I2S_TypeDef* I2Sx)
{
    uint32_t temp;
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    temp = I2Sx->TOR;
}

void I2S_RxFIFO_LVLCfg(I2S_TypeDef* I2Sx, uint8_t Level)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_TRIGLVL(Level));

    I2Sx->RFCR = Level;
}

void I2S_TxFIFO_LVLCfg(I2S_TypeDef* I2Sx, uint8_t Level)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_TRIGLVL(Level));

    I2Sx->TFCR = Level;
}

void I2S_RxFIFO_Flush(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    I2Sx->RFF = I2S_RFF0_RXCHFR_Msk;
}

void I2S_TxFIFO_Flush(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    I2Sx->TFF = I2S_TFF0_TXCHFR_Msk;
}

void I2S_RxBlk_DMA_Rst(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    I2Sx->RRXDMA = I2S_RRXDMA_RRXDMA_Msk;
}

void I2S_TxBlk_DMA_Rst(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));

    I2Sx->RTXDMA = I2S_RTXDMA_RTXDMA_Msk;
}

void I2S_TransmitData(I2S_TypeDef *I2Sx, uint32_t *pData, uint32_t Size)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_EVENNUM(Size));

    while ((Size > 1) && (Size % 2 == 0))
    {
        I2Sx->LRBR_LTHR = *pData;
        pData++;
        Size--;
        I2Sx->RRBR_RTHR = *pData;
        pData++;
        Size--;
    }
}

void I2S_ReceiveData(I2S_TypeDef *I2Sx, uint32_t *pData, uint32_t Size)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_INSTANCE(I2Sx));
    assert_param(IS_I2S_EVENNUM(Size));

    while ((Size > 1) && (Size % 2 == 0))
    {
        *pData = I2Sx->LRBR_LTHR;
        pData++;
        Size--;
        *pData = I2Sx->RRBR_RTHR;
        pData++;
        Size--;
    }
}
