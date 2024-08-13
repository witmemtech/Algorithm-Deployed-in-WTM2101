/**
  ******************************************************************************
  * @file    timer.c
  * @brief   The Source Codes for the TIMER Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "timer.h"

uint32_t TIMER_Transfer_second_to_tick(TMR_TypeDef* TIMERx, uint32_t second)
{
    uint32_t timer_div = 0;

    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx == TIMER0)
    {
        timer_div = RCC_TIM0_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER1)
    {
        timer_div = RCC_TIM1_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER2)
    {
        timer_div = RCC_TIM2_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER3)
    {
        timer_div = RCC_TIM3_Get_ClkDiv() + 1;
    }

    return (RCC_Get_SYSClk() / (RCC_AHB_Get_ClkDiv() + 1) / timer_div * second);
}

uint32_t TIMER_Transfer_millisecond_to_tick(TMR_TypeDef* TIMERx, uint32_t millisecond)
{
    uint32_t timer_div = 0;

    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx == TIMER0)
    {
        timer_div = RCC_TIM0_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER1)
    {
        timer_div = RCC_TIM1_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER2)
    {
        timer_div = RCC_TIM2_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER3)
    {
        timer_div = RCC_TIM3_Get_ClkDiv() + 1;
    }

    return (RCC_Get_SYSClk() / (RCC_AHB_Get_ClkDiv() + 1) / timer_div / 1000 * millisecond);
}

uint32_t TIMER_Transfer_microsecond_to_tick(TMR_TypeDef* TIMERx, uint32_t microsecond)
{
    uint32_t timer_div = 0;

    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx == TIMER0)
    {
        timer_div = RCC_TIM0_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER1)
    {
        timer_div = RCC_TIM1_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER2)
    {
        timer_div = RCC_TIM2_Get_ClkDiv() + 1;
    }
    else if (TIMERx == TIMER3)
    {
        timer_div = RCC_TIM3_Get_ClkDiv() + 1;
    }

    return (RCC_Get_SYSClk() / (RCC_AHB_Get_ClkDiv() + 1) / timer_div / 1000 * microsecond / 1000);
}

void TIMER_Init(TMR_TypeDef* TIMERx, TIMER_InitTypeDef* TIM_InitStruct)
{
    uint32_t pwm_period = 0;

    assert_param(TIMERx != NULL && TIM_InitStruct != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));
    assert_param(IS_TIMER_MODE(TIM_InitStruct->mode));

    /*the timer mode is set*/
    if (TIM_InitStruct->mode == TIMER_FREE_RUNING_MODE)
    {
        TIMERx->TIMERCONTROLREG &= ~TIMER_TIMER1_CONTROL_REGISTER_TIMER_MODE_Msk;
    }
    else if (TIM_InitStruct->mode == TIMER_USER_DEFINED_MODE)
    {
        TIMERx->TIMERCONTROLREG |= TIMER_TIMER1_CONTROL_REGISTER_TIMER_MODE_Msk;
    }

    /*the period is set*/
    if (TIM_InitStruct->period <= TIMER_TIMER1_LOAD_COUNT_REGISTER_TIMER1LOAD_COUNT_Msk)
    {
        TIMERx->TIMERLOADCOUNT = TIM_InitStruct->period;
    }
    else
    {
        TIMERx->TIMERLOADCOUNT = TIMER_TIMER1_LOAD_COUNT_REGISTER_TIMER1LOAD_COUNT_Msk;
    }

    if (TIM_InitStruct->pwm_period <= TIMER_TIMER1_LOAD_COUNT_REGISTER_TIMER1LOAD_COUNT_Msk)
    {
        pwm_period = TIM_InitStruct->pwm_period;
    }
    else
    {
        pwm_period = TIMER_TIMER1_LOAD2_COUNT_REGISTER_TIMER1LOAD_COUNT2_Msk;
    }

    /*the second period is set*/
    if (TIMERx == TIMER0)
    {
        TIMERS->TIMER0LOADCOUNT2 = pwm_period;
    }
    else if (TIMERx == TIMER1)
    {
        TIMERS->TIMER1LOADCOUNT2 = pwm_period;
    }
    else if (TIMERx == TIMER2)
    {
        TIMERS->TIMER2LOADCOUNT2 = pwm_period;
    }
    else if (TIMERx == TIMER3)
    {
        TIMERS->TIMER3LOADCOUNT2 = pwm_period;
    }
}

uint32_t TIMER_Get_LoadCounter_Value(TMR_TypeDef* TIMERx)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    return TIMERx->TIMERLOADCOUNT;
}

void TIMER_Set_LoadCounter_Value(TMR_TypeDef* TIMERx, uint32_t loadcounter)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    TIMERx->TIMERLOADCOUNT = loadcounter;
}

uint32_t TIMER_Get_LoadCounter2_Value(TMR_TypeDef* TIMERx)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx == TIMER0)
    {
        return TIMERS->TIMER0LOADCOUNT2;
    }
    else if (TIMERx == TIMER1)
    {
        return TIMERS->TIMER1LOADCOUNT2;
    }
    else if (TIMERx == TIMER2)
    {
        return TIMERS->TIMER2LOADCOUNT2;
    }
    else if (TIMERx == TIMER3)
    {
        return TIMERS->TIMER3LOADCOUNT2;
    }
}

void TIMER_Set_LoadCounter2_Value(TMR_TypeDef* TIMERx, uint32_t loadcounter)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx == TIMER0)
    {
        TIMERS->TIMER0LOADCOUNT2 = loadcounter;
    }
    else if (TIMERx == TIMER1)
    {
        TIMERS->TIMER1LOADCOUNT2 = loadcounter;
    }
    else if (TIMERx == TIMER2)
    {
        TIMERS->TIMER2LOADCOUNT2 = loadcounter;
    }
    else if (TIMERx == TIMER3)
    {
        TIMERS->TIMER3LOADCOUNT2 = loadcounter;
    }
}

int TIMER_Get_Current_Counter_Value(TMR_TypeDef* TIMERx)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    return TIMERx->TIMERCURRENTVALUE;
}

FunctionalState TIMER_Get_Enable_Status(TMR_TypeDef* TIMERx)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx->TIMERCONTROLREG & TIMER_TIMER1_CONTROL_REGISTER_TIMER_ENABLE_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void TIMER_Set_Enable_Cmd(TMR_TypeDef* TIMERx, FunctionalState NewState)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (NewState == DISABLE)
    {
        TIMERx->TIMERCONTROLREG &= ~TIMER_TIMER1_CONTROL_REGISTER_TIMER_ENABLE_Msk;
    }
    else
    {
        TIMERx->TIMERCONTROLREG |= TIMER_TIMER1_CONTROL_REGISTER_TIMER_ENABLE_Msk;
    }
}

uint8_t TIMER_Get_Running_Mode(TMR_TypeDef* TIMERx)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx->TIMERCONTROLREG & TIMER_TIMER1_CONTROL_REGISTER_TIMER_MODE_Msk)
    {
        return TIMER_USER_DEFINED_MODE;
    }
    else
    {
        return TIMER_FREE_RUNING_MODE;
    }
}

void TIMER_Set_Running_Mode(TMR_TypeDef* TIMERx, uint8_t mode)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (mode == TIMER_FREE_RUNING_MODE)
    {
        TIMERx->TIMERCONTROLREG &= ~TIMER_TIMER1_CONTROL_REGISTER_TIMER_MODE_Msk;
    }
    else if (mode == TIMER_USER_DEFINED_MODE)
    {
        TIMERx->TIMERCONTROLREG |= TIMER_TIMER1_CONTROL_REGISTER_TIMER_MODE_Msk;
    }
}

FunctionalState TIMER_Get_Interrupt_Enable_Status(TMR_TypeDef* TIMERx)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx->TIMERCONTROLREG & TIMER_TIMER1_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Msk)
    {
        return DISABLE;
    }
    else
    {
        return ENABLE;
    }
}

void TIMER_Set_Interrupt_Enable_Cmd(TMR_TypeDef* TIMERx, FunctionalState NewState)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (NewState == ENABLE)
    {
        TIMERx->TIMERCONTROLREG &= ~TIMER_TIMER1_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Msk;
    }
    else
    {
        TIMERx->TIMERCONTROLREG |= TIMER_TIMER1_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Msk;
    }
}

FunctionalState TIMER_Get_Pwm_Enable_Status(TMR_TypeDef* TIMERx)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (TIMERx->TIMERCONTROLREG & TIMER_TIMER1_CONTROL_REGISTER_TIMER_PWM_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void TIMER_Set_Pwm_Enable_Cmd(TMR_TypeDef* TIMERx, FunctionalState NewState)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    if (NewState == DISABLE)
    {
        TIMERx->TIMERCONTROLREG &= ~TIMER_TIMER1_CONTROL_REGISTER_TIMER_PWM_Msk;
    }
    else
    {
        TIMERx->TIMERCONTROLREG |= TIMER_TIMER1_CONTROL_REGISTER_TIMER_PWM_Msk;
    }
}

void TIMER_Clear_Interrupt_Cmd(TMR_TypeDef* TIMERx)
{
    assert_param(TIMERx != NULL);
    assert_param(IS_TIMER_ALL_INSTANCE(TIMERx));

    volatile uint32_t status;

    status = TIMERx->TIMEREOI;
}

FunctionalState TIMER_Get_Interrupt_Status(TMR_TypeDef* TIMERx)
{
    if (TIMERx->TIMERINTSTATUS)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}
