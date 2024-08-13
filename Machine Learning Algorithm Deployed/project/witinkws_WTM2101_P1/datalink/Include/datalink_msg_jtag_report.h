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
#ifndef DATALINK_MSG_JTAG_REPORT_H_99E9D16F_4526_7F9B_8206_E05082B5CC15_INCLUDED_
#define DATALINK_MSG_JTAG_REPORT_H_99E9D16F_4526_7F9B_8206_E05082B5CC15_INCLUDED_

#define DATALINK_MSG_ID_JTAG_REPORT 10

typedef struct __datalink_msg_jtag_report_buf_t {
    uint32_t                    size;
    void*                       buff;
    uint32_t                    head;
    uint32_t                    tail;
}datalink_jtag_buf_t;


__PACKED_BEGIN
typedef struct __datalink_msg_jtag_report_t {
    datalink_message_header_t   header;

    uint32_t                    version;
    uint32_t                    format;

    uint32_t                    tx_buff_size;
    uint32_t                    tx_buff_addr;
    uint32_t                    tx_head_addr;
    uint32_t                    tx_tail_addr;

    uint32_t                    rx_buff_size;
    uint32_t                    rx_buff_addr;
    uint32_t                    rx_head_addr;
    uint32_t                    rx_tail_addr;

    uint32_t                    block_size;

}__PACKED_END datalink_msg_jtag_report_t;


#endif

