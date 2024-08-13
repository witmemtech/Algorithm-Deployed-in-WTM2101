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

int datalink_encode(datalink_message_t* msg, uint8_t seq)
{
    uint16_t dcrc;
    uint8_t hchksum;

    msg->header.u.magic     = DATALINK_STX;
    msg->header.u.seq       = seq;

    dcrc = crc16(msg->payload, msg->header.u.dlen);
    msg->header.u.dcrc      = dcrc;

    hchksum = chksum8(msg->header.bytes, SIZEOF_DATALINK_MESSAGE_HEADER-1);
    msg->header.u.hchksum   = ~hchksum + 1u;

    return SIZEOF_DATALINK_MESSAGE_HEADER + msg->header.u.dlen;
}


int datalink_encode_heartbeat(
        datalink_message_t* msg,
        uint8_t     seq,
        uint32_t    version,
        uint32_t    date,
        uint32_t    time,
        uint32_t    timestamp)
{
    datalink_msg_heartbeat_t* heartbeat = (datalink_msg_heartbeat_t*)msg;
    heartbeat->header.u.msgid = DATALINK_MSG_ID_HEARTBEAT;
    heartbeat->header.u.dlen  = sizeof(datalink_msg_heartbeat_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    heartbeat->version        = version;
    heartbeat->date           = date;
    heartbeat->time           = time;
    heartbeat->timestamp      = timestamp;
    return datalink_encode(msg, seq);
}

int datalink_encode_file_info(
        datalink_message_t* msg,
        uint8_t     seq,
        const char* name,
        uint32_t    fileid,
        uint32_t    length)
{
    datalink_msg_file_info_t* info = (datalink_msg_file_info_t*)msg;
    info->header.u.msgid= DATALINK_MSG_ID_FILE_INFO;
    info->header.u.dlen = sizeof(datalink_msg_file_info_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    info->fileid        = fileid;
    info->length        = length;
    strncpy(info->name, name, sizeof(info->name));
    return datalink_encode(msg, seq);
}

int datalink_encode_file_data(
        datalink_message_t* msg,
        uint8_t     seq,
        uint32_t    fileid,
        uint32_t    dataid,
        const void* data_buffer,
        uint32_t    data_length)
{
    datalink_msg_file_data_t* data = (datalink_msg_file_data_t*)msg;
    data->header.u.msgid  = DATALINK_MSG_ID_FILE_DATA;
    data->header.u.dlen   = 2*sizeof(uint32_t) + data_length;
    data->fileid          = fileid;
    data->dataid          = dataid;
    memcpy(data->data, data_buffer, data_length);
    return datalink_encode(msg, seq);
}

int datalink_encode_file_ack(
        datalink_message_t* msg,
        uint8_t     seq,
        uint32_t    fileid,
        uint32_t    dataid)
{
    datalink_msg_file_ack_t* ack = (datalink_msg_file_ack_t*)msg;
    ack->header.u.msgid = DATALINK_MSG_ID_FILE_ACK;
    ack->header.u.dlen  = sizeof(datalink_msg_file_ack_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    ack->fileid         = fileid;
    ack->dataid         = dataid;
    return datalink_encode(msg, seq);
}

int datalink_encode_file_nak(
        datalink_message_t* msg,
        uint8_t     seq,
        uint32_t    fileid,
        uint32_t    dataid)
{
    datalink_msg_file_nak_t* nak = (datalink_msg_file_nak_t*)msg;
    nak->header.u.msgid = DATALINK_MSG_ID_FILE_NAK;
    nak->header.u.dlen  = sizeof(datalink_msg_file_nak_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    nak->fileid         = fileid;
    nak->dataid         = dataid;
    return datalink_encode(msg, seq);
}

int datalink_encode_file_crc(
        datalink_message_t* msg,
        uint8_t     seq,
        uint32_t    fileid,
        uint32_t    dataid,
        uint32_t    crcvalue)
{
    datalink_msg_file_crc_t* crc = (datalink_msg_file_crc_t*)msg;
    crc->header.u.msgid = DATALINK_MSG_ID_FILE_CRC;
    crc->header.u.dlen  = sizeof(datalink_msg_file_crc_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    crc->fileid         = fileid;
    crc->dataid         = dataid;
    crc->crcvalue       = crcvalue;
    return datalink_encode(msg, seq);
}

int datalink_encode_busy(
        datalink_message_t* msg,
        uint8_t     seq)
{
    datalink_msg_busy_t* busy = (datalink_msg_busy_t*)msg;
    busy->header.u.msgid = DATALINK_MSG_ID_BUSY;
    busy->header.u.dlen  = sizeof(datalink_msg_busy_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    return datalink_encode(msg, seq);
}

int datalink_encode_continue(
        datalink_message_t* msg,
        uint8_t     seq)
{
    datalink_msg_continue_t* pkg = (datalink_msg_continue_t*)msg;
    pkg->header.u.msgid = DATALINK_MSG_ID_CONTINUE;
    pkg->header.u.dlen  = sizeof(datalink_msg_continue_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    return datalink_encode(msg, seq);
}

int datalink_parse_char(uint8_t ch, datalink_message_t* msg, datalink_status_t* status)
{
    int got_message = 0;
	uint8_t hchk;
    uint16_t crcval;
	int i;
	int j;

	switch (status->parse_state) {
	    case DATALINK_PARSE_STATE_IDLE:
            if (ch == DATALINK_STX) {
                status->parse_state = DATALINK_PARSE_STATE_RECV_HDR;
                status->bytes_received = 1;
                msg->header.bytes[0] = ch;
            }
            break;

	    case DATALINK_PARSE_STATE_RECV_HDR:
            msg->header.bytes[status->bytes_received++] = ch;

            if (status->bytes_received == 8) {
                status->bytes_received = 0;

                hchk = chksum8(msg->header.bytes, 8);
                if (hchk != 0) {
                    printf("Error: datalink::invalid header:");

                    // walk through stream and try to resync
                    for (i = 1;i < 8;i++) {
                        if (msg->header.bytes[i] == DATALINK_STX) {
                            break;
                        }
                    }
                    if (i != 8) {
                        j = 0;
                        printf("resync\n");
                        status->bytes_received = 8 - i;
                        for (;i < 8;i++) {
                            msg->header.bytes[j++] = msg->header.bytes[i];
                        }
                        printf("\n");
                    } else {
                        for (i = 0;i < 8;i++) {
                            printf(" %02X", msg->header.bytes[i] & 0xFF);
                        }
                        printf("\n");
                        status->parse_state = DATALINK_PARSE_STATE_IDLE;
                    }

                } else {
                    status->parse_state = DATALINK_PARSE_STATE_RECV_PAYLOAD;
                    status->bytes_expect = msg->header.u.dlen;
                }
            }
            break;

	    case DATALINK_PARSE_STATE_RECV_PAYLOAD:
            msg->payload[status->bytes_received++] = ch;
            if (status->bytes_received == status->bytes_expect) {
                crcval = crc16(msg->payload, msg->header.u.dlen);
                if (crcval != msg->header.u.dcrc) {
                    printf("Error: datalink::invalid crc, %04X != dcrc(%04X)\r\n",
                            crcval, msg->header.u.dcrc);
                } else {
                    got_message = 1;
                }
                status->parse_state = DATALINK_PARSE_STATE_IDLE;
                status->bytes_received = 0;
            }
            break;

        default:
            status->parse_state = DATALINK_PARSE_STATE_IDLE;
            break;
    }

    return got_message;
}


