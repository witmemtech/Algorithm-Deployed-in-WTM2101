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

#define I2C_WR 0 /* д����bit */
#define I2C_RD 1 /* ������bit */

#define I2C_SCL_PIN GPIO_PIN_5
#define I2C_SDA_PIN GPIO_PIN_4

#define	I2C_SCL_IO	GPIO_AF5_GPIO
#define	I2C_SDA_IO	GPIO_AF4_GPIO

#define DELAY_NUM	100



/* SCL����ߵ�ƽ */
static void I2C_SCL_HIGH(void)
{
    GPIO_OutputHi(GPIOA, I2C_SCL_PIN);
}

/* SCL����͵�ƽ */
static void I2C_SCL_LOW(void)
{
    GPIO_OutputLo(GPIOA, I2C_SCL_PIN);
}

/* SDA����ߵ�ƽ */
static void I2C_SDA_HIGH(void)
{
    GPIO_OutputHi(GPIOA, I2C_SDA_PIN);
}

/* SDA����͵�ƽ */
static void I2C_SDA_LOW(void)
{
    GPIO_OutputLo(GPIOA, I2C_SDA_PIN);
}

/* ��ȡ�����ƽ */
static uint8_t I2C_SDA_READ(void)
{
    return (GPIO_ReadInputDataBit(GPIOA, I2C_SDA_PIN));
}

/* �������� */
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

/* ������� */
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
 * ��������: I2C����λ�ӳ٣����400KHz
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ����32MHz --- 180KHz
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
 * ��������: CPU����I2C���������ź�
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ������
 */
void I2C_Start(void)
{
    /*SDA���������*/
    I2C_SDA_OUTPUT();
    /* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
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
 * ��������: CPU����I2C����ֹͣ�ź�
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ������
 */
void I2C_Stop(void)
{
    /*SDA���������*/
    I2C_SDA_OUTPUT();
    /* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
    I2C_SDA_LOW();
	I2C_Delay();
    I2C_SCL_HIGH();
    I2C_Delay();
    I2C_SDA_HIGH();
	I2C_Delay();
}

/**
 * ��������: CPU��I2C�����豸����8bit����
 * �������: Byte �� �ȴ����͵��ֽ�
 * �� �� ֵ: ��
 * ˵    ������
 */
void I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    /*SDA���������*/
    I2C_SDA_OUTPUT();
	I2C_Delay();
    /* �ȷ����ֽڵĸ�λbit7 */
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
            I2C_SDA_HIGH(); // �ͷ�����
        }
        Byte <<= 1; /* ����һ��bit */
        I2C_Delay();
    }
}

/**
 * ��������: CPU��I2C�����豸��ȡ8bit����
 * �������: ��
 * �� �� ֵ: ����������
 * ˵    ������
 */
uint8_t I2C_ReadByte(void)
{
    uint8_t i;
    uint8_t value;
    // /*SDA����������*/
    // I2C_SDA_INPUT();
    /* ������1��bitΪ���ݵ�bit7 */
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
 * ��������: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
 * �������: ��
 * �� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
 * ˵    ������
 */
uint8_t I2C_WaitAck(void)
{
    uint8_t err_cnt = 0;

    /*SDA����������*/
    I2C_SDA_INPUT();

    //I2C_SDA_HIGH(); /* SDA���߱��ͷţ�����������������ɸߵ�ƽ */
    I2C_Delay();
    //I2C_Delay();
    I2C_SCL_HIGH(); /* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
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
 * ��������: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
 * �������: ��
 * �� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
 * ˵    ������
 */
uint8_t I2C_WaitAckfyy(void)
{
    uint8_t err_cnt = 0;

    /*SDA����������*/
    I2C_SDA_INPUT();

    //I2C_SDA_HIGH(); /* SDA���߱��ͷţ�����������������ɸߵ�ƽ */
    I2C_Delay();
    //I2C_Delay();
    I2C_SCL_HIGH(); /* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
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
 * ��������: CPU����һ��ACK�ź�
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ������
 */
void I2C_Ack(void)
{
    /*SDA���������*/
    I2C_SDA_OUTPUT();
    I2C_SDA_LOW(); /* CPU����SDA = 0 */
    I2C_Delay();
    I2C_SCL_HIGH(); /* CPU����1��ʱ�� */
    I2C_Delay();
    I2C_SCL_LOW();
    I2C_Delay();
    I2C_SDA_HIGH(); /* CPU�ͷ�SDA���� */
    /*add delay*/
    I2C_Delay();
    I2C_SDA_LOW();
}

/**
 * ��������: CPU����1��NACK�ź�
 * �������: ��
 * �� �� ֵ: ��
 * ˵    ������
 */
void I2C_NAck(void)
{
    /*SDA���������*/
    I2C_SDA_OUTPUT();
    I2C_SDA_HIGH(); /* CPU����SDA = 1 */
    I2C_Delay();
    I2C_SCL_HIGH(); /* CPU����1��ʱ�� */
    I2C_Delay();
    I2C_SCL_LOW();
    I2C_Delay();
}

/**
 * ��������: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
 * �������: _Address���豸��I2C���ߵ�ַ
 * �� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
 * ˵    �����ڷ���I2C�豸ǰ�����ȵ��� I2C_CheckDevice() ���I2C�豸�Ƿ��������ú���������GPIO
 */
uint8_t I2C_CheckDevice(uint8_t _Address)
{
    uint8_t ucAck;

    I2C_Start(); /* ���������ź� */
    /* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
    I2C_SendByte(_Address | I2C_WR);
    ucAck = I2C_WaitAck(); /* ����豸��ACKӦ�� */
    I2C_Stop();            /* ����ֹͣ�ź� */
    return ucAck;
}

/**
 * ��������: �жϴ���EERPOM�Ƿ�����
 * �������: ��
 * �� �� ֵ: 1 ��ʾ������ 0 ��ʾ������
 * ˵    ������
 */
uint8_t Codec_CheckOk(uint8_t _Address)
{
    if (I2C_CheckDevice(_Address) == 0)
    {
        return 1;
    }
    else
    {
        /* ʧ�ܺ��мǷ���I2C����ֹͣ�ź� */
        I2C_Stop();
        return 0;
    }
}

void Codec_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
	int i;

    /* enable GPIOA clock */
    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN, ENABLE);

    /* init the PA0,1 pin with output mode */
    GPIO_InitStructure.Pin = I2C_SCL_PIN | I2C_SDA_PIN;
    GPIO_InitStructure.Alternate = I2C_SCL_IO | I2C_SDA_IO;
    GPIO_InitStructure.Mode = GPIO_MODE_OUT;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    I2C_Stop();
}


uint8_t CodecReadByte(uint8_t device_addr, uint8_t ram_addr, uint8_t *data ,uint16_t len)
{
    uint16_t i;
    uint8_t i2c_buf[8];
    uint16_t len_f = 2;
    len_f =len;
    /* ���ô���EEPROM�漴��ȡָ�����У�������ȡ�����ֽ� */

    /* ��1��������I2C���������ź� */
    I2C_Start();

    /* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
    I2C_SendByte(device_addr | I2C_WR); /* �˴���дָ�� */

    /* ��3�����ȴ�ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM������Ӧ�� */
    }

    /* ��4���������ֽڵ�ַ��24C02ֻ��256�ֽڣ����1���ֽھ͹��ˣ������24C04���ϣ���ô�˴���Ҫ���������ַ */
    I2C_SendByte(ram_addr);

    /* ��5�����ȴ�ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM������Ӧ�� */
    }

    /* ��6������������I2C���ߡ�ǰ��Ĵ����Ŀ����EEPROM���͵�ַ�����濪ʼ��ȡ���� */
    I2C_Start();

    /* ��7������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
    I2C_SendByte(device_addr | I2C_RD); /* �˴��Ƕ�ָ�� */

    /* ��8��������ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM������Ӧ�� */
    }

    /* ��9����ѭ����ȡ���� */


    while(len_f--)
    {
      I2C_SDA_INPUT();
      //*data = I2C_ReadByte(); /* ��1���ֽ� */
      *(data++) = I2C_ReadByte();
      if(len_f>=1)I2C_Ack();
      //I2C_SDA_INPUT();
      //i2c_buf[1] = I2C_ReadByte();
      ////*data = (*data << 2) | I2C_ReadByte();
      //*data = *i2c_buf;
    }
    //I2C_SDA_INPUT();

    //*data = I2C_ReadByte(); /* ��1���ֽ� */
   
    //*data = (*data << 2) | I2C_ReadByte();

     /* ��1���ֽ� */
    
    /* ÿ����1���ֽں���Ҫ����Ack�� ���һ���ֽڲ���ҪAck����Nack */

    I2C_NAck(); /* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */

    /* ����I2C����ֹͣ�ź� */
    I2C_Stop();
    return 1; /* ִ�гɹ� */

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
    /* ����I2C����ֹͣ�ź� */
    I2C_Stop();
    return 0;
}




uint8_t DeviceSetSoftMode(uint8_t device_addr, uint8_t ram_addr, uint8_t *data , uint16_t len)
{
    uint16_t i, m;
    uint16_t len_f = len;
    /*���ڣ�������ֹͣ�źţ������ڲ�д������*/
    I2C_Stop();

    /* ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms
        CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
    */
    for (m = 0; m < 100; m++)
    {
        /* ��1��������I2C���������ź� */
        I2C_Start();

        /* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
        I2C_SendByte(device_addr | I2C_WR); /* �˴���дָ�� */

        /* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ�� */
        if (I2C_WaitAck() == 0)
        {
            break;
        }
    }
    if (m == 100)
    {
        goto cmd_fail; /* EEPROM����д��ʱ */
    }

    /* ��4���������ֽڵ�ַ��24C02ֻ��256�ֽڣ����1���ֽھ͹��ˣ������24C04���ϣ���ô�˴���Ҫ���������ַ */
 

    
    I2C_SendByte(ram_addr);

    /* ��5�����ȴ�ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM������Ӧ�� */
    }

    /* ��6������ʼд������ */
    //I2C_SendByte(data);
    while(len_f--)
    {
     I2C_SendByte(*(data++)); 
        if (I2C_WaitAck() != 0)
        {
            goto cmd_fail; /* EEPROM������Ӧ�� */
        }
    }
    /* ��7��������ACK */
    if (I2C_WaitAck() != 0)
    {
        goto cmd_fail; /* EEPROM������Ӧ�� */
    }

    /* ����ִ�гɹ�������I2C����ֹͣ�ź� */
    I2C_Stop();
    return 1;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
    /* ����I2C����ֹͣ�ź� */
    I2C_Stop();
    return 0;
}

void DelayTest()
{
    I2C_SCL_HIGH(); /* CPU����1��ʱ�� */
    I2C_Delay();
    I2C_SCL_LOW();
    I2C_Delay();
}