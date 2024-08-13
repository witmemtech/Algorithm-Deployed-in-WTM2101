/**
  ******************************************************************************  
  * @file    i2s.h
  * @brief   Header for i2s.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  *******************************************************************************  
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __I2S_H__
#define __I2S_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "WTM2101_I2S_register.h"
/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2S
  * @{
  */
  
/** @defgroup I2S_Exported_Types I2S Exported Types 
  * @{
  */

/** 
  * @brief  GI2S Mode enumeration 
  */
typedef enum
{
    I2S_MASTER = 0x00,
    I2S_SLAVE  = 0x01
}I2S_Mode;
   
/**
  * @brief  I2S Set Flag enumeration 
  */
typedef enum
{
    I2S_SET_OK = 0,
    I2S_SET_ERROR
}I2S_Set_State;   
   
/**
  * @}
  */  
   
/* Exported constants --------------------------------------------------------*/   

/** @defgroup I2S_Exported_Constants I2S Exported Constants
  * @{
  */ 
  
/** @defgroup I2S_Sclk_Number  I2S Sclk Number
  * @brief I2S Sclk Number define 
  * @{
  */
#define I2S_SCLKNUM_16                           (0U<<I2S_CCR_WSS_Pos)  /*!< 16 clock cycles        */
#define I2S_SCLKNUM_24                           (1U<<I2S_CCR_WSS_Pos)  /*!< 24 clock cycles        */
#define I2S_SCLKNUM_32                           (2U<<I2S_CCR_WSS_Pos)  /*!< 32 clock cycles        */
/**
  * @}
  */    
    
/** @defgroup I2S_Gate_Sclk_Number  I2S Gate Sclk Number
  * @brief I2S Gate Sclk Number define 
  * @{
  */
#define I2S_GATESCLKNUM_NONE                     (0U<<I2S_CCR_SCLKG_Pos)  /*!< No clock gating            */
#define I2S_GATESCLKNUM_12                       (1U<<I2S_CCR_SCLKG_Pos)  /*!< Gate after 12 clock cycles */
#define I2S_GATESCLKNUM_16                       (2U<<I2S_CCR_SCLKG_Pos)  /*!< Gate after 16 clock cycles */
#define I2S_GATESCLKNUM_20                       (3U<<I2S_CCR_SCLKG_Pos)  /*!< Gate after 20 clock cycles */
#define I2S_GATESCLKNUM_24                       (4U<<I2S_CCR_SCLKG_Pos)  /*!< Gate after 24 clock cycles */
/**
  * @}
  */

/** @defgroup I2S_Receiver_Resolution  I2S Receiver Resolution
  * @brief I2S Receiver Resolution define 
  * @{
  */
#define I2S_RES_LEN_IGNORE                       (0U<<I2S_RCR0_WLEN_Pos)  /*!< Ignore word length  */
#define I2S_RES_LEN_12                           (1U<<I2S_RCR0_WLEN_Pos)  /*!< 12 bit resolution   */
#define I2S_RES_LEN_16                           (2U<<I2S_RCR0_WLEN_Pos)  /*!< 16 bit resolution   */
#define I2S_RES_LEN_20                           (3U<<I2S_RCR0_WLEN_Pos)  /*!< 20 bit resolution   */
#define I2S_RES_LEN_24                           (4U<<I2S_RCR0_WLEN_Pos)  /*!< 24 bit resolution   */
#define I2S_RES_LEN_32                           (5U<<I2S_RCR0_WLEN_Pos)  /*!< 32 bit resolution   */
/**
  * @}
  */

/** @defgroup I2S_Interrupt_Source I2S Interrupt Source
  * @brief I2S Interrupt source select 
  * @{
  */
#define I2S_IT_TXFO                              I2S_ISR0_TXFO_Msk  /*!< Data Overrun interrupt for the TX channel  */
#define I2S_IT_TXFE                              I2S_ISR0_TXFE_Msk  /*!< Transmit Empty Trigger interrupt           */
#define I2S_IT_RXFO                              I2S_ISR0_RXFO_Msk  /*!< Data Overrun interrupt for the RX channel  */
#define I2S_IT_RXDA                              I2S_ISR0_RXDA_Msk  /*!< Receive Data Available interrupt           */
/**
  * @}
  */

/**
  * @}
  */   
   
/** @defgroup I2S_Functions_Prototypes I2S Functions Prototypes
  * @{
  */

/**
* @brief  I2S mode select function.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  Mode: I2S_MASTER or I2S_SLAVE.
* @retval None
*/
extern void I2S_Mode_Sel(I2S_TypeDef* I2Sx, I2S_Mode Mode);

/**
* @brief  Enable or disable the selected I2S function.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2S_Ctl(I2S_TypeDef* I2Sx, FunctionalState NewState);

/**
* @brief  Set I2S sample rate.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  Rate: sample rate.
* @retval I2S_SET_OK is success,I2S_SET_ERROR is error.
*/
extern I2S_Set_State I2S_SplRate_Set(I2S_TypeDef* I2Sx, uint16_t Rate);

/**
* @brief  Enable or disable the selected I2S receiver block.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2S_RxBlkCtl(I2S_TypeDef* I2Sx, FunctionalState NewState);

/**
* @brief  Enable or disable the selected I2S Transmitter block.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2S_TxBlkCtl(I2S_TypeDef* I2Sx, FunctionalState NewState);

/**
* @brief  Enable or disable the selected I2S Clock Generation block.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2S_ClkCtl(I2S_TypeDef* I2Sx, FunctionalState NewState);

/**
* @brief  Configure the selected I2S Clock.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  SclkNum: select number of sclk cycles,This parameter can be a value of 
*         @ref I2S_Sclk_Number.
* @param  SclkGate: select gating of sclk,This parameter can be a value of 
*         @ref I2S_Gate_Sclk_Number.
* @retval None
*/
extern void I2S_ClkCfg(I2S_TypeDef* I2Sx, uint32_t SclkNum, uint32_t SclkGate);

/**
* @brief  Reset the selected I2S RX FIFOs.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @retval None
*/
extern void I2S_RxBlk_FIFO_Rst(I2S_TypeDef* I2Sx);

/**
* @brief  Reset the selected I2S TX FIFOs.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @retval None
*/
extern void I2S_TxBlk_FIFO_Rst(I2S_TypeDef* I2Sx);

/**
* @brief  Enable or disable the selected I2S channel_0 Receive, just only one channel.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2S_RxChlCtl(I2S_TypeDef* I2Sx, FunctionalState NewState);

/**
* @brief  Enable or disable the selected I2S channel_0 Transmit, just only one channel.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2S_TxChlCtl(I2S_TypeDef* I2Sx, FunctionalState NewState);

/**
* @brief  Configure the selected I2S data resolution of the receiver.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  ResLen: resolution length.This parameter can be a value of 
*         @ref I2S_Receiver_Resolution.
* @retval None
*/
extern void I2S_RxCfg(I2S_TypeDef* I2Sx, uint32_t ResLen);

/**
* @brief  Configure the selected I2S data resolution of the transmitter.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  ResLen: resolution length.This parameter can be a value of 
*         @ref I2S_Receiver_Resolution.
* @retval None
*/
extern void I2S_TxCfg(I2S_TypeDef* I2Sx, uint32_t ResLen);

/**
* @brief  Get the selected I2S interrupt Status.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  I2S_IT: select interrupt source,This parameter can be a value of 
*         @ref I2S_Interrupt_Source.
* @retval selected interrupt Status
*/
extern ITStatus I2S_IT_GetStatBit(I2S_TypeDef* I2Sx, uint32_t I2S_IT);

/**
* @brief  Get all I2S interrupt Status.
* @param  I2Sx: to select the I2S peripheral.
* @retval I2S interrupt Status
*/
extern uint32_t I2S_IT_GetStat(I2S_TypeDef* I2Sx);

/**
* @brief  Enable or disable the selected I2C interrupt mask function.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  IT_Msk: Interrupt source selected,This parameter can be a 
*         value of @ref I2S_Interrupt_Source.
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2S_IT_MskCtl(I2S_TypeDef* I2Sx, uint32_t IT_Msk, FunctionalState NewState);

/**
* @brief  Clear RX FIFO Data Overrun interrupt..
* @param  I2Sx: to select the I2S peripheral.
* @retval None.
*/
extern void I2S_IT_RORClr(I2S_TypeDef* I2Sx);

/**
* @brief  Clear TX FIFO Data Overrun interrupt..
* @param  I2Sx: to select the I2S peripheral.
* @retval None.
*/
extern void I2S_IT_TORClr(I2S_TypeDef* I2Sx);

/**
* @brief  Configure the selected I2S trigger level in the RX FIFO.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  Level: trigger level.This parameter can be a value of 
*         0-7.
* @retval None
*/
extern void I2S_RxFIFO_LVLCfg(I2S_TypeDef* I2Sx, uint8_t Level);

/**
* @brief  Configure the selected I2S trigger level in the TX FIFO.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  Level: trigger level.This parameter can be a value of 
*         0-7.
* @retval None
*/
extern void I2S_TxFIFO_LVLCfg(I2S_TypeDef* I2Sx, uint8_t Level);

/**
* @brief  Flush the selected I2S RX FIFO.
* @param  I2Sx: to select the I2S peripheral.
* @retval None
*/
extern void I2S_RxFIFO_Flush(I2S_TypeDef* I2Sx);

/**
* @brief  Flush the selected I2S TX FIFO.
* @param  I2Sx: to select the I2S peripheral.
* @retval None
*/
extern void I2S_TxFIFO_Flush(I2S_TypeDef* I2Sx);

/**
* @brief  Reset the selected I2S Receiver Block DMA Register..
* @param  I2Sx: to select the I2S peripheral.
* @note
* @retval None
*/
extern void I2S_RxBlk_DMA_Rst(I2S_TypeDef* I2Sx);

/**
* @brief  Reset the selected I2S Transmitter Block DMA Register.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @retval None
*/
extern void I2S_TxBlk_DMA_Rst(I2S_TypeDef* I2Sx);

/**
* @brief  Transmit data by the select I2S.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  pData: data source point.
* @param  Size: data length,This number needs to be even.
* @retval None
*/
extern void I2S_TransmitData(I2S_TypeDef *I2Sx, uint32_t *pData, uint32_t Size);

/**
* @brief  Receive data from the select I2S.
* @param  I2Sx: to select the I2S peripheral.
* @note
* @param  pData: data destination point.
* @param  Size: data length,This number needs to be even.
* @retval None
*/
extern void I2S_ReceiveData(I2S_TypeDef *I2Sx, uint32_t *pData, uint32_t Size);

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup I2S_Private_Macros I2S Private Macros
  * @{
  */

 #define IS_I2S_SCLKNUM(NUM)        (((NUM) == I2S_SCLKNUM_16)       ||\
                                    ((NUM) == I2S_SCLKNUM_24)        ||\
                                    ((NUM) == I2S_SCLKNUM_32))
 #define IS_I2S_GATESCLKNUM(NUM)    (((NUM) == I2S_GATESCLKNUM_NONE) ||\
                                    ((NUM) == I2S_GATESCLKNUM_12)    ||\
                                    ((NUM) == I2S_GATESCLKNUM_16)    ||\
                                    ((NUM) == I2S_GATESCLKNUM_20)    ||\
                                    ((NUM) == I2S_GATESCLKNUM_24))
 #define IS_I2S_RESLEN(LEN)         (((LEN) == I2S_RES_LEN_IGNORE)   ||\
                                    ((LEN) == I2S_RES_LEN_12)        ||\
                                    ((LEN) == I2S_RES_LEN_16)        ||\
                                    ((LEN) == I2S_RES_LEN_20)        ||\
                                    ((LEN) == I2S_RES_LEN_24)        ||\
                                    ((LEN) == I2S_RES_LEN_32))
#define IS_I2S_INT(INT)             (((INT) == I2S_IT_TXFO)          ||\
                                    ((INT) == I2S_IT_TXFE)           ||\
                                    ((INT) == I2S_IT_RXFO)           ||\
                                    ((INT) == I2S_IT_RXDA))
#define IS_I2S_TRIGLVL(LVL)         ((LVL) <= 7)
#define IS_I2S_EVENNUM(EVEN)        (((EVEN)%2) == 0)
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
