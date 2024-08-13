/**
******************************************************************************
* @file    system_stm32f4xx.c
* @author  MCD Application Team
* @version V1.5.0
* @date    06-March-2015
* @brief   CMSIS Cortex-M4 Device Peripheral Access Layer System Source File.
*          This file contains the system clock configuration for STM32F4xx devices.
*
* This file configures the system clock as follows:
*=============================================================================
*                    Supported STM32F42xxx/43xxx devices
*-----------------------------------------------------------------------------
*        System Clock source                    | PLL (HSE)
*-----------------------------------------------------------------------------
*        SYSCLK(Hz)                             | 180000000
*-----------------------------------------------------------------------------
*        HCLK(Hz)                               | 180000000
*-----------------------------------------------------------------------------
*        AHB Prescaler                          | 1
*-----------------------------------------------------------------------------
*        APB1 Prescaler                         | 4
*-----------------------------------------------------------------------------
*        APB2 Prescaler                         | 2
*-----------------------------------------------------------------------------
*        HSE Frequency(Hz)                      | 25000000
*-----------------------------------------------------------------------------
*        PLL_M                                  | 25
*-----------------------------------------------------------------------------
*        PLL_N                                  | 360
*-----------------------------------------------------------------------------
*        PLL_P                                  | 2
*-----------------------------------------------------------------------------
*        PLL_Q                                  | 7
*-----------------------------------------------------------------------------
*        PLLI2S_N                               | NA
*-----------------------------------------------------------------------------
*        PLLI2S_R                               | NA
*-----------------------------------------------------------------------------
*        I2S input clock                        | NA
*-----------------------------------------------------------------------------
*        VDD(V)                                 | 3.3
*-----------------------------------------------------------------------------
*        Main regulator output voltage          | Scale1 mode
*-----------------------------------------------------------------------------
*        Flash Latency(WS)                      | 5
*-----------------------------------------------------------------------------
*        Prefetch Buffer                        | ON
*-----------------------------------------------------------------------------
*        Instruction cache                      | ON
*-----------------------------------------------------------------------------
*        Data cache                             | ON
*-----------------------------------------------------------------------------
*        Require 48MHz for USB OTG FS,          | Disabled
*        SDIO and RNG clock                     |
*-----------------------------------------------------------------------------
*=============================================================================
*
*/

#include "stm32f4xx.h"

/************************* PLL Parameters *************************************/

#define PLL_M 25
//#define PLL_N 360
#define PLL_N 360
#define PLL_P 2
#define PLL_Q 7

void SystemInit_ExtMemCtl(void);

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET 0x00 /*!< Vector Table base offset field. \ \
This value must be a multiple of 0x200. */
/******************************************************************************/

/************************* PLL Parameters *************************************/

/* Everything is defined in "Options for target" inside "Keil uVision" */
/* Settings by Tilen MAJERLE */
#ifdef USE_INTERNAL_RC_CLOCK
/* 16MHz internal RC clock */
uint32_t SystemCoreClock = ((HSI_VALUE / PLL_M) * PLL_N) / PLL_P;
#else
/* External clock */
uint32_t SystemCoreClock = ((HSE_VALUE / PLL_M) * PLL_N) / PLL_P;
#endif

const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/******************************************************************************/

static void SetSysClock(void);

/**
* @brief  Setup the microcontroller system
*         Initialize the Embedded Flash Interface, the PLL and update the
*         SystemFrequency variable.
* @param  None
* @retval None
*/
void SystemInit(void) {
/* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset CFGR register */
  RCC->CFGR = 0x00000000;

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset PLLCFGR register */
  RCC->PLLCFGR = 0x24003010;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;

#if defined(DATA_IN_ExtSRAM) || defined(DATA_IN_ExtSDRAM)
  SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */

  /* Configure the System clock source, PLL Multiplier and Divider factors,
  AHB/APBx prescalers and Flash settings ----------------------------------*/
  SetSysClock();

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif
}

/**
* @brief  Update SystemCoreClock variable according to Clock Register Values.
*         The SystemCoreClock variable contains the core clock (HCLK), it can
*         be used by the user application to setup the SysTick timer or configure
*         other parameters.
*
* @note   Each time the core clock (HCLK) changes, this function must be called
*         to update SystemCoreClock variable value. Otherwise, any configuration
*         based on this variable will be incorrect.
*
* @note   - The system frequency computed by this function is not the real
*           frequency in the chip. It is calculated based on the predefined
*           constant and the selected clock source:
*
*           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
*
*           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
*
*           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**)
*             or HSI_VALUE(*) multiplied/divided by the PLL factors.
*
*         (*) HSI_VALUE is a constant defined in stm32f4xx.h file (default value
*             16 MHz) but the real value may vary depending on the variations
*             in voltage and temperature.
*
*         (**) HSE_VALUE is a constant defined in stm32f4xx.h file (default value
*              25 MHz), user has to ensure that HSE_VALUE is same as the real
*              frequency of the crystal used. Otherwise, this function may
*              have wrong result.
*
*         - The result of this function could be not correct when using fractional
*           value for HSE crystal.
*
* @param  None
* @retval None
*/
void SystemCoreClockUpdate(void) {
  uint32_t tmp = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;

  switch (tmp) {
  case 0x00: /* HSI used as system clock source */
    SystemCoreClock = HSI_VALUE;
    break;
  case 0x04: /* HSE used as system clock source */
    SystemCoreClock = HSE_VALUE;
    break;
  case 0x08: /* PLL P used as system clock source */
    /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
    SYSCLK = PLL_VCO / PLL_P
    */
    pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
    pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;

    if (pllsource != 0) {
      /* HSE used as PLL clock source */
      pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
    } else {
      /* HSI used as PLL clock source */
      pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
    }
    pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 16) + 1) * 2;
    SystemCoreClock = pllvco / pllp;

    break;
  default:
    SystemCoreClock = HSI_VALUE;
    break;
  }
  /* Compute HCLK frequency --------------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK frequency */
  SystemCoreClock >>= tmp;
}

/**
* @brief  Configures the System clock source, PLL Multiplier and Divider factors,
*         AHB/APBx prescalers and Flash settings
* @Note   This function should be called only once the RCC clock configuration
*         is reset to the default reset state (done in SystemInit() function).
* @param  None
* @retval None
*/
static void SetSysClock(void) {
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

#ifndef USE_INTERNAL_RC_CLOCK
  /* Enable HSE */
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);

#ifdef USE_HSE_BYPASS
  /* Enable HSE Bypass */
  RCC->CR |= ((uint32_t)RCC_CR_HSEBYP;
#endif

  /* Wait till HSE is ready and if Time out is reached exit */
  do {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  }while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  /* Check if HSE has started */
  if((RCC->CR & RCC_CR_HSERDY) != RESET) {
    HSEStatus = (uint32_t)0x01;
  }
  else {
    HSEStatus = (uint32_t)0x00;
  }
#endif

  /* Select regulator voltage output Scale 1 mode */
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR |= PWR_CR_VOS;

  /* HCLK = SYSCLK / 1 */
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

  /* PCLK2 = HCLK / 2 */
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

  /* PCLK1 = HCLK / 4 */
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV4;

  /* If HSE is on */
  if (HSEStatus == (uint32_t)0x01) {
    /* Configure the main PLL */
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) - 1) << 16) | (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

    /* Enable the main PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till the main PLL is ready */
    while ((RCC->CR & RCC_CR_PLLRDY) == 0)
      ;

    /* Enable the Over-drive to extend the clock frequency to 180 Mhz */
    PWR->CR |= PWR_CR_ODEN;
    while ((PWR->CSR & PWR_CSR_ODRDY) == 0)
      ;

    PWR->CR |= PWR_CR_ODSWEN;
    while ((PWR->CSR & PWR_CSR_ODSWRDY) == 0)
      ;

    /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;
  }
  else /* Internal RC here */
  {
    /* Configure the main PLL, RC internal source */
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) - 1) << 16) | (PLL_Q << 24);

    /* Enable the main PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till the main PLL is ready */
    while ((RCC->CR & RCC_CR_PLLRDY) == 0)
      ;

    /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_2WS;
  }

  /* Select the main PLL as system clock source */
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= RCC_CFGR_SW_PLL;

  /* Wait till the main PLL is used as system clock source */
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  /* Update system core clock variable */
  SystemCoreClockUpdate();
}
