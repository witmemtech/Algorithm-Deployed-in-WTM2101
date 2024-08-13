/**
  ******************************************************************************
  * @file    wdt.c
  * @brief   The Source Codes for the WDT Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "wdt.h"

FunctionalState WDT_Get_Enable_Status(WDT_TypeDef *wdt)
{
    assert_param(wdt != NULL);
    assert_param(IS_WDT_ALL_INSTANCE(wdt));

    if (wdt->WDT_CR & WDT_WDT_CR_WDT_EN_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void WDT_Set_Enable_Cmd(WDT_TypeDef *wdt, FunctionalState NewState)
{
    assert_param(wdt != NULL);
    assert_param(IS_WDT_ALL_INSTANCE(wdt));

    if (NewState == ENABLE)
    {
        wdt->WDT_CR |= WDT_WDT_CR_WDT_EN_Msk;
    }
}

void WDT_Set_Timeout_Value(WDT_TypeDef *wdt, uint8_t value)
{
    assert_param(wdt != NULL);
    assert_param(IS_WDT_ALL_INSTANCE(wdt));

    wdt->WDT_TORR = (value << WDT_WDT_TORR_TOP_Pos);
}

int WDT_Get_Current_Counter_Value(WDT_TypeDef *wdt)
{
    assert_param(wdt != NULL);
    assert_param(IS_WDT_ALL_INSTANCE(wdt));

    return wdt->WDT_CCVR;
}

void WDT_Feed_Dog(WDT_TypeDef *wdt)
{
    assert_param(wdt != NULL);
    assert_param(IS_WDT_ALL_INSTANCE(wdt));

    wdt->WDT_CRR = WDT_FEED_DOG_VALUE;
}

void WDT_Clear_Int_Cmd(WDT_TypeDef *wdt)
{
    volatile uint8_t status = 0;
    assert_param(wdt != NULL);
    assert_param(IS_WDT_ALL_INSTANCE(wdt));

    status = wdt->WDT_EOI;
}
