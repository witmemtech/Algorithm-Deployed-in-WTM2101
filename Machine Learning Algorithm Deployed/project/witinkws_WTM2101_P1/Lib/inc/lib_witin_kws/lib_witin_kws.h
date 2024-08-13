 /*
 * Copyright 2020 Beijing Zhicun (WITIN) Technology Co., LTD
 * Author: Yang Xitong, Liu Zhiming
 * All Rights Reserved.
 * 
 */

#ifndef LIB_WITIN_KWS_LIB_WITIN_KWS_H_
#define LIB_WITIN_KWS_LIB_WITIN_KWS_H_

#include <stdint.h>

typedef void (*WitinCallBack)(int, void*);

/** 
 * @brief function pointer parameter when get key words  
 */
typedef struct
{
    int id;        /*!< key words id */
    float score;   /*!< key words score */
}CallBackKeyWordsType;

/**
 * @brief CallBack type
 */
enum CallBackTypes
{
    kWitinKwsCallBackGetWords = 0,
};

/**
 * @brief Kws WorkMode wakeup or commands
 */
enum WitinKwsWorkMode
{
    kWitinWakeupMode = 0,
    kWitinCommandsMode,
};

/**
 * @brief Options when use WitinKwsSetOption
 */
enum WitinKwsOptionLists
{
    kWitinKwsWorkMode = 0,
    kWitinKwsActiveFrams,
    kWitinKwsGetWordsCallBack,
    kWitinKwsInactiveCallBack,
};

/**
 * @brief        Kws initialize
 * @return       void
 */
int WitinKwsInit(void);

/**
 * @brief        Kws uninitialize
 * @return       void
 */
void WitinKwsRelease(void);

/**
 * @brief        Decode one frame of data from the neural network output
 * @param[in]    in   input data
 * @param[in]      skip3FrameFlag   skip 3 frame or not , >0: open  <=0: close
 * @param[in]      skipFrameIndex   skip frame in total skipframes 0,1,2
 * @return       void
 */
void WitinKwsDecodeOneFrame(int8_t* nnet_out, int skip3FrameFlag, int skipFrameIndex);

/**
 * @brief        Kws get fbank features
 * @param[in]    in_frame        input PCM audio data buf£¬10ms data size: 160 * sizeof(int16_t) 16KHz,16bit
 * @param[out]   out_feature     output buf£¬size: 40 * sizeof(int8_t)
 * @param[callback] callback typedef void (*WitinCallBack)(int, void*);
 * @return       void
 */
void WitinKwsGetFbank(int16_t* in_frame, uint8_t* out_feature);
void WitinKwsGetFbank_WithWatchCallBack(int16_t* in_frame, uint8_t* out_feature, WitinCallBack callback);

/**
 * @brief        KwsSetOption
 * @param[in]    type            option type refer to WitinKwsOptionLists
 * @param[out]   value           output value
 * @return       0 success, not 0 failed
 */
int WitinKwsSetOption(int type, intptr_t value);

// wake-up model
#define KWS_ID_WKUP (0)

// recognition model
#define KWS_ID_CMDS (1)

#define DECODER_ALWAYS_ON (-1)

#define NUM_KWS_MODULES (2)

extern int32_t CUR_KWS_ID;

/**
 * @brief        get nnet input dimension
 * @return       return nnet input dimension
 */
int32_t WitinKwsGetNnetInDimension(void);

/**
 * @brief        get nnet output dimension
 * @return       return nnet output dimension
 */
int32_t WitinKwsGetNnetOutDimension(void);

/**
 * @brief        get nnet layer
 * @return       return nnet layer
 */
int32_t WitinKwsGetNnetLayerNum(void);

/**
 * @brief        get wake-up string by id 
 * @param[in]    id   wake-up string id
 * @return       get wake-up string
 */
const char* WitinKwsGetTipsWkupByid(int32_t id);

/**
 * @brief        get commands string by id
 * @param[in]    id   commands id
 * @return       get commands string
 */
const char* WitinKwsGetTipsCmdsByid(int32_t id);

/**
 * @brief        allocates size bytes and returns a pointer to the allocated memory 
 * @return       NULL       success
 * @return       NOT NULL   failed 
 */
void* OsalMalloc(uint32_t size);


/**
 * @brief        free size bytes and returns a result 
 * @return       1       success
 * @return       0   failed 
 */
int OsalFree(void *ptr);

/**
 * @brief            DNN logsoftmax layer. Since Chip donot support ssoftmax, Mcu perform it
 * @param[in]        in           input
 * @param[in,out]    out          output
 * @param[in]        logpriors    log prior probability
 * @param[in]        dimension    data dimension
 * @return           void
 */
void WitinKwsLogSoftMax(int8_t *in, const float* logpriors, uint32_t dim);

/**
 * @brief            DNN logsoftmax layer. Since Chip donot support ssoftmax, Mcu perform it
 * @param[in]        in           input nnet out data
 * @param[in]        index          index in data in
 * @return           float          logsoftmax value
 */
float WitinKwsGetLogSoftMax(int8_t* in, uint32_t index);


void WitinKwsLogSoftMaxByIndex(int8_t *in,float* out,int16_t* indexs, const float* logpriors, int16_t index_len);
void LogSoftMax_int16(int8_t *in,  int16_t *dst, uint32_t dim,uint8_t rshift);
void LogSoftMax_f(int8_t *in,  float *dst, uint32_t dim,uint8_t rshift);

/**
 * @brief        get logpriors of phoneme status(log priori probability)
 * @return       return logpriors address
 */
const float* WitinKwsGetLogPriors(void);

typedef struct _FST_UNIT
{
    int16_t start;
    int16_t end;
    int16_t ilabel;
    int16_t olabel;
    int16_t weight;
} FST_ARC;

typedef struct _STATE_MAP
{
    uint16_t start;
    uint16_t len;
    uint16_t start_igz;
    uint16_t len_igz;
    uint16_t start_iez;
    uint16_t len_iez;
} STATE_MAP;

typedef struct _KWS_FST_MODU
{
    STATE_MAP* map;
    FST_ARC* arcs;
    int16_t num_states;
    int16_t num_arcs;
    const int16_t* pdfs;
    int16_t num_pdfs;
    int8_t num_max_paths;   // max path length when decoded
 }KWS_FST_MODU;
 
 typedef struct _kws_word_hash_node {
    const uint8_t *wordPtr;
    uint8_t wordIndex;
    struct _kws_word_info_node* next;
}kws_word_info_node_t;

typedef struct _kws_wordList_info {
    kws_word_info_node_t* head;
    kws_word_info_node_t* tail;
}kws_wordList_hash_t;

typedef struct _KWS_ACOU_MODU
{
    const int8_t* key_words_str;  // key word string buf
    const uint8_t* key_words;     // array of key word order
    const uint8_t* key_words_len; // array of key word length
    int8_t max_kw_len;           // max key word length
    int8_t min_kw_len;           // min key word length
    int16_t num_key_words;        // key word number
    int16_t kwstr_len;            // max len of key word string
    kws_wordList_hash_t wordHash[16];
}
KWS_ACOU_MODU;
 
extern KWS_FST_MODU* cur_fst_modu;


extern int32_t get_nnet_in_dim();
extern int32_t get_nnet_out_dim();
extern int32_t get_nnet_layer_num();
extern int32_t get_num_states_0(void);
extern int32_t get_num_states_1(void);
extern const void* get_fst_data_0(void);
extern const void* get_fst_data_1(void);
extern int32_t get_nub_arcs_0(void);
extern int32_t get_nub_arcs_1(void);
extern const int16_t* get_pdfs_0(void);
extern int32_t get_num_of_pdf_0(void);
extern const float* get_logpriors(void);
extern const char* get_kws_tips_wkup_byid(int32_t id);
extern const char* get_kws_tips_cmds_byid(int32_t id);


typedef void *(*witin_kws_alloc_func_t)(uint32_t size);
typedef void (*witin_kws_free_func_t)(void *ptr);
typedef int (*witin_log_func_t)(const char *, ...);

typedef struct KWS_CONFIG_ {
    witin_kws_alloc_func_t malloc_func;   // set a malloc function 
    witin_kws_free_func_t free_func;      // set a free function 
    witin_log_func_t log_func;            // set a printf function
} WITIN_KWS_CONFIG_t;

/**
 * @brief            set configs
 * @param[in]        config           
 */
void WitinKwsSetConfig(WITIN_KWS_CONFIG_t *config);

/**
 * @brief            printf info use log_func in struct KWS_CONFIG_t
 * @param[in]        format            format is same as printf 1th para
 */
int WitinKwsLog(const char *format, ...);

#endif  // LIB_WITIN_KWS_LIB_WITIN_KWS_H_
