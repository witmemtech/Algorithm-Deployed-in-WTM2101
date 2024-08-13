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
#include <time.h>

#include "crc.h"
#include "datalink.h"
#include "applink.h"

#include "JLinkARM.h"
#include "JLinkRV32.h"
#include "riscv_encoding.h"
#include "riscv_devices.h"

#include "jtaglink_win32.h"

static jtaglink_handle_t app;

// int jtagxfer_sendrecv_msg(
//      const datalink_message_t* txmsg,
//      datalink_message_t* rxmsg);
int jtaglink_get_ll_xfer_parameter(uint32_t* txmsg_addr, uint32_t* rxmsg_addr)
{
    *txmsg_addr = JLINKARM_ReadReg(RV32REG_A0);
    *rxmsg_addr = JLINKARM_ReadReg(RV32REG_A1);
    return 0;
}

int jtaglink_is_valid_address(uint32_t addr)
{
    if ((0x00000000 <= addr) && (addr <= 0x0003FFFF)) {
        return 1;
    }
    if ((0x20000000 <= addr) && (addr <= 0x2002FFFF)) {
        return 1;
    }
    if ((0x30000000 <= addr) && (addr <= 0x3004FFFF)) {
        return 1;
    }
    return 0;
}

int jtaglink_wait_handshake(jtaglink_handle_t* inst)
{
    const datalink_msg_jtag_report_t* report;
    uint32_t rv32_request_msg_addr;
    uint32_t rv32_response_msg_addr;
    int nr_bytes;

    if (JLINKARM_RV32_WaitEbreak(inst->heartbeat_tmo) != 0) {
        printf("Error: cpu not enter ebreak mode\n");
        return -1;
    }

    jtaglink_get_ll_xfer_parameter(&rv32_request_msg_addr, &rv32_response_msg_addr);
    if (!jtaglink_is_valid_address(rv32_request_msg_addr)) {
        printf("Error: request_msg address invalid\n");
        return -1;
    }
    if (!jtaglink_is_valid_address(rv32_response_msg_addr)) {
        printf("Error: response_msg address invalid\n");
        return -1;
    }
    //printf("Info: txmsg@%08x\n", rv32_request_msg_addr);
    //printf("Info: rxmsg@%08x\n", rv32_response_msg_addr);

    JLINKARM_ReadMem(
            rv32_request_msg_addr,
            sizeof(datalink_message_t),
            &inst->rx_msg);
    if (!datalink_is_valid_message(&inst->rx_msg)) {
        printf("Error: invalid datalink_is_valid_message\n");
        return -1;
    }
    //datalink_print_message(&inst->rx_msg);


    ////////////////////////////////////////////////////////
    //
    //  decode buffers
    //
    report = (const datalink_msg_jtag_report_t*)&inst->rx_msg;

    // pc.rxfifo <-- dev.txfifo
    inst->rx_buff_size = report->tx_buff_size;
    inst->rx_buff_addr = report->tx_buff_addr;
    inst->rx_head_addr = report->tx_head_addr;
    inst->rx_tail_addr = report->tx_tail_addr;
    // pc.txfifo --> dev.rxfifo
    inst->tx_buff_size = report->rx_buff_size;
    inst->tx_buff_addr = report->rx_buff_addr;
    inst->tx_head_addr = report->rx_head_addr;
    inst->tx_tail_addr = report->rx_tail_addr;
    // update block_size
    if (report->block_size < inst->block_size) {
        inst->block_size   = report->block_size;
    }
 
    ////////////////////////////////////////////////////////
    //
    //  debug
    //
    //  // pc.rxfifo <-- dev.txfifo
    //  printf(".rv32_txfifo.buffer = 0x%08x\n", inst->rx_buff_addr);
    //  printf(".rv32_txfifo.size   = 0x%08x\n", inst->rx_buff_size);
    //  JLINKARM_ReadMem(inst->rx_head_addr, sizeof(uint32_t), &value);
    //  printf(".rv32_txfifo.head   = 0x%08x\n", value);
    //  JLINKARM_ReadMem(inst->rx_tail_addr, sizeof(uint32_t), &value);
    //  printf(".rv32_txfifo.tail   = 0x%08x\n", value);

    //  // pc.txfifo --> dev.rxfifo
    //  printf(".rv32_rxfifo.buffer = 0x%08x\n", inst->tx_buff_addr);
    //  printf(".rv32_rxfifo.size   = 0x%08x\n", inst->tx_buff_size);
    //  JLINKARM_ReadMem(inst->tx_head_addr, sizeof(uint32_t), &value);
    //  printf(".rv32_rxfifo.head   = 0x%08x\n", value);
    //  JLINKARM_ReadMem(inst->tx_tail_addr, sizeof(uint32_t), &value);
    //  printf(".rv32_rxfifo.tail   = 0x%08x\n", value);
    //  printf("\n");


    ////////////////////////////////////////////////////////
    //
    //  send handshake package
    //
    datalink_encode_heartbeat(
                &inst->tx_msg,
                inst->tx_seq,
                FW_DCCRN_v2_1_0,
                0x20221230,
                0x00133002,
                (uint32_t)user_get_tick());
    inst->tx_seq++;
    nr_bytes = SIZEOF_DATALINK_MESSAGE_HEADER + inst->tx_msg.header.u.dlen;
    JLINKARM_WriteMem(
            rv32_response_msg_addr,
            nr_bytes,
            &inst->tx_msg);

    jtagxfer_callback_connected(inst,
            report->version,
            report->format);

    return 1;
}

int jtaglink_send_msg(jtaglink_handle_t* inst, const datalink_message_t* msg)
{
    uint32_t length;
    uint32_t fifo_buff_addr;
    uint32_t fifo_size;
    uint32_t fifo_head;
    uint32_t fifo_tail;
    uint32_t nr_bytes;
    uint32_t offs;
    const uint8_t* data;

    if (user_kbhit()) {
        return 0;
    }

    length         = SIZEOF_DATALINK_MESSAGE_HEADER + msg->header.u.dlen;
    data           = (uint8_t*)msg;

    fifo_buff_addr = inst->tx_buff_addr;
    fifo_size      = inst->tx_buff_size;

    JLINKARM_ReadMem(
            inst->tx_head_addr,
            sizeof(uint32_t),
            &fifo_head);

    JLINKARM_ReadMem(
            inst->tx_tail_addr,
            sizeof(uint32_t),
            &fifo_tail);

    nr_bytes = fifo_tail - fifo_head;
    if (nr_bytes + length >= fifo_size) {
        printf("Error: download fifo full\n");
        return -1;
    }

    // write first part
    offs = fifo_tail % fifo_size;
    nr_bytes = fifo_size - offs;
    if (nr_bytes > length) {
        nr_bytes = length;
    }
    JLINKARM_WriteMem(fifo_buff_addr + offs, nr_bytes, data);
    fifo_tail += nr_bytes;
    data += nr_bytes;

    // write second part
    offs = fifo_tail % fifo_size;
    if (nr_bytes < length) {
        nr_bytes = length - nr_bytes;
        JLINKARM_WriteMem(fifo_buff_addr + offs, nr_bytes, data);
        fifo_tail += nr_bytes;
        data += nr_bytes;
    }

    // update fifo tail
    JLINKARM_WriteMem(inst->tx_tail_addr, sizeof(uint32_t), &fifo_tail);

    return length;
}

int jtaglink_recv_msg(jtaglink_handle_t* inst, uint8_t* buffer, int maxsize)
{
    uint32_t fifo_buff_addr;
    uint32_t fifo_size;
    uint32_t fifo_head;
    uint32_t fifo_tail;
    uint32_t fifo_bytes_cnt;
    uint32_t nr_bytes;
    uint32_t offs;
    int nr_bytes_read = 0;

    if (user_kbhit()) {
        return 0;
    }

    fifo_buff_addr  = inst->rx_buff_addr;
    fifo_size       = inst->rx_buff_size;

    JLINKARM_ReadMem(
            inst->rx_head_addr,
            sizeof(uint32_t),
            &fifo_head);

    JLINKARM_ReadMem(
            inst->rx_tail_addr,
            sizeof(uint32_t),
            &fifo_tail);

    fifo_bytes_cnt = fifo_tail - fifo_head;
    if (fifo_bytes_cnt <= 0) {
        return 0;
    }
    if ((int)fifo_bytes_cnt > maxsize) {
        fifo_bytes_cnt = maxsize;
    }

    // read first part
    offs = fifo_head % fifo_size;
    nr_bytes = fifo_size - offs;
    if (nr_bytes > fifo_bytes_cnt) {
        nr_bytes = fifo_bytes_cnt;
    }
    JLINKARM_ReadMem(fifo_buff_addr + offs, nr_bytes, buffer);
    fifo_head += nr_bytes;
    buffer += nr_bytes;
    nr_bytes_read += nr_bytes;

    // read second part when fifo pointer wrapped
    if (nr_bytes_read < (int)fifo_bytes_cnt) {
        offs = fifo_head % fifo_size;
        nr_bytes = fifo_bytes_cnt - nr_bytes_read;
        JLINKARM_ReadMem(fifo_buff_addr + offs, nr_bytes, buffer);
        fifo_head += nr_bytes;
        buffer += nr_bytes;
        nr_bytes_read += nr_bytes;
    }

    // update fifo head
    JLINKARM_WriteMem(inst->rx_head_addr, sizeof(uint32_t), &fifo_head);

    return nr_bytes_read;
}

int jtaglink_wait_msg(jtaglink_handle_t* inst, datalink_message_t* msg, uint32_t timeout)
{
    while (1) {
        if (user_kbhit()) {
            return -1;
        }

        // try to read some bytes
        if ((inst->link_bufcount <= 0) || (inst->link_bufoffset >= inst->link_bufcount)) {
            uint32_t t0;
            uint32_t t1;

            inst->link_bufoffset = 0;
            t0 = (uint32_t)user_get_tick();
            while (1) {
                if (user_kbhit()) {
                    return -1;
                }

                t1 = (uint32_t)user_get_tick();
                if (t1 - t0 > timeout) {
                    return 0;
                }

                inst->link_bufcount = jtaglink_recv_msg(inst, inst->link_buffer, sizeof(inst->link_buffer));
                if (inst->link_bufcount > 0) {
                    //printf("> received %d bytes\n", bufcount);
                    break;
                }
            }
        }

        // parse stream
        while (inst->link_bufoffset < inst->link_bufcount) {
            uint8_t ch = inst->link_buffer[inst->link_bufoffset++];
            if (datalink_parse_char(ch, msg, &inst->link_status)) {
                //------debug.begin------
                //if (msg->header.u.msgid == DATALINK_MSG_ID_HEARTBEAT) {
                //    printf("Info: recv heartbeat %6d\r\n", msg->header.u.seq);
                //} else if (msg->header.u.msgid == DATALINK_MSG_ID_FILE_ACK) {
                //    printf("Info: recv ack       %6d\r\n", msg->header.u.seq);
                //} else if (msg->header.u.msgid == DATALINK_MSG_ID_FILE_INFO) {
                //    printf("Info: recv info      %6d\r\n", msg->header.u.seq);
                //} else if (msg->header.u.msgid == DATALINK_MSG_ID_FILE_DATA) {
                //    printf("Info: recv data      %6d\r\n", msg->header.u.seq);
                //} else if (msg->header.u.msgid == DATALINK_MSG_ID_FILE_CRC) {
                //    printf("Info: recv crc       %6d\r\n", msg->header.u.seq);
                //}
                //------debug.end------
                return 1;
            }
        }// end while (bufoffset < bufcount)
    }// end while (1)
}

jtaglink_handle_t* jtaglink_create(int block_size, void* user_tx, void* user_rx)
{
    memset(&app, 0, sizeof(jtaglink_handle_t));

    app.heartbeat_tmo = HEARTBEAT_TMO;
    app.alive_tmo     = ALIVE_TMO;
    app.ack_tmo       = ACK_TMO;
    app.block_size    = block_size;

    app.user_tx       = user_tx;
    app.user_rx       = user_rx;

    return &app;
}

int jtaglink_recv_data(jtaglink_handle_t* self)
{
    uint32_t nr_bytes;

    if (self->msg == NULL) {
        return 0;
    }

    if (self->msg->header.u.msgid != DATALINK_MSG_ID_FILE_DATA) {
        return 0;
    }

    const datalink_msg_file_data_t* data_msg;
    data_msg = (datalink_msg_file_data_t*)self->msg;
    nr_bytes = data_msg->header.u.dlen 
        - sizeof(uint32_t)
        - sizeof(uint32_t);

    jtagxfer_callback_set_file_data(
            self,
            self->user_rx,
            data_msg->fileid,
            data_msg->dataid,
            data_msg->data,
            nr_bytes);

    self->rx_pkg_id++;
    self->rx_offset += nr_bytes;
    self->winsize--;

    if (self->rx_pkg_id >= self->nr_rx_data_pkgs) {
        jtagxfer_callback_file_received(
                self,
                self->user_rx,
                self->rx_fileid);
    }
    return 1;
}

int jtaglink_recv_debug(jtaglink_handle_t* self)
{
    if (self->msg == NULL) {
        return 0;
    }

    if (self->msg->header.u.msgid != DATALINK_MSG_ID_DEBUG) {
        return 0;
    }

    const datalink_msg_debug_t* debug_msg;
    debug_msg = (datalink_msg_debug_t*)self->msg;

    jtagxfer_callback_debug_received(
            self,
            self->user_rx,
            debug_msg->raw,
            debug_msg->header.u.dlen);

    return 1;
}

int jtaglink_recv_spectrum_mask(jtaglink_handle_t* self)
{
    uint32_t nr_bytes;
    uint32_t count;
    float values[DATALINK_MAX_PAYLOAD_LEN/sizeof(float)];

    if (self->msg == NULL) {
        return 0;
    }

    if (self->msg->header.u.msgid != DATALINK_MSG_ID_SPECTRUM_MASK) {
        return 0;
    }

    const datalink_msg_spectrum_mask_t* mask_msg;
    mask_msg = (datalink_msg_spectrum_mask_t*)self->msg;
    nr_bytes = mask_msg->header.u.dlen;

    if (nr_bytes > DATALINK_MAX_PAYLOAD_LEN) {
        printf("Warning: device upload %d bytes > max len %d bytes\n",
                nr_bytes, DATALINK_MAX_PAYLOAD_LEN);
        return -1;
    }

    //
    // we copy data to avoid warning for gcc-9.x and newer compiler.
    //
    count = nr_bytes/sizeof(float);
    for (int i = 0;i < count;i++) {
        values[i] = mask_msg->mask[i];
    }
    jtagxfer_callback_spectrum_mask(
            self,
            self->user_rx,
            mask_msg->label,
            values,
            count);

    return 1;
}


int jtaglink_run(jtaglink_handle_t* self)
{
    char name[128];
    uint32_t nr_bytes;
    int nr_pkgs;
    datalink_msg_file_info_t* info_msg;
    datalink_msg_file_data_t* data_msg;

    printf("<RUN>\n");

    ////////////////////////////////////////////////////////////////////////////
    //
    //  low-level handshake
    //
    printf("Info: block_size %d bytes/frame (host)\n", self->block_size);
    if (jtaglink_wait_handshake(self) <= 0) {
        printf("Error: handshake fail\n");
        return -1;
    }
    printf("Info: block_size %d bytes/frame (negotiated)\n", self->block_size);

    JLINKARM_RV32_SkipEbreak(1);

    ////////////////////////////////////////////////////////////////////////////
    //
    //  high level handshake1
    //
    //  pc ---info---> dev
    //  pc <--ack----- dev
    //
    jtagxfer_callback_get_file_info(
            self,
            self->user_tx,
            self->tx_fileid,
            name,
            &self->tx_fileid,
            &self->tx_length);
    self->rx_fileid       = self->tx_fileid;
    nr_pkgs = (self->tx_length + self->block_size - 1)/self->block_size;
    self->nr_tx_data_pkgs = nr_pkgs;

    datalink_encode_file_info(
            &self->tx_msg,
            self->tx_seq,
            name,
            self->tx_fileid,
            self->tx_length);
    self->tx_seq++;
    if (jtaglink_send_msg(self, &self->tx_msg) <= 0) {
        printf("Error: send file INFO fail\n");
        return -1;
    }
    if (jtaglink_wait_msg(self, &self->rx_msg, self->ack_tmo) <= 0) {
        printf("Error: not response\n");
        return -1;
    }
    if (self->rx_msg.header.u.msgid != DATALINK_MSG_ID_FILE_ACK) {
        printf("Error: expect ACK, but got 0x%02x\n", self->rx_msg.header.u.msgid);
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  high level handshake2
    //
    //  pc <--info---- dev
    //  pc ---ack----> dev
    //
    if (jtaglink_wait_msg(self, &self->rx_msg, self->ack_tmo) <= 0) {
        printf("Error: not response\n");
        return -1;
    }
    if (self->rx_msg.header.u.msgid != DATALINK_MSG_ID_FILE_INFO) {
        printf("Error: expect INFO, but got 0x%02x\n", self->rx_msg.header.u.msgid);
        return -1;
    }

    info_msg = (datalink_msg_file_info_t*)&self->rx_msg;
    self->rx_fileid = info_msg->fileid;
    self->rx_length = info_msg->length;
    nr_pkgs = (self->rx_length + self->block_size - 1)/self->block_size;
    self->nr_rx_data_pkgs = nr_pkgs;
    jtagxfer_callback_set_file_info(
            self,
            self->user_rx,
            self->rx_fileid,
            self->rx_length);

    datalink_encode_file_ack(
            &self->tx_msg,
            self->tx_seq,
            self->tx_fileid,
            0);
    self->tx_seq++;
    if (jtaglink_send_msg(self, &self->tx_msg) <= 0) {
        printf("Error: send file ACK fail\n");
        return -1;
    }



    ////////////////////////////////////////////////////////////////////////////
    //
    //  data exchange
    //
    nr_bytes = SIZEOF_DATALINK_MESSAGE_HEADER 
        + sizeof(uint32_t)*2
        + self->block_size;
    self->max_winsize = self->tx_buff_size / nr_bytes;

    printf("Info: window size %d\n", self->max_winsize);

    printf("<BEGIN>\n");
    while (1) {
        if (user_kbhit()) {
            break;
        }

        printf("%6.2f%%\r", 100.0*self->rx_pkg_id/self->nr_rx_data_pkgs);

        ////////////////////////////////////////////////////////////////////////
        //
        //  sending
        //
        while (self->winsize < self->max_winsize) {
            if (self->tx_offset >= self->tx_length) {
                break;
            }

            data_msg = (datalink_msg_file_data_t*)&self->tx_msg;
            data_msg->header.u.msgid = DATALINK_MSG_ID_FILE_DATA;
            data_msg->fileid = self->tx_fileid;
            data_msg->dataid = self->tx_offset;

            jtagxfer_callback_get_file_data(
                    self,
                    self->user_tx,
                    data_msg->fileid,
                    data_msg->dataid,
                    self->block_size,
                    data_msg->data);

            data_msg->header.u.dlen = 
                + sizeof(uint32_t)
                + sizeof(uint32_t)
                + self->block_size;

            datalink_encode(&self->tx_msg, self->tx_seq);
            self->tx_seq++;
            if (jtaglink_send_msg(self, &self->tx_msg) <= 0) {
                printf("Error: send file DATA fail\n");
                break;
            }

            self->tx_pkg_id++;
            self->tx_offset += self->block_size;
            self->winsize++;

            if (self->tx_pkg_id >= self->nr_tx_data_pkgs) {
                jtagxfer_callback_file_sent(
                        self,
                        self->user_tx,
                        self->tx_fileid);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        //
        //  receiving
        //
        if (jtaglink_wait_msg(self, &self->rx_msg, self->ack_tmo) <= 0) {
            printf("Error: not response after sent file DATA\n");
            return -1;
        }
        self->msg = &self->rx_msg;
        jtaglink_recv_data(self);
        jtaglink_recv_debug(self);
        jtaglink_recv_spectrum_mask(self);
        self->msg = NULL;

        if (self->tx_pkg_id >= self->nr_tx_data_pkgs) {
            if (self->rx_pkg_id >= self->nr_rx_data_pkgs) {
                printf("Info: all done\n");
                break;
            }
        }
    }
    printf("%6.2f%%\n", 100.0);
    printf("<END>\n");

    ////////////////////////////////////////////////////////////////////////////
    //
    //  send EOF and wait EOF
    //  still process debug and spectrum_mask message.
    //
    datalink_encode_file_eof(
            &self->tx_msg,
            self->tx_seq,
            self->tx_fileid,
            0);
    self->tx_seq++;
    if (jtaglink_send_msg(self, &self->tx_msg) <= 0) {
        printf("Error: send file EOF fail\n");
        return -1;
    }

    while (1) {
        if (jtaglink_wait_msg(self, &self->rx_msg, self->alive_tmo) <= 0) {
            printf("Error: not response after sent file EOF to device\n");
            return -1;
        }
        self->msg = &self->rx_msg;
        jtaglink_recv_debug(self);
        jtaglink_recv_spectrum_mask(self);
        if (self->msg->header.u.msgid == DATALINK_MSG_ID_FILE_EOF) {
            self->msg = NULL;
            break;
        }
        self->msg = NULL;
    }

    user_sleep(100);
    return 0;
}

void jtaglink_close(jtaglink_handle_t* self)
{
    memset(self, 0, sizeof(jtaglink_handle_t));
}

