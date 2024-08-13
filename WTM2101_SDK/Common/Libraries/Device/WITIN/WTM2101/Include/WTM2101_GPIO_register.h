/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 GPIO register.
  * @date    2023-03-20
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Mon Mar 20 11:31:58 2023/////////////


#ifndef __WTM2101_GPIO_REGISTER_H_INCLUDED__
#define __WTM2101_GPIO_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_SWPORTA_DR
//
#define GPIO_GPIO_SWPORTA_DR_PORT_A_DATA_Pos                                    0
#define GPIO_GPIO_SWPORTA_DR_PORT_A_DATA_Msk                                    (0xfffffU << GPIO_GPIO_SWPORTA_DR_PORT_A_DATA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_SWPORTA_DDR
//
#define GPIO_GPIO_SWPORTA_DDR_PORT_A_DATA_DIRECTION_Pos                         0
#define GPIO_GPIO_SWPORTA_DDR_PORT_A_DATA_DIRECTION_Msk                         (0xfffffU << GPIO_GPIO_SWPORTA_DDR_PORT_A_DATA_DIRECTION_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_INTEN
//
#define GPIO_GPIO_INTEN_INTERRUPT_ENABLE_Pos                                    0
#define GPIO_GPIO_INTEN_INTERRUPT_ENABLE_Msk                                    (0xfffffU << GPIO_GPIO_INTEN_INTERRUPT_ENABLE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_INTMASK
//
#define GPIO_GPIO_INTMASK_INTERRUPT_MASK_Pos                                    0
#define GPIO_GPIO_INTMASK_INTERRUPT_MASK_Msk                                    (0xfffffU << GPIO_GPIO_INTMASK_INTERRUPT_MASK_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_INTTYPE_LEVEL
//
#define GPIO_GPIO_INTTYPE_LEVEL_INTERRUPT_LEVEL_Pos                             0
#define GPIO_GPIO_INTTYPE_LEVEL_INTERRUPT_LEVEL_Msk                             (0xfffffU << GPIO_GPIO_INTTYPE_LEVEL_INTERRUPT_LEVEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_INT_POLARITY
//
#define GPIO_GPIO_INT_POLARITY_INTERRUPT_POLARITY_Pos                           0
#define GPIO_GPIO_INT_POLARITY_INTERRUPT_POLARITY_Msk                           (0xfffffU << GPIO_GPIO_INT_POLARITY_INTERRUPT_POLARITY_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_INTSTATUS
//
#define GPIO_GPIO_INTSTATUS_INTERRUPT_STATUS_OF_PORT_A_Pos                      0
#define GPIO_GPIO_INTSTATUS_INTERRUPT_STATUS_OF_PORT_A_Msk                      (0xfffffU << GPIO_GPIO_INTSTATUS_INTERRUPT_STATUS_OF_PORT_A_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_RAW_INTSTATUS
//
#define GPIO_GPIO_RAW_INTSTATUS_RAW_INTERRUPT_STATUS_Pos                        0
#define GPIO_GPIO_RAW_INTSTATUS_RAW_INTERRUPT_STATUS_Msk                        (0xfffffU << GPIO_GPIO_RAW_INTSTATUS_RAW_INTERRUPT_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_DEBOUNCE
//
#define GPIO_GPIO_DEBOUNCE_DEBOUNCE_ENABLE_Pos                                  0
#define GPIO_GPIO_DEBOUNCE_DEBOUNCE_ENABLE_Msk                                  (0xfffffU << GPIO_GPIO_DEBOUNCE_DEBOUNCE_ENABLE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_PORTA_EOI
//
#define GPIO_GPIO_PORTA_EOI_CLEAR_INTERRUPT_Pos                                 0
#define GPIO_GPIO_PORTA_EOI_CLEAR_INTERRUPT_Msk                                 (0xfffffU << GPIO_GPIO_PORTA_EOI_CLEAR_INTERRUPT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_EXT_PORTA
//
#define GPIO_GPIO_EXT_PORTA_EXTERNAL_PORTA_Pos                                  0
#define GPIO_GPIO_EXT_PORTA_EXTERNAL_PORTA_Msk                                  (0xfffffU << GPIO_GPIO_EXT_PORTA_EXTERNAL_PORTA_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_LS_SYNC
//
#define GPIO_GPIO_LS_SYNC_SYNCHRONIZATION_LEVEL_Pos                             0
#define GPIO_GPIO_LS_SYNC_SYNCHRONIZATION_LEVEL_Msk                             (0x1U << GPIO_GPIO_LS_SYNC_SYNCHRONIZATION_LEVEL_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_ID_CODE
//
#define GPIO_GPIO_ID_CODE_GPIO_ID_CODE_Pos                                      0
#define GPIO_GPIO_ID_CODE_GPIO_ID_CODE_Msk                                      (0xfffffU << GPIO_GPIO_ID_CODE_GPIO_ID_CODE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_INT_BOTHEDGE
//
#define GPIO_GPIO_INT_BOTHEDGE_INTERRUPT_EDGE_TYPE_Pos                          0
#define GPIO_GPIO_INT_BOTHEDGE_INTERRUPT_EDGE_TYPE_Msk                          (0xfffffU << GPIO_GPIO_INT_BOTHEDGE_INTERRUPT_EDGE_TYPE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_VER_ID_CODE
//
#define GPIO_GPIO_VER_ID_CODE_GPIO_COMPONENT_VERSION_Pos                        0
#define GPIO_GPIO_VER_ID_CODE_GPIO_COMPONENT_VERSION_Msk                        (0xffffffffU << GPIO_GPIO_VER_ID_CODE_GPIO_COMPONENT_VERSION_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_CONFIG_REG2
//
#define GPIO_GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_D_Pos                           15
#define GPIO_GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_D_Msk                           (0x1fU << GPIO_GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_D_Pos)

#define GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_C_Pos                              10
#define GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_C_Msk                              (0x1fU << GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_C_Pos)

#define GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_B_Pos                              5
#define GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_B_Msk                              (0x1fU << GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_B_Pos)

#define GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_A_Pos                              0
#define GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_A_Msk                              (0x1fU << GPIO_GPIO_CONFIG_REG2_ENCODED_PWIDTH_A_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_CONFIG_REG1
//
#define GPIO_GPIO_CONFIG_REG1_INTERRUPT_BOTH_EDGE_TYPE_Pos                      21
#define GPIO_GPIO_CONFIG_REG1_INTERRUPT_BOTH_EDGE_TYPE_Msk                      (0x1U << GPIO_GPIO_CONFIG_REG1_INTERRUPT_BOTH_EDGE_TYPE_Pos)

#define GPIO_GPIO_CONFIG_REG1_ENCODED_ID_WIDTH_Pos                              16
#define GPIO_GPIO_CONFIG_REG1_ENCODED_ID_WIDTH_Msk                              (0x1fU << GPIO_GPIO_CONFIG_REG1_ENCODED_ID_WIDTH_Pos)

#define GPIO_GPIO_CONFIG_REG1_GPIO_ID_Pos                                       15
#define GPIO_GPIO_CONFIG_REG1_GPIO_ID_Msk                                       (0x1U << GPIO_GPIO_CONFIG_REG1_GPIO_ID_Pos)

#define GPIO_GPIO_CONFIG_REG1_ADD_ENCODED_PARAMS_Pos                            14
#define GPIO_GPIO_CONFIG_REG1_ADD_ENCODED_PARAMS_Msk                            (0x1U << GPIO_GPIO_CONFIG_REG1_ADD_ENCODED_PARAMS_Pos)

#define GPIO_GPIO_CONFIG_REG1_DEBOUNCE_Pos                                      13
#define GPIO_GPIO_CONFIG_REG1_DEBOUNCE_Msk                                      (0x1U << GPIO_GPIO_CONFIG_REG1_DEBOUNCE_Pos)

#define GPIO_GPIO_CONFIG_REG1_PORTA_INTR_Pos                                    12
#define GPIO_GPIO_CONFIG_REG1_PORTA_INTR_Msk                                    (0x1U << GPIO_GPIO_CONFIG_REG1_PORTA_INTR_Pos)

#define GPIO_GPIO_CONFIG_REG1_HW_PORTD_Pos                                      11
#define GPIO_GPIO_CONFIG_REG1_HW_PORTD_Msk                                      (0x1U << GPIO_GPIO_CONFIG_REG1_HW_PORTD_Pos)

#define GPIO_GPIO_CONFIG_REG1_HW_PORTC_Pos                                      10
#define GPIO_GPIO_CONFIG_REG1_HW_PORTC_Msk                                      (0x1U << GPIO_GPIO_CONFIG_REG1_HW_PORTC_Pos)

#define GPIO_GPIO_CONFIG_REG1_HW_PORTB_Pos                                      9
#define GPIO_GPIO_CONFIG_REG1_HW_PORTB_Msk                                      (0x1U << GPIO_GPIO_CONFIG_REG1_HW_PORTB_Pos)

#define GPIO_GPIO_CONFIG_REG1_HW_PORTA_Pos                                      8
#define GPIO_GPIO_CONFIG_REG1_HW_PORTA_Msk                                      (0x1U << GPIO_GPIO_CONFIG_REG1_HW_PORTA_Pos)

#define GPIO_GPIO_CONFIG_REG1_PORTD_SINGLE_CTL_Pos                              7
#define GPIO_GPIO_CONFIG_REG1_PORTD_SINGLE_CTL_Msk                              (0x1U << GPIO_GPIO_CONFIG_REG1_PORTD_SINGLE_CTL_Pos)

#define GPIO_GPIO_CONFIG_REG1_PORTC_SINGLE_CTL_Pos                              6
#define GPIO_GPIO_CONFIG_REG1_PORTC_SINGLE_CTL_Msk                              (0x1U << GPIO_GPIO_CONFIG_REG1_PORTC_SINGLE_CTL_Pos)

#define GPIO_GPIO_CONFIG_REG1_PORTB_SINGLE_CTL_Pos                              5
#define GPIO_GPIO_CONFIG_REG1_PORTB_SINGLE_CTL_Msk                              (0x1U << GPIO_GPIO_CONFIG_REG1_PORTB_SINGLE_CTL_Pos)

#define GPIO_GPIO_CONFIG_REG1_PORTA_SINGLE_CTL_Pos                              4
#define GPIO_GPIO_CONFIG_REG1_PORTA_SINGLE_CTL_Msk                              (0x1U << GPIO_GPIO_CONFIG_REG1_PORTA_SINGLE_CTL_Pos)

#define GPIO_GPIO_CONFIG_REG1_NUM_PORTS_Pos                                     2
#define GPIO_GPIO_CONFIG_REG1_NUM_PORTS_Msk                                     (0x3U << GPIO_GPIO_CONFIG_REG1_NUM_PORTS_Pos)

#define GPIO_GPIO_CONFIG_REG1_APB_DATA_WIDTH_Pos                                0
#define GPIO_GPIO_CONFIG_REG1_APB_DATA_WIDTH_Msk                                (0x3U << GPIO_GPIO_CONFIG_REG1_APB_DATA_WIDTH_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PULLUP
//
#define GPIO_PULLUP_PULL_UP_Pos                                                 0
#define GPIO_PULLUP_PULL_UP_Msk                                                 (0xfffffU << GPIO_PULLUP_PULL_UP_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PULLDOWN
//
#define GPIO_PULLDOWN_PULL_DOWN_Pos                                             0
#define GPIO_PULLDOWN_PULL_DOWN_Msk                                             (0xfffffU << GPIO_PULLDOWN_PULL_DOWN_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DRV0
//
#define GPIO_DRV0_DRV0_Pos                                                      0
#define GPIO_DRV0_DRV0_Msk                                                      (0xfffffU << GPIO_DRV0_DRV0_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// DRV1
//
#define GPIO_DRV1_DRV1_Pos                                                      0
#define GPIO_DRV1_DRV1_Msk                                                      (0xfffffU << GPIO_DRV1_DRV1_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// PAD_RESV
//
#define GPIO_PAD_RESV_PAD_RESV_Pos                                              0
#define GPIO_PAD_RESV_PAD_RESV_Msk                                              (0xffffU << GPIO_PAD_RESV_PAD_RESV_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_WAKEUP
//
#define GPIO_GPIO_WAKEUP_GPIO_WAKEUP_Pos                                        0
#define GPIO_GPIO_WAKEUP_GPIO_WAKEUP_Msk                                        (0xfffffU << GPIO_GPIO_WAKEUP_GPIO_WAKEUP_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_WAKEUP_EOI
//
#define GPIO_GPIO_WAKEUP_EOI_GPIO_WAKEUP_EOI_Pos                                0
#define GPIO_GPIO_WAKEUP_EOI_GPIO_WAKEUP_EOI_Msk                                (0xffffffU << GPIO_GPIO_WAKEUP_EOI_GPIO_WAKEUP_EOI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// GPIO_TEST_PORT
//
#define GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_VALID_Pos                            16
#define GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_VALID_Msk                            (0xffffU << GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_VALID_Pos)

#define GPIO_GPIO_TEST_PORT_CTRL_BK_ENABLE_Pos                                  8
#define GPIO_GPIO_TEST_PORT_CTRL_BK_ENABLE_Msk                                  (0x1U << GPIO_GPIO_TEST_PORT_CTRL_BK_ENABLE_Pos)

#define GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_DAT_CHOOSE_Pos                       1
#define GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_DAT_CHOOSE_Msk                       (0x7U << GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_DAT_CHOOSE_Pos)

#define GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_16BITS_EN_Pos                        0
#define GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_16BITS_EN_Msk                        (0x1U << GPIO_GPIO_TEST_PORT_GPIO_TEST_PORT_16BITS_EN_Pos)

#endif //__WTM2101_GPIO_REGISTER_H_INCLUDED__