#ifndef __WITIN_NPU_ENGINE__
#define __WITIN_NPU_ENGINE__

#include "witin_type.h"
//version 
char* wengine_get_version(void);

//get bin model len
int wengine_get_bin_model_len(unsigned char *binModel);

//get model info
int wengine_get_model_info(WITIN_MODEL_INFO_T* info);

// get input info 
void wengine_get_input_info(int net_index, DataIO_T *inputArrayAddr, int *count);

// get output info
void wengine_get_output_info(int net_index, DataIO_T *outputArrayAddr, int *count);
 
//set data 
void wengine_set_input_data(DataIO_T * info, unsigned char *inputData);

// get output 
void wengine_get_output_data(DataIO_T *info, char *output);

// npu engine init
int wengine_init(WITIN_CONFIG_T *config);

//npu infer
int wengine_process_net(int netIndex, int isNeedBackOld, int isNeedResumeNew, int adc_time);

//npu deinit
int wengine_deinit();

// set hook
void wengine_set_hook(WITIN_HOOK_T *hook);


//////////////////////////////////////// special api ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

///////////// skip flow i when skip_list[i] =1, parallel run flow i when run flow parallel_list[i]
/////skip list/////          //////parallel_list////////
/* 0           0 */   // flow0 not parallel
/* 1           0 */   // flow1 skip flag set, parallel in flow 0
/* 0           0 */   // flow2 not parallel
/* 1           2 */   // flow3 skip flag set, parallel in flow 2

int wengine_set_skip_and_parallel_list(int net_index, char* skip_list, unsigned char *parallel_list, int count);

//backup regfile
// flag_1_back_0_set 1 back regfile , 0 set regfile
int wengine_backup_or_set_regfile(char *buffer, int len, int flag_1_back_0_set);


#endif