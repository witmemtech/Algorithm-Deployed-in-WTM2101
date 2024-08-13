#ifndef __NET_PARSE_H__
#define __NET_PARSE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define LITTLE_ENDIAN

#include <stdint.h>
#include "stdio.h"
#include "cJSON.h"
#include "witin_type.h"
#include "witin_npu_macro.h"

#pragma pack(4)

// base
/////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef  int  Addr_t;
typedef  int Len_t; 

typedef void *(*event_parse_handler_t)(cJSON * json);
typedef void (*event_free_handler_t)(void *ptr); 

typedef struct TypeDictItem {
    char name[20];
    SramType_T type;
    event_parse_handler_t parse_handler;
    event_free_handler_t  free_handler;
} TypeDictItem_t;

extern const TypeDictItem_t sramTypeDict[SRAMTypeMAX];

// evnet type
typedef  enum EventType_ {
    UPDATE_SIGMOID_TAB = 1,  
    UPDATE_TANH_TAB = 2,
    UPDATE_ROUND_CONFIG = 3,
    UPDATE_SYSTEM_CONFIG = 4,
    RAM_INIT = 5,
    CUSTOM_COPY = 6,
    CUSTOM_CLEAN = 7,
    CUSTOM_ADD = 8,
    CUSTOM_PN = 9,
    CUSTOM_MUL = 10,
    CUSTOM_CONCAT = 11,
    CUSTOM_ACTIVATE = 12,
    CUSTOM_POOLING = 13,
    EVENT_TYPE_MMAX=14,
} EventType_T;

typedef enum DataType_ {
    E_INT8 = 1,
    E_UINT8 = 2,
    E_INT16 = 3,
    E_UINT16 = 4
} EventDataType_t; 

extern const TypeDictItem_t EventTypeDict[EVENT_TYPE_MMAX];

//opt PN event
#if USE_EVENT_CUSTOM_PN
typedef struct OptPNEvent {
    CHAR_INT_UNION_T src_addr;
    SramType_T src_type;
    CHAR_INT_UNION_T dst_addr;
    SramType_T dst_type;
    CHAR_INT_UNION_T OPT_N;
    CHAR_INT_UNION_T OPT_W;
    CHAR_INT_UNION_T OPT_H;
    CHAR_INT_UNION_T OPT_C;
    CHAR_INT_UNION_T opt_value;
}OptPNEvent_T;
#endif

//opt copy event
#if USE_EVENT_CUSTOM_COPY
typedef struct OptCopyEvent {
    CHAR_INT_UNION_T src_addr;
    SramType_T src_type;
    CHAR_INT_UNION_T dst_addr;
    SramType_T dst_type;
    CHAR_INT_UNION_T len;
    EventType_T type;
}OptCopyEvent_T;
#endif

//opt clean event
#if USE_EVENT_CUSTOM_CLEAN
typedef struct OptCleanEvent {
    CHAR_INT_UNION_T addr;
    CHAR_INT_UNION_T len;
    EventType_T type;
}OptCleanEvent_T;
#endif

#if (USE_EVENT_CUSTOM_ADD || USE_EVENT_CUSTOM_MUL)
typedef struct OptLogicEvent {
    CHAR_INT_UNION_T left_addr;
    SramType_T left_type;
    CHAR_INT_UNION_T right_addr;
    SramType_T right_type;
    CHAR_INT_UNION_T store_addr;
    SramType_T store_type;
    CHAR_INT_UNION_T len;
    CHAR_INT_UNION_T fix_mode;
    CHAR_INT_UNION_T shift_en;
    CHAR_INT_UNION_T shift_direction;
    CHAR_INT_UNION_T shift_num;
    EventDataType_t store_data_type;
    EventDataType_t left_data_type;
    EventDataType_t right_data_type;
}OptLogicEvent_T;
#endif


#if USE_EVENT_CUSTOM_CONCAT
typedef struct ConcatEventIO_ {
    CHAR_INT_UNION_T addr;
    SramType_T type;
    CHAR_INT_UNION_T shape_N;
    CHAR_INT_UNION_T shape_W;
    CHAR_INT_UNION_T shape_H;
    CHAR_INT_UNION_T shape_C;
} ConcatEventIO_T; 

//concat
typedef struct ConcatEvent_ {
    CHAR_INT_UNION_T axis;
    CHAR_INT_UNION_T input_num;
    ConcatEventIO_T *intput;
    ConcatEventIO_T *output;
    int *copyLen;
}ConcatEvent_T;
#endif

//Activate
#if USE_EVENT_CUSTOM_ACTIVATE
typedef struct ActivateEvent_ {
    CHAR_INT_UNION_T src_addr;
    SramType_T       src_type;
    CHAR_INT_UNION_T dst_addr;
    SramType_T       dst_type;
    CHAR_INT_UNION_T len;
    CHAR_INT_UNION_T act_type;
    CHAR_INT_UNION_T data_offset;
    CHAR_INT_UNION_T data_len;
    CHAR_INT_UNION_T data_bitwidth;
    unsigned char *activateTablePt;
}ActivateEvent_T;
#endif

//pooling
#if USE_EVENT_CUSTOM_POOLING
typedef enum poolingType_ {
    POOL_AVG = 1,
    POOL_MAX = 2,
    POOL_MIN = 3,
} poolingType_T; 

typedef struct PoolingEvent {
    CHAR_INT_UNION_T src_addr;
    SramType_T       src_type;
    CHAR_INT_UNION_T dst_addr;
    SramType_T       dst_type;
    poolingType_T type;
    CHAR_INT_UNION_T input_N;
    CHAR_INT_UNION_T input_W;
    CHAR_INT_UNION_T input_H;
    CHAR_INT_UNION_T input_C;
    CHAR_INT_UNION_T pool_size_h;
    CHAR_INT_UNION_T pool_size_w;
    CHAR_INT_UNION_T stride_h;
    CHAR_INT_UNION_T stride_w;
    CHAR_INT_UNION_T pad_top;
    CHAR_INT_UNION_T pad_left;
    CHAR_INT_UNION_T pad_bottom;
    CHAR_INT_UNION_T pad_right;
    CHAR_FLOAT_UNION_T scale_in;
    CHAR_FLOAT_UNION_T scale_out;

}PoolingEvent_T; 
#endif

//init
#if USE_EVENT_RAM_INIT
typedef struct InitEvent {
    CHAR_INT_UNION_T addr;
    CHAR_INT_UNION_T data_bitwidth;
    CHAR_INT_UNION_T data_len;
    CHAR_INT_UNION_T data_offset;
    CHAR_INT_UNION_T len;
    SramType_T type;
    unsigned char *data;
} InitEvent_T; 
#endif

//systemevent 
typedef  struct SysEvent_ {
    CHAR_INT_UNION_T data_offset;
    CHAR_INT_UNION_T data_len;
    CHAR_INT_UNION_T data_bitwidth;
    CHAR_INT_UNION_T init;
    unsigned char *data;
} SysEvent_T;

// 
typedef  struct Event_ {
    EventType_T type;
    void *payload;
    int init;
} Event_T;


extern const TypeDictItem_t netTypeDict[FLOW_TYPE_MAX];

////////////////////////////////////////////////////////////////////////////////////////////////////
// module
// 
typedef struct BaseInfo_ {
    CHAR_INT_UNION_T  fifo_en;
    CHAR_INT_UNION_T  fifo_update_len;
    CHAR_INT_UNION_T  round_cfg_start;  // round config table start
    CHAR_INT_UNION_T  round_cfg_len;  //round config table end
    CHAR_INT_UNION_T  round_bit_width;
    CHAR_INT_UNION_T  round_start; // system config table end
    CHAR_INT_UNION_T  round_num; // system config table start
} BaseInfo_T;


typedef enum 
{
  line=0,
  nonline=1,
  relu=2,
}ActiveType_T;

typedef enum 
{
  tab_sigmoid=1,
  tab_tanh=2,
}TableType_T;

// diff
typedef struct DiffInfo_ {
    CHAR_INT_UNION_T round_index;
    // diff data store addr
    CHAR_INT_UNION_T fetch_addr;

    CHAR_INT_UNION_T expect_input_addr_start;

    CHAR_INT_UNION_T expect_input_len;

    CHAR_INT_UNION_T npu_output_addr_start;

    CHAR_INT_UNION_T npu_output_len;
    // expect input/output 0
    CHAR_INT_UNION_T expect_input0_data_array_offset;

    CHAR_INT_UNION_T expect_input0_data_array_len;

    CHAR_INT_UNION_T expect_output0_data_array_offset;

    CHAR_INT_UNION_T expect_output0_data_array_len;

    // expect input/output 1
    CHAR_INT_UNION_T expect_input1_data_array_offset;

    CHAR_INT_UNION_T expect_input1_data_array_len;

    CHAR_INT_UNION_T expect_output1_data_array_offset;

    CHAR_INT_UNION_T expect_output1_data_array_len;;

    //round config
    CHAR_INT_UNION_T round_config_array_offset;

    CHAR_INT_UNION_T round_config_array_len;

    CHAR_INT_UNION_T round_config_array_bitwidth;

    CHAR_INT_UNION_T package_len;

    //activate table
    CHAR_INT_UNION_T act_type;

    CHAR_INT_UNION_T table_type;

    CHAR_INT_UNION_T lookup_tab_data_offset;

    CHAR_INT_UNION_T lookup_table_data_len;

    CHAR_INT_UNION_T gain;

    signed char *expect_output_data_array0;
    unsigned char *expect_input_data_array0;

    signed char *expect_output_data_array1;
    unsigned char *expect_input_data_array1;

    unsigned int *round_config_data;

    unsigned char *lookup_tab;
    uint8_t           *tab_data;



    //diffvale
    int8_t *npu_output_0;
    int8_t *npu_output_1;
    int8_t *diff;
    float scale;
    int update_flag;


} DiffInfo_T;


// cnn
#if (USE_CONV_2D_SPLIT || USE_CONV_2D)
typedef struct CnnInfo_ {
    //instruction
    CHAR_INT_UNION_T instruction_reg_addr;
    CHAR_INT_UNION_T instruction_array_offset;
    CHAR_INT_UNION_T instruction_array_len;
    CHAR_INT_UNION_T instruction_array_bitwidth;

    CHAR_INT_UNION_T parameters_reg_addr;
    CHAR_INT_UNION_T parameters_array_offset;
    CHAR_INT_UNION_T parameters_array_len;
    CHAR_INT_UNION_T parameters_array_bitwidth;
    unsigned short *instructions_array;
    unsigned int *parameters_array;
} CnnInfo_T;
#endif

//sprase
typedef struct Sprase_info_ {
   CHAR_INT_UNION_T round_index;
   CHAR_INT_UNION_T sparse_cfg_addr;
   CHAR_INT_UNION_T sparse_cfg_len;
   CHAR_INT_UNION_T sparse_ext_scale;
   CHAR_INT_UNION_T bias_high_array_offset;
   CHAR_INT_UNION_T bias_high_array_len;
   CHAR_INT_UNION_T bias_high_array_bitwidth;

    unsigned char *frame_array;
    unsigned char *bias_high_array;
}Sprase_info_T;
 

//compute_flow
typedef struct Compute_flow_ {
    short flow_cnt;

    // flow type
    Flow_type_T type;

    //init event
    short eventCount;
    Event_T *event;

    //base
    BaseInfo_T *baseInfo;

    //diff count
    unsigned char diff_count;
    DiffInfo_T *diffInfo;

    //cnn
    #if (USE_CONV_2D_SPLIT || USE_CONV_2D)
    CnnInfo_T *cnnInfo;
    #endif

    //sparse
    unsigned char sparse_count;
    Sprase_info_T *spraseInfo;


    //skip and params
    int skipFlag;
    int parallel_flow_index;

}Compute_flow_T; 

typedef  struct DmaControl {
    int instruction_addr;
    int params_addr;
} DmaControl_T; 


//tempBuffer
typedef struct WITIN_DIFF_CONFIG_ {
    short *sum_nnet_out_temp0_;
    short *sum_nnet_out_temp1_;
    int8_t *diff_out_temp_;

    int *round_config_back;
    short i_layer;
    short i_flow;
    short minicycle_;
    short diff_infer_time;
    short state;
    short ministate;
    short backup_switch;
    short refresh_switch;
    short clock_switch;
    short isDmaWfi;
    short maxRoundConfigLen;
    short max_output_len;
}WITIN_DIFF_CONFIG_T;

//net_config
typedef struct Net_config_ {
    short net_index;
    unsigned char net_input_num;
    unsigned char net_output_num;
    DataIO_T *net_input;
    DataIO_T *net_output;
    short flow_count;
    short round_count;
    Compute_flow_T *flowInfo;
    int net_cnt;
    int compensate_en;
    int max_dma_len;
    int fifo_udpate_len;
    WITIN_DIFF_CONFIG_T *diff_config;
    SysEvent_T *systemEvent;
    SysEvent_T *systemEventBackUP;

    int initFlag;
    char adc_time;
} Net_config_T; 



typedef struct WITIN_BIN_MODEL_INFO_ {
    char *modelJsonDataPt;
    int modelJsonDataLen;
    char *modelRawDataPt;
    int modelRawDataLen;
} WITIN_BIN_MODEL_INFO_T;

//model
typedef struct WITIN_MODEL_{
    WITIN_MODEL_INFO_T info;
    int maxDmaLen;
    unsigned char *dmaBuffer;
    Net_config_T *netInfo;
    WITIN_CONFIG_T config;
    unsigned char *regfile_temp_buffer;

} WITIN_MODEL_T;

#pragma pack()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Net_config_T *witin_get_netObj(WITIN_MODEL_T *model,int index);

Compute_flow_T *witin_get_flowObj(Net_config_T *config, int index);

Event_T *witin_get_eventObj(Compute_flow_T *flow, int index);

DiffInfo_T *witin_get_diffInfoObj(Compute_flow_T *flow, int index);

 DiffInfo_T *witin_search_diffInfoObj_from_round(Compute_flow_T *flow, int roundIndex);

Sprase_info_T *witin_get_sparseObj(Compute_flow_T *flow, int index);

DataIO_T *witin_get_inputObj(Net_config_T *netObj, int index);

DataIO_T *witin_get_outputObj(Net_config_T *netObj, int index);

#if USE_EVENT_CUSTOM_CONCAT
ConcatEventIO_T *witin_get_concat_input(ConcatEvent_T *event, int index);
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public api
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// init
void witin_parse_init(void *(*malloc_fun)(size_t size), void (*free_fun)(void *ptr));

// gen model
WITIN_MODEL_T *witin_gen_model(WITIN_CONFIG_T *config, WITIN_BIN_MODEL_INFO_T *modelInfo) ;

//free
void witin_free_model(WITIN_MODEL_T *modelPt);

//
const char *witin_get_flow_name(int type);

#ifdef __cplusplus
}
#endif

#endif //__NET_PARSE_H__