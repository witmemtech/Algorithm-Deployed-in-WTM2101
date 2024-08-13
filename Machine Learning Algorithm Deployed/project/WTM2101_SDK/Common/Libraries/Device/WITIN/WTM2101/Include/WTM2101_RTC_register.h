/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 RTC register.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Sat Aug 21 12:46:34 2021/////////////


#ifndef __WTM2101_RTC_REGISTER_H_INCLUDED__
#define __WTM2101_RTC_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// RTC_CCVR
//
#define RTC_RTC_CCVR_CURRENT_COUNTER_VALUE_REGISTER_Pos                         0
#define RTC_RTC_CCVR_CURRENT_COUNTER_VALUE_REGISTER_Msk                         (0xffffffffU << RTC_RTC_CCVR_CURRENT_COUNTER_VALUE_REGISTER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTC_CMR
//
#define RTC_RTC_CMR_COUNTER_MATCH_Pos                                           0
#define RTC_RTC_CMR_COUNTER_MATCH_Msk                                           (0xffffffffU << RTC_RTC_CMR_COUNTER_MATCH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTC_CLR
//
#define RTC_RTC_CLR_COUNTER_LOAD_Pos                                            0
#define RTC_RTC_CLR_COUNTER_LOAD_Msk                                            (0xffffffffU << RTC_RTC_CLR_COUNTER_LOAD_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTC_CCR
//
#define RTC_RTC_CCR_RTC_WEN_Pos                                                 3
#define RTC_RTC_CCR_RTC_WEN_Msk                                                 (0x1U << RTC_RTC_CCR_RTC_WEN_Pos)

#define RTC_RTC_CCR_RTC_EN_Pos                                                  2
#define RTC_RTC_CCR_RTC_EN_Msk                                                  (0x1U << RTC_RTC_CCR_RTC_EN_Pos)

#define RTC_RTC_CCR_RTC_MASK_Pos                                                1
#define RTC_RTC_CCR_RTC_MASK_Msk                                                (0x1U << RTC_RTC_CCR_RTC_MASK_Pos)

#define RTC_RTC_CCR_RTC_IEN_Pos                                                 0
#define RTC_RTC_CCR_RTC_IEN_Msk                                                 (0x1U << RTC_RTC_CCR_RTC_IEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTC_STAT
//
#define RTC_RTC_STAT_RTC_STAT_Pos                                               0
#define RTC_RTC_STAT_RTC_STAT_Msk                                               (0x1U << RTC_RTC_STAT_RTC_STAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTC_RSTAT
//
#define RTC_RTC_RSTAT_RTC_RSTAT_Pos                                             0
#define RTC_RTC_RSTAT_RTC_RSTAT_Msk                                             (0x1U << RTC_RTC_RSTAT_RTC_RSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTC_EOI
//
#define RTC_RTC_EOI_RTC_EOI_Pos                                                 0
#define RTC_RTC_EOI_RTC_EOI_Msk                                                 (0x1U << RTC_RTC_EOI_RTC_EOI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTC_COMP_VERSION
//
#define RTC_RTC_COMP_VERSION_RTC_COMP_VERSION_Pos                               0
#define RTC_RTC_COMP_VERSION_RTC_COMP_VERSION_Msk                               (0xffffffffU << RTC_RTC_COMP_VERSION_RTC_COMP_VERSION_Pos)

#endif //__WTM2101_RTC_REGISTER_H_INCLUDED__