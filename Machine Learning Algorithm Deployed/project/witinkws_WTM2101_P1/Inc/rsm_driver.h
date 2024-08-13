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
#ifndef RSM_DRIVER_H_BEA833F2_DC4A_225B_A8DB_9453CCBE08EC_INCLUDED_
#define RSM_DRIVER_H_BEA833F2_DC4A_225B_A8DB_9453CCBE08EC_INCLUDED_

// abbreviation: ASC
//
// ANCSONIC
// ^  ^   ^
// A  S   C
//

// sleep: GPIO0  == 0
// wake : GPIO11 == 0
void gpio_wake_init(void);

void GPIO_IRQHandler(void);
void wfi_wait_GPIO(void);

#endif

