/**
  ******************************************************************************
  * @file    audio.c
  * @brief   The Source Codes for the AUDIO Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "audio.h"
#include "pmu.h"

FunctionalState AUDIO_Get_Channel_Transmit_Enabledstatus(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    FunctionalState status = DISABLE;

    if (channel == AUDIO_CHANNEL0)
    {
        if (audio->TRCTRL & AUDIO_TRCTRL_CH0_TR_EN_O_Msk)
        {
            status = ENABLE;
        }
        else
        {
            status = DISABLE;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (audio->TRCTRL & AUDIO_TRCTRL_CH1_TR_EN_O_Msk)
        {
            status = ENABLE;
        }
        else
        {
            status = DISABLE;
        }
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        if (audio->TRCTRL & AUDIO_TRCTRL_CH2_TR_EN_O_Msk)
        {
            status = ENABLE;
        }
        else
        {
            status = DISABLE;
        }
    }

    return status;
}

void AUDIO_Set_Channel_Transmit_Cmd(AUD_TypeDef *audio, uint8_t channel, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        if (newstatus)
        {
            audio->TRCTRL |= AUDIO_TRCTRL_CH0_TR_EN_O_Msk;
        }
        else
        {
            audio->TRCTRL &= ~AUDIO_TRCTRL_CH0_TR_EN_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (newstatus)
        {
            audio->TRCTRL |= AUDIO_TRCTRL_CH1_TR_EN_O_Msk;
        }
        else
        {
            audio->TRCTRL &= ~AUDIO_TRCTRL_CH1_TR_EN_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        if (newstatus)
        {
            audio->TRCTRL |= AUDIO_TRCTRL_CH2_TR_EN_O_Msk;
        }
        else
        {
            audio->TRCTRL &= ~AUDIO_TRCTRL_CH2_TR_EN_O_Msk;
        }
    }
}

uint8_t AUDIO_Get_Channel_Transmit_Mode(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        return ((audio->TRCTRL & AUDIO_TRCTRL_CH0_TR_MOD_SEL_O_Msk) >> AUDIO_TRCTRL_CH0_TR_MOD_SEL_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        return ((audio->TRCTRL & AUDIO_TRCTRL_CH1_TR_MOD_SEL_O_Msk) >> AUDIO_TRCTRL_CH1_TR_MOD_SEL_O_Pos);
    }
}

void AUDIO_Set_Channel_Transmit_Mode(AUD_TypeDef *audio, uint8_t channel, uint8_t mode)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_CHANNEL_TRANSMIT_MODE(mode));

    if (channel == AUDIO_CHANNEL0)
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_CH0_TR_MOD_SEL_O_Msk;
        audio->TRCTRL |= (mode << AUDIO_TRCTRL_CH0_TR_MOD_SEL_O_Pos);

    }
    else if (channel == AUDIO_CHANNEL1)
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_CH1_TR_MOD_SEL_O_Msk;
        audio->TRCTRL |= (mode << AUDIO_TRCTRL_CH1_TR_MOD_SEL_O_Pos);
    }
}

uint8_t AUDIO_Get_Channel_Input_Select(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    uint8_t value = AUDIO_CHANNEL_INPUT_FROM_DIGITAL;

    if (channel == AUDIO_CHANNEL0)
    {
        return ((audio->TRCTRL & AUDIO_TRCTRL_CH0_PDM_SEL_O_Msk) >> AUDIO_TRCTRL_CH0_PDM_SEL_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        return ((audio->TRCTRL & AUDIO_TRCTRL_CH1_PDM_SEL_O_Msk) >> AUDIO_TRCTRL_CH1_PDM_SEL_O_Pos);
    }
}

void AUDIO_Set_Channel_Input_Select(AUD_TypeDef *audio, uint8_t channel, uint8_t select)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_Channel_INPUT_SELECT(select));

    if (channel == AUDIO_CHANNEL0)
    {
        if (select == AUDIO_CHANNEL_INPUT_FROM_DIGITAL)
        {
            audio->TRCTRL &= ~AUDIO_TRCTRL_CH0_PDM_SEL_O_Msk;
        }
        else if (select == AUDIO_CHANNEL_INPUT_FROM_ANALOG)
        {
            audio->TRCTRL |= AUDIO_TRCTRL_CH0_PDM_SEL_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (select == AUDIO_CHANNEL_INPUT_FROM_DIGITAL)
        {
            audio->TRCTRL &= ~AUDIO_TRCTRL_CH1_PDM_SEL_O_Msk;
        }
        else if (select == AUDIO_CHANNEL_INPUT_FROM_ANALOG)
        {
            audio->TRCTRL |= AUDIO_TRCTRL_CH1_PDM_SEL_O_Msk;
        }
    }
}

uint8_t AUDIO_Get_Channel_Clock_Divider(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->TRCTRL & AUDIO_TRCTRL_CH_CLK_DIV_O_Msk) >> AUDIO_TRCTRL_CH_CLK_DIV_O_Pos);
}

void AUDIO_Set_Channel_Clock_Divider(AUD_TypeDef *audio, uint8_t divider)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->TRCTRL &= ~AUDIO_TRCTRL_CH_CLK_DIV_O_Msk;
    for(int i=0;i<100;i++){
        __NOP();
    }
    audio->TRCTRL |= (divider << AUDIO_TRCTRL_CH_CLK_DIV_O_Pos);
}

uint8_t AUDIO_Get_Channel_Edge_Capture_Select(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    uint8_t value = AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE;

    if (channel == AUDIO_CHANNEL0)
    {
        return ((audio->TRCTRL & AUDIO_TRCTRL_CH0_PDM_EDGE_SEL_O_Msk) >> AUDIO_TRCTRL_CH0_PDM_EDGE_SEL_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        return ((audio->TRCTRL & AUDIO_TRCTRL_CH1_PDM_EDGE_SEL_O_Msk) >> AUDIO_TRCTRL_CH1_PDM_EDGE_SEL_O_Pos);
    }
}

void AUDIO_Set_Channel_Edge_Capture_Select(AUD_TypeDef *audio, uint8_t channel, uint8_t edge)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_CHANNEL_CAPTURE_CLOCK_EDGE(edge));

    if (channel == AUDIO_CHANNEL0)
    {
        if (edge == AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE)
        {
            audio->TRCTRL &= ~AUDIO_TRCTRL_CH0_PDM_EDGE_SEL_O_Msk;
        }
        else if (edge == AUDIO_CHANNEL_FALL_CLOCK_EDGE_CAPTURE)
        {
            audio->TRCTRL |= AUDIO_TRCTRL_CH0_PDM_EDGE_SEL_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (edge == AUDIO_CHANNEL_RISE_CLOCK_EDGE_CAPTURE)
        {
            audio->TRCTRL &= ~AUDIO_TRCTRL_CH1_PDM_EDGE_SEL_O_Msk;
        }
        else if (edge == AUDIO_CHANNEL_FALL_CLOCK_EDGE_CAPTURE)
        {
            audio->TRCTRL |= AUDIO_TRCTRL_CH1_PDM_EDGE_SEL_O_Msk;
        }
    }
}

uint8_t AUDIO_Get_Biquad_Select_Channel(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    uint8_t value = AUDIO_CHANNEL0;

    if (audio->TRCTRL & AUDIO_TRCTRL_VAD_CH_SEL_O_Msk)
    {
        value = AUDIO_CHANNEL1;
    }
    else
    {
        value = AUDIO_CHANNEL0;
    }

    return value;
}

void AUDIO_Set_Biquad_Select_Channel(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_VAD_CH_SEL_O_Msk;
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_VAD_CH_SEL_O_Msk;
    }
}

uint8_t AUDIO_Get_Biquad_SelectSource(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    uint8_t value = AUDIO_BIQUAD_SOURCE_SELECT_FROM_SINC_FILTER;

    if (audio->TRCTRL & AUDIO_TRCTRL_BIQUAD_SOURCE_SEL_O_Msk)
    {
        value = AUDIO_BIQUAD_SOURCE_SELECT_FROM_SINC_COMPENSATE;
    }
    else
    {
        value = AUDIO_BIQUAD_SOURCE_SELECT_FROM_SINC_FILTER;
    }

    return value;
}

void AUDIO_Set_Biquad_SelectSource(AUD_TypeDef *audio, uint8_t source)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_BIQUAD_SOURCE_SELECT(source));

    if (source == AUDIO_BIQUAD_SOURCE_SELECT_FROM_SINC_FILTER)
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_BIQUAD_SOURCE_SEL_O_Msk;
    }
    else if (source == AUDIO_BIQUAD_SOURCE_SELECT_FROM_SINC_COMPENSATE)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_BIQUAD_SOURCE_SEL_O_Msk;
    }
}

FunctionalState AUDIO_Get_Sinc5d2_Bypass_EnabledStatus(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    FunctionalState status = DISABLE;

    if (audio->TRCTRL & AUDIO_TRCTRL_SINC5D2_BYPASS_O_Msk)
    {
        status = ENABLE;
    }
    else
    {
        status = DISABLE;
    }

    return status;
}

void AUDIO_Set_Sinc5d2_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    if (newstatus)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_SINC5D2_BYPASS_O_Msk;
    }
    else
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_SINC5D2_BYPASS_O_Msk;
    }
}

FunctionalState AUDIO_Get_Halfband_Bypass_EnabledStatus(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    FunctionalState status = DISABLE;

    if (audio->TRCTRL & AUDIO_TRCTRL_HALFBAND_BYPASS_O_Msk)
    {
        status = ENABLE;
    }
    else
    {
        status = DISABLE;
    }

    return status;
}

void AUDIO_Set_Halfband_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    if (newstatus)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_HALFBAND_BYPASS_O_Msk;
    }
    else
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_HALFBAND_BYPASS_O_Msk;
    }
}

FunctionalState AUDIO_Get_Highpass_Bypass_EnabledStatus(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    FunctionalState status = DISABLE;

    if (audio->TRCTRL & AUDIO_TRCTRL_HIGHPASS_BYPASS_O_Msk)
    {
        status = ENABLE;
    }
    else
    {
        status = DISABLE;
    }

    return status;
}

void AUDIO_Set_Highpass_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    if (newstatus)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_HIGHPASS_BYPASS_O_Msk;
    }
    else
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_HIGHPASS_BYPASS_O_Msk;
    }
}

FunctionalState AUDIO_Get_Biquad_Bypass_EnabledStatus(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    FunctionalState status = DISABLE;

    if (audio->TRCTRL & AUDIO_TRCTRL_BIQUAD_BYPASS_O_Msk)
    {
        status = ENABLE;
    }
    else
    {
        status = DISABLE;
    }

    return status;
}

void AUDIO_Set_Biquad_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    if (newstatus)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_BIQUAD_BYPASS_O_Msk;
    }
    else
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_BIQUAD_BYPASS_O_Msk;
    }
}

FunctionalState AUDIO_Get_Channel2_High_Bypass_EnabledStatus(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    FunctionalState status = DISABLE;

    if (audio->TRCTRL & AUDIO_TRCTRL_CH2_HIGH_BYPASS_O_Msk)
    {
        status = ENABLE;
    }
    else
    {
        status = DISABLE;
    }

    return status;
}

void AUDIO_Set_Channel2_High_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    if (newstatus)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_CH2_HIGH_BYPASS_O_Msk;
    }
    else
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_CH2_HIGH_BYPASS_O_Msk;
    }
}

uint8_t AUDIO_Get_Channel0_Select_Pdm(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    uint8_t value = AUDIO_PDM0;

    if (audio->TRCTRL & AUDIO_TRCTRL_CH0_PDM_CH_CHANGE_O_Msk)
    {
        value = AUDIO_PDM1;
    }
    else
    {
        value = AUDIO_PDM0;
    }

    return value;
}

void AUDIO_Set_Channel0_Select_Pdm(AUD_TypeDef *audio,uint8_t pdm)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_PDM(pdm));

    if (pdm == AUDIO_PDM0)
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_CH0_PDM_CH_CHANGE_O_Msk;
    }
    else if (pdm == AUDIO_PDM1)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_CH0_PDM_CH_CHANGE_O_Msk;
    }
}

uint8_t AUDIO_Get_Channel1_Select_Pdm(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    uint8_t value = AUDIO_PDM0;

    if (audio->TRCTRL & AUDIO_TRCTRL_CH1_PDM_CH_CHANGE_O_Msk)
    {
        value = AUDIO_PDM1;
    }
    else
    {
        value = AUDIO_PDM0;
    }

    return value;
}

void AUDIO_Set_Channel1_Select_Pdm(AUD_TypeDef *audio, uint8_t pdm)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_PDM(pdm));

    if (pdm == AUDIO_PDM0)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_CH1_PDM_CH_CHANGE_O_Msk;
    }
    else if (pdm == AUDIO_PDM1)
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_CH1_PDM_CH_CHANGE_O_Msk;
    }
}

void AUDIO_Reset_Vad(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->TRCTRL |= AUDIO_TRCTRL_VAD_RST_O_Msk;
    audio->TRCTRL &= ~AUDIO_TRCTRL_VAD_RST_O_Msk;
}

void AUDIO_Channel0_12bit_Pcm_Cmd(AUD_TypeDef *audio,FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    if (newstatus)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_CH0_PCM_SEL_O_Msk;
    }
    else
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_CH0_PCM_SEL_O_Msk;
    }
}

uint8_t AUDIO_Get_CHANNEL0_PCM_ZEROPADDING(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return (audio->TRCTRL & AUDIO_TRCTRL_CH0_PCM_ZEROPADDING_O_Msk) >> AUDIO_TRCTRL_CH0_PCM_ZEROPADDING_O_Pos;
}

void AUDIO_Set_CHANNEL0_PCM_ZEROPADDING(AUD_TypeDef *audio,uint8_t value)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL0_PCM_ZEROPADDING(value));

    audio->TRCTRL &= ~AUDIO_TRCTRL_CH0_PCM_ZEROPADDING_O_Msk;
    audio->TRCTRL |= (value << AUDIO_TRCTRL_CH0_PCM_ZEROPADDING_O_Pos);
}

FunctionalState AUDIO_Get_Pre_Emphasis_Bypass_EnabledStatus(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    FunctionalState status = DISABLE;

    if (audio->TRCTRL & AUDIO_TRCTRL_PRE_EMPHASIS_BYPASS_O_Msk)
    {
        status = ENABLE;
    }
    else
    {
        status = DISABLE;
    }

    return status;
}

void AUDIO_Set_Pre_Emphasis_Bypass_Cmd(AUD_TypeDef *audio, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    if (newstatus)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_PRE_EMPHASIS_BYPASS_O_Msk;
    }
    else
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_PRE_EMPHASIS_BYPASS_O_Msk;
    }
}

FunctionalState AUDIO_Get_Analog_Emphasis_EnabledStatus(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    FunctionalState status = DISABLE;

    if (audio->TRCTRL & AUDIO_TRCTRL_ANA_EMPHASIS_SEL_O_Msk)
    {
        status = ENABLE;
    }
    else
    {
        status = DISABLE;
    }

    return status;
}

void AUDIO_Set_Analog_Emphasis_Cmd(AUD_TypeDef *audio, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    if (newstatus)
    {
        audio->TRCTRL |= AUDIO_TRCTRL_ANA_EMPHASIS_SEL_O_Msk;
    }
    else
    {
        audio->TRCTRL &= ~AUDIO_TRCTRL_ANA_EMPHASIS_SEL_O_Msk;
    }
}

void AUDIO_Clear_Fifo_Interrupt(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_RAM_FIFO_VAD_INTERRUPT(interrupt));

    if (channel == AUDIO_CHANNEL0)
    {
        if (interrupt & AUDIO_FIFO_UNDERFLOW_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO0_UNDERFLOW_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_OVERFLOW_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO0_OVERFLOW_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_WRITE_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO0_WRITE_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_READ_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO0_READ_CLR_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (interrupt & AUDIO_FIFO_UNDERFLOW_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO1_UNDERFLOW_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_OVERFLOW_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO1_OVERFLOW_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_WRITE_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO1_WRITE_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_READ_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO1_READ_CLR_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        if (interrupt & AUDIO_FIFO_UNDERFLOW_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO2_UNDERFLOW_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_OVERFLOW_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO2_OVERFLOW_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_WRITE_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO2_WRITE_CLR_O_Msk;
        }
        if (interrupt & AUDIO_FIFO_READ_INTERRUPT)
        {
            audio->FFCLR = AUDIO_FFCLR_FIFO2_READ_CLR_O_Msk;
        }
    }
}

uint32_t AUDIO_Read_Fifo_Data(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        return audio->FF0DATA;
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        return audio->FF1DATA;
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        return audio->FF2DATA;
    }
}

uint32_t AUDIO_Get_RAM_Depth(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    uint32_t depth = 0;

    if (channel == AUDIO_CHANNEL0)
    {
        depth = ((audio->RAM0CFG0 & AUDIO_RAM0CFG0_RAM0_DEPTH_CFG_O_Msk) >> AUDIO_RAM0CFG0_RAM0_DEPTH_CFG_O_Pos);
    }
    else
    {
        depth = ((audio->RAM1CFG0 & AUDIO_RAM1CFG0_RAM1_DEPTH_CFG_O_Msk) >> AUDIO_RAM1CFG0_RAM1_DEPTH_CFG_O_Pos);
    }

    return depth;
}

void AUDIO_Set_RAM_Depth(AUD_TypeDef *audio, uint8_t channel, uint32_t depth)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        audio->RAM0CFG0 &= ~AUDIO_RAM0CFG0_RAM0_DEPTH_CFG_O_Pos;
        audio->RAM0CFG0 |= (depth << AUDIO_RAM0CFG0_RAM0_DEPTH_CFG_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        audio->RAM1CFG0 &= ~AUDIO_RAM0CFG0_RAM0_DEPTH_CFG_O_Pos;
        audio->RAM1CFG0 |= (depth << AUDIO_RAM1CFG0_RAM1_DEPTH_CFG_O_Pos);
    }
}

uint32_t AUDIO_Get_RAM_Frame_Move(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    uint32_t depth = 0;

    if (channel == AUDIO_CHANNEL0)
    {
        depth = ((audio->RAM0CFG0 & AUDIO_RAM0CFG0_RAM0_FRAME_MOVE_O_Msk) >> AUDIO_RAM0CFG0_RAM0_FRAME_MOVE_O_Pos);
    }
    else
    {
        depth = ((audio->RAM1CFG0 & AUDIO_RAM1CFG0_RAM1_FRAME_MOVE_O_Msk) >> AUDIO_RAM1CFG0_RAM1_FRAME_MOVE_O_Pos);
    }

    return depth;
}

void AUDIO_Set_RAM_Frame_Move(AUD_TypeDef *audio, uint8_t channel, uint32_t frame_move)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        audio->RAM0CFG0 &= ~AUDIO_RAM0CFG0_RAM0_FRAME_MOVE_O_Msk;
        audio->RAM0CFG0 |= (frame_move << AUDIO_RAM0CFG0_RAM0_FRAME_MOVE_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        audio->RAM1CFG0 &= ~AUDIO_RAM0CFG0_RAM0_FRAME_MOVE_O_Msk;
        audio->RAM1CFG0 |= (frame_move << AUDIO_RAM1CFG0_RAM1_FRAME_MOVE_O_Pos);
    }
}

uint32_t AUDIO_Get_RAM_Length(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    uint32_t depth = 0;

    if (channel == AUDIO_CHANNEL0)
    {
        depth = audio->RAM1CFG0;
    }
    else
    {
        depth = audio->RAM1CFG1;
    }

    return depth;
}

void AUDIO_Set_RAM_Length(AUD_TypeDef *audio, uint8_t channel, uint32_t length)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        audio->RAM0CFG1 = length;
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        audio->RAM1CFG1 = length;
    }
}

void AUDIO_Clear_Ram_Interrupt(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_RAM_FIFO_VAD_INTERRUPT(interrupt));

    if (channel == AUDIO_CHANNEL0)
    {
        if (interrupt & AUDIO_RAM_INTERRUPT)
        {
            audio->RAMCLR |= AUDIO_RAMCLR_RAM0_CLR_O_Msk;
        }
        if (interrupt & AUDIO_RAM_FRAME_VLD_INTERRUPT)
        {
            audio->RAMCLR |= AUDIO_RAMCLR_RAM0_FRAME_VLD_CLR_O_Msk;
        }
        if (interrupt & AUDIO_RAM_READ_INTERRUPT)
        {
            audio->RAMCLR |= AUDIO_RAMCLR_RAM0_RD_CLR_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (interrupt & AUDIO_RAM_INTERRUPT)
        {
            audio->RAMCLR |= AUDIO_RAMCLR_RAM1_CLR_O_Msk;
        }
        if (interrupt & AUDIO_RAM_FRAME_VLD_INTERRUPT)
        {
            audio->RAMCLR |= AUDIO_RAMCLR_RAM1_FRAME_VLD_CLR_O_Msk;
        }
        if (interrupt & AUDIO_RAM_READ_INTERRUPT)
        {
            audio->RAMCLR |= AUDIO_RAMCLR_RAM1_RD_CLR_O_Msk;
        }
    }
}

uint32_t AUDIO_Read_Ram_Data(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        return audio->RAM0DATA;
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        return audio->RAM1DATA;
    }
}

uint32_t AUDIO_Get_Bq_B0_Configuration(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->PCM0CFG0 & AUDIO_PCMCFG0_BQ_B0_O_Msk) >> AUDIO_PCMCFG0_BQ_B0_O_Pos);
}

void AUDIO_Set_Bq_B0_Configuration(AUD_TypeDef *audio, int16_t value)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->PCM0CFG0 = (audio->PCM0CFG0 | (value << AUDIO_PCMCFG0_BQ_B0_O_Pos));
}

uint32_t AUDIO_Get_Bq_B1_Configuration(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->PCM0CFG0 & AUDIO_PCMCFG0_BQ_B1_O_Msk) >> AUDIO_PCMCFG0_BQ_B1_O_Pos);
}

void AUDIO_Set_Bq_B1_Configuration(AUD_TypeDef *audio, int16_t value)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->PCM0CFG0 = (audio->PCM0CFG0 | (value << AUDIO_PCMCFG0_BQ_B1_O_Pos));
}

uint32_t AUDIO_Get_Bq_B2_Configuration(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->PCM0CFG1 & AUDIO_PCMCFG1_BQ_B2_O_Msk) >> AUDIO_PCMCFG1_BQ_B2_O_Pos);
}

void AUDIO_Set_Bq_B2_Configuration(AUD_TypeDef *audio, uint16_t value)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->PCM0CFG1 = (audio->PCM0CFG1 | (value << AUDIO_PCMCFG1_BQ_B2_O_Pos));
}

uint32_t AUDIO_Get_Bq_A0_Configuration(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->PCM0CFG1 & AUDIO_PCMCFG1_BQ_A0_O_Msk) >> AUDIO_PCMCFG1_BQ_A0_O_Pos);
}

void AUDIO_Set_Bq_A0_Configuration(AUD_TypeDef *audio, uint16_t value)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->PCM0CFG1 = (audio->PCM0CFG1 | (value << AUDIO_PCMCFG1_BQ_A0_O_Pos));
}

uint32_t AUDIO_Get_Bq_A1_Configuration(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return audio->PCM0CFG2;
}

void AUDIO_Set_Bq_A1_Configuration(AUD_TypeDef *audio, int16_t value)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->PCM0CFG2 = value;
}

__NOINLINE uint32_t AUDIO_Get_Channel_Gain_Configuration(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    uint8_t gain = 0;

    if (channel == AUDIO_CHANNEL0)
    {
        gain = ((audio->PCMGAIN & AUDIO_PCMGAIN_CH0_GAIN_O_Msk) >> AUDIO_PCMGAIN_CH0_GAIN_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        gain = ((audio->PCMGAIN & AUDIO_PCMGAIN_CH1_GAIN_O_Msk) >> AUDIO_PCMGAIN_CH1_GAIN_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        gain = ((audio->PCMGAIN & AUDIO_PCMGAIN_CH2_GAIN_O_Msk) >> AUDIO_PCMGAIN_CH2_GAIN_O_Pos);
    }

    return gain;
}


#pragma GCC push_options
#pragma GCC optimize("no-inline,no-inline-functions,no-inline-small-functions")
__NOINLINE void delay_cycles(int cycles) {
    volatile int i;
    int cnt;

    cnt = cycles;
    for (i = 0; i < cnt; i++) {
    };
}
#pragma GCC pop_options

__NOINLINE void AUDIO_Set_Channel_Gain_Configuration(AUD_TypeDef *audio, uint8_t channel, uint8_t value)
{
    volatile uint32_t dummy;
    uint32_t tmp;

    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        tmp = audio->PCMGAIN;
        tmp &= ~AUDIO_PCMGAIN_CH0_GAIN_O_Msk;
        tmp |= value << AUDIO_PCMGAIN_CH0_GAIN_O_Pos;
        delay_cycles(10);
        audio->PCMGAIN = tmp;
        delay_cycles(10);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        tmp = audio->PCMGAIN;
        tmp &= ~AUDIO_PCMGAIN_CH1_GAIN_O_Msk;
        tmp |= value << AUDIO_PCMGAIN_CH1_GAIN_O_Pos;
        delay_cycles(10);
        audio->PCMGAIN = tmp;
        delay_cycles(10);
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        tmp = audio->PCMGAIN;
        tmp &= ~AUDIO_PCMGAIN_CH2_GAIN_O_Msk;
        tmp |= value << AUDIO_PCMGAIN_CH2_GAIN_O_Pos;
        delay_cycles(10);
        audio->PCMGAIN = tmp;
        delay_cycles(10);
    }
}

uint32_t AUDIO_Get_Pcm_Data_Number(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return audio->VADCNT;
}

uint32_t AUDIO_Get_Short_Term_Power_Threshold(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return audio->VAD0;
}

void AUDIO_Set_Short_Term_Power_Threshold(AUD_TypeDef *audio, uint32_t threshold)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->VAD0 = threshold;
}

uint32_t AUDIO_Get_Long_Term_Power_Threshold(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return audio->VAD1;
}

void AUDIO_Set_Long_Term_Power_Threshold(AUD_TypeDef *audio, uint32_t threshold)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->VAD1 = threshold;
}

uint32_t AUDIO_Get_Deviation_Threshold(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return audio->VAD2;
}

void AUDIO_Set_Deviation_Threshold(AUD_TypeDef *audio, uint32_t threshold)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->VAD2 = threshold;
}

uint32_t AUDIO_Get_Short_Term_Attack_Window_Length_Threshold(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->VAD3 & AUDIO_VAD3_DEF_STP_WINLEN_O_Msk) >> AUDIO_VAD3_DEF_STP_WINLEN_O_Pos);
}

void AUDIO_Set_Short_Term_Attack_Window_Length_Threshold(AUD_TypeDef *audio, uint16_t threshold)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->VAD3 = (audio->VAD3 | (threshold << AUDIO_VAD3_DEF_STP_WINLEN_O_Pos));
}

uint32_t AUDIO_Get_Short_Term_Attack_Window_Length_Shift(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->VAD3 & AUDIO_VAD3_SPT_WIN_SHIFT_O_Msk) >> AUDIO_VAD3_SPT_WIN_SHIFT_O_Pos);
}

void AUDIO_Set_Short_Term_Attack_Window_Length_Shift(AUD_TypeDef *audio, uint16_t shift)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->VAD3 = (audio->VAD3 | (shift << AUDIO_VAD3_SPT_WIN_SHIFT_O_Pos));
}

uint32_t AUDIO_Get_Long_Term_Attack_Window_Length_Threshold(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->VAD4 & AUDIO_VAD4_DEF_LTP_WINLEN_O_Msk) >> AUDIO_VAD4_DEF_LTP_WINLEN_O_Pos);
}

void AUDIO_Set_Long_Term_Attack_Window_Length_Threshold(AUD_TypeDef *audio, uint16_t threshold)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->VAD4 = (audio->VAD4 | (threshold << AUDIO_VAD4_DEF_LTP_WINLEN_O_Pos));
}

uint32_t AUDIO_Get_Long_Term_Attack_Window_Length_Shift(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return ((audio->VAD4 & AUDIO_VAD4_LPT_WIN_SHIFT_O_Msk) >> AUDIO_VAD4_LPT_WIN_SHIFT_O_Pos);
}

void AUDIO_Set_Long_Term_Attack_Window_Length_Shift(AUD_TypeDef *audio, uint16_t shift)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    audio->VAD4 = (audio->VAD4 | (shift << AUDIO_VAD4_LPT_WIN_SHIFT_O_Pos));
}

uint32_t AUDIO_Get_Ram_Interrupt_Status(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    uint32_t status = 0;

    if (channel == AUDIO_CHANNEL0)
    {
        if (audio->TRINT & AUDIO_TRINT_RAM0_FRAME_VLD_INT_Msk)
            status |= AUDIO_RAM_FRAME_VLD_INTERRUPT;
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (audio->TRINT & AUDIO_TRINT_RAM1_FRAME_VLD_INT_Msk)
            status |= AUDIO_RAM_FRAME_VLD_INTERRUPT;
    }

    return status;
}

uint32_t AUDIO_Get_FIFO_Interrupt_Status(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    uint32_t status = 0, reg = 0;

    reg = audio->TRINT;
    if (channel == AUDIO_CHANNEL0)
    {
        if (reg & AUDIO_TRINT_FIFO0_FULL_INT_Msk)
        {
            status |= AUDIO_FIFO_FULL_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO0_HALF_FULL_INT_Msk)
        {
            status |= AUDIO_FIFO_HALF_FULL_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO0_EMP_INT_Msk)
        {
            status |= AUDIO_FIFO_EMPTY_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO0_OVERFLOW_INT_Msk)
        {
            status |= AUDIO_FIFO_OVERFLOW_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO0_UNDERFLOW_INT_Msk)
        {
            status |= AUDIO_FIFO_UNDERFLOW_INTERRUPT;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (reg & AUDIO_TRINT_FIFO1_FULL_INT_Msk)
        {
            status |= AUDIO_FIFO_FULL_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO1_HALF_FULL_INT_Msk)
        {
            status |= AUDIO_FIFO_HALF_FULL_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO1_EMP_INT_Msk)
        {
            status |= AUDIO_FIFO_EMPTY_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO1_OVERFLOW_INT_Msk)
        {
            status |= AUDIO_FIFO_OVERFLOW_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO1_UNDERFLOW_INT_Msk)
        {
            status |= AUDIO_FIFO_UNDERFLOW_INTERRUPT;
        }
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        if (reg & AUDIO_TRINT_FIFO2_FULL_INT_Msk)
        {
            status |= AUDIO_FIFO_FULL_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO2_HALF_FULL_INT_Msk)
        {
            status |= AUDIO_FIFO_HALF_FULL_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO2_EMP_INT_Msk)
        {
            status |= AUDIO_FIFO_EMPTY_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO2_OVERFLOW_INT_Msk)
        {
            status |= AUDIO_FIFO_OVERFLOW_INTERRUPT;
        }
        if (reg & AUDIO_TRINT_FIFO2_UNDERFLOW_INT_Msk)
        {
            status |= AUDIO_FIFO_UNDERFLOW_INTERRUPT;
        }
    }

    return status;
}

uint32_t AUDIO_Get_Vad_Interrupt_Status(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    uint32_t status = 0;

    if (audio->TRINT & AUDIO_TRINT_VAD_ACT_INT_Msk)
    {
        status |= AUDIO_VAD_ACT_INTERRUPT;
    }

    return status;
}

void AUDIO_Set_Ram_Interrupt_Mask(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_RAM_FIFO_VAD_INTERRUPT(interrupt));

    if (channel == AUDIO_CHANNEL0)
    {
        if (interrupt & AUDIO_RAM_FRAME_VLD_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_RAM0_FRAME_VLD_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_RAM0_FRAME_VLD_INT_Msk;
            }
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (interrupt & AUDIO_RAM_FRAME_VLD_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_RAM1_FRAME_VLD_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_RAM1_FRAME_VLD_INT_Msk;
            }
        }
    }
}

void AUDIO_Set_FIFO_Interrupt_Mask(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_RAM_FIFO_VAD_INTERRUPT(interrupt));

    if (channel == AUDIO_CHANNEL0)
    {
        if (interrupt & AUDIO_FIFO_FULL_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO0_FULL_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_RAM0_FRAME_VLD_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_HALF_FULL_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO0_HALF_FULL_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO0_HALF_FULL_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_EMPTY_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO0_EMP_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO0_EMP_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_OVERFLOW_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO0_OVERFLOW_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO0_OVERFLOW_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_UNDERFLOW_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO0_UNDERFLOW_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO0_UNDERFLOW_INT_Msk;
            }
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (interrupt & AUDIO_FIFO_FULL_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO1_FULL_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO1_FULL_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_HALF_FULL_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO1_HALF_FULL_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO1_HALF_FULL_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_EMPTY_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO1_EMP_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO1_EMP_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_OVERFLOW_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO1_OVERFLOW_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO1_OVERFLOW_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_UNDERFLOW_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO1_UNDERFLOW_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO1_UNDERFLOW_INT_Msk;
            }
        }
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        if (interrupt & AUDIO_FIFO_FULL_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO2_FULL_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO2_FULL_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_HALF_FULL_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO2_HALF_FULL_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO2_HALF_FULL_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_EMPTY_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO2_EMP_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO2_EMP_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_OVERFLOW_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO2_OVERFLOW_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO2_OVERFLOW_INT_Msk;
            }
        }
        if (interrupt & AUDIO_FIFO_UNDERFLOW_INTERRUPT)
        {
            if (!newstatus)
            {
                audio->TRINTMSK |= AUDIO_TRINT_FIFO2_UNDERFLOW_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_TRINT_FIFO2_UNDERFLOW_INT_Msk;
            }
        }
    }
}

void AUDIO_Set_Vad_Interrupt_Mask(AUD_TypeDef *audio, uint32_t interrupt, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_RAM_FIFO_VAD_INTERRUPT(interrupt));

    if (interrupt & AUDIO_VAD_ACT_INTERRUPT)
    {
        if (!newstatus)
        {
            audio->TRINTMSK |= AUDIO_TRINT_VAD_ACT_INT_Msk;
        }
        else
        {
            audio->TRINTMSK &= ~AUDIO_TRINT_VAD_ACT_INT_Msk;
        }
    }
}

uint32_t AUDIO_Get_DigitalCompa_or_DigitalCompa_or_Compwakeup_Interrupt_Status(AUD_TypeDef *audio)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));

    return audio->AFEINT;
}

void AUDIO_Set_DigitalCompa_or_DigitalCompa_or_Compwakeup_Interrupt_Status(AUD_TypeDef *audio, uint32_t interrupt, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_DIGITAL_COMP_CHANNEL_INTERRUPT(interrupt));

    if (interrupt & AUDIO_DIGITAL_CMPA_INTERRUPT)
    {
        if (newstatus)
        {
            audio->AFEINTMSK |= AUDIO_AFEINT_DIG_CMPA_INT_Msk;
        }
        else
        {
            audio->AFEINTMSK &= ~AUDIO_AFEINT_DIG_CMPA_INT_Msk;
        }
    }
    if (interrupt & AUDIO_DIGITAL_CMPB_INTERRUPT)
    {
        if (newstatus)
        {
            audio->AFEINTMSK |= AUDIO_AFEINT_DIG_CMPB_INT_Msk;
        }
        else
        {
            audio->AFEINTMSK &= ~AUDIO_AFEINT_DIG_CMPB_INT_Msk;
        }
    }
    if (interrupt & AUDIO_COMP_WAKEUP_INTERRUPT)
    {
        if (newstatus)
        {
            audio->AFEINTMSK |= AUDIO_AFEINT_COMP_WKUP_INT_Msk;
        }
        else
        {
            audio->AFEINTMSK &= ~AUDIO_AFEINT_COMP_WKUP_INT_Msk;
        }
    }
}

uint32_t AUDIO_Get_Channel_Interrupt_Status(AUD_TypeDef *audio, uint8_t channel)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    uint32_t status = 0, reg = 0;

    reg = audio->AFEINTMSK;

    if (channel == AUDIO_CHANNEL0)
    {
        if (reg & AUDIO_AFEINT_CH0_AUDIO_OUT_RDY_INT_Msk)
        {
            status |= AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT;
        }
        if (reg & AUDIO_AFEINT_CH0_AGC_GAIN_RDY_INT_Msk)
        {
            status |= AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT;
        }
        if (reg & AUDIO_AFEINT_CH0_DIG_CMP_CNT_INT_Msk)
        {
            status |= AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (reg & AUDIO_AFEINT_CH1_AUDIO_OUT_RDY_INT_Msk)
        {
            status |= AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT;
        }
        if (reg & AUDIO_AFEINT_CH1_AGC_GAIN_RDY_INT_Msk)
        {
            status |= AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT;
        }
        if (reg & AUDIO_AFEINT_CH1_DIG_CMP_CNT_INT_Msk)
        {
            status |= AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT;
        }
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        if (reg & AUDIO_AFEINT_CH2_AUDIO_OUT_RDY_INT_Msk)
        {
            status |= AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT;
        }
        if (reg & AUDIO_AFEINT_CH2_AGC_GAIN_RDY_INT_Msk)
        {
            status |= AUDIO_AFEINT_CH2_AGC_GAIN_RDY_INT_Msk;
        }
        if (reg & AUDIO_AFEINT_CH2_DIG_CMP_CNT_INT_Msk)
        {
            status |= AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT;
        }
    }

    return status;
}

void AUDIO_Set_Channel_Interrupt_Status(AUD_TypeDef *audio, uint8_t channel, uint32_t interrupt, FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_DIGITAL_COMP_CHANNEL_INTERRUPT(interrupt));

    if (channel == AUDIO_CHANNEL0)
    {
        if (interrupt & AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH0_AUDIO_OUT_RDY_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH0_AUDIO_OUT_RDY_INT_Msk;
            }
        }
        if (interrupt & AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH0_AGC_GAIN_RDY_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH0_AGC_GAIN_RDY_INT_Msk;
            }
        }
        if (interrupt & AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH0_DIG_CMP_CNT_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH0_DIG_CMP_CNT_INT_Msk;
            }
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (interrupt & AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH1_AUDIO_OUT_RDY_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH1_AUDIO_OUT_RDY_INT_Msk;
            }
        }
        if (interrupt & AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH1_AGC_GAIN_RDY_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH1_AGC_GAIN_RDY_INT_Msk;
            }
        }
        if (interrupt & AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH1_DIG_CMP_CNT_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH1_DIG_CMP_CNT_INT_Msk;
            }
        }
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        if (interrupt & AUDIO_CHANNEL_AUDIO_OUT_RDY_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH2_AUDIO_OUT_RDY_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH2_AUDIO_OUT_RDY_INT_Msk;
            }
        }
        if (interrupt & AUDIO_CHANNEL_AGC_AGIN_RDY_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH2_AGC_GAIN_RDY_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH2_AGC_GAIN_RDY_INT_Msk;
            }
        }
        if (interrupt & AUDIO_CHANNEL_DIGITAL_CMP_CNT_INTERRUPT)
        {
            if (newstatus)
            {
                audio->TRINTMSK |= AUDIO_AFEINT_CH2_DIG_CMP_CNT_INT_Msk;
            }
            else
            {
                audio->TRINTMSK &= ~AUDIO_AFEINT_CH2_DIG_CMP_CNT_INT_Msk;
            }
        }
    }
}

void AUDIO_Set_Clock_Switch_Configuration(AUD_TypeDef *audio,uint8_t channel,uint8_t clock_switch)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));
    assert_param(IS_AUDIO_CLOCK_SWITCH_CONFIGURATION(clock_switch));

    if (channel == AUDIO_CHANNEL0)
    {
        audio->CLKSWI_CFG &= ~AUDIO_CLKSWI_CFG_CH0_RD_CLK_SEL_O_Msk;
        audio->CLKSWI_CFG |= (clock_switch << AUDIO_CLKSWI_CFG_CH0_RD_CLK_SEL_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        audio->CLKSWI_CFG &= ~AUDIO_CLKSWI_CFG_CH1_RD_CLK_SEL_O_Msk;
        audio->CLKSWI_CFG |= (clock_switch << AUDIO_CLKSWI_CFG_CH1_RD_CLK_SEL_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        audio->CLKSWI_CFG &= ~AUDIO_CLKSWI_CFG_CH2_RD_CLK_SEL_O_Msk;
        audio->CLKSWI_CFG |= (clock_switch << AUDIO_CLKSWI_CFG_CH2_RD_CLK_SEL_O_Pos);
    }
}

void AUDIO_Set_Hardware_Request_Dma_Cmd(AUD_TypeDef *audio,uint8_t channel,FunctionalState newstatus)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        if (newstatus)
        {
            audio->AUDIO_DMA_CFG |= AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_EN_O_Msk;
        }
        else
        {
            audio->AUDIO_DMA_CFG &= ~AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_EN_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        if (newstatus)
        {
            audio->AUDIO_DMA_CFG |= AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_EN_O_Msk;
        }
        else
        {
            audio->AUDIO_DMA_CFG &= ~AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_EN_O_Msk;
        }
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        if (newstatus)
        {
            audio->AUDIO_DMA_CFG |= AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_EN_O_Msk;
        }
        else
        {
            audio->AUDIO_DMA_CFG &= ~AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_EN_O_Msk;
        }
    }
}

void AUDIO_Set_Dma_Level(AUD_TypeDef *audio,uint8_t channel,uint8_t level)
{
    assert_param(audio != NULL);
    assert_param(IS_AUD_ALL_INSTANCE(audio));
    assert_param(IS_AUDIO_CHANNEL(channel));

    if (channel == AUDIO_CHANNEL0)
    {
        audio->AUDIO_DMA_CFG &= ~AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_LEVEL_O_Msk;
        audio->AUDIO_DMA_CFG |= (level << AUDIO_AUDIO_DMA_CFG_CH0_DMA_REQ_LEVEL_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL1)
    {
        audio->AUDIO_DMA_CFG &= ~AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_LEVEL_O_Msk;
        audio->AUDIO_DMA_CFG |= (level << AUDIO_AUDIO_DMA_CFG_CH1_DMA_REQ_LEVEL_O_Pos);
    }
    else if (channel == AUDIO_CHANNEL2)
    {
        audio->AUDIO_DMA_CFG &= ~AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_LEVEL_O_Msk;
        audio->AUDIO_DMA_CFG |= (level << AUDIO_AUDIO_DMA_CFG_CH2_DMA_REQ_LEVEL_O_Pos);
    }
}

/* audio vad parameter config */
#define DEF_STP_THRESHOLD 256
#define DEF_LTP_THRESHOLD 64
#define DEF_DEVIATION 256
#define DEF_STP_WINLEN 2
#define SPT_WIN_SHIFT 1
#define DEF_LTP_WINLEN 64
#define LPT_WIN_SHIFT 6

void VAD_Config(void)
{
    AUDIO_Set_Bq_B0_Configuration(AUD, 0x95f);
    AUDIO_Set_Bq_B1_Configuration(AUD, 0);

    AUDIO_Set_Bq_A0_Configuration(AUD, 0xed42);
    AUDIO_Set_Bq_B2_Configuration(AUD, 0xe000);
    AUDIO_Set_Bq_A1_Configuration(AUD,0xd41);

    AUDIO_Set_Short_Term_Power_Threshold(AUD, DEF_STP_THRESHOLD * DEF_STP_THRESHOLD);
    AUDIO_Set_Long_Term_Power_Threshold(AUD, DEF_LTP_THRESHOLD * DEF_LTP_THRESHOLD);
    AUDIO_Set_Deviation_Threshold(AUD, DEF_DEVIATION * DEF_DEVIATION);
    AUDIO_Set_Short_Term_Attack_Window_Length_Threshold(AUD, DEF_STP_WINLEN);
    AUDIO_Set_Short_Term_Attack_Window_Length_Shift(AUD, SPT_WIN_SHIFT);
    AUDIO_Set_Long_Term_Attack_Window_Length_Threshold(AUD, DEF_LTP_WINLEN);
    AUDIO_Set_Long_Term_Attack_Window_Length_Shift(AUD, LPT_WIN_SHIFT);
    AUDIO_Set_Vad_Interrupt_Mask(AUD, AUDIO_VAD_ACT_INTERRUPT, ENABLE);
    PMU_Set_Ie_Msk(PMU, PMU_VAD_IMSK, ENABLE);
}
