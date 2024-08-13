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
#ifndef CRC_H_455ECB53_A607_E0FF_F6CA_57BF40E8741B_INCLUDED_
#define CRC_H_455ECB53_A607_E0FF_F6CA_57BF40E8741B_INCLUDED_

uint8_t chksum8(uint8_t* buf, int nr_bytes);
uint16_t crc16(const void* buf, int len);

uint16_t crc16_init(void);
uint16_t crc16_update(uint16_t crcvalue, const void* buf, int len);

#endif

