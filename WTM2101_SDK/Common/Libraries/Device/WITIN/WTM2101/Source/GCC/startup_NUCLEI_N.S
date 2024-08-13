#include "riscv_encoding.h"

.macro DECLARE_INT_HANDLER  INT_HDL_NAME
#if defined(__riscv_xlen) && (__riscv_xlen == 32)
    .word \INT_HDL_NAME
#else
    .dword \INT_HDL_NAME
#endif
.endm

/*
 * === Different Download and Running Mode ===
 * flashxip: Program will to be download into flash and run directly in Flash
 * flash: Program will be download into flash, when running, program will be copied to ilm/ram and run in ilm/ram
 * ilm: Program will be download into ilm/ram and run directly in ilm/ram, program lost when poweroff
 * ddr: Program will be download into ddr and run directly in ddr, program lost when poweroff
 */

/*** Vector Table Code Section ***/
    /*
     * Put the interrupt vectors in this section according to the run mode:
     * This startup code and link script file are configured for FlashXIP mode:
     * FlashXIP: .vtable
     * ILM: .vtable
     * DDR: .vtable
     * Flash: .vtable_ilm
     */
    .section .vtable

    .weak   SVC_IRQHandler 
    .weak   SysTick_IRQHandler
    .weak   GPIO_WAKEUP_IRQHandler
    .weak   WDG_IRQHandler
    .weak   RTC_IRQHandler
    .weak   FLASH_IRQHandler
    .weak   UART0_IRQHandler
    .weak   UART1_IRQHandler
    .weak   TIMER0_IRQHandler
    .weak   TIMER1_IRQHandler
    .weak   TIMER2_IRQHandler
    .weak   TIMER3_IRQHandler
    .weak   I2C_IRQHandler
    .weak   I2S0_IRQHandler
    .weak   SPIM_IRQHandler
    .weak   QSPI_IRQHandler
    .weak   PWM0_IRQHandler
    .weak   PWM1_IRQHandler
    .weak   DMA_IRQHandler
    .weak   NPU_IRQHandler
    .weak   AUDIO_IRQHandler
    .weak   VAD_IRQHandler
    .weak   FFT_IRQHandler
    .weak   AFC320K_IRQHandler
    .weak   GPIO_IRQHandler
    .weak   I2S1_IRQHandler
    .weak   SPIS_IRQHandler
    .weak   AFC24M_IRQHandler
    .weak   RESERVED1_IRQHandler
    .weak   RESERVED2_IRQHandler
    .weak   RESERVED3_IRQHandler
    .weak   TE_IRQHandler
    .weak   TE_CRIT_IRQHandler
    .weak   IDLE_IRQHandler

    /* ---------------------------------------------------------------------- */
    /* reset handler                                                          */
    /* ---------------------------------------------------------------------- */
    .section .vectors, "ax"
    .globl vector_base
vector_base:
    j _start                                                /* 0: Reserved, Jump to _start when reset for ILM/FlashXIP mode.*/

    .align LOG_REGBYTES                                     /*    Need to align 4 byte for RV32, 8 Byte for RV64 */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 1: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 2: Reserved */
    DECLARE_INT_HANDLER     SVC_IRQHandler                  /* 3: Machine software interrupt */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 4: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 5: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 6: Reserved */
    DECLARE_INT_HANDLER     SysTick_IRQHandler              /* 7: Machine timer interrupt */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 8: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 9: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 10: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 11: Reserved */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 12: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 13: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 14: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 15: Reserved */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 16: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 17: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 18: Reserved */

    DECLARE_INT_HANDLER     GPIO_WAKEUP_IRQHandler          /* 19: Peripheral Interrupt */
    DECLARE_INT_HANDLER     WDG_IRQHandler                  /* 20: Peripheral Interrupt */
    DECLARE_INT_HANDLER     RTC_IRQHandler                  /* 21: Peripheral Interrupt */
    DECLARE_INT_HANDLER     FLASH_IRQHandler                /* 22: Peripheral Interrupt */
    DECLARE_INT_HANDLER     UART0_IRQHandler                /* 23: Peripheral Interrupt */
    DECLARE_INT_HANDLER     UART1_IRQHandler                /* 24: Peripheral Interrupt */
    DECLARE_INT_HANDLER     TIMER0_IRQHandler               /* 25: Peripheral Interrupt */
    DECLARE_INT_HANDLER     TIMER1_IRQHandler               /* 26: Peripheral Interrupt */
    DECLARE_INT_HANDLER     TIMER2_IRQHandler               /* 27: Peripheral Interrupt */
    DECLARE_INT_HANDLER     TIMER3_IRQHandler               /* 28: Peripheral Interrupt */
    DECLARE_INT_HANDLER     I2C_IRQHandler                  /* 29: Peripheral Interrupt */
    DECLARE_INT_HANDLER     I2S0_IRQHandler                 /* 30: Peripheral Interrupt */
    DECLARE_INT_HANDLER     SPIM_IRQHandler                 /* 31: Peripheral Interrupt */
    DECLARE_INT_HANDLER     QSPI_IRQHandler                 /* 32: Peripheral Interrupt */
    DECLARE_INT_HANDLER     PWM0_IRQHandler                 /* 33: Peripheral Interrupt */
    DECLARE_INT_HANDLER     PWM1_IRQHandler                 /* 34: Peripheral Interrupt */
    DECLARE_INT_HANDLER     DMA_IRQHandler                  /* 35: Peripheral Interrupt */
    DECLARE_INT_HANDLER     NPU_IRQHandler                  /* 36: Peripheral Interrupt */
    DECLARE_INT_HANDLER     AUDIO_IRQHandler                /* 37: Peripheral Interrupt */
    DECLARE_INT_HANDLER     VAD_IRQHandler                  /* 38: Peripheral Interrupt */
    DECLARE_INT_HANDLER     FFT_IRQHandler                  /* 39: Peripheral Interrupt */
    DECLARE_INT_HANDLER     AFC320K_IRQHandler              /* 40: Peripheral Interrupt */
    DECLARE_INT_HANDLER     GPIO_IRQHandler                 /* 41: Peripheral Interrupt */
    DECLARE_INT_HANDLER     I2S1_IRQHandler                 /* 42: Peripheral Interrupt */
    DECLARE_INT_HANDLER     SPIS_IRQHandler                 /* 43: Peripheral Interrupt */
    DECLARE_INT_HANDLER     AFC24M_IRQHandler               /* 44: Peripheral Interrupt */
    DECLARE_INT_HANDLER     RESERVED1_IRQHandler            /* 45: Peripheral Interrupt */
    DECLARE_INT_HANDLER     RESERVED2_IRQHandler            /* 46: Peripheral Interrupt */
    DECLARE_INT_HANDLER     RESERVED3_IRQHandler            /* 47: Peripheral Interrupt */
    DECLARE_INT_HANDLER     TE_IRQHandler                   /* 48: Peripheral Interrupt */
    DECLARE_INT_HANDLER     TE_CRIT_IRQHandler              /* 49: Peripheral Interrupt */
    DECLARE_INT_HANDLER     IDLE_IRQHandler                 /* 50: Peripheral Interrupt */

/*** Startup Code Section ***/
    .section .init

    .globl _start
    .globl _real_start
    .type _start,@function

/**
 * Reset Handler called on controller reset
 */

_start:
    /* ---------------------------------------------------------------------- */
    /* Startup Stage 1                                                        */
    /* ---------------------------------------------------------------------- */
    /* Disable Global Interrupt */
    csrc CSR_MSTATUS, MSTATUS_MIE

    ///* obtain label `_start` runtime address from current PC */
    //auipc   a0, 0x00000 /* a0 := PC + 0x00000*/
    //addi    a0, a0, -4  /* a0 := a0 - 4 */


    ///* if boot from SRAM, just run it*/
    //li      a1, 1
    //slli    a1, a1, 29
    ///* if (_start >= 0x2000_0000) goto _real_start */
    //bleu    a1, a0, _real_start 


    ///* if boot from FLASH, just run it*/
    //li      a1, 1
    //slli    a1, a1, 27
    ///* if (_start >= 0x0800_0000) goto _real_start */
    //bleu    a1, a0, _real_start 


    ///* if boot from 0x00000000, we need to change real start entry */
    ///* convert _real_start address to FLASH section, then jump */
    //la      a0, _real_start
    //add     a0, a0, a1
    //jr      a0


_real_start:
    /*
     * Set the the NMI base mnvec to share
     * with mtvec by setting CSR_MMISC_CTL
     * bit 9 NMI_CAUSE_FFF to 1
     */
    li t0, MMISC_CTL_NMI_CAUSE_FFF
    csrs CSR_MMISC_CTL, t0


    /*
     * Intialize ECLIC vector interrupt
     * base address mtvt to vector_base
     */
    la t0, vector_base
    csrw CSR_MTVT, t0


    /*
     * Set ECLIC non-vector entry to be controlled
     * by mtvt2 CSR register.
     * Intialize ECLIC non-vector interrupt
     * base address mtvt2 to irq_entry.
     *
     *  https://www.rvmcu.com/site/nuclei_n_isa/
     *  7.5.14
     *
     *  bit31:2     COMMON-CODE-ENTRY
     *  bit1        RESERVED
     *  bit0        MTVT2EN
     *              - 0: ECLIC Non-vector common entry load from mtvec register (POR default)
     *              - 1: ECLIC Non-vector common entry load from COMMON-CODE-ENTRY
     */
    la      t0, irq_entry
    csrw    CSR_MTVT2, t0
    csrs    CSR_MTVT2, 0x1


    /*
     * Set Exception Entry MTVEC to exc_entry
     * Due to settings above, Exception and NMI
     * will share common entry.
     *
     *  https://www.rvmcu.com/site/nuclei_n_isa/
     *  7.4.17
     *
     *  bit31:6     Entry
     *  bit5:0      Mode
     *              - 6'b11: ECLIC mode
     *              - others: default mode
     */
    la      t0, exc_entry
    csrw    CSR_MTVEC, t0
    csrs    CSR_MTVEC, 0x3

    /* Initialize GP and Stack Pointer SP */
    .option push
    .option norelax
    la      gp, __sdata_start__+0x800

    .option pop
    la      sp, __stack_end__
    la      tp, __tbss_start__


    /* ---------------------------------------------------------------------- */
    /* Startup Stage 2                                                        */
    /* ---------------------------------------------------------------------- */

.L_data_init:
    /* -------------------------------------------------- */
    /* Copy data from ROM (RW)
     *
     * uint32_t* pdst = __data_start__;
     * uint32_t* pend = __data_end__;
     * uint32_t* psrc = __data_load_start__;
     * while (pdst < pend) {
     *     *pdst++ = *psrc++;
     * }
     */
    la      a0, __data_load_start__
    la      a1, __data_start__
    la      a2, __data_end__
    bgeu    a1, a2, 2f      /* 2f: forward nearest label `2` */
1:
    lw      t0, (a0)
    sw      t0, (a1)
    addi    a0, a0, 4
    addi    a1, a1, 4
    bltu    a1, a2, 1b      /* 1b: backward nearest label `1` */
2:
    nop

.L_tdata_init:
    /* -------------------------------------------------- */
    /* Copy tdata from ROM
     *
     * uint32_t* pdst = __tdata_start__;
     * uint32_t* pend = __tdata_end__;
     * uint32_t* psrc = __tdata_load_start__;
     * while (pdst < pend) {
     *     *pdst++ = *psrc++;
     * }
     */
    la      a0, __tdata_load_start__
    la      a1, __tdata_start__
    la      a2, __tdata_end__
    bgeu    a1, a2, 2f
1:
    lw      t0, (a0)
    sw      t0, (a1)
    addi    a0, a0, 4
    addi    a1, a1, 4
    bltu    a1, a2, 1b
2:
    nop


.L_sdata_init:
    /* -------------------------------------------------- */
    /* Copy sdata from rom
     *
     * uint32_t* pdst = __sdata_start__;
     * uint32_t* pend = __sdata_end__;
     * uint32_t* psrc = __sdata_load_start__;
     * while (pdst < pend) {
     *     *pdst++ = *psrc++;
     * }
     */
    la      a0, __sdata_load_start__
    la      a1, __sdata_start__
    la      a2, __sdata_end__
    bgeu    a1, a2, 2f
1:
    lw      t0, (a0)
    sw      t0, (a1)
    addi    a0, a0, 4
    addi    a1, a1, 4
    bltu    a1, a2, 1b
2:
    nop


.L_rodata_init:
    /* -------------------------------------------------- */
    /* Copy rodata from rom (RO)
     *
     * uint32_t* pdst = __rodata_start__;
     * uint32_t* pend = __rodata_end__;
     * uint32_t* psrc = __rodata_load_start__;
     * while (pdst < pend) {
     *     *pdst++ = *psrc++;
     * }
     */
    la      a0, __rodata_load_start__
    la      a1, __rodata_start__
    beq     a0, a1, 2f
    la      a2, __rodata_end__
    bgeu    a1, a2, 2f
1:
    lw      t0, (a0)
    sw      t0, (a1)
    addi    a0, a0, 4
    addi    a1, a1, 4
    bltu    a1, a2, 1b
2:
    nop


.L_bss_init:
    /* -------------------------------------------------- */
    /* bss (ZO) */
    la      a0, __bss_start__
    la      a1, __bss_end__
    bgeu    a0, a1, 2f
1:
    sw      zero, 0(a0)
    addi    a0, a0, 4
    bltu    a0, a1, 1b
2:
    nop


.L_tbss_init:
    /* -------------------------------------------------- */
    /* Zero tbss (ZO)
     *
     * for (pdst = __tbss_start__, pend = __tbss_end__;pdst < pend;pdst++) {
     *     *pdst = 0;
     * }
     */
    la      a0, __tbss_start__
    la      a1, __tbss_end__
    bgeu    a0, a1, 2f
1:
    sw      zero, 0(a0)
    addi    a0, a0, 4
    bltu    a0, a1, 1b
2:
    nop


.L_sbss_init:
    /* -------------------------------------------------- */
    /* Zero sbss (ZO) 
     *
     * for (pdst = __sbss_start__, pend = __sbss_end__;pdst < pend;pdst++) {
     *     *pdst = 0;
     * }
     */
    la      a0, __sbss_start__
    la      a1, __sbss_end__
    bgeu    a0, a1, 2f
1:
    sw      zero, 0(a0)
    addi    a0, a0, 4
    bltu    a0, a1, 1b
2:
    nop

//.L_bss_tbss_sbss_init:
//    call System_clean_up_bss_section

.L_heap_init:
    /* -------------------------------------------------- */
    /* TODO: heap (malloc/free) */
    call heap_init
    nop
    
    /* ---------------------------------------------------------------------- */
    /* Startup Stage 3                                                        */
    /* ---------------------------------------------------------------------- */
#ifdef __riscv_flen
    /* Enable FPU */
    li      t0, MSTATUS_FS
    csrs    mstatus, t0
    csrw    fcsr, x0
#endif

    /* Enable mcycle and minstret counter */
    csrci   CSR_MCOUNTINHIBIT, 0x5


#ifdef __USING_NEWLIBC
    /* Call global constructors */
    la      a0, __libc_fini_array
    call    atexit
    /* Call C/C++ constructor start up code */
    call    __libc_init_array
#else
    /*
     * Call runtime library constructors 
     *
     * void (*func)(void);
     * for (func = __ctors_start__;func != __ctors_end__;func++) {
     *     func();
     * }
     */
//    la      s0, __ctors_start__
//    la      s1, __ctors_end__
//1:
//    beq     s0, s1, 2f
//    lw      t1, 0(s0)
//    addi    s0, s0, 4  
//    jalr    t1
//    j       1b
//2:
//    nop
#endif
    /*
     * Call vendor defined SystemInit to
     * initialize the micro-controller system.
     */
    call SystemInit

    /* do pre-init steps before main */
    call _premain_init
    /* ===== Call Main Function  ===== */
    /* argc = argv = 0 */
    li a0, 0
    li a1, 0
    call main
    /* do post-main steps after main */
    call _postmain_fini

.L_dead_loop:
    j .L_dead_loop
