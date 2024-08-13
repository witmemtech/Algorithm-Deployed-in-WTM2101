#ifdef CONFIG_RAM_KWS_SPI

#include "spi_transfer_protocol.h"

extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );
int lframe_ctol_init(Lframe_ctol *lframe,void *user_data)
{
    int ret = 1;
    if (lframe == NULL || user_data == NULL) 
    {
        return -1;
    }    
    
    /*Ĭ���Ǵ��豸*/
    lframe->device_type = LFRMAE_SLAVE;
    /*Ĭ��֧�ֿɿ�����*/
    lframe->qos_level = P2P_TRANSFER_PROTOCOL_LIKE_TCP;
    /*��ǰʵ�ʴ���Ĵ�С*/
    lframe->current_length = LFRAME_TRANSFER_SIZE * LFRAME_TRANSFER_SIZE_COUNT + LFRAEM_TRANSFER_ALIGMENT_SIZE;
    /*Ĭ�ϵ�Ӳ��������SPI*/
    lframe->hardware_type = P2P_SPI;

    /*д����*/
    lframe->slist = vfs_list_head();
    if (lframe->slist == NULL)  
    {
        ret = -2;
        goto error;
    }
    /*������*/
    lframe->rlist = vfs_list_head();
    if (lframe->rlist == NULL)
    {
        ret = -3;
        goto error;
    }
    /*�������*/
    lframe->alist = NULL;

    /*���պͷ��͹�ϣ��ֵ*/
    lframe->send_hash = 0x00;
    lframe->rece_hash = 0x00;

    /*����ʧ��,��ʱʱ��*/
    switch(lframe->hardware_type)
    {
        case P2P_SPI:
          lframe->send_timer_timeout_microseoncd = 100;
          lframe->rece_timer_timeout_microseoncd = 0;
          break;
        case P2P_I2C:
          lframe->send_timer_timeout_microseoncd = 100;
          lframe->rece_timer_timeout_microseoncd = 0;
          break;
        case P2P_UART:
          lframe->send_timer_timeout_microseoncd = 100;
          lframe->rece_timer_timeout_microseoncd = 0;
          break;
        case P2P_I2S:
          lframe->send_timer_timeout_microseoncd = 100;
          lframe->rece_timer_timeout_microseoncd = 0;
          break;
    }
    /*���ձ�־,���˵����豸ʹ��*/
    lframe->rece_flag = NULL;
    /*���λ�����,���˵����豸ʹ��*/
    lframe->ring_buffer = NULL;

    /*�������ݵ�buffer*/
    lframe->rece_buff.msg = (uint8_t *)pvPortMalloc(RECE_BUFF_SIZE);
    if(!lframe->rece_buff.msg)
    {
        ret = -4;
        goto error;
    }
    memset(lframe->rece_buff.msg,0,RECE_BUFF_SIZE);
    lframe->rece_buff.msg_size = RECE_BUFF_SIZE;
    lframe->rece_buff.index = 0;
    
    /*�������ݵ�buffer*/
    lframe->send_buff.msg = (uint8_t *)pvPortMalloc(SEND_BUFF_SIZE);
    if(!lframe->send_buff.msg)
    {
        ret = -5;
        goto error;
    }
    memset(lframe->send_buff.msg,0,SEND_BUFF_SIZE);
    lframe->send_buff.msg_size = SEND_BUFF_SIZE;
    lframe->send_buff.index = 0;

    lframe->user_data = user_data;

    return ret;

error:
    if(lframe->slist)
      vfs_list_del(lframe->slist);
    if(lframe->rlist)
      vfs_list_del(lframe->rlist);
    if(lframe->rece_buff.msg)
      vPortFree(lframe->rece_buff.msg);
    if(lframe->send_buff.msg)
      vPortFree(lframe->send_buff.msg);

    return ret;
}

int lframe_core_status_set(Lframe_ctol *lframe, int mode)
{
    if (lframe == NULL)  return -1;
    return 1;
}

int lframe_alist_packet_handler(Lframe_ctol *lframe,int command,int value,int hash)
{
    Frame_head ack_packet;
    unsigned int sum = 0;

    if (lframe == NULL) return -1;
    ack_packet.header = 0x78;
    ack_packet.extern_order.ctl_order.command = command;
    ack_packet.extern_order.ctl_order.value = value;
    ack_packet.total_length = sizeof(Frame_head);
    ack_packet.hash = hash;
    ack_packet.crc32 = 0;
    sum = crc32_compute_table_lookup((uint8_t *)&ack_packet, sizeof(Frame_head));
    ack_packet.crc32 = sum;

    if(!(lframe->alist->count))
        vfs_list_push_for_data_safe(lframe->alist, (uint8_t *)&ack_packet, 0, sizeof(Frame_head));
    return 1;
}

int lframe_buf_stoken(uint8_t *buf,int len,int offset)
{
    int total_len = 0;
    unsigned int old_sum = 0,new_sum = 0;
    
    for(;offset < len;offset++)
    {
        if(offset + sizeof(Frame_head) > len)
            return -1;
        if(LFREME_HEAD_HEADER_GET((Frame_head *)(buf+offset)) == 0x78)
        {
            total_len = LFREME_HEAD_LENGTH_GET((Frame_head *)(buf+offset));
            if((total_len < sizeof(Frame_head)) || ((total_len + offset) > len))
                continue;
            
            old_sum = LFREME_HEAD_CHECKSUM_GET((Frame_head *)(buf+offset));
            LFREME_HEAD_CHECKSUM_SET((Frame_head *)(buf+offset),0);
            new_sum = crc32_compute_table_lookup((uint8_t *)(buf+offset),total_len);
            LFREME_HEAD_CHECKSUM_SET((Frame_head *)(buf+offset),old_sum);
            if(old_sum == new_sum)
              return offset;
        }
    }

    return -2;
}

int lframe_receive_packet_handler(Lframe_ctol *lframe)
{
    int total_len = 0,_temp_length = 0;
    int ret = 0,_temp_index = 0,hash = 0;
    static int error = 0;

    do
    {
        /*����֡ͷѰ�Һ��ʵ����ݰ�*/
        ret = lframe_buf_stoken(lframe->rece_buff.msg,lframe->current_length,_temp_index);
        if(ret >= 0)
        {
            error = 0;
            total_len = LFREME_HEAD_LENGTH_GET((Frame_head *)(lframe->rece_buff.msg + ret));
            if(total_len == sizeof(Frame_head))
            {
                /*���������*/
                if(LFREME_HEAD_EXTERN_CTL_ORDER_COMMAND_GET((Frame_head *)(lframe->rece_buff.msg + ret)) == ACK_COMMAND)
                {
                    hash = LFREME_HEAD_HASH_GET((Frame_head *)(lframe->rece_buff.msg + ret));
                    if(lframe->send_hash == hash)
                    {
                        vfs_list_remove_safe(lframe->slist,0);
                        lframe->send_hash = 0;
                        lframe->send_buff.index = 0;
                        memset(lframe->send_buff.msg,0,lframe->send_buff.msg_size);
                    }
                }
            }
            else
            {
                /*�������ݰ�*/
                if(lframe->call_info.wci_reav_packet)
                {
                    if(lframe->rece_hash != LFREME_HEAD_HASH_GET((Frame_head *)(lframe->rece_buff.msg + ret)))
                    {
                        lframe->rece_hash = LFREME_HEAD_HASH_GET((Frame_head *)(lframe->rece_buff.msg + ret));
                        lframe->call_info.wci_reav_packet(lframe,(lframe->rece_buff.msg + ret + sizeof(Frame_head)),total_len - lframe->rece_buff.msg[ret+total_len-1] - sizeof(Frame_head));
                    }
                }
                lframe_alist_packet_handler(lframe,ACK_COMMAND,0,lframe->rece_hash);
            }
        }
        _temp_index += ret + total_len;
    }while(ret >= 0);

    /*�쳣��ֹ����*/
    error++;
    if(error > 10)
    {
        if(lframe->call_info.change_mode)
        {
            lframe->call_info.change_mode(lframe,0);
        }
        error = 0;
    }

    return 1;
}

int lframe_sendpacket_handler(Lframe_ctol *lframe)
{
    unsigned int aligment_len = 0, hash = 0,sum = 0;
    unsigned char temp[16]={0}; 
    static uint8_t randdom = 0;  
    
    memset(temp, 0, sizeof(temp));
    /*��������*/
    aligment_len = lframe->slist->next->count % 8;
    if (aligment_len == 0)  aligment_len = 8;
    else if (aligment_len == 7) aligment_len = 9;
    else
        aligment_len = 8 - aligment_len;
    temp[aligment_len - 2] = __get_rv_cycle() % 256; /*�����ڶ�λ�����*/
    if(randdom == temp[aligment_len - 2])
       temp[aligment_len - 2] = ++randdom;
    else
       randdom = temp[aligment_len - 2];
    temp[aligment_len - 1] = aligment_len; /*�����ֽڵ����*/

    /*�������*/
    LFREME_HEAD_HEADER_SET((Frame_head *)lframe->send_buff.msg,LFRAME_RECOGNISE_HEAER);
    LFREME_HEAD_EXTERN_CTL_ORDER_COMMAND_SET((Frame_head *)lframe->send_buff.msg,APPLICATION_COMMAND);
    LFREME_HEAD_EXTERN_CTL_ORDER_VALUE_SET((Frame_head *)lframe->send_buff.msg,0);
    LFREME_HEAD_LENGTH_SET((Frame_head *)lframe->send_buff.msg, (lframe->slist->next->count + sizeof(Frame_head) + aligment_len));
    lframe->send_buff.index = LFREME_HEAD_LENGTH_GET((Frame_head *)lframe->send_buff.msg);
    
    memcpy(lframe->send_buff.msg + sizeof(Frame_head), lframe->slist->next->data, lframe->slist->next->count);
    memcpy(lframe->send_buff.msg + sizeof(Frame_head) + lframe->slist->next->count, temp, aligment_len);
    hash = wslhash_bkd((lframe->send_buff.msg) + sizeof(Frame_head), lframe->slist->next->count + aligment_len);
    lframe->send_hash = hash;
    LFREME_HEAD_HASH_SET((Frame_head *)lframe->send_buff.msg, hash);
    LFREME_HEAD_CHECKSUM_SET((Frame_head *)lframe->send_buff.msg,0);
    sum = crc32_compute_table_lookup(lframe->send_buff.msg, lframe->send_buff.index);
    LFREME_HEAD_CHECKSUM_SET((Frame_head *)lframe->send_buff.msg, sum);
}

int lframe_slist_handler(Lframe_ctol *lframe)
{
    int ret = 0;  

    if (lframe == NULL) 
        return-1; 
    if (lframe->call_info.transfer == NULL) 
        return -2;
    
    /*�������buffer��NULL,��䷢��buffer*/
    if(lframe->send_buff.index == 0)
        lframe_sendpacket_handler(lframe);

    if(lframe->device_type != LFRAME_ENDPOINT)
    {
        /*�����豸���ö�д�ӿ�*/
        ret = lframe->call_info.transfer_and_recv(lframe,lframe->send_buff.msg, lframe->send_buff.index,lframe->rece_buff.msg,lframe->current_length);
        /*�������buffer*/
        lframe_receive_packet_handler(lframe);
    }
    else 
    {
        /*�˵����豸���÷��ͽӿ�*/
        lframe->call_info.transfer(lframe,lframe->send_buff.msg, lframe->send_buff.index);
    }
  
    return 1;
}

int lframe_alist_handler(Lframe_ctol *lframe)
{
    int ret = 0;
    if (lframe == NULL)  return -1;
    if (lframe->call_info.transfer_and_recv == NULL)  return -2;

    /*���д�����д����͵������ҷ���buffer�ǿ�,���Ȱ�д�����е��������뷢��buffer*/
    if ((lframe->slist->count > 0) && (lframe->send_buff.index == 0))
        lframe_sendpacket_handler(lframe);
    
    /*��������뷢��buffer*/
    memcpy(lframe->send_buff.msg + lframe->send_buff.index,lframe->alist->next->data,lframe->alist->next->count);
    ret = lframe->call_info.transfer_and_recv(lframe,lframe->send_buff.msg,lframe->send_buff.index + lframe->alist->next->count,lframe->rece_buff.msg,lframe->current_length);
    memset(lframe->send_buff.msg + lframe->send_buff.index,0,lframe->alist->next->count);
    /*�����ACK����,���ͺ�ɾ��*/
    if(LFREME_HEAD_EXTERN_CTL_ORDER_COMMAND_GET((Frame_head *)(lframe->alist->next->data)) == ACK_COMMAND)
        vfs_list_remove_safe(lframe->alist, 0);
    
    /*�������buffer������*/
    lframe_receive_packet_handler(lframe);
    
    return 1;
}

int lframe_rlist_handler(Lframe_ctol *lframe)
{
    int ret = 0;
    if (lframe == NULL)  return -1;
    if (lframe->call_info.transfer_and_recv == NULL)  return -2;
    
    /*���÷��ͺͽ��սӿ�*/
    ret = lframe->call_info.transfer_and_recv(lframe,NULL, 0,lframe->rece_buff.msg,lframe->current_length);
    /*�������buffer*/
    lframe_receive_packet_handler(lframe);
}

int lframe_core(Lframe_ctol *lframe)
{
    int ret = 0;

    while (1)
    {
        if(lframe->device_type != LFRAME_ENDPOINT)
        {
            /*�յ��������˳�*/
            if((lframe->rlist->count != 0))
            {
                break;
            }
            /*��������*/
            if (lframe->alist->count > 0)
            {
                ret = lframe_alist_handler(lframe);
            }
            /*����������*/
            else if (lframe->slist->count > 0)
            {
                ret = lframe_slist_handler(lframe);
                if (ret < 0) {
                    vfs_list_remove_safe(lframe->slist, 0);
                    memset(lframe->send_buff.msg,0,lframe->send_buff.msg_size);    
                }
            }
            /*ֻ������*/
            else 
            {
                lframe_rlist_handler(lframe);
                break;
            }
        }
        else if(lframe->device_type == LFRAME_ENDPOINT)
        {
            /*����������ݻ��߽������ݳ�ʱ*/
            if (*(lframe->rece_flag))
            {
                /*�����ٽ���,�ӻ��λ�������ȡ����*/
                __disable_irq();
                ret = Ring_Cache_Pop(lframe->ring_buffer, lframe->rece_buff.msg, RING_CACHE_SIZE);
                *(lframe->rece_flag) = 0;
                __enable_irq();
                lframe->current_length = ret;
                /*�������buffer*/
                ret = lframe_receive_packet_handler(lframe);
            }
            /*��������*/
            if(lframe->alist->count > 0)
            {
                /*��������*/
                lframe->call_info.transfer(lframe,lframe->alist->next->data, lframe->alist->next->count);
                vfs_list_remove_safe(lframe->alist, 0);
            }
            /*����������*/
            if (lframe->slist->count > 0)
            {
                ret = lframe_slist_handler(lframe);
                if (ret < 0) {
                    vfs_list_remove_safe(lframe->slist, 0);
                    memset(lframe->send_buff.msg,0,lframe->send_buff.msg_size);    
                }
            }
            if((lframe->rlist->count != 0) || (lframe->slist->count == 0))
                break;
        }
    }

    return 1;
}

#endif