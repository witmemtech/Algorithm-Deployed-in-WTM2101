#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "gpio.h"

#include "WTM2101.h"
#include "rcc.h"
#include "pmu.h"
#include "audio.h"
#include "dma.h"

#include "basic_config.h"
#include "audio_config.h"

#ifdef AUDIO_ENABLE

#ifdef USE_AMIC
 #define AUDIO_FROM_PDM0
 #define USING_AMIC
#else
 #if AUDIO_CLK_PIN == GPIO_PIN_4
 #define AUDIO_FROM_PDM0
 #define USING_DMIC
 #endif

 #if AUDIO_CLK_PIN == GPIO_PIN_8
 #define AUDIO_FROM_PDM1
 #define USING_DMIC
 #endif
#endif

#if (4000000 <= HSE_VALUE) && (HSE_VALUE <= 4096000)
#elif (20000000 == HSE_VALUE)
#elif (24000000 <= HSE_VALUE) && (HSE_VALUE <= 24576000)
#else
#error "Only support HSE_VALUE range 4M..4.096M or 24.000M..24.576M"
#endif

uint32_t audio_get_pcm_freq(void)
{
    uint32_t pcm_freq;

    if ((4000000 <= HSE_VALUE) && (HSE_VALUE <= 4096000)) {
        // HSE -> AUDIODIV=2 -> PDMCLKDIV=1 -> Sinc5D32 -> isincD2 -> halfbandD2
        pcm_freq = HSE_VALUE/2/1/32/2/2;
    } else if (20000000 == HSE_VALUE) {
        // HSE -> AUDIODIV=10 -> PDMCLKDIV=1 -> Sinc5D32 -> isincD2 -> halfbandD2
        pcm_freq = HSE_VALUE/10/1/32/2/2;
    } else if ((24000000 <= HSE_VALUE) && (HSE_VALUE <= 24576000)) {
        // HSE -> AUDIODIV=6 -> PDMCLKDIV=2 -> Sinc5D32 -> isincD2 -> halfbandD2
        pcm_freq = HSE_VALUE/6/2/32/2/2;
    }

    return pcm_freq;
}

static void _gpio_config(void)
{
#ifdef USING_DMIC
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin          = AUDIO_CLK_PIN; 
    GPIO_InitStructure.Mode         = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate    = AUDIO_CLK_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin          = AUDIO_DATA_PIN; 
    GPIO_InitStructure.Mode         = GPIO_MODE_IN;
    GPIO_InitStructure.Alternate    = AUDIO_DATA_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
}

static void _audio_dma_config()
{
    DMA_InitTypeDef dma_inittypedef;
   
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);
    DMA_Clear_All_Interrupt_Cmd(DMA);

#if AUDIO_DMA_COUNT > 255
#error "count > 255, using LLP-mode please"
#endif
    dma_inittypedef.llp_src_en              = DISABLE;
    dma_inittypedef.llp_dst_en              = DISABLE;


    dma_inittypedef.reload_src_en           = DISABLE;
    dma_inittypedef.reload_dst_en           = DISABLE;
    dma_inittypedef.direction               = MEM_TO_MEM_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize               = DMA_MSIZE1;   
    dma_inittypedef.dst_msize               = DMA_MSIZE1;   
    dma_inittypedef.src_addr_type           = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.dst_addr_type           = DMA_ADDRESS_INCREASE;
    dma_inittypedef.src_width               = DMA_WIDTH32;    // two int16_t samples per read-op
    dma_inittypedef.dst_width               = DMA_WIDTH32;
    dma_inittypedef.src_per                 = DMA_AUDIO_CH0_REQ;
    dma_inittypedef.dst_per                 = DMA_AUDIO_CH0_REQ;
    dma_inittypedef.fifo_mode_en            = DISABLE;
    dma_inittypedef.max_abrst               = 0;
    dma_inittypedef.src_handshaking_type    = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type    = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority         = DMA_PRIORITY0;
    dma_inittypedef.int_en                  = ENABLE;
    DMA_Init(DMA, AUDIO_DMA_CHANNEL, &dma_inittypedef);

    DMA_Set_Enable_Cmd(DMA, ENABLE);

    DMA_Set_Transfer_Interrupt_Cmd(DMA, AUDIO_DMA_CHANNEL, ENABLE);
}

////////////////////////////////////////////////////////////
//
//  Analog MIC Config
//
//  0:-12.00 dB
//  1:-11.25 dB
//  2:-10.50 dB
//  3: -9.75 dB
//  4: -9.00 dB
//  5: -8.25 dB
//  6: -7.50 dB
//  7: -6.75 dB
//  8: -6.00 dB
//  9: -5.25 dB
// 10: -4.50 dB
// 11: -3.75 dB
// 12: -3.00 dB
// 13: -2.25 dB
// 14: -1.50 dB
// 15: -0.75 dB
// 16:  0    dB
// 17: +0.75 dB
// 18: +1.50 dB
// 19: +2.25 dB
// 20: +3.00 dB
// 21: +3.75 dB
// 22: +4.50 dB
// 23: +5.25 dB
// 24: +6.00 dB
// 25: +6.75 dB
// 26: +7.50 dB
// 27: +8.25 dB
// 28: +9.00 dB
// 29: +9.75 dB
// 30: +10.50 dB
// 31: +11.25 dB
// 32: +12.00 dB
// 33: +12.75 dB
// 34: +13.50 dB
// 35: +14.25 dB
// 36: +15.00 dB
// 37: +15.75 dB
// 38: +16.50 dB
// 39: +17.25 dB
// 40: +18.00 dB
// 41: +18.75 dB
// 42: +19.50 dB
// 43: +20.25 dB
// 44: +21.00 dB
// 45: +21.75 dB
// 46: +22.50 dB
// 47: +23.25 dB
// 48: +24.00 dB
// 49: +24.75 dB
// 50: +25.50 dB
// 51: +26.25 dB
// 52: +27.00 dB
// 53: +27.75 dB
// 54: +28.50 dB
// 55: +29.25 dB
// 56: +30.00 dB
// 57: +30.75 dB
// 58: +31.50 dB
// 59: +32.25 dB
// 60: +33.00 dB
// 61: +33.75 dB
// 62: +34.50 dB
// 63: +35.25 dB

#ifndef USE_AGC
 #define ANA_GAIN_DEFAULT   32 // +12dB
#endif


#ifdef USE_AGC
 // --- running in +12dB or +12.75dB
 // decrease 3dB when big noise detected
 #define ANA_GAIN_MIN       28 //  +9db
 #define ANA_GAIN_DEFAULT   32 // +12dB
 #define ANA_GAIN_MAX       33 // +12.75dB

 #define AGC_TARGET_THRES   0.5//0.1
 #define AGC_MAX_THRES      0.6//0.2

 #define AGC_ODR            16
 // decr must < 0
 // incr must > 0
 #define FAST_DECR          -204
 #define SLOW_DECR          -10
 #define SLOW_INCR          5
#endif // endif defined(USE_AGC)


#ifdef USE_AMIC
static void _mic_in_channel(void)
{
    //WRITE32(PMU_BASE+0x00000044,0x00000008);
    //PMU->TRIM1 |= PMU_TRIM_1_XVON_VBG_Msk;

    ////////////////////////////////////////////////////////////////////////////////
    uint32_t val;

    //0x5000306C: ANA0CFG              = 0x28100B04
    // |RSV20                          = 0
    // |pu_bst_ch1_o                   = 0
    // |pu_bst_ch0_o                   = 1
    // |RSV21                          = 0
    // |pu_audio_buf_ch0_o             = 1
    // |RSV22                          = 0
    // |RSV23                          = 0
    // |mute_pga_ch0_o                 = 0
    // |RSV24                          = 0
    // |mute_bst_ch1_o                 = 0
    // |mute_bst_ch0_o                 = 0
    // |micbias_en_o                   = 1
    // |bst_sel_ch1_o                  = 0
    // |bst_sel_ch0_o                  = 0
    // |rst_sd_ch1_o                   = 1
    // |rst_sd_ch0_o                   = 0
    // |bias_ref_sel_o                 = 1
    // |bias_out_en1_o                 = 1
    // |RSV25                          = 0
    // |RSV26                          = 0
    // |RSV27                          = 0
    // |vcom_sel_o                     = 4
    val = 0;
    val |= AUDIO_ANA0CFG_PU_BST_CH0_O_Msk;
    val |= AUDIO_ANA0CFG_PU_AUDIO_BUF_CH0_O_Msk;
    val |= AUDIO_ANA0CFG_MICBIAS_EN_O_Msk;
    val |= AUDIO_ANA0CFG_RST_SD_CH1_O_Msk;
    val |= AUDIO_ANA0CFG_BIAS_REF_SEL_O_Msk;
    val |= AUDIO_ANA0CFG_BIAS_OUT_EN1_O_Msk;


    //--- boost amp
    //0: +20dB
    //1: +12dB
    //oterhs: 0dB
    val |= AUDIO_ANA0CFG_BST_SEL_CH0_O_Msk & (0 << AUDIO_ANA0CFG_BST_SEL_CH0_O_Pos);
    val |= AUDIO_ANA0CFG_BST_SEL_CH1_O_Msk & (0 << AUDIO_ANA0CFG_BST_SEL_CH1_O_Pos);
    //val |= AUDIO_ANA0CFG_BST_SEL_CH0_O_Msk & (1 << AUDIO_ANA0CFG_BST_SEL_CH0_O_Pos);
    //val |= AUDIO_ANA0CFG_BST_SEL_CH1_O_Msk & (1 << AUDIO_ANA0CFG_BST_SEL_CH1_O_Pos);

    val |= AUDIO_ANA0CFG_VCOM_SEL_O_Msk & (4 << AUDIO_ANA0CFG_VCOM_SEL_O_Pos);
    AUD->ANA0CFG = val;

    //0x50003070: ANA1CFG              = 0x8624333
    // |analog_testpad_en_o            = 1
    // |RSV28                          = 0
    // |RSV29                          = 0
    // |test_sd_ch1_o                  = 6
    // |test_sd_ch0_o                  = 1
    // |RSV30                          = 0
    // |en_clk_adc_ch1_o               = 0
    // |en_clk_adc_ch0_o               = 1
    // |RSV31                          = 0
    // |sd_adc_sel_ch1_o               = 0
    // |sd_adc_sel_ch0_o               = 0
    // |iref_trim_o                    = 3
    // |en_osc80k_o                    = 0
    // |RSV32                          = 0
    // |en_sd_ch1_o                    = 1
    // |en_sd_ch0_o                    = 1
    // |RSV33                          = 0
    // |RSV34                          = 0
    // |pu_pga_ch0_o                   = 1
    // |pu_bg_o                        = 1
    val = 0;
    
    //val |= AUDIO_ANA1CFG_ANALOG_TESTPAD_EN_O_Msk;
    //val |= AUDIO_ANA1CFG_TEST_SD_CH1_O_Msk & (6 << AUDIO_ANA1CFG_TEST_SD_CH1_O_Pos);
    //val |= AUDIO_ANA1CFG_TEST_SD_CH0_O_Msk & (1 << AUDIO_ANA1CFG_TEST_SD_CH0_O_Pos);
    // bugfixed-2021.09.24: analog mic conflict with I2S1
    // begin
    val &= ~AUDIO_ANA1CFG_ANALOG_TESTPAD_EN_O_Msk;
    // end

    val |= AUDIO_ANA1CFG_EN_CLK_ADC_CH0_O_Msk;
    val |= AUDIO_ANA1CFG_IREF_TRIM_O_Msk & (3 << AUDIO_ANA1CFG_IREF_TRIM_O_Pos);
    val |= AUDIO_ANA1CFG_EN_SD_CH1_O_Msk;
    val |= AUDIO_ANA1CFG_EN_SD_CH0_O_Msk;
    val |= AUDIO_ANA1CFG_PU_PGA_CH0_O_Msk;
    val |= AUDIO_ANA1CFG_PU_BG_O_Msk;
    AUD->ANA1CFG = val;

    //0x50003074: ANA2CFG              = 0x18007
    // |ana_res_ctrl_o                 = 1
    // |bias_set_o                     = 2
    // |RSV35                          = 0
    // |RSV36                          = 0
    // |RSV37                          = 0
    // |vbg_trim_o                     = 7
    val = 0;
    val |= AUDIO_ANA2CFG_ANA_RES_CTRL_O_Msk & (1 << AUDIO_ANA2CFG_ANA_RES_CTRL_O_Pos);
    val |= AUDIO_ANA2CFG_BIAS_SET_O_Msk & (2 << AUDIO_ANA2CFG_BIAS_SET_O_Pos);
    val |= AUDIO_ANA2CFG_VBG_TRIM_O_Msk & (7 << AUDIO_ANA2CFG_VBG_TRIM_O_Pos);
    AUD->ANA2CFG = val;

    //0x50003088: ANA7CFG              = 0x3A000000
    // |ch0_agc_gain_force_o           = 0x1D
    // |ch0_agc_gain_default_o         = 0
    // |ch0_agc_default_en_o           = 0
    // |ch0_agc_gain_sel_o             = 0
    // |ch0_agc_en_o                   = 0
    // |ch0_config_slow_incr_o         = 0
    val = 0;
    val |= AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Msk & (ANA_GAIN_DEFAULT << AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Pos);
    AUD->ANA7CFG = val;

    //0x500030D4: ANA19CFG             = 0x00E4
    // |audio_test_sel_o               = 0
    // |vad_test_sel_o                 = 0
    // |vad_pu_vcom_o                  = 0
    // |vad_pu_bst_o                   = 0
    // |vad_mute_o                     = 0
    // |vad_gain_sel_o                 = 0
    // |vad_en_diff_o                  = 0
    // |current_sel_ch2_o              = 0
    // |current_sel_ch1_o              = 0
    // |pu_vcom_o                      = 1
    // |ldo_avdd12_audio_trim_o        = 6
    // |xvon_avdd12_audio_o            = 0
    // |en_audio_o                     = 1
    // |audio_test_i                   = 0
    // |porb_avdd12_audio_i            = 0
    val = 0;
    val |= AUDIO_ANA19CFG_PU_VCOM_O_Msk;
    val |= AUDIO_ANA19CFG_LDO_AVDD12_AUDIO_TRIM_O_Msk & (6 << AUDIO_ANA19CFG_LDO_AVDD12_AUDIO_TRIM_O_Pos);
    val |= AUDIO_ANA19CFG_EN_AUDIO_O_Msk;
    AUD->ANA19CFG = val;
}
#endif

#if defined(USE_AMIC) && defined(USE_AGC)
void _agc_config(void)
{
    ////////////////////////////////////////////////////////
    //
    //  config AGC
    //
    uint32_t val;

    ////////////////////////////////////////////////////////
    val = AUD->ANA3CFG;
    //val &= ~AUDIO_ANA3CFG_CH0_SYSCTL_AGCPEAK_O_Msk;
    val |= AUDIO_ANA3CFG_CH0_SYSCTL_AGCPEAK_O_Msk;

    val &= ~AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Msk;
    val |= AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Msk & (AGC_ODR << AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Pos);

    AUD->ANA3CFG = val;

    ////////////////////////////////////////////////////////
    uint16_t max_thres   = (int)(32768 * AGC_MAX_THRES);
    uint16_t target_thres= (int)(32768 * AGC_TARGET_THRES);
    val = 0;
    val |= AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Msk    & (max_thres    << AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Pos);
    val |= AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Msk & (target_thres << AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Pos);
    AUD->ANA5CFG = val;

    ////////////////////////////////////////////////////////
    val = 0;
    val |= AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Msk & ((SLOW_DECR & 0xFFFF) << AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Pos);
    val |= AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Msk & ((FAST_DECR & 0xFFFF) << AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Pos);
    AUD->ANA6CFG = val;

    ////////////////////////////////////////////////////////
    // when ch0_agc_en_o == 0 or ch0_agc_default_en_o == 1
    // agc_gain = ch0_agc_gain_default_o
    val = AUD->ANA7CFG;

    val &= ~AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Msk;
    val |= AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Msk & (SLOW_INCR << AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Pos);

    val &= ~AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Msk;
    val |= AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Msk & (ANA_GAIN_DEFAULT << AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Pos);

    val &= ~AUDIO_ANA7CFG_CH0_AGC_DEFAULT_EN_O_Msk; // agc_core.gain = agc_en?agc_core.calc:agc_default
    val |= AUDIO_ANA7CFG_CH0_AGC_GAIN_SEL_O_Msk;    // agc_gain from agc_core
    val |= AUDIO_ANA7CFG_CH0_AGC_EN_O_Msk;          // agc_gain = agc_core.calc

    AUD->ANA7CFG = val;

    ////////////////////////////////////////////////////////
    //
    //  config_update vaild when AGC_EN == 1
    //
    val = 0;
    val |= AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Msk  & (ANA_GAIN_MIN     << AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Pos);
    val |= AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Msk & (127              << AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Pos);
    val |= AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Msk  & (ANA_GAIN_MAX     << AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Pos);

    val |= AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Msk;
    AUD->ANA4CFG = val;

    val &= ~AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Msk;
    AUD->ANA4CFG = val;
}
#endif

static void _audio_config(void)
{
    RCC_Peri_Rst(RCC_AUD_RSTN);
    RCC_Peri_Rst(RCC_AUD_PRSTN);

    /*enable audio clock*/
    PMU_Set_Audio_Clock_Cmd(PMU, ENABLE);
    PMU_Set_Audio_Clock_Div_Num(PMU, (6-1));

    RCC_Peri_Rst(RCC_AUD_RSTN);
    RCC_Peri_Rst(RCC_AUD_PRSTN);
    
    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL0, DISABLE);
    AUDIO_Set_Channel_Clock_Divider(AUD, (2-1));

    AUDIO_Channel0_12bit_Pcm_Cmd(AUD, DISABLE);

    /*config filter*/
    //
    //  PreEmphasis : NO
    //  Sinc5d2     : Yes, 1/32
    //  iSincd2     : Yes, 1/2
    //  Halfband    : Yes, 1/2
    //  Highpass    : Yes
    //
    //  fs = 2.048M /32/2/2 = 16KHz
    //
#ifdef USING_DMIC
    AUDIO_Set_Pre_Emphasis_Bypass_Cmd(AUD, ENABLE);
    AUDIO_Set_Sinc5d2_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Halfband_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Highpass_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Channel2_High_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Channel_Transmit_Mode(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_TRANSMIT_RAM_MODE);
    AUDIO_Set_Channel_Input_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_INPUT_FROM_DIGITAL);
    AUDIO_Set_Channel_Edge_Capture_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE);
    AUDIO_Set_Ram_Interrupt_Mask(AUD, AUDIO_CHANNEL0, AUDIO_RAM_FRAME_VLD_INTERRUPT, DISABLE);
    AUDIO_Set_Ram_Interrupt_Mask(AUD, AUDIO_CHANNEL1, AUDIO_RAM_FRAME_VLD_INTERRUPT, DISABLE);
#endif
    
#ifdef USING_AMIC
    // pre-emphasis config for AGC input?
    // what's wrong???
    // this MUST NOT ENABLE
    AUDIO_Set_Analog_Emphasis_Cmd(AUD, DISABLE);

    AUDIO_Set_Pre_Emphasis_Bypass_Cmd(AUD, ENABLE);
    AUDIO_Set_Sinc5d2_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Halfband_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Highpass_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Channel2_High_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Channel_Transmit_Mode(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_TRANSMIT_RAM_MODE);
    AUDIO_Set_Channel_Input_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_INPUT_FROM_ANALOG);
    AUDIO_Set_Channel_Edge_Capture_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE);
    AUDIO_Set_Ram_Interrupt_Mask(AUD, AUDIO_CHANNEL0, AUDIO_RAM_FRAME_VLD_INTERRUPT, DISABLE);
    AUDIO_Set_Ram_Interrupt_Mask(AUD, AUDIO_CHANNEL1, AUDIO_RAM_FRAME_VLD_INTERRUPT, DISABLE);

    /* analog mic set */
    _mic_in_channel();
#ifdef USE_AGC
    _agc_config();
#endif
#endif

#ifdef AUDIO_FROM_PDM0
    AUDIO_Set_Channel0_Select_Pdm(AUD, AUDIO_PDM0);
#endif
#ifdef AUDIO_FROM_PDM1
    AUDIO_Set_Biquad_Select_Channel(AUD,AUDIO_PDM1);
    AUDIO_Set_Channel0_Select_Pdm(AUD, AUDIO_PDM1);
#endif

    //ram config
    AUDIO_Set_RAM_Depth(AUD,AUDIO_CHANNEL0,     AUDIO_FIFO_DEPTH/2-1);
    AUDIO_Set_RAM_Frame_Move(AUD,AUDIO_CHANNEL0,AUDIO_FRAME_SIZE/2-1);
    AUDIO_Set_RAM_Length(AUD,AUDIO_CHANNEL0,    AUDIO_FRAME_SIZE/2-1);
   
    //audio interrupt 
    ECLIC_ClearPendingIRQ(AUDIO_IRQn);
    ECLIC_SetPriorityIRQ(AUDIO_IRQn, 1);
    ECLIC_SetTrigIRQ(AUDIO_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(AUDIO_IRQn);
    //audio interrupt 
    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);
    
    //vld interrupt
    AUDIO_Set_Ram_Interrupt_Mask(AUD,AUDIO_CHANNEL0,AUDIO_RAM_FRAME_VLD_INTERRUPT,DISABLE);

    //audio dma config
    _audio_dma_config();

    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL0,ENABLE);
    AUDIO_Set_Channel_Gain_Configuration(AUD, AUDIO_CHANNEL0, AUDIO_GAIN);
    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL0,DISABLE);
        
    //vad
    //AUD->ANA0CFG=0x0010Af04;
    //AUD->ANA1CFG=0x00000301;
    //AUD->ANA2CFG=0x00010007;  
    //AUD->ANA19CFG=0x00037F04;
    //PMU->PMU_RESV_ADC_REG1=0x54;
    //PMU->PMU_RESV_ADC_REG0=0xb4;

#if VAD_ENABLE
    ECLIC_ClearPendingIRQ(VAD_IRQn);
    ECLIC_SetPriorityIRQ(VAD_IRQn, 1);
    ECLIC_SetTrigIRQ(VAD_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(VAD_IRQn);
    AUDIO_Set_Vad_Interrupt_Mask(AUD,AUDIO_VAD_ACT_INTERRUPT,ENABLE);
    PMU_Set_Ie_Msk(PMU, PMU_VAD_IMSK, ENABLE);
    AUDIO_Set_Bq_B0_Configuration(AUD, 0x95f);
    AUDIO_Set_Bq_B1_Configuration(AUD, 0);
    AUDIO_Set_Bq_A0_Configuration(AUD, 0xed42);
    AUDIO_Set_Bq_B2_Configuration(AUD, 0xe000);
    AUDIO_Set_Bq_A1_Configuration(AUD,0xd41);
#define DEF_STP_THRESHOLD 256  
#define DEF_LTP_THRESHOLD 64 
#define DEF_DEVIATION 256      
#define DEF_STP_WINLEN 2
#define SPT_WIN_SHIFT 1 
#define DEF_LTP_WINLEN 64
#define LPT_WIN_SHIFT 6 
    AUDIO_Set_Short_Term_Power_Threshold(AUD, DEF_STP_THRESHOLD * DEF_STP_THRESHOLD);
    AUDIO_Set_Long_Term_Power_Threshold(AUD, DEF_LTP_THRESHOLD * DEF_LTP_THRESHOLD);
    AUDIO_Set_Deviation_Threshold(AUD, DEF_DEVIATION * DEF_DEVIATION);
    AUDIO_Set_Short_Term_Attack_Window_Length_Threshold(AUD, DEF_STP_WINLEN);
    AUDIO_Set_Short_Term_Attack_Window_Length_Shift(AUD, SPT_WIN_SHIFT);
    AUDIO_Set_Long_Term_Attack_Window_Length_Threshold(AUD, DEF_LTP_WINLEN);
    AUDIO_Set_Long_Term_Attack_Window_Length_Shift(AUD, LPT_WIN_SHIFT);
#endif

    AUDIO_Clear_Ram_Interrupt(AUD, AUDIO_CHANNEL0, AUDIO_RAM_FRAME_VLD_INTERRUPT);

    //
    //  the audio clock from clock24
    //  clock24 from HSE or HSI
    //
    if ((4000000 <= HSE_VALUE) && (HSE_VALUE <= 4096000)) {
        // AUDIO_CLOCK_IN = 4.0MHz or 4.096MHz
        // div2 --> 2MHz
        PMU_Set_Audio_Clock_Div_Num(PMU, (2-1));
        AUDIO_Set_Channel_Clock_Divider(AUD, (1-1));    //audioclock to pdmclk:   2.096M/1 = 2.048M
    } else if (20000000 == HSE_VALUE) {
        PMU_Set_Audio_Clock_Div_Num(PMU, (10-1));
        AUDIO_Set_Channel_Clock_Divider(AUD, (1-1));    //audioclock to pdmclk:   2.000M/1 = 2.000M
    } else {
        // AUDIO_CLOCK_IN = 24.0MHz or 24.576MHz
        // div6 --> 4MHz
        PMU_Set_Audio_Clock_Div_Num(PMU, (6-1));
        AUDIO_Set_Channel_Clock_Divider(AUD, (2-1));    //audioclock to pdmclk:   4.096M/2 = 2.048M
    }
}

void audio_start(void)
{
    AUDIO_Set_Ram_Interrupt_Mask(AUD,AUDIO_CHANNEL0,AUDIO_RAM_FRAME_VLD_INTERRUPT,ENABLE);
#ifdef AUDIO_FROM_PDM0
    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL0,ENABLE);
#endif
#ifdef AUDIO_FROM_PDM1
    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL0,ENABLE);
    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL1,ENABLE);
#endif
}

void audio_stop(void)
{
    AUDIO_Set_Ram_Interrupt_Mask(AUD,AUDIO_CHANNEL0,AUDIO_RAM_FRAME_VLD_INTERRUPT,DISABLE);
#ifdef AUDIO_FROM_PDM0
    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL0,DISABLE);
#endif
#ifdef AUDIO_FROM_PDM1
    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL0,DISABLE);
    AUDIO_Set_Channel_Transmit_Cmd(AUD,AUDIO_CHANNEL1,DISABLE);
#endif   
}

void audio_open(void)
{
    _gpio_config();
    _audio_config();
}

#endif // end of #ifdef AUDIO_CHANNEL0

