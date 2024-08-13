#include "riscv_encoding.h"


/*
 * int getcontext(ucontext_t* ucp);
 */
.align 4
.global getcontext
getcontext:
    //csrc CSR_MSTATUS, MSTATUS_MIE
    /*  x10 alias function param `a0` */
    /* !dont touch anything, inclued sp! */
    /* save ucontext.uc_mcontext.regiters = {x...} */
    STORE x1,  1 *REGBYTES(a0)
    STORE x2,  2 *REGBYTES(a0)
    STORE x3,  3 *REGBYTES(a0)
    STORE x4,  4 *REGBYTES(a0)
    STORE x5,  5 *REGBYTES(a0)
    STORE x6,  6 *REGBYTES(a0)
    STORE x7,  7 *REGBYTES(a0)
    STORE x8,  8 *REGBYTES(a0)
    STORE x9,  9 *REGBYTES(a0)
    /*STORE x10, 10*REGBYTES(a0)*/
    STORE x11, 11*REGBYTES(a0)
    STORE x12, 12*REGBYTES(a0)
    STORE x13, 13*REGBYTES(a0)
    STORE x14, 14*REGBYTES(a0)
    STORE x15, 15*REGBYTES(a0)
#ifndef __riscv_32e
    STORE x16, 16*REGBYTES(a0)
    STORE x17, 17*REGBYTES(a0)
    STORE x18, 18*REGBYTES(a0)
    STORE x19, 19*REGBYTES(a0)
    STORE x20, 20*REGBYTES(a0)
    STORE x21, 21*REGBYTES(a0)
    STORE x22, 22*REGBYTES(a0)
    STORE x23, 23*REGBYTES(a0)
    STORE x24, 24*REGBYTES(a0)
    STORE x25, 25*REGBYTES(a0)
    STORE x26, 26*REGBYTES(a0)
    STORE x27, 27*REGBYTES(a0)
    STORE x28, 28*REGBYTES(a0)
    STORE x29, 29*REGBYTES(a0)
    STORE x30, 30*REGBYTES(a0)
    STORE x31, 31*REGBYTES(a0)
#endif /* __riscv_32e */
#ifndef __riscv_float_abi_soft
	FPSTORE fs0,  32*REGBYTES(a0)
	FPSTORE fs1,  33*REGBYTES(a0)
	FPSTORE fs2,  34*REGBYTES(a0)
	FPSTORE fs3,  35*REGBYTES(a0)
	FPSTORE fs4,  36*REGBYTES(a0)
	FPSTORE fs5,  37*REGBYTES(a0)
	FPSTORE fs6,  38*REGBYTES(a0)
	FPSTORE fs7,  39*REGBYTES(a0)
	FPSTORE fs8,  40*REGBYTES(a0)
	FPSTORE fs9,  41*REGBYTES(a0)
	FPSTORE fs10, 42*REGBYTES(a0)
	FPSTORE fs11, 44*REGBYTES(a0)
#endif

    //csrs CSR_MSTATUS, MSTATUS_MIE
    li x10, 0 /* return 0 (a0) */
    ret


/*
 * int setcontext(const ucontext_t* ucp);
 */
.align 4
.global setcontext
setcontext:
    //csrc CSR_MSTATUS, MSTATUS_MIE
    /*  x10 alias function param `a0` */
    /* restore {x...} = ucontext.uc_mcontext.regiters */
    LOAD x1,  1 *REGBYTES(a0)
    LOAD x2,  2 *REGBYTES(a0)
    LOAD x3,  3 *REGBYTES(a0)
    LOAD x4,  4 *REGBYTES(a0)
    LOAD x5,  5 *REGBYTES(a0)
    LOAD x6,  6 *REGBYTES(a0)
    LOAD x7,  7 *REGBYTES(a0)
    LOAD x8,  8 *REGBYTES(a0)
    LOAD x9,  9 *REGBYTES(a0)
    /*LOAD x10, 10*REGBYTES(a0)*/
    LOAD x11, 11*REGBYTES(a0)
    LOAD x12, 12*REGBYTES(a0)
    LOAD x13, 13*REGBYTES(a0)
    LOAD x14, 14*REGBYTES(a0)
    LOAD x15, 15*REGBYTES(a0)
#ifndef __riscv_32e
    LOAD x16, 16*REGBYTES(a0)
    LOAD x17, 17*REGBYTES(a0)
    LOAD x18, 18*REGBYTES(a0)
    LOAD x19, 19*REGBYTES(a0)
    LOAD x20, 20*REGBYTES(a0)
    LOAD x21, 21*REGBYTES(a0)
    LOAD x22, 22*REGBYTES(a0)
    LOAD x23, 23*REGBYTES(a0)
    LOAD x24, 24*REGBYTES(a0)
    LOAD x25, 25*REGBYTES(a0)
    LOAD x26, 26*REGBYTES(a0)
    LOAD x27, 27*REGBYTES(a0)
    LOAD x28, 28*REGBYTES(a0)
    LOAD x29, 29*REGBYTES(a0)
    LOAD x30, 30*REGBYTES(a0)
    LOAD x31, 31*REGBYTES(a0)
#endif
#ifndef __riscv_float_abi_soft
	FPLOAD fs0,  32*REGBYTES(a0)
	FPLOAD fs1,  33*REGBYTES(a0)
	FPLOAD fs2,  34*REGBYTES(a0)
	FPLOAD fs3,  35*REGBYTES(a0)
	FPLOAD fs4,  36*REGBYTES(a0)
	FPLOAD fs5,  37*REGBYTES(a0)
	FPLOAD fs6,  38*REGBYTES(a0)
	FPLOAD fs7,  39*REGBYTES(a0)
	FPLOAD fs8,  40*REGBYTES(a0)
	FPLOAD fs9,  41*REGBYTES(a0)
	FPLOAD fs10, 42*REGBYTES(a0)
	FPLOAD fs11, 44*REGBYTES(a0)
#endif
    //csrs CSR_MSTATUS, MSTATUS_MIE
    li x10, 0 /* return 0 (a0) */
    ret


/*
 * int swapcontext(ucontext_t *oucp, ucontext_t *ucp);
 *                 register a0       register a1
 */
.align 4
.global swapcontext 
swapcontext:
    /*  x10 alias function param `a0` */
    /*  x11 alias function param `a1` */
    /* !dont touch anything, inclued sp! */
    /* save ucontext.uc_mcontext.regiters = {x...} */
    STORE x1,  1 *REGBYTES(a0)
    STORE x2,  2 *REGBYTES(a0)
    STORE x3,  3 *REGBYTES(a0)
    STORE x4,  4 *REGBYTES(a0)
    STORE x5,  5 *REGBYTES(a0)
    STORE x6,  6 *REGBYTES(a0)
    STORE x7,  7 *REGBYTES(a0)
    STORE x8,  8 *REGBYTES(a0)
    STORE x9,  9 *REGBYTES(a0)
    /*STORE x10, 10*REGBYTES(a0)*/
    /*STORE x11, 11*REGBYTES(a0)*/
    STORE x12, 12*REGBYTES(a0)
    STORE x13, 13*REGBYTES(a0)
    STORE x14, 14*REGBYTES(a0)
    STORE x15, 15*REGBYTES(a0)
#ifndef __riscv_32e
    STORE x16, 16*REGBYTES(a0)
    STORE x17, 17*REGBYTES(a0)
    STORE x18, 18*REGBYTES(a0)
    STORE x19, 19*REGBYTES(a0)
    STORE x20, 20*REGBYTES(a0)
    STORE x21, 21*REGBYTES(a0)
    STORE x22, 22*REGBYTES(a0)
    STORE x23, 23*REGBYTES(a0)
    STORE x24, 24*REGBYTES(a0)
    STORE x25, 25*REGBYTES(a0)
    STORE x26, 26*REGBYTES(a0)
    STORE x27, 27*REGBYTES(a0)
    STORE x28, 28*REGBYTES(a0)
    STORE x29, 29*REGBYTES(a0)
    STORE x30, 30*REGBYTES(a0)
    STORE x31, 31*REGBYTES(a0)
#endif /* __riscv_32e */
#ifndef __riscv_float_abi_soft
	FPSTORE fs0,  32*REGBYTES(a0)
	FPSTORE fs1,  33*REGBYTES(a0)
	FPSTORE fs2,  34*REGBYTES(a0)
	FPSTORE fs3,  35*REGBYTES(a0)
	FPSTORE fs4,  36*REGBYTES(a0)
	FPSTORE fs5,  37*REGBYTES(a0)
	FPSTORE fs6,  38*REGBYTES(a0)
	FPSTORE fs7,  39*REGBYTES(a0)
	FPSTORE fs8,  40*REGBYTES(a0)
	FPSTORE fs9,  41*REGBYTES(a0)
	FPSTORE fs10, 42*REGBYTES(a0)
	FPSTORE fs11, 44*REGBYTES(a0)
#endif

    /* restore {x...} = ucontext.uc_mcontext.regiters */
    LOAD x1,  1 *REGBYTES(a1)
    LOAD x2,  2 *REGBYTES(a1)
    LOAD x3,  3 *REGBYTES(a1)
    LOAD x4,  4 *REGBYTES(a1)
    LOAD x5,  5 *REGBYTES(a1)
    LOAD x6,  6 *REGBYTES(a1)
    LOAD x7,  7 *REGBYTES(a1)
    LOAD x8,  8 *REGBYTES(a1)
    LOAD x9,  9 *REGBYTES(a1)
    /*LOAD x10, 10*REGBYTES(a1)*/
    /*LOAD x11, 11*REGBYTES(a1)*/
    LOAD x12, 12*REGBYTES(a1)
    LOAD x13, 13*REGBYTES(a1)
    LOAD x14, 14*REGBYTES(a1)
    LOAD x15, 15*REGBYTES(a1)
#ifndef __riscv_32e
    LOAD x16, 16*REGBYTES(a1)
    LOAD x17, 17*REGBYTES(a1)
    LOAD x18, 18*REGBYTES(a1)
    LOAD x19, 19*REGBYTES(a1)
    LOAD x20, 20*REGBYTES(a1)
    LOAD x21, 21*REGBYTES(a1)
    LOAD x22, 22*REGBYTES(a1)
    LOAD x23, 23*REGBYTES(a1)
    LOAD x24, 24*REGBYTES(a1)
    LOAD x25, 25*REGBYTES(a1)
    LOAD x26, 26*REGBYTES(a1)
    LOAD x27, 27*REGBYTES(a1)
    LOAD x28, 28*REGBYTES(a1)
    LOAD x29, 29*REGBYTES(a1)
    LOAD x30, 30*REGBYTES(a1)
    LOAD x31, 31*REGBYTES(a1)
#endif
#ifndef __riscv_float_abi_soft
	FPLOAD fs0,  32*REGBYTES(a1)
	FPLOAD fs1,  33*REGBYTES(a1)
	FPLOAD fs2,  34*REGBYTES(a1)
	FPLOAD fs3,  35*REGBYTES(a1)
	FPLOAD fs4,  36*REGBYTES(a1)
	FPLOAD fs5,  37*REGBYTES(a1)
	FPLOAD fs6,  38*REGBYTES(a1)
	FPLOAD fs7,  39*REGBYTES(a1)
	FPLOAD fs8,  40*REGBYTES(a1)
	FPLOAD fs9,  41*REGBYTES(a1)
	FPLOAD fs10, 42*REGBYTES(a1)
	FPLOAD fs11, 44*REGBYTES(a1)
#endif
    ret



