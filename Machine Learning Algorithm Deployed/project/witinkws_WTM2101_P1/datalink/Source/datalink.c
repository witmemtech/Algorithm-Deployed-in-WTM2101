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
    uint32_t max_bytes_size = DATALINK_MAX_PAYLOAD_LEN - 2*sizeof(uint32_t);
    if (data_length > max_bytes_size) {
        return -1;
    }
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

int datalink_encode_debug(
        datalink_message_t* msg,
        uint8_t     seq,
        const char* str,
        int         cnt)
{
    datalink_msg_debug_t* pkg = (datalink_msg_debug_t*)msg;
    if (cnt > DATALINK_MAX_PAYLOAD_LEN) {
        return -1;
    }
    pkg->header.u.msgid = DATALINK_MSG_ID_DEBUG;
    pkg->header.u.dlen  = cnt;
    memcpy(pkg->raw, str, cnt);
    return datalink_encode(msg, seq);
}

#ifndef _WIN32
//
//  for arm/riscv only, not x86
//
int datalink_encode_jtag_report(
        datalink_message_t*         msg,
        uint8_t                     seq,
        uint32_t                    version,
        uint32_t                    format,
        const datalink_jtag_buf_t*  txctrl,
        const datalink_jtag_buf_t*  rxctrl,
        uint32_t                    block_size)
{
    datalink_msg_jtag_report_t* info = (datalink_msg_jtag_report_t*)msg;
    info->header.u.msgid= DATALINK_MSG_ID_JTAG_REPORT;
    info->header.u.dlen = sizeof(datalink_msg_jtag_report_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    info->version       = version;
    info->format        = format;

    info->tx_buff_size  = txctrl->size;
    info->tx_buff_addr  = (uint32_t)(txctrl->buff);
    info->tx_head_addr  = (uint32_t)&(txctrl->head);
    info->tx_tail_addr  = (uint32_t)&(txctrl->tail);

    info->rx_buff_size  = rxctrl->size;
    info->rx_buff_addr  = (uint32_t)(rxctrl->buff);
    info->rx_head_addr  = (uint32_t)&(rxctrl->head);
    info->rx_tail_addr  = (uint32_t)&(rxctrl->tail);

    info->block_size    = block_size;

    return datalink_encode(msg, seq);
}
#endif

int datalink_encode_file_data2(
        datalink_message_t* msg,
        uint8_t     seq,
        uint32_t    fileid,
        uint32_t    dataid,
        const void* data_buffer,
        uint32_t    data_length)
{
    datalink_msg_file_data2_t* data2 = (datalink_msg_file_data2_t*)msg;
    uint32_t max_bytes_size = DATALINK_MAX_PAYLOAD_LEN - 2*sizeof(uint32_t);
    if (data_length > max_bytes_size) {
        return -1;
    }
    data2->header.u.msgid  = DATALINK_MSG_ID_FILE_DATA2;
    data2->header.u.dlen   = 2*sizeof(uint32_t) + data_length;
    data2->fileid          = fileid;
    data2->dataid          = dataid;
    memcpy(data2->data, data_buffer, data_length);
    return datalink_encode(msg, seq);
}

int datalink_encode_file_eof(
        datalink_message_t* msg,
        uint8_t     seq,
        uint32_t    fileid,
        uint32_t    result)
{
    datalink_msg_file_eof_t* eof = (datalink_msg_file_eof_t*)msg;
    eof->header.u.msgid = DATALINK_MSG_ID_FILE_EOF;
    eof->header.u.dlen  = sizeof(datalink_msg_file_eof_t) - SIZEOF_DATALINK_MESSAGE_HEADER;
    eof->fileid         = fileid;
    eof->result         = result;
    return datalink_encode(msg, seq);
}

int datalink_encode_spectrum_mask(
        datalink_message_t* msg,
        uint8_t             seq,
        const char          label[8],
        const float*        mask_buffer,
        uint32_t            mask_count)
{
    datalink_msg_spectrum_mask_t* mask_msg = (datalink_msg_spectrum_mask_t*)msg;
    uint32_t max_count = DATALINK_MSG_SPECTRUM_MASK_MAX_ITEM_COUNT;
    if (mask_count > max_count) {
        return -1;
    }
    mask_msg->header.u.msgid  = DATALINK_MSG_ID_SPECTRUM_MASK;
    mask_msg->header.u.dlen   = 8*sizeof(char) + mask_count * sizeof(float);
    strncpy(mask_msg->label, label, 8);
    memcpy(mask_msg->mask, mask_buffer, mask_count * sizeof(float));
    return datalink_encode(msg, seq);
}

int datalink_encode_command(
        datalink_message_t* msg,
        uint8_t     seq,
        const char* str,
        int         cnt)
{
    datalink_msg_command_t* pkg = (datalink_msg_command_t*)msg;
    if (cnt > DATALINK_MAX_PAYLOAD_LEN) {
        return -1;
    }
    pkg->header.u.msgid = DATALINK_MSG_ID_COMMAND;
    pkg->header.u.dlen  = cnt;
    memcpy(pkg->data, str, cnt);
    return datalink_encode(msg, seq);
}

int datalink_encode_status(
        datalink_message_t* msg,
        uint8_t     seq,
        uint32_t    errcode,
        const char* str,
        int         cnt)
{
    datalink_msg_status_t* pkg = (datalink_msg_status_t*)msg;
    if (cnt > DATALINK_MAX_PAYLOAD_LEN - sizeof(uint32_t)) {
        return -1;
    }
    pkg->header.u.msgid = DATALINK_MSG_ID_STATUS;
    pkg->header.u.dlen  = sizeof(uint32_t) + cnt;
    pkg->errcode        = errcode;
    memcpy(pkg->data, str, cnt);
    return datalink_encode(msg, seq);
}

int datalink_is_valid_message(const datalink_message_t* msg)
{
    uint8_t hchksum;
    uint16_t crcval;

    hchksum = chksum8(msg->header.bytes, 8);
    if (hchksum != 0) {
        return 0;
    }

    crcval = crc16(msg->payload, msg->header.u.dlen);
    if (crcval != msg->header.u.dcrc) {
        return 0;
    }

    return 1;
}

void datalink_print_message(const datalink_message_t* msg)
{
    printf("datalink_message_t:\n");
    printf("  .magic  = 0x%02x\n",  msg->header.u.magic);
    printf("  .seq    = 0x%02x\n",  msg->header.u.seq);
    printf("  .dlen   = %d\n",      msg->header.u.dlen);
    printf("  .dcrc   = 0x%04x\n",  msg->header.u.dcrc);

    printf("  .msgid  = %d ",      msg->header.u.msgid);
    switch (msg->header.u.msgid) {
        case DATALINK_MSG_ID_HEARTBEAT:
            printf("(heartbeat)");
            break;
        case DATALINK_MSG_ID_FILE_INFO:
            printf("(file::info)");
            break;
        case DATALINK_MSG_ID_FILE_DATA:
            printf("(file::data)");
            break;
        case DATALINK_MSG_ID_FILE_ACK:
            printf("(file::ack)");
            break;
        case DATALINK_MSG_ID_FILE_NAK:
            printf("(file::nak)");
            break;
        case DATALINK_MSG_ID_FILE_CRC:
            printf("(file::crc)");
            break;
        case DATALINK_MSG_ID_BUSY:
            printf("(busy)");
            break;
        case DATALINK_MSG_ID_CONTINUE:
            printf("(continue)");
            break;
        case DATALINK_MSG_ID_DEBUG:
            printf("(debug)");
            break;
        case DATALINK_MSG_ID_FILE_DATAEX:
            printf("(file::dataex)");
            break;
        case DATALINK_MSG_ID_JTAG_REPORT:
            printf("(jtag::report)");
            break;
        case DATALINK_MSG_ID_FILE_DATA2:
            printf("(file::data2)");
        case DATALINK_MSG_ID_FILE_EOF:
            printf("(file:eof)");
            break;
        case DATALINK_MSG_ID_SPECTRUM_MASK:
            printf("(spectrum:mask)");
            break;
        case DATALINK_MSG_ID_COMMAND:
            printf("(command)");
            break;
        case DATALINK_MSG_ID_STATUS:
            printf("(status)");
            break;
        default:
            printf("(unknown)");
            break;
    }
    printf("\n");

    printf("  .hchksum= 0x%02x\n",  msg->header.u.hchksum);
    printf("  ---BEGIN---\n");
    for (int i = 0;i < (int)msg->header.u.dlen;i++) {
        if ((i % 8) == 0) {
            printf("  ");
        }
        printf("%02X ", msg->payload[i] & 0xFF);
        if ((i % 8) == 7) {
            printf("\n");
        }
    }
    if (msg->header.u.dlen % 8 != 0) {
        printf("\n");
    }
    printf("  ---END---\n");

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


