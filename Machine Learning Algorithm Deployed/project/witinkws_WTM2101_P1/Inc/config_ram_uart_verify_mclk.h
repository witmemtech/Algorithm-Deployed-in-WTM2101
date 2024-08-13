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
#ifndef CONFIG_RAM_UART_VERIFY_MCLK_H_6C860F9F_EAAD_E7E3_E667_1FC55BA02FEF_INCLUDED_
#define CONFIG_RAM_UART_VERIFY_MCLK_H_6C860F9F_EAAD_E7E3_E667_1FC55BA02FEF_INCLUDED_

////////////////////////////////////////////////////////////
//
//  Configuration: RAM, UART, MCLK 4.096MHz
//
#ifdef CONFIG_RAM_UART_VERIFY_MCLK
 #define CONFIG_MODE            "RAM+UART+VERIFY"

 #define USE_HSE                //  4.096MHz
 #define NOT_USE_OSC_CALIBRATE
 #define USE_PLL_CLOCK          // HSE x PLL_N

 //#define PLL_N                  8   // 32.0MHz for CPU
 //#define USE_NPU_32M                // 32.0MHz for NPU
 //#define PLL_N                  9   // 36.0MHz for CPU
 //#define USE_NPU_36M                // 36.0MHz for NPU
 #define PLL_N                  12   // 49.152MHz for CPU
 #define USE_NPU_48M                 // 49.152MHz for NPU

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

 #define UART_BAUDRATE          115200
 #define UART0TX_DMA_CHANNEL    DMA_CHANNEL1
 #define UART0RX_DMA_CHANNEL    DMA_CHANNEL2
 #define UART0_TX_PIN           GPIO_PIN_16
 #define UART0_TX_AF            GPIO_AF17_UART0 
 #define UART0_RX_PIN           GPIO_PIN_17
 #define UART0_RX_AF            GPIO_AF17_UART0
 #define USE_PRINTF             PRINTF_RETARGER_NONE
#endif

#endif

