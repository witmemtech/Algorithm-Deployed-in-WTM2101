/**
  ******************************************************************************
  * @file    qspi.h
  * @brief   Header for qspi.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __QSPI_H__
#define __QSPI_H__

#ifdef  __cplusplus
extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "dma.h"
#include "WTM2101_QSPI_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup QSPI
* @{
*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup QSPI_Exported_Constants
* @{
*/

/** @defgroup QSPI_Sph QSPI Clock Phase
  * @{
  */
#define QSPI_SPH_0                     ((uint32_t)0X00000000)           /*!< Clock Phase 0 */
#define QSPI_SPH_1                     ((uint32_t)0x00000001U)          /*!< Clock Phase 1 */
#define IS_QSPI_SPH(SPH)               (((SPH) == QSPI_SPH_0) || \
                                       ((SPH) == QSPI_SPH_1))
/**
  * @}
  */

/** @defgroup QSPI_Spo QSPI Clock Polarity
  * @{
  */
#define QSPI_SPO_0                     ((uint32_t)0X00000000)           /*!< Clock Polarity 0 */
#define QSPI_SPO_1                     ((uint32_t)0x00000001U)          /*!< Clock Polarity 1 */
#define IS_QSPI_SPO(SPO)               (((SPO) == QSPI_SPO_0) || \
                                       ((SPO) == QSPI_SPO_1))
/**
  * @}
  */

/** @defgroup QSPI_Sample_Clock_sel QSPI Sample Clock
  * @{
  */
#define QSPI_SAMPLE_NO_REVERSE_CLOCK    ((uint32_t)0X00000000)           /*!< No Reverse Clock */
#define QSPI_SAMPLE_REVERSE_CLOCK       ((uint32_t)0X00000001)           /*!< Reverse Clock */
#define IS_QSPI_SAMPLE_CLOCK(CLOCK)     (((CLOCK) == QSPI_SAMPLE_NO_REVERSE_CLOCK) || \
                                        ((CLOCK) == QSPI_SAMPLE_REVERSE_CLOCK))
/**
  * @}
  */

/** @defgroup QSPI_AlternateBytesSize QSPI Alternate Bytes Size
  * @{
  */
#define QSPI_ALTERNATE_BYTES_8_BITS     ((uint32_t)0x00000000U)           /*!< 8-bit Alternate Bytes */
#define QSPI_ALTERNATE_BYTES_16_BITS    ((uint32_t)0x00000001U)           /*!< 16-bit Alternate Bytes */
#define QSPI_ALTERNATE_BYTES_24_BITS    ((uint32_t)0x00000002U)           /*!< 24-bit Alternate Bytes */
#define QSPI_ALTERNATE_BYTES_32_BITS    ((uint32_t)0x00000003U)           /*!< 32-bit Alternate Bytes */
#define IS_QSPI_ALTERNATEBYTESIZE(SIZE) (((SIZE) == QSPI_ALTERNATE_BYTES_8_BITS) || \
                                        ((SIZE) == QSPI_ALTERNATE_BYTES_16_BITS) || \
                                        ((SIZE) == QSPI_ALTERNATE_BYTES_24_BITS) || \
                                        ((SIZE) == QSPI_ALTERNATE_BYTES_32_BITS))
/**
  * @}
  */

/** @defgroup QSPI_AddressSize QSPI Address Size
  * @{
  */
#define QSPI_ADDRESS_8_BITS             ((uint32_t)0x00000000U)           /*!< 8-bit Address */
#define QSPI_ADDRESS_16_BITS            ((uint32_t)0x00000001U)           /*!< 16-bit Address */
#define QSPI_ADDRESS_24_BITS            ((uint32_t)0x00000002U)           /*!< 24-bit Address */
#define QSPI_ADDRESS_32_BITS            ((uint32_t)0x00000003U)           /*!< 32-bit Address */
#define IS_QSPI_ADDRESSSIZE(SIZE)       (((SIZE) == QSPI_ADDRESS_8_BITS) || \
                                        ((SIZE) == QSPI_ADDRESS_16_BITS) || \
                                        ((SIZE) == QSPI_ADDRESS_24_BITS) || \
                                        ((SIZE) == QSPI_ADDRESS_32_BITS))
/**
  * @}
  */

/** @defgroup QSPI_Write_Read_Mode QSPI Write Or Read Mode
  * @{
  */
#define QSPI_WRITE_DATA_MODE            ((uint32_t)0X00000000)           /*!< In Indirect Mode Write Data Mode */
#define QSPI_READ_DATA_MODE             ((uint32_t)0X00000001)           /*!< In Indirect Mode Read Data Mode */
#define IS_QSPI_WRITE_READ_DATA_MODE(MODE)  (((MODE) == QSPI_WRITE_DATA_MODE) || \
                                             ((MODE) == QSPI_READ_DATA_MODE))
/**
  * @}
  */

/** @defgroup QSPI_DataMode QSPI Data Mode
  * @{
  */
#define QSPI_DATA_NONE                  ((uint32_t)0X00000000)           /*!< No data */
#define QSPI_DATA_1_LINE                ((uint32_t)0x00000001U)          /*!< Data On Single Line */
#define QSPI_DATA_2_LINES               ((uint32_t)0x00000002U)          /*!< Data On Two Lines */
#define QSPI_DATA_4_LINES               ((uint32_t)0x00000003U)          /*!< Data On Four Lines */
#define IS_QSPI_DATAMODE(MODE)          (((MODE) == QSPI_DATA_NONE)   || \
                                        ((MODE) == QSPI_DATA_1_LINE)  || \
                                        ((MODE) == QSPI_DATA_2_LINES) || \
                                        ((MODE) == QSPI_DATA_4_LINES))
/**
  * @}
  */

/** @defgroup QSPI_AlternateBytesMode  QSPI Alternate Bytes Mode
* @{
*/
#define QSPI_ALTERNATE_BYTES_NONE       ((uint32_t)0x00000000U)           /*!< No Alternate Bytes */
#define QSPI_ALTERNATE_BYTES_1_LINE     ((uint32_t)0x00000001U)           /*!< Alternate Bytes On Single Line */
#define QSPI_ALTERNATE_BYTES_2_LINES    ((uint32_t)0x00000002U)           /*!< Alternate Bytes On Two Lines */
#define QSPI_ALTERNATE_BYTES_4_LINES    ((uint32_t)0x00000003U)           /*!< Alternate Bytes On Four Lines */
#define IS_QSPI_ALTERNATEBYTEMODE(MODE) (((MODE) == QSPI_ALTERNATE_BYTES_NONE)   || \
                                        ((MODE) == QSPI_ALTERNATE_BYTES_1_LINE)  || \
                                        ((MODE) == QSPI_ALTERNATE_BYTES_2_LINES) || \
                                        ((MODE) == QSPI_ALTERNATE_BYTES_4_LINES))
/**
  * @}
  */

/** @defgroup QSPI_AddressMode QSPI Address Mode
* @{
*/
#define QSPI_ADDRESS_NONE               ((uint32_t)0x00000000U)          /*!< No Address */
#define QSPI_ADDRESS_1_LINE             ((uint32_t)0x00000001U)          /*!< Address On Single Line */
#define QSPI_ADDRESS_2_LINES            ((uint32_t)0x00000002U)          /*!< Address On Two Lines */
#define QSPI_ADDRESS_4_LINES            ((uint32_t)0x00000003U)          /*!< Address On Four Lines */
#define IS_QSPI_ADDRESSMODE(MODE)       (((MODE) == QSPI_ADDRESS_NONE)   || \
                                        ((MODE) == QSPI_ADDRESS_1_LINE)  || \
                                        ((MODE) == QSPI_ADDRESS_2_LINES) || \
                                        ((MODE) == QSPI_ADDRESS_4_LINES))
/**
  * @}
  */

/** @defgroup QSPI_InstructionMode QSPI Instruction Mode
* @{
*/
#define QSPI_INSTRUCTION_NONE           ((uint32_t)0x00000000U)          /*!< No Instruction */
#define QSPI_INSTRUCTION_1_LINE         ((uint32_t)0x00000001U)          /*!< Instruction On Single Line */
#define QSPI_INSTRUCTION_2_LINES        ((uint32_t)0x00000002U)          /*!< Instruction On Two Lines */
#define QSPI_INSTRUCTION_4_LINES        ((uint32_t)0x00000003U)          /*!< Instruction On Four Lines */
#define IS_QSPI_INSTRUCTIONMODE(MODE)   (((MODE) == QSPI_INSTRUCTION_NONE)   || \
                                        ((MODE) == QSPI_INSTRUCTION_1_LINE)  || \
                                        ((MODE) == QSPI_INSTRUCTION_2_LINES) || \
                                        ((MODE) == QSPI_INSTRUCTION_4_LINES))
/**
  * @}
  */

/** @defgroup QSPI_Int_Type QSPI Interrupt Type
  * @{
  */
#define QSPI_INT_READ_UNDERFLOW         ((uint32_t)0X00000001U)          /*!< The Read Fifo Underflow Interrupt */
#define QSPI_INT_WRITE_OVERFLOW         ((uint32_t)0x00000002U)          /*!< The Write Fifo Overflow Interrupt */
#define QSPI_INT_POLLING_MATCH          ((uint32_t)0X00000004U)          /*!< The Polling Mode Match Interrupt */
#define QSPI_INT_TRANSMISSION_FINISH    ((uint32_t)0x00000008U)          /*!< The Transimission Complet Interrupt */
#define QSPI_INT_WRITE_EMPTY            ((uint32_t)0x00000010U)          /*!< The Transimission Empty Interrupt */
#define IS_QSPI_INT_TYPE(INT)           (((INT) == QSPI_INT_READ_UNDERFLOW)     || \
                                        ((INT) == QSPI_INT_WRITE_OVERFLOW)      || \
                                        ((INT) == QSPI_INT_POLLING_MATCH)       || \
                                        ((INT) == QSPI_INT_TRANSMISSION_FINISH) || \
                                        ((INT) == QSPI_INT_WRITE_EMPTY))
/**
  * @}
  */

/** @defgroup QSPI_Status_Type QSPI Starus Type
  * @{
  */
#define QSPI_IDLE_STATUS                ((uint32_t)0X00000000)           /*!< The Idle Status */
#define QSPI_INSTRUCTION_SEND_STATUS    ((uint32_t)0x00000001U)          /*!< The Instruction Send Status */
#define QSPI_ADDRESS_SEND_STATUS        ((uint32_t)0X00000002U)          /*!< The Address Send Status */
#define QSPI_ALTERNATEBYTE_SEND_STATUS  ((uint32_t)0x00000003U)          /*!< The Alternatebyte Send Status */
#define QSPI_DUMMY_CYCLE_STATUS         ((uint32_t)0X00000004U)          /*!< The Dummy Cycle Status */
#define QSPI_READ_DATA_STATUS           ((uint32_t)0X00000005U)          /*!< The Read Data Status */
#define QSPI_WRITE_DATA_STATUS          ((uint32_t)0X00000006U)          /*!< The Write Data Status */
#define QSPI_STOP_STATUS                ((uint32_t)0X00000007U)          /*!< The Stop Status */
#define IS_QSPI_STATUS_TYPE(STATUS)    (((STATUS) == QSPI_IDLE_STATUS)               || \
                                        ((STATUS) == QSPI_INSTRUCTION_SEND_STATUS)   || \
                                        ((STATUS) == QSPI_ADDRESS_SEND_STATUS)       || \
                                        ((STATUS) == QSPI_ALTERNATEBYTE_SEND_STATUS) || \
                                        ((STATUS) == QSPI_DUMMY_CYCLE_STATUS)        || \
                                        ((STATUS) == QSPI_READ_DATA_STATUS)          || \
                                        ((STATUS) == QSPI_WRITE_DATA_STATUS)         || \
                                        ((STATUS) == QSPI_STOP_STATUS))
/**
  * @}
  */

/** @defgroup QSPI_Afifo_Status_Type QSPI Afifo Starus Type
  * @{
  */
#define QSPI_WRITE_AFIFO_FULL           ((uint32_t)0X00000001U)          /*!< The Write Afifo Full */
#define QSPI_WRITE_AFIFO_EMPTY          ((uint32_t)0x00000002U)          /*!< The Write Afifo Empty */
#define QSPI_READ_AFIFO_FULL            ((uint32_t)0X00000004U)          /*!< The Read Afifo Full */
#define QSPI_READ_AFIFO_ALMOST_FULL     ((uint32_t)0X00000008U)          /*!< The Read Afifo Almost Full */
#define QSPI_READ_AFIFO_EMPTY           ((uint32_t)0x00000010U)          /*!< The Read Afifo Empty */
#define IS_QSPI_FIFO_STATUS_TYPE(STATUS)(((STATUS) == QSPI_WRITE_AFIFO_FULL)      || \
                                        ((STATUS) == QSPI_WRITE_AFIFO_EMPTY)      || \
                                        ((STATUS) == QSPI_READ_AFIFO_FULL)        || \
                                        ((STATUS) == QSPI_READ_AFIFO_ALMOST_FULL) || \
                                        ((STATUS) == QSPI_READ_AFIFO_EMPTY))
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup QSPI_Exported_Types QSPI Exported Types
* @{
*/

/**
* @brief  QSPI Init Structure Definition
*/
#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint32_t sample_clk_sel;     /* Specifies sample input data clock phase select. 
                                    This parameter can be a value of @ref QSPI_Sample_Clock_sel */
    uint32_t read_delay_time;    /* Specifies when the input data has inter-board delay , the read_delay_time is the delay time.
                                    This parameter can be a number between 0 and 3 */
    uint32_t alternatebytessize; /* Specifies the alternate bytes size.
                                    This parameter can be a value of @ref QSPI_AlternateBytesSize */                                                                                               
    uint32_t addresssize;        /* Specifies the address size.
                                    This parameter can be a value of @ref QSPI_AddressSize */
    uint32_t dummy_cycle;        /* Specifies the qspi send dummy cycle number in the dummy cycle status.
                                    This parameter can be a number between 0 and 31 */   
    uint32_t dmode_sel;          /* Specifies read or write data mode select. 
                                    This parameter can be a value of @ref QSPI_Dmode */
    uint32_t datamode;           /* Specifies the data mode
                                    This parameter can be a value of @ref QSPI_Write_Read_Mode */
    uint32_t alternatebytemode;  /* Specifies the alternate bytes mode
                                    This parameter can be a value of @ref QSPI_AlternateBytesMode */
    uint32_t addressmode;        /* Specifies the address mode
                                    This parameter can be a value of @ref QSPI_AddressMode */
    uint32_t instructionmode;    /* Specifies the instruction mode
                                    This parameter can be a value of @ref QSPI_InstructionMode */
    uint32_t sph;                /* Specifies the qspi clock phase. 
                                    This parameter can be a value of @ref QSPI_Sph */
    uint32_t spo;                /* Specifies the qspi clock polarity. 
                                    This parameter can be a value of @ref QSPI_Spo */
}QSPI_CtlInitTypeDef;

/**
* @brief  QSPI DMA Structure Definition
*/
typedef struct
{
    uint8_t wr_water_level;     /* Specifies the dma write water level
                                    This parameter can be a number between 0 and 7 */
    uint8_t rd_water_level;     /* Specifies the dma read water level
                                    This parameter can be a number between 0 and 7 */
    uint8_t write_en;           /* Specifies the dma write enable
                                    This parameter can be a value of the enable or disable */
    uint8_t read_en;            /* Specifies the dma read enable
                                    This parameter can be a value of the enable or disable */
}QSPI_DmaInitTypeDef;
#pragma pack(pop) 

/**
* @}
*/

/* Exported functions --------------------------------------------------------*/


/** @defgroup QSPI_Functions_Prototypes QSPI Functions Prototypes
* @{
*/

/**
* @brief  The QSPI initializes control register according to
*         the specified parameters in the QSPI_InitStruct. 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  QSPI_InitStruct: pointer to a QSPI_CtlInitTypeDef
*         structure that contains the configuration information for
*         the control register.
* @retval None
*/
extern void QSPI_Ctl_Init(QSPI_TypeDef* QSPIx, QSPI_CtlInitTypeDef* QSPI_InitStruct);

/**
* @brief  The QSPI uninitializes control register  
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval None
*/
extern void QSPI_Ctl_Uninit(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI gets the send-DMA water level
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval send-DMA water level value
*/
extern uint8_t QSPI_Get_Send_Dma_WaterLevel(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI gets the receive-DMA water level
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval receive-DMA water level value
*/
extern uint8_t QSPI_Get_Receive_Dma_WaterLevel(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI enable send-DMA and sets send-DMA water level
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  water_level: the water_level value is a value between 0 and 7
* @param  NewState: True or False
* @retval None
*/
extern void QSPI_Set_Send_Dma_Cmd(QSPI_TypeDef* QSPIx, uint8_t water_level, FunctionalState NewState);

/**
* @brief  The QSPI enable receive-DMA and sets receive-DMA water level
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  water_level: the water_level value is a value between 0 and 7
* @param  NewState: True or False
* @retval None
*/
extern void QSPI_Set_Receive_Dma_Cmd(QSPI_TypeDef* QSPIx, uint8_t water_level, FunctionalState NewState);

/**
* @brief  The QSPI sets the send-DMA and receive-DMA according to
*         the specified parameters in the QSPI_DmaInitStruct. 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  QSPI_DmaInitStruct: pointer to a QSPI_DmaInitTypeDef
*         structure that contains the configuration information for
*         the DMA register.
* @retval None
*/
extern void QSPI_Set_Dma_Cmd(QSPI_TypeDef* QSPIx, QSPI_DmaInitTypeDef *QSPI_DmaInitStruct);

/**
* @brief  The QSPI gets the SPO value
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_Spo group
*/
extern uint16_t QSPI_Get_Spo(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets the SPO value
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  spo: this can be one value according for the QSPI_Spo group
* @retval None
*/
extern void QSPI_Set_Spo(QSPI_TypeDef* QSPIx, uint16_t spo);

/**
* @brief  The QSPI gets the SPH value
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_Sph group
*/
extern uint16_t QSPI_Get_Sph(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets the SPH value
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  sph: this can be one value according for the QSPI_Sph group
* @retval None
*/
extern void QSPI_Set_Sph(QSPI_TypeDef* QSPIx, uint16_t sph);

/**
* @brief  The QSPI gets instruction mode 
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_InstructionMode group
*/
extern uint16_t QSPI_Get_Instruction_Mode(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets instruction mode 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  mode: this can be one value according for the QSPI_InstructionMode group
* @retval None
*/
extern void QSPI_Set_Instruction_Mode(QSPI_TypeDef* QSPIx, uint16_t mode);

/**
* @brief  The QSPI gets address mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_AddressMode group
*/
extern uint16_t QSPI_Get_Address_Mode(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets address mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  mode: this can be one value according for the QSPI_AddressMode group
* @retval None
*/
extern void QSPI_Set_Address_Mode(QSPI_TypeDef* QSPIx, uint16_t mode);

/**
* @brief  The QSPI gets alternate byte mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_AlternateBytesMode group
*/
extern uint16_t QSPI_Get_Alternatebyte_Mode(QSPI_TypeDef* QSPIx);

/**
* @brief  Set the QSPI alternate byte mode 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  mode: this can be one value according for the QSPI_AlternateBytesMode group
* @retval None
*/
extern void QSPI_Set_Alternatebyte_Mode(QSPI_TypeDef* QSPIx, uint16_t mode);

/**
* @brief  The QSPI gets data mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_DataMode group
*/
extern uint16_t QSPI_Get_Data_Mode(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets data mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  mode: this can be one value according for the QSPI_DataMode group
* @retval None
*/
extern void QSPI_Set_Data_Mode(QSPI_TypeDef* QSPIx, uint16_t mode);

/**
* @brief  The QSPI gets read or write mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_Write_Read_Mode group
*/
extern uint16_t QSPI_Get_Read_Or_Write_Mode(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets read or write mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  mode: this can be one value according for the QSPI_Write_Read_Mode group
* @retval None
*/
extern void QSPI_Set_Read_Or_Write_Mode(QSPI_TypeDef* QSPIx, uint8_t mode);

/**
* @brief  The QSPI gets dummy cycle 
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the dummy cycle value
*/
extern uint16_t QSPI_Get_Dummy_cycle(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets dummy cycle 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  cycle: the cycle is a value between 0 and 31
* @retval None
*/
extern void QSPI_Set_Dummy_cycle(QSPI_TypeDef* QSPIx, uint8_t cycle);

/**
* @brief  The QSPI gets address size
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_AddressSize group
*/
extern uint16_t QSPI_Get_Address_Size(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets address size
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  size: this can be one value according for the QSPI_AddressSize group
* @retval None
*/
extern void QSPI_Set_Address_Size(QSPI_TypeDef* QSPIx, uint16_t size);

/**
* @brief  The QSPI gets alternate byte size
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_AlternateBytesSize group
*/
extern uint16_t QSPI_Get_Alternatebyte_Size(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets alternate byte size
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  size: this can be one value according for the QSPI_AlternateBytesSize group
* @retval None
*/
extern void QSPI_Set_Alternatebyte_Size(QSPI_TypeDef* QSPIx, uint16_t size);

/**
* @brief  The QSPI gets delay time 
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the delay time value
*/
extern uint16_t QSPI_Get_Read_Delay_Time(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets delay time 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  delay_time: the delay_time is a value between 0 and 3
* @retval None
*/
extern void QSPI_Set_Read_Delay_Time(QSPI_TypeDef* QSPIx, uint16_t delay_time);

/**
* @brief  The QSPI gets sample clock
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the one value of QSPI_Sample_Clock_sel group
*/
extern uint16_t QSPI_Get_Sample_Clk(QSPI_TypeDef* QSPIx);

/**
* @brief  Set the QSPI sample clock
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  clk: this can be one value according for the QSPI_Sample_Clock_sel group
* @retval None
*/
extern void QSPI_Set_Sample_Clk(QSPI_TypeDef* QSPIx, uint16_t clk);

/**
* @brief  The QSPI gets the command
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the command value
*/
extern uint8_t QSPI_Get_Instrction(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets the command
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  instrction: the flash command  
* @retval None
*/
extern void QSPI_Set_Instrction(QSPI_TypeDef* QSPIx, uint8_t instrction);

/**
* @brief  The QSPI gets the address
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the address value
*/
extern uint32_t QSPI_Get_Address(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets the address
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  address: the flash address  
* @retval None
*/
extern void QSPI_Set_Address(QSPI_TypeDef* QSPIx, uint32_t address);

/**
* @brief  The QSPI gets alternate byte
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the alternate byte value
*/
extern uint32_t QSPI_Get_Alternatebyte(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets alternate byte
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  alternatebyte: the flash alternate byte  
* @retval None
*/
extern void QSPI_Set_Alternatebyte(QSPI_TypeDef* QSPIx, uint32_t alternatebyte);

/**
* @brief  The QSPI gets data length
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval the data length value
*/
extern uint32_t QSPI_Get_Data_Length(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets data length
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  length: the flash read-or-write length
* @retval None
*/
extern void QSPI_Set_Data_Length(QSPI_TypeDef* QSPIx, uint32_t length);

/**
* @brief  The QSPI sets mask and math value in the polling mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  mask_value: any bit could be masked, 1'b0:mask; 1'b1:don't mask
* @param  match_value: the active value
* @retval None
*/
extern void QSPI_Set_Polling_Configurationo(QSPI_TypeDef* QSPIx, uint8_t mask_value, uint8_t match_value);

/**
* @brief  The QSPI gets the AFIFO status
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval this can be one or more value according for the QSPI_Afifo_Status_Type group
*/
extern uint8_t QSPI_Get_Afifo_Status(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI gets the QSPI status
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval this can be one value according for the QSPI_Status_Type group
*/
extern uint8_t QSPI_Get_Status(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets the QSPI interrupt of the masking
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  int_type: this can be one value according for the QSPI_Int_Type group 
* @retval None
*/
extern void QSPI_Set_Int_Mask(QSPI_TypeDef* QSPIx, uint8_t int_type);

/**
* @brief  The QSPI clears the QSPI interrupt of the clearing
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  int_type: this can be one value according for the QSPI_Int_Type group 
* @retval None
*/
extern void QSPI_Clear_Int_Mask(QSPI_TypeDef* QSPIx, uint8_t int_type);

/**
* @brief  The QSPI gets interrupt status of the masking
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval this can be one or more value according for the QSPI_Int_Type group
*/
extern uint8_t QSPI_Get_Int_Mask_Status(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI gets interrupt status
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval this can be one or more value according for the QSPI_Int_Type group
*/
extern uint8_t QSPI_Get_Int_Pending_Status(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI clears the QSPI interrupt 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  int_type: this can be one value according for the QSPI_Int_Type group 
* @retval None
*/
extern void QSPI_Clear_Int_Pending_Cmd(QSPI_TypeDef* QSPIx, uint8_t int_type);

/**
* @brief  The QSPI sets the QSPI stop mode
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval None
*/
extern void QSPI_Set_Stop_Cmd(QSPI_TypeDef* QSPIx);

/**
* @brief  In memory map mode the read-command 0x03 is used by default.this function can switch the other read-command
          after you finish the configuration of the command.
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval None
*/
extern void QSPI_Set_MemoryMapMode_Command_Switch_Cmd(QSPI_TypeDef* QSPIx);

/**
* @brief  In memory map mode the 1 line mode is used by default.this function can switch to 4 lines mode.
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval None
*/
extern void QSPI_Set_MemoryMapMode_1line_Or_4lines_Cmd(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sets polling mode working
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  polling_config_updata: In polling mode the 1 line mode is used by default.this function can switch to 4 lines mode.
*         you can set none zero value to switch to 4lines mode
* @retval None
*/
extern void QSPI_Set_Polling_Mode_Cmd(QSPI_TypeDef* QSPIx, uint8_t polling_config_updata);

/**
* @brief  The QSPI sets starting mode  
* @param  QSPIx: QSPI base address.@ref QSPI
* @retval None
*/
extern void QSPI_Set_Start_Cmd(QSPI_TypeDef* QSPIx);

/**
* @brief  The QSPI sends the data 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  data: the buffer to send
* @param  length_bytes: the buffer length to send
* @retval send data size
*/
extern int QSPI_Transimit(QSPI_TypeDef* QSPIx, uint32_t *data, int length_bytes);

/**
* @brief  The QSPI receives the data 
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  data: the buffer to receive
* @param  length_bytes: the buffer length to receive
* @retval receive data size
*/
extern int QSPI_Receive(QSPI_TypeDef* QSPIx, uint32_t *data, int length_bytes);

/**
* @brief  The QSPI sends the data by the DMA
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  data: the buffer to send
* @param  length_bytes: the buffer length to send
* @param  dma_channel: the send DMA channel 
* @retval send data size
*/
extern int QSPI_Dma_Transimit(QSPI_TypeDef* QSPIx, uint32_t *data, int length_bytes, uint8_t dma_channel);

/**
* @brief  The QSPI receives the data by the DMA
* @param  QSPIx: QSPI base address.@ref QSPI
* @param  data: the buffer to send
* @param  length_bytes: the buffer length to send
* @param  dma_channel: the receive DMA channel
* @retval receive data size
*/
extern int QSPI_Dma_Receive(QSPI_TypeDef* QSPIx, uint32_t *data, int length_bytes, uint8_t dma_channel);

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
