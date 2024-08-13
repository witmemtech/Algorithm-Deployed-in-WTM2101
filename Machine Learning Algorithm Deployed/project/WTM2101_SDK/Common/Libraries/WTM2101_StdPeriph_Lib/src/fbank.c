/**
  ******************************************************************************
  * @file    fbank.c
  * @brief   The Source Codes for the FBANK Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "fbank.h"

void FBANK_Enable_Cmd(FBANK_TypeDef *fbank, FunctionalState NewState)
{
    assert_param(fbank != NULL);
    assert_param(IS_FBANK_ALL_INSTANCE(fbank));

    if (NewState)
    {
        fbank->FBANK_EN |= FBANK_FBANK_EN_FBANK_EN_Msk;
    }
    else
    {
        fbank->FBANK_EN &= ~FBANK_FBANK_EN_FBANK_EN_Msk;
    }
}

void FBANK_Ctl_Cmd(FBANK_TypeDef *fbank, uint32_t ctl,FunctionalState NewState)
{
    assert_param(fbank != NULL);
    assert_param(IS_FBANK_ALL_INSTANCE(fbank));
    assert_param(IS_FBANK_MODE(ctl));

    if (ctl & DATA_SRAM_SEL)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_FBANK_DATA_RAM_SEL_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_FBANK_DATA_RAM_SEL_Msk;
        }
    }

    if (ctl & SRAM_ADDR_SEL)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_SRAM_ADDR_SEL_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_SRAM_ADDR_SEL_Msk;
        }
    }

    if (ctl & FBANK_SRC_SEL)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_FBANK_SRC_SEL_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_FBANK_SRC_SEL_Msk;
        }
    }

    if (ctl & FFT_ENABLE)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_FFT_ENABLE_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_FFT_ENABLE_Msk;
        }
    }

    if (ctl & IFFT_ENABLE)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_IFFT_ENABLE_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_IFFT_ENABLE_Msk;
        }
    }

    if (ctl & MELFILTER_ENABLE)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_MELFILTER_ENABLE_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_MELFILTER_ENABLE_Msk;
        }
    }

    if (ctl & SQRT_ENABLE)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_SQRT_ENABLE_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_SQRT_ENABLE_Msk;
        }
    }

    if (ctl & LOG_ENABLE)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_LOG_ENABLE_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_LOG_ENABLE_Msk;
        }
    }

    if (ctl & DO_WINDOW)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_DO_WINDOW_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_DO_WINDOW_Msk;
        }
    }

    if (ctl & DO_BITREVERSE)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_DO_BITREVERSE_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_DO_BITREVERSE_Msk;
        }
    }

    if (ctl & DO_CFFT_HCLK)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_DO_CFFT_HCLK_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_DO_CFFT_HCLK_Msk;
        }
    }

    if (ctl & DO_RFFT_HCLK)
    {
        if (NewState)
        {
            fbank->FBANK_CONTROL |= FBANK_FBANK_CONTROL_DO_RFFT_HCLK_Msk;
        }
        else
        {
            fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_DO_RFFT_HCLK_Msk;
        }
    }
}

void FBANK_Set_Data_Length(FBANK_TypeDef *fbank,uint8_t length)
{
    assert_param(fbank != NULL);
    assert_param(IS_FBANK_ALL_INSTANCE(fbank));
    assert_param(IS_FBANK_DATA_LENGTH(length));

    fbank->FBANK_CONTROL &= ~FBANK_FBANK_CONTROL_FRAME_LEN_Msk;
    fbank->FBANK_CONTROL |= (length << FBANK_FBANK_CONTROL_FRAME_LEN_Pos);
}

void FBANK_Clear_Interrupt_Cmd(FBANK_TypeDef *fbank,uint8_t int_type)
{
    assert_param(fbank != NULL);
    assert_param(IS_FBANK_ALL_INSTANCE(fbank));
    assert_param(IS_FBANK_INTERRUPT(int_type));

    if (int_type & FBANK_INT)
    {
        fbank->INT_SOURCE &= ~FBANK_INT_MASK_FBANK_DONE_MASK_Msk;
    }
    if (int_type & FBANK_FOR_FFT_INT)
    {
        fbank->INT_SOURCE &= ~FBANK_INT_MASK_FFT_DONE_MASK_Msk;
    }
    if (int_type & FBANK_FOR_IFFT_INT)
    {
        fbank->INT_SOURCE &= ~FBANK_INT_MASK_IFFT_DONE_MASK_Msk;
    }
    if (int_type & FBANK_MELFILTER_INT)
    {
        fbank->INT_SOURCE &= ~FBANK_INT_MASK_MELFILTER_DONE_MASK_Msk;
    }
    if (int_type & FBANK_SQRT_INT)
    {
        fbank->INT_SOURCE &= ~FBANK_INT_MASK_SQRT_DONE_MASK_Msk;
    }
    if (int_type & FBANK_LOG_INT)
    {
        fbank->INT_SOURCE &= ~FBANK_INT_MASK_LOG_DONE_MASK_Msk;
    }
}

void FBANK_Set_Interrupt_Cmd(FBANK_TypeDef *fbank, uint8_t int_type, FunctionalState NewState)
{
    assert_param(fbank != NULL);
    assert_param(IS_FBANK_ALL_INSTANCE(fbank));
    assert_param(IS_FBANK_INTERRUPT(int_type));

    if (int_type & FBANK_INT)
    {
        if (NewState)
        {
            fbank->INT_MASK |= FBANK_INT_MASK_FBANK_DONE_MASK_Msk;
        }
        else
        {
            fbank->INT_MASK &= ~FBANK_INT_MASK_FBANK_DONE_MASK_Msk;
        }
    }
    if (int_type & FBANK_FOR_FFT_INT)
    {
        if (NewState)
        {
            fbank->INT_MASK |= FBANK_INT_MASK_FFT_DONE_MASK_Msk;
        }
        else
        {
            fbank->INT_MASK &= ~FBANK_INT_MASK_FFT_DONE_MASK_Msk;
        }
    }
    if (int_type & FBANK_FOR_IFFT_INT)
    {
        if (NewState)
        {
            fbank->INT_MASK |= FBANK_INT_MASK_IFFT_DONE_MASK_Msk;
        }
        else
        {
            fbank->INT_MASK &= ~FBANK_INT_MASK_IFFT_DONE_MASK_Msk;
        }
    }
    if (int_type & FBANK_MELFILTER_INT)
    {
        if (NewState)
        {
            fbank->INT_MASK |= FBANK_INT_MASK_MELFILTER_DONE_MASK_Msk;
        }
        else
        {
            fbank->INT_MASK &= ~FBANK_INT_MASK_MELFILTER_DONE_MASK_Msk;
        }
    }
    if (int_type & FBANK_SQRT_INT)
    {
        if (NewState)
        {
            fbank->INT_MASK |= FBANK_INT_MASK_SQRT_DONE_MASK_Msk;
        }
        else
        {
            fbank->INT_MASK &= ~FBANK_INT_MASK_SQRT_DONE_MASK_Msk;
        }
    }
    if (int_type & FBANK_LOG_INT)
    {
        if (NewState)
        {
            fbank->INT_MASK |= FBANK_INT_MASK_LOG_DONE_MASK_Msk;
        }
        else
        {
            fbank->INT_MASK &= ~FBANK_INT_MASK_LOG_DONE_MASK_Msk;
        }
    }
}

FunctionalState FBANK_Read_Audio_Sram_Status(FBANK_TypeDef *fbank)
{
    assert_param(fbank != NULL);
    assert_param(IS_FBANK_ALL_INSTANCE(fbank));

    if (fbank->FBANK_STATUS & FBANK_FBANK_STATUS_FBANK_READ_AUDIO_PENDING_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void FBANK_Write_Sram_Data(FBANK_TypeDef *fbank,uint32_t *data,int len)
{
    assert_param(fbank != NULL);
    assert_param(IS_FBANK_ALL_INSTANCE(fbank));

    int i = 0;

    for (i = 0; i < len; i++)
    {
        fbank->SRAM[i] = data[i];
    }
}

void FBANK_Read_Sram_Data(FBANK_TypeDef *fbank,uint32_t *data,int len)
{
    assert_param(fbank != NULL);
    assert_param(IS_FBANK_ALL_INSTANCE(fbank));

    int i = 0;

    for (i = 0; i < len; i++)
    {
        data[i] = fbank->SRAM[i];
    }
}

void FBANK_Write_Sram_Data_CP(FBANK_TypeDef *fbank,uint32_t *data,int len)
{
        int i=0;
        assert_param(fbank != NULL);
	assert_param(IS_FBANK_ALL_INSTANCE(fbank));
        //memcpy( fbank->SRAM,data,len<<2);
        //return;

        uint32_t *pSrc=data;
        volatile uint32_t *pDst=fbank->SRAM;

        uint32_t tmp_tab[8];

        for(i=0;i<len;i+=8)
        {
            tmp_tab[0]=*pSrc++;
            tmp_tab[1]=*pSrc++;
            tmp_tab[2]=*pSrc++;
            tmp_tab[3]=*pSrc++;
            *pDst++=tmp_tab[0];
            *pDst++=tmp_tab[1];
            *pDst++=tmp_tab[2];
            *pDst++=tmp_tab[3];
            tmp_tab[4]=*pSrc++;
            tmp_tab[5]=*pSrc++;
            tmp_tab[6]=*pSrc++;
            tmp_tab[7]=*pSrc++;
            *pDst++=tmp_tab[4];
            *pDst++=tmp_tab[5];
            *pDst++=tmp_tab[6];
            *pDst++=tmp_tab[7];
        }
}

void FBANK_Read_Sram_Data_CP(FBANK_TypeDef *fbank,uint32_t *data,int len)
{
        int i = 0;
        assert_param(fbank != NULL);
	assert_param(IS_FBANK_ALL_INSTANCE(fbank));
        //memcpy(data,fbank->SRAM,len<<2);
        
        volatile uint32_t *pSrc=fbank->SRAM;
        uint32_t *pDst=data;

        uint32_t tmp_tab[8];       

        for(i=0;i<len;i+=8)
        {
            tmp_tab[0]=*pSrc++;
            tmp_tab[1]=*pSrc++;
            tmp_tab[2]=*pSrc++;
            tmp_tab[3]=*pSrc++;
            *pDst++=tmp_tab[0];
            *pDst++=tmp_tab[1];
            *pDst++=tmp_tab[2];
            *pDst++=tmp_tab[3];
            tmp_tab[4]=*pSrc++;
            tmp_tab[5]=*pSrc++;
            tmp_tab[6]=*pSrc++;
            tmp_tab[7]=*pSrc++;
            *pDst++=tmp_tab[4];
            *pDst++=tmp_tab[5];
            *pDst++=tmp_tab[6];
            *pDst++=tmp_tab[7];
        }
}

void FBANK_Read_Sram_Data_CP2(FBANK_TypeDef *fbank,uint32_t *data,int len)
{
        int i = 0;
        assert_param(fbank != NULL);
	assert_param(IS_FBANK_ALL_INSTANCE(fbank));
        //memcpy(data,fbank->SRAM,len<<2);
        
        volatile uint32_t *pSrc=fbank->SRAM;
        uint32_t *pDst=data;

        uint32_t tmp_tab[8];       

        for(i=0;i<len;i+=8)
        {
            tmp_tab[0]=*pSrc++;
            tmp_tab[1]=*pSrc++;
            tmp_tab[2]=*pSrc++;
            tmp_tab[3]=*pSrc++;
            *pDst++=tmp_tab[0];           
            *pDst++=tmp_tab[2];            
            tmp_tab[4]=*pSrc++;
            tmp_tab[5]=*pSrc++;
            tmp_tab[6]=*pSrc++;
            tmp_tab[7]=*pSrc++;
            *pDst++=tmp_tab[4];           
            *pDst++=tmp_tab[6];
           
        }
}

