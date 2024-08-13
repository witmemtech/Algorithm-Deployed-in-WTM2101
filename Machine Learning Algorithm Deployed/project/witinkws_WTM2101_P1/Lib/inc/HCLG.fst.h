#ifndef HCLG_FST_H
#define HCLG_FST_H
#include "acou_model.h"
#include "kws_manager.h"
#include "lib_witin_kws/lib_witin_kws.h" 

static float FLOAT_UNIT = (1.0 / 256.0);
static float FLOAT_MUL = (256.0);

#define MAX_DECODE_PATHS (50)

#define SIGN_START (254)
#define SIGN_END (255)
//typedef struct _FST_UNIT
//{
//    int16_t start;
//    int16_t end;
//    int16_t ilabel;
//    int16_t olabel;
//    //float weight;
//    int16_t weight;
//}
//FST_ARC;

//记录每个fst state在fst_data数组中的位置和长度（多少个arc）

void HCLG_fst_init(void);
void set_kws_fst(int id);
int get_start_id(void);
STATE_MAP* get_state_by_id(int id);
FST_ARC* get_arc_by_idx(int idx);


int is_fst_changed(void);
void clear_fst_changed_flag(void);
 
extern KWS_FST_MODU* cur_fst_modu;



#endif
