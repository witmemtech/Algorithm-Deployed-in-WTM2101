/**
  ******************************************************************************  
  * @file    dma.h
  * @brief   Header for dma.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __DMA_H__
#define __DMA_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "stddef.h"
#include "WTM2101_DMAC_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/* Exported constants --------------------------------------------------------*/
 
/** @defgroup DMA_Exported_Constants
  * @{
  */

/** @defgroup DmaDirection_TypeDef
* @{
*/
#define    MEM_TO_MEM_FLOW_CTOL_DMA              (0x00)
#define    MEM_TO_PER_FLOW_CTOL_DMA              (0x01)
#define    PER_TO_MEM_FLOW_CTOL_DMA              (0x02)
#define    PER_TO_PER_FLOW_CTOL_DMA              (0x03)
#define    PER_TO_MEM_FLOW_CTOL_PER              (0x04)
#define    PER_TO_PER_FLOW_CTOL_SRC_PER          (0x05)
#define    MEM_TO_PER_FLOW_CTOL_PER              (0x06)
#define    PER_TO_PER_FLOW_CTOL_DST_PER          (0x07)
#define    IS_DMA_DIRECTION(direction)          (((direction) == MEM_TO_MEM_FLOW_CTOL_DMA)     || \
                                                 ((direction) == MEM_TO_PER_FLOW_CTOL_DMA)     || \
                                                 ((direction) == PER_TO_MEM_FLOW_CTOL_DMA)     || \
                                                 ((direction) == PER_TO_PER_FLOW_CTOL_DMA)     || \
                                                 ((direction) == PER_TO_MEM_FLOW_CTOL_PER)     || \
                                                 ((direction) == PER_TO_PER_FLOW_CTOL_SRC_PER) || \
                                                 ((direction) == MEM_TO_PER_FLOW_CTOL_PER)     || \
                                                 ((direction) == PER_TO_PER_FLOW_CTOL_DST_PER))
/**
* @}
*/

/** @defgroup DmaMsize_TypeDef
* @{
*/
#define    DMA_MSIZE1                            (0x00)
#define    DMA_MSIZE4                            (0x01)
#define    DMA_MSIZE8                            (0x02)
#define    DMA_MSIZE16                           (0x03)
#define    DMA_MSIZE32                           (0x04)
#define    DMA_MSIZE64                           (0x05)
#define    DMA_MSIZE128                          (0x06)
#define    DMA_MSIZE256                          (0x07) 
#define    IS_DMA_MSIZE(MSIZE)                  (((MSIZE) == DMA_MSIZE1)   || \
                                                 ((MSIZE) == DMA_MSIZE4)   || \
                                                 ((MSIZE) == DMA_MSIZE8)   || \
                                                 ((MSIZE) == DMA_MSIZE16)  || \
                                                 ((MSIZE) == DMA_MSIZE32)  || \
                                                 ((MSIZE) == DMA_MSIZE64)  || \
                                                 ((MSIZE) == DMA_MSIZE128) || \
                                                 ((MSIZE) == DMA_MSIZE256))
/**
* @}
*/

/** @defgroup DmaWidth_TypeDef
* @{
*/
#define    DMA_WIDTH8                            (0x00)
#define    DMA_WIDTH16                           (0x01)
#define    DMA_WIDTH32                           (0x02)
#define    DMA_WIDTH64                           (0x03)
#define    DMA_WIDTH128                          (0x04)
#define    DMA_WIDTH256                          (0x05)
#define    IS_DMA_WIDTH(WIDTH)                  (((WIDTH) == DMA_WIDTH8)   || \
                                                 ((WIDTH) == DMA_WIDTH16)  || \
                                                 ((WIDTH) == DMA_WIDTH32)  || \
                                                 ((WIDTH) == DMA_WIDTH64)  || \
                                                 ((WIDTH) == DMA_WIDTH128) || \
                                                 ((WIDTH) == DMA_WIDTH256))
/**
* @}
*/

/** @defgroup DmaPer_TypeDef
* @{
*/
#define    DMA_UART0_TX_REQ_OR_AUDIO_CH1         (0x00)
#define    DMA_UART0_RX_REQ_OR_AUDIO_CH2         (0x01)
#define    DMA_UART1_TX_REQ_OR_AUDIO_CH2         (0x02)
#define    DMA_UART1_RX_REQ_OR_AUDIO_CH1         (0x03)
#define    DMA_I2C_TX_REQ                        (0x04)
#define    DMA_I2C_RX_REQ                        (0x05)
#define    DMA_SPIM_TX_REQ                       (0x06)
#define    DMA_SPIM_RX_REQ                       (0x07)
#define    DMA_QSPI_TX_REQ                       (0x08)
#define    DMA_QSPI_RX_REQ                       (0x09)
#define    DMA_I2S1_REQ                          (0x0A)
#define    DMA_AUDIO_CH0_REQ                     (0x0B)
#define    DMA_I2S0_REQ                          (0x0C)
#define    DAC_REQ                               (0x0D)
#define    DMA_SPIS_TX_REQ                       (0x0E)
#define    DMA_SPIS_RX_REQ                       (0x0F)
#define    OTHER_REQ                             (0xFF)
#define    IS_DMA_HARDWARE_PER(PER)             (((PER) == DMA_UART0_TX_REQ_OR_AUDIO_CH1)  || \
                                                 ((PER) == DMA_UART0_RX_REQ_OR_AUDIO_CH2)  || \
                                                 ((PER) == DMA_UART1_TX_REQ_OR_AUDIO_CH2)  || \
                                                 ((PER) == DMA_UART1_RX_REQ_OR_AUDIO_CH1)  || \
                                                 ((PER) == DMA_I2C_TX_REQ)                 || \
                                                 ((PER) == DMA_I2C_RX_REQ)                 || \
                                                 ((PER) == DMA_SPIM_TX_REQ)                || \
                                                 ((PER) == DMA_SPIM_RX_REQ)                || \
                                                 ((PER) == DMA_QSPI_TX_REQ)                || \
                                                 ((PER) == DMA_QSPI_RX_REQ)                || \
                                                 ((PER) == I2S_MASTER_REQ)                 || \
                                                 ((PER) == RESERVED_REQ)                   || \
                                                 ((PER) == I2S_SLAVE_REQ)                  || \
                                                 ((PER) == DAC_REQ)                        || \
                                                 ((PER) == DMA_SPIS_TX_REQ)                || \
                                                 ((PER) == DMA_SPIS_RX_REQ)                || \
                                                 ((PER) == OTHER_REQ))
/**
* @}
*/

/** @defgroup DmaHandshakeType_TypeDef
* @{
*/
#define    DMA_HW_HANDSHAKE                      (0x00)
#define    DMA_SW_HANDSHAKE                      (0x01)
#define    IS_DMA_HANDSHAKE_TYPE(TYPE)          (((TYPE) == DMA_HW_HANDSHAKE) || \
                                                 ((TYPE) == DMA_SW_HANDSHAKE))
/**
* @}
*/

/** @defgroup DmaHandshakePolarity_TypeDef
* @{
*/
#define    DMA_HANDSHAKE_POLARITY_LOW            (0x00)
#define    DMA_HANDSHAKE_POLARITY_HIGH           (0x01)
#define    IS_DMA_HANDSHAKE_POLARITY(POLARITY)  (((POLARITY) == DMA_HANDSHAKE_POLARITY_LOW) || \
                                                 ((POLARITY) == DMA_HANDSHAKE_POLARITY_HIGH))
/**
* @}
*/

/** @defgroup DmaChlPri_TypeDef
* @{
*/
#define    DMA_PRIORITY0                         (0x00)
#define    DMA_PRIORITY1                         (0x01)
#define    DMA_PRIORITY2                         (0x02)
#define    DMA_PRIORITY3                         (0x03)
#define    DMA_PRIORITY4                         (0x04)
#define    DMA_PRIORITY5                         (0x05)
#define    DMA_PRIORITY6                         (0x06)
#define    DMA_PRIORITY7                         (0x07)
#define    IS_DMA_PRIORITY(PRIORITY)            (((PRIORITY) == DMA_PRIORITY0) || \
                                                 ((PRIORITY) == DMA_PRIORITY1) || \
                                                 ((PRIORITY) == DMA_PRIORITY2) || \
                                                 ((PRIORITY) == DMA_PRIORITY3) || \
                                                 ((PRIORITY) == DMA_PRIORITY4) || \
                                                 ((PRIORITY) == DMA_PRIORITY5) || \
                                                 ((PRIORITY) == DMA_PRIORITY6) || \
                                                 ((PRIORITY) == DMA_PRIORITY7))
/**
* @}
*/

/** @defgroup DmaAddrType_TypeDef
* @{
*/
#define    DMA_ADDRESS_INCREASE                  (0x00)
#define    DMA_ADDRESS_DECREASE                  (0x01)
#define    DMA_ADDRESS_NO_CHANGE                 (0x02)
#define    IS_DMA_ADDR_TYPE(TYPE)               (((TYPE) == DMA_ADDRESS_INCREASE) || \
                                                 ((TYPE) == DMA_ADDRESS_DECREASE) || \
                                                 ((TYPE) == DMA_ADDRESS_NO_CHANGE))
/**
* @}
*/

/** @defgroup DmaChl_TypeDef
* @{
*/
#define    DMA_CHANNEL0                          (0x01)
#define    DMA_CHANNEL1                          (0x02)
#define    DMA_CHANNEL2                          (0x04)
#define    DMA_CHANNEL3                          (0x08)
#define    DMA_CHANNEL4                          (0x10)
#define    DMA_CHANNEL5                          (0x20)
#define    IS_DMA_CHANNEL(CHANNEL)              (((CHANNEL) == DMA_CHANNEL0) || \
                                                 ((CHANNEL) == DMA_CHANNEL1) || \
                                                 ((CHANNEL) == DMA_CHANNEL2) || \
                                                 ((CHANNEL) == DMA_CHANNEL3) || \
                                                 ((CHANNEL) == DMA_CHANNEL4) || \
                                                 ((CHANNEL) == DMA_CHANNEL5))
/**
* @}
*/

/** @defgroup DmaChlIntFlag_TypeDef
* @{
*/
#define    DMA_CHANNEL0_INT_FLAG                 (0x01)
#define    DMA_CHANNEL1_INT_FLAG                 (0x02)
#define    DMA_CHANNEL2_INT_FLAG                 (0x04)
#define    DMA_CHANNEL3_INT_FLAG                 (0x08)
#define    DMA_CHANNEL4_INT_FLAG                 (0X10)
#define    DMA_CHANNEL5_INT_FLAG                 (0X20)
#define    IS_DMA_CHANNEL_INT_FLAG(CHANNEL)     (((CHANNEL) == DMA_CHANNEL0_INT_FLAG) || \
                                                 ((CHANNEL) == DMA_CHANNEL1_INT_FLAG) || \
                                                 ((CHANNEL) == DMA_CHANNEL2_INT_FLAG) || \
                                                 ((CHANNEL) == DMA_CHANNEL3_INT_FLAG) || \
                                                 ((CHANNEL) == DMA_CHANNEL4_INT_FLAG) || \
                                                 ((CHANNEL) == DMA_CHANNEL5_INT_FLAG))
/**
* @}
*/

/** @defgroup DMAInit_Transfer_TypeDef
* @{
*/
#define    DMA_INITTYPEDEF_TRANSFER_TO_UINT32(DMA_INIT_TYPE)   (((DMA_INIT_TYPE)->llp_src_en << 28)  | ((DMA_INIT_TYPE)->llp_dst_en << 27) | ((DMA_INIT_TYPE)->direction << 20)   | \
                                                               ((DMA_INIT_TYPE)->src_msize << 14)    | ((DMA_INIT_TYPE)->dst_msize << 11)  | ((DMA_INIT_TYPE)->src_addr_type << 9)| \
                                                               ((DMA_INIT_TYPE)->dst_addr_type << 7) | ((DMA_INIT_TYPE)->src_width << 4)   | ((DMA_INIT_TYPE)->dst_width << 1)    | \
                                                               ((DMA_INIT_TYPE)->int_en))
/**
* @}
*/

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup DMA_Exported_Types DMA Exported Types 
  * @{
  */

/**
* @brief  Dma Init Structure Definition
*/
typedef struct
{
    uint8_t llp_src_en;                     /*!< Specifies block chaining of source address
                                            This parameter is 1,and enable it*/

    uint8_t llp_dst_en;                     /*!< Specifies block chaining of destination address
                                            This parameter is 1,and enable it*/

    uint8_t reload_src_en;                  /*!< Specifies source address reload
                                            This parameter is 1,and enable it*/

    uint8_t reload_dst_en;                  /*!< Specifies destination address reload
                                            This parameter is 1,and enable it*/

    uint8_t direction;                      /*!< Specifies direction of transfer
                                            This parameter can be a value of DmaDirction_TypeDef */

    uint8_t src_msize;                      /*!< Specifies burst-transaction-request size of source address
                                            This parameter can be a value of DmaMsize_TypeDef */

    uint8_t dst_msize;                      /*!< Specifies burst-transaction-request size of destination address
                                            This parameter can be a value of DmaMsize_TypeDef */

    uint8_t src_addr_type;                  /*!< Specifies address type of source address
                                            This parameter can be a value of DmaAddrType_TypeDef */

    uint8_t dst_addr_type;                  /*!< Specifies address type of destination address
                                            This parameter can be a value of DmaAddrType_TypeDef */

    uint8_t src_width;                      /*!< Specifies data width of source address
                                            This parameter can be a value of DmaWidth_TypeDef */

    uint8_t dst_width;                      /*!< Specifies data width of destination address
                                            This parameter can be a value of DmaWidth_TypeDef */

    uint8_t dst_per;                        /*!< Specifies hardware handshaking interface of destination address
                                            This parameter can be a value of DmaPer_TypeDef */

    uint8_t src_per;                        /*!< Specifies hardware handshaking interface of source address
                                            This parameter can be a value of DmaPer_TypeDef */

    uint8_t fifo_mode_en;                   /*!< Determines how much space or data needs to be available in the FiFo before a burst transaction request is serviced
                                            If it is 1 that indicate data available is greater than or equal to half the FIFO depth for destination transfers and space available is greater than half the FIFO depth*/
    
    uint32_t max_abrst;                     /*!< Maximum AMBA burst length that is used for DMA transfers on this channel.
                                            A value of 0 indicates that software is not limiting.This value is between 1 and 1023*/

    uint8_t src_handshaking_type;           /*!< Specifies handshaking interface of source address
                                            This parameter can be a value of DmaHandshakeType_TypeDef */

    uint8_t dst_handshaking_type;           /*!< Specifies handshaking interface of destination address
                                            This parameter can be a value of DmaHandshakeType_TypeDef */

    uint8_t chanel_priority;                /*!< Specifies channel priority
                                            This parameter can be a value of DmaChlPri_TypeDef */
                                
    uint8_t int_en;                         /*!< Specifies interrupt mask of DMA
                                            If it is 1 indicate the interrupt is enabled */
}DMA_InitTypeDef;

/**
* @brief  Dma Block Chaining Init Structure Definition
*/
typedef struct _DMA_LlpTypeDef
{
    uint32_t src;                            /*!< Specifies source address of DMA */

    uint32_t dst;                            /*!< Specifies destination address of DMA*/

    uint32_t llp;                            /*!< Starting address in Memory of next LLI if block chaining is enabled */

    uint32_t ctl_reg_low;                    /*!< Specifies control register lower part*/

    uint32_t ctl_reg_high;                   /*!< Specifies control register higher part*/

    uint32_t reserved[2];                    /*!< Specifies necessary placeholder*/
}DMA_LlpTypeDef;

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup DMA_Functions_Prototypes DMA Functions Prototypes
* @{
*/

/**
* @brief  The DMA Initializes peripheral according to
*         the specified parameters in the init_struct parameter.
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @param  init_struct: pointer to a DMA_InitTypeDef
*         structure that contains the configuration information for
*         the specified DMA peripheral.
* @retval None
*/
extern void DMA_Init(DMA_TypeDef *dma, uint8_t chl, DMA_InitTypeDef *init_struct);

/**
* @brief  The DMA uninitializes peripheral
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @retval None
*/
extern void DMA_Uninit(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA gets enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Enable_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA sets enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Enable_Cmd(DMA_TypeDef *dma, FunctionalState NewState);

/**
* @brief  The DMA gets channel enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Enable_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel enabled or disabled command
* @note      You must finish all configuration before calling it 
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets channel source address
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  address: source address
* @retval None
*/
extern void DMA_Set_Channel_source_address(DMA_TypeDef *dma, uint8_t chl, uint32_t address);

/**
* @brief  The DMA sets channel destination address
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  address: destination address
* @retval None
*/
extern void DMA_Set_Channel_destination_address(DMA_TypeDef *dma, uint8_t chl, uint32_t address);

/**
* @brief  The DMA sets block chain address
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  address: block chain address
* @retval None
*/
extern void DMA_Set_block_chain_address(DMA_TypeDef *dma, uint8_t chl, uint32_t address);

/**
* @brief  The DMA gets channel interrupt enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Interrupt_Enable_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel interrupt enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Interrupt_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA gets channel destination width
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaWidth_TypeDef
*/
extern uint32_t DMA_Get_Channel_Destination_Width(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel destination width
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  width: this parameter can be one value of DmaWidth_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Destination_Width(DMA_TypeDef *dma, uint8_t chl, uint32_t width);

/**
* @brief  The DMA gets channel source width
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaWidth_TypeDef
*/
extern uint32_t DMA_Get_Channel_Source_Width(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel source width
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  width: this parameter can be one value of DmaWidth_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Source_Width(DMA_TypeDef *dma, uint8_t chl, uint32_t width);

/**
* @brief  The DMA gets channel destination address increment way
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaAddrType_TypeDef
*/
extern uint32_t DMA_Get_Channel_Destination_Address_Increment_way(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel destination address increment way
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  way: this parameter can be one value of DmaAddrType_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Destination_Address_Increment_way(DMA_TypeDef *dma, uint8_t chl, uint32_t way);

/**
* @brief  The DMA gets channel source address increment way
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaAddrType_TypeDef
*/
extern uint32_t DMA_Get_Channel_Source_Address_Increment_way(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel source address increment way
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  way: this parameter can be one value of DmaAddrType_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Source_Address_Increment_way(DMA_TypeDef *dma, uint8_t chl, uint32_t way);

/**
* @brief  The DMA gets channel destination brust size
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaMsize_TypeDef
*/
extern uint32_t DMA_Get_Channel_Destination_Brust_Size(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel destination brust size
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  size: this parameter can be one value of DmaMsize_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Destination_Brust_Size(DMA_TypeDef *dma, uint8_t chl, uint32_t size);

/**
* @brief  The DMA gets channel source brust size
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaMsize_TypeDef
*/
extern uint32_t DMA_Get_Channel_Source_Brust_Size(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel source brust size
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  size: this parameter can be one value of DmaMsize_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Source_Brust_Size(DMA_TypeDef *dma, uint8_t chl, uint32_t size);

/**
* @brief  The DMA gets channel transfer type
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaDirection_TypeDef
*/
extern uint32_t DMA_Get_Channel_Transfer_Type(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel transfer type
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  type: this parameter can be one value of DmaDirection_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Transfer_Type(DMA_TypeDef *dma, uint8_t chl, uint32_t type);

/**
* @brief  The DMA gets channel destination block chain enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Destination_Block_Chain_Enable_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel destination block chain enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Destination_Block_Chain_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA gets channel source block chain enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Source_Block_Chain_Enable_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel source block chain enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Source_Block_Chain_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets channel block transfer size
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  block_size: block transfer size
* @retval None
*/
extern void DMA_Set_Channel_Block_Transfer_Size(DMA_TypeDef *dma, uint8_t chl, uint32_t block_size);

/**
* @brief  The DMA gets channel priority
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaChlPri_TypeDef
*/
extern uint32_t DMA_Get_Channel_Priority(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel priority
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  priority: this parameter can be one value of DmaChlPri_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Priority(DMA_TypeDef *dma, uint8_t chl, uint32_t priority);

/**
* @brief  The DMA gets channel suspend status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Suspend_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel suspend command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Suspend_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA gets channel fifo empty status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Fifo_Empty_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA gets channel destination handshake type
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaHandshakeType_TypeDef
*/
extern uint32_t DMA_Get_Channel_Destination_Handshake_Type(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel destination handshake type
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  type: this parameter can be one value of DmaHandshakeType_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Destination_Handshake_Type(DMA_TypeDef *dma, uint8_t chl, uint32_t type);

/**
* @brief  The DMA gets channel source handshake type
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaHandshakeType_TypeDef
*/
extern uint32_t DMA_Get_Channel_Source_Handshake_Type(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel source handshake type
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  type: this parameter can be one value of DmaHandshakeType_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Source_Handshake_Type(DMA_TypeDef *dma, uint8_t chl, uint32_t type);

/**
* @brief  The DMA gets channel destination handshake polarity
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaHandshakePolarity_TypeDef
*/
extern uint32_t DMA_Get_Channel_Destination_Handshake_Polarity(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel destination handshake polarity
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  polarity: this parameter can be one value of DmaHandshakePolarity_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Destination_Handshake_Polarity(DMA_TypeDef *dma, uint8_t chl, uint32_t polarity);

/**
* @brief  The DMA gets channel source handshake polarity
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaHandshakePolarity_TypeDef
*/
extern uint32_t DMA_Get_Channel_Source_Handshake_Polarity(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel source handshake polarity
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  polarity: this parameter can be one value of DmaHandshakePolarity_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Source_Handshake_Polarity(DMA_TypeDef *dma, uint8_t chl, uint32_t polarity);

/**
* @brief  The DMA sets channel maximum brust length
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  size: the maximum brust length.A value of 0 indicates that software is not limiting the maximum
                burst length for DMA transfers on this channel
* @retval None
*/
extern void DMA_Set_Channel_Maximum_Brust_Length(DMA_TypeDef *dma, uint8_t chl, uint32_t size);

/**
* @brief  The DMA gets channel source autoreload enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Source_Autoreload_Enable_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel source autoreload enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Source_Autoreload_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA gets channel destination autoreload enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Destination_Autoreload_Enable_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel destination autoreload enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Destination_Autoreload_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA gets channel fifo mode enabled or disabled status
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval ENABLE or DISABLE
*/
extern FunctionalState DMA_Get_Channel_Fifo_Mode_Enable_Status(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel fifo mode enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE.The DISABLE command represents Space/data available for single transfer of the specified transfer width.
                    The ENABLE command represents Data available is greater than or equal to half the FIFO depth for destination transfers and 
                    space available is greater than half the fifo depth for source transfers
* @retval None
*/
extern void DMA_Set_Channel_Fifo_Mode_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA gets channel source handshake interface
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaPer_TypeDef
*/
extern uint32_t DMA_Get_Channel_Source_Handshake_Interface(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel source handshake interface
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  interface: this parameter can be one value of DmaPer_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Source_Handshake_Interface(DMA_TypeDef *dma, uint8_t chl, uint32_t interface);

/**
* @brief  The DMA gets channel destination handshake interface
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @retval one value of DmaPer_TypeDef
*/
extern uint32_t DMA_Get_Channel_Destination_Handshake_Interface(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA sets channel destination handshake interface
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  interface: this parameter can be one value of DmaPer_TypeDef
* @retval None
*/
extern void DMA_Set_Channel_Destination_Handshake_Interface(DMA_TypeDef *dma, uint8_t chl, uint32_t interface);

/**
* @brief  The DMA sets block transfer-finished interrupt enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Block_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets destination transfer-finished interrupt enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Destination_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets source transfer-finished interrupt enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Source_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets transfer-finished interrupt enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets error interrupt enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Error_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA gets block interrupt status after it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Block_Interrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets destination transfer interrupt status after it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Destination_Transfer_Interrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets source transfer interrupt status after it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Source_Transfer_Interrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets transfer interrupt status after it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Transfer_Interrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets error interrupt status after it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Error_Interrrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets raw block interrupt status before it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Raw_Block_Interrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets raw destination transfer interrupt status before it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Raw_Destination_Transfer_Interrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets raw source transfer interrupt status before it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Raw_Source_Transfer_Interrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets raw transfer interrupt status before it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Raw_Transfer_Interrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA gets raw error interrupt status before it is enabled.
* @note      The result and the DmaChlIntFlag_TypeDef structure to do logic AND, if it is 1, it means an interrupt has occurred
* @param  dma: dma base address.@ref DMA
* @retval the one or more value of DmaChlIntFlag_TypeDef structure
*/
extern int DMA_Get_Raw_Error_Interrrupt_Status(DMA_TypeDef *dma);

/**
* @brief  The DMA clear block interrupt command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @retval None
*/
extern void DMA_Clear_Block_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA clear destination transfer interrupt command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @retval None
*/
extern void DMA_Clear_Destination_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA clear source transfer interrupt command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @retval None
*/
extern void DMA_Clear_Source_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA clear transfer interrupt command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @retval None
*/
extern void DMA_Clear_Transfer_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA clear error interrupt command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @retval None
*/
extern void DMA_Clear_Error_Interrupt_Cmd(DMA_TypeDef *dma, uint8_t chl);

/**
* @brief  The DMA clear all DMA interrupt command
* @param  dma: dma base address.@ref DMA
* @retval None
*/
extern void DMA_Clear_All_Interrupt_Cmd(DMA_TypeDef *dma);

/**
* @brief  The DMA sets channel source software transaction request enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Source_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets channel destination software transaction request enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Destination_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets channel signal source software transaction request enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Single_Source_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets channel signal destination software transaction request enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Single_Destination_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets channel last source software transaction request enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Last_Source_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets channel last destination software transaction request enabled or disabled command
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be one value of DmaChl_TypeDef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void DMA_Set_Channel_Last_Destination_Software_Transaction_Request_Enable_Cmd(DMA_TypeDef *dma, uint8_t chl, FunctionalState NewState);

/**
* @brief  The DMA sets address of transfer and data
* @note   If you use block chaining ,the llp_addr parameter point to the address of DMA_LlpTypeDef struct,otherwise llp_addr is 0.
* @param  dma: dma base address.@ref DMA
* @param  chl: this parameter can be a value of DmaChl_TypeDef
* @param  src_addr: source address
* @param  dst_addr: destination address
* @param  block_size: block size of transfer
* @param  llp_addr: block chaining address 
* @retval None
*/
extern void DMA_Set_Addr(DMA_TypeDef *dma, uint8_t chl, uint32_t src_addr, uint32_t dst_addr, uint8_t block_size, uint32_t llp_addr);

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
