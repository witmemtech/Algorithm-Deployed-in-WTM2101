#ifndef _WNPU_DEVICE_H_INCLUDED
#define _WNPU_DEVICE_H_INCLUDED

#define xNB01P
#define xBB04P
#define BB04P1

#ifdef NB01P
#define SPI_ACCESS
#define SRAM_LENGTH 4096
#define SRAM_FIFO_ADDR 3072
#define SRAM_FIFO_LENGTH 1024
#else
#ifdef BB04P
#define APB_ACCESS
#define SRAM_LENGTH 8192
#define SRAM_FIFO_ADDR 7168
#define SRAM_FIFO_LENGTH 1024
#else
#ifdef BB04P1
#define APB_ACCESS
#define SRAM_LENGTH 8192
#define SRAM_FIFO_ADDR 7168
#define SRAM_FIFO_LENGTH 1024
#endif
#endif
#endif

#ifdef APB_ACCESS
#ifdef BB04P1
#define WTN_NPU_BASE 0x64002000 // bb04p1
#else
#ifdef BB04P
#define WTN_NPU_BASE 0x50004000 // bb04p
#endif
#endif

#include <WTM2101.h>


#define WIT_REG(x)  { \
						(volatile unsigned int *)(WTN_NPU_BASE + (x << 1)); \
					}

#define WRITE8(addr, value) { \
							*(volatile uint8_t *)(addr) = (uint8_t)value; \
						  }
#define WRITE16(addr, value)  {\
						  *(volatile uint16_t *)(addr) = (uint16_t)value;\
						  }
#define WRITE32(addr, value) {\
						*(volatile uint32_t *)(addr) = (uint32_t)value; \
						}

static inline uint8_t READ8(int addr) {
	 uint8_t value = (uint8_t)(*(volatile uint8_t *)(addr));
	  return value;
}

//#define READ16(addr)                (uint16_t)(*(volatile uint16_t *)(addr))

static inline short unsigned int READ16(int addr) {
	short unsigned int value = (*(volatile short unsigned int *)(addr));
	return value; 
}


static inline uint32_t READ32(int addr) {
	uint32_t value = ((uint32_t)(*(volatile uint32_t *)(addr))); 
	return value;
}

#define READ(addr) READ32(addr)
#define WRITE(addr, value) WRITE32(addr, value)

#define WRITE32_NPU(addr, value) WRITE32(addr + WTN_NPU_BASE, value)
#define READ32_NPU(addr) READ32(addr + WTN_NPU_BASE)
#define WRITE16_NPU(addr, value) WRITE16(addr + WTN_NPU_BASE, value)
#define READ16_NPU(addr) READ16(addr + WTN_NPU_BASE)
#define WRITE8_NPU(addr, value) WRITE8(addr + WTN_NPU_BASE, value)
#define READ8_NPU(addr) READ8(addr + WTN_NPU_BASE)
#else
#ifdef SPI_ACCESS
#define WNPU_REG_BASE 0x0 // NB01P
#define WIT_REG(x) ((unsigned int)(WTN_NPU_BASE + x))
#else
#error Access chip mode is not supported
#endif // SPI_ACCESS
#endif // APB_ACCESS

#define ACTV_TABLE_LEN 256

#endif // _WNPU_DEVICE_H_INCLUDED
