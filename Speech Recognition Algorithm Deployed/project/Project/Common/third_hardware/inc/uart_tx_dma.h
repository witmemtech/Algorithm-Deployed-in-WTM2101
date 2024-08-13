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
#ifndef UART_TX_DMA_H_C799707F_3FE1_7AE1_AF2D_562CFFB78AB2_INCLUDED_
#define UART_TX_DMA_H_C799707F_3FE1_7AE1_AF2D_562CFFB78AB2_INCLUDED_

// Sending dynamic data, format:
//      buffer0, nr_bytes0, buffer1, nr_bytes1, NULL
//
// must endswith `NULL`
//
void UART_SendBlock_Async(UART_TypeDef* UARTx, ...);

#endif

