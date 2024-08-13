/**
  ******************************************************************************
  * @file    uart.c
  * @brief   The Source Codes for the UART Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "uart.h"
#include "rcc.h"

void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
    uint32_t tmpreg = 0x00;
    uint32_t tmpclk = 0x00;
    uint32_t temp = 0;

    /* Check the parameters */
    assert_param(IS_UART_ALL_INSTANCE(UARTx));
    assert_param(IS_UART_WORDLEN(UART_InitStruct->WordLength));
    assert_param(IS_UART_STOPBIT(UART_InitStruct->StopBits));
    assert_param(IS_UART_PARITY(UART_InitStruct->Parity));
    assert_param(IS_UART_MODE(UART_InitStruct->Mode));
    assert_param(IS_FUNCTIONAL_STATE(UART_InitStruct->FIFOCtl));

    tmpclk = RCC_Get_SYSClk();
    temp = RCC_AHB_Get_ClkDiv() + 1;
    tmpclk = tmpclk / temp;
    tmpreg = 10 * tmpclk / (16 * UART_InitStruct->BaudRate);
    tmpreg = (tmpreg + 5) / 10;

    UARTx->LCR |= UART_LCR_DLAB_Msk;
    UARTx->IER_DLH = (uint8_t)(tmpreg >> 8);
    UARTx->DR_DLL = (uint8_t)tmpreg;
    UARTx->LCR &= ~UART_LCR_DLAB_Msk;

    tmpreg = UARTx->LCR & (UART_LCR_DLAB_Msk | UART_LCR_BREAK_Msk);
    tmpreg |= UART_InitStruct->WordLength;
    tmpreg |= UART_InitStruct->StopBits;
    tmpreg |= UART_InitStruct->Parity;

    UARTx->LCR = tmpreg;
    UARTx->MCR &= ~UART_MCR_LB_Msk;
    UARTx->MCR |= UART_InitStruct->Mode;

    if (UART_InitStruct->FIFOCtl == ENABLE)
    {
        UARTx->IIR_FCR = UART_FCR_FIFOE_Msk | UART_FCR_DMAM_Msk;
    }
    else
    {
        UARTx->IIR_FCR = 0;
    }
}

void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
    UART_InitStruct->BaudRate = 115200;
    UART_InitStruct->Parity = UART_PARITY_NONE;
    UART_InitStruct->StopBits = UART_STOPBITS_1;
    UART_InitStruct->WordLength = UART_WORDLENGTH_8B;
    UART_InitStruct->Mode = UART_MODE_UART;
    UART_InitStruct->FIFOCtl = DISABLE;
}

void UART_SendData(UART_TypeDef* UARTx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_INSTANCE(UARTx));

  UARTx->DR_DLL = Data;
}

uint8_t UART_ReceiveData(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_INSTANCE(UARTx));

  return (uint8_t)UARTx->DR_DLL;
}

void UART_IT_Cfg(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_INSTANCE(UARTx));
    assert_param(IS_UART_INT(UART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    UARTx->LCR &= ~UART_LCR_DLAB_Msk;

    if (NewState == ENABLE)
    {
        UARTx->IER_DLH |= UART_IT;
    }
    else
    {
        UARTx->IER_DLH &= ~UART_IT;
    }
}

UART_IT_TypeDef UART_IT_GetStat(UART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_INSTANCE(UARTx));

    return (UART_IT_TypeDef)(UARTx->IIR_FCR & UART_IIR_IID_Msk);
}

FlagStatus UART_Flag_GetStatBit(UART_TypeDef* UARTx, uint32_t UART_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_UART_ALL_INSTANCE(UARTx));
    assert_param(IS_UART_FLAG(UART_FLAG));

    if (UARTx->LSR & UART_FLAG)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

uint32_t UART_Flag_GetStat(UART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_INSTANCE(UARTx));

    return UARTx->LSR;
}

void UART_Flag_Clr(UART_TypeDef* UARTx)
{
    uint8_t temp;

    /* Check the parameters */
    assert_param(IS_UART_ALL_INSTANCE(UARTx));

    /* Read LSR Register to clear flags */
    temp = UARTx->LSR;
}

FlagStatus UART_Flag_GetFIFOStatus(UART_TypeDef* UARTx)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_UART_ALL_INSTANCE(UARTx));

    if(UARTx->IIR_FCR & UART_IIR_FIFOSE_Msk)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void UART_RxFIFO_LevelCfg(UART_TypeDef* UARTx, uint32_t FIFO_Level)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_UART_ALL_INSTANCE(UARTx));
    assert_param(IS_UART_FIFOLVL(FIFO_Level));

    tmpreg = FIFO_Level | UART_FCR_FIFOE_Msk;
    UARTx->IIR_FCR = tmpreg;
}
