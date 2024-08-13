// created by 杨西同
// 2019.11 忘记哪天创建的了。
#ifndef KWS_DECODER_H
#define KWS_DECODER_H
#include <stdlib.h>
#include <inttypes.h>
#include "kws_manager.h"
#include "lib_witin_kws/lib_witin_kws.h"

//typedef int8_t bool

void kws_decoder_test(void);
void decode_reset(void);
void decoder_init(void);
void set_on_get_keyword_func(WitinCallBack func);


extern int active_frms;
extern void (*on_decoder_not_active)(int, void*);
// 设置解码模块的响应时间（帧数）
// num_act_frms=DECODER_ALWAYS_ON 解码器一直响应，
// num_act_frms=0，decoder永久停止响应。
// num_act_frms>0, decoder将在未来的num_act_frms帧内保持响应。
void decoder_set_active_frms(int num_act_frms);

//查询decoder是否处于响应状态

int8_t decoder_is_active(void);

//设置回调函数，当decoder由响应状态转为非响应状态时，回调该函数。
void set_on_decoder_not_active(void(*func)(int, void*));

// 拆分 WitinKwsDecodeOneFrame 为三个函数
int8_t decode_one_frame_step0_return_active(void);
void decode_one_frame_step1(float* output);
void decode_one_frame_step2(void);

#endif
