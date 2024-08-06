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
#ifndef APPLINK_INL_H_65488130_045C_10EB_EB12_086B4DA63793_INCLUDED_
#define APPLINK_INL_H_65488130_045C_10EB_EB12_086B4DA63793_INCLUDED_

#define APPLINK_FRAME_SIZE      160 // 160*int16_t, maximal frame size

typedef struct {
    uint32_t                    ts;
    uint32_t                    ts_heartbeat;
    uint32_t                    block_size;

    ////////////////////////////////////
    // link layer
    datalink_status_t           parser;
    uint32_t                    link_tx_seq;
    uint32_t                    link_rx_seq;

    ////////////////////////////////////
    // receiver
    const datalink_message_t*   msg;
    datalink_message_t          rx_msg;
    uint32_t                    rx_file_length;
    uint32_t                    rx_file_offset;
    uint32_t                    rx_file_crc;

    ////////////////////////////////////
    // sender
    datalink_message_t          tx_ctrl_msg;
    datalink_message_t          tx_data_msg;
    uint32_t                    is_txdata_ack;
    uint32_t                    fileid;
    uint32_t                    tx_file_length;
    uint32_t                    tx_file_offset;
    uint32_t                    tx_file_crc;
}applink_handle_t;


void applink_init(applink_handle_t* self, uint32_t block_size);


// @retval 0    ignore
// @retval 1    packet match
int applink_send_heartbeat(applink_handle_t* self);
int applink_recv_heartbeat(applink_handle_t* self);
int applink_recv_file_ack(applink_handle_t* self);
int applink_recv_file_info(applink_handle_t* self);
int applink_recv_file_data(applink_handle_t* self);
int applink_recv_file_crc(applink_handle_t* self);



// user implement function
int uart_recv_msg(applink_handle_t* self);
int uart_send_msg(const datalink_message_t* msg);
void uartxfer_callback_reset(void);
void uartxfer_callback_process(int16_t* in, int16_t* out);


#endif

