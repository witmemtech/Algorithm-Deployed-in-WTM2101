/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 QSPI register.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Sat Aug 21 12:46:34 2021/////////////


#ifndef __WTM2101_QSPI_REGISTER_H_INCLUDED__
#define __WTM2101_QSPI_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// DMA_CTRL
//
#define QSPI_DMA_CTRL_WR_WATER_LEVEL_Pos                                        8
#define QSPI_DMA_CTRL_WR_WATER_LEVEL_Msk                                        (0xfU << QSPI_DMA_CTRL_WR_WATER_LEVEL_Pos)

#define QSPI_DMA_CTRL_RD_WATER_LEVEL_Pos                                        4
#define QSPI_DMA_CTRL_RD_WATER_LEVEL_Msk                                        (0xfU << QSPI_DMA_CTRL_RD_WATER_LEVEL_Pos)

#define QSPI_DMA_CTRL_QSPI_WRITE_EN_Pos                                         1
#define QSPI_DMA_CTRL_QSPI_WRITE_EN_Msk                                         (0x1U << QSPI_DMA_CTRL_QSPI_WRITE_EN_Pos)

#define QSPI_DMA_CTRL_QSPI_READ_EN_Pos                                          0
#define QSPI_DMA_CTRL_QSPI_READ_EN_Msk                                          (0x1U << QSPI_DMA_CTRL_QSPI_READ_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// QSPI_CTRL
//
#define QSPI_QSPI_CTRL_SAMPLE_CLK_SEL_Pos                                       22
#define QSPI_QSPI_CTRL_SAMPLE_CLK_SEL_Msk                                       (0x1U << QSPI_QSPI_CTRL_SAMPLE_CLK_SEL_Pos)

#define QSPI_QSPI_CTRL_READ_DELAY_TIME_Pos                                      20
#define QSPI_QSPI_CTRL_READ_DELAY_TIME_Msk                                      (0x3U << QSPI_QSPI_CTRL_READ_DELAY_TIME_Pos)

#define QSPI_QSPI_CTRL_ALSIZE_Pos                                               18
#define QSPI_QSPI_CTRL_ALSIZE_Msk                                               (0x3U << QSPI_QSPI_CTRL_ALSIZE_Pos)

#define QSPI_QSPI_CTRL_ADSIZE_Pos                                               16
#define QSPI_QSPI_CTRL_ADSIZE_Msk                                               (0x3U << QSPI_QSPI_CTRL_ADSIZE_Pos)

#define QSPI_QSPI_CTRL_DUMMY_CYCLE_Pos                                          11
#define QSPI_QSPI_CTRL_DUMMY_CYCLE_Msk                                          (0x1fU << QSPI_QSPI_CTRL_DUMMY_CYCLE_Pos)

#define QSPI_QSPI_CTRL_DMODE_SEL_Pos                                            10
#define QSPI_QSPI_CTRL_DMODE_SEL_Msk                                            (0x1U << QSPI_QSPI_CTRL_DMODE_SEL_Pos)

#define QSPI_QSPI_CTRL_DMODE_Pos                                                8
#define QSPI_QSPI_CTRL_DMODE_Msk                                                (0x3U << QSPI_QSPI_CTRL_DMODE_Pos)

#define QSPI_QSPI_CTRL_ALMODE_Pos                                               6
#define QSPI_QSPI_CTRL_ALMODE_Msk                                               (0x3U << QSPI_QSPI_CTRL_ALMODE_Pos)

#define QSPI_QSPI_CTRL_ADMODE_Pos                                               4
#define QSPI_QSPI_CTRL_ADMODE_Msk                                               (0x3U << QSPI_QSPI_CTRL_ADMODE_Pos)

#define QSPI_QSPI_CTRL_IMODE_Pos                                                2
#define QSPI_QSPI_CTRL_IMODE_Msk                                                (0x3U << QSPI_QSPI_CTRL_IMODE_Pos)

#define QSPI_QSPI_CTRL_SPH_Pos                                                  1
#define QSPI_QSPI_CTRL_SPH_Msk                                                  (0x1U << QSPI_QSPI_CTRL_SPH_Pos)

#define QSPI_QSPI_CTRL_SPO_Pos                                                  0
#define QSPI_QSPI_CTRL_SPO_Msk                                                  (0x1U << QSPI_QSPI_CTRL_SPO_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// QSPI_INS
//
#define QSPI_QSPI_INS_INSTRUCTION_Pos                                           0
#define QSPI_QSPI_INS_INSTRUCTION_Msk                                           (0xffU << QSPI_QSPI_INS_INSTRUCTION_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// QSPI_ADDR
//
#define QSPI_QSPI_ADDR_ADDRESS_Pos                                              0
#define QSPI_QSPI_ADDR_ADDRESS_Msk                                              (0xffffffffU << QSPI_QSPI_ADDR_ADDRESS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// QSPI_ALTER
//
#define QSPI_QSPI_ALTER_ALTERNATE_Pos                                           0
#define QSPI_QSPI_ALTER_ALTERNATE_Msk                                           (0xffffffffU << QSPI_QSPI_ALTER_ALTERNATE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// QSPI_DATA_LENGTH
//
#define QSPI_QSPI_DATA_LENGTH_DATA_LENGTH_Pos                                   0
#define QSPI_QSPI_DATA_LENGTH_DATA_LENGTH_Msk                                   (0x1fffffffU << QSPI_QSPI_DATA_LENGTH_DATA_LENGTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// POLLING_REG
//
#define QSPI_POLLING_REG_RDSR_MASK_Pos                                          8
#define QSPI_POLLING_REG_RDSR_MASK_Msk                                          (0xffU << QSPI_POLLING_REG_RDSR_MASK_Pos)

#define QSPI_POLLING_REG_RDSR_Pos                                               0
#define QSPI_POLLING_REG_RDSR_Msk                                               (0xffU << QSPI_POLLING_REG_RDSR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// AFIFO_STATUS
//
#define QSPI_AFIFO_STATUS_RD_AFIFO_EMPTY_Pos                                    4
#define QSPI_AFIFO_STATUS_RD_AFIFO_EMPTY_Msk                                    (0x1U << QSPI_AFIFO_STATUS_RD_AFIFO_EMPTY_Pos)

#define QSPI_AFIFO_STATUS_RD_AFIFO_ALMOST_FULL_Pos                              3
#define QSPI_AFIFO_STATUS_RD_AFIFO_ALMOST_FULL_Msk                              (0x1U << QSPI_AFIFO_STATUS_RD_AFIFO_ALMOST_FULL_Pos)

#define QSPI_AFIFO_STATUS_RD_AFIFO_FULL_Pos                                     2
#define QSPI_AFIFO_STATUS_RD_AFIFO_FULL_Msk                                     (0x1U << QSPI_AFIFO_STATUS_RD_AFIFO_FULL_Pos)

#define QSPI_AFIFO_STATUS_WR_AFIFO_EMPTY_Pos                                    1
#define QSPI_AFIFO_STATUS_WR_AFIFO_EMPTY_Msk                                    (0x1U << QSPI_AFIFO_STATUS_WR_AFIFO_EMPTY_Pos)

#define QSPI_AFIFO_STATUS_WR_AFIFO_FULL_Pos                                     0
#define QSPI_AFIFO_STATUS_WR_AFIFO_FULL_Msk                                     (0x1U << QSPI_AFIFO_STATUS_WR_AFIFO_FULL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// QSPI_STATUS
//
#define QSPI_QSPI_STATUS_STATE_Pos                                              0
#define QSPI_QSPI_STATUS_STATE_Msk                                              (0x7U << QSPI_QSPI_STATUS_STATE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK_SET
//
#define QSPI_INT_MASK_SET_INT_WRITE_FIFO_EMPTY_MASK_SET_Pos                     4
#define QSPI_INT_MASK_SET_INT_WRITE_FIFO_EMPTY_MASK_SET_Msk                     (0x1U << QSPI_INT_MASK_SET_INT_WRITE_FIFO_EMPTY_MASK_SET_Pos)

#define QSPI_INT_MASK_SET_INT_QSPI_FINISH_MASK_SET_Pos                          3
#define QSPI_INT_MASK_SET_INT_QSPI_FINISH_MASK_SET_Msk                          (0x1U << QSPI_INT_MASK_SET_INT_QSPI_FINISH_MASK_SET_Pos)

#define QSPI_INT_MASK_SET_INT_RDSR_MASK_SET_Pos                                 2
#define QSPI_INT_MASK_SET_INT_RDSR_MASK_SET_Msk                                 (0x1U << QSPI_INT_MASK_SET_INT_RDSR_MASK_SET_Pos)

#define QSPI_INT_MASK_SET_INT_WR_OVERFLOW_MASK_SET_Pos                          1
#define QSPI_INT_MASK_SET_INT_WR_OVERFLOW_MASK_SET_Msk                          (0x1U << QSPI_INT_MASK_SET_INT_WR_OVERFLOW_MASK_SET_Pos)

#define QSPI_INT_MASK_SET_INT_RD_UNDERFLOW_MASK_SET_Pos                         0
#define QSPI_INT_MASK_SET_INT_RD_UNDERFLOW_MASK_SET_Msk                         (0x1U << QSPI_INT_MASK_SET_INT_RD_UNDERFLOW_MASK_SET_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK_CLR
//
#define QSPI_INT_MASK_CLR_INT_WRITE_FIFO_EMPTY_MASK_CLR_Pos                     4
#define QSPI_INT_MASK_CLR_INT_WRITE_FIFO_EMPTY_MASK_CLR_Msk                     (0x1U << QSPI_INT_MASK_CLR_INT_WRITE_FIFO_EMPTY_MASK_CLR_Pos)

#define QSPI_INT_MASK_CLR_INT_QSPI_FINISH_MASK_CLR_Pos                          3
#define QSPI_INT_MASK_CLR_INT_QSPI_FINISH_MASK_CLR_Msk                          (0x1U << QSPI_INT_MASK_CLR_INT_QSPI_FINISH_MASK_CLR_Pos)

#define QSPI_INT_MASK_CLR_INT_RDSR_MASK_CLR_Pos                                 2
#define QSPI_INT_MASK_CLR_INT_RDSR_MASK_CLR_Msk                                 (0x1U << QSPI_INT_MASK_CLR_INT_RDSR_MASK_CLR_Pos)

#define QSPI_INT_MASK_CLR_INT_WR_OVERFLOW_MASK_CLR_Pos                          1
#define QSPI_INT_MASK_CLR_INT_WR_OVERFLOW_MASK_CLR_Msk                          (0x1U << QSPI_INT_MASK_CLR_INT_WR_OVERFLOW_MASK_CLR_Pos)

#define QSPI_INT_MASK_CLR_INT_RD_UNDERFLOW_MASK_CLR_Pos                         0
#define QSPI_INT_MASK_CLR_INT_RD_UNDERFLOW_MASK_CLR_Msk                         (0x1U << QSPI_INT_MASK_CLR_INT_RD_UNDERFLOW_MASK_CLR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_MASK_STATUS
//
#define QSPI_INT_MASK_STATUS_INT_WRITE_FIFO_EMPTY_MASK_STATUS_Pos               4
#define QSPI_INT_MASK_STATUS_INT_WRITE_FIFO_EMPTY_MASK_STATUS_Msk               (0x1U << QSPI_INT_MASK_STATUS_INT_WRITE_FIFO_EMPTY_MASK_STATUS_Pos)

#define QSPI_INT_MASK_STATUS_INT_QSPI_FINISH_MASK_STATUS_Pos                    3
#define QSPI_INT_MASK_STATUS_INT_QSPI_FINISH_MASK_STATUS_Msk                    (0x1U << QSPI_INT_MASK_STATUS_INT_QSPI_FINISH_MASK_STATUS_Pos)

#define QSPI_INT_MASK_STATUS_INT_RDSR_MASK_STATUS_Pos                           2
#define QSPI_INT_MASK_STATUS_INT_RDSR_MASK_STATUS_Msk                           (0x1U << QSPI_INT_MASK_STATUS_INT_RDSR_MASK_STATUS_Pos)

#define QSPI_INT_MASK_STATUS_INT_WR_OVERFLOW_MASK_STATUS_Pos                    1
#define QSPI_INT_MASK_STATUS_INT_WR_OVERFLOW_MASK_STATUS_Msk                    (0x1U << QSPI_INT_MASK_STATUS_INT_WR_OVERFLOW_MASK_STATUS_Pos)

#define QSPI_INT_MASK_STATUS_INT_RD_UNDERFLOW_MASK_STATUS_Pos                   0
#define QSPI_INT_MASK_STATUS_INT_RD_UNDERFLOW_MASK_STATUS_Msk                   (0x1U << QSPI_INT_MASK_STATUS_INT_RD_UNDERFLOW_MASK_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// INT_SR_PENDING
//
#define QSPI_INT_SR_PENDING_INT_WRITE_FIFO_EMPTY_Pos                            4
#define QSPI_INT_SR_PENDING_INT_WRITE_FIFO_EMPTY_Msk                            (0x1U << QSPI_INT_SR_PENDING_INT_WRITE_FIFO_EMPTY_Pos)

#define QSPI_INT_SR_PENDING_INT_QSPI_FINISH_Pos                                 3
#define QSPI_INT_SR_PENDING_INT_QSPI_FINISH_Msk                                 (0x1U << QSPI_INT_SR_PENDING_INT_QSPI_FINISH_Pos)

#define QSPI_INT_SR_PENDING_INT_RDSR_Pos                                        2
#define QSPI_INT_SR_PENDING_INT_RDSR_Msk                                        (0x1U << QSPI_INT_SR_PENDING_INT_RDSR_Pos)

#define QSPI_INT_SR_PENDING_INT_WR_OVERFLOW_Pos                                 1
#define QSPI_INT_SR_PENDING_INT_WR_OVERFLOW_Msk                                 (0x1U << QSPI_INT_SR_PENDING_INT_WR_OVERFLOW_Pos)

#define QSPI_INT_SR_PENDING_INT_RD_UNDERFLOW_Pos                                0
#define QSPI_INT_SR_PENDING_INT_RD_UNDERFLOW_Msk                                (0x1U << QSPI_INT_SR_PENDING_INT_RD_UNDERFLOW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// AFIFO_WDATA
//
#define QSPI_AFIFO_WDATA_AFIFO_WDATA_Pos                                        0
#define QSPI_AFIFO_WDATA_AFIFO_WDATA_Msk                                        (0xffffffffU << QSPI_AFIFO_WDATA_AFIFO_WDATA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// AFIFO_RDATA
//
#define QSPI_AFIFO_RDATA_AFIFO_RDATA_Pos                                        0
#define QSPI_AFIFO_RDATA_AFIFO_RDATA_Msk                                        (0xffffffffU << QSPI_AFIFO_RDATA_AFIFO_RDATA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// QSPI_PULSE
//
#define QSPI_QSPI_PULSE_CLR_AHB_CACHE_Pos                                       6
#define QSPI_QSPI_PULSE_CLR_AHB_CACHE_Msk                                       (0x1U << QSPI_QSPI_PULSE_CLR_AHB_CACHE_Pos)

#define QSPI_QSPI_PULSE_JUMP_TO_STOP_Pos                                        5
#define QSPI_QSPI_PULSE_JUMP_TO_STOP_Msk                                        (0x1U << QSPI_QSPI_PULSE_JUMP_TO_STOP_Pos)

#define QSPI_QSPI_PULSE_MAPPING_CONF_UPDATE_Pos                                 4
#define QSPI_QSPI_PULSE_MAPPING_CONF_UPDATE_Msk                                 (0x1U << QSPI_QSPI_PULSE_MAPPING_CONF_UPDATE_Pos)

#define QSPI_QSPI_PULSE_POLLING_CONF_UPDATE_Pos                                 3
#define QSPI_QSPI_PULSE_POLLING_CONF_UPDATE_Msk                                 (0x1U << QSPI_QSPI_PULSE_POLLING_CONF_UPDATE_Pos)

#define QSPI_QSPI_PULSE_POLLING_ACT_Pos                                         1
#define QSPI_QSPI_PULSE_POLLING_ACT_Msk                                         (0x1U << QSPI_QSPI_PULSE_POLLING_ACT_Pos)

#define QSPI_QSPI_PULSE_INDIRECT_ACT_Pos                                        0
#define QSPI_QSPI_PULSE_INDIRECT_ACT_Msk                                        (0x1U << QSPI_QSPI_PULSE_INDIRECT_ACT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MAPPING_ACT
//
#define QSPI_MAPPING_ACT_MAPPING_ACT_Pos                                        0
#define QSPI_MAPPING_ACT_MAPPING_ACT_Msk                                        (0x1U << QSPI_MAPPING_ACT_MAPPING_ACT_Pos)

#endif //__WTM2101_QSPI_REGISTER_H_INCLUDED__