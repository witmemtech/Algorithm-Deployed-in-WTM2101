/**
* @file    retarget.c
* @brief   The Source Codes for the retarget Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/
#include "retarget.h"

/*printf retarget*/
static uint32_t printf_retarget_type = PRINTF_RETARGET_NONE;

int __putchar(int ch, __printf_tag_ptr tag)
{
    switch(printf_retarget_type)
    {    
        case PRINTF_RETARGET_NONE:
            return 0;
              
        case PRINTF_RETARGET_UART0:
            while (UART_Flag_GetStatBit(UART0,UART_FLAG_TEMT) == RESET) {
            }
            UART_SendData(UART0, (uint8_t)ch);
            return ch;
       case PRINTF_RETARGET_UART1:
            while (UART_Flag_GetStatBit(UART1,UART_FLAG_TEMT) == RESET) {
            }
            UART_SendData(UART1, (uint8_t)ch);
            return ch;
       case PRINTF_RETARGET_SEGGER:
            (void)tag;
            SEGGER_RTT_Write(0, (char *)&ch, 1);
            return ch;
       default: 
            return -1;
    }
}

void printf_output_redirect_set(Retaget_Typedef type)
{ 
    if(type < PRINTF_RETARGET_NONE || type > PRINTF_RETARGET_SEGGER)
        return;

    printf_retarget_type = type;
}



