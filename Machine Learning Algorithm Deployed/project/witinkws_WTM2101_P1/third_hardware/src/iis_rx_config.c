#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "gpio.h"

#include "WTM2101.h"
#include "rcc.h"
#include "i2s.h"
#include "audio.h"
#include "dma.h"

#include "bb04p1_hal.h"
#include "basic_config.h"
#include "memory_placement.h"

#include "iis_tx_config.h"
#include "iis_rx_config.h"
#include "audio_config.h"
#include "bb04p1_mmap.h"

#if defined(I2S_ENABLE) && defined(USE_I2S_IN)


static void _gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_CLK_EN_Ctl(RCC_CLK_EN_GPIO_HCLKEN_Msk, ENABLE);

    GPIO_InitStructure.Pin = I2SRX_CK_PIN | I2SRX_SDI_PIN | I2SRX_WS_PIN;
    GPIO_InitStructure.Alternate = I2SRX_CK_AF| I2SRX_SDI_AF | I2SRX_WS_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void _gpio_unconfig(void)
{
    GPIO_DeInit(GPIOA, I2SRX_CK_PIN | I2SRX_SDI_PIN | I2SRX_WS_PIN);
}

static void _iis_rx_config(I2S_TypeDef* h)
{
    if (h == I2S0) {
        RCC_CLK_EN_Ctl(RCC_I2S0_CLKEN,ENABLE);
        RCC_Peri_Rst(RCC_I2S0_RSTN);
    } else if (h == I2S1) {
        RCC_CLK_EN_Ctl(RCC_I2S1_CLKEN,ENABLE);
        RCC_Peri_Rst(RCC_I2S1_RSTN);
    } else {
        return;
    }

#ifdef USE_I2S_MASTER
    I2S_Mode_Sel(h, I2S_MASTER);
#else
    I2S_Mode_Sel(h, I2S_SLAVE);
#endif

#ifdef I2S_AND_AUD_SAME_FREQ
    uint32_t pcm_freq = audio_get_pcm_freq();
#else
    uint32_t pcm_freq = I2S_FREQ;
#endif

    uint32_t clkdiv;
    uint32_t sysclock = 0;
    uint32_t ahbclock;
    uint32_t apbclock;

    sysclock = RCC_Get_SYSClk();

    clkdiv = RCC_AHB_Get_ClkDiv();
    ahbclock = sysclock / (clkdiv + 1);

    clkdiv = RCC_APB0_Get_ClkDiv();
    apbclock = ahbclock / (clkdiv + 1);

    //
    // clkdiv = round(sysclock/(pcm_freq*nbits*2channels))
    //
#ifdef USE_I2S_32BITS
    I2S_ClkCfg(h,I2S_SCLKNUM_32,I2S_GATESCLKNUM_NONE);
    clkdiv = (10*apbclock/(pcm_freq*32*2) + 5)/10;
#else
    I2S_ClkCfg(h,I2S_SCLKNUM_16,I2S_GATESCLKNUM_NONE);
    clkdiv = (10*apbclock/(pcm_freq*16*2) + 5)/10;
#endif

    if (h == I2S0) {
        RCC_I2S0_Set_ClkDiv(clkdiv - 1);
    } else {
        RCC_I2S1_Set_ClkDiv(clkdiv - 1);
    }
    I2S_Ctl(h,DISABLE);

#ifdef USE_I2S_32BITS
    I2S_RxCfg(h,I2S_RES_LEN_32);
#else
    I2S_RxCfg(h,I2S_RES_LEN_16);
#endif

    I2S_RxFIFO_LVLCfg(h, 4); // DO NOT CHANGE this
    I2S_RxFIFO_Flush(h);
    I2S_IT_MskCtl(h, I2S_IT_RXFO, ENABLE); // no overrun interrupt
    I2S_IT_MskCtl(h, I2S_IT_RXDA, DISABLE);// enable rx-fifo available interrupt

    //I2S_RxBlkCtl(h,ENABLE);
    //I2S_RxChlCtl(h,ENABLE);
    //I2S_ClkCtl(h,ENABLE);
    //I2S_Ctl(h,ENABLE);
}


static void _iis_rx_dma_config(I2S_TypeDef* h, int dma_channel)
{
    DMA_InitTypeDef dma_inittypedef;
    
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);

    DMA_Clear_All_Interrupt_Cmd(DMA);
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    
    dma_inittypedef.llp_src_en          = ENABLE;
    dma_inittypedef.llp_dst_en          = ENABLE;
    dma_inittypedef.reload_src_en       = DISABLE;
    dma_inittypedef.reload_dst_en       = DISABLE;
    dma_inittypedef.src_msize           = DMA_MSIZE8;   // DO NOT CHANGE this
    dma_inittypedef.dst_msize           = DMA_MSIZE8;   // DO NOT CHANGE this
    dma_inittypedef.src_addr_type       = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.dst_addr_type       = DMA_ADDRESS_INCREASE;

#ifdef USE_I2S_32BITS
    dma_inittypedef.src_width           = DMA_WIDTH32;
    dma_inittypedef.dst_width           = DMA_WIDTH32;
#else
    dma_inittypedef.src_width           = DMA_WIDTH16;
    dma_inittypedef.dst_width           = DMA_WIDTH16;
#endif

    dma_inittypedef.fifo_mode_en        = DISABLE;
    dma_inittypedef.max_abrst           = 0;
    dma_inittypedef.src_handshaking_type= DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type= DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority     = DMA_PRIORITY0;
    //dma_inittypedef.int_en              = DISABLE;
    dma_inittypedef.int_en              = ENABLE;


    ////////////////////////////////////////////////////////////////////////
    dma_inittypedef.direction = PER_TO_MEM_FLOW_CTOL_DMA;
    if (h == I2S0) {
        dma_inittypedef.src_per         = DMA_I2S0_REQ;
        dma_inittypedef.dst_per         = DMA_I2S0_REQ;
    } else if (h == I2S1) {
        dma_inittypedef.src_per         = DMA_I2S1_REQ;
        dma_inittypedef.dst_per         = DMA_I2S1_REQ;
    }
    DMA_Init(DMA, dma_channel, &dma_inittypedef);

    ////////////////////////////////////////////////////////////////////////
    //
    //  Enable DMA
    //
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);

    //DMA_Set_Transfer_Interrupt_Cmd(DMA, dma_channel, DISABLE);
    DMA_Set_Block_Interrupt_Cmd(DMA, dma_channel, ENABLE);





}

static void _iis_rx_dma_fifo_init(I2S_TypeDef* h, int dma_channel)
{
    uint32_t ctl0_cache;

    switch (dma_channel) {
        case DMA_CHANNEL0: ctl0_cache = (uint32_t)DMA->CTL0; break;
        case DMA_CHANNEL1: ctl0_cache = (uint32_t)DMA->CTL1; break;
        case DMA_CHANNEL2: ctl0_cache = (uint32_t)DMA->CTL2; break;
        case DMA_CHANNEL3: ctl0_cache = (uint32_t)DMA->CTL3; break;
        case DMA_CHANNEL4: ctl0_cache = (uint32_t)DMA->CTL4; break;
        case DMA_CHANNEL5: ctl0_cache = (uint32_t)DMA->CTL5; break;
        default:break;
    }

    for (int i = 0;i < I2SRX_NR_BLOCKS;i++) {
        // 80 x (L+R) <=> 160 x 32bits
        i2s_rx_llpcfg[i].llp         = mmap_to_sys((uint32_t)&i2s_rx_llpcfg[i+1]);
        i2s_rx_llpcfg[i].src         = mmap_to_sys((uint32_t)&(h->RXDMA));
        i2s_rx_llpcfg[i].dst         = mmap_to_sys((uint32_t)&i2s_rx_buffer[I2S_BLOCK_SIZE*i]);
        i2s_rx_llpcfg[i].ctl_reg_high= I2S_BLOCK_SIZE;
        i2s_rx_llpcfg[i].ctl_reg_low = ctl0_cache;
    }
    i2s_rx_llpcfg[I2SRX_NR_BLOCKS-1].llp = mmap_to_sys((uint32_t)&i2s_rx_llpcfg[0]);
}

uint32_t iis_rx_dma_pointer(void)
{
    uint32_t dar_cache;

    switch (I2SRX_DMA_CHANNEL) {
        case DMA_CHANNEL0:dar_cache = (uint32_t)DMA->DAR0; break;
        case DMA_CHANNEL1:dar_cache = (uint32_t)DMA->DAR1; break;
        case DMA_CHANNEL2:dar_cache = (uint32_t)DMA->DAR2; break;
        case DMA_CHANNEL3:dar_cache = (uint32_t)DMA->DAR3; break;
        case DMA_CHANNEL4:dar_cache = (uint32_t)DMA->DAR4; break;
        case DMA_CHANNEL5:dar_cache = (uint32_t)DMA->DAR5; break;
        default:break;
    }

    // convert to offset
    dar_cache -= mmap_to_sys((uint32_t)i2s_rx_buffer);
    return dar_cache;
}


uint32_t iis_rx_get_sclk_freq(void)
{
    uint32_t sysclock = RCC_Get_SYSClk();
#ifdef I2S_AND_AUD_SAME_FREQ
    uint32_t pcm_freq = audio_get_pcm_freq();
#else
    uint32_t pcm_freq = I2S_FREQ;
#endif

#ifdef USE_I2S_32BITS
    int clkdiv = (10*sysclock/(pcm_freq*32*2) + 5)/10;
#else
    int clkdiv = (10*sysclock/(pcm_freq*16*2) + 5)/10;
#endif

    return sysclock / clkdiv;
}


void iis_rx_open(void)
{
    _iis_rx_config(I2SRX_INSTANCE);
    _iis_rx_dma_config(I2SRX_INSTANCE, I2SRX_DMA_CHANNEL);   
    _iis_rx_dma_fifo_init(I2SRX_INSTANCE, I2SRX_DMA_CHANNEL);
}

void iis_rx_start(void)
{
    DMA_Set_Addr(DMA, I2SRX_DMA_CHANNEL, 0, 0, 0, mmap_to_sys((uint32_t)i2s_rx_llpcfg));
    DMA_Set_Channel_Enable_Cmd(DMA, I2SRX_DMA_CHANNEL, ENABLE);
    I2S_RxBlkCtl(I2SRX_INSTANCE,ENABLE);
    I2S_RxChlCtl(I2SRX_INSTANCE,ENABLE);
    I2S_ClkCtl(I2SRX_INSTANCE,ENABLE);
    I2S_Ctl(I2SRX_INSTANCE,ENABLE);

    //>> bugfixed-2022.03.22
    // I2S mode is master (default)
    // so GPIOs are conflict when other I2S Master startup early
    _gpio_config();
}

void iis_rx_stop(void)
{
    _gpio_unconfig();

    I2S_Ctl(I2SRX_INSTANCE,DISABLE);
    I2S_ClkCtl(I2SRX_INSTANCE,DISABLE);
    I2S_RxChlCtl(I2SRX_INSTANCE,DISABLE);
    I2S_RxBlkCtl(I2SRX_INSTANCE,DISABLE);
    DMA_Set_Channel_Enable_Cmd(DMA, I2SRX_DMA_CHANNEL, DISABLE);
}


void iis_tx_close(void) {
    if (I2STX_INSTANCE == I2S0) {
        RCC_CLK_EN_Ctl(RCC_I2S0_CLKEN,DISABLE);
    } else if (I2STX_INSTANCE == I2S1) {
        RCC_CLK_EN_Ctl(RCC_I2S1_CLKEN,DISABLE);
    }
}

#endif //endif defined(I2S_ENABLE) && defined(USE_I2S_IN)


                                                                              
