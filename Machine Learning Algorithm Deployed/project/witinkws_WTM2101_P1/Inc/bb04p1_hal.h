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
#ifndef BB04P_HAL_H_2720E909_6D5B_3F1B_7545_2F0CCE1EAF12_INCLUDED_
#define BB04P_HAL_H_2720E909_6D5B_3F1B_7545_2F0CCE1EAF12_INCLUDED_

typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;

void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);

void HAL_Peripherals_Reset(void);
void HAL_Reset_PLL(void);

typedef enum {
    DVDDC_0V9       = 0x00,
    DVDDC_1V06      = 0x11,
    DVDDC_1V08      = 0x12,
    DVDDC_1V09      = 0x13,
    DVDDC_1V10      = 0x10,
    DVDDC_1V13      = 0x14,
    DVDDC_1V15      = 0x15,
    DVDDC_1V17      = 0x16,
    DVDDC_1V18      = 0x17,

    DVDDC_LOW_POWER = 0x00, // 0.90V
    DVDDC_HI_PERF   = 0x10, // 1.10V
} dvddc_voltage_t;
void HAL_Change_DVDDC(dvddc_voltage_t vol);


typedef union {
    struct {
        uint32_t hsi_coarse :4;
        uint32_t hsi_fine   :5;
        uint32_t reserved0  :7;
        uint32_t lsi_coarse :3;
        uint32_t lsi_fine   :4;
        uint32_t reserved1  :9;
    }u;
    uint32_t u32;
}osc_calibrate_config_t;

void HAL_Config_Internal10K(void);
void HAL_Config_Internal160K(void);
void HAL_Config_External32K(void);
void HAL_Config_ExternalOSC(int plldiv);

// when cfg == NULL, auto call HAL_Calibrate_InternalOSC
// else using cfg to config OSC.
void HAL_Config_InternalOSC(int plldiv, osc_calibrate_config_t* cfg);


typedef struct {
    uint16_t osc_24m_coarse;
    uint16_t osc_24m_fine;
    uint32_t osc_24m_freq;
    uint16_t osc_320k_coarse;
    uint16_t osc_320k_fine;
    uint32_t osc_320k_freq;
}osc_trim_t;


uint32_t HAL_Get_HSI_Freq(void);
uint32_t HAL_Get_LSI_Freq(void);
void HAL_Get_OSC_Trim(osc_trim_t* cfg);



////////////////////////////////////////////////////////////////////////////////
void memdbg(const void* buf, int nr_bytes);
void memdbg16(const void* buf, int nr_bytes);



void system_cycle_reset();

void led_init(void);
void led_lo(void);
void led_hi(void);


#endif

