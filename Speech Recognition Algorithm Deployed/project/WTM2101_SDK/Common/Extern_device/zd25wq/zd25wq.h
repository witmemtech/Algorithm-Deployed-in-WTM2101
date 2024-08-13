/** Define to Prevent Recursive Inclusion */
#ifndef ZD25WQ_H
#define ZD25WQ_H

#ifdef __cplusplus
extern "C" {
#endif 

/** Includes */
#include "qspi.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "dma.h"
#include "heap.h"
#include "wtm2101_mmap.h"

/** @addtogroup WITIN_ZD25WQ_Driver
* @{
*/

/** @defgroup ZD25WQ COMMAND MARCO DEFINED
* @{
*/
#define ZD25WQ_RESET_ENABLE                                                                                                0X66
#define ZD25WQ_RESET                                                                                                       0X99
#define ZD25WQ_READ_STATUS_REGISTER                                                                                        0X05
#define ZD25WQ_READ_STATUS_REGISTER_S82S15                                                                                 0X35
#define ZD25WQ_READ_CONFIGRATION_REGISTER										   0X15												
#define ZD25WQ_WRITE_STATUS_REGISTER										  	   0X01
#define ZD25WQ_WRITE_CONFIGRATION_REGISTER										   0X31

#define ZD25WQ_READ_DATA                                                                                                   0X03
#define ZD25WQ_FAST_READ                                                                                                   0X0B
#define ZD25WQ_FAST_READ_QUAD_OUTPUT											   0X6B	
#define ZD25WQ_FAST_READ_QUAD_IO											   0XEB
#define ZD25WQ_FAST_READ_DUAL_OUTPUT                                                                                       0X3B
#define ZD25WQ_FAST_READ_DUAL_IO											   0XBB			

#define ZD25WQ_MANUFACTURER_DEVICE_ID								                           0X9F
#define ZD25WQ_MANUFACTURER_ID                                                                                             0X90
#define ZD25WQ_DUAL_MANUFACTURER_ID                                                                                        0X92
#define ZD25WQ_QUAD_MANUFACTURER_ID                                                                                        0X94
#define ZD25WQ_DEEP_SLEEP                                                                                                  0XB9
#define ZD25WQ_RELEASE_DEEP_POWER_DOWN_OR_READ_ELECTRONIC_ID                                                               0XAB
#define ZD25WQ_SET_BURST_LENGTH                                                                                            0X77
#define ZD25WQ_READ_SFDP_PARAMETER                                                                                         0X5A
#define ZD25WQ_RELEASE_READ_ENHANCED                                                                                       0XFF
#define ZD25WQ_READ_UNIQUE_ID                                                                                              0X4B

#define ZD25WQ_WRITE_ENABLE                                                                                                0X06
#define ZD25WQ_WRITE_DISABLE                                                                                               0X04
#define ZD25WQ_SR_WRITE_ENABLE                                                                                             0X50

#define ZD25WQ_PAGE_ERASE                                                                                                  0X81
#define ZD25WQ_SECTOR_ERASE                                                                                                0X20
#define ZD25WQ_BLOCK_ERASE_32K											           0X52
#define ZD25WQ_BLOCK_ERASE_64K											           0XD8
#define ZD25WQ_CHIP_ERASE                                                                                                  0XC7
#define ZD25WQ_PAGE_PROGRAM                                                                                                0X02
#define ZD25WQ_DUAL_PAGE_PROGRAM											   0XA2
#define ZD25WQ_QUAD_PAGE_PROGRAM											   0X32
#define ZD25WQ_SUSPEND                                                                                                     0XB0	
#define ZD25WQ_RESUME                                                                                                      0X30
/**
* @}
*/

/** @defgroup ZD25WQ FLAG MARCO DEFINED
* @{
*/
#define ZD25WQ_QSPI_1LINE                                                          0
#define ZD25WQ_QSPI_4LINES                                                         !ZD25WQ_QSPI_1LINE

#define ZD25WQ_CHIP_PROTECT_VALUE                                                  0X06
#define ZD25WQ_SIZE                                                                2097152        
#define ZD25WQ_SECTOR_SIZE                                                  	   4096
#define ZD25WQ_PAGE_SIZE                                                    	   256 
#define ZD25WQ_MANUFACTURER                                                        0XBA
#define ZD25WQ_DEVICE_TYPE                                                         0x60 
#define ZD25WQ_DEVICE_ID                                                           0X15
#define ZD25WQ_PAGE_WRITE_MAX_TIME_S                                               1  
#define ZD25WQ_SECTOR_BLOCK_ERASE_MAX_TIME_S                                       1
#define ZD25WQ_CHIP_ERASE_MAX_TIME_S                                               1                        
/**
* @}
*/

#define ZD25WQ_SEND_DMA_CHANNEL    DMA_CHANNEL_6
#define ZD25WQ_RECEIVE_DMA_CHANNEL DMA_CHANNEL_7
  
#define ZD25WQ_MALLOC(size)        pvPortMalloc(size)
#define ZD25WQ_free(pointer)       vPortFree(pointer)  

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint8_t                 qspi_1line_or_4lines;
    uint32_t                page_size, sector_size,flash_size;
    QSPI_CtlInitTypeDef     *qspi_ctl;
    QSPI_TypeDef            *qspi_hd;
    uint32_t                clock_divider;
    uint8_t                 send_dma_flag,send_dma_channel;
    DMA_InitTypeDef         *send_dma_inittypedef;
    uint8_t                 receive_dma_flag,receive_dma_channel;
    DMA_InitTypeDef         *receive_dma_inittypedef;
}ZD25WQ;
#pragma pack(pop) 

/**
* @brief  Init the ZD25WQ flash structure
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_qspi_init(ZD25WQ *ZD25WQ_hd);

/**
* @brief  Open the ZD25WQ flash
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @param  qspi_hd: the hardware qspi address 
* @param  line_type: the hardware qspi work mode 
* @param  send_dma_enable: the hardware qspi send dma enable flag 
* @param  send_dma_channel: the hardware qspi send dma channel 
* @param  receive_dma_enable: the hardware qspi receive dma enable flag
* @param  receive_dma_channel: the hardware qspi receive dma channel 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_open(ZD25WQ *ZD25WQ_hd, QSPI_TypeDef *qspi_hd,uint8_t line_type,uint8_t send_dma_enable,uint8_t send_dma_channel,uint8_t receive_dma_enable,uint8_t receive_dma_channel);

/**
* @brief  Close the ZD25WQ flash and instance
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_close(ZD25WQ *ZD25WQ_hd);

/**
* @brief  Erase the ZD25WQ flash sector or block
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @param  instruction: the erase command 
* @param  address: the erase address 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_sector_or_block_erase(ZD25WQ *ZD25WQ_hd,uint8_t instruction,uint32_t address);

/**
* @brief  Erase the ZD25WQ flash chip
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_chip_erase(ZD25WQ *ZD25WQ_hd);

/**
* @brief  Protect the ZD25WQ flash chip
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @param  newstatus: enable or disable the write protect 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_chip_write_protect(ZD25WQ *ZD25WQ_hd,FunctionalState newstatus);

/**
* @brief  Page program
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @param  address: the program address 
* @param  data: the program data buffer
* @param  len: the program data size 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_page_write(ZD25WQ *ZD25WQ_hd, uint32_t address, uint8_t *data,uint32_t len);

/**
* @brief  sector program
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @param  sector_index: the sector address index
* @param  data: the program data buffer
* @param  sector_counts: the program sector size 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_sector_write(ZD25WQ *ZD25WQ_hd,uint32_t sector_index, uint8_t *data, uint32_t sector_counts);

/**
* @brief  sector read
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @param  sector_index: the sector address index
* @param  data: the read data buffer
* @param  sector_counts: the read sector size 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_sector_read(ZD25WQ *ZD25WQ_hd,uint32_t sector_index, uint8_t *data, uint32_t sector_counts);

/**
* @brief  read data from the ZD25WQ flash
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @param  address: the read address
* @param  data: the read data buffer
* @param  len: the read data size 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_read(ZD25WQ *ZD25WQ_hd,uint32_t address, uint8_t *data,uint32_t len);

/**
* @brief  write data to the ZD25WQ flash
* @param  ZD25WQ_hd: the ZD25WQ flash structure instance 
* @param  address: the write address
* @param  buf: the write data buffer
* @param  length: the write data size 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern  int ZD25WQ_write(ZD25WQ *ZD25WQ_hd,uint32_t address, uint8_t *buf, uint32_t length);

/**
* @}
*/
#ifdef __cplusplus
}
#endif

#endif    
