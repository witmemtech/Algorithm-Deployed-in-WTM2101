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
#ifndef CONFIG_RAM_UART_VERIFY_NPUTRIM_H_707F8387_0135_251F_A3B0_6C83AA858EEA_INCLUDED_
#define CONFIG_RAM_UART_VERIFY_NPUTRIM_H_707F8387_0135_251F_A3B0_6C83AA858EEA_INCLUDED_

////////////////////////////////////////////////////////////
//
//  Configuration: RAM, UART, HSI24.576M with PLL without LSE 32.768K
//
#ifdef CONFIG_RAM_UART_VERIFY_NPUTRIM
 #define CONFIG_MODE            "RAM+UART+VERIFY"

 #define DATA_FROM_UART
 #define UART_SEND_STEP         6
 #define UART_RECEIVE_STEP      1

 #define USE_HSI                //  24.576MHz
 #define NOT_USE_OSC_CALIBRATE
 #define USE_PLL_CLOCK          // 147.456MHz
 #define PLL_N                  6

 #define USE_NPU_24M
 #define USE_NPU_DIFF
 #define USE_DCCRN

 #define NOT_USE_EXTRA_MASK
// #define MASKTYPE   MASKTYPE_SQRT
// #define MASKTYPE   MASKTYPE_POWER1P5
// #define MASKTYPE   MASKTYPE_POWER2
// #define MASKTYPE   MASKTYPE_POWER3
// #define MASKTYPE   MASKTYPE_EXTRA

 #define NOT_USE_IN_MASK_SMOOTH
// #define MASKSMOOTH MASKSMOOTH_SLIDERWIN
// #define MASKSMOOTH MASKSMOOTH_GAUSS

 #define NOT_USE_I2S_OUT
 #define NOT_USE_I2S_IN
 #define NOT_USE_I2S_32BITS

 #define NOT_QSPI_BOOT

 #define NOT_USE_AMIC
 #define NOT_USE_DMIC

 #define UART_BAUDRATE          921600 // 24.576M*6/16/921600 = 80 (bauderr = 0%)
 #define UART0TX_DMA_CHANNEL    DMA_CHANNEL1
 #define UART0RX_DMA_CHANNEL    DMA_CHANNEL2
 #define UART0_TX_PIN           GPIO_PIN_16
 #define UART0_TX_AF            GPIO_AF17_UART0 
 #define UART0_RX_PIN           GPIO_PIN_17
 #define UART0_RX_AF            GPIO_AF17_UART0
 #define UART1_TX_PIN           GPIO_PIN_14
 #define UART1_TX_AF            GPIO_AF14_UART1
 #define UART1_RX_PIN           GPIO_PIN_15
 #define UART1_RX_AF            GPIO_AF15_UART1
 #define USE_PRINTF             PRINTF_RETARGER_UART1
#endif


#endif

