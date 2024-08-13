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
#ifndef CONFIG_RAM_UART_VERIFY_HSI24MX6_H_FC9EECDC_637C_772F_C942_79BC46E0A8F1_INCLUDED_
#define CONFIG_RAM_UART_VERIFY_HSI24MX6_H_FC9EECDC_637C_772F_C942_79BC46E0A8F1_INCLUDED_

////////////////////////////////////////////////////////////
//
//  Configuration: RAM, UART, HSI24.576M with PLL
//
#ifdef CONFIG_RAM_UART_VERIFY_HSI24Mx6
 #define CONFIG_MODE            "RAM+UART+VERIFY"

 #define USE_HSI                //  24.576MHz
 //#define USE_OSC_CALIBRATE
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
 #define AUDIO_FRAME_SIZE         160
 #define PCM_FRAME_SIZE           160

 #define NOT_USE_AMIC
 #define NOT_USE_DMIC

 #define NOT_USE_ANCSONIC
 #define UART_ENABLE            1

 #define UART_BAUDRATE          921600 // 24.576M*6/16/921600 = 80 (bauderr = 0%)
 #define UART0TX_DMA_CHANNEL    DMA_CHANNEL1
 #define UART0RX_DMA_CHANNEL    DMA_CHANNEL2
 //#define UART0_TX_PIN           GPIO_PIN_4
 //#define UART0_TX_AF            GPIO_AF4_UART0 
 //#define UART0_RX_PIN           GPIO_PIN_5
 //#define UART0_RX_AF            GPIO_AF5_UART0
 #define UART0_TX_PIN           GPIO_PIN_16
 #define UART0_TX_AF            GPIO_AF16_UART0 
 #define UART0_RX_PIN           GPIO_PIN_17
 #define UART0_RX_AF            GPIO_AF17_UART0
 #define USE_PRINTF             PRINTF_RETARGER_NONE
 //#define USE_PRINTF             PRINTF_RETARGER_UART0

#endif

#endif

