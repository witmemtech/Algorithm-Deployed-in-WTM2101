/**
* @file    ucontext.c
* @brief   The Source Codes for the ucontext.c Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#include "ucontext.h"

void printcontext(const ucontext_t* ucp)
{
    printf(".uc_link   = %p\n", ucp->uc_link);
    printf(".uc_mcontext:\n");
    printf("  .x1 (ra) = %p\n", ucp->uc_mcontext.x1);
    printf("  .x2 (sp) = %p\n", ucp->uc_mcontext.x2);
    printf("  .x3 (gp) = %p\n", ucp->uc_mcontext.x3);
    printf("  .x4 (tp) = %p\n", ucp->uc_mcontext.x4);
    printf("  .x5 (t0) = %p\n", ucp->uc_mcontext.x5);
    printf("  .x6 (t1) = %p\n", ucp->uc_mcontext.x6);
    printf("  .x7 (t2) = %p\n", ucp->uc_mcontext.x7);
    printf("  .x8 (s0) = %p\n", ucp->uc_mcontext.x8);
    printf("  .x9 (s1) = %p\n", ucp->uc_mcontext.x9);
    printf("  .x10(a0) = %p\n", ucp->uc_mcontext.x10);
    printf("  .x11(a1) = %p\n", ucp->uc_mcontext.x11);
    printf("  .x12(a2) = %p\n", ucp->uc_mcontext.x12);
    printf("  .x13(a3) = %p\n", ucp->uc_mcontext.x13);
    printf("  .x14(a4) = %p\n", ucp->uc_mcontext.x14);
    printf("  .x15(a5) = %p\n", ucp->uc_mcontext.x15);
    printf("  .x16(a6) = %p\n", ucp->uc_mcontext.x16);
    printf("  .x17(a7) = %p\n", ucp->uc_mcontext.x17);
    printf("  .x18(s2) = %p\n", ucp->uc_mcontext.x18);
    printf("  .x19(s3) = %p\n", ucp->uc_mcontext.x19);
    printf("  .x20(s4) = %p\n", ucp->uc_mcontext.x20);
    printf("  .x21(s5) = %p\n", ucp->uc_mcontext.x21);
    printf("  .x22(s6) = %p\n", ucp->uc_mcontext.x22);
    printf("  .x23(s7) = %p\n", ucp->uc_mcontext.x23);
    printf("  .x24(s8) = %p\n", ucp->uc_mcontext.x24);
    printf("  .x25(s9) = %p\n", ucp->uc_mcontext.x25);
    printf("  .x26(s10)= %p\n", ucp->uc_mcontext.x26);
    printf("  .x27(s11)= %p\n", ucp->uc_mcontext.x27);
    printf("  .x28(t3) = %p\n", ucp->uc_mcontext.x28);
    printf("  .x29(t4) = %p\n", ucp->uc_mcontext.x29);
    printf("  .x30(t5) = %p\n", ucp->uc_mcontext.x30);
    printf("  .x31(t6) = %p\n", ucp->uc_mcontext.x31);
    // too long, just ignore float print
    printf(".uc_stack\n");
    printf("  .sp      = %p\n", ucp->uc_stack.ss_sp);
    printf("  .size    = %p\n", ucp->uc_stack.ss_size);
}

void makecontext(ucontext_t* ucp, void (*func) (void), int argc, ...)
{
    unsigned int sp;


    //
    //  high-addr
    // |         |
    // |ss_size-1|
    // |         | <-- new_sp here
    // |         |
    // |         |
    // |0        | <-- uc_stack.ss_sp
    // |         |
    //  low--addr
    //
    
    // bugfixed-2022.08.01: gcc stack frame alignment is 128 bytes --- begin ---
    sp = ((uint32_t)ucp->uc_stack.ss_sp) + ucp->uc_stack.ss_size - 16*sizeof(uint8_t);
    sp = (sp >> 4) << 4; // 128bits align
    // --- end ---

    ucp->uc_mcontext.x1 = (unsigned int)func;
    ucp->uc_mcontext.x2 = sp;
}

