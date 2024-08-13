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
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "basic_config.h"
#include <WTM2101.h>
#include <bb04p1_hal.h>

#include "gpio.h"
#include "spi.h"
#include "dma.h"
#include "pmu.h"
#include "rcc.h"
#include "main.h"

#include "spi_config.h"

#ifdef SPI_ENABLE

static void _gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_CLK_EN_Ctl(RCC_CLK_EN_GPIO_HCLKEN_Msk, ENABLE);

    GPIO_InitStructure.Pin       = SPI0_MISO_PIN;
    GPIO_InitStructure.Alternate = SPI0_MISO_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = SPI0_MOSI_PIN;
    GPIO_InitStructure.Alternate = SPI0_MOSI_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = SPI0_SCLK_PIN;
    GPIO_InitStructure.Alternate = SPI0_SCLK_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_OutputLo(GPIOA, SPI0_NSS_PIN);
    GPIO_InitStructure.Mode      = GPIO_MODE_OUT;
    GPIO_InitStructure.Pin       = SPI0_NSS_PIN;
    GPIO_InitStructure.Alternate = SPI0_NSS_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void _spi0_config(void)
{
    SPI_InitTypeDef SPI_InitStructure;

    RCC_CLK_EN_Ctl(RCC_CLK_EN_SPIM_CLKEN_Msk, ENABLE);

    SPI_InitStructure.cpol      = SPI_CPOL_0;
    SPI_InitStructure.cpha      = SPI_CPHA_1;
    SPI_InitStructure.datasize  = SPI_DATASIZE_16B;
    SPI_InitStructure.nss       = SPI_SOFTWARE_NSS;

    // 24.576M, 12.288MHz
    SPI_InitStructure.clk_div   = 2;

    SPI_Init(SPIM, &SPI_InitStructure);
    SPI_Set_Mode(SPIM, SPI_ONLY_SEND_MODE);
    SPI_Cmd(SPIM, ENABLE);
}

int spi_transmit(const uint16_t *txbuf, int count)
{
    RCC_CLK_EN_Ctl(RCC_CLK_EN_SPIM_CLKEN_Msk, ENABLE);

    //GPIO_OutputLo(GPIOA, SPI0_NSS_PIN);
    for (int i = 0; i < count; i++) {
        if (SPIM->SR & SPI_TRANSMIT_FIFO_NOT_FULL) {
            SPIM->DR = txbuf[i];
        } else {
            while (!(SPIM->SR & SPI_TRANSMIT_FIFO_EMPTY)) {
            }
        }
    }
    while (!(SPIM->SR & SPI_TRANSMIT_FIFO_EMPTY)) {
    }
    while (SPIM->SR & SPI_BUSY) {
    }
    //GPIO_OutputHi(GPIOA, SPI0_NSS_PIN);

    RCC_CLK_EN_Ctl(RCC_CLK_EN_SPIM_CLKEN_Msk, DISABLE);

    return count;
}

void spi_open(void)
{
    _gpio_config();
    _spi0_config();
}


#endif // #ifdef SPI_ENABLE





