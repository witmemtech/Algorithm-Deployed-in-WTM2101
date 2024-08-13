// created by 杨西同
// 2019.11 忘记哪天创建的了。
#ifndef ACOU_MODEL_H
#define ACOU_MODEL_H
#include <stdint.h>
#include "acou_model.h"
#include "lib_witin_kws/lib_witin_kws.h"



//extern int8_t phones[][16];
extern KWS_ACOU_MODU* cur_acou_model;

void set_kws_acou_model(int kws_id);

//获取wordid 对应的hashid
uint8_t wordHashIndex(uint8_t id);
void acou_model_init(void);

#endif // !ACOU_MODEL_H
