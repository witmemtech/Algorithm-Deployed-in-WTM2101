/* vim: set fileencoding=utf-8:
 *
 *                   GNU GENERAL PUBLIC LICENSE
 *                       Version 2, June 1991
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 *
 */
#ifndef JTAGLINK_RV32_H_56AEDC9E_E81C_BA29_C8F7_8B10B4D1B2B3_INCLUDED_
#define JTAGLINK_RV32_H_56AEDC9E_E81C_BA29_C8F7_8B10B4D1B2B3_INCLUDED_

#define JTAGXFER_FIFO_DEPTH     (DATALINK_MAX_PAYLOAD_LEN*2)

typedef struct {
    uint8_t             rxbuff[JTAGXFER_FIFO_DEPTH];
    uint8_t             txbuff[JTAGXFER_FIFO_DEPTH];

    uint32_t            recv_tmo;
    uint32_t            send_tmo;
    uint32_t            ts;

    datalink_status_t   link;
    uint32_t            tx_seq;

    uint32_t            rx_fileid;
    datalink_jtag_buf_t rx_ctrl;
    datalink_message_t  rx_msg;
    datalink_message_t* msg;

    uint32_t            tx_fileid;
    datalink_jtag_buf_t tx_ctrl;
    datalink_message_t  tx_msg;

    uint32_t            blocksize; // bytes
}jtaglink_handle_t;


// low-level api
int jtaglink_ll_xfer(const datalink_message_t* txmsg, datalink_message_t* rxmsg);

// high-level api
int jtaglink_init(jtaglink_handle_t* inst, int blocksize);
int jtaglink_reset(jtaglink_handle_t* inst);
int jtaglink_wait_handshake(jtaglink_handle_t* inst);

int jtaglink_flush(jtaglink_handle_t* inst);
int jtaglink_get_rxfifo_used(jtaglink_handle_t* inst);
int jtaglink_get_txfifo_free(jtaglink_handle_t* inst);
int jtaglink_send_msg(jtaglink_handle_t* inst, const datalink_message_t* msg);
int jtaglink_wait_msg(jtaglink_handle_t* inst, datalink_message_t* msg);
int jtaglink_recv_file_info(jtaglink_handle_t* inst);
int jtaglink_recv_file_data(jtaglink_handle_t* inst);
int jtaglink_recv_file_data2(jtaglink_handle_t* inst);
int jtaglink_recv_file_eof(jtaglink_handle_t* inst);

int jtaglink_send_data(
        jtaglink_handle_t* inst,
        uint32_t fileid,
        uint32_t offset,
        void*    buffer,
        uint32_t length);

// user-impl callback
void jtagxfer_callback_reset(void);
void jtagxfer_callback_process_mono(int16_t* in, int16_t* out, int nr_bytes);
void jtagxfer_callback_process_stereo(int16_t* in, int16_t* out, int nr_bytes);
int jtagxfer_callback_debug(char* buf, int max_len);
int jtagxfer_callback_spectrum_mask(char label[8], float* buf, int max_count);


#endif

