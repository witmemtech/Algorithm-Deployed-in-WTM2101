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
#include <wtm2101.h>
#include <wtm2101_hal.h>

#include "crc.h"
#include "datalink.h"
#include "jtaglink_rv32.h"

int jtaglink_init(jtaglink_handle_t* inst, int blocksize)
{
    memset(inst, 0, sizeof(jtaglink_handle_t));
    inst->recv_tmo    = 500;
    inst->send_tmo    = 1000;

    inst->rx_ctrl.size = JTAGXFER_FIFO_DEPTH;
    inst->rx_ctrl.buff = inst->rxbuff;
    inst->tx_ctrl.size = JTAGXFER_FIFO_DEPTH;
    inst->tx_ctrl.buff = inst->txbuff;

    inst->blocksize   = blocksize;
    return 0;
}

int jtaglink_reset(jtaglink_handle_t* inst)
{
    memset(&inst->link, 0, sizeof(datalink_status_t));

    inst->ts = 0;

    inst->tx_seq = 0;
    inst->tx_ctrl.head = 0;
    inst->tx_ctrl.tail = 0;

    inst->rx_ctrl.head = 0;
    inst->rx_ctrl.tail = 0;
    inst->msg = NULL;

    ECLIC_ClearPendingIRQ(3);

    return 0;
}

int jtaglink_wait_handshake(jtaglink_handle_t* inst)
{
    datalink_encode_jtag_report(
            &inst->tx_msg,
            inst->tx_seq,
            0x20221230, // hex-string
            0x4649464F, // big-endian, "\x46\x49\x46\4F" is "FIFO"
            &inst->tx_ctrl,
            &inst->rx_ctrl,
            inst->blocksize);
    inst->tx_seq++;

    printf("Info: wait handshake...\r\n");
    memset(&inst->rx_msg, 0, sizeof(datalink_message_t));
    jtaglink_ll_xfer(&inst->tx_msg, &inst->rx_msg);
    if (!datalink_is_valid_message(&inst->rx_msg)) {
        printf("Error: invalid response\r\n");
        return 0;
    }
    if (inst->rx_msg.header.u.msgid != DATALINK_MSG_ID_HEARTBEAT) {
        printf("Error: unexpcted response\r\n");
        return 0;
    }

    return 1;
}

int jtaglink_flush(jtaglink_handle_t* inst)
{
    uint32_t t0;
    uint32_t t1;
    uint32_t nr_bytes;

    // wait txfifo
    t0 = HAL_GetTick();
    while (1) {
        t1 = HAL_GetTick();
        if (t1 - t0 > inst->send_tmo) {
            return 0;
        }
        nr_bytes = inst->tx_ctrl.tail - inst->tx_ctrl.head;
        if (nr_bytes == 0) {
            break;
        }
    }

    // flush rxfifo
    inst->rx_ctrl.head = inst->rx_ctrl.tail;
    return 1;
}

int jtaglink_get_rxfifo_used(jtaglink_handle_t* inst)
{
    int nr_bytes = inst->rx_ctrl.tail - inst->rx_ctrl.head;
    return nr_bytes;
}

int jtaglink_get_txfifo_free(jtaglink_handle_t* inst)
{
    int nr_bytes;
    nr_bytes = inst->tx_ctrl.tail - inst->tx_ctrl.head;
    nr_bytes = inst->tx_ctrl.size-1 - nr_bytes;
    return nr_bytes;
}

int jtaglink_send_msg(jtaglink_handle_t* inst, const datalink_message_t* msg)
{
    int length;
    int nr_bytes;
    int offs;
    uint8_t* dst;
    uint8_t* src;
    uint32_t t0;
    uint32_t t1;

    length = SIZEOF_DATALINK_MESSAGE_HEADER + msg->header.u.dlen;

    ////////////////////////////////////////////////////////
    //
    //  wait txfifo not full
    //
    t0 = HAL_GetTick();
    while (1) {
        t1 = HAL_GetTick();
        if (t1 - t0 > inst->send_tmo) {
            printf("Error: txfifo full\r\n");
            return -1;
        }
        nr_bytes = inst->tx_ctrl.tail - inst->tx_ctrl.head;
        if (nr_bytes + length < inst->tx_ctrl.size) {
            break;
        }
    }

    ////////////////////////////////////////////////////////
    //
    //  first part
    //
    offs = inst->tx_ctrl.tail % inst->tx_ctrl.size;
    nr_bytes = inst->tx_ctrl.size - offs;
    if (nr_bytes > length) {
        nr_bytes = length;
    }
    src = (uint8_t*)msg;
    dst = ((uint8_t*)inst->tx_ctrl.buff) + offs;
    memcpy(dst, src, nr_bytes);
    inst->tx_ctrl.tail += nr_bytes;
    src += nr_bytes;

    ////////////////////////////////////////////////////////
    //
    //  second part
    //
    if (nr_bytes < length) {
        nr_bytes = length - nr_bytes;
        offs = inst->tx_ctrl.tail % inst->tx_ctrl.size;
        dst = ((uint8_t*)inst->tx_ctrl.buff) + offs;
        memcpy(dst, src, nr_bytes);
        inst->tx_ctrl.tail += nr_bytes;
        src += nr_bytes;
    }

    return length;
}

int jtaglink_wait_msg(jtaglink_handle_t* inst, datalink_message_t* msg)
{
    int nr_bytes;
    int offs;
    uint32_t t0;
    uint32_t t1;
    uint8_t ch;

    t0 = HAL_GetTick();
    while (1) {
        t1 = HAL_GetTick();
        if (t1 - t0 > inst->recv_tmo) {
            return 0;
        }
        nr_bytes = inst->rx_ctrl.tail - inst->rx_ctrl.head;
        if (nr_bytes <= 0) {
            continue;
        }

        offs = inst->rx_ctrl.head % inst->rx_ctrl.size;
        ch = ((uint8_t*)inst->rx_ctrl.buff)[offs];
        inst->rx_ctrl.head++;
        if (datalink_parse_char(ch, msg, (void*)&inst->link)) {
            return 1;
        }
    }

    return 0;
}

int jtaglink_recv_file_info(jtaglink_handle_t* inst)
{
    if (inst->msg == NULL) {
        return 0;
    }

    if (inst->msg->header.u.msgid != DATALINK_MSG_ID_FILE_INFO) {
        return 0;
    }

    ////////////////////////////////////////////////////////
    //
    //  received <info>
    //  callback_reset()
    //  send <ack>
    //
    const datalink_msg_file_info_t* info_msg;
    info_msg = (datalink_msg_file_info_t*)inst->msg;
    datalink_encode_file_ack(
            &inst->tx_msg,
            inst->tx_seq,
            info_msg->fileid,
            0);
    inst->tx_seq++;

    inst->tx_fileid = info_msg->fileid;
    inst->rx_fileid = info_msg->fileid;

    jtagxfer_callback_reset();

    jtaglink_send_msg(inst, &inst->tx_msg);

    ////////////////////////////////////////////////////////
    //
    //  send <info>
    //
    datalink_encode_file_info(
            &inst->tx_msg,
            inst->tx_seq,
            "response.wav",
            info_msg->fileid,
            info_msg->length);
    inst->tx_seq++;
    jtaglink_send_msg(inst, &inst->tx_msg);

    ////////////////////////////////////////////////////////
    //
    //  send <debug>
    //
    int nr_bytes;
    datalink_msg_debug_t* debug_msg;
    debug_msg = (datalink_msg_debug_t*)&inst->tx_msg;

    nr_bytes = jtagxfer_callback_debug(debug_msg->raw, DATALINK_MAX_PAYLOAD_LEN);
    if (nr_bytes > DATALINK_MAX_PAYLOAD_LEN) {
        nr_bytes = DATALINK_MAX_PAYLOAD_LEN;
    }
    debug_msg->header.u.msgid = DATALINK_MSG_ID_DEBUG;
    debug_msg->header.u.dlen  = nr_bytes;
    datalink_encode(&inst->tx_msg, inst->tx_seq);
    jtaglink_send_msg(inst, &inst->tx_msg);


    inst->msg = NULL;
    return 1;
}

int jtaglink_recv_file_data(jtaglink_handle_t* inst)
{
    int nr_bytes;
    int count;

    if (inst->msg == NULL) {
        return 0;
    }

    if (inst->msg->header.u.msgid != DATALINK_MSG_ID_FILE_DATA) {
        return 0;
    }

    const datalink_msg_file_data_t* data_rx;
    datalink_msg_file_data_t* data_tx;
    data_rx = (datalink_msg_file_data_t*)inst->msg;
    data_tx = (datalink_msg_file_data_t*)&inst->tx_msg;

    nr_bytes = inst->msg->header.u.dlen - sizeof(uint32_t) - sizeof(uint32_t);
    if (nr_bytes > inst->blocksize) {
        printf("Error: received %d bytes, but user blocksize(%d) too small\r\n",
                nr_bytes, inst->blocksize);
        inst->msg = NULL;
        return -1;
    }

    ////////////////////////////////////////////////////////
    //
    //  data
    //
    jtagxfer_callback_process_mono(
            (int16_t*)data_rx->data,
            (int16_t*)data_tx->data,
            nr_bytes);

    data_tx->header.u.msgid= data_rx->header.u.msgid;
    data_tx->header.u.dlen = data_rx->header.u.dlen;
    data_tx->fileid = data_rx->fileid;
    data_tx->dataid = data_rx->dataid;
    datalink_encode(&inst->tx_msg, inst->tx_seq);
    inst->tx_seq++;

    jtaglink_send_msg(inst, &inst->tx_msg);
    inst->msg = NULL;

    ////////////////////////////////////////////////////////
    //
    //  spectrum mask
    //
    //
    //  for 32bits processor,
    //  compiler alloc var in stack or global 
    //  always align 32bits.
    //
    //  so it will be ok.
    //
    datalink_msg_spectrum_mask_t* mask_msg;
    uint8_t* payload;
    mask_msg = (datalink_msg_spectrum_mask_t*)&inst->tx_msg;
    payload = ((uint8_t*)&inst->tx_msg) + SIZEOF_DATALINK_MESSAGE_HEADER + 8*sizeof(char);
    memset(mask_msg->label, 0, 8*sizeof(char));
    count = jtagxfer_callback_spectrum_mask(
            mask_msg->label,
            (float*)payload,
            DATALINK_MSG_SPECTRUM_MASK_MAX_ITEM_COUNT);
    if (count > 0) {
        inst->tx_msg.header.u.msgid = DATALINK_MSG_ID_SPECTRUM_MASK;
        inst->tx_msg.header.u.dlen  = 8*sizeof(char) + count * sizeof(float);
        datalink_encode(&inst->tx_msg, inst->tx_seq);
        inst->tx_seq++;
        jtaglink_send_msg(inst, &inst->tx_msg);
    }

    return 1;
}

int jtaglink_recv_file_data2(jtaglink_handle_t* inst)
{
    int nr_bytes;
    int count;

    if (inst->msg == NULL) {
        return 0;
    }

    if (inst->msg->header.u.msgid != DATALINK_MSG_ID_FILE_DATA2) {
        return 0;
    }

    const datalink_msg_file_data_t* data_rx;
    datalink_msg_file_data_t* data_tx;
    data_rx = (datalink_msg_file_data_t*)inst->msg;
    data_tx = (datalink_msg_file_data_t*)&inst->tx_msg;

    nr_bytes = inst->msg->header.u.dlen - sizeof(uint32_t) - sizeof(uint32_t);
    if (nr_bytes > inst->blocksize) {
        printf("Error: received %d bytes, but user blocksize(%d) too small\r\n",
                nr_bytes, inst->blocksize);
        inst->msg = NULL;
        return -1;
    }

    ////////////////////////////////////////////////////////
    //
    //  data
    //
    jtagxfer_callback_process_stereo(
            (int16_t*)data_rx->data,
            (int16_t*)data_tx->data,
            nr_bytes);

    data_tx->header.u.msgid= data_rx->header.u.msgid;
    data_tx->header.u.dlen = data_rx->header.u.dlen;
    data_tx->fileid = data_rx->fileid;
    data_tx->dataid = data_rx->dataid;
    datalink_encode(&inst->tx_msg, inst->tx_seq);
    inst->tx_seq++;

    jtaglink_send_msg(inst, &inst->tx_msg);
    inst->msg = NULL;

    ////////////////////////////////////////////////////////
    //
    //  spectrum mask
    //
    //
    //  for 32bits processor,
    //  compiler alloc var in stack or global 
    //  always align 32bits.
    //
    //  so it will be ok.
    //
    datalink_msg_spectrum_mask_t* mask_msg;
    uint8_t* payload;
    mask_msg = (datalink_msg_spectrum_mask_t*)&inst->tx_msg;
    payload = ((uint8_t*)&inst->tx_msg) + SIZEOF_DATALINK_MESSAGE_HEADER + 8*sizeof(char);
    memset(mask_msg->label, 0, 8*sizeof(char));
    count = jtagxfer_callback_spectrum_mask(
            mask_msg->label,
            (float*)payload,
            DATALINK_MSG_SPECTRUM_MASK_MAX_ITEM_COUNT);
    if (count > 0) {
        inst->tx_msg.header.u.msgid = DATALINK_MSG_ID_SPECTRUM_MASK;
        inst->tx_msg.header.u.dlen  = 8*sizeof(char) + count * sizeof(float);
        datalink_encode(&inst->tx_msg, inst->tx_seq);
        inst->tx_seq++;
        jtaglink_send_msg(inst, &inst->tx_msg);
    }


    return 1;
}

int jtaglink_recv_file_eof(jtaglink_handle_t* inst)
{
    if (inst->msg == NULL) {
        return 0;
    }

    if (inst->msg->header.u.msgid != DATALINK_MSG_ID_FILE_EOF) {
        return 0;
    }

    datalink_encode_file_eof(
            &inst->tx_msg,
            inst->tx_seq,
            inst->tx_fileid,
            0);
    inst->tx_seq++;

    jtaglink_send_msg(inst, &inst->tx_msg);
    inst->msg = NULL;

    return 1;
}

int jtaglink_send_data(
        jtaglink_handle_t* inst,
        uint32_t fileid,
        uint32_t offset,
        void*    buffer,
        uint32_t length)
{
    uint32_t nr_bytes;

    datalink_encode_file_data(
            &inst->tx_msg,
            inst->tx_seq,
            fileid,
            offset,
            buffer,
            length);
    inst->tx_seq++;

    nr_bytes = jtaglink_get_txfifo_free(inst);
    if (nr_bytes <= SIZEOF_DATALINK_MESSAGE_HEADER + inst->tx_msg.header.u.dlen) {
        return -1;
    }

    jtaglink_send_msg(inst, &inst->tx_msg);
    return nr_bytes;
}


