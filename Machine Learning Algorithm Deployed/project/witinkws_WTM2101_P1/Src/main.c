#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

#include <basic_config.h>
#include <wtm2101_config.h>
#include <WTM2101.h>
#include <wtm2101_hal.h>
#include <bb04p1_hal.h>

#include "audio.h"
#include "dma.h"
#include "fbank.h"
#include "gpio.h"
#include "i2c.h"
#include "i2s.h"
#include "npu.h"
#include "pmu.h"
#include "rcc.h"
#include "rtc.h"
#include "uart.h"
#include "gpio.h"
#include "spi.h"

#include "main.h"

#include "wtm2101_mmap.h"
#include "retarget.h"

#include "gpio_config.h"
#include "audio_config.h"
#include "fbank_config.h"
#include "rtc_config.h"
#include "uart_config.h"
#include "uart_tx_dma.h"
#include "uart_rx_dma.h"
#include "spi_config.h"

#include "cnn_framework.h"

#include "riscv_intrinsic.h"
#include "ucontext.h"
#include "ram_ld.h"

#include "crc.h"
#include "datalink.h"
#include "applink_rv32.h"
#include "jtaglink_rv32.h"

#include "rsm_driver.h"
#include "heap.h"
#include "LibNPU.h"
#include "witin_npu_interface.h"
#include "mnist_data.h"


#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y)  ((X) < (Y) ? (Y) : (X))


static void system_clock_init_internal_24M(uint8_t mul_ratio);

void _RSM2_Wait_GPIO() {

    ECLIC_ClearPendingIRQ(GPIO_WAKEUP_IRQn);
    ECLIC_SetPriorityIRQ(GPIO_WAKEUP_IRQn, 1);
    ECLIC_SetTrigIRQ(GPIO_WAKEUP_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(GPIO_WAKEUP_IRQn);

    /* the mask bit is ebabled */
    PMU_Set_Ie_Msk(PMU, PMU_GPIO_IMSK, ENABLE);
    PMU_Set_Ie_Msk(PMU, PMU_GPIO_EMSK, ENABLE);

    PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_ALL,DISABLE);
    PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_KEEP_VDD, ENABLE);

    PMU_Rsm_Mode_Cmd(PMU);
    __WFI();

    PMU_Set_Ie_Msk(PMU, PMU_GPIO_IMSK, DISABLE);
    PMU_Set_Ie_Msk(PMU, PMU_GPIO_EMSK, DISABLE);
}

static void system_clock_init_internal_24M(uint8_t mul_ratio)
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
    if(mul_ratio==1) {
        ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    }else {
        ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC | HAL_CLOCK_PLL,HAL_CLOCK_PLL,&hal_clock_24mosc_Configuration,mul_ratio,1,1);
    }
    if(ret <= 0) {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0) {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

void getMnistInput(const unsigned char *input, unsigned char *output){
    int out_index = 0;
    for(int i=0;i<98;i++){
       unsigned char data = input[i];
       for(int j=0;j<8;j++){
           if((data>>(8-j-1) & 0x01) > 0){
               output[out_index++] = 255;
           }else{
               output[out_index++] = 0;
           }
       }
    }
}

unsigned char input_buffer0[392] = {0};
unsigned char input_buffer1[392] = {0};
signed char net0_out0[384] = {0};
signed char net0_out1[384] = {0};
signed char net1_out[10] = {0};

int vector_mult(signed char *m, signed char *n, int len){
    int _sum = 0;
    for(int i=0;i<len;i++){
        _sum += m[i]*n[i];
    }
    return _sum;
}

void do_softmax(float* input){
    float v1 = expf(input[0]);
    float v2 = expf(input[1]);
    float v3 = expf(input[2]);
    float v4 = expf(input[3]);
    input[0] = v1/(v1+v2);
    input[1] = v2/(v1+v2);
    input[2] = v3/(v3+v4);
    input[3] = v4/(v3+v4);
}

int run_single_img(int img_index){
    
    getMnistInput(&mnist_input[img_index*2+0][0],input_buffer0);
    getMnistInput(&mnist_input[img_index*2+1][0],input_buffer1);
    unsigned char label = mnist_label[img_index];
    
    run_net0(input_buffer0, net0_out0);
    run_net0(input_buffer1, net0_out1);

    signed char* q0 = &net0_out0[0];
    signed char* k0 = &net0_out0[128];
    signed char* v0 = &net0_out0[256];
    signed char* q1 = &net0_out1[0];
    signed char* k1 = &net0_out1[128];
    signed char* v1 = &net0_out1[256];
    
    float softmax[4] = {0};
    softmax[0] = vector_mult(q0, k0, 128)/16256.25;
    softmax[1] = vector_mult(q0, k1, 128)/16256.25;
    softmax[2] = vector_mult(q1, k0, 128)/16256.25;
    softmax[3] = vector_mult(q1, k1, 128)/16256.25;
    do_softmax(softmax);
    for(int i=0;i<128;i++){
        input_buffer0[i] = (unsigned char)(v0[i]*softmax[0] + v1[i]*softmax[1]);
        input_buffer0[i+128] = (unsigned char)(v0[i]*softmax[2] + v1[i]*softmax[1]);
    }
    run_net1(input_buffer0, net1_out);

    int max_idx = -1;
    int max_value = -1000;
    for(int i=0;i<10;i++){
        if(net1_out[i] > max_value){
            max_idx = i;
            max_value = net1_out[i];
        }
    }
    int ret = max_idx==label ? 1 : 0;
    return ret;
}

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGER_NONE);
    
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();
    
    system_clock_init_internal_24M(PLL_N);

    // close first
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,DISABLE);
    RCC_CLK_EN_Ctl(RCC_UART1_CLKEN,DISABLE);

    uart_open();
    printf_output_redirect_set(USE_PRINTF);
    printf("uart ok\r\n");

    int ret = npu_init();
    if(ret){
        printf("npu init error %d",ret);
        return;
    }

    int correct_num=0;
    for(int i=0;i<MNIST_DATA_CNT;i++){
        correct_num += run_single_img(i);
    }
    printf("image num:%d \r\ncorrect ratio:%f\r\n", MNIST_DATA_CNT,correct_num*1.0/MNIST_DATA_CNT);
    
    _RSM2_Wait_GPIO();
    while(1){};
    return;
}
