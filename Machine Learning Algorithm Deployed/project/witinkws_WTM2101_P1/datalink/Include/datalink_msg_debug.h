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
#ifndef DATALINK_MSG_DEBUG_H_39B1CD7D_E5CA_2674_F5D1_A0DE0D244D98_INCLUDED_
#define DATALINK_MSG_DEBUG_H_39B1CD7D_E5CA_2674_F5D1_A0DE0D244D98_INCLUDED_

#define DATALINK_MSG_ID_DEBUG   8

__PACKED_BEGIN
typedef struct __datalink_msg_debug_t {
    datalink_message_header_t   header;
    // ------ payload ------
    char                        raw[1];
}__PACKED_END datalink_msg_debug_t;


#endif

