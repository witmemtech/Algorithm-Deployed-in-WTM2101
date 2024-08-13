#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

#include <basic_config.h>
#include <wtm2101_config.h>
#include <WTM2101.h>
#include <wtm2101_hal.h>

#include "gpio.h"
#include "pmu.h"
#include "rcc.h"
#include "main.h"
#include "wtm2101_mmap.h"
//#include "iis_tx_config.h"
//#include "iis_rx_config.h"

//#include "memory_placement.h"
#include "ucontext.h"
#include "rsm_driver.h"

#if 0
void GPIO_IRQHandler(void)
{
    GPIO_IT_ClrPending(GPIOA, GPIO_PIN_11);
    GPIO_IT_ClrWakeUpPending(GPIOA, GPIO_PIN_11);
}

void gpio_wake_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_IT_InitTypeDef GPIO_IT_InitStructure;

    RCC_CLK_EN_Ctl(RCC_GPIO_HCLKEN, ENABLE);

    ////////////////////////////////////////////////////////
    //
    //  GPIO0 as sleep key (low sleep)
    //
    GPIO_InitStructure.Pin      = GPIO_PIN_0;
    GPIO_InitStructure.Mode     = GPIO_MODE_INPU;
    GPIO_InitStructure.Alternate= GPIO_AF0_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);



    ////////////////////////////////////////////////////////
    //
    //  GPIO11 as wakeup key (low wakeup)
    //
    GPIO_InitStructure.Pin      = GPIO_PIN_11;
    GPIO_InitStructure.Mode     = GPIO_MODE_INPU;
    GPIO_InitStructure.Alternate= GPIO_AF1_GPIO;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ECLIC_ClearPendingIRQ(GPIO_IRQn);
    ECLIC_SetPriorityIRQ(GPIO_IRQn, 1);
    ECLIC_SetTrigIRQ(GPIO_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(GPIO_IRQn);

    GPIO_IT_InitStructure.Pin   = GPIO_PIN_11;
    GPIO_IT_InitStructure.Trig  = GPIO_IT_TRIG_FALLING;
    GPIO_IT_InitStructure.State = ENABLE;
    GPIO_IT_Cfg(GPIOA, &GPIO_IT_InitStructure);

    GPIO_IT_MskCfg(DISABLE);
    GPIO_IT_PinMskCfg(GPIOA, GPIO_PIN_11, DISABLE);
    PMU_Set_Ie_Msk(PMU, PMU_GPIO_IMSK | PMU_GPIO_EMSK, ENABLE);
}

void wfi_wait_GPIO(void)
{
    // config PMU
    PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_ALL, DISABLE);
    PMU_Set_Rsm_Mode_Parameter(PMU, PMU_RSM_MODE_KEEP_VDD, ENABLE);

    uint8_t temp = PMU->PMU_RESV_ADC_REG1;
    PMU->PMU_RESV_ADC_REG1 = 0x15;

    PMU_Rsm_Mode_Cmd(PMU);
    __WFI();
    PMU->PMU_RESV_ADC_REG1 = temp;
}
#endif


