/**
  ******************************************************************************
  * @file    lcd_ILI9341.c 
  * @brief   This file provide driver for lcd 
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
#include "lcd_ILI9341.h"
#include "GUI.h"
#include "witin_pic.h"

_lcd_dev lcddev;

static void Spi_Cs_High()
{
    GPIO_OutputHi(GPIOA, GPIO_PIN_1);
}

static void Spi_Cs_Low()
{
    GPIO_OutputLo(GPIOA, GPIO_PIN_1);
}

static void Lcd_Rs_Low()
{
    GPIO_OutputLo(GPIOA, LCD_COMMAND_DATA_CHANGE);
}

static void Lcd_Rs_High()
{
    GPIO_OutputHi(GPIOA, LCD_COMMAND_DATA_CHANGE);
}

static void Lcd_Reset(void)
{
    GPIO_OutputLo(GPIOA, LCD_RESET_PIN);
    system_delay_ms(100); //delay 100ms
    GPIO_OutputHi(GPIOA, LCD_RESET_PIN);
    system_delay_ms(100); //delay 100ms
}

static void Lcd_Wr_Reg(uint8_t data)
{
    Spi_Cs_Low();
    Lcd_Rs_Low();
    SPI_Send_Receive(SPIM,1, &data, 1, NULL, 0);
    Spi_Cs_High();
}

static void Lcd_Wr_Data(uint8_t data)
{
   Spi_Cs_Low();
   Lcd_Rs_High();
   SPI_Send_Receive(SPIM, 1, &data, 1, NULL, 0);
   Spi_Cs_High();
}

static void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
    Lcd_Wr_Reg(LCD_Reg);
    Lcd_Wr_Data(LCD_RegValue);
}

void Lcd_WriteData_16Bit(uint16_t data)
{
   Spi_Cs_Low();
   Lcd_Rs_High();
   SPI_Send_Receive(SPIM, 1, ((uint8_t *)&data + 1), 1, NULL, 0);
   SPI_Send_Receive(SPIM, 1, (uint8_t *)&data, 1, NULL, 0);
   Spi_Cs_High();
}

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);
}

static void LCD_direction(uint8_t direction)
{
    lcddev.setxcmd=0x2A;
    lcddev.setycmd=0x2B;
    lcddev.wramcmd=0x2C;
    switch(direction){
        case 0:
            lcddev.width=LCD_W;
            lcddev.height=LCD_H;
            LCD_WriteReg(0x36,(1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
            break;
        case 1:
            lcddev.width=LCD_H;
            lcddev.height=LCD_W;
            LCD_WriteReg(0x36,(1<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
            break;
        case 2:
            lcddev.width=LCD_W;
            lcddev.height=LCD_H;
            LCD_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
            break;
        case 3:
            lcddev.width=LCD_H;
            lcddev.height=LCD_W;
            LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
            break;
        default:
            break;
    }
}

static void LCD_WriteRAM_Prepare(void)
{
    Lcd_Wr_Reg(lcddev.wramcmd);
}

void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
{
    Lcd_Wr_Reg(lcddev.setxcmd);
    Lcd_Wr_Data(xStar>>8);
    Lcd_Wr_Data(0x00FF&xStar);
    Lcd_Wr_Data(xEnd>>8);
    Lcd_Wr_Data(0x00FF&xEnd);

    Lcd_Wr_Reg(lcddev.setycmd);
    Lcd_Wr_Data(yStar>>8);
    Lcd_Wr_Data(0x00FF&yStar);
    Lcd_Wr_Data(yEnd>>8);
    Lcd_Wr_Data(0x00FF&yEnd);

    LCD_WriteRAM_Prepare();
}

static void LCD_Clear(uint16_t Color)
{
    unsigned int i,m;
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
    Lcd_Rs_High();
    for(i=0;i<lcddev.height;i++)
    {
        for(m=0;m<lcddev.width;m++)
        {
            Lcd_WriteData_16Bit(Color);
        }
    }
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/
extern uint16_t POINT_COLOR;
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);
	Lcd_WriteData_16Bit(POINT_COLOR);
}

void DrawTestPage(uint8_t *str)
{
    LCD_Clear(WHITE);
    LCD_Fill(0,0,lcddev.width,20,BLUE);
    LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
    POINT_COLOR=WHITE;
    Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);
    Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"http://www.witintech.com",16,1);
}

void lcd_init(void)
{
    Lcd_Reset(); //reset lcd

//*************2.2inch ILI9341 init**********//
    Lcd_Wr_Reg(0xCF);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0xD9);   //C1
    Lcd_Wr_Data(0X30);
    Lcd_Wr_Reg(0xED);
    Lcd_Wr_Data(0x64);
    Lcd_Wr_Data(0x03);
    Lcd_Wr_Data(0X12);
    Lcd_Wr_Data(0X81);
    Lcd_Wr_Reg(0xE8);
    Lcd_Wr_Data(0x85);
    Lcd_Wr_Data(0x10);
    Lcd_Wr_Data(0x7A);
    Lcd_Wr_Reg(0xCB);
    Lcd_Wr_Data(0x39);
    Lcd_Wr_Data(0x2C);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0x34);
    Lcd_Wr_Data(0x02);
    Lcd_Wr_Reg(0xF7);
    Lcd_Wr_Data(0x20);
    Lcd_Wr_Reg(0xEA);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Reg(0xC0);    //Power control
    Lcd_Wr_Data(0x21);   //VRH[5:0]  //1B
    Lcd_Wr_Reg(0xC1);    //Power control
    Lcd_Wr_Data(0x12);   //SAP[2:0];BT[3:0] //01
    Lcd_Wr_Reg(0xC5);    //VCM control
    Lcd_Wr_Data(0x39); 	 //3F
    Lcd_Wr_Data(0x37); 	 //3C
    Lcd_Wr_Reg(0xC7);    //VCM control2
    Lcd_Wr_Data(0XAB);   //B0
    Lcd_Wr_Reg(0x36);    // Memory Access Control
    Lcd_Wr_Data(0x48);
    Lcd_Wr_Reg(0x3A);
    Lcd_Wr_Data(0x55);
    Lcd_Wr_Reg(0xB1);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0x1B);   //1A
    Lcd_Wr_Reg(0xB6);    // Display Function Control
    Lcd_Wr_Data(0x0A);
    Lcd_Wr_Data(0xA2);
    Lcd_Wr_Reg(0xF2);    // 3Gamma Function Disable
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Reg(0x26);    //Gamma curve selected
    Lcd_Wr_Data(0x01);

    Lcd_Wr_Reg(0xE0);    //Set Gamma
    Lcd_Wr_Data(0x0F);
    Lcd_Wr_Data(0x23);
    Lcd_Wr_Data(0x1F);
    Lcd_Wr_Data(0x0B);
    Lcd_Wr_Data(0x0E);
    Lcd_Wr_Data(0x08);
    Lcd_Wr_Data(0x4B);
    Lcd_Wr_Data(0XA8);
    Lcd_Wr_Data(0x3B);
    Lcd_Wr_Data(0x0A);
    Lcd_Wr_Data(0x14);
    Lcd_Wr_Data(0x06);
    Lcd_Wr_Data(0x10);
    Lcd_Wr_Data(0x09);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Reg(0XE1);    //Set Gamma
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0x1C);
    Lcd_Wr_Data(0x20);
    Lcd_Wr_Data(0x04);
    Lcd_Wr_Data(0x10);
    Lcd_Wr_Data(0x08);
    Lcd_Wr_Data(0x34);
    Lcd_Wr_Data(0x47);
    Lcd_Wr_Data(0x44);
    Lcd_Wr_Data(0x05);
    Lcd_Wr_Data(0x0B);
    Lcd_Wr_Data(0x09);
    Lcd_Wr_Data(0x2F);
    Lcd_Wr_Data(0x36);
    Lcd_Wr_Data(0x0F);
    Lcd_Wr_Reg(0x2B);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0x01);
    Lcd_Wr_Data(0x3f);
    Lcd_Wr_Reg(0x2A);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0x00);
    Lcd_Wr_Data(0xef);
    Lcd_Wr_Reg(0x11);    //Exit Sleep
    system_delay_ms(120);
    Lcd_Wr_Reg(0x29);    //display on

    LCD_direction(USE_HORIZONTAL);
    GPIO_OutputHi(GPIOA, LCD_BACK_LIGHT_EN);
    LCD_Clear(WHITE);    //white screen
}


void test_color(void)
{
    //DrawTestPage("");
    LCD_Fill(0,0,lcddev.width,lcddev.height,WHITE);
    Show_Str(20,30,BLUE,YELLOW,"BL Test",16,1);
    system_delay_ms(800);
    LCD_Fill(0,0,lcddev.width,lcddev.height,RED);
    Show_Str(20,30,BLUE,YELLOW,"RED ",16,1);
    system_delay_ms(800);
    LCD_Fill(0,0,lcddev.width,lcddev.height,GREEN);
    Show_Str(20,30,BLUE,YELLOW,"GREEN ",16,1);
    system_delay_ms(800);
    LCD_Fill(0,0,lcddev.width,lcddev.height,BLUE);
    Show_Str(20,30,RED,YELLOW,"BLUE ",16,1);
    system_delay_ms(800);
}


uint16_t ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};
void test_fillRec(void)
{
    uint8_t i=0;
    DrawTestPage("Rectangular filling test");
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for (i=0; i<5; i++)
    {
        POINT_COLOR=ColorTab[i];
        LCD_DrawRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60);
    }
    system_delay_ms(1500);
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for (i=0; i<5; i++)
    {
        POINT_COLOR=ColorTab[i];
        LCD_DrawFillRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60);
    }
    system_delay_ms(1500);
}

void test_circle(void)
{
    uint8_t i=0;
    DrawTestPage("Circle filling test");
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for (i=0; i<5; i++)
        gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,0);
    system_delay_ms(1500);
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for (i=0; i<5; i++)
        gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,1);
    system_delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Pic_test(void)
 * @date       :2018-08-09
 * @function   :picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void pic_test(void)
{
    LCD_Fill(0,0,lcddev.width,lcddev.height,BLACK);
    Gui_Drawbmp16(35,120,gImage_witin);
    Show_Str(120+12,200,BLUE,YELLOW,"witinmem",16,1);
    system_delay_ms(1200);
}


/*****************************************************************************
 * @name       :void Rotate_Test(void)
 * @date       :2018-08-09
 * @function   :rotate test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void rotate_test(void)
{
    uint8_t i=0;
    uint8_t *Direction[4]={"Rotation:0","Rotation:90","Rotation:180","Rotation:270"};

    for(i=0;i<4;i++)
    {
        LCD_direction(i);
        LCD_Fill(0,0,lcddev.width,lcddev.height,BLACK);
        Show_Str(20,30,BLUE,YELLOW,Direction[i],16,1);
        Gui_Drawbmp16(35,120,gImage_witin);
        system_delay_ms(1000);
    }
    LCD_direction(USE_HORIZONTAL);
}