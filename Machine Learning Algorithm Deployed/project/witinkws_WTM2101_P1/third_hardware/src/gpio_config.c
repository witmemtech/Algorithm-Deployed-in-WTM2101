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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#include <basic_config.h>
#include <wtm2101_config.h>
#include <WTM2101.h>
#include <wtm2101_hal.h>

#include "gpio.h"
#include "pmu.h"
#include "rcc.h"

#include "main.h"

#include "gpio_config.h"

void gpio_init(void)
{
    if ((PMU->REVID & 0x3F) == 0x01) {//VerA
        return;
    } 

    if (((PMU->REVID & 0x3F) == 0x11) ||//VerB
        ((PMU->REVID & 0x3F) == 0x13)) {//VerC
        ////////////////////////////////////////////////////////////////////////
        //
        //  Init GPIO default pullup, pulldown and iodir
        //
        uint32_t pulldown = 0;
        uint32_t pullup   = 0;
        uint32_t gpiodir  = 0; // 0: input, 1: output

        pullup   = 0xFFFFFFFF;
        pulldown = 0;

        //  GPIO6:  TCK (pulldown)
        //  GPIO7:  TMS (pullup)
        //  GPIO8:  TDI (pulldown)
        //  GPIO9:  TDO (pulldown)
        
        // TMS is pullup
        pullup  |= (1 << 7);
        pulldown&= ~(1 << 7);
        
        // TCK, TDI, TDO is pulldown
        pullup  &= ~((1 << 9) | (1 << 8) | (1 << 6));
        pulldown|= (1 << 9) | (1 << 8) | (1 << 6);

        // TDO is output
        gpiodir |= (1 << 9);

        #if defined(UART0_TX_PIN) || defined(UART0_RX_PIN)
        pullup   |= UART0_RX_PIN;
        pulldown &= ~UART0_TX_PIN;
        pulldown &= ~UART0_RX_PIN;
        #endif

        #if defined(UART1_TX_PIN) || defined(UART1_RX_PIN)
        pullup   |= UART1_RX_PIN;
        pulldown &= ~UART1_TX_PIN;
        pulldown &= ~UART1_RX_PIN;
        #endif

        #if defined(AUDIO_CLK_PIN) && defined(AUDIO_DATA_PIN)
        pullup   &= ~AUDIO_CLK_PIN;
        pullup   &= ~AUDIO_DATA_PIN;
        pulldown &= ~AUDIO_CLK_PIN;
        pulldown &= ~AUDIO_DATA_PIN;
        #endif

        #if defined(I2STX_INSTANCE)
        pullup   &= ~I2STX_SDO_PIN;
        pullup   &= ~I2STX_CK_PIN;
        pullup   &= ~I2STX_WS_PIN;
        pulldown &= ~I2STX_SDO_PIN;
        pulldown &= ~I2STX_CK_PIN;
        pulldown &= ~I2STX_WS_PIN;
        #endif

        #if defined(I2SRX_INSTANCE)
        pullup   &= ~I2SRX_SDI_PIN;
        pullup   &= ~I2SRX_CK_PIN;
        pullup   &= ~I2SRX_WS_PIN;
        pulldown |= I2SRX_SDI_PIN;
        pulldown &= ~I2SRX_CK_PIN;
        pulldown &= ~I2SRX_WS_PIN;
        #endif

        ////////////////////////////////////////////////////////////////////////
        //
        //  update GPIO config
        //
        GPIOA->DDR = gpiodir;

        // >> SMT function always enabled, SMT register reuse as pullup
        // PMU::GPIO_SMT0[6:0] => GPIO[6:0],    1'b1=pulldown, 1'b0=not-pulldown
        // PMU::GPIO_SMT1[7:0] => GPIO[15:8],   1'b1=pulldown, 1'b0=not-pulldown
        // PMU::GPIO_SMT2[3:0] => GPIO[19:16],  1'b1=pulldown, 1'b0=not-pulldown
        PMU->GPIO_SMT0 = pulldown & 0x7Fu;
        PMU->GPIO_SMT1 = (pulldown >> 8) & 0xFFu;
        PMU->GPIO_SMT2 = (pulldown >> 16) & 0x0Fu;
        
        // >> retention register reuse as pullup
        // PMU::RTN_0[7:0] <=> GPIO[7:0],       1'b1=pullup, 1'b0=not-pullup
        // PMU::RTN_1[7:0] <=> GPIO[15:8],      1'b1=pullup, 1'b0=not-pullup
        // PMU::RTN_2[3:0] <=> GPIO[19:16],     1'b1=pullup, 1'b0=not-pullup
        PMU->RTN_0 = pullup & 0xFFu;
        PMU->RTN_1 = (pullup >> 8) & 0xFFu;
        PMU->RTN_2 = (pullup >> 16) & 0x0Fu;
    }
}


