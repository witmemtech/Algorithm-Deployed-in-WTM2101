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
#ifndef APPLINK_WIN32_H_C3176F69_62FD_DAE0_3AF6_C64713FBE134_INCLUDED_
#define APPLINK_WIN32_H_C3176F69_62FD_DAE0_3AF6_C64713FBE134_INCLUDED_

typedef struct __datalink_state_t{
    uint32_t            connected;

    uint32_t            last_received_ts;
    uint32_t            heartbeat_sent_ts;
    uint32_t            data_sent_ts;

    uint32_t            tx_seq;
    uint32_t            rx_seq;
    uint64_t            nr_received;
    uint64_t            nr_sent;

    datalink_message_t* rx_msg;         // exist when received, else NULL
    datalink_status_t   rx_status;

    datalink_message_t* tx_ctrl_msg;    // always point to _tx_msg
    datalink_message_t* tx_data_msg;    // always point to _tx_data_msg
    uint32_t            tx_data_tries;

    //  actual message buffers
    datalink_message_t  _rx_msg;
    datalink_message_t  _tx_ctrl_msg;
    datalink_message_t  _tx_data_msg;
}datalink_state_t;


typedef enum __applink_state_t{
    APP_IDLE = 0,

    APP_STOP, // nothing to do, set to this state

    APP_SEND_INFO,
    APP_SEND_DATA,

    APP_RECV_INFO,
    APP_RECV_DATA,

    APP_WAIT_CLOSE,
    APP_DONE,
}applink_state_t;


typedef struct {
    applink_state_t     state;
    uint32_t            fileid;
    void*               user;
    uint32_t            remote_busy;
    uint32_t            busy_ts;
    uint32_t            data_length;// total data length 
    uint32_t            data_offset;// current data offset
    uint32_t            data_crc;   // crc16 of data_buffer[0..data_length]
    uint8_t             data_buffer[DATALINK_MAX_PAYLOAD_LEN];
}applink_sender_t;


typedef struct {
    applink_state_t     state;
    uint32_t            fileid;
    void*               user;
    uint32_t            data_length;// total data length
    uint32_t            data_offset;// current file pointer
    uint32_t            data_crc;   // update when received data.
}applink_receive_t;


struct applink_handle_t{
    uint32_t            ts;
    uint32_t            block_size;
    applink_dev_t       dev;
    datalink_state_t    link;
    applink_sender_t    sender;
    applink_receive_t   receiver;
    void*               user;
};

////////////////////////////////////////////////////////////////////////////////
//
//@retval APPLINK_OK        continue next callback processor
//@retval APPLINK_ERROR     internal error, stop all process
//
typedef applink_result_t (*applink_proc_pf)(applink_handle_t* self);


applink_result_t applink_proc_heartbeat_send(applink_handle_t* self);
applink_result_t applink_proc_heartbeat_received(applink_handle_t* self);
applink_result_t applink_proc_check_alive(applink_handle_t* self);
applink_result_t applink_proc_receiver_process(applink_handle_t* self);
applink_result_t applink_proc_sender_process(applink_handle_t* self);
applink_result_t applink_proc_file_info_timeout(applink_handle_t* self);
applink_result_t applink_proc_file_ack_timeout(applink_handle_t* self);
applink_result_t applink_proc_finally(applink_handle_t* self);

applink_result_t applink_send_msg(applink_handle_t* self, const datalink_message_t* msg);
applink_result_t applink_parse_char(applink_handle_t* self, uint8_t ch);

applink_handle_t* applink_create(
        applink_dev_t       dev,
        uint32_t            block_size,
        void*               user_tx,
        void*               user_rx);

int applink_run(applink_handle_t* app);

void applink_close(applink_handle_t* app);



#endif

