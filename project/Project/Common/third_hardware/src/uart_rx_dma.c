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
#include <wtm2101_hal.h>
#include <wtm2101_mmap.h>
#include <WTM2101_PMU_register.h>
#include <WTM2101_RCC_register.h>

#include "rcc.h"
#include "pmu.h"
#include "gpio.h"
#include "uart.h"
#include "dma.h"
#include "main.h"

#include "uart_config.h"
#include "uart_dma.inl.h"
#include "uart_rx_dma.h"

#if defined(UART_ENABLE) && defined(UART0RX_DMA_CHANNEL)

//#define DUMP_DMA_LL_CONFIG


////////////////////////////////////////////////////////////////////////////////
//
//  This design using DMA to send bytes.
//  DMA + buffer as VirtualRxFIFO
//
//  UART.RXD --> UART.SmallRxFIFO ---[DMA]--> VirtualRxFIFO --> user
//  UART.TXD <-- UART.SmallTxFIFO <--[DMA]--- BytesBlock <----- user
//

// DMA-based fifo
// `_rx_dma_fifo_head` pointer works with DMA->DAR
// `_rx_dma_fifo_tail` is DMA.DAR
static DMA_LlpTypeDef               _rx_dma_llp[DMA_MAX_LLP_COUNT];
static volatile uint8_t             _rx_dma_buffer[RXFIFO_DEPTH];
static volatile uint32_t            _rx_dma_fifo_head = 0;


void UART_RecvFIFO_Start(UART_TypeDef* UARTx)
{
    const int nr_cfg = 16;
    const int size   = RXFIFO_DEPTH/nr_cfg; // 1024 / 8 == 128
    uint32_t ctl0_cache;
    int offs = 0;
    int i;

    ////////////////////////////////////////////////////////
    //
    //  Prepare
    //
    if (UARTx != UART0) {
        printf("Error: just support UART0\n");
        return;
    }

    if (size >= 255) {
        printf("Error: maximal block count in DMA is 255!\n");
        return;
    }

    // let compiler optimize this code.
    switch (UART0RX_DMA_CHANNEL) {
        case DMA_CHANNEL0:ctl0_cache = (uint32_t)DMA->CTL0; break;
        case DMA_CHANNEL1:ctl0_cache = (uint32_t)DMA->CTL1; break;
        case DMA_CHANNEL2:ctl0_cache = (uint32_t)DMA->CTL2; break;
        case DMA_CHANNEL3:ctl0_cache = (uint32_t)DMA->CTL3; break;
        case DMA_CHANNEL4:ctl0_cache = (uint32_t)DMA->CTL4; break;
        case DMA_CHANNEL5:ctl0_cache = (uint32_t)DMA->CTL5; break;
        default:
            printf("Error: invalid UART0RX_DMA_CHANNEL value\n");
            return;
    }

    memset((char*)_rx_dma_buffer, 0, sizeof(_rx_dma_buffer));
    _rx_dma_fifo_head = 0;

    ////////////////////////////////////////////////////////
    //
    //  build and config linked list
    //
    for (i = 0;i < nr_cfg;i++) {
        _rx_dma_llp[i].src          = (uint32_t)&(UART0->DR_DLL);
        _rx_dma_llp[i].dst          = (uint32_t)&_rx_dma_buffer[offs];
        _rx_dma_llp[i].ctl_reg_high = size;
        _rx_dma_llp[i].ctl_reg_low  = ctl0_cache;
        offs += size;
    }

    // loop linked-list:)
    for (i = 0;i < nr_cfg;i++) {
        _rx_dma_llp[i].llp = (uint32_t)&_rx_dma_llp[i+1];
        if (i == nr_cfg-1) {
            _rx_dma_llp[i].llp = (uint32_t)&_rx_dma_llp[0];
        }
    }

    //  convert from DLM to SYS
    for (i = 0;i < nr_cfg;i++) {
        _rx_dma_llp[i].llp = mmap_to_sys(_rx_dma_llp[i].llp);
        _rx_dma_llp[i].src = mmap_to_sys(_rx_dma_llp[i].src);
        _rx_dma_llp[i].dst = mmap_to_sys(_rx_dma_llp[i].dst);
    }


#ifdef DUMP_DMA_LL_CONFIG
    printf("%s: DMA LLP\n", __func__);
    for (i = 0;i < nr_cfg;i++) {
        printf("> %p: next=%p, dst=%p, ctl.high=%d, ctl.low=0x%08x\n",
                &_rx_dma_llp[i],
                _rx_dma_llp[i].llp,
                _rx_dma_llp[i].dst,
                _rx_dma_llp[i].ctl_reg_high,
                _rx_dma_llp[i].ctl_reg_low);
    }
    printf("\n");
#endif

    DMA_Set_Addr(DMA,
            UART0RX_DMA_CHANNEL,
            (uint32_t)&(UART0->DR_DLL), 
            (uint32_t)NULL,
            0,
            mmap_to_sys((uint32_t)_rx_dma_llp));


    //// DEBUG
    //ECLIC_EnableIRQ(UART0_IRQn);
    DMA_Set_Channel_Enable_Cmd(DMA, UART0RX_DMA_CHANNEL, ENABLE);

    //UART0->MCR &= ~UART_MCR_LB_Msk; // disable loopback
    UART_IT_Cfg(UART0, UART_IT_ERBFI, ENABLE);
}

void UART_RecvFIFO_Stop(UART_TypeDef* UARTx)
{
    if (UARTx != UART0) {
        printf("Error: just support UART0\n");
        return;
    }

    DMA_Set_Channel_Enable_Cmd(DMA, UART0RX_DMA_CHANNEL, DISABLE);
    UART_IT_Cfg(UART0, UART_IT_ERBFI, DISABLE);
}

int UART_RecvFIFO_Read(UART_TypeDef* UARTx, uint8_t* pData, int Size)
{
    uint32_t used;
    uint32_t dar_cache;
    int i;

    ////////////////////////////////////////////////////////
    if (UARTx != UART0) {
        printf("Error: just support UART0\n");
        return -1;
    }

    // let compiler optimize this code.
    switch (UART0RX_DMA_CHANNEL) {
        case DMA_CHANNEL0:dar_cache = (uint32_t)DMA->DAR0; break;
        case DMA_CHANNEL1:dar_cache = (uint32_t)DMA->DAR1; break;
        case DMA_CHANNEL2:dar_cache = (uint32_t)DMA->DAR2; break;
        case DMA_CHANNEL3:dar_cache = (uint32_t)DMA->DAR3; break;
        case DMA_CHANNEL4:dar_cache = (uint32_t)DMA->DAR4; break;
        case DMA_CHANNEL5:dar_cache = (uint32_t)DMA->DAR5; break;
        default:
            printf("Error: invalid UART0RX_DMA_CHANNEL value\n");
            return -1;
    }

    // convert to offset
    dar_cache -= mmap_to_sys((uint32_t)_rx_dma_buffer);

    ////////////////////////////////////////////////////////
    //
    //  check fifo status
    //
    used = (dar_cache - _rx_dma_fifo_head) & (RXFIFO_DEPTH-1);
    if (used == 0) {
        return 0;
    }
    if (used >= RXFIFO_DEPTH*3/4) {
        _rx_dma_fifo_head = dar_cache;
        printf("Error: FIFO overflow, drop all exists data\n");
        return -1;
    }
    if ((pData == NULL) || (Size <= 0)) {
        return used;
    }

    ////////////////////////////////////////////////////////
    //
    //  copy data
    //
    if (used < Size) {
        Size = used;
    }

    for (i = 0;i < Size;i++) {
        *pData++ = _rx_dma_buffer[_rx_dma_fifo_head & (RXFIFO_DEPTH - 1)];
        _rx_dma_fifo_head = (_rx_dma_fifo_head + 1) & (RXFIFO_DEPTH - 1);
    }

    return Size;
}

void UART_RecvFIFO_Pruge(UART_TypeDef* UARTx)
{ 
    uint8_t val;
    while (UART_RecvFIFO_Read(UARTx, &val, 1) > 0) {
    }
}








#endif // #if defined(UART_ENABLE) && defined(UART0RX_DMA_CHANNEL)


