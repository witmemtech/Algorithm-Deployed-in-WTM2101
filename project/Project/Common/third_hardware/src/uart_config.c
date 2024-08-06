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
 * 2021.07.10 bugfix: can not change settings when DMA running.
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

#include "gpio.h"
#include "uart.h"
#include "dma.h"
#include "pmu.h"
#include "rcc.h"
#include "main.h"

#include "uart_config.h"
#include "uart_tx_dma.h"
#include "uart_rx_dma.h"

#ifdef UART_ENABLE

#if defined(UART0TX_DMA_CHANNEL) || \
    defined(UART1TX_DMA_CHANNEL) || \
    defined(UART0RX_DMA_CHANNEL) || \
    defined(UART1RX_DMA_CHANNEL)
#define UART_DMA_ENABLE
#endif


#ifdef UART_DMA_ENABLE
void UART_Handshake_Bugfix(void)
{
    // bugfix-2021.10.13: other change dma handshake
    // begin
    // SYS_CFG[11:8]::dma_reuse
    // - dma_reuse[3] uart1_rx
    // - dma_reuse[2] uart1_tx
    // - dma_reuse[1] uart0_rx
    // - dma_reuse[0] uart0_tx
    // end

#ifdef UART0TX_DMA_CHANNEL
    RCC->SYS_CFG &= ~(0x01 << RCC_SYS_CFG_DMA_REUSE_Pos);
#endif
#ifdef UART0RX_DMA_CHANNEL
    RCC->SYS_CFG &= ~(0x02 << RCC_SYS_CFG_DMA_REUSE_Pos);
#endif
#ifdef UART1TX_DMA_CHANNEL
    RCC->SYS_CFG &= ~(0x04 << RCC_SYS_CFG_DMA_REUSE_Pos);
#endif
#ifdef UART1RX_DMA_CHANNEL
    RCC->SYS_CFG &= ~(0x08 << RCC_SYS_CFG_DMA_REUSE_Pos);
#endif
}
#endif // #if defined(UART_DMA_ENABLE)


void _uart0_config(int linked_list_mode)
{
#ifdef UART0_ENABLE
 
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    GPIO_InitStructure.Pin          = UART0_TX_PIN;
    GPIO_InitStructure.Alternate    = UART0_TX_AF;
    GPIO_InitStructure.Mode         = GPIO_MODE_OUT;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin          = UART0_RX_PIN;
    GPIO_InitStructure.Alternate    = UART0_RX_AF;
    GPIO_InitStructure.Mode         = GPIO_MODE_IN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    

    USART_InitStructure.BaudRate = UART_BAUDRATE;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    #if defined(CONFIG_RAM_UART_VERIFY_HSI24Mx6)
    USART_InitStructure.FIFOCtl = ENABLE;
    #else
    USART_InitStructure.FIFOCtl = DISABLE;    /* enable fifo */
    #endif
    UART_Init(UART0, &USART_InitStructure);

#ifdef UART0TX_DMA_CHANNEL

    RCC_CLK_EN_Ctl(RCC_CLK_EN_GPIO_HCLKEN_Msk, ENABLE);
    RCC_CLK_EN_Ctl(RCC_CLK_EN_DMA_CLKEN_Msk, ENABLE);

    DMA_InitTypeDef DMA_InitStructure;

    //--------------------------------------------------------------------------
    DMA_InitStructure.direction             = MEM_TO_PER_FLOW_CTOL_DMA;
    if (linked_list_mode) {
        DMA_InitStructure.llp_src_en        = ENABLE;   // Linked-list mode enabled
    } else {
        DMA_InitStructure.llp_src_en        = DISABLE;  // Linked-list mode disabled
    }
    DMA_InitStructure.llp_dst_en            = DISABLE;  // Linked-list mode disabled
    DMA_InitStructure.reload_src_en         = DISABLE;  // Not auto reload to init value
    DMA_InitStructure.reload_dst_en         = DISABLE;  // Not auto reload to init value
    DMA_InitStructure.fifo_mode_en          = DISABLE;  // DMA internal FIFO disabled
    DMA_InitStructure.max_abrst             = 0;
    DMA_InitStructure.chanel_priority       = DMA_PRIORITY0;
    DMA_InitStructure.int_en                = DISABLE;
    //--------------------------------------------------------------------------
    DMA_InitStructure.src_msize             = DMA_MSIZE16;// 16 burst
    DMA_InitStructure.src_width             = DMA_WIDTH8; // 8bits
    DMA_InitStructure.src_addr_type         = DMA_ADDRESS_INCREASE;
    DMA_InitStructure.src_per               = DMA_UART0_TX_REQ_OR_AUDIO_CH1; // useless when MEM2PER
    DMA_InitStructure.src_handshaking_type  = DMA_HW_HANDSHAKE;
    //--------------------------------------------------------------------------
    DMA_InitStructure.dst_msize             = DMA_MSIZE16;// 16 burst
    DMA_InitStructure.dst_width             = DMA_WIDTH8; // 8bits
    DMA_InitStructure.dst_addr_type         = DMA_ADDRESS_NO_CHANGE;
    DMA_InitStructure.dst_per               = DMA_UART0_TX_REQ_OR_AUDIO_CH1;
    DMA_InitStructure.dst_handshaking_type  = DMA_HW_HANDSHAKE;

    // bugfix-2021.10.13: other change dma handshake
    // begin
    // SYS_CFG[11:8]::dma_reuse
    // - dma_reuse[3] uart1_rx
    // - dma_reuse[2] uart1_tx
    // - dma_reuse[1] uart0_rx
    // - dma_reuse[0] uart0_tx
    RCC->SYS_CFG &= ~(0x01 << RCC_SYS_CFG_DMA_REUSE_Pos);
    // end

    // bugfix-2021.07.10: can not change settings when DMA running.
    // begin
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Set_Channel_Enable_Cmd(DMA, UART0TX_DMA_CHANNEL, DISABLE);
    // end
    DMA_Init(DMA, UART0TX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    DMA_Clear_All_Interrupt_Cmd(DMA);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, UART0TX_DMA_CHANNEL, DISABLE);
    DMA_Set_Block_Interrupt_Cmd(DMA, UART0TX_DMA_CHANNEL, DISABLE);
    DMA_Set_Error_Interrupt_Cmd(DMA, UART0TX_DMA_CHANNEL, DISABLE);
#endif


#ifdef UART0RX_DMA_CHANNEL
    //--------------------------------------------------------------------------
    DMA_InitStructure.direction             = PER_TO_MEM_FLOW_CTOL_DMA;
    DMA_InitStructure.llp_src_en            = DISABLE;  // Linked-list mode disabled
    DMA_InitStructure.llp_dst_en            = ENABLE;   // Linked-list mode enabled
    DMA_InitStructure.reload_src_en         = DISABLE;  // Not auto reload to init value
    DMA_InitStructure.reload_dst_en         = DISABLE;  // Not auto reload to init value
    DMA_InitStructure.fifo_mode_en          = DISABLE;  // DMA internal FIFO disabled
    DMA_InitStructure.max_abrst             = 0;
    DMA_InitStructure.chanel_priority       = DMA_PRIORITY0;
    DMA_InitStructure.int_en                = DISABLE;
    //--------------------------------------------------------------------------
    DMA_InitStructure.src_msize             = DMA_MSIZE1; // 1 burst
    DMA_InitStructure.src_width             = DMA_WIDTH8; // 8bits
    DMA_InitStructure.src_addr_type         = DMA_ADDRESS_NO_CHANGE;
    DMA_InitStructure.src_per               = DMA_UART0_RX_REQ_OR_AUDIO_CH2;
    DMA_InitStructure.src_handshaking_type  = DMA_HW_HANDSHAKE;
    //--------------------------------------------------------------------------
    DMA_InitStructure.dst_msize             = DMA_MSIZE1; // 1 burst
    DMA_InitStructure.dst_width             = DMA_WIDTH8; // 8bits
    DMA_InitStructure.dst_addr_type         = DMA_ADDRESS_INCREASE;
    DMA_InitStructure.dst_per               = DMA_UART0_RX_REQ_OR_AUDIO_CH2; // useless when PER2MEM
    DMA_InitStructure.dst_handshaking_type  = DMA_HW_HANDSHAKE;

    // bugfix-2021.10.13: other change dma handshake
    // begin
    // SYS_CFG[11:8]::dma_reuse
    // - dma_reuse[3] uart1_rx
    // - dma_reuse[2] uart1_tx
    // - dma_reuse[1] uart0_rx
    // - dma_reuse[0] uart0_tx
    RCC->SYS_CFG &= ~(0x02 << RCC_SYS_CFG_DMA_REUSE_Pos);
    // end

    // bugfix-2021.07.10: can not change settings when DMA running.
    // begin
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Set_Channel_Enable_Cmd(DMA, UART0RX_DMA_CHANNEL, DISABLE);
    // end
    DMA_Init(DMA, UART0RX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    DMA_Clear_All_Interrupt_Cmd(DMA);
    //the UART peripheral missing IDLE interrupt (@_@ |||)
    //The DMA configured as blocks reciver, so I have to check DAR by myself:(
    //the DMA interrupt is useless.
    DMA_Set_Transfer_Interrupt_Cmd(DMA, UART0RX_DMA_CHANNEL, DISABLE);
    DMA_Set_Block_Interrupt_Cmd(DMA, UART0RX_DMA_CHANNEL, DISABLE);
    DMA_Set_Error_Interrupt_Cmd(DMA, UART0RX_DMA_CHANNEL, DISABLE);
#endif

    ////
    //// DEBUG
    //// when you not sure DMA working or not,
    //// enable this CPU interrupt, and add UART0_IRQHandler to bb04p_it.c
    ////
    #ifdef USE_UART_IRQ
    UART_IT_Cfg(UART0, UART_IT_ERBFI | UART_IT_ETBEI, DISABLE);
    ECLIC_ClearPendingIRQ(UART0_IRQn);
    ECLIC_SetPriorityIRQ(UART0_IRQn, 1);
    ECLIC_SetTrigIRQ(UART0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(UART0_IRQn);
    UART_IT_Cfg(UART0, UART_IT_ERBFI, ENABLE);
    #endif
    //ECLIC_DisableIRQ(UART0_IRQn);
    //ECLIC_SetPriorityIRQ(UART0_IRQn, 1);
    //ECLIC_SetTrigIRQ(UART0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    //ECLIC_SetShvIRQ(UART0_IRQn, ECLIC_NON_VECTOR_INTERRUPT);
    //
    //ECLIC_EnableIRQ(UART0_IRQn);
#endif // UART0_ENABLE
}


void _uart1_config(int linked_list_mode)
{
#ifdef UART1_ENABLE

    DMA_InitTypeDef DMA_InitStructure;

    //--------------------------------------------------------------------------
    UART_InitTypeDef UART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART1_CLKEN,ENABLE);

    //--------------------------------------------------------------------------
    GPIO_InitStructure.Pin          = UART1_TX_PIN;
    GPIO_InitStructure.Alternate    = UART1_TX_AF;
    GPIO_InitStructure.Mode         = GPIO_MODE_OUT;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin          = UART1_RX_PIN;
    GPIO_InitStructure.Alternate    = UART1_RX_AF;
    GPIO_InitStructure.Mode         = GPIO_MODE_IN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //--------------------------------------------------------------------------
    UART_InitStructure.BaudRate             = UART_BAUDRATE;
    UART_InitStructure.Parity               = UART_PARITY_NONE;
    UART_InitStructure.StopBits             = UART_STOPBITS_1;
    UART_InitStructure.WordLength           = UART_WORDLENGTH_8B;
    UART_InitStructure.Mode                 = UART_MODE_UART;
    UART_InitStructure.FIFOCtl              = DISABLE;   // UART internal FIFO enabled
    UART_Init(UART1, &UART_InitStructure);


#ifdef UART1TX_DMA_CHANNEL
    //--------------------------------------------------------------------------
    DMA_InitStructure.direction             = MEM_TO_PER_FLOW_CTOL_DMA;
    if (linked_list_mode) {
        DMA_InitStructure.llp_src_en        = ENABLE;   // Linked-list mode enabled
    } else {
        DMA_InitStructure.llp_src_en        = DISABLE;  // Linked-list mode disabled
    }
    DMA_InitStructure.llp_dst_en            = DISABLE;  // Linked-list mode disabled
    DMA_InitStructure.reload_src_en         = DISABLE;  // Not auto reload to init value
    DMA_InitStructure.reload_dst_en         = DISABLE;  // Not auto reload to init value
    DMA_InitStructure.fifo_mode_en          = DISABLE;  // DMA internal FIFO disabled
    DMA_InitStructure.max_abrst             = 0;
    DMA_InitStructure.chanel_priority       = DMA_PRIORITY0;
    DMA_InitStructure.int_en                = DISABLE; 
    //--------------------------------------------------------------------------
    DMA_InitStructure.src_msize             = DMA_MSIZE16;// 16 burst
    DMA_InitStructure.src_width             = DMA_WIDTH8; // 8bits
    DMA_InitStructure.src_addr_type         = DMA_ADDRESS_INCREASE;
    DMA_InitStructure.src_per               = DMA_UART1_TX_REQ_OR_AUDIO_CH2; // useless when MEM2PER
    DMA_InitStructure.src_handshaking_type  = DMA_HW_HANDSHAKE;
    //--------------------------------------------------------------------------
    DMA_InitStructure.dst_msize             = DMA_MSIZE16;// 16 burst
    DMA_InitStructure.dst_width             = DMA_WIDTH8; // 8bits
    DMA_InitStructure.dst_addr_type         = DMA_ADDRESS_NO_CHANGE;
    DMA_InitStructure.dst_per               = DMA_UART1_TX_REQ_OR_AUDIO_CH2;
    DMA_InitStructure.dst_handshaking_type  = DMA_HW_HANDSHAKE;

    // bugfix-2021.10.13: other change dma handshake
    // begin
    // SYS_CFG[11:8]::dma_reuse
    // - dma_reuse[3] uart1_rx
    // - dma_reuse[2] uart1_tx
    // - dma_reuse[1] uart0_rx
    // - dma_reuse[0] uart0_tx
    RCC->SYS_CFG &= ~(0x04 << RCC_SYS_CFG_DMA_REUSE_Pos);
    // end

    // bugfix-2021.07.10: can not change settings when DMA running.
    // begin
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Set_Channel_Enable_Cmd(DMA, UART1TX_DMA_CHANNEL, DISABLE);
    // end
    DMA_Init(DMA, UART1TX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    DMA_Clear_All_Interrupt_Cmd(DMA);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, UART1TX_DMA_CHANNEL, ENABLE);
    DMA_Set_Block_Interrupt_Cmd(DMA, UART1TX_DMA_CHANNEL, DISABLE);
    DMA_Set_Error_Interrupt_Cmd(DMA, UART1TX_DMA_CHANNEL, DISABLE);
#endif

#ifdef UART1RX_DMA_CHANNEL
    //--------------------------------------------------------------------------
    DMA_InitStructure.direction             = PER_TO_MEM_FLOW_CTOL_DMA;
    DMA_InitStructure.llp_src_en            = DISABLE;  // Linked-list mode disabled
    DMA_InitStructure.llp_dst_en            = ENABLE;   // Linked-list mode enabled
    DMA_InitStructure.reload_src_en         = DISABLE;  // Not auto reload to init value
    DMA_InitStructure.reload_dst_en         = DISABLE;  // Not auto reload to init value
    DMA_InitStructure.fifo_mode_en          = DISABLE;  // DMA internal FIFO disabled
    DMA_InitStructure.max_abrst             = 0;
    DMA_InitStructure.chanel_priority       = DMA_PRIORITY0;
    DMA_InitStructure.int_en                = DISABLE;
    //--------------------------------------------------------------------------
    DMA_InitStructure.src_msize             = DMA_MSIZE1; // 1 burst
    DMA_InitStructure.src_width             = DMA_WIDTH8; // 8bits
    DMA_InitStructure.src_addr_type         = DMA_ADDRESS_NO_CHANGE;
    DMA_InitStructure.src_per               = DMA_UART1_RX_REQ_OR_AUDIO_CH1;
    DMA_InitStructure.src_handshaking_type  = DMA_HW_HANDSHAKE;
    //--------------------------------------------------------------------------
    DMA_InitStructure.dst_msize             = DMA_MSIZE1; // 1 burst
    DMA_InitStructure.dst_width             = DMA_WIDTH8; // 8bits
    DMA_InitStructure.dst_addr_type         = DMA_ADDRESS_INCREASE;
    DMA_InitStructure.dst_per               = DMA_UART1_RX_REQ_OR_AUDIO_CH1; // useless when PER2MEM
    DMA_InitStructure.dst_handshaking_type  = DMA_HW_HANDSHAKE;

    // bugfix-2021.10.13: other change dma handshake
    // begin
    // SYS_CFG[11:8]::dma_reuse
    // - dma_reuse[3] uart1_rx
    // - dma_reuse[2] uart1_tx
    // - dma_reuse[1] uart0_rx
    // - dma_reuse[0] uart0_tx
    RCC->SYS_CFG &= ~(0x08 << RCC_SYS_CFG_DMA_REUSE_Pos);
    // end

    // bugfix-2021.07.10: can not change settings when DMA running.
    // begin
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Set_Channel_Enable_Cmd(DMA, UART1RX_DMA_CHANNEL, DISABLE);
    // end
    DMA_Init(DMA, UART1RX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    DMA_Clear_All_Interrupt_Cmd(DMA);
    //the UART peripheral missing IDLE interrupt (@_@ |||)
    //The DMA configured as blocks reciver, so I have to check DAR by myself:(
    //the DMA interrupt is useless.
    DMA_Set_Transfer_Interrupt_Cmd(DMA, UART1TX_DMA_CHANNEL, DISABLE);
    DMA_Set_Block_Interrupt_Cmd(DMA, UART1TX_DMA_CHANNEL, DISABLE);
    DMA_Set_Error_Interrupt_Cmd(DMA, UART1TX_DMA_CHANNEL, DISABLE);

#endif

    #ifdef USE_UART_IRQ
    UART_IT_Cfg(UART1, UART_IT_ERBFI | UART_IT_ETBEI, DISABLE);
    ECLIC_ClearPendingIRQ(UART1_IRQn);
    ECLIC_SetPriorityIRQ(UART1_IRQn, 1);
    ECLIC_SetTrigIRQ(UART1_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(UART1_IRQn);
    UART_IT_Cfg(UART1, UART_IT_ERBFI, ENABLE);
    #endif


#endif // UART1_ENABLE
}


void uart_open()
{
    _uart0_config(ENABLE);
    _uart1_config(ENABLE);

#ifdef UART_DMA_ENABLE
    UART_Handshake_Bugfix();
#endif
}

int send_one_byte(UART_TypeDef *dst_UART, uint8_t byte) {
  while (UART_Flag_GetStatBit(dst_UART,UART_FLAG_TEMT) == RESET);
  UART_SendData(dst_UART, byte);
}

uint8_t recv_one_byte(UART_TypeDef *dst_UART) {
  while (!(UART_Flag_GetStat(dst_UART) & UART_FLAG_DR));
  return UART_ReceiveData(dst_UART);
}



#endif // #ifdef UART_ENABLE

