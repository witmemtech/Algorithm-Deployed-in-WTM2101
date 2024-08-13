/**
  ******************************************************************************
  * @file    afc.c
  * @brief   The Source Codes for the AFC Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "afc.h"

uint16_t AFC_Get_Test_Time(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return (afc->CORE_CTRL & AFC_24M_CORE_CTRL_TEST_TIME_Msk);
    }
    else if(afc == AFC320k)
    {
        return (afc->CORE_CTRL & AFC_320K_CORE_CTRL_TEST_TIME_Msk);
    }
}

void AFC_Set_Test_Time(AFC_TypeDef *afc, uint16_t value)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        afc->CORE_CTRL &= ~AFC_24M_CORE_CTRL_TEST_TIME_Msk;
        afc->CORE_CTRL |= (value << AFC_24M_CORE_CTRL_TEST_TIME_Pos);
    }
    else if (afc == AFC320k)
    {
        afc->CORE_CTRL &= ~AFC_320K_CORE_CTRL_TEST_TIME_Msk;
        afc->CORE_CTRL |= (value << AFC_320K_CORE_CTRL_TEST_TIME_Pos);
    }
}

uint16_t AFC_Get_Frequency_Target(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return ((afc->CORE_CTRL & AFC_24M_CORE_CTRL_FRE_TARGET_Msk) >> AFC_24M_CORE_CTRL_FRE_TARGET_Pos);
    }
    else if (afc == AFC320k)
    {
        return ((afc->CORE_CTRL & AFC_320K_CORE_CTRL_FRE_TARGET_Msk) >> AFC_320K_CORE_CTRL_FRE_TARGET_Pos);
    }
}

void AFC_Set_Frequency_Target(AFC_TypeDef *afc, uint16_t value)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        afc->CORE_CTRL &= ~AFC_24M_CORE_CTRL_FRE_TARGET_Msk;
        afc->CORE_CTRL |= (value << AFC_24M_CORE_CTRL_FRE_TARGET_Pos);
    }
    else if (afc == AFC320k)
    {
        afc->CORE_CTRL &= ~AFC_320K_CORE_CTRL_FRE_TARGET_Msk;
        afc->CORE_CTRL |= (value << AFC_320K_CORE_CTRL_FRE_TARGET_Pos);
    }
}

void AFC_Set_Enable_Cmd(AFC_TypeDef *afc, FunctionalState newstatus)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        if (newstatus)
        {
            afc->CORE_EN = AFC_24M_CORE_EN_WORK_EN_Msk;
        }
        else
        {
            afc->CORE_EN = ~AFC_24M_CORE_EN_WORK_EN_Msk;
        }
    }
    else if (afc == AFC320k)
    {
        if (newstatus)
        {
            afc->CORE_EN = AFC_320K_CORE_EN_WORK_EN_Msk;
        }
        else
        {
            afc->CORE_EN = ~AFC_320K_CORE_EN_WORK_EN_Msk;
        }
    }
}

void AFC_Set_Divison_Result(AFC_TypeDef *afc, uint16_t value)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        afc->OP_RESULT &= ~AFC_24M_OP_RESULT_INT_VALUE_Msk;
        afc->OP_RESULT |= (value << AFC_24M_OP_RESULT_INT_VALUE_Pos);
    }
    else if (afc == AFC320k)
    {
        afc->OP_RESULT &= ~AFC_320K_OP_RESULT_INT_VALUE_Msk;
        afc->OP_RESULT |= (value << AFC_320K_OP_RESULT_INT_VALUE_Pos);
    }
}

void AFC_Set_Remain_Value(AFC_TypeDef *afc, uint16_t value)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        afc->OP_RESULT &= ~AFC_24M_OP_RESULT_REMAIN_VALUE_Msk;
        afc->OP_RESULT |= (value << AFC_24M_OP_RESULT_REMAIN_VALUE_Pos);
    }
    else if (afc == AFC320k)
    {
        afc->OP_RESULT &= ~AFC_320K_OP_RESULT_REMAIN_VALUE_Msk;
        afc->OP_RESULT |= (value << AFC_320K_OP_RESULT_REMAIN_VALUE_Pos);
    }
}

uint32_t AFC_Get_Frequency_Calibration_Cycle_Count(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return afc->AFC_FRE_CNT & AFC_24M_AFC_24M_FRE_CNT_FRE_CNT_Msk;
    }
    else if (afc == AFC320k)
    {
        return afc->AFC_FRE_CNT & AFC_320K_AFC_320K_FRE_CNT_FRE_CNT_Msk;
    }
}

uint16_t AFC_Get_Core_Trim_Fine(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return ((afc->CORE_TRIM_SIGNAL & AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_FINE_Msk) >> AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_FINE_Pos);
    }
    else if (afc == AFC320k)
    {
        return ((afc->CORE_TRIM_SIGNAL & AFC_320K_CORE_TRIM_SIGNAL_CORE_TRIM_FINE_Msk) >> AFC_320K_CORE_TRIM_SIGNAL_CORE_TRIM_FINE_Pos);
    }
}

uint16_t AFC_Get_Core_Trim_Coarse(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return ((afc->CORE_TRIM_SIGNAL & AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_COARSE_Msk) >> AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_COARSE_Pos);
    }
    else if (afc == AFC320k)
    {
        return ((afc->CORE_TRIM_SIGNAL & AFC_320K_CORE_TRIM_SIGNAL_CORE_TRIM_COARSE_Msk) >> AFC_320K_CORE_TRIM_SIGNAL_CORE_TRIM_COARSE_Pos);
    }
}

uint16_t AFC_Get_Trim_Enabled_Singal(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return ((afc->CORE_TRIM_SIGNAL & AFC_24M_CORE_TRIM_SIGNAL_AFC_TRIM_RST_Msk) >> AFC_24M_CORE_TRIM_SIGNAL_AFC_TRIM_RST_Pos);
    }
    else if (afc == AFC320k)
    {
        return ((afc->CORE_TRIM_SIGNAL & AFC_320K_CORE_TRIM_SIGNAL_AFC_TRIM_RST_Msk) >> AFC_320K_CORE_TRIM_SIGNAL_AFC_TRIM_RST_Pos);
    }
}

uint16_t AFC_Get_Frequency_Count_Difference(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return ((afc->OP_DATA & AFC_24M_OP_DATA_FRE_CNT_SUB_Msk) >> AFC_24M_OP_DATA_FRE_CNT_SUB_Pos);
    }
    else if (afc == AFC320k)
    {
        return ((afc->OP_DATA & AFC_320K_OP_DATA_FRE_CNT_SUB_Msk) >> AFC_320K_OP_DATA_FRE_CNT_SUB_Pos);
    }
}

uint16_t AFC_Get_Last_Frequency_Count_Difference(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return ((afc->OP_DATA & AFC_24M_OP_DATA_FRE_CNT_SUB_TEMP_Msk) >> AFC_24M_OP_DATA_FRE_CNT_SUB_TEMP_Pos);
    }
    else if (afc == AFC320k)
    {
        return ((afc->OP_DATA & AFC_320K_OP_DATA_FRE_CNT_SUB_TEMP_Msk) >> AFC_320K_OP_DATA_FRE_CNT_SUB_TEMP_Pos);
    }
}

uint16_t AFC_Get_Fine_Trim_Signal_Compare_Status(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        return ((afc->OP_DATA & AFC_24M_OP_DATA_FINE_TRIM_SIGN_COMP_Msk) >> AFC_24M_OP_DATA_FINE_TRIM_SIGN_COMP_Pos);
    }
    else if (afc == AFC320k)
    {
        return ((afc->OP_DATA & AFC_320K_OP_DATA_FINE_TRIM_SIGN_COMP_Msk) >> AFC_320K_OP_DATA_FINE_TRIM_SIGN_COMP_Pos);
    }
}

void AFC_Set_Pulse_Cmd(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    if (afc == AFC24M)
    {
        afc->AFC_PULSE = AFC_24M_AFC_PULSE_OP_PULSE_Msk;
    }
    else if (afc == AFC320k)
    {
        afc->AFC_PULSE = AFC_320K_AFC_PULSE_OP_PULSE_Msk;
    }
}

void AFC_Set_Interrupt_Mask(AFC_TypeDef *afc, uint32_t interrupt)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));
    assert_param(IS_AFC_INTERRUPT_MODE(interrupt));

    afc->INT_MASK_SET = interrupt;
}

void AFC_Set_Interrupt_Clear(AFC_TypeDef *afc, uint32_t interrupt)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));
    assert_param(IS_AFC_INTERRUPT_MODE(interrupt));

    afc->INT_MASK_CLR = interrupt;
}

uint32_t AFC_Get_Interrupt_Status(AFC_TypeDef *afc)
{
    assert_param(afc != NULL);
    assert_param(IS_AFC_ALL_INSTANCE(afc));

    return afc->INT_MASK_STATUS;
}
