#include "duart.h"

static Duart *duart0_temp_hd = NULL,*duart1_temp_hd = NULL;
void UART0_IRQHandler(void)
{
    int size = 0;
    UART_IT_TypeDef uart_int_flag;

    uart_int_flag = UART_IT_GetStat(UART0);
    if(uart_int_flag == UART_IT_Received_Data_Available)
    {
        for(int i=0;i<4;i++)
        {
            if(UART_Flag_GetStatBit(UART0, UART_FLAG_DR))
            {
                Ring_Cache_Push(&duart0_temp_hd->ring_buffer,UART_ReceiveData(UART0));
            }
            else
            {
                break;
            }
        }
    }
    else if(uart_int_flag == UART_IT_Character_Timeout)
    {
        while (UART_Flag_GetStatBit(UART0, UART_FLAG_DR))
        {
            Ring_Cache_Push(&duart0_temp_hd->ring_buffer,UART_ReceiveData(UART0));
        }
        duart0_temp_hd->receive_flag = 1;
    }
}

void UART1_IRQHandler(void)
{
    int size = 0;
    UART_IT_TypeDef uart_int_flag;

    uart_int_flag = UART_IT_GetStat(UART1);
    if(uart_int_flag == UART_IT_Received_Data_Available)
    {
        for(int i=0;i<4;i++)
        {
            if(UART_Flag_GetStatBit(UART1, UART_FLAG_DR))
            {
                Ring_Cache_Push(&duart1_temp_hd->ring_buffer,UART_ReceiveData(UART1));
            }
            else
            {
                break;
            }
        }
    }
    else if(uart_int_flag == UART_IT_Character_Timeout)
    {
        while (UART_Flag_GetStatBit(UART1, UART_FLAG_DR))
        {
            Ring_Cache_Push(&duart1_temp_hd->ring_buffer,UART_ReceiveData(UART1));
        }
        duart1_temp_hd->receive_flag = 1;
    }
}

static void system_delay_us(uint32_t time)
{
  unsigned long long ahbclock = RCC_Get_SYSClk()/(RCC_AHB_Get_ClkDiv()+1);
  unsigned long long temp = 0;
  temp = __get_rv_cycle();
  do{
  }while((temp + time * ahbclock/1000000) > __get_rv_cycle());
}

static void uart_open(UART_TypeDef *uart)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_Uart1InitStructure;
    
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN,ENABLE);

    if(uart == UART0)
    {
        RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);
        GPIO_Uart1InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
        GPIO_Uart1InitStructure.Alternate = GPIO_AF4_UART0 | GPIO_AF5_UART0;
        
    }
    else if(uart == UART1)
    {
        RCC_CLK_EN_Ctl(RCC_UART1_CLKEN,ENABLE);
        GPIO_Uart1InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15;
        GPIO_Uart1InitStructure.Alternate = GPIO_AF14_UART1 | GPIO_AF15_UART1;
    }
    GPIO_Init(GPIOA, &GPIO_Uart1InitStructure);

    USART_InitStructure.BaudRate = 115200;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(uart, &USART_InitStructure);

    UART_IT_Cfg(uart, UART_IT_ERBFI, DISABLE);
    if(uart == UART0)
    {
        ECLIC_ClearPendingIRQ(UART0_IRQn);
        ECLIC_SetPriorityIRQ(UART0_IRQn, 2);
        ECLIC_SetTrigIRQ(UART0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(UART0_IRQn);
    }
    else if(uart == UART1)
    {
        ECLIC_ClearPendingIRQ(UART1_IRQn);
        ECLIC_SetPriorityIRQ(UART1_IRQn, 2);
        ECLIC_SetTrigIRQ(UART1_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(UART1_IRQn);
    }
    UART_RxFIFO_LevelCfg(uart, UART_RX_FIFO_1DIV2);
    UART_IT_Cfg(uart, UART_IT_ERBFI, ENABLE);
}

static int duart_reav_packet(struct _Lframe_ctol * wframe, unsigned char *buf, int len)
{
    int ret = 0;
    Duart *duart_hd = (Duart *)wframe->user_data;
    if (duart_hd == NULL || buf == NULL) return -1;

    if(len)
      ret = vfs_list_push_for_data_safe(duart_hd->rlist, buf, 0, len);
    
    return ret;
}

static int duart_change_mode(struct _Lframe_ctol * lframe, uint to_mode)
{
    return 0;
}

static int duart_send_data(struct _Lframe_ctol * wframe,unsigned char *data, int len)
{
    int ret = 0;
    Duart *duart_hd = (Duart *)wframe->user_data;
    if (duart_hd == NULL || data == NULL) return -1;

    for(int index = 0;index < len; index++)
    {
        UART_SendData(duart_hd->uart_hd,data[index]);
        while (UART_Flag_GetStatBit(duart_hd->uart_hd,UART_FLAG_TEMT) == RESET);
    }
    system_delay_us(SERIAL_SEND_DELAY_MS * 1000);

    return 1;
}

static int duart_transfer_and_recv(struct _Lframe_ctol * wframe,unsigned char *send_buf, int send_length,unsigned char *receive_buf, int rece_length)
{
    return 0;
}

extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv ); 
Duart *duart_open(UART_TypeDef *uart)
{
    int ret = 0;
    Duart *duart_hd = NULL;

    duart_hd = (Duart *)pvPortMalloc(sizeof(Duart));
    if(!duart_hd) return NULL;

    duart_hd->uart_hd = uart;
    
    duart_hd->alist = vfs_list_head();
    if(!(duart_hd->alist))
    {
        vPortFree(duart_hd);
        return NULL;
    }
    ret = lframe_ctol_init(&(duart_hd->frame_ctl),duart_hd);
    if(ret < 0) 
    {
        vPortFree(duart_hd->alist);
        vPortFree(duart_hd);
        return NULL;
    }
    duart_hd->frame_ctl.device_type = LFRAME_ENDPOINT;
    duart_hd->frame_ctl.hardware_type = P2P_UART;

    duart_hd->rlist = duart_hd->frame_ctl.rlist;
    duart_hd->slist = duart_hd->frame_ctl.slist;
    duart_hd->frame_ctl.alist = duart_hd->alist;

    duart_hd->frame_ctl.call_info.wci_reav_packet = duart_reav_packet;
    duart_hd->frame_ctl.call_info.change_mode = duart_change_mode;
    duart_hd->frame_ctl.call_info.transfer = duart_send_data;
    duart_hd->frame_ctl.call_info.transfer_and_recv = duart_transfer_and_recv;
    duart_hd->frame_ctl.rece_flag = &(duart_hd->receive_flag);
    duart_hd->frame_ctl.ring_buffer = &(duart_hd->ring_buffer);

    duart_hd->sync_async = LFRAME_ASYNC;
    Ring_Cache_Init(&duart_hd->ring_buffer,RING_CACHE_SIZE);
    if(duart_hd->uart_hd == UART0)
        duart0_temp_hd = duart_hd;
    else if(duart_hd->uart_hd == UART1)
        duart1_temp_hd = duart_hd;
    duart_hd->receive_flag = 0;

    uart_open(duart_hd->uart_hd);  
    //lframe_core(&(duart_hd->frame_ctl));

    return duart_hd;
}

int duart_write(Duart *duart_hd,uint8_t *buf,int len)
{
    int ret = 1;
    if (duart_hd == NULL || buf == NULL)
      return -1;

    ret = vfs_list_push_for_data_safe(duart_hd->slist, buf, 0, len);
    return ret;
}

int duart_read(Duart *duart_hd,uint8_t *buf,int *len,int timeout_ms)
{
    int ret = 0,count = 0;
    if (duart_hd == NULL || buf == NULL)
      return -1;
    

    if(duart_hd->sync_async == LFRAME_SYNC)
    {  
        while(count++ < timeout_ms)
        {
            lframe_core(&(duart_hd->frame_ctl));
            if(duart_hd->rlist->count > 0)
                break;
            system_delay_us(1000);
        }
        if(count >= timeout_ms)
            return 0;
    }

    ret = duart_hd->rlist->count;
    if(ret > 0)
    {
        *len = duart_hd->rlist->next->count;
        memcpy(buf,duart_hd->rlist->next->data,*len);
        vfs_list_remove_safe(duart_hd->rlist,0);
    }

    return ret;
}

int duart_ctl(Duart *duart_hd,int command, ...)
{
    va_list ParamList;
    int value = 0;

    if (duart_hd == NULL) return -1;
    va_start(ParamList, command);

    if (SYNC_ASYNC_SET_COMMAND & command) {
        value = va_arg(ParamList, int);
        if(value == LFRAME_SYNC)
            duart_hd->sync_async = LFRAME_SYNC;
        else if(value == LFRAME_ASYNC)
            duart_hd->sync_async = LFRAME_ASYNC;
    }
   
    va_end(ParamList);

    return 1;
}
