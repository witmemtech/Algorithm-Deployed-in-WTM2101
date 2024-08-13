// created by ����ͬ
// 2019.11 �������촴�����ˡ�
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
// ���ý���ģ�����Ӧʱ�䣨֡����
// num_act_frms=DECODER_ALWAYS_ON ������һֱ��Ӧ��
// num_act_frms=0��decoder����ֹͣ��Ӧ��
// num_act_frms>0, decoder����δ����num_act_frms֡�ڱ�����Ӧ��
void decoder_set_active_frms(int num_act_frms);

//��ѯdecoder�Ƿ�����Ӧ״̬

int8_t decoder_is_active(void);

//���ûص���������decoder����Ӧ״̬תΪ����Ӧ״̬ʱ���ص��ú�����
void set_on_decoder_not_active(void(*func)(int, void*));

// ��� WitinKwsDecodeOneFrame Ϊ��������
int8_t decode_one_frame_step0_return_active(void);
void decode_one_frame_step1(float* output);
void decode_one_frame_step2(void);

#endif
