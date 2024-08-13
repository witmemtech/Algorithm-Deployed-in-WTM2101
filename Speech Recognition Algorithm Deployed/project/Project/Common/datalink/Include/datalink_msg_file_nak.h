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
#ifndef DATALINK_MSG_FILE_NACK_H_ED103D29_6011_1EBD_38C7_8EFD8087E92B_INCLUDED_
#define DATALINK_MSG_FILE_NACK_H_ED103D29_6011_1EBD_38C7_8EFD8087E92B_INCLUDED_

#define DATALINK_MSG_ID_FILE_NAK    4

__PACKED_BEGIN
typedef struct __datalink_msg_file_nak_t {
    datalink_message_header_t   header;
    // ------ payload ------
    uint32_t    fileid;
    uint32_t    dataid;
}__PACKED_END datalink_msg_file_nak_t;


#endif

