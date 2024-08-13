#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <stdint.h>
#include "global_def.h"


#ifdef PLATFORM_RSIC_V_N307
#define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline
#else
#define __STATIC_FORCEINLINE static inline
#endif

#ifdef USE_DECODER_V2_1

typedef struct _TOKEN
{
    //user should fill bellow args
    int32_t weight;
    int32_t start_wgt;
    uint16_t path_len;
    uint16_t start_plen;
    int16_t id;
    int16_t ilabel;
    int16_t olabel;
    uint8_t start_sign;
    uint8_t word_id;
    uint8_t end_sign;
}
TOKEN;

typedef struct __HeapTokens
{
    TOKEN** token_ptrs;
    int token_counts;

    TOKEN** token2_ptrs;
    int token2_counts;

    TOKEN** c_token_pointers_s;
    TOKEN** p_token_pointers_d;

}HeapTokens;


__STATIC_FORCEINLINE TOKEN* get_worst_token_by_map(HeapTokens* ptk)
{
    return ptk->token_ptrs[0];

}

__STATIC_FORCEINLINE TOKEN* get_token_by_index(HeapTokens* ptk, int index)
{
    return ptk->token_ptrs[index];
}


HeapTokens* tokens_init(int token_number);

void print_htk(HeapTokens* htoken);

void SiftDownHeapTokens(HeapTokens* htks, int start);

void InsertHeapTokens(HeapTokens* htks, TOKEN* x);

int tokens_exchange_to_another(HeapTokens* htoken);

void reset_tokens(HeapTokens* htoken);

#endif

#ifdef USE_DECODER_V2_2

typedef struct _TOKEN
{
	//user should fill bellow args
	int32_t weight;
	int32_t start_wgt;//命令词起始信号处的weight
	int32_t end_wgt;//命令词结束信号处的weight
	uint16_t path_len;
	uint16_t start_plen;//命令词起始信号处的路径长度
	uint16_t end_plen;//命令词结束信号处的路径长度
	int16_t id;
	int16_t ilabel;
	int16_t olabel;
	uint8_t start_sign;
	uint8_t word_id;
	uint8_t end_sign;
}
TOKEN;

typedef struct __HeapTokens
{
	TOKEN** cur_toks;
	int cur_toks_cnt;

	TOKEN** prev_toks;
	int prev_toks_cnt;

}HeapTokens;


__STATIC_FORCEINLINE TOKEN* get_worst_token_by_map(HeapTokens* ptk)
{
	return ptk->cur_toks[0];

}

__STATIC_FORCEINLINE TOKEN* get_token_by_index(HeapTokens* ptk, int index)
{
	return ptk->cur_toks[index];
}


HeapTokens* tokens_init(int token_number);

void print_htk(HeapTokens* htoken);

void SiftDownHeapTokens(HeapTokens* htks, int start);

void InsertHeapTokens(HeapTokens* htks, TOKEN* x);

int tokens_exchange_to_another(HeapTokens* htoken);

void reset_tokens(HeapTokens* htoken);

void append_sort_heap(HeapTokens* htks, TOKEN* new_tok);
void updata_sort_heap_top(HeapTokens* htks, int start);


#endif

#endif
