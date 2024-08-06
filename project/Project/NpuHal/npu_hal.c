#include "npu_hal.h"
#include "string.h"
#include "stdio.h"
#include "heap.h"
#include "wtm2101_hal.h"
#include "basic_config.h"
#include "WTM2101.h"
#include "rcc.h"
#include "config_common.h"

#define  NET_MAX     1
#define  NET_IDX_0   0

DataIO_T inputInfo[NET_MAX] = {0};
DataIO_T outputInfo[NET_MAX] = {0};

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

extern void time_debug(int status, char *str);
extern void yield();
void witin_layer_handler(WitinCallBackInfo_T info, WITIN_CALL_TYPE_t type) {
    
#if 0
    if(info.flow_index == 0 && type == LAYER_START) {
        time_debug(0, "in");
    }

    if(info.flow_index == 27 && type == LAYER_END) {
        char test[40] = {0};
        sprintf(test,"flow_%d_round_%d",info.flow_index, info.round_index);
        time_debug(1, test);
    }
#else
    #if 0
    if(type == LAYER_RUN) {
        if(info.net_index == 1 && coroutine_is_enable() && (info.flow_index == 1 || 
              info.flow_index == 3 ||
              info.flow_index == 15 ||
              info.flow_index == 19 || 
              info.flow_index == 20)) {
                  yield();
        } else {
            wnpu_wfi_prepare();
            wnpu_wfi_wait();
            wnpu_wfi_cleanup();
        }
    }
    #endif
#endif
}

int npu_init() {
    memset(&config, 0, sizeof(WITIN_CONFIG_T));
    memset(&hook, 0, sizeof(WITIN_HOOK_T));
    
    config.isUseDiff = 0;
    config.isUseWfi = 0;
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
        while(1){
            printf("npu init err:%d\n",res);
            system_delay_s(2);
        }
    }else{
        printf("npu init ok\n");
    }
    
    wengine_get_input_info(NET_IDX_0, &inputInfo[NET_IDX_0], &intputCount);
    wengine_get_output_info(NET_IDX_0, &outputInfo[NET_IDX_0], &outputCount);

    #if 1
    DataIO_T inputInfo[10] = {0};
    DataIO_T outputInfo[10] = {0};
    int intputCount = 0;
    int outputCount = 0;
    int net_index = 0;
    wengine_get_input_info(net_index, inputInfo, &intputCount);
    wengine_get_output_info(net_index, outputInfo, &outputCount);
    for(int i=0;i<intputCount;i++){
        printf("\ninput:%d inputInfo:\naddr:%d\nlen:%d\nshapes:%d,%d,%d,%d\r\n",i,inputInfo[i].addr,inputInfo[i].len,
               inputInfo[i].shape[0],inputInfo[i].shape[1],inputInfo[i].shape[2],inputInfo[i].shape[3]);
    }
    for(int i=0;i<outputCount;i++){
        printf("\noutput:%d outputInfo:\naddr:%d\nlen:%d\nshapes:%d,%d,%d,%d\r\n",i,outputInfo[i].addr,outputInfo[i].len,
           outputInfo[i].shape[0],outputInfo[i].shape[1],outputInfo[i].shape[2],outputInfo[i].shape[3]);
    }
    #endif

    return res;
}


int npu_infer(unsigned char *input, signed char *output) {

    wengine_set_input_data(&inputInfo[NET_IDX_0], input);
    wengine_process_net(NET_IDX_0,0,0,2);
    wengine_get_output_data(&outputInfo[NET_IDX_0], output);

    return 0;

}
