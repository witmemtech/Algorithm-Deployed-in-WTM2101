/**
  ******************************************************************************
  * @file    main.h
  * @brief   Header for main.c module.
  * @date    2023-02-08
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "WTM2101_config.h"
#include "WTM2101.h"
#include "wtm2101_hal.h"
#include "hal_clock.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <basic_config.h>
#include <wtm2101_config.h>
#include <WTM2101.h>
#include <wtm2101_hal.h>
#include "audio.h"
#include "dma.h"
#include "fbank.h"
#include "gpio.h"
#include "i2c.h"
#include "i2s.h"
#include "npu.h"
#include "pmu.h"
#include "rcc.h"
#include "rtc.h"
#include "uart.h"
#include "gpio.h"
#include "wtm2101_mmap.h"
#include "retarget.h"
#include "gpio_config.h"
#include "audio_config.h"
#include "fbank_config.h"
#include "rtc_config.h"
#include "uart_config.h"
#include "uart_tx_dma.h"
#include "uart_rx_dma.h"
#include "spi_config.h"
#include "witin_npu_engine.h"
#include "wnpu_config.h"
#include "riscv_intrinsic.h"
#include "ucontext.h"
#include "ram_ld.h"
#include "heap.h"
#include "LibNPU.h"
#include "witin_npu_interface.h"
#include "hal_i2s.h"
#include "hal_audio.h"
#include "i2c_config.h"
#include "npu_hal.h"
#include "config_common.h"
#include "feature_tools.h"

#if USE_ES8311
#include "ES8311.h"
#endif

#if USE_UART_PROTOCOL
#include "trans_protocol.h"
#endif

extern void time_debug(int status, char *str) ;

#ifdef __cplusplus
}
#endif


#endif
