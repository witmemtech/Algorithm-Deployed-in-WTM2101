#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audio.h"
#include "dma.h"
#include "fbank.h"
#include "gpio.h"
#include "i2c.h"
#include "i2s.h"
#include "main.h"
#include "pmu.h"
#include "pwm.h"
#include "qspi.h"
#include "rcc.h"
#include "rtc.h"
#include "spi.h"
#include "time.h"
#include "uart.h"
#include "wdt.h"

#define I2C_WR 0 /* 写控制bit */
#define I2C_RD 1 /* 读控制bit */

#define I2C_SCL_PIN GPIO_PIN_5
#define I2C_SDA_PIN GPIO_PIN_4

#define	I2C_SCL_IO	GPIO_AF5_GPIO
#define	I2C_SDA_IO	GPIO_AF4_GPIO

#define DELAY_NUM	200



/* SCL输出高电平 */
static void I2C_SCL_HIGH(void)
{
    GPIO_OutputHi(GPIOA, I2C_SCL_PIN);
}

/* SCL输出低电平 */
static void I2C_SCL_LOW(void)
{
    GPIO_OutputLo(GPIOA, I2C_SCL_PIN);
}

/* SDA输出高电平 */
static void I2C_SDA_HIGH(void)
{
    GPIO_OutputHi(GPIOA, I2C_SDA_PIN);
}

/* SDA输出低电平 */
static void I2C_SDA_LOW(void)
{
    GPIO_OutputLo(GPIOA, I2C_SDA_PIN);
}

/* 读取输入电平 */
static uint8_t I2C_SDA_READ(void)
{
    return (GPIO_ReadInputDataBit(GPIOA, I2C_SDA_PIN));
}

/* 上拉输入 */
static void I2C_SDA_INPUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* enable GPIOA clock */
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN, ENABLE);

    /* init the PA0,1 pin with output mode */
    GPIO_InitStructure.Pin = I2C_SDA_PIN;
    GPIO_InitStructure.Alternate = I2C_SDA_IO;
    GPIO_InitStructure.Mode = GPIO_MODE_INPU;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/* 推挽输出 */
static void I2C_SDA_OUTPUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* enable GPIOA clock */
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN, ENABLE);

    /* init the PA0,1 pin with output mode */
    GPIO_InitStructure.Pin = I2C_SDA_PIN;
    GPIO_InitStructure.Alternate = I2C_SDA_IO;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

volatile static uint32_t test_cnt = 0;
/**
 * 函数功能: I2C总线位延迟，最快400KHz
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：32MHz --- 180KHz
 */
static void I2C_Delay(void)
{
    test_cnt = 0;
    for (uint16_t i = 0; i < DELAY_NUM; i++)
    {
        test_cnt++;
    }
}

static void I2C_Delay_Ack(void)
{
    test_cnt = 0;
    for (uint16_t i = 0; i < DELAY_NUM; i++)
    {
        test_cnt++;
    }
}

/**
 * 函数功能: CPU发起I2C总线启动信号
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_Start(void)
{
    /*SDA引脚做输出*/
    I2C_SDA_OUTPUT();
    /* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
    I2C_SDA_HIGH();
	I2C_Delay();
    I2C_SCL_HIGH();
    I2C_Delay();
    I2C_SDA_LOW();
    I2C_Delay();
    I2C_SCL_LOW();
    I2C_Delay();
}

/**
 * 函数功能: CPU发起I2C总线停止信号
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_Stop(void)
{
    /*SDA引脚做输出*/
    I2C_SDA_OUTPUT();
    /* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
    I2C_SDA_LOW();
	I2C_Delay();
    I2C_SCL_HIGH();
    I2C_Delay();
    I2C_SDA_HIGH();
	I2C_Delay();
}

/**
 * 函数功能: CPU向I2C总线设备发送8bit数据
 * 输入参数: Byte ： 等待发送的字节
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    /*SDA引脚做输出*/
    I2C_SDA_OUTPUT();
	I2C_Delay();
    /* 先发送字节的高位bit7 */
    for (i = 0; i < 8; i++)
    {
        if (Byte & 0x80)
        {
            I2C_SDA_HIGH();
        }
        else
        {
            I2C_SDA_LOW();
        }
        I2C_Delay();
        I2C_SCL_HIGH();
        I2C_Delay();
        I2C_SCL_LOW();
		I2C_Delay();
        if (i == 7)
        {
            I2C_SDA_HIGH(); // 释放总线
        }
        Byte <<= 1; /* 左移一个bit */
        I2C_Delay();
    }
}

/**
 * 函数功能: CPU从I2C总线设备读取8bit数据
 * 输入参数: 无
 * 返 回 值: 读到的数据
 * 说    明：无
 */
uint8_t I2C_ReadByte(void)
{
    uint8_t i;
    uint8_t value;
    // /*SDA引脚做输入*/
    // I2C_SDA_INPUT();
    /* 读到第1个bit为数据的bit7 */
    value = 0;
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        I2C_SCL_HIGH();
        I2C_Delay();
        if (I2C_SDA_READ())
        {
            value++;
        }
        I2C_SCL_LOW();
        I2C_Delay();
    }
    return value;
}

/**
 * 函数功能: CPU产生一个时钟，并读取器件的ACK应答信号
 * 输入参数: 无
 * 返 回 值: 返回0表示正确应答，1表示无器件响应
 * 说    明：无
 */
uint8_t I2C_WaitAck(void)
{
    uint8_t err_cnt = 0;

    /*SDA引脚做输入*/
    I2C_SDA_INPUT();

    I2C_SDA_HIGH(); /* SDA总线被释放，由外界上拉电阻拉成高电平 */
    I2C_Delay();

    I2C_SCL_HIGH(); /* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
    // I2C_Delay();
    I2C_Delay_Ack();

    while (I2C_SDA_READ())
    {
        err_cnt++;
        if (err_cnt > 100)
        {
            I2C_SCL_LOW();
            I2C_Delay();
            return 1;
        }
    }
    I2C_SCL_LOW();
    I2C_Delay();
    return 0;
}

/**
 * 函数功能: CPU产生一个ACK信号
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_Ack(void)
{
    /*SDA引脚做输出*/
    I2C_SDA_OUTPUT();
    I2C_SDA_LOW(); /* CPU驱动SDA = 0 */
    I2C_Delay();
    I2C_SCL_HIGH(); /* CPU产生1个时钟 */
    I2C_Delay();
    I2C_SCL_LOW();
    I2C_Delay();
    I2C_SDA_HIGH(); /* CPU释放SDA总线 */
    /*add delay*/
    I2C_Delay();
    I2C_SDA_LOW();
}

/**
 * 函数功能: CPU产生1个NACK信号
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_NAck(void)
{
    /*SDA引脚做输出*/
    I2C_SDA_OUTPUT();
    I2C_SDA_HIGH(); /* CPU驱动SDA = 1 */
    I2C_Delay();
    I2C_SCL_HIGH(); /* CPU产生1个时钟 */
    I2C_Delay();
    I2C_SCL_LOW();
    I2C_Delay();
}

/**
 * 函数功能: 检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
 * 输入参数: _Address：设备的I2C总线地址
 * 返 回 值: 返回值 0 表示正确， 返回1表示未探测到
 * 说    明：在访问I2C设备前，请先调用 I2C_CheckDevice() 检测I2C设备是否正常，该函数会配置GPIO
 */
uint8_t I2C_CheckDevice(uint8_t _Address)
{
    uint8_t ucAck;

    I2C_Start(); /* 发送启动信号 */
    /* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
    I2C_SendByte(_Address | I2C_WR);
    ucAck = I2C_WaitAck(); /* 检测设备的ACK应答 */
    I2C_Stop();            /* 发送停止信号 */
    return ucAck;
}

/**
 * 函数功能: 判断串行EERPOM是否正常
 * 输入参数: 无
 * 返 回 值: 1 表示正常， 0 表示不正常
 * 说    明：无
 */
uint8_t Codec_CheckOk(uint8_t _Address)
{
    if (I2C_CheckDevice(_Address) == 0)
    {
        return 1;
    }
    else
    {
        /* 失败后，切记发送I2C总线停止信号 */
        I2C_Stop();
        return 0;
    }
}
void i2c_config(void)
{
    I2C_InitTypeDef I2C_InitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;
  
    RCC_CLK_EN_Ctl(RCC_I2C_PCLKEN | RCC_GPIO_HCLKEN,ENABLE);
    
    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPU;
    GPIO_InitStructure.Alternate = GPIO_AF4_I2C | GPIO_AF5_I2C;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_OD_Set(GPIOA,GPIO_PIN_4 | GPIO_PIN_5,ENABLE);

    I2C_InitStruct.Mode = I2C_MODE_MASTER;
    I2C_InitStruct.Speed = I2C_SPEED_FAST;
    I2C_InitStruct.AddrMode = I2C_ADDR_7BITS_MASTER;
    I2C_InitStruct.Restart = I2C_RESTART_ENABLE;
    I2C_InitStruct.Address = 0x18;
    I2C_InitStruct.Rate =400000;
    I2C_InitStruct.SpkLen = 1;
    I2C_Init(I2C,&I2C_InitStruct);
}
void Codec_Init()
{
 //   GPIO_InitTypeDef GPIO_InitStructure;
	//int i;

 //   /* enable GPIOA clock */
 //   RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN, ENABLE);

 //   /* init the PA0,1 pin with output mode */
 //   GPIO_InitStructure.Pin = I2C_SCL_PIN | I2C_SDA_PIN;
 //   GPIO_InitStructure.Alternate = I2C_SCL_IO | I2C_SDA_IO;
 //   GPIO_InitStructure.Mode = GPIO_MODE_OUT;

 //   GPIO_Init(GPIOA, &GPIO_InitStructure);

 //   I2C_Stop();
    i2c_config();
}

uint8_t CodecReadByte(uint8_t device_addr, uint8_t ram_addr, uint8_t *data)
{
    uint16_t i;

    /* 采用串行EEPROM随即读取指令序列，连续读取若干字节 */

    /* 第1步：发起I2C总线启动信号 */
    I2C_Start();

    /* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
    I2C_SendByte(device_addr | I2C_WR); /* 此处是写指令 */

    /* 第3步：等待ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM器件无应答 */
    }

    /* 第4步：发送字节地址，24C02只有256字节，因此1个字节就够了，如果是24C04以上，那么此处需要连发多个地址 */
    I2C_SendByte(ram_addr);

    /* 第5步：等待ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM器件无应答 */
    }

    /* 第6步：重新启动I2C总线。前面的代码的目的向EEPROM传送地址，下面开始读取数据 */
    I2C_Start();

    /* 第7步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
    I2C_SendByte(device_addr | I2C_RD); /* 此处是读指令 */

    /* 第8步：发送ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM器件无应答 */
    }

    /* 第9步：循环读取数据 */

    /*SDA引脚做输入*/
    I2C_SDA_INPUT();
    *data = I2C_ReadByte(); /* 读1个字节 */

    /* 每读完1个字节后，需要发送Ack， 最后一个字节不需要Ack，发Nack */

    I2C_NAck(); /* 最后1个字节读完后，CPU产生NACK信号(驱动SDA = 1) */

    /* 发送I2C总线停止信号 */
    I2C_Stop();
    return 1; /* 执行成功 */

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
    /* 发送I2C总线停止信号 */
    I2C_Stop();
    return 0;
}

uint8_t DeviceSetSoftMode(uint8_t device_addr, uint8_t ram_addr, uint8_t data)
{
    uint16_t i, m;

    /*　第０步：发停止信号，启动内部写操作　*/
    I2C_Stop();

    /* 通过检查器件应答的方式，判断内部写操作是否完成, 一般小于 10ms
        CLK频率为200KHz时，查询次数为30次左右
    */
    for (m = 0; m < 100; m++)
    {
        /* 第1步：发起I2C总线启动信号 */
        I2C_Start();

        /* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
        I2C_SendByte(device_addr | I2C_WR); /* 此处是写指令 */

        /* 第3步：发送一个时钟，判断器件是否正确应答 */
        if (I2C_WaitAck() == 0)
        {
            break;
        }
    }
    if (m == 100)
    {
        goto cmd_fail; /* EEPROM器件写超时 */
    }

    /* 第4步：发送字节地址，24C02只有256字节，因此1个字节就够了，如果是24C04以上，那么此处需要连发多个地址 */
    I2C_SendByte(ram_addr);

    /* 第5步：等待ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM器件无应答 */
    }

    /* 第6步：开始写入数据 */
    I2C_SendByte(data);

    /* 第7步：发送ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM器件无应答 */
    }

    /* 命令执行成功，发送I2C总线停止信号 */
    I2C_Stop();
    return 1;

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
    /* 发送I2C总线停止信号 */
    I2C_Stop();
    return 0;
}

void DelayTest()
{
    I2C_SCL_HIGH(); /* CPU产生1个时钟 */
    I2C_Delay();
    I2C_SCL_LOW();
    I2C_Delay();
}