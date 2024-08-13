/**
  ******************************************************************************
  * @file    spi.h
  * @brief   Header for spi.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __SPI_H__
#define __SPI_H__

#ifdef  __cplusplus
extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "rcc.h"
#include "WTM2101_SPI_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
* @{
*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
* @{
*/

/** @defgroup SpiDatasize_TypeDef
* @{
*/
#define    SPI_DATASIZE_4B  (0x03)
#define    SPI_DATASIZE_5B  (0x04)
#define    SPI_DATASIZE_6B  (0x05)
#define    SPI_DATASIZE_7B  (0x06)
#define    SPI_DATASIZE_8B  (0x07)
#define    SPI_DATASIZE_9B  (0x08)
#define    SPI_DATASIZE_10B (0x09)
#define    SPI_DATASIZE_11B (0x0a)
#define    SPI_DATASIZE_12B (0x0b)
#define    SPI_DATASIZE_13B (0x0c)
#define    SPI_DATASIZE_14B (0x0d)
#define    SPI_DATASIZE_15B (0x0e)
#define    SPI_DATASIZE_16B (0x0f)
#define    SPI_DATASIZE_17B (0x10)
#define    SPI_DATASIZE_18B (0x11)
#define    SPI_DATASIZE_19B (0x12)
#define    SPI_DATASIZE_20B (0x13)
#define    SPI_DATASIZE_21B (0x14)
#define    SPI_DATASIZE_22B (0x15)
#define    SPI_DATASIZE_23B (0x16)
#define    SPI_DATASIZE_24B (0x17)
#define    SPI_DATASIZE_25B (0x18)
#define    SPI_DATASIZE_26B (0x19)
#define    SPI_DATASIZE_27B (0x1a)
#define    SPI_DATASIZE_28B (0x1b)
#define    SPI_DATASIZE_29B (0x1c)
#define    SPI_DATASIZE_30B (0x1d)
#define    SPI_DATASIZE_31B (0x1e)
#define    SPI_DATASIZE_32B (0x1f)
#define    IS_SPI_DATASIZE(SIZE)          (((SIZE) == SPI_DATASIZE_4B) || \
                                          ((SIZE) == SPI_DATASIZE_5B)  || \
                                          ((SIZE) == SPI_DATASIZE_6B)  || \
                                          ((SIZE) == SPI_DATASIZE_7B)  || \
                                          ((SIZE) == SPI_DATASIZE_8B)  || \
                                          ((SIZE) == SPI_DATASIZE_9B)  || \
                                          ((SIZE) == SPI_DATASIZE_10B) || \
                                          ((SIZE) == SPI_DATASIZE_11B) || \
                                          ((SIZE) == SPI_DATASIZE_12B) || \
                                          ((SIZE) == SPI_DATASIZE_13B) || \
                                          ((SIZE) == SPI_DATASIZE_14B) || \
                                          ((SIZE) == SPI_DATASIZE_15B) || \
                                          ((SIZE) == SPI_DATASIZE_16B) || \
                                          ((SIZE) == SPI_DATASIZE_17B) || \
                                          ((SIZE) == SPI_DATASIZE_19B) || \
                                          ((SIZE) == SPI_DATASIZE_20B) || \
                                          ((SIZE) == SPI_DATASIZE_21B) || \
                                          ((SIZE) == SPI_DATASIZE_22B) || \
                                          ((SIZE) == SPI_DATASIZE_23B) || \
                                          ((SIZE) == SPI_DATASIZE_24B) || \
                                          ((SIZE) == SPI_DATASIZE_25B) || \
                                          ((SIZE) == SPI_DATASIZE_26B) || \
                                          ((SIZE) == SPI_DATASIZE_27B) || \
                                          ((SIZE) == SPI_DATASIZE_28B) || \
                                          ((SIZE) == SPI_DATASIZE_29B) || \
                                          ((SIZE) == SPI_DATASIZE_30B) || \
                                          ((SIZE) == SPI_DATASIZE_31B) || \
                                          ((SIZE) == SPI_DATASIZE_32B))
/**
  * @}
  */


/** @defgroup SpiCpol_TypeDef
* @{
*/
#define    SPI_CPOL_0  (0x00)                         /*!< Cpol 0 */
#define    SPI_CPOL_1  (0x01)                         /*!< Cpol 1 */
#define    IS_SPI_CPOL(CPOL)  (((CPOL) == SPI_CPOL_0) || \
                              ((CPOL) == SPI_CPOL_1))
/**
  * @}
  */


/** @defgroup SpiCpha_TypeDef
* @{
*/
#define    SPI_CPHA_0   (0x00)                          /*!< Cpha 0 */
#define    SPI_CPHA_1   (0x01)                          /*!< Cpha 1 */
#define    IS_SPI_CPHA(CPHA)  (((CPHA) == SPI_CPOL_0) || \
                              ((CPHA) == SPI_CPOL_1))
/**
  * @}
  */


/** @defgroup SpiNss_TypeDef
* @{
*/
#define    SPI_HARDWARE_NSS0 (0x01)                   /*!<hardware select0*/
#define    SPI_HARDWARE_NSS1 (0x02)                   /*!<hardware select1*/
#define    SPI_HARDWARE_NSS2 (0x03)                   /*!<hardware select2*/
#define    SPI_SOFTWARE_NSS  (0x04)                   /*!<software*/
#define    IS_SPI_NSS(NSS)  (((NSS) == SPI_HARDWARE_NSS0) || \
                            ((NSS) == SPI_HARDWARE_NSS1) || \
                            ((NSS) == SPI_HARDWARE_NSS2) || \
                            ((NSS) == SPI_SOFTWARE_NSS))
/**
  * @}
  */


/** @defgroup SpiMode_TypeDef
* @{
*/
#define    SPI_SEND_AND_RECEIVE_MODE (0x00)           /*!<send_and_receive*/
#define    SPI_ONLY_SEND_MODE        (0x01)           /*!<only send*/
#define    SPI_ONLY_RECEIVE_MODE     (0x02)           /*!<only receive*/
#define    IS_SPI_MODE(MODE)        (((MODE) == SPI_SEND_AND_RECEIVE_MODE) || \
                                    ((MODE) == SPI_ONLY_SEND_MODE) || \
                                    ((MODE) == SPI_ONLY_RECEIVE_MODE))
/**
  * @}
  */


/** @defgroup SpiIntStatus_TypeDef
* @{
*/
#define    SPI_TRANSMIT_FIFO_EMPTY_INT     (0x01)      /*!Transmit FIFO Empty Interrupt*/
#define    SPI_TRANSMIT_FIFO_OVERFLOW_INT  (0x02)      /*!Transmit FIFO Overflow Interrupt*/
#define    SPI_RECEIVE_FIFO_UNDERFLOW_INT  (0x04)      /*!Receive FIFO Underflow Interrupt*/
#define    SPI_RECEIVE_FIFO_OVERFLOW_INT   (0x08)      /*!Receive FIFO Overflow Interrupt*/
#define    SPI_RECEIVE_FIFO_FULL_INT       (0x10)      /*!Receive FIFO FULL Interrupt*/
#define    SPI_MULTI_MASTER_CONTENTION_INT (0x20)      /*!Multi-Master Contention Interrupt */
#define    IS_SPI_INTERRUPT_TYPE(TYPE) (((TYPE) & SPI_TRANSMIT_FIFO_EMPTY_INT) || \
                                       ((TYPE) & SPI_TRANSMIT_FIFO_OVERFLOW_INT) || \
                                       ((TYPE) & SPI_RECEIVE_FIFO_UNDERFLOW_INT) || \
                                       ((TYPE) & SPI_RECEIVE_FIFO_OVERFLOW_INT) || \
                                       ((TYPE) & SPI_RECEIVE_FIFO_FULL_INT) || \
                                       ((TYPE) & SPI_MULTI_MASTER_CONTENTION_INT))
/**
  * @}
  */


/** @defgroup SpiStatus_TypeDef
* @{
*/
#define    SPI_BUSY                        (0x01)     /*!Busy Flag*/
#define    SPI_TRANSMIT_FIFO_NOT_FULL      (0x02)     /*!Transmit FIFO Not Full Flag*/
#define    SPI_TRANSMIT_FIFO_EMPTY         (0x04)     /*!Transmit FIFO Empty Flag*/
#define    SPI_RECEIVE_FIFO_NOT_EMPTY      (0x08)     /*!Receive FIFO Not Empty Flag*/
#define    SPI_RECEIVE_FIFO_FULL           (0x10)     /*!Receive FIFO Full Flag*/
#define    SPI_TRANSMISSION_ERROR          (0x20)     /*!Transmission Error*/
#define    SPI_DATA_COLLISION_ERROR        (0x40)     /*!Data Collision Error*/
#define    IS_SPI_STATUS_FLAG(FLAG) (((FLAG) & SPI_BUSY) || \
                                    ((FLAG) & SPI_TRANSMIT_FIFO_NOT_FULL) || \
                                    ((FLAG) & SPI_TRANSMIT_FIFO_EMPTY) || \
                                    ((FLAG) & SPI_RECEIVE_FIFO_NOT_EMPTY) || \
                                    ((FLAG) & SPI_RECEIVE_FIFO_FULL) || \
                                    ((FLAG) & SPI_TRANSMISSION_ERROR) || \
                                    ((FLAG) & SPI_DATA_COLLISION_ERROR))
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup SPI_Exported_Types SPI Exported Types
  * @{
  */

/**
* @brief  SPI Init Structure Definition
*/
typedef struct
{
    uint32_t datasize;            /*!< Specifies spi datasize
                                      This parameter can be a value of SpiDatasize_TypeDef */

    uint32_t cpol;                /*!< Specifies spi cpol
                                      This parameter can be a value of SpiCpol_TypeDef */

    uint32_t cpha;                /*!< Specifies spi cpha
                                      This parameter can be a value of SpiCpha_TypeDef */

    uint32_t nss;                 /*!< Specifies spi nss signal
                                      This parameter can be a value of SpiNss_TypeDef
                                      This parameter is used by SPI MASTER */

    uint32_t clk_div;            /*!< Specifies spi datarate
                                     The spi_clk = APB1_clk / clk_div.
                                     The master :spi_clk <= APB1_clk / 2
                                     The slave(receive only):spi_clk >= 8 * clk_in
                                     The slave:spi_clk >= 10 * clk_in
                                     The note is that the clk_div must be the even and cant be the 0
                                     This parameter is used by SPI MASTER */
}SPI_InitTypeDef;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup SPI_Functions_Prototypes SPI Functions Prototypes
* @{
*/

/**
* @brief  Initializes the SPI peripheral according to
*         the specified parameters in the SPI_InitStruct.
* @param  SPIx: can be the SPIM or SPIS
* @param  SPI_InitStruct: pointer to a SPI_InitTypeDef
*         structure that contains the configuration information for
*         the specified SPI peripheral.
* @retval None
*/
extern void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);

/**
* @brief  Uninitializes the SPI peripheral according to
*         the specified parameters in the SPI_InitStruct.
* @param  SPIx: can be the SPIM or SPIS
* @retval None
*/
extern void SPI_Uninit(SPI_TypeDef* SPIx);

/**
* @brief  Enabled or disabled the spi
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Set one or more nss signal
* @param  SPIx: can be the SPIM or SPIS
* @param  nss: the one value of SpiNss_TypeDef value
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Nss_Cmd(SPI_TypeDef* SPIx, uint8_t nss, FunctionalState NewState);

/**
* @brief  Set spi transmit or receive mode
* @param  SPIx: can be the SPIM or SPIS
* @param  mode: the one value of SpiMode_TypeDef
* @retval None
*/
extern void SPI_Set_Mode(SPI_TypeDef* SPIx, uint8_t mode);

/**
* @brief  Set spi loop back mode
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Set_Loopback(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Set spi transmit fifo threshold value
* @param  SPIx: can be the SPIM or SPIS
* @param  value: the threshold value
* @retval None
*/
extern void SPI_Set_Tx_Fifo_Threshold(SPI_TypeDef* SPIx, int value);

/**
* @brief  Set spi receive fifo threshold value
* @param  SPIx: can be the SPIM or SPIS
* @param  value: the threshold value
* @retval None
*/
extern void SPI_Set_Rx_Fifo_Threshold(SPI_TypeDef* SPIx, int value);

/**
* @brief  Get spi transmit fifo data number
* @param  SPIx: can be the SPIM or SPIS
* @retval the number of valid data entry
*/
extern int SPI_Get_Tx_Fifo_level(SPI_TypeDef* SPIx);

/**
* @brief  Get spi receive fifo data number
* @param  SPIx: can be the SPIM or SPIS
* @retval the number of valid data entry
*/
extern int SPI_Get_Rx_Fifo_level(SPI_TypeDef* SPIx);

/**
* @brief  Get spi status
* @param  SPIx: can be the SPIM or SPIS
* @retval The value can be one or more of the SpiStatus_TypeDef enum
*/
extern int SPI_Get_Status_Cmd(SPI_TypeDef* SPIx);

/**
* @brief  Enabled or disabled the spi transmit fifo empty interrupt
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Set_Tx_Fifo_Empty_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Enabled or disabled the spi transmit fifo overflow interrupt
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Set_Tx_Fifo_Overflow_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Enabled or disabled the spi receive fifo underflow interrupt
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Set_Rx_Fifo_Underflow_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Enabled or disabled the spi receive fifo overflow interrupt
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Set_Rx_Fifo_Overflow_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Enabled or disabled the spi receive fifo full interrupt
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Set_Rx_Fifo_Full_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Enabled or disabled the spi multli_master content interrupt
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Set_Mutli_Master_Contention_Interrupt(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Get spi interrupt status
* @param  SPIx: can be the SPIM or SPIS
* @retval The value can be one or more of the SpiIntStatus_TypeDef enum
*/
extern int SPI_Get_Interrupt_Status(SPI_TypeDef* SPIx);

/**
* @brief  Clear spi transmit fifo overflow interrupt
* @param  SPIx: can be the SPIM or SPIS
* @retval None
*/
extern void SPI_Clear_Tx_Fifo_Overflow_Interrupt(SPI_TypeDef* SPIx);

/**
* @brief  Clear spi receive fifo overflow interrupt
* @param  SPIx: can be the SPIM or SPIS
* @retval None
*/
extern void SPI_Clear_Rx_Fifo_Overflow_Interrupt(SPI_TypeDef* SPIx);

/**
* @brief  Clear spi receive fifo underflow interrupt
* @param  SPIx: can be the SPIM or SPIS
* @retval None
*/
extern void SPI_Clear_Rx_Fifo_Underflow_Interrupt(SPI_TypeDef* SPIx);

/**
* @brief  Enabled or disabled spi dma receive
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Dma_Receive_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Enabled or disabled spi dma send
* @param  SPIx: can be the SPIM or SPIS
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void SPI_Dma_Send_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);

/**
* @brief  Set spi dma transmit data level
* @param  SPIx: can be the SPIM or SPIS
* @param  value: the data level
* @retval None
*/
extern void SPI_Set_Dma_Transmit_Data_level(SPI_TypeDef* SPIx, int level);

/**
* @brief  Set spi dma receive data level
* @param  SPIx: can be the SPIM or SPIS
* @param  value: the data level
* @retval None
*/
extern void SPI_Set_Dma_Receive_Data_level(SPI_TypeDef* SPIx, int level);

/**
* @brief  The spi send data
* @param  SPIx: can be the SPIM or SPIS
* @param  size: the buffer pointer point to uint8_t * and size is 1. the buffer pointer point to uint16_t * and size is 2.the buffer pointer point to uint32_t * and size is 4.
* @param  sendbuffer: the buffer to be send
* @param  sendbuffer_length: the length of sendbuffer
* @retval data size
*/
int SPI_Send(SPI_TypeDef* SPIx, uint8_t size, void *sendbuffer, uint32_t sendbuffer_length);

/**
* @brief  The spi send and receice data
* @param  SPIx: can be the SPIM or SPIS
* @param  size: the buffer pointer point to uint8_t * and size is 1. the buffer pointer point to uint16_t * and size is 2.the buffer pointer point to uint32_t * and size is 4.
* @param  sendbuffer: the buffer to be send
* @param  sendbuffer_length: the length of sendbuffer
* @param  receivebuffer: the buffer to be receive
* @param  receivebuffer_length: the length of receivebuffer
* @note   sendbuffer is NULL,SPI only receive the data,or receivebuffer is NULL,SPI only send the data,or SPI send and receive data at the same time
* @retval data size
*/
extern int SPI_Send_Receive(SPI_TypeDef* SPIx, uint8_t size, void *sendbuffer, uint32_t sendbuffer_length, void *receivebuffer, uint32_t receivebuffer_length);
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
