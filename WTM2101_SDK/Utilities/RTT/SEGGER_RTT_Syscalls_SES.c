/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 2014 - 2019 SEGGER Microcontroller GmbH             *
*                                                                    *
*           www.segger.com     Support: support@segger.com           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* - Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* - Neither the name of SEGGER Microcontroller GmbH                  *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED.                                                        *
* IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
---------------------------END-OF-HEADER------------------------------
File    : SEGGER_RTT_Syscalls_SES.c
Purpose : Reimplementation of printf, puts and __getchar using RTT
          in SEGGER Embedded Studio.
          To use RTT for printf output, include this file in your
          application.
Revision: $Rev: 12804 $
----------------------------------------------------------------------
*/
#if (defined __SES_ARM) || (defined __CROSSWORKS_ARM) || (defined __SES_RISCV)

#include "SEGGER_RTT.h"
#include <stdarg.h>
#include <stdio.h>
#include "limits.h"
#include "__libc.h"
#include "__vfprintf.h"

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
//
// Select string formatting implementation.
//
// RTT printf formatting
//  - Configurable stack usage. (SEGGER_RTT_PRINTF_BUFFER_SIZE in SEGGER_RTT_Conf.h)
//  - No maximum string length.
//  - Limited conversion specifiers and flags. (See SEGGER_RTT_printf.c)
// Standard library printf formatting
//  - Configurable formatting capabilities.
//  - Full conversion specifier and flag support.
//  - Maximum string length has to be known or (slightly) slower character-wise output.
//
// #define PRINTF_USE_SEGGER_RTT_FORMATTING    0 // Use standard library formatting
// #define PRINTF_USE_SEGGER_RTT_FORMATTING    1 // Use RTT formatting
//
#ifndef   PRINTF_USE_SEGGER_RTT_FORMATTING
  #define PRINTF_USE_SEGGER_RTT_FORMATTING    0
#endif
//
// If using standard library formatting,
// select maximum output string buffer size or character-wise output.
//
// #define PRINTF_BUFFER_SIZE                  0 // Use character-wise output
// #define PRINTF_BUFFER_SIZE                128 // Default maximum string length
//
#ifndef   PRINTF_BUFFER_SIZE
  #define PRINTF_BUFFER_SIZE                128
#endif

#endif
/****** End Of File *************************************************/
