/**
* @file    wtm2101_system.c
* @brief   The Source Codes for the wtm2101_system Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/
#include "wtm2101_system.h"
#include <stdio.h>

uint32_t __WTM2101_RevID = 0;

void core_exception_dump(unsigned long mcause)
{
    printf("MCAUSE 0x%x\r\n", mcause);
    unsigned char exception_code  = mcause & 0x1F;
    switch (exception_code)
    {
        case 0x0:
            printf("Instruction address misaligned\r\n");
            break;
        case 0x1:
            printf("Instruction access fault\r\n");
            break;
        case 0x2:
            printf("Illegal instruction\r\n");
            break;
        case 0x3:
            printf("break point\r\n");
            break;
        case 0x4:
            printf("Load address misaligned\r\n");
            break;
        case 0x5:
            printf("Load address fault\r\n");
            break;
        case 0x6:
            printf("store/AMO address misaligned\r\n");
            break;
        case 0x7:
            printf("store/AMO access fault\r\n");
            break;
        case 0x8:
            printf("Environment call from U-mode\r\n");
            break;
        case 0xB:
            printf("Environment call from M-mode\r\n");
            break;
        default:
            break;
    }
}
/**
 * \brief      Common NMI and Exception handler entry
 * \details
 * This function provided a command entry for NMI and exception. Silicon Vendor could modify
 * this template implementation according to requirement.
 * \remarks
 * - RISCV provided common entry for all types of exception. This is proposed code template
 *   for exception entry function, Silicon Vendor could modify the implementation.
 * - For the core_exception_handler template, we provided exception register function \ref Exception_Register_EXCn
 *   which can help developer to register your exception handler for specific exception number.
 */
__WEAK uint32_t core_exception_handler(unsigned long mcause, unsigned long sp)
{
    printf("core exception excution\r\n");
    printf("SP 0x%x\r\n", sp);
    core_exception_dump(mcause);
    while (1) {
    }
}

void heap_init(void) 
{
    extern uint32_t(__heap_start__);
    extern uint32_t(__HEAPSIZE__);
    uint32_t *heap_start = NULL;
    heap_start = &__heap_start__;
    *heap_start = 0;
    *(heap_start+1) = (uint32_t)&__HEAPSIZE__;
}

void SystemInit (void)
{
    /*Make sure minimal clocks enabled*/
    RCC_CLK_EN_Ctl(RCC_PMU_PCLKEN | RCC_AHB1_CLKEN | RCC_AHB2_CLKEN | RCC_APB0_CLKEN | RCC_GPIO_HCLKEN | RCC_DB_CLKEN, ENABLE);
  
    /*Close the other clocks,except the gpio clock,bus clocks,pmu clock*/
    RCC_CLK_EN_Ctl( RCC_FLASH_CLKEN | RCC_FLASH_REG_CLKEN | RCC_DMA_CLKEN |
                    RCC_WDT_PCLKEN | RCC_RTC_PCLKEN |
                    RCC_UART0_CLKEN | RCC_UART1_CLKEN | RCC_I2C_PCLKEN | RCC_TIME_CLKEN |
                    RCC_I2S1_CLKEN | RCC_SPIM_PCLKEN | RCC_QSPI_PCLKEN | 
                    RCC_PWM0_CLKEN | RCC_PWM1_CLKEN | RCC_FFT_CLKEN | 
                    RCC_AUD_CLKEN | RCC_I2S_MCLKEN | RCC_TRIM_CLKEN | RCC_AUD_PCLKEN |
                    RCC_SPIS_PCLKEN | RCC_I2S0_CLKEN | RCC_DAC_CLKEN | RCC_EXTFLASH_CLKEN,
                    DISABLE);

    /*Get the chip id*/
    __WTM2101_RevID = PMU->REVID; 

    /*Pull up gpio*/
    PMU->RTN_0 = (uint8_t)0xff;
    PMU->RTN_1 = (uint8_t)0xff;
    PMU->RTN_2 = (uint8_t)0x0f;
}

void ECLIC_Init(void)
{
    /* Global Configuration about MTH and NLBits.
     * TODO: Please adapt it according to your system requirement.
     * This function is called in _init function */
    /* Set CSR MTH to zero */
    ECLIC_SetMth(0);
    /* Set Nlbits to the CLICINTCTLBITS, all the bits are level bits */
    ECLIC_SetCfgNlbits(__ECLIC_INTCTLBITS);
}

void _premain_init(void)
{
    /* TODO: Add your own initialization code here, called before main  */
    /* __ICACHE_PRESENT and __DCACHE_PRESENT are defined in WTM2101.h */
  #if defined(__ICACHE_PRESENT) && __ICACHE_PRESENT == 1
      EnableICache();
  #endif
  #if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT == 1
      EnableDCache();
  #endif

    /* ECLIC initilization, mainly MTH and NLBIT settings */
    ECLIC_Init();
}


void _postmain_fini(int status)
{
    /* TODO: Add your own finishing code here, called after main */
}

