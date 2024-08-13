/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes the use of an internal PDM to read the data 
             collected by the analog MIC and sending the data read in real time 
             through I2S1 via FIFO of AUDIO channel 0.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
 
#include "main.h"

#define ANA_GAIN_MIN (2)
#define ANA_GAIN_DEFAULT (15) 
#define ANA_GAIN_MAX (20)     

#define AGC_TARGET_THRES (0.1)
#define AGC_MAX_THRES (0.2)
#define AGC_ODR (16)

/* decr must < 0,incr must > 0 */
#define FAST_DECR (-204)
#define SLOW_DECR (-10)
#define SLOW_INCR (5)

#define DATA_BUFF_LEN (4)

#define AUDIO_TRANSFER_DMA

uint16_t audio_buff[DATA_BUFF_LEN * 2];
uint32_t iis_buff[DATA_BUFF_LEN * 2];

volatile Bool audio_buff_ok = FALSE;
volatile Bool audio_dma_completed = FALSE;
volatile Bool i2s_dma_completed = FALSE;

 
static void i2s1_config(void);
static void uart_init(void);
static void iis_dma_config(void);
void DMA_IRQHandler(void);
static void audio_config(void);
void AUDIO_IRQHandler(void);
static void audio_dma_init(void);
static void _mic_in_channel(void);
static void _agc_config(void);
static void audio_start(void);
static void system_clock_init(void);

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Reset all peripherals except PMU */
    RCC_Peri_Rst(0xFFFFFFFF & (~(RCC_PMU_PRSTN | RCC_GPIO_RSTN)));

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();
  
    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);
  
    /* Initial clock */
    system_clock_init();
  
    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);

    /* Initial audio and i2s */
    audio_config();
    i2s1_config();

    /* Application entry */
    audio_start();
    while (1)
    {
        if (audio_buff_ok != FALSE)
        {
            audio_buff_ok = FALSE;

#if defined(AUDIO_TRANSFER_DMA)

            DMA_Set_Addr(DMA, DMA_CHANNEL0, (uint32_t) & (AUD->FF0DATA), mmap_to_sys((uint32_t)audio_buff), DATA_BUFF_LEN, 0);
            DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL0, ENABLE);
            while (audio_dma_completed == FALSE);
            audio_dma_completed = FALSE;
#else
            uint32_t tmp = 0;
            for (uint8_t i = 0; i < DATA_BUFF_LEN; i++)
            {
                tmp = AUDIO_Read_Fifo_Data(AUD, AUDIO_CHANNEL0);
                audio_buff[i << 1] = tmp;
                audio_buff[(i << 1) + 1] = tmp >> 16;
            }
#endif

            for (int i = 0; i < DATA_BUFF_LEN *2; i++)
            {
                /* left channel data */
                iis_buff[i] = audio_buff[i];
                /* right channel data */
                iis_buff[i] &= 0x0000ffff;
            }
            DMA_Set_Addr(DMA, DMA_CHANNEL1, mmap_to_sys((uint32_t)iis_buff), (uint32_t) & (I2S1->TXDMA), DATA_BUFF_LEN *2, 0);
            DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL1, ENABLE);

            while (i2s_dma_completed == FALSE);
            i2s_dma_completed = FALSE;
        }
        else
        {
        }
    }
}


static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);
   
    /*the gpio4,gpio5*/
    GPIO_InitStructure.Pin = GPIO_PIN_16 | GPIO_PIN_17;
    GPIO_InitStructure.Alternate = GPIO_AF16_UART0 | GPIO_AF17_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);
}

static void i2s1_config(void)
{

    uint32_t clk_num = 0;
    GPIO_InitTypeDef GPIO_Uart1InitStructure;

    /* initial gpio */
    GPIO_Uart1InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_Uart1InitStructure.Alternate = GPIO_AF10_I2S1 | GPIO_AF11_I2S1 | GPIO_AF12_I2S1 | GPIO_AF13_I2S1;
    GPIO_Init(GPIOA, &GPIO_Uart1InitStructure);

    /* initial i2s */
    RCC_CLK_EN_Ctl(RCC_I2S1_CLKEN, ENABLE);
    I2S_Ctl(I2S1, DISABLE);

    I2S_Mode_Sel(I2S1, I2S_MASTER);
    I2S_ClkCfg(I2S1, I2S_SCLKNUM_16, I2S_GATESCLKNUM_NONE);
    RCC_I2S1_Set_ClkDiv(48 - 1); /* 48 = 512k / (16k*16*2) */

    I2S_TxCfg(I2S1, I2S_RES_LEN_16);
    I2S_TxFIFO_LVLCfg(I2S1, 1);
    I2S_TxFIFO_Flush(I2S1);

    I2S_IT_MskCtl(I2S1, I2S_IT_TXFE, DISABLE); 
   
    I2S_Ctl(I2S1, ENABLE);
    I2S_TxBlkCtl(I2S1, ENABLE);
    I2S_RxChlCtl(I2S1, DISABLE);
    I2S_TxChlCtl(I2S1, ENABLE);
    I2S_ClkCtl(I2S1, ENABLE);

    /* initial i2s dma */
    iis_dma_config();
}

static void iis_dma_config(void)
{
    DMA_InitTypeDef dma_inittypedef;

    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);
    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Clear_All_Interrupt_Cmd(DMA);
    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);

    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;
    dma_inittypedef.direction = MEM_TO_PER_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE8;
    dma_inittypedef.dst_msize = DMA_MSIZE8;
    dma_inittypedef.src_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.src_width = DMA_WIDTH32;
    dma_inittypedef.dst_width = DMA_WIDTH16;
    dma_inittypedef.src_per = DMA_I2S1_REQ;
    dma_inittypedef.dst_per = DMA_I2S1_REQ;
    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY1;
    dma_inittypedef.int_en = ENABLE;
    DMA_Init(DMA, DMA_CHANNEL1, &dma_inittypedef);

    DMA_Set_Enable_Cmd(DMA, ENABLE);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL1, ENABLE);
}

void DMA_IRQHandler(void)
{
    uint8_t transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);

    if (transfer_int_flag & DMA_CHANNEL0_INT_FLAG)
    {
        audio_dma_completed = TRUE;
        DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0);
    }

    if (transfer_int_flag & DMA_CHANNEL1_INT_FLAG)
    {
        i2s_dma_completed = TRUE;
        DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL1);
    }
}

static void audio_dma_init(void)
{
    DMA_InitTypeDef dma_inittypedef;
    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);
    DMA_Set_Enable_Cmd(DMA, DISABLE);

    DMA_Clear_All_Interrupt_Cmd(DMA);
    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);

    dma_inittypedef.llp_src_en = DISABLE;
    dma_inittypedef.llp_dst_en = DISABLE;
    dma_inittypedef.reload_src_en = DISABLE;
    dma_inittypedef.reload_dst_en = DISABLE;
    dma_inittypedef.direction = MEM_TO_MEM_FLOW_CTOL_DMA;
    dma_inittypedef.src_msize = DMA_MSIZE8;
    dma_inittypedef.dst_msize = DMA_MSIZE8;
    dma_inittypedef.src_addr_type = DMA_ADDRESS_NO_CHANGE;
    dma_inittypedef.dst_addr_type = DMA_ADDRESS_INCREASE;
    dma_inittypedef.src_width = DMA_WIDTH32;
    dma_inittypedef.dst_width = DMA_WIDTH16;
    dma_inittypedef.src_per = DMA_AUDIO_CH0_REQ;
    dma_inittypedef.dst_per = DMA_AUDIO_CH0_REQ;
    dma_inittypedef.fifo_mode_en = DISABLE;
    dma_inittypedef.max_abrst = 0;
    dma_inittypedef.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_inittypedef.chanel_priority = DMA_PRIORITY0;
    dma_inittypedef.int_en = ENABLE;
    DMA_Init(DMA, DMA_CHANNEL0, &dma_inittypedef);

    DMA_Set_Enable_Cmd(DMA, ENABLE);
    DMA_Set_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0, ENABLE);
}

static void _mic_in_channel(void)
{
    uint32_t val;

    /*
    0x5000306C: ANA0CFG              = 0x28100B04
        |RSV20                          = 0
        |pu_bst_ch1_o                   = 0
        |pu_bst_ch0_o                   = 1
        |RSV21                          = 0
        |pu_audio_buf_ch0_o             = 1
        |RSV22                          = 0
        |RSV23                          = 0
        |mute_pga_ch0_o                 = 0
        |RSV24                          = 0
        |mute_bst_ch1_o                 = 0
        |mute_bst_ch0_o                 = 0
        |micbias_en_o                   = 1
        |bst_sel_ch1_o                  = 0
        |bst_sel_ch0_o                  = 0
        |rst_sd_ch1_o                   = 1
        |rst_sd_ch0_o                   = 0
        |bias_ref_sel_o                 = 1
        |bias_out_en1_o                 = 1
        |RSV25                          = 0
        |RSV26                          = 0
        |RSV27                          = 0
        |vcom_sel_o                     = 4
    */
    val = 0;
    val |= AUDIO_ANA0CFG_PU_BST_CH0_O_Msk;
    val |= AUDIO_ANA0CFG_PU_AUDIO_BUF_CH0_O_Msk;
    val |= AUDIO_ANA0CFG_MICBIAS_EN_O_Msk;
    val |= AUDIO_ANA0CFG_RST_SD_CH1_O_Msk;
    val |= AUDIO_ANA0CFG_BIAS_REF_SEL_O_Msk;
    val |= AUDIO_ANA0CFG_BIAS_OUT_EN1_O_Msk;
    val |= AUDIO_ANA0CFG_BST_SEL_CH0_O_Msk & (0 << AUDIO_ANA0CFG_BST_SEL_CH0_O_Pos);
    val |= AUDIO_ANA0CFG_BST_SEL_CH1_O_Msk & (0 << AUDIO_ANA0CFG_BST_SEL_CH1_O_Pos);
    val |= AUDIO_ANA0CFG_VCOM_SEL_O_Msk & (4 << AUDIO_ANA0CFG_VCOM_SEL_O_Pos);
    AUD->ANA0CFG = val;

   /*
   0x50003070: ANA1CFG              = 0x8624333
        |analog_testpad_en_o            = 1
        |RSV28                          = 0
        |RSV29                          = 0
        |test_sd_ch1_o                  = 6
        |test_sd_ch0_o                  = 1
        |RSV30                          = 0
        |en_clk_adc_ch1_o               = 0
        |en_clk_adc_ch0_o               = 1
        |RSV31                          = 0
        |sd_adc_sel_ch1_o               = 0
        |sd_adc_sel_ch0_o               = 0
        |iref_trim_o                    = 3
        |en_osc80k_o                    = 0
        |RSV32                          = 0
        |en_sd_ch1_o                    = 1
        |en_sd_ch0_o                    = 1
        |RSV33                          = 0
        |RSV34                          = 0
        |pu_pga_ch0_o                   = 1
        |pu_bg_o                        = 1
    */
    val = 0;
    val &= ~AUDIO_ANA1CFG_ANALOG_TESTPAD_EN_O_Msk;

    val |= AUDIO_ANA1CFG_EN_CLK_ADC_CH0_O_Msk;
    val |= AUDIO_ANA1CFG_IREF_TRIM_O_Msk & (3 << AUDIO_ANA1CFG_IREF_TRIM_O_Pos);
    val |= AUDIO_ANA1CFG_EN_SD_CH1_O_Msk;
    val |= AUDIO_ANA1CFG_EN_SD_CH0_O_Msk;
    val |= AUDIO_ANA1CFG_PU_PGA_CH0_O_Msk;
    val |= AUDIO_ANA1CFG_PU_BG_O_Msk;
    AUD->ANA1CFG = val;

    /*
    0x50003074: ANA2CFG              = 0x18007
        |ana_res_ctrl_o                 = 1
        |bias_set_o                     = 2
        |RSV35                          = 0
        |RSV36                          = 0
        |RSV37                          = 0
        |vbg_trim_o                     = 7
    */
    val = 0;
    val |= AUDIO_ANA2CFG_ANA_RES_CTRL_O_Msk & (1 << AUDIO_ANA2CFG_ANA_RES_CTRL_O_Pos);
    val |= AUDIO_ANA2CFG_BIAS_SET_O_Msk & (2 << AUDIO_ANA2CFG_BIAS_SET_O_Pos);
    val |= AUDIO_ANA2CFG_VBG_TRIM_O_Msk & (7 << AUDIO_ANA2CFG_VBG_TRIM_O_Pos);
    AUD->ANA2CFG = val;

    /*
    0x50003088: ANA7CFG              = 0x3A000000
        |ch0_agc_gain_force_o           = 0x1D
        |ch0_agc_gain_default_o         = 0
        |ch0_agc_default_en_o           = 0
        |ch0_agc_gain_sel_o             = 0
        |ch0_agc_en_o                   = 0
        |ch0_config_slow_incr_o         = 0
    */
    val = 0;
    val |= AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Msk & (ANA_GAIN_DEFAULT << AUDIO_ANA7CFG_CH0_AGC_GAIN_FORCE_O_Pos);
    AUD->ANA7CFG = val;

    /*
    0x500030D4: ANA19CFG             = 0x00E4
        |audio_test_sel_o               = 0
        |vad_test_sel_o                 = 0
        |vad_pu_vcom_o                  = 0
        |vad_pu_bst_o                   = 0
        |vad_mute_o                     = 0
        |vad_gain_sel_o                 = 0
        |vad_en_diff_o                  = 0
        |current_sel_ch2_o              = 0
        |current_sel_ch1_o              = 0
        |pu_vcom_o                      = 1
        |ldo_avdd12_audio_trim_o        = 6
        |xvon_avdd12_audio_o            = 0
        |en_audio_o                     = 1
        |audio_test_i                   = 0
        |porb_avdd12_audio_i            = 0
    */
    val = 0;
    val |= AUDIO_ANA19CFG_PU_VCOM_O_Msk;
    val |= AUDIO_ANA19CFG_LDO_AVDD12_AUDIO_TRIM_O_Msk & (6 << AUDIO_ANA19CFG_LDO_AVDD12_AUDIO_TRIM_O_Pos);
    val |= AUDIO_ANA19CFG_EN_AUDIO_O_Msk;
    AUD->ANA19CFG = val;
}


static void _agc_config(void)
{
    /* config AGC */
    uint32_t val;
    val = AUD->ANA3CFG;
    val |= AUDIO_ANA3CFG_CH0_SYSCTL_AGCPEAK_O_Msk;

    val &= ~AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Msk;
    val |= AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Msk & (AGC_ODR << AUDIO_ANA3CFG_CH0_AGCCFG_ODR_O_Pos);

    AUD->ANA3CFG = val;

    uint16_t max_thres = (int)(32768 * AGC_MAX_THRES);
    uint16_t target_thres = (int)(32768 * AGC_TARGET_THRES);
    val = 0;
    val |= AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Msk & (max_thres << AUDIO_ANA5CFG_CH0_CONFIG_MAX_THRESHOLD_O_Pos);
    val |= AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Msk & (target_thres << AUDIO_ANA5CFG_CH0_CONFIG_TARGET_THRESHOLD_O_Pos);
    AUD->ANA5CFG = val;

    val = 0;
    val |= AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Msk & ((SLOW_DECR & 0xFFFF) << AUDIO_ANA6CFG_CH0_CONFIG_SLOW_DECR_O_Pos);
    val |= AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Msk & ((FAST_DECR & 0xFFFF) << AUDIO_ANA6CFG_CH0_CONFIG_FAST_DECR_O_Pos);
    AUD->ANA6CFG = val;


    /* 
        when ch0_agc_en_o == 0 or ch0_agc_default_en_o == 1
        agc_gain = ch0_agc_gain_default_o
    */
    val = AUD->ANA7CFG;

    val &= ~AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Msk;
    val |= AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Msk & (SLOW_INCR << AUDIO_ANA7CFG_CH0_CONFIG_SLOW_INCR_O_Pos);

    val &= ~AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Msk;
    val |= AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Msk & (ANA_GAIN_DEFAULT << AUDIO_ANA7CFG_CH0_AGC_GAIN_DEFAULT_O_Pos);

    val &= ~AUDIO_ANA7CFG_CH0_AGC_DEFAULT_EN_O_Msk; /* agc_core.gain = agc_en?agc_core.calc:agc_default */
    val |= AUDIO_ANA7CFG_CH0_AGC_GAIN_SEL_O_Msk;    /* agc_gain from agc_core */
    val |= AUDIO_ANA7CFG_CH0_AGC_EN_O_Msk;          /* agc_gain = agc_core.calc */

    AUD->ANA7CFG = val;

    /* config_update vaild when AGC_EN == 1 */
    val = 0;
    val |= AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Msk & (ANA_GAIN_MIN << AUDIO_ANA4CFG_CH0_CONFIG_MIN_GAIN_O_Pos);
    val |= AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Msk & (127 << AUDIO_ANA4CFG_CH0_CONFIG_INIT_GAIN_O_Pos);
    val |= AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Msk & (ANA_GAIN_MAX << AUDIO_ANA4CFG_CH0_CONFIG_MAX_GAIN_O_Pos);

    val |= AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Msk;
    AUD->ANA4CFG = val;

    val &= ~AUDIO_ANA4CFG_CH0_CONFIG_UPDATE_O_Msk;
    AUD->ANA4CFG = val;
}

static void audio_config(void)
{   
    /* initial audio rcc and pmu */
    RCC_CLK_EN_Ctl(RCC_AUD_PCLKEN | RCC_AUD_CLKEN, ENABLE);
    RCC_Peri_Rst(RCC_AUD_PRSTN);
    RCC_Peri_Rst(RCC_AUD_RSTN);
    PMU_Set_Audio_Clock_Cmd(PMU, ENABLE);

    /* initial audio dma */
    audio_dma_init();

    /* audio clk 4M/(3+1)=1MHz */
    AUDIO_Set_Channel_Clock_Divider(AUD, 3);
    PMU_Set_Audio_Clock_Div_Num(PMU, 5);

    AUDIO_Channel0_12bit_Pcm_Cmd(AUD, DISABLE);

    AUDIO_Set_Channel0_Select_Pdm(AUD, AUDIO_PDM0);

    AUDIO_Set_Channel_Transmit_Mode(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_TRANSMIT_FIFO_MODE);
    AUDIO_Set_Channel_Input_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_INPUT_FROM_ANALOG);
    AUDIO_Set_Channel_Edge_Capture_Select(AUD, AUDIO_CHANNEL0, AUDIO_CHANNEL_FALL_CLOCK_EDGE_CAPTURE);
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, ENABLE);
    AUDIO_Set_Channel_Gain_Configuration(AUD, AUDIO_CHANNEL0, 16);
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, DISABLE);

    AUDIO_Set_Analog_Emphasis_Cmd(AUD, ENABLE); 

    /* audio filter config */
    AUDIO_Set_Pre_Emphasis_Bypass_Cmd(AUD, ENABLE);
    AUDIO_Set_Sinc5d2_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Halfband_Bypass_Cmd(AUD, ENABLE);
    AUDIO_Set_Highpass_Bypass_Cmd(AUD, DISABLE);
    AUDIO_Set_Channel2_High_Bypass_Cmd(AUD, DISABLE);

    /* analog mic set */
    _mic_in_channel(); 
    _agc_config();    

    /* audio interrupt config */
    ECLIC_ClearPendingIRQ(AUDIO_IRQn);
    ECLIC_SetPriorityIRQ(AUDIO_IRQn, 2);
    ECLIC_SetTrigIRQ(AUDIO_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(AUDIO_IRQn);
}

void AUDIO_IRQHandler(void)
{
    if (AUDIO_Get_FIFO_Interrupt_Status(AUD, AUDIO_CHANNEL0) & AUDIO_FIFO_HALF_FULL_INTERRUPT)
    {
        audio_buff_ok = TRUE;
        ECLIC_ClearPendingIRQ(AUDIO_IRQn);
        AUDIO_Clear_Fifo_Interrupt(AUD, AUDIO_CHANNEL0, AUDIO_FIFO_HALF_FULL_INTERRUPT);
    }
}

static void audio_start(void)
{
    AUDIO_Set_FIFO_Interrupt_Mask(AUD, AUDIO_CHANNEL0, AUDIO_FIFO_HALF_FULL_INTERRUPT, ENABLE);
    AUDIO_Set_Channel_Transmit_Cmd(AUD, AUDIO_CHANNEL0, ENABLE);
}

static void system_clock_init(void)
{
    int ret = 0; 
    /* The clock instance */
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /* Construct 24mosc related configuration parameters */
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_INTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = ENABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /* Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc is calibrated by the xtal 32k */
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /* According to the clock instance, initialize the hardware */
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}