#ifndef _DUART_H
#define _DUART_H

#include "WTM2101.h"
#include "gpio.h"
#include "uart.h"

#include "vfs_list.h"
#include "spi_transfer_protocol.h"
#include "ring_cache.h"
#include "timer.h"

#include "string.h"
#include <stdarg.h>

#define SYNC_ASYNC_SET_COMMAND 0x0001
#define SERIAL_SEND_DELAY_MS 3

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    UART_TypeDef *uart_hd;
    vfs_list_type *slist, *rlist, *alist;
    Lframe_ctol frame_ctl;
    uint8_t sync_async;
    Ring_Cache ring_buffer;
    uint8_t receive_flag;
}Duart;
#pragma pack(pop)


extern Duart *duart_open(UART_TypeDef *uart);
extern int duart_write(Duart *duart_hd,uint8_t *buf,int len);
extern int duart_read(Duart *duart_hd,uint8_t *buf,int *len,int timeout_ms);
extern int duart_ctl(Duart *duart_hd,int command, ...);

#endif
