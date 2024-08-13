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
#ifndef UART_RX_DMA_H_3383DDEC_30B4_F318_FAA0_930754191F7D_INCLUDED_
#define UART_RX_DMA_H_3383DDEC_30B4_F318_FAA0_930754191F7D_INCLUDED_

// DMA chain-mode based fifo
void UART_RecvFIFO_Start(UART_TypeDef* UARTx);
void UART_RecvFIFO_Stop(UART_TypeDef* UARTx);
int  UART_RecvFIFO_Read(UART_TypeDef* UARTx, uint8_t* pData, int Size);
void UART_RecvFIFO_Pruge(UART_TypeDef* UARTx);

#endif

