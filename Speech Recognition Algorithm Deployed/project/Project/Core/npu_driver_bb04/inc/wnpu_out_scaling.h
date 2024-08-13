#ifndef WNPU_OUT_SCALING
#define WNPU_OUT_SCALING

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "net_parse.h"

void wnpu_tab_init(DiffInfo_T *tab, float scale);

void wnpu_tab_set_scale(DiffInfo_T *tab, float scale);

int wnpu_tab_update_data(DiffInfo_T *tab);

void wnpu_tab_write_data(DiffInfo_T *tab);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WNPU_OUT_SCALING