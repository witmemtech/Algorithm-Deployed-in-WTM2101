#ifndef  __CNN_FRAMEWORK_H__
#define __CNN_FRAMEWORK_H__
#include "witin_npu_interface.h"
#include "witin_npu_engine.h"
#include "witin_type.h"


int npu_init();
void run_net0(unsigned char *input, signed char *output);
void run_net1(unsigned char *input, signed char *output);

#endif