#ifndef __WITIN_NPU_CUSTOM_EVENT_H__
#define __WITIN_NPU_CUSTOM_EVENT_H__

#include "witin_type.h"
#include "net_parse.h"

void doCustomEvent(WITIN_MODEL_T *model, Compute_flow_T *flow, Event_T *event, int isClockSwitch);

#endif