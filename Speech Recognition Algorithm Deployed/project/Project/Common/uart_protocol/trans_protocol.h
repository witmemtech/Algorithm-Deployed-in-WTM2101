
#ifndef TRANS_PROTOCOL_H
#define TRANS_PROTOCOL_H

#include <stdint.h>
#include "WTM2101.h"

int8_t is_trans_working(void);

#define MAX_PACK_LEN 2048

#pragma anon_unions
#pragma pack(push)
#pragma pack(1)
typedef struct _msgpack {
	int8_t type[4];
	union {
	    int8_t len_msg[4];
	    int32_t length;
	};
        union {
            int8_t checksum_msg[4];
	    int32_t checksum;
        };
	int8_t data[MAX_PACK_LEN];
} MSG_PACK;

#pragma pack(pop)

/*协议*/
// 格式 	 |4byte|4byte|len bytes|
// 含义		 |type | len | data    |
//			 |类型 | 长度| 数据	   |
//字节序: 小端， 低bit 低 byte

// type
//
// 1.	r_mc  ---	audio mic in 数据 ,类型short,
// 2.	r_fb  ---	接收来自host端的fbank 数据
// 3.   fbnk  --- 	fbank, 类型int8
// 4.	nnet  ---   chip net 输出数据, 类型 int
// 5.	log_  ---	log softmax 之后数据，类型flot
// 6.	cmd_  ---	识别的数据，带格式数据 char 类型，id=%d word=%d score=%f
// 7.   0xcc  ---	握手
// 8.	0xcd  --- 	握手确认
// 9.	0xdd  ---   分手
// 10.	0xde  ---	分手确认

// len
// int 类型

//数据
// 长度为len的数据

typedef enum UART_TRANS_TYPE {
	//--------------------------------------------------------
	// start receive
	UART_TRANS_TYPE_AUDIO_FROM_HOST = 1, // audio from host, int16
	UART_TRANS_TYPE_FBANK_FROM_HOST = 2, // fbank from host, uint8
										 // receive end

	//-------------------------------------------------------
	// send start
	UART_TRANS_TYPE_FBANK = 3,			   // fbank 特征
	UART_TRANS_TYPE_NNET_OUT = 4,		   // 芯片输出
	UART_TRANS_TYPE_LOG_SOFTMAX = 5,	   //softmax 之后数据
	UART_TRANS_TYPE_DECODE_OUT = 6,		   // 识别的命令词
	UART_TRANS_TYPE_CONNECT = 7,		   //握手
	UART_TRANS_TYPE_CONNECT_ACCEPT = 8,	   //握手确认
	UART_TRANS_TYPE_DISCONNECT = 9,		   //分手
	UART_TRANS_TYPE_DISCONNECT_ACCEPT = 10, //分手确认
        UART_INT16 = 11,
        UART_NONE = 12,
	// send end
} UART_TRANS_TYPE_T;

void uart_protocol_init(UART_TypeDef *uart);

void uart_send_data(void *pData, int len, UART_TRANS_TYPE_T type);

int uart_receive_data(void *pData, int len, UART_TRANS_TYPE_T type);

void when_get_key_word_outside_data(int type, void *args);

void outside_data_init(void);

void outside_data_process(void);

extern volatile uint8_t ENABLE_DATA_TRANS;
#endif
