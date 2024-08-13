#ifndef UCONTEXT_H_E9ABF307_A8FB_B728_D2D0_B27C8ECD45A8_INCLUDED_
#define UCONTEXT_H_E9ABF307_A8FB_B728_D2D0_B27C8ECD45A8_INCLUDED_

#ifndef __BEGIN_ALIGN
#define __BEGIN_ALIGN
#define __END_ALIGN     __attribute__ ((aligned (16)))
#endif

typedef unsigned long           sigset_t;   // reserved
typedef unsigned long           flags_t;    // reserved

typedef struct __mcontext       mcontext_t;
typedef struct __ucontext       ucontext_t;
typedef struct __sigaltstack    stack_t;

struct __mcontext {
    // offset: 0
    unsigned int x0;        // reserved
    unsigned int x1;        // ra
    unsigned int x2;        // sp
    unsigned int x3;        // sp
    unsigned int x4;        // tp
    unsigned int x5;        // t0
    unsigned int x6;        // t1
    unsigned int x7;        // t2
    unsigned int x8;        // s0
    unsigned int x9;        // s1
    unsigned int x10;       // a0/ret
    unsigned int x11;       // a1
    unsigned int x12;       // a2
    unsigned int x13;       // a3
    unsigned int x14;       // a4
    unsigned int x15;       // a5
    unsigned int x16;       // a6
    unsigned int x17;       // a7
    unsigned int x18;       // a7
    unsigned int x19;       // a7
    unsigned int x20;       // a7
    unsigned int x21;       // a7
    unsigned int x22;       // a7
    unsigned int x23;       // a7
    unsigned int x24;       // a7
    unsigned int x25;       // a7
    unsigned int x26;       // a7
    unsigned int x27;       // a7
    unsigned int x28;       // t3
    unsigned int x29;       // t4
    unsigned int x30;       // t5
    unsigned int x31;       // t6

    // offset: 32
    unsigned int fs0;
    unsigned int fs1;
    unsigned int fs2;
    unsigned int fs3;
    unsigned int fs4;
    unsigned int fs5;
    unsigned int fs6;
    unsigned int fs7;
    unsigned int fs8;
    unsigned int fs9;
    unsigned int fs10;
    unsigned int fs11;
    unsigned int fs12;
};

struct __sigaltstack {
    void*       ss_sp;
    int         ss_flags;
    size_t      ss_size;
};


__BEGIN_ALIGN
struct __ucontext {
  // ucontext.s want this fields in order
  // DO NOT change [begin]
  mcontext_t	uc_mcontext;
  // DO NOT change [end]
  ucontext_t* uc_link;
  stack_t	    uc_stack;
  sigset_t	uc_sigmask;
  flags_t     uc_flags;
  uint32_t    uc_custom;
} __END_ALIGN;


/**
* @brief  printf the context info 
* @param  ucp: the context struct
* @retval None
*/  
void printcontext(const ucontext_t* ucp);

/**
* @brief  construct the context info 
* @note   the context must fill by getcontext!
* @param  ucp: the context struct
* @param  func: the function entry
* @param  argc: the function parameter
* @retval Greater than 0 for success, otherwise failure
*/  
void makecontext(ucontext_t* ucp, void (*func) (void), int argc, ...);

/**
* @brief  get the context info 
* @param  ucp: the context struct
* @retval Greater than or equal 0 for success, otherwise failure
*/  
int getcontext(ucontext_t* ucp);

/**
* @brief  set the context info 
* @param  ucp: the context struct
* @retval Greater than or equal 0 for success, otherwise failure
*/  
int setcontext(const ucontext_t* ucp);

/**
* @brief  swap the context info 
* @param  oucp: the current context struct
* @param  ucp: the swaped context struct
* @retval Greater than or equal 0 for success, otherwise failure
*/ 
int swapcontext(ucontext_t *oucp, ucontext_t *ucp);

#endif

