/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 RCC register.
  * @date    2023-03-20
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Mon Mar 20 11:31:58 2023/////////////


#ifndef __WTM2101_RCC_REGISTER_H_INCLUDED__
#define __WTM2101_RCC_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// CLK_DIV_0
//
#define RCC_CLK_DIV_0_DIV_DB_Pos                                                24
#define RCC_CLK_DIV_0_DIV_DB_Msk                                                (0xffU << RCC_CLK_DIV_0_DIV_DB_Pos)

#define RCC_CLK_DIV_0_DIV_FFT_Pos                                               16
#define RCC_CLK_DIV_0_DIV_FFT_Msk                                               (0xffU << RCC_CLK_DIV_0_DIV_FFT_Pos)

#define RCC_CLK_DIV_0_DIV_I2S_M_Pos                                             8
#define RCC_CLK_DIV_0_DIV_I2S_M_Msk                                             (0xffU << RCC_CLK_DIV_0_DIV_I2S_M_Pos)

#define RCC_CLK_DIV_0_DIV_AHB_Pos                                               0
#define RCC_CLK_DIV_0_DIV_AHB_Msk                                               (0xffU << RCC_CLK_DIV_0_DIV_AHB_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLK_SEL
//
#define RCC_CLK_SEL_DBCLK_SELACK_Pos                                            13
#define RCC_CLK_SEL_DBCLK_SELACK_Msk                                            (0x1U << RCC_CLK_SEL_DBCLK_SELACK_Pos)

#define RCC_CLK_SEL_DBCLK_SEL_Pos                                               12
#define RCC_CLK_SEL_DBCLK_SEL_Msk                                               (0x1U << RCC_CLK_SEL_DBCLK_SEL_Pos)

#define RCC_CLK_SEL_SYSTICK_SEL_Pos                                             8
#define RCC_CLK_SEL_SYSTICK_SEL_Msk                                             (0x3U << RCC_CLK_SEL_SYSTICK_SEL_Pos)

#define RCC_CLK_SEL_SYSCLK_SELACK_Pos                                           7
#define RCC_CLK_SEL_SYSCLK_SELACK_Msk                                           (0x1U << RCC_CLK_SEL_SYSCLK_SELACK_Pos)

#define RCC_CLK_SEL_SYSCLK_SEL_Pos                                              0
#define RCC_CLK_SEL_SYSCLK_SEL_Msk                                              (0x7U << RCC_CLK_SEL_SYSCLK_SEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLK_EN
//
#define RCC_CLK_EN_APB0_CLKEN_Pos                                               31
#define RCC_CLK_EN_APB0_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_APB0_CLKEN_Pos)

#define RCC_CLK_EN_AHB1_CLKEN_Pos                                               30
#define RCC_CLK_EN_AHB1_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_AHB1_CLKEN_Pos)

#define RCC_CLK_EN_AHB2_CLKEN_Pos                                               29
#define RCC_CLK_EN_AHB2_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_AHB2_CLKEN_Pos)

#define RCC_CLK_EN_EXFLASH_CLKEN_Pos                                            28
#define RCC_CLK_EN_EXFLASH_CLKEN_Msk                                            (0x1U << RCC_CLK_EN_EXFLASH_CLKEN_Pos)

#define RCC_CLK_EN_DAC_CLKEN_Pos                                                27
#define RCC_CLK_EN_DAC_CLKEN_Msk                                                (0x1U << RCC_CLK_EN_DAC_CLKEN_Pos)

#define RCC_CLK_EN_I2S0_CLKEN_Pos                                               26
#define RCC_CLK_EN_I2S0_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_I2S0_CLKEN_Pos)

#define RCC_CLK_EN_SPIS_CLKEN_Pos                                               25
#define RCC_CLK_EN_SPIS_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_SPIS_CLKEN_Pos)

#define RCC_CLK_EN_AUD_PCLKEN_Pos                                               24
#define RCC_CLK_EN_AUD_PCLKEN_Msk                                               (0x1U << RCC_CLK_EN_AUD_PCLKEN_Pos)

#define RCC_CLK_EN_TRIM_CLKEN_Pos                                               23
#define RCC_CLK_EN_TRIM_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_TRIM_CLKEN_Pos)

#define RCC_CLK_EN_I2S_MCLKEN_Pos                                               22
#define RCC_CLK_EN_I2S_MCLKEN_Msk                                               (0x1U << RCC_CLK_EN_I2S_MCLKEN_Pos)

#define RCC_CLK_EN_FFT_CLKEN_Pos                                                21
#define RCC_CLK_EN_FFT_CLKEN_Msk                                                (0x1U << RCC_CLK_EN_FFT_CLKEN_Pos)

#define RCC_CLK_EN_AUD_CLKEN_Pos                                                20
#define RCC_CLK_EN_AUD_CLKEN_Msk                                                (0x1U << RCC_CLK_EN_AUD_CLKEN_Pos)

#define RCC_CLK_EN_DB_CLKEN_Pos                                                 19
#define RCC_CLK_EN_DB_CLKEN_Msk                                                 (0x1U << RCC_CLK_EN_DB_CLKEN_Pos)

#define RCC_CLK_EN_PWM1_CLKEN_Pos                                               18
#define RCC_CLK_EN_PWM1_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_PWM1_CLKEN_Pos)

#define RCC_CLK_EN_PWM0_CLKEN_Pos                                               17
#define RCC_CLK_EN_PWM0_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_PWM0_CLKEN_Pos)

#define RCC_CLK_EN_QSPI_CLKEN_Pos                                               16
#define RCC_CLK_EN_QSPI_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_QSPI_CLKEN_Pos)

#define RCC_CLK_EN_SPIM_CLKEN_Pos                                               15
#define RCC_CLK_EN_SPIM_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_SPIM_CLKEN_Pos)

#define RCC_CLK_EN_I2S1_CLKEN_Pos                                               14
#define RCC_CLK_EN_I2S1_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_I2S1_CLKEN_Pos)

#define RCC_CLK_EN_GPIO_HCLKEN_Pos                                              13
#define RCC_CLK_EN_GPIO_HCLKEN_Msk                                              (0x1U << RCC_CLK_EN_GPIO_HCLKEN_Pos)

#define RCC_CLK_EN_TIME_CLKEN_Pos                                               9
#define RCC_CLK_EN_TIME_CLKEN_Msk                                               (0x1U << RCC_CLK_EN_TIME_CLKEN_Pos)

#define RCC_CLK_EN_I2C_CLKEN_Pos                                                8
#define RCC_CLK_EN_I2C_CLKEN_Msk                                                (0x1U << RCC_CLK_EN_I2C_CLKEN_Pos)

#define RCC_CLK_EN_UART1_CLKEN_Pos                                              7
#define RCC_CLK_EN_UART1_CLKEN_Msk                                              (0x1U << RCC_CLK_EN_UART1_CLKEN_Pos)

#define RCC_CLK_EN_UART0_CLKEN_Pos                                              6
#define RCC_CLK_EN_UART0_CLKEN_Msk                                              (0x1U << RCC_CLK_EN_UART0_CLKEN_Pos)

#define RCC_CLK_EN_PMU_PCLKEN_Pos                                               5
#define RCC_CLK_EN_PMU_PCLKEN_Msk                                               (0x1U << RCC_CLK_EN_PMU_PCLKEN_Pos)

#define RCC_CLK_EN_RTC_PCLKEN_Pos                                               4
#define RCC_CLK_EN_RTC_PCLKEN_Msk                                               (0x1U << RCC_CLK_EN_RTC_PCLKEN_Pos)

#define RCC_CLK_EN_WDT_PCLKEN_Pos                                               3
#define RCC_CLK_EN_WDT_PCLKEN_Msk                                               (0x1U << RCC_CLK_EN_WDT_PCLKEN_Pos)

#define RCC_CLK_EN_DMA_CLKEN_Pos                                                2
#define RCC_CLK_EN_DMA_CLKEN_Msk                                                (0x1U << RCC_CLK_EN_DMA_CLKEN_Pos)

#define RCC_CLK_EN_FLASH_REG_CLKEN_Pos                                          1
#define RCC_CLK_EN_FLASH_REG_CLKEN_Msk                                          (0x1U << RCC_CLK_EN_FLASH_REG_CLKEN_Pos)

#define RCC_CLK_EN_FLASH_CLKEN_Pos                                              0
#define RCC_CLK_EN_FLASH_CLKEN_Msk                                              (0x1U << RCC_CLK_EN_FLASH_CLKEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RST_EN
//
#define RCC_RST_EN_DAC_RSTN_Pos                                                 27
#define RCC_RST_EN_DAC_RSTN_Msk                                                 (0x1U << RCC_RST_EN_DAC_RSTN_Pos)

#define RCC_RST_EN_I2S0_RSTN_Pos                                                26
#define RCC_RST_EN_I2S0_RSTN_Msk                                                (0x1U << RCC_RST_EN_I2S0_RSTN_Pos)

#define RCC_RST_EN_SPIS_RSTN_Pos                                                25
#define RCC_RST_EN_SPIS_RSTN_Msk                                                (0x1U << RCC_RST_EN_SPIS_RSTN_Pos)

#define RCC_RST_EN_AUD_HRSTN_Pos                                                24
#define RCC_RST_EN_AUD_HRSTN_Msk                                                (0x1U << RCC_RST_EN_AUD_HRSTN_Pos)

#define RCC_RST_EN_TRIM_RSTN_Pos                                                23
#define RCC_RST_EN_TRIM_RSTN_Msk                                                (0x1U << RCC_RST_EN_TRIM_RSTN_Pos)

#define RCC_RST_EN_FFT_RSTN_Pos                                                 21
#define RCC_RST_EN_FFT_RSTN_Msk                                                 (0x1U << RCC_RST_EN_FFT_RSTN_Pos)

#define RCC_RST_EN_AUD_RSTN_Pos                                                 20
#define RCC_RST_EN_AUD_RSTN_Msk                                                 (0x1U << RCC_RST_EN_AUD_RSTN_Pos)

#define RCC_RST_EN_DB_RSTN_Pos                                                  19
#define RCC_RST_EN_DB_RSTN_Msk                                                  (0x1U << RCC_RST_EN_DB_RSTN_Pos)

#define RCC_RST_EN_PWM1_RSTN_Pos                                                18
#define RCC_RST_EN_PWM1_RSTN_Msk                                                (0x1U << RCC_RST_EN_PWM1_RSTN_Pos)

#define RCC_RST_EN_PWM0_RSTN_Pos                                                17
#define RCC_RST_EN_PWM0_RSTN_Msk                                                (0x1U << RCC_RST_EN_PWM0_RSTN_Pos)

#define RCC_RST_EN_QSPI_RSTN_Pos                                                16
#define RCC_RST_EN_QSPI_RSTN_Msk                                                (0x1U << RCC_RST_EN_QSPI_RSTN_Pos)

#define RCC_RST_EN_SPIM_RSTN_Pos                                                15
#define RCC_RST_EN_SPIM_RSTN_Msk                                                (0x1U << RCC_RST_EN_SPIM_RSTN_Pos)

#define RCC_RST_EN_I2S1_RSTN_Pos                                                14
#define RCC_RST_EN_I2S1_RSTN_Msk                                                (0x1U << RCC_RST_EN_I2S1_RSTN_Pos)

#define RCC_RST_EN_GPIO_RSTN_Pos                                                13
#define RCC_RST_EN_GPIO_RSTN_Msk                                                (0x1U << RCC_RST_EN_GPIO_RSTN_Pos)

#define RCC_RST_EN_TIME3_RSTN_Pos                                               12
#define RCC_RST_EN_TIME3_RSTN_Msk                                               (0x1U << RCC_RST_EN_TIME3_RSTN_Pos)

#define RCC_RST_EN_TIME2_RSTN_Pos                                               11
#define RCC_RST_EN_TIME2_RSTN_Msk                                               (0x1U << RCC_RST_EN_TIME2_RSTN_Pos)

#define RCC_RST_EN_TIME1_RSTN_Pos                                               10
#define RCC_RST_EN_TIME1_RSTN_Msk                                               (0x1U << RCC_RST_EN_TIME1_RSTN_Pos)

#define RCC_RST_EN_TIME0_RSTN_Pos                                               9
#define RCC_RST_EN_TIME0_RSTN_Msk                                               (0x1U << RCC_RST_EN_TIME0_RSTN_Pos)

#define RCC_RST_EN_I2C_RSTN_Pos                                                 8
#define RCC_RST_EN_I2C_RSTN_Msk                                                 (0x1U << RCC_RST_EN_I2C_RSTN_Pos)

#define RCC_RST_EN_UART1_RSTN_Pos                                               7
#define RCC_RST_EN_UART1_RSTN_Msk                                               (0x1U << RCC_RST_EN_UART1_RSTN_Pos)

#define RCC_RST_EN_UART0_RSTN_Pos                                               6
#define RCC_RST_EN_UART0_RSTN_Msk                                               (0x1U << RCC_RST_EN_UART0_RSTN_Pos)

#define RCC_RST_EN_PMU_PRSTN_Pos                                                5
#define RCC_RST_EN_PMU_PRSTN_Msk                                                (0x1U << RCC_RST_EN_PMU_PRSTN_Pos)

#define RCC_RST_EN_RTC_PRSTN_Pos                                                4
#define RCC_RST_EN_RTC_PRSTN_Msk                                                (0x1U << RCC_RST_EN_RTC_PRSTN_Pos)

#define RCC_RST_EN_WDT_PRSTN_Pos                                                3
#define RCC_RST_EN_WDT_PRSTN_Msk                                                (0x1U << RCC_RST_EN_WDT_PRSTN_Pos)

#define RCC_RST_EN_DMA_RSTN_Pos                                                 2
#define RCC_RST_EN_DMA_RSTN_Msk                                                 (0x1U << RCC_RST_EN_DMA_RSTN_Pos)

#define RCC_RST_EN_FLASH_REG_RSTN_Pos                                           1
#define RCC_RST_EN_FLASH_REG_RSTN_Msk                                           (0x1U << RCC_RST_EN_FLASH_REG_RSTN_Pos)

#define RCC_RST_EN_FLASH_RSTN_Pos                                               0
#define RCC_RST_EN_FLASH_RSTN_Msk                                               (0x1U << RCC_RST_EN_FLASH_RSTN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIM_DIV
//
#define RCC_TIM_DIV_TIM3_DIV_Pos                                                24
#define RCC_TIM_DIV_TIM3_DIV_Msk                                                (0xffU << RCC_TIM_DIV_TIM3_DIV_Pos)

#define RCC_TIM_DIV_TIM2_DIV_Pos                                                16
#define RCC_TIM_DIV_TIM2_DIV_Msk                                                (0xffU << RCC_TIM_DIV_TIM2_DIV_Pos)

#define RCC_TIM_DIV_TIM1_DIV_Pos                                                8
#define RCC_TIM_DIV_TIM1_DIV_Msk                                                (0xffU << RCC_TIM_DIV_TIM1_DIV_Pos)

#define RCC_TIM_DIV_TIM0_DIV_Pos                                                0
#define RCC_TIM_DIV_TIM0_DIV_Msk                                                (0xffU << RCC_TIM_DIV_TIM0_DIV_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLK_DIV_1
//
#define RCC_CLK_DIV_1_DIV_SPIM_Pos                                              24
#define RCC_CLK_DIV_1_DIV_SPIM_Msk                                              (0xffU << RCC_CLK_DIV_1_DIV_SPIM_Pos)

#define RCC_CLK_DIV_1_DIV_SPIS_Pos                                              16
#define RCC_CLK_DIV_1_DIV_SPIS_Msk                                              (0xffU << RCC_CLK_DIV_1_DIV_SPIS_Pos)

#define RCC_CLK_DIV_1_DIV_APB0_Pos                                              0
#define RCC_CLK_DIV_1_DIV_APB0_Msk                                              (0xfU << RCC_CLK_DIV_1_DIV_APB0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SYS_CFG
//
#define RCC_SYS_CFG_MEM_CFG_Pos                                                 31
#define RCC_SYS_CFG_MEM_CFG_Msk                                                 (0x1U << RCC_SYS_CFG_MEM_CFG_Pos)

#define RCC_SYS_CFG_DMA_REUSE_Pos                                               8
#define RCC_SYS_CFG_DMA_REUSE_Msk                                               (0xfU << RCC_SYS_CFG_DMA_REUSE_Pos)

#define RCC_SYS_CFG_ADC_CLKO_EN_Pos                                             7
#define RCC_SYS_CFG_ADC_CLKO_EN_Msk                                             (0x1U << RCC_SYS_CFG_ADC_CLKO_EN_Pos)

#define RCC_SYS_CFG_NNVAD_ST_Pos                                                5
#define RCC_SYS_CFG_NNVAD_ST_Msk                                                (0x1U << RCC_SYS_CFG_NNVAD_ST_Pos)

#define RCC_SYS_CFG_NPU_BOOT_ST_Pos                                             4
#define RCC_SYS_CFG_NPU_BOOT_ST_Msk                                             (0x1U << RCC_SYS_CFG_NPU_BOOT_ST_Pos)

#define RCC_SYS_CFG_NPU_BOOT_STATUS_Pos                                         3
#define RCC_SYS_CFG_NPU_BOOT_STATUS_Msk                                         (0x1U << RCC_SYS_CFG_NPU_BOOT_STATUS_Pos)

#define RCC_SYS_CFG_NPU_AGV_SEL_Pos                                             2
#define RCC_SYS_CFG_NPU_AGV_SEL_Msk                                             (0x1U << RCC_SYS_CFG_NPU_AGV_SEL_Pos)

#define RCC_SYS_CFG_NPU_IBUS_SEL_Pos                                            1
#define RCC_SYS_CFG_NPU_IBUS_SEL_Msk                                            (0x0U << RCC_SYS_CFG_NPU_IBUS_SEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLK_DIV_2
//
#define RCC_CLK_DIV_2_DIV_QSPI_Pos                                              16
#define RCC_CLK_DIV_2_DIV_QSPI_Msk                                              (0xffU << RCC_CLK_DIV_2_DIV_QSPI_Pos)

#define RCC_CLK_DIV_2_DIV_PWM1_Pos                                              8
#define RCC_CLK_DIV_2_DIV_PWM1_Msk                                              (0xffU << RCC_CLK_DIV_2_DIV_PWM1_Pos)

#define RCC_CLK_DIV_2_DIV_PWM0_Pos                                              0
#define RCC_CLK_DIV_2_DIV_PWM0_Msk                                              (0xffU << RCC_CLK_DIV_2_DIV_PWM0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLK_DIV_3
//
#define RCC_CLK_DIV_3_DIV_GI2S_1_Pos                                            16
#define RCC_CLK_DIV_3_DIV_GI2S_1_Msk                                            (0xfffU << RCC_CLK_DIV_3_DIV_GI2S_1_Pos)

#define RCC_CLK_DIV_3_DIV_GI2S_0_Pos                                            0
#define RCC_CLK_DIV_3_DIV_GI2S_0_Msk                                            (0xfffU << RCC_CLK_DIV_3_DIV_GI2S_0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PMUX_C0
//
#define RCC_PMUX_C0_PAD15_CFG_Pos                                               30
#define RCC_PMUX_C0_PAD15_CFG_Msk                                               (0x3U << RCC_PMUX_C0_PAD15_CFG_Pos)

#define RCC_PMUX_C0_PAD14_CFG_Pos                                               28
#define RCC_PMUX_C0_PAD14_CFG_Msk                                               (0x3U << RCC_PMUX_C0_PAD14_CFG_Pos)

#define RCC_PMUX_C0_PAD13_CFG_Pos                                               26
#define RCC_PMUX_C0_PAD13_CFG_Msk                                               (0x3U << RCC_PMUX_C0_PAD13_CFG_Pos)

#define RCC_PMUX_C0_PAD12_CFG_Pos                                               24
#define RCC_PMUX_C0_PAD12_CFG_Msk                                               (0x3U << RCC_PMUX_C0_PAD12_CFG_Pos)

#define RCC_PMUX_C0_PAD11_CFG_Pos                                               22
#define RCC_PMUX_C0_PAD11_CFG_Msk                                               (0x3U << RCC_PMUX_C0_PAD11_CFG_Pos)

#define RCC_PMUX_C0_PAD10_CFG_Pos                                               20
#define RCC_PMUX_C0_PAD10_CFG_Msk                                               (0x3U << RCC_PMUX_C0_PAD10_CFG_Pos)

#define RCC_PMUX_C0_PAD9_CFG_Pos                                                18
#define RCC_PMUX_C0_PAD9_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD9_CFG_Pos)

#define RCC_PMUX_C0_PAD8_CFG_Pos                                                16
#define RCC_PMUX_C0_PAD8_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD8_CFG_Pos)

#define RCC_PMUX_C0_PAD7_CFG_Pos                                                14
#define RCC_PMUX_C0_PAD7_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD7_CFG_Pos)

#define RCC_PMUX_C0_PAD6_CFG_Pos                                                12
#define RCC_PMUX_C0_PAD6_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD6_CFG_Pos)

#define RCC_PMUX_C0_PAD5_CFG_Pos                                                10
#define RCC_PMUX_C0_PAD5_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD5_CFG_Pos)

#define RCC_PMUX_C0_PAD4_CFG_Pos                                                8
#define RCC_PMUX_C0_PAD4_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD4_CFG_Pos)

#define RCC_PMUX_C0_PAD3_CFG_Pos                                                6
#define RCC_PMUX_C0_PAD3_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD3_CFG_Pos)

#define RCC_PMUX_C0_PAD2_CFG_Pos                                                4
#define RCC_PMUX_C0_PAD2_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD2_CFG_Pos)

#define RCC_PMUX_C0_PAD1_CFG_Pos                                                2
#define RCC_PMUX_C0_PAD1_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD1_CFG_Pos)

#define RCC_PMUX_C0_PAD0_CFG_Pos                                                0
#define RCC_PMUX_C0_PAD0_CFG_Msk                                                (0x3U << RCC_PMUX_C0_PAD0_CFG_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PMUX_C1
//
#define RCC_PMUX_C1_PAD19_CFG_Pos                                               6
#define RCC_PMUX_C1_PAD19_CFG_Msk                                               (0x3U << RCC_PMUX_C1_PAD19_CFG_Pos)

#define RCC_PMUX_C1_PAD18_CFG_Pos                                               4
#define RCC_PMUX_C1_PAD18_CFG_Msk                                               (0x3U << RCC_PMUX_C1_PAD18_CFG_Pos)

#define RCC_PMUX_C1_PAD17_CFG_Pos                                               2
#define RCC_PMUX_C1_PAD17_CFG_Msk                                               (0x3U << RCC_PMUX_C1_PAD17_CFG_Pos)

#define RCC_PMUX_C1_PAD16_CFG_Pos                                               0
#define RCC_PMUX_C1_PAD16_CFG_Msk                                               (0x3U << RCC_PMUX_C1_PAD16_CFG_Pos)

#endif //__WTM2101_RCC_REGISTER_H_INCLUDED__