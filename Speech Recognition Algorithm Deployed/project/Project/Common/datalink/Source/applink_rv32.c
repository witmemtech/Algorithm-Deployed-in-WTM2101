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
#include <string.h>
#include <stdint.h>

#include <basic_config.h>
#include <wtm2101_config.h>
#include <WTM2101.h>
#include <wtm2101_hal.h>
//#include <bb04p1_hal.h>

#include "crc.h"
#include "datalink.h"
#include "applink_rv32.h"

void applink_init(applink_handle_t* self, uint32_t block_size)
{
   memset(self, 0, sizeof(applink_handle_t));
   self->block_size = block_size;
}



// @retval 0    ignore
// @retval 1    packet match
int applink_send_heartbeat(applink_handle_t* self)
{
    if (self->ts - self->ts_heartbeat > 1000) {
        printf("Info: send heartbeat\r\n");
        self->ts_heartbeat = self->ts;
        datalink_encode_heartbeat(
                &self->tx_ctrl_msg,
                self->link_tx_seq,
                FW_DCCRN_v2_1_0,
                0x20220701,
                0x00184000,
                (uint32_t)HAL_GetTick());
        self->link_tx_seq++;
        uart_send_msg(&self->tx_ctrl_msg);
    }

    return 1;
}

int applink_recv_heartbeat(applink_handle_t* self)
{
    if (self->msg == NULL) {
          return 0;
    }

    if (self->msg->header.u.msgid != DATALINK_MSG_ID_HEARTBEAT) {
        return 0;
    }

    self->msg = NULL;
    return 1;
}

int applink_recv_file_ack(applink_handle_t* self)
{
    if (self->msg == NULL) {
        return 0;
    }

    if (self->msg->header.u.msgid != DATALINK_MSG_ID_FILE_ACK) {
        return 0;
    }

    if (self->tx_file_offset == self->tx_file_length) {
        datalink_encode_file_crc(
                &self->tx_ctrl_msg,
                self->link_tx_seq,
                self->fileid,
                self->tx_file_length,
                self->tx_file_crc);
        uart_send_msg(&self->tx_ctrl_msg);
        self->link_tx_seq++;
    }
    self->is_txdata_ack = 0;

    self->msg = NULL;
    return 1;
}

int applink_recv_file_info(applink_handle_t* self)
{
    if (self->msg == NULL) {
        return 0;
    }

    if (self->msg->header.u.msgid != DATALINK_MSG_ID_FILE_INFO) {
        return 0;
    }

    const datalink_msg_file_info_t* info = (datalink_msg_file_info_t*)self->msg;

    printf("Info: prepare new wav file\r\n");
    self->is_txdata_ack    = 0;
    self->rx_file_length = info->length;
    self->rx_file_offset = 0;
    self->rx_file_crc    = crc16_init();

    uartxfer_callback_reset();

    self->fileid++;
    self->tx_file_length = self->rx_file_length;
    self->tx_file_offset = 0;
    self->tx_file_crc    = crc16_init();
    datalink_encode_file_info(
            &self->tx_ctrl_msg,
            self->link_tx_seq,
            "denoise",
            self->fileid,
            self->tx_file_length);
    self->link_tx_seq++;
    uart_send_msg(&self->tx_ctrl_msg);

    datalink_encode_file_ack(
            &self->tx_ctrl_msg,
            self->link_tx_seq,
            info->fileid,
            0);
    self->link_tx_seq++;
    uart_send_msg(&self->tx_ctrl_msg);

    self->msg = NULL;
    return 1;
}

int applink_recv_file_data(applink_handle_t* self)
{
    static int16_t buff_in[APPLINK_FRAME_SIZE] = {0};
    static int16_t buff_out[APPLINK_FRAME_SIZE] = {0};
    int nr_bytes;

    if (self->msg == NULL) {
        return 0;
    }

    if (self->msg->header.u.msgid != DATALINK_MSG_ID_FILE_DATA) {
        return 0;
    }

    const datalink_msg_file_data_t* data = (datalink_msg_file_data_t*)self->msg;
    nr_bytes = data->header.u.dlen - 2*sizeof(uint32_t);

    if (data->dataid < self->rx_file_offset) {
        printf("Warning: data duplicated, resend last data\r\n");

        datalink_encode(&self->tx_data_msg, self->link_tx_seq);
        self->link_tx_seq++;
        uart_send_msg(&self->tx_data_msg);

        datalink_encode_file_ack(
                &self->tx_ctrl_msg,
                self->link_tx_seq,
                data->fileid,
                data->dataid);
        self->link_tx_seq++;
        uart_send_msg(&self->tx_ctrl_msg);

        self->msg = NULL;
        return 1;
    }

    if (self->rx_file_offset < data->dataid) {
        printf("Warning: !!!Impossible!!! data lost\r\n");
        datalink_encode_file_nak(
                &self->tx_ctrl_msg,
                self->link_tx_seq,
                data->fileid,
                data->dataid);
        self->link_tx_seq++;
        uart_send_msg(&self->tx_ctrl_msg);

        self->msg = NULL;
        return 1;
    } 

    if (nr_bytes > self->block_size) {
        printf("Error: %d bytes (actual) > %d (block_size)\r\n", nr_bytes, self->block_size);
        datalink_encode_file_nak(
                &self->tx_ctrl_msg,
                self->link_tx_seq,
                data->fileid,
                data->dataid);
        self->link_tx_seq++;
        uart_send_msg(&self->tx_ctrl_msg);

        self->msg = NULL;
        return 1;
    }

    if (self->is_txdata_ack) {
        printf("Info: last data not ack, ignore host data packet\r\n");
        printf("Info: resend last data packet\r\n");
        datalink_encode(&self->tx_data_msg, self->link_tx_seq);
        self->link_tx_seq++;
        uart_send_msg(&self->tx_data_msg);

        self->msg = NULL;
        return 1;
    }

    memcpy(buff_in, data->data, nr_bytes);

    uartxfer_callback_process(buff_in, buff_out);

    datalink_encode_file_data(
            &self->tx_data_msg,
            self->link_tx_seq,
            self->fileid,
            self->tx_file_offset,
            buff_out,
            nr_bytes);
    self->link_tx_seq++;
    self->is_txdata_ack = 1;
    uart_send_msg(&self->tx_data_msg);

    self->rx_file_crc = crc16_update(
            self->rx_file_crc,
            data->data,
            nr_bytes);
    self->rx_file_offset += nr_bytes;

    self->tx_file_crc = crc16_update(
            self->tx_file_crc,
            buff_out,
            nr_bytes);
    self->tx_file_offset += nr_bytes;


    datalink_encode_file_ack(
            &self->tx_ctrl_msg,
            self->link_tx_seq,
            data->fileid,
            data->dataid);
    self->link_tx_seq++;
    uart_send_msg(&self->tx_ctrl_msg);

    if (self->rx_file_offset >= self->rx_file_length) {
        printf("Info: all data received\r\n");
    }

    self->msg = NULL;
    return 0;
}

int applink_recv_file_crc(applink_handle_t* self)
{
    if (self->msg == NULL) {
        return 0;
    }

    if (self->msg->header.u.msgid != DATALINK_MSG_ID_FILE_CRC) {
        return 0;
    }

    const datalink_msg_file_crc_t* crc = (datalink_msg_file_crc_t*)self->msg;
    if (crc->crcvalue != self->rx_file_crc) {
        printf("Error: data crc not match, 0x%08x != 0x%08x (expect)\r\n",
                self->rx_file_crc, crc->crcvalue);
    } else {
        printf("Info: final data CRC match\r\n");
    }

    self->msg = NULL;
    return 1;
}

