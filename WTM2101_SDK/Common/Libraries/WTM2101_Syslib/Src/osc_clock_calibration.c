#include "osc_clock_calibration.h"

static void udelay(uint32_t cnt)
{
    volatile uint32_t i;
    for (i = 0;i < cnt;i++) {
    }
}

#ifndef  OSC_DEBUG_PARA
#define  OSC_DEBUG_PARA  0
uint32_t m_24m_trim_coarse = 0, m_24m_trim_fine = 0,m_320k_trim_coarse = 0, m_320k_trim_fine = 0;
#endif

uint32_t osc_24m_calibration_start(void)
{
    uint32_t fre = 0;
    uint32_t _24m_div_number_old = 0,sysclk_old_old = 0;
    FunctionalState extern_clk_flag_old = 0,_32k_enable_flag_old = 0;

    _24m_div_number_old = PMU_Get_24M_Clock_Source_div(PMU);
    sysclk_old_old = RCC->CLK_SEL & RCC_CLK_SEL_SYSCLK_SEL_Msk;
    extern_clk_flag_old = GPIOA->PAD_RESV & 0x10;
    _32k_enable_flag_old = PMU->CTL & PMU_PMU_CTL_XTL32K_EN_Msk;

    /*init the related the clock and parameter*/
    PMU_Set_24M_Clock_Source_div(PMU,1);
    PMU_Select_24Mhz_Clock_Cmd(PMU,OSC_INTERNAL_24M);
    RCC_SYSClk_Sel(RCC_SYSCLK_Int24M);
    PMU_Enable_External_Clock(PMU,ENABLE);
    PMU_Set_Clock_Source_Cmd(PMU,XTL32K,ENABLE);

    /*enable the interrupt*/
    ECLIC_ClearPendingIRQ(AFC24MK_IRQn);
    ECLIC_SetPriorityIRQ(AFC24MK_IRQn, 1);
    ECLIC_SetTrigIRQ(AFC24MK_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(AFC24MK_IRQn);

    /*enable the calibration clock*/
    RCC_CLK_EN_Ctl(RCC_TRIM_CLKEN,ENABLE);
    RCC_Peri_Rst(RCC_TRIM_RSTN);

    /*trim reset*/
    PMU_Set_24M_Trim_Source(PMU,PMU_24M_TRIM_SOURCE_FROM_CPU);
    PMU->_24M_TRIM_FINE = 0x10;
    PMU->_24M_TRIM_COARSE = 0x8;
    PMU->TRIM_RST = 0x1;

    PMU_Set_24M_Trim_Source(PMU,PMU_24M_TRIM_SOURCE_FROM_MOUDLE);
    /*enable the osc24m interrupt*/
    AFC_Set_Interrupt_Clear(AFC24M,AFC_ALL_INTERRUPT & (~AFC_TRIM_ACK_INTERRUPT));
    AFC_Set_Interrupt_Mask(AFC24M,AFC_TRIM_ACK_INTERRUPT);

    /*set the calibration parameter*/
    //AFC_Set_Test_Time(AFC24M,0x20);
    //AFC_Set_Frequency_Target(AFC24M,0x5dc0);
    AFC24M->CORE_CTRL = 0x5dc020;

    /*start the calibration*/
    AFC_Set_Enable_Cmd(AFC24M,ENABLE);
    udelay(800 * 500);

    fre = AFC_Get_Frequency_Calibration_Cycle_Count(AFC24M);
    fre = fre * 1024;

    #if OSC_DEBUG_PARA
    m_24m_trim_coarse = (AFC24M->CORE_TRIM_SIGNAL & 0xf00) >> 8;
    m_24m_trim_fine = AFC24M->CORE_TRIM_SIGNAL & 0x1f;
    printf("fre:%d,m_24m_trim_coarse:%d,m_24m_trim_fine:%d\r\n",fre,m_24m_trim_coarse,m_24m_trim_fine);
    #endif

    /*close the osc24m register*/
    AFC_Set_Enable_Cmd(AFC24M,DISABLE);
    PMU_Set_24M_Trim_Source(PMU,PMU_24M_TRIM_SOURCE_FROM_OTHER);
    RCC_CLK_EN_Ctl(RCC_TRIM_CLKEN,DISABLE);
    ECLIC_DisableIRQ(AFC24MK_IRQn);

    /*uninit the related the clock and parameter*/
    PMU_Set_Clock_Source_Cmd(PMU,XTL32K,_32k_enable_flag_old);
    PMU_Enable_External_Clock(PMU,extern_clk_flag_old);
    PMU_Set_24M_Clock_Source_div(PMU,_24m_div_number_old);
    RCC_SYSClk_Sel(sysclk_old_old);

    return fre;
}

uint32_t osc_320k_calibration_start(void)
{
    uint32_t fre = 0;
    uint32_t sysclk_old_old = 0;
    FunctionalState extern_clk_flag_old = 0,_32k_enable_flag_old = 0,_320k_enable_flag_old = 0;

    sysclk_old_old = RCC->CLK_SEL & RCC_CLK_SEL_SYSCLK_SEL_Msk;
    extern_clk_flag_old = GPIOA->PAD_RESV & 0x10;
    _32k_enable_flag_old = PMU->CTL & PMU_PMU_CTL_XTL32K_EN_Msk;
    _320k_enable_flag_old = PMU->CTL & PMU_PMU_CTL_OSC320K_EN_Msk;

    /*init the related the clock and parameter*/
    PMU_Enable_External_Clock(PMU,ENABLE);
    PMU_Set_Clock_Source_Cmd(PMU,XTL32K | OSC_320K,ENABLE);
    RCC_SYSClk_Sel(RCC_SYSCLK_Int24M);

    /*enable the interrupt*/
    ECLIC_ClearPendingIRQ(AFC320K_IRQn);
    ECLIC_SetPriorityIRQ(AFC320K_IRQn, 1);
    ECLIC_SetTrigIRQ(AFC320K_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(AFC320K_IRQn);

    /*enable the 320k clock*/
    RCC_CLK_EN_Ctl(RCC_TRIM_CLKEN,ENABLE);
    RCC_Peri_Rst(RCC_TRIM_RSTN);

    /*trim reset*/
    PMU_Set_320K_Trim_Source(PMU,PMU_320K_TRIM_SOURCE_FROM_MOUDLE);
    PMU->_320K_TRIM = 0x84;
    PMU->TRIM_RST = 0x2;

    /*enable the osc320K interrupt*/
    AFC_Set_Interrupt_Clear(AFC320k,AFC_ALL_INTERRUPT & (~AFC_TRIM_ACK_INTERRUPT));
    AFC_Set_Interrupt_Mask(AFC320k,AFC_TRIM_ACK_INTERRUPT);

    /*set the calibration parameter*/
    //AFC_Set_Test_Time(AFC320k,0x20);
    //AFC_Set_Frequency_Target(AFC320k,0x13a);
    AFC320k->CORE_CTRL = (((AFC320k->CORE_CTRL)|0x13a20)&0x13a20);

    /*start the calibration*/
    AFC_Set_Enable_Cmd(AFC320k,ENABLE);
    udelay(500 * 1000);

    fre = AFC_Get_Frequency_Calibration_Cycle_Count(AFC320k);
    fre = fre * 1024;

    #if OSC_DEBUG_PARA
    m_320k_trim_coarse = (AFC320k->CORE_TRIM_SIGNAL & 0x70) >> 4;
    m_320k_trim_fine = (AFC320k->CORE_TRIM_SIGNAL & 0xf);
    printf("fre:%d,m_320k_trim_coarse:%d,m_320k_trim_fine:%d\r\n",fre,m_320k_trim_coarse,m_320k_trim_fine);
    #endif

    /*close the osc24m register*/
    AFC_Set_Enable_Cmd(AFC320k,DISABLE);
    RCC_CLK_EN_Ctl(RCC_TRIM_CLKEN,DISABLE);
    ECLIC_DisableIRQ(AFC320K_IRQn);

    /*uninit the related the clock and parameter*/
    PMU_Set_Clock_Source_Cmd(PMU,XTL32K,_32k_enable_flag_old);
    PMU_Enable_External_Clock(PMU,extern_clk_flag_old);
    PMU_Set_Clock_Source_Cmd(PMU,OSC_320K,_320k_enable_flag_old);
    RCC_SYSClk_Sel(sysclk_old_old);

    return fre;
}

void  AFC24M_IRQHandler(void)
{
    int m=0, ims=0, n=0, op_data=0, remin_value=0, int_value=0, divider=0, fine_trim=0, fre_target=0;

    m = AFC24M->INT_SR_PENDING;
        ims = AFC24M->INT_MASK_STATUS;

        if(0x800 == ((m & 0x800) & (~(ims & 0x800))))
    {
        AFC24M->INT_SR_PENDING=0x800;
                __ECLIC_ClearPendingIRQ(AFC24MK_IRQn);

    }

    if(0x400 == ((m & 0x400) & (~(ims & 0x400))))
    {
        AFC24M->INT_SR_PENDING=0x400;
        __ECLIC_ClearPendingIRQ(44);
    }

           if (0x200 == ((m & 0x200) & (~(ims & 0x200))))
    {
                AFC24M->INT_MASK_SET=0xdff;

          op_data =AFC24M->OP_DATA;

        int_value = (op_data & 0x7ff) / 0x13;
        remin_value = (op_data & 0x7ff) % 0x13;
        if(remin_value == 0x1)
        {
            n = 0x1;
        }
        else
        {
            n = 0x0;
        }
                AFC24M->INT_SR_PENDING=0x200;
        __ECLIC_ClearPendingIRQ(AFC24MK_IRQn);
                AFC24M->INT_MASK_CLR=0xdff;

        //printf(" Request cpu to do the first operation \n");
        m = AFC24M->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
                AFC24M->OP_RESULT=(n<<5)+int_value;
                AFC24M->AFC_PULSE=0X1;

    }

     if(0x100 == ((m & 0x100)& (~(ims & 0x100))))
     {
                AFC24M->INT_MASK_SET=0xeff;
        m = AFC24M->AFC_FRE_CNT;

        fine_trim =AFC24M->CORE_TRIM_SIGNAL;// READ(AFC_24M_REG_CORE_TRIM_SIGNAL);
        fre_target = AFC24M->CORE_CTRL;//READ(AFC_24M_REG_CORE_CTRL);
        if(((fine_trim&0x1f)==0x0) && ((m&0x7fff)>=((fre_target&0x7fff00)>>8)))
                {
            AFC24M->INT_SR_PENDING=0x100;
            __ECLIC_ClearPendingIRQ(44);
            //printf(" The current frequency is %x \n", m);
            //printf("12 \n");


        }
        else if(((fine_trim&0x1f)==0x1f) && ((m&0x7fff)<=((fre_target&0x7fff00)>>8)))
                {
                        AFC24M->INT_SR_PENDING=0x100;

            __ECLIC_ClearPendingIRQ(44);
            //printf(" The current frequency is %x \n", m);
            //printf("13\n");

        }
                else
                {
            op_data =AFC24M->OP_DATA;// READ(AFC_24M_REG_OP_DATA);
                if(((op_data>>31)&0x1)==1)
            {
                int_value = (((op_data>>16)&0x7ff) * (abs(0x10-(fine_trim&0x1f)))) / (((op_data>>16)&0x7ff) + (op_data&0x7ff));
                divider = (((op_data>>16)&0x7ff) + (op_data&0x7ff));
                remin_value = (((op_data>>16)&0x7ff) * (abs(0x10-(fine_trim&0x1f)))) % (((op_data>>16)&0x7ff) + (op_data&0x7ff));
                if(remin_value>=(divider>>1))
                {
                    n = 0x1;
                }
                else
                {
                    n = 0x0;
                }
            }
            else
            {
                int_value = (((op_data>>16)&0x7ff) * (abs(0x10-(fine_trim&0x1f)))) / (((op_data>>16)&0x1ff) - (op_data&0x7ff));
                divider = (((op_data>>16)&0x7ff) - (op_data&0x7ff));
                remin_value = (((op_data>>16)&0x7ff) * (abs(0x10-(fine_trim&0x1f)))) % (((op_data>>16)&0x7ff) - (op_data&0x7ff));
                if(remin_value>=(divider>>1))
                {
                    n = 0x1;
                }
                else
                {
                    n = 0x0;
                }
            }
                        AFC24M->INT_SR_PENDING=0x100;

            __ECLIC_ClearPendingIRQ(44);
                        AFC24M->INT_MASK_CLR=0xeff;

            //printf(" Request cpu to do the second operation \n");
                        m = AFC24M->AFC_FRE_CNT;

            //printf(" The current frequency is %x \n", m);
            if(int_value >=0x1e)
            {

                            AFC24M->OP_RESULT=(n<<5)+0x1e;



            }
            else
            {
                         AFC24M->OP_RESULT=(n<<5)+int_value;

            }
                        AFC24M->AFC_PULSE=0X1;

        }
    }

    if(0x80 == ((m & 0x80)& (~(ims & 0x80))))
    {
                AFC24M->INT_SR_PENDING=0x80;

         m = AFC24M->AFC_FRE_CNT;
        __ECLIC_ClearPendingIRQ(44);
        //printf(" The current frequency is %x \n", m);
        //printf(" Coarse tuning out of bounds \n");
    }

    if(0x40 == ((m & 0x40)& (~(ims & 0x40))))
    {
                AFC24M->INT_SR_PENDING=0x40;

        __ECLIC_ClearPendingIRQ(44);
        m =  AFC24M->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Coarse tuning increase upward to the limit \n");
    }

    if(0x20 == ((m & 0x20)& (~(ims & 0x20))))
    {
                AFC24M->INT_SR_PENDING=0x20;

        __ECLIC_ClearPendingIRQ(44);
        m =AFC24M->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Coarse tuning decrease upward to the limit \n");
    }

    if(0x10 == ((m & 0x10)& (~(ims & 0x10))))
    {
                AFC24M->INT_SR_PENDING=0x10;

        __ECLIC_ClearPendingIRQ(44);
        m =AFC24M->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Frequency reaches target \n");

    }

    if(0x8 == ((m & 0x8)& (~(ims & 0x8))))
    {
                AFC24M->INT_SR_PENDING=0x8;

        __ECLIC_ClearPendingIRQ(44);
        m =AFC24M->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" FINE TRIM ERROR \n");
    }

    if(0x4 == ((m & 0x4)& (~(ims & 0x4))))
    {
                AFC24M->INT_SR_PENDING=0x4;

        __ECLIC_ClearPendingIRQ(44);
        m = AFC24M->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" First round of 19k 1 \n");

    }

    if(0x2 == ((m & 0x2)& (~(ims & 0x2))))
    {
                AFC24M->INT_SR_PENDING=0x2;

        __ECLIC_ClearPendingIRQ(44);
        m = AFC24M->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Second round of 19k 2 \n");

    }

    if(0x1 == ((m & 0x1)& (~(ims & 0x1))))
    {
                AFC24M->INT_SR_PENDING=0x1;
        __ECLIC_ClearPendingIRQ(44);
        m = AFC24M->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf("3 \n");
    }

}

void  AFC320K_IRQHandler(void)
{
        //printf("afc 320k irq\n");
    int m=0, ims=0, n=0, op_data=0, remin_value=0, int_value=0, divider=0, fine_trim=0, fre_target=0;

    m = AFC320k->INT_SR_PENDING;
        ims = AFC320k->INT_MASK_STATUS;

        if(0x800 == ((m & 0x800)& (~(ims & 0x800))))
    {
        AFC320k->INT_SR_PENDING=0x800;
                __ECLIC_ClearPendingIRQ(AFC320K_IRQn);

    }

        else if(0x400 == ((m & 0x400)& (~(ims & 0x400))))
    {
        AFC320k->INT_SR_PENDING=0x400;
        __ECLIC_ClearPendingIRQ(40);
    }

    else if (0x200 == ((m & 0x200)& (~(ims & 0x200))))
    {
                AFC320k->INT_MASK_SET=0xdff;

          op_data =AFC320k->OP_DATA;

        int_value =(op_data & 0x1ff) / 0x2;
        remin_value = (op_data & 0x1ff) % 0x2;
        if(remin_value == 0x1)
        {
            n = 0x1;
        }
        else
        {
            n = 0x0;
        }
                AFC320k->INT_SR_PENDING=0x200;
        __ECLIC_ClearPendingIRQ(AFC320K_IRQn);
                AFC320k->INT_MASK_CLR=0xdff;

        //printf(" Request cpu to do the first operation \n");
        //m = AFC320k->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
                AFC320k->OP_RESULT=(n<<4)+int_value;
                AFC320k->AFC_PULSE=0X1;

    }

    else if(0x100 == ((m & 0x100)& (~(ims & 0x100))))
    {
                AFC320k->INT_MASK_SET=0xeff;
        m = AFC320k->AFC_FRE_CNT;

        fine_trim =AFC320k->CORE_TRIM_SIGNAL;// READ(AFC_24M_REG_CORE_TRIM_SIGNAL);
        fre_target = AFC320k->CORE_CTRL;//READ(AFC_24M_REG_CORE_CTRL);
        if(((fine_trim&0xf)==0x0) && ((m&0x1ff)>=((fre_target&0x1ff00)>>8)))
                {
            AFC320k->INT_SR_PENDING=0x100;
            __ECLIC_ClearPendingIRQ(40);
            //printf(" The current frequency is %x \n", m);
            //printf(" Second round of 2k \n");

        }
        else if(((fine_trim&0xf)==0xf) && ((m&0x1ff)<=((fre_target&0x1ff00)>>8)))
                {
                        AFC320k->INT_SR_PENDING=0x100;

            __ECLIC_ClearPendingIRQ(40);
            //printf(" The current frequency is %x \n", m);
            //printf(" Second round of 2k \n");

        }
                else
                {
            op_data =AFC320k->OP_DATA;// READ(AFC_24M_REG_OP_DATA);
                        if(((op_data>>24)&0x1)==1)
            {
                int_value = (((op_data>>12)&0x1ff) * (abs(0x8-(fine_trim&0xf)))) / (((op_data>>12)&0x1ff) + (op_data&0x1ff));
                divider = (((op_data>>12)&0x1ff) + (op_data&0x1ff));
                remin_value = (((op_data>>12)&0x1ff) * (abs(0x8-(fine_trim&0xf)))) % (((op_data>>12)&0x1ff) + (op_data&0x1ff));
                if(remin_value>=(divider>>1))
                {
                    n = 0x1;
                }
                else
                {
                    n = 0x0;
                }
            }
            else
            {
                int_value = (((op_data>>12)&0x1ff) * (abs(0x8-(fine_trim&0xf)))) / (((op_data>>12)&0x1ff) - (op_data&0x1ff));
                divider = (((op_data>>12)&0x1ff) - (op_data&0x1ff));
                remin_value = (((op_data>>12)&0x1ff) * (abs(0x8-(fine_trim&0xf)))) % (((op_data>>12)&0x1ff) - (op_data&0x1ff));
                if(remin_value>=(divider>>1))
                {
                    n = 0x1;
                }
                else
                {
                    n = 0x0;
                }
            }
                        AFC320k->INT_SR_PENDING=0x100;

            __ECLIC_ClearPendingIRQ(40);
                        AFC320k->INT_MASK_CLR=0xeff;

            //printf(" Request cpu to do the second operation \n");
                        m = AFC320k->AFC_FRE_CNT;

            //printf(" The current frequency is %x \n", m);
            if(int_value >=0xe)
            {

                              AFC320k->OP_RESULT=(n<<4)+0xe;



            }
            else
            {
                              AFC320k->OP_RESULT=(n<<4)+int_value;

            }
                        AFC320k->AFC_PULSE=0X1;

        }
    }

    else if(0x80 == ((m & 0x80)& (~(ims & 0x80))))
    {
                AFC320k->INT_SR_PENDING=0x80;

         m = AFC320k->AFC_FRE_CNT;
        __ECLIC_ClearPendingIRQ(40);
        //printf(" The current frequency is %x \n", m);
        //printf(" Coarse tuning out of bounds \n");
    }

    else if(0x40 == ((m & 0x40)& (~(ims & 0x40))))
    {
                AFC320k->INT_SR_PENDING=0x40;

        __ECLIC_ClearPendingIRQ(40);
        m =  AFC320k->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Coarse tuning increase upward to the limit \n");
    }

    else if(0x20 == ((m & 0x20)& (~(ims & 0x20))))
    {
                AFC320k->INT_SR_PENDING=0x20;

        __ECLIC_ClearPendingIRQ(40);
        m =AFC320k->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Coarse tuning decrease upward to the limit \n");
    }

    else if(0x10 == ((m & 0x10)& (~(ims & 0x10))))
    {
                AFC320k->INT_SR_PENDING=0x10;

        __ECLIC_ClearPendingIRQ(40);
        m =AFC320k->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Frequency reaches target \n");
               // printf(" afc_finish 1\n");

    }

    else if(0x8 == ((m & 0x8)& (~(ims & 0x8))))
    {
                AFC320k->INT_SR_PENDING=0x8;

        __ECLIC_ClearPendingIRQ(40);
        m =AFC320k->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" FINE TRIM ERROR \n");
    }

    else if(0x4 == ((m & 0x4)& (~(ims & 0x4))))
    {
                AFC320k->INT_SR_PENDING=0x4;

        __ECLIC_ClearPendingIRQ(40);
        m = AFC320k->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" First round of 19k \n");
    }

    else if(0x2 == ((m & 0x2)& (~(ims & 0x2))))
    {
                AFC320k->INT_SR_PENDING=0x2;

        __ECLIC_ClearPendingIRQ(40);
        m = AFC320k->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Second round of 19k \n");
    }

    else if(0x1 == ((m & 0x1)& (~(ims & 0x1))))
    {
                AFC320k->INT_SR_PENDING=0x1;

        __ECLIC_ClearPendingIRQ(40);
        m = AFC320k->AFC_FRE_CNT;
        //printf(" The current frequency is %x \n", m);
        //printf(" Third round of 19k \n");
               // printf(" afc_finish 2\n");

    }
}