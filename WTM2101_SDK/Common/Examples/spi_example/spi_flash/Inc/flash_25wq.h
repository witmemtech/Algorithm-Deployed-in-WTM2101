/**
  ******************************************************************************
  * @file    flash_25wq.h
  * @brief   Header for flash_25wq.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __FLASH_25WQ_H__
#define __FLASH_25WQ_H__

#define FLASH_ID_SIZE (2)
 /* 复位操作 */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99
#define ENTER_QPI_MODE_CMD                   0x38
#define EXIT_QPI_MODE_CMD                    0xFF

/* 识别操作 */
#define READ_ID_CMD                          0x90
#define DUAL_READ_ID_CMD                     0x92
#define QUAD_READ_ID_CMD                     0x94
#define READ_JEDEC_ID_CMD                    0x9F

/* 读操作 */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* 写操作 */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04
#define WRITE_ENABLE_VOLATILE_CMD            0x50

/* 寄存器操作 */
#define READ_STATUS_REG1_CMD                  0x05
#define READ_STATUS_REG2_CMD                  0x35
#define READ_STATUS_REG3_CMD                  0x15
#define WRITE_STATUS_REG1_CMD                 0x01
#define WRITE_STATUS_REG2_CMD                 0x31
#define WRITE_STATUS_REG3_CMD                 0x11

/* 编程操作 */
#define QUAD_INPUT_PAGE_PROG_CMD             0x32
#define EXT_QUAD_IN_FAST_PROG_CMD            0x12
#define PAGE_PROG_CMD                        0x02
/* 擦除操作 */
#define PAGE_ERASE_CMD                       0x81
#define SECTOR_ERASE_CMD                     0x20
#define CHIP_ERASE_CMD                       0xC7
#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

#define GLOBAL_BLOCK_UNLOCK                  0x98

#define FLASH_PAGE_SIZE                      256

void spi_cs_high(void);
void spi_cs_low(void);
void spi_read_flash_id(uint8_t *id);
void spi_flash_write_enable(void);
void spi_flash_read(uint8_t *buf, uint32_t addr, int len);
uint8_t spi_flash_read_status_reg(void);
void spi_flash_page_erase(uint32_t addr);
void spi_flash_page_prog(uint8_t *data, uint32_t addr, int len);
void spi_flash_global_block_unlock(void);
void spi_flash_write_disable(void);
#endif