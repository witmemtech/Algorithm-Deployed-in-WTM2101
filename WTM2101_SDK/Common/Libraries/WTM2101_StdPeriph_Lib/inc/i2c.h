/**
  ******************************************************************************  
  * @file    i2c.h
  * @brief   Header for i2c.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *  
  ******************************************************************************  
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "WTM2101_I2C_register.h"
/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/** @defgroup I2C_Exported_Types I2C Exported Types
  * @{
  */

/**
  * @brief  I2C Set Flag enumeration
  */
typedef enum
{
    I2C_SET_OK = 0,
    I2C_SET_ERROR
}I2C_Set_State;

/**
  * @brief  I2C state enumeration
  */
typedef enum
{
    I2C_OK = 0,
    I2C_ADDR_BYTE_NUM_ERROR,
    I2C_TIMEOUT_ERROR,
    I2C_TX_ABORT_ERROR
}I2C_State;

/**
  * @brief I2C Init Structure Definition
  */
typedef struct
{
    uint32_t Mode;                         /*!< Specifies the I2C mode.
                                              This parameter can be a value of @ref I2C_Mode*/

    uint32_t Speed;                        /*!< Specifies the device speed mode.
                                                This parameter can be a value of @ref I2C_Speed_Mode*/
    
    uint32_t AddrMode;                     /*!< Specifies the device addressing mode.
                                                This parameter can be a value of @ref I2C_Addressing_Mode*/
    
    uint32_t Address;                      /*!< Specifies the device own address or slave address,
                                                Decided by the mode of work.
                                                This parameter can be a 7-bit or 10-bit address*/
    
    uint32_t Restart;                      /*!< Enables or disables the RESTART conditions function.
                                                This parameter can be a value of @ref I2C_Restart_Config */
    
    uint32_t Rate;                         /*!< Specifies the I2C rate,I2C_SPEED_STD mode Mode<=100K,
                                                I2C_SPEED_FAST Mode Rate<=400K*/
    
    uint32_t SpkLen;                       /*!< Specifies the spklen value,SpkLen >=1 */

}I2C_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup I2C_Exported_Constants I2C Exported Constants
  * @{
  */

/** @defgroup I2C_Mode I2C Mode
  * @brief I2C mode select
  * @{
  */
#define I2C_MODE_MASTER                  ((1U<<I2C_IC_CON_MASTER_MODE_Pos)|(1U<<I2C_IC_CON_IC_SLAVE_DISABLE_Pos))  /*!< Master mode           */
#define I2C_MODE_SLAVE                   ((0U<<I2C_IC_CON_MASTER_MODE_Pos)|(0U<<I2C_IC_CON_IC_SLAVE_DISABLE_Pos))  /*!< Slave mode            */
/**
  * @}
  */

/** @defgroup I2C_Speed_Mode I2C Speed Mode
  * @brief I2C speed mode select
  * @{
  */
#define I2C_SPEED_STD                    (1U<<I2C_IC_CON_SPEED_Pos)  /*!< Standard mode         */
#define I2C_SPEED_FAST                   (2U<<I2C_IC_CON_SPEED_Pos)  /*!< Fast mode             */
/**
  * @}
  */

/** @defgroup I2C_Addressing_Mode I2C Addressing Mode
  * @brief I2C addressing mode select
  * @{
  */
#define I2C_ADDR_7BITS_MASTER            (0U<<I2C_IC_TAR_IC_10BITADDR_MASTER_Pos)  /*!< Master mode 7-bit addressing  */
#define I2C_ADDR_10BITS_MASTER           (1U<<I2C_IC_TAR_IC_10BITADDR_MASTER_Pos)  /*!< Master mode10-bit addressing  */
#define I2C_ADDR_7BITS_SLAVE             (0U<<I2C_IC_CON_IC_10BITADDR_SLAVE_Pos)   /*!< Slave mode 7-bit addressing   */
#define I2C_ADDR_10BITS_SLAVE            (1U<<I2C_IC_CON_IC_10BITADDR_SLAVE_Pos)   /*!< Slave mode10-bit addressing   */
/**
  * @}
  */

/** @defgroup I2C_Restart_Config I2C Restart Config
  * @brief I2C Restart Config select
  * @{
  */
#define I2C_RESTART_ENABLE               (1U<<I2C_IC_CON_IC_RESTART_EN_Pos)  /*!< Enable sent RESTART conditions   */
#define I2C_RESTART_DISABLE              (0U<<I2C_IC_CON_IC_RESTART_EN_Pos)  /*!< Disable sent RESTART conditions  */
/**
  * @}
  */

/** @defgroup I2C_TX_Empty_Config I2C TX Empty Config
  * @brief I2C behavior of TX EMPTY interrupt select
  * @{
  */
#define I2C_TX_EMPTY_MODE0               (0U<<I2C_IC_CON_TX_EMPTY_CTR_Pos)  /*!< TX EMPTY interrupt mode0 */
#define I2C_TX_EMPTY_MODE1               (1U<<I2C_IC_CON_TX_EMPTY_CTR_Pos)  /*!< TX EMPTY interrupt mode1 */
/**
  * @}
  */

/** @defgroup I2C_Interrupt_Source I2C Interrupt Source
  * @brief I2C Interrupt Source select
  * @{
  */
#define I2C_IT_RX_UNDER                  I2C_IC_INTR_STAT_R_RX_UNDER_Msk   /*!< RX_UNDER interrupt   */
#define I2C_IT_RX_OVER                   I2C_IC_INTR_STAT_R_RX_OVER_Msk    /*!< RX_OVER interrupt    */
#define I2C_IT_RX_FULL                   I2C_IC_INTR_STAT_R_RX_FULL_Msk    /*!< RX_FULL interrupt  (no clr) */
#define I2C_IT_TX_OVER                   I2C_IC_INTR_STAT_R_TX_OVER_Msk    /*!< TX_OVER interrupt    */
#define I2C_IT_TX_EMPTY                  I2C_IC_INTR_STAT_R_TX_EMPTY_Msk   /*!< TX_EMPTY interrupt  (no clr) */
#define I2C_IT_RD_REQ                    I2C_IC_INTR_STAT_R_RD_REQ_Msk     /*!< RD_REQ interrupt     */
#define I2C_IT_TX_ABRT                   I2C_IC_INTR_STAT_R_TX_ABRT_Msk    /*!< TX_ABRT interrupt    */
#define I2C_IT_RX_DONE                   I2C_IC_INTR_STAT_R_RX_DONE_Msk    /*!< RX_DONE interrupt    */
#define I2C_IT_ACT                       I2C_IC_INTR_STAT_R_ACTIVITY_Msk   /*!< ACTIVITY interrupt   */
#define I2C_IT_STOP_DET                  I2C_IC_INTR_STAT_R_STOP_DET_Msk   /*!< STOP_DET interrupt   */
#define I2C_IT_START_DET                 I2C_IC_INTR_STAT_R_START_DET_Msk  /*!< START_DET interrupt  */
#define I2C_IT_GEN_CALL                  I2C_IC_INTR_STAT_R_GEN_CALL_Msk   /*!< GEN_CALL interrupt   */
#define I2C_IT_ALL                       (0x00000FFFU)                     /*!< All interrupt        */
/**
  * @}
  */

/** @defgroup I2C_Status I2C status
  * @brief I2C status flag select
  * @{
  */
#define I2C_FLAG_ACT                     I2C_IC_STATUS_ACTIVITY_Msk      /*!< Activity Status flag                 */
#define I2C_FLAG_TFNF                    I2C_IC_STATUS_TFNF_Msk          /*!< Transmit FIFO Not Full flag          */
#define I2C_FLAG_TFE                     I2C_IC_STATUS_TFE_Msk           /*!< Transmit FIFO Completely Empty flag  */
#define I2C_FLAG_RFNE                    I2C_IC_STATUS_RFNE_Msk          /*!< Receive FIFO Not Empty flag          */
#define I2C_FLAG_RFF                     I2C_IC_STATUS_RFF_Msk           /*!< Receive FIFO Completely Full flag    */
#define I2C_FLAG_MST_ACT                 I2C_IC_STATUS_MST_ACTIVITY_Msk  /*!< Master FSM Activity Status flag      */
#define I2C_FLAG_SLV_ACT                 I2C_IC_STATUS_SLV_ACTIVITY_Msk  /*!< Slave FSM Activity Status flag       */
/**
  * @}
  */

/** @defgroup I2C_FIFO_DMA_Channel_Config I2C FIFO DMA Channel Config
  * @brief I2C FIFO DMA channel interface select
  * @{
  */
#define I2C_TX_DMA_EN                    I2C_IC_DMA_CR_TDMAE_Msk  /*!< Transmit DMA Enable  */
#define I2C_RX_DMA_EN                    I2C_IC_DMA_CR_RDMAE_Msk  /*!< Receive DMA Enable   */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup I2C_Functions_Prototypes I2C Functions Prototypes
  * @{
  */

/* Initialization and Configuration functions *********************************/
/**
* @brief  Initializes the I2Cx peripheral basic functions according to
*         the specified parameters in the I2C_InitStruct.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @note
* @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that contains
*         the basic configuration information for the specified I2C peripheral.
* @retval I2C_SET_OK is success,I2C_SET_ERROR is error.
*/
extern I2C_Set_State I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);

/**
* @brief  Set the selected I2C timeout period.
* @param  Time: Timeout period.
* @retval None
*/
extern void I2C_TimeOutPeriod_Set(uint32_t Time);

/**
* @brief  Set the selected I2C Target Address.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @note   Set the address succeed only when I2C is disabled.
* @param  Addr: Target Address.
* @retval None
*/
extern void I2C_TarAddr_Set(I2C_TypeDef* I2Cx, uint32_t Addr);

/**
* @brief  Enable or disable the selected I2C function.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @note
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2C_Ctl(I2C_TypeDef* I2Cx, FunctionalState NewState);

/**
* @brief  Configure the behavior of the TX_EMPTY interrupt status.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @note
* @param  Mode: behavior of the TX_EMPTY interrupt mode,This parameter can be a
*         value of @ref I2C_TX_Empty_Config.
* @retval None
*/
extern void I2C_TX_EmptyCtl(I2C_TypeDef* I2Cx, uint32_t Mode);

/**
* @brief  Enable or disable the selected I2C ACK General Call function.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @note
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2C_Ack_GenCallCtl(I2C_TypeDef* I2Cx, FunctionalState NewState);

/**
* @brief  Enable or disable the selected I2C DMA function.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @note
* @param  DMADir: FIFO DMA channel interface,This parameter can be a
*         value of @ref I2C_FIFO_DMA_Channel_Config.
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2C_DMACtl(I2C_TypeDef* I2Cx, uint32_t DMADir, FunctionalState NewState);

/**
* @brief  Set I2C standard speed Clock SCL High Count.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  HCNT: Count value.
* @retval None
*/
extern void I2C_Set_SS_HCNT(I2C_TypeDef* I2Cx, uint16_t HCNT);  /*!< >SPKLEN+5  */

/**
* @brief  Set I2C standard speed Clock SCL Low Count.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  LCNT: Count value.
* @retval None
*/
extern void I2C_Set_SS_LCNT(I2C_TypeDef* I2Cx, uint16_t LCNT);  /*!< >SPKLEN+7  */

/**
* @brief  Set I2C Fast Mode Clock SCL High Count.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  HCNT: Count value.
* @retval None
*/
extern void I2C_Set_FS_HCNT(I2C_TypeDef* I2Cx, uint16_t HCNT);  /*!< >SPKLEN+5  */

/**
* @brief  Set I2C Fast Mode Clock SCL Low Count.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  LCNT: Count value.
* @retval None
*/
extern void I2C_Set_FS_LCNT(I2C_TypeDef* I2Cx, uint16_t LCNT);  /*!< >SPKLEN+7  */

/**
* @brief  Set I2C Receive FIFO Threshold.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  RxTL: Threshold value.
* @retval None
*/
extern void I2C_Set_RX_TL(I2C_TypeDef* I2Cx, uint8_t RxTL);     /*!< 0-7=>1-8 (FIFO depth is 8)  */

/**
* @brief  Set I2C Transmit FIFO Threshold.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  TxTL: Threshold value.
* @retval None
*/
extern void I2C_Set_TX_TL(I2C_TypeDef* I2Cx, uint8_t TxTL);     /*!< 0-7=>1-8 (FIFO depth is 8)  */

/**
* @brief  Set I2C ISS and FS spike suppression limit.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  Spklen: duration value.
* @retval None
*/
extern void I2C_Set_FS_SPKLEN(I2C_TypeDef* I2Cx, uint8_t Spklen);  /*!< >=1  */

/**
* @brief  Set SDA hold time when I2C as a reciever.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  HoldTime: hold time value.
* @retval None
*/
extern void I2C_Set_SDA_RX_HOLD(I2C_TypeDef* I2Cx, uint8_t HoldTime);

/**
* @brief  Set SDA hold time when I2C as a transmitter.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  HoldTime: hold time value.
* @retval None
*/
extern void I2C_Set_SDA_TX_HOLD(I2C_TypeDef* I2Cx, uint16_t HoldTime);

/**
* @brief  Set I2C DMA Transmit Data Level.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  Level: Level value.
* @retval None
*/
extern void I2C_Set_DMA_TDLR(I2C_TypeDef* I2Cx, uint8_t Level);

/**
* @brief  Set I2C DMA Receive Data Level.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  Level: Level value.
* @retval None
*/
extern void I2C_Set_DMA_RDLR(I2C_TypeDef* I2Cx, uint8_t Level);


/* operation functions *****************************************************/

/**
* @brief  Write Command to TX FIFO.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  Cmd: Command value.
* @retval None
*/
extern void I2C_Write_Cmd(I2C_TypeDef* I2Cx, uint8_t Cmd);

/**
* @brief  Read Command to TX FIFO.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  Cmd: Command value.
* @retval None
*/
extern void I2C_Read_Cmd(I2C_TypeDef* I2Cx, uint8_t Cmd);

/**
* @brief  Write Data to TX FIFO.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  Data: Data value.
* @retval None
*/
extern void I2C_Write_Data(I2C_TypeDef* I2Cx, uint8_t Data);

/**
* @brief  Read data from Rx FIFO.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @retval Read value
*/
extern uint8_t I2C_Read_Data(I2C_TypeDef* I2Cx);

/* Interrupts and flags management functions **********************************/
/**
* @brief  Enable or disable the selected I2C interrupt mask function.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @note
* @param  IT_Msk: Interrupt source selected,This parameter can be a
*         value of @ref I2C_Interrupt_Source.
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE
* @retval None
*/
extern void I2C_IT_MskCtl(I2C_TypeDef* I2Cx, uint32_t IT_Msk, FunctionalState NewState);

/**
* @brief  Read I2C interrupt mask status.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @retval interrupt mask status
*/
extern uint32_t I2C_IT_ReadMsk(I2C_TypeDef* I2Cx);

/**
* @brief  Get the selected I2Cx interrupt status.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  I2C_IT: Interrupt source selected,This parameter can be a
*         value of @ref I2C_Interrupt_Source.
* @retval selected interrupt status
*/
extern ITStatus I2C_IT_GetStatBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);

/**
* @brief  Get the selected I2Cx raw interrupt status.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  I2C_IT: Interrupt source selected,This parameter can be a
*         value of @ref I2C_Interrupt_Source.
* @retval selected raw interrupt status
*/
extern ITStatus I2C_IT_GetRAWStatBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);

/**
* @brief  Get the selected I2Cx raw interrupt status.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @retval Raw interrupt status
*/
extern uint32_t I2C_IT_GetRAWStat(I2C_TypeDef* I2Cx);

/**
* @brief  Clear interrupt Status.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  I2C_IT: Interrupt source selected,This parameter can be a
*         value of @ref I2C_Interrupt_Source.
* @retval None.
*/
extern void I2C_IT_ClrStat(I2C_TypeDef* I2Cx, uint32_t I2C_IT);

/**
* @brief  Get the selected I2Cx status flag.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @param  I2C_FLAG: status flag selected,This parameter can be a
*         value of @ref I2C_Status.
* @retval Selected  flag status.
*/
extern ITStatus I2C_Flag_GetStatBit(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);

/**
* @brief  Get the I2Cx status flag.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @retval Flag status.
*/
extern uint32_t I2C_Flag_GetStat(I2C_TypeDef* I2Cx);

/**
* @brief  Get Transmit FIFO Level.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @retval Transmit FIFO Level value.
*/
extern uint8_t I2C_GetTXFlr(I2C_TypeDef* I2Cx);

/**
* @brief  Get Receive FIFO Level.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @retval Receive FIFO Level value.
*/
extern uint8_t I2C_GetRXFlr(I2C_TypeDef* I2Cx);

/**
* @brief  Get Transmit Abort Status.
* @param  I2Cx: to select the I2C peripheral, just only one I2C Peripheral.
* @retval Transmit Abort Status.
*/
extern uint32_t I2C_GetTXABRT_Src(I2C_TypeDef* I2Cx);

/**
* @brief  Write one byte to slave device address addr.
* @param  addr: Slave device register address.
* @param  addr_byte_num: 1->only 1 byte address addr[7:0],
*         2->2 bytes address, first address addr[7:0],second address addr[15:8].
* @param  data: Write data.
* @retval I2C_State:I2C_OK->success,I2C_ADDR_BYTE_NUM_ERROR->addr_byte_num error,
*         I2C_TIMEOUT_ERROR->timeout error,I2C_TX_ABORT_ERROR->tx abort refer to @ref I2C_State
*/
extern I2C_State WriteByte(uint16_t addr, uint8_t addr_byte_num, uint8_t data);

/**
* @brief  Write multiple bytes to slave device address addr.
* @param  addr: Slave device register address.
* @param  addr_byte_num: 1->only 1 byte address addr[7:0],
*         2->2 bytes address, first address addr[7:0],second address addr[15:8].
* @param  buffer: Write data buffer.
* @param  num: Number of write data.
* @retval I2C_State:I2C_OK->success,I2C_ADDR_BYTE_NUM_ERROR->addr_byte_num error,
*         I2C_TIMEOUT_ERROR->timeout error,I2C_TX_ABORT_ERROR->tx abort refer to @ref I2C_State
*/
extern I2C_State WriteBytes(uint16_t addr, uint8_t addr_byte_num, uint8_t *buffer, uint16_t num);

/**
* @brief  Read one byte from slave device address addr.
* @param  addr: Slave device register address.
* @param  addr_byte_num: 1->only 1 byte address addr[7:0],
*         2->2 bytes address, first address addr[7:0],second address addr[15:8].
* @param  recv: Read data buffer.
* @retval I2C_State:I2C_OK->success,I2C_ADDR_BYTE_NUM_ERROR->addr_byte_num error,
*         I2C_TIMEOUT_ERROR->timeout error,I2C_TX_ABORT_ERROR->tx abort refer to @ref I2C_State
*/
extern I2C_State ReadByte(uint16_t addr, uint8_t addr_byte_num, uint8_t *recv);

/**
* @brief  Read multiple bytes from slave device address addr.
* @param  addr: Slave device register address.
* @param  addr_byte_num: 1->only 1 byte address addr[7:0],
*         2->2 bytes address, first address addr[7:0],second address addr[15:8].
* @param  recv: Read data buffer.
* @param  num: Number of read data.
* @retval I2C_State:I2C_OK->success,I2C_ADDR_BYTE_NUM_ERROR->addr_byte_num error,
*         I2C_TIMEOUT_ERROR->timeout error,I2C_TX_ABORT_ERROR->tx abort refer to @ref I2C_State
*/
extern I2C_State ReadBytes(uint16_t addr, uint8_t addr_byte_num, uint8_t *recv, uint16_t num);


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup I2C_Private_Macros I2C Private Macros
  * @{
  */
#define IS_I2C_MODE(MODE)           (((MODE) == I2C_MODE_MASTER)        ||\
                                    ((MODE) == I2C_MODE_SLAVE))
#define IS_I2C_SPEED(SPEED)         (((SPEED) == I2C_SPEED_STD)         ||\
                                    ((SPEED) == I2C_SPEED_FAST))
#define IS_I2C_ADDRMODE(MODE)       (((MODE) == I2C_ADDR_7BITS_MASTER)  ||\
                                    ((MODE) == I2C_ADDR_10BITS_MASTER)  ||\
                                    ((MODE) == I2C_ADDR_7BITS_SLAVE)    ||\
                                    ((MODE) == I2C_ADDR_10BITS_SLAVE))
#define IS_I2C_ADDR(ADDR)           ((ADDR) <= 0x000003FF)
#define IS_I2C_RST(EN)              (((EN) == I2C_RESTART_ENABLE)       ||\
                                    ((EN) == I2C_RESTART_DISABLE))
#define IS_I2C_TX_EMPTY_MODE(MODE)  (((MODE) == I2C_TX_EMPTY_MODE0)     ||\
                                    ((MODE) == I2C_TX_EMPTY_MODE1))
#define IS_I2C_INT(INT)             (((INT) == I2C_IT_RX_UNDER)         ||\
                                    ((INT) == I2C_IT_RX_OVER)           ||\
                                    ((INT) == I2C_IT_RX_FULL)           ||\
                                    ((INT) == I2C_IT_TX_OVER)           ||\
                                    ((INT) == I2C_IT_TX_EMPTY)          ||\
                                    ((INT) == I2C_IT_RD_REQ)            ||\
                                    ((INT) == I2C_IT_TX_ABRT)           ||\
                                    ((INT) == I2C_IT_RX_DONE)           ||\
                                    ((INT) == I2C_IT_ACT)               ||\
                                    ((INT) == I2C_IT_STOP_DET)          ||\
                                    ((INT) == I2C_IT_START_DET)         ||\
                                    ((INT) == I2C_IT_GEN_CALL)          ||\
                                    ((INT) == I2C_IT_ALL))
#define IS_I2C_DMADIR(DIR)          (((DIR) == I2C_TX_DMA_EN)           ||\
                                    ((DIR) == I2C_RX_DMA_EN))
#define IS_I2C_FLAG(FLAG)           (((FLAG) == I2C_FLAG_ACT)           ||\
                                    ((FLAG) == I2C_FLAG_TFNF)           ||\
                                    ((FLAG) == I2C_FLAG_TFE)            ||\
                                    ((FLAG) == I2C_FLAG_RFNE)           ||\
                                    ((FLAG) == I2C_FLAG_RFF)            ||\
                                    ((FLAG) == I2C_FLAG_MST_ACT)        ||\
                                    ((FLAG) == I2C_FLAG_SLV_ACT))
#define IS_I2C_TIMEOUT(TIME)        ((TIME) != 0x0)
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
