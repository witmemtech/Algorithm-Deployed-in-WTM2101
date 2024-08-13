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
#ifndef DATALINK_MSG_STATUS_H_DF13C4DA_3293_A6C9_379D_3FE15B173422_INCLUDED_
#define DATALINK_MSG_STATUS_H_DF13C4DA_3293_A6C9_379D_3FE15B173422_INCLUDED_

#define DATALINK_MSG_ID_STATUS      15

__PACKED_BEGIN
typedef struct __datalink_msg_status_t {
    datalink_message_header_t   header;
    // ------ payload ------
    uint32_t    errcode; // 0: no error, others: error
    uint8_t     data[DATALINK_MAX_PAYLOAD_LEN - sizeof(uint32_t)];
}__PACKED_END datalink_msg_status_t;


#endif

