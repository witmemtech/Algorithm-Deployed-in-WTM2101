/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   The Source Codes for the RTC Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "rtc.h"

uint32_t RTC_Transfer_second_to_tick(RTC_TypeDef *rtc, uint32_t second)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    volatile uint32_t clock_source = 0;
    volatile uint32_t clock_frequency = 0;

    clock_source = PMU_Get_Rtc_Clock_Source(PMU);

    switch (clock_source)
    {
        case PMU_CLK_RTC_SWITCH_SYSCLK_DIV_32:
            clock_frequency = RCC_Get_SYSClk() / 32;
            break;
        case PMU_CLK_RTC_SWITCH_10KHZ:
            clock_frequency = 10000;
            break;
        case PMU_CLK_RTC_SWITCH_32KHZ:
            clock_frequency = 32768;
            break;
        case PMU_CLK_RTC_SWITCH_160KHZ:
            clock_frequency = 160000;
            break;
        default:
            break;
    }

    return (second * clock_frequency);
}

uint32_t RTC_Transfer_millisecond_to_tick(RTC_TypeDef *rtc, uint32_t millisecond)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    volatile uint32_t clock_source = 0;
    volatile uint32_t clock_frequency = 0;

    clock_source = PMU_Get_Rtc_Clock_Source(PMU);

    switch (clock_source)
    {
        case PMU_CLK_RTC_SWITCH_SYSCLK_DIV_32:
            clock_frequency = RCC_Get_SYSClk() / 32;
            break;
        case PMU_CLK_RTC_SWITCH_10KHZ:
            clock_frequency = 10000;
            break;
        case PMU_CLK_RTC_SWITCH_32KHZ:
            clock_frequency = 32768;
            break;
        case PMU_CLK_RTC_SWITCH_160KHZ:
            clock_frequency = 160000;
            break;
        default:
            break;
    }

    return (clock_frequency / 1000.0 * millisecond);
}

uint32_t RTC_Transfer_microsecond_to_tick(RTC_TypeDef *rtc, uint32_t microsecond)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    volatile uint32_t clock_source = 0;
    volatile uint32_t clock_frequency = 0;

    clock_source = PMU_Get_Rtc_Clock_Source(PMU);

    switch(clock_source)
    {
        case PMU_CLK_RTC_SWITCH_SYSCLK_DIV_32:
            clock_frequency = RCC_Get_SYSClk() / 32;
            break;
        case PMU_CLK_RTC_SWITCH_10KHZ:
            clock_frequency = 10000;
            break;
        case PMU_CLK_RTC_SWITCH_32KHZ:
            clock_frequency = 32768;
            break;
        case PMU_CLK_RTC_SWITCH_160KHZ:
            clock_frequency = 160000;
            break;
        default:
            break;
    }

    return (clock_frequency / 1000000.0 * microsecond);
}

uint32_t RTC_Get_Counter_Value(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    return rtc->RTC_CCVR;
}

uint32_t RTC_Get_Compare_Time_Value(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    return rtc->RTC_CMR;
}

void RTC_Set_Compare_Time_Value(RTC_TypeDef *rtc, uint32_t timeout)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    rtc->RTC_CMR = timeout;
}

uint32_t RTC_Get_Initial_Time_Value(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    return rtc->RTC_CLR;
}

void RTC_Set_Initial_Time_Value(RTC_TypeDef *rtc, uint32_t timeout)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    rtc->RTC_CLR = timeout;
}

FunctionalState RTC_Get_Interrupt_Enable_Status(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    if (rtc->RTC_CCR & RTC_RTC_CCR_RTC_IEN_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void RTC_Set_Interrupt_Cmd(RTC_TypeDef *rtc, FunctionalState NewState)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    if (NewState == ENABLE)
    {
        rtc->RTC_CCR |= RTC_RTC_CCR_RTC_IEN_Msk;
    }
    else
    {
        rtc->RTC_CCR &= ~RTC_RTC_CCR_RTC_IEN_Msk;
    }
}

FunctionalState RTC_Get_Interrupt_Unmask_Status(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    if (!(rtc->RTC_CCR & RTC_RTC_CCR_RTC_MASK_Msk))
    {
        return DISABLE;
    }
    else
    {
        return ENABLE;
    }
}

void RTC_Set_Interrupt_Unmask_Cmd(RTC_TypeDef *rtc, FunctionalState NewState)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    if (NewState == ENABLE)
    {
        rtc->RTC_CCR &= ~RTC_RTC_CCR_RTC_MASK_Msk;
    }
    else
    {
        rtc->RTC_CCR |= RTC_RTC_CCR_RTC_MASK_Msk;
    }
}

FunctionalState RTC_Get_Wrap_Status(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    if (!(rtc->RTC_CCR & RTC_RTC_CCR_RTC_WEN_Msk))
    {
        return DISABLE;
    }
    else
    {
        return ENABLE;
    }
}

void RTC_Set_Wrap_Cmd(RTC_TypeDef *rtc, FunctionalState NewState)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    if (NewState == ENABLE)
    {
        rtc->RTC_CCR |= RTC_RTC_CCR_RTC_WEN_Msk;
    }
    else
    {
        rtc->RTC_CCR &= ~RTC_RTC_CCR_RTC_WEN_Msk;
    }
}

FunctionalState RTC_Get_Interrupt_Status(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    if (rtc->RTC_STAT & RTC_RTC_STAT_RTC_STAT_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

FunctionalState RTC_Get_Raw_Interrupt_Status(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    if (rtc->RTC_RSTAT & RTC_RTC_RSTAT_RTC_RSTAT_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void RTC_Clear_Int_Cmd(RTC_TypeDef *rtc)
{
    assert_param(rtc != NULL);
    assert_param(IS_RTC_ALL_INSTANCE(rtc));

    volatile uint8_t status = 0;

    status = rtc->RTC_EOI;
}
