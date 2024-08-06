/** Define to Prevent Recursive Inclusion */
#ifndef _OSC_CLOCK_CALIBRATION_H
#define _OSC_CLOCK_CALIBRATION_H


#ifdef __cplusplus
extern "C" {
#endif


#include "pmu.h"
#include "afc.h"
#include "rcc.h"
#include "stdlib.h"

#ifdef __cplusplus
}
#endif

extern uint32_t osc_24m_calibration_start(void);
extern uint32_t osc_320k_calibration_start(void);

#endif