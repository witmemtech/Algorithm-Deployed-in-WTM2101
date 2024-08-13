#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wtm2101_config.h>
#include "WTM2101.h"
#include <bb04p1_hal.h>

#include <basic_config.h>

#include "osc_clock_calibration.h"

#include "gpio.h"
#include "main.h"
#include "spi.h"

static volatile uint32_t _hsi_trim_freq = 0;
static volatile uint32_t _lsi_trim_freq = 0;

// osc_clock_calibration.c
extern uint32_t m_24m_trim_coarse;
extern uint32_t m_24m_trim_fine;
extern uint32_t m_320k_trim_coarse;
extern uint32_t m_320k_trim_fine;


//  void HAL_Init(void) {
//      uint32_t mctl = 0;
//  
//      SysTick_Config(SYSTICK_VALUE);
//  
//      // after SysTick_Config, SysTimer_IRQn enabled
//      // !!! DO NOT enable RV32 Interrupt in this function !!!
//      ECLIC_DisableIRQ(SysTimer_IRQn);
//      SysTimer_SetControlValue(SysTimer_MTIMECTL_TIMESTOP_Msk);
//  
//      //`MTIMECTL`, alias name `MSTOP`
//      //
//      //## Correct setting
//      //  bit0:timestop == 0
//      //  bit1:cmpclren == 0
//      //  bit2:clksrc   == 1
//      //
//      //  always@(posedge clk)
//      //  begin
//      //      if (timestop)
//      //          mtime_r <= mtime_r;
//      //      else if (clksrc)
//      //          mtime_r <= mtime_r + 64'b1;
//      //      else
//      //          mtime_r <= edges_of(rtctick);
//      //  end
//      //
//      //## Default POR setting
//      //  bit0:timestop == 0
//      //  bit1:cmpclren == 0
//      //  bit2:clksrc   == 0
//      //
//      //  always@(posedge clk)
//      //  begin
//      //      systick_cnt[3:0] <= systick_cnt[3:0] + 4'd1;
//      //  end
//      //
//      //  assign rtctick = systick_cnt[3];
//      //
//      //  the mtimer source will be 24MHz/8 = 3MHz :)
//      //
//      ECLIC_SetPriorityIRQ(SysTimer_IRQn, 2);
//      mctl &= ~SysTimer_MTIMECTL_TIMESTOP_Msk;
//      mctl |= SysTimer_MTIMECTL_CLKSRC_Msk;
//  
//  #ifdef CONFIG_ENABLE_SYSTICK_AUTORELOAD
//      //
//      //  counter automatic clear mode,
//      //  interrupt have to capture edge.
//      //
//      ECLIC_SetTrigIRQ(SysTimer_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
//      mctl |= SysTimer_MTIMECTL_CMPCLREN_Msk;
//  #else
//      //
//      //  counter increase always,
//      //  user must reload next compare value in ISR:
//      //
//      //      void SysTick_IRQHandler(void)
//      //      {
//      //          SysTick_Reload(TIMER_TICKS);
//      //      }
//      //
//      ECLIC_SetTrigIRQ(SysTimer_IRQn, ECLIC_LEVEL_TRIGGER);
//  #endif
//  
//      SysTimer_SetControlValue(mctl);
//  
//      ECLIC_EnableIRQ(SysTimer_IRQn);
//  }

void HAL_Peripherals_Reset(void)
{
    // Asynchronous reset, Synchronous release
    //
    //  RCC_Peri_Rst generate reset pluse.
    //  Peripheral need system clock to release reset state,
    //  else peripheral will keep reset.
    //

    // close all
    RCC_CLK_EN_Ctl(
            //RCC_GPIO_HCLKEN |  // gpio 关闭会导致uart输出不正常
            RCC_FLASH_CLKEN | RCC_FLASH_REG_CLKEN | RCC_DMA_CLKEN |
            RCC_WDT_PCLKEN | RCC_RTC_PCLKEN |
            RCC_UART0_CLKEN | RCC_UART1_CLKEN | RCC_I2C_PCLKEN | RCC_TIME_CLKEN |
            RCC_I2S1_CLKEN | RCC_SPIM_PCLKEN | RCC_QSPI_PCLKEN | 
            RCC_PWM0_CLKEN | RCC_PWM1_CLKEN | RCC_DB_CLKEN | RCC_FFT_CLKEN | 
            RCC_AUD_CLKEN | RCC_I2S_MCLKEN | RCC_TRIM_CLKEN | RCC_AUD_PCLKEN |
            RCC_SPIS_PCLKEN | RCC_I2S0_CLKEN | RCC_DAC_CLKEN | RCC_EXTFLASH_CLKEN,
            DISABLE);

    //open nesscessary
    RCC_CLK_EN_Ctl(
            RCC_PMU_PCLKEN | 
            RCC_AHB1_CLKEN | 
            RCC_AHB2_CLKEN | 
            RCC_APB0_CLKEN, 
            ENABLE);
}


uint32_t HAL_GetTick(void)
{
    const uint64_t AHBCLOCK = RCC_Get_SYSClk() / (RCC_AHB_Get_ClkDiv() + 1);
    uint64_t cycles = __get_rv_cycle();
    uint64_t ticks = cycles / (AHBCLOCK / 1000);
    return ticks;
}

void HAL_Delay(uint32_t ms)
{
    const uint64_t AHBCLOCK = RCC_Get_SYSClk() / (RCC_AHB_Get_ClkDiv() + 1);
    uint64_t duration = ms * AHBCLOCK/1000;
    uint64_t cycles0 = __get_rv_cycle();
    uint64_t cycles1 = 0;

    do {
        cycles1 = __get_rv_cycle();
    } while (cycles1 - cycles0 < duration);
}

void HAL_Enable_CLKIN(void)
{
    // HTAL PAD config
    //
    //  - bit3: PAD.XTAL_IN.schmitt
    //  - bit4: PAD.XTAL_IN.input

    //0x64001000, GPIOA
    //0x64001010, GPIOA::PAD_RESV
    GPIOA->PAD_RESV |= (1 << 3)|(1 << 4);
    PMU_Select_24Mhz_Clock_Cmd(PMU, XTL_EXTERNAL_24M);
}

void HAL_Disable_CLKIN(void)
{
    // HTAL PAD config
    //
    //  - bit3: PAD.XTAL_IN.schmitt
    //  - bit4: PAD.XTAL_IN.input
    GPIOA->PAD_RESV &= ~((1 << 3)|(1 << 4));
}

void HAL_Config_Internal10K(void)
{
    PMU_Set_Clock_Source_Cmd(PMU, _24M | OSC_10K | OSC_320K | XTL32K | PLL, ENABLE);
    PMU_Enable_External_Clock(PMU, ENABLE);
    RCC_SYSClk_Sel(RCC_SYSCLK_Int160K);
    RCC_AHB_Set_ClkDiv(0);
    RCC_APB0_Set_ClkDiv(0);

    HAL_Disable_CLKIN();
    PMU_Select_24Mhz_Clock_Cmd(PMU, OSC_INTERNAL_24M);
    system_delay_ms(10);
    RCC_SYSClk_Sel(RCC_SYSCLK_Int10K);

    PMU_Enable_External_Clock(PMU, DISABLE); // disable external clock PAD
}

void HAL_Config_Internal160K(void)
{
    PMU_Set_Clock_Source_Cmd(PMU, _24M | OSC_10K | OSC_320K | XTL32K | PLL, ENABLE);
    PMU_Enable_External_Clock(PMU, ENABLE);
    RCC_SYSClk_Sel(RCC_SYSCLK_Int160K);
    RCC_AHB_Set_ClkDiv(0);
    RCC_APB0_Set_ClkDiv(0);

    HAL_Disable_CLKIN();
    PMU_Select_24Mhz_Clock_Cmd(PMU, OSC_INTERNAL_24M);
    system_delay_ms(10);
    RCC_SYSClk_Sel(RCC_SYSCLK_Int160K);

    PMU_Enable_External_Clock(PMU, DISABLE); // disable external clock PAD
}

void HAL_Config_External32K(void)
{
    PMU_Set_Clock_Source_Cmd(PMU, _24M | OSC_10K | OSC_320K | XTL32K | PLL, ENABLE);
    PMU_Enable_External_Clock(PMU, ENABLE);
    RCC_SYSClk_Sel(RCC_SYSCLK_Int160K);
    RCC_AHB_Set_ClkDiv(0);
    RCC_APB0_Set_ClkDiv(0);

    HAL_Enable_CLKIN();
    PMU_Select_24Mhz_Clock_Cmd(PMU, OSC_INTERNAL_24M);
    //system_delay_ms(10);
    RCC_SYSClk_Sel(RCC_SYSCLK_Ext32K);
}

//VOL0  TRIM    Voltage     Actual
//----------------------------------
//0     x       0.90V       0.90V
//1     1       1.06V       1.12V
//1     2       1.08V       1.13V
//1     3       1.09V       1.14V
//1     0       1.10V       1.15V
//1     4       1.13V       1.17V
//1     5       1.15V       1.18V
//1     6       1.17V       1.19V
//1     7       1.18V       1.20V
//
void HAL_Change_DVDDC(dvddc_voltage_t vol)
{
    uint32_t val;

    // TRIM0      := 0x4000_2040
    val = 0;
    if (vol & 0x10) {
        val |= ((vol & 0x7) << PMU_TRIM0_LDO_PMUVDD_TRIM_VSEL_Pos) & PMU_TRIM0_LDO_PMUVDD_TRIM_VSEL_Msk;
    }
    PMU->TRIM0 = val;

    // VOL_UPDATE := 0x4000_2020
    val |= PMU_VOL_UPDATE_VOL1_UPDATE_VALUE_Msk; // default 1'b1
    if (vol & 0x10) {
        val |= PMU_VOL_UPDATE_VOL0_UPDATE_VALUE_Msk;
    }
    val |= PMU_VOL_UPDATE_VOL_UPDATE_Msk;        // enable Voltage change

    PMU->VOL_UPDATA = val; // header typo actual `UPDATE` :(
}

void HAL_Reset_PLL(void)
{
    uint32_t val;

    // howto: disable PLL, clear flags, then change PLLdiv
    //
    // --- por default (begin) ---
    //  val = 0;
    //  val |= (3 << PMU_PLL_0_PLL_DIG_CUR_SEL_Pos) & PMU_PLL_0_PLL_DIG_CUR_SEL_Msk;
    //  val |= (1 << PMU_PLL_0_PLL_CP_CUR_SEL_Pos) & PMU_PLL_0_PLL_CP_CUR_SEL_Msk;
    //  PMU->PLL_0 = val;
    // --- por default (end) ---
    //
    // val = (2 << 3) | (3 << 1)
    //     = 0x16
    //
    // PLL_0 := 0x4000_2070
    //
    val = 0;
    val |= (2 << PMU_PLL_0_PLL_DIG_CUR_SEL_Pos) & PMU_PLL_0_PLL_DIG_CUR_SEL_Msk;
    val |= (3 << PMU_PLL_0_PLL_CP_CUR_SEL_Pos) & PMU_PLL_0_PLL_CP_CUR_SEL_Msk;
    PMU->PLL_0 = val;


    // --- por default (begin) ---
    //  val = 0;
    //  val |= (2 << PMU_PLL_5_PLL_VCO_KVCO_SEL_Pos) & PMU_PLL_5_PLL_VCO_KVCO_SEL_Msk;
    //  val |= (1 << PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Pos) & PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Msk;
    //  val |= PMU_PLL_5_PLL_VCO_OPENLOOP_ENB_Msk;
    //  PMU->PLL_5 = val;
    // --- por default (end) ---
    //
    // val = (0x7 << 3) | (1 << 1) | 0x1
    //     = 0x3b
    //
    // PLL_5 := 0x4000_2084
    //
    val = 0;

#if defined(USE_HSE) && HSE_VALUE <= 4096000
    val |= (7 << PMU_PLL_5_PLL_VCO_KVCO_SEL_Pos) & PMU_PLL_5_PLL_VCO_KVCO_SEL_Msk;
#else
    val |= (0 << PMU_PLL_5_PLL_VCO_KVCO_SEL_Pos) & PMU_PLL_5_PLL_VCO_KVCO_SEL_Msk;
#endif

    val |= (1 << PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Pos) & PMU_PLL_5_PLL_LOCK_DETECT_MODE_SEL_Msk;
    val |= PMU_PLL_5_PLL_VCO_OPENLOOP_ENB_Msk;
    PMU->PLL_5 = val;
}

void HAL_Startup_PLL(int plldiv)
{
    uint32_t val;

    //PMU_Set_Pll_Division(PMU, plldiv);

    // --- por default (begin) ---
    //  val = 0;
    //  val |= (0xF << PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Pos) & PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Msk;
    //  val |= (0x0 << PMU_PLL_4_PLL_DIV8_ENB_Pos) & PMU_PLL_4_PLL_DIV8_ENB_Msk;
    //  val |= (0x4 << PMU_PLL_4_PLL_VCO_BAND_SEL_Pos) & PMU_PLL_4_PLL_VCO_BAND_SEL_Msk;
    //  PMU->PLL_4 = val;
    //
    //  val = 0;
    //  val |= (0x2 << PMU_PLL_1_PLL_LOOP_CAP1_SEL_Pos) & PMU_PLL_1_PLL_LOOP_CAP1_SEL_Msk;
    //  val |= (0x7 << PMU_PLL_1_PLL_DIV_Pos) & PMU_PLL_1_PLL_DIV_Msk;
    //  PMU->PLL_1 = val;
    //
    // --- por default (end) ---

    val = 0;
    val |= (0x4 << PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Pos) & PMU_PLL_4_PLL_LOCK_DETECT_TRIM_Msk;
    val |= (0x0 << PMU_PLL_4_PLL_DIV8_ENB_Pos) & PMU_PLL_4_PLL_DIV8_ENB_Msk;
    val |= (0x0 << PMU_PLL_4_PLL_VCO_BAND_SEL_Pos) & PMU_PLL_4_PLL_VCO_BAND_SEL_Msk;
    PMU->PLL_4 = val;

    val = 0;
    val |= (0x2 << PMU_PLL_1_PLL_LOOP_CAP1_SEL_Pos) & PMU_PLL_1_PLL_LOOP_CAP1_SEL_Msk;
    val |= (plldiv << PMU_PLL_1_PLL_DIV_Pos) & PMU_PLL_1_PLL_DIV_Msk;
    PMU->PLL_1 = val;
}

//
//  the `24Mhz_clock` just a name, depends on external clock or OSC trim value.
//
//                                            +---+       +-+
//                        +-----------------> |PLL| ----> | |
//                  +-+   |            +-+    +---+       |M|
// CLKIN ---------> |M|   +----------> |M|                |U| --> Sysclock
//       +---+      |U| --+            |U| --> Int24M --> |X|
//       |OSC| ---> |X|   +- OSCDIV -> |X|                | |
//       +---+      +-+                +-+                +-+
//                   ^                  ^                  ^
//                   |                  |                  RCC_SYSClk_Sel()
//                   |                  PMU_Set_24M_Clock_Source_div()
//                   PMU_Select_24Mhz_Clock_Cmd()
//
//
void HAL_Config_ExternalOSC(int plldiv)
{
#ifdef USE_PLL_CLOCK
    //PMU_Set_Clock_Source_Cmd(PMU, _24M | OSC_10K | OSC_320K | XTL32K | PLL, ENABLE);
    PMU_Set_Clock_Source_Cmd(PMU, _24M | XTL32K | PLL, ENABLE);
#else
    PMU_Set_Clock_Source_Cmd(PMU, _24M | OSC_10K | OSC_320K | XTL32K, ENABLE);
#endif

    PMU_Set_24M_Clock_Source_div(PMU, 1);
    PMU_Enable_External_Clock(PMU, ENABLE);

    //RCC_SYSClk_Sel(RCC_SYSCLK_Int160K);
    //RCC_AHB_Set_ClkDiv(0);
    //RCC_APB0_Set_ClkDiv(0);

    PMU_Select_24Mhz_Clock_Cmd(PMU, XTL_EXTERNAL_24M);

    if (plldiv == 1) {
        HAL_Reset_PLL();
        HAL_Change_DVDDC(DVDDC_LOW_POWER);
        RCC_SYSClk_Sel(RCC_SYSCLK_Int24M);
        return;
    }

    HAL_Reset_PLL();

    uint32_t expect_clock = HSE_VALUE * plldiv;
    if (expect_clock > 24576000) {
        HAL_Change_DVDDC(DVDDC_HI_PERF);
    } else {
        HAL_Change_DVDDC(DVDDC_LOW_POWER);
    }

    HAL_Startup_PLL(plldiv);
    system_delay_us(2000);

    RCC_SYSClk_Sel(RCC_SYSCLK_IntPLL);
}

void HAL_Update_Trim_And_OSC(osc_calibrate_config_t* cfg)
{
    if (cfg == NULL) {
        return;
    }

    // trim 2bits clock source
    // 0: other 
    // 1: from CPU
    // 2: from AFC
    //
    // trim module clock from cpu
    PMU->SYS_CFG = 
        (1 << PMU_SYS_CFG_REG_320K_TRIM_SEL_Pos) | 
        (1 << PMU_SYS_CFG_REG_24M_TRIM_SEL_Pos);

    if ((cfg->u.hsi_coarse * 16 + cfg->u.hsi_fine) != 0) {
        PMU->_24M_TRIM_COARSE   = cfg->u.hsi_coarse;
        PMU->_24M_TRIM_FINE     = cfg->u.hsi_fine;
        m_24m_trim_coarse        = cfg->u.hsi_coarse;
        m_24m_trim_fine          = cfg->u.hsi_fine;
    } else {
        PMU->_24M_TRIM_COARSE   = 3;
        PMU->_24M_TRIM_FINE     = 19;
        m_24m_trim_coarse = 3;
        m_24m_trim_fine   = 19;
    }

    if ((cfg->u.lsi_coarse * 8 + cfg->u.lsi_fine) != 0) {
        PMU->_320K_TRIM = 
            (cfg->u.lsi_coarse << PMU_320K_TRIM_REG_320K_TRIM_COARSE_Pos) |
            (cfg->u.lsi_fine << PMU_320K_TRIM_REG_320K_TRIM_FINE_Pos);
        m_320k_trim_coarse = cfg->u.lsi_coarse;
        m_320k_trim_fine   = cfg->u.lsi_fine;
    } else {
        PMU->_320K_TRIM = 
            (3 << PMU_320K_TRIM_REG_320K_TRIM_COARSE_Pos) |
            (10 << PMU_320K_TRIM_REG_320K_TRIM_FINE_Pos);
        m_320k_trim_coarse = 3;
        m_320k_trim_fine   = 10;
    }

    // synchronize
    PMU->TRIM_RST = 1;
}

// when cfg == NULL, auto call HAL_Calibrate_InternalOSC
// else using cfg to config OSC.
void HAL_Config_InternalOSC(int plldiv, osc_calibrate_config_t* cfg)
{
    // external 32KHz OSC must exists!
#ifdef USE_PLL_CLOCK
    PMU_Set_Clock_Source_Cmd(PMU, _24M | OSC_10K | OSC_320K | XTL32K | PLL, ENABLE);
#else
    PMU_Set_Clock_Source_Cmd(PMU, _24M | OSC_10K | OSC_320K | XTL32K, ENABLE);
#endif
    PMU_Set_24M_Clock_Source_div(PMU, 1);
    PMU_Enable_External_Clock(PMU, ENABLE);

    RCC_SYSClk_Sel(RCC_SYSCLK_Int160K);
    RCC_AHB_Set_ClkDiv(0);
    RCC_APB0_Set_ClkDiv(0);

    PMU_Select_24Mhz_Clock_Cmd(PMU, OSC_INTERNAL_24M);

    if (cfg != NULL) {
        HAL_Update_Trim_And_OSC(cfg);
    } else {
        _hsi_trim_freq = osc_24m_calibration_start();
        _lsi_trim_freq = osc_320k_calibration_start();
    }

    if (plldiv == 1) {
        HAL_Reset_PLL();
        HAL_Change_DVDDC(DVDDC_LOW_POWER);
        //HAL_Change_DVDDC(DVDDC_HI_PERF);
        RCC_SYSClk_Sel(RCC_SYSCLK_Int24M);
        PMU_Enable_External_Clock(PMU, DISABLE);
        return;
    }

    HAL_Reset_PLL();
#ifdef FORCE_DVDDC_TO_0V9
    HAL_Change_DVDDC(DVDDC_LOW_POWER);
#else
    uint32_t expect_clock = HSI_VALUE * plldiv;
    if (expect_clock >= 50000000) {
        HAL_Change_DVDDC(DVDDC_HI_PERF);
    } else {
        HAL_Change_DVDDC(DVDDC_LOW_POWER);
    }
#endif
    HAL_Startup_PLL(plldiv);
    system_delay_us(200);

    RCC_SYSClk_Sel(RCC_SYSCLK_IntPLL);

    PMU_Enable_External_Clock(PMU, DISABLE);
}

uint32_t HAL_Get_HSI_Freq(void)
{
    return _hsi_trim_freq;
}

uint32_t HAL_Get_LSI_Freq(void)
{
    return _lsi_trim_freq;
}

void HAL_Get_OSC_Trim(osc_trim_t* cfg)
{
    if (cfg == NULL) {
        return;
    }

    cfg->osc_24m_freq   = _hsi_trim_freq;
    cfg->osc_24m_coarse = m_24m_trim_coarse;
    cfg->osc_24m_fine   = m_24m_trim_fine;
    cfg->osc_320k_freq  = _lsi_trim_freq;
    cfg->osc_320k_coarse= m_320k_trim_coarse;
    cfg->osc_320k_fine  = m_320k_trim_fine;
}

void puthex(uint8_t v)
{
    uint8_t ch;

    ch = (v >> 4) & 0xF;
    if (ch < 10) {
        putchar('0' + ch);
    } else {
        putchar('A' + ch - 10);
    }

    ch = v & 0xF;
    if (ch < 10) {
        putchar('0' + ch);
    } else {
        putchar('A' + ch - 10);
    }
}

void memdbg(const void *buf, int nr_bytes)
{
    const uint8_t *p = (const uint8_t *)buf;
    int i;

    for (i = 0; i < nr_bytes; i++) {
        printf(" ");
        puthex(p[i] & 0xFF);
        if ((i % 8) == 7) {
            printf("\r\n");
        }
    }
    if ((i % 8) != 0) {
        printf("\r\n");
    }
}

void memdbg16(const void *buf, int nr_bytes)
{
    const uint16_t *p = (const uint16_t *)buf;
    int i;

    for (i = 0; i < nr_bytes / 2; i++) {
        printf(" ");
        puthex((p[i] >> 8) & 0xFF);
        puthex(p[i] & 0xFF);
        if ((i % 4) == 3) {
            printf("\r\n");
        }
    }
    if ((i % 4) != 0) {
        printf("\r\n");
    }
}

void led_hi(void)
{
    GPIO_OutputHi(GPIOA, LED_PIN);
}

void led_lo(void)
{
    GPIO_OutputLo(GPIOA, LED_PIN);
}







void system_cycle_reset() {
    __RV_CSR_WRITE(CSR_MCYCLEH, 0);
    __RV_CSR_WRITE(CSR_MCYCLE, 0);
}


