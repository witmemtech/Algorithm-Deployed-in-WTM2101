#ifndef BYTE_MAP_H
#define BYTE_MAP_H
#include "heap_sort.h"

#ifdef PLATFORM_RSIC_V_N307
#define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline
#else
#define __STATIC_FORCEINLINE static inline
#endif


extern uint8_t* byte_map_for_arc1_src;
extern uint8_t* byte_map_for_arc1;
void clear_byte_map_for_arc1(HeapTokens* ptk);


__STATIC_FORCEINLINE void set_index_by_id(int id, int index)
{
    byte_map_for_arc1[id] = index | 0x80;
}

__STATIC_FORCEINLINE void set_byte_on_map_for_arc1(int id)
{
    byte_map_for_arc1[id] = 1;
}

__STATIC_FORCEINLINE void set_byte_off_map_for_arc1(int id)
{
    byte_map_for_arc1[id] = 0;
}

__STATIC_FORCEINLINE int get_byte_map_for_arc1(int id)
{
    return byte_map_for_arc1[id];
}

void init_byte_map_for_arc1();

int get_byte_map_for_arc1_number();

#endif