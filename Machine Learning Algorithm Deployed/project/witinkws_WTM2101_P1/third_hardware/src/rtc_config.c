#include "rtc_config.h"

#include "gpio.h"
#include "rtc.h"

void RTC_IRQHandler(void)
{
    RTC_Clear_Int_Cmd(RTC);
}
void rtc_open()
{
    RCC_CLK_EN_Ctl(RCC_RTC_PCLKEN, ENABLE);

    /*Initial interrupt*/
    ECLIC_ClearPendingIRQ(RTC_IRQn);
    ECLIC_SetPriorityIRQ(RTC_IRQn, 1);
    ECLIC_SetTrigIRQ(RTC_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(RTC_IRQn);

    /*Initial the rtc time */
    PMU_Set_Rtc_Clock_Source(PMU, PMU_CLK_RTC_SWITCH_160KHZ);

    /*Initial loop-back mode*/
    RTC_Set_Wrap_Cmd(RTC, ENABLE);
    RTC_Set_Initial_Time_Value(RTC,0);
    RTC_Set_Compare_Time_Value(RTC,0);

    RTC_Set_Interrupt_Unmask_Cmd(RTC, ENABLE);
    RTC_Set_Interrupt_Cmd(RTC,ENABLE);

    PMU_Set_Ie_Msk(PMU, PMU_RTC_IMSK, ENABLE);
    PMU_Set_Ie_Msk(PMU, PMU_RTC_EMSK, ENABLE);
}
