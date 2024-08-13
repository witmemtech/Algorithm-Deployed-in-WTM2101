/**
  ******************************************************************************  
  * @file    fbank.h
  * @brief   Header for fbank.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  * 
  *******************************************************************************  
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __FBANK_H__
#define __FBANK_H__

#ifdef  __cplusplus
extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "stddef.h"
#include "WTM2101_FBANK_register.h"

/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup FBANK
  * @{
  */

/* Exported constants --------------------------------------------------------*/
 
/** @defgroup FBANK_Exported_Constants
  * @{
  */

/** @defgroup Fbank_Mode_Typedef
* @{
*/
#define  DATA_SRAM_SEL          (FBANK_FBANK_CONTROL_FBANK_DATA_RAM_SEL_Msk)     /*select the fbank data sram source.disabled:fbank;enaled:AHB*/
#define  SRAM_ADDR_SEL          (FBANK_FBANK_CONTROL_SRAM_ADDR_SEL_Msk)          /*when AHB SRAM visit the fbank data sram,it select the address order.disabled:positive order;enabled:inverted order*/
#define  FBANK_SRC_SEL          (FBANK_FBANK_CONTROL_FBANK_SRC_SEL_Msk)          /*fbank initial data and start signal source£¬1'b0:ahb bus; 1'b1:audio*/
#define  FFT_ENABLE             (FBANK_FBANK_CONTROL_FFT_ENABLE_Msk)             /*fbank enable signal*/
#define  IFFT_ENABLE            (FBANK_FBANK_CONTROL_IFFT_ENABLE_Msk)            /*ifbank enable signal*/
#define  MELFILTER_ENABLE       (FBANK_FBANK_CONTROL_MELFILTER_ENABLE_Msk)       /*mel filter enable signal*/
#define  SQRT_ENABLE            (FBANK_FBANK_CONTROL_SQRT_ENABLE_Msk)            /*sqrt enable signal*/
#define  LOG_ENABLE             (FBANK_FBANK_CONTROL_LOG_ENABLE_Msk)             /*log enable signal*/
#define  DO_WINDOW              (FBANK_FBANK_CONTROL_DO_WINDOW_Msk)              /*adding window operation in biteverse mode*/
#define  DO_BITREVERSE          (FBANK_FBANK_CONTROL_DO_BITREVERSE_Msk)          /*data reverse enable signal in ram*/
#define  DO_CFFT_HCLK           (FBANK_FBANK_CONTROL_DO_CFFT_HCLK_Msk)           /*do the 256 points complex number fbank*/
#define  DO_RFFT_HCLK           (FBANK_FBANK_CONTROL_DO_RFFT_HCLK_Msk)           /*do the 512 points real number fbank*/
#define  IS_FBANK_MODE(MODE)   (((MODE) == DATA_SRAM_SEL)    || \
                                ((MODE) == SRAM_ADDR_SEL)    || \
                                ((MODE) == FBANK_SRC_SEL)    || \
                                ((MODE) == FFT_ENABLE)       || \
                                ((MODE) == IFFT_ENABLE)      || \
                                ((MODE) == MELFILTER_ENABLE) || \
                                ((MODE) == SQRT_ENABLE)      || \
                                ((MODE) == LOG_ENABLE)       || \
                                ((MODE) == DO_WINDOW)        || \
                                ((MODE) == DO_BITREVERSE)    || \
                                ((MODE) == DO_CFFT_HCLK)     || \
                                ((MODE) == DO_RFFT_HCLK)) 
/**
* @}
*/

/** @defgroup Fbank_Source_Data_Length_Typedef
* @{
*/
#define  FBANK_DATA_LENGTH_200          (0x00)
#define  FBANK_DATA_LENGTH_160          (0x01)
#define  FBANK_DATA_LENGTH_240          (0x02)
#define  FBANK_DATA_LENGTH_256          (0x03)
#define  IS_FBANK_DATA_LENGTH(LENGTH)   (((LENGTH) == FBANK_DATA_LENGTH_200) || \
                                        ((LENGTH) == FBANK_DATA_LENGTH_160)  || \
                                        ((LENGTH) == FBANK_DATA_LENGTH_240)  || \
                                        ((LENGTH) == FBANK_DATA_LENGTH_256))
/**
* @}
*/

/** @defgroup Fbank_Interrupt_Typedef
* @{
*/
#define  FBANK_INT                      (FBANK_INT_MASK_FBANK_DONE_MASK_Msk)
#define  FBANK_FOR_FFT_INT              (FBANK_INT_MASK_FFT_DONE_MASK_Msk)
#define  FBANK_FOR_IFFT_INT             (FBANK_INT_MASK_IFFT_DONE_MASK_Msk)
#define  FBANK_MELFILTER_INT            (FBANK_INT_MASK_MELFILTER_DONE_MASK_Msk)
#define  FBANK_SQRT_INT                 (FBANK_INT_MASK_SQRT_DONE_MASK_Msk)
#define  FBANK_LOG_INT                  (FBANK_INT_MASK_LOG_DONE_MASK_Msk)
#define  IS_FBANK_INTERRUPT(INT)        (((INT) == FBANK_INT)          || \
                                        ((INT) == FBANK_FOR_FFT_INT)   || \
                                        ((INT) == FBANK_FOR_IFFT_INT)  || \
                                        ((INT) == FBANK_MELFILTER_INT) || \
                                        ((INT) == FBANK_SQRT_INT)      || \
                                        ((INT) == FBANK_LOG_INT))   
/**
* @}
*/

/**
* @}
*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup FBANK_Functions_Prototypes FBANK Functions Prototypes
* @{
*/

/**
* @brief  Fbank set enabled command
* @param  fbank: fbank base address
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void FBANK_Enable_Cmd(FBANK_TypeDef *fbank, FunctionalState NewState);

/**
* @brief  Fbank set control operation
* @param  fbank: fbank base address
* @param  ctl: This parameter can be one or more value of @ref Fbank_Mode_Typedef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void FBANK_Ctl_Cmd(FBANK_TypeDef *fbank, uint32_t ctl, FunctionalState NewState);

/**
* @brief  Fbank set data length
* @param  fbank: fbank base address
* @param  length: This parameter can be only one value of @ref Fbank_Source_Data_Length_Typedef
* @retval None
*/
extern void FBANK_Set_Data_Length(FBANK_TypeDef *fbank, uint8_t length);

/**
* @brief  Fbank Clear interrupt
* @param  fbank: fbank base address
* @param  int_type: This parameter can be one or more value of @ref Fbank_Interrupt_Typedef
* @retval None
*/
extern void FBANK_Clear_Interrupt_Cmd(FBANK_TypeDef *fbank, uint8_t int_type);

/**
* @brief  Fbank set interrupt
* @param  fbank: fbank base address
* @param  int_type: This parameter can be one or more value of @ref Fbank_Interrupt_Typedef
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
extern void FBANK_Set_Interrupt_Cmd(FBANK_TypeDef *fbank, uint8_t int_type, FunctionalState NewState);

/**
* @brief  Fbank get audio sram status
* @param  fbank: fbank base address
* @retval ENABLE or DISABLE
*/
extern FunctionalState FBANK_Read_Audio_Sram_Status(FBANK_TypeDef *fbank);

/**
* @brief  Fbank write Sram data
* @param  fbank: fbank base address
* @param  data: the data to write into fbank sram
* @retval None
*/
extern void FBANK_Write_Sram_Data(FBANK_TypeDef *fbank, uint32_t *data, int len);

/**
* @brief  Fbank read Sram data
* @param  fbank: fbank base address
* @param  data: the data to read into fbank sram
* @retval None
*/
extern void FBANK_Read_Sram_Data(FBANK_TypeDef *fbank, uint32_t *data, int len);

/**
* @brief  Fbank write Sram data
* @param  fbank: fbank base address
* @param  data: the data to write into fbank sram
* @retval None
*/
extern void FBANK_Write_Sram_Data_CP(FBANK_TypeDef *fbank,uint32_t *data,int len);

/**
* @brief  Fbank read Sram data
* @param  fbank: fbank base address
* @param  data: the data to read into fbank sram
* @retval None
*/
extern void FBANK_Read_Sram_Data_CP(FBANK_TypeDef *fbank,uint32_t *data,int len);

/**
* @brief  Fbank read Sram data
* @param  fbank: fbank base address
* @param  data: the data to read into fbank sram
* @retval None
*/
extern void FBANK_Read_Sram_Data_CP2(FBANK_TypeDef *fbank,uint32_t *data,int len);

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
