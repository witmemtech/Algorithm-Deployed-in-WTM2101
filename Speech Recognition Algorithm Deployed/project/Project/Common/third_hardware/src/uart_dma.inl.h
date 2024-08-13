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
#ifndef UART_DMA_INL_H_FCC42CFC_24BB_BA0D_1B0E_C0A86F6F1348_INCLUDED_
#define UART_DMA_INL_H_FCC42CFC_24BB_BA0D_1B0E_C0A86F6F1348_INCLUDED_

#define RXFIFO_DEPTH            2048 // !!! must be pow(2, n) !!!


#define LE2BE_32(v) (\
    (((v) >> 24) & 0x000000FF) | \
    (((v) >>  8) & 0x0000FF00) | \
    (((v) <<  8) & 0x00FF0000) | \
    (((v) << 24) & 0xFF000000) \
)

#define BE2LE_32(v) LE2BE_32(v)


#define LE2BE_16(v) (\
    (((v) >>  8) & 0x00FF) | \
    (((v) <<  8) & 0xFF00) \
)

#define BE2LE_16(v) LE2BE_16(v)



#endif

