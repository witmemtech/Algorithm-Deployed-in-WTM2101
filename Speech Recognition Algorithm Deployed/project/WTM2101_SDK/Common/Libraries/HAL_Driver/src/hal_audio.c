/**
* @file    hal_audio.c
* @brief   The Source Codes for the hal_audio Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

/** Includes */
#include "hal_audio.h"

#define HAL_AUDIO_INSTANCE_NUMBER 3
static Audio_InitTypeDef hal_audio_instance[HAL_AUDIO_INSTANCE_NUMBER];

Audio_InitTypeDef* hal_audio_instance_get(Hal_Audio_Instance_Typedef number)
{
    if(number < HAL_AUDIO_INSTANCE1 || number > HAL_AUDIO_INSTANCE3)
        return NULL;

    return (&hal_audio_instance[number]);
}

__attribute__((weak)) void VAD_IRQHandler(void)
{
    /*the vad interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    AUDIO_Reset_Vad(AUD);
}

__attribute__((weak)) void DMA_IRQHandler(void)
{
    /*the dma interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    /*for example, you are using the HAL_AUDIO_INSTANCE1 instance*/
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    if(DMA_Get_Transfer_Interrupt_Status(DMA) & hal_audio_instance->dma_channel)
    {
        DMA_Clear_Transfer_Interrupt_Cmd(DMA,hal_audio_instance->dma_channel);
        /*data handle*/
        hal_audio_instance->Data_handle_info.dma_receive_handler(hal_audio_instance);
    }
}

__attribute__((weak)) void AUDIO_IRQHandler(void)
{
    /*the audio interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/

    /*for example, you are using the HAL_AUDIO_INSTANCE1 instance*/
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    /*if the audio ram buffer is used,as below*/
    if(AUDIO_Get_Ram_Interrupt_Status(hal_audio_instance->instance,hal_audio_instance->channel.ChannelNumber) & HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT)
    {
        /*the interrupt is clear*/
        AUDIO_Clear_Ram_Interrupt(hal_audio_instance->instance,hal_audio_instance->channel.ChannelNumber,HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT);
        /*data handle*/
        hal_audio_instance->Data_handle_info.audio_receive_handler(hal_audio_instance);
    }

    /*if the audio fifo buffer is used,as below*/
    if (AUDIO_Get_FIFO_Interrupt_Status(hal_audio_instance->instance, hal_audio_instance->channel.ChannelNumber) & HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT)
    {
        /*data handle*/
        hal_audio_instance->Data_handle_info.audio_receive_handler(hal_audio_instance);
    }
}

static void dma_receive_handler(struct Audio_InitTypeDef *audio_instance)
{
    if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_RAM_MODE)
       audio_instance->dma_finish_flag = 1;
}

static void audio_receive_handler(struct Audio_InitTypeDef *audio_instance)
{
    if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_RAM_MODE)
    {
        /*ram mode*/
        audio_instance->audio_cache.cache.sram.sram_data_flag = 1;
    }
    else if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_FIFO_MODE)
    {
        /*fifo mode*/
        uint8_t temp[16] = {0};
        uint32_t _ = 0;

        for(int i = 0;i < 4;i++)
        {
            if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL0_NUMBER)
                _ =  audio_instance->instance->FF0DATA;
            else if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL1_NUMBER)
                _ =  audio_instance->instance->FF1DATA;
            else if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL2_NUMBER)
                _ =  audio_instance->instance->FF2DATA;
            temp[0 + i * 4] = (_ >> 0);
            temp[1 + i * 4] = (_ >> 8);
            temp[2 + i * 4] = (_ >> 16);
            temp[3 + i * 4] = (_ >> 24);
        }
        /*the data is push to ring buffer*/
        Ring_Cache_Push_String(&(audio_instance->audio_cache.cache.ring),temp,16);
    }
}

static int HAL_Audio_AnalogInit(Audio_InitTypeDef *audio_instance)
{
    uint32_t val = 0;

    /* 0x5000306C: ANA0CFG              = 0x28100B04
    * |RSV20                          = 0
    * |pu_bst_ch1_o                   = 0
    * |pu_bst_ch0_o                   = 1
    * |RSV21                          = 0
    * |pu_audio_buf_ch0_o             = 1
    * |RSV22                          = 0
    * |RSV23                          = 0
    * |mute_pga_ch0_o                 = 0
    * |RSV24                          = 0
    * |mute_bst_ch1_o                 = 0
    * |mute_bst_ch0_o                 = 0
    * |micbias_en_o                   = 1
    * |bst_sel_ch1_o                  = 0
    * |bst_sel_ch0_o                  = 0
    * |rst_sd_ch1_o                   = 1
    * |rst_sd_ch0_o                   = 0
    * |bias_ref_sel_o                 = 1
    * |bias_out_en1_o                 = 1
    * |RSV25                          = 0
    * |RSV26                          = 0
    * |RSV27                          = 0
    * |vcom_sel_o                     = 4
    */
    val = 0;
    if (audio_instance->InputType == HAL_AUDIO_MIC_INPUT_AMIC) {
        val |=  AUDIO_ANA0CFG_PU_BST_CH0_O_Msk;
        val &= ~AUDIO_ANA0CFG_PU_BST_CH1_O_Msk;
        val &= ~AUDIO_ANA0CFG_RST_SD_CH0_O_Msk;
        val |=  AUDIO_ANA0CFG_RST_SD_CH1_O_Msk;
        val |=  AUDIO_ANA0CFG_PU_AUDIO_BUF_CH0_O_Msk;
        val |=  AUDIO_ANA0CFG_MICBIAS_EN_O_Msk;
        val |=  AUDIO_ANA0CFG_BIAS_REF_SEL_O_Msk;
        val |=  AUDIO_ANA0CFG_BIAS_OUT_EN1_O_Msk;

        if (audio_instance->Analog.MicBoostGain == HAL_AUDIO_ANALOG_MIC_BOOST_20DB) {
            val |= AUDIO_ANA0CFG_BST_SEL_CH0_O_Msk & (0 << AUDIO_ANA0CFG_BST_SEL_CH0_O_Pos);
        } else if (audio_instance->Analog.MicBoostGain == HAL_AUDIO_ANALOG_MIC_BOOST_12DB) {
            val |= AUDIO_ANA0CFG_BST_SEL_CH0_O_Msk & (1 << AUDIO_ANA0CFG_BST_SEL_CH0_O_Pos);
        } else if (audio_instance->Analog.MicBoostGain == HAL_AUDIO_ANALOG_MIC_BOOST_0DB) {
            val |= AUDIO_ANA0CFG_BST_SEL_CH0_O_Msk & (2 << AUDIO_ANA0CFG_BST_SEL_CH0_O_Pos);
        }

    } else if (audio_instance->InputType == HAL_AUDIO_MIC_INPUT_LINEIN) {
        val &= ~AUDIO_ANA0CFG_PU_BST_CH0_O_Msk;
        val |=  AUDIO_ANA0CFG_PU_BST_CH1_O_Msk;

        val |=  AUDIO_ANA0CFG_PU_AUDIO_BUF_CH0_O_Msk;
        val |=  AUDIO_ANA0CFG_MICBIAS_EN_O_Msk;
        val |=  AUDIO_ANA0CFG_BIAS_REF_SEL_O_Msk;
        val |=  AUDIO_ANA0CFG_BIAS_OUT_EN1_O_Msk;

        val |= AUDIO_ANA0CFG_BST_SEL_CH1_O_Msk & (2 << AUDIO_ANA0CFG_BST_SEL_CH1_O_Pos);

        val |= AUDIO_ANA0CFG_BST_SEL_CH1_O_Msk & (audio_instance->Analog.LinBoostGain << AUDIO_ANA0CFG_BST_SEL_CH1_O_Pos);
    }

    val |= AUDIO_ANA0CFG_VCOM_SEL_O_Msk & (4 << AUDIO_ANA0CFG_VCOM_SEL_O_Pos);

    audio_instance->instance->ANA0CFG = val;

    /*0x50003070: ANA1CFG              = 0x4313
    * |analog_testpad_en_o            = 1
    * |RSV28                          = 0
    * |RSV29                          = 0
    * |test_sd_ch1_o                  = 6
    * |test_sd_ch0_o                  = 1
    * |RSV30                          = 0
    * |en_clk_adc_ch1_o               = 0
    * |en_clk_adc_ch0_o               = 1
    * |RSV31                          = 0
    * |sd_adc_sel_ch1_o               = 0
    * |sd_adc_sel_ch0_o               = 0
    * |iref_trim_o                    = 3
    * |en_osc80k_o                    = 0
    * |RSV32                          = 0
    * |en_sd_ch1_o                    = 1
    * |en_sd_ch0_o                    = 1
    * |RSV33                          = 0
    * |RSV34                          = 0
    * |pu_pga_ch0_o                   = 1
    * |pu_bg_o                        = 1
    */
    val = 0;

    /*val |= AUDIO_ANA1CFG_ANALOG_TESTPAD_EN_O_Msk;
    * val |= AUDIO_ANA1CFG_TEST_SD_CH1_O_Msk & (6 << AUDIO_ANA1CFG_TEST_SD_CH1_O_Pos);
    * val |= AUDIO_ANA1CFG_TEST_SD_CH0_O_Msk & (1 << AUDIO_ANA1CFG_TEST_SD_CH0_O_Pos);
    * bugfixed-2021.09.24: analog mic conflict with I2S1
    */
    val &= ~AUDIO_ANA1CFG_ANALOG_TESTPAD_EN_O_Msk;

    val |= AUDIO_ANA1CFG_IREF_TRIM_O_Msk & (3 << AUDIO_ANA1CFG_IREF_TRIM_O_Pos);

    if (audio_instance->InputType == HAL_AUDIO_MIC_INPUT_AMIC) {
        val |= AUDIO_ANA1CFG_EN_CLK_ADC_CH0_O_Msk;  /* enable ADC0 clock */
        val |= AUDIO_ANA1CFG_EN_SD_CH0_O_Msk;       /* enable sigmadelta0 */
        val |= AUDIO_ANA1CFG_PU_PGA_CH0_O_Msk;      /* enable PGA */
    } else if (audio_instance->InputType == HAL_AUDIO_MIC_INPUT_LINEIN) {
        val |= AUDIO_ANA1CFG_EN_CLK_ADC_CH1_O_Msk;  /* enable ADC1 clock */
        val |= AUDIO_ANA1CFG_EN_SD_CH1_O_Msk;       /* enable sigmadelta1 */
    }

    val |= AUDIO_ANA1CFG_PU_BG_O_Msk;
    audio_instance->instance->ANA1CFG = val;

    /*0x50003074: ANA2CFG             = 0x10007
    * |ana_res_ctrl_o                 = 1
    * |bias_set_o                     = 2
    * |RSV35                          = 0
    * |RSV36                          = 0
    * |RSV37                          = 0
    * |vbg_trim_o                     = 7
    */
    val = 0;
    val |= AUDIO_ANA2CFG_ANA_RES_CTRL_O_Msk & (1 << AUDIO_ANA2CFG_ANA_RES_CTRL_O_Pos);
    val |= AUDIO_ANA2CFG_VBG_TRIM_O_Msk & (7 << AUDIO_ANA2CFG_VBG_TRIM_O_Pos);
    audio_instance->instance->ANA2CFG = val;


    if (audio_instance->InputType == HAL_AUDIO_MIC_INPUT_LINEIN) {
        /*0x500030B0: ANA17CFG             = 0x20000000
        * |RSV72                          = 0x10
        * |RSV73                          = 0
        * |RSV74                          = 0
        * |RSV75                          = 0
        * |RSV76                          = 0
        * |RSV77                          = 0
        */
        audio_instance->instance->ANA17CFG = 0x20000000;

        /*0x5000309C: ANA12CFG             = 0x20000000
        * |RSV52                          = 0x10
        * |RSV53                          = 0
        * |RSV54                          = 0
        * |RSV55                          = 0
        * |RSV56                          = 0
        * |RSV57                          = 0
        */
        audio_instance->instance->ANA12CFG = 0x20000000;
    }


    if ((audio_instance->Analog.AGC_Enable == ENABLE) && (audio_instance->InputType == HAL_AUDIO_MIC_INPUT_AMIC)) {
        /*0x50003088: ANA7CFG              = 0x3A000000
        * |ch0_agc_gain_force_o           = 0x1D
        * |ch0_agc_gain_default_o         = 0
        * |ch0_agc_default_en_o           = 0
        * |ch0_agc_gain_sel_o             = 0
        * |ch0_agc_en_o                   = 0
        * |ch0_config_slow_incr_o         = 0
        *

        * when ch0_agc_en_o == 0 or ch0_agc_default_en_o == 1
        * agc_gain = ch0_agc_gain_default_o
        *
        *  when agc_gain_sel == 1:
        *      if !agc_en || agc_default_en:
        *          pga_gain = agc_gain_default
        *      else
        *          pga_gain = agc_core.calculated
        *  when agc_gain_sel == 0:
        *      pga_gain = agc_gain_force
        */
        val = 0;

        val |= AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Msk &
            (audio_instance->Analog.PGAGainDefault << AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Pos);

        audio_instance->instance->ANA7CFG = val;
    }


    /*0x500030D4: ANA19CFG            = 0x0085
    * |audio_test_sel_o               = 0
    * |vad_test_sel_o                 = 0
    * |vad_pu_vcom_o                  = 0
    * |vad_pu_bst_o                   = 0
    * |vad_mute_o                     = 0
    * |vad_gain_sel_o                 = 0
    * |vad_en_diff_o                  = 0
    * |current_sel_ch2_o              = 0
    * |current_sel_ch1_o              = 0
    * |pu_vcom_o                      = 1
    * |ldo_avdd12_audio_trim_o        = 0
    * |xvon_avdd12_audio_o            = 0
    * |en_audio_o                     = 1
    * |audio_test_i                   = 0
    * |porb_avdd12_audio_i            = 0
    */
    val = 0;
    val |= AUDIO_ANA19CFG_PU_VCOM_O_Msk;
    val |= AUDIO_ANA19CFG_EN_AUDIO_O_Msk;
    audio_instance->instance->ANA19CFG = val;

    return 1;
}

static int HAL_Audio_AGCInit(Audio_InitTypeDef *audio_instance)
{
    uint32_t val;
    uint32_t tmp;

    val = audio_instance->instance->ANA3CFG;
    val &= ~AUDIO_ANA3CFG_CH0_SYSCTL_AGCPEAK_O_Msk;
    val |= AUDIO_ANA3CFG_CH0_SYSCTL_AGCPEAK_O_Msk;

    val &= ~AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Msk;
    val |= AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Msk &
        (audio_instance->Analog.AGCOverSampling << AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Pos);

    audio_instance->instance->ANA3CFG = val;

    val = 0;

    tmp = audio_instance->Analog.AGCMaximalThreshold & 0xFFFF;
    tmp <<= AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Pos;
    tmp &= AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Msk;
    val |= tmp;

    tmp = audio_instance->Analog.AGCTargetThreshold & 0xFFFF;
    tmp <<= AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Pos;
    tmp &= AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Msk;
    val |= tmp;

    audio_instance->instance->ANA5CFG = val;

    val = 0;

    tmp = audio_instance->Analog.AGCLongTermAttack & 0xFFFF;
    tmp <<= AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Pos;
    tmp &= AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Msk;
    val |= tmp;

    tmp = audio_instance->Analog.AGCShortTermAttack & 0xFFFF;
    tmp <<= AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Pos;
    tmp &= AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Msk;
    val |= tmp;

    audio_instance->instance->ANA6CFG = val;

    val = audio_instance->instance->ANA7CFG;

    tmp = audio_instance->Analog.AGCLongTermRelease & 0xFFFF;
    tmp <<= AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Pos;
    tmp &= AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Msk;
    val &= ~AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Msk;
    val |= tmp;

    tmp = audio_instance->Analog.PGAGainDefault & 0xFFFF;
    tmp <<= AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Pos;
    tmp &= AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Msk;
    val &= ~AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Msk;
    val |= tmp;

    val &= ~AUDIO_ANA7CFG_CH0_AGC_DEFAULT_EN_O_Msk; /* gain = ch0_agc_gain_default when stop */
    val |= AUDIO_ANA7CFG_CH0_AGC_GAIN_SEL_O_Msk;    /* agc_gain from agc_core */
    val |= AUDIO_ANA7CFG_CH0_AGC_EN_O_Msk;          /* agc_gain = agc_core.calc */

    audio_instance->instance->ANA7CFG = val;

    val = 0;

    tmp = audio_instance->Analog.PGAGainMinmal;
    tmp <<= AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Pos;
    tmp &= AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Msk;
    val |= tmp;

    tmp = audio_instance->Analog.PGAGainDefault;
    tmp <<= AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Pos;
    tmp &= AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Msk;
    val |= tmp;

    tmp = audio_instance->Analog.PGAGainMaximal;
    tmp <<= AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Pos;
    tmp &= AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Msk;
    val |= tmp;

    /* cross clock domain transfer */
    val |= AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Msk;
    audio_instance->instance->ANA4CFG = val;

    val &= ~AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Msk;
    audio_instance->instance->ANA4CFG = val;

    return 1;
}

int hal_audio_init(Audio_InitTypeDef *audio_instance,Audio_Mic_Input_TypeDef type)
{
    if(audio_instance == NULL)
        return -1;
    if(type < HAL_AUDIO_MIC_INPUT_AMIC || type > HAL_AUDIO_MIC_INPUT_LINEIN)
        return -2;

    /*Implement the constructor according to the passed parameters*/
    audio_instance->enable = DISABLE;
    audio_instance->instance = AUD;
    audio_instance->audio_rst = ENABLE;
    audio_instance->prescale = 6;
    if(type == HAL_AUDIO_MIC_INPUT_LINEIN)
        audio_instance->divider = 2;
    else
        audio_instance->divider = 4;

    audio_instance->InputType = type;
    {
        if(audio_instance->InputType == HAL_AUDIO_MIC_INPUT_DMIC)
            audio_instance->Pdm.enable = ENABLE;
        else
            audio_instance->Pdm.enable = DISABLE;
        audio_instance->Pdm.PdmNumber = HAL_AUDIO_CONNECT_PDM0;
        audio_instance->Pdm.Pdm_Clk_Io = GPIO_PIN_4;
        audio_instance->Pdm.Pdm_Clk_IO_AF = GPIO_AF4_PDM0;
        audio_instance->Pdm.Pdm_Data_Io = GPIO_PIN_5;
        audio_instance->Pdm.Pdm_Data_Io_AF = GPIO_AF5_PDM0;
    }

    if(audio_instance->InputType == HAL_AUDIO_MIC_INPUT_LINEIN)
        audio_instance->channel.ChannelNumber = HAL_AUDIO_CHANNEL2_NUMBER;
    else
        audio_instance->channel.ChannelNumber = HAL_AUDIO_CHANNEL0_NUMBER;
    audio_instance->channel.ChannelWidth = HAL_AUDIO_CHANNEL_WIDTH_16BITS;
    if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL0_NUMBER)
      audio_instance->channel.BufferMode = HAL_AUDIO_BUFFER_RAM_MODE;
    else
        audio_instance->channel.BufferMode = HAL_AUDIO_BUFFER_FIFO_MODE;
    if(audio_instance->InputType == HAL_AUDIO_MIC_INPUT_DMIC)
        audio_instance->channel.Source = HAL_AUDIO_BUFFER_DATE_FROM_DIGITAL;
    else
        audio_instance->channel.Source = HAL_AUDIO_BUFFER_DATE_FROM_ANALOG;
    audio_instance->channel.ChannelGain = 12;
    audio_instance->channel.Clk_Edge = HAL_AUDIO_CLK_EDGE_CAPTURE_RISE;

    if(audio_instance->InputType != HAL_AUDIO_MIC_INPUT_DMIC)
        audio_instance->channel.Filter.FuncAnalogPreEmphasis = ENABLE;
    else
        audio_instance->channel.Filter.FuncAnalogPreEmphasis = DISABLE;
    audio_instance->channel.Filter.FuncSinc5D2 = ENABLE;
    if(audio_instance->InputType == HAL_AUDIO_MIC_INPUT_LINEIN)
        audio_instance->channel.Filter.FuncHalfBandD2 = ENABLE;
    else
        audio_instance->channel.Filter.FuncHalfBandD2 = DISABLE;
    audio_instance->channel.Filter.FuncHighPass = ENABLE;
    audio_instance->channel.Filter.FuncPreEmphasis = DISABLE;

    audio_instance->channel.Buffer_Ram_Depth = 480;
    audio_instance->channel.Buffer_Ram_Frame_Move = 240;
    audio_instance->channel.Buffer_Ram_Length = 240;

    {
        audio_instance->Analog.MicBoostGain = HAL_AUDIO_ANALOG_MIC_BOOST_20DB;
        audio_instance->Analog.LinBoostGain = HAL_AUDIO_ANALOG_LIN_BOOST_18DB;

        audio_instance->Analog.PGAGainDefault = 15;
        audio_instance->Analog.PGAGainMinmal = 2;
        audio_instance->Analog.PGAGainMaximal = 20;

        audio_instance->Analog.AGC_Enable = ENABLE;
        audio_instance->Analog.AGCOverSampling = 16;
        audio_instance->Analog.AGCTargetThreshold = (int)(32768 * 0.1);
        audio_instance->Analog.AGCMaximalThreshold =  (int)(32768 * 0.2);
        audio_instance->Analog.AGCShortTermAttack = -204;
        audio_instance->Analog.AGCLongTermAttack = -10;
        audio_instance->Analog.AGCLongTermRelease = 5;
    }

    audio_instance->interrupt.enable = ENABLE;
    if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_RAM_MODE)
        audio_instance->interrupt.type = HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT;
    else
        audio_instance->interrupt.type = HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT;

    {
        if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_RAM_MODE)
            audio_instance->dma_enable = ENABLE;
        else
            audio_instance->dma_enable = DISABLE;
        audio_instance->dma_channel = DMA_CHANNEL0;
        audio_instance->dma_finish_flag = 0;

        audio_instance->dma.llp_src_en = DISABLE;
        audio_instance->dma.llp_dst_en = DISABLE;
        audio_instance->dma.reload_src_en = DISABLE;
        audio_instance->dma.reload_dst_en = DISABLE;
        audio_instance->dma.direction = MEM_TO_MEM_FLOW_CTOL_DMA;
        audio_instance->dma.src_msize = DMA_MSIZE8;
        audio_instance->dma.dst_msize = DMA_MSIZE8;
        audio_instance->dma.src_addr_type = DMA_ADDRESS_NO_CHANGE;
        audio_instance->dma.dst_addr_type = DMA_ADDRESS_INCREASE;
        audio_instance->dma.src_width = DMA_WIDTH32;
        audio_instance->dma.dst_width = DMA_WIDTH16;
        if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL0_NUMBER)
        {
            audio_instance->dma.src_per = DMA_AUDIO_CH0_REQ;
            audio_instance->dma.dst_per = DMA_AUDIO_CH0_REQ;
        }
        else if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL1_NUMBER)
        {
            audio_instance->dma.src_per = DMA_UART0_TX_REQ_OR_AUDIO_CH1;
            audio_instance->dma.dst_per = DMA_UART0_TX_REQ_OR_AUDIO_CH1;
        }
        else if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL2_NUMBER)
        {
            audio_instance->dma.src_per = DMA_UART0_RX_REQ_OR_AUDIO_CH2;
            audio_instance->dma.dst_per = DMA_UART0_RX_REQ_OR_AUDIO_CH2;
        }
        audio_instance->dma.fifo_mode_en = DISABLE;
        audio_instance->dma.max_abrst = 0;
        audio_instance->dma.src_handshaking_type = DMA_HW_HANDSHAKE;
        audio_instance->dma.dst_handshaking_type = DMA_HW_HANDSHAKE;
        audio_instance->dma.chanel_priority = DMA_PRIORITY0;
        audio_instance->dma.int_en = ENABLE;
    }

    {
        audio_instance->Data_handle_info.dma_receive_handler = dma_receive_handler;
        audio_instance->Data_handle_info.audio_receive_handler = audio_receive_handler;
    }
    audio_instance->vad_flag = DISABLE;

    return 1;
}

int hal_audio_open(Audio_InitTypeDef *audio_instance)
{
    if(audio_instance == NULL)
        return -1;
    if(audio_instance->enable == ENABLE)
        return -2;

    /*the audio data cache is malloc*/
    if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_FIFO_MODE)
    {
        /*if the ring buffer is used,the data cahche size is twice*/
        if(Ring_Cache_Init(&(audio_instance->audio_cache.cache.ring),audio_instance->channel.Buffer_Ram_Length * 4 * 2) <= 0)
            return -3;
    }
    else if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_RAM_MODE)
    {
        /*if the sram buffer is used,the data cahche size is same*/
        audio_instance->audio_cache.cache.sram.sram_data_flag = 0;
        audio_instance->audio_cache.cache.sram.sram_data = (uint8_t *)HAL_AUDIO_MALLOC(audio_instance->channel.Buffer_Ram_Length * 4);
        if(!audio_instance->audio_cache.cache.sram.sram_data)
            return -3;
    }

    /*the audio clock was enabled and audio module was reset*/
    RCC_CLK_EN_Ctl(RCC_AUD_CLKEN, ENABLE);
    RCC_CLK_EN_Ctl(RCC_AUD_PCLKEN, ENABLE);
    PMU_Set_Audio_Clock_Cmd(PMU, ENABLE);
    if(audio_instance->audio_rst == ENABLE)
    {
        RCC_Peri_Rst(RCC_AUD_RSTN);
        RCC_Peri_Rst(RCC_AUD_PRSTN);
    }

    /*configurate the audio clock prescale*/
    PMU_Set_Audio_Clock_Div_Num(PMU, audio_instance->prescale - 1);

    /*configurate the audio clock divider*/
    if(audio_instance->channel.ChannelWidth == HAL_AUDIO_CHANNEL_WIDTH_12BITS)
        AUDIO_Set_Channel_Clock_Divider(audio_instance->instance,0);
    else
        AUDIO_Set_Channel_Clock_Divider(audio_instance->instance,audio_instance->divider - 1);

    /*the gpio was configurated, if it is dmic*/
    if((audio_instance->Pdm.enable == ENABLE) && (audio_instance->InputType == HAL_AUDIO_MIC_INPUT_DMIC))
    {
        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.Pin          = audio_instance->Pdm.Pdm_Clk_Io;
        GPIO_InitStructure.Mode         = GPIO_MODE_OUT;
        GPIO_InitStructure.Alternate    = audio_instance->Pdm.Pdm_Clk_IO_AF;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.Pin          = audio_instance->Pdm.Pdm_Data_Io;
        GPIO_InitStructure.Mode         = GPIO_MODE_IN;
        GPIO_InitStructure.Alternate    = audio_instance->Pdm.Pdm_Data_Io_AF;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }

    AUDIO_Set_Channel_Transmit_Cmd(audio_instance->instance,audio_instance->channel.ChannelNumber,DISABLE);
    /*the channel0 data width was configurated*/
    if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL0_NUMBER)
    {
        if(audio_instance->channel.ChannelWidth == HAL_AUDIO_CHANNEL_WIDTH_12BITS)
            AUDIO_Channel0_12bit_Pcm_Cmd(audio_instance->instance, ENABLE);
        else
            AUDIO_Channel0_12bit_Pcm_Cmd(audio_instance->instance, DISABLE);
    }

    /*the channel filter was configurated*/
    if(audio_instance->channel.Filter.FuncAnalogPreEmphasis == DISABLE)
        AUDIO_Set_Analog_Emphasis_Cmd(audio_instance->instance, DISABLE);
    else
        AUDIO_Set_Analog_Emphasis_Cmd(audio_instance->instance, ENABLE);

    if(audio_instance->channel.Filter.FuncPreEmphasis == DISABLE)
        AUDIO_Set_Pre_Emphasis_Bypass_Cmd(audio_instance->instance, ENABLE);
    else
        AUDIO_Set_Pre_Emphasis_Bypass_Cmd(audio_instance->instance, DISABLE);

    if(audio_instance->channel.Filter.FuncSinc5D2 == DISABLE)
        AUDIO_Set_Sinc5d2_Bypass_Cmd(audio_instance->instance, ENABLE);
    else
        AUDIO_Set_Sinc5d2_Bypass_Cmd(audio_instance->instance, DISABLE);

    if(audio_instance->channel.Filter.FuncHalfBandD2 == DISABLE)
        AUDIO_Set_Halfband_Bypass_Cmd(audio_instance->instance, ENABLE);
    else
        AUDIO_Set_Halfband_Bypass_Cmd(audio_instance->instance, DISABLE);

    if(audio_instance->channel.Filter.FuncHighPass == DISABLE)
        AUDIO_Set_Highpass_Bypass_Cmd(audio_instance->instance, ENABLE);
    else
        AUDIO_Set_Highpass_Bypass_Cmd(audio_instance->instance, DISABLE);
    AUDIO_Set_Channel2_High_Bypass_Cmd(AUD, DISABLE);

    /*analog mic was configurated*/
    if(audio_instance->InputType != HAL_AUDIO_MIC_INPUT_DMIC)
    {
        if(audio_instance->channel.ChannelWidth == HAL_AUDIO_CHANNEL_WIDTH_16BITS)
        {
            HAL_Audio_AnalogInit(audio_instance);
        }
        else
        {
            AUD->ANA0CFG  = 0x0010AF04;
            AUD->ANA1CFG  = 0x00000301;
            AUD->ANA2CFG  = 0x00010007;
            AUD->ANA19CFG = 0x00037F87;
        }

       if(audio_instance->InputType == HAL_AUDIO_MIC_INPUT_AMIC)
       {
          if((audio_instance->channel.ChannelWidth == HAL_AUDIO_CHANNEL_WIDTH_16BITS) && (audio_instance->Analog.AGC_Enable == ENABLE))
              HAL_Audio_AGCInit(audio_instance);
       }
    }

    /*the channel was configurated*/
    AUDIO_Set_Channel_Transmit_Mode(audio_instance->instance, audio_instance->channel.ChannelNumber, audio_instance->channel.BufferMode);
    {
        /*this is a hardware bug,cross clock not works,so the gain is updated when the audio channel is enabled*/
        AUDIO_Set_Channel_Transmit_Cmd(audio_instance->instance,audio_instance->channel.ChannelNumber,ENABLE);
        AUDIO_Set_Channel_Gain_Configuration(audio_instance->instance, audio_instance->channel.ChannelNumber, audio_instance->channel.ChannelGain);
        AUDIO_Set_Channel_Transmit_Cmd(audio_instance->instance,audio_instance->channel.ChannelNumber,DISABLE);
    }
    AUDIO_Set_Channel_Edge_Capture_Select(audio_instance->instance, audio_instance->channel.ChannelNumber, audio_instance->channel.Clk_Edge);
    AUDIO_Set_Channel_Input_Select(audio_instance->instance, audio_instance->channel.ChannelNumber, audio_instance->channel.Source);
    if(audio_instance->channel.ChannelWidth == HAL_AUDIO_CHANNEL_WIDTH_12BITS)
        AUDIO_Set_CHANNEL0_PCM_ZEROPADDING(audio_instance->instance,4);

    /*the channel was connected with pdm*/
    if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL0_NUMBER)
        AUDIO_Set_Channel0_Select_Pdm(audio_instance->instance, audio_instance->Pdm.PdmNumber);
    else if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL1_NUMBER)
        AUDIO_Set_Channel1_Select_Pdm(audio_instance->instance, audio_instance->Pdm.PdmNumber);

    /*the ram buffer parameter of audio channel was configurated*/
    if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_RAM_MODE)
    {
        AUDIO_Set_RAM_Depth(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->channel.Buffer_Ram_Depth - 1);
        AUDIO_Set_RAM_Frame_Move(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->channel.Buffer_Ram_Frame_Move - 1);
        AUDIO_Set_RAM_Length(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->channel.Buffer_Ram_Length - 1);
    }

    /*the interrupt of audio was configurated*/
    if(audio_instance->interrupt.enable == ENABLE)
    {
        ECLIC_ClearPendingIRQ(AUDIO_IRQn);
        ECLIC_SetPriorityIRQ(AUDIO_IRQn, 1);
        ECLIC_SetTrigIRQ(AUDIO_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(AUDIO_IRQn);
        if(audio_instance->interrupt.type == HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT)
            AUDIO_Set_Ram_Interrupt_Mask(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->interrupt.type,DISABLE);
        else if(audio_instance->interrupt.type == HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT)
            AUDIO_Set_FIFO_Interrupt_Mask(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->interrupt.type,DISABLE);
    }

    /*the dma of audio was configurated*/
    if(audio_instance->dma_enable == ENABLE)
    {
        if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL1_NUMBER)
        {
            RCC_Config_Dma_Requst0_Reuse(ENABLE);
        }
        else if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL2_NUMBER)
        {
            RCC_Config_Dma_Requst1_Reuse(ENABLE);
        }

        RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);
        DMA_Clear_All_Interrupt_Cmd(DMA);
        DMA_Init(DMA, audio_instance->dma_channel, &(audio_instance->dma));

        if(audio_instance->dma.int_en == ENABLE)
        {
            ECLIC_ClearPendingIRQ(DMA_IRQn);
            ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
            ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
            ECLIC_EnableIRQ(DMA_IRQn);
            DMA_Set_Transfer_Interrupt_Cmd(DMA,audio_instance->dma_channel,ENABLE);
        }
        DMA_Set_Enable_Cmd(DMA, ENABLE);
    }

    if(audio_instance->vad_flag == ENABLE)
    {
        ECLIC_ClearPendingIRQ(VAD_IRQn);
        ECLIC_SetPriorityIRQ(VAD_IRQn, 1);
        ECLIC_SetTrigIRQ(VAD_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(VAD_IRQn);
        AUDIO_Set_Vad_Interrupt_Mask(AUD,AUDIO_VAD_ACT_INTERRUPT,ENABLE);
        PMU_Set_Ie_Msk(PMU, PMU_VAD_IMSK, ENABLE);
        VAD_Config();
    }
    audio_instance->enable = ENABLE;

    return 1;
}

int hal_audio_ctl(Audio_InitTypeDef *audio_instance,int command, ...)
{
    va_list ParamList;
    volatile int value = 0;

    if (audio_instance == NULL)
        return -1;
    va_start(ParamList, command);

    switch(command)
    {
      case HAL_AUDIO_CHANNEL_ENABLE_COMMAND:
      {
          /*the audio channel was enabled or disabled*/
          value = va_arg(ParamList, int);
          if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL1_NUMBER)
          {
              AUDIO_Set_Channel_Transmit_Cmd(audio_instance->instance,HAL_AUDIO_CHANNEL0_NUMBER,value);
          }
          if((audio_instance->Pdm.PdmNumber == HAL_AUDIO_CONNECT_PDM1) && (audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL0_NUMBER))
          {
              AUDIO_Set_Channel_Transmit_Cmd(audio_instance->instance,HAL_AUDIO_CHANNEL1_NUMBER,value);
          }
          AUDIO_Set_Channel_Transmit_Cmd(audio_instance->instance,audio_instance->channel.ChannelNumber,value);
          break;
      }

      case HAL_AUDIO_INTERRUPT_ENABLE_COMMAND:
      {
          /*the audio channel interrupt was enabled or disabled*/
          value = va_arg(ParamList, int);
          if(audio_instance->interrupt.type == HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT)
              AUDIO_Set_Ram_Interrupt_Mask(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->interrupt.type,value);
          else if(audio_instance->interrupt.type == HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT)
              AUDIO_Set_FIFO_Interrupt_Mask(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->interrupt.type,value);
          break;
      }

      case HAL_AUDIO_CHANNEL_DATA_WIDTH16BITS_COMMAND:
      {
          /*the audio channel data width16bits was update*/
          value = va_arg(ParamList, int);
          if(audio_instance->channel.ChannelNumber != HAL_AUDIO_CHANNEL0_NUMBER)
              return -2;
          if(audio_instance->InputType != HAL_AUDIO_MIC_INPUT_AMIC)
              return -2;

          if(value == ENABLE)
          {
              AUDIO_Set_Channel_Clock_Divider(audio_instance->instance,audio_instance->divider - 1);
              AUDIO_Channel0_12bit_Pcm_Cmd(audio_instance->instance, DISABLE);
              AUDIO_Set_CHANNEL0_PCM_ZEROPADDING(audio_instance->instance,0);
              HAL_Audio_AnalogInit(audio_instance);
              if(audio_instance->Analog.AGC_Enable == ENABLE)
                  HAL_Audio_AGCInit(audio_instance);
          }
          else
          {
              AUDIO_Set_Channel_Clock_Divider(audio_instance->instance,0);
              AUDIO_Channel0_12bit_Pcm_Cmd(audio_instance->instance, ENABLE);
              AUDIO_Set_CHANNEL0_PCM_ZEROPADDING(audio_instance->instance,4);
              if(audio_instance->Analog.AGC_Enable == ENABLE)
              {
                  AUD->ANA3CFG = 0;
                  AUD->ANA4CFG = 0;
                  AUD->ANA5CFG = 0;
                  AUD->ANA6CFG = 0;
                  AUD->ANA7CFG = 0;
              }
              AUD->ANA0CFG  = 0x0010AF04;
              AUD->ANA1CFG  = 0x00000301;
              AUD->ANA2CFG  = 0x00010007;
              AUD->ANA19CFG = 0x00037F87;
          }
          break;
      }

      case HAL_AUDIO_CLOCK_SWITCH_COMMAND:
      {
          /*the audio channel clock source was update*/
          value = va_arg(ParamList, int);
          AUDIO_Set_Clock_Switch_Configuration(audio_instance->instance,audio_instance->channel.ChannelNumber,value);
          break;
      }

      case HAL_VAD_INTERRUPT_ENABLE_COMMAND:
      {
          value = va_arg(ParamList, int);
          if(value)
          {
              ECLIC_EnableIRQ(VAD_IRQn);
              AUDIO_Set_Vad_Interrupt_Mask(audio_instance->instance,AUDIO_VAD_ACT_INTERRUPT,ENABLE);
          }
          else
          {
              ECLIC_DisableIRQ(VAD_IRQn);
              AUDIO_Set_Vad_Interrupt_Mask(audio_instance->instance,AUDIO_VAD_ACT_INTERRUPT,DISABLE);
          }
          break;
      }

      default:
        return -10;
    }

    va_end(ParamList);

    return 1;
}

int hal_audio_read(Audio_InitTypeDef *audio_instance,uint8_t *buffer)
{
    if(audio_instance == NULL)
        return -1;

    if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_RAM_MODE)
    {
        if(audio_instance->audio_cache.cache.sram.sram_data_flag)
        {
            /*Copy the audio buffer data to sram with the hal audio instance*/
            audio_instance->audio_cache.cache.sram.sram_data_flag = 0;
            if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL0_NUMBER)
                DMA_Set_Addr(DMA, audio_instance->dma_channel, (uint32_t) & (audio_instance->instance->RAM0DATA), mmap_to_sys((uint32_t )(audio_instance->audio_cache.cache.sram.sram_data)), audio_instance->channel.Buffer_Ram_Length, 0);
            if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL1_NUMBER)
                DMA_Set_Addr(DMA, audio_instance->dma_channel, (uint32_t) & (audio_instance->instance->RAM1DATA), mmap_to_sys((uint32_t )(audio_instance->audio_cache.cache.sram.sram_data)), audio_instance->channel.Buffer_Ram_Length, 0);
            RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);
            DMA_Set_Channel_Enable_Cmd(DMA, audio_instance->dma_channel, ENABLE);
            while (!(audio_instance->dma_finish_flag));
            audio_instance->dma_finish_flag = 0;

          return 1;
        }
    }
    else if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_FIFO_MODE)
    {
        if(audio_instance->audio_cache.cache.ring.current_size >= audio_instance->channel.Buffer_Ram_Length * 4)
        {
            /*Copy the hal audio buffer data to buffer with the hal audio instance*/
            Ring_Cache_Pop(&(audio_instance->audio_cache.cache.ring),buffer,audio_instance->channel.Buffer_Ram_Length * 4);

          return 1;
        }
    }

    return -10;
}

int hal_audio_close(Audio_InitTypeDef *audio_instance)
{
    if(audio_instance == NULL)
        return -1;
    if(audio_instance->enable == DISABLE)
        return -2;

    /*the audio channel interrupt is close*/
    if(audio_instance->interrupt.enable == ENABLE)
    {
        if(audio_instance->interrupt.type == HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT)
            AUDIO_Set_Ram_Interrupt_Mask(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->interrupt.type,DISABLE);
        else if(audio_instance->interrupt.type == HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT)
            AUDIO_Set_FIFO_Interrupt_Mask(audio_instance->instance,audio_instance->channel.ChannelNumber,audio_instance->interrupt.type,DISABLE);
    }

    /*the dma is close*/
    if(audio_instance->dma_enable == ENABLE)
    {
        DMA_Set_Transfer_Interrupt_Cmd(DMA,audio_instance->dma_channel,DISABLE);
        DMA_Set_Channel_Enable_Cmd(DMA, audio_instance->dma_channel, DISABLE);
    }

    /*the gpio is close*/
    if(audio_instance->InputType == HAL_AUDIO_MIC_INPUT_DMIC)
    {
        GPIO_DeInit(GPIOA,audio_instance->Pdm.Pdm_Clk_Io | audio_instance->Pdm.Pdm_Data_Io);
    }

    /*the audio channel is close*/
    AUDIO_Set_Channel_Transmit_Cmd(audio_instance->instance,audio_instance->channel.ChannelNumber,DISABLE);
    if(audio_instance->channel.ChannelNumber == HAL_AUDIO_CHANNEL1_NUMBER)
    {
        AUDIO_Set_Channel_Transmit_Cmd(audio_instance->instance,HAL_AUDIO_CHANNEL0_NUMBER,DISABLE);
    }

    /*the reset audio module*/
    RCC_Peri_Rst(RCC_AUD_RSTN);
    RCC_Peri_Rst(RCC_AUD_PRSTN);

    /*free heap*/
    if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_FIFO_MODE)
    {
        HAL_AUDIO_FREE(audio_instance->audio_cache.cache.ring.data);
    }
    else if(audio_instance->channel.BufferMode == HAL_AUDIO_BUFFER_RAM_MODE)
    {
        HAL_AUDIO_FREE(audio_instance->audio_cache.cache.sram.sram_data);
    }

    /*the hal audio flag is disabled*/
    audio_instance->enable = DISABLE;

    return 1;
}
