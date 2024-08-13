#ifndef  KWS_MANAGER_H
#define KWS_MANAGER_H


#define NUM_KWS_MODULES (2)

#define KWS_ID_WKUP (0)
#define KWS_ID_CMDS (1)

#define DECODER_ALWAYS_ON (-1)
// 定义被唤醒后的响应时间为5秒
#define DECODER_ACITVE_FRMS (5*100)

extern int32_t CUR_KWS_ID;

void set_kws_module(int kws_id);

#endif // ! KWS_MANAGER_H
