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

#if defined(I2S_ENABLE) && defined(USE_I2S_OUT)


static void _gpio_pre_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_CLK_EN_Ctl(RCC_CLK_EN_GPIO_HCLKEN_Msk, ENABLE);

    GPIO_InitStructure.Pin = I2STX_CK_PIN | I2STX_SDO_PIN | I2STX_WS_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPD;
    GPIO_InitStructure.Alternate = 0; // GPIO
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void _gpio_post_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_CLK_EN_Ctl(RCC_CLK_EN_GPIO_HCLKEN_Msk, ENABLE);

    GPIO_InitStructure.Pin = I2STX_CK_PIN | I2STX_SDO_PIN | I2STX_WS_PIN;
    GPIO_InitStructure.Alternate = I2STX_CK_AF| I2STX_SDO_AF | I2STX_WS_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void _gpio_unconfig(void)
{
    GPIO_DeInit(GPIOA, I2STX_CK_PIN | I2STX_SDO_PIN | I2STX_WS_PIN);
}

static void _iis_tx_config(I2S_TypeDef* h)
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
    uint32_t sysclock;
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
    I2S_TxCfg(h,I2S_RES_LEN_32);
#else
    I2S_TxCfg(h,I2S_RES_LEN_16);
#endif

    //  This I2S peripheral missing hardware DMA handshakes
    //  using interrupt as handshake, so take care about bellow config!!!
    //
    // there are L+R data per channel
    // tx-rx-count range: 0, 2, 4, 8
    //
    // RxFIFO hardware: 
    //  Left:  8 x wordsize
    //  Right: 8 x wordsize (trigger)
    //
    // TxFIFO hardware:
    //  Left:  8 x wordsize
    //  Right: 8 x wordsize (trigger)
    //
    //## example
    //  I2S.TxLVL == 3
    //  DMA.msize == DMA_MSIZE8
    //
    //          +------+     +---------+
    //  DMA --> |TxFIFO| --> |TxShifter| --> SD
    //   ^      +------+     +---------+
    //   |          |
    //   +---intr---+
    //
    //  when TxFIFO.cnt <= 3, intr valid
    //  DMA copy 4x2 data to it,
    //  !!! and intr must keep low after DMA transfer !!!
    //   - or -
    //  system hang
    //
    I2S_TxFIFO_LVLCfg(h, 3); // DO NOT CHANGE this
    I2S_TxFIFO_Flush(h);
    I2S_IT_MskCtl(h, I2S_IT_TXFO, ENABLE); // no overrun interrupt
    I2S_IT_MskCtl(h, I2S_IT_TXFE, DISABLE);// enable tx-fifo empty interrupt
    I2S_IT_MskCtl(h, I2S_IT_RXFO, ENABLE); // no overrun interrupt
    I2S_IT_MskCtl(h, I2S_IT_RXDA, ENABLE); // no rx-fifo available interrupt
}

static void _iis_tx_dma_config(I2S_TypeDef* h, int dma_channel)
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
    dma_inittypedef.src_addr_type       = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_addr_type       = DMA_ADDRESS_NO_CHANGE;

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
    dma_inittypedef.int_en              = DISABLE;


    ////////////////////////////////////////////////////////////////////////
    dma_inittypedef.direction = MEM_TO_PER_FLOW_CTOL_DMA;
    if (h == I2S0) {
        dma_inittypedef.src_per             = DMA_I2S0_REQ;
        dma_inittypedef.dst_per             = DMA_I2S0_REQ;
    } else if (h == I2S1) {
        dma_inittypedef.src_per             = DMA_I2S1_REQ;
        dma_inittypedef.dst_per             = DMA_I2S1_REQ;
    }
    DMA_Init(DMA, dma_channel, &dma_inittypedef);

    ////////////////////////////////////////////////////////////////////////
    //
    //  Enable DMA
    //
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, dma_channel, DISABLE);
}


static void _iis_tx_dma_fifo_init(I2S_TypeDef* h, int dma_channel)
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

    for (int i = 0;i < I2STX_NR_BLOCKS;i++) {
        // 80 x (L+R) <=> 160 x 32bits
        i2s_tx_llpcfg[i].llp         = mmap_to_sys((uint32_t)&i2s_tx_llpcfg[i+1]);
        i2s_tx_llpcfg[i].src         = mmap_to_sys((uint32_t)&i2s_tx_buffer[I2S_BLOCK_SIZE*i]);
        i2s_tx_llpcfg[i].dst         = mmap_to_sys((uint32_t)&(h->TXDMA));
        i2s_tx_llpcfg[i].ctl_reg_high= I2S_BLOCK_SIZE;
        i2s_tx_llpcfg[i].ctl_reg_low = ctl0_cache;
    }
    i2s_tx_llpcfg[I2STX_NR_BLOCKS-1].llp = mmap_to_sys((uint32_t)&i2s_tx_llpcfg[0]);
}


uint32_t iis_tx_get_sclk_freq(void)
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

#if defined(CONFIG_RAM_K1_IISMIC_REALTIME_HSI24Mx2) || \
    defined(CONFIG_QSPI_K1_IISMIC_REALTIME_HSI24Mx2) || \
    defined(USE_ES_8311)

void _iis_mclk_start(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    uint32_t pcm_freq;
    uint32_t clkdiv;
    uint32_t sysclock;
    uint32_t ahbclock;
    uint32_t apbclock;

    RCC_CLK_EN_Ctl(RCC_CLK_EN_GPIO_HCLKEN_Msk, ENABLE);
    GPIO_InitStructure.Mode      = GPIO_MODE_OUT;
    GPIO_InitStructure.Pin       = GPIO_PIN_9;
    GPIO_InitStructure.Alternate = GPIO_AF9_I2S;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    sysclock = RCC_Get_SYSClk();

    clkdiv = RCC_AHB_Get_ClkDiv();
    ahbclock = sysclock / (clkdiv + 1);

    clkdiv = RCC_APB0_Get_ClkDiv();
    apbclock = ahbclock / (clkdiv + 1);

#ifdef I2S_AND_AUD_SAME_FREQ
    pcm_freq = audio_get_pcm_freq();
#else
    pcm_freq = I2S_FREQ;
#endif
    //
    // clkdiv = round(sysclock/(pcm_freq*nbits*2channels))
    //
    // mclk is 256 x pcm_freq
#ifdef USE_I2S_32BITS
    clkdiv = (10*apbclock/(pcm_freq*32*2) + 5)/10;
    clkdiv = clkdiv / 4;
#else
    clkdiv = (10*apbclock/(pcm_freq*16*2) + 5)/10;
    clkdiv = clkdiv / 8;
#endif

    RCC_I2S_M_Set_ClkDiv(clkdiv - 1);
    RCC_CLK_EN_Ctl(RCC_CLK_EN_I2S_MCLKEN_Msk, ENABLE);
}
#endif

void iis_tx_open(void)
{
    //>> bugfixed-2022.05.19
    // maybe I2S have some bug, so we pulldown GPIO first.
    _gpio_pre_config();
    _iis_tx_config(I2STX_INSTANCE);
    #if defined(CONFIG_RAM_K1_IISMIC_REALTIME_HSI24Mx2) || \
        defined(CONFIG_QSPI_K1_IISMIC_REALTIME_HSI24Mx2) || \
        defined(USE_ES_8311)
    _iis_mclk_start();
    #endif
    _iis_tx_dma_config(I2STX_INSTANCE, I2STX_DMA_CHANNEL);   
    _iis_tx_dma_fifo_init(I2STX_INSTANCE, I2STX_DMA_CHANNEL);
}

void iis_tx_start(void)
{
    DMA_Set_Addr(DMA, I2STX_DMA_CHANNEL, 0, 0, 0, mmap_to_sys((uint32_t)i2s_tx_llpcfg));
    DMA_Set_Channel_Enable_Cmd(DMA, I2STX_DMA_CHANNEL, ENABLE);
    I2S_TxBlkCtl(I2STX_INSTANCE,ENABLE);
    I2S_TxChlCtl(I2STX_INSTANCE,ENABLE);
    I2S_ClkCtl(I2STX_INSTANCE,ENABLE);
    I2S_Ctl(I2STX_INSTANCE,ENABLE);

    //>> bugfixed-2022.03.22
    // I2S mode is master (default)
    // so GPIOs are conflict when other I2S Master startup early
    _gpio_post_config();
}

void iis_tx_stop(void)
{
    _gpio_unconfig();

    I2S_Ctl(I2STX_INSTANCE,DISABLE);
    I2S_ClkCtl(I2STX_INSTANCE,DISABLE);
    I2S_TxChlCtl(I2STX_INSTANCE,DISABLE);
    I2S_TxBlkCtl(I2STX_INSTANCE,DISABLE);
    DMA_Set_Channel_Enable_Cmd(DMA, I2STX_DMA_CHANNEL, DISABLE);
}


#endif //endif defined(I2S_ENABLE) && defined(USE_I2S_OUT)


                                                                              
