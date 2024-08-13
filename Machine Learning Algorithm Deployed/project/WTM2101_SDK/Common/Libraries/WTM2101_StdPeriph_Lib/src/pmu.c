/**
  ******************************************************************************  
  * @file    pmu.c
  * @brief   The Source Codes for the PMU Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************  
  */

/* Includes */
#include "pmu.h"

void PMU_Dsm_Mode_Cmd(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->CTL |= PMU_PMU_CTL_PDDS_Msk;
    __RV_CSR_WRITE(CSR_SLEEPVALUE, 0x01); 
}

void PMU_Rsm_Mode_Cmd(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->CTL &= ~PMU_PMU_CTL_PDDS_Msk;
    __RV_CSR_WRITE(CSR_SLEEPVALUE, 0x01); 
}

void PMU_Standby_Mode_Cmd(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->CTL &= ~PMU_PMU_CTL_PDDS_Msk;
    __RV_CSR_WRITE(CSR_SLEEPVALUE, 0); 
}

void PMU_Enable_External_Clock(PMU_TypeDef *pmu, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));   
     
    if (NewState)
    {
        GPIOA->PAD_RESV |= (0x10 << GPIO_PAD_RESV_PAD_RESV_Pos);
    }
    else
    {
        GPIOA->PAD_RESV &= ~(0x10 << GPIO_PAD_RESV_PAD_RESV_Pos);
    }
}

uint8_t PMU_Get_24Mhz_Clock_Source(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return ((pmu->TRIM1 & PMU_TRIM_1_OSC24M_SEL_Msk) >> PMU_TRIM_1_OSC24M_SEL_Pos);
}

void PMU_Select_24Mhz_Clock_Cmd(PMU_TypeDef *pmu, uint8_t clock_select)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_CLOCK_24MHZ_SELECT(clock_select));

    if (clock_select == OSC_INTERNAL_24M)
    {
        pmu->TRIM1 &= ~PMU_TRIM_1_OSC24M_SEL_Msk;
    }
    else if (clock_select == XTL_EXTERNAL_24M)
    {
        pmu->TRIM1 |= PMU_TRIM_1_OSC24M_SEL_Msk;
    }
}

uint8_t PMU_Get_24M_Clock_Source_div(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
      
    uint8_t div = 0;
    if (!(pmu->CTL & PMU_PMU_CTL_OSC10K_EN_Msk))
    {
        div = 1;
    }
    else
    {   
        switch ((pmu->PMU_RESV & PMU_PMU_RESV_PMU_RESV_REG11_Msk) >> PMU_PMU_RESV_PMU_RESV_REG11_Pos)
        {
            case 0:
                div = 12;
                break;
            case 1:
                div = 6;
                break;
            case 2:
                div = 4;
                break;
            case 3:
                div = 2;
                break;
        }
    }

    return div;
}

void PMU_Set_24M_Clock_Source_div(PMU_TypeDef *pmu, uint8_t div)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    switch (div)
    { 
        case 1:
            pmu->CTL &= ~PMU_PMU_CTL_OSC10K_EN_Msk;
            break;
        case 2:
            pmu->CTL |= PMU_PMU_CTL_OSC10K_EN_Msk;
            pmu->PMU_RESV &= ~PMU_PMU_RESV_PMU_RESV_REG11_Msk;
            pmu->PMU_RESV |= (3 << PMU_PMU_RESV_PMU_RESV_REG11_Pos);
            break;
        case 4:
            pmu->CTL |= PMU_PMU_CTL_OSC10K_EN_Msk;
            pmu->PMU_RESV &= ~PMU_PMU_RESV_PMU_RESV_REG11_Msk;
            pmu->PMU_RESV |= (2 << PMU_PMU_RESV_PMU_RESV_REG11_Pos);
            break;
        case 6:
            pmu->CTL |= PMU_PMU_CTL_OSC10K_EN_Msk;
            pmu->PMU_RESV &= ~PMU_PMU_RESV_PMU_RESV_REG11_Msk;
            pmu->PMU_RESV |= (1 << PMU_PMU_RESV_PMU_RESV_REG11_Pos);
            break;
        case 12:
            pmu->CTL |= PMU_PMU_CTL_OSC10K_EN_Msk;
            pmu->PMU_RESV &= ~PMU_PMU_RESV_PMU_RESV_REG11_Msk;
            break;
    }   
}

void PMU_Set_Clock_Source_Cmd(PMU_TypeDef *pmu, uint8_t clock_souce, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_CLOCK_SOUCE(clock_souce));

    if (clock_souce & OSC_10K)
    {
        if (NewState)
        {
            pmu->PMU_RESV |= (4 << PMU_PMU_RESV_PMU_RESV_REG11_Pos);
        }
        else
        {
            pmu->PMU_RESV &= ~(4 << PMU_PMU_RESV_PMU_RESV_REG11_Pos);
        }
    }

    if (clock_souce & XTL32K)
    {
        if (NewState)
        {
            pmu->CTL |= PMU_PMU_CTL_XTL32K_EN_Msk;
        }
        else
        {
            pmu->CTL &= ~PMU_PMU_CTL_XTL32K_EN_Msk;            
        }

    }

    if (clock_souce & OSC_320K)
    {
        if (NewState)
        {
            pmu->CTL |= PMU_PMU_CTL_OSC320K_EN_Msk;
        }
        else
        {
            pmu->CTL &= ~PMU_PMU_CTL_OSC320K_EN_Msk;
        }
    }

    if (clock_souce & _24M)
    {
        if (NewState)
        {
            if (!(pmu->TRIM1 & PMU_TRIM_1_OSC24M_SEL_Msk))
            {
                pmu->CTL |= PMU_PMU_CTL_OSC_EN_Msk;
            }
            pmu->CTL |= PMU_PMU_CTL_OSC24M_EN_Msk;
        }
        else
        {   
            pmu->CTL &= ~PMU_PMU_CTL_OSC24M_EN_Msk;
            if (!(pmu->TRIM1 & PMU_TRIM_1_OSC24M_SEL_Msk))
            {
                if (!(pmu->CTL & PMU_PMU_CTL_PLL_EN_Msk))
                {
                    pmu->CTL &= ~PMU_PMU_CTL_OSC_EN_Msk;
                }

            }
        }
    }

    if (clock_souce & PLL)
    {
        if (NewState)
        {
            if (!(pmu->TRIM1 & PMU_TRIM_1_OSC24M_SEL_Msk))
            {
                pmu->CTL |= PMU_PMU_CTL_OSC_EN_Msk;
            }
            pmu->CTL |= PMU_PMU_CTL_PLL_EN_Msk;
            pmu->CLK |= PMU_PMU_CLK_PLL_GATE_DIS_Msk;
            while (!(pmu->CTL & PMU_PMU_CTL_PLL_EN_Msk));
        }
        else
        {
            pmu->CLK &= ~PMU_PMU_CLK_PLL_GATE_DIS_Msk;
            pmu->CTL &= ~PMU_PMU_CTL_PLL_EN_Msk;
            if (!(pmu->TRIM1 & PMU_TRIM_1_OSC24M_SEL_Msk))
            {
                if (!(pmu->CTL & PMU_PMU_CTL_OSC24M_EN_Msk))
                {
                    pmu->CTL &= ~PMU_PMU_CTL_OSC_EN_Msk;
                }
            }
        }
    } 
}

void PMU_Set_Audio_Clock_Cmd(PMU_TypeDef *pmu, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (NewState)
    {
        pmu->CTL |= PMU_PMU_CTL_AUD_CLKEN_Msk;
    }
    else
    {
        pmu->CTL &= ~PMU_PMU_CTL_AUD_CLKEN_Msk;
    }
}

void PMU_Set_Rsm_Mode_Parameter(PMU_TypeDef *pmu, uint8_t parameter, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_RSM_MODE_PARAMETER(parameter));

    if (parameter & PMU_RSM_MODE_KEEP_AUDIO)
    {   
        if (NewState)
        {
            pmu->RSM_CTL |= PMU_RSM_CTL_KEEP_AUDIO_Msk;
        }
        else
        {
            pmu->RSM_CTL &= ~PMU_RSM_CTL_KEEP_AUDIO_Msk;
        }
    }
    if (parameter & PMU_RSM_MODE_KEEP_OSC10K)
    {
        if (NewState)
        {
            pmu->RSM_CTL |= PMU_RSM_CTL_KEEP_OSC10K_Msk;
        }
        else
        {
            pmu->RSM_CTL &= ~PMU_RSM_CTL_KEEP_OSC10K_Msk;
        }
    }    
    if (parameter & PMU_RSM_MODE_KEEP_XTL32K)
    {
        if (NewState)
        {
            pmu->RSM_CTL |= PMU_RSM_CTL_KEEP_XTL32K_Msk;
        }
        else
        {
            pmu->RSM_CTL &= ~PMU_RSM_CTL_KEEP_XTL32K_Msk;
        }
    }    
    if (parameter & PMU_RSM_MODE_KEEP_OSC2M)
    {
        if (NewState)
        {
            pmu->RSM_CTL |= PMU_RSM_CTL_KEEP_OSC2M_Msk;
        }
        else
        {
            pmu->RSM_CTL &= ~PMU_RSM_CTL_KEEP_OSC2M_Msk;
        }
    }   
    if (parameter & PMU_RSM_MODE_KEEP_FLASH)
    {
        if (NewState)
        {
            pmu->RSM_CTL |= PMU_RSM_CTL_FLASH_KEEP_Msk;
        }
        else
        {
            pmu->RSM_CTL &= ~PMU_RSM_CTL_FLASH_KEEP_Msk;
        }
    }    
    if (parameter & PMU_RSM_MODE_KEEP_WDT)
    {
        if (NewState)
        {
            pmu->RSM_CTL |= PMU_RSM_CTL_WDT_KEEP_Msk;
        }
        else
        {
            pmu->RSM_CTL &= ~PMU_RSM_CTL_WDT_KEEP_Msk;
        }
    }    
    if (parameter & PMU_RSM_MODE_KEEP_VDD3)
    {
        if (NewState)
        {
            pmu->RSM_CTL |= PMU_RSM_CTL_VDD3_KEEP_Msk;
        }
        else
        {
            pmu->RSM_CTL &= ~PMU_RSM_CTL_VDD3_KEEP_Msk;
        }
    }    
    if (parameter & PMU_RSM_MODE_KEEP_VDD)
    {
        if (NewState)
        {
            pmu->RSM_CTL |= PMU_RSM_CTL_VDD_KEEP_Msk;
        }
        else
        {
            pmu->RSM_CTL &= ~PMU_RSM_CTL_VDD_KEEP_Msk;
        }
    }
}

uint8_t PMU_Get_Reset_Flag(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return pmu->FLAG_CTL;
}

void PMU_Clear_Reset_Flag(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->FLAG_CTL |= PMU_FLAG_CTL_FLAG_CLR_Msk;
}

FunctionalState PMU_Get_High_Clock_For_Rtc_And_Wdt_EnableStatus(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (pmu->CLK & PMU_PMU_CLK_TCLK_EN_Msk)
    {
        return ENABLE;
    }
    else
    { 
        return DISABLE;
    }
}

void PMU_Enable_High_Clock_For_Rtc_And_Wdt(PMU_TypeDef *pmu, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (NewState)
    {
        pmu->CLK |= PMU_PMU_CLK_TCLK_EN_Msk;
    }
    else
    {
        pmu->CLK &= ~PMU_PMU_CLK_TCLK_EN_Msk;
    }
}

uint8_t PMU_Get_Rtc_Clock_Source(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return (pmu->CLK & PMU_PMU_CLK_RTCCLK_SEL_Msk);
}

void PMU_Set_Rtc_Clock_Source(PMU_TypeDef *pmu, uint8_t select_rtc_clock)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_RTC_CLOCK_SELECT(select_rtc_clock));
    
    pmu->CLK |= PMU_PMU_CLK_TCLK_EN_Msk;
    pmu->CLK &= ~PMU_PMU_CLK_RTCCLK_SEL_Msk;
    pmu->CLK |= select_rtc_clock;
}

uint8_t PMU_Get_Wdt_Clock_Source(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return (pmu->CLK & PMU_PMU_CLK_WDTCLK_SEL_Msk);
}

void PMU_Set_Wdt_Clock_Source(PMU_TypeDef *pmu, uint8_t select_wdt_clock)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_WDT_CLOCK_SELECT(select_wdt_clock));

    pmu->CLK |= PMU_PMU_CLK_TCLK_EN_Msk;
    pmu->CLK &= ~PMU_PMU_CLK_WDTCLK_SEL_Msk;
    pmu->CLK |= select_wdt_clock;
}

uint8_t PMU_Get_Ie_Msk(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return (pmu->IE_MSK);
}

void PMU_Set_Ie_Msk(PMU_TypeDef *pmu, uint8_t ie_msk, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_INTERRUPT_OR_EVENT_MASK(ie_msk));

    if (ie_msk & PMU_VAD_IMSK)
    { 
        if (NewState)
        {
            pmu->IE_MSK |= PMU_IE_MSK_VAD_IMSK_Msk;
        }
        else
        {
            pmu->IE_MSK &= ~PMU_IE_MSK_VAD_IMSK_Msk;
        }
    }

    if (ie_msk & PMU_RTC_IMSK)
    {
        if (NewState)
        {
            pmu->IE_MSK |= PMU_IE_MSK_RTC_IMSK_Msk;
        }
        else
        {
            pmu->IE_MSK &= ~PMU_IE_MSK_RTC_IMSK_Msk;
        }
    }

    if (ie_msk & PMU_WDT_IMSK)
    {
        if (NewState)
        {
            pmu->IE_MSK |= PMU_IE_MSK_WDT_IMSK_Msk;
        }
        else
        {
            pmu->IE_MSK &= ~PMU_IE_MSK_WDT_IMSK_Msk;
        }
    }
   
    if (ie_msk & PMU_GPIO_IMSK)
    {
        if (NewState)
        {
            pmu->IE_MSK |= PMU_IE_MSK_GPIO_IMSK_Msk;
        }
        else
        {
            pmu->IE_MSK &= ~PMU_IE_MSK_GPIO_IMSK_Msk;
        }
    }

    if (ie_msk & PMU_VAD_EMSK)
    {
        if (NewState)
        {
            pmu->IE_MSK |= PMU_IE_MSK_VAD_EMSK_Msk;
        }
        else
        {
            pmu->IE_MSK &= ~PMU_IE_MSK_VAD_EMSK_Msk;
        }
    }

    if (ie_msk & PMU_RTC_EMSK)
    {
        if (NewState)
        {
            pmu->IE_MSK |= PMU_IE_MSK_RTC_EMSK_Msk;
        }
        else
        {
            pmu->IE_MSK &= ~PMU_IE_MSK_RTC_EMSK_Msk;
        }
    }

    if (ie_msk & PMU_WDT_EMSK)
    {
        if (NewState)
        {
            pmu->IE_MSK |= PMU_IE_MSK_WDT_EMSK_Msk;
        }
        else
        {
            pmu->IE_MSK &= ~PMU_IE_MSK_WDT_EMSK_Msk;
        }
    }

    if (ie_msk & PMU_GPIO_EMSK)
    {
        if (NewState)
        {
            pmu->IE_MSK |= PMU_IE_MSK_GPIO_EMSK_Msk;
        }
        else
        {
            pmu->IE_MSK &= ~PMU_IE_MSK_GPIO_EMSK_Msk;
        }
    }
}

FunctionalState PMU_Get_Npu_Poweron_Cmd_Status(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (pmu->LP_CTL & PMU_LP_CTL_NPU_PD_Msk)
    {
        return DISABLE;
    }
    else 
    {
        return ENABLE;
    }
}

void PMU_Set_Npu_Poweron_Cmd(PMU_TypeDef *pmu, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (NewState)
    {
        pmu->LP_CTL &= ~PMU_LP_CTL_NPU_PD_Msk;
    }
    else
    {
        pmu->LP_CTL |= PMU_LP_CTL_NPU_PD_Msk;
    }
}

FunctionalState PMU_Get_Npu_Reset_Status(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (pmu->LP_CTL & PMU_LP_CTL_NPU_RSTN_Msk)
    {
        return ENABLE;
    }
    else 
    {
        return DISABLE;
    }
}

void PMU_Set_Npu_Reset(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->LP_CTL |= PMU_LP_CTL_NPU_RSTN_Msk;
}

FunctionalState PMU_Get_Npu_Clock_Cmd_Status(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (pmu->LP_CTL & PMU_LP_CTL_NPU_CLKEN_Msk)
    {
        return ENABLE;
    }
    else 
    {
        return DISABLE;
    }
}

void PMU_Set_Npu_Clock_Cmd(PMU_TypeDef *pmu, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (NewState)
    {
        pmu->LP_CTL |= PMU_LP_CTL_NPU_CLKEN_Msk;
    }
    else
    {
        pmu->LP_CTL &= ~PMU_LP_CTL_NPU_CLKEN_Msk;
    }
}

FunctionalState PMU_Get_Periphral_Poweron_Cmd_Status(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (pmu->LP_CTL & PMU_LP_CTL_PERI_PD_Msk)
    {
        return DISABLE;
    }
    else 
    {
        return ENABLE;
    }
}

void PMU_Set_Periphral_Poweron_Cmd(PMU_TypeDef *pmu, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if(NewState)
    {
        pmu->LP_CTL &= ~PMU_LP_CTL_PERI_PD_Msk;
    }
    else
    {
        pmu->LP_CTL |= PMU_LP_CTL_PERI_PD_Msk;
    }
}

uint8_t PMU_Get_Audio_Clock_Div_Num(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return ((pmu->CLK_CTL & PMU_CLK_CTL_AUD_DIV_NUM_Msk) >> PMU_CLK_CTL_AUD_DIV_NUM_Pos);
}

void PMU_Set_Audio_Clock_Div_Num(PMU_TypeDef *pmu,uint8_t div_num)
{
    #if 0
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->CLK_CTL &= ~PMU_CLK_CTL_AUD_DIV_NUM_Msk;
    for(int i=0;i<100;i++){
        __NOP();
    }
    //__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    pmu->CLK_CTL |= (div_num << PMU_CLK_CTL_AUD_DIV_NUM_Pos);
    #else
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    uint8_t data = pmu->CLK_CTL;
    data &= ~PMU_CLK_CTL_AUD_DIV_NUM_Msk;
    data |= (div_num << PMU_CLK_CTL_AUD_DIV_NUM_Pos);
    pmu->CLK_CTL = data;
    #endif
}

uint8_t PMU_Get_NPU_Clock_Div_Num(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return ((pmu->CLK_CTL & PMU_CLK_CTL_NPU_DIV_NUM_Msk) >> PMU_CLK_CTL_NPU_DIV_NUM_Pos);
}

void PMU_Set_NPU_Clock_Div_Num(PMU_TypeDef *pmu,uint8_t div_num)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
 
    pmu->CLK_CTL &= ~PMU_CLK_CTL_NPU_DIV_NUM_Msk;
    pmu->CLK_CTL |= (div_num << PMU_CLK_CTL_NPU_DIV_NUM_Pos);
}

uint8_t PMU_Get_Ldo_Voltage_Value(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    if (pmu->VOL_UPDATA & PMU_VOL_UPDATE_VOL0_UPDATE_VALUE_Msk)
    {
        return PMU_LDO_VOLTAGE_1_1V;
    }
    else
    {
        return PMU_LDO_VOLTAGE_0_9V;
    }
}

void PMU_Set_Ldo_Voltage_Value(PMU_TypeDef *pmu,uint8_t ldo_voltage)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_Ldo_Voltage_Value(ldo_voltage));

    if (ldo_voltage == PMU_LDO_VOLTAGE_0_9V)
    {
        pmu->VOL_UPDATA &= ~PMU_VOL_UPDATE_VOL0_UPDATE_VALUE_Msk;
    }
    else if(ldo_voltage == PMU_LDO_VOLTAGE_1_1V)
    {
        pmu->VOL_UPDATA |= PMU_VOL_UPDATE_VOL0_UPDATE_VALUE_Msk;
    }
}

void PMU_Set_Ldo_Voltage_Cmd(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->VOL_UPDATA |= PMU_VOL_UPDATE_VOL_UPDATE_Msk;
}

uint8_t PMU_Get_Sram_Poweron_Status(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return pmu->SRAM_PD;
}

void PMU_Set_Sram_Poweron_Cmd(PMU_TypeDef *pmu, uint8_t sram_address, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_Sram_Address(sram_address));

    if (sram_address & PMU_SRAM0)
    {
        if (NewState)
        {
            pmu->SRAM_PD &= ~PMU_SRAM_PD_SRAM0_PD_Msk;
        }
        else
        {
            pmu->SRAM_PD |= PMU_SRAM_PD_SRAM0_PD_Msk;
        }
    }
    if (sram_address & PMU_SRAM1_FIRST_32K)
    {
        if (NewState)
        {
            pmu->SRAM_PD &= ~PMU_SRAM_PD_SRAM1_0_PD_Msk;
        }
        else
        {
            pmu->SRAM_PD |= PMU_SRAM_PD_SRAM1_0_PD_Msk;
        }

    }
    if (sram_address & PMU_SRAM1_SECOND_32K)
    {
        if (NewState)
        {
            pmu->SRAM_PD &= ~PMU_SRAM_PD_SRAM1_1_PD_Msk;
        }
        else
        {
            pmu->SRAM_PD |= PMU_SRAM_PD_SRAM1_1_PD_Msk;
        }

    }
    if (sram_address & PMU_SRAM2_FIRST_32K)
    {
        if (NewState)
        {
            pmu->SRAM_PD &= ~PMU_SRAM_PD_SRAM2_0_PD_Msk;
        }
        else
        {
            pmu->SRAM_PD |= PMU_SRAM_PD_SRAM2_0_PD_Msk;
        }
    }
    if (sram_address & PMU_SRAM2_SECOND_32K)
    {
        if (NewState)
        {
            pmu->SRAM_PD &= ~PMU_SRAM_PD_SRAM2_1_PD_Msk;
        }
        else
        {
            pmu->SRAM_PD |= PMU_SRAM_PD_SRAM2_1_PD_Msk;
        }
    }
}

void PMU_Set_Sram_Retain_In_Rsm_Mode_Cmd(PMU_TypeDef *pmu, uint8_t sram_address, FunctionalState NewState)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
    assert_param(IS_PMU_Sram_Address(sram_address));

    if (sram_address & PMU_SRAM0)
    {
        if (NewState)
        {
            pmu->SRAM_RTN &= ~PMU_SRAM_RTN_SRAM0_Msk;
        }
        else
        {
            pmu->SRAM_RTN |= PMU_SRAM_RTN_SRAM0_Msk;
        }
    }
    if (sram_address & PMU_SRAM1_FIRST_32K)
    {
        if (NewState)
        {
            pmu->SRAM_RTN &= ~PMU_SRAM_RTN_SRAM1_Msk;           
        }
        else
        {
            pmu->SRAM_RTN |= PMU_SRAM_RTN_SRAM1_Msk;
        }
    }
    if (sram_address & PMU_SRAM1_SECOND_32K)
    {
        if (NewState)
        {
            pmu->SRAM_RTN &= ~PMU_SRAM_RTN_SRAM2_Msk;
        }
        else
        {
            pmu->SRAM_RTN |= PMU_SRAM_RTN_SRAM2_Msk;
        }
    }
    if (sram_address & PMU_SRAM2_FIRST_32K)
    {
        if (NewState)
        {
            pmu->SRAM_RTN &= ~PMU_SRAM_RTN_SRAM3_Msk;
        }
        else
        {
            pmu->SRAM_RTN |= PMU_SRAM_RTN_SRAM3_Msk;
        }

    }
    if (sram_address & PMU_SRAM2_SECOND_32K)
    {
        if (NewState)
        {
            pmu->SRAM_RTN &= ~PMU_SRAM_RTN_SRAM4_Msk;
        }
        else
        {
            pmu->SRAM_RTN |= PMU_SRAM_RTN_SRAM4_Msk;
        }
    }
    if (sram_address & PMU_DSP_SRAM_RTN)
    {
        if (NewState)
        {
            pmu->SRAM_RTN &= ~PMU_SRAM_RTN_DSP_SRAM_Msk;
        }
        else
        {
            pmu->SRAM_RTN |= PMU_SRAM_RTN_DSP_SRAM_Msk;
        }
    }
}

uint8_t PMU_Get_Pll_Division(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    return (pmu->PLL_1 & PMU_PLL_1_PLL_DIV_Msk);
}

void PMU_Set_Pll_Division(PMU_TypeDef *pmu, uint8_t division)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->PLL_1 = (pmu->PLL_1 & PMU_PLL_1_PLL_LOOP_CAP1_SEL_Msk) | (division << PMU_PLL_1_PLL_DIV_Pos);
}

void PMU_Software_Reset(PMU_TypeDef *pmu)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));

    pmu->SOFT_RST = PMU_SOFTWARE_RESET_VALUE;
}

void PMU_Set_24M_Trim_Source(PMU_TypeDef *pmu,uint8_t source)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
        
    PMU->SYS_CFG &= ~PMU_SYS_CFG_REG_24M_TRIM_SEL_Msk;
    PMU->SYS_CFG |= (source << PMU_SYS_CFG_REG_24M_TRIM_SEL_Pos);
}

void PMU_Set_320K_Trim_Source(PMU_TypeDef *pmu,uint8_t source)
{
    assert_param(pmu != NULL);
    assert_param(IS_PMU_ALL_INSTANCE(pmu));
        
    PMU->SYS_CFG &= ~PMU_SYS_CFG_REG_320K_TRIM_SEL_Msk;
    PMU->SYS_CFG |= (source << PMU_SYS_CFG_REG_320K_TRIM_SEL_Pos);    
}
