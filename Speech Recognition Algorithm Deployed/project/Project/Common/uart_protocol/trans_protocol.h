
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

/*Э��*/
// ��ʽ 	 |4byte|4byte|len bytes|
// ����		 |type | len | data    |
//			 |���� | ����| ����	   |
//�ֽ���: С�ˣ� ��bit �� byte

// type
//
// 1.	r_mc  ---	audio mic in ���� ,����short,
// 2.	r_fb  ---	��������host�˵�fbank ����
// 3.   fbnk  --- 	fbank, ����int8
// 4.	nnet  ---   chip net �������, ���� int
// 5.	log_  ---	log softmax ֮�����ݣ�����flot
// 6.	cmd_  ---	ʶ������ݣ�����ʽ���� char ���ͣ�id=%d word=%d score=%f
// 7.   0xcc  ---	����
// 8.	0xcd  --- 	����ȷ��
// 9.	0xdd  ---   ����
// 10.	0xde  ---	����ȷ��

// len
// int ����

//����
// ����Ϊlen������

typedef enum UART_TRANS_TYPE {
	//--------------------------------------------------------
	// start receive
	UART_TRANS_TYPE_AUDIO_FROM_HOST = 1, // audio from host, int16
	UART_TRANS_TYPE_FBANK_FROM_HOST = 2, // fbank from host, uint8
										 // receive end

	//-------------------------------------------------------
	// send start
	UART_TRANS_TYPE_FBANK = 3,			   // fbank ����
	UART_TRANS_TYPE_NNET_OUT = 4,		   // оƬ���
	UART_TRANS_TYPE_LOG_SOFTMAX = 5,	   //softmax ֮������
	UART_TRANS_TYPE_DECODE_OUT = 6,		   // ʶ��������
	UART_TRANS_TYPE_CONNECT = 7,		   //����
	UART_TRANS_TYPE_CONNECT_ACCEPT = 8,	   //����ȷ��
	UART_TRANS_TYPE_DISCONNECT = 9,		   //����
	UART_TRANS_TYPE_DISCONNECT_ACCEPT = 10, //����ȷ��
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
