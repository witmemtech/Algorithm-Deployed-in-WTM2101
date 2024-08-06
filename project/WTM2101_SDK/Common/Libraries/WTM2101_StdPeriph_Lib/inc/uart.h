/**
  ******************************************************************************
  * @file    uart.h
  * @brief   Header for uart.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
  
/** Define to Prevent Recursive Inclusion */
#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "WTM2101_UART_register.h"
/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */
  
/** @defgroup UART_Exported_Types UART Exported Types 
  * @{
  */

/**
  * @brief  UART interrupt ID enumeration 
  */
typedef enum
{
  UART_IT_Modem_Status              = 0x00, /*!< modem status Interrupt            */
  UART_NO_Pending_INT               = 0x01, /*!< no interrupt pending              */
  UART_IT_THR_Empty                 = 0x02, /*!< THR emptyInterrupt                */
  UART_IT_Received_Data_Available   = 0x04, /*!< received data available Interrupt */
  UART_IT_Receive_Line_Status       = 0x06, /*!< receiver line status Interrupt    */
  UART_IT_Character_Timeout         = 0x0C, /*!< character timeout Interrupt       */
}UART_IT_TypeDef;

/**
  * @brief UART Init Structure Definition
  */
typedef struct 
{
  uint32_t BaudRate;              /*!< This member configures the UART communication baud rate.
                                       The baud rate is computed using the following formula:
                                       baud rate = (serial clock freq) / (16 * divisor). */
  
  uint32_t WordLength;            /*!< Specifies the number of data bits transmitted or received in a frame.
                                       This parameter can be a value of @ref UART_Word_Length_Define*/
  
  uint32_t StopBits;              /*!< Specifies the number of stop bits transmitted.
                                       This parameter can be a value of @ref UART_Stop_Bits_Define*/ 
  
  uint32_t Parity;                /*!< Specifies the parity mode.
                                       This parameter can be a value of @ref UART_Parity_Define*/

  uint32_t Mode;                  /*!< Specifies UART work mode.
                                       This parameter can be a value of @ref UART_Mode_Define*/

  FunctionalState FIFOCtl;        /*!< FIFO function control. 
                                       This parameter can be a value of @ref FunctionalState */

}UART_InitTypeDef;   
   
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/   

/** @defgroup UART_Exported_Constants UART Exported Constants
  * @{
  */ 


/** @defgroup UART_Word_Length_Define UART Word Length Define
  * @brief UART Word Length 
  * @{
  */
#define UART_WORDLENGTH_5B                 (0U<<UART_LCR_DLS_Pos)   /*!< 5bits length           */
#define UART_WORDLENGTH_6B                 (1U<<UART_LCR_DLS_Pos)   /*!< 6bits length           */
#define UART_WORDLENGTH_7B                 (2U<<UART_LCR_DLS_Pos)   /*!< 7bits length           */
#define UART_WORDLENGTH_8B                 (3U<<UART_LCR_DLS_Pos)   /*!< 8bits length           */
/**
  * @}
  */

/** @defgroup UART_Stop_Bits_Define UART Number of Stop Bits Define
  * @brief UART Number of Stop Bits
  * @{
  */
#define UART_STOPBITS_1                    (0U<<UART_LCR_STOP_Pos)  /*!< 1bit stop bit          */
#define UART_STOPBITS_1_5                  (1U<<UART_LCR_STOP_Pos)  /*!< 1.5-bit stop bit       */
#define UART_STOPBITS_2                    (1U<<UART_LCR_STOP_Pos)  /*!< 2-bit stop bit         */
/**
  * @}
  */

/** @defgroup UART_Parity_Define UART Parity Define
  * @brief UART Parity 
  * @{
  */
#define UART_PARITY_NONE                   (0U<<UART_LCR_EPS_Pos)                      /*!< no parity             */
#define UART_PARITY_EVEN                   ((1U<<UART_LCR_EPS_Pos)|UART_LCR_PEN_Msk)   /*!< even parity           */
#define UART_PARITY_ODD                    ((0U<<UART_LCR_EPS_Pos)|UART_LCR_PEN_Msk)   /*!< odd parity            */
#define UART_PARITY_FORCE0                 ((3U<<UART_LCR_EPS_Pos)|UART_LCR_PEN_Msk)   /*!< force0 parity         */
#define UART_PARITY_FORCE1                 ((2U<<UART_LCR_EPS_Pos)|UART_LCR_PEN_Msk)   /*!< force1 parity         */
/**
  * @}
  */

/** @defgroup UART_Mode_Define UART Mode Define
  * @brief UART Mode 
  * @{
  */
#define UART_MODE_UART                     (0U<<UART_MCR_LB_Pos)  /*!< uart mode             */
#define UART_MODE_LOOPBACK                 (1U<<UART_MCR_LB_Pos)  /*!< loopback mode         */
/**
  * @}
  */

/** @defgroup UART_Interrupt_Define UART Interrupt Define
  * @brief UART Interrupt
  * @{
  */
#define  UART_IT_ERBFI                      UART_IER_ERBFI_Msk  /*!< Enable Received Data Available Interrupt          */
#define  UART_IT_ETBEI                      UART_IER_ETBEI_Msk  /*!< Enable Transmit Holding Register Empty Interrupt  */
#define  UART_IT_ELSI                       UART_IER_ELSI_Msk   /*!< Enable Receiver Line Status Interrupt             */
#define  UART_IT_EDSSI                      UART_IER_EDSSI_Msk  /*!< Enable Modem Status Interrupt                     */
/**
  * @}
  */   

/** @defgroup UART_Flag_Define UART Flag Define
  * @brief UART Flag 
  * @{
  */
#define  UART_FLAG_DR                       UART_LSR_DR_Msk    /*!<Data Ready bit                       */
#define  UART_FLAG_OE                       UART_LSR_OE_Msk    /*!<Overrun error bit                    */
#define  UART_FLAG_PE                       UART_LSR_PE_Msk    /*!<Parity Error bit                     */
#define  UART_FLAG_FE                       UART_LSR_FE_Msk    /*!<Framing Error bit                    */
#define  UART_FLAG_BI                       UART_LSR_BI_Msk    /*!<Break Interrupt bit                  */
#define  UART_FLAG_THRE                     UART_LSR_THRE_Msk  /*!<Transmit Holding Register Empty bit  */
#define  UART_FLAG_TEMT                     UART_LSR_TEMT_Msk  /*!<Transmitter Empty bit                */
#define  UART_FLAG_RFE                      UART_LSR_RFE_Msk   /*!<Receiver FIFO Error bit              */
/**
  * @}
  */

/** @defgroup UART_FIFO_Level_Define UART FIFO Level Define
  * @brief UART FIFO Level 
  * @{
  */
#define  UART_RX_FIFO_1                     (0U<<UART_FCR_RT_Pos)  /*!< UART trigger levels 1                */
#define  UART_RX_FIFO_1DIV4                 (1U<<UART_FCR_RT_Pos)  /*!< UART trigger levels 1/4              */
#define  UART_RX_FIFO_1DIV2                 (2U<<UART_FCR_RT_Pos)  /*!< UART trigger levels 1/2              */
#define  UART_RX_FIFO_2LTF                  (3U<<UART_FCR_RT_Pos)  /*!< UART trigger levels 2 less than full */
/**
  * @}
  */


/**
  * @}
  */

/** @defgroup UART_Functions_Prototypes UART Functions Prototypes
  * @{
  */
/* Initialization and Configuration functions *********************************/
/**
* @brief  Initializes the UARTx peripheral according to
*         the specified parameters in the UART_InitStruct.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that contains
*         the configuration information for the specified UART peripheral.
* @retval None
*/
extern void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);

/**
* @brief  The UART init structure parameters values set as default.
* @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that contains
*         the configuration information for the specified UART peripheral.
* @retval None
*/
extern void UART_StructInit(UART_InitTypeDef* UART_InitStruct);

/* Data transfers functions ***************************************************/

/**
* @brief  Send one byte data by UARTx.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @param  Data: the data to be send.
* @retval None
*/ 
extern void UART_SendData(UART_TypeDef* UARTx, uint8_t Data);

/**
* @brief  Receive one byte data by UARTx.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @retval The data receive by UARTx.
*/  
extern uint8_t UART_ReceiveData(UART_TypeDef* UARTx);

/* Interrupts and flags management functions **********************************/
/**
* @brief  Configure the selected UARTx interrupt function.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @param  UART_IT: select interrupt source,This parameter can be one value of 
*         @ref UART_Interrupt_Define.
* @param  NewState: ENABLE or DISABLE function
*         This parameter can be select ENABLE or DISABLE,refer to @ref FunctionalState.
* @retval None
*/
extern void UART_IT_Cfg(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);

/**
* @brief  Get the selected UARTx interrupt state.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @retval Interrupt state
*/
extern UART_IT_TypeDef UART_IT_GetStat(UART_TypeDef* UARTx);

/**
* @brief  Get the selected UARTx falg state.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @param  UART_FLAG: select status flag,This parameter can be one value of 
*         @ref UART_Flag_Define.
* @retval Flag state selected.
*/
extern FlagStatus UART_Flag_GetStatBit(UART_TypeDef* UARTx, uint32_t UART_FLAG);

/**
* @brief  Get the UARTx falg status.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @retval All Flag status.
*/
extern uint32_t UART_Flag_GetStat(UART_TypeDef* UARTx);

/**
* @brief  Clear the UARTx flag status.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @retval None
*/
extern void UART_Flag_Clr(UART_TypeDef* UARTx);

/* FIFO Configuration functions ***********************************************/
/**
* @brief  Get the UARTx FIFO falg state.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @retval FIFO flag state.
*/
extern FlagStatus UART_Flag_GetFIFOStatus(UART_TypeDef* UARTx);

/**
* @brief  Configure the receiver FIFO trigger level.
* @param  UARTx: where x can  be 0 or 1 to select the UART peripheral.
* @param  FIFO_Level: select trigger levels,This parameter can be one value of 
*         @ref UART_FIFO_Level_Define.
* @retval None
*/
extern void UART_RxFIFO_LevelCfg(UART_TypeDef* UARTx, uint32_t FIFO_Level);
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup UART_Private_Macros UART Private Macros
  * @{
  */
#define IS_UART_WORDLEN(LEN)       (((LEN) == UART_WORDLENGTH_5B)     ||\
                                    ((LEN) == UART_WORDLENGTH_6B)     ||\
                                    ((LEN) == UART_WORDLENGTH_7B)     ||\
                                    ((LEN) == UART_WORDLENGTH_8B))
#define IS_UART_STOPBIT(BIT)       (((BIT) == UART_STOPBITS_1)        ||\
                                    ((BIT) == UART_STOPBITS_1_5)      ||\
                                    ((BIT) == UART_STOPBITS_2))
#define IS_UART_PARITY(PTY)        (((PTY) == UART_PARITY_NONE)       ||\
                                    ((PTY) == UART_PARITY_EVEN)       ||\
                                    ((PTY) == UART_PARITY_ODD)        ||\
                                    ((PTY) == UART_PARITY_FORCE0)     ||\
                                    ((PTY) == UART_PARITY_FORCE1))
#define IS_UART_MODE(MODE)         (((MODE) == UART_MODE_UART)        ||\
                                    ((MODE) == UART_MODE_LOOPBACK))
#define IS_UART_BAUDRATE(BAUDRATE)  ((BAUDRATE) <= 230400U) 
#define IS_UART_INT(INT)           (((INT) == UART_IT_ERBFI)          ||\
                                    ((INT) == UART_IT_ETBEI)          ||\
                                    ((INT) == UART_IT_ELSI)           ||\
                                    ((INT) == UART_IT_EDSSI))
#define IS_UART_FLAG(FLAG)         (((FLAG) == UART_FLAG_DR)          ||\
                                    ((FLAG) == UART_FLAG_OE)          ||\
                                    ((FLAG) == UART_FLAG_PE)          ||\
                                    ((FLAG) == UART_FLAG_FE)          ||\
                                    ((FLAG) == UART_FLAG_BI)          ||\
                                    ((FLAG) == UART_FLAG_THRE)        ||\
                                    ((FLAG) == UART_FLAG_TEMT)        ||\
                                    ((FLAG) == UART_FLAG_RFE))
#define IS_UART_FIFOLVL(LVL)       (((LVL) == UART_RX_FIFO_1)         ||\
                                    ((LVL) == UART_RX_FIFO_1DIV4)     ||\
                                    ((LVL) == UART_RX_FIFO_1DIV2)     ||\
                                    ((LVL) == UART_RX_FIFO_2LTF))
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
