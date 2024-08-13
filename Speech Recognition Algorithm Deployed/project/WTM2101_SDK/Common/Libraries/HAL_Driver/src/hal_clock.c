/**
* @file    hal_clock.c
* @brief   The Source Codes for the hal_clock Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

/** Includes */
#include "hal_clock.h"

static Hal_Clock_InitTypeDef hal_clock_instance = {
    ._24mosc_configuration.clock_hz = 24576000,
    ._24mosc_configuration.clock320k_hz = 320000,
    ._24mosc_configuration.clock_divider = 1,
};

static void HAL_Reset_PLL(int flag,int clock_frequency)
{
    uint32_t val = 0;
    val = 0;
    val |= (2 << PMU_PLL_0_PLL_DIG_CUR_SEL_Pos) & PMU_PLL_0_PLL_DIG_CUR_SEL_Msk;
    val |= (3 << PMU_PLL_0_PLL_CP_CUR_SEL_Pos) & PMU_PLL_0_PLL_CP_CUR_SEL_Msk;
    PMU->PLL_0 = val;

    val = 0;

    if(flag)
    {
      if(clock_frequency <= 4096000)
        val |= (7 << PMU_PLL_5_PLL_VCO_KVCO_SEL_Pos) & PMU_PLL_5_PLL_VCO_KVCO_SEL_Msk;
      else
        val |= (0 << PMU_PLL_5_PLL_VCO_KVCO_SEL_Pos) & PMU_PLL_5_PLL_VCO_KVCO_SEL_Msk;
    }

    val |= (1 << PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Pos) & PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Msk;
    val |= PMU_PLL_5_PLL_VCO_OPENLOOP_ENB_Msk;
    PMU->PLL_5 = val;
}

static void HAL_Startup_PLL(int plldiv)
{
    uint32_t val;

    val = 0;
    val |= (0x4 << PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Pos) & PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Msk;
    val |= (0x0 << PMU_PLL_4_PLL_DIV8_ENB_Pos) & PMU_PLL_4_PLL_DIV8_ENB_Msk;
    val |= (0x0 << PMU_PLL_4_PLL_VCO_BAND_SEL_Pos) & PMU_PLL_4_PLL_VCO_BAND_SEL_Msk;
    PMU->PLL_4 = val;

    val = 0;
    val |= (0x2 << PMU_PLL_1_PLL_LOOP_CAP1_SEL_Pos) & PMU_PLL_1_PLL_LOOP_CAP1_SEL_Msk;
    val |= (plldiv << PMU_PLL_1_PLL_DIV_Pos) & PMU_PLL_1_PLL_DIV_Msk;
    PMU->PLL_1 = val;
}

static void HAL_Update_Trim_And_OSC(int _24m_coarse,int _24m_fine,int _320k_coarse,int _320k_fine)
{
    /*trim 2bits clock source
     * 0: other
     * 1: from CPU
     * 2: from AFC
     *
     * trim module clock from cpu
     */
    PMU->SYS_CFG =
        (1 << PMU_SYS_CFG_REG_320K_TRIM_SEL_Pos) |
        (1 << PMU_SYS_CFG_REG_24M_TRIM_SEL_Pos);

    if ((_24m_coarse * 16 + _24m_fine) != 0) {
        PMU->_24M_TRIM_COARSE   = _24m_coarse;
        PMU->_24M_TRIM_FINE     = _24m_fine;
    } else {
        PMU->_24M_TRIM_COARSE   = 3;
        PMU->_24M_TRIM_FINE     = 19;
    }

    if ((_320k_coarse * 8 + _320k_fine) != 0) {
        PMU->_320K_TRIM =
            (_320k_coarse << PMU_320K_TRIM_REG_320K_TRIM_COARSE_Pos) |
            (_320k_fine << PMU_320K_TRIM_REG_320K_TRIM_FINE_Pos);
    } else {
        PMU->_320K_TRIM =
            (3 << PMU_320K_TRIM_REG_320K_TRIM_COARSE_Pos) |
            (10 << PMU_320K_TRIM_REG_320K_TRIM_FINE_Pos);
    }

    PMU->TRIM_RST = 1;
}

Hal_Clock_InitTypeDef* hal_clock_instance_get(void)
{
  return (&hal_clock_instance);
}

int hal_clock_init(Hal_Clock_InitTypeDef *clock_instance,int used_clock,Hal_Clock_SelectTypeDef system_clock,Hal_Clock_24mosc_Configuration *_24moc_config,int pll_factor,int ahb_divider,int apb_divider)
{
    if(!clock_instance)
        return -1;
    if((!(used_clock & HAL_CLOCK_24MOSC)) && (!(used_clock & HAL_CLOCK_PLL)) && (!(used_clock & HAL_CLOCK_10KOSC)) && (!(used_clock & HAL_CLOCK_320KOSC)) && (!(used_clock & HAL_CLOCK_XTL32K)))
        return -2;
    if(!_24moc_config)
        return -3;
    if((system_clock != HAL_CLOCK_24MOSC) && (system_clock != HAL_CLOCK_PLL) && (system_clock != HAL_CLOCK_10KOSC) && (system_clock != HAL_CLOCK_320KOSC) && (system_clock != HAL_CLOCK_XTL32K))
        return -4;

    clock_instance->need_use_clock = used_clock;
    clock_instance->system_clock_select_source = system_clock;
    memcpy(&(clock_instance->_24mosc_configuration),_24moc_config,sizeof(Hal_Clock_24mosc_Configuration));
    clock_instance->pllclock_upfrequency_coefficient = pll_factor;
    clock_instance->ahbbus_downfrequency_coefficient = ahb_divider;
    clock_instance->apbbus_downfrequency_coefficient = apb_divider;

    return 1;
}

int hal_clock_open(Hal_Clock_InitTypeDef *clock_instance)
{
    int ret = 10;
    uint16_t data[256] = {0};
    if(!clock_instance)
        return -1;

    /* enable the necessary clock source */
    PMU_Set_Clock_Source_Cmd(PMU, clock_instance->need_use_clock, ENABLE);
    if(clock_instance->need_use_clock & HAL_CLOCK_XTL32K)
    {
        PMU_Enable_External_Clock(PMU, ENABLE);
    }
    if(clock_instance->system_clock_select_source == HAL_CLOCK_PLL)
    {
        PMU_Set_Clock_Source_Cmd(PMU, HAL_CLOCK_24MOSC, ENABLE);
    }
    /* switch the system clock to internal 24mosc*/
    RCC_SYSClk_Sel(RCC_SYSCLK_Int24M);
    /* turn off the clock source that is not enabled */
    int dis_clk_src = (~(clock_instance->need_use_clock)) & (HAL_CLOCK_24MOSC | HAL_CLOCK_PLL);
    PMU_Set_Clock_Source_Cmd(PMU, dis_clk_src, DISABLE);

    if((clock_instance->system_clock_select_source == HAL_CLOCK_PLL) || (clock_instance->system_clock_select_source == HAL_CLOCK_24MOSC))
    {
        if(clock_instance->_24mosc_configuration.use_24mosc_way == HAL_CLOCK_24MOSC_EXTERNAL)
        {
            /* select the external xtal*/
            PMU_Set_Clock_Source_Cmd(PMU, HAL_CLOCK_XTL32K | HAL_CLOCK_320KOSC, ENABLE);
            /* switch the system clock to 320k*/
            RCC_SYSClk_Sel(RCC_SYSCLK_Int160K);
            PMU_Set_24M_Clock_Source_div(PMU, clock_instance->_24mosc_configuration.clock_divider);
            PMU_Enable_External_Clock(PMU, ENABLE);
            PMU_Select_24Mhz_Clock_Cmd(PMU, XTL_EXTERNAL_24M);
            HAL_Reset_PLL(1,clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider);
            if(clock_instance->system_clock_select_source == HAL_CLOCK_24MOSC)
            {
                /* set the ahb and apb0 bus divider */
                RCC_AHB_Set_ClkDiv(clock_instance->ahbbus_downfrequency_coefficient - 1);
                RCC_APB0_Set_ClkDiv(clock_instance->apbbus_downfrequency_coefficient - 1);
                clock_instance->system_clock_frequency = clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider;
                RCC_SYSClk_Sel(RCC_SYSCLK_Int24M);
                PMU_Set_Clock_Source_Cmd(PMU, HAL_CLOCK_320KOSC, DISABLE);
                return 1;
            }
            /* switch the system clock to PLL */
            if(clock_instance->pllclock_upfrequency_coefficient == 6)
            {
                *((uint32_t *)0x40002070) = 0x00000016;
                *((uint32_t *)0x40002084) = 0x00000003;
            }
            HAL_Startup_PLL(clock_instance->pllclock_upfrequency_coefficient);
            system_delay_us(2000);
            RCC_SYSClk_Sel(RCC_SYSCLK_IntPLL);
            PMU_Set_Clock_Source_Cmd(PMU, HAL_CLOCK_320KOSC, DISABLE);
            RCC_AHB_Set_ClkDiv(clock_instance->ahbbus_downfrequency_coefficient - 1);
            RCC_APB0_Set_ClkDiv(clock_instance->apbbus_downfrequency_coefficient - 1);
            clock_instance->system_clock_frequency = clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider * clock_instance->pllclock_upfrequency_coefficient;
        }
        else
        {
            if(clock_instance->_24mosc_configuration.internal_24mosc_calibration_flag)
            {
                PMU_Set_24M_Clock_Source_div(PMU, clock_instance->_24mosc_configuration.clock_divider);
                PMU_Select_24Mhz_Clock_Cmd(PMU, OSC_INTERNAL_24M);
                if(clock_instance->_24mosc_configuration.calibration_way == HAL_CLOCK_24MOSC_USE_NPU_CALIBRATION_PARAMETER)
                {
                     /*use NPU calibration parameter */
                     NPU_Init();
                     system_delay_ms(10);
                     ret = NPU_READ_TRIM(data);
                     ret = NPU_USE_TRIM(data);
                     if((ret == 0) || (ret == 1)) ret = 1;
                     else ret = -2;
                     clock_instance->_24m_coarse = data[128];
                     clock_instance->_24m_fine   = data[129];
                     clock_instance->_320k_coarse = data[130];
                     clock_instance->_320k_fine   = data[131];

                     HAL_Update_Trim_And_OSC(clock_instance->_24m_coarse,clock_instance->_24m_fine,clock_instance->_320k_coarse,clock_instance->_320k_fine);
                }
                else
                {
                     /*use xtal32k calibration */
                     clock_instance->_24mosc_configuration.clock_hz = osc_24m_calibration_start();
                     clock_instance->_24mosc_configuration.clock320k_hz = osc_320k_calibration_start();
                }
            }

            HAL_Reset_PLL(0,clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider);
            if(clock_instance->system_clock_select_source == HAL_CLOCK_24MOSC)
            {
                /* set the ahb and apb0 bus divider */
                RCC_AHB_Set_ClkDiv(clock_instance->ahbbus_downfrequency_coefficient - 1);
                RCC_APB0_Set_ClkDiv(clock_instance->apbbus_downfrequency_coefficient - 1);
                clock_instance->system_clock_frequency = clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider;
                return 1;
            }
            /* switch the system clock to PLL */
            if(clock_instance->pllclock_upfrequency_coefficient == 6)
            {
                *((uint32_t *)0x40002070) = 0x00000016;
                *((uint32_t *)0x40002084) = 0x00000003;
            }
            HAL_Startup_PLL(clock_instance->pllclock_upfrequency_coefficient);
            system_delay_us(200);

            RCC_SYSClk_Sel(RCC_SYSCLK_IntPLL);
            RCC_AHB_Set_ClkDiv(clock_instance->ahbbus_downfrequency_coefficient - 1);
            RCC_APB0_Set_ClkDiv(clock_instance->apbbus_downfrequency_coefficient - 1);
            clock_instance->system_clock_frequency = clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider * clock_instance->pllclock_upfrequency_coefficient;
        }
    }

    return ret;
}

int hal_clock_ctl(Hal_Clock_InitTypeDef *clock_instance,int command, ...)
{
    va_list ParamList;
    volatile int value = 0;

    if (clock_instance == NULL) 
        return -1;
    va_start(ParamList, command);

    switch(command)
    {
        case HAL_CLOCK_SWITCH_SYSTEM_CLOCK_COMMAND:
        {
            value = va_arg(ParamList, int);
            switch(value)
            {
                case HAL_CLOCK_24MOSC:
                    PMU_Set_Clock_Source_Cmd(PMU, HAL_CLOCK_24MOSC, ENABLE);
                    RCC_SYSClk_Sel(RCC_SYSCLK_Int24M);
                    system_delay_us(200);
                    PMU_Set_Clock_Source_Cmd(PMU, HAL_CLOCK_PLL, DISABLE);

                    RCC_AHB_Set_ClkDiv(clock_instance->ahbbus_downfrequency_coefficient - 1);
                    RCC_APB0_Set_ClkDiv(clock_instance->apbbus_downfrequency_coefficient - 1);
                    clock_instance->system_clock_frequency = clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider;
                break;

                case HAL_CLOCK_PLL:
                    PMU_Set_Clock_Source_Cmd(PMU, HAL_CLOCK_24MOSC | HAL_CLOCK_PLL, ENABLE);
                    HAL_Reset_PLL(0,clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider);
                    /* switch the system clock to PLL */
                    if(clock_instance->pllclock_upfrequency_coefficient == 6)
                    {
                        *((uint32_t *)0x40002070) = 0x00000016;
                        *((uint32_t *)0x40002084) = 0x00000003;
                    }
                    HAL_Startup_PLL(clock_instance->pllclock_upfrequency_coefficient);
                    system_delay_us(200);

                    RCC_SYSClk_Sel(RCC_SYSCLK_IntPLL);
                    RCC_AHB_Set_ClkDiv(clock_instance->ahbbus_downfrequency_coefficient - 1);
                    RCC_APB0_Set_ClkDiv(clock_instance->apbbus_downfrequency_coefficient - 1);
                    clock_instance->system_clock_frequency = clock_instance->_24mosc_configuration.clock_hz / clock_instance->_24mosc_configuration.clock_divider * clock_instance->pllclock_upfrequency_coefficient;

                break;

                case HAL_CLOCK_10KOSC:
                    RCC_SYSClk_Sel(RCC_SYSCLK_Int10K);
                break;

                case HAL_CLOCK_320KOSC:
                    PMU_Set_Clock_Source_Cmd(PMU, HAL_CLOCK_320KOSC, ENABLE);
                    RCC_SYSClk_Sel(RCC_SYSCLK_Int160K);
                break;

                case HAL_CLOCK_XTL32K:
                    RCC_SYSClk_Sel(RCC_SYSCLK_Ext32K);
                break;
            }
            break;
        }

        default:
            return -10;
    }

    va_end(ParamList);

    return 1;
}

int hal_clock_close(Hal_Clock_InitTypeDef *clock_instance)
{
    if(!clock_instance)
        return -1;

    return 1;
}
