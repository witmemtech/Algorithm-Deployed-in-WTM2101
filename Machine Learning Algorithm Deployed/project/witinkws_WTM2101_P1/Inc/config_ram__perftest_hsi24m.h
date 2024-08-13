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
#ifndef CONFIG_RAM__PERFTEST_HSI24M_H_A39791CF_68B6_D664_5E0E_3F293F10FE96_INCLUDED_
#define CONFIG_RAM__PERFTEST_HSI24M_H_A39791CF_68B6_D664_5E0E_3F293F10FE96_INCLUDED_

////////////////////////////////////////////////////////////
//
//  Configuration: RAM, I2S, HSI24.576M
//
#ifdef CONFIG_RAM__PERFTEST_HSI24M
 #define CONFIG_MODE            "RAM+perftest"

 #define USE_HSI                //  24.576MHz
 #define USE_OSC_CALIBRATE

 //-----------------------------------------------
 // 24 is actual 24.576M, 48 is 49.152M,
 // 

 //// sys16, npu16
 //#define USE_PLL_CLOCK
 //#define PLL_N                  2
 //#define NPU_CLKDIV             3
 //#define SYS_CLKDIV             3
 //#define USE_NPU_16M



 //// sys12, npu12
 //#define NOT_USE_PLL_CLOCK
 //#define PLL_N                  1
 //#define NOT_NPU_CLKDIV
 //#define SYS_CLKDIV             2
 //#define USE_NPU_12M

 // sys24, npu24
 #define NOT_USE_PLL_CLOCK
 #define PLL_N                  1
 #define NOT_NPU_CLKDIV
 #define USE_NPU_24M

 //// sys48, npu24
 //#define USE_PLL_CLOCK
 //#define PLL_N                  2
 //#define NPU_CLKDIV             2
 //#define USE_NPU_24M

 //// sys48m, npu48m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  2
 //#define NOT_NPU_CLKDIV
 //#define USE_NPU_48M

 //// sys72m, npu24m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  3
 //#define NPU_CLKDIV             3
 //#define USE_NPU_24M

 //// sys72m, npu72m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  3
 //#define NOT_NPU_CLKDIV
 //#define USE_NPU_72M

 //// sys96m, npu24m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  4
 //#define NPU_CLKDIV             4
 //#define USE_NPU_24M

 //// sys96m, npu48m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  4
 //#define NPU_CLKDIV             2
 //#define USE_NPU_48M

 //// sys120m, npu24m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  5
 //#define NPU_CLKDIV             5
 //#define USE_NPU_24M

 //// sys144m, npu24m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  6
 //#define NPU_CLKDIV             6
 //#define USE_NPU_24M

 //// sys144m, npu48m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  6
 //#define NPU_CLKDIV             3
 //#define USE_NPU_48M

 //// sys144m, npu72m
 //#define USE_PLL_CLOCK
 //#define PLL_N                  6
 //#define NPU_CLKDIV             2
 //#define USE_NPU_72M


 //-----------------------------------------------
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

 #define NOT_USE_SWITCH
 #define NOT_USE_I2S_MASTER
 #define NOT_USE_I2S_OUT
 #define NOT_USE_I2S_IN
 #define NOT_QSPI_BOOT
 #define NOT_USE_AMIC
 #define NOT_USE_DMIC

 //#define UART_BAUDRATE          115200
 //#define UART0_TX_PIN           GPIO_PIN_16
 //#define UART0_TX_AF            GPIO_AF17_UART0 
 //#define UART0_RX_PIN           GPIO_PIN_17
 //#define UART0_RX_AF            GPIO_AF17_UART0
 //#define USE_PRINTF             PRINTF_RETARGER_UART0

 #define UART_BAUDRATE          9600
 //#define UART_BAUDRATE          115200
 #define UART1_TX_PIN           GPIO_PIN_14
 #define UART1_TX_AF            GPIO_AF14_UART1
 #define UART1_RX_PIN           GPIO_PIN_15
 #define UART1_RX_AF            GPIO_AF15_UART1
 #define USE_PRINTF             PRINTF_RETARGER_UART1
#endif


#endif

