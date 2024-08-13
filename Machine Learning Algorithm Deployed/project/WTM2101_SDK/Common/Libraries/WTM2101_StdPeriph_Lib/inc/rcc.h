/**
  ******************************************************************************
  * @file    rcc.h
  * @brief   Header for rcc.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __RCC_H__
#define __RCC_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "pmu.h"
#include "WTM2101_RCC_register.h"
#include "WTM2101_PMU_register.h"
/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */


/* Exported constants --------------------------------------------------------*/   

/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup Debounce_Clock_Source_Define Debounce Clock Source Define
  * @brief Debounce Clock Source 
  * @{
  */
#define RCC_DEB_HCLK                       (0U<<RCC_CLK_SEL_DBCLK_SEL_Pos)  /*!< Debounce clock source is HCLK                                 */
#define RCC_DEB_INT10K                     (1U<<RCC_CLK_SEL_DBCLK_SEL_Pos)  /*!< Debounce clock source is the internal 10KHz oscillator clock  */
/**
  * @}
  */

/** @defgroup SysTick_Clock_Source_Define SysTick Clock Source Define
  * @brief SysTick Clock Source 
  * @{
  */
#define RCC_SYSTICK_AHB_DIV8               (0U<<RCC_CLK_SEL_SYSTICK_SEL_Pos)  /*!< SysTick clock from internal AHB clock divided by 8         */
#define RCC_SYSTICK_Int10K                 (1U<<RCC_CLK_SEL_SYSTICK_SEL_Pos)  /*!< SysTick clock from internal 10KHz oscillator clock         */
#define RCC_SYSTICK_Ext32K                 (2U<<RCC_CLK_SEL_SYSTICK_SEL_Pos)  /*!< SysTick clock from external 32KHz crystal clock            */
/**
  * @}
  */

/** @defgroup System_Clock_Source_Define System Clock Source Define
  * @brief System Clock Source 
  * @{
  */
#define RCC_SYSCLK_Int24M                  (0U<<RCC_CLK_SEL_SYSCLK_SEL_Pos)  /*!< Clock source from internal 24MHz oscillator        */
#define RCC_SYSCLK_AUDIO                   (1U<<RCC_CLK_SEL_SYSCLK_SEL_Pos)  /*!< Clock source from AUDIO                            */
#define RCC_SYSCLK_IntPLL                  (2U<<RCC_CLK_SEL_SYSCLK_SEL_Pos)  /*!< Clock source from internal PLL                     */
#define RCC_SYSCLK_Int10K                  (3U<<RCC_CLK_SEL_SYSCLK_SEL_Pos)  /*!< Clock source from internal 10KHz oscillator clock  */
#define RCC_SYSCLK_Ext32K                  (4U<<RCC_CLK_SEL_SYSCLK_SEL_Pos)  /*!< Clock source from external 32KHz crystal clock     */
#define RCC_SYSCLK_Int160K                 (5U<<RCC_CLK_SEL_SYSCLK_SEL_Pos)  /*!< Clock source from internal 160KHz crystal clock    */
#define RCC_SYSCLK_MASK                    RCC_CLK_SEL_SYSCLK_SEL_Msk
/**
  * @}
  */


/** @defgroup SRAM_Access_Mode_Define SRAM Access Mode Define
  * @brief SRAM Access Mode 
  * @{
  */
#define RCC_SRAM_MODE0                     (0U<<RCC_SYS_CFG_MEM_CFG_Pos)  /*!< the SRAM only can be accessed in 0x20000000           */
#define RCC_SRAM_MODE1                     (1U<<RCC_SYS_CFG_MEM_CFG_Pos)  /*!< the SRAM aliased in the boot memory space 0x00000000  */
/**
  * @}
  */

/** @defgroup RCC_Clock_Source_Enable_Define RCC Clock Source Enable Define
  * @brief RCC Clock Source Enable
  * @{
  */
#define RCC_FLASH_CLKEN                    RCC_CLK_EN_FLASH_CLKEN_Msk      /*!< Enable the flash controller clock          */
#define RCC_FLASH_REG_CLKEN                RCC_CLK_EN_FLASH_REG_CLKEN_Msk  /*!< Enable the flash controller regfile clock  */
#define RCC_DMA_CLKEN                      RCC_CLK_EN_DMA_CLKEN_Msk        /*!< Enable the MDA engine clock                */
#define RCC_WDT_PCLKEN                     RCC_CLK_EN_WDT_PCLKEN_Msk       /*!< Enable the whatch dog timer APB clock      */
#define RCC_RTC_PCLKEN                     RCC_CLK_EN_RTC_PCLKEN_Msk       /*!< Enable RTC APB clock                       */
#define RCC_PMU_PCLKEN                     RCC_CLK_EN_PMU_PCLKEN_Msk       /*!< Enable PMU APB clock                       */
#define RCC_UART0_CLKEN                    RCC_CLK_EN_UART0_CLKEN_Msk      /*!< Enable UART0 clock                         */
#define RCC_UART1_CLKEN                    RCC_CLK_EN_UART1_CLKEN_Msk      /*!< Enable UART1 clock                         */
#define RCC_I2C_PCLKEN                     RCC_CLK_EN_I2C_CLKEN_Msk        /*!< Enable I2C APB clock                       */
#define RCC_TIME_CLKEN                     RCC_CLK_EN_TIME_CLKEN_Msk       /*!< Enable Timer APB clock                     */
#define RCC_GPIO_HCLKEN                    RCC_CLK_EN_GPIO_HCLKEN_Msk      /*!< Enable GPIO AHB clock                      */
#define RCC_I2S1_CLKEN                     RCC_CLK_EN_I2S1_CLKEN_Msk       /*!< Enable I2S1 clock                          */
#define RCC_SPIM_PCLKEN                    RCC_CLK_EN_SPIM_CLKEN_Msk       /*!< Enable SPI master APB clock                */
#define RCC_QSPI_PCLKEN                    RCC_CLK_EN_QSPI_CLKEN_Msk       /*!< Enable QSPI clock                          */
#define RCC_PWM0_CLKEN                     RCC_CLK_EN_PWM0_CLKEN_Msk       /*!< Enable PWM0 clock                          */
#define RCC_PWM1_CLKEN                     RCC_CLK_EN_PWM1_CLKEN_Msk       /*!< Enable PWM1 clock                          */
#define RCC_DB_CLKEN                       RCC_CLK_EN_DB_CLKEN_Msk         /*!< Enable Debounce                            */
#define RCC_AUD_CLKEN                      RCC_CLK_EN_AUD_CLKEN_Msk        /*!< Enable Audio clock                         */
#define RCC_FFT_CLKEN                      RCC_CLK_EN_FFT_CLKEN_Msk        /*!< Enable FFT clock                           */
#define RCC_I2S_MCLKEN                     RCC_CLK_EN_I2S_MCLKEN_Msk       /*!< Enable I2S master clock                    */
#define RCC_TRIM_CLKEN                     RCC_CLK_EN_TRIM_CLKEN_Msk       /*!< Enable external flash controller clock     */
#define RCC_AUD_PCLKEN                     RCC_CLK_EN_AUD_PCLKEN_Msk       /*!< Enable audio apb clock                     */
#define RCC_SPIS_PCLKEN                    RCC_CLK_EN_SPIS_CLKEN_Msk       /*!< Enable SPI master APB clock                */
#define RCC_I2S0_CLKEN                     RCC_CLK_EN_I2S0_CLKEN_Msk       /*!< Enable i2s0  clock                         */
#define RCC_DAC_CLKEN                      RCC_CLK_EN_DAC_CLKEN_Msk        /*!< Enable general dac  clock                  */
#define RCC_EXTFLASH_CLKEN                 RCC_CLK_EN_EXFLASH_CLKEN_Msk    /*!< Enable external flash controller clock     */
#define RCC_AHB2_CLKEN                     RCC_CLK_EN_AHB2_CLKEN_Msk       /*!< Enable AHB2 clock                          */
#define RCC_AHB1_CLKEN                     RCC_CLK_EN_AHB1_CLKEN_Msk       /*!< Enable AHB1 clock                          */
#define RCC_APB0_CLKEN                     RCC_CLK_EN_APB0_CLKEN_Msk       /*!< Enable APB0 clock                          */
/**
  * @}
  */


/** @defgroup RCC_Peripheral_Reset_Define RCC Peripheral Reset Define
  * @brief RCC Peripheral Reset
  * @{
  */
#define RCC_FLASH_RSTN                    RCC_RST_EN_FLASH_RSTN_Msk      /*!< Reset the flash controller clock            */
#define RCC_FLASH_REG_RSTN                RCC_RST_EN_FLASH_REG_RSTN_Msk  /*!< Reset the flash controller AHB clock        */
#define RCC_DMA_RSTN                      RCC_RST_EN_DMA_RSTN_Msk        /*!< Reset the MDA                               */
#define RCC_WDT_PRSTN                     RCC_RST_EN_WDT_PRSTN_Msk       /*!< Reset the whatch dog timer                  */
#define RCC_RTC_PRSTN                     RCC_RST_EN_RTC_PRSTN_Msk       /*!< Reset RTC                                   */
#define RCC_PMU_PRSTN                     RCC_RST_EN_PMU_PRSTN_Msk       /*!< Reset PMU APB interface logic               */
#define RCC_UART0_RSTN                    RCC_RST_EN_UART0_RSTN_Msk      /*!< Reset UART0                                 */
#define RCC_UART1_RSTN                    RCC_RST_EN_UART1_RSTN_Msk      /*!< Reset UART1                                 */
#define RCC_I2C_RSTN                      RCC_RST_EN_I2C_RSTN_Msk        /*!< Reset I2C                                   */
#define RCC_TIME0_RSTN                    RCC_RST_EN_TIME0_RSTN_Msk      /*!< Reset Timer 0                               */
#define RCC_TIME1_RSTN                    RCC_RST_EN_TIME1_RSTN_Msk      /*!< Reset Timer 1                               */
#define RCC_TIME2_RSTN                    RCC_RST_EN_TIME2_RSTN_Msk      /*!< Reset Timer 2                               */
#define RCC_TIME3_RSTN                    RCC_RST_EN_TIME3_RSTN_Msk      /*!< Reset Timer 3                               */
#define RCC_GPIO_RSTN                     RCC_RST_EN_GPIO_RSTN_Msk       /*!< Reset GPIO                                  */
#define RCC_I2S1_RSTN                     RCC_RST_EN_I2S1_RSTN_Msk       /*!< Reset I2S                                   */
#define RCC_SPIM_RSTN                     RCC_RST_EN_SPIM_RSTN_Msk       /*!< Reset SPIM                                  */
#define RCC_QSPI_RSTN                     RCC_RST_EN_QSPI_RSTN_Msk       /*!< Reset QSPI                                  */
#define RCC_PWM0_RSTN                     RCC_RST_EN_PWM0_RSTN_Msk       /*!< Reset PWM0                                  */
#define RCC_PWM1_RSTN                     RCC_RST_EN_PWM1_RSTN_Msk       /*!< Reset PWM1                                  */
#define RCC_DB_RSTN                       RCC_RST_EN_DB_RSTN_Msk         /*!< Reset Debounce  logic                       */
#define RCC_AUD_RSTN                      RCC_RST_EN_AUD_RSTN_Msk        /*!< Reset Audio logic                           */
#define RCC_FFT_RSTN                      RCC_RST_EN_FFT_RSTN_Msk        /*!< Reset FFT logic                             */
#define RCC_TRIM_RSTN                     RCC_RST_EN_TRIM_RSTN_Msk       /*!< Reset the clock trim logic                  */
#define RCC_AUD_PRSTN                     RCC_RST_EN_AUD_HRSTN_Msk       /*!< Reset Audio APB register                    */
#define RCC_SPIS_RSTN                     RCC_RST_EN_SPIS_RSTN_Msk       /*!< Reset SPIS                                  */
#define RCC_I2S0_RSTN                     RCC_RST_EN_I2S0_RSTN_Msk       /*!< Reset general I2S                           */
#define RCC_DAC_RSTN                      RCC_RST_EN_DAC_RSTN_Msk        /*!< Reset general DAC                           */
/**
  * @}
  */
  
/**
  * @}
  */

/** @defgroup RCC_Functions_Prototypes RCC Functions Prototypes
  * @{
  */

/**
* @brief  Selected Debounce clock source.
* @param  Deb_Src: Debounce clock source select,This parameter can be one
*         value of @ref Debounce_Clock_Source_Define.
* @retval None
*/
extern void RCC_Deb_Clk_Sel(uint32_t Deb_Src); 

/**
* @brief  Selected SysTick clock source.
* @param  SysTick_Src: SysTick clock source select,This parameter can be one
*         value of @ref SysTick_Clock_Source_Define.
* @retval None
*/
extern void RCC_SysTick_Sel(uint32_t SysTick_Src); 

/**
* @brief  Selected System clock source.
* @param  SYSClk_Src: System clock source select,This parameter can be one
*         value of @ref System_Clock_Source_Define.
* @retval None
*/ 
extern void RCC_SYSClk_Sel(uint32_t SYSClk_Src); 

/**
* @brief  Get System clock frequency.
* @param  None
* @retval System clock frequency value.
*/ 
extern uint32_t RCC_Get_SYSClk(void);

/**
* @brief  Enable or disable the selected clock source.
* @param  CLK_EN: to select the clock source,This parameter can be one 
*         value of @ref RCC_Clock_Source_Enable_Define.
* @param  NewState: ENABLE or DISABLE function.
*         This parameter can be select ENABLE or DISABLE,refer to @ref FunctionalState.
* @retval None
*/
extern void RCC_CLK_EN_Ctl(uint32_t CLK_EN, FunctionalState NewState); 

/**
* @brief  Set HCLK clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_AHB_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get HCLK clock divide number.
* @param  None
* @retval HCLK divide number value.
*/
extern uint8_t RCC_AHB_Get_ClkDiv(void);

/**
* @brief  Set APB0 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-15.
* @retval None
*/
extern void RCC_APB0_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get APB0 clock divide number.
* @param  None
* @retval APB0 divide number value.
*/
extern uint8_t RCC_APB0_Get_ClkDiv(void);

/**
* @brief  Set debounce clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_Deb_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get debounce clock divide number.
* @param  None
* @retval debounce divide number value.
*/
extern uint8_t RCC_Deb_Get_ClkDiv(void);

/**
* @brief  Set FFT clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_FFT_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get FFT clock divide number.
* @param  None
* @retval FFT divide number value.
*/
extern uint8_t RCC_FFT_Get_ClkDiv(void);

/**
* @brief  Set I2S_M clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_I2S_M_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get I2S_M clock divide number.
* @param  None
* @retval I2S_M divide number value.
*/
extern uint8_t RCC_I2S_M_Get_ClkDiv(void);

/**
* @brief  Set I2S0 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-4096.
* @retval None
*/
extern void RCC_I2S0_Set_ClkDiv(uint16_t CLK_Div);

/**
* @brief  Get I2S0 clock divide number.
* @param  None
* @retval I2S0 divide number value.
*/
extern uint16_t RCC_I2S0_Get_ClkDiv(void);

/**
* @brief  Set I2S1 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-4096.
* @retval None
*/
extern void RCC_I2S1_Set_ClkDiv(uint16_t CLK_Div);

/**
* @brief  Get I2S1 clock divide number.
* @param  None
* @retval I2S1 divide number value.
*/
extern uint16_t RCC_I2S1_Get_ClkDiv(void);

/**
* @brief  Set PWM0 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_PWM0_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get PWM0 clock divide number.
* @param  None
* @retval PWM0 divide number value.
*/
extern uint8_t RCC_PWM0_Get_ClkDiv(void);

/**
* @brief  Set PWM1 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255
* @retval None
*/
extern void RCC_PWM1_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get PWM1 clock divide number.
* @param  None
* @retval PWM1 divide number value.
*/
extern uint8_t RCC_PWM1_Get_ClkDiv(void);

/**
* @brief  Set QSPI clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_QSPI_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get QSPI clock divide number.
* @param  None
* @retval QSPI divide number value.
*/
extern uint8_t RCC_QSPI_Get_ClkDiv(void);

/**
* @brief  Set TIMER0 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_TIM0_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get TIMER0 clock divide number.
* @param  None
* @retval TIMER0 divide number value.
*/
extern uint8_t RCC_TIM0_Get_ClkDiv(void);

/**
* @brief  Set TIMER1 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_TIM1_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get TIMER1 clock divide number.
* @param  None
* @retval TIMER1 divide number value.
*/
extern uint8_t RCC_TIM1_Get_ClkDiv(void);

/**
* @brief  Set TIMER2 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_TIM2_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get TIMER2 clock divide number.
* @param  None
* @retval TIMER2 divide number value.
*/
extern uint8_t RCC_TIM2_Get_ClkDiv(void);

/**
* @brief  Set TIMER3 clock divide number.
* @param  CLK_Div: divide number value.
* @note   CLK_Div need between 0-255.
* @retval None
*/
extern void RCC_TIM3_Set_ClkDiv(uint8_t CLK_Div);

/**
* @brief  Get TIMER3 clock divide number.
* @param  None
* @retval TIMER3 divide number value.
*/
extern uint8_t RCC_TIM3_Get_ClkDiv(void);

/**
* @brief  Reset the select peripheral.
* @param  Peri: the select peripheral,This parameter can be one 
*         value of @ref RCC_Peripheral_Reset_Define.
* @retval None
*/
extern void RCC_Peri_Rst(uint32_t Peri); 

/**
* @brief  Set the SRAM mode.
* @param  Mode: the select peripheral,This parameter can be one 
*         value of @ref SRAM_Access_Mode_Define.
* @retval None
*/
extern void RCC_MemCfg(uint32_t Mode);

/**
* @brief  Set dma request0 reuse.
* @param  NewState: The ENABLED status represent the audio channel 1. The DISABLED status represents the uart0 tx
* @retval None
*/
extern void RCC_Config_Dma_Requst0_Reuse(FunctionalState NewState);

/**
* @brief  Set dma request1 reuse.
* @param  NewState: The ENABLED status represent the audio channel 2. The DISABLED status represents the uart0 rx
* @retval None
*/
extern void RCC_Config_Dma_Requst1_Reuse(FunctionalState NewState);

/**
* @brief  Set dma request2 reuse.
* @param  NewState: The ENABLED status represent the audio channel 2. The DISABLED status represents the uart1 tx
* @retval None
*/
extern void RCC_Config_Dma_Requst2_Reuse(FunctionalState NewState);

/**
* @brief  Set dma request3 reuse.
* @param  NewState: The ENABLED status represent the audio channel 1. The DISABLED status represents the uart1 rx
* @retval None
*/
extern void RCC_Config_Dma_Requst3_Reuse(FunctionalState NewState);

/**
* @brief  Get RCC SYSCLK_SELACK state.
* @param  None
* @retval SYSCLK_SELACK state,refer to @ref FlagStatus.
*/
extern FlagStatus RCC_SYSCLK_SELACK_GetStatBit(void);

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */

#define IS_RCC_CLKSRC(SRC)         (((SRC) == RCC_DEB_HCLK)                 ||\
                                    ((SRC) == RCC_DEB_INT10K))   
#define IS_RCC_SYSTICKSRC(SRC)     (((SRC) == RCC_SYSTICK_AHB_DIV8)         ||\
                                    ((SRC) == RCC_SYSTICK_Int10K)           ||\
                                    ((SRC) == RCC_SYSTICK_Ext32K))
#define IS_RCC_SYSCLKSRC(SRC)     (((SRC) == RCC_SYSCLK_Int24M)             ||\
                                    ((SRC) == RCC_SYSCLK_AUDIO)             ||\
                                    ((SRC) == RCC_SYSCLK_IntPLL)            ||\
                                    ((SRC) == RCC_SYSCLK_Int10K)            ||\
                                    ((SRC) == RCC_SYSCLK_Ext32K)            ||\
                                    ((SRC) == RCC_SYSCLK_Int160K))
#define IS_RCC_CLKSRCEN(EN)       (((EN) == RCC_FLASH_CLKEN)                ||\
                                    ((EN) == RCC_FLASH_REG_CLKEN)           ||\
                                    ((EN) == RCC_DMA_CLKEN)                 ||\
                                    ((EN) == RCC_WDT_PCLKEN)                ||\
                                    ((EN) == RCC_RTC_PCLKEN)                ||\
                                    ((EN) == RCC_PMU_PCLKEN)                ||\
                                    ((EN) == RCC_UART0_CLKEN)               ||\
                                    ((EN) == RCC_UART1_CLKEN)               ||\
                                    ((EN) == RCC_I2C_PCLKEN)                ||\
                                    ((EN) == RCC_TIME_CLKEN)                ||\
                                    ((EN) == RCC_GPIO_HCLKEN)               ||\
                                    ((EN) == RCC_I2S1_CLKEN)                ||\
                                    ((EN) == RCC_SPIM_PCLKEN)               ||\
                                    ((EN) == RCC_QSPI_PCLKEN)               ||\
                                    ((EN) == RCC_PWM0_CLKEN)                ||\
                                    ((EN) == RCC_PWM1_CLKEN)                ||\
                                    ((EN) == RCC_DB_CLKEN)                  ||\
                                    ((EN) == RCC_AUD_CLKEN)                 ||\
                                    ((EN) == RCC_FFT_CLKEN)                 ||\
                                    ((EN) == RCC_I2S_MCLKEN)                ||\
                                    ((EN) == RCC_TRIM_CLKEN)                ||\
                                    ((EN) == RCC_AUD_PCLKEN)                ||\
                                    ((EN) == RCC_SPIS_PCLKEN)               ||\
                                    ((EN) == RCC_I2S0_CLKEN)                ||\
                                    ((EN) == RCC_DAC_CLKEN)                 ||\
                                    ((EN) == RCC_EXTFLASH_CLKEN)            ||\
                                    ((EN) == RCC_AHB1_CLKEN)                ||\
                                    ((EN) == RCC_APB0_CLKEN))
#define IS_RCC_CALVAL(VAL)          ((VAL) <= 0x00FFFFFF) 
#define IS_RCC_DIV(DIV)             ((DIV) <= 0x0F)
#define IS_RCC_PERI(PERI)          (((PERI) == RCC_FLASH_RSTN)               ||\
                                    ((PERI) == RCC_FLASH_REG_RSTN)           ||\
                                    ((PERI) == RCC_DMA_RSTN)                 ||\
                                    ((PERI) == RCC_WDT_PRSTN)                ||\
                                    ((PERI) == RCC_RTC_PRSTN)                ||\
                                    ((PERI) == RCC_PMU_PRSTN)                ||\
                                    ((PERI) == RCC_UART0_RSTN)               ||\
                                    ((PERI) == RCC_UART1_RSTN)               ||\
                                    ((PERI) == RCC_I2C_RSTN)                 ||\
                                    ((PERI) == RCC_TIME0_RSTN)               ||\
                                    ((PERI) == RCC_TIME1_RSTN)               ||\
                                    ((PERI) == RCC_TIME2_RSTN)               ||\
                                    ((PERI) == RCC_TIME3_RSTN)               ||\
                                    ((PERI) == RCC_GPIO_RSTN)                ||\
                                    ((PERI) == RCC_I2S1_RSTN)                 ||\
                                    ((PERI) == RCC_SPIM_RSTN)                ||\
                                    ((PERI) == RCC_QSPI_RSTN)                ||\
                                    ((PERI) == RCC_PWM0_RSTN)                ||\
                                    ((PERI) == RCC_PWM1_RSTN)                ||\
                                    ((PERI) == RCC_DB_RSTN)                  ||\
                                    ((PERI) == RCC_AUD_RSTN)                 ||\
                                    ((PERI) == RCC_FFT_RSTN)                 ||\
                                    ((PERI) == RCC_TRIM_RSTN)                ||\
                                    ((PERI) == RCC_AUD_PRSTN)                ||\
                                    ((PERI) == RCC_SPIS_RSTN)                ||\
                                    ((PERI) == RCC_I2S0_RSTN)                ||\
                                    ((PERI) == RCC_DAC_RSTN))
#define IS_RCC_SRAMMODE(MODE)      (((MODE) == RCC_SRAM_MODE0)               ||\
                                    ((MODE) == RCC_SRAM_MODE1))  
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
