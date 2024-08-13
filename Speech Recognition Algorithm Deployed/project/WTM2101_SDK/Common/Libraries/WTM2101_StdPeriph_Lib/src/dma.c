/**
  ******************************************************************************
  * @file    dma.c
  * @brief   The Source Codes for the DMA Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "dma.h"

void DMA_Init(DMA_TypeDef *dma, uint8_t chl, DMA_InitTypeDef *init_struct)
{
    assert_param(dma != NULL && init_struct != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_DIRECTION(init_struct->direction));
    assert_param(IS_DMA_MSIZE(init_struct->dst_msize));
    assert_param(IS_DMA_MSIZE(init_struct->src_msize));
    assert_param(IS_DMA_ADDR_TYPE(init_struct->src_addr_type));
    assert_param(IS_DMA_ADDR_TYPE(init_struct->dst_addr_type));
    assert_param(IS_DMA_WIDTH(init_struct->dst_width));
    assert_param(IS_DMA_WIDTH(init_struct->src_width));
    assert_param(IS_DMA_HARDWARE_PER(init_struct->dst_per));
    assert_param(IS_DMA_HARDWARE_PER(init_struct->src_per));
    assert_param(IS_DMA_HANDSHAKE_TYPE(init_struct->src_handshaking_type));
    assert_param(IS_DMA_HANDSHAKE_TYPE(init_struct->dst_handshaking_type));
    assert_param(IS_DMA_PRIORITY(init_struct->chanel_priority));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;
    uint32_t *ctl1 = NULL;
    uint32_t *cfg0 = NULL;
    uint32_t *cfg1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL0)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL1)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL2)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL3)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL4)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL5)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG5)) + 1;
    }

    *ctl0 &= ~0xffffffff;
    *ctl1 &= ~0xffffffff;
    *cfg0 &= ~0xffffffff;
    *cfg1 &= ~0xffffffff;

    /*the register set*/
    *ctl0 |= (init_struct->llp_src_en) << DMAC_CTL0_LLP_SRC_EN_Pos;
    *ctl0 |= (init_struct->llp_dst_en) << DMAC_CTL0_LLP_DST_EN_Pos;
    *ctl0 |= (init_struct->direction) << DMAC_CTL0_TT_FC_Pos;
    *ctl0 |= (init_struct->src_msize) << DMAC_CTL0_SRC_MSIZE_Pos;
    *ctl0 |= (init_struct->dst_msize) << DMAC_CTL0_DEST_MSIZE_Pos;
    *ctl0 |= (init_struct->src_addr_type) << DMAC_CTL0_SINC_Pos;
    *ctl0 |= (init_struct->dst_addr_type) << DMAC_CTL0_DINC_Pos;
    *ctl0 |= (init_struct->src_width) << DMAC_CTL0_SRC_TR_WIDTH_Pos;
    *ctl0 |= (init_struct->dst_width) << DMAC_CTL0_DST_TR_WIDTH_Pos;
    *ctl0 |= (init_struct->int_en << DMAC_CTL0_INT_EN_Pos);

    *cfg1 |= (init_struct->dst_per) << (DMAC_CFG0_DEST_PER_Pos - 32);
    *cfg1 |= (init_struct->src_per) << (DMAC_CFG0_SRC_PER_Pos - 32);
    *cfg1 |= (init_struct->fifo_mode_en) << (DMAC_CFG0_FIFO_MODE_Pos - 32);
    *cfg0 |= (init_struct->reload_dst_en) << DMAC_CFG0_RELOAD_DST_Pos;
    *cfg0 |= (init_struct->reload_src_en) << DMAC_CFG0_RELOAD_SRC_Pos;
    *cfg0 |= (init_struct->max_abrst) << DMAC_CFG0_MAX_ABRST_Pos;
    *cfg0 |= (init_struct->src_handshaking_type) << DMAC_CFG0_HS_SEL_SRC_Pos;
    *cfg0 |= (init_struct->dst_handshaking_type) << DMAC_CFG0_HS_SEL_DST_Pos;
    *cfg0 |= (init_struct->chanel_priority) << DMAC_CFG0_CH_PRIOR_Pos;
}

void DMA_Uninit(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;
    uint32_t *ctl1 = NULL;
    uint32_t *cfg0 = NULL;
    uint32_t *cfg1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL0)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL1)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL2)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL3)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL4)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL5)) + 1;
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
        cfg1 = ((uint32_t *) & (dma->CFG5)) + 1;
    }

    *ctl0 &= ~0xffffffff;
    *ctl1 &= ~0xffffffff;
    *cfg0 &= ~0xffffffff;
    *cfg1 &= ~0xffffffff;
}

FunctionalState DMA_Get_Enable_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    if (*(((uint32_t *) & (dma->DMA_CFG)) + 0))
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Enable_Cmd(DMA_TypeDef *dma, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->DMA_CFG)) + 0) = 1;
    }
    else
    {
        *(((uint32_t *) & (dma->DMA_CFG)) + 0) = 0;
    }
}

FunctionalState DMA_Get_Channel_Enable_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if ((*(((uint32_t *) & (dma->DMA_CHENR)) + 0)) & chl)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Channel_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->DMA_CHENR)) + 0) = ((((uint32_t)chl) << DMAC_LSTDSTREG_LSTDST_WE_Pos) | (((uint32_t)chl) << DMAC_LSTDSTREG_LSTDST_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->DMA_CHENR)) + 0) = (((uint32_t)chl) << DMAC_LSTDSTREG_LSTDST_WE_Pos);
    }
}

void DMA_Set_Channel_source_address(DMA_TypeDef *dma, uint8_t chl, uint32_t address)
{
    uint32_t *src = NULL;

    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (chl == DMA_CHANNEL0)
    {
        src = ((uint32_t *) & (dma->SAR0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        src = ((uint32_t *) & (dma->SAR1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        src = ((uint32_t *) & (dma->SAR2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        src = ((uint32_t *) & (dma->SAR3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        src = ((uint32_t *) & (dma->SAR4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        src = ((uint32_t *) & (dma->SAR5)) + 0;
    }

    *src = address;
}

void DMA_Set_Channel_destination_address(DMA_TypeDef *dma, uint8_t chl, uint32_t address)
{
    uint32_t *dst = NULL;

    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (chl == DMA_CHANNEL0)
    {
        dst = ((uint32_t *) & (dma->DAR0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        dst = ((uint32_t *) & (dma->DAR1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        dst = ((uint32_t *) & (dma->DAR2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        dst = ((uint32_t *) & (dma->DAR3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        dst = ((uint32_t *) & (dma->DAR4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        dst = ((uint32_t *) & (dma->DAR5)) + 0;
    }

    *dst = address;
}

void DMA_Set_block_chain_address(DMA_TypeDef *dma, uint8_t chl, uint32_t address)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *llp = NULL;

    if (chl == DMA_CHANNEL0)
    {
        llp = ((uint32_t *) & (dma->LLP0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        llp = ((uint32_t *) & (dma->LLP1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        llp = ((uint32_t *) & (dma->LLP2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        llp = ((uint32_t *) & (dma->LLP3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        llp = ((uint32_t *) & (dma->LLP4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        llp = ((uint32_t *) & (dma->LLP5)) + 0;
    }

    *llp = (address >> 2) << 2;
}

FunctionalState DMA_Get_Channel_Interrupt_Enable_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    if ((*ctl0) & DMAC_CTL0_INT_EN_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Channel_Interrupt_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    if (NewState == ENABLE)
    {
        *ctl0 |= DMAC_CTL0_INT_EN_Msk;
    }
    else
    {
        *ctl0 &= ~DMAC_CTL0_INT_EN_Msk;
    }
}

uint32_t DMA_Get_Channel_Destination_Width(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    return (((*ctl0) & DMAC_CTL0_DST_TR_WIDTH_Msk) >> DMAC_CTL0_DST_TR_WIDTH_Pos);
}

void DMA_Set_Channel_Destination_Width(DMA_TypeDef *dma, uint8_t chl, uint32_t width)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_WIDTH(width));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    *ctl0 |= (width << DMAC_CTL0_DST_TR_WIDTH_Pos);
}

uint32_t DMA_Get_Channel_Source_Width(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    return (((*ctl0) & DMAC_CTL0_SRC_TR_WIDTH_Msk) >> DMAC_CTL0_SRC_TR_WIDTH_Pos);
}

void DMA_Set_Channel_Source_Width(DMA_TypeDef *dma, uint8_t chl, uint32_t width)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_WIDTH(width));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    *ctl0 |= (width << DMAC_CTL0_SRC_TR_WIDTH_Pos);
}

uint32_t DMA_Get_Channel_Destination_Address_Increment_way(DMA_TypeDef *dma, uint8_t chl)
{
    uint32_t *ctl0 = NULL;

    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    return (((*ctl0) & DMAC_CTL0_DINC_Msk) >> DMAC_CTL0_DINC_Pos);
}

void DMA_Set_Channel_Destination_Address_Increment_way(DMA_TypeDef *dma, uint8_t chl, uint32_t way)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_ADDR_TYPE(way));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    *ctl0 |= (way << DMAC_CTL0_DINC_Pos);
}

uint32_t DMA_Get_Channel_Source_Address_Increment_way(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    return (((*ctl0) & DMAC_CTL0_SINC_Msk) >> DMAC_CTL0_SINC_Pos);
}

void DMA_Set_Channel_Source_Address_Increment_way(DMA_TypeDef *dma, uint8_t chl, uint32_t way)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_ADDR_TYPE(way));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    *ctl0 |= (way << DMAC_CTL0_SINC_Pos);
}

uint32_t DMA_Get_Channel_Destination_Brust_Size(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    return (((*ctl0) & DMAC_CTL0_DEST_MSIZE_Msk) >> DMAC_CTL0_DEST_MSIZE_Pos);
}

void DMA_Set_Channel_Destination_Brust_Size(DMA_TypeDef *dma, uint8_t chl, uint32_t size)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_MSIZE(size));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    *ctl0 |= (size << DMAC_CTL0_DEST_MSIZE_Pos);
}

uint32_t DMA_Get_Channel_Source_Brust_Size(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    return (((*ctl0) & DMAC_CTL0_SRC_MSIZE_Msk) >> DMAC_CTL0_SRC_MSIZE_Pos);
}

void DMA_Set_Channel_Source_Brust_Size(DMA_TypeDef *dma, uint8_t chl, uint32_t size)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_MSIZE(size));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    *ctl0 |= (size << DMAC_CTL0_SRC_MSIZE_Pos);
}

uint32_t DMA_Get_Channel_Transfer_Type(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    return (((*ctl0) & DMAC_CTL0_TT_FC_Msk) >> DMAC_CTL0_TT_FC_Pos);
}

void DMA_Set_Channel_Transfer_Type(DMA_TypeDef *dma, uint8_t chl, uint32_t type)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_DIRECTION(type));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    *ctl0 |= (type << DMAC_CTL0_TT_FC_Pos);
}

FunctionalState DMA_Get_Channel_Destination_Block_Chain_Enable_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    if ((*ctl0) & DMAC_CTL0_LLP_DST_EN_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Channel_Destination_Block_Chain_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    if (NewState == ENABLE)
    {
        *ctl0 |= DMAC_CTL0_LLP_DST_EN_Msk;
    }
    else
    {
        *ctl0 &= ~DMAC_CTL0_LLP_DST_EN_Msk;
    }
}

FunctionalState DMA_Get_Channel_Source_Block_Chain_Enable_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    if ((*ctl0) & DMAC_CTL0_LLP_SRC_EN_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Channel_Source_Block_Chain_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl0 = ((uint32_t *) & (dma->CTL0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl0 = ((uint32_t *) & (dma->CTL1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl0 = ((uint32_t *) & (dma->CTL2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl0 = ((uint32_t *) & (dma->CTL3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl0 = ((uint32_t *) & (dma->CTL4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl0 = ((uint32_t *) & (dma->CTL5)) + 0;
    }

    if (NewState == ENABLE)
    {
        *ctl0 |= DMAC_CTL0_LLP_SRC_EN_Msk;
    }
    else
    {
        *ctl0 &= ~DMAC_CTL0_LLP_SRC_EN_Msk;
    }
}

void DMA_Set_Channel_Block_Transfer_Size(DMA_TypeDef *dma, uint8_t chl, uint32_t block_size)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *ctl1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        ctl1 = ((uint32_t *) & (dma->CTL0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        ctl1 = ((uint32_t *) & (dma->CTL1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        ctl1 = ((uint32_t *) & (dma->CTL2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        ctl1 = ((uint32_t *) & (dma->CTL3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        ctl1 = ((uint32_t *) & (dma->CTL4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        ctl1 = ((uint32_t *) & (dma->CTL5)) + 1;
    }

    *ctl1 &= ~(0xFF << (DMAC_CTL0_BLOCK_TS_Pos - 32));
    *ctl1 |= (block_size << (DMAC_CTL0_BLOCK_TS_Pos - 32));
}

uint32_t DMA_Get_Channel_Priority(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    return (((*cfg0) & DMAC_CFG0_CH_PRIOR_Msk) >> DMAC_CFG0_CH_PRIOR_Pos);
}

void DMA_Set_Channel_Priority(DMA_TypeDef *dma, uint8_t chl, uint32_t priority)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_PRIORITY(priority));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    *cfg0 |= (priority << DMAC_CFG0_CH_PRIOR_Pos);
}

FunctionalState DMA_Get_Channel_Suspend_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    if ((*cfg0) & DMAC_CFG0_CH_SUSP_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Channel_Suspend_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    if (NewState == ENABLE)
    {
        *cfg0 |= DMAC_CFG0_CH_SUSP_Msk;
    }
    else
    {
        *cfg0 &= ~DMAC_CFG0_CH_SUSP_Msk;
    }
}

FunctionalState DMA_Get_Channel_Fifo_Empty_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    if ((*cfg0) & DMAC_CFG0_FIFO_EMPTY_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

uint32_t DMA_Get_Channel_Destination_Handshake_Type(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    return (((*cfg0) & DMAC_CFG0_HS_SEL_DST_Msk) >> DMAC_CFG0_HS_SEL_DST_Pos);
}

void DMA_Set_Channel_Destination_Handshake_Type(DMA_TypeDef *dma, uint8_t chl, uint32_t type)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_HANDSHAKE_TYPE(type));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    *cfg0 |= (type << DMAC_CFG0_HS_SEL_DST_Pos);
}

uint32_t DMA_Get_Channel_Source_Handshake_Type(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    return (((*cfg0) & DMAC_CFG0_HS_SEL_SRC_Msk) >> DMAC_CFG0_HS_SEL_SRC_Pos);
}

void DMA_Set_Channel_Source_Handshake_Type(DMA_TypeDef *dma, uint8_t chl, uint32_t type)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_HANDSHAKE_TYPE(type));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    *cfg0 |= (type << DMAC_CFG0_HS_SEL_SRC_Pos);
}

uint32_t DMA_Get_Channel_Destination_Handshake_Polarity(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    return (((*cfg0) & DMAC_CFG0_DST_HS_POL_Msk) >> DMAC_CFG0_DST_HS_POL_Pos);
}

void DMA_Set_Channel_Destination_Handshake_Polarity(DMA_TypeDef *dma, uint8_t chl, uint32_t polarity)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_HANDSHAKE_POLARITY(polarity));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    *cfg0 |= (polarity << DMAC_CFG0_DST_HS_POL_Pos);
}

uint32_t DMA_Get_Channel_Source_Handshake_Polarity(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    return (((*cfg0) & DMAC_CFG0_SRC_HS_POL_Msk) >> DMAC_CFG0_SRC_HS_POL_Pos);
}

void DMA_Set_Channel_Source_Handshake_Polarity(DMA_TypeDef *dma, uint8_t chl, uint32_t polarity)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_HANDSHAKE_POLARITY(polarity));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    *cfg0 |= (polarity << DMAC_CFG0_SRC_HS_POL_Pos);
}

void DMA_Set_Channel_Maximum_Brust_Length(DMA_TypeDef *dma, uint8_t chl, uint32_t size)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    *cfg0 |= (size << DMAC_CFG0_MAX_ABRST_Pos);
}

FunctionalState DMA_Get_Channel_Source_Autoreload_Enable_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    if ((*cfg0) & DMAC_CFG0_RELOAD_SRC_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Channel_Source_Autoreload_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    if (NewState == ENABLE)
    {
        *cfg0 |= DMAC_CFG0_RELOAD_SRC_Msk;
    }
    else
    {
        *cfg0 &= ~DMAC_CFG0_RELOAD_SRC_Msk;
    }
}

FunctionalState DMA_Get_Channel_Destination_Autoreload_Enable_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    if ((*cfg0) & DMAC_CFG0_RELOAD_DST_Msk)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Channel_Destination_Autoreload_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg0 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg0 = ((uint32_t *) & (dma->CFG0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg0 = ((uint32_t *) & (dma->CFG1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg0 = ((uint32_t *) & (dma->CFG2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg0 = ((uint32_t *) & (dma->CFG3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg0 = ((uint32_t *) & (dma->CFG4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg0 = ((uint32_t *) & (dma->CFG5)) + 0;
    }

    if (NewState == ENABLE)
    {
        *cfg0 |= DMAC_CFG0_RELOAD_DST_Msk;
    }
    else
    {
        *cfg0 &= ~DMAC_CFG0_RELOAD_DST_Msk;
    }
}

FunctionalState DMA_Get_Channel_Fifo_Mode_Enable_Status(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg1 = ((uint32_t *) & (dma->CFG0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg1 = ((uint32_t *) & (dma->CFG1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg1 = ((uint32_t *) & (dma->CFG2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg1 = ((uint32_t *) & (dma->CFG3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg1 = ((uint32_t *) & (dma->CFG4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg1 = ((uint32_t *) & (dma->CFG5)) + 1;
    }

    if ((*cfg1) & (1 << 1))
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

void DMA_Set_Channel_Fifo_Mode_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg1 = ((uint32_t *) & (dma->CFG0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg1 = ((uint32_t *) & (dma->CFG1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg1 = ((uint32_t *) & (dma->CFG2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg1 = ((uint32_t *) & (dma->CFG3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg1 = ((uint32_t *) & (dma->CFG4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg1 = ((uint32_t *) & (dma->CFG5)) + 1;
    }

    if (NewState == ENABLE)
    {
        *cfg1 |= (1 << 1);
    }
    else
    {
        *cfg1 &= ~(1 << 1);
    }
}

uint32_t DMA_Get_Channel_Source_Handshake_Interface(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg1 = ((uint32_t *) & (dma->CFG0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg1 = ((uint32_t *) & (dma->CFG1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg1 = ((uint32_t *) & (dma->CFG2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg1 = ((uint32_t *) & (dma->CFG3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg1 = ((uint32_t *) & (dma->CFG4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg1 = ((uint32_t *) & (dma->CFG5)) + 1;
    }

    return (((*cfg1) & (1 << 7)) >> (DMAC_CFG0_SRC_PER_Pos - 32));
}

void DMA_Set_Channel_Source_Handshake_Interface(DMA_TypeDef *dma, uint8_t chl, uint32_t interface)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_HARDWARE_PER(interface));

    uint32_t *cfg1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg1 = ((uint32_t *) & (dma->CFG0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg1 = ((uint32_t *) & (dma->CFG1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg1 = ((uint32_t *) & (dma->CFG2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg1 = ((uint32_t *) & (dma->CFG3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg1 = ((uint32_t *) & (dma->CFG4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg1 = ((uint32_t *) & (dma->CFG5)) + 1;
    }

    *cfg1 |= (interface << (DMAC_CFG0_SRC_PER_Pos - 32));
}

uint32_t DMA_Get_Channel_Destination_Handshake_Interface(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    uint32_t *cfg1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg1 = ((uint32_t *) & (dma->CFG0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg1 = ((uint32_t *) & (dma->CFG1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg1 = ((uint32_t *) & (dma->CFG2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg1 = ((uint32_t *) & (dma->CFG3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg1 = ((uint32_t *) & (dma->CFG4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg1 = ((uint32_t *) & (dma->CFG5)) + 1;
    }

    return (((*cfg1) & (1 << 11)) >> (DMAC_CFG0_DEST_PER_Pos - 32));
}

void DMA_Set_Channel_Destination_Handshake_Interface(DMA_TypeDef *dma, uint8_t chl, uint32_t interface)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));
    assert_param(IS_DMA_HARDWARE_PER(interface));

    uint32_t *cfg1 = NULL;

    if (chl == DMA_CHANNEL0)
    {
        cfg1 = ((uint32_t *) & (dma->CFG0)) + 1;
    }
    else if (chl == DMA_CHANNEL1)
    {
        cfg1 = ((uint32_t *) & (dma->CFG1)) + 1;
    }
    else if (chl == DMA_CHANNEL2)
    {
        cfg1 = ((uint32_t *) & (dma->CFG2)) + 1;
    }
    else if (chl == DMA_CHANNEL3)
    {
        cfg1 = ((uint32_t *) & (dma->CFG3)) + 1;
    }
    else if (chl == DMA_CHANNEL4)
    {
        cfg1 = ((uint32_t *) & (dma->CFG4)) + 1;
    }
    else if (chl == DMA_CHANNEL5)
    {
        cfg1 = ((uint32_t *) & (dma->CFG5)) + 1;
    }

    *cfg1 |= (interface << (DMAC_CFG0_DEST_PER_Pos - 32));
}

void DMA_Set_Block_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->MASK_BLOCK)) + 0) = ((((uint32_t)chl) << DMAC_MASKBLOCK_INT_MASK_WE_Pos) | (((uint32_t)chl) << DMAC_MASKBLOCK_INT_MASK_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->MASK_BLOCK)) + 0) = (((uint32_t)chl) << DMAC_MASKBLOCK_INT_MASK_WE_Pos);
    }
}

void DMA_Set_Destination_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->MASK_DSTTRAN)) + 0) = ((((uint32_t)chl) << DMAC_MASKDSTTRAN_INT_MASK_WE_Pos) | (((uint32_t)chl) << DMAC_MASKDSTTRAN_INT_MASK_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->MASK_DSTTRAN)) + 0) = (((uint32_t)chl) << DMAC_MASKDSTTRAN_INT_MASK_WE_Pos);
    }
}

void DMA_Set_Source_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->MASK_SRCTRAN)) + 0) = ((((uint32_t)chl) << DMAC_MASKSRCTRAN_INT_MASK_WE_Pos) | (((uint32_t)chl) << DMAC_MASKSRCTRAN_INT_MASK_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->MASK_SRCTRAN)) + 0) = (((uint32_t)chl) << DMAC_MASKSRCTRAN_INT_MASK_WE_Pos);
    }
}

void DMA_Set_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->MASK_INTTFR)) + 0) = ((((uint32_t)chl) << DMAC_MASKTFR_INT_MASK_WE_Pos) | (((uint32_t)chl) << DMAC_MASKTFR_INT_MASK_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->MASK_INTTFR)) + 0) = (((uint32_t)chl) << DMAC_MASKTFR_INT_MASK_WE_Pos);
    }
}

void DMA_Set_Error_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->MASK_ERR)) + 0) = ((((uint32_t)chl) << DMAC_MASKERR_INT_MASK_WE_Pos) | (((uint32_t)chl) << DMAC_MASKERR_INT_MASK_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->MASK_ERR)) + 0) = (((uint32_t)chl) << DMAC_MASKERR_INT_MASK_WE_Pos);
    }
}

int DMA_Get_Block_Interrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->STA_BLOCK)) + 0);
}

int DMA_Get_Destination_Transfer_Interrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->STA_DSTTRAN)) + 0);
}

int DMA_Get_Source_Transfer_Interrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->STA_SRCTRAN)) + 0);
}

int DMA_Get_Transfer_Interrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->STA_INTTFR)) + 0);
}

int DMA_Get_Error_Interrrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->STA_ERR)) + 0);
}

int DMA_Get_Raw_Block_Interrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->RAW_STA_BLOCK)) + 0);
}

int DMA_Get_Raw_Destination_Transfer_Interrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->RAW_STA_DSTTRAN)) + 0);
}

int DMA_Get_Raw_Source_Transfer_Interrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->RAW_STA_SRCTRAN)) + 0);
}

int DMA_Get_Raw_Transfer_Interrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->RAW_STA_INTTFR)) + 0);
}

int DMA_Get_Raw_Error_Interrrupt_Status(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    return *(((uint32_t *) & (dma->RAW_STA_ERR)) + 0);
}

void DMA_Clear_Block_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    *(((uint32_t *) & (dma->CLR_STA_BLOCK)) + 0) |= chl;
}

void DMA_Clear_Destination_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    *(((uint32_t *) & (dma->CLR_STA_DSTTRAN)) + 0) |= chl;
}

void DMA_Clear_Source_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    *(((uint32_t *) & (dma->CLR_STA_SRCTRAN)) + 0) |= chl;
}

void DMA_Clear_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    *(((uint32_t *) & (dma->CLR_STA_TFR)) + 0) |= chl;
}

void DMA_Clear_Error_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    *(((uint32_t *) & (dma->CLR_STA_ERR)) + 0) |= chl;
}

void DMA_Clear_All_Interrupt_Cmd(DMA_TypeDef *dma)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    *(((uint32_t *) & (dma->CLR_STA_BLOCK)) + 0) |= 0x3f;
    *(((uint32_t *) & (dma->CLR_STA_DSTTRAN)) + 0) |= 0x3f;
    *(((uint32_t *) & (dma->CLR_STA_ERR)) + 0) |= 0x3f;
    *(((uint32_t *) & (dma->CLR_STA_SRCTRAN)) + 0) |= 0x3f;
    *(((uint32_t *) & (dma->CLR_STA_TFR)) + 0) |= 0x3f;
}

void DMA_Set_Channel_Source_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->REQ_SRC)) + 0) = ((((uint32_t)chl) << DMAC_REQSRCREG_SRC_REQ_WE_Pos) | (((uint32_t)chl) << DMAC_REQSRCREG_SRC_REQ_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->REQ_SRC)) + 0) = (((uint32_t)chl) << DMAC_REQSRCREG_SRC_REQ_WE_Pos);
    }
}

void DMA_Set_Channel_Destination_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->REQ_DST)) + 0) = ((((uint32_t)chl) << DMAC_REQDSTREG_DST_REQ_WE_Pos) | (((uint32_t)chl) << DMAC_REQDSTREG_DST_REQ_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->REQ_DST)) + 0) = (((uint32_t)chl) << DMAC_REQDSTREG_DST_REQ_WE_Pos);
    }
}

void DMA_Set_Channel_Single_Source_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->SGL_REQ_SRC)) + 0) = ((((uint32_t)chl) << DMAC_SGLREQSRCREG_SRC_SGLREQ_WE_Pos) | (((uint32_t)chl) << DMAC_SGLREQSRCREG_SRC_SGLREQ_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->SGL_REQ_SRC)) + 0) = (((uint32_t)chl) << DMAC_SGLREQSRCREG_SRC_SGLREQ_WE_Pos);
    }
}

void DMA_Set_Channel_Single_Destination_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->SGL_REQ_DST)) + 0) = ((((uint32_t)chl) << DMAC_SGLREQDSTREG_DST_SGLREQ_WE_Pos) | (((uint32_t)chl) << DMAC_SGLREQDSTREG_DST_SGLREQ_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->SGL_REQ_DST)) + 0) = (((uint32_t)chl) << DMAC_SGLREQDSTREG_DST_SGLREQ_WE_Pos);
    }
}

void DMA_Set_Channel_Last_Source_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->LST_SRC)) + 0) = ((((uint32_t)chl) << DMAC_LSTSRCREG_LSTSRC_WE_Pos) | (((uint32_t)chl) << DMAC_LSTSRCREG_LSTSRC_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->LST_SRC)) + 0) = (((uint32_t)chl) << DMAC_LSTSRCREG_LSTSRC_WE_Pos);
    }
}

void DMA_Set_Channel_Last_Destination_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState)
{
    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));
    assert_param(IS_DMA_CHANNEL(chl));

    if (NewState == ENABLE)
    {
        *(((uint32_t *) & (dma->LST_DST)) + 0) = ((((uint32_t)chl) << DMAC_LSTDSTREG_LSTDST_WE_Pos) | (((uint32_t)chl) << DMAC_LSTDSTREG_LSTDST_Pos));
    }
    else
    {
        *(((uint32_t *) & (dma->LST_DST)) + 0) = (((uint32_t)chl) << DMAC_LSTDSTREG_LSTDST_WE_Pos);
    }
}

void DMA_Set_Addr(DMA_TypeDef *dma, uint8_t chl, uint32_t src_addr, uint32_t dst_addr, uint8_t block_size, uint32_t llp_addr)
{
    uint32_t *src = NULL, *dst = NULL, *ctl1 = NULL, *llp = NULL;

    assert_param(dma != NULL);
    assert_param(IS_DMA_ALL_INSTANCE(dma));

    if (chl == DMA_CHANNEL0)
    {
        src = ((uint32_t *) & (dma->SAR0)) + 0;
        dst = ((uint32_t *) & (dma->DAR0)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL0)) + 1;
        llp = ((uint32_t *) & (dma->LLP0)) + 0;
    }
    else if (chl == DMA_CHANNEL1)
    {
        src = ((uint32_t *) & (dma->SAR1)) + 0;
        dst = ((uint32_t *) & (dma->DAR1)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL1)) + 1;
        llp = ((uint32_t *) & (dma->LLP1)) + 0;
    }
    else if (chl == DMA_CHANNEL2)
    {
        src = ((uint32_t *) & (dma->SAR2)) + 0;
        dst = ((uint32_t *) & (dma->DAR2)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL2)) + 1;
        llp = ((uint32_t *) & (dma->LLP2)) + 0;
    }
    else if (chl == DMA_CHANNEL3)
    {
        src = ((uint32_t *) & (dma->SAR3)) + 0;
        dst = ((uint32_t *) & (dma->DAR3)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL3)) + 1;
        llp = ((uint32_t *) & (dma->LLP3)) + 0;
    }
    else if (chl == DMA_CHANNEL4)
    {
        src = ((uint32_t *) & (dma->SAR4)) + 0;
        dst = ((uint32_t *) & (dma->DAR4)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL4)) + 1;
        llp = ((uint32_t *) & (dma->LLP4)) + 0;
    }
    else if (chl == DMA_CHANNEL5)
    {
        src = ((uint32_t *) & (dma->SAR5)) + 0;
        dst = ((uint32_t *) & (dma->DAR5)) + 0;
        ctl1 = ((uint32_t *) & (dma->CTL5)) + 1;
        llp = ((uint32_t *) & (dma->LLP5)) + 0;
    }

    *src = src_addr;
    *dst = dst_addr;
    *ctl1 = block_size;
    *llp = (llp_addr >> 2) << 2;
}
