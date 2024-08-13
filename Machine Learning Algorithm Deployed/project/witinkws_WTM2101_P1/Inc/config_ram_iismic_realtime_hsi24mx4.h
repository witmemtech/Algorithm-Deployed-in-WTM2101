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
#ifndef CONFIG_RAM_IISMIC_REALTIME_HSI24MX4_H_B5A2EC13_1118_019F_2861_3F26AB882661_INCLUDED_
#define CONFIG_RAM_IISMIC_REALTIME_HSI24MX4_H_B5A2EC13_1118_019F_2861_3F26AB882661_INCLUDED_

#ifdef CONFIG_RAM_DEMO
 #define CONFIG_MODE            "RAM+IISMIC+I2S"

 #define USE_HSI                //  4.096MHz
 #define USE_PLL_CLOCK          // HSE x PLL_N
 #define PLL_N                  6   // only for poweron

 #define USE_NPU_DIFF
 #define USE_DCCRN

 #define NOT_USE_EXTRA_MASK
 #define NOT_USE_IN_MASK_SMOOTH

 #define PCM_FRAME_SIZE         160
 #define NOT_I2S_AND_AUD_SAME_FREQ
 #define USE_I2S_MASTER
 #define USE_I2S_OUT
 #define USE_I2S_IN
 #define USE_I2S_32BITS

 #define NOT_QSPI_BOOT

 #define AUDIO_FRAME_SIZE         160
 #define NOT_USE_AMIC
 #define NOT_USE_DMIC
 #define USE_IISMIC

 #define UART_ENABLE            1
 #define UART_BAUDRATE          115200

 #if 1
     #define UART0_TX_PIN           GPIO_PIN_16
     #define UART0_TX_AF            GPIO_AF16_UART0 
     #define UART0_RX_PIN           GPIO_PIN_17
     #define UART0_RX_AF            GPIO_AF17_UART0
     #define USE_PRINTF             PRINTF_RETARGER_UART0
 #else
     #define UART1_TX_PIN           GPIO_PIN_6
     #define UART1_TX_AF            GPIO_AF6_UART1
     #define UART1_RX_PIN           GPIO_PIN_7
     #define UART1_RX_AF            GPIO_AF7_UART1
     #define USE_PRINTF             PRINTF_RETARGER_UART1
 #endif
 #define USE_UART_IRQ


 // shift 1 bits <=> 6dB
 //#define I2SRX_32BITS_ASR       0 // avoid ifft overflow
 //#define I2STX_32BITS_ASR       3 // avoid max98357 (+6dB) overflow

 // --------- ----
 // function  GPIO
 // --------- ----
 // I2S0.CK   2
 // I2S0.WS   1
 // I2S0.SDI  3
 // --------- ----
 // I2S1.CK   12
 // I2S1.SDO  10
 // I2S1.WS   13
 // --------- ----
 #define I2STX_INSTANCE         I2S1
 #define I2STX_DMA_CHANNEL      DMA_CHANNEL1
 #define I2STX_SDO_PIN          GPIO_PIN_10
 #define I2STX_SDO_AF           GPIO_AF10_I2S1
 #define I2STX_CK_PIN           GPIO_PIN_12
 #define I2STX_CK_AF            GPIO_AF12_I2S1
 #define I2STX_WS_PIN           GPIO_PIN_13
 #define I2STX_WS_AF            GPIO_AF13_I2S1

 #define I2SRX_INSTANCE         I2S0
 #define I2SRX_DMA_CHANNEL      DMA_CHANNEL2
 #define I2SRX_SDI_PIN          GPIO_PIN_3
 #define I2SRX_SDI_AF           GPIO_AF3_I2S0
 #define I2SRX_CK_PIN           GPIO_PIN_2
 #define I2SRX_CK_AF            GPIO_AF2_I2S0
 #define I2SRX_WS_PIN           GPIO_PIN_1
 #define I2SRX_WS_AF            GPIO_AF1_I2S0


#endif

#endif

