#ifndef  __CNN_FRAMEWORK_H__
#define __CNN_FRAMEWORK_H__
#include "witin_npu_interface.h"
#include "witin_npu_engine.h"
#include "witin_type.h"


int npu_init();

int npu_infer(unsigned char *input, signed char *output);

#endif