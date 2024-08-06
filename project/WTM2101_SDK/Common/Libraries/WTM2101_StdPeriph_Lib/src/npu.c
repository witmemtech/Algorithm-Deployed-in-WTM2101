/********************************************************************************
  * @file    npu.c
  * @brief   The Source Codes for the NPU Functions
  * @version V1.0.0.0
  * @date    2023-02-08
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <stdio.h>
#include "npu.h"
#include "debugio.h"
#include "wtm2101_hal.h"

#define WRITE8(addr,value)            *(volatile uint8_t *)(addr)=(uint8_t)value
#define WRITE16(addr,value)           *(volatile uint16_t *)(addr) = (uint16_t)value
#define WRITE32(addr,value)           *(volatile uint32_t *)(addr)=(uint32_t)value

#define READ8(addr)                   (uint8_t)(*(volatile uint8_t *)(addr))
#define READ16(addr)                  *(volatile short unsigned int *)(addr)
#define READ32(addr)                  (uint32_t)(*(volatile uint32_t *)(addr))
#define READ(addr)                    READ32(addr)
#define WRITE(addr,value)             WRITE32(addr,value)

/*
#define WRITE32_NPU(addr,value)       WRITE32(addr+MPU_BASE_ADDR,value)
#define READ32_NPU(addr)              READ32(addr+MPU_BASE_ADDR)
#define WRITE16_NPU(addr,value)       WRITE16(addr+MPU_BASE_ADDR,value)
#define READ16_NPU(addr)              READ16(addr+MPU_BASE_ADDR)
#define WRITE8_NPU(addr,value)        WRITE8(addr+MPU_BASE_ADDR,value)
#define READ8_NPU(addr)               READ8(addr+MPU_BASE_ADDR)
*/

#define OUT_REGFILE_DEPTH             (8192UL)
#define REGFILE_DATA                  ((uint16_t)0x0030)


extern void system_delay_tick(uint32_t time);

void WRITE32_NPU(uint32_t addr, uint32_t value)
{
    WRITE32(addr + MPU_BASE_ADDR, value);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
}

uint32_t READ32_NPU(uint32_t addr)
{
    uint32_t data = 0;
    data = READ32(addr + MPU_BASE_ADDR);
    return data;
}

void WRITE16_NPU(uint16_t addr, uint16_t value)
{
    WRITE16(addr + MPU_BASE_ADDR, value);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
}

uint16_t READ16_NPU(uint16_t addr)
{
    uint16_t data = 0;
    data = READ16(addr + MPU_BASE_ADDR);
    return data;
}

void WRITE8_NPU(uint8_t addr, uint8_t value)
{
    WRITE8(addr + MPU_BASE_ADDR, value);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
}

uint8_t READ8_NPU(uint8_t addr)
{
    uint8_t value = 0;
    value = READ8(addr + MPU_BASE_ADDR);
    return value;
}

/* Includes */
/* sram 256 *64bit address from 0
regfile size =1024*8
*/

static void Delay_nop(uint32_t n)
{
    uint16_t i = 0;
    for (i = 0; i < n; i++)
    {
        __NOP();
    }
}

void npu_clk_div(uint8_t num)
{
    WRITE16(PMU_BASE + 0x001c, READ(PMU_BASE + 0x001c) & ~(0x0f << 0) | num); /* NPU_CLK_DIV */
}

void npu_soft_reset(void)
{
    WRITE32(PMU_BASE + 0x0018, READ32(PMU_BASE + 0x0018) & ~(1 << 5));
    WRITE32(PMU_BASE + 0x0018, READ32(PMU_BASE + 0x0018) | (1 << 5));
    system_delay_us(20);
    WRITE32(PMU_BASE + 0x0018, READ32(PMU_BASE + 0x0018) & ~(1 << 5));
}

void NPU_Init(void)
{
    WRITE8(PMU_BASE + 0x001C, (READ8(PMU_BASE + 0x001C) & 0x00F0) | 0);
    WRITE8(PMU_BASE + 0x0018,  READ8(PMU_BASE + 0x0018) | 0x0010);
    /* delay 10 cycle */
    Delay_nop(10);
    /* ctrl sel reg */
    WRITE32(RCC_BASE + 0x001c,0x107);
}

void NPU_Interrupt_Init(NPU_IT_MASK irq_mask)
{
    __enable_irq();
    ECLIC_SetPriorityIRQ(NPU_IRQn, 2);
    ECLIC_SetTrigIRQ(NPU_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(NPU_IRQn);
    WRITE16(MPU_BASE_ADDR + 0x002a,READ(MPU_BASE_ADDR + 0x002a) | irq_mask);
}

void __WEAK NPU_IRQHandler(void)
{
    printf("interrupt status is 0x%x",READ( MPU_BASE_ADDR + 0x002C));
}

void round_cfg_srame_read(uint32_t round_addr, uint32_t *data_read, uint32_t number)
{
    uint16_t count = 0;
    count = number;
    /* address */
    WRITE16_NPU(0x025c, 0x00);
    WRITE16_NPU(0x0036, round_addr & 0x007f);
    /* write addr to 0x0034,13bit,the data will be read to fifo address from  0 to round_addr */
    WRITE16_NPU(0x0034, 0x2000);

    while (count--)
    {
        *data_read = READ32_NPU(0x0000);
        data_read++;
    }
    /* disable */
    WRITE16_NPU(0x0034, 0x0000);
}

void round_cfg_srame_write(uint32_t round_addr, uint32_t *data_write_buf, uint32_t number)
{
    uint16_t count = 0;
    count = number;
    /* address */
    WRITE16_NPU(0x025c, 0x00);
    system_delay_tick(10);
    WRITE16_NPU(0x0036, round_addr & 0x007f);
    /* write addr to 0x0034,13bit,the data will be write to fifo address from  0 to round_addr */
    system_delay_tick(10);
    WRITE16_NPU(0x0034, 0x1000);
    system_delay_tick(10);
    while (count--)
    {
        WRITE32_NPU(0x0000, *data_write_buf);
        data_write_buf++;
    }
    /* disable */
    system_delay_tick(10);
    WRITE16_NPU(0x0034, 0x0000);
}

void wtn_npu_dma_start(void)
{
    WRITE16_NPU(0x0100, 0x0001);
}

void wtn_npu_dma_done(void)
{
    while (1)
    {
        if (READ16_NPU(0x002C) == 0x4000)
        {
            break;
        }
    }
    WRITE16_NPU(0x0026, 0x4000);
    WRITE16_NPU(0x0100, 0x0000);
}

void wtn_npu_dma_npu2soc(uint16_t regfile_addr, uint32_t soc_mem_addr, uint32_t data_size)
{
    uint16_t soc_mem_addrl = (soc_mem_addr & 0xFFFF);
    uint16_t soc_mem_addrh = (soc_mem_addr & 0xFFFF0000) >> 16;
    WRITE16_NPU(0x002A, 0x4000);

    WRITE16_NPU(0x010E, regfile_addr);

    WRITE16_NPU(0x0114, soc_mem_addrh);
    WRITE16_NPU(0x0118, soc_mem_addrl);

    WRITE16_NPU(0x010C, data_size);

    WRITE16_NPU(0x0102, 0x0008);
}

void wtn_npu_dma_soc2npu(uint32_t soc_mem_addr, uint16_t regfile_addr, uint32_t data_size)
{
    uint16_t soc_mem_addrl = (soc_mem_addr & 0xFFFF);
    uint16_t soc_mem_addrh = (soc_mem_addr & 0xFFFF0000) >> 16;

    WRITE16_NPU(0x002A, 0x4000);
    WRITE16_NPU(0x0112, soc_mem_addrh);
    WRITE16_NPU(0x0116, soc_mem_addrl);
    WRITE16_NPU(0x0110, regfile_addr);
    WRITE16_NPU(0x010A, data_size);
    WRITE16_NPU(0x0102, 0x0004);
}

void regfile_write_byte(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint8_t *data_write_buf)
{
    uint16_t address_map = regfile_start_addr % 4;
    uint16_t cycle = 0;
    uint16_t remain = 0;
    cycle = (regfile_write_length - (4 - address_map)) / 4;
    remain = (regfile_write_length - (4 - address_map)) % 4;
    if ((regfile_start_addr > OUT_REGFILE_DEPTH) || (regfile_start_addr + regfile_write_length > OUT_REGFILE_DEPTH))
    {
        printf("operation failure\n");
    }

    /* FIFO 8K EN */
    WRITE16_NPU(0x000E, 0x0000);
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* regfile_write_length */
    WRITE16_NPU(0x003A, ((regfile_write_length - 1) << 2) & 0x7ffc);
    /* write mode enable */
    WRITE16_NPU(0x0034, 0x4000);
    /* Write regfile by byte(8bit) */
    for (uint16_t j = 0;j < 4;j++)
    {
        if (address_map + j > 3)
        {
            break;
        }
        WRITE8_NPU(REGFILE_DATA+address_map + j, *data_write_buf);
        data_write_buf++;
    }
    for (uint16_t i = 0;i < cycle;i++)
    {
        WRITE8_NPU(REGFILE_DATA + 0, *data_write_buf);
        data_write_buf++;
        WRITE8_NPU(REGFILE_DATA + 1, *data_write_buf);
        data_write_buf++;
        WRITE8_NPU(REGFILE_DATA + 2, *data_write_buf);
        data_write_buf++;
        WRITE8_NPU(REGFILE_DATA + 3, *data_write_buf);
        data_write_buf++;
    }
    for (uint16_t j = 0;j < 4;j++)
    {
        if (j + 1 > remain)
        {
            break;
        }
        WRITE8_NPU(REGFILE_DATA + j, *data_write_buf);
        data_write_buf++;
    }
    /* write mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

void regfile_read_byte(uint32_t regfile_start_addr, uint32_t regfile_read_length, uint8_t *data_read_buf)
{
    uint16_t address_map = regfile_start_addr % 4;
    uint16_t cycle = 0;
    uint16_t remain = 0;
    cycle = (regfile_read_length - (4 - address_map)) / 4;
    remain = (regfile_read_length - (4 - address_map)) % 4;

    if ((regfile_start_addr > OUT_REGFILE_DEPTH) || (regfile_start_addr + regfile_read_length > OUT_REGFILE_DEPTH))
    {
        printf("operation failure\n");
    }
    /* FIFO 8K EN */
    WRITE16_NPU(0x000E, 0x0000);
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* read mode enable */
    WRITE16_NPU(0x0034, 0x8000);

    for (uint16_t j = 0;j < 4;j++)
    {
        if (address_map + j > 3)
        {
            break;
        }
        *data_read_buf = READ8_NPU(REGFILE_DATA+address_map + j);
        /* debug_fprintf(fp, "%d\n", *data_read_buf); */
        data_read_buf++;
    }
    for (uint16_t i = 0;i < cycle;i++)
    {
        *data_read_buf = READ8_NPU(REGFILE_DATA);
        data_read_buf++;
        *data_read_buf = READ8_NPU(REGFILE_DATA + 1);
        data_read_buf++;
        *data_read_buf = READ8_NPU(REGFILE_DATA + 2);
        data_read_buf++;
        *data_read_buf = READ8_NPU(REGFILE_DATA + 3);
        data_read_buf++;
    }
    for (uint16_t j = 0;j < 4;j++)
    {
        if (j + 1 > remain)
        {
            break;
        }
        *data_read_buf = READ8_NPU(REGFILE_DATA + j);
        data_read_buf++;
    }

    /* read mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

/* regfile_start_addr must even like 0,2,4,6,8......;regfile_write_length the number of 16bit */
void regfile_write_halfword(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint16_t *data_write_buf)
{
    uint16_t address_map = regfile_start_addr % 4;
    uint16_t cycle = 0;
    uint16_t remain = 0;
    if (address_map == 0)
    {
        cycle = (regfile_write_length - 2) / 2;
    }
    else if (address_map == 2)
    {
        cycle = (regfile_write_length - 1) / 2;
    }

    remain = (regfile_write_length - address_map / 2) % 2;
    if ((regfile_start_addr > OUT_REGFILE_DEPTH) || (regfile_start_addr + regfile_write_length > OUT_REGFILE_DEPTH))
    {
        printf("operation failure\n");
    }

    /* FIFO 8K EN */
    WRITE16_NPU(0x000E, 0x0000);
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* regfile_write_length */
    WRITE16_NPU(0x003A, ((regfile_write_length*2 - 1) << 2) & 0x7ffc);
    /* write mode enable */
    WRITE16_NPU(0x0034, 0x4000);
    /* Write regfile by byte(8bit) */
    for (uint16_t j = 0;j < 4;j = j + 2)
    {
        if (address_map + j > 2)
        {
            break;
        }
        WRITE16_NPU(REGFILE_DATA + address_map + j, *data_write_buf);
        data_write_buf++;
    }
    for (uint16_t i = 0;i < cycle;i++)
    {
        WRITE16_NPU(REGFILE_DATA + 0, *data_write_buf);
        data_write_buf++;

        WRITE16_NPU(REGFILE_DATA + 2, *data_write_buf);
        data_write_buf++;
    }

    if (remain > 0)
    {
        WRITE16_NPU(REGFILE_DATA, *data_write_buf);
        data_write_buf++;
    }

    /* write mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

void regfile_read_halfword(uint32_t regfile_start_addr, uint32_t regfile_read_length, uint16_t *data_read_buf)
{
    uint16_t address_map = regfile_start_addr % 4;
    uint16_t cycle = 0;
    uint16_t remain = 0;
    if (address_map == 0)
    {
        cycle = (regfile_read_length - 2) / 2;
    }
    else if (address_map == 2)
    {
        cycle = (regfile_read_length - 1) / 2;
    }

    if ((regfile_start_addr > OUT_REGFILE_DEPTH) || (regfile_start_addr + regfile_read_length > OUT_REGFILE_DEPTH))
    {
        printf("operation failure\n");
    }
    /* FIFO 8K EN */
    WRITE16_NPU(0x000E, 0x0000);
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* read mode enable */
    WRITE16_NPU(0x0034, 0x8000);

    for (uint16_t j = 0;j < 4;j = j + 2)
    {
        if (address_map + j > 2)
        {
            break;
        }
        *data_read_buf = READ16_NPU(REGFILE_DATA + address_map + j);
        data_read_buf++;
    }

    for (uint16_t i = 0;i < cycle;i++)
    {
        *data_read_buf = READ16_NPU(REGFILE_DATA + 0);
        data_read_buf++;
        *data_read_buf = READ16_NPU(REGFILE_DATA + 2);
        data_read_buf++;
    }

    if (remain > 0)
    {
        *data_read_buf = READ16_NPU(REGFILE_DATA + 0);
        data_read_buf++;
    }

    /* read mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

/* regfile_start_addr must even like 0,4,8......;regfile_write_length the number of 32bit */
void regfile_write_word(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint32_t *data_write_buf)
{
    uint16_t cycle = 0;

    cycle = regfile_write_length;
    if ((regfile_start_addr > OUT_REGFILE_DEPTH) || (regfile_start_addr + regfile_write_length > OUT_REGFILE_DEPTH))
    {
        printf("operation failure\n");
    }

    /* FIFO 8K EN */
    WRITE16_NPU(0x000E, 0x0000);
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* regfile_write_length */
    WRITE16_NPU(0x003A, ((regfile_write_length * 4 - 1) << 2) & 0x7ffc);
    /* write mode enable */
    WRITE16_NPU(0x0034, 0x4000);
    /* Write regfile by byte(8bit) */

    for (uint16_t i = 0;i < cycle;i++)
    {
        WRITE32_NPU(REGFILE_DATA + 0, *data_write_buf);
        data_write_buf++;
    }

    /* write mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

void regfile_read_word(uint32_t regfile_start_addr, uint32_t regfile_read_length, uint32_t *data_read_buf)
{
    uint16_t cycle = 0;

    cycle = regfile_read_length;

    if ((regfile_start_addr > OUT_REGFILE_DEPTH) || (regfile_start_addr + regfile_read_length > OUT_REGFILE_DEPTH))
    {
        printf("operation failure\n");
    }
    /* FIFO 8K EN */
    WRITE16_NPU(0x000E, 0x0000);
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* read mode enable */
    WRITE16_NPU(0x0034, 0x8000);

    for (uint16_t i = 0;i < cycle;i++)
    {
        *data_read_buf = READ32_NPU(REGFILE_DATA);
        data_read_buf++;
    }

    /* read mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

void ADC_Debug_Ctrl(void)
{
    /* [0]pi_sel=0, */
    WRITE16_NPU(0x025C, 0x0000);
    /* close adc_debug_mode, init must before adc_debug_mode=1 */
    WRITE16_NPU(0x02EC, READ16_NPU(0x02EC) & ~(1 << 2));
    WRITE16_NPU(0x003E, 0x0000);
    WRITE16_NPU(0x0036, 0x0000);
    WRITE16_NPU(0x0034, 0x1000);
    WRITE32_NPU(0x0000, 0x01040002);
    WRITE32_NPU(0x0000, 0x00000000);
    WRITE32_NPU(0x0000, 0x10000000);
    WRITE32_NPU(0x0000, 0x03ff0000);
    WRITE16_NPU(0x0034, 0x0000);

    /* clr_dacfifo */
    WRITE16_NPU(0x002E, READ16_NPU(0x002E) | (1 << 6));
    WRITE16_NPU(0x002E, READ16_NPU(0x002E) & ~(1 << 6));
    /* enable adc_debug_mode */
    WRITE16_NPU(0x02EC, READ16_NPU(0x02EC) | (1 << 2));
    /* set init_round/max_round */
    WRITE16_NPU(0x003C, 0x0001);
    /* start_infer */
    WRITE16_NPU(0x003E, 0x8000);
    /* wait enough time */
    Delay_nop(10);
    /* WTM2101 set soft-reset to npu module */
    WRITE16(0x40002018, READ8(0x40002018) | (1 << 5));
    WRITE16(0x40002018, READ8(0x40002018) & ~(1 << 5));
}

/* regfile_start_addr >=7168 */
void regfile_write_byte_high_fifo(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint8_t *data_write_buf, uint16_t fifo_depth)
{
    uint16_t address_map = regfile_start_addr % 4;
    uint16_t cycle = 0;
    uint16_t remain = 0;
    cycle = (regfile_write_length - (4 - address_map)) / 4;
    remain = (regfile_write_length - (4 - address_map)) % 4;
    if ((regfile_start_addr > OUT_REGFILE_DEPTH) || (regfile_start_addr + regfile_write_length > OUT_REGFILE_DEPTH))
    {
        printf("operation failure\n");
    }

    /* FIFO high 1K EN */
    WRITE16_NPU(0x000E, 0x8000);
    WRITE16_NPU(0x000E, (0x8000|((fifo_depth-1)&0x003ff))); /* write fifo depth */
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* regfile_write_length */
    WRITE16_NPU(0x003A, ((regfile_write_length - 1) << 2) & 0x7ffc);
    /* write mode enable */
    WRITE16_NPU(0x0034, 0x4000);
    /* Write regfile by byte(8bit) */
    for (uint16_t j = 0;j < 4;j++)
    {
        if (address_map + j > 3)
        {
            break;
        }
        WRITE8_NPU(REGFILE_DATA + address_map + j, *data_write_buf);
        data_write_buf++;
    }
    for (uint16_t i = 0;i < cycle;i++)
    {
        WRITE8_NPU(REGFILE_DATA + 0, *data_write_buf);
        data_write_buf++;
        WRITE8_NPU(REGFILE_DATA + 1, *data_write_buf);
        data_write_buf++;
        WRITE8_NPU(REGFILE_DATA + 2, *data_write_buf);
        data_write_buf++;
        WRITE8_NPU(REGFILE_DATA + 3, *data_write_buf);
        data_write_buf++;
    }
    for (uint16_t j = 0;j < 4;j++)
    {
        if (j + 1 > remain)
        {
            break;
        }
        WRITE8_NPU(REGFILE_DATA + j, *data_write_buf);
        data_write_buf++;
    }
    /* write mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

/* regfile_start_addr must even like 0,2,4,6,8......;regfile_write_length the number of 8bit,must be n*4,fifo_depth the number of 8bit,must be n*4;*/
void regfile_write_halfword_high_fifo(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint16_t *data_write_buf, uint16_t fifo_depth)
{
    uint16_t address_map = regfile_start_addr % 4;
    uint16_t cycle = 0;
    uint16_t remain = 0;
    if (address_map == 0)
    {
        cycle = (regfile_write_length - 4) / 4;
    }
    else if (address_map == 2)
    {
        cycle = (regfile_write_length - 2) / 4;
    }

    remain = ((regfile_write_length - address_map) % 4) / 2;

    /* FIFO high 1K EN */
    WRITE16_NPU(0x000E, 0x8000);
    WRITE16_NPU(0x000E, (0x8000 | ((fifo_depth - 1) & 0x003ff))); /* write fifo depth */
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* regfile_write_length */
    WRITE16_NPU(0x003A, ((regfile_write_length - 1) << 2) & 0x7ffc);
    /* write mode enable */
    WRITE16_NPU(0x0034, 0x4000);
    /* Write regfile by byte(8bit) */
    for (uint16_t j = 0;j < 4;j = j + 2)
    {
        if (address_map + j > 2)
        {
            break;
        }
        WRITE16_NPU(REGFILE_DATA+address_map + j, *data_write_buf);
        data_write_buf++;
    }
    for (uint16_t i = 0;i < cycle;i++)
    {
        WRITE16_NPU(REGFILE_DATA + 0, *data_write_buf);
        data_write_buf++;

        WRITE16_NPU(REGFILE_DATA + 2, *data_write_buf);
        data_write_buf++;
    }

    if(remain > 0)
    {
        WRITE16_NPU(REGFILE_DATA, *data_write_buf);
        data_write_buf++;
    }

    /* write mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

/* regfile_start_addr must even like 0,4,8......;regfile_write_length the number of 8bit,must be n*4,fifo_depth the number of 8bit,must be n*4; */
void regfile_write_word_high_fifo(uint32_t regfile_start_addr, uint32_t regfile_write_length, uint32_t *data_write_buf, uint16_t fifo_depth)
{
    uint16_t cycle = 0;

    cycle = regfile_write_length / 4;

    /* FIFO high 1K EN */
    WRITE16_NPU(0x000E, 0x8000);
    WRITE16_NPU(0x000E, (0x8000 | ((fifo_depth - 1) & 0x003ff))); /* write fifo depth */
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* regfile_write_length */
    WRITE16_NPU(0x003A, ((regfile_write_length - 1) << 2) & 0x7ffc);
    /* WRITE16_NPU(0x003A, ((fifo_depth) << 2) & 0x7ffc); */
    /* write mode enable */
    WRITE16_NPU(0x0034, 0x4000);
    /* Write regfile by byte(8bit) */
    system_delay_tick(10);
    for (uint16_t i = 0;i < cycle;i++)
    {
        WRITE32_NPU(REGFILE_DATA + 0, *data_write_buf);
        data_write_buf++;
    }
    system_delay_tick(10);
    /* write mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}

void regfile_read_byte_fast(uint32_t regfile_start_addr, uint32_t regfile_read_length, uint8_t *data_read_buf)
{
    uint32_t regfile_data = 0x00;
    uint16_t address_map = regfile_start_addr % 4;
    uint16_t cycle = 0;
    uint16_t remain = 0;
    cycle = (regfile_read_length - (4 - address_map)) / 4;
    remain = (regfile_read_length - (4 - address_map)) % 4;

    if ((regfile_start_addr > OUT_REGFILE_DEPTH) || (regfile_start_addr + regfile_read_length > OUT_REGFILE_DEPTH))
    {
        printf("operation failure\n");
    }
    /* FIFO 8K EN */
    WRITE16_NPU(0x000E, 0x0000);
    /* write addr to 0x0038,[12:0],the data will be write to fifo address from  0 to regfile_addr */
    WRITE16_NPU(0x0038, regfile_start_addr & 0x1fff);
    /* read mode enable */
    WRITE16_NPU(0x0034, 0x8000);

    for (uint16_t j = 0;j < 4;j++)
    {
        if (address_map + j > 3)
        {
            break;
        }
        *data_read_buf = READ8_NPU(REGFILE_DATA + address_map + j);
        /* debug_fprintf(fp, "%d\n", *data_read_buf); */
        data_read_buf++;
    }
    for (uint16_t i = 0;i < cycle;i++)
    {
        regfile_data = READ32_NPU(REGFILE_DATA);
        /* printf("i--%d--0x%x\n",i,regfile_data); */
        *data_read_buf = (uint8_t)((regfile_data & 0xff000000) >> 24);
        data_read_buf++;
        *data_read_buf = (uint8_t)((regfile_data & 0x00ff0000) >> 16);
        data_read_buf++;

        *data_read_buf = (uint8_t)((regfile_data & 0x0000ff00) >> 8);
        data_read_buf++;

        *data_read_buf = (uint8_t)((regfile_data & 0x000000ff));
        data_read_buf++;
    }
    for (uint16_t j = 0;j < 4;j++)
    {
        if (j + 1 > remain)
        {
            break;
        }
        *data_read_buf = READ8_NPU(REGFILE_DATA + j);
        data_read_buf++;
    }

    /* read mode disable */
    WRITE16_NPU(0x0034, 0x0000);
}
