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

#include "gpio.h"
#include "uart.h"
#include "dma.h"
#include "main.h"

#include "uart_config.h"
#include "uart_dma.inl.h"
#include "uart_tx_dma.h"

#if defined(UART_ENABLE) && defined(UART0TX_DMA_CHANNEL)

//#define DUMP_DMA_LL_CONFIG


////////////////////////////////////////////////////////////////////////////////
//
//  This design using DMA to send bytes.
//  DMA + buffer as VirtualRxFIFO
//
//  UART.RXD --> UART.SmallRxFIFO ---[DMA]--> VirtualRxFIFO --> user
//  UART.TXD <-- UART.SmallTxFIFO <--[DMA]--- BytesBlock <----- user
//

// DMA-based async sending 
static DMA_LlpTypeDef               _tx_dma_llp[DMA_MAX_LLP_COUNT];

void UART_SendBlock_Async(UART_TypeDef* UARTx, ...)
{
    uint8_t* buffer = NULL;
    int bufsize;
    va_list ap;
    int chl = -1;
    int offs;
    int size;
    int nr_cfg;
    int i;
    uint32_t ctl0_cache;

#ifdef UART0TX_DMA_CHANNEL
    if (UARTx == UART0) {
        chl = UART0TX_DMA_CHANNEL;
    } 
#endif
#ifdef UART1TX_DMA_CHANNEL
    if (UARTx == UART1) {
        chl = UART1TX_DMA_CHANNEL;
    }
#endif
    if (chl < 0) {
        return;
    }

    switch (chl) {
        case DMA_CHANNEL0:ctl0_cache = (uint32_t)DMA->CTL0; break;
        case DMA_CHANNEL1:ctl0_cache = (uint32_t)DMA->CTL1; break;
        case DMA_CHANNEL2:ctl0_cache = (uint32_t)DMA->CTL2; break;
        case DMA_CHANNEL3:ctl0_cache = (uint32_t)DMA->CTL3; break;
        case DMA_CHANNEL4:ctl0_cache = (uint32_t)DMA->CTL4; break;
        case DMA_CHANNEL5:ctl0_cache = (uint32_t)DMA->CTL5; break;
        default:
            printf("Error: invalid channel id\n");
            return;
    }

    ////////////////////////////////////////////////////////
    // Wait last Transmitting
    while (DMA_Get_Channel_Enable_Status(DMA, chl)) {
    }
    UART_IT_Cfg(UARTx, UART_IT_ETBEI, DISABLE);
    while (UART_Flag_GetStatBit(UARTx, UART_FLAG_TEMT) == RESET) {
    }

    ////////////////////////////////////////////////////////
    //
    //  parser user arguments
    //
    va_start(ap, UARTx);
    nr_cfg = 0;
    while (1) {
        // fetch buffer and size
        buffer  = va_arg(ap, uint8_t*);
        bufsize = va_arg(ap, int);
        if ((buffer == NULL) || (bufsize == 0)) {
            break;
        }

        // build linked list config
        for (offs = 0;offs < bufsize;offs += DMA_MAX_BLK_SIZE) {
            if (nr_cfg > DMA_MAX_LLP_COUNT) {
                printf("Error: overflow LLP\n");
                break;
            }

            size = bufsize - offs;
            if (size > DMA_MAX_BLK_SIZE) {
                size = DMA_MAX_BLK_SIZE;
            }

            _tx_dma_llp[nr_cfg].src           = (uint32_t)&buffer[offs];
            _tx_dma_llp[nr_cfg].dst           = NULL;
            _tx_dma_llp[nr_cfg].ctl_reg_high  = size;
            _tx_dma_llp[nr_cfg].ctl_reg_low   = ctl0_cache;
            nr_cfg++;
        }
    }

    if (nr_cfg <= 0) {
        va_end(ap);
        return;
    }

    ////////////////////////////////////////////////////////
    //
    //  build linked list
    //
    for (i = 0;i < nr_cfg;i++) {
        _tx_dma_llp[i].llp = (uint32_t)&_tx_dma_llp[i+1];
        if (i == nr_cfg-1) {
            _tx_dma_llp[i].llp = NULL;
        }
    }

    ////////////////////////////////////////////////////////
    //
    //  convert from DLM to SYS
    //
    for (i = 0;i < nr_cfg;i++) {
        _tx_dma_llp[i].llp = mmap_to_sys(_tx_dma_llp[i].llp);
        _tx_dma_llp[i].src = mmap_to_sys(_tx_dma_llp[i].src);
        _tx_dma_llp[i].dst = mmap_to_sys(_tx_dma_llp[i].dst);
    }


#ifdef DUMP_DMA_LL_CONFIG
    ////////////////////////////////////////////////////////
    //
    //  Perform new DMA Transmitting
    //
    for (i = 0;i < nr_cfg;i++) {
        printf("> %p: next=%p, %p, %d\n",
                _tx_dma_llp[i],
                _tx_dma_llp[i].llp,
                _tx_dma_llp[i].src,
                _tx_dma_llp[i].ctl_reg_high);
    }
    printf("\n");
#endif

    DMA_Set_Addr(DMA,
            chl,
            (uint32_t)NULL,
            (uint32_t)&(UARTx->DR_DLL),
            0,
            mmap_to_sys((uint32_t)_tx_dma_llp));

    DMA_Set_Channel_Enable_Cmd(DMA, chl, ENABLE);
    UART_IT_Cfg(UARTx, UART_IT_ETBEI, ENABLE);

    va_end(ap);
}



#endif // #if defined(UART_ENABLE) && defined(UART0TX_DMA_CHANNEL)


