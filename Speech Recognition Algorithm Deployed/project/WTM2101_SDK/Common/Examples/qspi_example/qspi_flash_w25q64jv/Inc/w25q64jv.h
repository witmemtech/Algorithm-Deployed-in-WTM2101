/**
  ******************************************************************************
  * @file    w25q64jv.h
  * @brief   Header for w25q64jv.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/** Define to Prevent Recursive Inclusion */
#ifndef W25Q64JV_H
#define W25Q64JV_H

#ifdef __cplusplus
extern "C" {
#endif 

/** Includes */
#include "qspi.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "dma.h"


/** @defgroup w25q64jv COMMAND MARCO DEFINED
* @{
*/
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
#define PAGE_PROG_CMD                        0x02
#define QUAD_INPUT_PAGE_PROG_CMD             0x32
#define EXT_QUAD_IN_FAST_PROG_CMD            0x12

/* 擦除操作 */
#define SECTOR_ERASE_CMD                     0x20
#define CHIP_ERASE_CMD                       0xC7
#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

#define GLOBAL_BLOCK_UNLOCK                  0x98

#define W25Q64JV_SIZE                                                                8388608        
#define W25Q64JV_SECTOR_SIZE                                                  	4096
#define W25Q64JV_PAGE_SIZE                                                    	256            
/**
* @}
*/
#define w25q64jv_SECTOR_BLOCK_ERASE_MAX_TIME_S                                       100
#define W25Q64JV_MALLOC(size)        malloc(size)
#define W25Q64JV_free(pointer)       free(pointer)  

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint8_t                 qspi_1line_or_4lines;
    uint32_t                page_size, sector_size,flash_size;
    QSPI_CtlInitTypeDef     *qspi_ctl;
    QSPI_TypeDef        *qspi_hd;
    uint8_t                 send_dma_flag,send_dma_channel;
    DMA_InitTypeDef         *send_dma_inittypedef;
    uint8_t                 receive_dma_flag,receive_dma_channel;
    DMA_InitTypeDef         *receive_dma_inittypedef;
}W25q64jv;
#pragma pack(pop) 

#define W25Q64JV_QSPI_1LINE                                                          0
#define W25Q64JV_QSPI_4LINES                                                         !W25Q64JV_QSPI_1LINE

extern int w25q64jv_qspi_init(W25q64jv *W25q64jv_hd);
extern int w25q64jv_open(W25q64jv *W25q64jv_hd, QSPI_TypeDef *qspi_hd,uint8_t line_type);
extern uint8_t w25q64jv_read_status_reg(W25q64jv *W25q64jv_hd, int8_t reg_cmd);
extern void w25q64jv_write_enable(W25q64jv *W25q64jv_hd);
extern void w25q64jv_write_status_reg(W25q64jv *W25q64jv_hd, uint8_t reg_cmd, uint8_t status);
extern void w25q64jv_write_enable_for_volatile(W25q64jv *W25q64jv_hd);
extern int w25q64jv_sector_erase(W25q64jv *W25q64jv_hd, uint8_t instruction, uint32_t address);
extern int w25q64jv_fast_quad_read(W25q64jv *W25q64jv_hd, uint32_t address, uint8_t *data,uint32_t len);
extern int w25q64jv_quad_page_program(W25q64jv *W25q64jv_hd, uint32_t address, uint8_t *data, int len);
extern int w25q64jv_read(W25q64jv *W25q64jv_hd, uint32_t address, uint8_t *data,uint32_t len);
extern int w25q64jv_page_program(W25q64jv *W25q64jv_hd, uint32_t address, uint8_t *data, int len);
extern int w25q64jv_chip_erase(W25q64jv *W25q64jv_hd);
extern int w25q64jv_receive_dma_init(W25q64jv *W25q64jv_hd,uint8_t dma_channel);
extern int w25q64jv_send_dma_init(W25q64jv *W25q64jv_hd, uint8_t dma_channel);
extern int w25q64jv_read_jedec_id(W25q64jv *W25q64jv_hd, uint8_t *id);
/**
* @}
*/
#ifdef __cplusplus
}
#endif

#endif    
