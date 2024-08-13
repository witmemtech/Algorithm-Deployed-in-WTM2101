/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the spi interrupt to transfer 
  *          continuously converted data.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"
static void spi_master_config(void);
static void spi_slave_config(void);
static void system_clock_init(void);
static void uart0_config(void);

#define TEST_BUF_SIZE (8)
uint8_t send_data[TEST_BUF_SIZE] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
uint8_t recv_data[TEST_BUF_SIZE] = {0};
uint8_t index = 0;
uint8_t recv_index = 0;

void main(void)
{
    /* retarget printf to NONE */
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();

    /* config system clock */
    system_clock_init();

    /* config uart0 for print */
    uart0_config();

    /* retarget printf to uart0 */
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);

    /* Disable N307 Interrupt before spi interrupt transmit*/
    __disable_irq();

    /* config spi slave */
    spi_slave_config();
    /* config spi master */
    spi_master_config();

    /* Enable N307 Interrupt */
    __enable_irq();

    /* Application entry */
    while (recv_index != sizeof(recv_data) || index != sizeof(send_data));

    if (memcmp(send_data, recv_data, sizeof(send_data)) == 0) 
    {
        printf("pass\r\n");
    }
    else
    {
        printf("failed\r\n");
    }

    while(1){};
}


void SPIM_IRQHandler(void)
{
    uint32_t status = 0;
    status = SPI_Get_Interrupt_Status(SPIM);
    if (status & SPI_TRANSMIT_FIFO_EMPTY_INT)
    {
        SPI_Send(SPIM, 1, &send_data[index], 1);
        index++;
        if (index == sizeof(send_data))
        {
            SPI_Set_Tx_Fifo_Empty_Interrupt(SPIM, DISABLE);
        }
    }
}

void SPIS_IRQHandler(void)
{
    uint32_t status = 0;
    status = SPI_Get_Interrupt_Status(SPIS);
    if (status & SPI_RECEIVE_FIFO_FULL_INT) 
    {
        recv_data[recv_index] = *((uint8_t *)&SPIS->DR);
        recv_index++;
        if (recv_index == sizeof(recv_data))
        {
            SPI_Set_Rx_Fifo_Full_Interrupt(SPIS, DISABLE);
        }
    }
}

static void spi_master_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef spi_init_type;
    RCC_CLK_EN_Ctl(RCC_SPIM_PCLKEN,ENABLE);

    SPI_Uninit(SPIM);

    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;     /* spi master pin config */
    GPIO_InitStructure.Alternate = GPIO_AF0_SPI0 | GPIO_AF1_SPI0 | GPIO_AF2_SPI0 | GPIO_AF3_SPI0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    spi_init_type.cpol = SPI_CPOL_0;                /* cpol 0*/
    spi_init_type.cpha = SPI_CPHA_0;                /* cpha 0*/
    spi_init_type.datasize = SPI_DATASIZE_8B;       /* spi data width 8 bit */
    spi_init_type.clk_div = 12;                     /* spi speed = AHB / 12 */
    spi_init_type.nss = SPI_HARDWARE_NSS0;
    SPI_Init(SPIM, &spi_init_type);
    SPIM->IMR = 0;                                  /* disable all interrupt */
    SPI_Set_Tx_Fifo_Threshold(SPIM, 0);
    SPI_Set_Tx_Fifo_Empty_Interrupt(SPIM, ENABLE);  /* enable tx fifo empty interrupt */

    /* init spi interrupt */
    ECLIC_ClearPendingIRQ(SPIM_IRQn);
    ECLIC_SetPriorityIRQ(SPIM_IRQn, 1);
    ECLIC_SetTrigIRQ(SPIM_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(SPIM_IRQn);

    SPI_Cmd(SPIM, ENABLE);
}

static void spi_slave_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef spi_init_type;
    RCC_CLK_EN_Ctl(RCC_SPIS_PCLKEN,ENABLE);

    SPI_Uninit(SPIS);

    GPIO_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17;    /* spi slave pin config */
    GPIO_InitStructure.Alternate = GPIO_AF14_SPIS | GPIO_AF15_SPIS | GPIO_AF16_SPIS | GPIO_AF17_SPIS;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    spi_init_type.cpol = SPI_CPOL_0;             /* cpol 0*/
    spi_init_type.cpha = SPI_CPHA_0;             /* cpha 0*/
    spi_init_type.datasize = SPI_DATASIZE_8B;    /* spi data width 8 bit */
    SPI_Init(SPIS, &spi_init_type);

    SPIS->IMR = 0;                                  /* disable all interrupt */
    SPI_Set_Rx_Fifo_Threshold(SPIS, 0);
    SPI_Set_Rx_Fifo_Full_Interrupt(SPIS, ENABLE);

    /* init spi interrupt */
    ECLIC_ClearPendingIRQ(SPIS_IRQn);
    ECLIC_SetPriorityIRQ(SPIS_IRQn, 2);
    ECLIC_SetTrigIRQ(SPIS_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(SPIS_IRQn);

    SPI_Cmd(SPIS, ENABLE);
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

static void uart0_config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;    /* uart0 pin config */
    GPIO_InitStructure.Alternate = GPIO_AF4_UART0 | GPIO_AF5_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);

    UART_IT_Cfg(UART0, UART_IT_ERBFI, DISABLE);
}

