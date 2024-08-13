#ifndef __JTAG_PORT_H
#define __JTAG_PORT_H
#if USE_HARDWARE
#include "stm32f4xx_gpio.h"
#endif
#define TRUE 1
#define FALSE 0

// JTAG Instruction Register Addresses
#define INST_LENGTH 5 // number of bits in the Instruction Register
#define BYPASS 0xffff
#define EXTEST 0x0000
#define SAMPLE 0x0002

#define RESET 0x2fff  // System RESET Instruction

#define IDCODE 0x1004 // IDCODE Instruction address/HALT
#define IDCODE_LEN 32 // number of bits in the ID code

#define REG_DMI 0X11  // DMI register

/**************platform**************************************/
/**************user do this**********************************/
#define DEBUG_PRINT printf

#if USE_HARDWARE
#define DELAY() {__NOP();__NOP();__NOP();}
#define Delay_ms() {\
                        for(int i = 0;i < 180000;i++) \
                            __NOP(); \
                   }

#define TCK 				   GPIO_Pin_4 // JTAG Test Clock
#define TMS 				   GPIO_Pin_5 // JTAG Mode Select
#define TDI 				   GPIO_Pin_6 // JTAG Data Input
#define TDO 				   GPIO_Pin_7 // JTAG Data Output
#ifdef CJTAG_MODE
#pragma GCC push_options
#pragma GCC optimize ("O0")
#endif
#define JTAG_IO_SET_TMS_HIGH() {GPIOB->BSRRL = TMS;}
#define JTAG_IO_SET_TMS_LOW() {GPIOB->BSRRH = TMS;}
#define JTAG_IO_SET_TMS(VALUE) {if(VALUE) {GPIOB->BSRRL = TMS;} else {GPIOB->BSRRH = TMS;}}
#ifdef CJTAG_MODE
#define JTAG_IO_SET_TCK_HIGH() {GPIOB->BSRRL = TCK;DELAY();}
#define JTAG_IO_SET_TCK_LOW() {GPIOB->BSRRH = TCK;DELAY();}
#define JTAG_STROBETCK() {GPIOB->BSRRL = TCK;DELAY();GPIOB->BSRRH = TCK;DELAY();}
#define CJTAG_STROBETCK() {GPIOB->BSRRH = TCK;DELAY();GPIOB->BSRRL = TCK;DELAY();}
#else
#define JTAG_IO_SET_TCK_HIGH() {GPIOB->BSRRL = TCK;}
#define JTAG_IO_SET_TCK_LOW() {GPIOB->BSRRH = TCK;}
#define JTAG_STROBETCK() {GPIOB->BSRRL = TCK;DELAY();GPIOB->BSRRH = TCK;DELAY();}
#define CJTAG_STROBETCK() {GPIOB->BSRRH = TCK;DELAY();GPIOB->BSRRL = TCK;DELAY();}
#endif
#define JTAG_SET_TMS_INPUT() {GPIOB->MODER  = 0x1180;}
#define JTAG_SET_TMS_OUTPUT() {GPIOB->MODER = 0x1580;}
#define JTAG_IO_SET_TCK(VALUE) {if(VALUE) {GPIOB->BSRRL = TCK;} else {GPIOB->BSRRH = TCK;}}
#define JTAG_IO_SET_TDI(VALUE) {if(VALUE) {GPIOB->BSRRL = TDI;} else {GPIOB->BSRRH = TDI;}}
#define JTAG_IO_SET(PIN, VALUE) {if(VALUE) {GPIOB->BSRRL = PIN;} else {GPIOB->BSRRH = PIN;}}
#define JTAG_READ_TDO() (GPIOB->IDR & TDO)
#define JTAG_READ_TMS() (GPIOB->IDR & TMS)
#ifdef CJTAG_MODE
#pragma GCC pop_options
#endif

#else
#define DELAY() {}
#define Delay_ms() {}
#define JTAG_IO_SET_TMS_HIGH() {}
#define JTAG_IO_SET_TMS_LOW() {}
#define JTAG_IO_SET_TMS(VALUE) {}
#define JTAG_IO_SET_TCK_HIGH() {}
#define JTAG_IO_SET_TCK_LOW() {}
#define JTAG_STROBETCK() {}
#define CJTAG_STROBETCK() {}
#define JTAG_SET_TMS_INPUT() {}
#define JTAG_SET_TMS_OUTPUT() {}
#define JTAG_IO_SET_TCK(VALUE) {}
#define JTAG_IO_SET_TDI(VALUE) {}
#define JTAG_IO_SET(PIN, VALUE) {}
#define JTAG_READ_TDO() (0)
#define JTAG_READ_TMS() (0)
#endif

extern void Jtag_Io_Config(void);
extern void Jtag_Download_Bin(const uint32_t *file, int size);
#endif

