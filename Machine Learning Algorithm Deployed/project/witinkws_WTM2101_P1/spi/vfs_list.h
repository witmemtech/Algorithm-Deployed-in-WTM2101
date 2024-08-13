#ifndef __VFS_LIST__
#define __VFS_LIST__
#pragma once
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
typedef	unsigned short	        ushort;
typedef	unsigned int	          uint;
typedef	unsigned char	          uchar;
typedef uint64_t                uint64;
typedef int64_t                 int64;
typedef uchar                   uint8;
typedef ushort                  uint16;
typedef uint                    uint32;

typedef struct low_vfs_list_type
{
    unsigned char             *data;
    unsigned int              count;
    struct low_vfs_list_type  *next;
}vfs_list_type;


//************************************
// Method:    vfs_list_head
// FullName:  vfs_list_head
// Access:    public 
// Returns:   vfs_list_type *
// Qualifier:
// Parameter: void
//************************************
vfs_list_type * vfs_list_head(void);
int             vfs_list_del(vfs_list_type *_list);
int             vfs_list_del_safe(vfs_list_type *_list);
int             vfs_list_remove(vfs_list_type *_list, uint index);
int             vfs_list_remove_safe(vfs_list_type *_list, uint index);
int             vfs_list_clear(vfs_list_type *_list);
int             vfs_list_clear_safe(vfs_list_type *_list);
int             vfs_list_push(vfs_list_type *_list, unsigned char * data, unsigned int count);
int             vfs_list_push_safe(vfs_list_type *_list, unsigned char * data, unsigned int count);
int             vfs_list_push_for_data(vfs_list_type *_list, unsigned char *data, unsigned int offset, unsigned int len);
int             vfs_list_push_for_data_safe(vfs_list_type *_list, unsigned char *data, unsigned int offset, unsigned int len);
int             vfs_list_insert(vfs_list_type *_list, uint index, unsigned char * data, unsigned int len);
int             vfs_list_insert_safe(vfs_list_type *_list, uint index, unsigned char * data, unsigned int len);
vfs_list_type   vfs_list_pop(vfs_list_type *_list);
vfs_list_type   vfs_list_pop_safe(vfs_list_type *_list);
vfs_list_type * vfs_list_find_at(vfs_list_type *_list, int index);
vfs_list_type * vfs_list_find_at_safe(vfs_list_type *_list, int index);
vfs_list_type * vfs_list_create_for_str(const char * data, const char divsion);
int             vfs_list_secede(vfs_list_type *_list, uint index);
int             vfs_list_secede_safe(vfs_list_type *_list, uint index);
#define         vfs_list_get_item(item , head,index) item = head; \
                             for(int z = 0x00 ; z < index;z++) { \
                                 item = item->next; \
                                 if(item == NULL) break; } \

#endif



