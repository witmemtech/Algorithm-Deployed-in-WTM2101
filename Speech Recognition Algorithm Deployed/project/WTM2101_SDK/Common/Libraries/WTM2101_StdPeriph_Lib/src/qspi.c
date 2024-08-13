/**
  ******************************************************************************  
  * @file    qspi.c
  * @brief   The Source Codes for the QSPI Functions
  * @version V1.0.0.1
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************  
  */

/* Includes */
#include "qspi.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")

void QSPI_Ctl_Init(QSPI_TypeDef* QSPIx, QSPI_CtlInitTypeDef* QSPI_InitStruct)
{  
    assert_param(QSPIx != NULL && QSPI_InitStruct != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_SAMPLE_CLOCK(QSPI_InitStruct->sample_clk_sel));
    assert_param(IS_QSPI_ALTERNATEBYTESIZE(QSPI_InitStruct->alternatebytessize));
    assert_param(IS_QSPI_ADDRESSSIZE(QSPI_InitStruct->addresssize));
    assert_param(IS_QSPI_WRITE_READ_DATA_MODE(QSPI_InitStruct->dmode_sel));
    assert_param(IS_QSPI_DATAMODE(QSPI_InitStruct->datamode));
    assert_param(IS_QSPI_ALTERNATEBYTEMODE(QSPI_InitStruct->alternatebytemode));
    assert_param(IS_QSPI_ADDRESSMODE(QSPI_InitStruct->addressmode));
    assert_param(IS_QSPI_INSTRUCTIONMODE(QSPI_InitStruct->instructionmode));
    assert_param(IS_QSPI_SPH(QSPI_InitStruct->sph));
    assert_param(IS_QSPI_SPO(QSPI_InitStruct->spo));

    QSPIx->QSPI_CTRL = (QSPI_InitStruct->spo << 0) | (QSPI_InitStruct->sph << 1) | (QSPI_InitStruct->instructionmode << 2) | (QSPI_InitStruct->addressmode << 4) |
        (QSPI_InitStruct->alternatebytemode << 6) | (QSPI_InitStruct->datamode << 8) | (QSPI_InitStruct->dmode_sel << 10) |
        (QSPI_InitStruct->dummy_cycle << 11) | (QSPI_InitStruct->addresssize << 16) | (QSPI_InitStruct->alternatebytessize << 18) |
        (QSPI_InitStruct->read_delay_time << 20) | (QSPI_InitStruct->sample_clk_sel << 22);
}

void QSPI_Ctl_Uninit(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_CTRL = 0;
}

uint8_t QSPI_Get_Send_Dma_WaterLevel(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->DMA_CTRL & QSPI_DMA_CTRL_WR_WATER_LEVEL_Msk) >> QSPI_DMA_CTRL_WR_WATER_LEVEL_Pos);
}

uint8_t QSPI_Get_Receive_Dma_WaterLevel(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->DMA_CTRL & QSPI_DMA_CTRL_RD_WATER_LEVEL_Msk) >> QSPI_DMA_CTRL_RD_WATER_LEVEL_Pos);
}

void QSPI_Set_Send_Dma_Cmd(QSPI_TypeDef* QSPIx, uint8_t water_level, FunctionalState NewState)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->DMA_CTRL &= ~(QSPI_DMA_CTRL_QSPI_WRITE_EN_Msk | QSPI_DMA_CTRL_WR_WATER_LEVEL_Msk);
    if (NewState == ENABLE)
    {
        QSPIx->DMA_CTRL |= (water_level << QSPI_DMA_CTRL_WR_WATER_LEVEL_Pos);
        QSPIx->DMA_CTRL |= QSPI_DMA_CTRL_QSPI_WRITE_EN_Msk;
    }
}

void QSPI_Set_Receive_Dma_Cmd(QSPI_TypeDef* QSPIx, uint8_t water_level, FunctionalState NewState)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->DMA_CTRL &= ~(QSPI_DMA_CTRL_QSPI_READ_EN_Msk | QSPI_DMA_CTRL_RD_WATER_LEVEL_Msk);
   
    if (NewState == ENABLE)
    {
        QSPIx->DMA_CTRL |= (water_level << QSPI_DMA_CTRL_RD_WATER_LEVEL_Pos);
        QSPIx->DMA_CTRL |= QSPI_DMA_CTRL_QSPI_READ_EN_Msk;
    }
}

void QSPI_Set_Dma_Cmd(QSPI_TypeDef* QSPIx, QSPI_DmaInitTypeDef *QSPI_DmaInitStruct)
{
    assert_param(QSPIx != NULL && QSPI_DmaInitStruct != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
  
    QSPIx->DMA_CTRL &= ~(QSPI_DMA_CTRL_QSPI_WRITE_EN_Msk | QSPI_DMA_CTRL_WR_WATER_LEVEL_Msk | QSPI_DMA_CTRL_QSPI_READ_EN_Msk | QSPI_DMA_CTRL_RD_WATER_LEVEL_Msk);
    QSPIx->DMA_CTRL = (QSPI_DmaInitStruct->read_en << QSPI_DMA_CTRL_QSPI_READ_EN_Pos) | (QSPI_DmaInitStruct->write_en << QSPI_DMA_CTRL_QSPI_WRITE_EN_Pos) | \
                      (QSPI_DmaInitStruct->rd_water_level << QSPI_DMA_CTRL_RD_WATER_LEVEL_Pos) | (QSPI_DmaInitStruct->wr_water_level << QSPI_DMA_CTRL_WR_WATER_LEVEL_Pos);
}

uint16_t QSPI_Get_Spo(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_SPO_Msk) >> QSPI_QSPI_CTRL_SPO_Pos);
}

void QSPI_Set_Spo(QSPI_TypeDef* QSPIx, uint16_t spo)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_SPO(spo));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_SPO_Msk;
    QSPIx->QSPI_CTRL |= (spo << QSPI_QSPI_CTRL_SPO_Pos);
}

uint16_t QSPI_Get_Sph(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_SPH_Msk) >> QSPI_QSPI_CTRL_SPH_Pos);
}

void QSPI_Set_Sph(QSPI_TypeDef* QSPIx, uint16_t sph)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_SPH(sph));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_SPH_Msk;
    QSPIx->QSPI_CTRL |= (sph << QSPI_QSPI_CTRL_SPH_Pos);
}

uint16_t QSPI_Get_Instruction_Mode(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_IMODE_Msk) >> QSPI_QSPI_CTRL_IMODE_Pos);
}

void QSPI_Set_Instruction_Mode(QSPI_TypeDef* QSPIx, uint16_t mode)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_INSTRUCTIONMODE(mode));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_IMODE_Msk;
    QSPIx->QSPI_CTRL |= (mode << QSPI_QSPI_CTRL_IMODE_Pos);
}

uint16_t QSPI_Get_Address_Mode(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_ADMODE_Msk) >> QSPI_QSPI_CTRL_ADMODE_Pos);
}

void QSPI_Set_Address_Mode(QSPI_TypeDef* QSPIx, uint16_t mode)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_ADDRESSMODE(mode));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_ADMODE_Msk;
    QSPIx->QSPI_CTRL |= (mode << QSPI_QSPI_CTRL_ADMODE_Pos);
}

uint16_t QSPI_Get_Alternatebyte_Mode(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_ALMODE_Msk) >> QSPI_QSPI_CTRL_ALMODE_Pos);
}

void QSPI_Set_Alternatebyte_Mode(QSPI_TypeDef* QSPIx, uint16_t mode)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_ALTERNATEBYTEMODE(mode));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_ALMODE_Msk;
    QSPIx->QSPI_CTRL |= (mode << QSPI_QSPI_CTRL_ALMODE_Pos);
}

uint16_t QSPI_Get_Data_Mode(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_DMODE_Msk) >> QSPI_QSPI_CTRL_DMODE_Pos);
}

void QSPI_Set_Data_Mode(QSPI_TypeDef* QSPIx, uint16_t mode)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_DATAMODE(mode));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_DMODE_Msk;
    QSPIx->QSPI_CTRL |= (mode << QSPI_QSPI_CTRL_DMODE_Pos);
}

uint16_t QSPI_Get_Read_Or_Write_Mode(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_DMODE_SEL_Msk) >> QSPI_QSPI_CTRL_DMODE_SEL_Pos);
}

void QSPI_Set_Read_Or_Write_Mode(QSPI_TypeDef* QSPIx, uint8_t mode)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_WRITE_READ_DATA_MODE(mode));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_DMODE_SEL_Msk;
    QSPIx->QSPI_CTRL |= (mode << QSPI_QSPI_CTRL_DMODE_SEL_Pos);
}

uint16_t QSPI_Get_Dummy_cycle(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_DUMMY_CYCLE_Msk) >> QSPI_QSPI_CTRL_DUMMY_CYCLE_Pos);
}

void QSPI_Set_Dummy_cycle(QSPI_TypeDef* QSPIx, uint8_t cycle)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_DUMMY_CYCLE_Msk;
    QSPIx->QSPI_CTRL |= (cycle << QSPI_QSPI_CTRL_DUMMY_CYCLE_Pos);
}

uint16_t QSPI_Get_Address_Size(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_ADSIZE_Msk) >> QSPI_QSPI_CTRL_ADSIZE_Pos);
}

void QSPI_Set_Address_Size(QSPI_TypeDef* QSPIx, uint16_t size)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_ADDRESSSIZE(size));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_ADSIZE_Msk;
    QSPIx->QSPI_CTRL |= (size << QSPI_QSPI_CTRL_ADSIZE_Pos);
}

uint16_t QSPI_Get_Alternatebyte_Size(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_ALSIZE_Msk) >> QSPI_QSPI_CTRL_ALSIZE_Pos);
}

void QSPI_Set_Alternatebyte_Size(QSPI_TypeDef* QSPIx, uint16_t size)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_ALTERNATEBYTESIZE(size));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_ALSIZE_Msk;
    QSPIx->QSPI_CTRL |= (size << QSPI_QSPI_CTRL_ALSIZE_Pos);
}

uint16_t QSPI_Get_Read_Delay_Time(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_READ_DELAY_TIME_Msk) >> QSPI_QSPI_CTRL_READ_DELAY_TIME_Pos);
}

void QSPI_Set_Read_Delay_Time(QSPI_TypeDef* QSPIx, uint16_t delay_time)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_READ_DELAY_TIME_Msk;
    QSPIx->QSPI_CTRL |= (delay_time << QSPI_QSPI_CTRL_READ_DELAY_TIME_Pos);
}

uint16_t QSPI_Get_Sample_Clk(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return ((QSPIx->QSPI_CTRL & QSPI_QSPI_CTRL_SAMPLE_CLK_SEL_Msk) >> QSPI_QSPI_CTRL_SAMPLE_CLK_SEL_Pos);
}

void QSPI_Set_Sample_Clk(QSPI_TypeDef* QSPIx, uint16_t clk)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_SAMPLE_CLOCK(clk));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_SAMPLE_CLK_SEL_Msk;
    QSPIx->QSPI_CTRL |= (clk << QSPI_QSPI_CTRL_SAMPLE_CLK_SEL_Pos);
} 

uint8_t QSPI_Get_Instrction(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return QSPIx->QSPI_INS;
}

void QSPI_Set_Instrction(QSPI_TypeDef* QSPIx, uint8_t instrction)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_INS = instrction;
}

uint32_t QSPI_Get_Address(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return QSPIx->QSPI_ADDR;
}

void QSPI_Set_Address(QSPI_TypeDef* QSPIx, uint32_t address)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_ADDR = address;
}

uint32_t QSPI_Get_Alternatebyte(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return QSPIx->QSPI_ALTER;

}

void QSPI_Set_Alternatebyte(QSPI_TypeDef* QSPIx, uint32_t alternatebyte)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_ALTER = alternatebyte;
}

uint32_t QSPI_Get_Data_Length(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return QSPIx->QSPI_DATA_NUM + 1;

}

void QSPI_Set_Data_Length(QSPI_TypeDef* QSPIx,uint32_t length)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_DATA_NUM = length - 1;
}

void QSPI_Set_Polling_Configurationo(QSPI_TypeDef* QSPIx, uint8_t mask_value, uint8_t match_value)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->POLLING_REG = (match_value << 0) | (mask_value << 8);
}

uint8_t QSPI_Get_Afifo_Status(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return QSPIx->AFIFO_STATUS;

}

uint8_t QSPI_Get_Status(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return QSPIx->QSPI_STATUS;
}

void QSPI_Set_Int_Mask(QSPI_TypeDef* QSPIx, uint8_t int_type)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_INT_TYPE(int_type));

    QSPIx->INT_MASK_SET |= int_type;
}

void QSPI_Clear_Int_Mask(QSPI_TypeDef* QSPIx, uint8_t int_type)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_INT_TYPE(int_type));

    QSPIx->INT_MASK_CLR |= int_type;
}

uint8_t QSPI_Get_Int_Mask_Status(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return QSPIx->INT_MASK_STATUS;
}

uint8_t QSPI_Get_Int_Pending_Status(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    return QSPIx->INT_SR_PENDING;
}

void QSPI_Clear_Int_Pending_Cmd(QSPI_TypeDef* QSPIx, uint8_t int_type)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    assert_param(IS_QSPI_INT_TYPE(int_type));

    QSPIx->INT_SR_PENDING |= int_type;
}

void QSPI_Set_Stop_Cmd(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_JUMP_TO_STOP_Msk;
}

void QSPI_Set_MemoryMapMode_Command_Switch_Cmd(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_MAPPING_CONF_UPDATE_Msk;
}

void QSPI_Set_MemoryMapMode_1line_Or_4lines_Cmd(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->MAPPING_ACT = QSPI_MAPPING_ACT_MAPPING_ACT_Msk;
}

void QSPI_Set_Polling_Mode_Cmd(QSPI_TypeDef* QSPIx, uint8_t polling_config_updata)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    if (polling_config_updata)
        QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_POLLING_CONF_UPDATE_Msk;
    QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_POLLING_ACT_Msk;
}

void QSPI_Set_Start_Cmd(QSPI_TypeDef* QSPIx)
{
    assert_param(QSPIx != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_INDIRECT_ACT_Msk;
}

int QSPI_Transimit(QSPI_TypeDef* QSPIx, uint32_t *data, int length_bytes)
{
    int send_len = 0,index = 0,flag = 0;
    assert_param(QSPIx != NULL);
    assert_param(data != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_DMODE_SEL_Msk;
    QSPIx->QSPI_DATA_NUM = length_bytes - 1;
    
    for (send_len = 0;send_len< length_bytes;)
    { 
        if (!(QSPIx->AFIFO_STATUS & QSPI_WRITE_AFIFO_FULL))
        {   /* writing the data until the fifo is full */   
            QSPIx->AFIFO_WDATA = data[index];
            index++;
            send_len += 4;
        }
        else
        {   /* starting sending the data when the fifo is full */
            if (!flag)
            {
                flag = 1;
                QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_INDIRECT_ACT_Msk;
            }
        }
    }
    /* starting sending the data when the fifo is always not full */
    if (!flag)
    {
        QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_INDIRECT_ACT_Msk;
    }
    /* waiting */
    while (!(QSPIx->AFIFO_STATUS & QSPI_WRITE_AFIFO_EMPTY));

    return length_bytes;
} 

int QSPI_Receive(QSPI_TypeDef* QSPIx, uint32_t *data, int length_bytes)
{
    int send_len = 0,index = 0;
    assert_param(QSPIx != NULL);
    assert_param(data != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    
    QSPIx->QSPI_CTRL |= QSPI_QSPI_CTRL_DMODE_SEL_Msk;
    QSPIx->QSPI_DATA_NUM = length_bytes - 1;
    QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_INDIRECT_ACT_Msk;

    for (send_len = 0;send_len< length_bytes;)
    { 
        if (!(QSPIx->AFIFO_STATUS & QSPI_READ_AFIFO_EMPTY))
        {   
            /* reading the data when the fifo is not empty */  
            data[index]=QSPIx->AFIFO_RDATA;
            index++;
            send_len += 4;
        }
    }

    return length_bytes;
} 

int QSPI_Dma_Transimit(QSPI_TypeDef* QSPIx, uint32_t *data, int length_bytes, uint8_t dma_channel)
{
    int index_size = 0,block_size = 0,total_size = 0,flag = 0;
    assert_param(QSPIx != NULL);
    assert_param(data != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));

    QSPIx->QSPI_CTRL &= ~QSPI_QSPI_CTRL_DMODE_SEL_Msk;
    QSPIx->QSPI_DATA_NUM = length_bytes - 1;
    
    total_size = length_bytes;
    while (total_size > 0)
    { 
        block_size = total_size > 32 ? 32 :total_size;
        total_size -= block_size;
        block_size = (block_size == 32) ? 8 : block_size / 4 + 1; 
        DMA_Set_Addr(DMA, dma_channel, (uint32_t)(data+index_size), (uint32_t)&(QSPIx->AFIFO_WDATA), block_size, 0);
        DMA_Set_Channel_Enable_Cmd(DMA, dma_channel, ENABLE);
        if (!flag)
        {
            flag = 1;
            QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_INDIRECT_ACT_Msk;
        }
        while (!(QSPIx->AFIFO_STATUS & QSPI_WRITE_AFIFO_EMPTY));
        index_size+=block_size;
    }
    while (!(QSPIx->AFIFO_STATUS & QSPI_WRITE_AFIFO_EMPTY));

    return length_bytes;
} 

int QSPI_Dma_Receive(QSPI_TypeDef* QSPIx, uint32_t *data, int length_bytes, uint8_t dma_channel)
{
    int block_size = 0;
    assert_param(QSPIx != NULL);
    assert_param(data != NULL);
    assert_param(IS_QSPI_ALL_INSTANCE(QSPIx));
    
    QSPIx->QSPI_CTRL |= QSPI_QSPI_CTRL_DMODE_SEL_Msk;
    QSPIx->QSPI_DATA_NUM = length_bytes - 1;
    QSPIx->QSPI_PULSE = QSPI_QSPI_PULSE_INDIRECT_ACT_Msk;

    block_size = length_bytes % 4 ? length_bytes / 4 + 1 : length_bytes / 4; 
    DMA_Set_Addr(DMA, dma_channel, (uint32_t)&(QSPIx->AFIFO_RDATA), (uint32_t)data, block_size, 0);
    DMA_Set_Channel_Enable_Cmd(DMA, dma_channel, ENABLE);
    while (!(QSPIx->AFIFO_STATUS & QSPI_READ_AFIFO_EMPTY));

    return length_bytes;
} 

#pragma GCC pop_options
