#ifndef P2P_TRANSFER_PROTOCOL_H
#define P2P_TRANSFER_PROTOCOL_H
struct _Lframe_ctol;

#include "wtm2101.h"

#include "vfs_list.h"
#include "ring_cache.h"
#include "hash.h"
#include "crc32.h"

#define LFRAME_SUSPEND        1
#define LFRAME_RUN            2
#define LFRAME_FAULT          3

#define APPLICATION_COMMAND   1
#define EXCHANGE_COMMAND      2
#define ACK_COMMAND           4
#define DELETE_MESSAGE        8

#define LFRAME_MASTER         1
#define LFRMAE_SLAVE          2
#define LFRAME_ENDPOINT       3

#define LFRAME_SYNC           1
#define LFRAME_ASYNC          2

#define LFRAME_RECOGNISE_HEAER        0X78
#define LFRAME_TRANSFER_SIZE          250
#define LFRAME_TRANSFER_SIZE_COUNT    40
#define LFRAME_TRANSFER_SIZE_MAX_COUNT (LFRAME_TRANSFER_SIZE_COUNT + 1)
#define LFRAEM_TRANSFER_ALIGMENT_SIZE 64

#define SEND_BUFF_SIZE (LFRAME_TRANSFER_SIZE * LFRAME_TRANSFER_SIZE_MAX_COUNT + LFRAEM_TRANSFER_ALIGMENT_SIZE)
#define RECE_BUFF_SIZE (LFRAME_TRANSFER_SIZE * LFRAME_TRANSFER_SIZE_MAX_COUNT + LFRAEM_TRANSFER_ALIGMENT_SIZE)

typedef enum {
    P2P_TRANSFER_PROTOCOL_LIKE_UDP = 1,
    P2P_TRANSFER_PROTOCOL_LIKE_TCP
}P2P_TRANSFER_PROTOCOL_QOS_LEVEL;

typedef  enum{
    P2P_SPI = 1,
    P2P_I2C,
    P2P_UART,
    P2P_I2S
}P2P_TRANSFER_PROTOCOL_HARDWARE_TYPE;

#define  LFREME_HEAD_HEADER_SET(frame,head)   ((frame)->header=head)
#define  LFREME_HEAD_HEADER_GET(frame)        ((frame)->header)
#define  LFREME_HEAD_LENGTH_SET(frame,len)    ((frame)->total_length=len)
#define  LFREME_HEAD_LENGTH_GET(frame)        ((frame)->total_length)
#define  LFREME_HEAD_CHECKSUM_SET(frame,check) ((frame)->crc32=check)
#define  LFREME_HEAD_CHECKSUM_GET(frame)       ((frame)->crc32)
#define  LFREME_HEAD_HASH_SET(frame,_hash)     ((frame)->hash=_hash)
#define  LFREME_HEAD_HASH_GET(frame)          ((frame)->hash)

#define  LFREME_HEAD_EXTERN_CTL_ORDER_COMMAND_SET(frame,_command)       ((frame)->extern_order.ctl_order.command=_command)
#define  LFREME_HEAD_EXTERN_CTL_ORDER_COMMAND_GET(frame)                ((frame)->extern_order.ctl_order.command)
#define  LFREME_HEAD_EXTERN_CTL_ORDER_VALUE_SET(frame,_value)    ((frame)->extern_order.ctl_order.value=_value)
#define  LFREME_HEAD_EXTERN_CTL_ORDER_VALUE_GET(frame)           ((frame)->extern_order.ctl_order.value)

typedef struct
{
    int(*wci_reav_packet)(struct _Lframe_ctol * wframe, unsigned char *data, int len);
    int(*change_mode)(struct _Lframe_ctol * wframe, uint  to_mode);
    int(*transfer)(struct _Lframe_ctol * wframe,unsigned char *data, int len);
    int(*transfer_and_recv)(struct _Lframe_ctol * wframe,unsigned char *send_buf, int send_length,unsigned char *receive_buf, int rece_length);
}Lframe_Call_Info;

#pragma pack(push) 
#pragma pack(1)  
typedef struct {
    unsigned char header;
    union
    {
        unsigned char reserved[5];
        struct {
            unsigned char command;
            int value;
        }ctl_order;
    }extern_order;
    unsigned short total_length;
    unsigned int crc32;
    unsigned int hash;
}Frame_head;

typedef struct _p2p_data_buf{
        unsigned char *msg;
        int msg_size;
        int index;  
}p2p_data_buf;

typedef struct _Lframe_ctol{
    char      device_type;
    char               qos_level;
    int                current_length;
    char      hardware_type;
    //uint8_t            *mutex;       
    vfs_list_type      * slist, *rlist, *alist;
    //unsigned int       mode_flag;   //标志  
    unsigned int       send_hash;   //本地发送哈希值
    unsigned int       rece_hash;   //本地接收哈希值
    unsigned int       send_timer_timeout_microseoncd;
    unsigned int       rece_timer_timeout_microseoncd;
    unsigned char      *rece_flag;
    Ring_Cache         *ring_buffer;
    //TMR_TypeDef        *send_timer;  
    //TMR_TypeDef        *rece_timer;
    //unsigned int       send_count;
    //unsigned int       rece_count;
    p2p_data_buf       rece_buff;
    p2p_data_buf       send_buff;
    //int                resend_num;  //重发次数
    void               *user_data; //用户层数据
    Lframe_Call_Info   call_info;   //回调接口    
}Lframe_ctol;
#pragma pack(pop) 

extern int lframe_ctol_init(Lframe_ctol *lframe, void *user_data);
extern int lframe_core_status_set(Lframe_ctol *lframe, int mode);
extern int lframe_rlist_handler(Lframe_ctol *lframe);
extern int lframe_slist_handler(Lframe_ctol *lframe);
extern int lframe_core(Lframe_ctol *lframe);
extern int lframe_alist_packet_handler(Lframe_ctol *lframe,int command,int value,int hash);

#endif
