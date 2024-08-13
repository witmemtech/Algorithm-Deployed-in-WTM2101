/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   The Source Codes for the GPIO Functions
  * @version V1.0.0.1
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "gpio.h"


void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint8_t  tmp_pu = 0x00;
    uint8_t  tmp_pd = 0x00;
    uint32_t pinpos = 0x00;
    uint32_t curpin = 0x00;
    uint32_t pos    = 0x00;
    __IO uint8_t *reg_puctl;
    __IO uint8_t *reg_pdctl;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->Pin));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->Mode));
    assert_param(IS_GPIO_ALT(GPIO_InitStruct->Alternate));

    for (pinpos = 0x00; pinpos < GPIO_NUMBER; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;
        curpin = (GPIO_InitStruct->Pin) & pos;

        if (curpin == pos)
        {
            /* Configure IO Alternate Function */
            if (GPIO_InitStruct->Alternate < 0x04)
            {
                if (pinpos<16)
                {
                    RCC->PMUX_C0 &= ~(RCC_PMUX_C0_PAD0_CFG_Msk << (pinpos * 2));
                    RCC->PMUX_C0 |= GPIO_InitStruct->Alternate << (pinpos * 2);
                }
                else
                {
                    RCC->PMUX_C1 &= ~(RCC_PMUX_C1_PAD16_CFG_Msk << ((pinpos - 16) * 2));
                    RCC->PMUX_C1 |= GPIO_InitStruct->Alternate << ((pinpos - 16) * 2);
                }
            }

            reg_puctl = (pinpos > 7) ? ((pinpos > 15) ? &PMU->RTN_2 : &PMU->RTN_1) : &PMU->RTN_0;
            reg_pdctl = (pinpos > 7) ? ((pinpos > 15) ? &PMU->GPIO_SMT2 : &PMU->GPIO_SMT1) : ((pinpos == 7) ? &PMU->RTN_2 : &PMU->GPIO_SMT0);
            tmp_pu = (uint8_t)(1 << (pinpos % 8));
            tmp_pd = (pinpos == 7) ? 0x10 : tmp_pu;

            /* Configure IO  Input Output Mode */
            switch(GPIO_InitStruct->Mode)
            {
                case GPIO_MODE_IN:
                    GPIOx->DDR &= ~curpin;
                    *reg_pdctl &= ~tmp_pd;
                    *reg_puctl &= ~tmp_pu;
                    break;
                case GPIO_MODE_OUT:
                    GPIOx->DDR |= curpin;
                    *reg_pdctl &= ~tmp_pd;
                    *reg_puctl &= ~tmp_pu;
                    break;
                case GPIO_MODE_INPU:
                    GPIOx->DDR &= ~curpin;
                    *reg_pdctl &= ~tmp_pd;
                    *reg_puctl |= tmp_pu;
                    break;
                case GPIO_MODE_INPD:
                    GPIOx->DDR &= ~curpin;
                    *reg_pdctl |= tmp_pd;
                    *reg_puctl &= ~tmp_pu;
                    break;
                case GPIO_MODE_OUTPU:
                    GPIOx->DDR |= curpin;
                    *reg_pdctl &= ~tmp_pd;
                    *reg_puctl |= tmp_pu;
                    break;
                case GPIO_MODE_OUTPD:
                    GPIOx->DDR |= curpin;
                    *reg_pdctl |= tmp_pd;
                    *reg_puctl &= ~tmp_pu;
                    break;
                default:
                    break;
            }
        }
    }
}

void GPIO_OD_Set(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState NewState)
{
    uint32_t pinpos = 0x00;
    uint32_t curpin = 0x00;
    uint32_t pos = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    for (pinpos = 0x00; pinpos < GPIO_NUMBER; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;
        curpin = GPIO_Pin & pos;

        if (curpin == pos)
        {
            if ((pinpos == 4) || (pinpos == 5))
            {
                (NewState == ENABLE) ? (PMU->GPIO_OD |= 1 << (pinpos - 4)) : (PMU->GPIO_OD &= ~(1 << (pinpos - 4)));
            }
            else if ((pinpos == 12) || (pinpos == 13))
            {
                (NewState == ENABLE) ? (PMU->GPIO_OD |= 1 << (pinpos - 10)) : (PMU->GPIO_OD &= ~(1 << (pinpos - 10)));
            }
        }
    }
}

void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    /* Reset GPIO init structure parameters values */
    GPIO_InitStruct->Pin = GPIO_PIN_All;
    GPIO_InitStruct->Mode = GPIO_MODE_IN;
    GPIO_InitStruct->Alternate = 0;
}

void GPIO_DeInit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    uint32_t pinpos = 0x00;
    uint32_t curpin = 0x00;
    uint32_t pos = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    /* Configure IO  as default GPIO function */
    for (pinpos = 0x00; pinpos < GPIO_NUMBER; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;
        curpin = GPIO_Pin & pos;

        if (curpin == pos)
        {
            GPIOx->DDR &= ~curpin;
            if (pinpos < 16)
            {
                RCC->PMUX_C0 &= ~(RCC_PMUX_C0_PAD0_CFG_Msk << (pinpos * 2));
            }
            else
            {
                RCC->PMUX_C1 &= ~(RCC_PMUX_C1_PAD16_CFG_Msk <<((pinpos - 16) * 2));
            }
        }
    }
}

void GPIO_DebounceCfg(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Configure IO  as default GPIO function */
    if (NewState == ENABLE)
    {
        GPIOx->INTDEB |= GPIO_Pin;
    }
    else
    {
        GPIOx->INTDEB &= ~GPIO_Pin;
    }
}

void GPIO_OutputHi(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->ODR |= GPIO_Pin;
}

void GPIO_OutputLo(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->ODR  &= ~GPIO_Pin;
}

void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->ODR ^= GPIO_Pin;
}

uint32_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));

    return GPIOx->EXT_PORTA;
}

GPIO_PinState GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    GPIO_PinState bitstatus;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    if ((GPIO_ReadInputData(GPIOx) & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
    {
        bitstatus = GPIO_PIN_SET;
    }
    else
    {
        bitstatus = GPIO_PIN_RESET;
    }

    return bitstatus;
}

GPIO_PinState GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    GPIO_PinState bitstatus;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
    {
        bitstatus = GPIO_PIN_SET;
    }
    else
    {
        bitstatus = GPIO_PIN_RESET;
    }

    return bitstatus;
}

uint32_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));

    return GPIOx->ODR;
}

void GPIO_IT_Cfg(GPIO_TypeDef* GPIOx, GPIO_IT_InitTypeDef* GPIO_IT_InitStruct)
{
    uint32_t pin = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_IT_InitStruct->Pin));
    assert_param(IS_GPIO_TRIG(GPIO_IT_InitStruct->Trig));
    assert_param(IS_FUNCTIONAL_STATE(GPIO_IT_InitStruct->State));

    pin = GPIO_IT_InitStruct->Pin;
    /* GPIO interruput trigger Configuration */
    /* Reset Interrupt both edge type */
    if (GPIO_IT_InitStruct->Trig != GPIO_IT_TRIG_RISING_FALLING)
    {
      GPIOx->INTEDG &= ~pin;
    }

    switch (GPIO_IT_InitStruct->Trig)
    {
        case GPIO_IT_TRIG_LOW_LEVEL:
            GPIOx->INTTYP &= ~pin;
            GPIOx->INTPOL &= ~pin;
            break;
        case GPIO_IT_TRIG_HIGH_LEVEL:
            GPIOx->INTTYP &= ~pin;
            GPIOx->INTPOL |= pin;
            break;
        case GPIO_IT_TRIG_RISING:
            GPIOx->INTTYP |= pin;
            GPIOx->INTPOL |= pin;
            break;
        case GPIO_IT_TRIG_FALLING:
            GPIOx->INTTYP |= pin;
            GPIOx->INTPOL &= ~pin;
            break;
        case GPIO_IT_TRIG_RISING_FALLING:
            GPIOx->INTEDG |= pin;
            break;
        default:
            break;
    }
    /* GPIO interruput ENABLE Configuration */
    if (GPIO_IT_InitStruct->State == ENABLE)
    {
        GPIOx->INTEN |= pin;
    }
    else
    {
        GPIOx->INTEN &= ~pin;
    }
}

void GPIO_IT_MskCfg(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        PMU->IE_MSK &= ~PMU_IE_MSK_GPIO_IMSK_Msk;
    }
    else
    {
        PMU->IE_MSK |= PMU_IE_MSK_GPIO_IMSK_Msk;
    }
}

void GPIO_IT_PinMskCfg(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* GPIO interruput mask Configuration */
    if (NewState == ENABLE)
    {
        GPIOx->INTMSK |= GPIO_Pin;
    }
    else
    {
        GPIOx->INTMSK &= ~GPIO_Pin;
    }
}

void GPIO_IT_SyncLvCfg(GPIO_TypeDef* GPIOx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        GPIOx->INTSYNC = 0x01;
    }
    else
    {
        GPIOx->INTSYNC = 0x00;
    }
}

ITStatus GPIO_IT_GetStatBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    if (GPIOx->INTSTA & GPIO_Pin)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

ITStatus GPIO_IT_GetRAWStatBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    if (GPIOx->INTRSTA & GPIO_Pin)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

uint32_t GPIO_IT_GetRAWStat(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));

    return GPIOx->INTRSTA;
}

void GPIO_IT_ClrPending(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->INTCLR |= GPIO_Pin;
}

uint32_t GPIO_IT_GetWakeupStat(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));

    return  GPIOx->WAKEUP;
}

void GPIO_IT_ClrWakeUpPending(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->WAKEUP_EOI |= GPIO_Pin;
}
