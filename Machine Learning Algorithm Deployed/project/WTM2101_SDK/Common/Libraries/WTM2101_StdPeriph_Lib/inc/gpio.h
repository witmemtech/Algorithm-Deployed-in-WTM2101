/**
  ******************************************************************************  
  * @file    gpio.h
  * @brief   Header for gpio.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *******************************************************************************  
  */

/** Define to Prevent Recursive Inclusion */
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes */
#include "WTM2101.h"
#include "WTM2101_GPIO_register.h"
#include "WTM2101_RCC_register.h"
#include "WTM2101_PMU_register.h"
/** @addtogroup WITIN_WTM2101_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup GPIO_Exported_Types GPIO Exported Types
  * @{
  */

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
}GPIO_PinState;

/**
  * @brief GPIO interrupt Init Structure Definition
  */
typedef struct
{
    uint32_t Pin;                   /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_Pins_Define */

    uint8_t Trig;                   /*!< Specifies the interrupt trigger mode for the selected pins.
                                       This parameter can be a value of @ref GPIO_Interrupt_Trig_Mode_Define */

    FunctionalState State;          /*!< Interrupt function control.
                                       This parameter can be a value of @ref FunctionalState */

}GPIO_IT_InitTypeDef;

/**
  * @brief GPIO Init Structure Definition
  */
typedef struct
{
    uint32_t Pin;                   /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_Pins_Define */

    uint32_t Mode;                  /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIO_Mode_Define   */

    uint8_t Alternate;              /*!< Peripheral to be connected to the selected pins.
                                       This parameter can be a value of @ref GPIO_Alternate_Function_define */
}GPIO_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
  * @{
  */

/** @defgroup GPIO_Pins_Define GPIO Pins Define
  * @brief GPIO Pins
  * @{
  */
#define GPIO_PIN_0                      0x00000001  /*!< GPIO pin 0          */
#define GPIO_PIN_1                      0x00000002  /*!< GPIO pin 1          */
#define GPIO_PIN_2                      0x00000004  /*!< GPIO pin 2          */
#define GPIO_PIN_3                      0x00000008  /*!< GPIO pin 3          */
#define GPIO_PIN_4                      0x00000010  /*!< GPIO pin 4          */
#define GPIO_PIN_5                      0x00000020  /*!< GPIO pin 5          */
#define GPIO_PIN_6                      0x00000040  /*!< GPIO pin 6          */
#define GPIO_PIN_7                      0x00000080  /*!< GPIO pin 7          */
#define GPIO_PIN_8                      0x00000100  /*!< GPIO pin 8          */
#define GPIO_PIN_9                      0x00000200  /*!< GPIO pin 9          */
#define GPIO_PIN_10                     0x00000400  /*!< GPIO pin 10         */
#define GPIO_PIN_11                     0x00000800  /*!< GPIO pin 11         */
#define GPIO_PIN_12                     0x00001000  /*!< GPIO pin 12         */
#define GPIO_PIN_13                     0x00002000  /*!< GPIO pin 13         */
#define GPIO_PIN_14                     0x00004000  /*!< GPIO pin 14         */
#define GPIO_PIN_15                     0x00008000  /*!< GPIO pin 15         */
#define GPIO_PIN_16                     0x00010000  /*!< GPIO pin 16         */
#define GPIO_PIN_17                     0x00020000  /*!< GPIO pin 17         */
#define GPIO_PIN_18                     0x00040000  /*!< GPIO pin 18         */
#define GPIO_PIN_19                     0x00080000  /*!< GPIO pin 19         */
#define GPIO_PIN_All                    0x000FFFFF  /*!< All pins selected   */
/**
  * @}
  */

/** @defgroup GPIO_Pin_Number GPIO Pin Number Define
  * @brief GPIO Pin Number
  * @{
  */
#define GPIO_NUMBER                     20U
/**
  * @}
  */

/** @defgroup GPIO_Mode_Define GPIO Mode Define
  * @brief GPIO Configuration Mode
  * @{
  */
#define GPIO_MODE_IN                    0U  /*!< Input  Mode           */
#define GPIO_MODE_OUT                   1U  /*!< Output Mode           */
#define GPIO_MODE_INPU                  2U  /*!< Pullup Input Mode     */
#define GPIO_MODE_INPD                  3U  /*!< Pulldown Input Mode   */
#define GPIO_MODE_OUTPU                 4U  /*!< Pullup Output Mode    */
#define GPIO_MODE_OUTPD                 5U  /*!< Pulldown Output Mode  */
/**
  * @}
  */

/** @defgroup GPIO_Interrupt_Trig_Mode_Define GPIO Interrupt Trigger Mode Define
  * @brief GPIO Interrupt Trigger Mode
  * @{
  */
#define GPIO_IT_TRIG_LOW_LEVEL          0U  /*!< Low Level Interrupt Trigger Mode       */
#define GPIO_IT_TRIG_HIGH_LEVEL         1U  /*!< High Level Interrupt Trigger Mode      */
#define GPIO_IT_TRIG_RISING             2U  /*!< Rising Interrupt Trigger Mode          */
#define GPIO_IT_TRIG_FALLING            3U  /*!< Falling Interrupt Trigger Mode         */
#define GPIO_IT_TRIG_RISING_FALLING     4U  /*!< Rising Falling Interrupt Trigger Mode  */
/**
  * @}
  */

/** @defgroup  GPIO_Alternate_Function_define GPIO Alternate Function define
  * @brief GPIO Alternate Function
  * @{
  */
//  GPIO::PAD0
#define GPIO_AF0_GPIO                   0U     /*!< gpio0_out                  */
#define GPIO_AF0_I2S0                   1U     /*!< i2s0_sdo                   */
#define GPIO_AF0_PWM0                   2U     /*!< pwm0_ch0_out               */
#define GPIO_AF0_SPI0                   3U     /*!< spi0_mosi_out/spi0_mosi_in */


//  GPIO::PAD1
#define GPIO_AF1_GPIO                   0U     /*!< gpio1_out                  */
#define GPIO_AF1_I2S0                   1U     /*!< i2s0_lrclk_out             */
#define GPIO_AF1_PWM0                   2U     /*!< pwm0_ch1_out               */
#define GPIO_AF1_SPI0                   3U     /*!< spi0_cs_out                */

//  GPIO::PAD2
#define GPIO_AF2_GPIO                   0U     /*!< gpio2_out                  */
#define GPIO_AF2_I2S0                   1U     /*!< i2s0_sclk_out              */
#define GPIO_AF2_PWM0                   2U     /*!< pwm0_ch2_out               */
#define GPIO_AF2_SPI0                   3U     /*!< spi0_sclk_out              */

//  GPIO::PAD3
#define GPIO_AF3_GPIO                   0U     /*!< gpio3_out                  */
#define GPIO_AF3_I2S0                   1U     /*!< is20_sdi                   */
#define GPIO_AF3_PWM0                   2U     /*!< pwm0_ch3_out               */
#define GPIO_AF3_SPI0                   3U     /*!< spi0_miso_out/spi0_miso_in */

//  GPIO::PAD4
#define GPIO_AF4_GPIO                   0U     /*!< gpio4_out                  */
#define GPIO_AF4_I2C                    1U     /*!< i2c_sda_out/i2c_sda_in     */
#define GPIO_AF4_PDM0                   2U     /*!< TODO: pdm0_clk_out         */
#define GPIO_AF4_UART0                  3U     /*!< uart0_tx                   */

//  GPIO::PAD5
#define GPIO_AF5_GPIO                   0U     /*!< gpio5_out                  */
#define GPIO_AF5_I2C                    1U     /*!< i2c_scl_out                */
#define GPIO_AF5_PDM0                   2U     /*!< TODO: pdm0_datain          */
#define GPIO_AF5_UART0                  3U     /*!< uart0_rx                   */

//  GPIO::PAD6
#define GPIO_AF6_TCK                    0U     /*!< jtag_tck_out               */
#define GPIO_AF6_GPIO                   1U     /*!< gpio6_out                  */
#define GPIO_AF6_UART1                  2U     /*!< uart1_tx_out               */
#define GPIO_AF6_I2S1                   3U     /*!< i2s1_clk_out               */

//  GPIO::PAD7
#define GPIO_AF7_TMS                    0U     /*!< jtag_tms_out               */
#define GPIO_AF7_GPIO                   1U     /*!< gpio7_out                  */
#define GPIO_AF7_UART1                  2U     /*!< uart1_rx_out               */
#define GPIO_AF7_I2S1                   3U     /*!< i2s1_lrclk_out             */

//  GPIO::PAD8
#define GPIO_AF8_TDI                    0U     /*!< jtag_tdi_out               */
#define GPIO_AF8_GPIO                   1U     /*!< gpio8_out                  */
#define GPIO_AF8_SPI0                   2U     /*!< spi0_cs1_out               */
#define GPIO_AF8_PDM1                   3U     /*!< pdm1_clk_out               */

//  GPIO::PAD9
#define GPIO_AF9_TDO                    0U     /*!< jtag_tdo_out               */
#define GPIO_AF9_GPIO                   1U     /*!< gpio9_out                  */
#define GPIO_AF9_I2S                    2U     /*!< i2s1_mclk_out              */
#define GPIO_AF9_PDM1                   3U     /*!< pdm1_datain_out            */

//  GPIO::PAD10
#define GPIO_AF10_GPIO                  0U     /*!< gpio10_out                 */
#define GPIO_AF10_PWM0_BK0              1U     /*!< pwm0_bk0                   */
#define GPIO_AF10_I2S1                  2U     /*!< i2s1_sdo                   */
#define GPIO_AF10_PWM1                  3U     /*!< pwm1_ch0_out               */

//  GPIO::PAD11
#define GPIO_AF11_GPIO                  0U     /*!< gpio11_out                 */
#define GPIO_AF11_PWM0_BK1              1U     /*!< pwm0_bk1                   */
#define GPIO_AF11_I2S1                  2U     /*!< i2s1_sdi                   */
#define GPIO_AF11_PWM1                  3U     /*!< pwm1_ch1_out               */

//  GPIO::PAD12
#define GPIO_AF12_GPIO                  0U     /*!< gpio12_out                 */
#define GPIO_AF12_I2C                   1U     /*!< i2c sda                    */
#define GPIO_AF12_I2S1                  2U     /*!< i2s1_sclk_out              */
#define GPIO_AF12_PWM1                  3U     /*!< pwm1_ch2_out               */

//  GPIO::PAD13
#define GPIO_AF13_GPIO                  0U     /*!< gpio13_out                 */
#define GPIO_AF13_I2C                   1U     /*!< i2c clk                    */
#define GPIO_AF13_I2S1                  2U     /*!< i2s1_lrclk_out             */
#define GPIO_AF13_PWM1                  3U     /*!< pwm1_ch3_out               */

//  GPIO::PAD14
#define GPIO_AF14_GPIO                  0U     /*!< gpio14_out                 */
#define GPIO_AF14_SPIS                  1U     /*!< spi slave cs               */
#define GPIO_AF14_UART1                 2U     /*!< uart1_tx                   */
#define GPIO_AF14_QSPI                  3U     /*!< qspi_csn                   */

//  GPIO::PAD15
#define GPIO_AF15_GPIO                  0U     /*!< gpio15_out                 */
#define GPIO_AF15_SPIS                  1U     /*!< spi slave clk              */
#define GPIO_AF15_UART1                 2U     /*!< uart1_rx                   */
#define GPIO_AF15_QSPI                  3U     /*!< qspi_sck                   */

//  GPIO::PAD16
#define GPIO_AF16_GPIO                  0U     /*!< gpio16_out                 */
#define GPIO_AF16_SPIS                  1U     /*!< spi slave mosi             */
#define GPIO_AF16_UART0                 2U     /*!< uart0_tx                   */
#define GPIO_AF16_QSPI                  3U     /*!< qspi_io0                   */

//  GPIO::PAD17
#define GPIO_AF17_GPIO                  0U     /*!< gpio17_out                 */
#define GPIO_AF17_SPIS                  1U     /*!< spi slave miso             */
#define GPIO_AF17_UART0                 2U     /*!< uart0_rx                   */
#define GPIO_AF17_QSPI                  3U     /*!< qspi_io1                   */

//  GPIO::PAD18
#define GPIO_AF18_GPIO                  0U     /*!< gpio18_out                 */
#define GPIO_AF18_PWM0_BK2              1U     /*!< pwm0_bk2                   */
#define GPIO_AF18_I2S                   2U     /*!< i2s_mclk                   */
#define GPIO_AF18_QSPI                  3U     /*!< qspi_io2                   */

//  GPIO::PAD19
#define GPIO_AF19_GPIO                  0U     /*!< gpio19_out                 */
#define GPIO_AF19_PWM0_BK3              1U     /*!< pwm0_bk3                   */
#define GPIO_AF19_SPI0                  2U     /*!< spi master cs2             */
#define GPIO_AF19_QSPI                  3U     /*!< qspi_io3                   */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIO_Functions_Prototypes GPIO Functions Prototypes
  * @{
  */
/* Initialization and Configuration functions *********************************/

/**
* @brief  Initializes the GPIOx peripheral according to
*         the specified parameters in the GPIO_InitStruct.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
*         the configuration information for the specified GPIO peripheral.
* @retval None
*/
extern void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);

/**
* @brief  Set the GPIOx peripheral open drain function.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bits to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19) or GPIO_PIN_All,refer to @ref GPIO_Pins_Define.
* @param  NewState: ENABLE or DISABLE function
*         This parameter can be select ENABLE or DISABLE,refer to @ref FunctionalState.
* @retval None
*/
extern void GPIO_OD_Set(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState NewState);

/**
* @brief  The GPIO init structure parameters values set as default.
* @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
*         the configuration information for the specified GPIO peripheral.
* @retval None
*/
extern void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);

/**
* @brief  De-initializes the GPIOx peripheral registers to their default
*         reset values.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bit to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19) or GPIO_PIN_All,refer to @ref GPIO_Pins_Define.
* @retval None
*/
extern void GPIO_DeInit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Configure the selected GPIO Pins debounce function.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bits to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19) or GPIO_PIN_All,refer to @ref GPIO_Pins_Define.
* @param  NewState: ENABLE or DISABLE function
*         This parameter can be select ENABLE or DISABLE,refer to @ref FunctionalState.
* @retval None
*/
extern void GPIO_DebounceCfg(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState NewState);

/* IO operation functions *****************************************************/

/**
* @brief  Output High Level on the selected GPIO Pins.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bits to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19) or GPIO_PIN_All,refer to @ref GPIO_Pins_Define.
* @retval None
*/
extern void GPIO_OutputHi(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Output Low Level on the selected GPIO Pins.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bits to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19) or GPIO_PIN_All,refer to @ref GPIO_Pins_Define.
* @retval None
*/
extern void GPIO_OutputLo(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Toggle the specified GPIO pins.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bits to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19) or GPIO_PIN_All,refer to @ref GPIO_Pins_Define.
* @retval None
*/
extern void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Read the specified input port pin.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bits to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19),refer to @ref GPIO_Pins_Define.
* @retval The input port pin state,refer to @ref GPIO_PinState.
*/
extern GPIO_PinState GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Read all input port pins.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @retval The input port pins value.
*/
extern uint32_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);

/**
* @brief  Read the specified output port pin.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bits to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19),refer to @ref GPIO_Pins_Define.
* @retval The output port pin state,refer to @ref GPIO_PinState.
*/
extern GPIO_PinState GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Read all output port pins.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @retval The output port pins value.
*/
extern uint32_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);

/* INT Initialization and Configuration functions *****************************/

/**
* @brief  Configure the selected GPIO Pins interrupt function.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_IT_InitStruct: pointer to a GPIO_IT_InitTypeDef structure that contains
*         the configuration information for the specified GPIO interrupt function.
* @retval None
*/
extern void GPIO_IT_Cfg(GPIO_TypeDef* GPIOx, GPIO_IT_InitTypeDef* GPIO_IT_InitStruct);

/**
* @brief  Configure the GPIO interrupt mask function.
* @param  NewState: ENABLE or DISABLE function
*         This parameter can be select ENABLE or DISABLE,refer to @ref FunctionalState.
* @retval None
*/
extern void GPIO_IT_MskCfg(FunctionalState NewState);

/**
* @brief  Configure the selected GPIO Pins interrupt mask function.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bits to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19) or GPIO_PIN_All,refer to @ref GPIO_Pins_Define.
* @param  NewState: ENABLE or DISABLE function
*         This parameter can be select ENABLE or DISABLE,refer to @ref FunctionalState.
* @retval None
*/
extern void GPIO_IT_PinMskCfg(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState NewState);

/**
* @brief  Configure all level-sensitive interrupts synchronized to pclk_intr.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  NewState: ENABLE or DISABLE function
*         This parameter can be select ENABLE or DISABLE,refer to @ref FunctionalState.
* @retval None
*/
extern void GPIO_IT_SyncLvCfg(GPIO_TypeDef* GPIOx, FunctionalState NewState);

/**
* @brief  Get the selected GPIO Pin interrupt state.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bit to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19),refer to @ref GPIO_Pins_Define.
* @retval The selected pin interrupt state,refer to @ref ITStatus.
*/
extern ITStatus GPIO_IT_GetStatBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Get the selected GPIO Pin raw interrupt state.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @param  GPIO_Pin: specifies the port bit to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19),refer to @ref GPIO_Pins_Define.
* @retval The selected pin raw interrupt state,refer to @ref ITStatus.
*/
extern ITStatus GPIO_IT_GetRAWStatBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Get all GPIO Pins raw interrupt status.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @retval The selected pins raw interrupt status.
*/
extern uint32_t GPIO_IT_GetRAWStat(GPIO_TypeDef* GPIOx);

/**
* @brief  Clear the selected GPIO Pins interrupt status
*         just effective for edge-detected interrupts.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @note   Just be used for edge-detected interrupts.
* @param  GPIO_Pin: specifies the port bit to be written
*         This parameter can be in value of GPIO_PIN_x where x can be (0..19) or GPIO_PIN_All,refer to @ref GPIO_Pins_Define.
* @retval None
*/
extern void GPIO_IT_ClrPending(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Clear the selected GPIO Pins wakeup interrupt Status
* @param  GPIOx: to select the GPIO peripheral, where x can only be A now.
* @note
* @param  GPIO_Pin: specifies the port bit to be written.
*         This parameter can be one of GPIO_PIN_x where x can be (0..19).
* @retval None
*/
extern void GPIO_IT_ClrWakeUpPending(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
* @brief  Get all GPIO Pins wakeup status.
* @param  GPIOx: where x can only be A to select the GPIO peripheral.
* @note
* @retval The wakeup pins value.
*/
extern uint32_t GPIO_IT_GetWakeupStat(GPIO_TypeDef* GPIOx);
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define IS_GPIO_PIN(PIN)            (((PIN) & GPIO_PIN_All ) != 0x00U)
#define IS_GPIO_MODE(MODE)          (((MODE) == GPIO_MODE_IN)        ||\
                                    ((MODE) == GPIO_MODE_OUT)        ||\
                                    ((MODE) == GPIO_MODE_INPU)       ||\
                                    ((MODE) == GPIO_MODE_INPD))

#define IS_GPIO_ALT(ALT)            (((ALT) == GPIO_AF0_GPIO)        ||\
                                    ((ALT) == GPIO_AF0_I2S0)         ||\
                                    ((ALT) == GPIO_AF0_PWM0)         ||\
                                    ((ALT) == GPIO_AF0_SPI0)         ||\
                                    ((ALT) == GPIO_AF1_GPIO)         ||\
                                    ((ALT) == GPIO_AF1_I2S0)         ||\
                                    ((ALT) == GPIO_AF1_PWM0)         ||\
                                    ((ALT) == GPIO_AF1_SPI0)         ||\
                                    ((ALT) == GPIO_AF2_GPIO)         ||\
                                    ((ALT) == GPIO_AF2_I2S0)         ||\
                                    ((ALT) == GPIO_AF2_PWM0)         ||\
                                    ((ALT) == GPIO_AF2_SPI0)         ||\
                                    ((ALT) == GPIO_AF3_GPIO)         ||\
                                    ((ALT) == GPIO_AF3_I2S0)         ||\
                                    ((ALT) == GPIO_AF3_PWM0)         ||\
                                    ((ALT) == GPIO_AF3_SPI0)         ||\
                                    ((ALT) == GPIO_AF4_GPIO)         ||\
                                    ((ALT) == GPIO_AF4_I2C)          ||\
                                    ((ALT) == GPIO_AF4_PDM0)         ||\
                                    ((ALT) == GPIO_AF4_UART0)        ||\
                                    ((ALT) == GPIO_AF5_GPIO)         ||\
                                    ((ALT) == GPIO_AF5_I2C)          ||\
                                    ((ALT) == GPIO_AF5_PDM0)         ||\
                                    ((ALT) == GPIO_AF5_UART0)        ||\
                                    ((ALT) == GPIO_AF10_GPIO)        ||\
                                    ((ALT) == GPIO_AF10_EXFLASH)     ||\
                                    ((ALT) == GPIO_AF10_I2S1)        ||\
                                    ((ALT) == GPIO_AF10_PWM1)        ||\
                                    ((ALT) == GPIO_AF11_GPIO)        ||\
                                    ((ALT) == GPIO_AF11_EXFLASH)     ||\
                                    ((ALT) == GPIO_AF11_I2S1)        ||\
                                    ((ALT) == GPIO_AF11_PWM1)        ||\
                                    ((ALT) == GPIO_AF12_GPIO)        ||\
                                    ((ALT) == GPIO_AF12_EXFLASH)     ||\
                                    ((ALT) == GPIO_AF12_I2S1)        ||\
                                    ((ALT) == GPIO_AF12_PWM1)        ||\
                                    ((ALT) == GPIO_AF13_GPIO)        ||\
                                    ((ALT) == GPIO_AF13_EXFLASH)     ||\
                                    ((ALT) == GPIO_AF13_I2S1)        ||\
                                    ((ALT) == GPIO_AF13_PWM1)        ||\
                                    ((ALT) == GPIO_AF14_GPIO)        ||\
                                    ((ALT) == GPIO_AF14_I2C)         ||\
                                    ((ALT) == GPIO_AF14_UART1)       ||\
                                    ((ALT) == GPIO_AF14_QSPI)        ||\
                                    ((ALT) == GPIO_AF15_GPIO)        ||\
                                    ((ALT) == GPIO_AF15_I2C)         ||\
                                    ((ALT) == GPIO_AF15_UART1)       ||\
                                    ((ALT) == GPIO_AF15_QSPI)        ||\
                                    ((ALT) == GPIO_AF16_GPIO)        ||\
                                    ((ALT) == GPIO_AF16_PWM0)        ||\
                                    ((ALT) == GPIO_AF16_UART0)       ||\
                                    ((ALT) == GPIO_AF16_QSPI)        ||\
                                    ((ALT) == GPIO_AF17_GPIO)        ||\
                                    ((ALT) == GPIO_AF17_PWM0)        ||\
                                    ((ALT) == GPIO_AF17_UART0)       ||\
                                    ((ALT) == GPIO_AF17_QSPI)        ||\
                                    ((ALT) == GPIO_AF18_GPIO)        ||\
                                    ((ALT) == GPIO_AF18_PWM0)        ||\
                                    ((ALT) == GPIO_AF18_I2S)         ||\
                                    ((ALT) == GPIO_AF18_QSPI)        ||\
                                    ((ALT) == GPIO_AF19_GPIO)        ||\
                                    ((ALT) == GPIO_AF19_PWM0)        ||\
                                    ((ALT) == GPIO_AF19_QSPI))

#define IS_GPIO_TRIG(TRIG)          (((TRIG) == GPIO_IT_TRIG_LOW_LEVEL)    ||\
                                    ((TRIG) == GPIO_IT_TRIG_HIGH_LEVEL)    ||\
                                    ((TRIG) == GPIO_IT_TRIG_RISING)        ||\
                                    ((TRIG) == GPIO_IT_TRIG_FALLING)       ||\
                                    ((TRIG) == GPIO_IT_TRIG_RISING_FALLING))
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
