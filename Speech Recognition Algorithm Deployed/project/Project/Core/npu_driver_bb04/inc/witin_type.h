#ifndef __WITIN_TYPE_H__
#define __WITIN_TYPE_H__

#include "stdint.h"
#include "stdio.h"

typedef union {
    int value_i;
    char value_c[4];
} CHAR_INT_UNION_T;

typedef union {
    float value_f;
    char value_c[4];
} CHAR_FLOAT_UNION_T;

//sram type
typedef enum SramType {
    MCU_RAM = 1,
    NPU_REGFILE = 2,
    SRAMTypeMAX = 3,
} SramType_T;

typedef enum Flow_type_{
    ALL_ROUND = 1,
    CONV_2D_SPLIT = 2,
    CONV_2D = 3,
    EVENT = 4,
    FLOW_TYPE_MAX = 5,
}Flow_type_T; 

typedef enum WITIN_CALL_TYPE {
    LAYER_START = 1,
    LAYER_RUN = 2,
    LAYER_END = 3,
} WITIN_CALL_TYPE_t;

//
//call back
typedef struct callBackInfo_{
    int flow_index;
    int round_index;
    int net_index;
    Flow_type_T type;
} WitinCallBackInfo_T;

typedef void (*witin_layer_callback_t)(WitinCallBackInfo_T info, WITIN_CALL_TYPE_t type);
typedef void *(*witin_alloc_func_t)(size_t size);
typedef void (*witin_free_func_t)(void *ptr);
typedef int (*log_func_t)(const char *, ...);

// input or output
typedef struct Dataio_ {
    int addr;
    int len;
    char comment[20];
    int shape[4];
    SramType_T type;
} DataIO_T;

typedef enum WITIN_ERROR {
    ERROR_NOT_INIT = 1,  // Not init
} WITIN_ERROR_t;

typedef struct WITIN_HOOK {
    witin_layer_callback_t layerCallBack; 
    log_func_t          logFunc;
    int   log_level;
} WITIN_HOOK_T;

// model config
typedef struct WITIN_CONFIG_ {
// local 
    char isUseWfi; // lowpower
    char isUseDiff; // diff 
    char isUseDmaTransport; //use dma transport data
    unsigned char *model_data_addr; // bin model data pt
    witin_free_func_t freeFunc;
    witin_alloc_func_t allocFunc;
} WITIN_CONFIG_T;

typedef struct WITIN_MODEL_INFO_ {
    char *version;
    char *modelName;
    char *chip_id;
    char *date;
    short net_count;
} WITIN_MODEL_INFO_T;


//definations
typedef  enum WITIN_LOG_LEVEL {
    LOG_INFO=1,
    LOG_WARNNING = 2,
    LOG_ERROR=3,

}WITIN_LOG_LEVEL_t;

#endif