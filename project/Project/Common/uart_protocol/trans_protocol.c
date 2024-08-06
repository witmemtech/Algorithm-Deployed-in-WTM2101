#include "trans_protocol.h"
#include "string.h"

void receive_pack_head(MSG_PACK *pack);
void receive_pack_data(MSG_PACK *pack);
void send_pack_all(MSG_PACK *pack);
void test_trans(void);

UART_TypeDef *dst_uart=NULL;

int send_one_byte(UART_TypeDef *dst_UART, uint8_t byte);
uint8_t recv_one_byte(UART_TypeDef *dst_UART);

volatile uint8_t ENABLE_DATA_TRANS = 1;

void uart_protocol_init(UART_TypeDef *uart){
    dst_uart = uart;
}

void receive_pack_head(MSG_PACK *pack) {
	for (int i = 0; i < 4; i++) {
		pack->type[i] = recv_one_byte(dst_uart);
	}
	int8_t *length = (int8_t *)&pack->length;
	for (int i = 3; i >= 0; i--) {
		length[i] = recv_one_byte(dst_uart);
	}
}

void receive_pack_data(MSG_PACK *pack) {
	for (int i = 0; i < pack->length; i++) {
		pack->data[i] = recv_one_byte(dst_uart);
	}
        for (int i = 0; i < 4; i++) {
		pack->checksum_msg[i] = recv_one_byte(dst_uart);
	}
}

int caculateCheckValue(void *pData, int len) {
	int sum = 0;
	uint8_t *charPData = pData;
	for (int i = 0; i < len; i++) {
		sum += charPData[i];
	}
	return sum;
}

int8_t is_trans_working() {
	return ENABLE_DATA_TRANS;
}

void send_pack_all(MSG_PACK *pack) {
        int cksum = caculateCheckValue(pack->data, pack->length);
        pack->checksum = cksum;
	for (int i = 0; i < 4; i++) {
	    send_one_byte(dst_uart, pack->type[i]);
	}

	for (int i = 0; i < 4; i++) {
	    send_one_byte(dst_uart, pack->len_msg[i]);
	}

	for (int i = 0; i < pack->length; i++) {
	    send_one_byte(dst_uart, pack->data[i]);
	}
        for (int i=0; i < 4 ;i++){
            send_one_byte(dst_uart, pack->checksum_msg[i]);
        }
}

void test_trans(void) {
	if (0 == ENABLE_DATA_TRANS)
		return;

	MSG_PACK pack_recv = {0};
	receive_pack_head(&pack_recv);
	receive_pack_data(&pack_recv);
	send_pack_all(&pack_recv);
}



const char trans_type[UART_TRANS_TYPE_DISCONNECT_ACCEPT + 1][4] = {
	"none",
	"r_mc",
	"r_fb",
	"fbnk",
	"nnet",
	"log_",
	"cmd_",
	"0xcc",
	"0xcd",
	"bye_",
	"0xde"};

MSG_PACK pack_buffer;
void uart_send_data(void *pData, int len, UART_TRANS_TYPE_T type) {
	memset(&pack_buffer, 0, sizeof(MSG_PACK));
	if (type < UART_TRANS_TYPE_FBANK && type > UART_TRANS_TYPE_DISCONNECT_ACCEPT) {
		return;
	}
	memcpy(&pack_buffer.type, &trans_type[type], 4);
	int32_t pack_len = 0;
	switch (type) {
	case UART_TRANS_TYPE_LOG_SOFTMAX:
		pack_len = sizeof(float) * len;
		break;
        case UART_INT16:
            pack_len = sizeof(int16_t) * len;
	    break;
	case UART_TRANS_TYPE_FBANK:
	case UART_TRANS_TYPE_NNET_OUT:
	case UART_TRANS_TYPE_DECODE_OUT:
	case UART_TRANS_TYPE_CONNECT_ACCEPT:
	case UART_TRANS_TYPE_DISCONNECT_ACCEPT:
	default:
		pack_len = len;
		break;
	}
	pack_buffer.length = pack_len;
	memcpy(&pack_buffer.data, pData, pack_len);
	send_pack_all(&pack_buffer);
}

int uart_receive_data(void *pData, int len, UART_TRANS_TYPE_T type) {
	memset(&pack_buffer, 0, sizeof(MSG_PACK));
	//if (type < UART_TRANS_TYPE_FBANK && type > UART_TRANS_TYPE_DISCONNECT_ACCEPT) {
	//	return -1;
	//}
	receive_pack_head(&pack_buffer);
	if (strncmp((const char *)&pack_buffer.type, (const char *)&trans_type[type], 4) == 0) {
            int pack_len = 0;
            switch (type) {
                case UART_TRANS_TYPE_AUDIO_FROM_HOST:
                        pack_len = sizeof(int16_t) * len;
                        break;
                case UART_TRANS_TYPE_FBANK_FROM_HOST:
                case UART_TRANS_TYPE_CONNECT:
                case UART_TRANS_TYPE_DISCONNECT:
                default:
                        pack_len = len;
                        break;
            }
            if (pack_len == pack_buffer.length) {
                    receive_pack_data(&pack_buffer);
                    int calc_sum = caculateCheckValue(pack_buffer.data, pack_len);
                    if(calc_sum != pack_buffer.checksum){
                        return -1;
                    }
                    memcpy(pData, pack_buffer.data, pack_len);
                    return 0;
            }
	} 
        else {
            if (strncmp((const char *)&pack_buffer.type, "bye_", 4) == 0)
            {
                    ENABLE_DATA_TRANS = 0;
                    return 1;
            }
	}
	return -1;
}
