/**
  ******************************************************************************
  * @file    main.h
  * @brief   Header for lcd_ILI9341.c module.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __LCD_ILI9341_H__
#define __LCD_ILI9341_H__
#include <stdint.h>
//LCD param
typedef struct  
{										    
    uint16_t width;			//LCD width
    uint16_t height;			//LCD height
    uint16_t id;				//LCD ID
    uint8_t  dir;			  //0:portrait 1:horizontal
    uint16_t wramcmd;		//write gram
    uint16_t  setxcmd;		//x
    uint16_t  setycmd;		//y 
}_lcd_dev; 	
extern _lcd_dev lcddev;	

//LCD size
#define LCD_W 240
#define LCD_H 320
#define LCD_RESET_PIN GPIO_PIN_10
#define LCD_COMMAND_DATA_CHANGE GPIO_PIN_11
#define LCD_BACK_LIGHT_EN GPIO_PIN_12

#define USE_HORIZONTAL  	 0

//color
#define WHITE       0xFFFF
#define BLACK       0x0000	  
#define BLUE        0x001F  
#define BRED        0XF81F
#define GRED        0XFFE0
#define GBLUE       0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN       0XBC40
#define BRRED       0XFC07
#define GRAY        0X8430

void lcd_init(void);
void Lcd_WriteData_16Bit(uint16_t data);
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void test_circle(void);
void test_fillRec(void);
void test_color(void);
void pic_test(void);
void rotate_test(void);
void LCD_DrawPoint(uint16_t x,uint16_t y);
#endif