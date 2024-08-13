/**
  ******************************************************************************
  * @file    npu.h
  * @brief   Header for npu.c module.
  * @date    2023-02-08
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __NPU_H__
#define __NPU_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "debugio.h"
#include "stdint.h"
/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup NPU
  * @{
  */
  
/* Exported constants --------------------------------------------------------*/
/** @defgroup NPU_Exported_Constants
* @{
*/

/** @defgroup NPUBaseAddress_TypeDef
* @{
*/
#define MPU_BASE_ADDR                     0x64002000
/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported types ------------------------------------------------------------*/
/** @defgroup NPU_Exported_Types NPU Exported Types 
  * @{
  */

/** 
  * @brief NPU Interrupt Mask Enumeration 
  */
typedef enum
{
    INTERRUPT_MASK_DMA_ERROR                         =   ((uint16_t) 1<<15),
    INTERRUPT_MASK_DMA_DONE                          =   ((uint16_t) 1<<14),
    INTERRUPT_MASK_SPARSE_MATRIX                     =   ((uint16_t) 1<<13),
    INTERRUPT_MASK_DACFF_UPDATE_READY                =   ((uint16_t) 1<<12),
    INTERRUPT_MASK_SINGLE_EXT2DACFF_DONE             =   ((uint16_t) 1<<11),
    INTERRUPT_MASK_EXT2DACFF_START                   =   ((uint16_t) 1<<10),
    INTERRUPT_MASK_SINGLE_POST2DACFF_DONE            =   ((uint16_t) 1<<9),
    INTERRUPT_MASK_POST2DACFF_START                  =   ((uint16_t) 1<<8),
    INTERRUPT_MASK_AHB_IBUS_RSP_ERR                  =   ((uint16_t) 1<<7),
    INTERRUPT_MASK_AHB3M_TIMEOUT                     =   ((uint16_t) 1<<6),
    INTERRUPT_MASK_ERASE_ARRAY_DONE                  =   ((uint16_t) 1<<5),
    INTERRUPT_MASK_PROG_ARRAY_DONE                   =   ((uint16_t) 1<<4),
    INTERRUPT_MASK_READ_ARRAY_DONE                   =   ((uint16_t) 1<<3),
    INTERRUPT_MASK_NNVAD_DONE                        =   ((uint16_t) 1<<2),
    INTERRUPT_MASK_ALL_ROUND_DONE                    =   ((uint16_t) 1<<1),
    INTERRUPT_MASK_CUR_ROUND_DONE                    =   ((uint16_t) 1<<0)
}NPU_IT_MASK;

/** 
  * @brief NPU Interrupt Clear Enumeration 
  */
typedef enum
{
    INTERRUPT_CLEAR_DMA_ERROR                         =   ((uint16_t) 1<<15),
    INTERRUPT_CLEAR_DMA_DONE                          =   ((uint16_t) 1<<14),
    INTERRUPT_CLEAR_SPARSE_MATRIX                     =   ((uint16_t) 1<<13),
    INTERRUPT_CLEAR_DACFF_UPDATE_READY                =   ((uint16_t) 1<<12),
    INTERRUPT_CLEAR_SINGLE_EXT2DACFF_DONE             =   ((uint16_t) 1<<11),
    INTERRUPT_CLEAR_EXT2DACFF_START                   =   ((uint16_t) 1<<10),
    INTERRUPT_CLEAR_SINGLE_POST2DACFF_DONE            =   ((uint16_t) 1<<9),
    INTERRUPT_CLEAR_POST2DACFF_START                  =   ((uint16_t) 1<<8),
    INTERRUPT_CLEAR_AHB_IBUS_RSP_ERR                  =   ((uint16_t) 1<<7),
    INTERRUPT_CLEAR_AHB3M_TIMEOUT                     =   ((uint16_t) 1<<6),
    INTERRUPT_CLEAR_ERASE_ARRAY_DONE                  =   ((uint16_t) 1<<5),
    INTERRUPT_CLEAR_PROG_ARRAY_DONE                   =   ((uint16_t) 1<<4),
    INTERRUPT_CLEAR_READ_ARRAY_DONE                   =   ((uint16_t) 1<<3),
    INTERRUPT_CLEAR_NNVAD_DONE                        =   ((uint16_t) 1<<2),
    INTERRUPT_CLEAR_ALL_ROUND_DONE                    =   ((uint16_t) 1<<1),
    INTERRUPT_CLEAR_CUR_ROUND_DONE                    =   ((uint16_t) 1<<0)
}NPU_IT_CLEAR;

/**  
  * @brief NPU Interrupt Status Enumeration 
  */
typedef enum
{
    INTERRUPT_STATUS_DMA_ERROR                         =   ((uint16_t) 1<<15),
    INTERRUPT_STATUS_DMA_DONE                          =   ((uint16_t) 1<<14),
    INTERRUPT_STATUS_SPARSE_MATRIX                     =   ((uint16_t) 1<<13),
    INTERRUPT_STATUS_DACFF_UPDATE_READY                =   ((uint16_t) 1<<12),
    INTERRUPT_STATUS_SINGLE_EXT2DACFF_DONE             =   ((uint16_t) 1<<11),
    INTERRUPT_STATUS_EXT2DACFF_START                   =   ((uint16_t) 1<<10),
    INTERRUPT_STATUS_SINGLE_POST2DACFF_DONE            =   ((uint16_t) 1<<9),
    INTERRUPT_STATUS_POST2DACFF_START                  =   ((uint16_t) 1<<8),
    INTERRUPT_STATUS_AHB_IBUS_RSP_ERR                  =   ((uint16_t) 1<<7),
    INTERRUPT_STATUS_AHB3M_TIMEOUT                     =   ((uint16_t) 1<<6),
    INTERRUPT_STATUS_ERASE_ARRAY_DONE                  =   ((uint16_t) 1<<5),
    INTERRUPT_STATUS_PROG_ARRAY_DONE                   =   ((uint16_t) 1<<4),
    INTERRUPT_STATUS_READ_ARRAY_DONE                   =   ((uint16_t) 1<<3),
    INTERRUPT_STATUS_NNVAD_DONE                        =   ((uint16_t) 1<<2),
    INTERRUPT_STATUS_ALL_ROUND_DONE                    =   ((uint16_t) 1<<1),
    INTERRUPT_STATUS_CUR_ROUND_DONE                    =   ((uint16_t) 1<<0)
}NPU_IT_STATUE;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup NPU_Functions_Prototypes NPU Functions Prototypes
* @{
*/

/**
* @brief  NPU write by 32bit method.
* @param  addr:the register address need to write
* @param  value:the value need to write
*/ 
extern void WRITE32_NPU(uint32_t addr, uint32_t value);

/**
* @brief  NPU read by 32bit method.
* @param  addr:the register address need to read
* @param  return the value that need read
*/ 
extern uint32_t READ32_NPU(uint32_t addr);

/**
* @brief  NPU write by 16bit method.
* @param  addr:the register address need to write
* @param  value:the value need to write
*/ 
extern void WRITE16_NPU(uint16_t addr, uint16_t value);

/**
* @brief  NPU read by 16bit method.
* @param  addr:the register address need to read
* @param  return the value that need read
*/
extern uint16_t READ16_NPU(uint16_t addr);

/**
* @brief  NPU write by 8bit method.
* @param  addr:the register address need to write
* @param  value:the value need to write
*/ 
extern void WRITE8_NPU(uint8_t addr, uint8_t value);

/**
* @brief  NPU read by 8bit method.
* @param  addr:the register address need to read
* @param  return the value that need read
*/
extern uint8_t READ8_NPU(uint8_t addr);

/**
* @brief  NPU Clock divider.
* @param  num: the divider value
* @retval None
*/
extern void npu_clk_div(uint8_t num);

/**
* @brief  NPU software reset.
* @param  None
* @retval None
*/
extern void npu_soft_reset(void);

/**
* @brief  NPU Init.
* @param  None
*/ 
extern void NPU_Init(void);

/**
* @brief  sram read.
* @param  round_addr: the address need to read of sram.
* @note
* @param  *data_read the buffer used to put the read data
* @param  number the number to read
* @retval None
*/
extern void round_cfg_srame_read(uint32_t round_addr, uint32_t *data_read, uint32_t number);

/**
* @brief  sram write.
* @param  round_addr: the address need to write of sram.
* @note
* @param  *data_write_buf the buffer used to put the write data
* @param  number the number to write
* @retval None
*/
extern void round_cfg_srame_write(uint32_t round_addr, uint32_t *data_write_buf, uint32_t number);

/**
* @brief  NPU dma start.
* @param  None
*/ 
extern void wtn_npu_dma_start(void);

/**
* @brief  NPU dma done.
* @param  None
*/
extern void wtn_npu_dma_done(void);

/**
* @brief  regile data mem to soc memory.
* @param  regfile_addr: the regfile address need to write,8k Byte
* @note
* @param  soc_mem_addr 0x3000_0000~0x3004_ffff
* @param  data_size  the number to memory
* @retval None
*/
extern void wtn_npu_dma_npu2soc(uint16_t regfile_addr, uint32_t soc_mem_addr, uint32_t data_size);

/**
* @brief  soc memory to regile data mem.
* @param  regfile_addr: the regfile address need to write,8k Byte
* @note
* @param  soc_mem_addr 0x3000_0000~0x3004_ffff
* @param  data_size  the number to memory
* @retval None
*/
extern void wtn_npu_dma_soc2npu(uint32_t soc_mem_addr, uint16_t regfile_addr, uint32_t data_size);

/**
* @brief  NPU interrupt init.
* @param  irq_mask is NPU_IT_MASK 
*/
extern void NPU_Interrupt_Init(NPU_IT_MASK irq_mask);

/**
* @brief  ADC_Debug_Ctrl
* @param  None
* @note
* @retval None
*/
extern void ADC_Debug_Ctrl(void);

/**
* @brief  regfile write byte.
* @param  regfile_start_addr: the address need to write of regfile.
* @note
* @param  *data_write_buf the buffer used to put the write data
* @param  regfile_write_length the number to write
* @retval None
*/
extern void regfile_write_byte(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint8_t *data_write_buf);

/**
* @brief  regfile read byte.
* @param  regfile_start_addr: the address need to read of regfile.
* @note
* @param  *data_read_buf the buffer used to put the read data
* @param  regfile_read_length the number to write
* @retval None
*/
extern void regfile_read_byte(uint32_t regfile_start_addr, uint32_t regfile_read_length, uint8_t *data_read_buf) ;

/**
* @brief  regfile write halfword.
* @param  regfile_start_addr: the address need to write of regfile.regfile_start_addr must even like 0,2,4,6,8......
* @note
* @param  *data_write_buf the buffer used to put the write data
* @param  regfile_write_length the number to write, the number of 16bit
* @retval None
*/
extern void regfile_write_halfword(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint16_t *data_write_buf);

/**
* @brief  regfile read halfword.
* @param  regfile_start_addr: the address need to read of regfile..regfile_start_addr must even like 0,2,4,6,8......
* @note
* @param  *data_read_buf the buffer used to put the read data
* @param  regfile_read_length the number to read, the number of 16bit
* @retval None
*/
extern void regfile_read_halfword(uint32_t regfile_start_addr, uint32_t regfile_read_length, uint16_t *data_read_buf);

/**
* @brief  regfile write word.
* @param  regfile_start_addr: the address need to write of regfile.regfile_start_addr must even like 0,4,8......
* @note
* @param  *data_write_buf the buffer used to put the write data
* @param  regfile_write_length the number to write, the number of 32bit
* @retval None
*/
extern void regfile_write_word(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint32_t *data_write_buf);

/**
* @brief  regfile read word.
* @param  regfile_start_addr: the address need to read of regfile..regfile_start_addr must even like 0,4,8......
* @note
* @param  *data_read_buf the buffer used to put the read data
* @param  regfile_read_length the number to read, the number of 32bit
* @retval None
*/
extern void regfile_read_word(uint32_t regfile_start_addr, uint32_t regfile_read_length, uint32_t *data_read_buf);

/**
* @brief  regfile write byte .
* @param  regfile_start_addr: the address need to write of regfile.regfile_start_addr >=7168
* @note
* @param  *data_write_buf the buffer used to put the write data
* @param  regfile_write_length the number to write, the number of 8bit
* @param  fifo_depth the number to write, the number of 8bit
* @retval None
*/
extern void regfile_write_byte_high_fifo(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint8_t *data_write_buf, uint16_t fifo_depth);

/**
* @brief  regfile write halfword .
* @param  regfile_start_addr: the address need to write of regfile.regfile_start_addr >=7168
* @note
* @param  *data_write_buf the buffer used to put the write data
* @param  regfile_write_length the number to write, the number of 8bit
* @param  fifo_depth the number to write, the number of 8bit
* @retval None
*/
extern void regfile_write_halfword_high_fifo(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint16_t *data_write_buf, uint16_t fifo_depth);

/**
* @brief  regfile write word .
* @param  regfile_start_addr: the address need to write of regfile.regfile_start_addr >=7168
* @note
* @param  *data_write_buf the buffer used to put the write data
* @param  regfile_write_length the number to write, the number of 8bit
* @param  fifo_depth the number to write, the number of 8bit
* @retval None
*/
extern void regfile_write_word_high_fifo(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint32_t *data_write_buf, uint16_t fifo_depth);

/**
* @brief  regfile read fast mode.
* @param  regfile_start_addr: the address need to write of regfile.regfile_start_addr >=7168
* @note
* @param  *data_write_buf the buffer used to put the write data
* @param  regfile_write_length the number to write, the number of 8bit
* @param  fifo_depth the number to write, the number of 8bit
* @retval None
*/
extern void regfile_read_byte_fast(uint32_t regfile_start_addr, uint32_t regfile_read_length, uint8_t *data_read_buf);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  
