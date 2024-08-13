/**
* @file    ZD25WQ.c
* @brief   The Source Codes for the ZD25WQ Functions
* @version V1.0.0.0
* @date    2023/04/10
* @author  li
* DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
*
* (C)Copyright WITIN Technology Co.Ltd 2023 All rights reserved
*/
#include "zd25wq.h"

extern void system_delay_ms(uint32_t time);
extern void system_delay_us(uint32_t time);
volatile uint8_t rdsr_flag = 0;
void QSPI_IRQHandler(void)
{
    if(QSPI_Get_Int_Pending_Status(QSPI) & QSPI_INT_POLLING_MATCH)
    {   
        QSPI_Clear_Int_Pending_Cmd(QSPI,QSPI_INT_POLLING_MATCH);
        rdsr_flag = 1;
    }
}

static int ZD25WQ_send(ZD25WQ *ZD25WQ_hd, int8_t instruction,int32_t address,int32_t alternatebyte,int8_t dummy_cycle,uint8_t *data,int32_t len)
{ 
    int ret = 0;
    uint8_t temp[50]={0};

    if(ZD25WQ_hd == NULL)
    {
        ret = -1;
        goto end;
    }
     
    QSPI_Ctl_Init(QSPI,ZD25WQ_hd->qspi_ctl);

    QSPI_Set_Instrction(QSPI,instruction);
    QSPI_Set_Address(QSPI,address);
    QSPI_Set_Alternatebyte(QSPI,alternatebyte);
    QSPI_Set_Dummy_cycle(QSPI,dummy_cycle);
    
    if(!len)
    {
        QSPI_Set_Data_Length(QSPI,1);
        QSPI_Set_Read_Or_Write_Mode(QSPI,QSPI_WRITE_DATA_MODE);
        
        QSPI_Set_Start_Cmd(QSPI);
        while(QSPI_Get_Status(QSPI));
    }
    else
    {
        if(!(ZD25WQ_hd->send_dma_flag))
        {
            ret = QSPI_Transimit(QSPI,(uint32_t *)data,len);
        }
        else
        {    
            ret = QSPI_Dma_Transimit(QSPI,mmap_to_sys((uint32_t)data),len,ZD25WQ_hd->send_dma_channel);
            system_delay_us(100);
        }
        if(ret <= 0)
        {
            ret = -3;
            goto end;
        }
    }

end:
    return ret;
}

static int  ZD25WQ_receive(ZD25WQ *ZD25WQ_hd, int8_t instruction,int32_t address,int32_t alternatebyte,int8_t dummy_cycle,uint8_t *data,int32_t len)
{  
    int ret = 1;

    if(ZD25WQ_hd == NULL)
    {
        ret = -1;
        goto end;
    }
    
    QSPI_Ctl_Init(QSPI,ZD25WQ_hd->qspi_ctl);

    QSPI_Set_Instrction(QSPI,instruction);
    QSPI_Set_Address(QSPI,address);
    QSPI_Set_Alternatebyte(QSPI,alternatebyte);
    QSPI_Set_Dummy_cycle(QSPI,dummy_cycle);
    
    if(!(ZD25WQ_hd->receive_dma_flag))
    {
        ret = QSPI_Receive(QSPI,(uint32_t *)data,len);
    }
    else
    {
        ret = QSPI_Dma_Receive(QSPI,mmap_to_sys((uint32_t)data),len,ZD25WQ_hd->receive_dma_channel);
        system_delay_ms(10);
    }
    if(ret <= 0) 
    {
        ret = -3;
        goto end;
    }

end:
    return ret;
}

static int ZD25WQ_polling(ZD25WQ *ZD25WQ_hd, int8_t instruction,int8_t dummy_cycle,int8_t match_value,int8_t mask_value,int32_t timeout_ms)
{
    int ret = 1;
    int32_t timeout = 0;

    if(ZD25WQ_hd == NULL)
    {
        ret = -1;
        goto end;
    }
    
    QSPI_Ctl_Init(QSPI,ZD25WQ_hd->qspi_ctl);

    QSPI_Set_Instrction(QSPI,instruction);
    QSPI_Set_Address(QSPI,0);
    QSPI_Set_Alternatebyte(QSPI,0);
    QSPI_Set_Dummy_cycle(QSPI,dummy_cycle);

    rdsr_flag = 0;
    QSPI_Set_Polling_Configurationo(QSPI,mask_value,match_value);
    QSPI_Set_Read_Or_Write_Mode(QSPI,QSPI_READ_DATA_MODE);
    QSPI_Set_Data_Length(QSPI,0Xffffffff);
    QSPI_Set_Polling_Mode_Cmd(QSPI,1);
    while(!rdsr_flag)
    {
        if(timeout++ > timeout_ms)
        {
            QSPI_Set_Stop_Cmd(QSPI);
            ret = -2;
            break;
        }
        system_delay_ms(1);
    }

end:
    QSPI_Set_Polling_Configurationo(QSPI,0,0);
    return ret;
} 

static int ZD25WQ_valid_id(ZD25WQ *ZD25WQ_hd)
{
    uint8_t value[3]={0};
    int count = 3;

    while(count-- > 0)
    {
        ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
        ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
        ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
        ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
        ZD25WQ_receive(ZD25WQ_hd,ZD25WQ_MANUFACTURER_DEVICE_ID,0,0,0,value,3);
        if(value[0] == ZD25WQ_MANUFACTURER && value[1] == ZD25WQ_DEVICE_TYPE && value[2] == ZD25WQ_DEVICE_ID)
            break;
    }
    if(count<=0) return -1;

    return 1;
}

static int ZD25WQ_send_dma_init(ZD25WQ *ZD25WQ_hd,uint8_t dma_channel)
{
    if(ZD25WQ_hd == NULL)
        return -1;
    if(!IS_DMA_CHANNEL(dma_channel))
        return -2;

    ZD25WQ_hd->send_dma_inittypedef = (DMA_InitTypeDef *)ZD25WQ_MALLOC(sizeof(DMA_InitTypeDef));
    if(ZD25WQ_hd->send_dma_inittypedef == NULL)
        return -3;

    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN,ENABLE);
    QSPI_Set_Send_Dma_Cmd(QSPI,1,ENABLE);

    ZD25WQ_hd->send_dma_inittypedef->llp_src_en = DISABLE;
    ZD25WQ_hd->send_dma_inittypedef->llp_dst_en = DISABLE;
    ZD25WQ_hd->send_dma_inittypedef->reload_src_en = DISABLE;
    ZD25WQ_hd->send_dma_inittypedef->reload_dst_en = DISABLE;
    ZD25WQ_hd->send_dma_inittypedef->direction = MEM_TO_PER_FLOW_CTOL_DMA;
    ZD25WQ_hd->send_dma_inittypedef->src_msize = DMA_MSIZE1;
    ZD25WQ_hd->send_dma_inittypedef->dst_msize = DMA_MSIZE1;
    ZD25WQ_hd->send_dma_inittypedef->src_addr_type = DMA_ADDRESS_INCREASE;
    ZD25WQ_hd->send_dma_inittypedef->dst_addr_type = DMA_ADDRESS_NO_CHANGE;
    ZD25WQ_hd->send_dma_inittypedef->src_width = DMA_WIDTH32;
    ZD25WQ_hd->send_dma_inittypedef->dst_width = DMA_WIDTH32;
    ZD25WQ_hd->send_dma_inittypedef->dst_per = DMA_QSPI_TX_REQ;
    ZD25WQ_hd->send_dma_inittypedef->src_per = DMA_QSPI_TX_REQ;

    ZD25WQ_hd->send_dma_inittypedef->fifo_mode_en = DISABLE;
    ZD25WQ_hd->send_dma_inittypedef->max_abrst = 0;
    ZD25WQ_hd->send_dma_inittypedef->src_handshaking_type = DMA_HW_HANDSHAKE;
    ZD25WQ_hd->send_dma_inittypedef->dst_handshaking_type = DMA_HW_HANDSHAKE;
    ZD25WQ_hd->send_dma_inittypedef->chanel_priority = DMA_PRIORITY0;
    ZD25WQ_hd->send_dma_inittypedef->int_en = DISABLE;

    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Init(DMA, dma_channel, ZD25WQ_hd->send_dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    ZD25WQ_hd->send_dma_flag = 1;
    ZD25WQ_hd->send_dma_channel = dma_channel;

    return 1;
}

static int ZD25WQ_send_dma_uninit(ZD25WQ *ZD25WQ_hd)
{
    if(ZD25WQ_hd == NULL)
        return -1;
    
    QSPI_Set_Send_Dma_Cmd(QSPI,0,DISABLE);

    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Uninit(DMA,DMA_CHANNEL0);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    ZD25WQ_free(ZD25WQ_hd->send_dma_inittypedef);
    ZD25WQ_hd->send_dma_inittypedef = NULL;
    ZD25WQ_hd->send_dma_flag = 0;
    ZD25WQ_hd->send_dma_channel = 0;

    return 1;
}

static int ZD25WQ_receive_dma_init(ZD25WQ *ZD25WQ_hd,uint8_t dma_channel)
{
    if(ZD25WQ_hd == NULL)
        return -1;
    if(!IS_DMA_CHANNEL(dma_channel))
        return -2;

    ZD25WQ_hd->receive_dma_inittypedef = (DMA_InitTypeDef *)ZD25WQ_MALLOC(sizeof(DMA_InitTypeDef));
    if(ZD25WQ_hd->receive_dma_inittypedef == NULL)
        return -2;
    
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN,ENABLE);
    QSPI_Set_Receive_Dma_Cmd(QSPI,1,ENABLE);

    ZD25WQ_hd->receive_dma_inittypedef->llp_src_en = DISABLE;
    ZD25WQ_hd->receive_dma_inittypedef->llp_dst_en = DISABLE;
    ZD25WQ_hd->receive_dma_inittypedef->reload_src_en = DISABLE;
    ZD25WQ_hd->receive_dma_inittypedef->reload_dst_en = DISABLE;
    ZD25WQ_hd->receive_dma_inittypedef->direction = PER_TO_MEM_FLOW_CTOL_DMA;
    ZD25WQ_hd->receive_dma_inittypedef->src_msize = DMA_MSIZE1;
    ZD25WQ_hd->receive_dma_inittypedef->dst_msize = DMA_MSIZE1;
    ZD25WQ_hd->receive_dma_inittypedef->src_addr_type = DMA_ADDRESS_NO_CHANGE;
    ZD25WQ_hd->receive_dma_inittypedef->dst_addr_type = DMA_ADDRESS_INCREASE;
    ZD25WQ_hd->receive_dma_inittypedef->src_width = DMA_WIDTH32;
    ZD25WQ_hd->receive_dma_inittypedef->dst_width = DMA_WIDTH32;
    ZD25WQ_hd->receive_dma_inittypedef->dst_per = DMA_QSPI_RX_REQ;
    ZD25WQ_hd->receive_dma_inittypedef->src_per = DMA_QSPI_RX_REQ;

    ZD25WQ_hd->receive_dma_inittypedef->fifo_mode_en = DISABLE;
    ZD25WQ_hd->receive_dma_inittypedef->max_abrst = 0;
    ZD25WQ_hd->receive_dma_inittypedef->src_handshaking_type = DMA_HW_HANDSHAKE;
    ZD25WQ_hd->receive_dma_inittypedef->dst_handshaking_type = DMA_HW_HANDSHAKE;
    ZD25WQ_hd->receive_dma_inittypedef->chanel_priority = DMA_PRIORITY0;
    ZD25WQ_hd->receive_dma_inittypedef->int_en = DISABLE;

    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Init(DMA, dma_channel, ZD25WQ_hd->receive_dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    ZD25WQ_hd->receive_dma_flag = 1;
    ZD25WQ_hd->receive_dma_channel = dma_channel;

    return 1;
}

static int ZD25WQ_receive_dma_uninit(ZD25WQ *ZD25WQ_hd)
{
    if(ZD25WQ_hd == NULL)
        return -1;
    
    QSPI_Set_Receive_Dma_Cmd(QSPI,0,DISABLE);

    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Uninit(DMA,DMA_CHANNEL1);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    ZD25WQ_free(ZD25WQ_hd->receive_dma_inittypedef);
    ZD25WQ_hd->receive_dma_inittypedef = NULL;
    ZD25WQ_hd->receive_dma_flag = 0;
    ZD25WQ_hd->receive_dma_channel = 0;

    return 1;
}

int ZD25WQ_sector_or_block_erase(ZD25WQ *ZD25WQ_hd,uint8_t instruction,uint32_t address)
{
    int ret = 0;
    if (ZD25WQ_hd == NULL) return -1;

    /*write enable*/
    ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE; 
    ZD25WQ_send(ZD25WQ_hd,ZD25WQ_WRITE_ENABLE,0,0,0,NULL,0);
    
    /*sector or block erase*/ 
    ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
    ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ZD25WQ_send(ZD25WQ_hd,instruction,address,0,0,NULL,0);
    
    /*waiting*/
    ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ret = ZD25WQ_polling(ZD25WQ_hd,ZD25WQ_READ_STATUS_REGISTER,0,0x00,0x01,ZD25WQ_SECTOR_BLOCK_ERASE_MAX_TIME_S * 1000); 
    if(ret <= 0) return -2;
 
    return 1;
}

int ZD25WQ_chip_erase(ZD25WQ *ZD25WQ_hd)
{
    int ret = 0;
    if (ZD25WQ_hd == NULL) return -1;
    
    ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ZD25WQ_send(ZD25WQ_hd,ZD25WQ_WRITE_ENABLE,0,0,0,NULL,0);
    ZD25WQ_send(ZD25WQ_hd,ZD25WQ_CHIP_ERASE,0,0,0,NULL,0);

    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    ret = ZD25WQ_polling(ZD25WQ_hd,ZD25WQ_READ_STATUS_REGISTER,0,0x00,0x01,ZD25WQ_CHIP_ERASE_MAX_TIME_S * 1000); 
    if(ret <= 0) return -2;

    return 1;
}

int ZD25WQ_chip_write_protect(ZD25WQ *ZD25WQ_hd,FunctionalState newstatus)
{
    volatile uint8_t value = 0;
    if (ZD25WQ_hd == NULL) return -1; 
    
    ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ZD25WQ_receive(ZD25WQ_hd,ZD25WQ_READ_STATUS_REGISTER,0,0,0,value,1);

    /* write enable */
    ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;    
    ZD25WQ_send(ZD25WQ_hd,ZD25WQ_WRITE_ENABLE,0,0,0,NULL,0);

    if(newstatus)
    {
        value = (ZD25WQ_CHIP_PROTECT_VALUE << 2);
        ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
        ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
        ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
        ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    }
    else 
    {
        value = 0;
        ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
        ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
        ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
        ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    }
    ZD25WQ_send(ZD25WQ_hd,ZD25WQ_WRITE_STATUS_REGISTER,0,0,0,&value,1);

    return 1;
}

int ZD25WQ_page_write(ZD25WQ *ZD25WQ_hd, uint32_t address, uint8_t *data,uint32_t len)
{
    if (ZD25WQ_hd == NULL || data == NULL) return -1;
     
    if(ZD25WQ_hd->qspi_1line_or_4lines == ZD25WQ_QSPI_1LINE)
        ZD25WQ_send(ZD25WQ_hd,ZD25WQ_PAGE_PROGRAM,address,0,0,data,len);  
    else
        ZD25WQ_send(ZD25WQ_hd,ZD25WQ_QUAD_PAGE_PROGRAM,address,0,0,data,len);  
    
    return len;
}

int ZD25WQ_sector_write(ZD25WQ *ZD25WQ_hd,uint32_t sector_index, uint8_t *data, uint32_t sector_counts)
{   
    int pages = ZD25WQ_hd->sector_size / ZD25WQ_hd->page_size, index = 0x00, sc = sector_counts;
    while (sector_counts-- > 0x00)
    {
        ZD25WQ_sector_or_block_erase(ZD25WQ_hd, ZD25WQ_SECTOR_ERASE,sector_index*ZD25WQ_hd->sector_size);
        index = 0x00;
        while (index < pages)
        {
            ZD25WQ_page_write(ZD25WQ_hd,(sector_index*ZD25WQ_hd->sector_size)+index*ZD25WQ_hd->page_size ,data,ZD25WQ_hd->page_size);
            data += ZD25WQ_hd->page_size;
            index++;
        }
        sector_index++;
    }

    return sc*ZD25WQ_hd->sector_size;
}

int ZD25WQ_sector_read(ZD25WQ *ZD25WQ_hd,uint32_t sector_index, uint8_t *data, uint32_t sector_counts)
{
    int size = 0;
    size = ZD25WQ_read(ZD25WQ_hd, sector_index*ZD25WQ_hd->sector_size, data, ZD25WQ_hd->sector_size*sector_counts);

    return size;
}

int ZD25WQ_read(ZD25WQ *ZD25WQ_hd,uint32_t address, uint8_t *data,uint32_t len)
{
    int ret = 0;
    if (ZD25WQ_hd == NULL || data == NULL) return -1;
    
    if(ZD25WQ_hd->qspi_1line_or_4lines == ZD25WQ_QSPI_1LINE)
    {
        ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
        ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
        ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
        ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
        ret = ZD25WQ_receive(ZD25WQ_hd,ZD25WQ_READ_DATA,address,0x00,0,data,len);
        if(ret <= 0) return -2;
    }
    else
    {
        ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_4_LINES;
        ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_32_BITS;
        ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_4_LINES;
        ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
        ret = ZD25WQ_receive(ZD25WQ_hd,ZD25WQ_FAST_READ_QUAD_IO,(address << 8) | 0xf0,0,4,data,len);
        if(ret <= 0) return -2;
    } 

    return ret;
}

int ZD25WQ_write(ZD25WQ *ZD25WQ_hd,uint32_t address, uint8_t *buf, uint32_t length)
{
    int ret = 0;
    uint32_t ilen = 0,write_length = 0; 
    if (ZD25WQ_hd == NULL || buf == NULL || length == 0) return -1;

    write_length = length;
    while (write_length > 0)
    { 
        ilen = ZD25WQ_hd->page_size - (address % ZD25WQ_hd->page_size);
        if (write_length < ilen)
            ilen = write_length;
        
        ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
        ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
        ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
        ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;    
        ZD25WQ_send(ZD25WQ_hd,ZD25WQ_WRITE_ENABLE,0,0,0,NULL,0);

        if(ZD25WQ_hd->qspi_1line_or_4lines == ZD25WQ_QSPI_1LINE)
        {
            ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
            ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
            ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
            ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
        }
        else
        {
            ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
            ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
            ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_4_LINES;
            ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
        }
        ret = ZD25WQ_page_write(ZD25WQ_hd,address,buf,ilen);
        if(ret <= 0) return -2;
       
        ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
        ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
        ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
        ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
        ret = ZD25WQ_polling(ZD25WQ_hd,ZD25WQ_READ_STATUS_REGISTER,0,0x00,0x01,ZD25WQ_SECTOR_BLOCK_ERASE_MAX_TIME_S * 1000); 
        if(ret <= 0) return -3;
       
        address += ilen;
        write_length -= ilen;
        buf += ilen;
    }

    return length;
}

int ZD25WQ_qspi_init(ZD25WQ *ZD25WQ_hd)
{
    if(ZD25WQ_hd == NULL)
        return -1;

    ZD25WQ_hd->qspi_ctl = (QSPI_CtlInitTypeDef *)ZD25WQ_MALLOC(sizeof(QSPI_CtlInitTypeDef));
    if(ZD25WQ_hd->qspi_ctl == NULL)
        return -2;

    ZD25WQ_hd->qspi_ctl->sph = QSPI_SPH_0;
    ZD25WQ_hd->qspi_ctl->spo = QSPI_SPO_0;
    ZD25WQ_hd->qspi_ctl->sample_clk_sel = QSPI_SAMPLE_NO_REVERSE_CLOCK;
    ZD25WQ_hd->qspi_ctl->read_delay_time = 0;
    ZD25WQ_hd->qspi_ctl->alternatebytessize = QSPI_ALTERNATE_BYTES_8_BITS;
    ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
    ZD25WQ_hd->qspi_ctl->dummy_cycle = 6;
    ZD25WQ_hd->qspi_ctl->dmode_sel = QSPI_WRITE_DATA_MODE;
    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    ZD25WQ_hd->qspi_ctl->alternatebytemode = QSPI_ALTERNATE_BYTES_NONE;
    ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
    ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    
    ZD25WQ_hd->clock_divider = 2;

    ZD25WQ_hd->send_dma_flag = 0;
    ZD25WQ_hd->receive_dma_flag = 0;

    return 1;
}

int ZD25WQ_open(ZD25WQ *ZD25WQ_hd, QSPI_TypeDef *qspi_hd,uint8_t line_type,uint8_t send_dma_enable,uint8_t send_dma_channel,uint8_t receive_dma_enable,uint8_t receive_dma_channel)
{
    int ret = 0;
    GPIO_InitTypeDef Qspi_InitStructure;

    if (ZD25WQ_hd == NULL || qspi_hd == NULL ) return -1;
    if(line_type != ZD25WQ_QSPI_1LINE && line_type != ZD25WQ_QSPI_4LINES) return -2;

    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN,ENABLE);
    RCC_CLK_EN_Ctl(RCC_QSPI_PCLKEN,ENABLE);
    RCC_Peri_Rst(RCC_QSPI_RSTN);

    ZD25WQ_hd->qspi_hd = qspi_hd;
    ZD25WQ_hd->qspi_1line_or_4lines = line_type;
    
    /*clock divider*/
    RCC_QSPI_Set_ClkDiv(ZD25WQ_hd->clock_divider - 1);

    /*init gpio*/
    if(ZD25WQ_hd->qspi_1line_or_4lines == ZD25WQ_QSPI_1LINE)
    {
        Qspi_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17;
        Qspi_InitStructure.Alternate = GPIO_AF14_QSPI | GPIO_AF15_QSPI | GPIO_AF16_QSPI | GPIO_AF17_QSPI;
        GPIO_Init(GPIOA, &Qspi_InitStructure);
    }
    else if(ZD25WQ_hd->qspi_1line_or_4lines == ZD25WQ_QSPI_1LINE)
    {
        Qspi_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17 | GPIO_PIN_18 | GPIO_PIN_19;
        Qspi_InitStructure.Alternate = GPIO_AF14_QSPI | GPIO_AF15_QSPI | GPIO_AF16_QSPI | GPIO_AF17_QSPI | GPIO_AF18_QSPI | GPIO_AF19_QSPI;
        GPIO_Init(GPIOA, &Qspi_InitStructure);
    }

    /*Enable The Interrupt For Qspi*/
    QSPI_Set_Int_Mask(QSPI,QSPI_INT_TRANSMISSION_FINISH);
    QSPI_Clear_Int_Mask(QSPI,QSPI_INT_POLLING_MATCH);
    ECLIC_ClearPendingIRQ(QSPI_IRQn);
    ECLIC_SetPriorityIRQ(QSPI_IRQn, 1);
    ECLIC_SetTrigIRQ(QSPI_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(QSPI_IRQn);

    /*software reset*/
    ZD25WQ_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    ZD25WQ_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    ZD25WQ_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    ZD25WQ_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ZD25WQ_send(ZD25WQ_hd,ZD25WQ_RESET_ENABLE,0,0,0,NULL,0);
    ZD25WQ_send(ZD25WQ_hd,ZD25WQ_RESET,0,0,0,NULL,0);
    system_delay_ms(10);

    /*read device id*/
    ret = ZD25WQ_valid_id(ZD25WQ_hd);
    if(ret <= 0) return -3;

    /*send dma init*/
    if(send_dma_enable)
    {
        ret = ZD25WQ_send_dma_init(ZD25WQ_hd,send_dma_channel);
        if(ret <= 0) return -4;
    }
    /*receive dma init*/
    if(receive_dma_enable)
    {
        ret = ZD25WQ_receive_dma_init(ZD25WQ_hd,receive_dma_channel);
        if(ret <= 0) return -4;
    }

    ZD25WQ_hd->page_size = ZD25WQ_PAGE_SIZE;
    ZD25WQ_hd->sector_size = ZD25WQ_SECTOR_SIZE;
    ZD25WQ_hd->flash_size = ZD25WQ_SIZE;

    return 1;
}

int ZD25WQ_close(ZD25WQ *ZD25WQ_hd)
{
    if (ZD25WQ_hd == NULL ) return -1;

    /*uninit gpio*/
    if(ZD25WQ_hd->qspi_1line_or_4lines == ZD25WQ_QSPI_1LINE)
    {
        GPIO_DeInit(GPIOA, GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17);
    }
    else if(ZD25WQ_hd->qspi_1line_or_4lines == ZD25WQ_QSPI_1LINE)
    {
        GPIO_DeInit(GPIOA, GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17 | GPIO_PIN_18 | GPIO_PIN_19);
    }

    /*Disable The Interrupt For Qspi*/
    QSPI_Set_Int_Mask(QSPI,QSPI_INT_READ_UNDERFLOW | QSPI_INT_WRITE_OVERFLOW | QSPI_INT_TRANSMISSION_FINISH | QSPI_INT_WRITE_EMPTY);
    ECLIC_ClearPendingIRQ(QSPI_IRQn);
    ECLIC_SetPriorityIRQ(QSPI_IRQn, 1);
    ECLIC_SetTrigIRQ(QSPI_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_DisableIRQ(QSPI_IRQn);
    
    /*send dma uninit*/
    if(ZD25WQ_hd->send_dma_flag)
    {
        ZD25WQ_send_dma_uninit(ZD25WQ_hd);
    }
    /*receive dma uninit*/
    if(ZD25WQ_hd->receive_dma_flag)
    {
        ZD25WQ_receive_dma_uninit(ZD25WQ_hd);
    }

    /*free memory*/
    ZD25WQ_free(ZD25WQ_hd->qspi_ctl);
    memset(ZD25WQ_hd,0,sizeof(ZD25WQ));

    return 1;
}
