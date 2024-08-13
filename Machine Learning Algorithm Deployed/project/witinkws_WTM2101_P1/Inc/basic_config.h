#ifndef BB04P1_BASIC_CONFIG_H
#define BB04P1_BASIC_CONFIG_H

#include "WTM2101.h"



////////////////////////////////////////////////////////////////////////////////
//
//  project
//
//  make sure BOOT=QSPI_MODE when QSPI_xxx config
//  make sure BOOT=RAM_MODE  when RAM_xxx  config
#define PRINTF_RETARGER_NONE    0
#define PRINTF_RETARGER_UART0   1
#define PRINTF_RETARGER_UART1   2
#define PRINTF_RETARGER_SEGGER  3 

#if defined(CONFIG_RAM_K1_IISMIC_REALTIME_HSI24Mx2) || \
    defined(CONFIG_QSPI_K1_IISMIC_REALTIME_HSI24Mx2)
#define LED_PIN                 GPIO_PIN_0
#define LED_AF                  GPIO_AF0_GPIO
#else
#define LED_PIN                 GPIO_PIN_0
#define LED_AF                  GPIO_AF0_GPIO
#endif
#define BUTTON_PIN              GPIO_PIN_11
#define BUTTON_AF               GPIO_AF11_GPIO


////////////////////////////////////////////////////////////////////////////////
// Configuration BEGIN
//
//
//  FORCE_DVDDC_TO_0V9          force Core LDO output 0.9V
//  NOT_FORCE_DVDDC_TO_0V9      output 0.9V when freq <= 50MHz, else output 1.1V
//
//
//  DATA_FROM_UART              Denoise data from uart, and send back to uart
//  NOT_DATA_FROM_UART          Realtime denoise, recording from audio, sending to I2S
//  - UART_SEND_STEP            --- DO NOT CHANGE ---
//  - UART_RECEIVE_STEP         --- DO NOT CHANGE ---
//
//
//  UART_BAUDRATE               UART baud
//
//
//  USE_UART_LP_MODE            enable UART peripheral when use, disable when sent
//  NOT_USE_UART_LP_MODE        keep UART clock ON
//
//
//  USE_HSI                     SoC sysclock from internal OSC,
//                              calibrate with external 32.768KHz XTL
//                              when startup.
//  NOT_USE_HSI                 SoC sysclock from external XTL
//
//  USE_OSC_CALIBRATE           Enable calibrate when using internal osc (HSI)
//  NOT_USE_OSC_CALIBRATE
//
//  USE_PLL_CLOCK               Enable PLL, and sysclock from PLL
//  - PLL_N                     the PLL multi factor, valid when USE_PLL_CLOCK exists
//  NOT_USE_PLL_CLOCK           Enable PLL, and sysclock from PLL
//
//
//  USE_NPU_24M                 the selection of NPU analog config headers 
//  USE_NPU_32M                 each macro will include a different analog config.
//  USE_NPU_36M
//  ...
//  USE_NPU_72M
//
//
//  USE_I2S_OUT                 enable I2S peripheral and output
//  - USE_I2S_32BITS            I2S output bitswidth is 32bits
//  - NOT_USE_I2S_32BITS        I2S output bitswidth is 16bits
//
//  - USE_I2S_MASTER            I2S master mode
//  - NOT_USE_I2S_MASTER        I2S slave mode
//
//  - USE_I2S_SLAVE             I2S slave mode
//  - NOT_USE_I2S_SLAVE         I2S master mode
//
//  - I2S_AND_AUD_SAME_FREQ     calculate I2S PCM freq from Actual Audio freq
//
//  - USE_I2S_DVFS              dynamic change AHB or APB clkdiv
//  - NOT_USE_I2S_DVFS          disable DVFS
//
//  NOT_USE_I2S_OUT             no I2S output
//
//
//  USE_SWITCH                  using GPIO1 to select Transparency or Denoise mode
//  NOT_USE_SWITCH              not selectable
//
//
//  QSPI_BOOT                   the firmware is build for QSPI boot mode
//  NOT_QSPI_BOOT               the firmware is build for SRAM boot mode
//

// bb04p1_hal.h
extern uint32_t HAL_GetTick(void);

////////////////////////////////////////////////////////////////////////////////

#include "config_common.h"
#include "config_ram_iismic_realtime_hsi24mx4.h"


////////////////////////////////////////////////////////////////////////////////
// Configuration END
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  self-check macros relation
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#if defined(USE_EXTRA_MASK) && defined(NOT_USE_EXTRA_MASK)
#error "both USE_EXTRA_MASK and NOT_USE_EXTRA_MASK defined"
#endif

#if !defined(USE_EXTRA_MASK) && !defined(NOT_USE_EXTRA_MASK)
#error "define USE_EXTRA_MASK or NOT_USE_EXTRA_MASK please"
#endif

#if defined(USE_EXTRA_MASK) && !defined(MASKTYPE)
#error "define MASKTYPE please"
#endif


#if defined(USE_IN_MASK_SMOOTH) && defined(NOT_USE_IN_MASK_SMOOTH)
#error "both USE_IN_MASK_SMOOTH and NOT_USE_IN_MASK_SMOOTH defined"
#endif

#if !defined(USE_IN_MASK_SMOOTH) && !defined(NOT_USE_IN_MASK_SMOOTH)
#error "define USE_IN_MASK_SMOOTH or NOT_USE_IN_MASK_SMOOTH please"
#endif

#if defined(USE_IN_MASK_SMOOTH) && !defined(MASKSMOOTH)
#error "define MASKSMOOTH please"
#endif


//
//  make sure we use correct npu clock
//
#if !defined(NPU_CLKDIV) && !defined(NOT_NPU_CLKDIV)
 #if defined(USE_PLL_CLOCK)
  #if defined(USE_NPU_24M) && (PLL_N != 1)
   #define NPU_CLKDIV    PLL_N
  #else
   #define NOT_NPU_CLKDIV
  #endif
 #else
  #define NOT_NPU_CLKDIV
 #endif
#endif


////////////////////////////////////////////////////////////
//
//  UART macros
//
#ifndef UART_BAUDRATE // default baud
#define UART_BAUDRATE           115200
#endif

#ifndef CONFIG_MODE
#error "missing CONFIG_xxx or macro not match"
#endif


#ifndef USE_PRINTF
#error "missing USE_PRINTF macro"
#endif


#ifdef AUDIO_ENABLE
#undef AUDIO_ENABLE
#endif

#if defined(USE_AMIC)
 #define AUDIO_ENABLE

#elif defined(USE_DMIC)
 #if defined(AUDIO_CLK_PIN) && defined(AUDIO_DATA_PIN)
 #define AUDIO_ENABLE
 #endif

#elif defined(NOT_USE_AMIC) || defined(NOT_USE_DMIC)
 #ifdef AUDIO_CLK_PIN
 #undef AUDIO_CLK_PIN
 #endif
 #ifdef AUDIO_DATA_PIN
 #undef AUDIO_DATA_PIN
 #endif

#else
 #error "define one of macors: USE_AMIC, USE_DMIC, NOT_USE_AMIC, NOT_USE_DMIC please"

#endif


//#ifdef UART_ENABLE
//#undef UART_ENABLE
//#endif

#if defined(UART0_TX_PIN) || defined(UART0_RX_PIN)
 #define UART0_ENABLE
#endif

#if defined(UART1_TX_PIN) || defined(UART1_RX_PIN)
 #define UART1_ENABLE
#endif



////////////////////////////////////////////////////////////
//
//  I2S macros
//
//
//  USE_I2S_OUT: enable I2S output
//  NOT_USE_I2S_OUT: disable I2S peripheral
//
#if defined(USE_I2S_OUT) && defined(NOT_USE_I2S_OUT)
#error "both USE_I2S_OUT and NOT_USE_I2S_OUT defined"
#endif

#if !defined(USE_I2S_OUT) && !defined(NOT_USE_I2S_OUT)
#error "define USE_I2S_OUT or NOT_USE_I2S_OUT please"
#endif

#if defined(USE_I2S_IN) && defined(NOT_USE_I2S_IN)
#error "both USE_I2S_IN and NOT_USE_I2S_IN defined"
#endif

#if !defined(USE_I2S_IN) && !defined(NOT_USE_I2S_IN)
#error "define USE_I2S_IN or NOT_USE_I2S_IN please"
#endif



#ifdef I2S_ENABLE
#undef I2S_ENABLE
#endif

#if defined(USE_I2S_OUT) || defined(USE_I2S_IN)
 //#define I2S_ENABLE
#endif


// just keep 32bits macro
// delete 16bits macro
#if defined(USE_I2S_16BITS)
 #undef USE_I2S_16BITS
 
 #ifdef USE_I2S_32BITS
 #undef USE_I2S_32BITS
 #endif
 #ifndef NOT_USE_I2S_32BITS
 #define NOT_USE_I2S_32BITS
 #endif
#endif

#if defined(NOT_USE_I2S_16BITS)
 #undef NOT_USE_I2S_16BITS
 
 #ifndef USE_I2S_32BITS
 #define USE_I2S_32BITS
 #endif
 #ifdef NOT_USE_I2S_32BITS
 #undef NOT_USE_I2S_32BITS
 #endif
#endif

#if defined(USE_I2S_OUT) || defined(USE_I2S_IN)
 #if defined(USE_I2S_32BITS) && defined(NOT_USE_I2S_32BITS)
 #error "both USE_I2S_32BITS and NOT_USE_I2S_32BITS defined"
 #endif

 #if !defined(USE_I2S_32BITS) && !defined(NOT_USE_I2S_32BITS)
 #error "define USE_I2S_32BITS or NOT_USE_I2S_32BITS please"
 #endif

 // ------ master or slave mode ------
 #if defined(USE_I2S_MASTER) && defined(USE_I2S_SLAVE)
 #error "both USE_I2S_MASTER and USE_I2S_SLAVE defined"
 #endif

 #if defined(NOT_USE_I2S_MASTER) && defined(NOT_USE_I2S_SLAVE)
 #error "both NOT_USE_I2S_MASTER and NOT_USE_I2S_SLAVE defined"
 #endif

 // --- check master mode
 #if defined(USE_I2S_MASTER)
 #ifndef NOT_USE_I2S_SLAVE
 #define NOT_USE_I2S_SLAVE
 #endif
 #endif

 #if defined(NOT_USE_I2S_MASTER) && !defined(USE_I2S_SLAVE)
 #define USE_I2S_SLAVE
 #endif

 // --- check slave mode
 #if defined(USE_I2S_SLAVE)
 #ifndef NOT_USE_I2S_MASTER
 #define NOT_USE_I2S_MASTER
 #endif
 #endif

 #if defined(NOT_USE_I2S_SLAVE) && !defined(USE_I2S_MASTER)
 #define USE_I2S_MASTER
 #endif

 // --- final check
 #if defined(USE_I2S_MASTER) && defined(NOT_USE_I2S_MASTER)
 #error "both USE_I2S_MASTER and NOT_USE_I2S_MASTER defined"
 #endif

 #if !defined(USE_I2S_MASTER) && !defined(NOT_USE_I2S_MASTER)
 #error "define USE_I2S_MASTER or NOT_USE_I2S_MASTER please"
 #endif

 #if defined(USE_I2S_SLAVE) && defined(NOT_USE_I2S_SLAVE)
 #error "both USE_I2S_SLAVE and NOT_USE_I2S_SLAVE defined"
 #endif

 #if !defined(USE_I2S_SLAVE) && !defined(NOT_USE_I2S_SLAVE)
 #error "define USE_I2S_SLAVE or NOT_USE_I2S_SLAVE please"
 #endif
#endif

////////////////////////////////////////////////////////////
//
//  SPI macros
//
#ifdef SPI_ENABLE
#undef SPI_ENABLE
#endif

#if defined(SPI0_SCLK_PIN)
#define SPI_ENABLE
#endif


////////////////////////////////////////////////////////////
//
//  NPU macros
//
//
//  USE_NPU_DIFF: enable npu dynamic compensate algorithm
//  NOT_USE_NPU_DIFF: disable dynamic compensate
//
#if defined(USE_NPU_DIFF) && defined(NOT_USE_NPU_DIFF)
#error "both USE_NPU_DIFF and NOT_USE_NPU_DIFF defined"
#endif

#if !defined(USE_NPU_DIFF) && !defined(NOT_USE_NPU_DIFF)
#error "define USE_NPU_DIFF or NOT_USE_NPU_DIFF please"
#endif


////////////////////////////////////////////////////////////
//
//  Etc.
//
//
//  USE_PLL_CLOCK: enable PLLx6 (147MHz) as default sysclock
//  NOT_USE_PLL_CLOCK: using internal OSC (24.576MHz) as default sysclock
//
#if defined(USE_PLL_CLOCK) && defined(NOT_USE_PLL_CLOCK)
#error "both USE_PLL_CLOCK and NOT_USE_PLL_CLOCK defined"
#endif

#if !defined(USE_PLL_CLOCK) && !defined(NOT_USE_PLL_CLOCK)
#error "define USE_PLL_CLOCK or NOT_USE_PLL_CLOCK please"
#endif

#if defined(USE_PLL_CLOCK) && !defined(PLL_N)
#error "missing PLL_N when USE_PLL_CLOCK exists"
#endif

#if defined(USE_DCCRN) && defined(NOT_USE_DCCRN)
#error "both USE_DCCRN and NOT_USE_DCCRN defined"
#endif

#if !defined(USE_DCCRN) && !defined(NOT_USE_DCCRN)
#error "define USE_DCCRN or NOT_USE_DCCRN please"
#endif



//
//  DATA_FROM_UART must enable PLL to speed up xfer baud (921600)
//
//#if defined(DATA_FROM_UART) && !defined(USE_PLL_CLOCK)
//#error "not define `USE_PLL_CLOCK` when DATA_FROM_UART exists, UART will be low speed"
//#endif

#if defined(DATA_FROM_UART) && !defined(USE_DCCRN)
#error "expect USE_DCCRN defined when DATA_FROM_UART exists"
#endif

//#if !defined(DATA_FROM_UART) && !defined(AUDIO_ENABLE)
//#error "Audio mode must enable when DATA_FROM_UART disabled"
//#endif

//#if !defined(DATA_FROM_UART) && !defined(I2S_ENABLE)
//#error "I2S mode must enable when DATA_FROM_UART disabled"
//#endif


//
//  HSI and HSE
//
#if defined(USE_HSE) && defined(USE_HSI)
#error "both USE_HSE and USE_HSI defined"
#endif

#ifdef USE_HSE
 #ifndef NOT_USE_HSI
 #define NOT_USE_HSI
 #endif
#endif

#ifdef USE_HSI
 #ifndef NOT_USE_HSE
 #define NOT_USE_HSE
 #endif
#endif

#if defined(USE_HSI) && defined(NOT_USE_HSI)
#error "both USE_HSI and NOT_USE_HSI defined"
#endif

#if !defined(USE_HSI) && !defined(NOT_USE_HSI)
#error "define USE_HSI or NOT_USE_HSI please"
#endif

#if defined(USE_HSE) && defined(NOT_USE_HSE)
#error "both USE_HSE and NOT_USE_HSE defined"
#endif

#if !defined(USE_HSE) && !defined(NOT_USE_HSE)
#error "define USE_HSE or NOT_USE_HSE please"
#endif

#ifndef HSI_VALUE
#error "missing HSI_VALUE"
#endif

#ifndef HSE_VALUE
#error "missing HSE_VALUE"
#endif

#ifdef USE_HSI
 #if HSI_VALUE != 24576000
 #error "HSI_VALUE must be 24576000 when use HSI"
 #endif
 //#if HSE_VALUE != 24576000
 //#error "HSE_VALUE must be 24576000 when use HSI"
 //#endif
#endif



////////////////////////////////////////////////////////////////////////////////
//
//  DMA limits
//
#ifndef DMA_MAX_BLK_SIZE
#define DMA_MAX_BLK_SIZE          255
#endif

#ifndef DMA_MAX_LLP_COUNT
#define DMA_MAX_LLP_COUNT         20
#endif

#ifndef DMA_MAX_CHANNELS
#define DMA_MAX_CHANNELS          6
#endif




////////////////////////////////////////////////////////////////////////////////
//
//  UART macros
//
//
//  acceptable bauderr < 3%
//  CP2102: 48M/4/115200 = 104.16 ~= 104 (bauderr = +0.16%) 
//  CP2102: 48M/4/921600 =  13.02 ~=  13 (bauderr = +0.15%) 
//
//#if defined(DATA_FROM_UART) && defined(UART_ENABLE)
//  #define USE_UART_DMA
//  #define DMA_UART0_RXCHANNEL         DMA_CHANNEL5
//  //#define DMA_UART0_TXCHANNEL       // unused
//  //#define DMA_UART1_RXCHANNEL       // unused
//  //#define DMA_UART1_TXCHANNEL       // unused
//#else
//  #define NOT_USE_UART_DMA
//#endif


////////////////////////////////////////////////////////////////////////////////
//
//  Audio
//
#ifdef AUDIO_ENABLE
  //
  //    DMA_max_count/block <= 255, using LLP-mode when count > 255!
  //    AUDIO data size 16bits, read 32bits per time
  //
  //#define AUDIO_GAIN                16
  //#define AUDIO_GAIN                14
  //#define AUDIO_GAIN                12
  //#define AUDIO_GAIN                10
  //#define AUDIO_GAIN                9
  //#define AUDIO_GAIN                8
  //#define AUDIO_GAIN                7
  //#define AUDIO_GAIN                6
  
  //--- full range 27bits ---
  //#define AUDIO_GAIN                4 // bits:27..12
  //#define AUDIO_GAIN                6 // bits:26..11
  //#define AUDIO_GAIN                10// bits:24..9
  //#define AUDIO_GAIN                12// bits:23..8

  #ifndef AUDIO_GAIN
   #ifdef USE_DMIC
   #define AUDIO_GAIN                16
   #endif
   #ifdef USE_AMIC
   #define AUDIO_GAIN                14
   #endif
  #endif

  #define AUDIO_FIFO_DEPTH          960 // 480 x 32bits, BB04P1 32bits access
  #define AUDIO_DMA_CHANNEL         DMA_CHANNEL0            // DONT change
  #define AUDIO_DMA_INT_FLAG        DMA_CHANNEL0_INT_FLAG   // DONT change
  #define AUDIO_SAMPELS_PER_BLOCK   PCM_FRAME_SIZE
//  #define AUDIO_FRAME_SIZE          (PCM_FRAME_SIZE*1)      // 1 x frames
  #define AUDIO_DMA_COUNT           (AUDIO_FRAME_SIZE/2)    // 32bits read-write
#endif


////////////////////////////////////////////////////////////////////////////////
//
//  I2S macros predeinfes
//
#ifdef I2S_ENABLE
  // audio half frame per block: 160/2 == 80 (L+R) frames per I2S DMA block
  // 8 x PCM_FRAME_SIZE buffer with L+R
  #ifndef I2S_AND_AUD_SAME_FREQ
   #define I2S_FREQ                 16000
  #endif
  #define I2S_SAMPLES_PER_BLK       (PCM_FRAME_SIZE/2)      // 80 samples
  #define I2S_BLOCK_SIZE            (I2S_SAMPLES_PER_BLK*2) // L + R

  #define I2STX_NR_BLOCKS           16
  #define I2STX_MOD                 (I2S_SAMPLES_PER_BLK*I2STX_NR_BLOCKS/AUDIO_FRAME_SIZE)

  #define I2SRX_NR_BLOCKS           8
  #define I2SRX_MOD                 (I2S_SAMPLES_PER_BLK*I2SRX_NR_BLOCKS/AUDIO_FRAME_SIZE)
#endif

#if defined(I2S_ENABLE) && !defined(I2STX_32BITS_ASL)
  // MAX98357 included PA, `<= 12`
  // PCM5102 better value 16

  //#define I2STX_32BITS_ASL          12
#endif


////////////////////////////////////////////////////////////////////////////////
//
//  clock calibration ref
//
extern uint32_t osc24m_clock;
extern uint32_t osc320k_clock;

extern uint32_t printf_retarger_type;

#endif
