/**
* @file    main.c
* @brief   The Source Codes for the main Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/
#include "main.h"

#define HAL_AUDIO_EXAMPLE 2

static void hal_audio_interrupt_handle_example1(void);
static void hal_audio_with_dma_interrupt_handle_example1(void);
static void hal_audio_interrupt_handle_example2(void);
static void hal_audio_with_dma_interrupt_handle_example2(void);
static void hal_audio_interrupt_handle_example3(void);
static void hal_audio_with_dma_interrupt_handle_example3(void);
static void hal_audio_interrupt_handle_example4(void);
static void hal_audio_with_dma_interrupt_handle_example4(void);

void DMA_IRQHandler(void);
void AUDIO_IRQHandler(void);

static void audio_init(void);
static void audio_start(void);
static void audio_data_handle(void);

static int i2s_init(void);
static void uart_init(void);
static void clock_init(void);

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Reset all peripherals except PMU */
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();
  
    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);
  
    /* Initial clock */
    clock_init();
  
    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);
    audio_init();
    i2s_init();

    /* Show  message */
    printf("BUILD: %s  %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    audio_start();

    while(1)
    {
        audio_data_handle();
    }
}

void DMA_IRQHandler(void)
{
#if (HAL_AUDIO_EXAMPLE == 1)
   hal_audio_with_dma_interrupt_handle_example1();
#elif HAL_AUDIO_EXAMPLE == 2
   hal_audio_with_dma_interrupt_handle_example2();
#elif HAL_AUDIO_EXAMPLE == 3
   hal_audio_with_dma_interrupt_handle_example3();
#elif HAL_AUDIO_EXAMPLE == 4
   hal_audio_with_dma_interrupt_handle_example4();
#endif
}

void AUDIO_IRQHandler(void)
{
#if (HAL_AUDIO_EXAMPLE == 1)
   hal_audio_interrupt_handle_example1();
#elif HAL_AUDIO_EXAMPLE == 2
   hal_audio_interrupt_handle_example2();
#elif HAL_AUDIO_EXAMPLE == 3
   hal_audio_interrupt_handle_example3();
#elif HAL_AUDIO_EXAMPLE == 4
   hal_audio_interrupt_handle_example4();
#endif
}

static void hal_audio_with_dma_interrupt_handle_example1(void)
{
    uint16_t block_int_flag = 0,transfer_int_flag = 0;
    /* The hal audio instance */
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    /* The hal i2s instance */    
    Hal_I2s_InitTypeDef* hal_i2s_instance= hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
    transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);
    
    do
    {
        /* The hal i2s instance handle the data */
        if (block_int_flag & hal_i2s_instance->dma.dma_channel)
        {
            DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance->dma.dma_channel);
            hal_i2s_instance->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance);
        }
        /* The hal audio instance handle the data */
        if (transfer_int_flag & hal_audio_instance->dma_channel)
        {
            DMA_Clear_Transfer_Interrupt_Cmd(DMA,hal_audio_instance->dma_channel);
            hal_audio_instance->Data_handle_info.dma_receive_handler(hal_audio_instance);
        }
        /* Get the dma interrupt status */
        block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
        transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);
    }while(block_int_flag || transfer_int_flag);
}

static void hal_audio_interrupt_handle_example1(void)
{
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    /* if the audio ram buffer is used,as below */
    if (AUDIO_Get_Ram_Interrupt_Status(hal_audio_instance->instance,hal_audio_instance->channel.ChannelNumber) & HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT)
    {
        /* the interrupt is clear */
        AUDIO_Clear_Ram_Interrupt(hal_audio_instance->instance,hal_audio_instance->channel.ChannelNumber,HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT);
        /* data handle */
        hal_audio_instance->Data_handle_info.audio_receive_handler(hal_audio_instance);
    }
}

static void hal_audio_with_dma_interrupt_handle_example2(void)
{
    uint16_t block_int_flag = 0, transfer_int_flag = 0;
    /* The hal audio instance */
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    /* The hal i2s instance */  
    Hal_I2s_InitTypeDef* hal_i2s_instance= hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
    transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);
    
    do
    {
        /* The hal i2s instance handle the data */
        if (block_int_flag & hal_i2s_instance->dma.dma_channel)
        {
            DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance->dma.dma_channel);
            hal_i2s_instance->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance);
        }
        /* The hal audio instance handle the data */
        if (transfer_int_flag & hal_audio_instance->dma_channel)
        {
            DMA_Clear_Transfer_Interrupt_Cmd(DMA,hal_audio_instance->dma_channel);
            hal_audio_instance->Data_handle_info.dma_receive_handler(hal_audio_instance);
        }
        /* Get the dma interrupt  status */
        block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
        transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);
    }while(block_int_flag || transfer_int_flag);
}

static void hal_audio_interrupt_handle_example2(void)
{
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    /* if the audio ram buffer is used,as below */
    if (AUDIO_Get_Ram_Interrupt_Status(hal_audio_instance->instance,hal_audio_instance->channel.ChannelNumber) & HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT)
    {
        /* the interrupt is clear */
        AUDIO_Clear_Ram_Interrupt(hal_audio_instance->instance,hal_audio_instance->channel.ChannelNumber,HAL_AUDIO_BUFFER_RAM_VLD_INTERRUPT);
        /* data handle */
        hal_audio_instance->Data_handle_info.audio_receive_handler(hal_audio_instance);
    }
}

static void hal_audio_with_dma_interrupt_handle_example3(void)
{
    uint16_t block_int_flag = 0;
    /* The hal i2s instance */  
    Hal_I2s_InitTypeDef* hal_i2s_instance= hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
    
    do
    {
        /* The hal i2s instance handle the data */
        if (block_int_flag & hal_i2s_instance->dma.dma_channel)
        {
            DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance->dma.dma_channel);
            hal_i2s_instance->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance);
        }
        /* Get the dma interrupt status */
        block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
    }while(block_int_flag);
}

static void hal_audio_interrupt_handle_example3(void)
{
    /* The hal audio instance */
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    if (AUDIO_Get_FIFO_Interrupt_Status(hal_audio_instance->instance, hal_audio_instance->channel.ChannelNumber)  & HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT)  
    {
        /* the data is push to ring buffer with hal audio instance */
        hal_audio_instance->Data_handle_info.audio_receive_handler(hal_audio_instance);
    }
}

static void hal_audio_with_dma_interrupt_handle_example4(void)
{
    uint16_t block_int_flag = 0;
    /* The hal i2s instance */  
    Hal_I2s_InitTypeDef* hal_i2s_instance= hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
    
    do
    {
        /* The hal i2s instance handle the data */
        if (block_int_flag  & hal_i2s_instance->dma.dma_channel)
        {
            DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance->dma.dma_channel);
           hal_i2s_instance->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance);
        }
        /* Get the dma interrupt status */
        block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
    }while(block_int_flag);
}

static void hal_audio_interrupt_handle_example4(void)
{
    /* The hal audio instance1 */
    Audio_InitTypeDef* hal_audio_instance1 = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    /* The hal audio instance2 */
    Audio_InitTypeDef* hal_audio_instance2 = hal_audio_instance_get(HAL_AUDIO_INSTANCE2);

    if (AUDIO_Get_FIFO_Interrupt_Status(hal_audio_instance1->instance, hal_audio_instance1->channel.ChannelNumber)  & HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT)  
    {
        /* the data is push to ring buffer with hal audio instance1 */
        hal_audio_instance1->Data_handle_info.audio_receive_handler(hal_audio_instance1);
    }

    if (AUDIO_Get_FIFO_Interrupt_Status(hal_audio_instance2->instance, hal_audio_instance2->channel.ChannelNumber)  & HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT)  
    {
        /* the data is push to ring buffer with hal audio instance2 */
        hal_audio_instance2->Data_handle_info.audio_receive_handler(hal_audio_instance2);
    }
}

static int hal_audio_init_example1(void)
{
    int ret = 0;
    /* The hal audio instance */
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    if (!hal_audio_instance)
    {
        printf("hal_audio_instance is null,this is a  error\r\n");
        return -1;
    }

    /* Init hal audio instance,using the input  dmic */        
    ret = hal_audio_init(hal_audio_instance,HAL_AUDIO_MIC_INPUT_DMIC);  
    if (ret <= 0)
    {
        printf("hal_audio_init is error:%d\r\n",ret);
        return -2;
    }
    /* the frame shift of audio interrupt is 80 words */
    hal_audio_instance->channel.Buffer_Ram_Frame_Move = 80;
    /*Each 80 words of data are acquired, then an audio interrupt is triggered */
    hal_audio_instance->channel.Buffer_Ram_Length = 80;

    /* Open the audio hardware with the hal audio instance */    
    ret = hal_audio_open(hal_audio_instance);
    if (ret <= 0)
    {
        printf("hal_audio_open is error:%d\r\n",ret);
        return -3;
    }

    return 1;
}

static int hal_audio_init_example2(void)
{
    int ret = 0;
    /* The hal audio instance */
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    if (!hal_audio_instance)
    {
        printf("hal_audio_instance is null,this is a error\r\n");
        return -1;
    }

    /* Init hal audio instance,using the input amic */  
    ret = hal_audio_init(hal_audio_instance,HAL_AUDIO_MIC_INPUT_AMIC);  
    if (ret <= 0)
    {
        printf("hal_audio_init is error:%d\r\n",ret);
        return -2;
    }
    /* the frame shift of audio interrupt is 80 words */
    hal_audio_instance->channel.Buffer_Ram_Frame_Move = 80;
    /* Each 80 words of data are acquired, then an audio interrupt is triggered */
    hal_audio_instance->channel.Buffer_Ram_Length = 80;

    /* Open the audio hardware with the hal audio instance */  
    ret = hal_audio_open(hal_audio_instance);
    if (ret <= 0)
    {
        printf("hal_audio_open is error:%d\r\n",ret);
        return -3;
    }

    return 1;
}

static int hal_audio_init_example3(void)
{
    int ret = 0;
    /* The hal audio instance */
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    if (!hal_audio_instance)
    {
        printf("hal_audio_instance is null,this is a  error\r\n");
        return -1;
    }

    /* Init hal audio instance,using the input linein */          
    ret = hal_audio_init(hal_audio_instance,HAL_AUDIO_MIC_INPUT_LINEIN);  
    if (ret <= 0)
    {
        printf("hal_audio_init is error:%d\r\n",ret);
        return -2;
    }
    /* Each 80 words of data are acquired, then the buffer is handled by hal audio instance */
    hal_audio_instance->channel.Buffer_Ram_Length = 80;

    /* Open the audio hardware with the hal audio instance */
    ret = hal_audio_open(hal_audio_instance);
    if (ret <= 0)
    {
        printf("hal_audio_open is error:%d\r\n",ret);
        return -3;
    }

    return 1;
}

static int hal_audio_init_example4(void)
{
    int ret = 0;
    /* The hal audio instance1 */
    Audio_InitTypeDef* hal_audio_instance1 = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    /* The hal audio instance2 */
    Audio_InitTypeDef* hal_audio_instance2 = hal_audio_instance_get(HAL_AUDIO_INSTANCE2);
    if ((!hal_audio_instance1)  ||  (!hal_audio_instance2))
    {
        printf("hal_audio_instance is null,this is a  error\r\n");
        return -1;
    }

    /* Init hal audio instance1,using the input  dmic */            
    ret = hal_audio_init(hal_audio_instance1,HAL_AUDIO_MIC_INPUT_DMIC);  
    if (ret <= 0)
    {
        printf("hal_audio_init hal_audio_instance1 is error:%d\r\n",ret);
        return -2;
    }
    /* Using the fifo buffer replace ram buffer with the hal audio instance1 */
    hal_audio_instance1->channel.BufferMode = HAL_AUDIO_BUFFER_FIFO_MODE;
    /* Using the fifo half  full interrupt  replace  ram  buffer  interrupt with the hal audio instance1 */
    hal_audio_instance1->interrupt.type = HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT;
    /* Disable the dma with the hal audio instance1 */

    hal_audio_instance1->dma_enable = DISABLE;
    /* Each 80 words of data are acquired, then the buffer is handled by hal audio instance1 */
    hal_audio_instance1->channel.Buffer_Ram_Length = 80;

    /* Init hal audio instance2,using the input  dmic */    
    ret = hal_audio_init(hal_audio_instance2,HAL_AUDIO_MIC_INPUT_DMIC);  
    if (ret <= 0)
    {
        printf("hal_audio_init hal_audio_instance2 is error:%d\r\n",ret);
        return -3;
    }
    /* Because the hal_audio_instance1 have reset the audio hardware,so the hal_audio_instance2 must no  reset the audio hardware again */
    hal_audio_instance2->audio_rst = DISABLE;
    /* Because the hal_audio_instance1 have inited pdm0,so the hal_audio_instance2 must not init pdm0 */
    hal_audio_instance2->Pdm.enable = DISABLE;

    /* Using the audio channel2 with the hal audio instance2 */
    hal_audio_instance2->channel.ChannelNumber = HAL_AUDIO_CHANNEL1_NUMBER;
    /* Using the fifo buffer replace ram buffer with the hal audio instance2 */
    hal_audio_instance2->channel.BufferMode = HAL_AUDIO_BUFFER_FIFO_MODE;
    /* Using the fifo half full interrupt replace ram buffer interrupt with the hal audio instance2 */    
    hal_audio_instance2->interrupt.type = HAL_AUDIO_BUFFER_FIFO_HALF_FULL_INTERRUPT;
    /* Using the fail clock edge capture data with the hal audio instance2 */    
    hal_audio_instance2->channel.Clk_Edge = HAL_AUDIO_CLK_EDGE_CAPTURE_FAIL;

    /* Disable the dma with the hal audio instance2 */
    hal_audio_instance2->dma_enable = DISABLE;
    /*Each 80 words of data are acquired, then the buffer is handled by hal audio instance2 */
    hal_audio_instance2->channel.Buffer_Ram_Length = 80;

    /* Open the audio hardware with the hal audio instance1 */
    ret = hal_audio_open(hal_audio_instance1);
    if (ret <= 0)
    {
        printf("hal_audio_open hal_audio_instance1 is error:%d\r\n",ret);
        return -4;
    }
    /* Open the audio hardware with the hal audio instance2 */
    ret = hal_audio_open(hal_audio_instance2);
    if (ret <= 0)
    {
        printf("hal_audio_open hal_audio_instance2 is error:%d\r\n",ret);
        return -5;
    }
      
    return 1;
}

static int hal_audio_start_example1(void)
{
    int ret = 0;
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    /* Enable the audio interrupt with the hal audio instance */
    ret = hal_audio_ctl(hal_audio_instance,HAL_AUDIO_INTERRUPT_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -1;
    }

    /* Start the audio with the hal audio instance */
    ret = hal_audio_ctl(hal_audio_instance,HAL_AUDIO_CHANNEL_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -2;
    }

    return 1;
}

static int hal_audio_start_example2(void)
{
    int ret = 0;
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    /* Enable the audio interrupt with the hal audio instance */
    ret = hal_audio_ctl(hal_audio_instance,HAL_AUDIO_INTERRUPT_ENABLE_COMMAND,ENABLE);
    if (ret <= 0) {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -1;
    }

    /* Start the audio with the hal audio instance */
    ret = hal_audio_ctl(hal_audio_instance,HAL_AUDIO_CHANNEL_ENABLE_COMMAND,ENABLE);
    if (ret <= 0) {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -2;
    }

    return 0;
}

static int hal_audio_start_example3(void)
{
    int ret = 0;
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);

    /* Enable the audio interrupt with the hal audio instance */    
    ret = hal_audio_ctl(hal_audio_instance,HAL_AUDIO_INTERRUPT_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -1;
    }

    /* Start the audio with the hal audio instance */
    ret = hal_audio_ctl(hal_audio_instance,HAL_AUDIO_CHANNEL_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -2;
    }

    return 1;
}

static int hal_audio_start_example4(void)
{
    int ret = 0;
    Audio_InitTypeDef* hal_audio_instance1 = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    Audio_InitTypeDef* hal_audio_instance2 = hal_audio_instance_get(HAL_AUDIO_INSTANCE2);

    /* Enable the audio interrupt with the hal audio instance1 */    
    ret = hal_audio_ctl(hal_audio_instance1,HAL_AUDIO_INTERRUPT_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -1;
    }
    /* Enable the audio interrupt with the hal audio instance2 */    
    ret = hal_audio_ctl(hal_audio_instance2,HAL_AUDIO_INTERRUPT_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -2;
    }

    /* Start the audio with the hal audio instance1 */
    ret = hal_audio_ctl(hal_audio_instance1,HAL_AUDIO_CHANNEL_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -3;
    }
    /* Start the audio with the hal audio instance2 */
    ret = hal_audio_ctl(hal_audio_instance2,HAL_AUDIO_CHANNEL_ENABLE_COMMAND,ENABLE);
    if (ret <= 0)
    {
        printf("hal_audio_ctl is error:%d\r\n",ret);
        return -4;
    }

    return 1;
}
    
static int hal_audio_data_handle_example1(void)
{
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    static  long  i2s_running = 0;

    /* Wait the audio interrupt */
    if (hal_audio_read(hal_audio_instance,NULL)  >  0)
    {
        /* then you can handle the data as below in sram buffer */

        /* Write the data with hal audio instance to i2s with the hal i2s instance */
        hal_i2s_write(hal_i2s_instance,hal_audio_instance->audio_cache.cache.sram.sram_data,NULL,hal_i2s_instance->lr_channel_need_sizes_by_width  /  2);
        i2s_running++;
        if (i2s_running == 2)  
        {
            /* Note,because the i2s data may be discontinuous, the data is cached once */
            /* Start the i2s with the hal i2s instance */
            hal_i2s_ctl(hal_i2s_instance,HAL_I2S_CHANNEL_ENABLE_COMMAND,ENABLE);
        }
    }
}

static int hal_audio_data_handle_example2(void)
{
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    static long i2s_running = 0;

    /* Wait the audio interrupt */
    if (hal_audio_read(hal_audio_instance,NULL)  >  0)
    {
        /* then you can handle the data as below in sram buffer */
        /* . */
        /* . */
        /* . */
      
        /* Write the data  with hal audio instance to i2s with the hal i2s instance */
        hal_i2s_write(hal_i2s_instance,hal_audio_instance->audio_cache.cache.sram.sram_data,NULL,hal_i2s_instance->lr_channel_need_sizes_by_width  /  2);
        i2s_running++;
        if (i2s_running == 2)  
        {
            /* Note,because the i2s data may be discontinuous, the data is cached  once */
            /* Start the i2s with the hal i2s instance */
            hal_i2s_ctl(hal_i2s_instance,HAL_I2S_CHANNEL_ENABLE_COMMAND,ENABLE);
        }
    }
}

static int hal_audio_data_handle_example3(void)
{
    static uint8_t temp[80 * 4] = {0};

    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    static long i2s_running = 0;

    /* Wait  for  enough  data with the hal audio instance */
    if (hal_audio_read(hal_audio_instance,temp)  >  0)
    {
        /* then you  can  handle the data  as  below */
        /* . */
        /* . */
        /* . */

        /* Write the data  to  i2s with the hal  i2s  instance */        
        hal_i2s_write(hal_i2s_instance,temp,NULL,hal_i2s_instance->lr_channel_need_sizes_by_width / 2);
        i2s_running++;
        if (i2s_running == 2)
        {
            /* Note,because the i2s data may be discontinuous, the data is cached once */
            /* Start the i2s with the hal i2s instance */
            hal_i2s_ctl(hal_i2s_instance,HAL_I2S_CHANNEL_ENABLE_COMMAND,ENABLE);
        }
    }
}

static int hal_audio_data_handle_example4(void)
{
    static  int data_flag1 = 0,data_flag2 = 0;
    static  uint8_t  temp1[80 * 4] = {0},temp2[80 * 4] = {0};

    Audio_InitTypeDef* hal_audio_instance1 = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    Audio_InitTypeDef* hal_audio_instance2 = hal_audio_instance_get(HAL_AUDIO_INSTANCE2);
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    static  long  i2s_running = 0;

    /* Wait for enough data with the hal audio instance */
    if (hal_audio_read(hal_audio_instance1,temp1) > 0)
    {
          data_flag1 = 1;
    }
    /* Wait for enough  data with the hal audio instance */
    if (hal_audio_read(hal_audio_instance2,temp2) > 0)
    {
          data_flag2 = 1;
    }

    if (data_flag1 && data_flag2)
    {
        data_flag1 = 0;
        data_flag2 = 0;
        /* then you can handle the data  as below */
        /* . */
        /* . */
        /* . */

        /* Write the data  to  i2s  left  and  right  channel with the hal  i2s  instance */    
        hal_i2s_write(hal_i2s_instance,temp1,temp2,hal_i2s_instance->lr_channel_need_sizes_by_width / 2);
        i2s_running++;
        if (i2s_running == 2)  
        {
            /* Note,because the i2s data may be discontinuous, the data is cached  once */
            /* Start the i2s with the hal  i2s  instance */
            hal_i2s_ctl(hal_i2s_instance,HAL_I2S_CHANNEL_ENABLE_COMMAND,ENABLE);
        }
    }
}

static void audio_init(void)
{
#if (HAL_AUDIO_EXAMPLE == 1)
    hal_audio_init_example1();
#elif HAL_AUDIO_EXAMPLE == 2
    hal_audio_init_example2();
#elif HAL_AUDIO_EXAMPLE == 3
    hal_audio_init_example3();
#elif HAL_AUDIO_EXAMPLE == 4
    hal_audio_init_example4();
#endif
}

static void audio_start(void)
{
#if (HAL_AUDIO_EXAMPLE == 1)
    hal_audio_start_example1();
#elif HAL_AUDIO_EXAMPLE == 2
    hal_audio_start_example2();
#elif HAL_AUDIO_EXAMPLE == 3
    hal_audio_start_example3();
#elif HAL_AUDIO_EXAMPLE == 4
    hal_audio_start_example4();
#endif
}

static void audio_data_handle(void)
{
#if (HAL_AUDIO_EXAMPLE == 1)
    hal_audio_data_handle_example1();
#elif HAL_AUDIO_EXAMPLE == 2
    hal_audio_data_handle_example2();
#elif HAL_AUDIO_EXAMPLE == 3
    hal_audio_data_handle_example3();
#elif HAL_AUDIO_EXAMPLE == 4
    hal_audio_data_handle_example4();
#endif
}

static int i2s_init(void)
{
    int ret = 0;
    /* The hal i2s instance */
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    if (!hal_i2s_instance)
    {
        printf("hal_i2s_instance is null,this is a error\r\n");
        return -1;
    }

    /* Init hal i2s instance,using I2S1,only sending,master,16bits width word,320 half words data of left and right channel is handled application */
    ret = hal_i2s_init(hal_i2s_instance,I2S1,HAL_I2S_ONLY_SEND,HAL_I2S_MASTER,HAL_I2S_16BITS_WIDTH_WORD,320);
    if (ret <= 0)
    {
        printf("hal_i2s_init is error:%d\r\n",ret);
        return -2;
    }

    /* Open the hal i2s  hardware with the hal i2s instance */
    ret = hal_i2s_open(hal_i2s_instance);
    if (ret <= 0)
    {
        printf("hal_i2s_open is error:%d\r\n",ret);
        return -3;
    }

    return 1;
}

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);
    
    /*the gpio4,gpio5*/
    GPIO_InitStructure.Pin = GPIO_PIN_16 | GPIO_PIN_17;
    GPIO_InitStructure.Alternate = GPIO_AF16_UART0 | GPIO_AF17_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);
}

static void clock_init(void)
{
    int ret = 0; 
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_INTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = ENABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /* Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc is calibrated by the xtal 32k */
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if (ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if (ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

