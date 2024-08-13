/**
  ******************************************************************************
  * @file    WTM2101.h
  * @brief   Header for WTM2101.h module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

/** @addtogroup WITIN_WTM2101_AI_CHIP
* @{
*/

#ifndef __WTM2101_H__
#define __WTM2101_H__

#ifdef __cplusplus
extern "C" {
#endif

  /** @addtogroup Configuration_of_RISC-V_Core
  * @{
  */

#include <nmsis_compiler.h>
  
  /** @addtogroup Configuration_of_RISC-V_Core
  * @{
  */
  
  /** Interrupt Number Definition */
  /**
  *     N307 Interrupt Tree
  *                            +-------+
  *                            | ECLIC |     +----+
  *         ext_irq[..] -----> |...... | --> |N307|
  *         ext_irq[1] ------> |20     |     +----+
  *         ext_irq[0] ------> |19     |
  *                            |18     |
  *                            |...... |
  *                            |9      |
  *           +-----+ tickirq  |8      |
  *           |     | -------> |7      |
  *           |     |          |6      |
  *           |Timer|          |5      |
  *           |     | softirq  |4      |
  *           |     | -------> |3      |
  *           +-----+          |2      |
  *                            |1      |
  *                            |0      |
  *                            +-------+
  * 
  */
  typedef enum IRQn
  {
    /* ========================================  Nuclei N/NX Specific Interrupt Numbers  ========================================= */
    Reserved0_IRQn                  =   0,          /*!< Internal reserved         */
    Reserved1_IRQn                  =   1,          /*!< Internal reserved         */
    Reserved2_IRQn                  =   2,          /*!< Internal reserved         */
    SysTimerSW_IRQn                 =   3,          /*!< System Timer SW interrupt */
    Reserved3_IRQn                  =   4,          /*!< Internal reserved         */
    Reserved4_IRQn                  =   5,          /*!< Internal reserved         */
    Reserved5_IRQn                  =   6,          /*!< Internal reserved         */
    SysTimer_IRQn                   =   7,          /*!< System Timer Interrupt    */
    Reserved6_IRQn                  =   8,          /*!< Internal reserved         */
    Reserved7_IRQn                  =   9,          /*!< Internal reserved         */
    Reserved8_IRQn                  =  10,          /*!< Internal reserved         */
    Reserved9_IRQn                  =  11,          /*!< Internal reserved         */
    Reserved10_IRQn                 =  12,          /*!< Internal reserved         */
    Reserved11_IRQn                 =  13,          /*!< Internal reserved         */
    Reserved12_IRQn                 =  14,          /*!< Internal reserved         */
    Reserved13_IRQn                 =  15,          /*!< Internal reserved         */
    Reserved14_IRQn                 =  16,          /*!< Internal reserved         */
    Reserved15_IRQn                 =  17,          /*!< Internal reserved         */
    Reserved16_IRQn                 =  18,          /*!< Internal reserved         */
    
    /******  WTM2101 External Interrupt Numbers ************************************************************/
    GPIO_WAKEUP_IRQn                = 19,           /*!< GPIO WAKEUP Interrupt     */
    WDG_IRQn                        = 20,           /*!< WATCH DOG Interrupt       */
    RTC_IRQn                        = 21,           /*!< RTC Interrupt             */
    FLASH_IRQn                      = 22,           /*!< FLASH Interrupt           */
    UART0_IRQn                      = 23,           /*!< UART0 Interrupt           */
    UART1_IRQn                      = 24,           /*!< UART1 Interrupt           */
    TIMER0_IRQn                     = 25,           /*!< TIMER1 Interrupt          */
    TIMER1_IRQn                     = 26,           /*!< TIMER2 Interrupt          */
    TIMER2_IRQn                     = 27,           /*!< TIMER3 Interrupt          */
    TIMER3_IRQn                     = 28,           /*!< TIMER4 Interrupt          */
    I2C_IRQn                        = 29,           /*!< I2C Interrupt             */
    I2S0_IRQn                       = 30,           /*!< I2S0 Interrupt            */
    SPIM_IRQn                       = 31,           /*!< SPI  Master Interrupt     */
    QSPI_IRQn                       = 32,           /*!< QSPI Interrupt            */
    PWM0_IRQn                       = 33,           /*!< PWM0 Interrupt            */
    PWM1_IRQn                       = 34,           /*!< PWM1 Interrupt            */
    DMA_IRQn                        = 35,           /*!< DMA Interrupt             */
    NPU_IRQn                        = 36,           /*!< NPU Interrupt             */
    AUDIO_IRQn                      = 37,           /*!< AUDIO Interrupt           */
    VAD_IRQn                        = 38,           /*!< VAD  Interrupt            */
    FBANK_IRQn                      = 39,           /*!< FBANK Interrupt           */
    AFC320K_IRQn                    = 40,           /*!< AFC 320k Interrupt        */
    GPIO_IRQn                       = 41,           /*!< GPIO Interrupt            */
    I2S1_IRQn                       = 42,           /*!< I2S1 Interrupt            */
    SPIS_IRQn                       = 43,           /*!< SPI Slave Interrupt       */
    AFC24MK_IRQn                    = 44,           /*!< AFC 24M Interrupt         */
    RESERVED1                       = 45,           /*!< Reserved1 Interrupt       */
    RESERVED2                       = 46,           /*!< Reserved2 Interrupt       */
    RESERVED3                       = 47,           /*!< Reserved3 Interrupt       */
    TE_IRQn                         = 48,           /*!< Te Interrupt              */
    TE_CRIT_IRQn                    = 49,           /*!< Te Ceit Interrupt         */
    IDLE_IRQn                       = 50,           /*!< Idle Interrupt            */
    SOC_INT_MAX,
  } IRQn_Type;
  
  /** Processor and Core Peripheral Section */
  
  /* Configuration of the RISC-V Processor and Core Peripherals */
#ifndef __RV_REV
#define __RV_REV                        0x0000          /*!< RISC-V Core Revision */
#endif

#ifndef __MPU_PRESENT
#define __MPU_PRESENT                   0
#endif

#ifndef __DSP_PRESENT
#define __DSP_PRESENT                   0
#endif

#ifndef __ECLIC_PRESENT
#define __ECLIC_PRESENT                 1
#endif

#ifndef __SYSTIMER_PRESENT
#define __SYSTIMER_PRESENT              1
#endif

#ifndef __Vendor_SysTickConfig
#define __Vendor_SysTickConfig          0
#endif

#ifndef __Nlbit_PRIO_BITS
#define __Nlbit_PRIO_BITS               4
#endif

#ifndef __REV_A
#define __REV_A  0x01
#endif

#ifndef __REV_B
#define __REV_B  0x11
#endif
extern uint32_t __WTM2101_RevID;
  /**
  *@}
  */ /* End of group Configuration_of_RV_Core */

  
  /** @addtogroup Device_Peripheral_Registers
  * @{
  */
  
  /** Device Specific Peripheral Registers Structures */
  
  /**
  * @brief Port A
  */
  typedef struct
  {
    __IO uint32_t ODR;                            /*!< Port A Data Output Register,                                                Address offset:0x00        */
    __IO uint32_t DDR;                            /*!< Port A Data Direction Register,                                             Address offset:0x04        */
    __IO uint32_t DRV0;                           /*!< Port A Drv0 Register,                                                       Address offset:0x08        */
    __IO uint32_t DRV1;                           /*!< Port A Drv1 Register,                                                       Address offset:0x0C        */
    __IO uint32_t PAD_RESV;                       /*!< Port A Pad Resv Register,                                                   Address offset:0x10        */
    __IO uint32_t WAKEUP;                         /*!< Port A GPIO Wakeup Register,                                                Address offset:0x14        */
    __IO uint32_t WAKEUP_EOI;                     /*!< Port A GPIO Wakeup eoi Register,                                            Address offset:0x18        */
    __IO uint32_t TEST_PORT;                      /*!< Port A GPIO Test Port Register,                                             Address offset:0x1C        */
    __I  uint32_t RESERVED0[4];                   /*!< Reserved,                                                                   Address offset:0x20 - 0x2F */
    __IO uint32_t INTEN;                          /*!< Port A Interrupt Enable Register,                                           Address offset:0x30        */
    __IO uint32_t INTMSK;                         /*!< Port A Interrupt Mask Register,                                             Address offset:0x34        */
    __IO uint32_t INTTYP;                         /*!< Port A Interrupt Trig Type Register,                                        Address offset:0x38        */
    __IO uint32_t INTPOL;                         /*!< Port A Interrupt Trig Polarity Register,                                    Address offset:0x3C        */
    __I  uint32_t INTSTA;                         /*!< Port A Interrupt Status Register,                                           Address offset:0x40        */
    __I  uint32_t INTRSTA;                        /*!< Port A Interrupt Raw Status Register,                                       Address offset:0x44        */
    __IO uint32_t INTDEB;                         /*!< Port A Interrupt Trig Debounce Enable Register,                             Address offset:0x48        */
    __O  uint32_t INTCLR;                         /*!< Port A Interrupt (Edge-Type) Clear Register,                                Address offset:0x4C        */
    __IO uint32_t EXT_PORTA;                      /*!< Port A Data Input Register,                                                 Address offset:0x50        */
    __I  uint32_t RESERVED1[3];                   /*!< Reserved,                                                                   Address offset:0x54 - 0x5F */
    __IO uint32_t INTSYNC;                        /*!< Port A Interrupt (Level-Type) Internal CLK Synchronization Enable Register, Address offset:0x60        */
    __I  uint32_t ID_CODE;                        /*!< Port A Id Code,                                                             Address offset:0x64        */
    __IO uint32_t INTEDG;                         /*!< Port A Interrupt Dual-Edge Trig Enable Register,                            Address offset:0x68        */
    __I  uint32_t VER_ID_CODE;                    /*!< Port A Component Version Register,                                          Address offset:0x6C        */
    __I  uint32_t CONFIG_REG2;                    /*!< Port A Configuration Register 2 Register,                                   Address offset:0x70        */
    __I  uint32_t CONFIG_REG1;                    /*!< Port A Configuration Register 1 Register,                                   Address offset:0x74        */
    __IO uint32_t PULLUP;                         /*!< Port A GPIO Pullup set Register,                                            Address offset:0x78        */
    __IO uint32_t PULLDOWN;                       /*!< Port A GPIO Pulldown set Register,                                          Address offset:0x7C        */
  } GPIO_TypeDef;
  
  /**
  * @brief PMU register
  */
  typedef struct 
  {
    __IO uint8_t CTL;                         /*!< PMU Control Register,                             Address offset:0x00        */
    __I  uint8_t RESERVED0[3];                /*!< Reserved,                                         Address offset:0x01 - 0x03 */
    __I  uint8_t RESERVED1[4];                /*!< Reserved,                                         Address offset:0x04 - 0x07 */
    __IO uint8_t RSM_CTL;                     /*!< RSM Control Register,                             Address offset:0x08        */
    __I  uint8_t RESERVED2[3];                /*!< Reserved,                                         Address offset:0x09 - 0x0B */
    __IO uint8_t FLAG_CTL;                    /*!< FLAG Control Register,                            Address offset:0x0C        */
    __I  uint8_t RESERVED3[3];                /*!< Reserved,                                         Address offset:0x0D - 0x0F */
    __IO uint8_t CLK;                         /*!< PMU Clock Register,                               Address offset:0x10        */
    __I  uint8_t RESERVED4[3];                /*!< Reserved,                                         Address offset:0x11 - 0x13 */
    __IO uint8_t IE_MSK;                      /*!< IE Interrupt Mask Register,                       Address offset:0x14        */
    __I  uint8_t RESERVED5[3];                /*!< Reserved,                                         Address offset:0x15 - 0x17 */
    __IO uint8_t LP_CTL;                      /*!< NPU Control Register,                             Address offset:0x18        */
    __I  uint8_t RESERVED6[3];                /*!< Reserved,                                         Address offset:0x19 - 0x1B */
    __IO uint8_t CLK_CTL;                     /*!< Comparator Control Register,                      Address offset:0x1C        */
    __I  uint8_t RESERVED7[3];                /*!< Reserved,                                         Address offset:0x1D - 0x1F */
    __IO uint8_t VOL_UPDATA;                  /*!< Voltage Updata Register,                          Address offset:0x20        */
    __I  uint8_t RESERVED8[15];               /*!< Reserved,                                         Address offset:0x21 - 0x2F */
    __IO uint8_t SRAM_PD;                     /*!< SRAM Power Down Control Register                  Address offset:0x30        */
    __I  uint8_t RESERVED9[3];                /*!< Reserved,                                         Address offset:0x31 - 0x33 */
    __IO uint8_t SRAM_RTN;                    /*!< SRAM Retain mode                                  Address offset:0x34        */
    __I  uint8_t RESERVED10[3];               /*!< Reserved,                                         Address offset:0x35 - 0x37 */
    __IO uint8_t PMU_RESV;                    /*!< Reserved                                          Address offset:0x38        */
    __I  uint8_t RESERVED11[7];               /*!< Reserved,                                         Address offset:0x39 - 0x3F */
    __IO uint8_t TRIM0;                       /*!<                                                   Address offset:0x40        */
    __I  uint8_t RESERVED12[3];               /*!< Reserved,                                         Address offset:0x41 - 0x43 */
    __IO uint8_t TRIM1;                       /*!<                                                   Address offset:0x44        */
    __I  uint8_t RESERVED13[3];               /*!< Reserved,                                         Address offset:0x45 - 0x47 */
    __IO uint8_t TRIM2;                       /*!<                                                   Address offset:0x48        */
    __I  uint8_t RESERVED14[3];               /*!< Reserved,                                         Address offset:0x49 - 0x4B */
    __IO uint8_t TRIM3;                       /*!<                                                   Address offset:0x4C        */
    __I  uint8_t RESERVED15[3];               /*!< Reserved,                                         Address offset:0x4D - 0x4F */
    __IO uint8_t TRIM4;                       /*!<                                                   Address offset:0x50        */
    __I  uint8_t RESERVED16[3];               /*!< Reserved,                                         Address offset:0x51 - 0x53 */
    __IO uint8_t TRIM5;                       /*!<                                                   Address offset:0x54        */
    __I  uint8_t RESERVED17[3];               /*!< Reserved,                                         Address offset:0x55 - 0x57 */
    __IO uint8_t GPIO_OD;                     /*!<                                                   Address offset:0x58        */
    __I  uint8_t RESERVED18[3];               /*!< Reserved,                                         Address offset:0x59 - 0x5B */
    __IO uint8_t GPIO_SMT0;                   /*!<                                                   Address offset:0x5C        */
    __I  uint8_t RESERVED19[3];               /*!< Reserved,                                         Address offset:0x5D - 0x5F */
    __IO uint8_t GPIO_SMT1;                   /*!<                                                   Address offset:0x60        */
    __I  uint8_t RESERVED20[3];               /*!< Reserved,                                         Address offset:0x61 - 0x63 */
    __IO uint8_t GPIO_SMT2;                   /*!<                                                   Address offset:0x64        */
    __I  uint8_t RESERVED21[3];               /*!< Reserved,                                         Address offset:0x65 - 0x67 */
    __IO uint8_t PMU_RESV_ADC_REG0;           /*!<                                                   Address offset:0x68        */
    __I  uint8_t RESERVED22[3];               /*!< Reserved,                                         Address offset:0x69 - 0x6B */
    __IO uint8_t PMU_RESV_ADC_REG1;           /*!<                                                   Address offset:0x6c        */
    __I  uint8_t RESERVED23[3];               /*!< Reserved,                                         Address offset:0x6d - 0x6F */
    __IO uint8_t PLL_0;                       /*!<                                                   Address offset:0x70        */
    __I  uint8_t RESERVED24[3];               /*!< Reserved,                                         Address offset:0x71 - 0x73 */
    __IO uint8_t PLL_1;                       /*!<                                                   Address offset:0x74        */
    __I  uint8_t RESERVED25[3];               /*!< Reserved,                                         Address offset:0x75 - 0x77 */
    __IO uint8_t PLL_2;                       /*!<                                                   Address offset:0x78        */
    __I  uint8_t RESERVED26[3];               /*!< Reserved,                                         Address offset:0x79 - 0x7B */
    __IO uint8_t PLL_3;                       /*!<                                                   Address offset:0x7C        */
    __I  uint8_t RESERVED27[3];               /*!< Reserved,                                         Address offset:0x7D - 0x7F */
    __IO uint8_t PLL_4;                       /*!<                                                   Address offset:0x80        */
    __I  uint8_t RESERVED28[3];               /*!< Reserved,                                         Address offset:0x81 - 0x83 */
    __IO uint8_t PLL_5;                       /*!<                                                   Address offset:0x84        */
    __I  uint8_t RESERVED29[11];              /*!< Reserved,                                         Address offset:0x85 - 0x8F */
    __IO uint8_t TRIM_RST;                    /*!<                                                   Address offset:0x90        */
    __I  uint8_t RESERVED30[3];               /*!< Reserved,                                         Address offset:0x91 - 0x93 */
    __IO uint8_t _320K_TRIM;                  /*!<                                                   Address offset:0x94        */
    __I  uint8_t RESERVED31[3];               /*!< Reserved,                                         Address offset:0x95 - 0x97 */
    __IO uint8_t _24M_TRIM_FINE;              /*!<                                                   Address offset:0x98        */
    __I  uint8_t RESERVED32[3];               /*!< Reserved,                                         Address offset:0x99 - 0x9B */
    __IO uint8_t _24M_TRIM_COARSE;            /*!<                                                   Address offset:0x9C        */
    __I  uint8_t RESERVED33[3];               /*!< Reserved,                                         Address offset:0x9D - 0x9F */
    __IO uint8_t SOFT_RST;                    /*!< SOFT_RST                                          Address offset:0xA0        */
    __I  uint8_t RESERVED34[3];               /*!< Reserved,                                         Address offset:0xA1 - 0xA3 */
    __IO uint8_t REVID;                       /*!<                                                   Address offset:0xA4        */
    __I  uint8_t RESERVED35[3];               /*!< Reserved,                                         Address offset:0xA5 - 0xA7 */
    __IO uint8_t SYS_CFG;                     /*!<                                                   Address offset:0xA8        */
    __I  uint8_t RESERVED36[3];               /*!< Reserved,                                         Address offset:0xA9 - 0xAB */
    __IO uint8_t GPIO_WU_CLR;                 /*!<                                                   Address offset:0xAC        */
    __I  uint8_t RESERVED37[3];               /*!< Reserved,                                         Address offset:0xAD - 0xAF */
    __IO uint8_t RST_VEC_0;                   /*!<                                                   Address offset:0xB0        */
    __I  uint8_t RESERVED38[3];               /*!< Reserved,                                         Address offset:0x81 - 0xB3 */
    __IO uint8_t RST_VEC_1;                   /*!<                                                   Address offset:0xB4        */
    __I  uint8_t RESERVED39[3];               /*!< Reserved,                                         Address offset:0xB5 - 0xB7 */
    __IO uint8_t RST_VEC_2;                   /*!<                                                   Address offset:0xB8        */
    __I  uint8_t RESERVED40[3];               /*!< Reserved,                                         Address offset:0xB9 - 0xBB */
    __IO uint8_t RST_VEC_3;                   /*!<                                                   Address offset:0xBC        */
    __I  uint8_t RESERVED41[3];               /*!< Reserved,                                         Address offset:0xBD - 0xBF */
    __IO uint8_t RTN_0;                       /*!<                                                   Address offset:0xC0        */
    __I  uint8_t RESERVED42[3];               /*!< Reserved,                                         Address offset:0xC1 - 0xC3 */
    __IO uint8_t RTN_1;                       /*!<                                                   Address offset:0xC4        */
    __I  uint8_t RESERVED43[3];               /*!< Reserved,                                         Address offset:0xC5 - 0xC7 */
    __IO uint8_t RTN_2;                       /*!<                                                   Address offset:0xC8        */
    __I  uint8_t RESERVED44[3];               /*!< Reserved,                                         Address offset:0xC9 - 0xCB */
    __IO uint8_t RTN_3;                       /*!<                                                   Address offset:0xCC        */
  } PMU_TypeDef;
  
  /**
  * @brief UART register
  */
  typedef struct 
  {
    __IO uint32_t DR_DLL;                      /*!< UART Transmit Holding Receive Buffer Divisor Latch (Low) Register, Address offset:0x00        */
    __IO uint32_t IER_DLH;                     /*!< UART Interrupt Enable Divisor Latch (High) Register,               Address offset:0x04        */
    __IO uint32_t IIR_FCR;                     /*!< UART Interrupt Identification FIFO Control Register,               Address offset:0x08        */
    __IO uint32_t LCR;                         /*!< UART Line Control Register,                                        Address offset:0x0C        */
    __IO uint32_t MCR;                         /*!< UART Modem Control Register,                                       Address offset:0x10        */
    __I  uint32_t LSR;                         /*!< UART Line Status Register,                                         Address offset:0x14        */
    __I  uint32_t MSR;                         /*!< UART Modem Status Register,                                        Address offset:0x18        */
    __IO uint32_t SCR;                         /*!< UART Scratchpad Register,                                          Address offset:0x1C        */
    __IO uint32_t LPDLL;                       /*!< UART Low Power Divisor Latch (Low) Register,                       Address offset:0x20        */
    __IO uint32_t LPDLH;                       /*!< UART Low Power Divisor Latch (High) Register,                      Address offset:0x24        */
    __I  uint32_t RESERVED0[18];               /*!< Reserved,                                                          Address offset:0x28 - 0x6F */
    __IO uint32_t FAR;                         /*!< UART FIFO Access Register,                                         Address offset:0x70        */
    __I  uint32_t TFR;                         /*!< UART Transmit FIFO Read Register,                                  Address offset:0x74        */
    __O  uint32_t RFW;                         /*!< UART Receive FIFO Write Register,                                  Address offset:0x78        */
    __I  uint32_t USR;                         /*!< UART Status Register,                                              Address offset:0x7C        */
    __I  uint32_t TFL;                         /*!< UART Transmit FIFO Level Register,                                 Address offset:0x80        */
    __I  uint32_t RFL;                         /*!< UART Receive FIFO Level Register,                                  Address offset:0x84        */
    __O  uint32_t SRR;                         /*!< UART Software Reset Register,                                      Address offset:0x88        */
    __IO uint32_t SRTS;                        /*!< UART Shadow Request to Send Register,                              Address offset:0x8C        */
    __IO uint32_t SBCR;                        /*!< UART Shadow Break Control Register,                                Address offset:0x90        */
    __IO uint32_t SDMAM;                       /*!< UART Shadow DMA Mode Register,                                     Address offset:0x94        */
    __IO uint32_t SFE;                         /*!< UART Shadow FIFO Enable Register,                                  Address offset:0x98        */
    __IO uint32_t SRT;                         /*!< UART Shadow RCVR Trigger Register,                                 Address offset:0x9C        */
    __IO uint32_t STET;                        /*!< UART Shadow TX Empty Trigger Register,                             Address offset:0xA0        */
    __O  uint32_t HTX;                         /*!< UART Halt TX Register,                                             Address offset:0xA4        */
    __O  uint32_t DMASA;                       /*!< UART DMA Software Acknowledge Register,                            Address offset:0xA8        */
    __I  uint32_t RESERVED1[18];               /*!< Reserved,                                                          Address offset:0xAC - 0xF3 */
    __I  uint32_t CPR;                         /*!< UART Component Parameter Register,                                 Address offset:0xF4        */
    __I  uint32_t UCV;                         /*!< UART Component Version Register,                                   Address offset:0xF8        */
    __I  uint32_t CTR;                         /*!< UART Component Type Register Register,                             Address offset:0xFC        */
  } UART_TypeDef;

 
  /**
  * @brief I2C register
  */
  typedef struct 
  {
    __IO uint32_t CON;                       /*!< I2C Control Register,                                                             Address offset:0x00        */
    __IO uint32_t TAR;                       /*!< I2C Target Address Register,                                                      Address offset:0x04        */
    __IO uint32_t SAR;                       /*!< I2C Slave Address Register,                                                       Address offset:0x08        */
    __I  uint32_t RESERVED0;                 /*!< Reserved,                                                                         Address offset:0x0C        */
    __IO uint32_t DATA_CMD;                  /*!< I2C Rx/Tx Data Buffer and Command Register,                                       Address offset:0x10        */
    __IO uint32_t SS_SCL_HCNT;               /*!< I2C Standard speed I2C Clock SCL High Count Register,                             Address offset:0x14        */
    __IO uint32_t SS_SCL_LCNT;               /*!< I2C Standard speed I2C Clock SCL Low Count Register,                              Address offset:0x18        */
    __IO uint32_t FS_SCL_HCNT;               /*!< I2C Fast Mode and Fast Mode Plus I2C Clock SCL High Count Register,               Address offset:0x1C        */
    __IO uint32_t FS_SCL_LCNT;               /*!< I2C Fast Mode and Fast Mode Plus I2C Clock SCL Low Count Register,                Address offset:0x20        */
    __I  uint32_t RESERVED1[2];              /*!< Reserved,                                                                         Address offset:0x24 - 0x2B */
    __I  uint32_t INTR_STAT;                 /*!< I2C Interrupt Status Register,                                                    Address offset:0x2C        */
    __IO uint32_t INTR_MSK;                  /*!< I2C Interrupt Mask Register,                                                      Address offset:0x30        */
    __I  uint32_t RAW_INTR_STAT;             /*!< I2C Raw Interrupt Status Register,                                                Address offset:0x34        */
    __IO uint32_t RX_TL;                     /*!< I2C Receive FIFO Threshold Register,                                              Address offset:0x38        */
    __IO uint32_t TX_TL;                     /*!< I2C Transmit FIFO Threshold Register,                                             Address offset:0x3C        */
    __I  uint32_t CLR_INTR;                  /*!< I2C Clear Combined and Individual Interrupts Register,                            Address offset:0x40        */
    __I  uint32_t CLR_RX_UNDER;              /*!< I2C Clear RX_UNDER Interrupt Register,                                            Address offset:0x44        */
    __I  uint32_t CLR_RX_OVER;               /*!< I2C Clear RX_OVER Interrupt Register,                                             Address offset:0x48        */
    __I  uint32_t CLR_TX_OVER;               /*!< I2C Clear TX_OVER Interrupt Register,                                             Address offset:0x4C        */
    __I  uint32_t CLR_RD_REQ;                /*!< I2C Clear RD_REQ Interrupt Register,                                              Address offset:0x50        */
    __I  uint32_t CLR_TX_ABRT;               /*!< I2C Clear TX_ABRT Interrupt Register,                                             Address offset:0x54        */
    __I  uint32_t CLR_RX_DONE;               /*!< I2C Clear RX_DONE Interrupt Register,                                             Address offset:0x58        */
    __I  uint32_t CLR_ACTIVITY;              /*!< I2C Clear ACTIVITY Interrupt Register,                                            Address offset:0x5C        */
    __I  uint32_t CLR_STOP_DET;              /*!< I2C Clear STOP_DET Interrupt Register,                                            Address offset:0x60        */
    __I  uint32_t CLR_START_DET;             /*!< I2C Clear START_DET Interrupt Register,                                           Address offset:0x64        */
    __I  uint32_t CLR_GEN_CALL;              /*!< I2C Clear GEN_CALL Interrupt Register,                                            Address offset:0x68        */
    __IO uint32_t ENABLE;                    /*!< I2C Enable Register,                                                              Address offset:0x6C        */
    __I  uint32_t STAT;                      /*!< I2C Status register Register,                                                     Address offset:0x70        */
    __I  uint32_t TXFLR;                     /*!< I2C Transmit FIFO Level Register Register,                                        Address offset:0x74        */
    __I  uint32_t RXFLR;                     /*!< I2C Receive FIFO Level Register Register,                                         Address offset:0x78        */
    __IO uint32_t SDA_HOLD;                  /*!< I2C SDA hold time length register Register,                                       Address offset:0x7C        */
    __I  uint32_t TX_ABRT_SRC;               /*!< I2C Transmit Abort Status Register Register,                                      Address offset:0x80        */
    __I  uint32_t RESERVED2;                 /*!< Reserved,                                                                         Address offset:0x84        */
    __IO uint32_t DMA_CR;                    /*!< I2C DMA Control Register for transmit and receive handshaking interface Register, Address offset:0x88        */
    __IO uint32_t DMA_TDLR;                  /*!< I2C DMA Transmit Data Level Register,                                             Address offset:0x8C        */
    __IO uint32_t DMA_RDLR;                  /*!< I2C DMA Receive Data Level Register,                                              Address offset:0x90        */
    __IO uint32_t SDA_SETUP;                 /*!< I2C SDA Setup Register Register,                                                  Address offset:0x94        */
    __IO uint32_t ACK_GEN_CALL;              /*!< I2C ACK General Call Register Register,                                           Address offset:0x98        */
    __I  uint32_t ENABLE_STAT;               /*!< I2C Enable Status Register Register,                                              Address offset:0x9C        */
    __IO uint32_t FS_SPKLEN;                 /*!< I2C ISS and FS spike suppression limit Register,                                  Address offset:0xA0        */
  } I2C_TypeDef;
  
  /**
  * @brief PWM register
  */
  typedef struct 
  {
    __IO uint32_t CTL;                      /*!< PWM control Register,                              Address offset:0x00        */
    __IO uint32_t CH_CTL;                   /*!< PWM Channel Control Register,                      Address offset:0x04        */
    __IO uint32_t CH0_INI;                  /*!< PWM Channel0 initialization configure Register,    Address offset:0x08        */
    __IO uint32_t CH1_INI;                  /*!< PWM Channel1 initialization configure Register,    Address offset:0x0C        */
    __IO uint32_t CH2_INI;                  /*!< PWM Channel2 initialization configure Register,    Address offset:0x10        */
    __IO uint32_t CH3_INI;                  /*!< PWM Channel3 initialization configure Register,    Address offset:0x14        */
    __I  uint32_t RESERVED0[58];            /*!< Reserved,                                          Address offset:0x18 - FF   */
    __I  uint32_t CH0_RB_VAL;               /*!< PWM Channel0 capture value Register,               Address offset:0x100       */
    __I  uint32_t CH1_RB_VAL;               /*!< PWM Channel1 capture value Register,               Address offset:0x104       */
    __I  uint32_t CH2_RB_VAL;               /*!< PWM Channel2 capture value Register,               Address offset:0x108       */
    __I  uint32_t CH3_RB_VAL;               /*!< PWM Channel3 capture value Register,               Address offset:0x10C       */
    __I  uint32_t RESERVED1[60];            /*!< Reserved,                                          Address offset:0x110 - 1FF */
    __IO uint32_t PUL;                      /*!< PWM bike Register,                                 Address offset:0x200       */
    __I  uint32_t RESERVED2[15];            /*!< Reserved,                                          Address offset:0x204 - 23F */
    __O  uint32_t INT_MSK_SET;              /*!< PWM interrupt mask Register,                       Address offset:0x240       */
    __O  uint32_t INT_MSK_CLR;              /*!< PWM interrupt mask clear Register,                 Address offset:0x244       */
    __I  uint32_t RESERVED3[2];             /*!< Reserved,                                          Address offset:0x248 - 24F */
    __IO uint32_t INT_SR_PND;               /*!< PWM interrupt status Register,                     Address offset:0x250       */
  } PWM_TypeDef;
  
  /**
  * @brief RCC register
  */
  typedef struct 
  {
    __IO uint32_t CLK_DIV_0;                /*!< RCC clock division0 Register,                      Address offset:0x00      */
    __IO uint32_t CLK_SEL;                  /*!< RCC clock source select Register,                  Address offset:0x04      */
    __IO uint32_t CLK_EN;                   /*!< RCC clock enable Register,                         Address offset:0x08      */
    __O  uint32_t RST_EN;                   /*!< Peripheral reset Register,                         Address offset:0x0C      */
    __I  uint32_t RESERVED0;                /*!< Reserved,                                          Address offset:0x10      */
    __IO uint32_t TIM_DIV;                  /*!< Timer clock division Register,                     Address offset:0x14      */
    __IO uint32_t CLK_DIV_1;                /*!< RCC clock division1 Register,                      Address offset:0x18      */
    __IO uint32_t SYS_CFG;                  /*!< Memory access configure Register,                  Address offset:0x1C      */
    __IO uint32_t CLK_DIV_2;                /*!< RCC clock division2 Register,                      Address offset:0x20      */
    __IO uint32_t CLK_DIV_3;                /*!< RCC clock division3 Register,                      Address offset:0x24      */
    __I  uint32_t RESERVED1[2];             /*!< Reserved,                                          Address offset:0x28 - 2F */
    __IO uint32_t PMUX_C0;                  /*!< GPIO_0-15 Alternate Function Selection Register,   Address offset:0x30      */
    __IO uint32_t PMUX_C1;                  /*!< GPIO_16-19 Alternate Function Selection Register,  Address offset:0x34      */
  } RCC_TypeDef;
  
  /**
  * @brief Serial Peripheral Interface
  */
  typedef struct
  {
    __IO uint32_t CTRLR0;               /*!< Control register 0                              Address offset:0x00 */
    __IO uint32_t CTRLR1;               /*!< Control register 1                              Address offset:0x04 */
    __IO uint32_t SSIENR;               /*!< SSI Enable Register                             Address offset:0x08 */
    __IO uint32_t MWCR;                 /*!< Microwire Control Register                      Address offset:0x0C */
    __IO uint32_t SER;                  /*!< Slave Enable Register                           Address offset:0x10 */
    __IO uint32_t BAUDR;                /*!< Baud Rate Select                                Address offset:0x14 */
    __IO uint32_t TXFTLR;               /*!< Transmit FIFO Threshold Level                   Address offset:0x18 */
    __IO uint32_t RXFTLR;               /*!< Receive FIFO Threshold Level                    Address offset:0x1C */
    __I  uint32_t TXFLR;                /*!< Transmit FIFO Level Register                    Address offset:0x20 */
    __I  uint32_t RXFLR;                /*!< Receive FIFO Level Register                     Address offset:0x24 */
    __I  uint32_t SR;                   /*!< Status Register                                 Address offset:0x28 */
    __IO uint32_t IMR;                  /*!< Interrupt Mask Register                         Address offset:0x2C */
    __I  uint32_t ISR;                  /*!< Interrupt Status Register                       Address offset:0X30 */
    __I  uint32_t RISR;                 /*!< Raw Interrupt Status Register                   Address offset:0X34 */
    __I  uint32_t TXOICR;               /*!< Transmit FIFO Overflow Interrupt Clear Register Address offset:0X38 */
    __I  uint32_t RXOICR;               /*!< Receive FIFO Overflow Interrupt Clear Register  Address offset:0X3C */
    __I  uint32_t RXUICR;               /*!< Receive FIFO Underflow Interrupt Clear Register Address offset:0X40 */
    __I  uint32_t MSTICR;               /*!< Multi-Master Interrupt Clear Register           Address offset:0X44 */
    __I  uint32_t ICR;                  /*!< Interrupt Clear Register                        Address offset:0X48 */
    __IO uint32_t DMACR;                /*!< DMA Control Register                            Address offset:0X4C */
    __IO uint32_t DMATDLR;              /*!< DMA Transmit Data Level                         Address offset:0X50 */
    __IO uint32_t DMARDLR;              /*!< DMA Receive Data Level                          Address offset:0X54 */
    __I  uint32_t IDR;                  /*!< Identification Register                         Address offset:0X58 */
    __I  uint32_t SSI_COMP_VERSION;     /*!< coreKit version ID register                     Address offset:0X5C */
    __IO uint32_t DR;                   /*!< Data Register                                   Address offset:0X60 */
  } SPI_TypeDef;
  
  /**
  * @brief Watch Dog Interface
  */
  typedef struct
  {
    __IO uint32_t WDT_CR;                               /*!< Control register                           Address offset:0x00        */
    __IO uint32_t WDT_TORR;                             /*!< Timeout range register                     Address offset:0x04        */
    __I  uint32_t WDT_CCVR;                             /*!< Current counter value register             Address offset:0x08        */
    __O  uint32_t WDT_CRR;                              /*!< Counter restart register                   Address offset:0x0C        */
    __I  uint32_t WDT_STAT;                             /*!< Interrupt status register                  Address offset:0x10        */
    __I  uint32_t WDT_EOI;                              /*!< Interrupt clear register                   Address offset:0x1C        */
    __I  uint32_t RESERVED[51];                         /*!< Reserved,                                  Address offset:0x20 - 0xE3 */
    __I  uint32_t COMP_PARAMS_5;                        /*!< Component Parameters 5                     Address offset:0xE4        */
    __I  uint32_t COMP_PARAMS_4;                        /*!< Component Parameters 4                     Address offset:0xE8        */
    __I  uint32_t COMP_PARAMS_3;                        /*!< Component Parameters 3                     Address offset:0xEC        */
    __I  uint32_t COMP_PARAMS_2;                        /*!< Component Parameters 2                     Address offset:0xF0        */
    __I  uint32_t COMP_PARAMS_1;                        /*!< Component Parameters 1                     Address offset:0xF4        */
    __I  uint32_t COMP_VERSION;                         /*!< Component Version                          Address offset:0xF8        */
    __I  uint32_t COMP_TYPE;                            /*!< Component Type                             Address offset:0xFC        */
  } WDT_TypeDef;
  
  /**
  * @brief RTC Interface
  */
  typedef struct
  {
    __I  uint32_t RTC_CCVR;                             /*!< Current Counter Value Register             Address offset:0x00 */
    __IO uint32_t RTC_CMR;                              /*!< Counter Match Register                     Address offset:0x04 */
    __IO uint32_t RTC_CLR;                              /*!< Counter Load Register                      Address offset:0x08 */
    __IO uint32_t RTC_CCR;                              /*!< Counter Control Register                   Address offset:0x0C */
    __I  uint32_t RTC_STAT;                             /*!< Interrupt Status Register                  Address offset:0x10 */
    __I  uint32_t RTC_RSTAT;                            /*!< Interrupt Raw Status Register              Address offset:0x14 */
    __I  uint32_t RTC_EOI;                              /*!< End of Interrupt Register                  Address offset:0x18 */
    __I  uint32_t COMP_VERSION;                         /*!< End of Interrupt Register                  Address offset:0x1C */
  } RTC_TypeDef;
  
  /**
  * @brief DMA Channel Interface
  */
  typedef struct
  {
    __IO uint64_t SAR0;                 /*!< Channe0  Source Address Register                     Address offset:0x00          */
    __IO uint64_t DAR0;                 /*!< Channe0  Destination Address Register                Address offset:0x08          */
    __IO uint64_t LLP0;                 /*!< Channe0  Linked List Pointer Register                Address offset:0x10          */
    __IO uint64_t CTL0;                 /*!< Channe0  Control Register                            Address offset:0x18          */
    __IO uint64_t SSTAT0;               /*!< Reserved                                             Address offset:0x20          */
    __IO uint64_t DSTAT0;               /*!< Reserved                                             Address offset:0x28          */
    __IO uint64_t SSTATAR0;             /*!< Reserved                                             Address offset:0x30          */
    __IO uint64_t DSTATAR0;             /*!< Reserved                                             Address offset:0x38          */
    __IO uint64_t CFG0;                 /*!< Channe0  Configuration Register                      Address offset:0x40          */
    __IO uint64_t SGR0;                 /*!< Reserved                                             Address offset:0x48          */
    __IO uint64_t DSR0;                 /*!< Reserved                                             Address offset:0x50          */

    __IO uint64_t SAR1;                 /*!< Channel  Source Address Register                     Address offset:0x58          */
    __IO uint64_t DAR1;                 /*!< Channel  Destination Address Register                Address offset:0x60          */
    __IO uint64_t LLP1;                 /*!< Channel  Linked List Pointer Register                Address offset:0x68          */
    __IO uint64_t CTL1;                 /*!< Channel  Control Register                            Address offset:0x70          */
    __IO uint64_t SSTAT1;               /*!< Reserved                                             Address offset:0x78          */
    __IO uint64_t DSTAT1;               /*!< Reserved                                             Address offset:0x80          */
    __IO uint64_t SSTATAR1;             /*!< Reserved                                             Address offset:0x88          */
    __IO uint64_t DSTATAR1;             /*!< Reserved                                             Address offset:0x90          */
    __IO uint64_t CFG1;                 /*!< Channel  Configuration Register                      Address offset:0x98          */
    __IO uint64_t SGR1;                 /*!< Reserved                                             Address offset:0xA0          */
    __IO uint64_t DSR1;                 /*!< Reserved                                             Address offset:0xA8          */
    
    __IO uint64_t SAR2;                 /*!< Channe2  Source Address Register                     Address offset:0xB0          */
    __IO uint64_t DAR2;                 /*!< Channe2  Destination Address Register                Address offset:0xB8          */
    __IO uint64_t LLP2;                 /*!< Channe2  Linked List Pointer Register                Address offset:0xC0          */
    __IO uint64_t CTL2;                 /*!< Channe2  Control Register                            Address offset:0xC8          */
    __IO uint64_t SSTAT2;               /*!< Reserved                                             Address offset:0xD0          */
    __IO uint64_t DSTAT2;               /*!< Reserved                                             Address offset:0xD8          */
    __IO uint64_t SSTATAR2;             /*!< Reserved                                             Address offset:0xE0          */
    __IO uint64_t DSTATAR2;             /*!< Reserved                                             Address offset:0xE8          */
    __IO uint64_t CFG2;                 /*!< Channe2  Configuration Register                      Address offset:0xF0          */
    __IO uint64_t SGR2;                 /*!< Reserved                                             Address offset:0xF8          */
    __IO uint64_t DSR2;                 /*!< Reserved                                             Address offset:0x100         */
    
    __IO uint64_t SAR3;                 /*!< Channe3  Source Address Register                     Address offset:0x108         */
    __IO uint64_t DAR3;                 /*!< Channe3  Destination Address Register                Address offset:0x110         */
    __IO uint64_t LLP3;                 /*!< Channe3  Linked List Pointer Register                Address offset:0x118         */
    __IO uint64_t CTL3;                 /*!< Channe3  Control Register                            Address offset:0x120         */
    __IO uint64_t SSTAT3;               /*!< Reserved                                             Address offset:0x128         */
    __IO uint64_t DSTAT3;               /*!< Reserved                                             Address offset:0x130         */
    __IO uint64_t SSTATAR3;             /*!< Reserved                                             Address offset:0x138         */
    __IO uint64_t DSTATAR3;             /*!< Reserved                                             Address offset:0x140         */
    __IO uint64_t CFG3;                 /*!< Channe3  Configuration Register                      Address offset:0x148         */
    __IO uint64_t SGR3;                 /*!< Reserved                                             Address offset:0x150         */
    __IO uint64_t DSR3;                 /*!< Reserved                                             Address offset:0x158         */
    
    __IO uint64_t SAR4;                 /*!< Channe4  Source Address Register                     Address offset:0x160         */
    __IO uint64_t DAR4;                 /*!< Channe4  Destination Address Register                Address offset:0x168         */
    __IO uint64_t LLP4;                 /*!< Channe4  Linked List Pointer Register                Address offset:0x170         */
    __IO uint64_t CTL4;                 /*!< Channe4  Control Register                            Address offset:0x178         */
    __IO uint64_t SSTAT4;               /*!< Reserved                                             Address offset:0x180         */
    __IO uint64_t DSTAT4;               /*!< Reserved                                             Address offset:0x188         */
    __IO uint64_t SSTATAR4;             /*!< Reserved                                             Address offset:0x190         */
    __IO uint64_t DSTATAR4;             /*!< Reserved                                             Address offset:0x198         */
    __IO uint64_t CFG4;                 /*!< Channe4  Configuration Register                      Address offset:0x1A0         */
    __IO uint64_t SGR4;                 /*!< Reserved                                             Address offset:0x1A8         */
    __IO uint64_t DSR4;                 /*!< Reserved                                             Address offset:0x1B0         */

    __IO uint64_t SAR5;                 /*!< Channe5  Source Address Register                     Address offset:0x1B8         */
    __IO uint64_t DAR5;                 /*!< Channe5  Destination Address Register                Address offset:0x1C0         */
    __IO uint64_t LLP5;                 /*!< Channe5  Linked List Pointer Register                Address offset:0x1C8         */
    __IO uint64_t CTL5;                 /*!< Channe5  Control Register                            Address offset:0x1D0         */
    __IO uint64_t SSTAT5;               /*!< Reserved                                             Address offset:0x1D8         */
    __IO uint64_t DSTAT5;               /*!< Reserved                                             Address offset:0x1E0         */
    __IO uint64_t SSTATAR5;             /*!< Reserved                                             Address offset:0x1E8         */
    __IO uint64_t DSTATAR5;             /*!< Reserved                                             Address offset:0x1F0         */
    __IO uint64_t CFG5;                 /*!< Channe5  Configuration Register                      Address offset:0x1F8         */
    __IO uint64_t SGR5;                 /*!< Reserved                                             Address offset:0x200         */
    __IO uint64_t DSR5;                 /*!< Reserved                                             Address offset:0x208         */

    __I uint64_t RESERVED12[22];        /*!< Reserved                                             Address offset:0x210 - 0x2BF */
    __I uint64_t RAW_STA_INTTFR;        /*!< Raw Status for IntTfr Interrupt                      Address offset:0x2C0         */
    __I uint64_t RAW_STA_BLOCK;         /*!< Raw Status for IntBlock Interrupt                    Address offset:0x2C8         */
    __I uint64_t RAW_STA_SRCTRAN;       /*!< Raw Status for IntSrcTran Interrupt                  Address offset:0x2D0         */
    __I uint64_t RAW_STA_DSTTRAN;       /*!< Raw Status for IntDstTran Interrupt                  Address offset:0x2D8         */
    __I uint64_t RAW_STA_ERR;           /*!< Raw Status for IntErr Interrupt                      Address offset:0x2E0         */
    __I uint64_t STA_INTTFR;            /*!< Status for IntTfr Interrupt                          Address offset:0x2E8         */
    __I uint64_t STA_BLOCK;             /*!< Status for IntBlock Interrupt                        Address offset:0x2F0         */
    __I uint64_t STA_SRCTRAN;           /*!< Status for IntSrcTran Interrupt                      Address offset:0x2F8         */
    __I uint64_t STA_DSTTRAN;           /*!< Status for IntDstTran Interrupt                      Address offset:0x300         */
    __I uint64_t STA_ERR;               /*!< Status for IntErr Interrupt                          Address offset:0x308         */
    __IO uint64_t MASK_INTTFR;          /*!< Mask for IntTfr Interrupt                            Address offset:0x310         */
    __IO uint64_t MASK_BLOCK;           /*!< Mask for IntBlock Interrupt                          Address offset:0x318         */
    __IO uint64_t MASK_SRCTRAN;         /*!< Mask for IntSrcTran Interrupt                        Address offset:0x320         */
    __IO uint64_t MASK_DSTTRAN;         /*!< Mask for IntDstTran Interrupt                        Address offset:0x328         */
    __IO uint64_t MASK_ERR;             /*!< Mask for IntErr Interrupt                            Address offset:0x330         */
    __O uint64_t CLR_STA_TFR;           /*!< Clear for IntTfr Interrupt                           Address offset:0x338         */
    __O uint64_t CLR_STA_BLOCK;         /*!< Clear for IntBlock Interrupt                         Address offset:0x340         */
    __O uint64_t CLR_STA_SRCTRAN;       /*!< Clear for IntSrcTran Interrupt                       Address offset:0x348         */
    __O uint64_t CLR_STA_DSTTRAN;       /*!< Clear for IntDstTran Interrupt                       Address offset:0x350         */
    __O uint64_t CLR_STA_ERR;           /*!< Clear for IntErr Interrupt                           Address offset:0x358         */
    __O uint64_t STA_INT;               /*!< Status for each interrupt type                       Address offset:0x360         */
    
    __IO uint64_t REQ_SRC;              /*!< Source Software Transaction Request Register         Address offset:0x368         */
    __IO uint64_t REQ_DST;              /*!< Destination Software Transaction Request Register    Address offset:0x370         */
    __IO uint64_t SGL_REQ_SRC;          /*!< Single Source Transaction Request Register           Address offset:0x378         */
    __IO uint64_t SGL_REQ_DST;          /*!< Single Destination Transaction Request Register      Address offset:0x380         */
    __IO uint64_t LST_SRC;              /*!< Last Source Transaction Request Register             Address offset:0x388         */
    __IO uint64_t LST_DST;              /*!< Last Destination Transaction Request Register        Address offset:0x390         */
    
    __IO uint64_t DMA_CFG;              /*!< DMA Configuration Register                           Address offset:0x398         */
    __IO uint64_t DMA_CHENR;            /*!< DMA Channel Enable Register                          Address offset:0x3A0         */
    __IO uint64_t DMA_LDREG;            /*!< DMA Channel Enable Register                          Address offset:0x3A8         */
    __IO uint64_t DMA_TESTREG;          /*!< DMA Channel Enable Register                          Address offset:0x3B0         */
    __I uint64_t RESERVED13[2];         /*!< Reserved                                             Address offset:0x3B8 - 0x3C7 */
    __IO uint64_t COMP_PARAMS_6;        /*!< DMA Channel Enable Register                          Address offset:0x3C8         */
    __IO uint64_t COMP_PARAMS_5;        /*!< DMA Channel Enable Register                          Address offset:0x3D0         */
    __IO uint64_t COMP_PARAMS_4;        /*!< DMA Channel Enable Register                          Address offset:0x3D8         */
    __IO uint64_t COMP_PARAMS_3;        /*!< DMA Channel Enable Register                          Address offset:0x3E0         */
    __IO uint64_t COMP_PARAMS_2;        /*!< DMA Channel Enable Register                          Address offset:0x3E8         */
    __IO uint64_t COMP_PARAMS_1;        /*!< DMA Channel Enable Register                          Address offset:0x3F0         */
    __IO uint64_t COMPONENT_ID;         /*!< DMA Channel Enable Register                          Address offset:0x3F8         */
  } DMA_TypeDef;
  
  /**
  * @brief  timer Interface
  */
  typedef struct
  {
    __IO uint32_t TIMERLOADCOUNT;        /*!< Value to be loaded into Timer                       Address offset:0x00,0x14,0x28,0x3C */
    __I  uint32_t TIMERCURRENTVALUE;     /*!< Current Value of Timer1                             Address offset:0x04,0x18,0x2C,0x40 */
    __IO uint32_t TIMERCONTROLREG;       /*!< Control Register for Timer1                         Address offset:0x08,0x1C,0x30,0x44 */
    __I  uint32_t TIMEREOI;              /*!< Clears the interrupt from Timer1                    Address offset:0x0C,0x20,0x34,0x48 */
    __I  uint32_t TIMERINTSTATUS;        /*!< Contains the interrupt status for Timer1            Address offset:0x10,0x24,0x38,0x4C */
  }TMR_TypeDef;
  
  /**
  * @brief  timer total interrupt and pwm count value Interface
  */
  typedef struct
  {
    __I  uint32_t TIMERSINTSTATUS;      /*!< Contains the interrupt status of all timers in the component                Address offset:0xA0 */
    __I  uint32_t TIMERSEOI;            /*!< Returns all zeroes (0) and clears all active interrupts                     Address offset:0xA4 */
    __I  uint32_t TIMERSRAWTNTSTATUS;   /*!< Contains the unmasked interrupt status of all timers in the component       Address offset:0xA8 */
    __I  uint32_t TIMERS_VERSION;       /*!< Component Version                                                           Address offset:0xAC */
    __IO uint32_t TIMER0LOADCOUNT2;     /*!< Value to be loaded into Timer0 when toggle output changes from 0 to 1       Address offset:0xB0 */
    __IO uint32_t TIMER1LOADCOUNT2;     /*!< Value to be loaded into Timer1 when toggle output changes from 0 to 1       Address offset:0xB4 */
    __IO uint32_t TIMER2LOADCOUNT2;     /*!< Value to be loaded into Timer2 when toggle output changes from 0 to 1       Address offset:0xB8 */
    __IO uint32_t TIMER3LOADCOUNT2;     /*!< Value to be loaded into Timer3 when toggle output changes from 0 to 1       Address offset:0xBC */
  } TMR_TINT_PWM_TypeDef;
  
  /**
  * @brief I2S register
  */
  typedef struct
  {
    __IO uint32_t IER;                  /*!< I2S Enable Register,                                           Address offset:0x00      */
    __IO uint32_t IRER;                 /*!< I2S Receiver Block Enable Register,                            Address offset:0x04      */
    __IO uint32_t ITER;                 /*!< I2S Transmitter Block Enable Register,                         Address offset:0x08      */
    __IO uint32_t CER;                  /*!< I2S Clock Enable Register,                                     Address offset:0x0C      */
    __IO uint32_t CCR;                  /*!< I2S Clock Configuration Register,                              Address offset:0x10      */
    __O  uint32_t RXFFR;                /*!< I2S Receiver Block FIFO Register,                              Address offset:0x14      */
    __O  uint32_t TXFFR;                /*!< I2S Transmitter Block FIFO Register,                           Address offset:0x18      */
    __I  uint32_t RESERVED0;            /*!< reserved,                                                      Address offset:0x1C      */
    __IO uint32_t LRBR_LTHR;            /*!< I2S Left Receive Buffer and Left Transmit Holding Register,    Address offset:0x20      */
    __IO uint32_t RRBR_RTHR;            /*!< I2S Right Receive Buffer and Right Transmit Holding Register,  Address offset:0x24      */
    __IO uint32_t RER;                  /*!< I2S Receive Enable Register,                                   Address offset:0x28      */
    __IO uint32_t TER;                  /*!< I2S Transmit Enable Register,                                  Address offset:0x2C      */
    __IO uint32_t RCR;                  /*!< I2S Receive Configuration Register,                            Address offset:0x30      */
    __IO uint32_t TCR;                  /*!< I2S Transmit Configuration Register,                           Address offset:0x34      */
    __I  uint32_t ISR;                  /*!< I2S Interrupt Status Register,                                 Address offset:0x38      */
    __IO uint32_t IMR;                  /*!< I2S Interrupt Mask Register,                                   Address offset:0x3C      */
    __I  uint32_t ROR;                  /*!< I2S Receive Overrun Register,                                  Address offset:0x40      */
    __I  uint32_t TOR;                  /*!< I2S Transmit Overrun Register,                                 Address offset:0x44      */
    __IO uint32_t RFCR;                 /*!< I2S Receive FIFO Configuration Register,                       Address offset:0x48      */
    __IO uint32_t TFCR;                 /*!< I2S Transmit FIFO Configuration Register,                      Address offset:0x4C      */
    __O  uint32_t RFF;                  /*!< I2S Receive FIFO Flush Register,                               Address offset:0x50      */
    __O  uint32_t TFF;                  /*!< I2S Transmit FIFO Flush Register,                              Address offset:0x54      */
    __I  uint32_t RESERVED1[90];        /*!< Reserved,                                                      Address offset:0x58-1BF  */
    __I  uint32_t RXDMA;                /*!< I2S Receiver Block DMA Register,                               Address offset:0x1C0     */
    __O  uint32_t RRXDMA;               /*!< I2S Reset Receiver Block DMA Register,                         Address offset:0x1C4     */
    __O  uint32_t TXDMA;                /*!< I2S Transmitter Block DMA Register,                            Address offset:0x1C8     */
    __O  uint32_t RTXDMA;               /*!< I2S Reset Transmitter Block DMA Register,                      Address offset:0x1CC     */
    __I  uint32_t RESERVED2[8];         /*!< Reserved,                                                      Address offset:0x1D0-1EF */
    __I  uint32_t COMP_PARAM2;          /*!< I2S parameter2 Register,                                       Address offset:0x1F0     */
    __I  uint32_t COMP_PARAM1;          /*!< I2S parameter1 Register,                                       Address offset:0x1F4     */
    __I  uint32_t COMP_VERSION;         /*!< I2S version Register,                                          Address offset:0x1F8     */
    __IO uint32_t M_L_SW;               /*!< I2S master slave switch Register,                              Address offset:0x1FC     */
    __I  uint32_t COMP_TYPE;            /*!< I2S type Register,                                             Address offset:0x200     */
  } I2S_TypeDef; 
  

  /**
  * @brief AUD register
  */
  typedef struct
  {
      __IO uint32_t TRCTRL;           /*!< Audio Control Register0,                                       Address offset:0x00 */
      __IO uint32_t FFCLR;            /*!< FIFO Clear Register                                            Address offset:0x04 */
      __I  uint32_t FF0DATA;          /*!< FIFO0 Data Register                                            Address offset:0x08 */
      __I  uint32_t FF1DATA;          /*!< FIFO1 Data Register                                            Address offset:0x0C */
      __I  uint32_t FF2DATA;          /*!< FIFO2 Data Register                                            Address offset:0x10 */
      __IO uint32_t RAM0CFG0;         /*!< RAM0 Configuration Register0                                   Address offset:0x14 */
      __IO uint32_t RAM1CFG0;         /*!< RAM0 Configuration Register0                                   Address offset:0x18 */
      __IO uint32_t RAM0CFG1;         /*!< RAM1 Configuration Register1                                   Address offset:0x1C */
      __IO uint32_t RAM1CFG1;         /*!< RAM1 Configuration Register1                                   Address offset:0x20 */
      __IO uint32_t RAMCLR;           /*!< RAM0 Clear Register                                            Address offset:0x24 */
      __I  uint32_t RAM0DATA;         /*!< RAM0 DATA Register                                             Address offset:0x28 */
      __I  uint32_t RAM1DATA;         /*!< RAM1 DATA Register                                             Address offset:0x2C */
      __IO uint32_t PCM0CFG0;         /*!< PCM0 Configuration Register0                                   Address offset:0x30 */
      __IO uint32_t PCM0CFG1;         /*!< PCM0 Configuration Register1                                   Address offset:0x34 */
      __IO uint32_t PCM0CFG2;         /*!< PCM0 Configuration Register2                                   Address offset:0x38 */
      __IO uint32_t PCMGAIN;          /*!< PCM0 Gain Register                                             Address offset:0x3C */
      __I  uint32_t VADCNT;           /*!< VAD Count Register                                             Address offset:0x40 */
      __IO uint32_t VAD0;             /*!< VAD Register0                                                  Address offset:0x44 */
      __IO uint32_t VAD1;             /*!< VAD Register1                                                  Address offset:0x48 */
      __IO uint32_t VAD2;             /*!< VAD Register2                                                  Address offset:0x4C */
      __IO uint32_t VAD3;             /*!< VAD Register3                                                  Address offset:0x50 */
      __IO uint32_t VAD4;             /*!< VAD Register4                                                  Address offset:0x54 */
      __I  uint32_t TRINT;            /*!< FIFO Interrupt Register                                        Address offset:0x58 */
      __IO uint32_t TRINTMSK;         /*!< FIFO Interrupt Mask Register                                   Address offset:0x5C */
      __I  uint32_t AFEINT;           /*!< AFE Interrupt Register                                         Address offset:0x60 */
      __IO uint32_t AFEINTMSK;        /*!< AFE Interrupt Mask Register                                    Address offset:0x64 */
      __IO uint32_t ANALOCK;          /*!< ANALOG Lock Register                                           Address offset:0x68 */
      __IO uint32_t ANA0CFG;          /*!< ANALOG Configuration Register0                                 Address offset:0x6C */
      __IO uint32_t ANA1CFG;          /*!< ANALOG Configuration Register1                                 Address offset:0x70 */
      __IO uint32_t ANA2CFG;          /*!< ANALOG Configuration Register2                                 Address offset:0x74 */
      __IO uint32_t ANA3CFG;          /*!< ANALOG Configuration Register3                                 Address offset:0x78 */
      __IO uint32_t ANA4CFG;          /*!< ANALOG Configuration Register4                                 Address offset:0x7C */
      __IO uint32_t ANA5CFG;          /*!< ANALOG Configuration Register5                                 Address offset:0x80 */
      __IO uint32_t ANA6CFG;          /*!< ANALOG Configuration Register6                                 Address offset:0x84 */
      __IO uint32_t ANA7CFG;          /*!< ANALOG Configuration Register7                                 Address offset:0x88 */
      __IO uint32_t ANA8CFG;          /*!< ANALOG Configuration Register8                                 Address offset:0x8C */
      __IO uint32_t ANA9CFG;          /*!< ANALOG Configuration Register9                                 Address offset:0x90 */
      __IO uint32_t ANA10CFG;         /*!< ANALOG Configuration Register10                                Address offset:0x94 */
      __IO uint32_t ANA11CFG;         /*!< ANALOG Configuration Register11                                Address offset:0x98 */
      __IO uint32_t ANA12CFG;         /*!< ANALOG Configuration Register12                                Address offset:0x9c */
      __IO uint32_t ANA13CFG;         /*!< ANALOG Configuration Register13                                Address offset:0xA0 */
      __IO uint32_t ANA14CFG;         /*!< ANALOG Configuration Register14                                Address offset:0xA4 */
      __IO uint32_t ANA15CFG;         /*!< ANALOG Configuration Register15                                Address offset:0xA8 */
      __IO uint32_t ANA16CFG;         /*!< ANALOG Configuration Register16                                Address offset:0xAC */
      __IO uint32_t ANA17CFG;         /*!< ANALOG Configuration Register17                                Address offset:0xB0 */
      __IO uint32_t ANA18CFG;         /*!< ANALOG Configuration Register18                                Address offset:0xB4 */
      __IO uint32_t VADDEBUG0;        /*!< VAD Debug Register0                                            Address offset:0xB8 */
      __IO uint32_t VADDEBUG1;        /*!< VAD Debug Register1                                            Address offset:0xBC */
      __IO uint32_t VADDEBUG2;        /*!< VAD Debug Register2                                            Address offset:0xC0 */
      __IO uint32_t VADDEBUG3;        /*!< VAD Debug Register3                                            Address offset:0xC4 */
      __IO uint32_t VADDEBUG4;        /*!< VAD Debug Register4                                            Address offset:0xC8 */
      __IO uint32_t LRFIFO;           /*!< VAD Left And Right Channel Fifo                                Address offset:0xCC */
      __IO uint32_t LRRAM;            /*!< VAD Left And Right Channel Ram                                 Address offset:0xD0 */
      __IO uint32_t ANA19CFG;         /*!< ANALOG Configuration Register19                                Address offset:0xD4 */
      __IO uint32_t ANA20CFG;         /*!< ANALOG Configuration Register20                                Address offset:0xD8 */
      __IO uint32_t CLKSWI_CFG;       /*!< VAD Clock SWitch Configuration                                 Address offset:0xDC */
      __IO uint32_t AUDIO_DMA_CFG;    /*!< VAD Dma Configuration                                          Address offset:0xE0 */
  } AUD_TypeDef; 
  
  /**
  * @brief  FBANK register
  */
  typedef struct
  {
      __IO uint32_t SRAM[512];            /*!< FBANK Sram                                             */
      __IO uint32_t FBANK_EN;             /*!< FBANK Enabled                      Address offset:0x00 */
      __IO uint32_t FBANK_CONTROL;        /*!< FBANK Control Register             Address offset:0x04 */
      __IO uint32_t DEBUG_REGISTER;       /*!< Debug Register                     Address offset:0x08 */
      __IO uint32_t INT_MASK;             /*!< FBANK Interrupt Mask Register      Address offset:0x0C */
      __IO uint32_t INT_SOURCE;           /*!< FBANK Interrupt Source Register    Address offset:0x10 */
      __I  uint32_t FBANK_STATUS;         /*!< FBANK Status Register              Address offset:0x14 */
  }FBANK_TypeDef;

  /**
  * @brief  QSPI register
  */
  typedef struct
  {
      __IO uint32_t DMA_CTRL;             /*!< QSPI Dma Control Register              Address offset:0x00      */
      __IO uint32_t QSPI_CTRL;            /*!< QSPI Control Register                  Address offset:0x04      */
      __IO uint32_t QSPI_INS;             /*!< QSPI Instrction Register               Address offset:0x08      */
      __IO uint32_t QSPI_ADDR;            /*!< QSPI Address Register                  Address offset:0x0C      */
      __IO uint32_t QSPI_ALTER;           /*!< QSPI Alternate Register                Address offset:0x10      */
      __IO uint32_t QSPI_DATA_NUM;        /*!< QSPI Data Length Register              Address offset:0x14      */
      __IO uint32_t POLLING_REG;          /*!< QSPI Polling Status Register           Address offset:0x18      */
      __I  uint32_t AFIFO_STATUS;         /*!< QSPI Fifo Status Register              Address offset:0x1C      */
      __I  uint32_t QSPI_STATUS;          /*!< QSPI Status Register                   Address offset:0x20      */
      __O  uint32_t INT_MASK_SET;         /*!< QSPI Interrupt Mask Set Register       Address offset:0x24      */
      __O  uint32_t INT_MASK_CLR;         /*!< QSPI Interrupt Mask Clear Register     Address offset:0x28      */
      __I  uint32_t INT_MASK_STATUS;      /*!< QSPI Interrupt Mask Status Register    Address offset:0x2C      */
      __IO uint32_t INT_SR_PENDING;       /*!< QSPI Interrupt Pending Status Register Address offset:0x30      */
      __I  uint32_t RESERVED0[3];         /*!< Reserved0                              Address offset:0x34 - 3F */
      __IO uint32_t AFIFO_WDATA;          /*!< QSPI Write Fifo Register               Address offset:0x40      */
      __I  uint32_t AFIFO_RDATA;          /*!< QSPI Read Fifo Register                Address offset:0x44      */
      __IO uint32_t QSPI_PULSE;           /*!< QSPI Start and Stop Register           Address offset:0x48      */
      __IO uint32_t MAPPING_ACT;          /*!< QSPI Mapping Active Register           Address offset:0x4C      */
  }QSPI_TypeDef;

  /**
  * @brief  AFC register
  */
  typedef struct
  {
      __IO uint32_t CORE_CTRL;            /*!< AFC Frequency Target Register      Address offset:0x00        */
      __IO uint32_t CORE_EN;              /*!< AFC Enable Register                Address offset:0x04        */
      __IO uint32_t OP_RESULT;            /*!< AFC Op_Result Register             Address offset:0x08        */
      __I  uint32_t RESERVED0[61];        /*!< Reserved0                          Address offset:0x0C-0xFF   */
      __I  uint32_t AFC_FRE_CNT;          /*!< AFC Frequency count Register       Address offset:0x100       */
      __I  uint32_t CORE_TRIM_SIGNAL;     /*!< AFC Trim Signal Register           Address offset:0x104       */
      __I  uint32_t OP_DATA;              /*!< AFC Op_Data Register               Address offset:0x108       */
      __I  uint32_t RESERVED1[61];        /*!< Reserved1                          Address offset:0x10C-0x1FF */
      __O  uint32_t AFC_PULSE;            /*!< AFC Pulse Register                 Address offset:0x200       */
      __I  uint32_t RESERVED2[15];         /*!< Reserved2                         Address offset:0x204-0x23F */
      __O  uint32_t INT_MASK_SET;         /*!< AFC Interrupt Mask Set Register    Address offset:0x240       */
      __O  uint32_t INT_MASK_CLR;         /*!< AFC Interrupt Mask Clear Register  Address offset:0x244       */
      __O  uint32_t RESERVED3[1];;        /*!< Reserved3                          Address offset:0x248-0x24B */
      __I  uint32_t INT_MASK_STATUS;      /*!< AFC Interrupt Status Register      Address offset:0x24C       */
      __O  uint32_t INT_SR_PENDING;       /*!< AFC Status Register                Address offset:0x250       */
  }AFC_TypeDef;

  /**
  * @}
  */
  /* End of group Device_Peripheral_Registers */

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */
  
  /* Peripheral and SRAM base address */
#define EXTFLASH_BASE                       (0x09000000UL)                          /*!< (EXTFLASH  ) Base Address */
#define SRAM_BASE                           (0x30020000UL)                          /*!< (SRAM      ) Base Address */
#define PERIPH_BASE                         (0x40000000UL)                          /*!< (Peripheral) Base Address */
#define SCS_BASE                            (0xF0000000UL)                          /*!< (System    ) Base Address */
  
  /*!< Peripheral Memory Map */
#define APB0PERIPH_BASE                 (PERIPH_BASE + 0x00000000)
#define AHB1PERIPH_BASE                 (PERIPH_BASE + 0x10000000)
#define APB1PERIPH_BASE                 (PERIPH_BASE + 0x20000000)
  
  /*!< APB0 Peripheral Memory Map */
#define WDT_BASE                    (APB0PERIPH_BASE + 0x00000000)
#define RTC_BASE                    (APB0PERIPH_BASE + 0x00001000)
#define PMU_BASE                    (APB0PERIPH_BASE + 0x00002000)
  
  /*!< AHB1 Peripheral Memory Map */
#define DMA_BASE                    (AHB1PERIPH_BASE + 0x00000000)
#define FLASH_CTL_BASE              (AHB1PERIPH_BASE + 0x00001000)
#define RCC_BASE                    (AHB1PERIPH_BASE + 0X00002000)
#define AUDIO_BASE                  (AHB1PERIPH_BASE + 0x00003000)
#define FBANK_BASE                  (AHB1PERIPH_BASE + 0x00004000)

  /*!< APB1 Peripheral Memory Map */

#define QSPI_BASE                   (APB1PERIPH_BASE + 0x04000000)
#define GPIO_BASE                   (APB1PERIPH_BASE + 0x04001000)
#define NPU_BASE                    (APB1PERIPH_BASE + 0x04002000)
#define UART0_BASE                  (APB1PERIPH_BASE + 0x04004000)
#define UART1_BASE                  (APB1PERIPH_BASE + 0x04005000)
#define TIMER_BASE                  (APB1PERIPH_BASE + 0x04006000)
#define I2C_BASE                    (APB1PERIPH_BASE + 0x04007000)
#define I2S0_BASE                   (APB1PERIPH_BASE + 0x04008000) 
#define I2S1_BASE                   (APB1PERIPH_BASE + 0x04009000)
#define SPIM_BASE                   (APB1PERIPH_BASE + 0x0400a000)
#define PWM0_BASE                   (APB1PERIPH_BASE + 0x0400b000)
#define PWM1_BASE                   (APB1PERIPH_BASE + 0x0400c000)
#define AFC320K_BASE                (APB1PERIPH_BASE + 0x0400d000)
#define AFC24M_BASE                 (APB1PERIPH_BASE + 0x0400e000)  
#define SPIS_BASE                   (APB1PERIPH_BASE + 0x0400f000)

#define N307_JTAG_BASE              (SCS_BASE        + 0x00000)             /*!< (JTAG   ) Base Address */
#define N307_MTIMER_BASE            (SCS_BASE        + 0x10000)             /*!< (SysTimer)Base Address */
#define N307_ECLIC_ADDR_BASE        (SCS_BASE        + 0x20000)             /*!< (INTC   ) Base Address */

#define __SYSTIMER_BASEADDR         N307_MTIMER_BASE
#define __ECLIC_BASEADDR            N307_ECLIC_ADDR_BASE

  /**
  * @}
  */
  
  /** @addtogroup Peripheral_Declaration
  * @{
  */
#define WDT                             ((WDT_TypeDef *) WDT_BASE)
#define RTC                             ((RTC_TypeDef *) RTC_BASE)
#define PMU                             ((PMU_TypeDef *) PMU_BASE)

#define DMA                             ((DMA_TypeDef *) DMA_BASE)
#define FLASH                           ((FLASH_TypeDef *) FLASH_CTL_BASE)
#define RCC                             ((RCC_TypeDef *) RCC_BASE)
#define AUD                             ((AUD_TypeDef *) AUDIO_BASE)
#define FBANK                           ((FBANK_TypeDef *) FBANK_BASE)

#define QSPI                            ((QSPI_TypeDef *)(QSPI_BASE))
#define GPIOA                           ((GPIO_TypeDef *) GPIO_BASE)
#define UART0                           ((UART_TypeDef *) UART0_BASE)
#define UART1                           ((UART_TypeDef *) UART1_BASE)
#define TIMER0                          ((TMR_TypeDef *) (TIMER_BASE + 0x00))
#define TIMER1                          ((TMR_TypeDef *) (TIMER_BASE + 0x14))
#define TIMER2                          ((TMR_TypeDef *) (TIMER_BASE + 0x28))
#define TIMER3                          ((TMR_TypeDef *) (TIMER_BASE + 0x3c))
#define TIMERS                          ((TMR_TINT_PWM_TypeDef *) (TIMER_BASE + 0xa0))
#define I2C                             ((I2C_TypeDef *) I2C_BASE)
#define I2S0                            ((I2S_TypeDef *) I2S0_BASE)
#define I2S1                            ((I2S_TypeDef *) I2S1_BASE)
#define SPIM                            ((SPI_TypeDef *)(SPIM_BASE))
#define PWM0                            ((PWM_TypeDef *) PWM0_BASE)
#define PWM1                            ((PWM_TypeDef *) PWM1_BASE)
#define AFC320k                         ((AFC_TypeDef *) AFC320K_BASE)
#define AFC24M                          ((AFC_TypeDef *) AFC24M_BASE)
#define SPIS                            ((SPI_TypeDef *)(SPIS_BASE))
  /**
  * @}
  */
  
  /** @addtogroup Exported_types
  * @{
  */ 
  
  /** @defgroup IT_Flag_Status IT Flag Status
  * @brief IT Flag Status enumeration
  * @{
  */
  typedef enum
  {
    RESET = 0U,
    SET = !RESET
  } FlagStatus,ITStatus;
  /**
  * @}
  */
  
  /** @defgroup FunctionalState 
  * @brief State enumeration
  * @{
  */
  typedef enum
  {
    DISABLE = 0U,
    ENABLE = !DISABLE
  } FunctionalState;
  /**
  * @}
  */
  
  /** @defgroup Bool
  * @brief Bool enumeration
  * @{
  */
  typedef enum
  {
    FALSE = 0U,
    TRUE = !FALSE
  } Bool;
  /**
  * @}
  */

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
  
  
  
  /**
  * @}
  */
  
  /** @addtogroup Exported_macros
  * @{
  */
  /******************************* RCC Instances *******************************/
#define IS_RCC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == RCC)
  
  /******************************* PMU Instances *******************************/
#define IS_PMU_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PMU)
  
  /******************************* GPIO Instances *******************************/
#define IS_GPIO_ALL_INSTANCE(INSTANCE) ((INSTANCE) == GPIOA)
  
  /******************************* UART Instances *******************************/
#define IS_UART_ALL_INSTANCE(INSTANCE) (((INSTANCE) == UART0)||((INSTANCE) == UART1))
  
  /******************************* I2C Instances ********************************/
#define IS_I2C_ALL_INSTANCE(INSTANCE) ((INSTANCE) == I2C)
  
  /******************************* I2S Instances ********************************/
#define IS_I2S_ALL_INSTANCE(INSTANCE) (((INSTANCE) == I2S0)||((INSTANCE) == I2S1))

  /******************************* PWM Instances ********************************/
#define IS_PWM_ALL_INSTANCE(INSTANCE) (((INSTANCE) == PWM0)||((INSTANCE) == PWM1))

  /******************************* AUD Instances ********************************/
#define IS_AUD_ALL_INSTANCE(INSTANCE) ((INSTANCE) == AUD)
  
  /******************************* PMU Instances ********************************/
#define IS_PMU_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PMU)

  /******************************* DMA Instances ********************************/
#define IS_DMA_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DMA)

  /******************************* FBANK Instances ********************************/
#define IS_FBANK_ALL_INSTANCE(INSTANCE) (((INSTANCE) == FBANK))

  /******************************* QSPI Instances ********************************/
#define IS_QSPI_ALL_INSTANCE(INSTANCE) ((INSTANCE) == QSPI)

  /******************************* RTC Instances ********************************/
#define IS_RTC_ALL_INSTANCE(INSTANCE) (((INSTANCE) == RTC))

  /******************************* SPI Instances ********************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE) ((INSTANCE) == SPIM || (INSTANCE) == SPIS)

  /******************************* TIMER Instances ********************************/
#define IS_TIMER_ALL_INSTANCE(INSTANCE) ((INSTANCE) == TIMER0||(INSTANCE) == TIMER1 ||(INSTANCE) == TIMER2 || (INSTANCE) == TIMER3)

  /******************************* WDT Instances ********************************/
#define IS_WDT_ALL_INSTANCE(INSTANCE) (((INSTANCE) == WDT))

  /******************************* AFC Instances ********************************/
#define IS_AFC_ALL_INSTANCE(INSTANCE) (((INSTANCE) == AFC320k) || (INSTANCE) == AFC24M)
  /**
  * @}
  */
  
#include "WTM2101_assert.h"
#include <nmsis_core.h>
#include <wtm2101_system.h>

#include "WTM2101_AFC_24M_register.h"
#include "WTM2101_AFC_320K_register.h"
#include "WTM2101_AUDIO_register.h"
#include "WTM2101_DMAC_register.h"
#include "WTM2101_FBANK_register.h"
#include "WTM2101_GPIO_register.h"
#include "WTM2101_I2C_register.h"
#include "WTM2101_I2S_register.h"
#include "WTM2101_PMU_register.h"
#include "WTM2101_PWM_register.h"
#include "WTM2101_QSPI_register.h"
#include "WTM2101_RCC_register.h"
#include "WTM2101_RTC_register.h"
#include "WTM2101_SPI_register.h"
#include "WTM2101_TIMER_register.h"
#include "WTM2101_UART_register.h"
#include "WTM2101_WDT_register.h"


// yL, patch-2024.06.06
// begin ///////////////////////////////////////////////////////////////////////
#ifndef   __NOINLINE
  #define __NOINLINE                __attribute__((noinline))
#endif

#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE           static inline
#endif

#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE      __attribute__((always_inline)) static inline
#endif
// end /////////////////////////////////////////////////////////////////////////



#ifdef __cplusplus
}
#endif

#endif  /* __WTM2101_H__ */

/** @}
*/
/* End of group WITIN_WTM2101_AI_CHIP */
