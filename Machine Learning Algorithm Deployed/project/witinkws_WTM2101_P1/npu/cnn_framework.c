#include "cnn_framework.h"
#include "string.h"
#include "stdio.h"
#include "heap.h"
#include "wtm2101_hal.h"
#include "basic_config.h"
#include "WTM2101.h"
#include "rcc.h"
#include "config_common.h"

DataIO_T inputInfo[2] = {0};
DataIO_T outputInfo[2] = {0};

int intputCount = 0;
int outputCount = 0;
extern char register_data[];
WITIN_CONFIG_T config;
WITIN_HOOK_T hook;

extern void coroutine_enable(void);
extern void coroutine_disable(void);
extern int coroutine_is_enable(void);

extern void wnpu_wfi_prepare(void) ;
extern void wnpu_wfi_wait(void);
extern void wnpu_wfi_cleanup(void);

extern void yield();
void witin_layer_handler(WitinCallBackInfo_T info, WITIN_CALL_TYPE_t type) {

}

int npu_init() {
    memset(&config, 0, sizeof(WITIN_CONFIG_T));
    memset(&hook, 0, sizeof(WITIN_HOOK_T));
    
    config.isUseDiff = 1;
    config.isUseWfi = 1;
    config.isUseDmaTransport = 0;
    config.model_data_addr = (unsigned char *)register_data;
    config.allocFunc = pvPortMalloc;
    config.freeFunc = vPortFree;
    hook.logFunc = printf;
    hook.layerCallBack = witin_layer_handler;
    hook.log_level = LOG_ERROR;

    wengine_set_hook(&hook);

    int res = wengine_init(&config);
    if(res < 0) {
        printf("wengine err\n");
        return -1;
    }else{
        printf("wengine init ok\n");
    }
    
    wengine_get_input_info(0, &inputInfo[0], &intputCount);
    wengine_get_output_info(0, &outputInfo[0], &outputCount);
    wengine_get_input_info(1, &inputInfo[1], &intputCount);
    wengine_get_output_info(1, &outputInfo[1], &outputCount);

    return 0;
}

unsigned char net_input_buffer[512] = {0};
void do_pn(char *input, unsigned char *output){
    for(int i = 0; i < 256; i++) {
        int8_t _tmp = input[i];
        if(_tmp>=0){
            output[i] = _tmp;
            output[i+256] = 0;
        }else{
            output[i] = 0;
            output[i+256] = -_tmp;
        }
    }
}

void run_net0(unsigned char *input, signed char *output) {
    wengine_set_input_data(&inputInfo[0], input);
    wengine_process_net(0,0,0,2);
    wengine_get_output_data(&outputInfo[0], output);
}

void run_net1(unsigned char *input, signed char *output) {
    do_pn(input, net_input_buffer);
    wengine_set_input_data(&inputInfo[1], net_input_buffer);
    wengine_process_net(1,0,0,2);
    wengine_get_output_data(&outputInfo[1], output);
}