#ifdef CONFIG_RAM_KWS_SPI

#include "dspi.h"
#include "wtm2101_mmap.h"

extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );

/*发送和接收dma链表的首地址*/
static uint32_t spi_transmit_llp_address = 0;
static uint32_t spi_receive_llp_address = 0;
/*spi slave的cs中断标志*/
volatile static uint8_t gpio_spi_slave_flag = 0;

void GPIO_IRQHandler(void)
{
    GPIO_IT_ClrPending(GPIOA, GPIO_PIN_14);
    gpio_spi_slave_flag = 1;
}

static void system_delay_us(uint32_t time)
{
  unsigned long long ahbclock = RCC_Get_SYSClk()/(RCC_AHB_Get_ClkDiv()+1);
  unsigned long long temp = 0;
  temp = __get_rv_cycle();
  do{
  }while((temp + time * ahbclock/1000000) > __get_rv_cycle());
}

int spis_send_dma_init()
{
    DMA_InitTypeDef dma_inittypedef;

    /*dma clear all interrupt flag*/
    DMA_Clear_All_Interrupt_Cmd(DMA);
    dma_inittypedef.llp_src_en = ENABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;
    dma_inittypedef.direction = MEM_TO_PER_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE1;
    dma_inittypedef.dst_msize = DMA_MSIZE4;
    dma_inittypedef.src_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.src_width = DMA_WIDTH8;
    dma_inittypedef.dst_width = DMA_WIDTH8;

    dma_inittypedef.dst_per = DMA_SPIS_TX_REQ;
    dma_inittypedef.src_per = DMA_SPIS_TX_REQ;

    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;
    dma_inittypedef.int_en = ENABLE;
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Init(DMA, DMA_CHANNEL1, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    spi_transmit_llp_address = (uint32_t)(DMA_LlpTypeDef *)pvPortMalloc(sizeof(DMA_LlpTypeDef) * LFRAME_TRANSFER_SIZE_MAX_COUNT);
    if(!spi_transmit_llp_address)
    {    
        DMA_Set_Enable_Cmd(DMA, DISABLE);
        memset(&dma_inittypedef,0,sizeof(DMA_InitTypeDef));
        DMA_Init(DMA, DMA_CHANNEL1, &dma_inittypedef);
        DMA_Set_Enable_Cmd(DMA, ENABLE);
        return -1;
    }

    return 1;
}

static void spis_send_dma_llp_config(unsigned char *send_buf,int send_length,int dma_channel)
{
    int _size = 0,count = 0;
    uint32_t ctl0_cache = 0,dma_llp_address = 0;

    _size = sizeof(DMA_LlpTypeDef);
    count = (send_length - LFRAEM_TRANSFER_ALIGMENT_SIZE) / LFRAME_TRANSFER_SIZE;

    switch (dma_channel) {
        case DMA_CHANNEL0: ctl0_cache = (uint32_t)DMA->CTL0; break;
        case DMA_CHANNEL1: ctl0_cache = (uint32_t)DMA->CTL1; break;
        case DMA_CHANNEL2: ctl0_cache = (uint32_t)DMA->CTL2; break;
        case DMA_CHANNEL3: ctl0_cache = (uint32_t)DMA->CTL3; break;
        case DMA_CHANNEL4: ctl0_cache = (uint32_t)DMA->CTL4; break;
        case DMA_CHANNEL5: ctl0_cache = (uint32_t)DMA->CTL5; break;
        default:break;
    }
    
    /*配置发送dma的链表*/
    dma_llp_address = mmap_to_sys(spi_transmit_llp_address);
    for(int i = 0;i < count;i++)
    {
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->llp         = dma_llp_address + (_size * (i+1));
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->src         = mmap_to_sys((uint32_t)(send_buf + LFRAME_TRANSFER_SIZE * i));             
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->dst         = (uint32_t)&SPIS->DR;                           
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->ctl_reg_high= LFRAME_TRANSFER_SIZE;                                      
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->ctl_reg_low = ctl0_cache;
    }

    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->llp         = 0;
    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->src         = mmap_to_sys((uint32_t)(send_buf + LFRAME_TRANSFER_SIZE * count));               
    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->dst         = (uint32_t)&SPIS->DR;                           
    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->ctl_reg_high= LFRAEM_TRANSFER_ALIGMENT_SIZE;                                      
    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->ctl_reg_low = ctl0_cache;
} 

int spis_receive_dma_init(void)
{
    DMA_InitTypeDef dma_inittypedef;

    /*dma clear all interrupt flag*/
    DMA_Clear_All_Interrupt_Cmd(DMA);
    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = ENABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;
    dma_inittypedef.direction = PER_TO_MEM_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE4;
    dma_inittypedef.dst_msize = DMA_MSIZE1;
    dma_inittypedef.src_addr_type = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_width = DMA_WIDTH8;
    dma_inittypedef.src_width = DMA_WIDTH8;

    dma_inittypedef.dst_per = DMA_SPIS_RX_REQ;
    dma_inittypedef.src_per = DMA_SPIS_RX_REQ;
    
    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;
    dma_inittypedef.int_en = ENABLE;
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Init(DMA, DMA_CHANNEL3, &dma_inittypedef);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    spi_receive_llp_address = (uint32_t)(DMA_LlpTypeDef *)pvPortMalloc(sizeof(DMA_LlpTypeDef) * (LFRAME_TRANSFER_SIZE_MAX_COUNT));
    if(!spi_receive_llp_address)
    {    
        DMA_Set_Enable_Cmd(DMA, DISABLE);
        memset(&dma_inittypedef,0,sizeof(DMA_InitTypeDef));
        DMA_Init(DMA, DMA_CHANNEL3, &dma_inittypedef);
        DMA_Set_Enable_Cmd(DMA, ENABLE);
        return -1;
    }

    return 1;
}

static void spis_receive_dma_llp_config(unsigned char *receive_buf,int receive_length,int dma_channel)
{
    int _size = 0,count = 0;
    uint32_t ctl0_cache = 0,dma_llp_address = 0;
    
    _size = sizeof(DMA_LlpTypeDef);
    count = (receive_length - LFRAEM_TRANSFER_ALIGMENT_SIZE) / LFRAME_TRANSFER_SIZE;

    switch (dma_channel) {
        case DMA_CHANNEL0: ctl0_cache = (uint32_t)DMA->CTL0; break;
        case DMA_CHANNEL1: ctl0_cache = (uint32_t)DMA->CTL1; break;
        case DMA_CHANNEL2: ctl0_cache = (uint32_t)DMA->CTL2; break;
        case DMA_CHANNEL3: ctl0_cache = (uint32_t)DMA->CTL3; break;
        case DMA_CHANNEL4: ctl0_cache = (uint32_t)DMA->CTL4; break;
        case DMA_CHANNEL5: ctl0_cache = (uint32_t)DMA->CTL5; break;
        default:break;
    }
    
    /*配置接收dma的链表*/
    dma_llp_address = mmap_to_sys(spi_receive_llp_address);
    for(int i = 0;i < count;i++)
    {
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->llp         = dma_llp_address + (_size * (i+1));
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->src         = (uint32_t)&SPIS->DR;             
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->dst         = mmap_to_sys((uint32_t)(receive_buf + LFRAME_TRANSFER_SIZE * i));                           
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->ctl_reg_high= LFRAME_TRANSFER_SIZE;                                      
        ((DMA_LlpTypeDef *)(dma_llp_address + _size * i))->ctl_reg_low = ctl0_cache;
    }

    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->llp         = 0;
    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->src         = (uint32_t)&SPIS->DR;             
    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->dst         = mmap_to_sys((uint32_t)(receive_buf + LFRAME_TRANSFER_SIZE * count));                           
    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->ctl_reg_high= LFRAEM_TRANSFER_ALIGMENT_SIZE;                                      
    ((DMA_LlpTypeDef *)(dma_llp_address + _size * count))->ctl_reg_low = ctl0_cache;
}

int spi_slave_open(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef spi_init_type;
    GPIO_IT_InitTypeDef GPIO_IT_InitStructure;
    
    /*初始化时钟*/
    RCC_CLK_EN_Ctl(RCC_SPIS_PCLKEN,ENABLE);
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN,ENABLE);
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN,ENABLE);
    RCC_Peri_Rst(RCC_SPIS_RSTN);
    RCC_Peri_Rst(RCC_DMA_RSTN);
    RCC_Peri_Rst(RCC_GPIO_RSTN);

    /*初始化 spl slave的mosi,miso,clk*/
    GPIO_InitStructure.Pin = GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17;
    GPIO_InitStructure.Alternate = GPIO_AF15_SPIS | GPIO_AF16_SPIS | GPIO_AF17_SPIS;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /*初始化cs*/
    GPIO_InitStructure.Pin = GPIO_PIN_14;
    GPIO_InitStructure.Alternate = GPIO_AF14_GPIO;
    GPIO_InitStructure.Mode = GPIO_MODE_INPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*初始化spi slave*/
    spi_init_type.cpol = SPI_CPOL_0;
    spi_init_type.cpha = SPI_CPHA_1;
    spi_init_type.datasize = SPI_DATASIZE_8B;
    SPI_Init(SPIS, &spi_init_type);
   
    /*发送和接收dma初始化*/
    SPI_Dma_Receive_Cmd(SPIS,ENABLE);
    SPI_Dma_Send_Cmd(SPIS,ENABLE);
    SPI_Set_Dma_Transmit_Data_level(SPIS,4);
    SPI_Set_Dma_Receive_Data_level(SPIS,3);
    if(spis_receive_dma_init() < 0)
    {  
      return -1;
    }
    if(spis_send_dma_init() < 0)
    {
      return -2;
    }
    
    /*cs中断初始化*/
    ECLIC_ClearPendingIRQ(GPIO_IRQn);
    ECLIC_SetPriorityIRQ(GPIO_IRQn, 1);
    ECLIC_SetTrigIRQ(GPIO_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(GPIO_IRQn);

    GPIO_IT_InitStructure.Pin = GPIO_PIN_14;
    GPIO_IT_InitStructure.Trig = GPIO_IT_TRIG_FALLING;
    GPIO_IT_InitStructure.State = ENABLE;
    GPIO_IT_Cfg(GPIOA, &GPIO_IT_InitStructure);
    
    GPIO_IT_MskCfg(DISABLE);
    GPIO_IT_PinMskCfg(GPIOA,GPIO_PIN_14,DISABLE);
    PMU_Set_Ie_Msk(PMU,PMU_GPIO_IMSK | PMU_GPIO_EMSK,ENABLE);

    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);

    while(GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_14) == GPIO_PIN_RESET);
    SPI_Cmd(SPIS, ENABLE);
    return 0;
}

static int dspi_reav_packet(struct _Lframe_ctol * wframe, unsigned char *buf, int len)
{
    int ret = 0;
    Dspi *dspi_hd = (Dspi *)wframe->user_data;
    if (dspi_hd == NULL || buf == NULL) return -1;

    if(len)
      ret = vfs_list_push_for_data_safe(dspi_hd->rlist, buf, 0, len);
    
    return ret;
}

static int dspi_change_mode(struct _Lframe_ctol * lframe, uint to_mode)
{
    Dspi *dspi_hd = (Dspi *)lframe->user_data;

    SPI_Cmd(SPIS, DISABLE);
    while(GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_14) == GPIO_PIN_RESET);
    SPI_Cmd(SPIS, ENABLE);

    return 1;
}

static int dspi_send_data(struct _Lframe_ctol * wframe,unsigned char *data, int len)
{
    return 1;
}

static int dspi_transfer_and_recv(struct _Lframe_ctol * wframe,unsigned char *send_buf, int send_length,unsigned char *receive_buf, int rece_length)
{
    int ret = 1,count = 0;
    Dspi *dspi_hd = (Dspi *)wframe->user_data;

    /*如果片选信号先触发,当前传输无效,等待下一次传输*/
    if(gpio_spi_slave_flag)
        gpio_spi_slave_flag = 0;
    while(GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_14) == GPIO_PIN_RESET);

    /*配置发送DMA的链表*/
    {
        spis_send_dma_llp_config(send_buf,wframe->current_length,DMA_CHANNEL1);

        DMA_Set_Addr(DMA, DMA_CHANNEL1, mmap_to_sys((uint32_t) send_buf), (uint32_t)&(dspi_hd->spi_hd->DR), 0, mmap_to_sys(spi_transmit_llp_address));
    }

    /*配置接收DMA的链表*/
    {
        memset(receive_buf,wframe->rece_buff.msg_size,0);
        spis_receive_dma_llp_config(receive_buf,wframe->current_length,DMA_CHANNEL3);
  
        DMA_Set_Addr(DMA, DMA_CHANNEL3, (uint32_t)&(dspi_hd->spi_hd->DR), mmap_to_sys((uint32_t)receive_buf), 0, mmap_to_sys(spi_receive_llp_address));
    }

    /*等待片选信号触发,超时时间由send_timer_timeout_microseoncd设置*/
    while(gpio_spi_slave_flag == 0)
    {
        /*100ms timeout*/
        if(++count > (dspi_hd->frame_ctl.send_timer_timeout_microseoncd * 1000))
            break;
        system_delay_us(1);
    } 
    if(count >= (dspi_hd->frame_ctl.send_timer_timeout_microseoncd * 1000)) 
        return -1;
    
    /*开始传输*/
    if((gpio_spi_slave_flag == 1))
    {
        DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL3 | DMA_CHANNEL1, ENABLE);
        gpio_spi_slave_flag = 0;
        count = 0;
        do
        {
            if(GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_14) || ((++count) > (dspi_hd->frame_ctl.send_timer_timeout_microseoncd * 1000)))
              break;
            system_delay_us(1);
        }while(1);
    }
    if(count >= (dspi_hd->frame_ctl.send_timer_timeout_microseoncd * 1000)) 
        return -2;   
    
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL3 | DMA_CHANNEL1, DISABLE);
     
    return ret;
}

extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv ); 
Dspi *dspi_open(void)
{
    int ret = 0;
    Dspi *dspi_hd = NULL;

    dspi_hd = (Dspi *)pvPortMalloc(sizeof(Dspi));
    if(!dspi_hd) return NULL;
    
    /*硬件初始化*/
    spi_transmit_llp_address = 0;
    spi_receive_llp_address = 0;
    ret = spi_slave_open();
    if(ret < 0)
    {    
        return NULL;
    }
    dspi_hd->spi_hd = SPIS;
    
    /*初始化命令队列*/
    dspi_hd->alist = vfs_list_head();
    if(!(dspi_hd->alist))
    {
        vPortFree((DMA_LlpTypeDef *)spi_transmit_llp_address);
        vPortFree((DMA_LlpTypeDef *)spi_receive_llp_address);
        vPortFree(dspi_hd);
        return NULL;
    }

    /*初始化协议栈*/
    ret = lframe_ctol_init(&(dspi_hd->frame_ctl),dspi_hd);
    if(ret < 0) 
    {
        vPortFree((DMA_LlpTypeDef *)spi_transmit_llp_address);
        vPortFree((DMA_LlpTypeDef *)spi_receive_llp_address);
        vPortFree(dspi_hd->alist);
        vPortFree(dspi_hd);
        return NULL;
    }
    dspi_hd->rlist = dspi_hd->frame_ctl.rlist;
    dspi_hd->slist = dspi_hd->frame_ctl.slist;
    dspi_hd->frame_ctl.alist = dspi_hd->alist;

    /*协议栈硬件接口层*/
    dspi_hd->frame_ctl.call_info.wci_reav_packet = dspi_reav_packet;
    dspi_hd->frame_ctl.call_info.change_mode = dspi_change_mode;
    dspi_hd->frame_ctl.call_info.transfer = dspi_send_data;
    dspi_hd->frame_ctl.call_info.transfer_and_recv = dspi_transfer_and_recv;

    //lframe_core(&(dspi_hd->frame_ctl));

    return dspi_hd;
}

int dspi_write(Dspi *dspi_hd,uint8_t *buf,int len)
{
    int ret = 1;
    if (dspi_hd == NULL || buf == NULL)
      return -1;

    ret = vfs_list_push_for_data_safe(dspi_hd->slist, buf, 0, len);
    return ret;
}

int dspi_read(Dspi *dspi_hd,uint8_t *buf,int *len)
{
    int ret = 0;
    if (dspi_hd == NULL || buf == NULL)
      return -1;

    ret = dspi_hd->rlist->count;
    if(ret > 0)
    {
        *len = dspi_hd->rlist->next->count;
        memcpy(buf,dspi_hd->rlist->next->data,*len);
        vfs_list_remove_safe(dspi_hd->rlist,0);
    }

    return ret;
}

int dspi_ctl(Dspi *dspi_hd,int command, ...)
{
    va_list ParamList;
    int value = 0;

    if (dspi_hd == NULL) return -1;
    va_start(ParamList, command);

    if (EXCHANGE_COMMAND & command) {
        value = va_arg(ParamList, int);
        lframe_alist_packet_handler(&(dspi_hd->frame_ctl),EXCHANGE_COMMAND,value,0);
    }
    if(DELETE_MESSAGE & command)
    {
        while(dspi_hd->rlist->count)
          vfs_list_remove_safe(dspi_hd->rlist,0);
    }

    va_end(ParamList);

    return 1;
}

#endif
