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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "crc.h"
#include "datalink.h"
#include "applink.h"
#include "applink_win32.h"

static applink_handle_t app;

static applink_proc_pf processors[] = {
    applink_proc_heartbeat_send,
    applink_proc_heartbeat_received,
    applink_proc_check_alive,
    applink_proc_receiver_process,
    applink_proc_sender_process,
    applink_proc_file_info_timeout,
    applink_proc_file_ack_timeout,
    applink_proc_debug,
    applink_proc_finally,
};

applink_result_t applink_proc_heartbeat_send(applink_handle_t* self)
{
    if (self->ts - self->link.heartbeat_sent_ts > HEARTBEAT_TMO) {
        self->link.heartbeat_sent_ts = self->ts;
        datalink_encode_heartbeat(
                self->link.tx_ctrl_msg,
                self->link.tx_seq,
                FW_DCCRN_v2_1_0,
                0x20220511,
                0x00093011,
                self->ts);
        self->link.tx_seq++;
        if (applink_send_msg(self, self->link.tx_ctrl_msg) != APPLINK_OK) {
            self->link.nr_sent++;
            return APPLINK_ERROR;
        }
        return APPLINK_OK;
    }

    return APPLINK_OK;
}

applink_result_t applink_proc_heartbeat_received(applink_handle_t* self)
{
    if (self->link.rx_msg == NULL) {
        return APPLINK_OK;
    }

    if (self->link.rx_msg->header.u.msgid == DATALINK_MSG_ID_HEARTBEAT) {
        if (self->link.rx_msg->header.u.msgid == DATALINK_MSG_ID_HEARTBEAT) {
            const datalink_msg_heartbeat_t* heartbeat;
            heartbeat = (const datalink_msg_heartbeat_t*)self->link.rx_msg;
            callback_link_connected(self,
                heartbeat->date,
                heartbeat->time);
            self->link.connected = 1;
            self->link.rx_msg = NULL;
            return APPLINK_OK;
        }

        self->link.rx_msg = NULL;
        return APPLINK_OK;
    }

    return APPLINK_OK;
}

applink_result_t applink_proc_check_alive(applink_handle_t* self)
{
    if (self->link.connected && (self->ts - self->link.last_received_ts > ALIVE_TMO)) {
        printf("Info: nothing received during 3 seconds\n");

        // reset timer
        self->link.heartbeat_sent_ts     = self->ts;
        self->link.data_sent_ts          = self->ts;

        // reset state
        self->link.connected = 0;

        if (self->sender.state != APP_STOP) {
            self->sender.state           = APP_IDLE;
            self->sender.data_offset     = 0;
        }
        if (self->receiver.state != APP_STOP) {
            self->receiver.state         = APP_IDLE;
            self->receiver.data_length   = 0;
            self->receiver.data_offset   = 0;
        }

        callback_connection_lost(self);
        return APPLINK_BREAK;
    }

    if (!self->link.connected) {
        if (self->ts - self->link.last_received_ts < 2*HEARTBEAT_TMO) {
            callback_link_connected(self, 0, 0);
            self->link.connected = 1;
        }
    }

    if (self->link.connected) {
        return APPLINK_OK;
    }
    return APPLINK_BREAK;
}


applink_result_t applink_proc_receiver_process(applink_handle_t* self)
{
    if (self->link.rx_msg == NULL) {
        return APPLINK_OK;
    }

    if (self->link.rx_msg->header.u.msgid == DATALINK_MSG_ID_FILE_INFO) {
        if (self->receiver.state == APP_IDLE) {
            const datalink_msg_file_info_t* info;
            info = (const datalink_msg_file_info_t*)self->link.rx_msg;

            printf("Info: receiver got info \"%s\", id 0x%08x, %d bytes\n",
                    info->name, info->fileid, info->length);

            callback_set_file_info(self, self->receiver.user, info->fileid, info->length);

            self->receiver.fileid      = info->fileid;
            self->receiver.data_length = info->length;
            self->receiver.data_offset = 0;
            datalink_encode_file_ack(
                    self->link.tx_ctrl_msg,
                    self->link.tx_seq,
                    self->receiver.fileid,
                    0);
            self->link.tx_seq++;
            if (applink_send_msg(self, self->link.tx_ctrl_msg) != APPLINK_OK) {
                self->link.nr_sent++;
                return APPLINK_ERROR;
            }

        } else {
            printf("Warning: apprx: received file info again\n");
        }

        self->receiver.state = APP_RECV_INFO;
        self->link.rx_msg = NULL;
        return APPLINK_OK;
    }

    if (self->link.rx_msg->header.u.msgid == DATALINK_MSG_ID_FILE_DATA) {
        const datalink_msg_file_data_t* data;
        data = (const datalink_msg_file_data_t*)self->link.rx_msg;

        if ((self->receiver.state == APP_IDLE) ||
            (self->receiver.state == APP_STOP) ||
            (self->receiver.state == APP_DONE)) {
            printf("Warning: apprx: unexpected data block received\n");

            datalink_encode_file_nak(
                self->link.tx_ctrl_msg,
                self->link.tx_seq,
                data->fileid,
                data->dataid);
            self->link.tx_seq++;
            if (applink_send_msg(self, self->link.tx_ctrl_msg) != APPLINK_OK) {
                self->link.nr_sent++;
                return APPLINK_ERROR;
            }

            self->link.rx_msg = NULL;
            return APPLINK_OK;
        }

        if ((self->receiver.state == APP_RECV_INFO) || 
            (self->receiver.state == APP_RECV_DATA)) {
            int nr_bytes = self->link.rx_msg->header.u.dlen - 2*sizeof(uint32_t);

            if (data->dataid < self->receiver.data_offset) {
                printf("Warning: data duplicated, %08x, %08x\n",
                        self->receiver.data_offset, data->dataid);
                self->receiver.data_offset = data->dataid;

            } else if (self->receiver.data_offset < data->dataid) {
                printf("Warning: data lost!, %08x, %08x\n",
                        self->receiver.data_offset, data->dataid);
                self->receiver.data_offset = data->dataid;

            } else {
                uint16_t crcval;

                callback_set_file_data(self, self->receiver.user, data->fileid, data->dataid, data->data, nr_bytes);

                crcval = crc16_update(self->receiver.data_crc, data->data, nr_bytes);
                self->receiver.data_crc = crcval;

                self->receiver.data_offset += nr_bytes;
                if (self->receiver.data_offset == self->receiver.data_length) {
                    self->receiver.state = APP_WAIT_CLOSE;
                }
            }

            datalink_encode_file_ack(
                    self->link.tx_ctrl_msg,
                    self->link.tx_seq,
                    data->fileid,
                    data->dataid);
            self->link.tx_seq++;
            if (applink_send_msg(self, self->link.tx_ctrl_msg) != APPLINK_OK) {
                self->link.nr_sent++;
                return APPLINK_ERROR;
            }

            self->receiver.state = APP_RECV_DATA;
            self->link.rx_msg = NULL;
            return APPLINK_OK;
        }

        printf("Warning: received data package, but why we here?\n");
        self->link.rx_msg = NULL;
        return APPLINK_OK;
    }

    if (self->link.rx_msg->header.u.msgid == DATALINK_MSG_ID_FILE_CRC) {
        const datalink_msg_file_crc_t* crc = (datalink_msg_file_crc_t*)self->link.rx_msg;
        if (crc->crcvalue != self->receiver.data_crc) {
            printf("Error: data crc not match, 0x%08x != 0x%08x (expect)\n",
                    self->receiver.data_crc, crc->crcvalue);
        }

        callback_file_received(self, self->receiver.user, crc->fileid);

        self->receiver.state = APP_DONE;
        self->link.rx_msg = NULL;
        return APPLINK_OK;
    }

    // leave rx_msg
    return APPLINK_OK;
}

applink_result_t applink_proc_sender_process(applink_handle_t* self)
{
    const datalink_msg_file_ack_t* ack;
    const datalink_msg_file_data_t* data;

    if (self->link.rx_msg == NULL) {
        return APPLINK_OK;
    }

    if (self->link.rx_msg->header.u.msgid != DATALINK_MSG_ID_FILE_ACK) {
        return APPLINK_OK;
    }

    if (self->sender.remote_busy) {
        if (self->ts - self->sender.busy_ts > BUSY_TMO) {
            printf("Error: datalink: target is busy\n");
            return APPLINK_ERROR;
        }
        return APPLINK_OK;
    }

    ack  = (datalink_msg_file_ack_t*)self->link.rx_msg;
    data = (datalink_msg_file_data_t*)self->link.tx_data_msg;

    //printf("Info: ACK.dataid = %04x\n", ack->dataid);
    if (self->sender.state == APP_STOP) {
        printf("Warning: unexpected ACK, fileid=%08x, dataid=%08x\n",
                ack->fileid, ack->dataid);
        self->link.rx_msg = NULL;
        return APPLINK_OK;
    }

    if (self->sender.state == APP_DONE) {
        self->link.rx_msg = NULL;
        return APPLINK_OK;
    }

    if (self->sender.state == APP_WAIT_CLOSE) {
        if (data->dataid == ack->dataid) {
            if (self->sender.state == APP_WAIT_CLOSE) {

                // when all data blocks accepted by device,
                // send whole file crc checker.
                // and this is optional.
                callback_get_file_crc(
                        self,
                        self->sender.user,
                        self->sender.fileid,
                        &self->sender.data_crc);

                datalink_encode_file_crc(
                        self->link.tx_ctrl_msg,
                        self->link.tx_seq,
                        ack->fileid,
                        ack->dataid,
                        self->sender.data_crc);
                self->link.tx_seq++;
                if (applink_send_msg(self, self->link.tx_ctrl_msg) != APPLINK_OK) {
                    self->link.nr_sent++;
                    return APPLINK_ERROR;
                }

                callback_file_sent(self, self->sender.user,self->sender.fileid);

                self->sender.state = APP_DONE;
                self->link.rx_msg = NULL;
                return APPLINK_OK;
            }
        }
        self->link.rx_msg = NULL;
        return APPLINK_OK;
    }

    if ((self->sender.state == APP_SEND_INFO) || 
        (self->sender.state == APP_SEND_DATA)) {
                int nr_bytes;

        if (data->dataid != ack->dataid) {
            printf("Info: not match ACK.dataid%08X with DATA.dataid%08X\n",
                    ack->dataid, data->dataid);
            self->link.rx_msg = NULL;
            return APPLINK_OK;
        }

        nr_bytes = self->sender.data_length - self->sender.data_offset;
        if (nr_bytes > self->block_size) {
            nr_bytes = self->block_size;
        }

        //printf("Info: send data, offset = 0x%08x/0x%08x, size = %d, seq=%d\n", 
        //        self->sender.data_offset,
        //        self->sender.data_length,
        //        nr_bytes,
        //        self->link.tx_seq);
        
        //printf("0x%08x/0x%08x\n", self->sender.data_offset, self->sender.data_length);


        callback_get_file_data(
                self,
                self->sender.user,
                self->sender.fileid,
                self->sender.data_offset,
                nr_bytes,
                self->sender.data_buffer);

        datalink_encode_file_data(
                self->link.tx_data_msg,
                self->link.tx_seq,
                self->sender.fileid,
                self->sender.data_offset,
                self->sender.data_buffer,
                nr_bytes);
        self->link.tx_data_tries = 0;
        self->link.tx_seq++;
        if (applink_send_msg(self, self->link.tx_data_msg) != APPLINK_OK) {
            self->link.nr_sent++;
            return APPLINK_ERROR;
        }
        self->sender.data_offset += nr_bytes;
        self->link.data_sent_ts = self->ts;
        self->sender.state = APP_SEND_DATA;

        nr_bytes = self->sender.data_length - self->sender.data_offset;
        if (nr_bytes <= 0) {
            printf("Info: sender::WAIT_CLOSE\n");
            self->sender.state = APP_WAIT_CLOSE;
        }

        self->link.rx_msg = NULL;
        return APPLINK_OK;
    }

    // leave rx_msg
    return APPLINK_OK;
}

applink_result_t applink_proc_file_info_timeout(applink_handle_t* self)
{
    char name[128];

    if (self->ts - self->link.data_sent_ts < ACK_TMO) {
        return APPLINK_OK;
    }

    if ((self->sender.state == APP_STOP) || (self->sender.state == APP_DONE)) {
        return APPLINK_OK;
    }

    if ((self->sender.state != APP_IDLE) && (self->sender.state != APP_SEND_INFO)) {
        return APPLINK_OK;
    }

    callback_get_file_info(
            self,
            self->sender.user,
            self->sender.fileid,
            name,
            &self->sender.fileid,
            &self->sender.data_length);

    datalink_encode_file_info(
            self->link.tx_ctrl_msg,
            self->link.tx_seq,
            name,
            self->sender.fileid,
            self->sender.data_length);
    self->link.tx_seq++;
    if (applink_send_msg(self, self->link.tx_ctrl_msg) != APPLINK_OK) {
        self->link.nr_sent++;
        return APPLINK_ERROR;
    }
    self->link.data_sent_ts = self->ts;
    self->sender.state = APP_SEND_INFO;

    return APPLINK_OK;
}

applink_result_t applink_proc_file_ack_timeout(applink_handle_t* self)
{
    if (self->ts - self->link.data_sent_ts < ACK_TMO) {
        return APPLINK_OK;
    }

    // APP_SEND_DATA -and- APP_WAIT_CLOSE need device send back ACK package.
    if ((self->sender.state != APP_SEND_DATA) && (self->sender.state != APP_WAIT_CLOSE)) {
        return APPLINK_OK;
    }

    if (self->sender.remote_busy) {
        return APPLINK_OK;
    }

    self->link.tx_data_tries++;
    if (self->link.tx_data_tries > DATA_RETRIES) {
        printf("Error: datalink::sender: re-send three times, fail\n");
        callback_connection_lost(self);
        self->sender.state = APP_DONE;
        return APPLINK_OK;
    }

    datalink_encode(self->link.tx_data_msg, self->link.tx_seq);

    printf("Info: datalink::sender: re-send data, .seq = %d, .dataid = 0x%08x\n", 
            ((datalink_msg_file_data_t*)self->link.tx_data_msg)->header.u.seq,
            ((datalink_msg_file_data_t*)self->link.tx_data_msg)->dataid);

    self->link.tx_seq++;
    if (applink_send_msg(self, self->link.tx_data_msg) != APPLINK_OK) {
        self->link.nr_sent++;
        return APPLINK_ERROR;
    }

    self->link.data_sent_ts = self->ts;
    return APPLINK_OK;
}

applink_result_t applink_proc_debug(applink_handle_t* self)
{
    const datalink_msg_debug_t* dbg;
    int nr_bytes;

    if (self->link.rx_msg == NULL) {
        return APPLINK_OK;
    }

    if (self->link.rx_msg->header.u.msgid == DATALINK_MSG_ID_DEBUG) {
        dbg = (const datalink_msg_debug_t*)self->link.rx_msg;
        nr_bytes = dbg->header.u.dlen;
        callback_debug_received(
                self,
                self->receiver.user, 
                (uint8_t*)dbg->raw, 
                nr_bytes);
        self->link.rx_msg = NULL;
    }

    return APPLINK_OK;
}

applink_result_t applink_proc_busy(applink_handle_t* self)
{
    if (self->link.rx_msg == NULL) {
        return APPLINK_OK;
    }

    if (self->link.rx_msg->header.u.msgid == DATALINK_MSG_ID_BUSY) {
        printf("Info: datalink: target is busy\n");
        if (self->sender.state == APP_SEND_DATA) {
            printf("Info: datalink: sender sleep\n");
            self->sender.busy_ts = self->ts;
            self->sender.remote_busy = 1;
        }
        self->link.rx_msg = NULL;
    }

    return APPLINK_OK;
}

applink_result_t applink_proc_continue(applink_handle_t* self)
{
    if (self->link.rx_msg == NULL) {
        return APPLINK_OK;
    }

    if (self->link.rx_msg->header.u.msgid == DATALINK_MSG_ID_CONTINUE) {
        printf("Info: datalink: continue\n");
        if (self->sender.state == APP_SEND_DATA) {
            printf("Info: datalink: sender wake\n");
            self->sender.busy_ts = self->ts;
            self->sender.remote_busy = 0;
        }
        self->link.rx_msg = NULL;
    }

    return APPLINK_OK;
}

applink_result_t applink_proc_finally(applink_handle_t* self)
{
    if (self->link.rx_msg != NULL) {
        printf("Error: unknown msgid = %d\n", self->link.rx_msg->header.u.msgid);
        self->link.rx_msg = NULL;
    } 

    return APPLINK_OK;
}

applink_result_t applink_send_msg(applink_handle_t* self, const datalink_message_t* msg)
{
    int nr_bytes = SIZEOF_DATALINK_MESSAGE_HEADER + msg->header.u.dlen;

    if (user_send_msg(self->dev, (uint8_t*)msg, nr_bytes) <= 0) {
        printf("Error: applink_send_msg fail\n");
        return APPLINK_ERROR;
    }

    return APPLINK_OK;
}

applink_result_t applink_parse_char(applink_handle_t* self, uint8_t ch)
{
    if (datalink_parse_char(ch, &self->link._rx_msg, &self->link.rx_status)) {
        self->link.last_received_ts = self->ts;
        self->link.rx_msg = &self->link._rx_msg;

        if (self->link.rx_seq != self->link.rx_msg->header.u.seq) {
            if (self->link.nr_received == 0) { // ignore first pack
            } else {
                printf("Warning: receiving channel data lost\n");
            }
            self->link.rx_seq = self->link.rx_msg->header.u.seq;
        }
        // next package expect seqid
        self->link.rx_seq = (self->link.rx_seq + 1) & 0xFFu;
        self->link.nr_received++;
        return APPLINK_OK;
    }

    return APPLINK_OK;
}

applink_handle_t* applink_create(
        applink_dev_t       dev,
        uint32_t            block_size,
        void*               user_tx,
        void*               user_rx)
{
    app.block_size = block_size;

    memset(&app.link, 0, sizeof(app.link));
    app.link.tx_ctrl_msg       = &app.link._tx_ctrl_msg;
    app.link.tx_data_msg       = &app.link._tx_data_msg;

    memset(&app.sender, 0, sizeof(app.sender));
    app.sender.state           = APP_STOP;
    if (user_tx != NULL) {
        app.sender.state        = APP_IDLE;
        app.sender.user         = user_tx;
        app.sender.data_length  = 0;
        app.sender.data_offset  = 0;
        app.sender.data_crc     = crc16_init();
    }

    memset(&app.receiver, 0, sizeof(app.receiver));
    app.receiver.state         = APP_STOP;
    if (user_rx != NULL) {
        app.receiver.state      = APP_IDLE;
        app.receiver.user       = user_rx;
        app.receiver.cache_offset = 0;
        app.receiver.data_length  = 0;
        app.receiver.data_offset  = 0;
        app.receiver.data_crc   = crc16_init();
    }

    app.link.last_received_ts  = 0;
    app.link.heartbeat_sent_ts = 0;
    app.link.data_sent_ts      = 0;

    app.dev  = dev;

    app.ts = user_get_tick();
    app.link.last_received_ts   = app.ts;
    app.link.heartbeat_sent_ts  = app.ts;
    app.link.data_sent_ts       = app.ts;

    return &app;
}

int applink_run(applink_handle_t* self)
{
    applink_result_t result;
    uint8_t buffer[1024];
    int buf_len = 0;
    int buf_offs = 0;
    uint8_t ch;
	int i;
    int nr_bytes;

    while (1) {
        if (user_kbhit()) {
            break;
        }

        self->ts = user_get_tick();

        if ((self->sender.state == APP_DONE) && (self->receiver.state == APP_STOP)) {
            printf("Info: all sent\n");
            break;
        }
        if ((self->receiver.state == APP_DONE) && (self->sender.state == APP_STOP)) {
            printf("Info: all recv\n");
            break;
        }
        if ((self->sender.state == APP_DONE) && (self->receiver.state == APP_DONE)) {
            printf("Info: all done\n");
            break;
        }

        if (buf_offs >= buf_len) { // bytes processed, read more
            buf_offs = 0;
            nr_bytes = user_recv_msg(self->dev, buffer, sizeof(buffer));
            if (nr_bytes < 0) {
                break;
            }
            buf_len = nr_bytes;
        }


        if (buf_offs < buf_len) {
            ch = buffer[buf_offs++];
            applink_parse_char(self, ch);
        }

        for (i = 0;i < sizeof(processors)/sizeof(processors[0]);i++) {
            result = processors[i](self);
            if (result == APPLINK_ERROR) { // something wrong
                return -1;
            } else if (result == APPLINK_OK) {
                continue;
            } else if (result == APPLINK_BREAK) {
                break;
            } else {
                printf("Warning: unexpected process result = %d\n", result);
            }
        }
    }

    return 0;
}

void applink_close(applink_handle_t* self)
{
    memset(self, 0, sizeof(applink_handle_t));
}




