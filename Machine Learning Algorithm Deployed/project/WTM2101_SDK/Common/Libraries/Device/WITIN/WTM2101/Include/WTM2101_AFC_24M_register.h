/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 AFC 24M register.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Sat Aug 21 12:46:34 2021/////////////


#ifndef __WTM2101_AFC_24M_REGISTER_H_INCLUDED__
#define __WTM2101_AFC_24M_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// CORE_CTRL
//
#define AFC_24M_CORE_CTRL_FRE_TARGET_Pos                                        8
#define AFC_24M_CORE_CTRL_FRE_TARGET_Msk                                        (0x7fffU << AFC_24M_CORE_CTRL_FRE_TARGET_Pos)

#define AFC_24M_CORE_CTRL_TEST_TIME_Pos                                         0
#define AFC_24M_CORE_CTRL_TEST_TIME_Msk                                         (0xffU << AFC_24M_CORE_CTRL_TEST_TIME_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CORE_EN
//
#define AFC_24M_CORE_EN_WORK_EN_Pos                                             0
#define AFC_24M_CORE_EN_WORK_EN_Msk                                             (0x1U << AFC_24M_CORE_EN_WORK_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// OP_RESULT
//
#define AFC_24M_OP_RESULT_REMAIN_VALUE_Pos                                      5
#define AFC_24M_OP_RESULT_REMAIN_VALUE_Msk                                      (0x1U << AFC_24M_OP_RESULT_REMAIN_VALUE_Pos)

#define AFC_24M_OP_RESULT_INT_VALUE_Pos                                         0
#define AFC_24M_OP_RESULT_INT_VALUE_Msk                                         (0x1fU << AFC_24M_OP_RESULT_INT_VALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// AFC_24M_FRE_CNT
//
#define AFC_24M_AFC_24M_FRE_CNT_FRE_CNT_Pos                                     0
#define AFC_24M_AFC_24M_FRE_CNT_FRE_CNT_Msk                                     (0x7fffU << AFC_24M_AFC_24M_FRE_CNT_FRE_CNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CORE_TRIM_SIGNAL
//
#define AFC_24M_CORE_TRIM_SIGNAL_AFC_TRIM_RST_Pos                               12
#define AFC_24M_CORE_TRIM_SIGNAL_AFC_TRIM_RST_Msk                               (0x1U << AFC_24M_CORE_TRIM_SIGNAL_AFC_TRIM_RST_Pos)

#define AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_COARSE_Pos                           8
#define AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_COARSE_Msk                           (0xfU << AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_COARSE_Pos)

#define AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_FINE_Pos                             0
#define AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_FINE_Msk                             (0x1fU << AFC_24M_CORE_TRIM_SIGNAL_CORE_TRIM_FINE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// OP_DATA
//
#define AFC_24M_OP_DATA_FINE_TRIM_SIGN_COMP_Pos                                 31
#define AFC_24M_OP_DATA_FINE_TRIM_SIGN_COMP_Msk                                 (0x1U << AFC_24M_OP_DATA_FINE_TRIM_SIGN_COMP_Pos)

#define AFC_24M_OP_DATA_FRE_CNT_SUB_TEMP_Pos                                    16
#define AFC_24M_OP_DATA_FRE_CNT_SUB_TEMP_Msk                                    (0x7fffU << AFC_24M_OP_DATA_FRE_CNT_SUB_TEMP_Pos)

#define AFC_24M_OP_DATA_FRE_CNT_SUB_Pos                                         0
#define AFC_24M_OP_DATA_FRE_CNT_SUB_Msk                                         (0x7fffU << AFC_24M_OP_DATA_FRE_CNT_SUB_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// AFC_PULSE
//
#define AFC_24M_AFC_PULSE_OP_PULSE_Pos                                          0
#define AFC_24M_AFC_PULSE_OP_PULSE_Msk                                          (0x1U << AFC_24M_AFC_PULSE_OP_PULSE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK_SET
//
#define AFC_24M_INT_MASK_SET_INT_TRIM_ACK_MASK_SET_Pos                          11
#define AFC_24M_INT_MASK_SET_INT_TRIM_ACK_MASK_SET_Msk                          (0x1U << AFC_24M_INT_MASK_SET_INT_TRIM_ACK_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_FRE_DET_DONE_MASK_SET_Pos                      10
#define AFC_24M_INT_MASK_SET_INT_FRE_DET_DONE_MASK_SET_Msk                      (0x1U << AFC_24M_INT_MASK_SET_INT_FRE_DET_DONE_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_FINE_STEP0_OP_MASK_SET_Pos                     9
#define AFC_24M_INT_MASK_SET_INT_FINE_STEP0_OP_MASK_SET_Msk                     (0x1U << AFC_24M_INT_MASK_SET_INT_FINE_STEP0_OP_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_FINE_STEP1_OP_MASK_SET_Pos                     8
#define AFC_24M_INT_MASK_SET_INT_FINE_STEP1_OP_MASK_SET_Msk                     (0x1U << AFC_24M_INT_MASK_SET_INT_FINE_STEP1_OP_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_COARSE_OVER_MASK_SET_Pos                       7
#define AFC_24M_INT_MASK_SET_INT_COARSE_OVER_MASK_SET_Msk                       (0x1U << AFC_24M_INT_MASK_SET_INT_COARSE_OVER_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_COARSE_DEC_MASK_SET_Pos                        6
#define AFC_24M_INT_MASK_SET_INT_COARSE_DEC_MASK_SET_Msk                        (0x1U << AFC_24M_INT_MASK_SET_INT_COARSE_DEC_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_COARSE_INC_MASK_SET_Pos                        5
#define AFC_24M_INT_MASK_SET_INT_COARSE_INC_MASK_SET_Msk                        (0x1U << AFC_24M_INT_MASK_SET_INT_COARSE_INC_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_CALB_FINISH_MASK_SET_Pos                       4
#define AFC_24M_INT_MASK_SET_INT_CALB_FINISH_MASK_SET_Msk                       (0x1U << AFC_24M_INT_MASK_SET_INT_CALB_FINISH_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_FINE_ERROR_MASK_SET_Pos                        3
#define AFC_24M_INT_MASK_SET_INT_FINE_ERROR_MASK_SET_Msk                        (0x1U << AFC_24M_INT_MASK_SET_INT_FINE_ERROR_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_FINE_STEP0_DONE_MASK_SET_Pos                   2
#define AFC_24M_INT_MASK_SET_INT_FINE_STEP0_DONE_MASK_SET_Msk                   (0x1U << AFC_24M_INT_MASK_SET_INT_FINE_STEP0_DONE_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_FINE_STEP1_DONE_MASK_SET_Pos                   1
#define AFC_24M_INT_MASK_SET_INT_FINE_STEP1_DONE_MASK_SET_Msk                   (0x1U << AFC_24M_INT_MASK_SET_INT_FINE_STEP1_DONE_MASK_SET_Pos)

#define AFC_24M_INT_MASK_SET_INT_FINE_STEP2_DONE_MASK_SET_Pos                   0
#define AFC_24M_INT_MASK_SET_INT_FINE_STEP2_DONE_MASK_SET_Msk                   (0x1U << AFC_24M_INT_MASK_SET_INT_FINE_STEP2_DONE_MASK_SET_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK_CLR
//
#define AFC_24M_INT_MASK_CLR_INT_TRIM_ACK_MASK_CLR_Pos                          11
#define AFC_24M_INT_MASK_CLR_INT_TRIM_ACK_MASK_CLR_Msk                          (0x1U << AFC_24M_INT_MASK_CLR_INT_TRIM_ACK_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_FRE_DET_DONE_MASK_CLR_Pos                      10
#define AFC_24M_INT_MASK_CLR_INT_FRE_DET_DONE_MASK_CLR_Msk                      (0x1U << AFC_24M_INT_MASK_CLR_INT_FRE_DET_DONE_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP0_OP_MASK_CLR_Pos                     9
#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP0_OP_MASK_CLR_Msk                     (0x1U << AFC_24M_INT_MASK_CLR_INT_FINE_STEP0_OP_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP1_OP_MASK_CLR_Pos                     8
#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP1_OP_MASK_CLR_Msk                     (0x1U << AFC_24M_INT_MASK_CLR_INT_FINE_STEP1_OP_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_COARSE_OVER_MASK_CLR_Pos                       7
#define AFC_24M_INT_MASK_CLR_INT_COARSE_OVER_MASK_CLR_Msk                       (0x1U << AFC_24M_INT_MASK_CLR_INT_COARSE_OVER_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_COARSE_DEC_MASK_CLR_Pos                        6
#define AFC_24M_INT_MASK_CLR_INT_COARSE_DEC_MASK_CLR_Msk                        (0x1U << AFC_24M_INT_MASK_CLR_INT_COARSE_DEC_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_COARSE_INC_MASK_CLR_Pos                        5
#define AFC_24M_INT_MASK_CLR_INT_COARSE_INC_MASK_CLR_Msk                        (0x1U << AFC_24M_INT_MASK_CLR_INT_COARSE_INC_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_CALB_FINISH_MASK_CLR_Pos                       4
#define AFC_24M_INT_MASK_CLR_INT_CALB_FINISH_MASK_CLR_Msk                       (0x1U << AFC_24M_INT_MASK_CLR_INT_CALB_FINISH_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_FINE_ERROR_MASK_CLR_Pos                        3
#define AFC_24M_INT_MASK_CLR_INT_FINE_ERROR_MASK_CLR_Msk                        (0x1U << AFC_24M_INT_MASK_CLR_INT_FINE_ERROR_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP0_DONE_MASK_CLR_Pos                   2
#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP0_DONE_MASK_CLR_Msk                   (0x1U << AFC_24M_INT_MASK_CLR_INT_FINE_STEP0_DONE_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP1_DONE_MASK_CLR_Pos                   1
#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP1_DONE_MASK_CLR_Msk                   (0x1U << AFC_24M_INT_MASK_CLR_INT_FINE_STEP1_DONE_MASK_CLR_Pos)

#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP2_DONE_MASK_CLR_Pos                   0
#define AFC_24M_INT_MASK_CLR_INT_FINE_STEP2_DONE_MASK_CLR_Msk                   (0x1U << AFC_24M_INT_MASK_CLR_INT_FINE_STEP2_DONE_MASK_CLR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK_STATUS
//
#define AFC_24M_INT_MASK_STATUS_INT_TRIM_ACK_MASK_STATUS_Pos                    11
#define AFC_24M_INT_MASK_STATUS_INT_TRIM_ACK_MASK_STATUS_Msk                    (0x1U << AFC_24M_INT_MASK_STATUS_INT_TRIM_ACK_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_FRE_DET_DONE_MASK_STATUS_Pos                10
#define AFC_24M_INT_MASK_STATUS_INT_FRE_DET_DONE_MASK_STATUS_Msk                (0x1U << AFC_24M_INT_MASK_STATUS_INT_FRE_DET_DONE_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP0_OP_MASK_STATUS_Pos               9
#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP0_OP_MASK_STATUS_Msk               (0x1U << AFC_24M_INT_MASK_STATUS_INT_FINE_STEP0_OP_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP1_OP_MASK_STATUS_Pos               8
#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP1_OP_MASK_STATUS_Msk               (0x1U << AFC_24M_INT_MASK_STATUS_INT_FINE_STEP1_OP_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_COARSE_OVER_MASK_STATUS_Pos                 7
#define AFC_24M_INT_MASK_STATUS_INT_COARSE_OVER_MASK_STATUS_Msk                 (0x1U << AFC_24M_INT_MASK_STATUS_INT_COARSE_OVER_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_COARSE_DEC_MASK_STATUS_Pos                  6
#define AFC_24M_INT_MASK_STATUS_INT_COARSE_DEC_MASK_STATUS_Msk                  (0x1U << AFC_24M_INT_MASK_STATUS_INT_COARSE_DEC_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_COARSE_INC_MASK_STATUS_Pos                  5
#define AFC_24M_INT_MASK_STATUS_INT_COARSE_INC_MASK_STATUS_Msk                  (0x1U << AFC_24M_INT_MASK_STATUS_INT_COARSE_INC_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_CALB_FINISH_MASK_STATUS_Pos                 4
#define AFC_24M_INT_MASK_STATUS_INT_CALB_FINISH_MASK_STATUS_Msk                 (0x1U << AFC_24M_INT_MASK_STATUS_INT_CALB_FINISH_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_FINE_ERROR_MASK_STATUS_Pos                  3
#define AFC_24M_INT_MASK_STATUS_INT_FINE_ERROR_MASK_STATUS_Msk                  (0x1U << AFC_24M_INT_MASK_STATUS_INT_FINE_ERROR_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP0_DONE_MASK_STATUS_Pos             2
#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP0_DONE_MASK_STATUS_Msk             (0x1U << AFC_24M_INT_MASK_STATUS_INT_FINE_STEP0_DONE_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP1_DONE_MASK_STATUS_Pos             1
#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP1_DONE_MASK_STATUS_Msk             (0x1U << AFC_24M_INT_MASK_STATUS_INT_FINE_STEP1_DONE_MASK_STATUS_Pos)

#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP2_DONE_MASK_STATUS_Pos             0
#define AFC_24M_INT_MASK_STATUS_INT_FINE_STEP2_DONE_MASK_STATUS_Msk             (0x1U << AFC_24M_INT_MASK_STATUS_INT_FINE_STEP2_DONE_MASK_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_SR_PENDING
//
#define AFC_24M_INT_SR_PENDING_INT_TRIM_ACK_Pos                                 11
#define AFC_24M_INT_SR_PENDING_INT_TRIM_ACK_Msk                                 (0x1U << AFC_24M_INT_SR_PENDING_INT_TRIM_ACK_Pos)

#define AFC_24M_INT_SR_PENDING_INT_FRE_DET_DONE_Pos                             10
#define AFC_24M_INT_SR_PENDING_INT_FRE_DET_DONE_Msk                             (0x1U << AFC_24M_INT_SR_PENDING_INT_FRE_DET_DONE_Pos)

#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP0_OP_Pos                            9
#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP0_OP_Msk                            (0x1U << AFC_24M_INT_SR_PENDING_INT_FINE_STEP0_OP_Pos)

#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP1_OP_Pos                            8
#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP1_OP_Msk                            (0x1U << AFC_24M_INT_SR_PENDING_INT_FINE_STEP1_OP_Pos)

#define AFC_24M_INT_SR_PENDING_INT_COARSE_OVER_Pos                              7
#define AFC_24M_INT_SR_PENDING_INT_COARSE_OVER_Msk                              (0x1U << AFC_24M_INT_SR_PENDING_INT_COARSE_OVER_Pos)

#define AFC_24M_INT_SR_PENDING_INT_COARSE_DEC_Pos                               6
#define AFC_24M_INT_SR_PENDING_INT_COARSE_DEC_Msk                               (0x1U << AFC_24M_INT_SR_PENDING_INT_COARSE_DEC_Pos)

#define AFC_24M_INT_SR_PENDING_INT_COARSE_INC_Pos                               5
#define AFC_24M_INT_SR_PENDING_INT_COARSE_INC_Msk                               (0x1U << AFC_24M_INT_SR_PENDING_INT_COARSE_INC_Pos)

#define AFC_24M_INT_SR_PENDING_INT_CALB_FINISH_Pos                              4
#define AFC_24M_INT_SR_PENDING_INT_CALB_FINISH_Msk                              (0x1U << AFC_24M_INT_SR_PENDING_INT_CALB_FINISH_Pos)

#define AFC_24M_INT_SR_PENDING_INT_FINE_ERROR_Pos                               3
#define AFC_24M_INT_SR_PENDING_INT_FINE_ERROR_Msk                               (0x1U << AFC_24M_INT_SR_PENDING_INT_FINE_ERROR_Pos)

#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP0_DONE_Pos                          2
#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP0_DONE_Msk                          (0x1U << AFC_24M_INT_SR_PENDING_INT_FINE_STEP0_DONE_Pos)

#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP1_DONE_Pos                          1
#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP1_DONE_Msk                          (0x1U << AFC_24M_INT_SR_PENDING_INT_FINE_STEP1_DONE_Pos)

#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP2_DONE_Pos                          0
#define AFC_24M_INT_SR_PENDING_INT_FINE_STEP2_DONE_Msk                          (0x1U << AFC_24M_INT_SR_PENDING_INT_FINE_STEP2_DONE_Pos)

#endif //__WTM2101_AFC_24M_REGISTER_H_INCLUDED__