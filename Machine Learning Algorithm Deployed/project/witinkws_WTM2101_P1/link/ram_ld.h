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
#ifndef RAM_LD_H_AD0A10D2_DEB5_2E13_4617_D8ADE0F0F941_INCLUDED_
#define RAM_LD_H_AD0A10D2_DEB5_2E13_4617_D8ADE0F0F941_INCLUDED_

extern uint32_t __vectors_start__;
extern uint32_t __vectors_end__;

extern uint32_t __text_start__;
extern uint32_t __text_end__;
extern uint32_t __text_load_start__;

extern uint32_t __rodata_start__;
extern uint32_t __rodata_end__;
extern uint32_t __rodata_load_start__;

extern uint32_t __srodata_start__;
extern uint32_t __srodata_end__;
extern uint32_t __srodata_load_start__;

extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __data_load_start__;

extern uint32_t __tdata_start__;
extern uint32_t __tdata_end__;
extern uint32_t __tdata_load_start__;

extern uint32_t __sdata_start__;
extern uint32_t __sdata_end__;
extern uint32_t __sdata_load_start__;

extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __bss_load_start__;

extern uint32_t __tbss_start__;
extern uint32_t __tbss_end__;
extern uint32_t __tbss_load_start__;

extern uint32_t __sbss_start__;
extern uint32_t __sbss_end__;
extern uint32_t __sbss_load_start__;

extern uint32_t __heap_start__;
extern uint32_t __heap_end__;

extern uint32_t __stack_start__;
extern uint32_t __stack_end__;

#endif

