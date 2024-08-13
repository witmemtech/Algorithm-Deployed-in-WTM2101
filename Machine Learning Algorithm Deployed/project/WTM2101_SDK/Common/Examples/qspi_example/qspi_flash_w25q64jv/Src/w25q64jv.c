/**
* @file    w24q64jv.c
* @brief   The Source Codes for the w24q64jv Functions
* @version V1.0.0.0
* @date    2021/07/12
* @author  li
* DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
*
* (C)Copyright WITIN Technology Co.Ltd		2020 All rights reserved
*/
#include "w25q64jv.h"
#include "wtm2101_hal.h"
extern Bool rdsr_flag;

int w25q64jv_qspi_init(W25q64jv *W25q64jv_hd)
{
    if(W25q64jv_hd == NULL)
        return -1;

    W25q64jv_hd->qspi_ctl = (QSPI_CtlInitTypeDef *)W25Q64JV_MALLOC(sizeof(QSPI_CtlInitTypeDef));
    if(W25q64jv_hd->qspi_ctl == NULL)
        return -2;

    W25q64jv_hd->qspi_ctl->sph = QSPI_SPH_0;
    W25q64jv_hd->qspi_ctl->spo = QSPI_SPO_0;
    W25q64jv_hd->qspi_ctl->sample_clk_sel = QSPI_SAMPLE_NO_REVERSE_CLOCK;
    W25q64jv_hd->qspi_ctl->read_delay_time = 0;
    W25q64jv_hd->qspi_ctl->alternatebytessize = QSPI_ALTERNATE_BYTES_8_BITS;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
    W25q64jv_hd->qspi_ctl->dummy_cycle = 6;
    W25q64jv_hd->qspi_ctl->dmode_sel = QSPI_WRITE_DATA_MODE;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_4_LINES;
    W25q64jv_hd->qspi_ctl->alternatebytemode = QSPI_ALTERNATE_BYTES_NONE;
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_4_LINES;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_4_LINES;

    return 1;
}

static int w25q64jv_send(W25q64jv *W25q64jv_hd, int8_t instruction,int32_t address,int32_t alternatebyte,int8_t dummy_cycle,uint8_t *data,int32_t len)
{ 
    uint32_t *buffer = NULL;
    uint32_t buffer_length = 0;    
    int ret = 0;
    uint8_t temp[50]={0};

    if(W25q64jv_hd == NULL)
    {
        ret = -1;
        goto end;
    }
     
    QSPI_Ctl_Init(QSPI,W25q64jv_hd->qspi_ctl);

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
        buffer_length = (len / 4 + 1) * 4; 
        buffer = (uint32_t *)W25Q64JV_MALLOC(buffer_length);
        if(buffer == NULL) 
        {
            ret = -2;
            goto end;
        }
        memcpy(buffer,data,len);
        if(!(W25q64jv_hd->send_dma_flag))
            ret = QSPI_Transimit(QSPI,buffer,len);
        else
            ret = QSPI_Dma_Transimit(QSPI,buffer,len,W25q64jv_hd->send_dma_channel);
        W25Q64JV_free(buffer);
        if(ret <= 0)
        {
            ret = -3;
            goto end;
        }
    }

end:
    return ret;
}

static int w25q64jv_receive(W25q64jv *W25q64jv_hd, int8_t instruction,int32_t address,int32_t alternatebyte,int8_t dummy_cycle,uint8_t *data,int32_t len)
{
    uint32_t *buffer = NULL;
    uint32_t buffer_length = 0;    
    int ret = 1;

    if(W25q64jv_hd == NULL)
    {
        ret = -1;
        goto end;
    }
    
    QSPI_Ctl_Init(QSPI,W25q64jv_hd->qspi_ctl);

    QSPI_Set_Instrction(QSPI,instruction);
    QSPI_Set_Address(QSPI,address);
    QSPI_Set_Alternatebyte(QSPI,alternatebyte);
    QSPI_Set_Dummy_cycle(QSPI,dummy_cycle);
    
    buffer_length = (len / 4 + 1) * 4; 
    buffer = (uint32_t *)W25Q64JV_MALLOC(buffer_length);
    if(buffer == NULL) 
    {
        ret = -2;
        goto end;
    }
    memset(buffer,0,len);
    if(!(W25q64jv_hd->receive_dma_flag))
        ret = QSPI_Receive(QSPI,buffer,len);
    else
        ret = QSPI_Dma_Receive(QSPI,buffer,len,W25q64jv_hd->receive_dma_channel);
    memcpy(data,buffer,len);
    W25Q64JV_free(buffer);
    if(ret <= 0) 
    {
        ret = -3;
        goto end;
    }

end:
    return ret;
}


int w25q64jv_read_id(W25q64jv *W25q64jv_hd, uint8_t *id)
{
    uint8_t value[2]={0};
    int count = 3;

    while(count > 0)
    {
        count--;
        if(W25q64jv_hd->qspi_1line_or_4lines == W25Q64JV_QSPI_1LINE)
        {
            W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
            W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
            W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
            W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
            w25q64jv_receive(W25q64jv_hd,READ_ID_CMD,0,0,0,value,2);
        }
        else
        {
            W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_4_LINES;
            W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
            W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_4_LINES;
            W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
            w25q64jv_receive(W25q64jv_hd,QUAD_READ_ID_CMD,0,0,6,value,2);
        }
    }
    memcpy(id, value, sizeof(value));
    if(count<0) 
        return 1;

    return 0;
}

int w25q64jv_read_jedec_id(W25q64jv *W25q64jv_hd, uint8_t *id)
{
    uint8_t value[3]={0};

    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    w25q64jv_receive(W25q64jv_hd,READ_JEDEC_ID_CMD,0,0,0,value,3);
    memcpy(id, value, sizeof(value));

    return 0;
}

uint8_t w25q64jv_read_status_reg(W25q64jv *W25q64jv_hd, int8_t reg_cmd)
{
    uint8_t value = 0;

    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    w25q64jv_receive(W25q64jv_hd,reg_cmd,0,0,0,&value,1);

    return value;
}

void w25q64jv_write_status_reg(W25q64jv *W25q64jv_hd, uint8_t reg_cmd, uint8_t status)
{

    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    w25q64jv_send(W25q64jv_hd,reg_cmd,0,0,0,&status,1);
}

void w25q64jv_write_enable(W25q64jv *W25q64jv_hd)
{

    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    w25q64jv_send(W25q64jv_hd,WRITE_ENABLE_CMD,0,0,0,NULL,0);
}

void w25q64jv_reset(W25q64jv *W25q64jv_hd)
{

    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    w25q64jv_send(W25q64jv_hd,RESET_ENABLE_CMD,0,0,0,NULL,0);
    w25q64jv_send(W25q64jv_hd,RESET_MEMORY_CMD,0,0,0,NULL,0);
}

void w25q64jv_global_block_unlock(W25q64jv *W25q64jv_hd)
{

    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    w25q64jv_send(W25q64jv_hd,GLOBAL_BLOCK_UNLOCK,0,0,0,NULL,0);
}

void w25q64jv_write_enable_for_volatile(W25q64jv *W25q64jv_hd)
{

    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    w25q64jv_send(W25q64jv_hd,WRITE_ENABLE_VOLATILE_CMD,0,0,0,NULL,0);
}

static int w25q64jv_polling(W25q64jv *W25q64jv_hd, int8_t instruction,int8_t dummy_cycle,int8_t match_value,int8_t mask_value,int32_t timeout_ms)
{
    int ret = 1;
    int32_t timeout = 0;

    if(W25q64jv_hd == NULL)
    {
        ret = -1;
        goto end;
    }
    
    QSPI_Ctl_Init(QSPI,W25q64jv_hd->qspi_ctl);

    QSPI_Set_Instrction(QSPI,instruction);
    QSPI_Set_Address(QSPI,0);
    QSPI_Set_Alternatebyte(QSPI,0);
    QSPI_Set_Dummy_cycle(QSPI,dummy_cycle);

    rdsr_flag = FALSE;
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

int w25q64jv_sector_erase(W25q64jv *W25q64jv_hd, uint8_t instruction, uint32_t address)
{
    int ret = 0;
    uint8_t status = 0;
    if (W25q64jv_hd == NULL)
        return -1;

    /*write enable*/
    w25q64jv_write_enable(W25q64jv_hd);
    
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;

    w25q64jv_send(W25q64jv_hd,instruction,address,0,0,NULL,0);   
    /*waiting*/
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ret = w25q64jv_polling(W25q64jv_hd,READ_STATUS_REG1_CMD,0,0x00,0x01,w25q64jv_SECTOR_BLOCK_ERASE_MAX_TIME_S * 1000); 
    if(ret <= 0) 
        return -2;

    return 0;
}

int w25q64jv_chip_erase(W25q64jv *W25q64jv_hd)
{
    int ret = 0;
    uint8_t status = 0;
    if (W25q64jv_hd == NULL)
        return -1;

    /*write enable*/
    w25q64jv_write_enable(W25q64jv_hd);
    
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_NONE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;

    w25q64jv_send(W25q64jv_hd,CHIP_ERASE_CMD,0,0,0,NULL,0);   
    /*waiting*/
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ret = w25q64jv_polling(W25q64jv_hd,READ_STATUS_REG1_CMD,0,0x00,0x01,w25q64jv_SECTOR_BLOCK_ERASE_MAX_TIME_S * 1000); 
    if(ret <= 0) 
        return -2;

    return 0;
}

int w25q64jv_fast_quad_read(W25q64jv *W25q64jv_hd, uint32_t address, uint8_t *data,uint32_t len)
{
    int ret = 0;
    if (W25q64jv_hd == NULL || data == NULL)
        return -1;
    
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_4_LINES;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ret = w25q64jv_receive(W25q64jv_hd,QUAD_OUT_FAST_READ_CMD,address,0x00,8,data,len);
    if(ret <= 0)
        return -2;

    return ret;
}

int w25q64jv_read(W25q64jv *W25q64jv_hd, uint32_t address, uint8_t *data,uint32_t len)
{
    int ret = 0;
    if (W25q64jv_hd == NULL || data == NULL)
        return -1;
    
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ret = w25q64jv_receive(W25q64jv_hd,READ_CMD,address,0x00,0x00,data,len);
    if(ret <= 0)
        return -2;

    return ret;
}

int w25q64jv_page_program(W25q64jv *W25q64jv_hd, uint32_t address, uint8_t *data, int len)
{
    int ret = 0;
    if (W25q64jv_hd == NULL)
        return -1;

    if(W25q64jv_hd->page_size < len)
        return -2;
    /*write enable*/
    w25q64jv_write_enable(W25q64jv_hd);
    
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;

    w25q64jv_send(W25q64jv_hd,PAGE_PROG_CMD,address,0,0,data,len);
    
    /*waiting*/
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ret = w25q64jv_polling(W25q64jv_hd,READ_STATUS_REG1_CMD,0,0x00,0x01,w25q64jv_SECTOR_BLOCK_ERASE_MAX_TIME_S * 1000); 
    if(ret <= 0) 
        return -2;

    return 0;
}

int w25q64jv_quad_page_program(W25q64jv *W25q64jv_hd, uint32_t address, uint8_t *data, int len)
{
    int ret = 0;
    if (W25q64jv_hd == NULL)
        return -1;

    if(W25q64jv_hd->page_size < len)
        return -2;
    /*write enable*/
    w25q64jv_write_enable(W25q64jv_hd);
    
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_1_LINE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_24_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_4_LINES;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;

    w25q64jv_send(W25q64jv_hd,QUAD_INPUT_PAGE_PROG_CMD,address,0,0,data,len);
    
    /*waiting*/
    W25q64jv_hd->qspi_ctl->addressmode = QSPI_ADDRESS_NONE;
    W25q64jv_hd->qspi_ctl->addresssize = QSPI_ADDRESS_8_BITS;
    W25q64jv_hd->qspi_ctl->datamode = QSPI_DATA_1_LINE;
    W25q64jv_hd->qspi_ctl->instructionmode = QSPI_INSTRUCTION_1_LINE;
    ret = w25q64jv_polling(W25q64jv_hd,READ_STATUS_REG1_CMD,0,0x00,0x01,w25q64jv_SECTOR_BLOCK_ERASE_MAX_TIME_S * 1000); 
    if(ret <= 0) 
        return -2;

    return 0;
}

int w25q64jv_open(W25q64jv *W25q64jv_hd, QSPI_TypeDef *qspi_hd,uint8_t line_type)
{
    int ret = 0;
    uint8_t id[2] = {0};

    if (W25q64jv_hd == NULL || qspi_hd == NULL ) return -1;
    if(line_type != W25Q64JV_QSPI_1LINE && line_type != W25Q64JV_QSPI_4LINES)
        return -2;

    W25q64jv_hd->qspi_hd = qspi_hd;
    W25q64jv_hd->qspi_1line_or_4lines = line_type;

    /*Enable The Interrupt For Qspi*/
    QSPI_Set_Int_Mask(QSPI,QSPI_INT_READ_UNDERFLOW | QSPI_INT_WRITE_OVERFLOW | QSPI_INT_TRANSMISSION_FINISH | QSPI_INT_WRITE_EMPTY);
    QSPI_Clear_Int_Mask(QSPI,QSPI_INT_POLLING_MATCH);
    ECLIC_SetPriorityIRQ(QSPI_IRQn, 2);
    ECLIC_ClearPendingIRQ(QSPI_IRQn);
    ECLIC_EnableIRQ(QSPI_IRQn);
    ECLIC_SetTrigIRQ(QSPI_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);

    ret = w25q64jv_read_id(W25q64jv_hd, id);
    if(ret == 0)
        printf("read ID SUCCEED 0x%x 0x%x\r\n", id[0], id[1]);
    else
        printf("read ID failed\r\n");

    W25q64jv_hd->page_size = W25Q64JV_PAGE_SIZE;
    W25q64jv_hd->sector_size = W25Q64JV_SECTOR_SIZE;
    W25q64jv_hd->flash_size = W25Q64JV_SIZE;
    w25q64jv_reset(W25q64jv_hd);
    system_delay_ms(2);
    w25q64jv_global_block_unlock(W25q64jv_hd);
    return ret;

}

int w25q64jv_send_dma_init(W25q64jv *W25q64jv_hd, uint8_t dma_channel)
{
    if(W25q64jv_hd == NULL)
        return -1;
    if(!IS_DMA_CHANNEL(dma_channel))
        return -2;

    W25q64jv_hd->send_dma_inittypedef = (DMA_InitTypeDef *)W25Q64JV_MALLOC(sizeof(DMA_InitTypeDef));
    if(W25q64jv_hd->send_dma_inittypedef == NULL)
        return -3;
    
    QSPI_Set_Send_Dma_Cmd(QSPI,1,ENABLE);

    W25q64jv_hd->send_dma_inittypedef->llp_src_en = DISABLE;
    W25q64jv_hd->send_dma_inittypedef->llp_dst_en = DISABLE;
    W25q64jv_hd->send_dma_inittypedef->reload_src_en = DISABLE;
    W25q64jv_hd->send_dma_inittypedef->reload_dst_en = DISABLE;
    W25q64jv_hd->send_dma_inittypedef->direction = MEM_TO_PER_FLOW_CTOL_DMA;
    W25q64jv_hd->send_dma_inittypedef->src_msize = DMA_MSIZE1;
    W25q64jv_hd->send_dma_inittypedef->dst_msize = DMA_MSIZE1;
    W25q64jv_hd->send_dma_inittypedef->src_addr_type = DMA_ADDRESS_INCREASE;
    W25q64jv_hd->send_dma_inittypedef->dst_addr_type = DMA_ADDRESS_NO_CHANGE;
    W25q64jv_hd->send_dma_inittypedef->src_width = DMA_WIDTH32;
    W25q64jv_hd->send_dma_inittypedef->dst_width = DMA_WIDTH32;
    W25q64jv_hd->send_dma_inittypedef->dst_per = DMA_QSPI_TX_REQ;
    W25q64jv_hd->send_dma_inittypedef->src_per = DMA_QSPI_TX_REQ;

    W25q64jv_hd->send_dma_inittypedef->fifo_mode_en = DISABLE;
    W25q64jv_hd->send_dma_inittypedef->max_abrst = 0;
    W25q64jv_hd->send_dma_inittypedef->src_handshaking_type = DMA_HW_HANDSHAKE;
    W25q64jv_hd->send_dma_inittypedef->dst_handshaking_type = DMA_HW_HANDSHAKE;
    W25q64jv_hd->send_dma_inittypedef->chanel_priority = DMA_PRIORITY0;
    W25q64jv_hd->send_dma_inittypedef->int_en = DISABLE;

    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Init(DMA, dma_channel, W25q64jv_hd->send_dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    W25q64jv_hd->send_dma_flag = 1;
    W25q64jv_hd->send_dma_channel = dma_channel;

    return 1;
}

int w25q64jv_receive_dma_init(W25q64jv *W25q64jv_hd,uint8_t dma_channel)
{
    if(W25q64jv_hd == NULL)
        return -1;
    if(!IS_DMA_CHANNEL(dma_channel))
        return -2;

    W25q64jv_hd->receive_dma_inittypedef = (DMA_InitTypeDef *)W25Q64JV_MALLOC(sizeof(DMA_InitTypeDef));
    if(W25q64jv_hd->receive_dma_inittypedef == NULL)
        return -2;
    
    QSPI_Set_Receive_Dma_Cmd(QSPI,1,ENABLE);

    W25q64jv_hd->receive_dma_inittypedef->llp_src_en = DISABLE;
    W25q64jv_hd->receive_dma_inittypedef->llp_dst_en = DISABLE;
    W25q64jv_hd->receive_dma_inittypedef->reload_src_en = DISABLE;
    W25q64jv_hd->receive_dma_inittypedef->reload_dst_en = DISABLE;
    W25q64jv_hd->receive_dma_inittypedef->direction = PER_TO_MEM_FLOW_CTOL_DMA;
    W25q64jv_hd->receive_dma_inittypedef->src_msize = DMA_MSIZE1;
    W25q64jv_hd->receive_dma_inittypedef->dst_msize = DMA_MSIZE1;
    W25q64jv_hd->receive_dma_inittypedef->src_addr_type = DMA_ADDRESS_NO_CHANGE;
    W25q64jv_hd->receive_dma_inittypedef->dst_addr_type = DMA_ADDRESS_INCREASE;
    W25q64jv_hd->receive_dma_inittypedef->src_width = DMA_WIDTH32;
    W25q64jv_hd->receive_dma_inittypedef->dst_width = DMA_WIDTH32;
    W25q64jv_hd->receive_dma_inittypedef->dst_per = DMA_QSPI_RX_REQ;
    W25q64jv_hd->receive_dma_inittypedef->src_per = DMA_QSPI_RX_REQ;

    W25q64jv_hd->receive_dma_inittypedef->fifo_mode_en = DISABLE;
    W25q64jv_hd->receive_dma_inittypedef->max_abrst = 0;
    W25q64jv_hd->receive_dma_inittypedef->src_handshaking_type = DMA_HW_HANDSHAKE;
    W25q64jv_hd->receive_dma_inittypedef->dst_handshaking_type = DMA_HW_HANDSHAKE;
    W25q64jv_hd->receive_dma_inittypedef->chanel_priority = DMA_PRIORITY0;
    W25q64jv_hd->receive_dma_inittypedef->int_en = DISABLE;

    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Init(DMA, dma_channel, W25q64jv_hd->receive_dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    W25q64jv_hd->receive_dma_flag = 1;
    W25q64jv_hd->receive_dma_channel = dma_channel;

    return 1;
}
