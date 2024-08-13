#include <stdio.h>
#include <stdlib.h>
#include "fbank_config.h"
#include "rcc.h"

volatile uint8_t fft_interrupt_flag = 0; 
void FFT_IRQHandler(void)
{
    FBANK_Clear_Interrupt_Cmd(FBANK,FBANK_INT);
    fft_interrupt_flag = 1;
}

void FBANK_Write_Sram_Data_CP(FBANK_TypeDef *fbank,uint32_t *data,int len)
{
        int i=0;
        assert_param(fbank != NULL);
        assert_param(IS_FBANK_ALL_INSTANCE(fbank));
        //memcpy( fbank->SRAM,data,len<<2);
        //return;

        uint32_t *pSrc=data;
        volatile uint32_t *pDst=fbank->SRAM;

        uint32_t tmp_tab[8];

        for(i=0;i<len;i+=8)
        {
            tmp_tab[0]=*pSrc++;
            tmp_tab[1]=*pSrc++;
            tmp_tab[2]=*pSrc++;
            tmp_tab[3]=*pSrc++;
            *pDst++=tmp_tab[0];
            *pDst++=tmp_tab[1];
            *pDst++=tmp_tab[2];
            *pDst++=tmp_tab[3];
            tmp_tab[4]=*pSrc++;
            tmp_tab[5]=*pSrc++;
            tmp_tab[6]=*pSrc++;
            tmp_tab[7]=*pSrc++;
            *pDst++=tmp_tab[4];
            *pDst++=tmp_tab[5];
            *pDst++=tmp_tab[6];
            *pDst++=tmp_tab[7];
        }
}

void FBANK_Read_Sram_Data_CP(FBANK_TypeDef *fbank,uint32_t *data,int len)
{
        int i = 0;
        assert_param(fbank != NULL);
	assert_param(IS_FBANK_ALL_INSTANCE(fbank));
        //memcpy(data,fbank->SRAM,len<<2);
        
        volatile uint32_t *pSrc=fbank->SRAM;
        uint32_t *pDst=data;

        uint32_t tmp_tab[8];       

        for(i=0;i<len;i+=8)
        {
            tmp_tab[0]=*pSrc++;
            tmp_tab[1]=*pSrc++;
            tmp_tab[2]=*pSrc++;
            tmp_tab[3]=*pSrc++;
            *pDst++=tmp_tab[0];
            *pDst++=tmp_tab[1];
            *pDst++=tmp_tab[2];
            *pDst++=tmp_tab[3];
            tmp_tab[4]=*pSrc++;
            tmp_tab[5]=*pSrc++;
            tmp_tab[6]=*pSrc++;
            tmp_tab[7]=*pSrc++;
            *pDst++=tmp_tab[4];
            *pDst++=tmp_tab[5];
            *pDst++=tmp_tab[6];
            *pDst++=tmp_tab[7];
        }
}

void FBANK_Read_Sram_Data_CP2(FBANK_TypeDef *fbank,uint32_t *data,int len)
{
        int i = 0;
        assert_param(fbank != NULL);
	assert_param(IS_FBANK_ALL_INSTANCE(fbank));
        //memcpy(data,fbank->SRAM,len<<2);
        
        volatile uint32_t *pSrc=fbank->SRAM;
        uint32_t *pDst=data;

        uint32_t tmp_tab[8];       

        for(i=0;i<len;i+=8)
        {
            tmp_tab[0]=*pSrc++;
            tmp_tab[1]=*pSrc++;
            tmp_tab[2]=*pSrc++;
            tmp_tab[3]=*pSrc++;
            *pDst++=tmp_tab[0];           
            *pDst++=tmp_tab[2];            
            tmp_tab[4]=*pSrc++;
            tmp_tab[5]=*pSrc++;
            tmp_tab[6]=*pSrc++;
            tmp_tab[7]=*pSrc++;
            *pDst++=tmp_tab[4];           
            *pDst++=tmp_tab[6];
           
        }
}

void fft_calculate(uint32_t *data_write,uint32_t *data_read)
{
    //uint64_t ahbclock = 0;
    //uint64_t t0 = 0;
    //uint64_t t1 = 0;
    //uint64_t t2 = 0;
    //uint64_t t3 = 0;
    //ahbclock = RCC_Get_SYSClk() / (RCC_AHB_Get_ClkDiv() + 1);


    //t0 = __get_rv_cycle();

    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);
    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, DO_RFFT_HCLK | DO_CFFT_HCLK | FFT_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, ENABLE);
    //FBANK_Write_Sram_Data(FBANK, data_write, 512);
    uint32_t* pSrc;
    uint32_t* pDst;
    pSrc = (uint32_t*)data_write;
    pDst = (uint32_t*)FBANK->SRAM;
    for (int i = 0;i < 512;i+=8) {
        int32_t tmp0 = pSrc[0];
        int32_t tmp1 = pSrc[1];
        int32_t tmp2 = pSrc[2];
        int32_t tmp3 = pSrc[3];
        int32_t tmp4 = pSrc[4];
        int32_t tmp5 = pSrc[5];
        int32_t tmp6 = pSrc[6];
        int32_t tmp7 = pSrc[7];
        pDst[0] = tmp0;
        pDst[1] = tmp1;
        pDst[2] = tmp2;
        pDst[3] = tmp3;
        pDst[4] = tmp4;
        pDst[5] = tmp5;
        pDst[6] = tmp6;
        pDst[7] = tmp7;
        pSrc += 8;
        pDst += 8;
    }

    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);

    //t1 = __get_rv_cycle();

    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;

    //t2 = __get_rv_cycle();

    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);
    //FBANK_Read_Sram_Data(FBANK, data_read, 512);  
    pSrc = (uint32_t*)FBANK->SRAM;
    pDst = (uint32_t*)data_read;
    for (int i = 0;i < 512;i+=8) {
        int32_t tmp0 = pSrc[0];
        int32_t tmp1 = pSrc[1];
        int32_t tmp2 = pSrc[2];
        int32_t tmp3 = pSrc[3];
        int32_t tmp4 = pSrc[4];
        int32_t tmp5 = pSrc[5];
        int32_t tmp6 = pSrc[6];
        int32_t tmp7 = pSrc[7];
        pDst[0] = tmp0;
        pDst[1] = tmp1;
        pDst[2] = tmp2;
        pDst[3] = tmp3;
        pDst[4] = tmp4;
        pDst[5] = tmp5;
        pDst[6] = tmp6;
        pDst[7] = tmp7;
        pSrc += 8;
        pDst += 8;
    }

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);

    //t3 = __get_rv_cycle();

    //printf(" %-10s: %8d us\r\n", "> rfft.1", (t1 - t0) * 1000 * 1000 / ahbclock);
    //printf(" %-10s: %8d us\r\n", "> rfft.2", (t2 - t1) * 1000 * 1000 / ahbclock);
    //printf(" %-10s: %8d us\r\n", "> rfft.3", (t3 - t2) * 1000 * 1000 / ahbclock);
}

void fft_calculate_part1(uint32_t* data_write)
{
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);
    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, DO_RFFT_HCLK | DO_CFFT_HCLK | FFT_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, ENABLE);

    uint32_t* pSrc;
    uint32_t* pDst;
    pSrc = (uint32_t*)data_write;
    pDst = (uint32_t*)FBANK->SRAM;
    for (int i = 0;i < 512;i+=8) {
        int32_t tmp0 = pSrc[0];
        int32_t tmp1 = pSrc[1];
        int32_t tmp2 = pSrc[2];
        int32_t tmp3 = pSrc[3];
        int32_t tmp4 = pSrc[4];
        int32_t tmp5 = pSrc[5];
        int32_t tmp6 = pSrc[6];
        int32_t tmp7 = pSrc[7];
        pDst[0] = tmp0;
        pDst[1] = tmp1;
        pDst[2] = tmp2;
        pDst[3] = tmp3;
        pDst[4] = tmp4;
        pDst[5] = tmp5;
        pDst[6] = tmp6;
        pDst[7] = tmp7;
        pSrc += 8;
        pDst += 8;
    }

    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);
}


void fft_calculate_part2(uint32_t* data_read)
{
    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;

    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);

    uint32_t* pSrc;
    uint32_t* pDst;
    pSrc = (uint32_t*)FBANK->SRAM;
    pDst = (uint32_t*)data_read;
    for (int i = 0;i < 512;i+=8) {
        int32_t tmp0 = pSrc[0];
        int32_t tmp1 = pSrc[1];
        int32_t tmp2 = pSrc[2];
        int32_t tmp3 = pSrc[3];
        int32_t tmp4 = pSrc[4];
        int32_t tmp5 = pSrc[5];
        int32_t tmp6 = pSrc[6];
        int32_t tmp7 = pSrc[7];
        pDst[0] = tmp0;
        pDst[1] = tmp1;
        pDst[2] = tmp2;
        pDst[3] = tmp3;
        pDst[4] = tmp4;
        pDst[5] = tmp5;
        pDst[6] = tmp6;
        pDst[7] = tmp7;
        pSrc += 8;
        pDst += 8;
    }

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);
}



void ifft_calculate(uint32_t *data_write,uint32_t *data_read)
{
    //uint64_t ahbclock = 0;
    //uint64_t t0 = 0;
    //uint64_t t1 = 0;
    //uint64_t t2 = 0;
    //uint64_t t3 = 0;
    //ahbclock = RCC_Get_SYSClk() / (RCC_AHB_Get_ClkDiv() + 1);

    //t0 = __get_rv_cycle();

    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, DO_CFFT_HCLK | DO_BITREVERSE | IFFT_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);
    //FBANK_Write_Sram_Data(FBANK, data_write, 512);
    uint32_t* pSrc;
    uint32_t* pDst;
    pSrc = (uint32_t*)data_write;
    pDst = (uint32_t*)FBANK->SRAM;
    for (int i = 0;i < 512;i+=8) {
        int32_t tmp0 = pSrc[0];
        int32_t tmp1 = pSrc[1];
        int32_t tmp2 = pSrc[2];
        int32_t tmp3 = pSrc[3];
        int32_t tmp4 = pSrc[4];
        int32_t tmp5 = pSrc[5];
        int32_t tmp6 = pSrc[6];
        int32_t tmp7 = pSrc[7];
        pDst[0] = tmp0;
        pDst[1] = tmp1;
        pDst[2] = tmp2;
        pDst[3] = tmp3;
        pDst[4] = tmp4;
        pDst[5] = tmp5;
        pDst[6] = tmp6;
        pDst[7] = tmp7;
        pSrc += 8;
        pDst += 8;
    }

    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);

    //t1 = __get_rv_cycle();

    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;

    //t2 = __get_rv_cycle();
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    //FBANK_Read_Sram_Data(FBANK, data_read, 512);  
    pSrc = (uint32_t*)FBANK->SRAM;
    pDst = (uint32_t*)data_read;
    for (int i = 0;i < 512;i+=8) {
        int32_t tmp0 = pSrc[0];
        int32_t tmp1 = pSrc[1];
        int32_t tmp2 = pSrc[2];
        int32_t tmp3 = pSrc[3];
        int32_t tmp4 = pSrc[4];
        int32_t tmp5 = pSrc[5];
        int32_t tmp6 = pSrc[6];
        int32_t tmp7 = pSrc[7];
        pDst[0] = tmp0;
        pDst[1] = tmp1;
        pDst[2] = tmp2;
        pDst[3] = tmp3;
        pDst[4] = tmp4;
        pDst[5] = tmp5;
        pDst[6] = tmp6;
        pDst[7] = tmp7;
        pSrc += 8;
        pDst += 8;
    }

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);

    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);

    //t3 = __get_rv_cycle();

    //printf(" %-10s: %8d us\r\n", "> rifft.1", (t1 - t0) * 1000 * 1000 / ahbclock);
    //printf(" %-10s: %8d us\r\n", "> rifft.2", (t2 - t1) * 1000 * 1000 / ahbclock);
    //printf(" %-10s: %8d us\r\n", "> rifft.3", (t3 - t2) * 1000 * 1000 / ahbclock);
}

void ifft_calculate_part1(uint32_t* data_write)
{
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, DO_CFFT_HCLK | DO_BITREVERSE | IFFT_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);

    uint32_t* pSrc;
    uint32_t* pDst;
    pSrc = (uint32_t*)data_write;
    pDst = (uint32_t*)FBANK->SRAM;
    for (int i = 0;i < 512;i+=8) {
        int32_t tmp0 = pSrc[0];
        int32_t tmp1 = pSrc[1];
        int32_t tmp2 = pSrc[2];
        int32_t tmp3 = pSrc[3];
        int32_t tmp4 = pSrc[4];
        int32_t tmp5 = pSrc[5];
        int32_t tmp6 = pSrc[6];
        int32_t tmp7 = pSrc[7];
        pDst[0] = tmp0;
        pDst[1] = tmp1;
        pDst[2] = tmp2;
        pDst[3] = tmp3;
        pDst[4] = tmp4;
        pDst[5] = tmp5;
        pDst[6] = tmp6;
        pDst[7] = tmp7;
        pSrc += 8;
        pDst += 8;
    }

    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);
}

void ifft_calculate_part2(uint32_t* data_read)
{
    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    uint32_t* pSrc;
    uint32_t* pDst;
    pSrc = (uint32_t*)FBANK->SRAM;
    pDst = (uint32_t*)data_read;
    for (int i = 0;i < 512;i+=8) {
        int32_t tmp0 = pSrc[0];
        int32_t tmp1 = pSrc[1];
        int32_t tmp2 = pSrc[2];
        int32_t tmp3 = pSrc[3];
        int32_t tmp4 = pSrc[4];
        int32_t tmp5 = pSrc[5];
        int32_t tmp6 = pSrc[6];
        int32_t tmp7 = pSrc[7];
        pDst[0] = tmp0;
        pDst[1] = tmp1;
        pDst[2] = tmp2;
        pDst[3] = tmp3;
        pDst[4] = tmp4;
        pDst[5] = tmp5;
        pDst[6] = tmp6;
        pDst[7] = tmp7;
        pSrc += 8;
        pDst += 8;
    }

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);

    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);
}


void fbank_calculate(uint32_t *data_write,uint32_t *data_read)
{
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);
    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, DO_CFFT_HCLK | DO_RFFT_HCLK | DO_WINDOW | DO_BITREVERSE | LOG_ENABLE | SQRT_ENABLE | MELFILTER_ENABLE | FFT_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);
    FBANK_Write_Sram_Data(FBANK, data_write, 512);
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);
    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Read_Sram_Data(FBANK, data_read, 10);  

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);
}

void fbank_calculate_0516(uint32_t *data_write,uint32_t *data_read)
{
   

    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);
    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);

   
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, DO_CFFT_HCLK | DO_RFFT_HCLK | DO_WINDOW | DO_BITREVERSE  | SQRT_ENABLE | MELFILTER_ENABLE | FFT_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);
    FBANK_Write_Sram_Data_CP(FBANK, data_write, 512);

    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);
    PMU_Standby_Mode_Cmd(PMU);

    __WFI();
    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;
        
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Read_Sram_Data_CP(FBANK, data_read, 80);

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);
}

void fbank_calculate_win_fft(uint32_t *data_write,uint32_t *data_read)
{
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);
    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, DO_CFFT_HCLK | DO_RFFT_HCLK | DO_WINDOW | DO_BITREVERSE | FFT_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);
    FBANK_Write_Sram_Data_CP(FBANK, data_write, 512);

    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);
    PMU_Standby_Mode_Cmd(PMU);

    __WFI();
    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Read_Sram_Data_CP(FBANK, data_read, 512);     

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);
}


void fbank_calculate_sqrt_mel_log(uint32_t *data_write,uint32_t *data_read)
{
	RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);
    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, LOG_ENABLE | SQRT_ENABLE | MELFILTER_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);
    FBANK_Write_Sram_Data_CP(FBANK, data_write, 512);
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);
    PMU_Standby_Mode_Cmd(PMU);
    __WFI();
    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Read_Sram_Data(FBANK, data_read, 10);

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);
}

void fbank_calculate_sqrt_mel(uint32_t *data_write,uint32_t *data_read)
{
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, ENABLE);
    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_SetPriorityIRQ(FBANK_IRQn, 1);
    ECLIC_SetTrigIRQ(FBANK_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(FBANK_IRQn);

    FBANK_Set_Interrupt_Cmd(FBANK,FBANK_INT,ENABLE);
    
    FBANK_Ctl_Cmd(FBANK, 0xffff, DISABLE);
    FBANK_Ctl_Cmd(FBANK, SQRT_ENABLE | MELFILTER_ENABLE, ENABLE);
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Ctl_Cmd(FBANK, SRAM_ADDR_SEL, DISABLE);
    FBANK_Write_Sram_Data_CP(FBANK, data_write, 512);
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, DISABLE);
    FBANK_Enable_Cmd(FBANK, ENABLE);
    PMU_Standby_Mode_Cmd(PMU);

    __WFI();
    while(!fft_interrupt_flag);
    fft_interrupt_flag = 0;
    
    FBANK_Ctl_Cmd(FBANK, DATA_SRAM_SEL, ENABLE);
    FBANK_Read_Sram_Data_CP2(FBANK, data_read, 80);

    ECLIC_ClearPendingIRQ(FBANK_IRQn);  
    ECLIC_DisableIRQ(FBANK_IRQn);
    RCC_CLK_EN_Ctl(RCC_FFT_CLKEN, DISABLE);
}
