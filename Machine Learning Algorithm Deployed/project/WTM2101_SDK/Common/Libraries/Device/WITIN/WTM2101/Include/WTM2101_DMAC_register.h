/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 DMA register.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Sat Aug 21 12:46:34 2021/////////////


#ifndef __WTM2101_DMAC_REGISTER_H_INCLUDED__
#define __WTM2101_DMAC_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// SAR0
//
#define DMAC_SAR0_SAR_Pos                                                       0
#define DMAC_SAR0_SAR_Msk                                                       (0xffffffffU << DMAC_SAR0_SAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DAR0
//
#define DMAC_DAR0_DAR_Pos                                                       0
#define DMAC_DAR0_DAR_Msk                                                       (0xffffffffU << DMAC_DAR0_DAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LLP0
//
#define DMAC_LLP0_LOC_Pos                                                       2
#define DMAC_LLP0_LOC_Msk                                                       (0x3fffffffU << DMAC_LLP0_LOC_Pos)

#define DMAC_LLP0_LMS_Pos                                                       0
#define DMAC_LLP0_LMS_Msk                                                       (0x3U << DMAC_LLP0_LMS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CTL0
//
#define DMAC_CTL0_DONE_Pos                                                      44
#define DMAC_CTL0_DONE_Msk                                                      (0x1U << DMAC_CTL0_DONE_Pos)

#define DMAC_CTL0_BLOCK_TS_Pos                                                  32
#define DMAC_CTL0_BLOCK_TS_Msk                                                  (0xffU << DMAC_CTL0_BLOCK_TS_Pos)

#define DMAC_CTL0_LLP_SRC_EN_Pos                                                28
#define DMAC_CTL0_LLP_SRC_EN_Msk                                                (0x1U << DMAC_CTL0_LLP_SRC_EN_Pos)

#define DMAC_CTL0_LLP_DST_EN_Pos                                                27
#define DMAC_CTL0_LLP_DST_EN_Msk                                                (0x1U << DMAC_CTL0_LLP_DST_EN_Pos)

#define DMAC_CTL0_SMS_Pos                                                       25
#define DMAC_CTL0_SMS_Msk                                                       (0x3U << DMAC_CTL0_SMS_Pos)

#define DMAC_CTL0_DMS_Pos                                                       23
#define DMAC_CTL0_DMS_Msk                                                       (0x3U << DMAC_CTL0_DMS_Pos)

#define DMAC_CTL0_TT_FC_Pos                                                     20
#define DMAC_CTL0_TT_FC_Msk                                                     (0x7U << DMAC_CTL0_TT_FC_Pos)

#define DMAC_CTL0_DST_SCATTER_EN_Pos                                            18
#define DMAC_CTL0_DST_SCATTER_EN_Msk                                            (0x1U << DMAC_CTL0_DST_SCATTER_EN_Pos)

#define DMAC_CTL0_SRC_GATHER_EN_Pos                                             17
#define DMAC_CTL0_SRC_GATHER_EN_Msk                                             (0x1U << DMAC_CTL0_SRC_GATHER_EN_Pos)

#define DMAC_CTL0_SRC_MSIZE_Pos                                                 14
#define DMAC_CTL0_SRC_MSIZE_Msk                                                 (0x7U << DMAC_CTL0_SRC_MSIZE_Pos)

#define DMAC_CTL0_DEST_MSIZE_Pos                                                11
#define DMAC_CTL0_DEST_MSIZE_Msk                                                (0x7U << DMAC_CTL0_DEST_MSIZE_Pos)

#define DMAC_CTL0_SINC_Pos                                                      9
#define DMAC_CTL0_SINC_Msk                                                      (0x3U << DMAC_CTL0_SINC_Pos)

#define DMAC_CTL0_DINC_Pos                                                      7
#define DMAC_CTL0_DINC_Msk                                                      (0x3U << DMAC_CTL0_DINC_Pos)

#define DMAC_CTL0_SRC_TR_WIDTH_Pos                                              4
#define DMAC_CTL0_SRC_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL0_SRC_TR_WIDTH_Pos)

#define DMAC_CTL0_DST_TR_WIDTH_Pos                                              1
#define DMAC_CTL0_DST_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL0_DST_TR_WIDTH_Pos)

#define DMAC_CTL0_INT_EN_Pos                                                    0
#define DMAC_CTL0_INT_EN_Msk                                                    (0x1U << DMAC_CTL0_INT_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTAT0
//
#define DMAC_SSTAT0_SSTAT_Pos                                                   0
#define DMAC_SSTAT0_SSTAT_Msk                                                   (0xffffffffU << DMAC_SSTAT0_SSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTAT0
//
#define DMAC_DSTAT0_DSTAT_Pos                                                   0
#define DMAC_DSTAT0_DSTAT_Msk                                                   (0xffffffffU << DMAC_DSTAT0_DSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTATAR0
//
#define DMAC_SSTATAR0_SSTATAR_Pos                                               0
#define DMAC_SSTATAR0_SSTATAR_Msk                                               (0xffffffffU << DMAC_SSTATAR0_SSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTATAR0
//
#define DMAC_DSTATAR0_DSTATAR_Pos                                               0
#define DMAC_DSTATAR0_DSTATAR_Msk                                               (0xffffffffU << DMAC_DSTATAR0_DSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CFG0
//
#define DMAC_CFG0_DEST_PER_Pos                                                  43
#define DMAC_CFG0_DEST_PER_Msk                                                  (0xfU << DMAC_CFG0_DEST_PER_Pos)

#define DMAC_CFG0_SRC_PER_Pos                                                   39
#define DMAC_CFG0_SRC_PER_Msk                                                   (0xfU << DMAC_CFG0_SRC_PER_Pos)

#define DMAC_CFG0_SS_UPD_EN_Pos                                                 38
#define DMAC_CFG0_SS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG0_SS_UPD_EN_Pos)

#define DMAC_CFG0_DS_UPD_EN_Pos                                                 37
#define DMAC_CFG0_DS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG0_DS_UPD_EN_Pos)

#define DMAC_CFG0_PROTCTL_Pos                                                   34
#define DMAC_CFG0_PROTCTL_Msk                                                   (0x7U << DMAC_CFG0_PROTCTL_Pos)

#define DMAC_CFG0_FIFO_MODE_Pos                                                 33
#define DMAC_CFG0_FIFO_MODE_Msk                                                 (0x1U << DMAC_CFG0_FIFO_MODE_Pos)

#define DMAC_CFG0_FCMODE_Pos                                                    32
#define DMAC_CFG0_FCMODE_Msk                                                    (0x1U << DMAC_CFG0_FCMODE_Pos)

#define DMAC_CFG0_RELOAD_DST_Pos                                                31
#define DMAC_CFG0_RELOAD_DST_Msk                                                (0x1U << DMAC_CFG0_RELOAD_DST_Pos)

#define DMAC_CFG0_RELOAD_SRC_Pos                                                30
#define DMAC_CFG0_RELOAD_SRC_Msk                                                (0x1U << DMAC_CFG0_RELOAD_SRC_Pos)

#define DMAC_CFG0_MAX_ABRST_Pos                                                 20
#define DMAC_CFG0_MAX_ABRST_Msk                                                 (0x3ffU << DMAC_CFG0_MAX_ABRST_Pos)

#define DMAC_CFG0_SRC_HS_POL_Pos                                                19
#define DMAC_CFG0_SRC_HS_POL_Msk                                                (0x1U << DMAC_CFG0_SRC_HS_POL_Pos)

#define DMAC_CFG0_DST_HS_POL_Pos                                                18
#define DMAC_CFG0_DST_HS_POL_Msk                                                (0x1U << DMAC_CFG0_DST_HS_POL_Pos)

#define DMAC_CFG0_LOCK_B_Pos                                                    17
#define DMAC_CFG0_LOCK_B_Msk                                                    (0x1U << DMAC_CFG0_LOCK_B_Pos)

#define DMAC_CFG0_LOCK_CH_Pos                                                   16
#define DMAC_CFG0_LOCK_CH_Msk                                                   (0x1U << DMAC_CFG0_LOCK_CH_Pos)

#define DMAC_CFG0_LOCK_B_L_Pos                                                  14
#define DMAC_CFG0_LOCK_B_L_Msk                                                  (0x3U << DMAC_CFG0_LOCK_B_L_Pos)

#define DMAC_CFG0_LOCK_CH_L_Pos                                                 12
#define DMAC_CFG0_LOCK_CH_L_Msk                                                 (0x3U << DMAC_CFG0_LOCK_CH_L_Pos)

#define DMAC_CFG0_HS_SEL_SRC_Pos                                                11
#define DMAC_CFG0_HS_SEL_SRC_Msk                                                (0x1U << DMAC_CFG0_HS_SEL_SRC_Pos)

#define DMAC_CFG0_HS_SEL_DST_Pos                                                10
#define DMAC_CFG0_HS_SEL_DST_Msk                                                (0x1U << DMAC_CFG0_HS_SEL_DST_Pos)

#define DMAC_CFG0_FIFO_EMPTY_Pos                                                9
#define DMAC_CFG0_FIFO_EMPTY_Msk                                                (0x1U << DMAC_CFG0_FIFO_EMPTY_Pos)

#define DMAC_CFG0_CH_SUSP_Pos                                                   8
#define DMAC_CFG0_CH_SUSP_Msk                                                   (0x1U << DMAC_CFG0_CH_SUSP_Pos)

#define DMAC_CFG0_CH_PRIOR_Pos                                                  5
#define DMAC_CFG0_CH_PRIOR_Msk                                                  (0x7U << DMAC_CFG0_CH_PRIOR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SGR0
//
#define DMAC_SGR0_SGC_Pos                                                       20
#define DMAC_SGR0_SGC_Msk                                                       (0xffU << DMAC_SGR0_SGC_Pos)

#define DMAC_SGR0_SGI_Pos                                                       0
#define DMAC_SGR0_SGI_Msk                                                       (0xfffffU << DMAC_SGR0_SGI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSR0
//
#define DMAC_DSR0_DSC_Pos                                                       20
#define DMAC_DSR0_DSC_Msk                                                       (0xffU << DMAC_DSR0_DSC_Pos)

#define DMAC_DSR0_DSI_Pos                                                       0
#define DMAC_DSR0_DSI_Msk                                                       (0xfffffU << DMAC_DSR0_DSI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SAR1
//
#define DMAC_SAR1_SAR_Pos                                                       0
#define DMAC_SAR1_SAR_Msk                                                       (0xffffffffU << DMAC_SAR1_SAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DAR1
//
#define DMAC_DAR1_DAR_Pos                                                       0
#define DMAC_DAR1_DAR_Msk                                                       (0xffffffffU << DMAC_DAR1_DAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LLP1
//
#define DMAC_LLP1_LOC_Pos                                                       2
#define DMAC_LLP1_LOC_Msk                                                       (0x3fffffffU << DMAC_LLP1_LOC_Pos)

#define DMAC_LLP1_LMS_Pos                                                       0
#define DMAC_LLP1_LMS_Msk                                                       (0x3U << DMAC_LLP1_LMS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CTL1
//
#define DMAC_CTL1_DONE_Pos                                                      44
#define DMAC_CTL1_DONE_Msk                                                      (0x1U << DMAC_CTL1_DONE_Pos)

#define DMAC_CTL1_BLOCK_TS_Pos                                                  32
#define DMAC_CTL1_BLOCK_TS_Msk                                                  (0xffU << DMAC_CTL1_BLOCK_TS_Pos)

#define DMAC_CTL1_LLP_SRC_EN_Pos                                                28
#define DMAC_CTL1_LLP_SRC_EN_Msk                                                (0x1U << DMAC_CTL1_LLP_SRC_EN_Pos)

#define DMAC_CTL1_LLP_DST_EN_Pos                                                27
#define DMAC_CTL1_LLP_DST_EN_Msk                                                (0x1U << DMAC_CTL1_LLP_DST_EN_Pos)

#define DMAC_CTL1_SMS_Pos                                                       25
#define DMAC_CTL1_SMS_Msk                                                       (0x3U << DMAC_CTL1_SMS_Pos)

#define DMAC_CTL1_DMS_Pos                                                       23
#define DMAC_CTL1_DMS_Msk                                                       (0x3U << DMAC_CTL1_DMS_Pos)

#define DMAC_CTL1_TT_FC_Pos                                                     20
#define DMAC_CTL1_TT_FC_Msk                                                     (0x7U << DMAC_CTL1_TT_FC_Pos)

#define DMAC_CTL1_DST_SCATTER_EN_Pos                                            18
#define DMAC_CTL1_DST_SCATTER_EN_Msk                                            (0x1U << DMAC_CTL1_DST_SCATTER_EN_Pos)

#define DMAC_CTL1_SRC_GATHER_EN_Pos                                             17
#define DMAC_CTL1_SRC_GATHER_EN_Msk                                             (0x1U << DMAC_CTL1_SRC_GATHER_EN_Pos)

#define DMAC_CTL1_SRC_MSIZE_Pos                                                 14
#define DMAC_CTL1_SRC_MSIZE_Msk                                                 (0x7U << DMAC_CTL1_SRC_MSIZE_Pos)

#define DMAC_CTL1_DEST_MSIZE_Pos                                                11
#define DMAC_CTL1_DEST_MSIZE_Msk                                                (0x7U << DMAC_CTL1_DEST_MSIZE_Pos)

#define DMAC_CTL1_SINC_Pos                                                      9
#define DMAC_CTL1_SINC_Msk                                                      (0x3U << DMAC_CTL1_SINC_Pos)

#define DMAC_CTL1_DINC_Pos                                                      7
#define DMAC_CTL1_DINC_Msk                                                      (0x3U << DMAC_CTL1_DINC_Pos)

#define DMAC_CTL1_SRC_TR_WIDTH_Pos                                              4
#define DMAC_CTL1_SRC_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL1_SRC_TR_WIDTH_Pos)

#define DMAC_CTL1_DST_TR_WIDTH_Pos                                              1
#define DMAC_CTL1_DST_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL1_DST_TR_WIDTH_Pos)

#define DMAC_CTL1_INT_EN_Pos                                                    0
#define DMAC_CTL1_INT_EN_Msk                                                    (0x1U << DMAC_CTL1_INT_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTAT1
//
#define DMAC_SSTAT1_SSTAT_Pos                                                   0
#define DMAC_SSTAT1_SSTAT_Msk                                                   (0xffffffffU << DMAC_SSTAT1_SSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTAT1
//
#define DMAC_DSTAT1_DSTAT_Pos                                                   0
#define DMAC_DSTAT1_DSTAT_Msk                                                   (0xffffffffU << DMAC_DSTAT1_DSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTATAR1
//
#define DMAC_SSTATAR1_SSTATAR_Pos                                               0
#define DMAC_SSTATAR1_SSTATAR_Msk                                               (0xffffffffU << DMAC_SSTATAR1_SSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTATAR1
//
#define DMAC_DSTATAR1_DSTATAR_Pos                                               0
#define DMAC_DSTATAR1_DSTATAR_Msk                                               (0xffffffffU << DMAC_DSTATAR1_DSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CFG1
//
#define DMAC_CFG1_DEST_PER_Pos                                                  43
#define DMAC_CFG1_DEST_PER_Msk                                                  (0xfU << DMAC_CFG1_DEST_PER_Pos)

#define DMAC_CFG1_SRC_PER_Pos                                                   39
#define DMAC_CFG1_SRC_PER_Msk                                                   (0xfU << DMAC_CFG1_SRC_PER_Pos)

#define DMAC_CFG1_SS_UPD_EN_Pos                                                 38
#define DMAC_CFG1_SS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG1_SS_UPD_EN_Pos)

#define DMAC_CFG1_DS_UPD_EN_Pos                                                 37
#define DMAC_CFG1_DS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG1_DS_UPD_EN_Pos)

#define DMAC_CFG1_PROTCTL_Pos                                                   34
#define DMAC_CFG1_PROTCTL_Msk                                                   (0x7U << DMAC_CFG1_PROTCTL_Pos)

#define DMAC_CFG1_FIFO_MODE_Pos                                                 33
#define DMAC_CFG1_FIFO_MODE_Msk                                                 (0x1U << DMAC_CFG1_FIFO_MODE_Pos)

#define DMAC_CFG1_FCMODE_Pos                                                    32
#define DMAC_CFG1_FCMODE_Msk                                                    (0x1U << DMAC_CFG1_FCMODE_Pos)

#define DMAC_CFG1_RELOAD_DST_Pos                                                31
#define DMAC_CFG1_RELOAD_DST_Msk                                                (0x1U << DMAC_CFG1_RELOAD_DST_Pos)

#define DMAC_CFG1_RELOAD_SRC_Pos                                                30
#define DMAC_CFG1_RELOAD_SRC_Msk                                                (0x1U << DMAC_CFG1_RELOAD_SRC_Pos)

#define DMAC_CFG1_MAX_ABRST_Pos                                                 20
#define DMAC_CFG1_MAX_ABRST_Msk                                                 (0x3ffU << DMAC_CFG1_MAX_ABRST_Pos)

#define DMAC_CFG1_SRC_HS_POL_Pos                                                19
#define DMAC_CFG1_SRC_HS_POL_Msk                                                (0x1U << DMAC_CFG1_SRC_HS_POL_Pos)

#define DMAC_CFG1_DST_HS_POL_Pos                                                18
#define DMAC_CFG1_DST_HS_POL_Msk                                                (0x1U << DMAC_CFG1_DST_HS_POL_Pos)

#define DMAC_CFG1_LOCK_B_Pos                                                    17
#define DMAC_CFG1_LOCK_B_Msk                                                    (0x1U << DMAC_CFG1_LOCK_B_Pos)

#define DMAC_CFG1_LOCK_CH_Pos                                                   16
#define DMAC_CFG1_LOCK_CH_Msk                                                   (0x1U << DMAC_CFG1_LOCK_CH_Pos)

#define DMAC_CFG1_LOCK_B_L_Pos                                                  14
#define DMAC_CFG1_LOCK_B_L_Msk                                                  (0x3U << DMAC_CFG1_LOCK_B_L_Pos)

#define DMAC_CFG1_LOCK_CH_L_Pos                                                 12
#define DMAC_CFG1_LOCK_CH_L_Msk                                                 (0x3U << DMAC_CFG1_LOCK_CH_L_Pos)

#define DMAC_CFG1_HS_SEL_SRC_Pos                                                11
#define DMAC_CFG1_HS_SEL_SRC_Msk                                                (0x1U << DMAC_CFG1_HS_SEL_SRC_Pos)

#define DMAC_CFG1_HS_SEL_DST_Pos                                                10
#define DMAC_CFG1_HS_SEL_DST_Msk                                                (0x1U << DMAC_CFG1_HS_SEL_DST_Pos)

#define DMAC_CFG1_FIFO_EMPTY_Pos                                                9
#define DMAC_CFG1_FIFO_EMPTY_Msk                                                (0x1U << DMAC_CFG1_FIFO_EMPTY_Pos)

#define DMAC_CFG1_CH_SUSP_Pos                                                   8
#define DMAC_CFG1_CH_SUSP_Msk                                                   (0x1U << DMAC_CFG1_CH_SUSP_Pos)

#define DMAC_CFG1_CH_PRIOR_Pos                                                  5
#define DMAC_CFG1_CH_PRIOR_Msk                                                  (0x7U << DMAC_CFG1_CH_PRIOR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SGR1
//
#define DMAC_SGR1_SGC_Pos                                                       20
#define DMAC_SGR1_SGC_Msk                                                       (0xffU << DMAC_SGR1_SGC_Pos)

#define DMAC_SGR1_SGI_Pos                                                       0
#define DMAC_SGR1_SGI_Msk                                                       (0xfffffU << DMAC_SGR1_SGI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSR1
//
#define DMAC_DSR1_DSC_Pos                                                       20
#define DMAC_DSR1_DSC_Msk                                                       (0xffU << DMAC_DSR1_DSC_Pos)

#define DMAC_DSR1_DSI_Pos                                                       0
#define DMAC_DSR1_DSI_Msk                                                       (0xfffffU << DMAC_DSR1_DSI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SAR2
//
#define DMAC_SAR2_SAR_Pos                                                       0
#define DMAC_SAR2_SAR_Msk                                                       (0xffffffffU << DMAC_SAR2_SAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DAR2
//
#define DMAC_DAR2_DAR_Pos                                                       0
#define DMAC_DAR2_DAR_Msk                                                       (0xffffffffU << DMAC_DAR2_DAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LLP2
//
#define DMAC_LLP2_LOC_Pos                                                       2
#define DMAC_LLP2_LOC_Msk                                                       (0x3fffffffU << DMAC_LLP2_LOC_Pos)

#define DMAC_LLP2_LMS_Pos                                                       0
#define DMAC_LLP2_LMS_Msk                                                       (0x3U << DMAC_LLP2_LMS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CTL2
//
#define DMAC_CTL2_DONE_Pos                                                      44
#define DMAC_CTL2_DONE_Msk                                                      (0x1U << DMAC_CTL2_DONE_Pos)

#define DMAC_CTL2_BLOCK_TS_Pos                                                  32
#define DMAC_CTL2_BLOCK_TS_Msk                                                  (0xffU << DMAC_CTL2_BLOCK_TS_Pos)

#define DMAC_CTL2_LLP_SRC_EN_Pos                                                28
#define DMAC_CTL2_LLP_SRC_EN_Msk                                                (0x1U << DMAC_CTL2_LLP_SRC_EN_Pos)

#define DMAC_CTL2_LLP_DST_EN_Pos                                                27
#define DMAC_CTL2_LLP_DST_EN_Msk                                                (0x1U << DMAC_CTL2_LLP_DST_EN_Pos)

#define DMAC_CTL2_SMS_Pos                                                       25
#define DMAC_CTL2_SMS_Msk                                                       (0x3U << DMAC_CTL2_SMS_Pos)

#define DMAC_CTL2_DMS_Pos                                                       23
#define DMAC_CTL2_DMS_Msk                                                       (0x3U << DMAC_CTL2_DMS_Pos)

#define DMAC_CTL2_TT_FC_Pos                                                     20
#define DMAC_CTL2_TT_FC_Msk                                                     (0x7U << DMAC_CTL2_TT_FC_Pos)

#define DMAC_CTL2_DST_SCATTER_EN_Pos                                            18
#define DMAC_CTL2_DST_SCATTER_EN_Msk                                            (0x1U << DMAC_CTL2_DST_SCATTER_EN_Pos)

#define DMAC_CTL2_SRC_GATHER_EN_Pos                                             17
#define DMAC_CTL2_SRC_GATHER_EN_Msk                                             (0x1U << DMAC_CTL2_SRC_GATHER_EN_Pos)

#define DMAC_CTL2_SRC_MSIZE_Pos                                                 14
#define DMAC_CTL2_SRC_MSIZE_Msk                                                 (0x7U << DMAC_CTL2_SRC_MSIZE_Pos)

#define DMAC_CTL2_DEST_MSIZE_Pos                                                11
#define DMAC_CTL2_DEST_MSIZE_Msk                                                (0x7U << DMAC_CTL2_DEST_MSIZE_Pos)

#define DMAC_CTL2_SINC_Pos                                                      9
#define DMAC_CTL2_SINC_Msk                                                      (0x3U << DMAC_CTL2_SINC_Pos)

#define DMAC_CTL2_DINC_Pos                                                      7
#define DMAC_CTL2_DINC_Msk                                                      (0x3U << DMAC_CTL2_DINC_Pos)

#define DMAC_CTL2_SRC_TR_WIDTH_Pos                                              4
#define DMAC_CTL2_SRC_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL2_SRC_TR_WIDTH_Pos)

#define DMAC_CTL2_DST_TR_WIDTH_Pos                                              1
#define DMAC_CTL2_DST_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL2_DST_TR_WIDTH_Pos)

#define DMAC_CTL2_INT_EN_Pos                                                    0
#define DMAC_CTL2_INT_EN_Msk                                                    (0x1U << DMAC_CTL2_INT_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTAT2
//
#define DMAC_SSTAT2_SSTAT_Pos                                                   0
#define DMAC_SSTAT2_SSTAT_Msk                                                   (0xffffffffU << DMAC_SSTAT2_SSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTAT2
//
#define DMAC_DSTAT2_DSTAT_Pos                                                   0
#define DMAC_DSTAT2_DSTAT_Msk                                                   (0xffffffffU << DMAC_DSTAT2_DSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTATAR2
//
#define DMAC_SSTATAR2_SSTATAR_Pos                                               0
#define DMAC_SSTATAR2_SSTATAR_Msk                                               (0xffffffffU << DMAC_SSTATAR2_SSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTATAR2
//
#define DMAC_DSTATAR2_DSTATAR_Pos                                               0
#define DMAC_DSTATAR2_DSTATAR_Msk                                               (0xffffffffU << DMAC_DSTATAR2_DSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CFG2
//
#define DMAC_CFG2_DEST_PER_Pos                                                  43
#define DMAC_CFG2_DEST_PER_Msk                                                  (0xfU << DMAC_CFG2_DEST_PER_Pos)

#define DMAC_CFG2_SRC_PER_Pos                                                   39
#define DMAC_CFG2_SRC_PER_Msk                                                   (0xfU << DMAC_CFG2_SRC_PER_Pos)

#define DMAC_CFG2_SS_UPD_EN_Pos                                                 38
#define DMAC_CFG2_SS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG2_SS_UPD_EN_Pos)

#define DMAC_CFG2_DS_UPD_EN_Pos                                                 37
#define DMAC_CFG2_DS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG2_DS_UPD_EN_Pos)

#define DMAC_CFG2_PROTCTL_Pos                                                   34
#define DMAC_CFG2_PROTCTL_Msk                                                   (0x7U << DMAC_CFG2_PROTCTL_Pos)

#define DMAC_CFG2_FIFO_MODE_Pos                                                 33
#define DMAC_CFG2_FIFO_MODE_Msk                                                 (0x1U << DMAC_CFG2_FIFO_MODE_Pos)

#define DMAC_CFG2_FCMODE_Pos                                                    32
#define DMAC_CFG2_FCMODE_Msk                                                    (0x1U << DMAC_CFG2_FCMODE_Pos)

#define DMAC_CFG2_RELOAD_DST_Pos                                                31
#define DMAC_CFG2_RELOAD_DST_Msk                                                (0x1U << DMAC_CFG2_RELOAD_DST_Pos)

#define DMAC_CFG2_RELOAD_SRC_Pos                                                30
#define DMAC_CFG2_RELOAD_SRC_Msk                                                (0x1U << DMAC_CFG2_RELOAD_SRC_Pos)

#define DMAC_CFG2_MAX_ABRST_Pos                                                 20
#define DMAC_CFG2_MAX_ABRST_Msk                                                 (0x3ffU << DMAC_CFG2_MAX_ABRST_Pos)

#define DMAC_CFG2_SRC_HS_POL_Pos                                                19
#define DMAC_CFG2_SRC_HS_POL_Msk                                                (0x1U << DMAC_CFG2_SRC_HS_POL_Pos)

#define DMAC_CFG2_DST_HS_POL_Pos                                                18
#define DMAC_CFG2_DST_HS_POL_Msk                                                (0x1U << DMAC_CFG2_DST_HS_POL_Pos)

#define DMAC_CFG2_LOCK_B_Pos                                                    17
#define DMAC_CFG2_LOCK_B_Msk                                                    (0x1U << DMAC_CFG2_LOCK_B_Pos)

#define DMAC_CFG2_LOCK_CH_Pos                                                   16
#define DMAC_CFG2_LOCK_CH_Msk                                                   (0x1U << DMAC_CFG2_LOCK_CH_Pos)

#define DMAC_CFG2_LOCK_B_L_Pos                                                  14
#define DMAC_CFG2_LOCK_B_L_Msk                                                  (0x3U << DMAC_CFG2_LOCK_B_L_Pos)

#define DMAC_CFG2_LOCK_CH_L_Pos                                                 12
#define DMAC_CFG2_LOCK_CH_L_Msk                                                 (0x3U << DMAC_CFG2_LOCK_CH_L_Pos)

#define DMAC_CFG2_HS_SEL_SRC_Pos                                                11
#define DMAC_CFG2_HS_SEL_SRC_Msk                                                (0x1U << DMAC_CFG2_HS_SEL_SRC_Pos)

#define DMAC_CFG2_HS_SEL_DST_Pos                                                10
#define DMAC_CFG2_HS_SEL_DST_Msk                                                (0x1U << DMAC_CFG2_HS_SEL_DST_Pos)

#define DMAC_CFG2_FIFO_EMPTY_Pos                                                9
#define DMAC_CFG2_FIFO_EMPTY_Msk                                                (0x1U << DMAC_CFG2_FIFO_EMPTY_Pos)

#define DMAC_CFG2_CH_SUSP_Pos                                                   8
#define DMAC_CFG2_CH_SUSP_Msk                                                   (0x1U << DMAC_CFG2_CH_SUSP_Pos)

#define DMAC_CFG2_CH_PRIOR_Pos                                                  5
#define DMAC_CFG2_CH_PRIOR_Msk                                                  (0x7U << DMAC_CFG2_CH_PRIOR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SGR2
//
#define DMAC_SGR2_SGC_Pos                                                       20
#define DMAC_SGR2_SGC_Msk                                                       (0xffU << DMAC_SGR2_SGC_Pos)

#define DMAC_SGR2_SGI_Pos                                                       0
#define DMAC_SGR2_SGI_Msk                                                       (0xfffffU << DMAC_SGR2_SGI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSR2
//
#define DMAC_DSR2_DSC_Pos                                                       20
#define DMAC_DSR2_DSC_Msk                                                       (0xffU << DMAC_DSR2_DSC_Pos)

#define DMAC_DSR2_DSI_Pos                                                       0
#define DMAC_DSR2_DSI_Msk                                                       (0xfffffU << DMAC_DSR2_DSI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SAR3
//
#define DMAC_SAR3_SAR_Pos                                                       0
#define DMAC_SAR3_SAR_Msk                                                       (0xffffffffU << DMAC_SAR3_SAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DAR3
//
#define DMAC_DAR3_DAR_Pos                                                       0
#define DMAC_DAR3_DAR_Msk                                                       (0xffffffffU << DMAC_DAR3_DAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LLP3
//
#define DMAC_LLP3_LOC_Pos                                                       2
#define DMAC_LLP3_LOC_Msk                                                       (0x3fffffffU << DMAC_LLP3_LOC_Pos)

#define DMAC_LLP3_LMS_Pos                                                       0
#define DMAC_LLP3_LMS_Msk                                                       (0x3U << DMAC_LLP3_LMS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CTL3
//
#define DMAC_CTL3_DONE_Pos                                                      44
#define DMAC_CTL3_DONE_Msk                                                      (0x1U << DMAC_CTL3_DONE_Pos)

#define DMAC_CTL3_BLOCK_TS_Pos                                                  32
#define DMAC_CTL3_BLOCK_TS_Msk                                                  (0xffU << DMAC_CTL3_BLOCK_TS_Pos)

#define DMAC_CTL3_LLP_SRC_EN_Pos                                                28
#define DMAC_CTL3_LLP_SRC_EN_Msk                                                (0x1U << DMAC_CTL3_LLP_SRC_EN_Pos)

#define DMAC_CTL3_LLP_DST_EN_Pos                                                27
#define DMAC_CTL3_LLP_DST_EN_Msk                                                (0x1U << DMAC_CTL3_LLP_DST_EN_Pos)

#define DMAC_CTL3_SMS_Pos                                                       25
#define DMAC_CTL3_SMS_Msk                                                       (0x3U << DMAC_CTL3_SMS_Pos)

#define DMAC_CTL3_DMS_Pos                                                       23
#define DMAC_CTL3_DMS_Msk                                                       (0x3U << DMAC_CTL3_DMS_Pos)

#define DMAC_CTL3_TT_FC_Pos                                                     20
#define DMAC_CTL3_TT_FC_Msk                                                     (0x7U << DMAC_CTL3_TT_FC_Pos)

#define DMAC_CTL3_DST_SCATTER_EN_Pos                                            18
#define DMAC_CTL3_DST_SCATTER_EN_Msk                                            (0x1U << DMAC_CTL3_DST_SCATTER_EN_Pos)

#define DMAC_CTL3_SRC_GATHER_EN_Pos                                             17
#define DMAC_CTL3_SRC_GATHER_EN_Msk                                             (0x1U << DMAC_CTL3_SRC_GATHER_EN_Pos)

#define DMAC_CTL3_SRC_MSIZE_Pos                                                 14
#define DMAC_CTL3_SRC_MSIZE_Msk                                                 (0x7U << DMAC_CTL3_SRC_MSIZE_Pos)

#define DMAC_CTL3_DEST_MSIZE_Pos                                                11
#define DMAC_CTL3_DEST_MSIZE_Msk                                                (0x7U << DMAC_CTL3_DEST_MSIZE_Pos)

#define DMAC_CTL3_SINC_Pos                                                      9
#define DMAC_CTL3_SINC_Msk                                                      (0x3U << DMAC_CTL3_SINC_Pos)

#define DMAC_CTL3_DINC_Pos                                                      7
#define DMAC_CTL3_DINC_Msk                                                      (0x3U << DMAC_CTL3_DINC_Pos)

#define DMAC_CTL3_SRC_TR_WIDTH_Pos                                              4
#define DMAC_CTL3_SRC_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL3_SRC_TR_WIDTH_Pos)

#define DMAC_CTL3_DST_TR_WIDTH_Pos                                              1
#define DMAC_CTL3_DST_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL3_DST_TR_WIDTH_Pos)

#define DMAC_CTL3_INT_EN_Pos                                                    0
#define DMAC_CTL3_INT_EN_Msk                                                    (0x1U << DMAC_CTL3_INT_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTAT3
//
#define DMAC_SSTAT3_SSTAT_Pos                                                   0
#define DMAC_SSTAT3_SSTAT_Msk                                                   (0xffffffffU << DMAC_SSTAT3_SSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTAT3
//
#define DMAC_DSTAT3_DSTAT_Pos                                                   0
#define DMAC_DSTAT3_DSTAT_Msk                                                   (0xffffffffU << DMAC_DSTAT3_DSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTATAR3
//
#define DMAC_SSTATAR3_SSTATAR_Pos                                               0
#define DMAC_SSTATAR3_SSTATAR_Msk                                               (0xffffffffU << DMAC_SSTATAR3_SSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTATAR3
//
#define DMAC_DSTATAR3_DSTATAR_Pos                                               0
#define DMAC_DSTATAR3_DSTATAR_Msk                                               (0xffffffffU << DMAC_DSTATAR3_DSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CFG3
//
#define DMAC_CFG3_DEST_PER_Pos                                                  43
#define DMAC_CFG3_DEST_PER_Msk                                                  (0xfU << DMAC_CFG3_DEST_PER_Pos)

#define DMAC_CFG3_SRC_PER_Pos                                                   39
#define DMAC_CFG3_SRC_PER_Msk                                                   (0xfU << DMAC_CFG3_SRC_PER_Pos)

#define DMAC_CFG3_SS_UPD_EN_Pos                                                 38
#define DMAC_CFG3_SS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG3_SS_UPD_EN_Pos)

#define DMAC_CFG3_DS_UPD_EN_Pos                                                 37
#define DMAC_CFG3_DS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG3_DS_UPD_EN_Pos)

#define DMAC_CFG3_PROTCTL_Pos                                                   34
#define DMAC_CFG3_PROTCTL_Msk                                                   (0x7U << DMAC_CFG3_PROTCTL_Pos)

#define DMAC_CFG3_FIFO_MODE_Pos                                                 33
#define DMAC_CFG3_FIFO_MODE_Msk                                                 (0x1U << DMAC_CFG3_FIFO_MODE_Pos)

#define DMAC_CFG3_FCMODE_Pos                                                    32
#define DMAC_CFG3_FCMODE_Msk                                                    (0x1U << DMAC_CFG3_FCMODE_Pos)

#define DMAC_CFG3_RELOAD_DST_Pos                                                31
#define DMAC_CFG3_RELOAD_DST_Msk                                                (0x1U << DMAC_CFG3_RELOAD_DST_Pos)

#define DMAC_CFG3_RELOAD_SRC_Pos                                                30
#define DMAC_CFG3_RELOAD_SRC_Msk                                                (0x1U << DMAC_CFG3_RELOAD_SRC_Pos)

#define DMAC_CFG3_MAX_ABRST_Pos                                                 20
#define DMAC_CFG3_MAX_ABRST_Msk                                                 (0x3ffU << DMAC_CFG3_MAX_ABRST_Pos)

#define DMAC_CFG3_SRC_HS_POL_Pos                                                19
#define DMAC_CFG3_SRC_HS_POL_Msk                                                (0x1U << DMAC_CFG3_SRC_HS_POL_Pos)

#define DMAC_CFG3_DST_HS_POL_Pos                                                18
#define DMAC_CFG3_DST_HS_POL_Msk                                                (0x1U << DMAC_CFG3_DST_HS_POL_Pos)

#define DMAC_CFG3_LOCK_B_Pos                                                    17
#define DMAC_CFG3_LOCK_B_Msk                                                    (0x1U << DMAC_CFG3_LOCK_B_Pos)

#define DMAC_CFG3_LOCK_CH_Pos                                                   16
#define DMAC_CFG3_LOCK_CH_Msk                                                   (0x1U << DMAC_CFG3_LOCK_CH_Pos)

#define DMAC_CFG3_LOCK_B_L_Pos                                                  14
#define DMAC_CFG3_LOCK_B_L_Msk                                                  (0x3U << DMAC_CFG3_LOCK_B_L_Pos)

#define DMAC_CFG3_LOCK_CH_L_Pos                                                 12
#define DMAC_CFG3_LOCK_CH_L_Msk                                                 (0x3U << DMAC_CFG3_LOCK_CH_L_Pos)

#define DMAC_CFG3_HS_SEL_SRC_Pos                                                11
#define DMAC_CFG3_HS_SEL_SRC_Msk                                                (0x1U << DMAC_CFG3_HS_SEL_SRC_Pos)

#define DMAC_CFG3_HS_SEL_DST_Pos                                                10
#define DMAC_CFG3_HS_SEL_DST_Msk                                                (0x1U << DMAC_CFG3_HS_SEL_DST_Pos)

#define DMAC_CFG3_FIFO_EMPTY_Pos                                                9
#define DMAC_CFG3_FIFO_EMPTY_Msk                                                (0x1U << DMAC_CFG3_FIFO_EMPTY_Pos)

#define DMAC_CFG3_CH_SUSP_Pos                                                   8
#define DMAC_CFG3_CH_SUSP_Msk                                                   (0x1U << DMAC_CFG3_CH_SUSP_Pos)

#define DMAC_CFG3_CH_PRIOR_Pos                                                  5
#define DMAC_CFG3_CH_PRIOR_Msk                                                  (0x7U << DMAC_CFG3_CH_PRIOR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SGR3
//
#define DMAC_SGR3_SGC_Pos                                                       20
#define DMAC_SGR3_SGC_Msk                                                       (0xffU << DMAC_SGR3_SGC_Pos)

#define DMAC_SGR3_SGI_Pos                                                       0
#define DMAC_SGR3_SGI_Msk                                                       (0xfffffU << DMAC_SGR3_SGI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSR3
//
#define DMAC_DSR3_DSC_Pos                                                       20
#define DMAC_DSR3_DSC_Msk                                                       (0xffU << DMAC_DSR3_DSC_Pos)

#define DMAC_DSR3_DSI_Pos                                                       0
#define DMAC_DSR3_DSI_Msk                                                       (0xfffffU << DMAC_DSR3_DSI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SAR4
//
#define DMAC_SAR4_SAR_Pos                                                       0
#define DMAC_SAR4_SAR_Msk                                                       (0xffffffffU << DMAC_SAR4_SAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DAR4
//
#define DMAC_DAR4_DAR_Pos                                                       0
#define DMAC_DAR4_DAR_Msk                                                       (0xffffffffU << DMAC_DAR4_DAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LLP4
//
#define DMAC_LLP4_LOC_Pos                                                       2
#define DMAC_LLP4_LOC_Msk                                                       (0x3fffffffU << DMAC_LLP4_LOC_Pos)

#define DMAC_LLP4_LMS_Pos                                                       0
#define DMAC_LLP4_LMS_Msk                                                       (0x3U << DMAC_LLP4_LMS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CTL4
//
#define DMAC_CTL4_DONE_Pos                                                      44
#define DMAC_CTL4_DONE_Msk                                                      (0x1U << DMAC_CTL4_DONE_Pos)

#define DMAC_CTL4_BLOCK_TS_Pos                                                  32
#define DMAC_CTL4_BLOCK_TS_Msk                                                  (0xffU << DMAC_CTL4_BLOCK_TS_Pos)

#define DMAC_CTL4_LLP_SRC_EN_Pos                                                28
#define DMAC_CTL4_LLP_SRC_EN_Msk                                                (0x1U << DMAC_CTL4_LLP_SRC_EN_Pos)

#define DMAC_CTL4_LLP_DST_EN_Pos                                                27
#define DMAC_CTL4_LLP_DST_EN_Msk                                                (0x1U << DMAC_CTL4_LLP_DST_EN_Pos)

#define DMAC_CTL4_SMS_Pos                                                       25
#define DMAC_CTL4_SMS_Msk                                                       (0x3U << DMAC_CTL4_SMS_Pos)

#define DMAC_CTL4_DMS_Pos                                                       23
#define DMAC_CTL4_DMS_Msk                                                       (0x3U << DMAC_CTL4_DMS_Pos)

#define DMAC_CTL4_TT_FC_Pos                                                     20
#define DMAC_CTL4_TT_FC_Msk                                                     (0x7U << DMAC_CTL4_TT_FC_Pos)

#define DMAC_CTL4_DST_SCATTER_EN_Pos                                            18
#define DMAC_CTL4_DST_SCATTER_EN_Msk                                            (0x1U << DMAC_CTL4_DST_SCATTER_EN_Pos)

#define DMAC_CTL4_SRC_GATHER_EN_Pos                                             17
#define DMAC_CTL4_SRC_GATHER_EN_Msk                                             (0x1U << DMAC_CTL4_SRC_GATHER_EN_Pos)

#define DMAC_CTL4_SRC_MSIZE_Pos                                                 14
#define DMAC_CTL4_SRC_MSIZE_Msk                                                 (0x7U << DMAC_CTL4_SRC_MSIZE_Pos)

#define DMAC_CTL4_DEST_MSIZE_Pos                                                11
#define DMAC_CTL4_DEST_MSIZE_Msk                                                (0x7U << DMAC_CTL4_DEST_MSIZE_Pos)

#define DMAC_CTL4_SINC_Pos                                                      9
#define DMAC_CTL4_SINC_Msk                                                      (0x3U << DMAC_CTL4_SINC_Pos)

#define DMAC_CTL4_DINC_Pos                                                      7
#define DMAC_CTL4_DINC_Msk                                                      (0x3U << DMAC_CTL4_DINC_Pos)

#define DMAC_CTL4_SRC_TR_WIDTH_Pos                                              4
#define DMAC_CTL4_SRC_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL4_SRC_TR_WIDTH_Pos)

#define DMAC_CTL4_DST_TR_WIDTH_Pos                                              1
#define DMAC_CTL4_DST_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL4_DST_TR_WIDTH_Pos)

#define DMAC_CTL4_INT_EN_Pos                                                    0
#define DMAC_CTL4_INT_EN_Msk                                                    (0x1U << DMAC_CTL4_INT_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTAT4
//
#define DMAC_SSTAT4_SSTAT_Pos                                                   0
#define DMAC_SSTAT4_SSTAT_Msk                                                   (0xffffffffU << DMAC_SSTAT4_SSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTAT4
//
#define DMAC_DSTAT4_DSTAT_Pos                                                   0
#define DMAC_DSTAT4_DSTAT_Msk                                                   (0xffffffffU << DMAC_DSTAT4_DSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTATAR4
//
#define DMAC_SSTATAR4_SSTATAR_Pos                                               0
#define DMAC_SSTATAR4_SSTATAR_Msk                                               (0xffffffffU << DMAC_SSTATAR4_SSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTATAR4
//
#define DMAC_DSTATAR4_DSTATAR_Pos                                               0
#define DMAC_DSTATAR4_DSTATAR_Msk                                               (0xffffffffU << DMAC_DSTATAR4_DSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CFG4
//
#define DMAC_CFG4_DEST_PER_Pos                                                  43
#define DMAC_CFG4_DEST_PER_Msk                                                  (0xfU << DMAC_CFG4_DEST_PER_Pos)

#define DMAC_CFG4_SRC_PER_Pos                                                   39
#define DMAC_CFG4_SRC_PER_Msk                                                   (0xfU << DMAC_CFG4_SRC_PER_Pos)

#define DMAC_CFG4_SS_UPD_EN_Pos                                                 38
#define DMAC_CFG4_SS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG4_SS_UPD_EN_Pos)

#define DMAC_CFG4_DS_UPD_EN_Pos                                                 37
#define DMAC_CFG4_DS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG4_DS_UPD_EN_Pos)

#define DMAC_CFG4_PROTCTL_Pos                                                   34
#define DMAC_CFG4_PROTCTL_Msk                                                   (0x7U << DMAC_CFG4_PROTCTL_Pos)

#define DMAC_CFG4_FIFO_MODE_Pos                                                 33
#define DMAC_CFG4_FIFO_MODE_Msk                                                 (0x1U << DMAC_CFG4_FIFO_MODE_Pos)

#define DMAC_CFG4_FCMODE_Pos                                                    32
#define DMAC_CFG4_FCMODE_Msk                                                    (0x1U << DMAC_CFG4_FCMODE_Pos)

#define DMAC_CFG4_RELOAD_DST_Pos                                                31
#define DMAC_CFG4_RELOAD_DST_Msk                                                (0x1U << DMAC_CFG4_RELOAD_DST_Pos)

#define DMAC_CFG4_RELOAD_SRC_Pos                                                30
#define DMAC_CFG4_RELOAD_SRC_Msk                                                (0x1U << DMAC_CFG4_RELOAD_SRC_Pos)

#define DMAC_CFG4_MAX_ABRST_Pos                                                 20
#define DMAC_CFG4_MAX_ABRST_Msk                                                 (0x3ffU << DMAC_CFG4_MAX_ABRST_Pos)

#define DMAC_CFG4_SRC_HS_POL_Pos                                                19
#define DMAC_CFG4_SRC_HS_POL_Msk                                                (0x1U << DMAC_CFG4_SRC_HS_POL_Pos)

#define DMAC_CFG4_DST_HS_POL_Pos                                                18
#define DMAC_CFG4_DST_HS_POL_Msk                                                (0x1U << DMAC_CFG4_DST_HS_POL_Pos)

#define DMAC_CFG4_LOCK_B_Pos                                                    17
#define DMAC_CFG4_LOCK_B_Msk                                                    (0x1U << DMAC_CFG4_LOCK_B_Pos)

#define DMAC_CFG4_LOCK_CH_Pos                                                   16
#define DMAC_CFG4_LOCK_CH_Msk                                                   (0x1U << DMAC_CFG4_LOCK_CH_Pos)

#define DMAC_CFG4_LOCK_B_L_Pos                                                  14
#define DMAC_CFG4_LOCK_B_L_Msk                                                  (0x3U << DMAC_CFG4_LOCK_B_L_Pos)

#define DMAC_CFG4_LOCK_CH_L_Pos                                                 12
#define DMAC_CFG4_LOCK_CH_L_Msk                                                 (0x3U << DMAC_CFG4_LOCK_CH_L_Pos)

#define DMAC_CFG4_HS_SEL_SRC_Pos                                                11
#define DMAC_CFG4_HS_SEL_SRC_Msk                                                (0x1U << DMAC_CFG4_HS_SEL_SRC_Pos)

#define DMAC_CFG4_HS_SEL_DST_Pos                                                10
#define DMAC_CFG4_HS_SEL_DST_Msk                                                (0x1U << DMAC_CFG4_HS_SEL_DST_Pos)

#define DMAC_CFG4_FIFO_EMPTY_Pos                                                9
#define DMAC_CFG4_FIFO_EMPTY_Msk                                                (0x1U << DMAC_CFG4_FIFO_EMPTY_Pos)

#define DMAC_CFG4_CH_SUSP_Pos                                                   8
#define DMAC_CFG4_CH_SUSP_Msk                                                   (0x1U << DMAC_CFG4_CH_SUSP_Pos)

#define DMAC_CFG4_CH_PRIOR_Pos                                                  5
#define DMAC_CFG4_CH_PRIOR_Msk                                                  (0x7U << DMAC_CFG4_CH_PRIOR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SGR4
//
#define DMAC_SGR4_SGC_Pos                                                       20
#define DMAC_SGR4_SGC_Msk                                                       (0xffU << DMAC_SGR4_SGC_Pos)

#define DMAC_SGR4_SGI_Pos                                                       0
#define DMAC_SGR4_SGI_Msk                                                       (0xfffffU << DMAC_SGR4_SGI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSR4
//
#define DMAC_DSR4_DSC_Pos                                                       20
#define DMAC_DSR4_DSC_Msk                                                       (0xffU << DMAC_DSR4_DSC_Pos)

#define DMAC_DSR4_DSI_Pos                                                       0
#define DMAC_DSR4_DSI_Msk                                                       (0xfffffU << DMAC_DSR4_DSI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SAR5
//
#define DMAC_SAR5_SAR_Pos                                                       0
#define DMAC_SAR5_SAR_Msk                                                       (0xffffffffU << DMAC_SAR5_SAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DAR5
//
#define DMAC_DAR5_DAR_Pos                                                       0
#define DMAC_DAR5_DAR_Msk                                                       (0xffffffffU << DMAC_DAR5_DAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LLP5
//
#define DMAC_LLP5_LOC_Pos                                                       2
#define DMAC_LLP5_LOC_Msk                                                       (0x3fffffffU << DMAC_LLP5_LOC_Pos)

#define DMAC_LLP5_LMS_Pos                                                       0
#define DMAC_LLP5_LMS_Msk                                                       (0x3U << DMAC_LLP5_LMS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CTL5
//
#define DMAC_CTL5_DONE_Pos                                                      44
#define DMAC_CTL5_DONE_Msk                                                      (0x1U << DMAC_CTL5_DONE_Pos)

#define DMAC_CTL5_BLOCK_TS_Pos                                                  32
#define DMAC_CTL5_BLOCK_TS_Msk                                                  (0xffU << DMAC_CTL5_BLOCK_TS_Pos)

#define DMAC_CTL5_LLP_SRC_EN_Pos                                                28
#define DMAC_CTL5_LLP_SRC_EN_Msk                                                (0x1U << DMAC_CTL5_LLP_SRC_EN_Pos)

#define DMAC_CTL5_LLP_DST_EN_Pos                                                27
#define DMAC_CTL5_LLP_DST_EN_Msk                                                (0x1U << DMAC_CTL5_LLP_DST_EN_Pos)

#define DMAC_CTL5_SMS_Pos                                                       25
#define DMAC_CTL5_SMS_Msk                                                       (0x3U << DMAC_CTL5_SMS_Pos)

#define DMAC_CTL5_DMS_Pos                                                       23
#define DMAC_CTL5_DMS_Msk                                                       (0x3U << DMAC_CTL5_DMS_Pos)

#define DMAC_CTL5_TT_FC_Pos                                                     20
#define DMAC_CTL5_TT_FC_Msk                                                     (0x7U << DMAC_CTL5_TT_FC_Pos)

#define DMAC_CTL5_DST_SCATTER_EN_Pos                                            18
#define DMAC_CTL5_DST_SCATTER_EN_Msk                                            (0x1U << DMAC_CTL5_DST_SCATTER_EN_Pos)

#define DMAC_CTL5_SRC_GATHER_EN_Pos                                             17
#define DMAC_CTL5_SRC_GATHER_EN_Msk                                             (0x1U << DMAC_CTL5_SRC_GATHER_EN_Pos)

#define DMAC_CTL5_SRC_MSIZE_Pos                                                 14
#define DMAC_CTL5_SRC_MSIZE_Msk                                                 (0x7U << DMAC_CTL5_SRC_MSIZE_Pos)

#define DMAC_CTL5_DEST_MSIZE_Pos                                                11
#define DMAC_CTL5_DEST_MSIZE_Msk                                                (0x7U << DMAC_CTL5_DEST_MSIZE_Pos)

#define DMAC_CTL5_SINC_Pos                                                      9
#define DMAC_CTL5_SINC_Msk                                                      (0x3U << DMAC_CTL5_SINC_Pos)

#define DMAC_CTL5_DINC_Pos                                                      7
#define DMAC_CTL5_DINC_Msk                                                      (0x3U << DMAC_CTL5_DINC_Pos)

#define DMAC_CTL5_SRC_TR_WIDTH_Pos                                              4
#define DMAC_CTL5_SRC_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL5_SRC_TR_WIDTH_Pos)

#define DMAC_CTL5_DST_TR_WIDTH_Pos                                              1
#define DMAC_CTL5_DST_TR_WIDTH_Msk                                              (0x7U << DMAC_CTL5_DST_TR_WIDTH_Pos)

#define DMAC_CTL5_INT_EN_Pos                                                    0
#define DMAC_CTL5_INT_EN_Msk                                                    (0x1U << DMAC_CTL5_INT_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTAT5
//
#define DMAC_SSTAT5_SSTAT_Pos                                                   0
#define DMAC_SSTAT5_SSTAT_Msk                                                   (0xffffffffU << DMAC_SSTAT5_SSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTAT5
//
#define DMAC_DSTAT5_DSTAT_Pos                                                   0
#define DMAC_DSTAT5_DSTAT_Msk                                                   (0xffffffffU << DMAC_DSTAT5_DSTAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSTATAR5
//
#define DMAC_SSTATAR5_SSTATAR_Pos                                               0
#define DMAC_SSTATAR5_SSTATAR_Msk                                               (0xffffffffU << DMAC_SSTATAR5_SSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSTATAR5
//
#define DMAC_DSTATAR5_DSTATAR_Pos                                               0
#define DMAC_DSTATAR5_DSTATAR_Msk                                               (0xffffffffU << DMAC_DSTATAR5_DSTATAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CFG5
//
#define DMAC_CFG5_DEST_PER_Pos                                                  43
#define DMAC_CFG5_DEST_PER_Msk                                                  (0xfU << DMAC_CFG5_DEST_PER_Pos)

#define DMAC_CFG5_SRC_PER_Pos                                                   39
#define DMAC_CFG5_SRC_PER_Msk                                                   (0xfU << DMAC_CFG5_SRC_PER_Pos)

#define DMAC_CFG5_SS_UPD_EN_Pos                                                 38
#define DMAC_CFG5_SS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG5_SS_UPD_EN_Pos)

#define DMAC_CFG5_DS_UPD_EN_Pos                                                 37
#define DMAC_CFG5_DS_UPD_EN_Msk                                                 (0x1U << DMAC_CFG5_DS_UPD_EN_Pos)

#define DMAC_CFG5_PROTCTL_Pos                                                   34
#define DMAC_CFG5_PROTCTL_Msk                                                   (0x7U << DMAC_CFG5_PROTCTL_Pos)

#define DMAC_CFG5_FIFO_MODE_Pos                                                 33
#define DMAC_CFG5_FIFO_MODE_Msk                                                 (0x1U << DMAC_CFG5_FIFO_MODE_Pos)

#define DMAC_CFG5_FCMODE_Pos                                                    32
#define DMAC_CFG5_FCMODE_Msk                                                    (0x1U << DMAC_CFG5_FCMODE_Pos)

#define DMAC_CFG5_RELOAD_DST_Pos                                                31
#define DMAC_CFG5_RELOAD_DST_Msk                                                (0x1U << DMAC_CFG5_RELOAD_DST_Pos)

#define DMAC_CFG5_RELOAD_SRC_Pos                                                30
#define DMAC_CFG5_RELOAD_SRC_Msk                                                (0x1U << DMAC_CFG5_RELOAD_SRC_Pos)

#define DMAC_CFG5_MAX_ABRST_Pos                                                 20
#define DMAC_CFG5_MAX_ABRST_Msk                                                 (0x3ffU << DMAC_CFG5_MAX_ABRST_Pos)

#define DMAC_CFG5_SRC_HS_POL_Pos                                                19
#define DMAC_CFG5_SRC_HS_POL_Msk                                                (0x1U << DMAC_CFG5_SRC_HS_POL_Pos)

#define DMAC_CFG5_DST_HS_POL_Pos                                                18
#define DMAC_CFG5_DST_HS_POL_Msk                                                (0x1U << DMAC_CFG5_DST_HS_POL_Pos)

#define DMAC_CFG5_LOCK_B_Pos                                                    17
#define DMAC_CFG5_LOCK_B_Msk                                                    (0x1U << DMAC_CFG5_LOCK_B_Pos)

#define DMAC_CFG5_LOCK_CH_Pos                                                   16
#define DMAC_CFG5_LOCK_CH_Msk                                                   (0x1U << DMAC_CFG5_LOCK_CH_Pos)

#define DMAC_CFG5_LOCK_B_L_Pos                                                  14
#define DMAC_CFG5_LOCK_B_L_Msk                                                  (0x3U << DMAC_CFG5_LOCK_B_L_Pos)

#define DMAC_CFG5_LOCK_CH_L_Pos                                                 12
#define DMAC_CFG5_LOCK_CH_L_Msk                                                 (0x3U << DMAC_CFG5_LOCK_CH_L_Pos)

#define DMAC_CFG5_HS_SEL_SRC_Pos                                                11
#define DMAC_CFG5_HS_SEL_SRC_Msk                                                (0x1U << DMAC_CFG5_HS_SEL_SRC_Pos)

#define DMAC_CFG5_HS_SEL_DST_Pos                                                10
#define DMAC_CFG5_HS_SEL_DST_Msk                                                (0x1U << DMAC_CFG5_HS_SEL_DST_Pos)

#define DMAC_CFG5_FIFO_EMPTY_Pos                                                9
#define DMAC_CFG5_FIFO_EMPTY_Msk                                                (0x1U << DMAC_CFG5_FIFO_EMPTY_Pos)

#define DMAC_CFG5_CH_SUSP_Pos                                                   8
#define DMAC_CFG5_CH_SUSP_Msk                                                   (0x1U << DMAC_CFG5_CH_SUSP_Pos)

#define DMAC_CFG5_CH_PRIOR_Pos                                                  5
#define DMAC_CFG5_CH_PRIOR_Msk                                                  (0x7U << DMAC_CFG5_CH_PRIOR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SGR5
//
#define DMAC_SGR5_SGC_Pos                                                       20
#define DMAC_SGR5_SGC_Msk                                                       (0xffU << DMAC_SGR5_SGC_Pos)

#define DMAC_SGR5_SGI_Pos                                                       0
#define DMAC_SGR5_SGI_Msk                                                       (0xfffffU << DMAC_SGR5_SGI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DSR5
//
#define DMAC_DSR5_DSC_Pos                                                       20
#define DMAC_DSR5_DSC_Msk                                                       (0xffU << DMAC_DSR5_DSC_Pos)

#define DMAC_DSR5_DSI_Pos                                                       0
#define DMAC_DSR5_DSI_Msk                                                       (0xfffffU << DMAC_DSR5_DSI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAWTFR
//
#define DMAC_RAWTFR_RAW_Pos                                                     0
#define DMAC_RAWTFR_RAW_Msk                                                     (0x3fU << DMAC_RAWTFR_RAW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAWBLOCK
//
#define DMAC_RAWBLOCK_RAW_Pos                                                   0
#define DMAC_RAWBLOCK_RAW_Msk                                                   (0x3fU << DMAC_RAWBLOCK_RAW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAWSRCTRAN
//
#define DMAC_RAWSRCTRAN_RAW_Pos                                                 0
#define DMAC_RAWSRCTRAN_RAW_Msk                                                 (0x3fU << DMAC_RAWSRCTRAN_RAW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAWDSTTRAN
//
#define DMAC_RAWDSTTRAN_RAW_Pos                                                 0
#define DMAC_RAWDSTTRAN_RAW_Msk                                                 (0x3fU << DMAC_RAWDSTTRAN_RAW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RAWERR
//
#define DMAC_RAWERR_RAW_Pos                                                     0
#define DMAC_RAWERR_RAW_Msk                                                     (0x3fU << DMAC_RAWERR_RAW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// STATUSTFR
//
#define DMAC_STATUSTFR_STATUS_Pos                                               0
#define DMAC_STATUSTFR_STATUS_Msk                                               (0x3fU << DMAC_STATUSTFR_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// STATUSBLOCK
//
#define DMAC_STATUSBLOCK_STATUS_Pos                                             0
#define DMAC_STATUSBLOCK_STATUS_Msk                                             (0x3fU << DMAC_STATUSBLOCK_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// STATUSSRCTRAN
//
#define DMAC_STATUSSRCTRAN_STATUS_Pos                                           0
#define DMAC_STATUSSRCTRAN_STATUS_Msk                                           (0x3fU << DMAC_STATUSSRCTRAN_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// STATUSDSTTRAN
//
#define DMAC_STATUSDSTTRAN_STATUS_Pos                                           0
#define DMAC_STATUSDSTTRAN_STATUS_Msk                                           (0x3fU << DMAC_STATUSDSTTRAN_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// STATUSERR
//
#define DMAC_STATUSERR_STATUS_Pos                                               0
#define DMAC_STATUSERR_STATUS_Msk                                               (0x3fU << DMAC_STATUSERR_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MASKTFR
//
#define DMAC_MASKTFR_INT_MASK_WE_Pos                                            8
#define DMAC_MASKTFR_INT_MASK_WE_Msk                                            (0x3fU << DMAC_MASKTFR_INT_MASK_WE_Pos)

#define DMAC_MASKTFR_INT_MASK_Pos                                               0
#define DMAC_MASKTFR_INT_MASK_Msk                                               (0x3fU << DMAC_MASKTFR_INT_MASK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MASKBLOCK
//
#define DMAC_MASKBLOCK_INT_MASK_WE_Pos                                          8
#define DMAC_MASKBLOCK_INT_MASK_WE_Msk                                          (0x3fU << DMAC_MASKBLOCK_INT_MASK_WE_Pos)

#define DMAC_MASKBLOCK_INT_MASK_Pos                                             0
#define DMAC_MASKBLOCK_INT_MASK_Msk                                             (0x3fU << DMAC_MASKBLOCK_INT_MASK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MASKSRCTRAN
//
#define DMAC_MASKSRCTRAN_INT_MASK_WE_Pos                                        8
#define DMAC_MASKSRCTRAN_INT_MASK_WE_Msk                                        (0x3fU << DMAC_MASKSRCTRAN_INT_MASK_WE_Pos)

#define DMAC_MASKSRCTRAN_INT_MASK_Pos                                           0
#define DMAC_MASKSRCTRAN_INT_MASK_Msk                                           (0x3fU << DMAC_MASKSRCTRAN_INT_MASK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MASKDSTTRAN
//
#define DMAC_MASKDSTTRAN_INT_MASK_WE_Pos                                        8
#define DMAC_MASKDSTTRAN_INT_MASK_WE_Msk                                        (0x3fU << DMAC_MASKDSTTRAN_INT_MASK_WE_Pos)

#define DMAC_MASKDSTTRAN_INT_MASK_Pos                                           0
#define DMAC_MASKDSTTRAN_INT_MASK_Msk                                           (0x3fU << DMAC_MASKDSTTRAN_INT_MASK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MASKERR
//
#define DMAC_MASKERR_INT_MASK_WE_Pos                                            8
#define DMAC_MASKERR_INT_MASK_WE_Msk                                            (0x3fU << DMAC_MASKERR_INT_MASK_WE_Pos)

#define DMAC_MASKERR_INT_MASK_Pos                                               0
#define DMAC_MASKERR_INT_MASK_Msk                                               (0x3fU << DMAC_MASKERR_INT_MASK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLEARTFR
//
#define DMAC_CLEARTFR_CLEAR_Pos                                                 0
#define DMAC_CLEARTFR_CLEAR_Msk                                                 (0x3fU << DMAC_CLEARTFR_CLEAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLEARBLOCK
//
#define DMAC_CLEARBLOCK_CLEAR_Pos                                               0
#define DMAC_CLEARBLOCK_CLEAR_Msk                                               (0x3fU << DMAC_CLEARBLOCK_CLEAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLEARSRCTRAN
//
#define DMAC_CLEARSRCTRAN_CLEAR_Pos                                             0
#define DMAC_CLEARSRCTRAN_CLEAR_Msk                                             (0x3fU << DMAC_CLEARSRCTRAN_CLEAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLEARDSTTRAN
//
#define DMAC_CLEARDSTTRAN_CLEAR_Pos                                             0
#define DMAC_CLEARDSTTRAN_CLEAR_Msk                                             (0x3fU << DMAC_CLEARDSTTRAN_CLEAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CLEARERR
//
#define DMAC_CLEARERR_CLEAR_Pos                                                 0
#define DMAC_CLEARERR_CLEAR_Msk                                                 (0x3fU << DMAC_CLEARERR_CLEAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// STATUSINT
//
#define DMAC_STATUSINT_ERR_Pos                                                  4
#define DMAC_STATUSINT_ERR_Msk                                                  (0x1U << DMAC_STATUSINT_ERR_Pos)

#define DMAC_STATUSINT_DSTT_Pos                                                 3
#define DMAC_STATUSINT_DSTT_Msk                                                 (0x1U << DMAC_STATUSINT_DSTT_Pos)

#define DMAC_STATUSINT_SRCT_Pos                                                 2
#define DMAC_STATUSINT_SRCT_Msk                                                 (0x1U << DMAC_STATUSINT_SRCT_Pos)

#define DMAC_STATUSINT_BLOCK_Pos                                                1
#define DMAC_STATUSINT_BLOCK_Msk                                                (0x1U << DMAC_STATUSINT_BLOCK_Pos)

#define DMAC_STATUSINT_TFR_Pos                                                  0
#define DMAC_STATUSINT_TFR_Msk                                                  (0x1U << DMAC_STATUSINT_TFR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// REQSRCREG
//
#define DMAC_REQSRCREG_SRC_REQ_WE_Pos                                           8
#define DMAC_REQSRCREG_SRC_REQ_WE_Msk                                           (0x3fU << DMAC_REQSRCREG_SRC_REQ_WE_Pos)

#define DMAC_REQSRCREG_SRC_REQ_Pos                                              0
#define DMAC_REQSRCREG_SRC_REQ_Msk                                              (0x3fU << DMAC_REQSRCREG_SRC_REQ_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// REQDSTREG
//
#define DMAC_REQDSTREG_DST_REQ_WE_Pos                                           8
#define DMAC_REQDSTREG_DST_REQ_WE_Msk                                           (0x3fU << DMAC_REQDSTREG_DST_REQ_WE_Pos)

#define DMAC_REQDSTREG_DST_REQ_Pos                                              0
#define DMAC_REQDSTREG_DST_REQ_Msk                                              (0x3fU << DMAC_REQDSTREG_DST_REQ_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SGLREQSRCREG
//
#define DMAC_SGLREQSRCREG_SRC_SGLREQ_WE_Pos                                     8
#define DMAC_SGLREQSRCREG_SRC_SGLREQ_WE_Msk                                     (0x3fU << DMAC_SGLREQSRCREG_SRC_SGLREQ_WE_Pos)

#define DMAC_SGLREQSRCREG_SRC_SGLREQ_Pos                                        0
#define DMAC_SGLREQSRCREG_SRC_SGLREQ_Msk                                        (0x3fU << DMAC_SGLREQSRCREG_SRC_SGLREQ_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SGLREQDSTREG
//
#define DMAC_SGLREQDSTREG_DST_SGLREQ_WE_Pos                                     8
#define DMAC_SGLREQDSTREG_DST_SGLREQ_WE_Msk                                     (0x3fU << DMAC_SGLREQDSTREG_DST_SGLREQ_WE_Pos)

#define DMAC_SGLREQDSTREG_DST_SGLREQ_Pos                                        0
#define DMAC_SGLREQDSTREG_DST_SGLREQ_Msk                                        (0x3fU << DMAC_SGLREQDSTREG_DST_SGLREQ_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LSTSRCREG
//
#define DMAC_LSTSRCREG_LSTSRC_WE_Pos                                            8
#define DMAC_LSTSRCREG_LSTSRC_WE_Msk                                            (0x3fU << DMAC_LSTSRCREG_LSTSRC_WE_Pos)

#define DMAC_LSTSRCREG_LSTSRC_Pos                                               0
#define DMAC_LSTSRCREG_LSTSRC_Msk                                               (0x3fU << DMAC_LSTSRCREG_LSTSRC_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LSTDSTREG
//
#define DMAC_LSTDSTREG_LSTDST_WE_Pos                                            8
#define DMAC_LSTDSTREG_LSTDST_WE_Msk                                            (0x3fU << DMAC_LSTDSTREG_LSTDST_WE_Pos)

#define DMAC_LSTDSTREG_LSTDST_Pos                                               0
#define DMAC_LSTDSTREG_LSTDST_Msk                                               (0x3fU << DMAC_LSTDSTREG_LSTDST_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMACFGREG
//
#define DMAC_DMACFGREG_DMACFGREG_Pos                                            0
#define DMAC_DMACFGREG_DMACFGREG_Msk                                            (0x1U << DMAC_DMACFGREG_DMACFGREG_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CHENREG
//
#define DMAC_CHENREG_CH_EN_WE_Pos                                               8
#define DMAC_CHENREG_CH_EN_WE_Msk                                               (0x3fU << DMAC_CHENREG_CH_EN_WE_Pos)

#define DMAC_CHENREG_CH_EN_Pos                                                  0
#define DMAC_CHENREG_CH_EN_Msk                                                  (0x3fU << DMAC_CHENREG_CH_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMAIDREG
//
#define DMAC_DMAIDREG_DMAH_ID_NUM_Pos                                           0
#define DMAC_DMAIDREG_DMAH_ID_NUM_Msk                                           (0xffffffffU << DMAC_DMAIDREG_DMAH_ID_NUM_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMATESTREG
//
#define DMAC_DMATESTREG_TEST_SLV_IF_Pos                                         0
#define DMAC_DMATESTREG_TEST_SLV_IF_Msk                                         (0x1U << DMAC_DMATESTREG_TEST_SLV_IF_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMA_COMP_PARAMS_6
//
#define DMAC_DMA_COMP_PARAMS_6_CH7_FIFO_DEPTH_Pos                               60
#define DMAC_DMA_COMP_PARAMS_6_CH7_FIFO_DEPTH_Msk                               (0x7U << DMAC_DMA_COMP_PARAMS_6_CH7_FIFO_DEPTH_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_SMS_Pos                                      57
#define DMAC_DMA_COMP_PARAMS_6_CH7_SMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_6_CH7_SMS_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_LMS_Pos                                      54
#define DMAC_DMA_COMP_PARAMS_6_CH7_LMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_6_CH7_LMS_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_DMS_Pos                                      51
#define DMAC_DMA_COMP_PARAMS_6_CH7_DMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_6_CH7_DMS_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_MAX_MULT_SIZE_Pos                            48
#define DMAC_DMA_COMP_PARAMS_6_CH7_MAX_MULT_SIZE_Msk                            (0x7U << DMAC_DMA_COMP_PARAMS_6_CH7_MAX_MULT_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_FC_Pos                                       46
#define DMAC_DMA_COMP_PARAMS_6_CH7_FC_Msk                                       (0x3U << DMAC_DMA_COMP_PARAMS_6_CH7_FC_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_HC_LLP_Pos                                   45
#define DMAC_DMA_COMP_PARAMS_6_CH7_HC_LLP_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_6_CH7_HC_LLP_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_CTL_WB_EN_Pos                                44
#define DMAC_DMA_COMP_PARAMS_6_CH7_CTL_WB_EN_Msk                                (0x1U << DMAC_DMA_COMP_PARAMS_6_CH7_CTL_WB_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_MULTI_BLK_EN_Pos                             43
#define DMAC_DMA_COMP_PARAMS_6_CH7_MULTI_BLK_EN_Msk                             (0x1U << DMAC_DMA_COMP_PARAMS_6_CH7_MULTI_BLK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_LOCK_EN_Pos                                  42
#define DMAC_DMA_COMP_PARAMS_6_CH7_LOCK_EN_Msk                                  (0x1U << DMAC_DMA_COMP_PARAMS_6_CH7_LOCK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_SRC_GAT_EN_Pos                               41
#define DMAC_DMA_COMP_PARAMS_6_CH7_SRC_GAT_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_6_CH7_SRC_GAT_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_DST_SCA_EN_Pos                               40
#define DMAC_DMA_COMP_PARAMS_6_CH7_DST_SCA_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_6_CH7_DST_SCA_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_STAT_SRC_Pos                                 39
#define DMAC_DMA_COMP_PARAMS_6_CH7_STAT_SRC_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_6_CH7_STAT_SRC_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_STAT_DST_Pos                                 38
#define DMAC_DMA_COMP_PARAMS_6_CH7_STAT_DST_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_6_CH7_STAT_DST_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_STW_Pos                                      35
#define DMAC_DMA_COMP_PARAMS_6_CH7_STW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_6_CH7_STW_Pos)

#define DMAC_DMA_COMP_PARAMS_6_CH7_DTW_Pos                                      32
#define DMAC_DMA_COMP_PARAMS_6_CH7_DTW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_6_CH7_DTW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMA_COMP_PARAMS_5
//
#define DMAC_DMA_COMP_PARAMS_5_CH5_FIFO_DEPTH_Pos                               60
#define DMAC_DMA_COMP_PARAMS_5_CH5_FIFO_DEPTH_Msk                               (0x7U << DMAC_DMA_COMP_PARAMS_5_CH5_FIFO_DEPTH_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_SMS_Pos                                      57
#define DMAC_DMA_COMP_PARAMS_5_CH5_SMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH5_SMS_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_LMS_Pos                                      54
#define DMAC_DMA_COMP_PARAMS_5_CH5_LMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH5_LMS_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_DMS_Pos                                      51
#define DMAC_DMA_COMP_PARAMS_5_CH5_DMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH5_DMS_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_MAX_MULT_SIZE_Pos                            48
#define DMAC_DMA_COMP_PARAMS_5_CH5_MAX_MULT_SIZE_Msk                            (0x7U << DMAC_DMA_COMP_PARAMS_5_CH5_MAX_MULT_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_FC_Pos                                       46
#define DMAC_DMA_COMP_PARAMS_5_CH5_FC_Msk                                       (0x3U << DMAC_DMA_COMP_PARAMS_5_CH5_FC_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_HC_LLP_Pos                                   45
#define DMAC_DMA_COMP_PARAMS_5_CH5_HC_LLP_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_5_CH5_HC_LLP_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_CTL_WB_EN_Pos                                44
#define DMAC_DMA_COMP_PARAMS_5_CH5_CTL_WB_EN_Msk                                (0x1U << DMAC_DMA_COMP_PARAMS_5_CH5_CTL_WB_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_MULTI_BLK_EN_Pos                             43
#define DMAC_DMA_COMP_PARAMS_5_CH5_MULTI_BLK_EN_Msk                             (0x1U << DMAC_DMA_COMP_PARAMS_5_CH5_MULTI_BLK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_LOCK_EN_Pos                                  42
#define DMAC_DMA_COMP_PARAMS_5_CH5_LOCK_EN_Msk                                  (0x1U << DMAC_DMA_COMP_PARAMS_5_CH5_LOCK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_SRC_GAT_EN_Pos                               41
#define DMAC_DMA_COMP_PARAMS_5_CH5_SRC_GAT_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_5_CH5_SRC_GAT_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_DST_SCA_EN_Pos                               40
#define DMAC_DMA_COMP_PARAMS_5_CH5_DST_SCA_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_5_CH5_DST_SCA_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_STAT_SRC_Pos                                 39
#define DMAC_DMA_COMP_PARAMS_5_CH5_STAT_SRC_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_5_CH5_STAT_SRC_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_STAT_DST_Pos                                 38
#define DMAC_DMA_COMP_PARAMS_5_CH5_STAT_DST_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_5_CH5_STAT_DST_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_STW_Pos                                      35
#define DMAC_DMA_COMP_PARAMS_5_CH5_STW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH5_STW_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH5_DTW_Pos                                      32
#define DMAC_DMA_COMP_PARAMS_5_CH5_DTW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH5_DTW_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_FIFO_DEPTH_Pos                               28
#define DMAC_DMA_COMP_PARAMS_5_CH6_FIFO_DEPTH_Msk                               (0x7U << DMAC_DMA_COMP_PARAMS_5_CH6_FIFO_DEPTH_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_SMS_Pos                                      25
#define DMAC_DMA_COMP_PARAMS_5_CH6_SMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH6_SMS_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_LMS_Pos                                      22
#define DMAC_DMA_COMP_PARAMS_5_CH6_LMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH6_LMS_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_DMS_Pos                                      19
#define DMAC_DMA_COMP_PARAMS_5_CH6_DMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH6_DMS_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_MAX_MULT_SIZE_Pos                            16
#define DMAC_DMA_COMP_PARAMS_5_CH6_MAX_MULT_SIZE_Msk                            (0x7U << DMAC_DMA_COMP_PARAMS_5_CH6_MAX_MULT_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_FC_Pos                                       14
#define DMAC_DMA_COMP_PARAMS_5_CH6_FC_Msk                                       (0x3U << DMAC_DMA_COMP_PARAMS_5_CH6_FC_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_HC_LLP_Pos                                   13
#define DMAC_DMA_COMP_PARAMS_5_CH6_HC_LLP_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_5_CH6_HC_LLP_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_CTL_WB_EN_Pos                                12
#define DMAC_DMA_COMP_PARAMS_5_CH6_CTL_WB_EN_Msk                                (0x1U << DMAC_DMA_COMP_PARAMS_5_CH6_CTL_WB_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_MULTI_BLK_EN_Pos                             11
#define DMAC_DMA_COMP_PARAMS_5_CH6_MULTI_BLK_EN_Msk                             (0x1U << DMAC_DMA_COMP_PARAMS_5_CH6_MULTI_BLK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_LOCK_EN_Pos                                  10
#define DMAC_DMA_COMP_PARAMS_5_CH6_LOCK_EN_Msk                                  (0x1U << DMAC_DMA_COMP_PARAMS_5_CH6_LOCK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_SRC_GAT_EN_Pos                               9
#define DMAC_DMA_COMP_PARAMS_5_CH6_SRC_GAT_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_5_CH6_SRC_GAT_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_DST_SCA_EN_Pos                               8
#define DMAC_DMA_COMP_PARAMS_5_CH6_DST_SCA_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_5_CH6_DST_SCA_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_STAT_SRC_Pos                                 7
#define DMAC_DMA_COMP_PARAMS_5_CH6_STAT_SRC_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_5_CH6_STAT_SRC_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_STAT_DST_Pos                                 6
#define DMAC_DMA_COMP_PARAMS_5_CH6_STAT_DST_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_5_CH6_STAT_DST_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_STW_Pos                                      3
#define DMAC_DMA_COMP_PARAMS_5_CH6_STW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH6_STW_Pos)

#define DMAC_DMA_COMP_PARAMS_5_CH6_DTW_Pos                                      0
#define DMAC_DMA_COMP_PARAMS_5_CH6_DTW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_5_CH6_DTW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMA_COMP_PARAMS_4
//
#define DMAC_DMA_COMP_PARAMS_4_CH3_FIFO_DEPTH_Pos                               60
#define DMAC_DMA_COMP_PARAMS_4_CH3_FIFO_DEPTH_Msk                               (0x7U << DMAC_DMA_COMP_PARAMS_4_CH3_FIFO_DEPTH_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_SMS_Pos                                      57
#define DMAC_DMA_COMP_PARAMS_4_CH3_SMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH3_SMS_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_LMS_Pos                                      54
#define DMAC_DMA_COMP_PARAMS_4_CH3_LMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH3_LMS_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_DMS_Pos                                      51
#define DMAC_DMA_COMP_PARAMS_4_CH3_DMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH3_DMS_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_MAX_MULT_SIZE_Pos                            48
#define DMAC_DMA_COMP_PARAMS_4_CH3_MAX_MULT_SIZE_Msk                            (0x7U << DMAC_DMA_COMP_PARAMS_4_CH3_MAX_MULT_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_FC_Pos                                       46
#define DMAC_DMA_COMP_PARAMS_4_CH3_FC_Msk                                       (0x3U << DMAC_DMA_COMP_PARAMS_4_CH3_FC_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_HC_LLP_Pos                                   45
#define DMAC_DMA_COMP_PARAMS_4_CH3_HC_LLP_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_4_CH3_HC_LLP_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_CTL_WB_EN_Pos                                44
#define DMAC_DMA_COMP_PARAMS_4_CH3_CTL_WB_EN_Msk                                (0x1U << DMAC_DMA_COMP_PARAMS_4_CH3_CTL_WB_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_MULTI_BLK_EN_Pos                             43
#define DMAC_DMA_COMP_PARAMS_4_CH3_MULTI_BLK_EN_Msk                             (0x1U << DMAC_DMA_COMP_PARAMS_4_CH3_MULTI_BLK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_LOCK_EN_Pos                                  42
#define DMAC_DMA_COMP_PARAMS_4_CH3_LOCK_EN_Msk                                  (0x1U << DMAC_DMA_COMP_PARAMS_4_CH3_LOCK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_SRC_GAT_EN_Pos                               41
#define DMAC_DMA_COMP_PARAMS_4_CH3_SRC_GAT_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_4_CH3_SRC_GAT_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_DST_SCA_EN_Pos                               40
#define DMAC_DMA_COMP_PARAMS_4_CH3_DST_SCA_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_4_CH3_DST_SCA_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_STAT_SRC_Pos                                 39
#define DMAC_DMA_COMP_PARAMS_4_CH3_STAT_SRC_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_4_CH3_STAT_SRC_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_STAT_DST_Pos                                 38
#define DMAC_DMA_COMP_PARAMS_4_CH3_STAT_DST_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_4_CH3_STAT_DST_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_STW_Pos                                      35
#define DMAC_DMA_COMP_PARAMS_4_CH3_STW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH3_STW_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH3_DTW_Pos                                      32
#define DMAC_DMA_COMP_PARAMS_4_CH3_DTW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH3_DTW_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_FIFO_DEPTH_Pos                               28
#define DMAC_DMA_COMP_PARAMS_4_CH4_FIFO_DEPTH_Msk                               (0x7U << DMAC_DMA_COMP_PARAMS_4_CH4_FIFO_DEPTH_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_SMS_Pos                                      25
#define DMAC_DMA_COMP_PARAMS_4_CH4_SMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH4_SMS_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_LMS_Pos                                      22
#define DMAC_DMA_COMP_PARAMS_4_CH4_LMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH4_LMS_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_DMS_Pos                                      19
#define DMAC_DMA_COMP_PARAMS_4_CH4_DMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH4_DMS_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_MAX_MULT_SIZE_Pos                            16
#define DMAC_DMA_COMP_PARAMS_4_CH4_MAX_MULT_SIZE_Msk                            (0x7U << DMAC_DMA_COMP_PARAMS_4_CH4_MAX_MULT_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_FC_Pos                                       14
#define DMAC_DMA_COMP_PARAMS_4_CH4_FC_Msk                                       (0x3U << DMAC_DMA_COMP_PARAMS_4_CH4_FC_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_HC_LLP_Pos                                   13
#define DMAC_DMA_COMP_PARAMS_4_CH4_HC_LLP_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_4_CH4_HC_LLP_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_CTL_WB_EN_Pos                                12
#define DMAC_DMA_COMP_PARAMS_4_CH4_CTL_WB_EN_Msk                                (0x1U << DMAC_DMA_COMP_PARAMS_4_CH4_CTL_WB_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_MULTI_BLK_EN_Pos                             11
#define DMAC_DMA_COMP_PARAMS_4_CH4_MULTI_BLK_EN_Msk                             (0x1U << DMAC_DMA_COMP_PARAMS_4_CH4_MULTI_BLK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_LOCK_EN_Pos                                  10
#define DMAC_DMA_COMP_PARAMS_4_CH4_LOCK_EN_Msk                                  (0x1U << DMAC_DMA_COMP_PARAMS_4_CH4_LOCK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_SRC_GAT_EN_Pos                               9
#define DMAC_DMA_COMP_PARAMS_4_CH4_SRC_GAT_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_4_CH4_SRC_GAT_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_DST_SCA_EN_Pos                               8
#define DMAC_DMA_COMP_PARAMS_4_CH4_DST_SCA_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_4_CH4_DST_SCA_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_STAT_SRC_Pos                                 7
#define DMAC_DMA_COMP_PARAMS_4_CH4_STAT_SRC_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_4_CH4_STAT_SRC_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_STAT_DST_Pos                                 6
#define DMAC_DMA_COMP_PARAMS_4_CH4_STAT_DST_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_4_CH4_STAT_DST_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_STW_Pos                                      3
#define DMAC_DMA_COMP_PARAMS_4_CH4_STW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH4_STW_Pos)

#define DMAC_DMA_COMP_PARAMS_4_CH4_DTW_Pos                                      0
#define DMAC_DMA_COMP_PARAMS_4_CH4_DTW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_4_CH4_DTW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMA_COMP_PARAMS_3
//
#define DMAC_DMA_COMP_PARAMS_3_CH1_FIFO_DEPTH_Pos                               60
#define DMAC_DMA_COMP_PARAMS_3_CH1_FIFO_DEPTH_Msk                               (0x7U << DMAC_DMA_COMP_PARAMS_3_CH1_FIFO_DEPTH_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_SMS_Pos                                      57
#define DMAC_DMA_COMP_PARAMS_3_CH1_SMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH1_SMS_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_LMS_Pos                                      54
#define DMAC_DMA_COMP_PARAMS_3_CH1_LMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH1_LMS_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_DMS_Pos                                      51
#define DMAC_DMA_COMP_PARAMS_3_CH1_DMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH1_DMS_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_MAX_MULT_SIZE_Pos                            48
#define DMAC_DMA_COMP_PARAMS_3_CH1_MAX_MULT_SIZE_Msk                            (0x7U << DMAC_DMA_COMP_PARAMS_3_CH1_MAX_MULT_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_FC_Pos                                       46
#define DMAC_DMA_COMP_PARAMS_3_CH1_FC_Msk                                       (0x3U << DMAC_DMA_COMP_PARAMS_3_CH1_FC_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_HC_LLP_Pos                                   45
#define DMAC_DMA_COMP_PARAMS_3_CH1_HC_LLP_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_3_CH1_HC_LLP_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_CTL_WB_EN_Pos                                44
#define DMAC_DMA_COMP_PARAMS_3_CH1_CTL_WB_EN_Msk                                (0x1U << DMAC_DMA_COMP_PARAMS_3_CH1_CTL_WB_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_MULTI_BLK_EN_Pos                             43
#define DMAC_DMA_COMP_PARAMS_3_CH1_MULTI_BLK_EN_Msk                             (0x1U << DMAC_DMA_COMP_PARAMS_3_CH1_MULTI_BLK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_LOCK_EN_Pos                                  42
#define DMAC_DMA_COMP_PARAMS_3_CH1_LOCK_EN_Msk                                  (0x1U << DMAC_DMA_COMP_PARAMS_3_CH1_LOCK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_SRC_GAT_EN_Pos                               41
#define DMAC_DMA_COMP_PARAMS_3_CH1_SRC_GAT_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_3_CH1_SRC_GAT_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_DST_SCA_EN_Pos                               40
#define DMAC_DMA_COMP_PARAMS_3_CH1_DST_SCA_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_3_CH1_DST_SCA_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_STAT_SRC_Pos                                 39
#define DMAC_DMA_COMP_PARAMS_3_CH1_STAT_SRC_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_3_CH1_STAT_SRC_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_STAT_DST_Pos                                 38
#define DMAC_DMA_COMP_PARAMS_3_CH1_STAT_DST_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_3_CH1_STAT_DST_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_STW_Pos                                      35
#define DMAC_DMA_COMP_PARAMS_3_CH1_STW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH1_STW_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH1_DTW_Pos                                      32
#define DMAC_DMA_COMP_PARAMS_3_CH1_DTW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH1_DTW_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_FIFO_DEPTH_Pos                               28
#define DMAC_DMA_COMP_PARAMS_3_CH2_FIFO_DEPTH_Msk                               (0x7U << DMAC_DMA_COMP_PARAMS_3_CH2_FIFO_DEPTH_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_SMS_Pos                                      25
#define DMAC_DMA_COMP_PARAMS_3_CH2_SMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH2_SMS_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_LMS_Pos                                      22
#define DMAC_DMA_COMP_PARAMS_3_CH2_LMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH2_LMS_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_DMS_Pos                                      19
#define DMAC_DMA_COMP_PARAMS_3_CH2_DMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH2_DMS_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_MAX_MULT_SIZE_Pos                            16
#define DMAC_DMA_COMP_PARAMS_3_CH2_MAX_MULT_SIZE_Msk                            (0x7U << DMAC_DMA_COMP_PARAMS_3_CH2_MAX_MULT_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_FC_Pos                                       14
#define DMAC_DMA_COMP_PARAMS_3_CH2_FC_Msk                                       (0x3U << DMAC_DMA_COMP_PARAMS_3_CH2_FC_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_HC_LLP_Pos                                   13
#define DMAC_DMA_COMP_PARAMS_3_CH2_HC_LLP_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_3_CH2_HC_LLP_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_CTL_WB_EN_Pos                                12
#define DMAC_DMA_COMP_PARAMS_3_CH2_CTL_WB_EN_Msk                                (0x1U << DMAC_DMA_COMP_PARAMS_3_CH2_CTL_WB_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_MULTI_BLK_EN_Pos                             11
#define DMAC_DMA_COMP_PARAMS_3_CH2_MULTI_BLK_EN_Msk                             (0x1U << DMAC_DMA_COMP_PARAMS_3_CH2_MULTI_BLK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_LOCK_EN_Pos                                  10
#define DMAC_DMA_COMP_PARAMS_3_CH2_LOCK_EN_Msk                                  (0x1U << DMAC_DMA_COMP_PARAMS_3_CH2_LOCK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_SRC_GAT_EN_Pos                               9
#define DMAC_DMA_COMP_PARAMS_3_CH2_SRC_GAT_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_3_CH2_SRC_GAT_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_DST_SCA_EN_Pos                               8
#define DMAC_DMA_COMP_PARAMS_3_CH2_DST_SCA_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_3_CH2_DST_SCA_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_STAT_SRC_Pos                                 7
#define DMAC_DMA_COMP_PARAMS_3_CH2_STAT_SRC_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_3_CH2_STAT_SRC_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_STAT_DST_Pos                                 6
#define DMAC_DMA_COMP_PARAMS_3_CH2_STAT_DST_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_3_CH2_STAT_DST_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_STW_Pos                                      3
#define DMAC_DMA_COMP_PARAMS_3_CH2_STW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH2_STW_Pos)

#define DMAC_DMA_COMP_PARAMS_3_CH2_DTW_Pos                                      0
#define DMAC_DMA_COMP_PARAMS_3_CH2_DTW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_3_CH2_DTW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMA_COMP_PARAMS_2
//
#define DMAC_DMA_COMP_PARAMS_2_CH7_MULTI_BLK_TYPE_Pos                           60
#define DMAC_DMA_COMP_PARAMS_2_CH7_MULTI_BLK_TYPE_Msk                           (0xfU << DMAC_DMA_COMP_PARAMS_2_CH7_MULTI_BLK_TYPE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH6_MULTI_BLK_TYPE_Pos                           56
#define DMAC_DMA_COMP_PARAMS_2_CH6_MULTI_BLK_TYPE_Msk                           (0xfU << DMAC_DMA_COMP_PARAMS_2_CH6_MULTI_BLK_TYPE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH5_MULTI_BLK_TYPE_Pos                           52
#define DMAC_DMA_COMP_PARAMS_2_CH5_MULTI_BLK_TYPE_Msk                           (0xfU << DMAC_DMA_COMP_PARAMS_2_CH5_MULTI_BLK_TYPE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH4_MULTI_BLK_TYPE_Pos                           48
#define DMAC_DMA_COMP_PARAMS_2_CH4_MULTI_BLK_TYPE_Msk                           (0xfU << DMAC_DMA_COMP_PARAMS_2_CH4_MULTI_BLK_TYPE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH3_MULTI_BLK_TYPE_Pos                           44
#define DMAC_DMA_COMP_PARAMS_2_CH3_MULTI_BLK_TYPE_Msk                           (0xfU << DMAC_DMA_COMP_PARAMS_2_CH3_MULTI_BLK_TYPE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH2_MULTI_BLK_TYPE_Pos                           40
#define DMAC_DMA_COMP_PARAMS_2_CH2_MULTI_BLK_TYPE_Msk                           (0xfU << DMAC_DMA_COMP_PARAMS_2_CH2_MULTI_BLK_TYPE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH1_MULTI_BLK_TYPE_Pos                           36
#define DMAC_DMA_COMP_PARAMS_2_CH1_MULTI_BLK_TYPE_Msk                           (0xfU << DMAC_DMA_COMP_PARAMS_2_CH1_MULTI_BLK_TYPE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_MULTI_BLK_TYPE_Pos                           32
#define DMAC_DMA_COMP_PARAMS_2_CH0_MULTI_BLK_TYPE_Msk                           (0xfU << DMAC_DMA_COMP_PARAMS_2_CH0_MULTI_BLK_TYPE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_FIFO_DEPTH_Pos                               28
#define DMAC_DMA_COMP_PARAMS_2_CH0_FIFO_DEPTH_Msk                               (0x7U << DMAC_DMA_COMP_PARAMS_2_CH0_FIFO_DEPTH_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_SMS_Pos                                      25
#define DMAC_DMA_COMP_PARAMS_2_CH0_SMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_2_CH0_SMS_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_LMS_Pos                                      22
#define DMAC_DMA_COMP_PARAMS_2_CH0_LMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_2_CH0_LMS_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_DMS_Pos                                      19
#define DMAC_DMA_COMP_PARAMS_2_CH0_DMS_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_2_CH0_DMS_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_MAX_MULT_SIZE_Pos                            16
#define DMAC_DMA_COMP_PARAMS_2_CH0_MAX_MULT_SIZE_Msk                            (0x7U << DMAC_DMA_COMP_PARAMS_2_CH0_MAX_MULT_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_FC_Pos                                       14
#define DMAC_DMA_COMP_PARAMS_2_CH0_FC_Msk                                       (0x3U << DMAC_DMA_COMP_PARAMS_2_CH0_FC_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_HC_LLP_Pos                                   13
#define DMAC_DMA_COMP_PARAMS_2_CH0_HC_LLP_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_2_CH0_HC_LLP_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_CTL_WB_EN_Pos                                12
#define DMAC_DMA_COMP_PARAMS_2_CH0_CTL_WB_EN_Msk                                (0x1U << DMAC_DMA_COMP_PARAMS_2_CH0_CTL_WB_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_MULTI_BLK_EN_Pos                             11
#define DMAC_DMA_COMP_PARAMS_2_CH0_MULTI_BLK_EN_Msk                             (0x1U << DMAC_DMA_COMP_PARAMS_2_CH0_MULTI_BLK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_LOCK_EN_Pos                                  10
#define DMAC_DMA_COMP_PARAMS_2_CH0_LOCK_EN_Msk                                  (0x1U << DMAC_DMA_COMP_PARAMS_2_CH0_LOCK_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_SRC_GAT_EN_Pos                               9
#define DMAC_DMA_COMP_PARAMS_2_CH0_SRC_GAT_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_2_CH0_SRC_GAT_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_DST_SCA_EN_Pos                               8
#define DMAC_DMA_COMP_PARAMS_2_CH0_DST_SCA_EN_Msk                               (0x1U << DMAC_DMA_COMP_PARAMS_2_CH0_DST_SCA_EN_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_STAT_SRC_Pos                                 7
#define DMAC_DMA_COMP_PARAMS_2_CH0_STAT_SRC_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_2_CH0_STAT_SRC_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_STAT_DST_Pos                                 6
#define DMAC_DMA_COMP_PARAMS_2_CH0_STAT_DST_Msk                                 (0x1U << DMAC_DMA_COMP_PARAMS_2_CH0_STAT_DST_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_STW_Pos                                      3
#define DMAC_DMA_COMP_PARAMS_2_CH0_STW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_2_CH0_STW_Pos)

#define DMAC_DMA_COMP_PARAMS_2_CH0_DTW_Pos                                      0
#define DMAC_DMA_COMP_PARAMS_2_CH0_DTW_Msk                                      (0x7U << DMAC_DMA_COMP_PARAMS_2_CH0_DTW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMA_COMP_PARAMS_1
//
#define DMAC_DMA_COMP_PARAMS_1_STATIC_ENDIAN_SELECT_Pos                         61
#define DMAC_DMA_COMP_PARAMS_1_STATIC_ENDIAN_SELECT_Msk                         (0x1U << DMAC_DMA_COMP_PARAMS_1_STATIC_ENDIAN_SELECT_Pos)

#define DMAC_DMA_COMP_PARAMS_1_ADD_ENCODED_PARAMS_Pos                           60
#define DMAC_DMA_COMP_PARAMS_1_ADD_ENCODED_PARAMS_Msk                           (0x1U << DMAC_DMA_COMP_PARAMS_1_ADD_ENCODED_PARAMS_Pos)

#define DMAC_DMA_COMP_PARAMS_1_NUM_HS_INT_Pos                                   55
#define DMAC_DMA_COMP_PARAMS_1_NUM_HS_INT_Msk                                   (0x1fU << DMAC_DMA_COMP_PARAMS_1_NUM_HS_INT_Pos)

#define DMAC_DMA_COMP_PARAMS_1_M1_HDATA_WIDTH_Pos                               53
#define DMAC_DMA_COMP_PARAMS_1_M1_HDATA_WIDTH_Msk                               (0x3U << DMAC_DMA_COMP_PARAMS_1_M1_HDATA_WIDTH_Pos)

#define DMAC_DMA_COMP_PARAMS_1_M2_HDATA_WIDTH_Pos                               51
#define DMAC_DMA_COMP_PARAMS_1_M2_HDATA_WIDTH_Msk                               (0x3U << DMAC_DMA_COMP_PARAMS_1_M2_HDATA_WIDTH_Pos)

#define DMAC_DMA_COMP_PARAMS_1_M3_HDATA_WIDTH_Pos                               49
#define DMAC_DMA_COMP_PARAMS_1_M3_HDATA_WIDTH_Msk                               (0x3U << DMAC_DMA_COMP_PARAMS_1_M3_HDATA_WIDTH_Pos)

#define DMAC_DMA_COMP_PARAMS_1_M4_HDATA_WIDTH_Pos                               47
#define DMAC_DMA_COMP_PARAMS_1_M4_HDATA_WIDTH_Msk                               (0x3U << DMAC_DMA_COMP_PARAMS_1_M4_HDATA_WIDTH_Pos)

#define DMAC_DMA_COMP_PARAMS_1_S_HDATA_WIDTH_Pos                                45
#define DMAC_DMA_COMP_PARAMS_1_S_HDATA_WIDTH_Msk                                (0x3U << DMAC_DMA_COMP_PARAMS_1_S_HDATA_WIDTH_Pos)

#define DMAC_DMA_COMP_PARAMS_1_NUM_MASTER_INT_Pos                               43
#define DMAC_DMA_COMP_PARAMS_1_NUM_MASTER_INT_Msk                               (0x3U << DMAC_DMA_COMP_PARAMS_1_NUM_MASTER_INT_Pos)

#define DMAC_DMA_COMP_PARAMS_1_NUM_CHANNELS_Pos                                 40
#define DMAC_DMA_COMP_PARAMS_1_NUM_CHANNELS_Msk                                 (0x7U << DMAC_DMA_COMP_PARAMS_1_NUM_CHANNELS_Pos)

#define DMAC_DMA_COMP_PARAMS_1_MABRST_Pos                                       35
#define DMAC_DMA_COMP_PARAMS_1_MABRST_Msk                                       (0x1U << DMAC_DMA_COMP_PARAMS_1_MABRST_Pos)

#define DMAC_DMA_COMP_PARAMS_1_INTR_IO_Pos                                      33
#define DMAC_DMA_COMP_PARAMS_1_INTR_IO_Msk                                      (0x3U << DMAC_DMA_COMP_PARAMS_1_INTR_IO_Pos)

#define DMAC_DMA_COMP_PARAMS_1_BIG_ENDIAN_Pos                                   32
#define DMAC_DMA_COMP_PARAMS_1_BIG_ENDIAN_Msk                                   (0x1U << DMAC_DMA_COMP_PARAMS_1_BIG_ENDIAN_Pos)

#define DMAC_DMA_COMP_PARAMS_1_CH7_MAX_BLK_SIZE_Pos                             28
#define DMAC_DMA_COMP_PARAMS_1_CH7_MAX_BLK_SIZE_Msk                             (0xfU << DMAC_DMA_COMP_PARAMS_1_CH7_MAX_BLK_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_1_CH6_MAX_BLK_SIZE_Pos                             24
#define DMAC_DMA_COMP_PARAMS_1_CH6_MAX_BLK_SIZE_Msk                             (0xfU << DMAC_DMA_COMP_PARAMS_1_CH6_MAX_BLK_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_1_CH5_MAX_BLK_SIZE_Pos                             20
#define DMAC_DMA_COMP_PARAMS_1_CH5_MAX_BLK_SIZE_Msk                             (0xfU << DMAC_DMA_COMP_PARAMS_1_CH5_MAX_BLK_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_1_CH4_MAX_BLK_SIZE_Pos                             16
#define DMAC_DMA_COMP_PARAMS_1_CH4_MAX_BLK_SIZE_Msk                             (0xfU << DMAC_DMA_COMP_PARAMS_1_CH4_MAX_BLK_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_1_CH3_MAX_BLK_SIZE_Pos                             12
#define DMAC_DMA_COMP_PARAMS_1_CH3_MAX_BLK_SIZE_Msk                             (0xfU << DMAC_DMA_COMP_PARAMS_1_CH3_MAX_BLK_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_1_CH2_MAX_BLK_SIZE_Pos                             8
#define DMAC_DMA_COMP_PARAMS_1_CH2_MAX_BLK_SIZE_Msk                             (0xfU << DMAC_DMA_COMP_PARAMS_1_CH2_MAX_BLK_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_1_CH1_MAX_BLK_SIZE_Pos                             4
#define DMAC_DMA_COMP_PARAMS_1_CH1_MAX_BLK_SIZE_Msk                             (0xfU << DMAC_DMA_COMP_PARAMS_1_CH1_MAX_BLK_SIZE_Pos)

#define DMAC_DMA_COMP_PARAMS_1_CH0_MAX_BLK_SIZE_Pos                             0
#define DMAC_DMA_COMP_PARAMS_1_CH0_MAX_BLK_SIZE_Msk                             (0xfU << DMAC_DMA_COMP_PARAMS_1_CH0_MAX_BLK_SIZE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMA_COMPONENTID_REGISTER
//
#define DMAC_DMA_COMPONENTID_REGISTER_DMA_COMP_VERSION_Pos                      32
#define DMAC_DMA_COMPONENTID_REGISTER_DMA_COMP_VERSION_Msk                      (0xffffffffU << DMAC_DMA_COMPONENTID_REGISTER_DMA_COMP_VERSION_Pos)

#define DMAC_DMA_COMPONENTID_REGISTER_DMA_COMP_TYPE_Pos                         0
#define DMAC_DMA_COMPONENTID_REGISTER_DMA_COMP_TYPE_Msk                         (0xffffffffU << DMAC_DMA_COMPONENTID_REGISTER_DMA_COMP_TYPE_Pos)

#endif //__WTM2101_DMAC_REGISTER_H_INCLUDED__