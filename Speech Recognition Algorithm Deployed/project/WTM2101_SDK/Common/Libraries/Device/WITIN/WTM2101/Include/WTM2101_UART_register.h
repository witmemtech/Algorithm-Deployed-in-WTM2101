/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 UART register.
  * @date    2023-03-20
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Mon Mar 20 11:31:58 2023/////////////


#ifndef __WTM2101_UART_REGISTER_H_INCLUDED__
#define __WTM2101_UART_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// RBR
//
#define UART_RBR_RECEIVE_BUFFER_REGISTER_Pos                                    0
#define UART_RBR_RECEIVE_BUFFER_REGISTER_Msk                                    (0xffU << UART_RBR_RECEIVE_BUFFER_REGISTER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// THR
//
#define UART_THR_TRANSMIT_HOLDING_REGISTER_Pos                                  0
#define UART_THR_TRANSMIT_HOLDING_REGISTER_Msk                                  (0xffU << UART_THR_TRANSMIT_HOLDING_REGISTER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DLL
//
#define UART_DLL_DIVISOR_LATCH_Pos                                              0
#define UART_DLL_DIVISOR_LATCH_Msk                                              (0xffU << UART_DLL_DIVISOR_LATCH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DLH
//
#define UART_DLH_DIVISOR_LATCH_Pos                                              0
#define UART_DLH_DIVISOR_LATCH_Msk                                              (0xffU << UART_DLH_DIVISOR_LATCH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IER
//
#define UART_IER_PTIME_Pos                                                      7
#define UART_IER_PTIME_Msk                                                      (0x1U << UART_IER_PTIME_Pos)

#define UART_IER_EDSSI_Pos                                                      3
#define UART_IER_EDSSI_Msk                                                      (0x1U << UART_IER_EDSSI_Pos)

#define UART_IER_ELSI_Pos                                                       2
#define UART_IER_ELSI_Msk                                                       (0x1U << UART_IER_ELSI_Pos)

#define UART_IER_ETBEI_Pos                                                      1
#define UART_IER_ETBEI_Msk                                                      (0x1U << UART_IER_ETBEI_Pos)

#define UART_IER_ERBFI_Pos                                                      0
#define UART_IER_ERBFI_Msk                                                      (0x1U << UART_IER_ERBFI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// IIR
//
#define UART_IIR_FIFOSE_Pos                                                     6
#define UART_IIR_FIFOSE_Msk                                                     (0x3U << UART_IIR_FIFOSE_Pos)

#define UART_IIR_IID_Pos                                                        0
#define UART_IIR_IID_Msk                                                        (0xfU << UART_IIR_IID_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FCR
//
#define UART_FCR_RT_Pos                                                         6
#define UART_FCR_RT_Msk                                                         (0x3U << UART_FCR_RT_Pos)

#define UART_FCR_TET_Pos                                                        4
#define UART_FCR_TET_Msk                                                        (0x3U << UART_FCR_TET_Pos)

#define UART_FCR_DMAM_Pos                                                       3
#define UART_FCR_DMAM_Msk                                                       (0x1U << UART_FCR_DMAM_Pos)

#define UART_FCR_XFIFOR_Pos                                                     2
#define UART_FCR_XFIFOR_Msk                                                     (0x1U << UART_FCR_XFIFOR_Pos)

#define UART_FCR_RFIFOR_Pos                                                     1
#define UART_FCR_RFIFOR_Msk                                                     (0x1U << UART_FCR_RFIFOR_Pos)

#define UART_FCR_FIFOE_Pos                                                      0
#define UART_FCR_FIFOE_Msk                                                      (0x1U << UART_FCR_FIFOE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LCR
//
#define UART_LCR_DLAB_Pos                                                       7
#define UART_LCR_DLAB_Msk                                                       (0x1U << UART_LCR_DLAB_Pos)

#define UART_LCR_BREAK_Pos                                                      6
#define UART_LCR_BREAK_Msk                                                      (0x1U << UART_LCR_BREAK_Pos)

#define UART_LCR_STICK_PARITY_Pos                                               5
#define UART_LCR_STICK_PARITY_Msk                                               (0x1U << UART_LCR_STICK_PARITY_Pos)

#define UART_LCR_EPS_Pos                                                        4
#define UART_LCR_EPS_Msk                                                        (0x1U << UART_LCR_EPS_Pos)

#define UART_LCR_PEN_Pos                                                        3
#define UART_LCR_PEN_Msk                                                        (0x1U << UART_LCR_PEN_Pos)

#define UART_LCR_STOP_Pos                                                       2
#define UART_LCR_STOP_Msk                                                       (0x1U << UART_LCR_STOP_Pos)

#define UART_LCR_DLS_Pos                                                        0
#define UART_LCR_DLS_Msk                                                        (0x3U << UART_LCR_DLS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MCR
//
#define UART_MCR_SIRE_Pos                                                       6
#define UART_MCR_SIRE_Msk                                                       (0x1U << UART_MCR_SIRE_Pos)

#define UART_MCR_AFCE_Pos                                                       5
#define UART_MCR_AFCE_Msk                                                       (0x1U << UART_MCR_AFCE_Pos)

#define UART_MCR_LB_Pos                                                         4
#define UART_MCR_LB_Msk                                                         (0x1U << UART_MCR_LB_Pos)

#define UART_MCR_OUT2_Pos                                                       3
#define UART_MCR_OUT2_Msk                                                       (0x1U << UART_MCR_OUT2_Pos)

#define UART_MCR_OUT1_Pos                                                       2
#define UART_MCR_OUT1_Msk                                                       (0x1U << UART_MCR_OUT1_Pos)

#define UART_MCR_RTS_Pos                                                        1
#define UART_MCR_RTS_Msk                                                        (0x1U << UART_MCR_RTS_Pos)

#define UART_MCR_DTR_Pos                                                        0
#define UART_MCR_DTR_Msk                                                        (0x1U << UART_MCR_DTR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LSR
//
#define UART_LSR_RFE_Pos                                                        7
#define UART_LSR_RFE_Msk                                                        (0x1U << UART_LSR_RFE_Pos)

#define UART_LSR_TEMT_Pos                                                       6
#define UART_LSR_TEMT_Msk                                                       (0x1U << UART_LSR_TEMT_Pos)

#define UART_LSR_THRE_Pos                                                       5
#define UART_LSR_THRE_Msk                                                       (0x1U << UART_LSR_THRE_Pos)

#define UART_LSR_BI_Pos                                                         4
#define UART_LSR_BI_Msk                                                         (0x1U << UART_LSR_BI_Pos)

#define UART_LSR_FE_Pos                                                         3
#define UART_LSR_FE_Msk                                                         (0x1U << UART_LSR_FE_Pos)

#define UART_LSR_PE_Pos                                                         2
#define UART_LSR_PE_Msk                                                         (0x1U << UART_LSR_PE_Pos)

#define UART_LSR_OE_Pos                                                         1
#define UART_LSR_OE_Msk                                                         (0x1U << UART_LSR_OE_Pos)

#define UART_LSR_DR_Pos                                                         0
#define UART_LSR_DR_Msk                                                         (0x1U << UART_LSR_DR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// MSR
//
#define UART_MSR_DCD_Pos                                                        7
#define UART_MSR_DCD_Msk                                                        (0x1U << UART_MSR_DCD_Pos)

#define UART_MSR_RI_Pos                                                         6
#define UART_MSR_RI_Msk                                                         (0x1U << UART_MSR_RI_Pos)

#define UART_MSR_DSR_Pos                                                        5
#define UART_MSR_DSR_Msk                                                        (0x1U << UART_MSR_DSR_Pos)

#define UART_MSR_CTS_Pos                                                        4
#define UART_MSR_CTS_Msk                                                        (0x1U << UART_MSR_CTS_Pos)

#define UART_MSR_DDCD_Pos                                                       3
#define UART_MSR_DDCD_Msk                                                       (0x1U << UART_MSR_DDCD_Pos)

#define UART_MSR_TERI_Pos                                                       2
#define UART_MSR_TERI_Msk                                                       (0x1U << UART_MSR_TERI_Pos)

#define UART_MSR_DDSR_Pos                                                       1
#define UART_MSR_DDSR_Msk                                                       (0x1U << UART_MSR_DDSR_Pos)

#define UART_MSR_DCTS_Pos                                                       0
#define UART_MSR_DCTS_Msk                                                       (0x1U << UART_MSR_DCTS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SCR
//
#define UART_SCR_SCRATCHPAD_REGISTER_Pos                                        0
#define UART_SCR_SCRATCHPAD_REGISTER_Msk                                        (0xffU << UART_SCR_SCRATCHPAD_REGISTER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LPDLL
//
#define UART_LPDLL_LPDLL_Pos                                                    0
#define UART_LPDLL_LPDLL_Msk                                                    (0xffU << UART_LPDLL_LPDLL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// LPDLH
//
#define UART_LPDLH_LPDLH_Pos                                                    0
#define UART_LPDLH_LPDLH_Msk                                                    (0xffU << UART_LPDLH_LPDLH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// FAR
//
#define UART_FAR_FIFO_ACCESS_REGISTER_Pos                                       0
#define UART_FAR_FIFO_ACCESS_REGISTER_Msk                                       (0x1U << UART_FAR_FIFO_ACCESS_REGISTER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TFR
//
#define UART_TFR_TRANSMIT_FIFO_READ_Pos                                         0
#define UART_TFR_TRANSMIT_FIFO_READ_Msk                                         (0xffU << UART_TFR_TRANSMIT_FIFO_READ_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RFW
//
#define UART_RFW_RFFE_Pos                                                       9
#define UART_RFW_RFFE_Msk                                                       (0x1U << UART_RFW_RFFE_Pos)

#define UART_RFW_RFPE_Pos                                                       8
#define UART_RFW_RFPE_Msk                                                       (0x1U << UART_RFW_RFPE_Pos)

#define UART_RFW_RFWD_Pos                                                       0
#define UART_RFW_RFWD_Msk                                                       (0xffU << UART_RFW_RFWD_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// USR
//
#define UART_USR_RFF_Pos                                                        4
#define UART_USR_RFF_Msk                                                        (0x1U << UART_USR_RFF_Pos)

#define UART_USR_RFNE_Pos                                                       3
#define UART_USR_RFNE_Msk                                                       (0x1U << UART_USR_RFNE_Pos)

#define UART_USR_TFE_Pos                                                        2
#define UART_USR_TFE_Msk                                                        (0x1U << UART_USR_TFE_Pos)

#define UART_USR_TFNF_Pos                                                       1
#define UART_USR_TFNF_Msk                                                       (0x1U << UART_USR_TFNF_Pos)

#define UART_USR_BUSY_Pos                                                       0
#define UART_USR_BUSY_Msk                                                       (0x1U << UART_USR_BUSY_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TFL
//
#define UART_TFL_TRANSMIT_FIFO_LEVEL_Pos                                        0
#define UART_TFL_TRANSMIT_FIFO_LEVEL_Msk                                        (0x1fU << UART_TFL_TRANSMIT_FIFO_LEVEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// RFL
//
#define UART_RFL_RECEIVE_FIFO_LEVEL_Pos                                         0
#define UART_RFL_RECEIVE_FIFO_LEVEL_Msk                                         (0x1fU << UART_RFL_RECEIVE_FIFO_LEVEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SRR
//
#define UART_SRR_XFR_Pos                                                        2
#define UART_SRR_XFR_Msk                                                        (0x1U << UART_SRR_XFR_Pos)

#define UART_SRR_RFR_Pos                                                        1
#define UART_SRR_RFR_Msk                                                        (0x1U << UART_SRR_RFR_Pos)

#define UART_SRR_UR_Pos                                                         0
#define UART_SRR_UR_Msk                                                         (0x1U << UART_SRR_UR_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SRTS
//
#define UART_SRTS_SHADOW_REQUEST_TO_SEND_Pos                                    0
#define UART_SRTS_SHADOW_REQUEST_TO_SEND_Msk                                    (0x1U << UART_SRTS_SHADOW_REQUEST_TO_SEND_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SBCR
//
#define UART_SBCR_SHADOW_BREAK_CONTROL_REG_Pos                                  0
#define UART_SBCR_SHADOW_BREAK_CONTROL_REG_Msk                                  (0x1U << UART_SBCR_SHADOW_BREAK_CONTROL_REG_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SDMAM
//
#define UART_SDMAM_SHADOW_DMA_MODE_Pos                                          0
#define UART_SDMAM_SHADOW_DMA_MODE_Msk                                          (0x1U << UART_SDMAM_SHADOW_DMA_MODE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SFE
//
#define UART_SFE_SHADOW_FIFO_ENABLE_Pos                                         0
#define UART_SFE_SHADOW_FIFO_ENABLE_Msk                                         (0x1U << UART_SFE_SHADOW_FIFO_ENABLE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// SRT
//
#define UART_SRT_SHADOW_RCVR_TRIGGER_Pos                                        0
#define UART_SRT_SHADOW_RCVR_TRIGGER_Msk                                        (0x3U << UART_SRT_SHADOW_RCVR_TRIGGER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// STET
//
#define UART_STET_SHADOW_TX_EMPTY_TRIGGER_Pos                                   0
#define UART_STET_SHADOW_TX_EMPTY_TRIGGER_Msk                                   (0x3U << UART_STET_SHADOW_TX_EMPTY_TRIGGER_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// HTX
//
#define UART_HTX_HALT_TX_Pos                                                    0
#define UART_HTX_HALT_TX_Msk                                                    (0x1U << UART_HTX_HALT_TX_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DMASA
//
#define UART_DMASA_DMA_SOFTWARE_ACKNOWLEDGE_Pos                                 0
#define UART_DMASA_DMA_SOFTWARE_ACKNOWLEDGE_Msk                                 (0x1U << UART_DMASA_DMA_SOFTWARE_ACKNOWLEDGE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CPR
//
#define UART_CPR_FIFO_MODE_Pos                                                  16
#define UART_CPR_FIFO_MODE_Msk                                                  (0xffU << UART_CPR_FIFO_MODE_Pos)

#define UART_CPR_DMA_EXTRA_Pos                                                  13
#define UART_CPR_DMA_EXTRA_Msk                                                  (0x1U << UART_CPR_DMA_EXTRA_Pos)

#define UART_CPR_UART_ADD_ENCODED_PARAMS_Pos                                    12
#define UART_CPR_UART_ADD_ENCODED_PARAMS_Msk                                    (0x1U << UART_CPR_UART_ADD_ENCODED_PARAMS_Pos)

#define UART_CPR_SHADOW_Pos                                                     11
#define UART_CPR_SHADOW_Msk                                                     (0x1U << UART_CPR_SHADOW_Pos)

#define UART_CPR_FIFO_STAT_Pos                                                  10
#define UART_CPR_FIFO_STAT_Msk                                                  (0x1U << UART_CPR_FIFO_STAT_Pos)

#define UART_CPR_FIFO_ACCESS_Pos                                                9
#define UART_CPR_FIFO_ACCESS_Msk                                                (0x1U << UART_CPR_FIFO_ACCESS_Pos)

#define UART_CPR_NEW_FEAT_Pos                                                   8
#define UART_CPR_NEW_FEAT_Msk                                                   (0x1U << UART_CPR_NEW_FEAT_Pos)

#define UART_CPR_SIR_LP_MODE_Pos                                                7
#define UART_CPR_SIR_LP_MODE_Msk                                                (0x1U << UART_CPR_SIR_LP_MODE_Pos)

#define UART_CPR_SIR_MODE_Pos                                                   6
#define UART_CPR_SIR_MODE_Msk                                                   (0x1U << UART_CPR_SIR_MODE_Pos)

#define UART_CPR_THRE_MODE_Pos                                                  5
#define UART_CPR_THRE_MODE_Msk                                                  (0x1U << UART_CPR_THRE_MODE_Pos)

#define UART_CPR_AFCE_MODE_Pos                                                  4
#define UART_CPR_AFCE_MODE_Msk                                                  (0x1U << UART_CPR_AFCE_MODE_Pos)

#define UART_CPR_APB_DATA_WIDTH_Pos                                             0
#define UART_CPR_APB_DATA_WIDTH_Msk                                             (0x3U << UART_CPR_APB_DATA_WIDTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// UCV
//
#define UART_UCV_UART_COMPONENT_VERSION_Pos                                     0
#define UART_UCV_UART_COMPONENT_VERSION_Msk                                     (0xffffffffU << UART_UCV_UART_COMPONENT_VERSION_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// CTR
//
#define UART_CTR_PERIPHERAL_ID_Pos                                              0
#define UART_CTR_PERIPHERAL_ID_Msk                                              (0xffffffffU << UART_CTR_PERIPHERAL_ID_Pos)

#endif //__WTM2101_UART_REGISTER_H_INCLUDED__