/**
* @file    hal_uart.c
* @brief   The Source Codes for the hal_uart Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

/** Includes */
#include "hal_uart.h"
#include "timer.h"

#define HAL_UART_MALLOC(SIZE)  pvPortMalloc(SIZE)
#define HAL_UART_FREE(ADDRESS) vPortFree(ADDRESS)
#define HAL_UART_HELP_TIMER   TIMER0

static void hal_uart_gpio_init(Hal_Uart_InitTypeDef *uart_instance);
static void hal_uart_gpio_uninit(Hal_Uart_InitTypeDef *uart_instance);
static void hal_uart_send_dma_init(Hal_Uart_InitTypeDef *uart_instance);
static void hal_uart_dma_fifo_init(Hal_Uart_InitTypeDef *uart_instance,uint8_t *buffer,uint32_t size,uint32_t llp_count);
static void async_receive_handler(struct Hal_Uart_InitTypeDef *uart_instance);
static void send_dma_finish_handler(struct Hal_Uart_InitTypeDef *uart_instance);
static void uart_timeout_handler(struct Hal_Uart_InitTypeDef *uart_instance);
static void timer_init(struct Hal_Uart_InitTypeDef *uart_instance);
static void timer_uninit(struct Hal_Uart_InitTypeDef *uart_instance);

#define HAL_UART_INSTANCE_NUMBER 2
static Hal_Uart_InitTypeDef hal_uart_instance[HAL_UART_INSTANCE_NUMBER];

Hal_Uart_InitTypeDef* hal_uart_instance_get(Hal_Uart_Instance_Typedef number)
{
    if(number < HAL_UART_INSTANCE0 || number > HAL_UART_INSTANCE1)
        return NULL;

    return (&hal_uart_instance[number]);
}

__attribute__((weak)) void DMA_IRQHandler(void)
{
    /*the dma interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);

    if(DMA_Get_Transfer_Interrupt_Status(DMA) & hal_uart_instance->send_dma.dma_channel)
    {
        DMA_Clear_Transfer_Interrupt_Cmd(DMA,hal_uart_instance->send_dma.dma_channel);
        /*data handle*/
        hal_uart_instance->data_handle_info.send_dma_finish_handler(hal_uart_instance);
    }
}

__attribute__((weak)) void UART0_IRQHandler(void)
{
    /*the uart0 interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
    hal_uart_instance->data_handle_info.async_receive_handler(hal_uart_instance);
}

__attribute__((weak)) void UART1_IRQHandler(void)
{
    /*the uart1 interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
    hal_uart_instance->data_handle_info.async_receive_handler(hal_uart_instance);
}

__attribute__((weak)) void TIMER0_IRQHandler(void)
{
    /*the timer0 interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);

    TIMER_Clear_Interrupt_Cmd(hal_uart_instance->timer_instance);
    TIMER_Set_Enable_Cmd(hal_uart_instance->timer_instance,DISABLE);
    hal_uart_instance->data_handle_info.uart_timeout_handler(hal_uart_instance);
}

__attribute__((weak)) void TIMER1_IRQHandler(void)
{
    /*the timer1 interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);

    TIMER_Clear_Interrupt_Cmd(hal_uart_instance->timer_instance);
    TIMER_Set_Enable_Cmd(hal_uart_instance->timer_instance,DISABLE);
    hal_uart_instance->data_handle_info.uart_timeout_handler(hal_uart_instance);
}

__attribute__((weak)) void TIMER2_IRQHandler(void)
{
    /*the timer2 interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);

    TIMER_Clear_Interrupt_Cmd(hal_uart_instance->timer_instance);
    TIMER_Set_Enable_Cmd(hal_uart_instance->timer_instance,DISABLE);
    hal_uart_instance->data_handle_info.uart_timeout_handler(hal_uart_instance);
}

__attribute__((weak)) void TIMER3_IRQHandler(void)
{
    /*the timer3 interrupt program must be overwrite in application in one time*/
    /*this is a demonstration for you to understand the data working flow*/
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);

    TIMER_Clear_Interrupt_Cmd(hal_uart_instance->timer_instance);
    TIMER_Set_Enable_Cmd(hal_uart_instance->timer_instance,DISABLE);
    hal_uart_instance->data_handle_info.uart_timeout_handler(hal_uart_instance);
}

int hal_uart_init(Hal_Uart_InitTypeDef *uart_instance,UART_TypeDef *address,UART_InitTypeDef *initstructure,Hal_Uart_Receive_Mode_Typedef flag,async_handler async_callback,FunctionalState send_dma_enable_flag)
{
    if(uart_instance == NULL)
        return -1;
    if((address != UART0) && (address != UART1))
        return -2;
    if((flag != HAL_UART_RECEIVE_SYNC) && (flag != HAL_UART_RECEIVE_ASYNC))
        return -3;

    uart_instance->instance = address;
    uart_instance->timer_instance = HAL_UART_HELP_TIMER;
    memcpy(&(uart_instance->initstructure),initstructure,sizeof(UART_InitTypeDef));
    if(uart_instance->instance == UART0)
    {
        uart_instance->io.uart_tx = GPIO_PIN_4;
        uart_instance->io.uart_rx = GPIO_PIN_5;
        uart_instance->io.uart_tx_af = GPIO_AF4_UART0;
        uart_instance->io.uart_rx_af = GPIO_AF5_UART0;
    }
    else if(uart_instance->instance == UART1)
    {
        uart_instance->io.uart_tx = GPIO_PIN_14;
        uart_instance->io.uart_rx = GPIO_PIN_15;
        uart_instance->io.uart_tx_af = GPIO_AF14_UART1;
        uart_instance->io.uart_rx_af = GPIO_AF15_UART1;
    }

    uart_instance->sync_async_flag = flag;
    uart_instance->sync_receive_flag = FALSE;
    uart_instance->async_callback = NULL;
    uart_instance->async_callback = async_callback;

    uart_instance->data_handle_info.async_receive_handler = NULL;
    uart_instance->data_handle_info.send_dma_finish_handler = NULL;
    uart_instance->data_handle_info.uart_timeout_handler = NULL;

    uart_instance->send_dma.enable = send_dma_enable_flag;
    if(uart_instance->send_dma.enable == ENABLE)
    {
        uart_instance->send_dma.dma_channel = HAL_UART_SEND_DMA_DEFAULT_CHANNEL;
        {
            uart_instance->send_dma.config.llp_src_en          = ENABLE;
            uart_instance->send_dma.config.llp_dst_en          = ENABLE;
            uart_instance->send_dma.config.reload_src_en       = DISABLE;
            uart_instance->send_dma.config.reload_dst_en       = DISABLE;
            uart_instance->send_dma.config.src_msize           = DMA_MSIZE1;
            uart_instance->send_dma.config.dst_msize           = DMA_MSIZE1;
            uart_instance->send_dma.config.src_addr_type       = DMA_ADDRESS_INCREASE;
            uart_instance->send_dma.config.dst_addr_type       = DMA_ADDRESS_NO_CHANGE;
            uart_instance->send_dma.config.direction           = MEM_TO_PER_FLOW_CTOL_DMA;
            uart_instance->send_dma.config.src_width           = DMA_WIDTH8;
            uart_instance->send_dma.config.dst_width           = DMA_WIDTH8;
            uart_instance->send_dma.config.fifo_mode_en        = DISABLE;
            uart_instance->send_dma.config.max_abrst           = 0;
            uart_instance->send_dma.config.src_handshaking_type= DMA_HW_HANDSHAKE;
            uart_instance->send_dma.config.dst_handshaking_type= DMA_HW_HANDSHAKE;
            uart_instance->send_dma.config.chanel_priority     = DMA_PRIORITY0;
            uart_instance->send_dma.config.int_en              = ENABLE;

            if(uart_instance->instance == UART0)
            {
                uart_instance->send_dma.config.src_per = DMA_UART0_TX_REQ_OR_AUDIO_CH1;
                uart_instance->send_dma.config.dst_per = DMA_UART0_TX_REQ_OR_AUDIO_CH1;
            }
            else if(uart_instance->instance == UART1)
            {
                uart_instance->send_dma.config.src_per = DMA_UART1_TX_REQ_OR_AUDIO_CH2;
                uart_instance->send_dma.config.dst_per = DMA_UART1_TX_REQ_OR_AUDIO_CH2;
            }
        }
        uart_instance->send_dma.llp_cfg = NULL;
    }

    return 1;
}


int hal_uart_open(Hal_Uart_InitTypeDef *uart_instance)
{
    if(uart_instance == NULL)
        return -1;

    if(Ring_Cache_Init(&(uart_instance->cache.ring_buffer),HAL_UART_RECEIVE_RING_BUFFER_DEFAULT_SIZE) <= 0)
        return -2;

    if(uart_instance->instance == UART0)
        RCC_CLK_EN_Ctl(RCC_UART0_CLKEN, ENABLE);
    else if (uart_instance->instance == UART1)
        RCC_CLK_EN_Ctl(RCC_UART1_CLKEN, ENABLE);

    UART_Init(uart_instance->instance,&(uart_instance->initstructure));

    uart_instance->data_handle_info.async_receive_handler = async_receive_handler;
    uart_instance->data_handle_info.uart_timeout_handler = uart_timeout_handler;
    timer_init(uart_instance);

    UART_IT_Cfg(uart_instance->instance, UART_IT_ERBFI, DISABLE);
    if (uart_instance->instance == UART0)
    {
        ECLIC_ClearPendingIRQ(UART0_IRQn);
        ECLIC_SetPriorityIRQ(UART0_IRQn, 2);
        ECLIC_SetTrigIRQ(UART0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(UART0_IRQn);
    }
    else if (uart_instance->instance == UART1)
    {
        ECLIC_ClearPendingIRQ(UART1_IRQn);
        ECLIC_SetPriorityIRQ(UART1_IRQn, 2);
        ECLIC_SetTrigIRQ(UART1_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(UART1_IRQn);
    }
    UART_RxFIFO_LevelCfg(uart_instance->instance, UART_RX_FIFO_1);
    UART_IT_Cfg(uart_instance->instance, UART_IT_ERBFI, ENABLE);

    if(uart_instance->send_dma.enable)
    {
        uart_instance->data_handle_info.send_dma_finish_handler = send_dma_finish_handler;
        hal_uart_send_dma_init(uart_instance);
    }

    hal_uart_gpio_init(uart_instance);

    uart_instance->enable = ENABLE;

    return 1;
}

int hal_uart_ctl(Hal_Uart_InitTypeDef *uart_instance,int command, ...)
{
    va_list ParamList;
    volatile int value = 0;

    if (uart_instance == NULL)
        return -1;
    va_start(ParamList, command);

    switch(command)
    {
        case HAL_UART_MODE_SWITCH_COMMAND:
        {
            /*the uart receive mode switch*/
            value = va_arg(ParamList, int);
            if(value == HAL_UART_RECEIVE_SYNC)
            {
                uart_instance->sync_async_flag = HAL_UART_RECEIVE_SYNC;
            }
            else if(value == HAL_UART_RECEIVE_ASYNC)
            {
                uart_instance->sync_async_flag = HAL_UART_RECEIVE_ASYNC;
            }

            break;
        }

        default:
            return -10;
    }

    va_end(ParamList);

    return 1;
}

int hal_uart_read(Hal_Uart_InitTypeDef *uart_instance,uint8_t *buffer,uint32_t size,uint32_t *read_size,uint32_t timeout_ms)
{
    uint32_t time_index = 0;
    if(uart_instance == NULL || buffer == NULL)
        return -1;
    if(uart_instance->sync_async_flag == HAL_UART_RECEIVE_ASYNC)
        return -2;
    do
    {
        if(uart_instance->sync_receive_flag == TRUE)
        {
            uart_instance->sync_receive_flag = FALSE;
            (*read_size) += Ring_Cache_Pop(&(uart_instance->cache.ring_buffer),buffer + (*read_size),size);
            if((*read_size) >= size)
                break;
            size -= (*read_size);
        }
        system_delay_ms(1);
        time_index++;
    }while(time_index < timeout_ms);
    if(time_index >= timeout_ms)
        return -3;

    return 1;
}

int hal_uart_write(Hal_Uart_InitTypeDef *uart_instance,uint8_t *buffer,uint32_t size)
{
    uint32_t index = 0,llp_count = 0;
    if(uart_instance == NULL || buffer == NULL)
        return -1;

    if(uart_instance->send_dma.enable == DISABLE)
    {
        do
        {
            if(UART_Flag_GetStatBit(uart_instance->instance,UART_FLAG_TEMT) == SET)
            {
                UART_SendData(uart_instance->instance,buffer[index]);
                index++;
            }
        }while((index < size));
    }
    else
    {
        llp_count = (size / 240) + 1;
        uart_instance->send_dma.llp_cfg = (DMA_LlpTypeDef *)HAL_UART_MALLOC(llp_count * sizeof(DMA_LlpTypeDef));
        if(!uart_instance->send_dma.llp_cfg)
            return -2;

        hal_uart_dma_fifo_init(uart_instance,buffer,size,llp_count);
        DMA_Set_Addr(DMA, uart_instance->send_dma.dma_channel, 0, 0, 0, mmap_to_sys((uint32_t)(uart_instance->send_dma.llp_cfg)));
        DMA_Set_Channel_Enable_Cmd(DMA, uart_instance->send_dma.dma_channel, ENABLE);
        while(!(uart_instance->send_dma.finish_flag));
        uart_instance->send_dma.finish_flag = 0;

        HAL_UART_FREE(uart_instance->send_dma.llp_cfg);
    }

    return 1;
}

int hal_uart_close(struct Hal_Uart_InitTypeDef *uart_instance)
{
    if(uart_instance == NULL)
        return -1;
    if(uart_instance->enable != ENABLE)
        return -2;

    hal_uart_gpio_uninit(uart_instance);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, uart_instance->send_dma.dma_channel,DISABLE);

    uart_instance->data_handle_info.async_receive_handler = NULL;
    timer_uninit(uart_instance);
    UART_IT_Cfg(uart_instance->instance, UART_IT_ERBFI, DISABLE);
    if (uart_instance->instance == UART0)
    {
        ECLIC_ClearPendingIRQ(UART0_IRQn);
        ECLIC_EnableIRQ(UART0_IRQn);
    }
    else if (uart_instance->instance == UART1)
    {
        ECLIC_ClearPendingIRQ(UART1_IRQn);
        ECLIC_DisableIRQ(UART1_IRQn);
    }

    if(uart_instance->instance == UART0)
        RCC_CLK_EN_Ctl(RCC_UART0_CLKEN, DISABLE);
    else if (uart_instance->instance == UART1)
        RCC_CLK_EN_Ctl(RCC_UART1_CLKEN, DISABLE);

    Ring_Cache_Clear(&(uart_instance->cache.ring_buffer));

    uart_instance->enable = DISABLE;

    return 1;
}

static void hal_uart_gpio_init(Hal_Uart_InitTypeDef *uart_instance)
{
    GPIO_InitTypeDef GPIO_Uart1InitStructure;
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN, ENABLE);

    GPIO_Uart1InitStructure.Pin = uart_instance->io.uart_tx | uart_instance->io.uart_rx;
    GPIO_Uart1InitStructure.Alternate = uart_instance->io.uart_tx_af | uart_instance->io.uart_rx_af;
    GPIO_Init(GPIOA, &GPIO_Uart1InitStructure);
}

static void hal_uart_gpio_uninit(Hal_Uart_InitTypeDef *uart_instance)
{
    GPIO_InitTypeDef GPIO_Uart1InitStructure;
    GPIO_DeInit(GPIOA,uart_instance->io.uart_tx | uart_instance->io.uart_rx);
}

static void hal_uart_send_dma_init(Hal_Uart_InitTypeDef *uart_instance)
{
    DMA_InitTypeDef dma_inittypedef;

    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);

    DMA_Clear_All_Interrupt_Cmd(DMA);
    DMA_Set_Enable_Cmd(DMA, DISABLE);
    DMA_Init(DMA, uart_instance->send_dma.dma_channel, &uart_instance->send_dma.config);
    DMA_Set_Enable_Cmd(DMA, ENABLE);

    DMA_Set_Transfer_Interrupt_Cmd(DMA, uart_instance->send_dma.dma_channel, ENABLE);
    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);
}

static void hal_uart_dma_fifo_init(Hal_Uart_InitTypeDef *uart_instance,uint8_t *buffer,uint32_t size,uint32_t llp_count)
{
    volatile uint32_t ctl0_cache = 0,single_size = 0,total_size = 0;

    switch (uart_instance->send_dma.dma_channel) {
        case DMA_CHANNEL0: ctl0_cache = (uint32_t)DMA->CTL0; break;
        case DMA_CHANNEL1: ctl0_cache = (uint32_t)DMA->CTL1; break;
        case DMA_CHANNEL2: ctl0_cache = (uint32_t)DMA->CTL2; break;
        case DMA_CHANNEL3: ctl0_cache = (uint32_t)DMA->CTL3; break;
        case DMA_CHANNEL4: ctl0_cache = (uint32_t)DMA->CTL4; break;
        case DMA_CHANNEL5: ctl0_cache = (uint32_t)DMA->CTL5; break;
        default:break;
    }

    for(int index = 0; index < llp_count; index++)
    {
        if((index + 1) == llp_count)
            uart_instance->send_dma.llp_cfg[index].llp = 0;
        else
            uart_instance->send_dma.llp_cfg[index].llp      = mmap_to_sys((uint32_t)&(uart_instance->send_dma.llp_cfg[index + 1]));
        uart_instance->send_dma.llp_cfg[index].src          = mmap_to_sys((uint32_t)buffer);
        uart_instance->send_dma.llp_cfg[index].dst          = mmap_to_sys((uint32_t)&(uart_instance->instance->DR_DLL));
        single_size =  ((size - total_size) > 240 ) ? 240 : (size - total_size);
        total_size += single_size;
        uart_instance->send_dma.llp_cfg[index].ctl_reg_high = single_size ;
        uart_instance->send_dma.llp_cfg[index].ctl_reg_low  = ctl0_cache;
    }
}

static void async_receive_handler(struct Hal_Uart_InitTypeDef *uart_instance)
{
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
    uint8_t data = 0;

    data = UART_ReceiveData(hal_uart_instance->instance);
    TIMER_Set_Enable_Cmd(hal_uart_instance->timer_instance, DISABLE);
    Ring_Cache_Push(&hal_uart_instance->cache.ring_buffer, data);
    TIMER_Set_Enable_Cmd(hal_uart_instance->timer_instance, ENABLE);
}

static void send_dma_finish_handler(struct Hal_Uart_InitTypeDef *uart_instance)
{
    uart_instance->send_dma.finish_flag = 1;
}

static void uart_timeout_handler(struct Hal_Uart_InitTypeDef *uart_instance)
{
    Hal_Uart_InitTypeDef* hal_uart_instance = hal_uart_instance_get(HAL_UART_INSTANCE0);
    if(hal_uart_instance->sync_async_flag == HAL_UART_RECEIVE_SYNC)
    {
        hal_uart_instance->sync_receive_flag = TRUE;
    }
    else
    {
        if(hal_uart_instance->async_callback)
            hal_uart_instance->async_callback(hal_uart_instance);
    }
}

static void timer_init(struct Hal_Uart_InitTypeDef *uart_instance)
{
    RCC_CLK_EN_Ctl(RCC_TIME_CLKEN, ENABLE);

    uint32_t tick = 0,timeout_ms = 0;
    TIMER_InitTypeDef timer_inittypedef;

    TIMER_Set_Enable_Cmd(uart_instance->timer_instance,DISABLE);
    if(uart_instance->timer_instance == TIMER1)
    {
        ECLIC_ClearPendingIRQ(TIMER1_IRQn);
        ECLIC_SetPriorityIRQ(TIMER1_IRQn, 1);
        ECLIC_SetTrigIRQ(TIMER1_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(TIMER1_IRQn);
        RCC_TIM1_Set_ClkDiv(0xff);
    }
    else if(uart_instance->timer_instance == TIMER2)
    {
        ECLIC_ClearPendingIRQ(TIMER2_IRQn);
        ECLIC_SetPriorityIRQ(TIMER2_IRQn, 1);
        ECLIC_SetTrigIRQ(TIMER2_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(TIMER2_IRQn);
        RCC_TIM2_Set_ClkDiv(0xff);
    }
    else if(uart_instance->timer_instance == TIMER3)
    {
        ECLIC_ClearPendingIRQ(TIMER3_IRQn);
        ECLIC_SetPriorityIRQ(TIMER3_IRQn, 1);
        ECLIC_SetTrigIRQ(TIMER3_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(TIMER3_IRQn);
        RCC_TIM3_Set_ClkDiv(0xff);
    }
    else if(uart_instance->timer_instance == TIMER0)
    {
        ECLIC_ClearPendingIRQ(TIMER0_IRQn);
        ECLIC_SetPriorityIRQ(TIMER0_IRQn, 1);
        ECLIC_SetTrigIRQ(TIMER0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
        ECLIC_EnableIRQ(TIMER0_IRQn);
        RCC_TIM0_Set_ClkDiv(0xff);
    }

    if(uart_instance->initstructure.BaudRate <= 57600)
        timeout_ms = 2;
    else
        timeout_ms = 1;

    timer_inittypedef.mode = TIMER_USER_DEFINED_MODE;
    if(uart_instance->timer_instance == TIMER0)
        tick = TIMER_Transfer_millisecond_to_tick(TIMER0, timeout_ms);
    else if(uart_instance->timer_instance == TIMER1)
        tick = TIMER_Transfer_millisecond_to_tick(TIMER1, timeout_ms);
    else if(uart_instance->timer_instance == TIMER2)
        tick = TIMER_Transfer_millisecond_to_tick(TIMER2, timeout_ms);
    else if(uart_instance->timer_instance == TIMER3)
        tick = TIMER_Transfer_millisecond_to_tick(TIMER3, timeout_ms);
    timer_inittypedef.period = tick;
    TIMER_Init(uart_instance->timer_instance, &timer_inittypedef);
    TIMER_Set_Interrupt_Enable_Cmd(uart_instance->timer_instance, ENABLE);
}

static void timer_uninit(struct Hal_Uart_InitTypeDef *uart_instance)
{
    RCC_CLK_EN_Ctl(RCC_TIME_CLKEN, ENABLE);

    TIMER_Set_Enable_Cmd(uart_instance->timer_instance,DISABLE);
    if(uart_instance->timer_instance == TIMER1)
    {
        ECLIC_ClearPendingIRQ(TIMER1_IRQn);
        ECLIC_DisableIRQ(TIMER1_IRQn);
    }
    else if(uart_instance->timer_instance == TIMER2)
    {
        ECLIC_ClearPendingIRQ(TIMER2_IRQn);
        ECLIC_DisableIRQ(TIMER2_IRQn);
    }
    else if(uart_instance->timer_instance == TIMER3)
    {
        ECLIC_ClearPendingIRQ(TIMER3_IRQn);
        ECLIC_DisableIRQ(TIMER3_IRQn);
    }
    else if(uart_instance->timer_instance == TIMER0)
    {
        ECLIC_ClearPendingIRQ(TIMER0_IRQn);
        ECLIC_DisableIRQ(TIMER0_IRQn);
    }

    TIMER_Set_Interrupt_Enable_Cmd(uart_instance->timer_instance, DISABLE);

    RCC_CLK_EN_Ctl(RCC_TIME_CLKEN, DISABLE);
}
