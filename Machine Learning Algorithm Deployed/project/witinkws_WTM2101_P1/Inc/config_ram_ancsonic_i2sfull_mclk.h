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
#ifndef CONFIG_RAM_ANCSONIC_I2SFULL_MCLK_H_84090263_681D_0AB0_98C4_18391454A433_INCLUDED_
#define CONFIG_RAM_ANCSONIC_I2SFULL_MCLK_H_84090263_681D_0AB0_98C4_18391454A433_INCLUDED_

////////////////////////////////////////////////////////////
//
//  Configuration: RAM, AUDIO, I2S, HSI4.096M x12 (49MHz)
//
#ifdef CONFIG_RAM_ANCSONIC_I2SFULL_MCLK
 #define CONFIG_MODE            "RAM+I2Sfullduplex+ANCSONIC"

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

 #define USE_ANCSONIC_ALGO

 #define PCM_FRAME_SIZE         160
 #define I2S_AND_AUD_SAME_FREQ
 #define USE_I2S_SLAVE
 #define USE_I2S_OUT
 #define NOT_USE_I2S_IN
 #define USE_I2S_32BITS

 #define NOT_QSPI_BOOT

 #define USE_AMIC
 //#define USE_DMIC
 //#define AUDIO_CLK_PIN          GPIO_PIN_4
 //#define AUDIO_CLK_AF           GPIO_AF4_PDM0 
 //#define AUDIO_DATA_PIN         GPIO_PIN_5
 //#define AUDIO_DATA_AF          GPIO_AF5_PDM0

 #define UART_BAUDRATE          115200

 #define UART0_TX_PIN           GPIO_PIN_16
 #define UART0_TX_AF            GPIO_AF16_UART0 
 #define UART0_RX_PIN           GPIO_PIN_17
 #define UART0_RX_AF            GPIO_AF17_UART0
 #define USE_PRINTF             PRINTF_RETARGER_UART0


 // WARNING: by YuLinag & Yeyu
 // this is for ANCSONIC earphone
 // !!!do not change this!!!
 #define AUDIO_GAIN             4
 #define I2STX_32BITS_ASL       12

 // 0: reverbration off; 1: reverbration on
 #define REVERBRATION_FLAG      1


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

 //#define I2SRX_INSTANCE         I2S0
 //#define I2SRX_DMA_CHANNEL      DMA_CHANNEL2
 //#define I2SRX_SDI_PIN          GPIO_PIN_3
 //#define I2SRX_SDI_AF           GPIO_AF3_I2S0
 //#define I2SRX_CK_PIN           GPIO_PIN_2
 //#define I2SRX_CK_AF            GPIO_AF2_I2S0
 //#define I2SRX_WS_PIN           GPIO_PIN_1
 //#define I2SRX_WS_AF            GPIO_AF1_I2S0
#endif


#endif

