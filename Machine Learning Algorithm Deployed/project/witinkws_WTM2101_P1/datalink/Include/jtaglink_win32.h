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
#ifndef JTAGLINK_WIN32_H_E10248F4_75C9_46BF_77A7_1B5FEF3C7860_INCLUDED_
#define JTAGLINK_WIN32_H_E10248F4_75C9_46BF_77A7_1B5FEF3C7860_INCLUDED_

typedef struct {
    ////////////////////////////////////
    //
    // link state and status
    //
    datalink_status_t   link_status;
    uint8_t             link_buffer[1024];
    uint32_t            link_bufcount;
    uint32_t            link_bufoffset;

    uint32_t            heartbeat_tmo;
    uint32_t            alive_tmo;
    uint32_t            ack_tmo;

    uint32_t            ts;

    //////////////////////// begin /////
    // pc.txfifo --> dev.rxfifo
    uint32_t            tx_buff_size;
    uint32_t            tx_buff_addr;
    uint32_t            tx_head_addr;
    uint32_t            tx_tail_addr;
    // pc.rxfifo <-- dev.txfifo
    uint32_t            rx_buff_size;
    uint32_t            rx_buff_addr;
    uint32_t            rx_head_addr;
    uint32_t            rx_tail_addr;
    //////////////////////// end ///////

    datalink_message_t  rx_msg;
    datalink_message_t* msg;

    uint32_t            tx_seq;
    datalink_message_t  tx_msg;

    uint32_t            block_size; // bytes

    uint32_t            max_winsize;
    uint32_t            winsize;

    uint32_t            tx_fileid;
    uint32_t            tx_length;
    uint32_t            tx_offset;

    uint32_t            rx_fileid;
    uint32_t            rx_length;
    uint32_t            rx_offset;

    uint32_t            nr_tx_data_pkgs;
    uint32_t            tx_pkg_id;
    uint32_t            nr_rx_data_pkgs;
    uint32_t            rx_pkg_id;

    // --- callback parameter ---
    void*               user;
    void*               user_tx;
    void*               user_rx;
}jtaglink_handle_t;

////////////////////////////////////////////////////////////////////////////////
//
//  low level api
//
int jtaglink_get_ll_xfer_parameter(uint32_t* txmsg_addr, uint32_t* rxmsg_addr);
int jtaglink_is_valid_address(uint32_t addr);

int jtaglink_wait_handshake(jtaglink_handle_t* inst);
int jtaglink_send_msg(jtaglink_handle_t* inst, const datalink_message_t* msg);
int jtaglink_recv_msg(jtaglink_handle_t* inst, uint8_t* buffer, int maxsize);
int jtaglink_wait_msg(jtaglink_handle_t* inst, datalink_message_t* msg, uint32_t timeout);


////////////////////////////////////////////////////////////////////////////////
//
//  user-impl callback
//
applink_result_t jtagxfer_callback_connected(
	jtaglink_handle_t* self,
	uint32_t version,
	uint32_t format);

applink_result_t jtatlink_cb_connection_lost(applink_handle_t* self);

applink_result_t jtagxfer_callback_get_file_info(
        jtaglink_handle_t*  self,
        void*               user,
        uint32_t            fileid,
        char                name[128],
        uint32_t*           pfileid,
        uint32_t*           plength);

applink_result_t jtagxfer_callback_get_file_data(
        jtaglink_handle_t*  self,
        void*               user,
        uint32_t            fileid,
        uint32_t            offset,
        uint32_t            length,
        uint8_t*            buffer);

applink_result_t jtagxfer_callback_file_sent(
        jtaglink_handle_t*  self,
        void*               user,
        uint32_t            fileid);

applink_result_t jtagxfer_callback_set_file_info(
        jtaglink_handle_t*  self,
        void*               user,
        uint32_t            fileid,
        uint32_t            length);

applink_result_t jtagxfer_callback_set_file_data(
        jtaglink_handle_t*  self,
        void*               user,
        uint32_t            fileid,
        uint32_t            dataid,
        const void*         data,
        uint32_t            length);

applink_result_t jtagxfer_callback_file_received(
        jtaglink_handle_t*  self,
        void*               user,
        uint32_t            fileid);

applink_result_t jtagxfer_callback_debug_received(
        jtaglink_handle_t*  self,
        void*               user,
        const void*         buffer,
        uint32_t            length);

applink_result_t jtagxfer_callback_spectrum_mask(
        jtaglink_handle_t*  self,
        void*               user,
        const char          label[8],
        const float*        mask_buffer,
        uint32_t            mask_count);


////////////////////////////////////////////////////////////////////////////////
//
//  high level api
//
jtaglink_handle_t* jtaglink_create(
        int     block_size,
        void*   user_tx,
        void*   user_rx);

int jtaglink_run(jtaglink_handle_t* self);

void jtaglink_close(jtaglink_handle_t* self);


#endif

