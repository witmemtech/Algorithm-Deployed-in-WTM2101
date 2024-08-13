#include "main.h"

#ifndef MIN
#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))
#endif
#ifndef MAX
#define MAX(X, Y)  ((X) < (Y) ? (Y) : (X))
#endif

void time_debug(int status, char *str) {
    static uint64_t t0;
    static uint64_t t1;
    if(status == 0) {
       t0 = __get_rv_cycle();
    } else {
        t1 = __get_rv_cycle();
        uint64_t ahbclock = RCC_Get_SYSClk() / (RCC_AHB_Get_ClkDiv() + 1);
        int res = (int)((t1-t0) * 1000 * 1000/ahbclock);
        printf("%2s: %d us\r\n", str, res);
    }
}

void low_power_RSM2(uint32_t sleep_ms){


    PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_ALL, DISABLE);
    PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_KEEP_VDD, ENABLE);
    PMU_Rsm_Mode_Cmd(PMU);

    RCC_CLK_EN_Ctl(RCC_RTC_PCLKEN, ENABLE);
    RTC_Set_Initial_Time_Value(RTC, 0);
    RTC_Set_Compare_Time_Value(RTC, sleep_ms*160);  //PMU_CLK_RTC_SWITCH_10KHZ
    system_delay_us(100);
    __WFI();

    RTC_Set_Compare_Time_Value(RTC, 0);
    RTC_Set_Initial_Time_Value(RTC, 0);
    system_delay_us(100);

    RCC_CLK_EN_Ctl(RCC_RTC_PCLKEN, DISABLE);
}


void system_clock_init_internal_24M(uint8_t mul_ratio)
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
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_NPU_CALIBRATION_PARAMETER;

    /*Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc uses calibration parameters that are saved in the NPU */
    if(mul_ratio==1){
        ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_320KOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    }else{
        ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_PLL | HAL_CLOCK_320KOSC,HAL_CLOCK_PLL,&hal_clock_24mosc_Configuration,mul_ratio,1,1);
    }
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

int audio_init(void)
{
    int ret = 0;

    /*The hal audio instance1*/
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    if(!hal_audio_instance) {
        printf("hal_audio_instance_get err\r\n");
        return -1;
    }

    /*Init hal audio instance1,using the input dmic*/      
    ret = hal_audio_init(hal_audio_instance,HAL_AUDIO_MIC_INPUT_DMIC); 
    if(ret <= 0) {
        printf("hal_audio_init err\r\n");
        return -2;
    }

    /* the frame shift of audio interrupt is 80 words */
    hal_audio_instance->channel.Buffer_Ram_Frame_Move = AUDIO_FRAME_LEN/2;
    /* Each 80 words of data are acquired, then an audio interrupt is triggered */
    hal_audio_instance->channel.Buffer_Ram_Length = AUDIO_FRAME_LEN/2;

    /*Open the audio hardware with the hal audio instance1*/
    ret = hal_audio_open(hal_audio_instance);
    if(ret <= 0) {
        printf("hal_audio_open err:%d\r\n",ret);
        return -3;
    }
    
    return 0;
}

int audio_run(void)
{
    int ret;
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

int i2s_init(void)
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
    ret = hal_i2s_init(hal_i2s_instance,I2S1,HAL_I2S_ONLY_SEND,HAL_I2S_MASTER,HAL_I2S_16BITS_WIDTH_WORD,AUDIO_FRAME_LEN*2);
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

    return 0;
}

void AUDIO_IRQHandler(void)
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

void DEBUG_GPIO_Init(){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_PIN_2;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.Alternate = GPIO_AF2_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_OutputLo(GPIOA, GPIO_PIN_2);
}

void DMA_IRQHandler(void)
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

int16_t buffer_fbank_input[400] = {0};
uint8_t buffer_net_input[NET_INPUT_LEN] = {0};
int8_t net_output[2] = {0};

int select_fbank_input(int16_t *input, uint32_t index) {
    index = index % 5;
    if(index>3) {
        return 0;
    }
    if(index<2){
        for(int i=0;i<AUDIO_FRAME_LEN;i++){
             buffer_fbank_input[index*AUDIO_FRAME_LEN+i] = input[i];
        }
    }else if(index==2){
        for(int i=0;i<(AUDIO_FRAME_LEN/2);i++){
            buffer_fbank_input[index*AUDIO_FRAME_LEN+i] = input[i];
        }
        return 1;
    }
    return 0;
}

float softmax(int8_t *input){
    float e1 = expf((float)input[0]);
    float e2 = expf((float)input[1]);
    float output = e2/(e1+e2);
    return output;
}


#if USE_UART_PROTOCOL
int myUart_init(){
    UART_TypeDef *dst_UART = UART0;
    uart_protocol_init(dst_UART);
    uint8_t is_ok = 0;
    while(1){
        unsigned char value = recv_one_byte(dst_UART);
        switch(value){
          case 0x41:
               printf("im41\r\n");
               break;
          case 0xCC:
               is_ok = 1;
               RCC_CLK_EN_Ctl(RCC_UART0_CLKEN, ENABLE);
               UART_SendData(UART0,0xCD);
               while (UART_Flag_GetStatBit(UART0,UART_FLAG_TEMT) == RESET);
               break;
          default:;
        }
        if(is_ok){break;};
    }
    return 0;
}

int16_t uart_input[160] = {0};
void uart_protocol_process(){
    
    int ret;
    myUart_init();
    uint32_t frame_index = 0;
    while(1){
        ret = uart_receive_data(uart_input, 160, UART_TRANS_TYPE_AUDIO_FROM_HOST);
        if(ret){
            continue;
        }
        ret = select_fbank_input(uart_input, frame_index);
        // fbank
        if(ret){
            memmove(&buffer_net_input[0],&buffer_net_input[40],NET_INPUT_LEN-40);
            get_fbank(buffer_fbank_input,&buffer_net_input[NET_INPUT_LEN-40],NULL);
            npu_infer(buffer_net_input, net_output);
        }else{
            net_output[0] = -128;
            net_output[1] = -128;
        }
        uart_send_data(net_output,2,UART_TRANS_TYPE_NNET_OUT);
        frame_index++;
    }

}
#endif

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGER_NONE);
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));
    int ret;

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();
    
    // the mcu frequency is (PLL_N*24) mHz
    system_clock_init_internal_24M(PLL_N);

    // uart init
    uart_open();
    printf_output_redirect_set(PRINTF_RETARGER_UART0);
    printf("uart init ok\r\n");
    
    // fft init
    fft_init();

    // npu init
    npu_init();

#if USE_UART_PROTOCOL
    uart_protocol_process();
    return;
#endif

    // audio init
    audio_init();

    // i2s init
    i2s_init();
    
    // audio start
    audio_run();

    // tmp for debug
    //DEBUG_GPIO_Init();
 
    Audio_InitTypeDef* hal_audio_instance = hal_audio_instance_get(HAL_AUDIO_INSTANCE1);
    Hal_I2s_InitTypeDef* hal_i2s_instance = hal_i2s_instance_get(HAL_I2S_INSTANCE0);
    uint32_t frame_index = 0;

    while(1){
        if (hal_audio_read(hal_audio_instance,NULL)>0) {
            //GPIO_OutputHi(GPIOA, GPIO_PIN_2);

            ret = select_fbank_input((int16_t*)hal_audio_instance->audio_cache.cache.sram.sram_data, frame_index);
            // fbank
            if(ret){
                memmove(&buffer_net_input[0],&buffer_net_input[40],NET_INPUT_LEN-40);
                //fbank_process(buffer_fbank_input,&buffer_net_input[800]);
                get_fbank(buffer_fbank_input,&buffer_net_input[NET_INPUT_LEN-40],NULL);
                //for(int i=0;i<40;i++){
                //    printf("bi:%d\r\n",(int)buffer_net_input[i+NET_INPUT_LEN-40]);
                //}
                if(frame_index>100){
                    npu_infer(buffer_net_input, net_output);
                    float prob = softmax(net_output);
                    if(prob>0.9){
                        printf("net_output:%f\r\n",prob);
                    }
                }
            }

            /* Write the data  with hal audio instance to i2s with the hal i2s instance */
            hal_i2s_write(hal_i2s_instance,hal_audio_instance->audio_cache.cache.sram.sram_data,NULL,hal_i2s_instance->lr_channel_need_sizes_by_width  /  2);
            frame_index++;
            if(frame_index==2){  
                /* Note,because the i2s data may be discontinuous, the data is cached  once */
                /* Start the i2s with the hal i2s instance */
                hal_i2s_ctl(hal_i2s_instance,HAL_I2S_CHANNEL_ENABLE_COMMAND,ENABLE);
            }
            //GPIO_OutputLo(GPIOA, GPIO_PIN_2);
        }
    }


    return;
}