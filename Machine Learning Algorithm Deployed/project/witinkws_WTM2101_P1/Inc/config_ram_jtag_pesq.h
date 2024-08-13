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
#ifndef CONFIG_RAM_JTAG_PESQ_H_BFCA6621_2917_F7DE_D237_27EA8EC6F843_INCLUDED_
#define CONFIG_RAM_JTAG_PESQ_H_BFCA6621_2917_F7DE_D237_27EA8EC6F843_INCLUDED_

#if defined(CONFIG_RAM_JTAG_PESQ) || defined(CONFIG_QFLASH_JTAG_PESQ)

 #define CONFIG_MODE            "RAM+JTAG+VERIFY"
 #define USE_HSI
 #define NOT_USE_OSC_CALIBRATE
 #define USE_PLL_CLOCK          // 147.456MHz
 #define PLL_N                  6
 #define USE_NPU_24M
 #define USE_NPU_DIFF
 #define USE_DCCRN
 #define AUDIO_FRAME_SIZE       160
 #define NOT_USE_EXTRA_MASK
 #define NOT_USE_IN_MASK_SMOOTH
 #define NOT_USE_I2S_OUT
 #define NOT_USE_I2S_IN
 #define NOT_USE_I2S_32BITS
 #define NOT_USE_AMIC
 #define NOT_USE_DMIC
 #define NOT_QSPI_BOOT
 #define USE_PRINTF             PRINTF_RETARGER_NONE

#endif


#endif

