/**
  ******************************************************************************  
  * @file    pwm.c
  * @brief   The Source Codes for the PWM Functions
  * @version V1.0.0.0
  * @date    2023-02-07  
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************  
  */

/* Includes */
#include "pwm.h"

void PWM_Init(PWM_TypeDef* PWMx, PWM_InitTypeDef* PWM_InitStruct)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_MODE(PWM_InitStruct->Mode));
    assert_param(IS_PWM_CNTMODE(PWM_InitStruct->CountMode));

    tmpreg |= PWM_InitStruct->Mode;
    tmpreg |= PWM_InitStruct->CountMode;
    tmpreg |= (uint32_t)(PWM_InitStruct->Period << PWM_PWM_CTL_PWM_MAX_VALUE_Pos);
    PWMx->CTL = tmpreg;
}

void PWM_CH_Init(PWM_TypeDef* PWMx, uint32_t PWM_CHx, PWM_CH_InitTypeDef* PWM_CHInitStruct)
{
    uint32_t pos = 0x00, tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_CH(PWM_CHx));
    assert_param(IS_PWM_CHMODE(PWM_CHInitStruct->CH_Mode));
    assert_param(IS_PWM_OUTSIG(PWM_CHInitStruct->OUT_SIG));
    assert_param(IS_PWM_INSIG(PWM_CHInitStruct->IN_SIG));
    assert_param(IS_PWM_INITVAL(PWM_CHInitStruct->Init_Out_Val));
    assert_param(IS_FUNCTIONAL_STATE(PWM_CHInitStruct->CH_En));

    pos = PWM_CHx * 8;
    tmpreg = PWMx->CH_CTL;
    tmpreg &= ~((PWM_PWM_CH_CTL_PWM_0_ONE_SHOT_EN_Msk | PWM_PWM_CH_CTL_PWM_O_0_SW_Msk | \
    PWM_PWM_CH_CTL_PWM_I_0_SW_Msk | PWM_PWM_CH_CTL_PWM_O_0_INIT_Msk | PWM_PWM_CH_CTL_PWM_0_EN_Msk) << pos);

    tmpreg |= ((PWM_CHInitStruct->CH_Mode | PWM_CHInitStruct->OUT_SIG | PWM_CHInitStruct->IN_SIG | PWM_CHInitStruct->Init_Out_Val) << pos);
    if (PWM_CHInitStruct->CH_En == ENABLE)
    {
        tmpreg |= PWM_PWM_CH_CTL_PWM_0_EN_Msk << pos;
    }

    PWMx->CH_CTL = tmpreg;
}

void PWM_CH_SetParam(PWM_TypeDef* PWMx, uint32_t PWM_CHx, PWM_CH_ParamTypeDef* CH_Param)
{
    uint32_t pos = 0x00, tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_CH(PWM_CHx));
    assert_param(IS_PWM_VALUE(CH_Param->Dead_Zone));
    assert_param(IS_PWM_VALUE(CH_Param->Cmp_Val));

    pos = PWM_CHx;
    tmpreg = (uint32_t)CH_Param->Cmp_Val | ((uint32_t)CH_Param->Dead_Zone << PWM_PWM_CH0_INI_PWM_0_DEAD_ZONE_VALUE_Pos);
    *(((uint32_t*)(&(PWMx->CH0_INI))) + pos) = tmpreg;
}

void PWM_CH_GetCapParam(PWM_TypeDef* PWMx, uint32_t PWM_CHx, PWM_CH_CapParamTypeDef* CH_CapParam)
{
    uint32_t pos = 0x00, tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_CH(PWM_CHx));

    pos = PWM_CHx;
    tmpreg = *(((uint32_t*)(&(PWMx->CH0_RB_VAL))) + pos);
    CH_CapParam->HL_Cycle_Num = tmpreg & PWM_PWM_CH0_RB_VAL_PWM_I_0_H_WIDTH_Msk;
    CH_CapParam->Cycle_Num = tmpreg >> PWM_PWM_CH0_RB_VAL_PWM_I_0_CYCLE_Pos;
}

void PWM_IT_MskCtl(PWM_TypeDef* PWMx, uint32_t IT_Msk, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_INT(IT_Msk));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        PWMx->INT_MSK_SET = IT_Msk;
    }
    else
    {
        PWMx->INT_MSK_CLR = IT_Msk;
    }
}

FlagStatus PWM_IT_GetStatBit(PWM_TypeDef* PWMx, uint32_t PWM_IT)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_INT(PWM_IT));

    if ((PWMx->INT_SR_PND & PWM_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

uint32_t PWM_IT_GetStat(PWM_TypeDef* PWMx)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));

    return PWMx->INT_SR_PND;
}

void PWM_IT_ClrStat(PWM_TypeDef* PWMx, uint32_t PWM_IT)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_INT(PWM_IT));

    PWMx->INT_SR_PND &= ~PWM_IT;
}

void PWM_BK_Rel(PWM_TypeDef* PWMx, uint32_t PWM_CHx)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_CH(PWM_CHx));

    PWMx->PUL |= PWM_PWM_PUL_PWM_0_BKIN_RELEASE_Msk << (PWM_CHx << PWM_PWM_PUL_PWM_0_BKIN_RELEASE_Msk);
}

void PWM_Ch_Init_Out_Val_Enable(PWM_TypeDef* PWMx, uint32_t PWM_CHx)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_INSTANCE(PWMx));
    assert_param(IS_PWM_CH(PWM_CHx));

    PWMx->PUL |= PWM_PWM_PUL_PWM_O_0_INIT_PULSE_Msk << (PWM_CHx << PWM_PWM_PUL_PWM_0_BKIN_RELEASE_Msk);
}
