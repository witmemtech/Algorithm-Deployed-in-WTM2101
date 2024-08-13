/**
  ******************************************************************************
  * @file    spi.c
  * @brief   The Source Codes for the SPI Functions
  * @version V1.0.0.0
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes */
#include "spi.h"

void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
    assert_param(SPIx != ((void *)0) && SPI_InitStruct != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->datasize));
    assert_param(IS_SPI_CPOL(SPI_InitStruct->cpol));
    assert_param(IS_SPI_CPHA(SPI_InitStruct->cpha));
    assert_param(IS_SPI_NSS(SPI_InitStruct->nss));

    /*the value of register init*/
    SPIx->CTRLR0 &= ~SPI_CTRLR0_DFS_32_Msk;
    SPIx->CTRLR0 |= (SPI_InitStruct->datasize << SPI_CTRLR0_DFS_32_Pos);

    if (SPI_InitStruct->cpha == SPI_CPHA_1)
    {
        SPIx->CTRLR0 |= SPI_CTRLR0_SCPH_Msk;
    }
    else
    {
        SPIx->CTRLR0 &= ~SPI_CTRLR0_SCPH_Msk;
    }

    if (SPI_InitStruct->cpol == SPI_CPOL_1)
    {
        SPIx->CTRLR0 |= SPI_CTRLR0_SCPOL_Msk;
    }
    else
    {
        SPIx->CTRLR0 &= ~SPI_CTRLR0_SCPOL_Msk;
    }

    SPIx->BAUDR = SPI_InitStruct->clk_div;
    SPIx->SER &= ~SPI_SER_SER_Msk;

    if (SPI_InitStruct->nss == SPI_HARDWARE_NSS0)
    {
        SPIx->SER |= (0x01 << SPI_SER_SER_Pos);
    }
    else if (SPI_InitStruct->nss == SPI_HARDWARE_NSS1)
    {
        SPIx->SER |= (0x02 << SPI_SER_SER_Pos);
    }
    else if (SPI_InitStruct->nss == SPI_HARDWARE_NSS2)
    {
        SPIx->SER |= (0x04 << SPI_SER_SER_Pos);
    }
    else if (SPI_InitStruct->nss == SPI_SOFTWARE_NSS)
    {
        SPIx->SER |= (0x01 << SPI_SER_SER_Pos);
    }
}

void SPI_Uninit(SPI_TypeDef* SPIx)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    SPIx->SSIENR = 0;

    if (SPIx == SPIM)
    {
        RCC_Peri_Rst(RCC_SPIM_RSTN);
    }
    else if (SPIx == SPIS)
    {
        RCC_Peri_Rst(RCC_SPIS_RSTN);
    }
}

void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->SSIENR = 1;
    }
    else
    {
        SPIx->SSIENR = 0;
    }
}

void SPI_Nss_Cmd(SPI_TypeDef* SPIx, uint8_t nss, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (nss == SPI_HARDWARE_NSS0)
    {
        if (ENABLE == NewState)
        {
            SPIx->SER |= (0x01 << SPI_SER_SER_Pos);
        }
        else
        {
            SPIx->SER &= ~(0x01 << SPI_SER_SER_Pos);
        }
    }
    else if (nss == SPI_HARDWARE_NSS1)
    {
        if (ENABLE == NewState)
        {
            SPIx->SER |= (0x02 << SPI_SER_SER_Pos);
        }
        else
        {
            SPIx->SER &= ~(0x02 << SPI_SER_SER_Pos);
        }
    }
    else if (nss == SPI_HARDWARE_NSS2)
    {
        if (ENABLE == NewState)
        {
            SPIx->SER |= (0x04 << SPI_SER_SER_Pos);
        }
        else
        {
            SPIx->SER &= ~(0x04 << SPI_SER_SER_Pos);
        }
    }
}

void SPI_Set_Mode(SPI_TypeDef* SPIx, uint8_t mode)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    SPIx->CTRLR0 &= ~(3 << 8);
    if (mode == SPI_SEND_AND_RECEIVE_MODE)
    {
    }
    else if (mode == SPI_ONLY_SEND_MODE)
    {
        SPIx->CTRLR0 |= 1 << SPI_CTRLR0_TMOD_Pos;
    }
    else if (mode == SPI_ONLY_RECEIVE_MODE)
    {
        SPIx->CTRLR0 |= 2 << SPI_CTRLR0_TMOD_Pos;
    }
}

void SPI_Set_Loopback(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->CTRLR0 |= SPI_CTRLR0_SRL_Msk;
    }
    else
    {
        SPIx->CTRLR0 &= ~SPI_CTRLR0_SRL_Msk;
    }
}

void SPI_Set_Tx_Fifo_Threshold(SPI_TypeDef* SPIx, int value)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    SPIx->TXFTLR = value;
}

void SPI_Set_Rx_Fifo_Threshold(SPI_TypeDef* SPIx, int value)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    SPIx->RXFTLR = value;
}

int SPI_Get_Tx_Fifo_level(SPI_TypeDef* SPIx)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    return SPIx->TXFLR;
}

int SPI_Get_Rx_Fifo_level(SPI_TypeDef* SPIx)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    return SPIx->RXFLR;
}

int SPI_Get_Status_Cmd(SPI_TypeDef* SPIx)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    return SPIx->SR;
}

void SPI_Set_Tx_Fifo_Empty_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->IMR |= SPI_IMR_TXEIM_Msk;
    }
    else
    {
        SPIx->IMR &= ~SPI_IMR_TXEIM_Msk;
    }
}

void SPI_Set_Tx_Fifo_Overflow_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->IMR |= SPI_IMR_TXOIM_Msk;
    }
    else
    {
        SPIx->IMR &= ~SPI_IMR_TXOIM_Msk;
    }
}

void SPI_Set_Rx_Fifo_Underflow_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->IMR |= SPI_IMR_RXUIM_Msk;
    }
    else
    {
        SPIx->IMR &= ~SPI_IMR_RXUIM_Msk;
    }
}

void SPI_Set_Rx_Fifo_Overflow_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->IMR |= SPI_IMR_RXOIM_Msk;
    }
    else
    {
        SPIx->IMR &= ~SPI_IMR_RXOIM_Msk;
    }
}

void SPI_Set_Rx_Fifo_Full_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->IMR |= SPI_IMR_RXFIM_Msk;
    }
    else
    {
        SPIx->IMR &= ~SPI_IMR_RXFIM_Msk;
    }
}

void SPI_Set_Mutli_Master_Contention_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->IMR |= SPI_IMR_MSTIM_Msk;
    }
    else
    {
        SPIx->IMR &= ~SPI_IMR_MSTIM_Msk;
    }
}

int SPI_Get_Interrupt_Status(SPI_TypeDef* SPIx)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    return SPIx->ISR;
}

void SPI_Clear_Tx_Fifo_Overflow_Interrupt(SPI_TypeDef* SPIx)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    uint8_t temp = 0;

    temp = SPIx->TXOICR;
}

void SPI_Clear_Rx_Fifo_Overflow_Interrupt(SPI_TypeDef* SPIx)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    uint8_t temp = 0;

    temp = SPIx->RXOICR;
}

void SPI_Clear_Rx_Fifo_Underflow_Interrupt(SPI_TypeDef* SPIx)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    uint8_t temp = 0;

    temp = SPIx->RXUICR;
}

void SPI_Dma_Receive_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->DMACR |= SPI_DMACR_RDMAE_Msk;
    }
    else
    {
        SPIx->DMACR &= ~SPI_DMACR_RDMAE_Msk;
    }
}

void SPI_Dma_Send_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    if (ENABLE == NewState)
    {
        SPIx->DMACR |= SPI_DMACR_TDMAE_Msk;
    }
    else
    {
        SPIx->DMACR &= ~SPI_DMACR_TDMAE_Msk;
    }
}

void SPI_Set_Dma_Transmit_Data_level(SPI_TypeDef* SPIx, int level)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    SPIx->DMATDLR = level;
}

void SPI_Set_Dma_Receive_Data_level(SPI_TypeDef* SPIx, int level)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    SPIx->DMARDLR = level;
}

int SPI_Send(SPI_TypeDef* SPIx, uint8_t size, void *sendbuffer, uint32_t sendbuffer_length)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    int send_index = 0;
    int receive_index = 0;
    int unvalid_data = 0;
    int ret = 0;
    uint8_t reg_ser = 0;

    if (SPIx == SPIM)
    {
        /*waiting when spim is busy*/
        while (SPIx->SR & SPI_BUSY);

        reg_ser = SPIx->SER;
        SPIx->SER = 0;

        for (send_index = 0; send_index < sendbuffer_length; )
        {
            if(SPIx->SR & SPI_TRANSMIT_FIFO_NOT_FULL)
            {
                /*writing the data until the fifo is full*/
                if (size == 1)
                {
                    SPIx->DR = ((uint8_t *)sendbuffer)[send_index];
                }
                else if (size == 2)
                {
                    SPIx->DR = ((uint16_t *)sendbuffer)[send_index];
                }
                else if(size == 4)
                {
                    SPIx->DR = ((uint32_t *)sendbuffer)[send_index];
                }

                send_index++;
            }
            else
            {   /*starting sending the data when the fifo is full*/
                SPIx->SER = reg_ser;
            }
        }

        SPIx->SER = reg_ser;

        while (!(SPIx->SR & SPI_TRANSMIT_FIFO_EMPTY));
        while (SPIx->SR & SPI_BUSY);

        ret = send_index;
    }
    else if (SPIx == SPIS)
    {
        if (sendbuffer_length)
        {
            for (send_index = 0; send_index < sendbuffer_length; send_index++)
            {
                if (size == 1)
                {
                    SPIx->DR = ((uint8_t *)sendbuffer)[send_index];
                }
                else if (size == 2)
                {
                    SPIx->DR = ((uint16_t *)sendbuffer)[send_index];
                }
                else if (size == 4)
                {
                    SPIx->DR = ((uint32_t *)sendbuffer)[send_index];
                }
            }

            ret = send_index;
        }
    }
}

int SPI_Send_Receive(SPI_TypeDef* SPIx, uint8_t size, void *sendbuffer, uint32_t sendbuffer_length, void *receivebuffer, uint32_t receivebuffer_length)
{
    assert_param(SPIx != ((void *)0));
    assert_param(IS_SPI_ALL_INSTANCE(SPIx));

    int send_index = 0;
    int receive_index = 0;
    int unvalid_data = 0;
    int ret = 0;
    uint8_t reg_ser = 0;

    if (SPIx == SPIM)
    {
        /*waiting when spim is busy*/
        while (SPIx->SR & SPI_BUSY);

        reg_ser = SPIx->SER;
        SPIx->SER = 0;

        if(receivebuffer_length == 0)
        {
            for (send_index = 0; send_index < sendbuffer_length; )
            {
                if (SPIx->SR & SPI_TRANSMIT_FIFO_NOT_FULL)
                {
                    /*writing the data until the fifo is full*/
                    if (size == 1)
                    {
                        SPIx->DR = ((uint8_t *)sendbuffer)[send_index];
                    }
                    else if (size == 2)
                    {
                        SPIx->DR = ((uint16_t *)sendbuffer)[send_index];
                    }
                    else if (size == 4)
                    {
                        SPIx->DR = ((uint32_t *)sendbuffer)[send_index];
                    }

                    send_index++;
                }
                else
                {   /*starting sending the data when the fifo is full*/
                    SPIx->SER = reg_ser;
                }
            }

            SPIx->SER = reg_ser;

            while (!(SPIx->SR & SPI_TRANSMIT_FIFO_EMPTY));
            while (SPIx->SR & SPI_BUSY);

            /*clear receive fifo*/
            SPIx->SSIENR = 0;
            SPIx->SSIENR = 1;

            ret = send_index;
        }
        else
        {
            for (send_index = 0; send_index < receivebuffer_length; )
            {
                if (SPIx->SR & SPI_TRANSMIT_FIFO_NOT_FULL)
                {
                    /*writing the data until the fifo is full*/
                    if (sendbuffer_length == 0)
                    {
                        SPIx->DR = 0;
                    }
                    else
                    {
                        if (size == 1)
                        {
                            SPIx->DR = ((uint8_t *)sendbuffer)[send_index];
                        }
                        else if (size == 2)
                        {
                            SPIx->DR = ((uint16_t *)sendbuffer)[send_index];
                        }
                        else if (size == 4)
                        {
                            SPIx->DR = ((uint32_t *)sendbuffer)[send_index];
                        }
                    }

                    send_index++;
                }
                else
                {
                    /*starting sending the data when the fifo is full*/
                    SPIx->SER = reg_ser;
                    while (!(SPIx->SR & SPI_RECEIVE_FIFO_NOT_EMPTY));
                }

                if (SPIx->SR & SPI_RECEIVE_FIFO_NOT_EMPTY)
                {
                    if (size == 1)
                    {
                        ((uint8_t *)receivebuffer)[receive_index] = SPIx->DR;
                    }
                    else if (size == 2)
                    {
                        ((uint16_t *)receivebuffer)[receive_index] = SPIx->DR;
                    }
                    else if (size == 4)
                    {
                        ((uint32_t *)receivebuffer)[receive_index] = SPIx->DR;
                    }

                    receive_index++;
                }
            }

            SPIx->SER = reg_ser;

            for (; receive_index < receivebuffer_length; )
            {
                if (SPIx->SR & SPI_RECEIVE_FIFO_NOT_EMPTY)
                {
                    if (size == 1)
                    {
                        ((uint8_t *)receivebuffer)[receive_index] = SPIx->DR;
                    }
                    else if(size == 2)
                    {
                        ((uint16_t *)receivebuffer)[receive_index] = SPIx->DR;
                    }
                    else if(size == 4)
                    {
                        ((uint32_t *)receivebuffer)[receive_index] = SPIx->DR;
                    }

                    receive_index++;
                }
            }

            ret = receive_index;
        }
    }
    else if (SPIx == SPIS)
    {
        if (sendbuffer_length)
        {
            for (send_index = 0; send_index < sendbuffer_length; send_index++)
            {
                if (size == 1)
                {
                    SPIx->DR = ((uint8_t *)sendbuffer)[send_index];
                }
                else if (size == 2)
                {
                    SPIx->DR = ((uint16_t *)sendbuffer)[send_index];
                }
                else if (size == 4)
                {
                    SPIx->DR = ((uint32_t *)sendbuffer)[send_index];
                }
            }

            ret = send_index;
        }

        if (receivebuffer_length)
        {
            for (receive_index = 0; receive_index < receivebuffer_length; receive_index++)
            {
                if (size == 1)
                {
                    ((uint8_t *)receivebuffer)[receive_index] = SPIx->DR;
                }
                else if (size == 2)
                {
                    ((uint16_t *)receivebuffer)[receive_index] = SPIx->DR;
                }
                else if (size == 4)
                {
                    ((uint32_t *)receivebuffer)[receive_index] = SPIx->DR;
                }
            }

            ret = receive_index;
        }
    }

    return ret;
}
