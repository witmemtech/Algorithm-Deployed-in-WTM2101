/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 FBANK register.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Sat Aug 21 12:46:34 2021/////////////


#ifndef __WTM2101_FBANK_REGISTER_H_INCLUDED__
#define __WTM2101_FBANK_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// FBANK_EN
//
#define FBANK_FBANK_EN_FBANK_EN_Pos                                             0
#define FBANK_FBANK_EN_FBANK_EN_Msk                                             (0x1U << FBANK_FBANK_EN_FBANK_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FBANK_CONTROL
//
#define FBANK_FBANK_CONTROL_DO_RFFT_HCLK_Pos                                    15
#define FBANK_FBANK_CONTROL_DO_RFFT_HCLK_Msk                                    (0x1U << FBANK_FBANK_CONTROL_DO_RFFT_HCLK_Pos)

#define FBANK_FBANK_CONTROL_DO_CFFT_HCLK_Pos                                    14
#define FBANK_FBANK_CONTROL_DO_CFFT_HCLK_Msk                                    (0x1U << FBANK_FBANK_CONTROL_DO_CFFT_HCLK_Pos)

#define FBANK_FBANK_CONTROL_DO_BITREVERSE_Pos                                   13
#define FBANK_FBANK_CONTROL_DO_BITREVERSE_Msk                                   (0x1U << FBANK_FBANK_CONTROL_DO_BITREVERSE_Pos)

#define FBANK_FBANK_CONTROL_DO_WINDOW_Pos                                       12
#define FBANK_FBANK_CONTROL_DO_WINDOW_Msk                                       (0x1U << FBANK_FBANK_CONTROL_DO_WINDOW_Pos)

#define FBANK_FBANK_CONTROL_FRAME_LEN_Pos                                       8
#define FBANK_FBANK_CONTROL_FRAME_LEN_Msk                                       (0x3U << FBANK_FBANK_CONTROL_FRAME_LEN_Pos)

#define FBANK_FBANK_CONTROL_LOG_ENABLE_Pos                                      7
#define FBANK_FBANK_CONTROL_LOG_ENABLE_Msk                                      (0x1U << FBANK_FBANK_CONTROL_LOG_ENABLE_Pos)

#define FBANK_FBANK_CONTROL_SQRT_ENABLE_Pos                                     6
#define FBANK_FBANK_CONTROL_SQRT_ENABLE_Msk                                     (0x1U << FBANK_FBANK_CONTROL_SQRT_ENABLE_Pos)

#define FBANK_FBANK_CONTROL_MELFILTER_ENABLE_Pos                                5
#define FBANK_FBANK_CONTROL_MELFILTER_ENABLE_Msk                                (0x1U << FBANK_FBANK_CONTROL_MELFILTER_ENABLE_Pos)

#define FBANK_FBANK_CONTROL_IFFT_ENABLE_Pos                                     4
#define FBANK_FBANK_CONTROL_IFFT_ENABLE_Msk                                     (0x1U << FBANK_FBANK_CONTROL_IFFT_ENABLE_Pos)

#define FBANK_FBANK_CONTROL_FFT_ENABLE_Pos                                      3
#define FBANK_FBANK_CONTROL_FFT_ENABLE_Msk                                      (0x1U << FBANK_FBANK_CONTROL_FFT_ENABLE_Pos)

#define FBANK_FBANK_CONTROL_FBANK_SRC_SEL_Pos                                   2
#define FBANK_FBANK_CONTROL_FBANK_SRC_SEL_Msk                                   (0x1U << FBANK_FBANK_CONTROL_FBANK_SRC_SEL_Pos)

#define FBANK_FBANK_CONTROL_SRAM_ADDR_SEL_Pos                                   1
#define FBANK_FBANK_CONTROL_SRAM_ADDR_SEL_Msk                                   (0x1U << FBANK_FBANK_CONTROL_SRAM_ADDR_SEL_Pos)

#define FBANK_FBANK_CONTROL_FBANK_DATA_RAM_SEL_Pos                              0
#define FBANK_FBANK_CONTROL_FBANK_DATA_RAM_SEL_Msk                              (0x1U << FBANK_FBANK_CONTROL_FBANK_DATA_RAM_SEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DEBUG_REGISTER
//
#define FBANK_DEBUG_REGISTER_DEBUG_ENABLE_WINDOW_Pos                            5
#define FBANK_DEBUG_REGISTER_DEBUG_ENABLE_WINDOW_Msk                            (0x1U << FBANK_DEBUG_REGISTER_DEBUG_ENABLE_WINDOW_Pos)

#define FBANK_DEBUG_REGISTER_DEBUG_ENABLE_Pos                                   4
#define FBANK_DEBUG_REGISTER_DEBUG_ENABLE_Msk                                   (0x1U << FBANK_DEBUG_REGISTER_DEBUG_ENABLE_Pos)

#define FBANK_DEBUG_REGISTER_DEBUG_MAX_STAGES_Pos                               0
#define FBANK_DEBUG_REGISTER_DEBUG_MAX_STAGES_Msk                               (0xfU << FBANK_DEBUG_REGISTER_DEBUG_MAX_STAGES_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK
//
#define FBANK_INT_MASK_LOG_DONE_MASK_Pos                                        5
#define FBANK_INT_MASK_LOG_DONE_MASK_Msk                                        (0x1U << FBANK_INT_MASK_LOG_DONE_MASK_Pos)

#define FBANK_INT_MASK_SQRT_DONE_MASK_Pos                                       4
#define FBANK_INT_MASK_SQRT_DONE_MASK_Msk                                       (0x1U << FBANK_INT_MASK_SQRT_DONE_MASK_Pos)

#define FBANK_INT_MASK_MELFILTER_DONE_MASK_Pos                                  3
#define FBANK_INT_MASK_MELFILTER_DONE_MASK_Msk                                  (0x1U << FBANK_INT_MASK_MELFILTER_DONE_MASK_Pos)

#define FBANK_INT_MASK_IFFT_DONE_MASK_Pos                                       2
#define FBANK_INT_MASK_IFFT_DONE_MASK_Msk                                       (0x1U << FBANK_INT_MASK_IFFT_DONE_MASK_Pos)

#define FBANK_INT_MASK_FFT_DONE_MASK_Pos                                        1
#define FBANK_INT_MASK_FFT_DONE_MASK_Msk                                        (0x1U << FBANK_INT_MASK_FFT_DONE_MASK_Pos)

#define FBANK_INT_MASK_FBANK_DONE_MASK_Pos                                      0
#define FBANK_INT_MASK_FBANK_DONE_MASK_Msk                                      (0x1U << FBANK_INT_MASK_FBANK_DONE_MASK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_SOURCE
//
#define FBANK_INT_SOURCE_LOG_DONE_PENDING_Pos                                   5
#define FBANK_INT_SOURCE_LOG_DONE_PENDING_Msk                                   (0x1U << FBANK_INT_SOURCE_LOG_DONE_PENDING_Pos)

#define FBANK_INT_SOURCE_SQRT_DONE_PENDING_Pos                                  4
#define FBANK_INT_SOURCE_SQRT_DONE_PENDING_Msk                                  (0x1U << FBANK_INT_SOURCE_SQRT_DONE_PENDING_Pos)

#define FBANK_INT_SOURCE_MELFILTER_DONE_PENDING_Pos                             3
#define FBANK_INT_SOURCE_MELFILTER_DONE_PENDING_Msk                             (0x1U << FBANK_INT_SOURCE_MELFILTER_DONE_PENDING_Pos)

#define FBANK_INT_SOURCE_IFFT_DONE_PENDING_Pos                                  2
#define FBANK_INT_SOURCE_IFFT_DONE_PENDING_Msk                                  (0x1U << FBANK_INT_SOURCE_IFFT_DONE_PENDING_Pos)

#define FBANK_INT_SOURCE_FFT_DONE_PENDING_Pos                                   1
#define FBANK_INT_SOURCE_FFT_DONE_PENDING_Msk                                   (0x1U << FBANK_INT_SOURCE_FFT_DONE_PENDING_Pos)

#define FBANK_INT_SOURCE_FBANK_DONE_PENDING_Pos                                 0
#define FBANK_INT_SOURCE_FBANK_DONE_PENDING_Msk                                 (0x1U << FBANK_INT_SOURCE_FBANK_DONE_PENDING_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FBANK_STATUS
//
#define FBANK_FBANK_STATUS_FBANK_READ_AUDIO_PENDING_Pos                         0
#define FBANK_FBANK_STATUS_FBANK_READ_AUDIO_PENDING_Msk                         (0x1U << FBANK_FBANK_STATUS_FBANK_READ_AUDIO_PENDING_Pos)

#endif //__WTM2101_FBANK_REGISTER_H_INCLUDED__