#include "basic_config.h"
#include "audio_handle.h"
#include "dma.h"
#include "audio.h"

#include "hal_i2s.h"

#include "stdio.h"
#include "config_common.h"

//#ifdef USE_I2S_IN
//extern volatile uint32_t iis0_ram_buffer_write_flag;
//#endif
#ifdef AUDIO_ENABLE

extern volatile uint32_t audio_ram_buffer_write_flag;
extern volatile uint16_t audio_dma_flag;

void audio_ram_vld_callback(void)
{
    if(AUDIO_Get_Ram_Interrupt_Status(AUD,AUDIO_CHANNEL0) & AUDIO_RAM_FRAME_VLD_INTERRUPT)
    {   
		AUD->CLKSWI_CFG = 0x00;
		ECLIC_ClearPendingIRQ(AUDIO_IRQn);
        AUDIO_Clear_Ram_Interrupt(AUD,AUDIO_CHANNEL0,AUDIO_RAM_FRAME_VLD_INTERRUPT);
        ++audio_ram_buffer_write_flag;
    }
    
}

void VAD_IRQHandler(void)
{
  AUDIO_Reset_Vad(AUD);
}
#endif


void audio_ram_vld_callback(void)
{
}


void DMA_IRQHandler(void)
{

    #if USE_DEBUG_PIN
    GPIO_OutputHi(GPIOA, GPIO_PIN_7);
    #endif

    uint16_t block_int_flag = 0;

    /*The hal i2s instance*/
    Hal_I2s_InitTypeDef* hal_i2s_instance= hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    Hal_I2s_InitTypeDef* hal_i2s_instance1= hal_i2s_instance_get(HAL_I2S_INSTANCE1);
    block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
   
    do
    {
        /*The hal i2s instance handle the data*/
        if(block_int_flag & hal_i2s_instance->dma.dma_channel)
        {
            #if USE_DEBUG_PIN
            GPIO_OutputHi(GPIOA, GPIO_PIN_5);
            #endif
            DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance->dma.dma_channel);
            hal_i2s_instance->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance);
            #if USE_DEBUG_PIN
            GPIO_OutputLo(GPIOA, GPIO_PIN_5);
            #endif
        }
        /*The hal i2s instance1 handle the data*/
        if(block_int_flag & hal_i2s_instance1->dma.dma_channel)
        {
            #if USE_DEBUG_PIN
            GPIO_OutputHi(GPIOA, GPIO_PIN_6);
            #endif
            DMA_Clear_Block_Interrupt_Cmd(DMA,hal_i2s_instance1->dma.dma_channel);
            hal_i2s_instance1->Data_handle_info.transfer_and_receive_handler(hal_i2s_instance1);
            #if USE_DEBUG_PIN
            GPIO_OutputLo(GPIOA, GPIO_PIN_6);
            #endif
        }
        /*Get the dma interrupt status*/
        block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);
    }while(block_int_flag);  

    #if USE_DEBUG_PIN
    GPIO_OutputLo(GPIOA, GPIO_PIN_7);
    #endif

}


