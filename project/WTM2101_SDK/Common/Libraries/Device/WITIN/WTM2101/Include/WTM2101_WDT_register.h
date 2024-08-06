/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 WDT register.
  * @date    2023-03-20
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Mon Mar 20 11:31:58 2023/////////////


#ifndef __WTM2101_WDT_REGISTER_H_INCLUDED__
#define __WTM2101_WDT_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// WDT_CR
//
#define WDT_WDT_CR_RPL_Pos                                                      2
#define WDT_WDT_CR_RPL_Msk                                                      (0x7U << WDT_WDT_CR_RPL_Pos)

#define WDT_WDT_CR_RMOD_Pos                                                     1
#define WDT_WDT_CR_RMOD_Msk                                                     (0x1U << WDT_WDT_CR_RMOD_Pos)

#define WDT_WDT_CR_WDT_EN_Pos                                                   0
#define WDT_WDT_CR_WDT_EN_Msk                                                   (0x1U << WDT_WDT_CR_WDT_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_TORR
//
#define WDT_WDT_TORR_TOP_INIT_Pos                                               4
#define WDT_WDT_TORR_TOP_INIT_Msk                                               (0xfU << WDT_WDT_TORR_TOP_INIT_Pos)

#define WDT_WDT_TORR_TOP_Pos                                                    0
#define WDT_WDT_TORR_TOP_Msk                                                    (0xfU << WDT_WDT_TORR_TOP_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_CCVR
//
#define WDT_WDT_CCVR_WDT_CCVR_Pos                                               0
#define WDT_WDT_CCVR_WDT_CCVR_Msk                                               (0xffffffffU << WDT_WDT_CCVR_WDT_CCVR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_CRR
//
#define WDT_WDT_CRR_WDT_CRR_Pos                                                 0
#define WDT_WDT_CRR_WDT_CRR_Msk                                                 (0xffU << WDT_WDT_CRR_WDT_CRR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_STAT
//
#define WDT_WDT_STAT_WDT_STAT_Pos                                               0
#define WDT_WDT_STAT_WDT_STAT_Msk                                               (0x1U << WDT_WDT_STAT_WDT_STAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_EOI
//
#define WDT_WDT_EOI_WDT_EOI_Pos                                                 0
#define WDT_WDT_EOI_WDT_EOI_Msk                                                 (0x1U << WDT_WDT_EOI_WDT_EOI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_COMP_PARAMS_5
//
#define WDT_WDT_COMP_PARAMS_5_CP_WDT_USER_TOP_MAX_Pos                           0
#define WDT_WDT_COMP_PARAMS_5_CP_WDT_USER_TOP_MAX_Msk                           (0xffffffffU << WDT_WDT_COMP_PARAMS_5_CP_WDT_USER_TOP_MAX_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_COMP_PARAMS_4
//
#define WDT_WDT_COMP_PARAMS_4_CP_WDT_USER_TOP_INIT_MAX_Pos                      0
#define WDT_WDT_COMP_PARAMS_4_CP_WDT_USER_TOP_INIT_MAX_Msk                      (0xffffffffU << WDT_WDT_COMP_PARAMS_4_CP_WDT_USER_TOP_INIT_MAX_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_COMP_PARAMS_3
//
#define WDT_WDT_COMP_PARAMS_3_CD_WDT_TOP_RST_Pos                                0
#define WDT_WDT_COMP_PARAMS_3_CD_WDT_TOP_RST_Msk                                (0xffffffffU << WDT_WDT_COMP_PARAMS_3_CD_WDT_TOP_RST_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_COMP_PARAMS_2
//
#define WDT_WDT_COMP_PARAMS_2_CP_WDT_CNT_RST_Pos                                0
#define WDT_WDT_COMP_PARAMS_2_CP_WDT_CNT_RST_Msk                                (0xffffffffU << WDT_WDT_COMP_PARAMS_2_CP_WDT_CNT_RST_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_COMP_PARAMS_1
//
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_CNT_WIDTH_Pos                              24
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_CNT_WIDTH_Msk                              (0x1fU << WDT_WDT_COMP_PARAMS_1_CP_WDT_CNT_WIDTH_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_TOP_INIT_Pos                          20
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_TOP_INIT_Msk                          (0xfU << WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_TOP_INIT_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_TOP_Pos                               16
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_TOP_Msk                               (0xfU << WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_TOP_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_RPL_Pos                               10
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_RPL_Msk                               (0x7U << WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_RPL_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_APB_DATA_WIDTH_Pos                         8
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_APB_DATA_WIDTH_Msk                         (0x3U << WDT_WDT_COMP_PARAMS_1_CP_WDT_APB_DATA_WIDTH_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_PAUSE_Pos                                  7
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_PAUSE_Msk                                  (0x1U << WDT_WDT_COMP_PARAMS_1_CP_WDT_PAUSE_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_USE_FIX_TOP_Pos                            6
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_USE_FIX_TOP_Msk                            (0x1U << WDT_WDT_COMP_PARAMS_1_CP_WDT_USE_FIX_TOP_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_TOP_Pos                                 5
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_TOP_Msk                                 (0x1U << WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_TOP_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_RPL_Pos                                 4
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_RPL_Msk                                 (0x1U << WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_RPL_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_RMOD_Pos                                3
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_RMOD_Msk                                (0x1U << WDT_WDT_COMP_PARAMS_1_CP_WDT_HC_RMOD_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DUAL_TOP_Pos                               2
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DUAL_TOP_Msk                               (0x1U << WDT_WDT_COMP_PARAMS_1_CP_WDT_DUAL_TOP_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_RMOD_Pos                              1
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_RMOD_Msk                              (0x1U << WDT_WDT_COMP_PARAMS_1_CP_WDT_DFLT_RMOD_Pos)

#define WDT_WDT_COMP_PARAMS_1_CP_WDT_ALWAYS_EN_Pos                              0
#define WDT_WDT_COMP_PARAMS_1_CP_WDT_ALWAYS_EN_Msk                              (0x1U << WDT_WDT_COMP_PARAMS_1_CP_WDT_ALWAYS_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_COMP_VERSION
//
#define WDT_WDT_COMP_VERSION_WDT_COMP_VERSION_Pos                               0
#define WDT_WDT_COMP_VERSION_WDT_COMP_VERSION_Msk                               (0xffffffffU << WDT_WDT_COMP_VERSION_WDT_COMP_VERSION_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// WDT_COMP_TYPE
//
#define WDT_WDT_COMP_TYPE_WDT_COMP_TYPE_Pos                                     0
#define WDT_WDT_COMP_TYPE_WDT_COMP_TYPE_Msk                                     (0xffffffffU << WDT_WDT_COMP_TYPE_WDT_COMP_TYPE_Pos)

#endif //__WTM2101_WDT_REGISTER_H_INCLUDED__