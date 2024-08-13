/**
  ******************************************************************************
  * @file    GUI.c 
  * @brief   This file provide func to draw picture 
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "lcd_ILI9341.h"
#include "font.h"
#include "gui.h"
#include "string.h"
uint16_t POINT_COLOR = 0x0000;
uint16_t BACK_COLOR = 0xFFFF;
uint16_t DeviceCode;

/*******************************************************************
 * @name       :void GUI_DrawPoint(u16 x,u16 y,u16 color)
 * @date       :2018-08-09
 * @function   :draw a point in LCD screen
 * @parameters :x:the x coordinate of the point
                y:the y coordinate of the point
								color:the color value of the point
 * @retvalue   :None
********************************************************************/
static void GUI_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_SetCursor(x,y);//���ù��λ��
	Lcd_WriteData_16Bit(color);
}

/*******************************************************************
 * @name       :void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
 * @date       :2018-08-09
 * @function   :fill the specified area
 * @parameters :sx:the bebinning x coordinate of the specified area
                sy:the bebinning y coordinate of the specified area
								ex:the ending x coordinate of the specified area
								ey:the ending y coordinate of the specified area
								color:the filled color value
 * @retvalue   :None
********************************************************************/
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{
	uint16_t i,j;
	uint16_t width=ex-sx+1;
	uint16_t height=ey-sy+1;
	LCD_SetWindows(sx,sy,ex,ey);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		Lcd_WriteData_16Bit(color);
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}

/*****************************************************************************
 * @name       :void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
 * @date       :2018-08-09
 * @function   :Display a single English character
 * @parameters :x:the bebinning x coordinate of the Character display position
                y:the bebinning y coordinate of the Character display position
								fc:the color value of display character
								bc:the background color of display character
								num:the ascii code of display character(0~94)
								size:the size of display character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode)
{
    uint8_t temp;
    uint8_t pos,t;
    uint16_t colortemp=POINT_COLOR;

    num=num-' ';//get offset
    LCD_SetWindows(x,y,x+size/2-1,y+size-1);
    if(!mode)
    {
        for(pos=0;pos<size;pos++)
        {
            if(size==12)
                temp=asc2_1206[num][pos];
            else temp=asc2_1608[num][pos];
                for(t=0;t<size/2;t++)
                {
                    if(temp&0x01)
                        Lcd_WriteData_16Bit(fc);
                    else
                        Lcd_WriteData_16Bit(bc);
                    temp>>=1;
                }
        }
    }else{
        for(pos=0;pos<size;pos++)
        {
            if(size==12)
                temp=asc2_1206[num][pos];
            else
                temp=asc2_1608[num][pos];
            for(t=0;t<size/2;t++)
            {
                POINT_COLOR=fc;
                if(temp&0x01)
                    LCD_DrawPoint(x+t,y+pos);
                temp>>=1;
            }
         }
    }
    POINT_COLOR=colortemp;
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}

/*****************************************************************************
 * @name       :void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
 * @date       :2018-08-09
 * @function   :Display Chinese and English strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
                y:the bebinning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
{
    uint16_t x0=x;
    uint8_t bHz=0;
    while(*str!=0)
    {
        if(!bHz)
        {
            if(x>(lcddev.width-size/2)||y>(lcddev.height-size))
                return;
            if(*str>0x80)
                bHz=1;//chinese
	    else{//string
                if(*str==0x0D)//line break
                {
                    y+=size;
                    x=x0;
                    str++;
                }else{
                    if(size>16)//word stock do not have 12X24 16X32 use 8X16
                    {
                        LCD_ShowChar(x,y,fc,bc,*str,16,mode);
                        x+=8; //char half of world
                    }else{
                        LCD_ShowChar(x,y,fc,bc,*str,size,mode);
                        x+=size/2;
                    }
                }
                str++;
            }
        }
    }
}

/*****************************************************************************
 * @name       :void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
 * @date       :2018-08-09
 * @function   :Centered display of English and Chinese strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
                y:the bebinning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/
void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
{
    uint16_t len=strlen((const char *)str);
    uint16_t x1=(lcddev.width-len*8)/2;
    Show_Str(x1,y,fc,bc,str,size,mode);
}

/*******************************************************************
 * @name       :void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09
 * @function   :Draw a line between two points
 * @parameters :x1:the bebinning x coordinate of the line
                y1:the bebinning y coordinate of the line
		x2:the ending x coordinate of the line
	        y2:the ending y coordinate of the line
 * @retvalue   :None
********************************************************************/
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;

    delta_x=x2-x1;
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)
        incx=1;
    else if(delta_x==0)
        incx=0;
    else {
        incx=-1;
        delta_x=-delta_x;
    }
    if(delta_y>0)
        incy=1;
    else if(delta_y==0)
        incy=0;
    else{
        incy=-1;
        delta_y=-delta_y;
    }
    if( delta_x>delta_y)
        distance=delta_x;
    else
        distance=delta_y;
    for(t=0;t<=distance+1;t++ )
    {
        LCD_DrawPoint(uRow,uCol);
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}


/*****************************************************************************
 * @name       :void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09
 * @function   :Draw a rectangle
 * @parameters :x1:the bebinning x coordinate of the rectangle
                y1:the bebinning y coordinate of the rectangle
								x2:the ending x coordinate of the rectangle
								y2:the ending y coordinate of the rectangle
 * @retvalue   :None
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_DrawLine(x1,y1,x2,y1);
    LCD_DrawLine(x1,y1,x1,y2);
    LCD_DrawLine(x1,y2,x2,y2);
    LCD_DrawLine(x2,y1,x2,y2);
}


/*****************************************************************************
 * @name       :void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09
 * @function   :Filled a rectangle
 * @parameters :x1:the bebinning x coordinate of the filled rectangle
                y1:the bebinning y coordinate of the filled rectangle
		x2:the ending x coordinate of the filled rectangle
	        y2:the ending y coordinate of the filled rectangle
 * @retvalue   :None
******************************************************************************/
void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_Fill(x1,y1,x2,y2,POINT_COLOR);
}

/*****************************************************************************
 * @name       :void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
 * @date       :2018-08-09
 * @function   :8 symmetry circle drawing algorithm (internal call)
 * @parameters :xc:the x coordinate of the Circular center
                yc:the y coordinate of the Circular center
								x:the x coordinate relative to the Circular center
								y:the y coordinate relative to the Circular center
								c:the color value of the circle
 * @retvalue   :None
******************************************************************************/
void _draw_circle_8(int xc, int yc, int x, int y, uint16_t c)
{
    GUI_DrawPoint(xc + x, yc + y, c);

    GUI_DrawPoint(xc - x, yc + y, c);

    GUI_DrawPoint(xc + x, yc - y, c);

    GUI_DrawPoint(xc - x, yc - y, c);

    GUI_DrawPoint(xc + y, yc + x, c);

    GUI_DrawPoint(xc - y, yc + x, c);

    GUI_DrawPoint(xc + y, yc - x, c);

    GUI_DrawPoint(xc - y, yc - x, c);
}

/*****************************************************************************
 * @name       :void gui_circle(int xc, int yc,u16 c,int r, int fill)
 * @date       :2018-08-09
 * @function   :Draw a circle of specified size at a specified location
 * @parameters :xc:the x coordinate of the Circular center
                yc:the y coordinate of the Circular center
								r:Circular radius
								fill:1-filling,0-no filling
 * @retvalue   :None
******************************************************************************/
void gui_circle(int xc, int yc,uint16_t c,int r, int fill)
{
    int x = 0, y = r, yi, d;

    d = 3 - 2 * r;


    if (fill)
    {
        while (x <= y) {
            for (yi = x; yi <= y; yi++)
                _draw_circle_8(xc, yc, x, yi, c);

                if (d < 0) {
                    d = d + 4 * x + 6;
                } else {
                    d = d + 4 * (x - y) + 10;
                    y--;
                }
                x++;
        }
    } else {
        while (x <= y) {
            _draw_circle_8(xc, yc, x, y, c);
            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

/*****************************************************************************
 * @name       :void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p)
 * @date       :2018-08-09
 * @function   :Display a 16-bit BMP image
 * @parameters :x:the bebinning x coordinate of the BMP image
                y:the bebinning y coordinate of the BMP image
								p:the start address of image array
 * @retvalue   :None
******************************************************************************/
void Gui_Drawbmp16(uint16_t x,uint16_t y,const unsigned char *p)
{
    int i;
    unsigned char picH,picL;
    LCD_SetWindows(x,y,x+170-1,y+78-1);
    for(i=0;i<170*78;i++)
    {
        picL=*(p+i*2);
        picH=*(p+i*2+1);
        Lcd_WriteData_16Bit(picH<<8|picL);
    }
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}
