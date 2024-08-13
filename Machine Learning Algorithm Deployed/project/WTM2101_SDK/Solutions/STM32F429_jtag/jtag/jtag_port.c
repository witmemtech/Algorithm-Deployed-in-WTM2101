#include "debug_common.h"
#if USE_HARDWARE
#include "stm32f4xx_gpio.h"
#include "jtag_port.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#endif
void Jtag_Io_Config()
{
#if USE_HARDWARE
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
#ifdef CJTAG_MODE
    GPIO_InitStructure.GPIO_Pin = TCK | TMS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, TCK);
    GPIO_ResetBits(GPIOB, TMS);
#else
    GPIO_InitStructure.GPIO_Pin = TCK | TMS | TDI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = TDO;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    GPIO_ResetBits(GPIOB, TCK);
    GPIO_ResetBits(GPIOB, TMS);
    GPIO_ResetBits(GPIOB, TDI);
#endif
#endif
}


