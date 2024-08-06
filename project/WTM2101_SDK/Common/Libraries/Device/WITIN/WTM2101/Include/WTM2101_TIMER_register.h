/**
  ******************************************************************************
  * @file    reg_file
  * @brief   Header for WTM2101 TIMER register.
  * @date    2023-03-20
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/////////////Mon Mar 20 11:31:58 2023/////////////


#ifndef __WTM2101_TIMER_REGISTER_H_INCLUDED__
#define __WTM2101_TIMER_REGISTER_H_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
//
// TIMER1_LOAD_COUNT_REGISTER
//
#define TIMER_TIMER1_LOAD_COUNT_REGISTER_TIMER1LOAD_COUNT_Pos                   0
#define TIMER_TIMER1_LOAD_COUNT_REGISTER_TIMER1LOAD_COUNT_Msk                   (0xffffffU << TIMER_TIMER1_LOAD_COUNT_REGISTER_TIMER1LOAD_COUNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER2_LOAD_COUNT_REGISTER
//
#define TIMER_TIMER2_LOAD_COUNT_REGISTER_TIMER2LOAD_COUNT_Pos                   0
#define TIMER_TIMER2_LOAD_COUNT_REGISTER_TIMER2LOAD_COUNT_Msk                   (0xffffffU << TIMER_TIMER2_LOAD_COUNT_REGISTER_TIMER2LOAD_COUNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER3_LOAD_COUNT_REGISTER
//
#define TIMER_TIMER3_LOAD_COUNT_REGISTER_TIMER3LOAD_COUNT_Pos                   0
#define TIMER_TIMER3_LOAD_COUNT_REGISTER_TIMER3LOAD_COUNT_Msk                   (0xffffffU << TIMER_TIMER3_LOAD_COUNT_REGISTER_TIMER3LOAD_COUNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER4_LOAD_COUNT_REGISTER
//
#define TIMER_TIMER4_LOAD_COUNT_REGISTER_TIMER4LOAD_COUNT_Pos                   0
#define TIMER_TIMER4_LOAD_COUNT_REGISTER_TIMER4LOAD_COUNT_Msk                   (0xffffffU << TIMER_TIMER4_LOAD_COUNT_REGISTER_TIMER4LOAD_COUNT_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER1_LOAD2_COUNT_REGISTER
//
#define TIMER_TIMER1_LOAD2_COUNT_REGISTER_TIMER1LOAD_COUNT2_Pos                 0
#define TIMER_TIMER1_LOAD2_COUNT_REGISTER_TIMER1LOAD_COUNT2_Msk                 (0xffffffU << TIMER_TIMER1_LOAD2_COUNT_REGISTER_TIMER1LOAD_COUNT2_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER2_LOAD2_COUNT_REGISTER
//
#define TIMER_TIMER2_LOAD2_COUNT_REGISTER_TIMER2LOAD_COUNT2_Pos                 0
#define TIMER_TIMER2_LOAD2_COUNT_REGISTER_TIMER2LOAD_COUNT2_Msk                 (0xffffffU << TIMER_TIMER2_LOAD2_COUNT_REGISTER_TIMER2LOAD_COUNT2_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER3_LOAD2_COUNT_REGISTER
//
#define TIMER_TIMER3_LOAD2_COUNT_REGISTER_TIMER3LOAD_COUNT2_Pos                 0
#define TIMER_TIMER3_LOAD2_COUNT_REGISTER_TIMER3LOAD_COUNT2_Msk                 (0xffffffU << TIMER_TIMER3_LOAD2_COUNT_REGISTER_TIMER3LOAD_COUNT2_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER4_LOAD2_COUNT_REGISTER
//
#define TIMER_TIMER4_LOAD2_COUNT_REGISTER_TIMER4LOAD_COUNT2_Pos                 0
#define TIMER_TIMER4_LOAD2_COUNT_REGISTER_TIMER4LOAD_COUNT2_Msk                 (0xffffffU << TIMER_TIMER4_LOAD2_COUNT_REGISTER_TIMER4LOAD_COUNT2_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER1_CURRENT_VALUE_REGISTER
//
#define TIMER_TIMER1_CURRENT_VALUE_REGISTER_TIMER1_CURRENTVALUE_Pos             0
#define TIMER_TIMER1_CURRENT_VALUE_REGISTER_TIMER1_CURRENTVALUE_Msk             (0xffffffU << TIMER_TIMER1_CURRENT_VALUE_REGISTER_TIMER1_CURRENTVALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER2_CURRENT_VALUE_REGISTER
//
#define TIMER_TIMER2_CURRENT_VALUE_REGISTER_TIMER2_CURRENTVALUE_Pos             0
#define TIMER_TIMER2_CURRENT_VALUE_REGISTER_TIMER2_CURRENTVALUE_Msk             (0xffffffU << TIMER_TIMER2_CURRENT_VALUE_REGISTER_TIMER2_CURRENTVALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER3_CURRENT_VALUE_REGISTER
//
#define TIMER_TIMER3_CURRENT_VALUE_REGISTER_TIMER3_CURRENTVALUE_Pos             0
#define TIMER_TIMER3_CURRENT_VALUE_REGISTER_TIMER3_CURRENTVALUE_Msk             (0xffffffU << TIMER_TIMER3_CURRENT_VALUE_REGISTER_TIMER3_CURRENTVALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER4_CURRENT_VALUE_REGISTER
//
#define TIMER_TIMER4_CURRENT_VALUE_REGISTER_TIMER4_CURRENTVALUE_Pos             0
#define TIMER_TIMER4_CURRENT_VALUE_REGISTER_TIMER4_CURRENTVALUE_Msk             (0xffffffU << TIMER_TIMER4_CURRENT_VALUE_REGISTER_TIMER4_CURRENTVALUE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER1_CONTROL_REGISTER
//
#define TIMER_TIMER1_CONTROL_REGISTER_TIMER_PWM_Pos                             3
#define TIMER_TIMER1_CONTROL_REGISTER_TIMER_PWM_Msk                             (0x1U << TIMER_TIMER1_CONTROL_REGISTER_TIMER_PWM_Pos)

#define TIMER_TIMER1_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Pos                  2
#define TIMER_TIMER1_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Msk                  (0x1U << TIMER_TIMER1_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Pos)

#define TIMER_TIMER1_CONTROL_REGISTER_TIMER_MODE_Pos                            1
#define TIMER_TIMER1_CONTROL_REGISTER_TIMER_MODE_Msk                            (0x1U << TIMER_TIMER1_CONTROL_REGISTER_TIMER_MODE_Pos)

#define TIMER_TIMER1_CONTROL_REGISTER_TIMER_ENABLE_Pos                          0
#define TIMER_TIMER1_CONTROL_REGISTER_TIMER_ENABLE_Msk                          (0x1U << TIMER_TIMER1_CONTROL_REGISTER_TIMER_ENABLE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER2_CONTROL_REGISTER
//
#define TIMER_TIMER2_CONTROL_REGISTER_TIMER_PWM_Pos                             3
#define TIMER_TIMER2_CONTROL_REGISTER_TIMER_PWM_Msk                             (0x1U << TIMER_TIMER2_CONTROL_REGISTER_TIMER_PWM_Pos)

#define TIMER_TIMER2_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Pos                  2
#define TIMER_TIMER2_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Msk                  (0x1U << TIMER_TIMER2_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Pos)

#define TIMER_TIMER2_CONTROL_REGISTER_TIMER_MODE_Pos                            1
#define TIMER_TIMER2_CONTROL_REGISTER_TIMER_MODE_Msk                            (0x1U << TIMER_TIMER2_CONTROL_REGISTER_TIMER_MODE_Pos)

#define TIMER_TIMER2_CONTROL_REGISTER_TIMER_ENABLE_Pos                          0
#define TIMER_TIMER2_CONTROL_REGISTER_TIMER_ENABLE_Msk                          (0x1U << TIMER_TIMER2_CONTROL_REGISTER_TIMER_ENABLE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER3_CONTROL_REGISTER
//
#define TIMER_TIMER3_CONTROL_REGISTER_TIMER_PWM_Pos                             3
#define TIMER_TIMER3_CONTROL_REGISTER_TIMER_PWM_Msk                             (0x1U << TIMER_TIMER3_CONTROL_REGISTER_TIMER_PWM_Pos)

#define TIMER_TIMER3_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Pos                  2
#define TIMER_TIMER3_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Msk                  (0x1U << TIMER_TIMER3_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Pos)

#define TIMER_TIMER3_CONTROL_REGISTER_TIMER_MODE_Pos                            1
#define TIMER_TIMER3_CONTROL_REGISTER_TIMER_MODE_Msk                            (0x1U << TIMER_TIMER3_CONTROL_REGISTER_TIMER_MODE_Pos)

#define TIMER_TIMER3_CONTROL_REGISTER_TIMER_ENABLE_Pos                          0
#define TIMER_TIMER3_CONTROL_REGISTER_TIMER_ENABLE_Msk                          (0x1U << TIMER_TIMER3_CONTROL_REGISTER_TIMER_ENABLE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER4_CONTROL_REGISTER
//
#define TIMER_TIMER4_CONTROL_REGISTER_TIMER_PWM_Pos                             3
#define TIMER_TIMER4_CONTROL_REGISTER_TIMER_PWM_Msk                             (0x1U << TIMER_TIMER4_CONTROL_REGISTER_TIMER_PWM_Pos)

#define TIMER_TIMER4_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Pos                  2
#define TIMER_TIMER4_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Msk                  (0x1U << TIMER_TIMER4_CONTROL_REGISTER_TIMER_INTERRUPT_MASK_Pos)

#define TIMER_TIMER4_CONTROL_REGISTER_TIMER_MODE_Pos                            1
#define TIMER_TIMER4_CONTROL_REGISTER_TIMER_MODE_Msk                            (0x1U << TIMER_TIMER4_CONTROL_REGISTER_TIMER_MODE_Pos)

#define TIMER_TIMER4_CONTROL_REGISTER_TIMER_ENABLE_Pos                          0
#define TIMER_TIMER4_CONTROL_REGISTER_TIMER_ENABLE_Msk                          (0x1U << TIMER_TIMER4_CONTROL_REGISTER_TIMER_ENABLE_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER1_END_OF_INTERRUPT_REGISTER
//
#define TIMER_TIMER1_END_OF_INTERRUPT_REGISTER_TIMER1_EOI_Pos                   0
#define TIMER_TIMER1_END_OF_INTERRUPT_REGISTER_TIMER1_EOI_Msk                   (0x1U << TIMER_TIMER1_END_OF_INTERRUPT_REGISTER_TIMER1_EOI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER2_END_OF_INTERRUPT_REGISTER
//
#define TIMER_TIMER2_END_OF_INTERRUPT_REGISTER_TIMER2_EOI_Pos                   0
#define TIMER_TIMER2_END_OF_INTERRUPT_REGISTER_TIMER2_EOI_Msk                   (0x1U << TIMER_TIMER2_END_OF_INTERRUPT_REGISTER_TIMER2_EOI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER3_END_OF_INTERRUPT_REGISTER
//
#define TIMER_TIMER3_END_OF_INTERRUPT_REGISTER_TIMER3_EOI_Pos                   0
#define TIMER_TIMER3_END_OF_INTERRUPT_REGISTER_TIMER3_EOI_Msk                   (0x1U << TIMER_TIMER3_END_OF_INTERRUPT_REGISTER_TIMER3_EOI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER4_END_OF_INTERRUPT_REGISTER
//
#define TIMER_TIMER4_END_OF_INTERRUPT_REGISTER_TIMER4_EOI_Pos                   0
#define TIMER_TIMER4_END_OF_INTERRUPT_REGISTER_TIMER4_EOI_Msk                   (0x1U << TIMER_TIMER4_END_OF_INTERRUPT_REGISTER_TIMER4_EOI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER1_INTERRUPT_STATUS_REGISTER
//
#define TIMER_TIMER1_INTERRUPT_STATUS_REGISTER_TIMER1_INT_STATUS_Pos            0
#define TIMER_TIMER1_INTERRUPT_STATUS_REGISTER_TIMER1_INT_STATUS_Msk            (0x1U << TIMER_TIMER1_INTERRUPT_STATUS_REGISTER_TIMER1_INT_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER2_INTERRUPT_STATUS_REGISTER
//
#define TIMER_TIMER2_INTERRUPT_STATUS_REGISTER_TIMER2_INT_STATUS_Pos            0
#define TIMER_TIMER2_INTERRUPT_STATUS_REGISTER_TIMER2_INT_STATUS_Msk            (0x1U << TIMER_TIMER2_INTERRUPT_STATUS_REGISTER_TIMER2_INT_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER3_INTERRUPT_STATUS_REGISTER
//
#define TIMER_TIMER3_INTERRUPT_STATUS_REGISTER_TIMER3_INT_STATUS_Pos            0
#define TIMER_TIMER3_INTERRUPT_STATUS_REGISTER_TIMER3_INT_STATUS_Msk            (0x1U << TIMER_TIMER3_INTERRUPT_STATUS_REGISTER_TIMER3_INT_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMER4_INTERRUPT_STATUS_REGISTER
//
#define TIMER_TIMER4_INTERRUPT_STATUS_REGISTER_TIMER4_INT_STATUS_Pos            0
#define TIMER_TIMER4_INTERRUPT_STATUS_REGISTER_TIMER4_INT_STATUS_Msk            (0x1U << TIMER_TIMER4_INTERRUPT_STATUS_REGISTER_TIMER4_INT_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMERS_INTERRUPT_STATUS_REGISTER
//
#define TIMER_TIMERS_INTERRUPT_STATUS_REGISTER_TIMERS_INT_STATUS_Pos            0
#define TIMER_TIMERS_INTERRUPT_STATUS_REGISTER_TIMERS_INT_STATUS_Msk            (0xfU << TIMER_TIMERS_INTERRUPT_STATUS_REGISTER_TIMERS_INT_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMERS_END_OF_INTERRUPT_REGISTER
//
#define TIMER_TIMERS_END_OF_INTERRUPT_REGISTER_TIMERS_EOI_Pos                   0
#define TIMER_TIMERS_END_OF_INTERRUPT_REGISTER_TIMERS_EOI_Msk                   (0xfU << TIMER_TIMERS_END_OF_INTERRUPT_REGISTER_TIMERS_EOI_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMERS_RAW_INTERRUPT_STATUS_REGISTER
//
#define TIMER_TIMERS_RAW_INTERRUPT_STATUS_REGISTER_TIMERS_RAW_INT_STATUS_Pos    0
#define TIMER_TIMERS_RAW_INTERRUPT_STATUS_REGISTER_TIMERS_RAW_INT_STATUS_Msk    (0xfU << TIMER_TIMERS_RAW_INTERRUPT_STATUS_REGISTER_TIMERS_RAW_INT_STATUS_Pos)

////////////////////////////////////////////////////////////////////////////////
//
// TIMERS_COMPONENT_VERSION
//
#define TIMER_TIMERS_COMPONENT_VERSION_TIMERS_COMPONENT_VERSION_Pos             0
#define TIMER_TIMERS_COMPONENT_VERSION_TIMERS_COMPONENT_VERSION_Msk             (0xffffffffU << TIMER_TIMERS_COMPONENT_VERSION_TIMERS_COMPONENT_VERSION_Pos)

#endif //__WTM2101_TIMER_REGISTER_H_INCLUDED__