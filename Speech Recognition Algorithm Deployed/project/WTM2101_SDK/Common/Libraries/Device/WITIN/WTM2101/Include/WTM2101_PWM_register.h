/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 PWM register.
  * @date    2023-03-20
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Mon Mar 20 11:31:58 2023/////////////


#ifndef __WTM2101_PWM_REGISTER_H_INCLUDED__
#define __WTM2101_PWM_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CTL
//
#define PWM_PWM_CTL_PWM_MAX_VALUE_Pos                                           16
#define PWM_PWM_CTL_PWM_MAX_VALUE_Msk                                           (0xffffU << PWM_PWM_CTL_PWM_MAX_VALUE_Pos)

#define PWM_PWM_CTL_PWM_CNT_MODE_Pos                                            1
#define PWM_PWM_CTL_PWM_CNT_MODE_Msk                                            (0x3U << PWM_PWM_CTL_PWM_CNT_MODE_Pos)

#define PWM_PWM_CTL_PWM_CAP_SW_Pos                                              0
#define PWM_PWM_CTL_PWM_CAP_SW_Msk                                              (0x1U << PWM_PWM_CTL_PWM_CAP_SW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH_CTL
//
#define PWM_PWM_CH_CTL_PWM_3_ONE_SHOT_EN_Pos                                    28
#define PWM_PWM_CH_CTL_PWM_3_ONE_SHOT_EN_Msk                                    (0x1U << PWM_PWM_CH_CTL_PWM_3_ONE_SHOT_EN_Pos)

#define PWM_PWM_CH_CTL_PWM_O_3_SW_Pos                                           27
#define PWM_PWM_CH_CTL_PWM_O_3_SW_Msk                                           (0x1U << PWM_PWM_CH_CTL_PWM_O_3_SW_Pos)

#define PWM_PWM_CH_CTL_PWM_I_3_SW_Pos                                           26
#define PWM_PWM_CH_CTL_PWM_I_3_SW_Msk                                           (0x1U << PWM_PWM_CH_CTL_PWM_I_3_SW_Pos)

#define PWM_PWM_CH_CTL_PWM_O_3_INIT_Pos                                         25
#define PWM_PWM_CH_CTL_PWM_O_3_INIT_Msk                                         (0x1U << PWM_PWM_CH_CTL_PWM_O_3_INIT_Pos)

#define PWM_PWM_CH_CTL_PWM_3_EN_Pos                                             24
#define PWM_PWM_CH_CTL_PWM_3_EN_Msk                                             (0x1U << PWM_PWM_CH_CTL_PWM_3_EN_Pos)

#define PWM_PWM_CH_CTL_PWM_2_ONE_SHOT_EN_Pos                                    20
#define PWM_PWM_CH_CTL_PWM_2_ONE_SHOT_EN_Msk                                    (0x1U << PWM_PWM_CH_CTL_PWM_2_ONE_SHOT_EN_Pos)

#define PWM_PWM_CH_CTL_PWM_O_2_SW_Pos                                           19
#define PWM_PWM_CH_CTL_PWM_O_2_SW_Msk                                           (0x1U << PWM_PWM_CH_CTL_PWM_O_2_SW_Pos)

#define PWM_PWM_CH_CTL_PWM_I_2_SW_Pos                                           18
#define PWM_PWM_CH_CTL_PWM_I_2_SW_Msk                                           (0x1U << PWM_PWM_CH_CTL_PWM_I_2_SW_Pos)

#define PWM_PWM_CH_CTL_PWM_O_2_INIT_Pos                                         17
#define PWM_PWM_CH_CTL_PWM_O_2_INIT_Msk                                         (0x1U << PWM_PWM_CH_CTL_PWM_O_2_INIT_Pos)

#define PWM_PWM_CH_CTL_PWM_2_EN_Pos                                             16
#define PWM_PWM_CH_CTL_PWM_2_EN_Msk                                             (0x1U << PWM_PWM_CH_CTL_PWM_2_EN_Pos)

#define PWM_PWM_CH_CTL_PWM_1_ONE_SHOT_EN_Pos                                    12
#define PWM_PWM_CH_CTL_PWM_1_ONE_SHOT_EN_Msk                                    (0x1U << PWM_PWM_CH_CTL_PWM_1_ONE_SHOT_EN_Pos)

#define PWM_PWM_CH_CTL_PWM_O_1_SW_Pos                                           11
#define PWM_PWM_CH_CTL_PWM_O_1_SW_Msk                                           (0x1U << PWM_PWM_CH_CTL_PWM_O_1_SW_Pos)

#define PWM_PWM_CH_CTL_PWM_I_1_SW_Pos                                           10
#define PWM_PWM_CH_CTL_PWM_I_1_SW_Msk                                           (0x1U << PWM_PWM_CH_CTL_PWM_I_1_SW_Pos)

#define PWM_PWM_CH_CTL_PWM_O_1_INIT_Pos                                         9
#define PWM_PWM_CH_CTL_PWM_O_1_INIT_Msk                                         (0x1U << PWM_PWM_CH_CTL_PWM_O_1_INIT_Pos)

#define PWM_PWM_CH_CTL_PWM_1_EN_Pos                                             8
#define PWM_PWM_CH_CTL_PWM_1_EN_Msk                                             (0x1U << PWM_PWM_CH_CTL_PWM_1_EN_Pos)

#define PWM_PWM_CH_CTL_PWM_0_ONE_SHOT_EN_Pos                                    4
#define PWM_PWM_CH_CTL_PWM_0_ONE_SHOT_EN_Msk                                    (0x1U << PWM_PWM_CH_CTL_PWM_0_ONE_SHOT_EN_Pos)

#define PWM_PWM_CH_CTL_PWM_O_0_SW_Pos                                           3
#define PWM_PWM_CH_CTL_PWM_O_0_SW_Msk                                           (0x1U << PWM_PWM_CH_CTL_PWM_O_0_SW_Pos)

#define PWM_PWM_CH_CTL_PWM_I_0_SW_Pos                                           2
#define PWM_PWM_CH_CTL_PWM_I_0_SW_Msk                                           (0x1U << PWM_PWM_CH_CTL_PWM_I_0_SW_Pos)

#define PWM_PWM_CH_CTL_PWM_O_0_INIT_Pos                                         1
#define PWM_PWM_CH_CTL_PWM_O_0_INIT_Msk                                         (0x1U << PWM_PWM_CH_CTL_PWM_O_0_INIT_Pos)

#define PWM_PWM_CH_CTL_PWM_0_EN_Pos                                             0
#define PWM_PWM_CH_CTL_PWM_0_EN_Msk                                             (0x1U << PWM_PWM_CH_CTL_PWM_0_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH0_INI
//
#define PWM_PWM_CH0_INI_PWM_0_DEAD_ZONE_VALUE_Pos                               16
#define PWM_PWM_CH0_INI_PWM_0_DEAD_ZONE_VALUE_Msk                               (0xffffU << PWM_PWM_CH0_INI_PWM_0_DEAD_ZONE_VALUE_Pos)

#define PWM_PWM_CH0_INI_PWM_0_COMP_VALUE_Pos                                    0
#define PWM_PWM_CH0_INI_PWM_0_COMP_VALUE_Msk                                    (0xffffU << PWM_PWM_CH0_INI_PWM_0_COMP_VALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH1_INI
//
#define PWM_PWM_CH1_INI_PWM_1_DEAD_ZONE_VALUE_Pos                               16
#define PWM_PWM_CH1_INI_PWM_1_DEAD_ZONE_VALUE_Msk                               (0xffffU << PWM_PWM_CH1_INI_PWM_1_DEAD_ZONE_VALUE_Pos)

#define PWM_PWM_CH1_INI_PWM_1_COMP_VALUE_Pos                                    0
#define PWM_PWM_CH1_INI_PWM_1_COMP_VALUE_Msk                                    (0xffffU << PWM_PWM_CH1_INI_PWM_1_COMP_VALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH2_INI
//
#define PWM_PWM_CH2_INI_PWM_2_DEAD_ZONE_VALUE_Pos                               16
#define PWM_PWM_CH2_INI_PWM_2_DEAD_ZONE_VALUE_Msk                               (0xffffU << PWM_PWM_CH2_INI_PWM_2_DEAD_ZONE_VALUE_Pos)

#define PWM_PWM_CH2_INI_PWM_2_COMP_VALUE_Pos                                    0
#define PWM_PWM_CH2_INI_PWM_2_COMP_VALUE_Msk                                    (0xffffU << PWM_PWM_CH2_INI_PWM_2_COMP_VALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH3_INI
//
#define PWM_PWM_CH3_INI_PWM_3_DEAD_ZONE_VALUE_Pos                               16
#define PWM_PWM_CH3_INI_PWM_3_DEAD_ZONE_VALUE_Msk                               (0xffffU << PWM_PWM_CH3_INI_PWM_3_DEAD_ZONE_VALUE_Pos)

#define PWM_PWM_CH3_INI_PWM_3_COMP_VALUE_Pos                                    0
#define PWM_PWM_CH3_INI_PWM_3_COMP_VALUE_Msk                                    (0xffffU << PWM_PWM_CH3_INI_PWM_3_COMP_VALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH0_RB_VAL
//
#define PWM_PWM_CH0_RB_VAL_PWM_I_0_CYCLE_Pos                                    16
#define PWM_PWM_CH0_RB_VAL_PWM_I_0_CYCLE_Msk                                    (0xffffU << PWM_PWM_CH0_RB_VAL_PWM_I_0_CYCLE_Pos)

#define PWM_PWM_CH0_RB_VAL_PWM_I_0_H_WIDTH_Pos                                  0
#define PWM_PWM_CH0_RB_VAL_PWM_I_0_H_WIDTH_Msk                                  (0xffffU << PWM_PWM_CH0_RB_VAL_PWM_I_0_H_WIDTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH1_RB_VAL
//
#define PWM_PWM_CH1_RB_VAL_PWM_I_1_CYCLE_Pos                                    16
#define PWM_PWM_CH1_RB_VAL_PWM_I_1_CYCLE_Msk                                    (0xffffU << PWM_PWM_CH1_RB_VAL_PWM_I_1_CYCLE_Pos)

#define PWM_PWM_CH1_RB_VAL_PWM_I_1_H_WIDTH_Pos                                  0
#define PWM_PWM_CH1_RB_VAL_PWM_I_1_H_WIDTH_Msk                                  (0xffffU << PWM_PWM_CH1_RB_VAL_PWM_I_1_H_WIDTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH2_RB_VAL
//
#define PWM_PWM_CH2_RB_VAL_PWM_I_2_CYCLE_Pos                                    16
#define PWM_PWM_CH2_RB_VAL_PWM_I_2_CYCLE_Msk                                    (0xffffU << PWM_PWM_CH2_RB_VAL_PWM_I_2_CYCLE_Pos)

#define PWM_PWM_CH2_RB_VAL_PWM_I_2_H_WIDTH_Pos                                  0
#define PWM_PWM_CH2_RB_VAL_PWM_I_2_H_WIDTH_Msk                                  (0xffffU << PWM_PWM_CH2_RB_VAL_PWM_I_2_H_WIDTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_CH3_RB_VAL
//
#define PWM_PWM_CH3_RB_VAL_PWM_I_3_CYCLE_Pos                                    16
#define PWM_PWM_CH3_RB_VAL_PWM_I_3_CYCLE_Msk                                    (0xffffU << PWM_PWM_CH3_RB_VAL_PWM_I_3_CYCLE_Pos)

#define PWM_PWM_CH3_RB_VAL_PWM_I_3_H_WIDTH_Pos                                  0
#define PWM_PWM_CH3_RB_VAL_PWM_I_3_H_WIDTH_Msk                                  (0xffffU << PWM_PWM_CH3_RB_VAL_PWM_I_3_H_WIDTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PWM_PUL
//
#define PWM_PWM_PUL_PWM_3_BKIN_RELEASE_Pos                                      13
#define PWM_PWM_PUL_PWM_3_BKIN_RELEASE_Msk                                      (0x1U << PWM_PWM_PUL_PWM_3_BKIN_RELEASE_Pos)

#define PWM_PWM_PUL_PWM_O_3_INIT_PULSE_Pos                                      12
#define PWM_PWM_PUL_PWM_O_3_INIT_PULSE_Msk                                      (0x1U << PWM_PWM_PUL_PWM_O_3_INIT_PULSE_Pos)

#define PWM_PWM_PUL_PWM_2_BKIN_RELEASE_Pos                                      9
#define PWM_PWM_PUL_PWM_2_BKIN_RELEASE_Msk                                      (0x1U << PWM_PWM_PUL_PWM_2_BKIN_RELEASE_Pos)

#define PWM_PWM_PUL_PWM_O_2_INIT_PULSE_Pos                                      8
#define PWM_PWM_PUL_PWM_O_2_INIT_PULSE_Msk                                      (0x1U << PWM_PWM_PUL_PWM_O_2_INIT_PULSE_Pos)

#define PWM_PWM_PUL_PWM_1_BKIN_RELEASE_Pos                                      5
#define PWM_PWM_PUL_PWM_1_BKIN_RELEASE_Msk                                      (0x1U << PWM_PWM_PUL_PWM_1_BKIN_RELEASE_Pos)

#define PWM_PWM_PUL_PWM_O_1_INIT_PULSE_Pos                                      4
#define PWM_PWM_PUL_PWM_O_1_INIT_PULSE_Msk                                      (0x1U << PWM_PWM_PUL_PWM_O_1_INIT_PULSE_Pos)

#define PWM_PWM_PUL_PWM_0_BKIN_RELEASE_Pos                                      1
#define PWM_PWM_PUL_PWM_0_BKIN_RELEASE_Msk                                      (0x1U << PWM_PWM_PUL_PWM_0_BKIN_RELEASE_Pos)

#define PWM_PWM_PUL_PWM_O_0_INIT_PULSE_Pos                                      0
#define PWM_PWM_PUL_PWM_O_0_INIT_PULSE_Msk                                      (0x1U << PWM_PWM_PUL_PWM_O_0_INIT_PULSE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK_SET
//
#define PWM_INT_MASK_SET_PWM_OVERFLOW_MASK_SET_Pos                              13
#define PWM_INT_MASK_SET_PWM_OVERFLOW_MASK_SET_Msk                              (0x1U << PWM_INT_MASK_SET_PWM_OVERFLOW_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_UNDERFLOW_MASK_SET_Pos                             12
#define PWM_INT_MASK_SET_PWM_UNDERFLOW_MASK_SET_Msk                             (0x1U << PWM_INT_MASK_SET_PWM_UNDERFLOW_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_3_BKIN_MASK_SET_Pos                                11
#define PWM_INT_MASK_SET_PWM_3_BKIN_MASK_SET_Msk                                (0x1U << PWM_INT_MASK_SET_PWM_3_BKIN_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_I_3_CYCLE_MASK_SET_Pos                             10
#define PWM_INT_MASK_SET_PWM_I_3_CYCLE_MASK_SET_Msk                             (0x1U << PWM_INT_MASK_SET_PWM_I_3_CYCLE_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_I_3_H_MASK_SET_Pos                                 9
#define PWM_INT_MASK_SET_PWM_I_3_H_MASK_SET_Msk                                 (0x1U << PWM_INT_MASK_SET_PWM_I_3_H_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_2_BKIN_MASK_SET_Pos                                8
#define PWM_INT_MASK_SET_PWM_2_BKIN_MASK_SET_Msk                                (0x1U << PWM_INT_MASK_SET_PWM_2_BKIN_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_I_2_CYCLE_MASK_SET_Pos                             7
#define PWM_INT_MASK_SET_PWM_I_2_CYCLE_MASK_SET_Msk                             (0x1U << PWM_INT_MASK_SET_PWM_I_2_CYCLE_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_I_2_H_MASK_SET_Pos                                 6
#define PWM_INT_MASK_SET_PWM_I_2_H_MASK_SET_Msk                                 (0x1U << PWM_INT_MASK_SET_PWM_I_2_H_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_1_BKIN_MASK_SET_Pos                                5
#define PWM_INT_MASK_SET_PWM_1_BKIN_MASK_SET_Msk                                (0x1U << PWM_INT_MASK_SET_PWM_1_BKIN_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_I_1_CYCLE_MASK_SET_Pos                             4
#define PWM_INT_MASK_SET_PWM_I_1_CYCLE_MASK_SET_Msk                             (0x1U << PWM_INT_MASK_SET_PWM_I_1_CYCLE_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_I_1_H_MASK_SET_Pos                                 3
#define PWM_INT_MASK_SET_PWM_I_1_H_MASK_SET_Msk                                 (0x1U << PWM_INT_MASK_SET_PWM_I_1_H_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_0_BKIN_MASK_SET_Pos                                2
#define PWM_INT_MASK_SET_PWM_0_BKIN_MASK_SET_Msk                                (0x1U << PWM_INT_MASK_SET_PWM_0_BKIN_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_I_0_CYCLE_MASK_SET_Pos                             1
#define PWM_INT_MASK_SET_PWM_I_0_CYCLE_MASK_SET_Msk                             (0x1U << PWM_INT_MASK_SET_PWM_I_0_CYCLE_MASK_SET_Pos)

#define PWM_INT_MASK_SET_PWM_I_0_H_MASK_SET_Pos                                 0
#define PWM_INT_MASK_SET_PWM_I_0_H_MASK_SET_Msk                                 (0x1U << PWM_INT_MASK_SET_PWM_I_0_H_MASK_SET_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK_CLR
//
#define PWM_INT_MASK_CLR_PWM_OVERFLOW_MASK_CLR_Pos                              13
#define PWM_INT_MASK_CLR_PWM_OVERFLOW_MASK_CLR_Msk                              (0x1U << PWM_INT_MASK_CLR_PWM_OVERFLOW_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_UNDERFLOW_MASK_CLR_Pos                             12
#define PWM_INT_MASK_CLR_PWM_UNDERFLOW_MASK_CLR_Msk                             (0x1U << PWM_INT_MASK_CLR_PWM_UNDERFLOW_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_3_BKIN_MASK_CLR_Pos                                11
#define PWM_INT_MASK_CLR_PWM_3_BKIN_MASK_CLR_Msk                                (0x1U << PWM_INT_MASK_CLR_PWM_3_BKIN_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_I_3_CYCLE_MASK_CLR_Pos                             10
#define PWM_INT_MASK_CLR_PWM_I_3_CYCLE_MASK_CLR_Msk                             (0x1U << PWM_INT_MASK_CLR_PWM_I_3_CYCLE_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_I_3_H_MASK_CLR_Pos                                 9
#define PWM_INT_MASK_CLR_PWM_I_3_H_MASK_CLR_Msk                                 (0x1U << PWM_INT_MASK_CLR_PWM_I_3_H_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_2_BKIN_MASK_CLR_Pos                                8
#define PWM_INT_MASK_CLR_PWM_2_BKIN_MASK_CLR_Msk                                (0x1U << PWM_INT_MASK_CLR_PWM_2_BKIN_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_I_2_CYCLE_MASK_CLR_Pos                             7
#define PWM_INT_MASK_CLR_PWM_I_2_CYCLE_MASK_CLR_Msk                             (0x1U << PWM_INT_MASK_CLR_PWM_I_2_CYCLE_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_I_2_H_MASK_CLR_Pos                                 6
#define PWM_INT_MASK_CLR_PWM_I_2_H_MASK_CLR_Msk                                 (0x1U << PWM_INT_MASK_CLR_PWM_I_2_H_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_1_BKIN_MASK_CLR_Pos                                5
#define PWM_INT_MASK_CLR_PWM_1_BKIN_MASK_CLR_Msk                                (0x1U << PWM_INT_MASK_CLR_PWM_1_BKIN_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_I_1_CYCLE_MASK_CLR_Pos                             4
#define PWM_INT_MASK_CLR_PWM_I_1_CYCLE_MASK_CLR_Msk                             (0x1U << PWM_INT_MASK_CLR_PWM_I_1_CYCLE_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_I_1_H_MASK_CLR_Pos                                 3
#define PWM_INT_MASK_CLR_PWM_I_1_H_MASK_CLR_Msk                                 (0x1U << PWM_INT_MASK_CLR_PWM_I_1_H_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_0_BKIN_MASK_CLR_Pos                                2
#define PWM_INT_MASK_CLR_PWM_0_BKIN_MASK_CLR_Msk                                (0x1U << PWM_INT_MASK_CLR_PWM_0_BKIN_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_I_0_CYCLE_MASK_CLR_Pos                             1
#define PWM_INT_MASK_CLR_PWM_I_0_CYCLE_MASK_CLR_Msk                             (0x1U << PWM_INT_MASK_CLR_PWM_I_0_CYCLE_MASK_CLR_Pos)

#define PWM_INT_MASK_CLR_PWM_I_0_H_MASK_CLR_Pos                                 0
#define PWM_INT_MASK_CLR_PWM_I_0_H_MASK_CLR_Msk                                 (0x1U << PWM_INT_MASK_CLR_PWM_I_0_H_MASK_CLR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_SR_PENDING
//
#define PWM_INT_SR_PENDING_PWM_OVERFLOW_INT_Pos                                 13
#define PWM_INT_SR_PENDING_PWM_OVERFLOW_INT_Msk                                 (0x1U << PWM_INT_SR_PENDING_PWM_OVERFLOW_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_UNDERFLOW_INT_Pos                                12
#define PWM_INT_SR_PENDING_PWM_UNDERFLOW_INT_Msk                                (0x1U << PWM_INT_SR_PENDING_PWM_UNDERFLOW_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_3_BKIN_Pos                                       11
#define PWM_INT_SR_PENDING_PWM_3_BKIN_Msk                                       (0x1U << PWM_INT_SR_PENDING_PWM_3_BKIN_Pos)

#define PWM_INT_SR_PENDING_PWM_I_3_CYCLE_INT_Pos                                10
#define PWM_INT_SR_PENDING_PWM_I_3_CYCLE_INT_Msk                                (0x1U << PWM_INT_SR_PENDING_PWM_I_3_CYCLE_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_I_3_H_INT_Pos                                    9
#define PWM_INT_SR_PENDING_PWM_I_3_H_INT_Msk                                    (0x1U << PWM_INT_SR_PENDING_PWM_I_3_H_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_2_BKIN_Pos                                       8
#define PWM_INT_SR_PENDING_PWM_2_BKIN_Msk                                       (0x1U << PWM_INT_SR_PENDING_PWM_2_BKIN_Pos)

#define PWM_INT_SR_PENDING_PWM_I_2_CYCLE_INT_Pos                                7
#define PWM_INT_SR_PENDING_PWM_I_2_CYCLE_INT_Msk                                (0x1U << PWM_INT_SR_PENDING_PWM_I_2_CYCLE_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_I_2_H_INT_Pos                                    6
#define PWM_INT_SR_PENDING_PWM_I_2_H_INT_Msk                                    (0x1U << PWM_INT_SR_PENDING_PWM_I_2_H_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_1_BKIN_Pos                                       5
#define PWM_INT_SR_PENDING_PWM_1_BKIN_Msk                                       (0x1U << PWM_INT_SR_PENDING_PWM_1_BKIN_Pos)

#define PWM_INT_SR_PENDING_PWM_I_1_CYCLE_INT_Pos                                4
#define PWM_INT_SR_PENDING_PWM_I_1_CYCLE_INT_Msk                                (0x1U << PWM_INT_SR_PENDING_PWM_I_1_CYCLE_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_I_1_H_INT_Pos                                    3
#define PWM_INT_SR_PENDING_PWM_I_1_H_INT_Msk                                    (0x1U << PWM_INT_SR_PENDING_PWM_I_1_H_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_0_BKIN_Pos                                       2
#define PWM_INT_SR_PENDING_PWM_0_BKIN_Msk                                       (0x1U << PWM_INT_SR_PENDING_PWM_0_BKIN_Pos)

#define PWM_INT_SR_PENDING_PWM_I_0_CYCLE_INT_Pos                                1
#define PWM_INT_SR_PENDING_PWM_I_0_CYCLE_INT_Msk                                (0x1U << PWM_INT_SR_PENDING_PWM_I_0_CYCLE_INT_Pos)

#define PWM_INT_SR_PENDING_PWM_I_0_H_INT_Pos                                    0
#define PWM_INT_SR_PENDING_PWM_I_0_H_INT_Msk                                    (0x1U << PWM_INT_SR_PENDING_PWM_I_0_H_INT_Pos)

#endif //__WTM2101_PWM_REGISTER_H_INCLUDED__