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
#ifndef DATALINK_H_9B4818EA_4805_427F_6BFF_57DA2E96AE1C_INCLUDED_
#define DATALINK_H_9B4818EA_4805_427F_6BFF_57DA2E96AE1C_INCLUDED_

#define DATALINK_STX                254
#define DATALINK_MAX_PAYLOAD_LEN    1024   // 1K


//
// example:
//
//  __PACKED_BEGIN
//  struct struct_name {
//      <<<members>>>
//  }__PACKED_END;
//
//  __PACKED_BEGIN
//  typedef struct struct_name {
//      <<<members>>>
//  }__PACKED_END new_struct_name;
//
#if !defined(__PACKED_BEGIN) && !defined(__PACKED_END)
 #ifdef _MSC_VER
  #define __PACKED_BEGIN    __pragma(pack(push, 1))
  #define __PACKED_END      __pragma(pack(pop))
 #else
  #define __PACKED_BEGIN    /*nothing*/
  #define __PACKED_END      __attribute__((packed, aligned(1)))
 #endif
#endif

typedef enum {
    DATALINK_PARSE_STATE_ERROR      = -1,
    DATALINK_PARSE_STATE_IDLE       = 0,
    DATALINK_PARSE_STATE_RECV_HDR,
    DATALINK_PARSE_STATE_RECV_PAYLOAD,
} datalink_parse_state_t;


typedef struct __datalink_status {
    datalink_parse_state_t  parse_state;
    uint32_t                bytes_received;
    uint32_t                bytes_expect;
} datalink_status_t;


#define SIZEOF_DATALINK_MESSAGE_HEADER  8
typedef union __datalink_message_header_t {
    struct {
        uint32_t magic  :8;     // uint8_t
        uint32_t seq    :8;     // uint8_t
        uint32_t dlen   :16;    // uint16_t
        uint32_t dcrc   :16;    // uint16_t
        uint32_t msgid  :8;     // uint8_t
        uint32_t hchksum:8;     // uint8_t
    }u;
    uint8_t bytes[8];
}datalink_message_header_t;

typedef uint8_t datalink_message_payload_t[DATALINK_MAX_PAYLOAD_LEN];


__PACKED_BEGIN
typedef struct __datalink_message {
    datalink_message_header_t   header;
    datalink_message_payload_t  payload;
}__PACKED_END datalink_message_t;

#include "datalink_msg_heartbeat.h" // msgid=0
#include "datalink_msg_file_info.h" // msgid=1
#include "datalink_msg_file_data.h" // msgid=2
#include "datalink_msg_file_ack.h"  // msgid=3
#include "datalink_msg_file_nak.h"  // msgid=4
#include "datalink_msg_file_crc.h"  // msgid=5
#include "datalink_msg_busy.h"      // msgid=6
#include "datalink_msg_continue.h"  // msgid=7


int datalink_encode(
        datalink_message_t* msg,
        uint8_t             seq
);

int datalink_encode_heartbeat(
        datalink_message_t* msg,
        uint8_t             seq,
        uint32_t            version,
        uint32_t            date,
        uint32_t            time,
        uint32_t            timestamp
);

int datalink_encode_file_info(
        datalink_message_t* msg,
        uint8_t             seq,
        const char*         name,
        uint32_t            fileid,
        uint32_t            length
);

int datalink_encode_file_data(
        datalink_message_t* msg,
        uint8_t             seq,
        uint32_t            fileid,
        uint32_t            dataid,
        const void*         data_buffer,
        uint32_t            data_length
);

int datalink_encode_file_ack(
        datalink_message_t* msg,
        uint8_t             seq,
        uint32_t            fileid,
        uint32_t            dataid
);

int datalink_encode_file_nak(
        datalink_message_t* msg,
        uint8_t             seq,
        uint32_t            fileid,
        uint32_t            dataid
);

int datalink_encode_file_crc(
        datalink_message_t* msg,
        uint8_t             seq,
        uint32_t            fileid,
        uint32_t            dataid,
        uint32_t            crcvalue
);

int datalink_encode_busy(
        datalink_message_t* msg,
        uint8_t             seq
);

int datalink_encode_continue(
        datalink_message_t* msg,
        uint8_t             seq
);

int datalink_parse_char(
        uint8_t             ch,
        datalink_message_t* msg,
        datalink_status_t*  status
);

#endif

