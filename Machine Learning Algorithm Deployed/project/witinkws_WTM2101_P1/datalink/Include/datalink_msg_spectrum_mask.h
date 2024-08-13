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
#ifndef DATALINK_MSG_SPECTRUM_MASK_H_DACA314C_C608_B7E3_CE17_99F26ADC1429_INCLUDED_
#define DATALINK_MSG_SPECTRUM_MASK_H_DACA314C_C608_B7E3_CE17_99F26ADC1429_INCLUDED_

#define DATALINK_MSG_ID_SPECTRUM_MASK   13

#define DATALINK_MSG_SPECTRUM_MASK_MAX_ITEM_COUNT    \
    ((DATALINK_MAX_PAYLOAD_LEN - 8*sizeof(char))/sizeof(float))

__PACKED_BEGIN
typedef struct __datalink_msg_spectrum_mask_t {
    datalink_message_header_t   header;
    // ------ payload ------
    char        label[8];
    float       mask[DATALINK_MSG_SPECTRUM_MASK_MAX_ITEM_COUNT];
}__PACKED_END datalink_msg_spectrum_mask_t;


#endif

