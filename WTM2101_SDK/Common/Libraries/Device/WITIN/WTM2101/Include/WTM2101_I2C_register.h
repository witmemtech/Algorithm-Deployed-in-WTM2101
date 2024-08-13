/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 I2C register.
  * @date    2023-03-20
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Mon Mar 20 11:31:58 2023/////////////


#ifndef __WTM2101_I2C_REGISTER_H_INCLUDED__
#define __WTM2101_I2C_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// IC_CON
//
#define I2C_IC_CON_STOP_DET_IF_MASTER_ACTIVE_Pos                                10
#define I2C_IC_CON_STOP_DET_IF_MASTER_ACTIVE_Msk                                (0x1U << I2C_IC_CON_STOP_DET_IF_MASTER_ACTIVE_Pos)

#define I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_Pos                                    9
#define I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_Msk                                    (0x1U << I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_Pos)

#define I2C_IC_CON_TX_EMPTY_CTR_Pos                                             8
#define I2C_IC_CON_TX_EMPTY_CTR_Msk                                             (0x1U << I2C_IC_CON_TX_EMPTY_CTR_Pos)

#define I2C_IC_CON_STOP_DET_IFADDRESSED_Pos                                     7
#define I2C_IC_CON_STOP_DET_IFADDRESSED_Msk                                     (0x1U << I2C_IC_CON_STOP_DET_IFADDRESSED_Pos)

#define I2C_IC_CON_IC_SLAVE_DISABLE_Pos                                         6
#define I2C_IC_CON_IC_SLAVE_DISABLE_Msk                                         (0x1U << I2C_IC_CON_IC_SLAVE_DISABLE_Pos)

#define I2C_IC_CON_IC_RESTART_EN_Pos                                            5
#define I2C_IC_CON_IC_RESTART_EN_Msk                                            (0x1U << I2C_IC_CON_IC_RESTART_EN_Pos)

#define I2C_IC_CON_IC_10BITADDR_MASTER_Pos                                      4
#define I2C_IC_CON_IC_10BITADDR_MASTER_Msk                                      (0x1U << I2C_IC_CON_IC_10BITADDR_MASTER_Pos)

#define I2C_IC_CON_IC_10BITADDR_SLAVE_Pos                                       3
#define I2C_IC_CON_IC_10BITADDR_SLAVE_Msk                                       (0x1U << I2C_IC_CON_IC_10BITADDR_SLAVE_Pos)

#define I2C_IC_CON_SPEED_Pos                                                    1
#define I2C_IC_CON_SPEED_Msk                                                    (0x3U << I2C_IC_CON_SPEED_Pos)

#define I2C_IC_CON_MASTER_MODE_Pos                                              0
#define I2C_IC_CON_MASTER_MODE_Msk                                              (0x1U << I2C_IC_CON_MASTER_MODE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_TAR
//
#define I2C_IC_TAR_IC_10BITADDR_MASTER_Pos                                      12
#define I2C_IC_TAR_IC_10BITADDR_MASTER_Msk                                      (0x1U << I2C_IC_TAR_IC_10BITADDR_MASTER_Pos)

#define I2C_IC_TAR_SPECIAL_Pos                                                  11
#define I2C_IC_TAR_SPECIAL_Msk                                                  (0x1U << I2C_IC_TAR_SPECIAL_Pos)

#define I2C_IC_TAR_GC_OR_START_Pos                                              10
#define I2C_IC_TAR_GC_OR_START_Msk                                              (0x1U << I2C_IC_TAR_GC_OR_START_Pos)

#define I2C_IC_TAR_IC_TAR_Pos                                                   0
#define I2C_IC_TAR_IC_TAR_Msk                                                   (0x3ffU << I2C_IC_TAR_IC_TAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_SAR
//
#define I2C_IC_SAR_IC_SAR_Pos                                                   0
#define I2C_IC_SAR_IC_SAR_Msk                                                   (0x3ffU << I2C_IC_SAR_IC_SAR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_DATA_CMD
//
#define I2C_IC_DATA_CMD_FIRST_DATA_BYTE_Pos                                     11
#define I2C_IC_DATA_CMD_FIRST_DATA_BYTE_Msk                                     (0x1U << I2C_IC_DATA_CMD_FIRST_DATA_BYTE_Pos)

#define I2C_IC_DATA_CMD_RESTART_Pos                                             10
#define I2C_IC_DATA_CMD_RESTART_Msk                                             (0x1U << I2C_IC_DATA_CMD_RESTART_Pos)

#define I2C_IC_DATA_CMD_STOP_Pos                                                9
#define I2C_IC_DATA_CMD_STOP_Msk                                                (0x1U << I2C_IC_DATA_CMD_STOP_Pos)

#define I2C_IC_DATA_CMD_CMD_Pos                                                 8
#define I2C_IC_DATA_CMD_CMD_Msk                                                 (0x1U << I2C_IC_DATA_CMD_CMD_Pos)

#define I2C_IC_DATA_CMD_DAT_Pos                                                 0
#define I2C_IC_DATA_CMD_DAT_Msk                                                 (0xffU << I2C_IC_DATA_CMD_DAT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_SS_SCL_HCNT
//
#define I2C_IC_SS_SCL_HCNT_IC_SS_SCL_HCNT_Pos                                   0
#define I2C_IC_SS_SCL_HCNT_IC_SS_SCL_HCNT_Msk                                   (0xffffU << I2C_IC_SS_SCL_HCNT_IC_SS_SCL_HCNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_SS_SCL_LCNT
//
#define I2C_IC_SS_SCL_LCNT_IC_SS_SCL_LCNT_Pos                                   0
#define I2C_IC_SS_SCL_LCNT_IC_SS_SCL_LCNT_Msk                                   (0xffffU << I2C_IC_SS_SCL_LCNT_IC_SS_SCL_LCNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_FS_SCL_HCNT
//
#define I2C_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT_Pos                                   0
#define I2C_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT_Msk                                   (0xffffU << I2C_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_FS_SCL_LCNT
//
#define I2C_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT_Pos                                   0
#define I2C_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT_Msk                                   (0xffffU << I2C_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_INTR_STAT
//
#define I2C_IC_INTR_STAT_R_MST_ON_HOLD_Pos                                      13
#define I2C_IC_INTR_STAT_R_MST_ON_HOLD_Msk                                      (0x1U << I2C_IC_INTR_STAT_R_MST_ON_HOLD_Pos)

#define I2C_IC_INTR_STAT_R_RESTART_DET_Pos                                      12
#define I2C_IC_INTR_STAT_R_RESTART_DET_Msk                                      (0x1U << I2C_IC_INTR_STAT_R_RESTART_DET_Pos)

#define I2C_IC_INTR_STAT_R_GEN_CALL_Pos                                         11
#define I2C_IC_INTR_STAT_R_GEN_CALL_Msk                                         (0x1U << I2C_IC_INTR_STAT_R_GEN_CALL_Pos)

#define I2C_IC_INTR_STAT_R_START_DET_Pos                                        10
#define I2C_IC_INTR_STAT_R_START_DET_Msk                                        (0x1U << I2C_IC_INTR_STAT_R_START_DET_Pos)

#define I2C_IC_INTR_STAT_R_STOP_DET_Pos                                         9
#define I2C_IC_INTR_STAT_R_STOP_DET_Msk                                         (0x1U << I2C_IC_INTR_STAT_R_STOP_DET_Pos)

#define I2C_IC_INTR_STAT_R_ACTIVITY_Pos                                         8
#define I2C_IC_INTR_STAT_R_ACTIVITY_Msk                                         (0x1U << I2C_IC_INTR_STAT_R_ACTIVITY_Pos)

#define I2C_IC_INTR_STAT_R_RX_DONE_Pos                                          7
#define I2C_IC_INTR_STAT_R_RX_DONE_Msk                                          (0x1U << I2C_IC_INTR_STAT_R_RX_DONE_Pos)

#define I2C_IC_INTR_STAT_R_TX_ABRT_Pos                                          6
#define I2C_IC_INTR_STAT_R_TX_ABRT_Msk                                          (0x1U << I2C_IC_INTR_STAT_R_TX_ABRT_Pos)

#define I2C_IC_INTR_STAT_R_RD_REQ_Pos                                           5
#define I2C_IC_INTR_STAT_R_RD_REQ_Msk                                           (0x1U << I2C_IC_INTR_STAT_R_RD_REQ_Pos)

#define I2C_IC_INTR_STAT_R_TX_EMPTY_Pos                                         4
#define I2C_IC_INTR_STAT_R_TX_EMPTY_Msk                                         (0x1U << I2C_IC_INTR_STAT_R_TX_EMPTY_Pos)

#define I2C_IC_INTR_STAT_R_TX_OVER_Pos                                          3
#define I2C_IC_INTR_STAT_R_TX_OVER_Msk                                          (0x1U << I2C_IC_INTR_STAT_R_TX_OVER_Pos)

#define I2C_IC_INTR_STAT_R_RX_FULL_Pos                                          2
#define I2C_IC_INTR_STAT_R_RX_FULL_Msk                                          (0x1U << I2C_IC_INTR_STAT_R_RX_FULL_Pos)

#define I2C_IC_INTR_STAT_R_RX_OVER_Pos                                          1
#define I2C_IC_INTR_STAT_R_RX_OVER_Msk                                          (0x1U << I2C_IC_INTR_STAT_R_RX_OVER_Pos)

#define I2C_IC_INTR_STAT_R_RX_UNDER_Pos                                         0
#define I2C_IC_INTR_STAT_R_RX_UNDER_Msk                                         (0x1U << I2C_IC_INTR_STAT_R_RX_UNDER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_INTR_MASK
//
#define I2C_IC_INTR_MASK_M_MST_ON_HOLD_Pos                                      13
#define I2C_IC_INTR_MASK_M_MST_ON_HOLD_Msk                                      (0x1U << I2C_IC_INTR_MASK_M_MST_ON_HOLD_Pos)

#define I2C_IC_INTR_MASK_M_RESTART_DET_Pos                                      12
#define I2C_IC_INTR_MASK_M_RESTART_DET_Msk                                      (0x1U << I2C_IC_INTR_MASK_M_RESTART_DET_Pos)

#define I2C_IC_INTR_MASK_M_GEN_CALL_Pos                                         11
#define I2C_IC_INTR_MASK_M_GEN_CALL_Msk                                         (0x1U << I2C_IC_INTR_MASK_M_GEN_CALL_Pos)

#define I2C_IC_INTR_MASK_M_START_DET_Pos                                        10
#define I2C_IC_INTR_MASK_M_START_DET_Msk                                        (0x1U << I2C_IC_INTR_MASK_M_START_DET_Pos)

#define I2C_IC_INTR_MASK_M_STOP_DET_Pos                                         9
#define I2C_IC_INTR_MASK_M_STOP_DET_Msk                                         (0x1U << I2C_IC_INTR_MASK_M_STOP_DET_Pos)

#define I2C_IC_INTR_MASK_M_ACTIVITY_Pos                                         8
#define I2C_IC_INTR_MASK_M_ACTIVITY_Msk                                         (0x1U << I2C_IC_INTR_MASK_M_ACTIVITY_Pos)

#define I2C_IC_INTR_MASK_M_RX_DONE_Pos                                          7
#define I2C_IC_INTR_MASK_M_RX_DONE_Msk                                          (0x1U << I2C_IC_INTR_MASK_M_RX_DONE_Pos)

#define I2C_IC_INTR_MASK_M_TX_ABRT_Pos                                          6
#define I2C_IC_INTR_MASK_M_TX_ABRT_Msk                                          (0x1U << I2C_IC_INTR_MASK_M_TX_ABRT_Pos)

#define I2C_IC_INTR_MASK_M_RD_REQ_Pos                                           5
#define I2C_IC_INTR_MASK_M_RD_REQ_Msk                                           (0x1U << I2C_IC_INTR_MASK_M_RD_REQ_Pos)

#define I2C_IC_INTR_MASK_M_TX_EMPTY_Pos                                         4
#define I2C_IC_INTR_MASK_M_TX_EMPTY_Msk                                         (0x1U << I2C_IC_INTR_MASK_M_TX_EMPTY_Pos)

#define I2C_IC_INTR_MASK_M_TX_OVER_Pos                                          3
#define I2C_IC_INTR_MASK_M_TX_OVER_Msk                                          (0x1U << I2C_IC_INTR_MASK_M_TX_OVER_Pos)

#define I2C_IC_INTR_MASK_M_RX_FULL_Pos                                          2
#define I2C_IC_INTR_MASK_M_RX_FULL_Msk                                          (0x1U << I2C_IC_INTR_MASK_M_RX_FULL_Pos)

#define I2C_IC_INTR_MASK_M_RX_OVER_Pos                                          1
#define I2C_IC_INTR_MASK_M_RX_OVER_Msk                                          (0x1U << I2C_IC_INTR_MASK_M_RX_OVER_Pos)

#define I2C_IC_INTR_MASK_M_RX_UNDER_Pos                                         0
#define I2C_IC_INTR_MASK_M_RX_UNDER_Msk                                         (0x1U << I2C_IC_INTR_MASK_M_RX_UNDER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_RAW_INTR_STAT
//
#define I2C_IC_RAW_INTR_STAT_MST_ON_HOLD_Pos                                    13
#define I2C_IC_RAW_INTR_STAT_MST_ON_HOLD_Msk                                    (0x1U << I2C_IC_RAW_INTR_STAT_MST_ON_HOLD_Pos)

#define I2C_IC_RAW_INTR_STAT_RESTART_DET_Pos                                    12
#define I2C_IC_RAW_INTR_STAT_RESTART_DET_Msk                                    (0x1U << I2C_IC_RAW_INTR_STAT_RESTART_DET_Pos)

#define I2C_IC_RAW_INTR_STAT_GEN_CALL_Pos                                       11
#define I2C_IC_RAW_INTR_STAT_GEN_CALL_Msk                                       (0x1U << I2C_IC_RAW_INTR_STAT_GEN_CALL_Pos)

#define I2C_IC_RAW_INTR_STAT_START_DET_Pos                                      10
#define I2C_IC_RAW_INTR_STAT_START_DET_Msk                                      (0x1U << I2C_IC_RAW_INTR_STAT_START_DET_Pos)

#define I2C_IC_RAW_INTR_STAT_STOP_DET_Pos                                       9
#define I2C_IC_RAW_INTR_STAT_STOP_DET_Msk                                       (0x1U << I2C_IC_RAW_INTR_STAT_STOP_DET_Pos)

#define I2C_IC_RAW_INTR_STAT_ACTIVITY_Pos                                       8
#define I2C_IC_RAW_INTR_STAT_ACTIVITY_Msk                                       (0x1U << I2C_IC_RAW_INTR_STAT_ACTIVITY_Pos)

#define I2C_IC_RAW_INTR_STAT_RX_DONE_Pos                                        7
#define I2C_IC_RAW_INTR_STAT_RX_DONE_Msk                                        (0x1U << I2C_IC_RAW_INTR_STAT_RX_DONE_Pos)

#define I2C_IC_RAW_INTR_STAT_TX_ABRT_Pos                                        6
#define I2C_IC_RAW_INTR_STAT_TX_ABRT_Msk                                        (0x1U << I2C_IC_RAW_INTR_STAT_TX_ABRT_Pos)

#define I2C_IC_RAW_INTR_STAT_RD_REQ_Pos                                         5
#define I2C_IC_RAW_INTR_STAT_RD_REQ_Msk                                         (0x1U << I2C_IC_RAW_INTR_STAT_RD_REQ_Pos)

#define I2C_IC_RAW_INTR_STAT_TX_EMPTY_Pos                                       4
#define I2C_IC_RAW_INTR_STAT_TX_EMPTY_Msk                                       (0x1U << I2C_IC_RAW_INTR_STAT_TX_EMPTY_Pos)

#define I2C_IC_RAW_INTR_STAT_TX_OVER_Pos                                        3
#define I2C_IC_RAW_INTR_STAT_TX_OVER_Msk                                        (0x1U << I2C_IC_RAW_INTR_STAT_TX_OVER_Pos)

#define I2C_IC_RAW_INTR_STAT_RX_FULL_Pos                                        2
#define I2C_IC_RAW_INTR_STAT_RX_FULL_Msk                                        (0x1U << I2C_IC_RAW_INTR_STAT_RX_FULL_Pos)

#define I2C_IC_RAW_INTR_STAT_RX_OVER_Pos                                        1
#define I2C_IC_RAW_INTR_STAT_RX_OVER_Msk                                        (0x1U << I2C_IC_RAW_INTR_STAT_RX_OVER_Pos)

#define I2C_IC_RAW_INTR_STAT_RX_UNDER_Pos                                       0
#define I2C_IC_RAW_INTR_STAT_RX_UNDER_Msk                                       (0x1U << I2C_IC_RAW_INTR_STAT_RX_UNDER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_RX_TL
//
#define I2C_IC_RX_TL_RX_TL_Pos                                                  0
#define I2C_IC_RX_TL_RX_TL_Msk                                                  (0xffU << I2C_IC_RX_TL_RX_TL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_TX_TL
//
#define I2C_IC_TX_TL_TX_TL_Pos                                                  0
#define I2C_IC_TX_TL_TX_TL_Msk                                                  (0xffU << I2C_IC_TX_TL_TX_TL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_INTR
//
#define I2C_IC_CLR_INTR_CLR_INTR_Pos                                            0
#define I2C_IC_CLR_INTR_CLR_INTR_Msk                                            (0x1U << I2C_IC_CLR_INTR_CLR_INTR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_RX_UNDER
//
#define I2C_IC_CLR_RX_UNDER_CLR_RX_UNDER_Pos                                    0
#define I2C_IC_CLR_RX_UNDER_CLR_RX_UNDER_Msk                                    (0x1U << I2C_IC_CLR_RX_UNDER_CLR_RX_UNDER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_RX_OVER
//
#define I2C_IC_CLR_RX_OVER_CLR_RX_OVER_Pos                                      0
#define I2C_IC_CLR_RX_OVER_CLR_RX_OVER_Msk                                      (0x1U << I2C_IC_CLR_RX_OVER_CLR_RX_OVER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_TX_OVER
//
#define I2C_IC_CLR_TX_OVER_CLR_TX_OVER_Pos                                      0
#define I2C_IC_CLR_TX_OVER_CLR_TX_OVER_Msk                                      (0x1U << I2C_IC_CLR_TX_OVER_CLR_TX_OVER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_RD_REQ
//
#define I2C_IC_CLR_RD_REQ_CLR_RD_REQ_Pos                                        0
#define I2C_IC_CLR_RD_REQ_CLR_RD_REQ_Msk                                        (0x1U << I2C_IC_CLR_RD_REQ_CLR_RD_REQ_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_TX_ABRT
//
#define I2C_IC_CLR_TX_ABRT_CLR_TX_ABRT_Pos                                      0
#define I2C_IC_CLR_TX_ABRT_CLR_TX_ABRT_Msk                                      (0x1U << I2C_IC_CLR_TX_ABRT_CLR_TX_ABRT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_RX_DONE
//
#define I2C_IC_CLR_RX_DONE_CLR_RX_DONE_Pos                                      0
#define I2C_IC_CLR_RX_DONE_CLR_RX_DONE_Msk                                      (0x1U << I2C_IC_CLR_RX_DONE_CLR_RX_DONE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_ACTIVITY
//
#define I2C_IC_CLR_ACTIVITY_CLR_ACTIVITY_Pos                                    0
#define I2C_IC_CLR_ACTIVITY_CLR_ACTIVITY_Msk                                    (0x1U << I2C_IC_CLR_ACTIVITY_CLR_ACTIVITY_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_STOP_DET
//
#define I2C_IC_CLR_STOP_DET_CLR_STOP_DET_Pos                                    0
#define I2C_IC_CLR_STOP_DET_CLR_STOP_DET_Msk                                    (0x1U << I2C_IC_CLR_STOP_DET_CLR_STOP_DET_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_START_DET
//
#define I2C_IC_CLR_START_DET_CLR_START_DET_Pos                                  0
#define I2C_IC_CLR_START_DET_CLR_START_DET_Msk                                  (0x1U << I2C_IC_CLR_START_DET_CLR_START_DET_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_CLR_GEN_CALL
//
#define I2C_IC_CLR_GEN_CALL_CLR_GEN_CALL_Pos                                    0
#define I2C_IC_CLR_GEN_CALL_CLR_GEN_CALL_Msk                                    (0x1U << I2C_IC_CLR_GEN_CALL_CLR_GEN_CALL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_ENABLE
//
#define I2C_IC_ENABLE_TX_CMD_BLOCK_Pos                                          2
#define I2C_IC_ENABLE_TX_CMD_BLOCK_Msk                                          (0x1U << I2C_IC_ENABLE_TX_CMD_BLOCK_Pos)

#define I2C_IC_ENABLE_ABORT_Pos                                                 1
#define I2C_IC_ENABLE_ABORT_Msk                                                 (0x1U << I2C_IC_ENABLE_ABORT_Pos)

#define I2C_IC_ENABLE_ENABLE_Pos                                                0
#define I2C_IC_ENABLE_ENABLE_Msk                                                (0x1U << I2C_IC_ENABLE_ENABLE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_STATUS
//
#define I2C_IC_STATUS_SLV_HOLD_RX_FIFO_FULL_Pos                                 10
#define I2C_IC_STATUS_SLV_HOLD_RX_FIFO_FULL_Msk                                 (0x1U << I2C_IC_STATUS_SLV_HOLD_RX_FIFO_FULL_Pos)

#define I2C_IC_STATUS_SLV_HOLD_TX_FIFO_EMPTY_Pos                                9
#define I2C_IC_STATUS_SLV_HOLD_TX_FIFO_EMPTY_Msk                                (0x1U << I2C_IC_STATUS_SLV_HOLD_TX_FIFO_EMPTY_Pos)

#define I2C_IC_STATUS_MST_HOLD_RX_FIFO_FULL_Pos                                 8
#define I2C_IC_STATUS_MST_HOLD_RX_FIFO_FULL_Msk                                 (0x1U << I2C_IC_STATUS_MST_HOLD_RX_FIFO_FULL_Pos)

#define I2C_IC_STATUS_MST_HOLD_TX_FIFO_EMPTY_Pos                                7
#define I2C_IC_STATUS_MST_HOLD_TX_FIFO_EMPTY_Msk                                (0x1U << I2C_IC_STATUS_MST_HOLD_TX_FIFO_EMPTY_Pos)

#define I2C_IC_STATUS_SLV_ACTIVITY_Pos                                          6
#define I2C_IC_STATUS_SLV_ACTIVITY_Msk                                          (0x1U << I2C_IC_STATUS_SLV_ACTIVITY_Pos)

#define I2C_IC_STATUS_MST_ACTIVITY_Pos                                          5
#define I2C_IC_STATUS_MST_ACTIVITY_Msk                                          (0x1U << I2C_IC_STATUS_MST_ACTIVITY_Pos)

#define I2C_IC_STATUS_RFF_Pos                                                   4
#define I2C_IC_STATUS_RFF_Msk                                                   (0x1U << I2C_IC_STATUS_RFF_Pos)

#define I2C_IC_STATUS_RFNE_Pos                                                  3
#define I2C_IC_STATUS_RFNE_Msk                                                  (0x1U << I2C_IC_STATUS_RFNE_Pos)

#define I2C_IC_STATUS_TFE_Pos                                                   2
#define I2C_IC_STATUS_TFE_Msk                                                   (0x1U << I2C_IC_STATUS_TFE_Pos)

#define I2C_IC_STATUS_TFNF_Pos                                                  1
#define I2C_IC_STATUS_TFNF_Msk                                                  (0x1U << I2C_IC_STATUS_TFNF_Pos)

#define I2C_IC_STATUS_ACTIVITY_Pos                                              0
#define I2C_IC_STATUS_ACTIVITY_Msk                                              (0x1U << I2C_IC_STATUS_ACTIVITY_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_TXFLR
//
#define I2C_IC_TXFLR_TXFLR_Pos                                                  0
#define I2C_IC_TXFLR_TXFLR_Msk                                                  (0xfU << I2C_IC_TXFLR_TXFLR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_RXFLR
//
#define I2C_IC_RXFLR_RXFLR_Pos                                                  0
#define I2C_IC_RXFLR_RXFLR_Msk                                                  (0xfU << I2C_IC_RXFLR_RXFLR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_SDA_HOLD
//
#define I2C_IC_SDA_HOLD_IC_SDA_RX_HOLD_Pos                                      16
#define I2C_IC_SDA_HOLD_IC_SDA_RX_HOLD_Msk                                      (0xffU << I2C_IC_SDA_HOLD_IC_SDA_RX_HOLD_Pos)

#define I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_Pos                                      0
#define I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_Msk                                      (0xffffU << I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_TX_ABRT_SOURCE
//
#define I2C_IC_TX_ABRT_SOURCE_TX_FLUSH_CNT_Pos                                  23
#define I2C_IC_TX_ABRT_SOURCE_TX_FLUSH_CNT_Msk                                  (0x1ffU << I2C_IC_TX_ABRT_SOURCE_TX_FLUSH_CNT_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_USER_ABRT_Pos                                16
#define I2C_IC_TX_ABRT_SOURCE_ABRT_USER_ABRT_Msk                                (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_USER_ABRT_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_Pos                               15
#define I2C_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_Msk                               (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_Pos                              14
#define I2C_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_Msk                              (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_Pos                          13
#define I2C_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_Msk                          (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ARB_LOST_Pos                                      12
#define I2C_IC_TX_ABRT_SOURCE_ARB_LOST_Msk                                      (0x1U << I2C_IC_TX_ABRT_SOURCE_ARB_LOST_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS_Pos                               11
#define I2C_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS_Msk                               (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_Pos                           10
#define I2C_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_Msk                           (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_Pos                            9
#define I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_Msk                            (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_Pos                               8
#define I2C_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_Msk                               (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_Pos                             7
#define I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_Msk                             (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET_Pos                                6
#define I2C_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET_Msk                                (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ_Pos                               5
#define I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ_Msk                               (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_Pos                              4
#define I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_Msk                              (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_Pos                             3
#define I2C_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_Msk                             (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_Pos                            2
#define I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_Msk                            (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_Pos                            1
#define I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_Msk                            (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_Pos)

#define I2C_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_Pos                            0
#define I2C_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_Msk                            (0x1U << I2C_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_DMA_CR
//
#define I2C_IC_DMA_CR_TDMAE_Pos                                                 1
#define I2C_IC_DMA_CR_TDMAE_Msk                                                 (0x1U << I2C_IC_DMA_CR_TDMAE_Pos)

#define I2C_IC_DMA_CR_RDMAE_Pos                                                 0
#define I2C_IC_DMA_CR_RDMAE_Msk                                                 (0x1U << I2C_IC_DMA_CR_RDMAE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_DMA_TDLR
//
#define I2C_IC_DMA_TDLR_DMATDL_Pos                                              0
#define I2C_IC_DMA_TDLR_DMATDL_Msk                                              (0xfU << I2C_IC_DMA_TDLR_DMATDL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_DMA_RDLR
//
#define I2C_IC_DMA_RDLR_DMARDL_Pos                                              0
#define I2C_IC_DMA_RDLR_DMARDL_Msk                                              (0xfU << I2C_IC_DMA_RDLR_DMARDL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_SDA_SETUP
//
#define I2C_IC_SDA_SETUP_SDA_SETUP_Pos                                          0
#define I2C_IC_SDA_SETUP_SDA_SETUP_Msk                                          (0xffU << I2C_IC_SDA_SETUP_SDA_SETUP_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_ACK_GENERAL_CALL
//
#define I2C_IC_ACK_GENERAL_CALL_ACK_GEN_CALL_Pos                                0
#define I2C_IC_ACK_GENERAL_CALL_ACK_GEN_CALL_Msk                                (0x1U << I2C_IC_ACK_GENERAL_CALL_ACK_GEN_CALL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_ENABLE_STATUS
//
#define I2C_IC_ENABLE_STATUS_SLV_RX_DATA_LOST_Pos                               2
#define I2C_IC_ENABLE_STATUS_SLV_RX_DATA_LOST_Msk                               (0x1U << I2C_IC_ENABLE_STATUS_SLV_RX_DATA_LOST_Pos)

#define I2C_IC_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_Pos                        1
#define I2C_IC_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_Msk                        (0x1U << I2C_IC_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_Pos)

#define I2C_IC_ENABLE_STATUS_IC_EN_Pos                                          0
#define I2C_IC_ENABLE_STATUS_IC_EN_Msk                                          (0x1U << I2C_IC_ENABLE_STATUS_IC_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_FS_SPKLEN
//
#define I2C_IC_FS_SPKLEN_IC_FS_SPKLEN_Pos                                       0
#define I2C_IC_FS_SPKLEN_IC_FS_SPKLEN_Msk                                       (0xffU << I2C_IC_FS_SPKLEN_IC_FS_SPKLEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_COMP_PARAM_1
//
#define I2C_IC_COMP_PARAM_1_TX_BUFFER_DEPTH_Pos                                 16
#define I2C_IC_COMP_PARAM_1_TX_BUFFER_DEPTH_Msk                                 (0xffU << I2C_IC_COMP_PARAM_1_TX_BUFFER_DEPTH_Pos)

#define I2C_IC_COMP_PARAM_1_RX_BUFFER_DEPTH_Pos                                 8
#define I2C_IC_COMP_PARAM_1_RX_BUFFER_DEPTH_Msk                                 (0xffU << I2C_IC_COMP_PARAM_1_RX_BUFFER_DEPTH_Pos)

#define I2C_IC_COMP_PARAM_1_ADD_ENCODED_PARAMS_Pos                              7
#define I2C_IC_COMP_PARAM_1_ADD_ENCODED_PARAMS_Msk                              (0x1U << I2C_IC_COMP_PARAM_1_ADD_ENCODED_PARAMS_Pos)

#define I2C_IC_COMP_PARAM_1_HAS_DMA_Pos                                         6
#define I2C_IC_COMP_PARAM_1_HAS_DMA_Msk                                         (0x1U << I2C_IC_COMP_PARAM_1_HAS_DMA_Pos)

#define I2C_IC_COMP_PARAM_1_INTR_IO_Pos                                         5
#define I2C_IC_COMP_PARAM_1_INTR_IO_Msk                                         (0x1U << I2C_IC_COMP_PARAM_1_INTR_IO_Pos)

#define I2C_IC_COMP_PARAM_1_HC_COUNT_VALUES_Pos                                 4
#define I2C_IC_COMP_PARAM_1_HC_COUNT_VALUES_Msk                                 (0x1U << I2C_IC_COMP_PARAM_1_HC_COUNT_VALUES_Pos)

#define I2C_IC_COMP_PARAM_1_MAX_SPEED_MODE_Pos                                  2
#define I2C_IC_COMP_PARAM_1_MAX_SPEED_MODE_Msk                                  (0x3U << I2C_IC_COMP_PARAM_1_MAX_SPEED_MODE_Pos)

#define I2C_IC_COMP_PARAM_1_APB_DATA_WIDTH_Pos                                  0
#define I2C_IC_COMP_PARAM_1_APB_DATA_WIDTH_Msk                                  (0x3U << I2C_IC_COMP_PARAM_1_APB_DATA_WIDTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_COMP_VERSION
//
#define I2C_IC_COMP_VERSION_IC_COMP_VERSION_Pos                                 0
#define I2C_IC_COMP_VERSION_IC_COMP_VERSION_Msk                                 (0xffffffffU << I2C_IC_COMP_VERSION_IC_COMP_VERSION_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IC_COMP_TYPE
//
#define I2C_IC_COMP_TYPE_IC_COMP_TYPE_Pos                                       0
#define I2C_IC_COMP_TYPE_IC_COMP_TYPE_Msk                                       (0xffffffffU << I2C_IC_COMP_TYPE_IC_COMP_TYPE_Pos)

#endif //__WTM2101_I2C_REGISTER_H_INCLUDED__