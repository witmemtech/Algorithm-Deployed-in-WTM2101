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
#ifndef DATALINK_MSG_FILE_DATA_H_F2D2E256_467B_A392_0323_D47F5FB2D6B8_INCLUDED_
#define DATALINK_MSG_FILE_DATA_H_F2D2E256_467B_A392_0323_D47F5FB2D6B8_INCLUDED_

#define DATALINK_MSG_ID_FILE_DATA   2

__PACKED_BEGIN
typedef struct __datalink_msg_file_data_t {
    datalink_message_header_t   header;
    // ------ payload ------
    uint32_t    fileid;
    uint32_t    dataid;
    uint8_t     data[DATALINK_MAX_PAYLOAD_LEN - 2*sizeof(uint32_t)];
}__PACKED_END datalink_msg_file_data_t;


#endif

