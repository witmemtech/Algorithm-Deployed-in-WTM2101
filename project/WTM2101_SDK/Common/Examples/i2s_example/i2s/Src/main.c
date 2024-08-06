/**
* @file    main.c
* @brief    This example describes how to use the I2S to transfer continuously converted data.
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

#include "main.h"

#define SAMPLE_RATE  (16000)

static void i2s_config(void);
static void i2s_test(void);
static void system_clock_init(void);

void I2S0_IRQHandler(void)
{
    int stat = 0;
    /* get state of interrupt */
    stat = I2S_IT_GetStatBit(I2S0, I2S_IT_TXFE);
}

void main(void)
{
    /* retarget printf to NONE */      
    printf_output_redirect_set(PRINTF_RETARGET_NONE);
  
    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();

    /* Initial clock */
    system_clock_init();

    /* Config i2s */
    i2s_config();

    /*Application entry */
    while(1)
    {
       i2s_test();
       system_delay_ms(1);
    }
}

static void system_clock_init(void)
{
    int ret = 0; 
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_EXTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = DISABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /*Initialize the clock instance.the system clock is from external 24576000 crystal oscillator.*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,4,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void i2s_config(void)
{
    uint32_t clk_num = 0;
    GPIO_InitTypeDef GPIO_I2SInitStructure;
    RCC_CLK_EN_Ctl(RCC_I2S0_CLKEN, ENABLE);

    /* Initialize gpio */
    GPIO_I2SInitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_I2SInitStructure.Alternate = GPIO_AF0_I2S0 | GPIO_AF1_I2S0 | GPIO_AF2_I2S0 |GPIO_AF3_I2S0;
    GPIO_Init(GPIOA, &GPIO_I2SInitStructure);

    I2S_Ctl(I2S0,DISABLE);

    /* Select i2s mode */
    I2S_Mode_Sel(I2S0, I2S_MASTER);

    /* Set clknum of sampling */
    I2S_ClkCfg(I2S0,I2S_SCLKNUM_32, I2S_GATESCLKNUM_NONE);
    I2S_SplRate_Set(I2S0, SAMPLE_RATE);
    
    /* Config data length*/
    I2S_TxCfg(I2S0,I2S_RES_LEN_32);

    /*Set TX level of interrupt */
    I2S_TxFIFO_LVLCfg(I2S0, 7);
    I2S_TxFIFO_Flush(I2S0);
    
    /* Enable TX interrupt */
    I2S_IT_MskCtl(I2S0, I2S_IT_TXFE, DISABLE);
    ECLIC_ClearPendingIRQ(I2S0_IRQn);
    ECLIC_SetPriorityIRQ(I2S0_IRQn, 1);
    ECLIC_SetTrigIRQ(I2S0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(I2S0_IRQn);

    /* Enable i2s */
    I2S_Ctl(I2S0, ENABLE);
    I2S_TxBlkCtl(I2S0, ENABLE);
    I2S_TxChlCtl(I2S0, ENABLE);
    I2S_ClkCtl(I2S0, ENABLE);
}

static void i2s_test(void)
{
    uint32_t buffer[]={0x12345678,0x90112233};
    I2S_TransmitData(I2S0, buffer, 2);
}