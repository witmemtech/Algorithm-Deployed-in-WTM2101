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
#ifndef DATALINK_MSG_HEARTBEAT_H_80416F4A_9299_CCC0_590E_DF34C01C109E_INCLUDED_
#define DATALINK_MSG_HEARTBEAT_H_80416F4A_9299_CCC0_590E_DF34C01C109E_INCLUDED_

#define DATALINK_MSG_ID_HEARTBEAT   0

enum __datalink_msg_heartbeat_version_t {
   FW_UNKNOWN           =     0,
   FW_DCCRN_v1_0_0      = 10000, // DCCRN + noLSTM 
   FW_DCCRN_v2_0_0      = 20000, // DCCRN + LSTM 
   FW_DCCRN_v2_1_0      = 20100, // DCCRN + LSTM
};

__PACKED_BEGIN
typedef struct __datalink_msg_heartbeat_t {
    datalink_message_header_t   header;
    // ------ payload ------
    uint32_t    version;
    uint32_t    date;
    uint32_t    time;
    uint32_t    timestamp;
}__PACKED_END datalink_msg_heartbeat_t;


#endif

