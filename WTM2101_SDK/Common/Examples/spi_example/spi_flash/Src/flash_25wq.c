/**
  ******************************************************************************
  * @file    flash_25wq.c 
  * @brief   This file provide driver for flash 25wq.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>

#include <WTM2101_config.h>

#include <WTM2101.h>
#include <WTM2101_hal.h>
#include "spi.h"
#include "gpio.h"
#include "flash_25wq.h"

void spi_cs_high()
{
    GPIO_OutputHi(GPIOA, GPIO_PIN_1);
}

void spi_cs_low()
{
    GPIO_OutputLo(GPIOA, GPIO_PIN_1);
}

void spi_read_flash_id(uint8_t *id)
{
    uint8_t receive_data[6] = {0};
    uint8_t send_data[6] = {0};

    send_data[0] = READ_ID_CMD;
    spi_cs_low();
    SPI_Send_Receive(SPIM,1, send_data, sizeof(send_data), receive_data, sizeof(receive_data));
    spi_cs_high();
    memcpy(id, &receive_data[4], 2);
}

void spi_flash_write_enable(void)
{
    uint8_t receive_data[1] = {0};
    uint8_t send_data[1] = {0};

    send_data[0] = WRITE_ENABLE_CMD;
    spi_cs_low();
    SPI_Send_Receive(SPIM,1, send_data, sizeof(send_data), receive_data, sizeof(receive_data));
    spi_cs_high();
}

void spi_flash_write_disable(void)
{
    uint8_t receive_data[1] = {0};
    uint8_t send_data[1] = {0};

    send_data[0] = WRITE_DISABLE_CMD;
    spi_cs_low();
    SPI_Send_Receive(SPIM,1, send_data, sizeof(send_data), receive_data, sizeof(receive_data));
    spi_cs_high();
}

void spi_flash_read(uint8_t *buf, uint32_t addr, int len)
{
    uint8_t dummy_data[4] = {0};
    uint8_t cmd_data[4] = {0};

    cmd_data[0] = READ_CMD;
    cmd_data[1] = (addr >> 16) & 0xFF;
    cmd_data[2] = (addr >> 8) & 0xFF;
    cmd_data[3] = (addr >> 0) & 0xFF;
    spi_cs_low();
    SPI_Send_Receive(SPIM,1, cmd_data, sizeof(cmd_data), dummy_data, sizeof(dummy_data));

    SPI_Send_Receive(SPIM,1, NULL, 0, buf, len);
    spi_cs_high();
}

uint8_t spi_flash_read_status_reg(void)
{
    uint8_t receive_data[2] = {0};
    uint8_t send_data[2] = {0};

    send_data[0] = READ_STATUS_REG1_CMD;
    spi_cs_low();
    SPI_Send_Receive(SPIM,1, send_data, sizeof(send_data), receive_data, sizeof(receive_data));
    spi_cs_high();

    return receive_data[1];
}

void spi_flash_page_erase(uint32_t addr)
{
    uint8_t dummy_data[4] = {0};
    uint8_t cmd_data[4] = {0};

    cmd_data[0] = PAGE_ERASE_CMD;
    cmd_data[1] = (addr >> 16) & 0xFF;
    cmd_data[2] = (addr >> 8) & 0xFF;
    cmd_data[3] = (addr >> 0) & 0xFF;

    spi_cs_low();
    SPI_Send_Receive(SPIM,1, cmd_data, sizeof(cmd_data), dummy_data, sizeof(dummy_data));
    spi_cs_high();

    while(spi_flash_read_status_reg() & 0x1);
}

void spi_flash_page_prog(uint8_t *data, uint32_t addr, int len)
{
    uint8_t dummy_data[4] = {0};
    uint8_t cmd_data[4] = {0};

    if (len > FLASH_PAGE_SIZE)
    {
        printf("ERROR:page size too large\r\n");
        return;
    }
    cmd_data[0] = PAGE_PROG_CMD;
    cmd_data[1] = (addr >> 16) & 0xFF;
    cmd_data[2] = (addr >> 8) & 0xFF;
    cmd_data[3] = (addr >> 0) & 0xFF;
    spi_cs_low();
    SPI_Send_Receive(SPIM,1, cmd_data, sizeof(cmd_data), dummy_data, sizeof(dummy_data));
    SPI_Send_Receive(SPIM,1, data, len, NULL, 0);
    spi_cs_high();

    while(spi_flash_read_status_reg() & 0x1);
}

void spi_flash_global_block_unlock()
{
    uint8_t receive_data[1] = {0};
    uint8_t send_data[1] = {0};

    send_data[0] = GLOBAL_BLOCK_UNLOCK;
    spi_cs_low();
    SPI_Send_Receive(SPIM,1, send_data, sizeof(send_data), receive_data, sizeof(receive_data));
    spi_cs_high();
}