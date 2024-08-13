/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 audio register.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Sat Aug 21 12:46:34 2021/////////////


#ifndef __WTM2101_AUDIO_REGISTER_H_INCLUDED__
#define __WTM2101_AUDIO_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// TRCTRL
//
#define AUDIO_TRCTRL_ANA_EMPHASIS_SEL_O_Pos                                     29
#define AUDIO_TRCTRL_ANA_EMPHASIS_SEL_O_Msk                                     (0x1U << AUDIO_TRCTRL_ANA_EMPHASIS_SEL_O_Pos)

#define AUDIO_TRCTRL_PRE_EMPHASIS_BYPASS_O_Pos                                  28
#define AUDIO_TRCTRL_PRE_EMPHASIS_BYPASS_O_Msk                                  (0x1U << AUDIO_TRCTRL_PRE_EMPHASIS_BYPASS_O_Pos)

#define AUDIO_TRCTRL_CH0_PCM_ZEROPADDING_O_Pos                                  25
#define AUDIO_TRCTRL_CH0_PCM_ZEROPADDING_O_Msk                                  (0x7U << AUDIO_TRCTRL_CH0_PCM_ZEROPADDING_O_Pos)

#define AUDIO_TRCTRL_CH0_PCM_SEL_O_Pos                                          24
#define AUDIO_TRCTRL_CH0_PCM_SEL_O_Msk                                          (0x1U << AUDIO_TRCTRL_CH0_PCM_SEL_O_Pos)

#define AUDIO_TRCTRL_VAD_RST_O_Pos                                              23
#define AUDIO_TRCTRL_VAD_RST_O_Msk                                              (0x1U << AUDIO_TRCTRL_VAD_RST_O_Pos)

#define AUDIO_TRCTRL_CH1_PDM_CH_CHANGE_O_Pos                                    22
#define AUDIO_TRCTRL_CH1_PDM_CH_CHANGE_O_Msk                                    (0x1U << AUDIO_TRCTRL_CH1_PDM_CH_CHANGE_O_Pos)

#define AUDIO_TRCTRL_CH0_PDM_CH_CHANGE_O_Pos                                    21
#define AUDIO_TRCTRL_CH0_PDM_CH_CHANGE_O_Msk                                    (0x1U << AUDIO_TRCTRL_CH0_PDM_CH_CHANGE_O_Pos)

#define AUDIO_TRCTRL_CH2_HIGH_BYPASS_O_Pos                                      20
#define AUDIO_TRCTRL_CH2_HIGH_BYPASS_O_Msk                                      (0x1U << AUDIO_TRCTRL_CH2_HIGH_BYPASS_O_Pos)

#define AUDIO_TRCTRL_BIQUAD_BYPASS_O_Pos                                        19
#define AUDIO_TRCTRL_BIQUAD_BYPASS_O_Msk                                        (0x1U << AUDIO_TRCTRL_BIQUAD_BYPASS_O_Pos)

#define AUDIO_TRCTRL_HIGHPASS_BYPASS_O_Pos                                      18
#define AUDIO_TRCTRL_HIGHPASS_BYPASS_O_Msk                                      (0x1U << AUDIO_TRCTRL_HIGHPASS_BYPASS_O_Pos)

#define AUDIO_TRCTRL_HALFBAND_BYPASS_O_Pos                                      17
#define AUDIO_TRCTRL_HALFBAND_BYPASS_O_Msk                                      (0x1U << AUDIO_TRCTRL_HALFBAND_BYPASS_O_Pos)

#define AUDIO_TRCTRL_SINC5D2_BYPASS_O_Pos                                       16
#define AUDIO_TRCTRL_SINC5D2_BYPASS_O_Msk                                       (0x1U << AUDIO_TRCTRL_SINC5D2_BYPASS_O_Pos)

#define AUDIO_TRCTRL_BIQUAD_SOURCE_SEL_O_Pos                                    15
#define AUDIO_TRCTRL_BIQUAD_SOURCE_SEL_O_Msk                                    (0x1U << AUDIO_TRCTRL_BIQUAD_SOURCE_SEL_O_Pos)

#define AUDIO_TRCTRL_VAD_CH_SEL_O_Pos                                           14
#define AUDIO_TRCTRL_VAD_CH_SEL_O_Msk                                           (0x1U << AUDIO_TRCTRL_VAD_CH_SEL_O_Pos)

#define AUDIO_TRCTRL_CH1_PDM_EDGE_SEL_O_Pos                                     13
#define AUDIO_TRCTRL_CH1_PDM_EDGE_SEL_O_Msk                                     (0x1U << AUDIO_TRCTRL_CH1_PDM_EDGE_SEL_O_Pos)

#define AUDIO_TRCTRL_CH0_PDM_EDGE_SEL_O_Pos                                     12
#define AUDIO_TRCTRL_CH0_PDM_EDGE_SEL_O_Msk                                     (0x1U << AUDIO_TRCTRL_CH0_PDM_EDGE_SEL_O_Pos)

#define AUDIO_TRCTRL_RSV_Pos                                                    11
#define AUDIO_TRCTRL_RSV_Msk                                                    (0x1U << AUDIO_TRCTRL_RSV_Pos)

#define AUDIO_TRCTRL_CH_CLK_DIV_O_Pos                                           9
#define AUDIO_TRCTRL_CH_CLK_DIV_O_Msk                                           (0x3U << AUDIO_TRCTRL_CH_CLK_DIV_O_Pos)

#define AUDIO_TRCTRL_CH2_TR_EN_O_Pos                                            8
#define AUDIO_TRCTRL_CH2_TR_EN_O_Msk                                            (0x1U << AUDIO_TRCTRL_CH2_TR_EN_O_Pos)

#define AUDIO_TRCTRL_CH1_PDM_SEL_O_Pos                                          7
#define AUDIO_TRCTRL_CH1_PDM_SEL_O_Msk                                          (0x1U << AUDIO_TRCTRL_CH1_PDM_SEL_O_Pos)

#define AUDIO_TRCTRL_CH1_TR_MOD_SEL_O_Pos                                       5
#define AUDIO_TRCTRL_CH1_TR_MOD_SEL_O_Msk                                       (0x3U << AUDIO_TRCTRL_CH1_TR_MOD_SEL_O_Pos)

#define AUDIO_TRCTRL_CH1_TR_EN_O_Pos                                            4
#define AUDIO_TRCTRL_CH1_TR_EN_O_Msk                                            (0x1U << AUDIO_TRCTRL_CH1_TR_EN_O_Pos)

#define AUDIO_TRCTRL_CH0_PDM_SEL_O_Pos                                          3
#define AUDIO_TRCTRL_CH0_PDM_SEL_O_Msk                                          (0x1U << AUDIO_TRCTRL_CH0_PDM_SEL_O_Pos)

#define AUDIO_TRCTRL_CH0_TR_MOD_SEL_O_Pos                                       1
#define AUDIO_TRCTRL_CH0_TR_MOD_SEL_O_Msk                                       (0x3U << AUDIO_TRCTRL_CH0_TR_MOD_SEL_O_Pos)

#define AUDIO_TRCTRL_CH0_TR_EN_O_Pos                                            0
#define AUDIO_TRCTRL_CH0_TR_EN_O_Msk                                            (0x1U << AUDIO_TRCTRL_CH0_TR_EN_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FFCLR
//
#define AUDIO_FFCLR_FIFO2_READ_CLR_O_Pos                                        11
#define AUDIO_FFCLR_FIFO2_READ_CLR_O_Msk                                        (0x1U << AUDIO_FFCLR_FIFO2_READ_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO2_WRITE_CLR_O_Pos                                       10
#define AUDIO_FFCLR_FIFO2_WRITE_CLR_O_Msk                                       (0x1U << AUDIO_FFCLR_FIFO2_WRITE_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO2_OVERFLOW_CLR_O_Pos                                    9
#define AUDIO_FFCLR_FIFO2_OVERFLOW_CLR_O_Msk                                    (0x1U << AUDIO_FFCLR_FIFO2_OVERFLOW_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO2_UNDERFLOW_CLR_O_Pos                                   8
#define AUDIO_FFCLR_FIFO2_UNDERFLOW_CLR_O_Msk                                   (0x1U << AUDIO_FFCLR_FIFO2_UNDERFLOW_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO1_READ_CLR_O_Pos                                        7
#define AUDIO_FFCLR_FIFO1_READ_CLR_O_Msk                                        (0x1U << AUDIO_FFCLR_FIFO1_READ_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO1_WRITE_CLR_O_Pos                                       6
#define AUDIO_FFCLR_FIFO1_WRITE_CLR_O_Msk                                       (0x1U << AUDIO_FFCLR_FIFO1_WRITE_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO1_OVERFLOW_CLR_O_Pos                                    5
#define AUDIO_FFCLR_FIFO1_OVERFLOW_CLR_O_Msk                                    (0x1U << AUDIO_FFCLR_FIFO1_OVERFLOW_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO1_UNDERFLOW_CLR_O_Pos                                   4
#define AUDIO_FFCLR_FIFO1_UNDERFLOW_CLR_O_Msk                                   (0x1U << AUDIO_FFCLR_FIFO1_UNDERFLOW_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO0_READ_CLR_O_Pos                                        3
#define AUDIO_FFCLR_FIFO0_READ_CLR_O_Msk                                        (0x1U << AUDIO_FFCLR_FIFO0_READ_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO0_WRITE_CLR_O_Pos                                       2
#define AUDIO_FFCLR_FIFO0_WRITE_CLR_O_Msk                                       (0x1U << AUDIO_FFCLR_FIFO0_WRITE_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO0_OVERFLOW_CLR_O_Pos                                    1
#define AUDIO_FFCLR_FIFO0_OVERFLOW_CLR_O_Msk                                    (0x1U << AUDIO_FFCLR_FIFO0_OVERFLOW_CLR_O_Pos)

#define AUDIO_FFCLR_FIFO0_UNDERFLOW_CLR_O_Pos                                   0
#define AUDIO_FFCLR_FIFO0_UNDERFLOW_CLR_O_Msk                                   (0x1U << AUDIO_FFCLR_FIFO0_UNDERFLOW_CLR_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FF0DATA
//
#define AUDIO_FF0DATA_FIFO0_RDATA_I_Pos                                         0
#define AUDIO_FF0DATA_FIFO0_RDATA_I_Msk                                         (0xffffffffU << AUDIO_FF0DATA_FIFO0_RDATA_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FF1DATA
//
#define AUDIO_FF1DATA_FIFO1_RDATA_I_Pos                                         0
#define AUDIO_FF1DATA_FIFO1_RDATA_I_Msk                                         (0xffffffffU << AUDIO_FF1DATA_FIFO1_RDATA_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FF2DATA
//
#define AUDIO_FF2DATA_FIFO2_RDATA_I_Pos                                         0
#define AUDIO_FF2DATA_FIFO2_RDATA_I_Msk                                         (0xffffffffU << AUDIO_FF2DATA_FIFO2_RDATA_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAM0CFG0
//
#define AUDIO_RAM0CFG0_RAM0_FRAME_MOVE_O_Pos                                    16
#define AUDIO_RAM0CFG0_RAM0_FRAME_MOVE_O_Msk                                    (0xffffU << AUDIO_RAM0CFG0_RAM0_FRAME_MOVE_O_Pos)

#define AUDIO_RAM0CFG0_RAM0_DEPTH_CFG_O_Pos                                     0
#define AUDIO_RAM0CFG0_RAM0_DEPTH_CFG_O_Msk                                     (0xffffU << AUDIO_RAM0CFG0_RAM0_DEPTH_CFG_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAM1CFG0
//
#define AUDIO_RAM1CFG0_RAM1_FRAME_MOVE_O_Pos                                    16
#define AUDIO_RAM1CFG0_RAM1_FRAME_MOVE_O_Msk                                    (0xffffU << AUDIO_RAM1CFG0_RAM1_FRAME_MOVE_O_Pos)

#define AUDIO_RAM1CFG0_RAM1_DEPTH_CFG_O_Pos                                     0
#define AUDIO_RAM1CFG0_RAM1_DEPTH_CFG_O_Msk                                     (0xffffU << AUDIO_RAM1CFG0_RAM1_DEPTH_CFG_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAM0CFG1
//
#define AUDIO_RAM0CFG1_RAM0_LENTH_CFG_O_Pos                                     0
#define AUDIO_RAM0CFG1_RAM0_LENTH_CFG_O_Msk                                     (0xffffU << AUDIO_RAM0CFG1_RAM0_LENTH_CFG_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAM1CFG1
//
#define AUDIO_RAM1CFG1_RAM1_LENTH_CFG_O_Pos                                     0
#define AUDIO_RAM1CFG1_RAM1_LENTH_CFG_O_Msk                                     (0xffffU << AUDIO_RAM1CFG1_RAM1_LENTH_CFG_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAMCLR
//
#define AUDIO_RAMCLR_RAM1_RD_CLR_O_Pos                                          5
#define AUDIO_RAMCLR_RAM1_RD_CLR_O_Msk                                          (0x1U << AUDIO_RAMCLR_RAM1_RD_CLR_O_Pos)

#define AUDIO_RAMCLR_RAM1_FRAME_VLD_CLR_O_Pos                                   4
#define AUDIO_RAMCLR_RAM1_FRAME_VLD_CLR_O_Msk                                   (0x1U << AUDIO_RAMCLR_RAM1_FRAME_VLD_CLR_O_Pos)

#define AUDIO_RAMCLR_RAM1_CLR_O_Pos                                             3
#define AUDIO_RAMCLR_RAM1_CLR_O_Msk                                             (0x1U << AUDIO_RAMCLR_RAM1_CLR_O_Pos)

#define AUDIO_RAMCLR_RAM0_RD_CLR_O_Pos                                          2
#define AUDIO_RAMCLR_RAM0_RD_CLR_O_Msk                                          (0x1U << AUDIO_RAMCLR_RAM0_RD_CLR_O_Pos)

#define AUDIO_RAMCLR_RAM0_FRAME_VLD_CLR_O_Pos                                   1
#define AUDIO_RAMCLR_RAM0_FRAME_VLD_CLR_O_Msk                                   (0x1U << AUDIO_RAMCLR_RAM0_FRAME_VLD_CLR_O_Pos)

#define AUDIO_RAMCLR_RAM0_CLR_O_Pos                                             0
#define AUDIO_RAMCLR_RAM0_CLR_O_Msk                                             (0x1U << AUDIO_RAMCLR_RAM0_CLR_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAM0DATA
//
#define AUDIO_RAM0DATA_RAM0_DATA_Pos                                            0
#define AUDIO_RAM0DATA_RAM0_DATA_Msk                                            (0xffffffffU << AUDIO_RAM0DATA_RAM0_DATA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAM1DATA
//
#define AUDIO_RAM1DATA_RSV6_Pos                                                 0
#define AUDIO_RAM1DATA_RSV6_Msk                                                 (0xffffffffU << AUDIO_RAM1DATA_RSV6_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PCMCFG0
//
#define AUDIO_PCMCFG0_BQ_B1_O_Pos                                               16
#define AUDIO_PCMCFG0_BQ_B1_O_Msk                                               (0xffffU << AUDIO_PCMCFG0_BQ_B1_O_Pos)

#define AUDIO_PCMCFG0_BQ_B0_O_Pos                                               0
#define AUDIO_PCMCFG0_BQ_B0_O_Msk                                               (0xffffU << AUDIO_PCMCFG0_BQ_B0_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PCMCFG1
//
#define AUDIO_PCMCFG1_BQ_A0_O_Pos                                               16
#define AUDIO_PCMCFG1_BQ_A0_O_Msk                                               (0xffffU << AUDIO_PCMCFG1_BQ_A0_O_Pos)

#define AUDIO_PCMCFG1_BQ_B2_O_Pos                                               0
#define AUDIO_PCMCFG1_BQ_B2_O_Msk                                               (0xffffU << AUDIO_PCMCFG1_BQ_B2_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PCMCFG2
//
#define AUDIO_PCMCFG2_BQ_A1_O_Pos                                               0
#define AUDIO_PCMCFG2_BQ_A1_O_Msk                                               (0xffffU << AUDIO_PCMCFG2_BQ_A1_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PCMGAIN
//
#define AUDIO_PCMGAIN_CH2_GAIN_O_Pos                                            10
#define AUDIO_PCMGAIN_CH2_GAIN_O_Msk                                            (0x1fU << AUDIO_PCMGAIN_CH2_GAIN_O_Pos)

#define AUDIO_PCMGAIN_CH1_GAIN_O_Pos                                            5
#define AUDIO_PCMGAIN_CH1_GAIN_O_Msk                                            (0x1fU << AUDIO_PCMGAIN_CH1_GAIN_O_Pos)

#define AUDIO_PCMGAIN_CH0_GAIN_O_Pos                                            0
#define AUDIO_PCMGAIN_CH0_GAIN_O_Msk                                            (0x1fU << AUDIO_PCMGAIN_CH0_GAIN_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VADCNT
//
#define AUDIO_VADCNT_VAD_CNT_Pos                                                0
#define AUDIO_VADCNT_VAD_CNT_Msk                                                (0xffffffffU << AUDIO_VADCNT_VAD_CNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VAD0
//
#define AUDIO_VAD0_DEF_STP_THRESHOLD_O_Pos                                      0
#define AUDIO_VAD0_DEF_STP_THRESHOLD_O_Msk                                      (0xffffffffU << AUDIO_VAD0_DEF_STP_THRESHOLD_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VAD1
//
#define AUDIO_VAD1_DEF_LTP_THRESHOLD_O_Pos                                      0
#define AUDIO_VAD1_DEF_LTP_THRESHOLD_O_Msk                                      (0xffffffffU << AUDIO_VAD1_DEF_LTP_THRESHOLD_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VAD2
//
#define AUDIO_VAD2_DEF_DEVIATION_O_Pos                                          0
#define AUDIO_VAD2_DEF_DEVIATION_O_Msk                                          (0xffffffffU << AUDIO_VAD2_DEF_DEVIATION_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VAD3
//
#define AUDIO_VAD3_SPT_WIN_SHIFT_O_Pos                                          16
#define AUDIO_VAD3_SPT_WIN_SHIFT_O_Msk                                          (0xffffU << AUDIO_VAD3_SPT_WIN_SHIFT_O_Pos)

#define AUDIO_VAD3_DEF_STP_WINLEN_O_Pos                                         0
#define AUDIO_VAD3_DEF_STP_WINLEN_O_Msk                                         (0xffffU << AUDIO_VAD3_DEF_STP_WINLEN_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VAD4
//
#define AUDIO_VAD4_LPT_WIN_SHIFT_O_Pos                                          16
#define AUDIO_VAD4_LPT_WIN_SHIFT_O_Msk                                          (0xffffU << AUDIO_VAD4_LPT_WIN_SHIFT_O_Pos)

#define AUDIO_VAD4_DEF_LTP_WINLEN_O_Pos                                         0
#define AUDIO_VAD4_DEF_LTP_WINLEN_O_Msk                                         (0xffffU << AUDIO_VAD4_DEF_LTP_WINLEN_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRINT
//
#define AUDIO_TRINT_VAD_ACT_INT_Pos                                             17
#define AUDIO_TRINT_VAD_ACT_INT_Msk                                             (0x1U << AUDIO_TRINT_VAD_ACT_INT_Pos)

#define AUDIO_TRINT_FIFO2_UNDERFLOW_INT_Pos                                     16
#define AUDIO_TRINT_FIFO2_UNDERFLOW_INT_Msk                                     (0x1U << AUDIO_TRINT_FIFO2_UNDERFLOW_INT_Pos)

#define AUDIO_TRINT_FIFO2_OVERFLOW_INT_Pos                                      15
#define AUDIO_TRINT_FIFO2_OVERFLOW_INT_Msk                                      (0x1U << AUDIO_TRINT_FIFO2_OVERFLOW_INT_Pos)

#define AUDIO_TRINT_FIFO2_EMP_INT_Pos                                           14
#define AUDIO_TRINT_FIFO2_EMP_INT_Msk                                           (0x1U << AUDIO_TRINT_FIFO2_EMP_INT_Pos)

#define AUDIO_TRINT_FIFO2_HALF_FULL_INT_Pos                                     13
#define AUDIO_TRINT_FIFO2_HALF_FULL_INT_Msk                                     (0x1U << AUDIO_TRINT_FIFO2_HALF_FULL_INT_Pos)

#define AUDIO_TRINT_FIFO2_FULL_INT_Pos                                          12
#define AUDIO_TRINT_FIFO2_FULL_INT_Msk                                          (0x1U << AUDIO_TRINT_FIFO2_FULL_INT_Pos)

#define AUDIO_TRINT_FIFO1_UNDERFLOW_INT_Pos                                     11
#define AUDIO_TRINT_FIFO1_UNDERFLOW_INT_Msk                                     (0x1U << AUDIO_TRINT_FIFO1_UNDERFLOW_INT_Pos)

#define AUDIO_TRINT_FIFO1_OVERFLOW_INT_Pos                                      10
#define AUDIO_TRINT_FIFO1_OVERFLOW_INT_Msk                                      (0x1U << AUDIO_TRINT_FIFO1_OVERFLOW_INT_Pos)

#define AUDIO_TRINT_FIFO1_EMP_INT_Pos                                           9
#define AUDIO_TRINT_FIFO1_EMP_INT_Msk                                           (0x1U << AUDIO_TRINT_FIFO1_EMP_INT_Pos)

#define AUDIO_TRINT_FIFO1_HALF_FULL_INT_Pos                                     8
#define AUDIO_TRINT_FIFO1_HALF_FULL_INT_Msk                                     (0x1U << AUDIO_TRINT_FIFO1_HALF_FULL_INT_Pos)

#define AUDIO_TRINT_FIFO1_FULL_INT_Pos                                          7
#define AUDIO_TRINT_FIFO1_FULL_INT_Msk                                          (0x1U << AUDIO_TRINT_FIFO1_FULL_INT_Pos)

#define AUDIO_TRINT_RAM1_FRAME_VLD_INT_Pos                                      6
#define AUDIO_TRINT_RAM1_FRAME_VLD_INT_Msk                                      (0x1U << AUDIO_TRINT_RAM1_FRAME_VLD_INT_Pos)

#define AUDIO_TRINT_FIFO0_UNDERFLOW_INT_Pos                                     5
#define AUDIO_TRINT_FIFO0_UNDERFLOW_INT_Msk                                     (0x1U << AUDIO_TRINT_FIFO0_UNDERFLOW_INT_Pos)

#define AUDIO_TRINT_FIFO0_OVERFLOW_INT_Pos                                      4
#define AUDIO_TRINT_FIFO0_OVERFLOW_INT_Msk                                      (0x1U << AUDIO_TRINT_FIFO0_OVERFLOW_INT_Pos)

#define AUDIO_TRINT_FIFO0_EMP_INT_Pos                                           3
#define AUDIO_TRINT_FIFO0_EMP_INT_Msk                                           (0x1U << AUDIO_TRINT_FIFO0_EMP_INT_Pos)

#define AUDIO_TRINT_FIFO0_HALF_FULL_INT_Pos                                     2
#define AUDIO_TRINT_FIFO0_HALF_FULL_INT_Msk                                     (0x1U << AUDIO_TRINT_FIFO0_HALF_FULL_INT_Pos)

#define AUDIO_TRINT_FIFO0_FULL_INT_Pos                                          1
#define AUDIO_TRINT_FIFO0_FULL_INT_Msk                                          (0x1U << AUDIO_TRINT_FIFO0_FULL_INT_Pos)

#define AUDIO_TRINT_RAM0_FRAME_VLD_INT_Pos                                      0
#define AUDIO_TRINT_RAM0_FRAME_VLD_INT_Msk                                      (0x1U << AUDIO_TRINT_RAM0_FRAME_VLD_INT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TRINTMSK
//
#define AUDIO_TRINTMSK_VAD_ACT_MSK_O_Pos                                        17
#define AUDIO_TRINTMSK_VAD_ACT_MSK_O_Msk                                        (0x1U << AUDIO_TRINTMSK_VAD_ACT_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO2_UNDERFLOW_MSK_O_Pos                                16
#define AUDIO_TRINTMSK_FIFO2_UNDERFLOW_MSK_O_Msk                                (0x1U << AUDIO_TRINTMSK_FIFO2_UNDERFLOW_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO2_OVERFLOW_MSK_O_Pos                                 15
#define AUDIO_TRINTMSK_FIFO2_OVERFLOW_MSK_O_Msk                                 (0x1U << AUDIO_TRINTMSK_FIFO2_OVERFLOW_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO2_EMP_MSK_O_Pos                                      14
#define AUDIO_TRINTMSK_FIFO2_EMP_MSK_O_Msk                                      (0x1U << AUDIO_TRINTMSK_FIFO2_EMP_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO2_HALF_FULL_MSK_O_Pos                                13
#define AUDIO_TRINTMSK_FIFO2_HALF_FULL_MSK_O_Msk                                (0x1U << AUDIO_TRINTMSK_FIFO2_HALF_FULL_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO2_FULL_MSK_O_Pos                                     12
#define AUDIO_TRINTMSK_FIFO2_FULL_MSK_O_Msk                                     (0x1U << AUDIO_TRINTMSK_FIFO2_FULL_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO1_UNDERFLOW_MSK_O_Pos                                11
#define AUDIO_TRINTMSK_FIFO1_UNDERFLOW_MSK_O_Msk                                (0x1U << AUDIO_TRINTMSK_FIFO1_UNDERFLOW_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO1_OVERFLOW_MSK_O_Pos                                 10
#define AUDIO_TRINTMSK_FIFO1_OVERFLOW_MSK_O_Msk                                 (0x1U << AUDIO_TRINTMSK_FIFO1_OVERFLOW_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO1_EMP_MSK_O_Pos                                      9
#define AUDIO_TRINTMSK_FIFO1_EMP_MSK_O_Msk                                      (0x1U << AUDIO_TRINTMSK_FIFO1_EMP_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO1_HALF_FULL_MSK_O_Pos                                8
#define AUDIO_TRINTMSK_FIFO1_HALF_FULL_MSK_O_Msk                                (0x1U << AUDIO_TRINTMSK_FIFO1_HALF_FULL_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO1_FULL_MSK_O_Pos                                     7
#define AUDIO_TRINTMSK_FIFO1_FULL_MSK_O_Msk                                     (0x1U << AUDIO_TRINTMSK_FIFO1_FULL_MSK_O_Pos)

#define AUDIO_TRINTMSK_RAM1_FRAME_VLD_MSK_O_Pos                                 6
#define AUDIO_TRINTMSK_RAM1_FRAME_VLD_MSK_O_Msk                                 (0x1U << AUDIO_TRINTMSK_RAM1_FRAME_VLD_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO0_UNDERFLOW_MSK_O_Pos                                5
#define AUDIO_TRINTMSK_FIFO0_UNDERFLOW_MSK_O_Msk                                (0x1U << AUDIO_TRINTMSK_FIFO0_UNDERFLOW_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO0_OVERFLOW_MSK_O_Pos                                 4
#define AUDIO_TRINTMSK_FIFO0_OVERFLOW_MSK_O_Msk                                 (0x1U << AUDIO_TRINTMSK_FIFO0_OVERFLOW_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO0_EMP_MSK_O_Pos                                      3
#define AUDIO_TRINTMSK_FIFO0_EMP_MSK_O_Msk                                      (0x1U << AUDIO_TRINTMSK_FIFO0_EMP_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO0_HALF_FULL_MSK_O_Pos                                2
#define AUDIO_TRINTMSK_FIFO0_HALF_FULL_MSK_O_Msk                                (0x1U << AUDIO_TRINTMSK_FIFO0_HALF_FULL_MSK_O_Pos)

#define AUDIO_TRINTMSK_FIFO0_FULL_MSK_O_Pos                                     1
#define AUDIO_TRINTMSK_FIFO0_FULL_MSK_O_Msk                                     (0x1U << AUDIO_TRINTMSK_FIFO0_FULL_MSK_O_Pos)

#define AUDIO_TRINTMSK_RAM0_FRAME_VLD_MSK_O_Pos                                 0
#define AUDIO_TRINTMSK_RAM0_FRAME_VLD_MSK_O_Msk                                 (0x1U << AUDIO_TRINTMSK_RAM0_FRAME_VLD_MSK_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// AFEINT
//
#define AUDIO_AFEINT_CH2_DIG_CMP_CNT_INT_Pos                                    11
#define AUDIO_AFEINT_CH2_DIG_CMP_CNT_INT_Msk                                    (0x1U << AUDIO_AFEINT_CH2_DIG_CMP_CNT_INT_Pos)

#define AUDIO_AFEINT_CH2_AGC_GAIN_RDY_INT_Pos                                   10
#define AUDIO_AFEINT_CH2_AGC_GAIN_RDY_INT_Msk                                   (0x1U << AUDIO_AFEINT_CH2_AGC_GAIN_RDY_INT_Pos)

#define AUDIO_AFEINT_CH2_AUDIO_OUT_RDY_INT_Pos                                  9
#define AUDIO_AFEINT_CH2_AUDIO_OUT_RDY_INT_Msk                                  (0x1U << AUDIO_AFEINT_CH2_AUDIO_OUT_RDY_INT_Pos)

#define AUDIO_AFEINT_CH1_DIG_CMP_CNT_INT_Pos                                    8
#define AUDIO_AFEINT_CH1_DIG_CMP_CNT_INT_Msk                                    (0x1U << AUDIO_AFEINT_CH1_DIG_CMP_CNT_INT_Pos)

#define AUDIO_AFEINT_CH1_AGC_GAIN_RDY_INT_Pos                                   7
#define AUDIO_AFEINT_CH1_AGC_GAIN_RDY_INT_Msk                                   (0x1U << AUDIO_AFEINT_CH1_AGC_GAIN_RDY_INT_Pos)

#define AUDIO_AFEINT_CH1_AUDIO_OUT_RDY_INT_Pos                                  6
#define AUDIO_AFEINT_CH1_AUDIO_OUT_RDY_INT_Msk                                  (0x1U << AUDIO_AFEINT_CH1_AUDIO_OUT_RDY_INT_Pos)

#define AUDIO_AFEINT_CH0_DIG_CMP_CNT_INT_Pos                                    5
#define AUDIO_AFEINT_CH0_DIG_CMP_CNT_INT_Msk                                    (0x1U << AUDIO_AFEINT_CH0_DIG_CMP_CNT_INT_Pos)

#define AUDIO_AFEINT_CH0_AGC_GAIN_RDY_INT_Pos                                   4
#define AUDIO_AFEINT_CH0_AGC_GAIN_RDY_INT_Msk                                   (0x1U << AUDIO_AFEINT_CH0_AGC_GAIN_RDY_INT_Pos)

#define AUDIO_AFEINT_CH0_AUDIO_OUT_RDY_INT_Pos                                  3
#define AUDIO_AFEINT_CH0_AUDIO_OUT_RDY_INT_Msk                                  (0x1U << AUDIO_AFEINT_CH0_AUDIO_OUT_RDY_INT_Pos)

#define AUDIO_AFEINT_COMP_WKUP_INT_Pos                                          2
#define AUDIO_AFEINT_COMP_WKUP_INT_Msk                                          (0x1U << AUDIO_AFEINT_COMP_WKUP_INT_Pos)

#define AUDIO_AFEINT_DIG_CMPB_INT_Pos                                           1
#define AUDIO_AFEINT_DIG_CMPB_INT_Msk                                           (0x1U << AUDIO_AFEINT_DIG_CMPB_INT_Pos)

#define AUDIO_AFEINT_DIG_CMPA_INT_Pos                                           0
#define AUDIO_AFEINT_DIG_CMPA_INT_Msk                                           (0x1U << AUDIO_AFEINT_DIG_CMPA_INT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// AFEINTMSK
//
#define AUDIO_AFEINTMSK_RSV7_Pos                                                11
#define AUDIO_AFEINTMSK_RSV7_Msk                                                (0x1U << AUDIO_AFEINTMSK_RSV7_Pos)

#define AUDIO_AFEINTMSK_RSV8_Pos                                                10
#define AUDIO_AFEINTMSK_RSV8_Msk                                                (0x1U << AUDIO_AFEINTMSK_RSV8_Pos)

#define AUDIO_AFEINTMSK_RSV9_Pos                                                9
#define AUDIO_AFEINTMSK_RSV9_Msk                                                (0x1U << AUDIO_AFEINTMSK_RSV9_Pos)

#define AUDIO_AFEINTMSK_RSV10_Pos                                               8
#define AUDIO_AFEINTMSK_RSV10_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV10_Pos)

#define AUDIO_AFEINTMSK_RSV11_Pos                                               7
#define AUDIO_AFEINTMSK_RSV11_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV11_Pos)

#define AUDIO_AFEINTMSK_RSV12_Pos                                               6
#define AUDIO_AFEINTMSK_RSV12_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV12_Pos)

#define AUDIO_AFEINTMSK_RSV13_Pos                                               5
#define AUDIO_AFEINTMSK_RSV13_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV13_Pos)

#define AUDIO_AFEINTMSK_RSV14_Pos                                               4
#define AUDIO_AFEINTMSK_RSV14_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV14_Pos)

#define AUDIO_AFEINTMSK_RSV15_Pos                                               3
#define AUDIO_AFEINTMSK_RSV15_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV15_Pos)

#define AUDIO_AFEINTMSK_RSV16_Pos                                               2
#define AUDIO_AFEINTMSK_RSV16_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV16_Pos)

#define AUDIO_AFEINTMSK_RSV17_Pos                                               1
#define AUDIO_AFEINTMSK_RSV17_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV17_Pos)

#define AUDIO_AFEINTMSK_RSV18_Pos                                               0
#define AUDIO_AFEINTMSK_RSV18_Msk                                               (0x1U << AUDIO_AFEINTMSK_RSV18_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANALOCK
//
#define AUDIO_ANALOCK_RSV19_Pos                                                 0
#define AUDIO_ANALOCK_RSV19_Msk                                                 (0xffffffffU << AUDIO_ANALOCK_RSV19_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA0CFG
//
#define AUDIO_ANA0CFG_RSV20_Pos                                                 31
#define AUDIO_ANA0CFG_RSV20_Msk                                                 (0x1U << AUDIO_ANA0CFG_RSV20_Pos)

#define AUDIO_ANA0CFG_PU_BST_CH1_O_Pos                                          30
#define AUDIO_ANA0CFG_PU_BST_CH1_O_Msk                                          (0x1U << AUDIO_ANA0CFG_PU_BST_CH1_O_Pos)

#define AUDIO_ANA0CFG_PU_BST_CH0_O_Pos                                          29
#define AUDIO_ANA0CFG_PU_BST_CH0_O_Msk                                          (0x1U << AUDIO_ANA0CFG_PU_BST_CH0_O_Pos)

#define AUDIO_ANA0CFG_RSV21_Pos                                                 28
#define AUDIO_ANA0CFG_RSV21_Msk                                                 (0x1U << AUDIO_ANA0CFG_RSV21_Pos)

#define AUDIO_ANA0CFG_PU_AUDIO_BUF_CH0_O_Pos                                    27
#define AUDIO_ANA0CFG_PU_AUDIO_BUF_CH0_O_Msk                                    (0x1U << AUDIO_ANA0CFG_PU_AUDIO_BUF_CH0_O_Pos)

#define AUDIO_ANA0CFG_RSV22_Pos                                                 26
#define AUDIO_ANA0CFG_RSV22_Msk                                                 (0x1U << AUDIO_ANA0CFG_RSV22_Pos)

#define AUDIO_ANA0CFG_RSV23_Pos                                                 25
#define AUDIO_ANA0CFG_RSV23_Msk                                                 (0x1U << AUDIO_ANA0CFG_RSV23_Pos)

#define AUDIO_ANA0CFG_MUTE_PGA_CH0_O_Pos                                        24
#define AUDIO_ANA0CFG_MUTE_PGA_CH0_O_Msk                                        (0x1U << AUDIO_ANA0CFG_MUTE_PGA_CH0_O_Pos)

#define AUDIO_ANA0CFG_RSV24_Pos                                                 23
#define AUDIO_ANA0CFG_RSV24_Msk                                                 (0x1U << AUDIO_ANA0CFG_RSV24_Pos)

#define AUDIO_ANA0CFG_MUTE_BST_CH1_O_Pos                                        22
#define AUDIO_ANA0CFG_MUTE_BST_CH1_O_Msk                                        (0x1U << AUDIO_ANA0CFG_MUTE_BST_CH1_O_Pos)

#define AUDIO_ANA0CFG_MUTE_BST_CH0_O_Pos                                        21
#define AUDIO_ANA0CFG_MUTE_BST_CH0_O_Msk                                        (0x1U << AUDIO_ANA0CFG_MUTE_BST_CH0_O_Pos)

#define AUDIO_ANA0CFG_MICBIAS_EN_O_Pos                                          20
#define AUDIO_ANA0CFG_MICBIAS_EN_O_Msk                                          (0x1U << AUDIO_ANA0CFG_MICBIAS_EN_O_Pos)

#define AUDIO_ANA0CFG_BST_SEL_CH1_O_Pos                                         14
#define AUDIO_ANA0CFG_BST_SEL_CH1_O_Msk                                         (0x3fU << AUDIO_ANA0CFG_BST_SEL_CH1_O_Pos)

#define AUDIO_ANA0CFG_BST_SEL_CH0_O_Pos                                         12
#define AUDIO_ANA0CFG_BST_SEL_CH0_O_Msk                                         (0x3U << AUDIO_ANA0CFG_BST_SEL_CH0_O_Pos)

#define AUDIO_ANA0CFG_RST_SD_CH1_O_Pos                                          11
#define AUDIO_ANA0CFG_RST_SD_CH1_O_Msk                                          (0x1U << AUDIO_ANA0CFG_RST_SD_CH1_O_Pos)

#define AUDIO_ANA0CFG_RST_SD_CH0_O_Pos                                          10
#define AUDIO_ANA0CFG_RST_SD_CH0_O_Msk                                          (0x1U << AUDIO_ANA0CFG_RST_SD_CH0_O_Pos)

#define AUDIO_ANA0CFG_BIAS_REF_SEL_O_Pos                                        9
#define AUDIO_ANA0CFG_BIAS_REF_SEL_O_Msk                                        (0x1U << AUDIO_ANA0CFG_BIAS_REF_SEL_O_Pos)

#define AUDIO_ANA0CFG_BIAS_OUT_EN1_O_Pos                                        8
#define AUDIO_ANA0CFG_BIAS_OUT_EN1_O_Msk                                        (0x1U << AUDIO_ANA0CFG_BIAS_OUT_EN1_O_Pos)

#define AUDIO_ANA0CFG_RSV25_Pos                                                 7
#define AUDIO_ANA0CFG_RSV25_Msk                                                 (0x1U << AUDIO_ANA0CFG_RSV25_Pos)

#define AUDIO_ANA0CFG_RSV26_Pos                                                 6
#define AUDIO_ANA0CFG_RSV26_Msk                                                 (0x1U << AUDIO_ANA0CFG_RSV26_Pos)

#define AUDIO_ANA0CFG_RSV27_Pos                                                 3
#define AUDIO_ANA0CFG_RSV27_Msk                                                 (0x7U << AUDIO_ANA0CFG_RSV27_Pos)

#define AUDIO_ANA0CFG_VCOM_SEL_O_Pos                                            0
#define AUDIO_ANA0CFG_VCOM_SEL_O_Msk                                            (0x7U << AUDIO_ANA0CFG_VCOM_SEL_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA1CFG
//
#define AUDIO_ANA1CFG_ANALOG_TESTPAD_EN_O_Pos                                   27
#define AUDIO_ANA1CFG_ANALOG_TESTPAD_EN_O_Msk                                   (0x1U << AUDIO_ANA1CFG_ANALOG_TESTPAD_EN_O_Pos)

#define AUDIO_ANA1CFG_RSV28_Pos                                                 26
#define AUDIO_ANA1CFG_RSV28_Msk                                                 (0x1U << AUDIO_ANA1CFG_RSV28_Pos)

#define AUDIO_ANA1CFG_RSV29_Pos                                                 23
#define AUDIO_ANA1CFG_RSV29_Msk                                                 (0x7U << AUDIO_ANA1CFG_RSV29_Pos)

#define AUDIO_ANA1CFG_TEST_SD_CH1_O_Pos                                         20
#define AUDIO_ANA1CFG_TEST_SD_CH1_O_Msk                                         (0x7U << AUDIO_ANA1CFG_TEST_SD_CH1_O_Pos)

#define AUDIO_ANA1CFG_TEST_SD_CH0_O_Pos                                         17
#define AUDIO_ANA1CFG_TEST_SD_CH0_O_Msk                                         (0x7U << AUDIO_ANA1CFG_TEST_SD_CH0_O_Pos)

#define AUDIO_ANA1CFG_RSV30_Pos                                                 16
#define AUDIO_ANA1CFG_RSV30_Msk                                                 (0x1U << AUDIO_ANA1CFG_RSV30_Pos)

#define AUDIO_ANA1CFG_EN_CLK_ADC_CH1_O_Pos                                      15
#define AUDIO_ANA1CFG_EN_CLK_ADC_CH1_O_Msk                                      (0x1U << AUDIO_ANA1CFG_EN_CLK_ADC_CH1_O_Pos)

#define AUDIO_ANA1CFG_EN_CLK_ADC_CH0_O_Pos                                      14
#define AUDIO_ANA1CFG_EN_CLK_ADC_CH0_O_Msk                                      (0x1U << AUDIO_ANA1CFG_EN_CLK_ADC_CH0_O_Pos)

#define AUDIO_ANA1CFG_RSV31_Pos                                                 13
#define AUDIO_ANA1CFG_RSV31_Msk                                                 (0x1U << AUDIO_ANA1CFG_RSV31_Pos)

#define AUDIO_ANA1CFG_SD_ADC_SEL_CH1_O_Pos                                      12
#define AUDIO_ANA1CFG_SD_ADC_SEL_CH1_O_Msk                                      (0x1U << AUDIO_ANA1CFG_SD_ADC_SEL_CH1_O_Pos)

#define AUDIO_ANA1CFG_SD_ADC_SEL_CH0_O_Pos                                      11
#define AUDIO_ANA1CFG_SD_ADC_SEL_CH0_O_Msk                                      (0x1U << AUDIO_ANA1CFG_SD_ADC_SEL_CH0_O_Pos)

#define AUDIO_ANA1CFG_IREF_TRIM_O_Pos                                           8
#define AUDIO_ANA1CFG_IREF_TRIM_O_Msk                                           (0x7U << AUDIO_ANA1CFG_IREF_TRIM_O_Pos)

#define AUDIO_ANA1CFG_EN_OSC80K_O_Pos                                           7
#define AUDIO_ANA1CFG_EN_OSC80K_O_Msk                                           (0x1U << AUDIO_ANA1CFG_EN_OSC80K_O_Pos)

#define AUDIO_ANA1CFG_RSV32_Pos                                                 6
#define AUDIO_ANA1CFG_RSV32_Msk                                                 (0x1U << AUDIO_ANA1CFG_RSV32_Pos)

#define AUDIO_ANA1CFG_EN_SD_CH1_O_Pos                                           5
#define AUDIO_ANA1CFG_EN_SD_CH1_O_Msk                                           (0x1U << AUDIO_ANA1CFG_EN_SD_CH1_O_Pos)

#define AUDIO_ANA1CFG_EN_SD_CH0_O_Pos                                           4
#define AUDIO_ANA1CFG_EN_SD_CH0_O_Msk                                           (0x1U << AUDIO_ANA1CFG_EN_SD_CH0_O_Pos)

#define AUDIO_ANA1CFG_RSV33_Pos                                                 3
#define AUDIO_ANA1CFG_RSV33_Msk                                                 (0x1U << AUDIO_ANA1CFG_RSV33_Pos)

#define AUDIO_ANA1CFG_RSV34_Pos                                                 2
#define AUDIO_ANA1CFG_RSV34_Msk                                                 (0x1U << AUDIO_ANA1CFG_RSV34_Pos)

#define AUDIO_ANA1CFG_PU_PGA_CH0_O_Pos                                          1
#define AUDIO_ANA1CFG_PU_PGA_CH0_O_Msk                                          (0x1U << AUDIO_ANA1CFG_PU_PGA_CH0_O_Pos)

#define AUDIO_ANA1CFG_PU_BG_O_Pos                                               0
#define AUDIO_ANA1CFG_PU_BG_O_Msk                                               (0x1U << AUDIO_ANA1CFG_PU_BG_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA2CFG
//
#define AUDIO_ANA2CFG_ANA_RES_CTRL_O_Pos                                        16
#define AUDIO_ANA2CFG_ANA_RES_CTRL_O_Msk                                        (0xffffU << AUDIO_ANA2CFG_ANA_RES_CTRL_O_Pos)

#define AUDIO_ANA2CFG_BIAS_SET_O_Pos                                            14
#define AUDIO_ANA2CFG_BIAS_SET_O_Msk                                            (0x3U << AUDIO_ANA2CFG_BIAS_SET_O_Pos)

#define AUDIO_ANA2CFG_RSV35_Pos                                                 12
#define AUDIO_ANA2CFG_RSV35_Msk                                                 (0x3U << AUDIO_ANA2CFG_RSV35_Pos)

#define AUDIO_ANA2CFG_RSV36_Pos                                                 8
#define AUDIO_ANA2CFG_RSV36_Msk                                                 (0xfU << AUDIO_ANA2CFG_RSV36_Pos)

#define AUDIO_ANA2CFG_RSV37_Pos                                                 4
#define AUDIO_ANA2CFG_RSV37_Msk                                                 (0xfU << AUDIO_ANA2CFG_RSV37_Pos)

#define AUDIO_ANA2CFG_VBG_TRIM_O_Pos                                            0
#define AUDIO_ANA2CFG_VBG_TRIM_O_Msk                                            (0xfU << AUDIO_ANA2CFG_VBG_TRIM_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA3CFG
//
#define AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Pos                                      24
#define AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Msk                                      (0xffU << AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Pos)

#define AUDIO_ANA3CFG_CH0_SYSCTL_AGCPEAK_O_Pos                                  23
#define AUDIO_ANA3CFG_CH0_SYSCTL_AGCPEAK_O_Msk                                  (0x1U << AUDIO_ANA3CFG_CH0_SYSCTL_AGCPEAK_O_Pos)

#define AUDIO_ANA3CFG_CH0_DIG_COMP_THRES_O_Pos                                  7
#define AUDIO_ANA3CFG_CH0_DIG_COMP_THRES_O_Msk                                  (0xffffU << AUDIO_ANA3CFG_CH0_DIG_COMP_THRES_O_Pos)

#define AUDIO_ANA3CFG_CH0_DIG_COMP_MODE_O_Pos                                   6
#define AUDIO_ANA3CFG_CH0_DIG_COMP_MODE_O_Msk                                   (0x1U << AUDIO_ANA3CFG_CH0_DIG_COMP_MODE_O_Pos)

#define AUDIO_ANA3CFG_CH0_DIG_COMP_SET_O_Pos                                    1
#define AUDIO_ANA3CFG_CH0_DIG_COMP_SET_O_Msk                                    (0x1fU << AUDIO_ANA3CFG_CH0_DIG_COMP_SET_O_Pos)

#define AUDIO_ANA3CFG_CH0_DIG_COMP_EN_O_Pos                                     0
#define AUDIO_ANA3CFG_CH0_DIG_COMP_EN_O_Msk                                     (0x1U << AUDIO_ANA3CFG_CH0_DIG_COMP_EN_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA4CFG
//
#define AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Pos                                17
#define AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Msk                                (0xffU << AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Pos)

#define AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Pos                                 9
#define AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Msk                                 (0xffU << AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Pos)

#define AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Pos                                 1
#define AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Msk                                 (0xffU << AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Pos)

#define AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Pos                                   0
#define AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Msk                                   (0x1U << AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA5CFG
//
#define AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Pos                         16
#define AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Msk                         (0xffffU << AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Pos)

#define AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Pos                            0
#define AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Msk                            (0xffffU << AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA6CFG
//
#define AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Pos                                16
#define AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Msk                                (0xffffU << AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Pos)

#define AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Pos                                0
#define AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Msk                                (0xffffU << AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA7CFG
//
#define AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Pos                                  25
#define AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Msk                                  (0x3fU << AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Pos)

#define AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Pos                                19
#define AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Msk                                (0x3fU << AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Pos)

#define AUDIO_ANA7CFG_CH0_AGC_DEFAULT_EN_O_Pos                                  18
#define AUDIO_ANA7CFG_CH0_AGC_DEFAULT_EN_O_Msk                                  (0x1U << AUDIO_ANA7CFG_CH0_AGC_DEFAULT_EN_O_Pos)

#define AUDIO_ANA7CFG_CH0_AGC_GAIN_SEL_O_Pos                                    17
#define AUDIO_ANA7CFG_CH0_AGC_GAIN_SEL_O_Msk                                    (0x1U << AUDIO_ANA7CFG_CH0_AGC_GAIN_SEL_O_Pos)

#define AUDIO_ANA7CFG_CH0_AGC_EN_O_Pos                                          16
#define AUDIO_ANA7CFG_CH0_AGC_EN_O_Msk                                          (0x1U << AUDIO_ANA7CFG_CH0_AGC_EN_O_Pos)

#define AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Pos                                0
#define AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Msk                                (0xffffU << AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA8CFG
//
#define AUDIO_ANA8CFG_RSV38_Pos                                                 24
#define AUDIO_ANA8CFG_RSV38_Msk                                                 (0xffU << AUDIO_ANA8CFG_RSV38_Pos)

#define AUDIO_ANA8CFG_RSV39_Pos                                                 23
#define AUDIO_ANA8CFG_RSV39_Msk                                                 (0x1U << AUDIO_ANA8CFG_RSV39_Pos)

#define AUDIO_ANA8CFG_RSV40_Pos                                                 7
#define AUDIO_ANA8CFG_RSV40_Msk                                                 (0xffffU << AUDIO_ANA8CFG_RSV40_Pos)

#define AUDIO_ANA8CFG_RSV41_Pos                                                 6
#define AUDIO_ANA8CFG_RSV41_Msk                                                 (0x1U << AUDIO_ANA8CFG_RSV41_Pos)

#define AUDIO_ANA8CFG_RSV42_Pos                                                 1
#define AUDIO_ANA8CFG_RSV42_Msk                                                 (0x1fU << AUDIO_ANA8CFG_RSV42_Pos)

#define AUDIO_ANA8CFG_RSV43_Pos                                                 0
#define AUDIO_ANA8CFG_RSV43_Msk                                                 (0x1U << AUDIO_ANA8CFG_RSV43_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA9CFG
//
#define AUDIO_ANA9CFG_RSV44_Pos                                                 17
#define AUDIO_ANA9CFG_RSV44_Msk                                                 (0xffU << AUDIO_ANA9CFG_RSV44_Pos)

#define AUDIO_ANA9CFG_RSV45_Pos                                                 9
#define AUDIO_ANA9CFG_RSV45_Msk                                                 (0xffU << AUDIO_ANA9CFG_RSV45_Pos)

#define AUDIO_ANA9CFG_RSV46_Pos                                                 1
#define AUDIO_ANA9CFG_RSV46_Msk                                                 (0xffU << AUDIO_ANA9CFG_RSV46_Pos)

#define AUDIO_ANA9CFG_RSV47_Pos                                                 0
#define AUDIO_ANA9CFG_RSV47_Msk                                                 (0x1U << AUDIO_ANA9CFG_RSV47_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA10CFG
//
#define AUDIO_ANA10CFG_RSV48_Pos                                                16
#define AUDIO_ANA10CFG_RSV48_Msk                                                (0xffffU << AUDIO_ANA10CFG_RSV48_Pos)

#define AUDIO_ANA10CFG_RSV49_Pos                                                0
#define AUDIO_ANA10CFG_RSV49_Msk                                                (0xffffU << AUDIO_ANA10CFG_RSV49_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA11CFG
//
#define AUDIO_ANA11CFG_RSV50_Pos                                                16
#define AUDIO_ANA11CFG_RSV50_Msk                                                (0xffffU << AUDIO_ANA11CFG_RSV50_Pos)

#define AUDIO_ANA11CFG_RSV51_Pos                                                0
#define AUDIO_ANA11CFG_RSV51_Msk                                                (0xffffU << AUDIO_ANA11CFG_RSV51_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA12CFG
//
#define AUDIO_ANA12CFG_RSV52_Pos                                                25
#define AUDIO_ANA12CFG_RSV52_Msk                                                (0x3fU << AUDIO_ANA12CFG_RSV52_Pos)

#define AUDIO_ANA12CFG_RSV53_Pos                                                19
#define AUDIO_ANA12CFG_RSV53_Msk                                                (0x3fU << AUDIO_ANA12CFG_RSV53_Pos)

#define AUDIO_ANA12CFG_RSV54_Pos                                                18
#define AUDIO_ANA12CFG_RSV54_Msk                                                (0x1U << AUDIO_ANA12CFG_RSV54_Pos)

#define AUDIO_ANA12CFG_RSV55_Pos                                                17
#define AUDIO_ANA12CFG_RSV55_Msk                                                (0x1U << AUDIO_ANA12CFG_RSV55_Pos)

#define AUDIO_ANA12CFG_RSV56_Pos                                                16
#define AUDIO_ANA12CFG_RSV56_Msk                                                (0x1U << AUDIO_ANA12CFG_RSV56_Pos)

#define AUDIO_ANA12CFG_RSV57_Pos                                                0
#define AUDIO_ANA12CFG_RSV57_Msk                                                (0xffffU << AUDIO_ANA12CFG_RSV57_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA13CFG
//
#define AUDIO_ANA13CFG_RSV58_Pos                                                24
#define AUDIO_ANA13CFG_RSV58_Msk                                                (0xffU << AUDIO_ANA13CFG_RSV58_Pos)

#define AUDIO_ANA13CFG_RSV59_Pos                                                23
#define AUDIO_ANA13CFG_RSV59_Msk                                                (0x1U << AUDIO_ANA13CFG_RSV59_Pos)

#define AUDIO_ANA13CFG_RSV60_Pos                                                7
#define AUDIO_ANA13CFG_RSV60_Msk                                                (0xffffU << AUDIO_ANA13CFG_RSV60_Pos)

#define AUDIO_ANA13CFG_RSV61_Pos                                                6
#define AUDIO_ANA13CFG_RSV61_Msk                                                (0x1U << AUDIO_ANA13CFG_RSV61_Pos)

#define AUDIO_ANA13CFG_RSV62_Pos                                                1
#define AUDIO_ANA13CFG_RSV62_Msk                                                (0x1fU << AUDIO_ANA13CFG_RSV62_Pos)

#define AUDIO_ANA13CFG_RSV63_Pos                                                0
#define AUDIO_ANA13CFG_RSV63_Msk                                                (0x1U << AUDIO_ANA13CFG_RSV63_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA14CFG
//
#define AUDIO_ANA14CFG_RSV64_Pos                                                17
#define AUDIO_ANA14CFG_RSV64_Msk                                                (0xffU << AUDIO_ANA14CFG_RSV64_Pos)

#define AUDIO_ANA14CFG_RSV65_Pos                                                9
#define AUDIO_ANA14CFG_RSV65_Msk                                                (0xffU << AUDIO_ANA14CFG_RSV65_Pos)

#define AUDIO_ANA14CFG_RSV66_Pos                                                1
#define AUDIO_ANA14CFG_RSV66_Msk                                                (0xffU << AUDIO_ANA14CFG_RSV66_Pos)

#define AUDIO_ANA14CFG_RSV67_Pos                                                0
#define AUDIO_ANA14CFG_RSV67_Msk                                                (0x1U << AUDIO_ANA14CFG_RSV67_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA15CFG
//
#define AUDIO_ANA15CFG_RSV68_Pos                                                16
#define AUDIO_ANA15CFG_RSV68_Msk                                                (0xffffU << AUDIO_ANA15CFG_RSV68_Pos)

#define AUDIO_ANA15CFG_RSV69_Pos                                                0
#define AUDIO_ANA15CFG_RSV69_Msk                                                (0xffffU << AUDIO_ANA15CFG_RSV69_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA16CFG
//
#define AUDIO_ANA16CFG_RSV70_Pos                                                16
#define AUDIO_ANA16CFG_RSV70_Msk                                                (0xffffU << AUDIO_ANA16CFG_RSV70_Pos)

#define AUDIO_ANA16CFG_RSV71_Pos                                                0
#define AUDIO_ANA16CFG_RSV71_Msk                                                (0xffffU << AUDIO_ANA16CFG_RSV71_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA17CFG
//
#define AUDIO_ANA17CFG_RSV72_Pos                                                25
#define AUDIO_ANA17CFG_RSV72_Msk                                                (0x3fU << AUDIO_ANA17CFG_RSV72_Pos)

#define AUDIO_ANA17CFG_RSV73_Pos                                                19
#define AUDIO_ANA17CFG_RSV73_Msk                                                (0x3fU << AUDIO_ANA17CFG_RSV73_Pos)

#define AUDIO_ANA17CFG_RSV74_Pos                                                18
#define AUDIO_ANA17CFG_RSV74_Msk                                                (0x1U << AUDIO_ANA17CFG_RSV74_Pos)

#define AUDIO_ANA17CFG_RSV75_Pos                                                17
#define AUDIO_ANA17CFG_RSV75_Msk                                                (0x1U << AUDIO_ANA17CFG_RSV75_Pos)

#define AUDIO_ANA17CFG_RSV76_Pos                                                16
#define AUDIO_ANA17CFG_RSV76_Msk                                                (0x1U << AUDIO_ANA17CFG_RSV76_Pos)

#define AUDIO_ANA17CFG_RSV77_Pos                                                0
#define AUDIO_ANA17CFG_RSV77_Msk                                                (0xffffU << AUDIO_ANA17CFG_RSV77_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA18CFG
//
#define AUDIO_ANA18CFG_RSV78_Pos                                                12
#define AUDIO_ANA18CFG_RSV78_Msk                                                (0x3fU << AUDIO_ANA18CFG_RSV78_Pos)

#define AUDIO_ANA18CFG_RSV79_Pos                                                6
#define AUDIO_ANA18CFG_RSV79_Msk                                                (0x3fU << AUDIO_ANA18CFG_RSV79_Pos)

#define AUDIO_ANA18CFG_CH0_AGC_GAIN_I_Pos                                       0
#define AUDIO_ANA18CFG_CH0_AGC_GAIN_I_Msk                                       (0x3fU << AUDIO_ANA18CFG_CH0_AGC_GAIN_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VADDEBUG0
//
#define AUDIO_VADDEBUG0_VAD_STP_I_Pos                                           0
#define AUDIO_VADDEBUG0_VAD_STP_I_Msk                                           (0xffffffffU << AUDIO_VADDEBUG0_VAD_STP_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VADDEBUG1
//
#define AUDIO_VADDEBUG1_VAD_LTP_I_Pos                                           0
#define AUDIO_VADDEBUG1_VAD_LTP_I_Msk                                           (0xffffffffU << AUDIO_VADDEBUG1_VAD_LTP_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VADDEBUG2
//
#define AUDIO_VADDEBUG2_VAD_DEV_CAL1_I_Pos                                      0
#define AUDIO_VADDEBUG2_VAD_DEV_CAL1_I_Msk                                      (0xffffffffU << AUDIO_VADDEBUG2_VAD_DEV_CAL1_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VADDEBUG3
//
#define AUDIO_VADDEBUG3_VAD_DEV_CAL2_I_Pos                                      0
#define AUDIO_VADDEBUG3_VAD_DEV_CAL2_I_Msk                                      (0xffffffffU << AUDIO_VADDEBUG3_VAD_DEV_CAL2_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// VADDEBUG4
//
#define AUDIO_VADDEBUG4_VAD_FSM_I_Pos                                           0
#define AUDIO_VADDEBUG4_VAD_FSM_I_Msk                                           (0xffffffffU << AUDIO_VADDEBUG4_VAD_FSM_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LRFIFO
//
#define AUDIO_LRFIFO_LR_FIFO_DATA_I_Pos                                         0
#define AUDIO_LRFIFO_LR_FIFO_DATA_I_Msk                                         (0xffffffffU << AUDIO_LRFIFO_LR_FIFO_DATA_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LRRAM
//
#define AUDIO_LRRAM_LR_RAM_DATA_I_Pos                                           0
#define AUDIO_LRRAM_LR_RAM_DATA_I_Msk                                           (0xffffffffU << AUDIO_LRRAM_LR_RAM_DATA_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA19CFG
//
#define AUDIO_ANA19CFG_AUDIO_TEST_SEL_O_Pos                                     22
#define AUDIO_ANA19CFG_AUDIO_TEST_SEL_O_Msk                                     (0xffU << AUDIO_ANA19CFG_AUDIO_TEST_SEL_O_Pos)

#define AUDIO_ANA19CFG_VAD_TEST_SEL_O_Pos                                       18
#define AUDIO_ANA19CFG_VAD_TEST_SEL_O_Msk                                       (0xfU << AUDIO_ANA19CFG_VAD_TEST_SEL_O_Pos)

#define AUDIO_ANA19CFG_VAD_PU_VCOM_O_Pos                                        17
#define AUDIO_ANA19CFG_VAD_PU_VCOM_O_Msk                                        (0x1U << AUDIO_ANA19CFG_VAD_PU_VCOM_O_Pos)

#define AUDIO_ANA19CFG_VAD_PU_BST_O_Pos                                         16
#define AUDIO_ANA19CFG_VAD_PU_BST_O_Msk                                         (0x1U << AUDIO_ANA19CFG_VAD_PU_BST_O_Pos)

#define AUDIO_ANA19CFG_VAD_MUTE_O_Pos                                           15
#define AUDIO_ANA19CFG_VAD_MUTE_O_Msk                                           (0x1U << AUDIO_ANA19CFG_VAD_MUTE_O_Pos)

#define AUDIO_ANA19CFG_VAD_GAIN_SEL_O_Pos                                       13
#define AUDIO_ANA19CFG_VAD_GAIN_SEL_O_Msk                                       (0x3U << AUDIO_ANA19CFG_VAD_GAIN_SEL_O_Pos)

#define AUDIO_ANA19CFG_VAD_EN_DIFF_O_Pos                                        12
#define AUDIO_ANA19CFG_VAD_EN_DIFF_O_Msk                                        (0x1U << AUDIO_ANA19CFG_VAD_EN_DIFF_O_Pos)

#define AUDIO_ANA19CFG_CURRENT_SEL_CH2_O_Pos                                    10
#define AUDIO_ANA19CFG_CURRENT_SEL_CH2_O_Msk                                    (0x3U << AUDIO_ANA19CFG_CURRENT_SEL_CH2_O_Pos)

#define AUDIO_ANA19CFG_CURRENT_SEL_CH1_O_Pos                                    8
#define AUDIO_ANA19CFG_CURRENT_SEL_CH1_O_Msk                                    (0x3U << AUDIO_ANA19CFG_CURRENT_SEL_CH1_O_Pos)

#define AUDIO_ANA19CFG_PU_VCOM_O_Pos                                            7
#define AUDIO_ANA19CFG_PU_VCOM_O_Msk                                            (0x1U << AUDIO_ANA19CFG_PU_VCOM_O_Pos)

#define AUDIO_ANA19CFG_LDO_AVDD12_AUDIO_TRIM_O_Pos                              4
#define AUDIO_ANA19CFG_LDO_AVDD12_AUDIO_TRIM_O_Msk                              (0x7U << AUDIO_ANA19CFG_LDO_AVDD12_AUDIO_TRIM_O_Pos)

#define AUDIO_ANA19CFG_XVON_AVDD12_AUDIO_O_Pos                                  3
#define AUDIO_ANA19CFG_XVON_AVDD12_AUDIO_O_Msk                                  (0x1U << AUDIO_ANA19CFG_XVON_AVDD12_AUDIO_O_Pos)

#define AUDIO_ANA19CFG_EN_AUDIO_O_Pos                                           2
#define AUDIO_ANA19CFG_EN_AUDIO_O_Msk                                           (0x1U << AUDIO_ANA19CFG_EN_AUDIO_O_Pos)

#define AUDIO_ANA19CFG_AUDIO_TEST_I_Pos                                         1
#define AUDIO_ANA19CFG_AUDIO_TEST_I_Msk                                         (0x1U << AUDIO_ANA19CFG_AUDIO_TEST_I_Pos)

#define AUDIO_ANA19CFG_PORB_AVDD12_AUDIO_I_Pos                                  0
#define AUDIO_ANA19CFG_PORB_AVDD12_AUDIO_I_Msk                                  (0x1U << AUDIO_ANA19CFG_PORB_AVDD12_AUDIO_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ANA20CFG
//
#define AUDIO_ANA20CFG_RSV80_Pos                                                3
#define AUDIO_ANA20CFG_RSV80_Msk                                                (0x1U << AUDIO_ANA20CFG_RSV80_Pos)

#define AUDIO_ANA20CFG_RSV81_Pos                                                2
#define AUDIO_ANA20CFG_RSV81_Msk                                                (0x1U << AUDIO_ANA20CFG_RSV81_Pos)

#define AUDIO_ANA20CFG_RSV82_Pos                                                0
#define AUDIO_ANA20CFG_RSV82_Msk                                                (0x3U << AUDIO_ANA20CFG_RSV82_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLKSWI_CFG
//
#define AUDIO_CLKSWI_CFG_CH2_RD_CLK_SEL_O_Pos                                   7
#define AUDIO_CLKSWI_CFG_CH2_RD_CLK_SEL_O_Msk                                   (0x3U << AUDIO_CLKSWI_CFG_CH2_RD_CLK_SEL_O_Pos)

#define AUDIO_CLKSWI_CFG_CH1_RD_CLK_SEL_O_Pos                                   5
#define AUDIO_CLKSWI_CFG_CH1_RD_CLK_SEL_O_Msk                                   (0x3U << AUDIO_CLKSWI_CFG_CH1_RD_CLK_SEL_O_Pos)

#define AUDIO_CLKSWI_CFG_CH0_RD_CLK_SEL_O_Pos                                   3
#define AUDIO_CLKSWI_CFG_CH0_RD_CLK_SEL_O_Msk                                   (0x3U << AUDIO_CLKSWI_CFG_CH0_RD_CLK_SEL_O_Pos)

#define AUDIO_CLKSWI_CFG_CH2_RD_CLK_SWIACK_SYNC_I_Pos                           2
#define AUDIO_CLKSWI_CFG_CH2_RD_CLK_SWIACK_SYNC_I_Msk                           (0x1U << AUDIO_CLKSWI_CFG_CH2_RD_CLK_SWIACK_SYNC_I_Pos)

#define AUDIO_CLKSWI_CFG_CH1_RD_CLK_SWIACK_SYNC_I_Pos                           1
#define AUDIO_CLKSWI_CFG_CH1_RD_CLK_SWIACK_SYNC_I_Msk                           (0x1U << AUDIO_CLKSWI_CFG_CH1_RD_CLK_SWIACK_SYNC_I_Pos)

#define AUDIO_CLKSWI_CFG_CH0_RD_CLK_SWIACK_SYNC_I_Pos                           0
#define AUDIO_CLKSWI_CFG_CH0_RD_CLK_SWIACK_SYNC_I_Msk                           (0x1U << AUDIO_CLKSWI_CFG_CH0_RD_CLK_SWIACK_SYNC_I_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// AUDIO_DMA_CFG
//
#define AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_LEVEL_O_Pos                             11
#define AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_LEVEL_O_Msk                             (0xfU << AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_LEVEL_O_Pos)

#define AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_LEVEL_O_Pos                             7
#define AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_LEVEL_O_Msk                             (0xfU << AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_LEVEL_O_Pos)

#define AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_LEVEL_O_Pos                             3
#define AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_LEVEL_O_Msk                             (0xfU << AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_LEVEL_O_Pos)

#define AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_EN_O_Pos                                2
#define AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_EN_O_Msk                                (0x1U << AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_EN_O_Pos)

#define AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_EN_O_Pos                                1
#define AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_EN_O_Msk                                (0x1U << AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_EN_O_Pos)

#define AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_EN_O_Pos                                0
#define AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_EN_O_Msk                                (0x1U << AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_EN_O_Pos)

#endif //__WTM2101_AUDIO_REGISTER_H_INCLUDED__