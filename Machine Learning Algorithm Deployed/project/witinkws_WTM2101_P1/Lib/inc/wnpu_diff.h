#ifndef __COMPENSATION_H__
#define __COMPENSATION_H__

#include "net_parse.h"



void wnpu_compensate_init(WITIN_MODEL_T *model);
void wnpu_not_compensate_init(WITIN_MODEL_T *model);
void wnpu_compensate_cycles(int frame_index, Net_config_T *netObj);

#endif    //__COMPENSATION_H__
