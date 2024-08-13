/* vim: set fileencoding=utf-8:
 *
 *                   GNU GENERAL PUBLIC LICENSE
 *                       Version 2, June 1991
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 *
 */
#ifndef RISCV_INTRINSIC_H_DDCA3096_9B82_FBB7_C9B7_34BFF2FDE2CB_INCLUDED_
#define RISCV_INTRINSIC_H_DDCA3096_9B82_FBB7_C9B7_34BFF2FDE2CB_INCLUDED_

//  asm ( assembler template               /* codes    */
//      : output operands                  /* optional */
//      : input operands                   /* optional */
//      : list of clobbered registers      /* optional */
//      );
//
//  "r" -or- "=r"
//  * "r" says to GCC to use any register for storing the operands. 
//  * output operand constraint should have a constraint modifier "=".
//    And this modifier says that it is the output operand and is write-only.
//  * "f" means float registers
//

#include <stdint.h>
#include "nmsis_gcc.h"

#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE  __attribute__((always_inline)) static inline
#endif

#ifndef   __FORCE_NOINLINE
  #define __FORCE_NOINLINE      __attribute__ ((noinline))
#endif

__STATIC_FORCEINLINE uint32_t __get_rv_sp(void)
{
    register uint32_t v;
    __ASM volatile("addi %0, sp, 0":"=r"(v) : : "memory");
    return v;
}

//
//RNE Round to Nearest  (ties to Even)
//RTZ Round towards 0 
//RDN Round Down        (towards -maximal)
//RUP Round Up          (towards +maximal)
//RMM Round to Nearest  (ties to Max Magnitude)
//
__STATIC_FORCEINLINE int32_t __roundf(float v)
{
    int32_t out;
    __ASM volatile("fcvt.w.s %0, %1, rmm" : "=r"(out) : "f"(v): "memory");
    return out;
}


__STATIC_FORCEINLINE float __sqrtf(float v)
{
    float out;
    __ASM volatile("fsqrt.s %0, %1" : "=f"(out) : "f"(v));
    return out;
}


__STATIC_FORCEINLINE int32_t __sat_uint8(int32_t v)
{
    int32_t out;
    __ASM volatile("kslliw %0, %1, 23" : "=r"(out) : "r"(v));
    out >>= 23;
    return out;
}

//
//  output: -1024 .. 1023
//
__STATIC_FORCEINLINE int32_t __sat_int11(int32_t v)
{
    int32_t out;
    __ASM volatile("kslliw %0, %1, 21" : "=r"(out) : "r"(v));
    out >>= 21;
    return out;
}

//
//  output: -2048 .. 2047
//
__STATIC_FORCEINLINE int32_t __sat_int12(int32_t v)
{
    int32_t out;
    __ASM volatile("kslliw %0, %1, 20" : "=r"(out) : "r"(v));
    out >>= 20;
    return out;
}


__STATIC_FORCEINLINE int32_t __sat_int16(int32_t v)
{
    int32_t out;
    __ASM volatile("kslliw %0, %1, 16" : "=r"(out) : "r"(v));
    out >>= 16;
    return out;
}




#endif

