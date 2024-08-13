/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 PMU register.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Sat Aug 21 12:46:34 2021/////////////


#ifndef __WTM2101_PMU_REGISTER_H_INCLUDED__
#define __WTM2101_PMU_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// PMU_CTL
//
#define PMU_PMU_CTL_PDDS_Pos                                                    7
#define PMU_PMU_CTL_PDDS_Msk                                                    (0x1U << PMU_PMU_CTL_PDDS_Pos)

#define PMU_PMU_CTL_OSC320K_EN_Pos                                              6
#define PMU_PMU_CTL_OSC320K_EN_Msk                                              (0x1U << PMU_PMU_CTL_OSC320K_EN_Pos)

#define PMU_PMU_CTL_OSC_EN_Pos                                                  5
#define PMU_PMU_CTL_OSC_EN_Msk                                                  (0x1U << PMU_PMU_CTL_OSC_EN_Pos)

#define PMU_PMU_CTL_OSC24M_EN_Pos                                               4
#define PMU_PMU_CTL_OSC24M_EN_Msk                                               (0x1U << PMU_PMU_CTL_OSC24M_EN_Pos)

#define PMU_PMU_CTL_AUD_CLKEN_Pos                                               3
#define PMU_PMU_CTL_AUD_CLKEN_Msk                                               (0x1U << PMU_PMU_CTL_AUD_CLKEN_Pos)

#define PMU_PMU_CTL_OSC10K_EN_Pos                                               2
#define PMU_PMU_CTL_OSC10K_EN_Msk                                               (0x1U << PMU_PMU_CTL_OSC10K_EN_Pos)

#define PMU_PMU_CTL_XTL32K_EN_Pos                                               1
#define PMU_PMU_CTL_XTL32K_EN_Msk                                               (0x1U << PMU_PMU_CTL_XTL32K_EN_Pos)

#define PMU_PMU_CTL_PLL_EN_Pos                                                  0
#define PMU_PMU_CTL_PLL_EN_Msk                                                  (0x1U << PMU_PMU_CTL_PLL_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSM_CTL
//
#define PMU_DSM_CTL_RSV0_Pos                                                    7
#define PMU_DSM_CTL_RSV0_Msk                                                    (0x1U << PMU_DSM_CTL_RSV0_Pos)

#define PMU_DSM_CTL_PIN_WENB_Pos                                                6
#define PMU_DSM_CTL_PIN_WENB_Msk                                                (0x1U << PMU_DSM_CTL_PIN_WENB_Pos)

#define PMU_DSM_CTL_RSV1_Pos                                                    0
#define PMU_DSM_CTL_RSV1_Msk                                                    (0xfU << PMU_DSM_CTL_RSV1_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RSM_CTL
//
#define PMU_RSM_CTL_KEEP_AUDIO_Pos                                              7
#define PMU_RSM_CTL_KEEP_AUDIO_Msk                                              (0x1U << PMU_RSM_CTL_KEEP_AUDIO_Pos)

#define PMU_RSM_CTL_KEEP_OSC10K_Pos                                             6
#define PMU_RSM_CTL_KEEP_OSC10K_Msk                                             (0x1U << PMU_RSM_CTL_KEEP_OSC10K_Pos)

#define PMU_RSM_CTL_KEEP_XTL32K_Pos                                             5
#define PMU_RSM_CTL_KEEP_XTL32K_Msk                                             (0x1U << PMU_RSM_CTL_KEEP_XTL32K_Pos)

#define PMU_RSM_CTL_KEEP_OSC2M_Pos                                              4
#define PMU_RSM_CTL_KEEP_OSC2M_Msk                                              (0x1U << PMU_RSM_CTL_KEEP_OSC2M_Pos)

#define PMU_RSM_CTL_FLASH_KEEP_Pos                                              3
#define PMU_RSM_CTL_FLASH_KEEP_Msk                                              (0x1U << PMU_RSM_CTL_FLASH_KEEP_Pos)

#define PMU_RSM_CTL_WDT_KEEP_Pos                                                2
#define PMU_RSM_CTL_WDT_KEEP_Msk                                                (0x1U << PMU_RSM_CTL_WDT_KEEP_Pos)

#define PMU_RSM_CTL_VDD3_KEEP_Pos                                               1
#define PMU_RSM_CTL_VDD3_KEEP_Msk                                               (0x1U << PMU_RSM_CTL_VDD3_KEEP_Pos)

#define PMU_RSM_CTL_VDD_KEEP_Pos                                                0
#define PMU_RSM_CTL_VDD_KEEP_Msk                                                (0x1U << PMU_RSM_CTL_VDD_KEEP_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FLAG_CTL
//
#define PMU_FLAG_CTL_PORB_RST_FLAG_Pos                                          7
#define PMU_FLAG_CTL_PORB_RST_FLAG_Msk                                          (0x1U << PMU_FLAG_CTL_PORB_RST_FLAG_Pos)

#define PMU_FLAG_CTL_RSV_Pos                                                    6
#define PMU_FLAG_CTL_RSV_Msk                                                    (0x1U << PMU_FLAG_CTL_RSV_Pos)

#define PMU_FLAG_CTL_PIN_WU_FLAG_Pos                                            5
#define PMU_FLAG_CTL_PIN_WU_FLAG_Msk                                            (0x1U << PMU_FLAG_CTL_PIN_WU_FLAG_Pos)

#define PMU_FLAG_CTL_RSM0_WU_FLAG_Pos                                           4
#define PMU_FLAG_CTL_RSM0_WU_FLAG_Msk                                           (0x1U << PMU_FLAG_CTL_RSM0_WU_FLAG_Pos)

#define PMU_FLAG_CTL_RSM1_WU_FLAG_Pos                                           3
#define PMU_FLAG_CTL_RSM1_WU_FLAG_Msk                                           (0x1U << PMU_FLAG_CTL_RSM1_WU_FLAG_Pos)

#define PMU_FLAG_CTL_PIN_RST_FLAG_Pos                                           2
#define PMU_FLAG_CTL_PIN_RST_FLAG_Msk                                           (0x1U << PMU_FLAG_CTL_PIN_RST_FLAG_Pos)

#define PMU_FLAG_CTL_WDT_RST_FLAG_Pos                                           1
#define PMU_FLAG_CTL_WDT_RST_FLAG_Msk                                           (0x1U << PMU_FLAG_CTL_WDT_RST_FLAG_Pos)

#define PMU_FLAG_CTL_FLAG_CLR_Pos                                               0
#define PMU_FLAG_CTL_FLAG_CLR_Msk                                               (0x1U << PMU_FLAG_CTL_FLAG_CLR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PMU_CLK
//
#define PMU_PMU_CLK_TCLK_EN_Pos                                                 7
#define PMU_PMU_CLK_TCLK_EN_Msk                                                 (0x1U << PMU_PMU_CLK_TCLK_EN_Pos)

#define PMU_PMU_CLK_PLL_GATE_DIS_Pos                                            6
#define PMU_PMU_CLK_PLL_GATE_DIS_Msk                                            (0x1U << PMU_PMU_CLK_PLL_GATE_DIS_Pos)

#define PMU_PMU_CLK_WDT_SWIACK_Pos                                              5
#define PMU_PMU_CLK_WDT_SWIACK_Msk                                              (0x1U << PMU_PMU_CLK_WDT_SWIACK_Pos)

#define PMU_PMU_CLK_RTC_SWIACK_Pos                                              4
#define PMU_PMU_CLK_RTC_SWIACK_Msk                                              (0x1U << PMU_PMU_CLK_RTC_SWIACK_Pos)

#define PMU_PMU_CLK_WDTCLK_SEL_Pos                                              2
#define PMU_PMU_CLK_WDTCLK_SEL_Msk                                              (0x3U << PMU_PMU_CLK_WDTCLK_SEL_Pos)

#define PMU_PMU_CLK_RTCCLK_SEL_Pos                                              0
#define PMU_PMU_CLK_RTCCLK_SEL_Msk                                              (0x3U << PMU_PMU_CLK_RTCCLK_SEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IE_MSK
//
#define PMU_IE_MSK_VAD_IMSK_Pos                                                 7
#define PMU_IE_MSK_VAD_IMSK_Msk                                                 (0x1U << PMU_IE_MSK_VAD_IMSK_Pos)

#define PMU_IE_MSK_RTC_IMSK_Pos                                                 6
#define PMU_IE_MSK_RTC_IMSK_Msk                                                 (0x1U << PMU_IE_MSK_RTC_IMSK_Pos)

#define PMU_IE_MSK_WDT_IMSK_Pos                                                 5
#define PMU_IE_MSK_WDT_IMSK_Msk                                                 (0x1U << PMU_IE_MSK_WDT_IMSK_Pos)

#define PMU_IE_MSK_GPIO_IMSK_Pos                                                4
#define PMU_IE_MSK_GPIO_IMSK_Msk                                                (0x1U << PMU_IE_MSK_GPIO_IMSK_Pos)

#define PMU_IE_MSK_VAD_EMSK_Pos                                                 3
#define PMU_IE_MSK_VAD_EMSK_Msk                                                 (0x1U << PMU_IE_MSK_VAD_EMSK_Pos)

#define PMU_IE_MSK_RTC_EMSK_Pos                                                 2
#define PMU_IE_MSK_RTC_EMSK_Msk                                                 (0x1U << PMU_IE_MSK_RTC_EMSK_Pos)

#define PMU_IE_MSK_WDT_EMSK_Pos                                                 1
#define PMU_IE_MSK_WDT_EMSK_Msk                                                 (0x1U << PMU_IE_MSK_WDT_EMSK_Pos)

#define PMU_IE_MSK_GPIO_EMSK_Pos                                                0
#define PMU_IE_MSK_GPIO_EMSK_Msk                                                (0x1U << PMU_IE_MSK_GPIO_EMSK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LP_CTL
//
#define PMU_LP_CTL_NPU_PD_Pos                                                   7
#define PMU_LP_CTL_NPU_PD_Msk                                                   (0x1U << PMU_LP_CTL_NPU_PD_Pos)

#define PMU_LP_CTL_NPU_PD_ACK_Pos                                               6
#define PMU_LP_CTL_NPU_PD_ACK_Msk                                               (0x1U << PMU_LP_CTL_NPU_PD_ACK_Pos)

#define PMU_LP_CTL_NPU_RSTN_Pos                                                 5
#define PMU_LP_CTL_NPU_RSTN_Msk                                                 (0x1U << PMU_LP_CTL_NPU_RSTN_Pos)

#define PMU_LP_CTL_NPU_CLKEN_Pos                                                4
#define PMU_LP_CTL_NPU_CLKEN_Msk                                                (0x1U << PMU_LP_CTL_NPU_CLKEN_Pos)

#define PMU_LP_CTL_PERI_PD_Pos                                                  3
#define PMU_LP_CTL_PERI_PD_Msk                                                  (0x1U << PMU_LP_CTL_PERI_PD_Pos)

#define PMU_LP_CTL_PERI_PD_ACK_Pos                                              2
#define PMU_LP_CTL_PERI_PD_ACK_Msk                                              (0x1U << PMU_LP_CTL_PERI_PD_ACK_Pos)

#define PMU_LP_CTL_FLASH_DPD_ACK_Pos                                            1
#define PMU_LP_CTL_FLASH_DPD_ACK_Msk                                            (0x1U << PMU_LP_CTL_FLASH_DPD_ACK_Pos)

#define PMU_LP_CTL_FLASH_DPD_REQ_Pos                                            0
#define PMU_LP_CTL_FLASH_DPD_REQ_Msk                                            (0x1U << PMU_LP_CTL_FLASH_DPD_REQ_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLK_CTL
//
#define PMU_CLK_CTL_AUD_DIV_NUM_Pos                                             4
#define PMU_CLK_CTL_AUD_DIV_NUM_Msk                                             (0xfU << PMU_CLK_CTL_AUD_DIV_NUM_Pos)

#define PMU_CLK_CTL_NPU_DIV_NUM_Pos                                             0
#define PMU_CLK_CTL_NPU_DIV_NUM_Msk                                             (0xfU << PMU_CLK_CTL_NPU_DIV_NUM_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VOL_UPDATE
//
#define PMU_VOL_UPDATE_VOL_UPDATE_Pos                                           7
#define PMU_VOL_UPDATE_VOL_UPDATE_Msk                                           (0x1U << PMU_VOL_UPDATE_VOL_UPDATE_Pos)

#define PMU_VOL_UPDATE_VOL1_UPDATE_VALUE_Pos                                    1
#define PMU_VOL_UPDATE_VOL1_UPDATE_VALUE_Msk                                    (0x1U << PMU_VOL_UPDATE_VOL1_UPDATE_VALUE_Pos)

#define PMU_VOL_UPDATE_VOL0_UPDATE_VALUE_Pos                                    0
#define PMU_VOL_UPDATE_VOL0_UPDATE_VALUE_Msk                                    (0x1U << PMU_VOL_UPDATE_VOL0_UPDATE_VALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SRAM_PD
//
#define PMU_SRAM_PD_SRAM2_1_PD_Pos                                              4
#define PMU_SRAM_PD_SRAM2_1_PD_Msk                                              (0x1U << PMU_SRAM_PD_SRAM2_1_PD_Pos)

#define PMU_SRAM_PD_SRAM2_0_PD_Pos                                              3
#define PMU_SRAM_PD_SRAM2_0_PD_Msk                                              (0x1U << PMU_SRAM_PD_SRAM2_0_PD_Pos)

#define PMU_SRAM_PD_SRAM1_1_PD_Pos                                              2
#define PMU_SRAM_PD_SRAM1_1_PD_Msk                                              (0x1U << PMU_SRAM_PD_SRAM1_1_PD_Pos)

#define PMU_SRAM_PD_SRAM1_0_PD_Pos                                              1
#define PMU_SRAM_PD_SRAM1_0_PD_Msk                                              (0x1U << PMU_SRAM_PD_SRAM1_0_PD_Pos)

#define PMU_SRAM_PD_SRAM0_PD_Pos                                                0
#define PMU_SRAM_PD_SRAM0_PD_Msk                                                (0x1U << PMU_SRAM_PD_SRAM0_PD_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SRAM_RTN
//
#define PMU_SRAM_RTN_DSP_SRAM_Pos                                               5
#define PMU_SRAM_RTN_DSP_SRAM_Msk                                               (0x1U << PMU_SRAM_RTN_DSP_SRAM_Pos)

#define PMU_SRAM_RTN_SRAM4_Pos                                                  4
#define PMU_SRAM_RTN_SRAM4_Msk                                                  (0x1U << PMU_SRAM_RTN_SRAM4_Pos)

#define PMU_SRAM_RTN_SRAM3_Pos                                                  3
#define PMU_SRAM_RTN_SRAM3_Msk                                                  (0x1U << PMU_SRAM_RTN_SRAM3_Pos)

#define PMU_SRAM_RTN_SRAM2_Pos                                                  2
#define PMU_SRAM_RTN_SRAM2_Msk                                                  (0x1U << PMU_SRAM_RTN_SRAM2_Pos)

#define PMU_SRAM_RTN_SRAM1_Pos                                                  1
#define PMU_SRAM_RTN_SRAM1_Msk                                                  (0x1U << PMU_SRAM_RTN_SRAM1_Pos)

#define PMU_SRAM_RTN_SRAM0_Pos                                                  0
#define PMU_SRAM_RTN_SRAM0_Msk                                                  (0x1U << PMU_SRAM_RTN_SRAM0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PMU_RESV
//
#define PMU_PMU_RESV_PMU_RESV_REG33_Pos                                         4
#define PMU_PMU_RESV_PMU_RESV_REG33_Msk                                         (0xfU << PMU_PMU_RESV_PMU_RESV_REG33_Pos)

#define PMU_PMU_RESV_PMU_RESV_REG11_Pos                                         0
#define PMU_PMU_RESV_PMU_RESV_REG11_Msk                                         (0xfU << PMU_PMU_RESV_PMU_RESV_REG11_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRIM0
//
#define PMU_TRIM0_LDO_PMUVDD_TRIM_VSEL_Pos                                      4
#define PMU_TRIM0_LDO_PMUVDD_TRIM_VSEL_Msk                                      (0x7U << PMU_TRIM0_LDO_PMUVDD_TRIM_VSEL_Pos)

#define PMU_TRIM0_CLK_OUT_OE_Pos                                                3
#define PMU_TRIM0_CLK_OUT_OE_Msk                                                (0x1U << PMU_TRIM0_CLK_OUT_OE_Pos)

#define PMU_TRIM0_LDO_IOVDD11_TRIM_VSEL_Pos                                     0
#define PMU_TRIM0_LDO_IOVDD11_TRIM_VSEL_Msk                                     (0x7U << PMU_TRIM0_LDO_IOVDD11_TRIM_VSEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRIM_1
//
#define PMU_TRIM_1_OSC24M_SEL_Pos                                               7
#define PMU_TRIM_1_OSC24M_SEL_Msk                                               (0x1U << PMU_TRIM_1_OSC24M_SEL_Pos)

#define PMU_TRIM_1_TEST_OSC_SEL_Pos                                             4
#define PMU_TRIM_1_TEST_OSC_SEL_Msk                                             (0x7U << PMU_TRIM_1_TEST_OSC_SEL_Pos)

#define PMU_TRIM_1_XVON_VBG_Pos                                                 3
#define PMU_TRIM_1_XVON_VBG_Msk                                                 (0x1U << PMU_TRIM_1_XVON_VBG_Pos)

#define PMU_TRIM_1_BGAP_VOL_EN_Pos                                              2
#define PMU_TRIM_1_BGAP_VOL_EN_Msk                                              (0x1U << PMU_TRIM_1_BGAP_VOL_EN_Pos)

#define PMU_TRIM_1_BGAP_CURA_ADJ_Pos                                            0
#define PMU_TRIM_1_BGAP_CURA_ADJ_Msk                                            (0x3U << PMU_TRIM_1_BGAP_CURA_ADJ_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRIM_2
//
#define PMU_TRIM_2_TRIM_OSC10KR_Pos                                             2
#define PMU_TRIM_2_TRIM_OSC10KR_Msk                                             (0x7U << PMU_TRIM_2_TRIM_OSC10KR_Pos)

#define PMU_TRIM_2_TRIM_OSC10KC_Pos                                             0
#define PMU_TRIM_2_TRIM_OSC10KC_Msk                                             (0x3U << PMU_TRIM_2_TRIM_OSC10KC_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRIM_3
//
#define PMU_TRIM_3_CS_STATE_Pos                                                 3
#define PMU_TRIM_3_CS_STATE_Msk                                                 (0x1fU << PMU_TRIM_3_CS_STATE_Pos)

#define PMU_TRIM_3_BG_VOL_EN_Pos                                                2
#define PMU_TRIM_3_BG_VOL_EN_Msk                                                (0x1U << PMU_TRIM_3_BG_VOL_EN_Pos)

#define PMU_TRIM_3_PORB_AVDD11_NPU_Pos                                          0
#define PMU_TRIM_3_PORB_AVDD11_NPU_Msk                                          (0x1U << PMU_TRIM_3_PORB_AVDD11_NPU_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRIM_4
//
#define PMU_TRIM_4_PU_FLASH_VREF_Pos                                            4
#define PMU_TRIM_4_PU_FLASH_VREF_Msk                                            (0x1U << PMU_TRIM_4_PU_FLASH_VREF_Pos)

#define PMU_TRIM_4_VBG_FLASH_TRIM_Pos                                           0
#define PMU_TRIM_4_VBG_FLASH_TRIM_Msk                                           (0xfU << PMU_TRIM_4_VBG_FLASH_TRIM_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRIM_5
//
#define PMU_TRIM_5_TP_CLK_DRV_Pos                                               6
#define PMU_TRIM_5_TP_CLK_DRV_Msk                                               (0x3U << PMU_TRIM_5_TP_CLK_DRV_Pos)

#define PMU_TRIM_5_VBG_TRIM_TEMPSEL_Pos                                         4
#define PMU_TRIM_5_VBG_TRIM_TEMPSEL_Msk                                         (0x3U << PMU_TRIM_5_VBG_TRIM_TEMPSEL_Pos)

#define PMU_TRIM_5_VBG_TRIM_VSEL_Pos                                            0
#define PMU_TRIM_5_VBG_TRIM_VSEL_Msk                                            (0x7U << PMU_TRIM_5_VBG_TRIM_VSEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_OD
//
#define PMU_GPIO_OD_GPIO_IDDQ_Pos                                               4
#define PMU_GPIO_OD_GPIO_IDDQ_Msk                                               (0x1U << PMU_GPIO_OD_GPIO_IDDQ_Pos)

#define PMU_GPIO_OD_GPIO_OD_Pos                                                 0
#define PMU_GPIO_OD_GPIO_OD_Msk                                                 (0xfU << PMU_GPIO_OD_GPIO_OD_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_SMT0
//
#define PMU_GPIO_SMT0_GPIO_SMT_0_Pos                                            0
#define PMU_GPIO_SMT0_GPIO_SMT_0_Msk                                            (0xffU << PMU_GPIO_SMT0_GPIO_SMT_0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_SMT1
//
#define PMU_GPIO_SMT1_GPIO_SMT_1_Pos                                            0
#define PMU_GPIO_SMT1_GPIO_SMT_1_Msk                                            (0xffU << PMU_GPIO_SMT1_GPIO_SMT_1_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_SMT2
//
#define PMU_GPIO_SMT2_GPIO_SMT_2_Pos                                            0
#define PMU_GPIO_SMT2_GPIO_SMT_2_Msk                                            (0xfU << PMU_GPIO_SMT2_GPIO_SMT_2_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PMU_RESV_ADC_REG0
//
#define PMU_PMU_RESV_ADC_REG0_PMU_RESV_ADC_REG0_Pos                             0
#define PMU_PMU_RESV_ADC_REG0_PMU_RESV_ADC_REG0_Msk                             (0xffU << PMU_PMU_RESV_ADC_REG0_PMU_RESV_ADC_REG0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PMU_RESV_ADC_REG1
//
#define PMU_PMU_RESV_ADC_REG1_PMU_RESV_ADC_REG1_Pos                             0
#define PMU_PMU_RESV_ADC_REG1_PMU_RESV_ADC_REG1_Msk                             (0xffU << PMU_PMU_RESV_ADC_REG1_PMU_RESV_ADC_REG1_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PLL_0
//
#define PMU_PLL_0_PLL_DIG_CUR_SEL_Pos                                           3
#define PMU_PLL_0_PLL_DIG_CUR_SEL_Msk                                           (0x7U << PMU_PLL_0_PLL_DIG_CUR_SEL_Pos)

#define PMU_PLL_0_PLL_CP_CUR_SEL_Pos                                            1
#define PMU_PLL_0_PLL_CP_CUR_SEL_Msk                                            (0x3U << PMU_PLL_0_PLL_CP_CUR_SEL_Pos)

#define PMU_PLL_0_PLL_LOCK_DETECT_Pos                                           0
#define PMU_PLL_0_PLL_LOCK_DETECT_Msk                                           (0x1U << PMU_PLL_0_PLL_LOCK_DETECT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PLL_1
//
#define PMU_PLL_1_PLL_LOOP_CAP1_SEL_Pos                                         5
#define PMU_PLL_1_PLL_LOOP_CAP1_SEL_Msk                                         (0x7U << PMU_PLL_1_PLL_LOOP_CAP1_SEL_Pos)

#define PMU_PLL_1_PLL_DIV_Pos                                                   0
#define PMU_PLL_1_PLL_DIV_Msk                                                   (0x1fU << PMU_PLL_1_PLL_DIV_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PLL_2
//
#define PMU_PLL_2_PLL_TEST_MODE_ENB_Pos                                         7
#define PMU_PLL_2_PLL_TEST_MODE_ENB_Msk                                         (0x1U << PMU_PLL_2_PLL_TEST_MODE_ENB_Pos)

#define PMU_PLL_2_PLL_LOOP_CAP2_SEL_Pos                                         3
#define PMU_PLL_2_PLL_LOOP_CAP2_SEL_Msk                                         (0x7U << PMU_PLL_2_PLL_LOOP_CAP2_SEL_Pos)

#define PMU_PLL_2_PLL_LOOP_RES_SEL_Pos                                          0
#define PMU_PLL_2_PLL_LOOP_RES_SEL_Msk                                          (0x7U << PMU_PLL_2_PLL_LOOP_RES_SEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PLL_3
//
#define PMU_PLL_3_PLL_VCO_OPENLOOP_VOL_SEL_Pos                                  1
#define PMU_PLL_3_PLL_VCO_OPENLOOP_VOL_SEL_Msk                                  (0x7U << PMU_PLL_3_PLL_VCO_OPENLOOP_VOL_SEL_Pos)

#define PMU_PLL_3_PLL_DIV_0P5_EN_Pos                                            0
#define PMU_PLL_3_PLL_DIV_0P5_EN_Msk                                            (0x1U << PMU_PLL_3_PLL_DIV_0P5_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PLL_4
//
#define PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Pos                                      4
#define PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Msk                                      (0xfU << PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Pos)

#define PMU_PLL_4_PLL_DIV8_ENB_Pos                                              3
#define PMU_PLL_4_PLL_DIV8_ENB_Msk                                              (0x1U << PMU_PLL_4_PLL_DIV8_ENB_Pos)

#define PMU_PLL_4_PLL_VCO_BAND_SEL_Pos                                          0
#define PMU_PLL_4_PLL_VCO_BAND_SEL_Msk                                          (0x7U << PMU_PLL_4_PLL_VCO_BAND_SEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PLL_5
//
#define PMU_PLL_5_PLL_VCO_KVCO_SEL_Pos                                          3
#define PMU_PLL_5_PLL_VCO_KVCO_SEL_Msk                                          (0x7U << PMU_PLL_5_PLL_VCO_KVCO_SEL_Pos)

#define PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Pos                                  1
#define PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Msk                                  (0x3U << PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Pos)

#define PMU_PLL_5_PLL_VCO_OPENLOOP_ENB_Pos                                      0
#define PMU_PLL_5_PLL_VCO_OPENLOOP_ENB_Msk                                      (0x1U << PMU_PLL_5_PLL_VCO_OPENLOOP_ENB_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRIM_RST
//
#define PMU_TRIM_RST_320K_TRIM_ACK_Pos                                          3
#define PMU_TRIM_RST_320K_TRIM_ACK_Msk                                          (0x1U << PMU_TRIM_RST_320K_TRIM_ACK_Pos)

#define PMU_TRIM_RST_24M_TRIM_ACK_Pos                                           2
#define PMU_TRIM_RST_24M_TRIM_ACK_Msk                                           (0x1U << PMU_TRIM_RST_24M_TRIM_ACK_Pos)

#define PMU_TRIM_RST_320K_TRIM_RST_Pos                                          1
#define PMU_TRIM_RST_320K_TRIM_RST_Msk                                          (0x1U << PMU_TRIM_RST_320K_TRIM_RST_Pos)

#define PMU_TRIM_RST_24M_TRIM_RST_Pos                                           0
#define PMU_TRIM_RST_24M_TRIM_RST_Msk                                           (0x1U << PMU_TRIM_RST_24M_TRIM_RST_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// 320K_TRIM
//
#define PMU_320K_TRIM_REG_320K_TRIM_FINE_Pos                                    4
#define PMU_320K_TRIM_REG_320K_TRIM_FINE_Msk                                    (0xfU << PMU_320K_TRIM_REG_320K_TRIM_FINE_Pos)

#define PMU_320K_TRIM_REG_320K_TRIM_COARSE_Pos                                  0
#define PMU_320K_TRIM_REG_320K_TRIM_COARSE_Msk                                  (0x7U << PMU_320K_TRIM_REG_320K_TRIM_COARSE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// 24M_TRIM_FINE
//
#define PMU_24M_TRIM_FINE_REG_24M_TRIM_FINE_Pos                                 0
#define PMU_24M_TRIM_FINE_REG_24M_TRIM_FINE_Msk                                 (0x1fU << PMU_24M_TRIM_FINE_REG_24M_TRIM_FINE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// 24M_TRIM_COARSE
//
#define PMU_24M_TRIM_COARSE_REG_24M_TRIM_COARSE_Pos                             0
#define PMU_24M_TRIM_COARSE_REG_24M_TRIM_COARSE_Msk                             (0xfU << PMU_24M_TRIM_COARSE_REG_24M_TRIM_COARSE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SOFT_RST
//
#define PMU_SOFT_RST_SOFT_RST_Pos                                               0
#define PMU_SOFT_RST_SOFT_RST_Msk                                               (0xffU << PMU_SOFT_RST_SOFT_RST_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// REVID
//
#define PMU_REVID_REVID_Pos                                                     0
#define PMU_REVID_REVID_Msk                                                     (0xffU << PMU_REVID_REVID_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SYS_CFG
//
#define PMU_SYS_CFG_REG_320K_TRIM_SEL_Pos                                       6
#define PMU_SYS_CFG_REG_320K_TRIM_SEL_Msk                                       (0x3U << PMU_SYS_CFG_REG_320K_TRIM_SEL_Pos)

#define PMU_SYS_CFG_REG_24M_TRIM_SEL_Pos                                        4
#define PMU_SYS_CFG_REG_24M_TRIM_SEL_Msk                                        (0x3U << PMU_SYS_CFG_REG_24M_TRIM_SEL_Pos)

#define PMU_SYS_CFG_NPU_LOCK_Pos                                                2
#define PMU_SYS_CFG_NPU_LOCK_Msk                                                (0x1U << PMU_SYS_CFG_NPU_LOCK_Pos)

#define PMU_SYS_CFG_JTAG_LOCK_Pos                                               1
#define PMU_SYS_CFG_JTAG_LOCK_Msk                                               (0x1U << PMU_SYS_CFG_JTAG_LOCK_Pos)

#define PMU_SYS_CFG_RESET_VECTOR_MN_Pos                                         0
#define PMU_SYS_CFG_RESET_VECTOR_MN_Msk                                         (0x1U << PMU_SYS_CFG_RESET_VECTOR_MN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_WU_CLR
//
#define PMU_GPIO_WU_CLR_GPIO_WU_CLR_Pos                                         0
#define PMU_GPIO_WU_CLR_GPIO_WU_CLR_Msk                                         (0x1U << PMU_GPIO_WU_CLR_GPIO_WU_CLR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RST_VEC_0
//
#define PMU_RST_VEC_0_RESET_VECTOR_0_Pos                                        0
#define PMU_RST_VEC_0_RESET_VECTOR_0_Msk                                        (0xffU << PMU_RST_VEC_0_RESET_VECTOR_0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RST_VEC_1
//
#define PMU_RST_VEC_1_RESET_VECTOR_1_Pos                                        0
#define PMU_RST_VEC_1_RESET_VECTOR_1_Msk                                        (0xffU << PMU_RST_VEC_1_RESET_VECTOR_1_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RST_VEC_2
//
#define PMU_RST_VEC_2_RESET_VECTOR_2_Pos                                        0
#define PMU_RST_VEC_2_RESET_VECTOR_2_Msk                                        (0xffU << PMU_RST_VEC_2_RESET_VECTOR_2_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RST_VEC_3
//
#define PMU_RST_VEC_3_RESET_VECTOR_3_Pos                                        0
#define PMU_RST_VEC_3_RESET_VECTOR_3_Msk                                        (0xffU << PMU_RST_VEC_3_RESET_VECTOR_3_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTN_0
//
#define PMU_RTN_0_RETENTION_0_Pos                                               0
#define PMU_RTN_0_RETENTION_0_Msk                                               (0xffU << PMU_RTN_0_RETENTION_0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTN_1
//
#define PMU_RTN_1_RETENTION_1_Pos                                               0
#define PMU_RTN_1_RETENTION_1_Msk                                               (0xffU << PMU_RTN_1_RETENTION_1_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTN_2
//
#define PMU_RTN_2_RETENTION_2_Pos                                               0
#define PMU_RTN_2_RETENTION_2_Msk                                               (0xffU << PMU_RTN_2_RETENTION_2_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTN_3
//
#define PMU_RTN_3_RETENTION_3_Pos                                               0
#define PMU_RTN_3_RETENTION_3_Msk                                               (0xffU << PMU_RTN_3_RETENTION_3_Pos)

#endif //__WTM2101_PMU_REGISTER_H_INCLUDED__