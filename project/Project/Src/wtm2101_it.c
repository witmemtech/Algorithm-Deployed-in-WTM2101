#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include <wtm2101_config.h>
#include "WTM2101.h"

#include "pmu.h"
#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "main.h"

//
//  Non Vector handle must not have `__INTERRUPT` attribute!!!
//  Vector handle must have `__INTERRUPT`:)
//
//
//  I implement all handle as non-vector here.
//
void SysTick_IRQHandler(void)
{
    
}
#if 0
void AUDIO_IRQHandler(void)
{ 
    extern void audio_ram_vld_callback(void);
    audio_ram_vld_callback();
}
#endif
void core_exception_handler(uint32_t mcause, uint32_t sp)
{
    //uint32_t EXCn = (uint32_t)(mcause & 0X00000fff);
    //uint32_t mmisc_ctl = __RV_CSR_READ(CSR_MMISC_CTL);

    printf("<<<<<< exception >>>>>>\r\n");
    //char core_char[64];
    //sprintf(core_char,"CoreErr:%u,%u",mcause,sp);
    //wtm2101ac_send_info(core_char,strlen(core_char),2);

    //////////////////////////////////////////////////////////////////////////////
    //printf("    mcause = 0x%p (EXCn = %d)\r\n", mcause, EXCn);

    //if (mcause & (1u << 31)) {
    //    printf("    - Interrupt\r\n");
    //} else {
    //    printf("    - NMI\r\n");
    //}

    //if (mcause & (1u << 30)) {
    //    printf("    - Processor reading vector\r\n");
    //}

    //printf("    - MPP = %d\r\n", (mcause >> 28) & 3u);
    //printf("    - MPIE= %d\r\n", (mcause >> 27) & 1u);
    //printf("    - Code= %d\r\n", mcause & 0xFFF);

    //////////////////////////////////////////////////////////////////////////////
    //printf("    mmisc_ctl = 0x%p\r\n", mmisc_ctl);
    //if (mmisc_ctl & (1 << 6)) {
    //    printf("    - misalign access\r\n");
    //}

    ////////////////////////////////////////////////////////////////////////////
    while (1) {
    }
}



