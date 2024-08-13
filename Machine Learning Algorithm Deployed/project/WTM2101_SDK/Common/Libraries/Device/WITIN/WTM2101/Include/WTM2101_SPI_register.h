/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 SPI register.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Sat Aug 21 12:46:34 2021/////////////


#ifndef __WTM2101_SPI_REGISTER_H_INCLUDED__
#define __WTM2101_SPI_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// CTRLR0
//
#define SPI_CTRLR0_RSV_Pos                                                      21
#define SPI_CTRLR0_RSV_Msk                                                      (0x7ffU << SPI_CTRLR0_RSV_Pos)

#define SPI_CTRLR0_DFS_32_Pos                                                   16
#define SPI_CTRLR0_DFS_32_Msk                                                   (0x1fU << SPI_CTRLR0_DFS_32_Pos)

#define SPI_CTRLR0_CFS_Pos                                                      12
#define SPI_CTRLR0_CFS_Msk                                                      (0xfU << SPI_CTRLR0_CFS_Pos)

#define SPI_CTRLR0_SRL_Pos                                                      11
#define SPI_CTRLR0_SRL_Msk                                                      (0x1U << SPI_CTRLR0_SRL_Pos)

#define SPI_CTRLR0_SLV_OE_Pos                                                   10
#define SPI_CTRLR0_SLV_OE_Msk                                                   (0x1U << SPI_CTRLR0_SLV_OE_Pos)

#define SPI_CTRLR0_TMOD_Pos                                                     8
#define SPI_CTRLR0_TMOD_Msk                                                     (0x3U << SPI_CTRLR0_TMOD_Pos)

#define SPI_CTRLR0_SCPOL_Pos                                                    7
#define SPI_CTRLR0_SCPOL_Msk                                                    (0x1U << SPI_CTRLR0_SCPOL_Pos)

#define SPI_CTRLR0_SCPH_Pos                                                     6
#define SPI_CTRLR0_SCPH_Msk                                                     (0x1U << SPI_CTRLR0_SCPH_Pos)

#define SPI_CTRLR0_FRF_Pos                                                      4
#define SPI_CTRLR0_FRF_Msk                                                      (0x3U << SPI_CTRLR0_FRF_Pos)

#define SPI_CTRLR0_DFS_Pos                                                      0
#define SPI_CTRLR0_DFS_Msk                                                      (0xfU << SPI_CTRLR0_DFS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CTRLR1
//
#define SPI_CTRLR1_RSV_Pos                                                      16
#define SPI_CTRLR1_RSV_Msk                                                      (0xffffU << SPI_CTRLR1_RSV_Pos)

#define SPI_CTRLR1_NDF_Pos                                                      0
#define SPI_CTRLR1_NDF_Msk                                                      (0xffffU << SPI_CTRLR1_NDF_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSIENR
//
#define SPI_SSIENR_RSV_Pos                                                      1
#define SPI_SSIENR_RSV_Msk                                                      (0x7fffffffU << SPI_SSIENR_RSV_Pos)

#define SPI_SSIENR_SSI_EN_Pos                                                   0
#define SPI_SSIENR_SSI_EN_Msk                                                   (0x1U << SPI_SSIENR_SSI_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MWCR
//
#define SPI_MWCR_RSV_Pos                                                        3
#define SPI_MWCR_RSV_Msk                                                        (0x1fffffffU << SPI_MWCR_RSV_Pos)

#define SPI_MWCR_MHS_Pos                                                        2
#define SPI_MWCR_MHS_Msk                                                        (0x1U << SPI_MWCR_MHS_Pos)

#define SPI_MWCR_MOD_Pos                                                        1
#define SPI_MWCR_MOD_Msk                                                        (0x1U << SPI_MWCR_MOD_Pos)

#define SPI_MWCR_MWMOD_Pos                                                      0
#define SPI_MWCR_MWMOD_Msk                                                      (0x1U << SPI_MWCR_MWMOD_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SER
//
#define SPI_SER_RSV_Pos                                                         3
#define SPI_SER_RSV_Msk                                                         (0x1fffffffU << SPI_SER_RSV_Pos)

#define SPI_SER_SER_Pos                                                         0
#define SPI_SER_SER_Msk                                                         (0x7U << SPI_SER_SER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// BAUDR
//
#define SPI_BAUDR_RSV_Pos                                                       16
#define SPI_BAUDR_RSV_Msk                                                       (0xffffU << SPI_BAUDR_RSV_Pos)

#define SPI_BAUDR_SCKDV_Pos                                                     0
#define SPI_BAUDR_SCKDV_Msk                                                     (0xffffU << SPI_BAUDR_SCKDV_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TXFTLR
//
#define SPI_TXFTLR_RSV_Pos                                                      3
#define SPI_TXFTLR_RSV_Msk                                                      (0x1fffffffU << SPI_TXFTLR_RSV_Pos)

#define SPI_TXFTLR_TFT_Pos                                                      0
#define SPI_TXFTLR_TFT_Msk                                                      (0x7U << SPI_TXFTLR_TFT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RXFTLR
//
#define SPI_RXFTLR_RSV_Pos                                                      3
#define SPI_RXFTLR_RSV_Msk                                                      (0x1fffffffU << SPI_RXFTLR_RSV_Pos)

#define SPI_RXFTLR_RFT_Pos                                                      0
#define SPI_RXFTLR_RFT_Msk                                                      (0x7U << SPI_RXFTLR_RFT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TXFLR
//
#define SPI_TXFLR_RSV_Pos                                                       4
#define SPI_TXFLR_RSV_Msk                                                       (0xfffffffU << SPI_TXFLR_RSV_Pos)

#define SPI_TXFLR_TXTFL_Pos                                                     0
#define SPI_TXFLR_TXTFL_Msk                                                     (0xfU << SPI_TXFLR_TXTFL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RXFLR
//
#define SPI_RXFLR_RSV_Pos                                                       4
#define SPI_RXFLR_RSV_Msk                                                       (0xfffffffU << SPI_RXFLR_RSV_Pos)

#define SPI_RXFLR_RXTFL_Pos                                                     0
#define SPI_RXFLR_RXTFL_Msk                                                     (0xfU << SPI_RXFLR_RXTFL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SR
//
#define SPI_SR_RSV_Pos                                                          7
#define SPI_SR_RSV_Msk                                                          (0x1ffffffU << SPI_SR_RSV_Pos)

#define SPI_SR_DCOL_Pos                                                         6
#define SPI_SR_DCOL_Msk                                                         (0x1U << SPI_SR_DCOL_Pos)

#define SPI_SR_TXE_Pos                                                          5
#define SPI_SR_TXE_Msk                                                          (0x1U << SPI_SR_TXE_Pos)

#define SPI_SR_RFF_Pos                                                          4
#define SPI_SR_RFF_Msk                                                          (0x1U << SPI_SR_RFF_Pos)

#define SPI_SR_RFNE_Pos                                                         3
#define SPI_SR_RFNE_Msk                                                         (0x1U << SPI_SR_RFNE_Pos)

#define SPI_SR_TFE_Pos                                                          2
#define SPI_SR_TFE_Msk                                                          (0x1U << SPI_SR_TFE_Pos)

#define SPI_SR_TFNF_Pos                                                         1
#define SPI_SR_TFNF_Msk                                                         (0x1U << SPI_SR_TFNF_Pos)

#define SPI_SR_BUSY_Pos                                                         0
#define SPI_SR_BUSY_Msk                                                         (0x1U << SPI_SR_BUSY_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IMR
//
#define SPI_IMR_RSV_Pos                                                         6
#define SPI_IMR_RSV_Msk                                                         (0x3ffffffU << SPI_IMR_RSV_Pos)

#define SPI_IMR_MSTIM_Pos                                                       5
#define SPI_IMR_MSTIM_Msk                                                       (0x1U << SPI_IMR_MSTIM_Pos)

#define SPI_IMR_RXFIM_Pos                                                       4
#define SPI_IMR_RXFIM_Msk                                                       (0x1U << SPI_IMR_RXFIM_Pos)

#define SPI_IMR_RXOIM_Pos                                                       3
#define SPI_IMR_RXOIM_Msk                                                       (0x1U << SPI_IMR_RXOIM_Pos)

#define SPI_IMR_RXUIM_Pos                                                       2
#define SPI_IMR_RXUIM_Msk                                                       (0x1U << SPI_IMR_RXUIM_Pos)

#define SPI_IMR_TXOIM_Pos                                                       1
#define SPI_IMR_TXOIM_Msk                                                       (0x1U << SPI_IMR_TXOIM_Pos)

#define SPI_IMR_TXEIM_Pos                                                       0
#define SPI_IMR_TXEIM_Msk                                                       (0x1U << SPI_IMR_TXEIM_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ISR
//
#define SPI_ISR_RSV_Pos                                                         6
#define SPI_ISR_RSV_Msk                                                         (0x3ffffffU << SPI_ISR_RSV_Pos)

#define SPI_ISR_MSTIS_Pos                                                       5
#define SPI_ISR_MSTIS_Msk                                                       (0x1U << SPI_ISR_MSTIS_Pos)

#define SPI_ISR_RXFIS_Pos                                                       4
#define SPI_ISR_RXFIS_Msk                                                       (0x1U << SPI_ISR_RXFIS_Pos)

#define SPI_ISR_RXOIS_Pos                                                       3
#define SPI_ISR_RXOIS_Msk                                                       (0x1U << SPI_ISR_RXOIS_Pos)

#define SPI_ISR_RXUIS_Pos                                                       2
#define SPI_ISR_RXUIS_Msk                                                       (0x1U << SPI_ISR_RXUIS_Pos)

#define SPI_ISR_TXOIS_Pos                                                       1
#define SPI_ISR_TXOIS_Msk                                                       (0x1U << SPI_ISR_TXOIS_Pos)

#define SPI_ISR_TXEIS_Pos                                                       0
#define SPI_ISR_TXEIS_Msk                                                       (0x1U << SPI_ISR_TXEIS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RISR
//
#define SPI_RISR_RSV_Pos                                                        6
#define SPI_RISR_RSV_Msk                                                        (0x3ffffffU << SPI_RISR_RSV_Pos)

#define SPI_RISR_MSTIR_Pos                                                      5
#define SPI_RISR_MSTIR_Msk                                                      (0x1U << SPI_RISR_MSTIR_Pos)

#define SPI_RISR_RXFIR_Pos                                                      4
#define SPI_RISR_RXFIR_Msk                                                      (0x1U << SPI_RISR_RXFIR_Pos)

#define SPI_RISR_RXOIR_Pos                                                      3
#define SPI_RISR_RXOIR_Msk                                                      (0x1U << SPI_RISR_RXOIR_Pos)

#define SPI_RISR_RXUIR_Pos                                                      2
#define SPI_RISR_RXUIR_Msk                                                      (0x1U << SPI_RISR_RXUIR_Pos)

#define SPI_RISR_TXOIR_Pos                                                      1
#define SPI_RISR_TXOIR_Msk                                                      (0x1U << SPI_RISR_TXOIR_Pos)

#define SPI_RISR_TXEIR_Pos                                                      0
#define SPI_RISR_TXEIR_Msk                                                      (0x1U << SPI_RISR_TXEIR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TXOICR
//
#define SPI_TXOICR_RSV_Pos                                                      1
#define SPI_TXOICR_RSV_Msk                                                      (0x7fffffffU << SPI_TXOICR_RSV_Pos)

#define SPI_TXOICR_TXOICR_Pos                                                   0
#define SPI_TXOICR_TXOICR_Msk                                                   (0x1U << SPI_TXOICR_TXOICR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RXOICR
//
#define SPI_RXOICR_RSV_Pos                                                      1
#define SPI_RXOICR_RSV_Msk                                                      (0x7fffffffU << SPI_RXOICR_RSV_Pos)

#define SPI_RXOICR_RXOICR_Pos                                                   0
#define SPI_RXOICR_RXOICR_Msk                                                   (0x1U << SPI_RXOICR_RXOICR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RXUICR
//
#define SPI_RXUICR_RSV_Pos                                                      1
#define SPI_RXUICR_RSV_Msk                                                      (0x7fffffffU << SPI_RXUICR_RSV_Pos)

#define SPI_RXUICR_RXUICR_Pos                                                   0
#define SPI_RXUICR_RXUICR_Msk                                                   (0x1U << SPI_RXUICR_RXUICR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MSTICR
//
#define SPI_MSTICR_RSV_Pos                                                      1
#define SPI_MSTICR_RSV_Msk                                                      (0x7fffffffU << SPI_MSTICR_RSV_Pos)

#define SPI_MSTICR_MSTICR_Pos                                                   0
#define SPI_MSTICR_MSTICR_Msk                                                   (0x1U << SPI_MSTICR_MSTICR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// ICR
//
#define SPI_ICR_RSV_Pos                                                         1
#define SPI_ICR_RSV_Msk                                                         (0x7fffffffU << SPI_ICR_RSV_Pos)

#define SPI_ICR_ICR_Pos                                                         0
#define SPI_ICR_ICR_Msk                                                         (0x1U << SPI_ICR_ICR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMACR
//
#define SPI_DMACR_RSV_Pos                                                       2
#define SPI_DMACR_RSV_Msk                                                       (0x3fffffffU << SPI_DMACR_RSV_Pos)

#define SPI_DMACR_TDMAE_Pos                                                     1
#define SPI_DMACR_TDMAE_Msk                                                     (0x1U << SPI_DMACR_TDMAE_Pos)

#define SPI_DMACR_RDMAE_Pos                                                     0
#define SPI_DMACR_RDMAE_Msk                                                     (0x1U << SPI_DMACR_RDMAE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMATDLR
//
#define SPI_DMATDLR_RSV_Pos                                                     3
#define SPI_DMATDLR_RSV_Msk                                                     (0x1fffffffU << SPI_DMATDLR_RSV_Pos)

#define SPI_DMATDLR_DMATDL_Pos                                                  0
#define SPI_DMATDLR_DMATDL_Msk                                                  (0x7U << SPI_DMATDLR_DMATDL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMARDLR
//
#define SPI_DMARDLR_RSV_Pos                                                     3
#define SPI_DMARDLR_RSV_Msk                                                     (0x1fffffffU << SPI_DMARDLR_RSV_Pos)

#define SPI_DMARDLR_DMARDL_Pos                                                  0
#define SPI_DMARDLR_DMARDL_Msk                                                  (0x7U << SPI_DMARDLR_DMARDL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IDR
//
#define SPI_IDR_IDCODE_Pos                                                      0
#define SPI_IDR_IDCODE_Msk                                                      (0xffffffffU << SPI_IDR_IDCODE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SSI_COMP_VERSION
//
#define SPI_SSI_COMP_VERSION_SSI_COMP_VERSION_Pos                               0
#define SPI_SSI_COMP_VERSION_SSI_COMP_VERSION_Msk                               (0xffffffffU << SPI_SSI_COMP_VERSION_SSI_COMP_VERSION_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DR0
//
#define SPI_DR0_DR_Pos                                                          0
#define SPI_DR0_DR_Msk                                                          (0xffffffffU << SPI_DR0_DR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DR1
//
#define SPI_DR1_DR_Pos                                                          0
#define SPI_DR1_DR_Msk                                                          (0xffffffffU << SPI_DR1_DR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DR2
//
#define SPI_DR2_DR_Pos                                                          0
#define SPI_DR2_DR_Msk                                                          (0xffffffffU << SPI_DR2_DR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DR3
//
#define SPI_DR3_DR_Pos                                                          0
#define SPI_DR3_DR_Msk                                                          (0xffffffffU << SPI_DR3_DR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DR4
//
#define SPI_DR4_DR_Pos                                                          0
#define SPI_DR4_DR_Msk                                                          (0xffffffffU << SPI_DR4_DR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DR5
//
#define SPI_DR5_DR_Pos                                                          0
#define SPI_DR5_DR_Msk                                                          (0xffffffffU << SPI_DR5_DR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DR6
//
#define SPI_DR6_DR_Pos                                                          0
#define SPI_DR6_DR_Msk                                                          (0xffffffffU << SPI_DR6_DR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DR7
//
#define SPI_DR7_DR_Pos                                                          0
#define SPI_DR7_DR_Msk                                                          (0xffffffffU << SPI_DR7_DR_Pos)

#endif //__WTM2101_SPI_REGISTER_H_INCLUDED__