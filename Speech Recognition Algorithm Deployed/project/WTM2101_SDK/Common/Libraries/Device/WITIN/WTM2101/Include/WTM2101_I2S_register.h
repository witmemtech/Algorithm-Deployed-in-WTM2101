/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 I2S register.
  * @date    2023-03-20
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Mon Mar 20 11:31:58 2023/////////////


#ifndef __WTM2101_I2S_REGISTER_H_INCLUDED__
#define __WTM2101_I2S_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// IER
//
#define I2S_IER_IEN_Pos                                                         0
#define I2S_IER_IEN_Msk                                                         (0x1U << I2S_IER_IEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IRER
//
#define I2S_IRER_RXEN_Pos                                                       0
#define I2S_IRER_RXEN_Msk                                                       (0x1U << I2S_IRER_RXEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ITER
//
#define I2S_ITER_TXEN_Pos                                                       0
#define I2S_ITER_TXEN_Msk                                                       (0x1U << I2S_ITER_TXEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CER
//
#define I2S_CER_CLKEN_Pos                                                       0
#define I2S_CER_CLKEN_Msk                                                       (0x1U << I2S_CER_CLKEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CCR
//
#define I2S_CCR_WSS_Pos                                                         3
#define I2S_CCR_WSS_Msk                                                         (0x3U << I2S_CCR_WSS_Pos)

#define I2S_CCR_SCLKG_Pos                                                       0
#define I2S_CCR_SCLKG_Msk                                                       (0x7U << I2S_CCR_SCLKG_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RXFFR
//
#define I2S_RXFFR_RXFFR_Pos                                                     0
#define I2S_RXFFR_RXFFR_Msk                                                     (0x1U << I2S_RXFFR_RXFFR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TXFFR
//
#define I2S_TXFFR_TXFFR_Pos                                                     0
#define I2S_TXFFR_TXFFR_Msk                                                     (0x1U << I2S_TXFFR_TXFFR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LRBR0
//
#define I2S_LRBR0_LRBR0_Pos                                                     0
#define I2S_LRBR0_LRBR0_Msk                                                     (0xffffffffU << I2S_LRBR0_LRBR0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LTHR0
//
#define I2S_LTHR0_LTHR0_Pos                                                     0
#define I2S_LTHR0_LTHR0_Msk                                                     (0xffffffffU << I2S_LTHR0_LTHR0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RRBR0
//
#define I2S_RRBR0_RRBR0_Pos                                                     0
#define I2S_RRBR0_RRBR0_Msk                                                     (0xffffffffU << I2S_RRBR0_RRBR0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTHR0
//
#define I2S_RTHR0_RTHR0_Pos                                                     0
#define I2S_RTHR0_RTHR0_Msk                                                     (0xffffffffU << I2S_RTHR0_RTHR0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RER0
//
#define I2S_RER0_RXCHEN0_Pos                                                    0
#define I2S_RER0_RXCHEN0_Msk                                                    (0x1U << I2S_RER0_RXCHEN0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TER0
//
#define I2S_TER0_TXCHEN0_Pos                                                    0
#define I2S_TER0_TXCHEN0_Msk                                                    (0x1U << I2S_TER0_TXCHEN0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RCR0
//
#define I2S_RCR0_WLEN_Pos                                                       0
#define I2S_RCR0_WLEN_Msk                                                       (0x7U << I2S_RCR0_WLEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TCR0
//
#define I2S_TCR0_WLEN_Pos                                                       0
#define I2S_TCR0_WLEN_Msk                                                       (0x7U << I2S_TCR0_WLEN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ISR0
//
#define I2S_ISR0_TXFO_Pos                                                       5
#define I2S_ISR0_TXFO_Msk                                                       (0x1U << I2S_ISR0_TXFO_Pos)

#define I2S_ISR0_TXFE_Pos                                                       4
#define I2S_ISR0_TXFE_Msk                                                       (0x1U << I2S_ISR0_TXFE_Pos)

#define I2S_ISR0_RXFO_Pos                                                       1
#define I2S_ISR0_RXFO_Msk                                                       (0x1U << I2S_ISR0_RXFO_Pos)

#define I2S_ISR0_RXDA_Pos                                                       0
#define I2S_ISR0_RXDA_Msk                                                       (0x1U << I2S_ISR0_RXDA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IMR0
//
#define I2S_IMR0_TXFOM_Pos                                                      5
#define I2S_IMR0_TXFOM_Msk                                                      (0x1U << I2S_IMR0_TXFOM_Pos)

#define I2S_IMR0_TXFEM_Pos                                                      4
#define I2S_IMR0_TXFEM_Msk                                                      (0x1U << I2S_IMR0_TXFEM_Pos)

#define I2S_IMR0_RXFOM_Pos                                                      1
#define I2S_IMR0_RXFOM_Msk                                                      (0x1U << I2S_IMR0_RXFOM_Pos)

#define I2S_IMR0_RXDAM_Pos                                                      0
#define I2S_IMR0_RXDAM_Msk                                                      (0x1U << I2S_IMR0_RXDAM_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ROR0
//
#define I2S_ROR0_RXCHO_Pos                                                      0
#define I2S_ROR0_RXCHO_Msk                                                      (0x1U << I2S_ROR0_RXCHO_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TOR0
//
#define I2S_TOR0_TXCHO_Pos                                                      0
#define I2S_TOR0_TXCHO_Msk                                                      (0x1U << I2S_TOR0_TXCHO_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RFCR0
//
#define I2S_RFCR0_RXCHDT_Pos                                                    0
#define I2S_RFCR0_RXCHDT_Msk                                                    (0xfU << I2S_RFCR0_RXCHDT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TFCR0
//
#define I2S_TFCR0_TXCHET_Pos                                                    0
#define I2S_TFCR0_TXCHET_Msk                                                    (0xfU << I2S_TFCR0_TXCHET_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RFF0
//
#define I2S_RFF0_RXCHFR_Pos                                                     0
#define I2S_RFF0_RXCHFR_Msk                                                     (0x1U << I2S_RFF0_RXCHFR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TFF0
//
#define I2S_TFF0_TXCHFR_Pos                                                     0
#define I2S_TFF0_TXCHFR_Msk                                                     (0x1U << I2S_TFF0_TXCHFR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RXDMA
//
#define I2S_RXDMA_RXDMA_Pos                                                     0
#define I2S_RXDMA_RXDMA_Msk                                                     (0xffffffffU << I2S_RXDMA_RXDMA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RRXDMA
//
#define I2S_RRXDMA_RRXDMA_Pos                                                   0
#define I2S_RRXDMA_RRXDMA_Msk                                                   (0x1U << I2S_RRXDMA_RRXDMA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TXDMA
//
#define I2S_TXDMA_TXDMA_Pos                                                     0
#define I2S_TXDMA_TXDMA_Msk                                                     (0xffffffffU << I2S_TXDMA_TXDMA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RTXDMA
//
#define I2S_RTXDMA_RTXDMA_Pos                                                   0
#define I2S_RTXDMA_RTXDMA_Msk                                                   (0x1U << I2S_RTXDMA_RTXDMA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// I2S_COMP_PARAM_2
//
#define I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_3_Pos                              10
#define I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_3_Msk                              (0x7U << I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_3_Pos)

#define I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_2_Pos                              7
#define I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_2_Msk                              (0x7U << I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_2_Pos)

#define I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_1_Pos                              3
#define I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_1_Msk                              (0x7U << I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_1_Pos)

#define I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_0_Pos                              0
#define I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_0_Msk                              (0x7U << I2S_I2S_COMP_PARAM_2_I2S_RX_WORDSIZE_0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// I2S_COMP_PARAM_1
//
#define I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_3_Pos                              25
#define I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_3_Msk                              (0x7U << I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_3_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_2_Pos                              22
#define I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_2_Msk                              (0x7U << I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_2_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_1_Pos                              19
#define I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_1_Msk                              (0x7U << I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_1_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_0_Pos                              16
#define I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_0_Msk                              (0x7U << I2S_I2S_COMP_PARAM_1_I2S_TX_WORDSIZE_0_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_TX_CHANNELS_Pos                                9
#define I2S_I2S_COMP_PARAM_1_I2S_TX_CHANNELS_Msk                                (0x3U << I2S_I2S_COMP_PARAM_1_I2S_TX_CHANNELS_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_RX_CHANNELS_Pos                                7
#define I2S_I2S_COMP_PARAM_1_I2S_RX_CHANNELS_Msk                                (0x3U << I2S_I2S_COMP_PARAM_1_I2S_RX_CHANNELS_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_RECEIVER_BLOCK_Pos                             6
#define I2S_I2S_COMP_PARAM_1_I2S_RECEIVER_BLOCK_Msk                             (0x1U << I2S_I2S_COMP_PARAM_1_I2S_RECEIVER_BLOCK_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_TRANSMITTER_BLOCK_Pos                          5
#define I2S_I2S_COMP_PARAM_1_I2S_TRANSMITTER_BLOCK_Msk                          (0x1U << I2S_I2S_COMP_PARAM_1_I2S_TRANSMITTER_BLOCK_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_MODE_EN_Pos                                    4
#define I2S_I2S_COMP_PARAM_1_I2S_MODE_EN_Msk                                    (0x1U << I2S_I2S_COMP_PARAM_1_I2S_MODE_EN_Pos)

#define I2S_I2S_COMP_PARAM_1_I2S_FIFO_DEPTH_GLOBAL_Pos                          2
#define I2S_I2S_COMP_PARAM_1_I2S_FIFO_DEPTH_GLOBAL_Msk                          (0x3U << I2S_I2S_COMP_PARAM_1_I2S_FIFO_DEPTH_GLOBAL_Pos)

#define I2S_I2S_COMP_PARAM_1_APB_DATA_WIDTH_Pos                                 0
#define I2S_I2S_COMP_PARAM_1_APB_DATA_WIDTH_Msk                                 (0x3U << I2S_I2S_COMP_PARAM_1_APB_DATA_WIDTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// I2S_COMP_VERSION
//
#define I2S_I2S_COMP_VERSION_I2S_COMP_VERSION_Pos                               0
#define I2S_I2S_COMP_VERSION_I2S_COMP_VERSION_Msk                               (0xffffffffU << I2S_I2S_COMP_VERSION_I2S_COMP_VERSION_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// I2S_MST_SLV_SW
//
#define I2S_I2S_MST_SLV_SW_I2S_MST_SLV_SW_Pos                                   0
#define I2S_I2S_MST_SLV_SW_I2S_MST_SLV_SW_Msk                                   (0x1U << I2S_I2S_MST_SLV_SW_I2S_MST_SLV_SW_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// I2S_COMP_TYPE
//
#define I2S_I2S_COMP_TYPE_I2S_COMP_TYPE_Pos                                     0
#define I2S_I2S_COMP_TYPE_I2S_COMP_TYPE_Msk                                     (0xffffffffU << I2S_I2S_COMP_TYPE_I2S_COMP_TYPE_Pos)

#endif //__WTM2101_I2S_REGISTER_H_INCLUDED__