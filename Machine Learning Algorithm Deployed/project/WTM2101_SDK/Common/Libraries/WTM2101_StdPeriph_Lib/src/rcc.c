/**
  ******************************************************************************
  * @file    rcc.c
  * @brief   The Source Codes for the RCC Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "pmu.h"
#include "rcc.h"

#include "hal_clock.h"

void RCC_Deb_Clk_Sel(uint32_t Deb_Src)
{
    /* Check the parameters */
    assert_param(IS_RCC_CLKSRC(Deb_Src));

    RCC->CLK_SEL &= ~RCC_CLK_SEL_DBCLK_SEL_Msk;
    RCC->CLK_SEL |= Deb_Src;
}

void RCC_SysTick_Sel(uint32_t SysTick_Src)
{
    /* Check the parameters */
    assert_param(IS_RCC_SYSTICKSRC(SysTick_Src));

    RCC->CLK_SEL &= ~RCC_CLK_SEL_SYSTICK_SEL_Msk;
    RCC->CLK_SEL |= SysTick_Src;
}

void RCC_SYSClk_Sel(uint32_t SYSClk_Src)
{
    /* Check the parameters */
    assert_param(IS_RCC_SYSCLKSRC(SYSClk_Src));

    RCC->CLK_SEL &= ~RCC_CLK_SEL_SYSCLK_SEL_Msk;
    RCC->CLK_SEL |= SYSClk_Src;
}

static uint32_t RCC_Get_24M_SYSCLK(void)
{
    uint32_t value = 0;
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();

    if (!(PMU->CTL & PMU_PMU_CTL_OSC10K_EN_Msk))
    {
        value = hal_clock_instance->_24mosc_configuration.clock_hz / hal_clock_instance->_24mosc_configuration.clock_divider;
    }
    else
    {
        switch (PMU->PMU_RESV & PMU_PMU_RESV_PMU_RESV_REG11_Msk)
        {
            case 0:
                value = hal_clock_instance->_24mosc_configuration.clock_hz / hal_clock_instance->_24mosc_configuration.clock_divider / 12;
                break;
            case 1:
                value = hal_clock_instance->_24mosc_configuration.clock_hz / hal_clock_instance->_24mosc_configuration.clock_divider / 6;
                break;
            case 2:
                value = hal_clock_instance->_24mosc_configuration.clock_hz / hal_clock_instance->_24mosc_configuration.clock_divider / 4;
                break;
            case 3:
                value = hal_clock_instance->_24mosc_configuration.clock_hz / hal_clock_instance->_24mosc_configuration.clock_divider / 2;
                break;
        }
    }

    return value;
}

uint32_t RCC_Get_SYSClk(void)
{
    uint32_t tmpclk = 0;
    switch(RCC->CLK_SEL&RCC_CLK_SEL_SYSCLK_SEL_Msk)
    {
        case RCC_SYSCLK_Int24M:             /* bps<=57600 */
            tmpclk = RCC_Get_24M_SYSCLK();
            break;
        case RCC_SYSCLK_AUDIO:
            tmpclk = RCC_Get_24M_SYSCLK() / (PMU_Get_Audio_Clock_Div_Num(PMU) + 1);
            break;
        case RCC_SYSCLK_Int10K:             /* bps<=9600 */
            tmpclk = 10000;
            break;
        case RCC_SYSCLK_Ext32K:             /* bps<=19200 */
            tmpclk = 32768;
            break;
        case RCC_SYSCLK_Int160K:            /* bps<=19200 */
            tmpclk = 160000;
            break;
        case RCC_SYSCLK_IntPLL:             /* bps<=115200 */
            tmpclk = RCC_Get_24M_SYSCLK() * (PMU->PLL_1 & PMU_PLL_1_PLL_DIV_Msk);
            break;
        default:
            break;
    }

    return tmpclk;
}

void RCC_CLK_EN_Ctl(uint32_t CLK_EN, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_CLKSRCEN(CLK_EN));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        RCC->CLK_EN |= CLK_EN;
    }
    else
    {
        RCC->CLK_EN &= ~CLK_EN;
    }
}

void RCC_AHB_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->CLK_DIV_0 &= ~RCC_CLK_DIV_0_DIV_AHB_Msk;
    RCC->CLK_DIV_0 |= (uint32_t)CLK_Div;
}

uint8_t RCC_AHB_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_0 & RCC_CLK_DIV_0_DIV_AHB_Msk) >> RCC_CLK_DIV_0_DIV_AHB_Pos;
}

void RCC_APB0_Set_ClkDiv(uint8_t CLK_Div)
{
    /* Check the parameters */
    assert_param(IS_RCC_DIV(CLK_Div));

    RCC->CLK_DIV_1 &= ~RCC_CLK_DIV_1_DIV_APB0_Msk;
    RCC->CLK_DIV_1 |= (((uint32_t)CLK_Div));
}

uint8_t RCC_APB0_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_1 & RCC_CLK_DIV_1_DIV_APB0_Msk) >> RCC_CLK_DIV_1_DIV_APB0_Pos;
}

void RCC_Deb_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->CLK_DIV_0 &= ~RCC_CLK_DIV_0_DIV_DB_Msk;
    RCC->CLK_DIV_0 |= (((uint32_t)CLK_Div) << RCC_CLK_DIV_0_DIV_DB_Pos);
}

uint8_t RCC_Deb_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_0 & RCC_CLK_DIV_0_DIV_DB_Msk) >> RCC_CLK_DIV_0_DIV_DB_Pos;
}

void RCC_FFT_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->CLK_DIV_0 &= ~RCC_CLK_DIV_0_DIV_FFT_Msk;
    RCC->CLK_DIV_0 |= (((uint32_t)CLK_Div) << RCC_CLK_DIV_0_DIV_FFT_Pos);
}

uint8_t RCC_FFT_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_0 & RCC_CLK_DIV_0_DIV_FFT_Msk) >> RCC_CLK_DIV_0_DIV_FFT_Pos;
}

void RCC_I2S_M_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->CLK_DIV_0 &= ~RCC_CLK_DIV_0_DIV_I2S_M_Msk;
    RCC->CLK_DIV_0 |= (((uint32_t)CLK_Div) << RCC_CLK_DIV_0_DIV_I2S_M_Pos);
}

uint8_t RCC_I2S_M_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_0 & RCC_CLK_DIV_0_DIV_I2S_M_Msk) >> RCC_CLK_DIV_0_DIV_I2S_M_Pos;
}

void RCC_I2S0_Set_ClkDiv(uint16_t CLK_Div)
{
    RCC->CLK_DIV_3 &= ~RCC_CLK_DIV_3_DIV_GI2S_0_Msk;
    RCC->CLK_DIV_3 |= ((uint32_t)CLK_Div);
}

uint16_t RCC_I2S0_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_3 & RCC_CLK_DIV_3_DIV_GI2S_0_Msk) >> RCC_CLK_DIV_3_DIV_GI2S_0_Pos;
}

void RCC_I2S1_Set_ClkDiv(uint16_t CLK_Div)
{
    RCC->CLK_DIV_3 &= ~RCC_CLK_DIV_3_DIV_GI2S_1_Msk;
    RCC->CLK_DIV_3 |= (((uint32_t)CLK_Div) << RCC_CLK_DIV_3_DIV_GI2S_1_Pos);
}

uint16_t RCC_I2S1_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_3 & RCC_CLK_DIV_3_DIV_GI2S_1_Msk) >> RCC_CLK_DIV_3_DIV_GI2S_1_Pos;
}

void RCC_PWM0_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->CLK_DIV_2 &= ~RCC_CLK_DIV_2_DIV_PWM0_Msk;
    RCC->CLK_DIV_2 |= (((uint32_t)CLK_Div));
}

uint8_t RCC_PWM0_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_2 & RCC_CLK_DIV_2_DIV_PWM0_Msk) >> RCC_CLK_DIV_2_DIV_PWM0_Pos;
}

void RCC_PWM1_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->CLK_DIV_2 &= ~RCC_CLK_DIV_2_DIV_PWM1_Msk;
    RCC->CLK_DIV_2 |= (((uint32_t)CLK_Div) << RCC_CLK_DIV_2_DIV_PWM1_Pos);
}

uint8_t RCC_PWM1_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_2 & RCC_CLK_DIV_2_DIV_PWM1_Msk) >> RCC_CLK_DIV_2_DIV_PWM1_Pos;
}

void RCC_QSPI_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->CLK_DIV_2 &= ~RCC_CLK_DIV_2_DIV_QSPI_Msk;
    RCC->CLK_DIV_2 |= (((uint32_t)CLK_Div) << RCC_CLK_DIV_2_DIV_QSPI_Pos);
}

uint8_t RCC_QSPI_Get_ClkDiv(void)
{
    return (RCC->CLK_DIV_2 & RCC_CLK_DIV_2_DIV_QSPI_Msk) >> RCC_CLK_DIV_2_DIV_QSPI_Pos;
}

void RCC_TIM0_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->TIM_DIV &= ~RCC_TIM_DIV_TIM0_DIV_Msk;
    RCC->TIM_DIV |= CLK_Div << RCC_TIM_DIV_TIM0_DIV_Pos;
}

uint8_t RCC_TIM0_Get_ClkDiv(void)
{
    return (RCC->TIM_DIV & RCC_TIM_DIV_TIM0_DIV_Msk) >> RCC_TIM_DIV_TIM0_DIV_Pos;
}

void RCC_TIM1_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->TIM_DIV &= ~RCC_TIM_DIV_TIM1_DIV_Msk;
    RCC->TIM_DIV |= CLK_Div << RCC_TIM_DIV_TIM1_DIV_Pos;
}

uint8_t RCC_TIM1_Get_ClkDiv(void)
{
    return (RCC->TIM_DIV & RCC_TIM_DIV_TIM1_DIV_Msk) >> RCC_TIM_DIV_TIM1_DIV_Pos;
}

void RCC_TIM2_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->TIM_DIV &= ~RCC_TIM_DIV_TIM2_DIV_Msk;
    RCC->TIM_DIV |= CLK_Div << RCC_TIM_DIV_TIM2_DIV_Pos;
}

uint8_t RCC_TIM2_Get_ClkDiv(void)
{
    return (RCC->TIM_DIV & RCC_TIM_DIV_TIM2_DIV_Msk) >> RCC_TIM_DIV_TIM2_DIV_Pos;
}

void RCC_TIM3_Set_ClkDiv(uint8_t CLK_Div)
{
    RCC->TIM_DIV &= ~RCC_TIM_DIV_TIM3_DIV_Msk;
    RCC->TIM_DIV |= CLK_Div << RCC_TIM_DIV_TIM3_DIV_Pos;
}

uint8_t RCC_TIM3_Get_ClkDiv(void)
{
    return (RCC->TIM_DIV & RCC_TIM_DIV_TIM3_DIV_Msk) >> RCC_TIM_DIV_TIM3_DIV_Pos;
}

void RCC_Peri_Rst(uint32_t Peri)
{
    /* Check the parameters */
    assert_param(IS_RCC_PERI(Peri));

    volatile int dummy = 0;

    RCC->RST_EN &= ~Peri;
    for(dummy= 0; dummy < 100; dummy++) {};
    RCC->RST_EN |= Peri;
}

void RCC_MemCfg(uint32_t Mode)
{
    /* Check the parameters */
    assert_param(IS_RCC_SRAMMODE(Mode));

    RCC->SYS_CFG &= ~RCC_SYS_CFG_MEM_CFG_Msk;
    RCC->SYS_CFG |= Mode;
}

void RCC_Config_Dma_Requst0_Reuse(FunctionalState NewState)
{
    if (NewState)
    {
        RCC->SYS_CFG |= (1 << RCC_SYS_CFG_DMA_REUSE_Pos);
    }
    else
    {
        RCC->SYS_CFG &= ~(1 << RCC_SYS_CFG_DMA_REUSE_Pos);
    }
}

void RCC_Config_Dma_Requst1_Reuse(FunctionalState NewState)
{
    if (NewState)
    {
        RCC->SYS_CFG |= (2 << RCC_SYS_CFG_DMA_REUSE_Pos);
    }
    else
    {
        RCC->SYS_CFG &= ~(2 << RCC_SYS_CFG_DMA_REUSE_Pos);
    }
}

void RCC_Config_Dma_Requst2_Reuse(FunctionalState NewState)
{
    if (NewState)
    {
        RCC->SYS_CFG |= (4 << RCC_SYS_CFG_DMA_REUSE_Pos);
    }
    else
    {
        RCC->SYS_CFG &= ~(4 << RCC_SYS_CFG_DMA_REUSE_Pos);
    }
}

void RCC_Config_Dma_Requst3_Reuse(FunctionalState NewState)
{
    if (NewState)
    {
        RCC->SYS_CFG |= (8 << RCC_SYS_CFG_DMA_REUSE_Pos);
    }
    else
    {
        RCC->SYS_CFG &= ~(8 << RCC_SYS_CFG_DMA_REUSE_Pos);
    }
}

FlagStatus RCC_SYSCLK_SELACK_GetStatBit(void)
{
    FlagStatus bitstatus = RESET;

    if ((RCC->CLK_SEL & RCC_CLK_SEL_SYSCLK_SELACK_Msk) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}
