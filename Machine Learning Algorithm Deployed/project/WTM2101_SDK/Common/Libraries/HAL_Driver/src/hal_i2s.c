/**
* @file    hal_i2s.c
* @brief   The Source Codes for the hal_i2s Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

/** Includes */
#include "hal_i2s.h"

#define HAL_I2S_INSTANCE_NUMBER 2
static Hal_I2s_InitTypeDef hal_i2s_instance[HAL_I2S_INSTANCE_NUMBER];

__attribute__((weak)) void DMA_IRQHandler(void)
{
    /*the dma interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    /*for example, you are using the HAL_I2S_INSTANCE0 instance*/
    uint16_t block_int_flag;
    Hal_I2s_InitTypeDef* hal_i2s_instance= hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
  
    if(block_int_flag & hal_i2s_instance->dma.dma_channel)
    {
        DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance->dma.dma_channel);
        hal_i2s_instance->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance);
    }
}

static void hal_i2s_parameter_config(Hal_I2s_InitTypeDef *i2s_instance)
{
    uint32_t clkdiv = 0;
    uint32_t clock = 0;

    if (i2s_instance->instance == I2S0) 
    {
        RCC_CLK_EN_Ctl(RCC_I2S0_CLKEN,ENABLE);
        RCC_Peri_Rst(RCC_I2S0_RSTN);
    } 
    else if (i2s_instance->instance == I2S1)
    {
        RCC_CLK_EN_Ctl(RCC_I2S1_CLKEN,ENABLE);
        RCC_Peri_Rst(RCC_I2S1_RSTN);
    }

    I2S_Ctl(i2s_instance->instance,DISABLE);

    if(i2s_instance->mode == HAL_I2S_MASTER)
        I2S_Mode_Sel(i2s_instance->instance, I2S_MASTER);
    else
        I2S_Mode_Sel(i2s_instance->instance, I2S_SLAVE);  

    clock = RCC_Get_SYSClk();

    clkdiv = RCC_AHB_Get_ClkDiv();
    clock = clock / (clkdiv + 1);

    clkdiv = RCC_APB0_Get_ClkDiv();
    clock = clock / (clkdiv + 1);

    if(i2s_instance->width_word == HAL_I2S_32BITS_WIDTH_WORD)
    {
        I2S_ClkCfg(i2s_instance->instance,I2S_SCLKNUM_32,I2S_GATESCLKNUM_NONE);
        clkdiv = (10*clock/(i2s_instance->lrclk_frequency*32*2) + 5)/10;
    }
    else
    {
        I2S_ClkCfg(i2s_instance->instance,I2S_SCLKNUM_16,I2S_GATESCLKNUM_NONE);
        clkdiv = (10*clock/(i2s_instance->lrclk_frequency*16*2) + 5)/10;
    }

    if (i2s_instance->instance == I2S0) 
        RCC_I2S0_Set_ClkDiv(clkdiv - 1);
    else
        RCC_I2S1_Set_ClkDiv(clkdiv - 1);

    if(i2s_instance->width_word == HAL_I2S_32BITS_WIDTH_WORD)
    {
        if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
        {
            I2S_RxCfg(i2s_instance->instance,I2S_RES_LEN_32);
        }
        else if(i2s_instance->type == HAL_I2S_ONLY_SEND) 
        {
            I2S_TxCfg(i2s_instance->instance,I2S_RES_LEN_32);
        }
        else
        {
            I2S_RxCfg(i2s_instance->instance,I2S_RES_LEN_32);
            I2S_TxCfg(i2s_instance->instance,I2S_RES_LEN_32);
        }
    }
    else
    {
        if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
        {
            I2S_RxCfg(i2s_instance->instance,I2S_RES_LEN_16);
        }
        else if(i2s_instance->type == HAL_I2S_ONLY_SEND) 
        {
            I2S_TxCfg(i2s_instance->instance,I2S_RES_LEN_16);
        }
        else
        {
            I2S_RxCfg(i2s_instance->instance,I2S_RES_LEN_16);
            I2S_TxCfg(i2s_instance->instance,I2S_RES_LEN_16);
        }
    }
  
    if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
    {
        I2S_RxFIFO_LVLCfg(i2s_instance->instance,7);  /* don't change */
        I2S_RxFIFO_Flush(i2s_instance->instance);
    
        I2S_RxBlkCtl(i2s_instance->instance,ENABLE);
        I2S_RxChlCtl(i2s_instance->instance,ENABLE);

        I2S_IT_MskCtl(i2s_instance->instance, I2S_IT_RXDA, DISABLE); 
    }
    else if(i2s_instance->type == HAL_I2S_ONLY_SEND) 
    {
        I2S_TxFIFO_LVLCfg(i2s_instance->instance,0);  /* don't change */
        I2S_TxFIFO_Flush(i2s_instance->instance);

        I2S_TxBlkCtl(i2s_instance->instance,ENABLE);
        I2S_TxChlCtl(i2s_instance->instance,ENABLE);

        I2S_IT_MskCtl(i2s_instance->instance, I2S_IT_TXFE, DISABLE); 
    }
    else
    {
        I2S_RxFIFO_LVLCfg(i2s_instance->instance,7);  /* don't change */
        I2S_RxFIFO_Flush(i2s_instance->instance);
        I2S_TxFIFO_LVLCfg(i2s_instance->instance,0);  /* don't change */
        I2S_TxFIFO_Flush(i2s_instance->instance);

        I2S_RxBlkCtl(i2s_instance->instance,ENABLE);
        I2S_RxChlCtl(i2s_instance->instance,ENABLE);
        I2S_TxBlkCtl(i2s_instance->instance,ENABLE);
        I2S_TxChlCtl(i2s_instance->instance,ENABLE);

        I2S_IT_MskCtl(i2s_instance->instance, I2S_IT_RXDA, DISABLE); 
        I2S_IT_MskCtl(i2s_instance->instance, I2S_IT_TXFE, DISABLE); 
    }

    I2S_Ctl(i2s_instance->instance,ENABLE); 
}

static void hal_i2s_dma_init(Hal_I2s_InitTypeDef *i2s_instance)
{
    DMA_InitTypeDef dma_inittypedef;
  
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);

    DMA_Clear_All_Interrupt_Cmd(DMA);
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Init(DMA, i2s_instance->dma.dma_channel, &i2s_instance->dma.config);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    DMA_Set_Block_Interrupt_Cmd(DMA, i2s_instance->dma.dma_channel, ENABLE);
    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);
}

static void hal_i2s_dma_fifo_init(Hal_I2s_InitTypeDef *i2s_instance)
{
    uint32_t ctl0_cache;

    switch (i2s_instance->dma.dma_channel) {
        case DMA_CHANNEL0: ctl0_cache = (uint32_t)DMA->CTL0; break;
        case DMA_CHANNEL1: ctl0_cache = (uint32_t)DMA->CTL1; break;
        case DMA_CHANNEL2: ctl0_cache = (uint32_t)DMA->CTL2; break;
        case DMA_CHANNEL3: ctl0_cache = (uint32_t)DMA->CTL3; break;
        case DMA_CHANNEL4: ctl0_cache = (uint32_t)DMA->CTL4; break;
        case DMA_CHANNEL5: ctl0_cache = (uint32_t)DMA->CTL5; break;
        default:break;
    }

    i2s_instance->dma.llp_cfg[0].llp         = mmap_to_sys((uint32_t)&(i2s_instance->dma.llp_cfg[1]));
    if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
    {
        i2s_instance->dma.llp_cfg[0].src         = mmap_to_sys((uint32_t)&(i2s_instance->instance->RXDMA));
        i2s_instance->dma.llp_cfg[0].dst         = mmap_to_sys((uint32_t)&(i2s_instance->dma.cache_buffer[0]));
    }
    else
    {
        i2s_instance->dma.llp_cfg[0].src         = mmap_to_sys((uint32_t)&(i2s_instance->dma.cache_buffer[0]));
        i2s_instance->dma.llp_cfg[0].dst         = mmap_to_sys((uint32_t)&(i2s_instance->instance->TXDMA));
    }
    i2s_instance->dma.llp_cfg[0].ctl_reg_high= 16 ;
    i2s_instance->dma.llp_cfg[0].ctl_reg_low = ctl0_cache;

    i2s_instance->dma.llp_cfg[1].llp         = mmap_to_sys((uint32_t)&i2s_instance->dma.llp_cfg[0]);
    if(i2s_instance->type == HAL_I2S_ONLY_SEND)
    {
        i2s_instance->dma.llp_cfg[1].src         = mmap_to_sys((uint32_t)&(i2s_instance->dma.cache_buffer[16 * i2s_instance->width_word]));      
        i2s_instance->dma.llp_cfg[1].dst         = mmap_to_sys((uint32_t)&(i2s_instance->instance->TXDMA));
    }
    else
    {
        i2s_instance->dma.llp_cfg[1].src         = mmap_to_sys((uint32_t)&(i2s_instance->instance->RXDMA));
        i2s_instance->dma.llp_cfg[1].dst         = mmap_to_sys((uint32_t)&(i2s_instance->dma.cache_buffer[16 * i2s_instance->width_word]));
    }
    i2s_instance->dma.llp_cfg[1].ctl_reg_high= 16;

    if(i2s_instance->type == HAL_I2S_RECEIVE_AND_SEND)
    {
        ctl0_cache &= ~(7 << 20);
        ctl0_cache &= ~(3 << 9);
        ctl0_cache &= ~(3 << 7);
        ctl0_cache |= (2 << 20);
        ctl0_cache |= (2 << 9);
        ctl0_cache |= (0 << 7);
    }
    i2s_instance->dma.llp_cfg[1].ctl_reg_low = ctl0_cache;
}

static void hal_i2s_data_prehandle(Hal_I2s_InitTypeDef *i2s_instance)
{
    uint16_t *temp_data_pointer16 = NULL;
    uint32_t *temp_data_pointer32 = NULL;

    if(i2s_instance->width_word == HAL_I2S_16BITS_WIDTH_WORD)
        temp_data_pointer16 = (uint16_t *)(i2s_instance->dma.cache_buffer);
    else
        temp_data_pointer32 = (uint32_t *)(i2s_instance->dma.cache_buffer);

    if(i2s_instance->type == HAL_I2S_ONLY_SEND)
    {
        for (uint8_t i = 0;i < 32; i++)  
        {
             if(i2s_instance->width_word == HAL_I2S_16BITS_WIDTH_WORD)
                temp_data_pointer16[i] = 0;
             else
                temp_data_pointer32[i] = 0;
        }

        for (uint8_t i = 0;i < 16; i+=2)  
        {
            i2s_instance->instance->LRBR_LTHR =  0;
            i2s_instance->instance->RRBR_RTHR =  0;
        }
    }
    else if(i2s_instance->type == HAL_I2S_RECEIVE_AND_SEND)
    {
        for (uint8_t i = 0;i < 16; i++)  /* Prepare 4 groups of data in advance */
        {
            if(i2s_instance->width_word == HAL_I2S_16BITS_WIDTH_WORD)
                temp_data_pointer16[i] = 0;
            else
                temp_data_pointer32[i] = 0;
        }

        for (uint8_t i = 0;i < 8; i+=2)  /* Prepare 4 groups of data in advance */
        {
            i2s_instance->instance->LRBR_LTHR =  0;
            i2s_instance->instance->RRBR_RTHR =  0;
        }    
    }
} 

static void hal_i2s_gpio_init(Hal_I2s_InitTypeDef *i2s_instance)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_CLK_EN_Ctl(RCC_CLK_EN_GPIO_HCLKEN_Msk, ENABLE);

    if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
    {
        GPIO_InitStructure.Pin = i2s_instance->io.sdi_io | i2s_instance->io.bclk_io | i2s_instance->io.lrclk_io;
        GPIO_InitStructure.Alternate = i2s_instance->io.sdi_io_af | i2s_instance->io.bclk_io_af | i2s_instance->io.lrclk_io_af;
    }
    else if(i2s_instance->type == HAL_I2S_ONLY_SEND)
    {
        GPIO_InitStructure.Pin = i2s_instance->io.sdo_io | i2s_instance->io.bclk_io | i2s_instance->io.lrclk_io;
        GPIO_InitStructure.Alternate = i2s_instance->io.sdo_io_af | i2s_instance->io.bclk_io_af | i2s_instance->io.lrclk_io_af;
    }
    else
    {
        GPIO_InitStructure.Pin = i2s_instance->io.sdi_io | i2s_instance->io.sdo_io | i2s_instance->io.bclk_io | i2s_instance->io.lrclk_io;
        GPIO_InitStructure.Alternate = i2s_instance->io.sdi_io_af | i2s_instance->io.sdo_io_af | i2s_instance->io.bclk_io_af | i2s_instance->io.lrclk_io_af;
    }
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void hal_i2s_gpio_uninit(Hal_I2s_InitTypeDef *i2s_instance) 
{
    if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
    {
        GPIO_DeInit(GPIOA,  i2s_instance->io.sdi_io | i2s_instance->io.bclk_io | i2s_instance->io.lrclk_io);
    }
    else if(i2s_instance->type == HAL_I2S_ONLY_SEND)
    {
        GPIO_DeInit(GPIOA,  i2s_instance->io.sdo_io | i2s_instance->io.bclk_io | i2s_instance->io.lrclk_io);
    }
    else
    {
        GPIO_DeInit(GPIOA,  i2s_instance->io.sdi_io | i2s_instance->io.sdo_io | i2s_instance->io.bclk_io | i2s_instance->io.lrclk_io);
    }
}

static void transfer_and_receive_handler(struct Hal_I2s_InitTypeDef *i2s_instance)
{
    if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
    {
        if(i2s_instance->dma.dma_cnt%2)
        {
            memcpy(i2s_instance->receive_buffer.buffer + i2s_instance->receive_buffer.write_index,i2s_instance->dma.cache_buffer + 0,16 * i2s_instance->width_word);
        }
        else
        {
            memcpy(i2s_instance->receive_buffer.buffer + i2s_instance->receive_buffer.write_index,i2s_instance->dma.cache_buffer + 16 * i2s_instance->width_word,16 * i2s_instance->width_word);
        }
        i2s_instance->receive_buffer.write_index += 16 * i2s_instance->width_word;
        i2s_instance->receive_buffer.write_index %= i2s_instance->receive_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word; 
        i2s_instance->dma.dma_cnt++;
    }
    else if(i2s_instance->type == HAL_I2S_ONLY_SEND)
    {
        i2s_instance->dma.dma_cnt++;
        if(i2s_instance->dma.dma_cnt%2)
        {
            memcpy(i2s_instance->dma.cache_buffer + 0,i2s_instance->send_buffer.buffer + i2s_instance->send_buffer.write_index,16 * i2s_instance->width_word);       
        }
        else
        {
            memcpy(i2s_instance->dma.cache_buffer + 16 * i2s_instance->width_word,i2s_instance->send_buffer.buffer + i2s_instance->send_buffer.write_index,16 * i2s_instance->width_word);          
        }
        i2s_instance->send_buffer.write_index += 16 * i2s_instance->width_word;
        i2s_instance->send_buffer.write_index %= i2s_instance->send_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word; 
    }
    else
    {
        i2s_instance->dma.dma_cnt++;
        if(i2s_instance->dma.dma_cnt%2)
        {
            memcpy(i2s_instance->dma.cache_buffer + 0,i2s_instance->send_buffer.buffer + i2s_instance->send_buffer.write_index,16 * i2s_instance->width_word); 
            i2s_instance->send_buffer.write_index += 16 * i2s_instance->width_word;
            i2s_instance->send_buffer.write_index %= i2s_instance->send_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word; 
        }
        else                             
        {
            memcpy(i2s_instance->receive_buffer.buffer + i2s_instance->receive_buffer.write_index,i2s_instance->dma.cache_buffer + 16 * i2s_instance->width_word,16 * i2s_instance->width_word);
            i2s_instance->receive_buffer.write_index += 16 * i2s_instance->width_word;
            i2s_instance->receive_buffer.write_index %= i2s_instance->receive_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word; 
        }
    } 
}

Hal_I2s_InitTypeDef* hal_i2s_instance_get(Hal_I2s_Instance_Typedef number)
{
    if(number < HAL_I2S_INSTANCE0 || number > HAL_I2S_INSTANCE1)
        return NULL;

    return (&hal_i2s_instance[number]);
}

int hal_i2s_init(Hal_I2s_InitTypeDef *i2s_instance,I2S_TypeDef *address,Hal_I2s_Type_Typedef type,Hal_I2s_Work_Mode_Typedef mode,Hal_I2s_Width_Word_Typedef width,int lr_channel_need_sizes_by_width)
{
    if(i2s_instance == NULL)
        return -1;
    if((address != I2S0) && (address != I2S1))
        return -2;
    if(type < HAL_I2S_ONLY_RECEIVE || type > HAL_I2S_RECEIVE_AND_SEND)
        return -3;
    if(mode < HAL_I2S_MASTER || mode > HAL_I2S_SLAVE)
        return -4;  
    if(width < HAL_I2S_16BITS_WIDTH_WORD || width > HAL_I2S_32BITS_WIDTH_WORD)
        return -5;  

    /*Implement the constructor according to the passed parameters*/
    i2s_instance->instance = address;
    i2s_instance->type = type;
    i2s_instance->mode = mode;
    i2s_instance->width_word = width;
    i2s_instance->lrclk_frequency = 16000;
    i2s_instance->lr_channel_need_sizes_by_width = lr_channel_need_sizes_by_width;
    if(i2s_instance->instance == I2S0)
    {
        i2s_instance->io.sdo_io = GPIO_PIN_0;
        i2s_instance->io.lrclk_io = GPIO_PIN_1;
        i2s_instance->io.bclk_io = GPIO_PIN_2;
        i2s_instance->io.sdi_io = GPIO_PIN_3;

        i2s_instance->io.sdo_io_af = GPIO_AF0_I2S0;
        i2s_instance->io.lrclk_io_af = GPIO_AF1_I2S0;
        i2s_instance->io.bclk_io_af = GPIO_AF2_I2S0;
        i2s_instance->io.sdi_io_af = GPIO_AF3_I2S0;
    }
    else
    {
        i2s_instance->io.sdo_io = GPIO_PIN_10;
        i2s_instance->io.sdi_io = GPIO_PIN_11;
        i2s_instance->io.bclk_io = GPIO_PIN_12;
        i2s_instance->io.lrclk_io = GPIO_PIN_13;


        i2s_instance->io.sdo_io_af = GPIO_AF10_I2S1;
        i2s_instance->io.sdi_io_af = GPIO_AF11_I2S1;
        i2s_instance->io.bclk_io_af = GPIO_AF12_I2S1;
        i2s_instance->io.lrclk_io_af = GPIO_AF13_I2S1;
    }
  
    {
        i2s_instance->send_buffer.lr_channel_need_sizes_by_width_counts = 3;
        i2s_instance->send_buffer.buffer = NULL;
        i2s_instance->send_buffer.read_index = 0;
        i2s_instance->send_buffer.write_index = 0;
    }

    {
        i2s_instance->receive_buffer.lr_channel_need_sizes_by_width_counts = 3;
        i2s_instance->receive_buffer.buffer = NULL;
        i2s_instance->receive_buffer.read_index = 0;
        i2s_instance->receive_buffer.write_index = 0;
    }
    i2s_instance->Data_handle_info.transfer_and_receive_handler = transfer_and_receive_handler;

    {
        i2s_instance->dma.enable = ENABLE;
        i2s_instance->dma.dma_channel = DMA_CHANNEL2;

        i2s_instance->dma.config.llp_src_en          = ENABLE;
        i2s_instance->dma.config.llp_dst_en          = ENABLE;
        i2s_instance->dma.config.reload_src_en       = DISABLE;
        i2s_instance->dma.config.reload_dst_en       = DISABLE;
        i2s_instance->dma.config.src_msize           = DMA_MSIZE16;  
        i2s_instance->dma.config.dst_msize           = DMA_MSIZE16;   
        if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
        {
            i2s_instance->dma.config.src_addr_type       = DMA_ADDRESS_NO_CHANGE;
            i2s_instance->dma.config.dst_addr_type       = DMA_ADDRESS_INCREASE;
            i2s_instance->dma.config.direction           = PER_TO_MEM_FLOW_CTOL_DMA;
        }
        else
        {
            i2s_instance->dma.config.src_addr_type       = DMA_ADDRESS_INCREASE;
            i2s_instance->dma.config.dst_addr_type       = DMA_ADDRESS_NO_CHANGE;
            i2s_instance->dma.config.direction           = MEM_TO_PER_FLOW_CTOL_DMA;
        }

        if(HAL_I2S_32BITS_WIDTH_WORD == i2s_instance->width_word)
        {
            i2s_instance->dma.config.src_width           = DMA_WIDTH32;
            i2s_instance->dma.config.dst_width           = DMA_WIDTH32;
        }
        else
        {
            i2s_instance->dma.config.src_width           = DMA_WIDTH16; 
            i2s_instance->dma.config.dst_width           = DMA_WIDTH16; 
        }

        i2s_instance->dma.config.fifo_mode_en        = DISABLE;
        i2s_instance->dma.config.max_abrst           = 0;
        i2s_instance->dma.config.src_handshaking_type= DMA_HW_HANDSHAKE;
        i2s_instance->dma.config.dst_handshaking_type= DMA_HW_HANDSHAKE;
        i2s_instance->dma.config.chanel_priority     = DMA_PRIORITY0;
        i2s_instance->dma.config.int_en              = ENABLE;
    
        if(i2s_instance->instance == I2S0)
        {
            i2s_instance->dma.config.src_per = DMA_I2S0_REQ;
            i2s_instance->dma.config.dst_per = DMA_I2S0_REQ;
        }
        else
        {
            i2s_instance->dma.config.src_per = DMA_I2S1_REQ;
            i2s_instance->dma.config.dst_per = DMA_I2S1_REQ;
        }
        memset(i2s_instance->dma.cache_buffer,0,16 * 4 * 2);
        i2s_instance->dma.dma_cnt = 0;
    }

    return 1;
}

int hal_i2s_open(Hal_I2s_InitTypeDef *i2s_instance)
{
    if(i2s_instance == NULL)
        return -1;

    /* malloc memory*/
    if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
    {
        i2s_instance->receive_buffer.buffer = (uint8_t *)HAL_I2S_MALLOC(i2s_instance->receive_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word);
        if(!(i2s_instance->receive_buffer.buffer))
            return -2;
        memset(i2s_instance->receive_buffer.buffer,0,i2s_instance->receive_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word);
    }
    else if(i2s_instance->type == HAL_I2S_ONLY_SEND)
    {
        i2s_instance->send_buffer.buffer = (uint8_t *)HAL_I2S_MALLOC(i2s_instance->send_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word);
        if(!(i2s_instance->send_buffer.buffer))
            return -2;
        memset(i2s_instance->send_buffer.buffer,0,i2s_instance->send_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word);
    }
    else
    {
        i2s_instance->receive_buffer.buffer = (uint8_t *)HAL_I2S_MALLOC(i2s_instance->receive_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word);
        if(!(i2s_instance->receive_buffer.buffer))
            return -2;
        i2s_instance->send_buffer.buffer = (uint8_t *)HAL_I2S_MALLOC(i2s_instance->send_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word);
        if(!(i2s_instance->send_buffer.buffer))
            return -3;
        memset(i2s_instance->receive_buffer.buffer,0,i2s_instance->receive_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word);
        memset(i2s_instance->send_buffer.buffer,0,i2s_instance->send_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word);
    }

    /* i2s hardware configuration*/
    hal_i2s_parameter_config(i2s_instance);

    if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
    {
        I2S_RxBlk_DMA_Rst(i2s_instance->instance);
    }
    else if(i2s_instance->type == HAL_I2S_ONLY_SEND)
    {
        I2S_TxBlk_DMA_Rst(i2s_instance->instance);
    }
    else
    {
        I2S_RxBlk_DMA_Rst(i2s_instance->instance);
        I2S_TxBlk_DMA_Rst(i2s_instance->instance);
    }
    
    /* i2s-dma init */
    hal_i2s_dma_init(i2s_instance);
    hal_i2s_dma_fifo_init(i2s_instance);

    i2s_instance->enable = ENABLE;

    return 1;
}

int hal_i2s_ctl(Hal_I2s_InitTypeDef *i2s_instance,int command, ...)
{
    va_list ParamList;
    volatile int value = 0;

    if (i2s_instance == NULL) 
        return -1;
    va_start(ParamList, command);

    switch(command)
    {
        case HAL_I2S_CHANNEL_ENABLE_COMMAND:
        {
            /*the i2s was enabled or disabled*/
            value = va_arg(ParamList, int);
            if(value)
            { 
                i2s_instance->dma.dma_cnt = 0;

                I2S_RxFIFO_Flush(i2s_instance->instance);
                I2S_TxFIFO_Flush(i2s_instance->instance);

                hal_i2s_data_prehandle(i2s_instance);
                DMA_Set_Addr(DMA, i2s_instance->dma.dma_channel, 0, 0, 0, mmap_to_sys((uint32_t)i2s_instance->dma.llp_cfg));
                  
                if(i2s_instance->mode == HAL_I2S_MASTER)
                    I2S_ClkCtl(i2s_instance->instance,ENABLE);
         
                DMA_Set_Channel_Enable_Cmd(DMA, i2s_instance->dma.dma_channel, ENABLE);      

                /* i2s-gpio init*/
                hal_i2s_gpio_init(i2s_instance);
            }
            else
            {
                /* i2s-gpio uninit*/
                hal_i2s_gpio_uninit(i2s_instance);
 
                if(i2s_instance->mode == HAL_I2S_MASTER)
                    I2S_ClkCtl(i2s_instance->instance,DISABLE);
                
                DMA_Set_Channel_Enable_Cmd(DMA, i2s_instance->dma.dma_channel, DISABLE); 

                i2s_instance->send_buffer.read_index = 0;
                i2s_instance->send_buffer.write_index = 0;
                i2s_instance->receive_buffer.read_index = 0;
                i2s_instance->receive_buffer.write_index = 0;
            }

            break;
        }
        
        case HAL_I2S_CHANNEL_UPDATA_CLOCK_COMMAND:
        {
            uint32_t clock = 0,clkdiv = 0;
            clock = RCC_Get_SYSClk();

            clkdiv = RCC_AHB_Get_ClkDiv();
            clock = clock / (clkdiv + 1);

            clkdiv = RCC_APB0_Get_ClkDiv();
            clock = clock / (clkdiv + 1);

            if(i2s_instance->width_word == HAL_I2S_32BITS_WIDTH_WORD)
            {
                I2S_ClkCfg(i2s_instance->instance,I2S_SCLKNUM_32,I2S_GATESCLKNUM_NONE);
                clkdiv = (10*clock/(i2s_instance->lrclk_frequency*32*2) + 5)/10;
            }
            else
            {
                I2S_ClkCfg(i2s_instance->instance,I2S_SCLKNUM_16,I2S_GATESCLKNUM_NONE);
                clkdiv = (10*clock/(i2s_instance->lrclk_frequency*16*2) + 5)/10;
            }

            if (i2s_instance->instance == I2S0) 
                RCC_I2S0_Set_ClkDiv(clkdiv - 1);
            else
                RCC_I2S1_Set_ClkDiv(clkdiv - 1);
            break;
        }

        default:
            return -10;
    }

    va_end(ParamList);

    return 1;
}

int hal_i2s_write(Hal_I2s_InitTypeDef *i2s_instance,void *left_data,void *right_data,int size_by_data)
{
    volatile uint32_t *left_temp32 = NULL,*right_temp32 = NULL,*i2s_buffer32 = NULL;
    volatile uint16_t *left_temp16 = NULL,*right_temp16 = NULL,*i2s_buffer16 = NULL;

    if (i2s_instance == NULL || size_by_data <= 0) 
        return -1;

    if(i2s_instance->width_word == HAL_I2S_16BITS_WIDTH_WORD)
    {
        left_temp16 = (uint16_t *)left_data;
        right_temp16 = (uint16_t *)right_data;
        i2s_buffer16 = (uint16_t *)(&i2s_instance->send_buffer.buffer[i2s_instance->send_buffer.read_index]);
        for(int i = 0 ;i < size_by_data; i++)
        {
            if(left_temp16)
             i2s_buffer16[i * 2] =  left_temp16[i];
            if(right_temp16)
             i2s_buffer16[i * 2 + 1] = right_temp16[i];
        }
    }
    else
    {
        left_temp32 = (uint32_t *)left_data;
        right_temp32 = (uint32_t *)right_data;
        i2s_buffer32 = (uint32_t *)(&i2s_instance->send_buffer.buffer[i2s_instance->send_buffer.read_index]);
        for(int i = 0 ;i < size_by_data; i++)
        {
            if(left_temp32)
                i2s_buffer32[i * 2] =  left_temp32[i];
            if(right_temp32)
                i2s_buffer32[i * 2 + 1] = right_temp32[i];
        }
    }
    i2s_instance->send_buffer.read_index += i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word;
    i2s_instance->send_buffer.read_index %= i2s_instance->send_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word;

    return 1;
}

int hal_i2s_read(Hal_I2s_InitTypeDef *i2s_instance,void *left_data,void *right_data,int size_by_data)
{
    volatile uint32_t *left_temp32 = NULL,*right_temp32 = NULL,*i2s_buffer32 = NULL;
    volatile uint16_t *left_temp16 = NULL,*right_temp16 = NULL,*i2s_buffer16 = NULL;
    if (i2s_instance == NULL) 
        return -1;

    if(abs(i2s_instance->receive_buffer.write_index - i2s_instance->receive_buffer.read_index) >= i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word)
    {  
        if(i2s_instance->width_word == HAL_I2S_16BITS_WIDTH_WORD)
        {
            left_temp16 = (uint16_t *)left_data;
            right_temp16 = (uint16_t *)right_data;
            i2s_buffer16 = (uint16_t *)(&i2s_instance->receive_buffer.buffer[i2s_instance->receive_buffer.read_index]);
            for(int i = 0 ;i < size_by_data; i++)
            {
               if(left_temp16)
                  left_temp16[i] = i2s_buffer16[i * 2];
               if(right_temp16)
                  right_temp16[i] = i2s_buffer16[i * 2 + 1];
            }
        }
        else
        {
            left_temp32 = (uint32_t *)left_data;
            right_temp32 = (uint32_t *)right_data;
            i2s_buffer32 = (uint32_t *)(&i2s_instance->receive_buffer.buffer[i2s_instance->receive_buffer.read_index]);
            for(int i = 0 ;i < size_by_data; i++)
            {
              if(left_temp32)
                  left_temp32[i] = i2s_buffer32[i * 2];
              if(right_temp32)
                  right_temp32[i] = i2s_buffer32[i * 2 + 1];
            }
        }
        i2s_instance->receive_buffer.read_index += i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word;
        i2s_instance->receive_buffer.read_index %= i2s_instance->receive_buffer.lr_channel_need_sizes_by_width_counts * i2s_instance->lr_channel_need_sizes_by_width * i2s_instance->width_word;
        return 1;
    }

    return -10; 
}

int hal_i2s_close(Hal_I2s_InitTypeDef *i2s_instance)
{
    if(i2s_instance == NULL)
        return -1;
    if(i2s_instance->enable == DISABLE)
        return -2;

    /* i2s-gpio uninit*/
    hal_i2s_gpio_uninit(i2s_instance);

    /* i2s-dma uninit */
    if(i2s_instance->mode == HAL_I2S_MASTER)
        I2S_ClkCtl(i2s_instance->instance,DISABLE);
    DMA_Set_Channel_Enable_Cmd(DMA, i2s_instance->dma.dma_channel, DISABLE); 
    if (i2s_instance->instance == I2S0) 
    {
        RCC_Peri_Rst(RCC_I2S0_RSTN);
        RCC_CLK_EN_Ctl(RCC_I2S0_CLKEN,DISABLE);
    } 
    else if (i2s_instance->instance == I2S1)
    {
        RCC_Peri_Rst(RCC_I2S1_RSTN);
        RCC_CLK_EN_Ctl(RCC_I2S1_CLKEN,DISABLE);
    }
    I2S_Ctl(i2s_instance->instance,DISABLE);

    /* free memory */
    if(i2s_instance->type == HAL_I2S_ONLY_RECEIVE)
    {
        HAL_I2S_FREE(i2s_instance->receive_buffer.buffer);
    }
    else if(i2s_instance->type == HAL_I2S_ONLY_SEND)
    {
        HAL_I2S_FREE(i2s_instance->send_buffer.buffer);
    }
    else
    {
        HAL_I2S_FREE(i2s_instance->receive_buffer.buffer);    
        HAL_I2S_FREE(i2s_instance->send_buffer.buffer);
    }

    i2s_instance->enable = DISABLE;

    return 1;
}
