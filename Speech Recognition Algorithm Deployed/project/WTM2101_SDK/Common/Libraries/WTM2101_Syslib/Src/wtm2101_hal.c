/**
* @file    wtm2101_hal.c
* @brief   The Source Codes for the wtm2101_hal Functions
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/
#include "wtm2101_hal.h"

void system_delay_s(uint32_t time)
{
    unsigned long long ahbclock = RCC_Get_SYSClk()/(RCC_AHB_Get_ClkDiv()+1);
    unsigned long long temp = 0;
    temp = __get_rv_cycle();
    do{
    }while((temp + time * ahbclock) > __get_rv_cycle());
}

void system_delay_ms(uint32_t time)
{
    unsigned long long ahbclock = RCC_Get_SYSClk()/(RCC_AHB_Get_ClkDiv()+1);
    unsigned long long temp = 0;
    temp = __get_rv_cycle();
    do{
    }while((temp + time * ahbclock/1000) > __get_rv_cycle());
}

void system_delay_us(uint32_t time)
{
    unsigned long long ahbclock = RCC_Get_SYSClk()/(RCC_AHB_Get_ClkDiv()+1);
    unsigned long long temp = 0;
    temp = __get_rv_cycle();
    do{
    }while((temp + time * ahbclock/1000000) > __get_rv_cycle());
}

void system_delay_tick(uint32_t time)
{
    unsigned long long temp = 0;
    temp = __get_rv_cycle();
    do{
    }while((temp + time ) > __get_rv_cycle());
}

void system_config_dump(void) 
{
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    if(hal_clock_instance->_24mosc_configuration.use_24mosc_way == HAL_CLOCK_24MOSC_EXTERNAL)
        printf("Info: osc24M is from external\r\n");
    else
        printf("Info: osc24M is from internal\r\n");

    if(hal_clock_instance->_24mosc_configuration.internal_24mosc_calibration_flag)
        printf("Info: osc24M is calibrated\r\n");
    else
        printf("Info: osc24M is not calibrated\r\n");
    if(hal_clock_instance->_24mosc_configuration.calibration_way == HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER)
        printf("Info: osc24M clock is:%d\r\n", hal_clock_instance->_24mosc_configuration.clock_hz);
    else
        printf("Info: osc24M clock can not be calculated,default current clock:%d\r\n", hal_clock_instance->_24mosc_configuration.clock_hz);
    printf("Info: clock source is ");
    switch (RCC->CLK_SEL & RCC_SYSCLK_MASK) {
    case RCC_SYSCLK_Int24M:
        printf("OSC24M\r\n");
        break;
    case RCC_SYSCLK_Int160K:
        printf("OSC2M\r\n");
        break;
    case RCC_SYSCLK_Int10K:
        printf("OSC10K\r\n");
        break;
    case RCC_SYSCLK_Ext32K:
        printf("XOSC32K\r\n");
        break;
    case RCC_SYSCLK_IntPLL:
        printf("PLL\r\n");
        break;
    case RCC_SYSCLK_AUDIO:
        printf("PLL\r\n");
        break;
    default:
        printf("Unknown\r\n");
        break;
    }
  
    if(hal_clock_instance->system_clock_select_source & HAL_CLOCK_PLL)
        printf("Info: pll_upfrequency_coefficient = %d\r\n", hal_clock_instance->pllclock_upfrequency_coefficient);
    printf("Info: ahb_div = %d\r\n", hal_clock_instance->ahbbus_downfrequency_coefficient);
    printf("Info: apb_div = %d\r\n", hal_clock_instance->apbbus_downfrequency_coefficient);

    printf("Info: SysClock = %dHz\r\n", hal_clock_instance->system_clock_frequency);
    printf("Info: AHBClock = %dHz\r\n", hal_clock_instance->system_clock_frequency / hal_clock_instance->ahbbus_downfrequency_coefficient);
    printf("Info: APBClock = %dHz\r\n", hal_clock_instance->system_clock_frequency / hal_clock_instance->ahbbus_downfrequency_coefficient / hal_clock_instance->apbbus_downfrequency_coefficient);
    printf("\r\n");
}

