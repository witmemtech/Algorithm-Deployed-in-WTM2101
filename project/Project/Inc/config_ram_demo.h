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
#ifndef CONFIG_RAM_DEMO_B5A661_INCLUDED_
#define CONFIG_RAM_DEMO_B5A661_INCLUDED_

#ifdef CONFIG_RAM_DEMO

 #define PLL_N                   1
 #define USE_32BIT_I2S          (0)

 #define UART_ENABLE            (1)
          
 #if UART_ENABLE
     #define UART_BAUDRATE          115200
     #define USE_UART_PROTOCOL      (0)   
     #if 1
         #define UART0_TX_PIN           GPIO_PIN_16
         #define UART0_TX_AF            GPIO_AF16_UART0 
         #define UART0_RX_PIN           GPIO_PIN_17
         #define UART0_RX_AF            GPIO_AF17_UART0
     #else
         #define UART1_TX_PIN           GPIO_PIN_6
         #define UART1_TX_AF            GPIO_AF6_UART1
         #define UART1_RX_PIN           GPIO_PIN_7
         #define UART1_RX_AF            GPIO_AF7_UART1
         #define USE_PRINTF             PRINTF_RETARGER_UART1
     #endif
 #endif

 //#define AUDIO_FRAME_SIZE          (160)

#endif

#endif

