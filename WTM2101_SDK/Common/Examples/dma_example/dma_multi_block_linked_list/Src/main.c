/**
  ******************************************************************************
  * @file    main.c 
  * @brief   This example describes how to use the DMA to transfer 
  *          continuously converted data.
  * @date    2023-02-07
  * Copyright (c) 2023 Witmem Technology Co., Ltd
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "main.h"

#define DMA_TRANS_BLOCK_SIZE (100)
#define DMA_TEST_BUFFER_LEN (100)

volatile Bool dma_blk = FALSE;
volatile Bool dma_tfr = FALSE;

static int dma_test(void);
static void system_clock_init(void);
static void uart_init(void);

#pragma pack(push)
#pragma pack(1)
typedef struct {
    DMA_LlpTypeDef llp_struct;
    uint32_t      *origin_addr;
} LLP_Struct_Ex;
#pragma pack(pop)

void main(void)
{
    printf_output_redirect_set(PRINTF_RETARGET_NONE);

    /* Reset all peripherals except PMU */
    RCC_Peri_Rst(0xFFFFFFFF & (~RCC_PMU_PRSTN));

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();
  
    printf_output_redirect_set(PRINTF_RETARGET_SEGGER);
  
    /* Initial clock */
    system_clock_init();
  
    /* Initial periphral */
    uart_init();
    printf_output_redirect_set(PRINTF_RETARGET_UART0);

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    system_config_dump();

    /* Application entry */
    dma_test();

    while(1){};
}

static void system_clock_init(void)
{
    int ret = 0;
    /* The clock instance */   
    Hal_Clock_InitTypeDef * hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /* Construct 24mosc related configuration parameters */
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_INTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = ENABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /* Initialize the clock instance.the system clock is from internal 24mosc.the 24mosc is calibrated by the xtal 32k */
    ret = hal_clock_init(hal_clock_instance, HAL_CLOCK_24MOSC, HAL_CLOCK_24MOSC, &hal_clock_24mosc_Configuration, 0, 1, 1);
    if (ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /* According to the clock instance, initialize the hardware */
    ret = hal_clock_open(hal_clock_instance);
    if (ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}

static void uart_init(void)
{
    /*init uart*/
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN, ENABLE);
   
    /*the gpio4,gpio5*/
    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.Alternate = GPIO_AF4_UART0 | GPIO_AF5_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);
}

static int dma_data_compare(LLP_Struct_Ex *p)
{
    int test_result = 0;

    while (p){

        uint8_t *src_p =  (uint8_t *)p->llp_struct.src;
        uint8_t *dst_p =  (uint8_t *)p->llp_struct.dst;

        for(int i = 0; i < p->llp_struct.ctl_reg_high; i++) {
            if(src_p[i] != dst_p[i]) {
                test_result = 1;  
                break;
            }
        }
        p = (LLP_Struct_Ex *)p->llp_struct.llp;
    }

    if (test_result == 0) {
        printf("test succeed\r\n");
    } else {
        printf("test failed\r\n");
    }
    
    return test_result;
}

LLP_Struct_Ex* get_tail(LLP_Struct_Ex *p) {
    LLP_Struct_Ex* r = p;

    while (r->origin_addr != NULL) 
    {
        r = (LLP_Struct_Ex*)(r->origin_addr);
    }

    return r;
}

int llp_init(LLP_Struct_Ex **p) {
    if (*p == NULL) {
        *p = malloc(sizeof(LLP_Struct_Ex));
        memset(*p, 0x0, sizeof(LLP_Struct_Ex));
        if (p) return 1;
    }

    return -1;
}

int llp_append(LLP_Struct_Ex *p, uint32_t src, uint32_t dst, DMA_InitTypeDef *dma_init_type, uint32_t len) {
    LLP_Struct_Ex *tail;

    if (p == NULL) 
    {
        return -1;
    }

    tail = get_tail(p);
    tail->origin_addr = malloc(sizeof(LLP_Struct_Ex));
    memset(tail->origin_addr, 0x0, sizeof(LLP_Struct_Ex));
    tail->llp_struct.llp = mmap_to_sys((uint32_t)tail->origin_addr);
    tail = (LLP_Struct_Ex *)tail->origin_addr;

    tail->llp_struct.src = (uint32_t)mmap_to_sys((uint32_t)src);
    tail->llp_struct.dst = (uint32_t)mmap_to_sys((uint32_t)dst);
    tail->llp_struct.llp = (uint32_t)NULL;
    tail->llp_struct.ctl_reg_low  = DMA_INITTYPEDEF_TRANSFER_TO_UINT32(dma_init_type);
    tail->llp_struct.ctl_reg_high = len;
    tail->origin_addr    = 0;

    return 1;
}

int llp_free(LLP_Struct_Ex *p) 
{
    LLP_Struct_Ex *t =  (LLP_Struct_Ex *)p->origin_addr;
    LLP_Struct_Ex *f = (LLP_Struct_Ex *)p->origin_addr;

    while(t) {
        t = (LLP_Struct_Ex *)f->origin_addr;
        free(f);
        f = t;
    }

    return 0;
}

static int dma_test(void)
{
    /* Multi-Block Transfer with Linked List for Source and Linked List for Destination */

    LLP_Struct_Ex *llp = NULL;

    uint8_t dmatxdata0[DMA_TEST_BUFFER_LEN] = {};
    uint8_t dmarxdata0[DMA_TEST_BUFFER_LEN] = {};
    uint8_t dmatxdata1[DMA_TEST_BUFFER_LEN] = {};
    uint8_t dmarxdata1[DMA_TEST_BUFFER_LEN] = {};
    uint8_t dmatxdata2[DMA_TEST_BUFFER_LEN] = {};
    uint8_t dmarxdata2[DMA_TEST_BUFFER_LEN] = {};

    for (int i = 0; i < DMA_TEST_BUFFER_LEN; i++){
        dmatxdata0[i] = i;
        dmatxdata1[i] = i + DMA_TEST_BUFFER_LEN;
        dmatxdata2[i] = i + DMA_TEST_BUFFER_LEN * 2;
    }

    RCC_CLK_EN_Ctl(RCC_DMA_CLKEN, ENABLE);
    
    /*Initial interrupt*/
    ECLIC_SetShvIRQ(DMA_IRQn, ECLIC_VECTOR_INTERRUPT);
    ECLIC_ClearPendingIRQ(DMA_IRQn);
    ECLIC_SetPriorityIRQ(DMA_IRQn, 1);
    ECLIC_SetTrigIRQ(DMA_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(DMA_IRQn);
    
    /*Initial dma from memory to memory*/
    DMA_Clear_All_Interrupt_Cmd(DMA);

    DMA_InitTypeDef dma_init_type;

    dma_init_type.llp_src_en = ENABLE;
    dma_init_type.llp_dst_en = ENABLE;
    dma_init_type.reload_src_en = DISABLE;
    dma_init_type.reload_dst_en = DISABLE;
    dma_init_type.direction = MEM_TO_MEM_FLOW_CTOL_DMA;
    dma_init_type.src_msize = DMA_MSIZE1;
    dma_init_type.dst_msize = DMA_MSIZE1;
    dma_init_type.src_addr_type = DMA_ADDRESS_INCREASE;
    dma_init_type.dst_addr_type = DMA_ADDRESS_INCREASE;
    dma_init_type.src_width = DMA_WIDTH8;
    dma_init_type.dst_width = DMA_WIDTH8;
    dma_init_type.src_per = OTHER_REQ;
    dma_init_type.dst_per = OTHER_REQ;
    dma_init_type.fifo_mode_en = DISABLE;
    dma_init_type.max_abrst = 0;
    dma_init_type.src_handshaking_type = DMA_HW_HANDSHAKE;
    dma_init_type.dst_handshaking_type = DMA_HW_HANDSHAKE;
    dma_init_type.chanel_priority = DMA_PRIORITY0;
    dma_init_type.int_en = ENABLE;
    DMA_Init(DMA, DMA_CHANNEL0, &dma_init_type);

    /* DMA is enabled */
    DMA_Set_Enable_Cmd(DMA, ENABLE);
    /* DMA transfer finished interrupt is enabled */
    DMA_Set_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0, ENABLE);
    /* DMA block transfer finished interrupt is enabled */
    DMA_Set_Block_Interrupt_Cmd(DMA, DMA_CHANNEL0, ENABLE);

    llp_init(&llp);

    llp_append(llp, (uint32_t)dmatxdata0, (uint32_t)dmarxdata0, &dma_init_type, DMA_TRANS_BLOCK_SIZE);
    llp_append(llp, (uint32_t)dmatxdata1, (uint32_t)dmarxdata1, &dma_init_type, DMA_TRANS_BLOCK_SIZE);
    llp_append(llp, (uint32_t)dmatxdata2, (uint32_t)dmarxdata2, &dma_init_type, DMA_TRANS_BLOCK_SIZE);

    DMA_Set_Addr(DMA, DMA_CHANNEL0, 0, 0, 0, llp->llp_struct.llp);
    DMA_Set_Channel_Enable_Cmd(DMA, DMA_CHANNEL0, ENABLE);
    
    while (dma_blk == FALSE && dma_tfr == FALSE);

    dma_data_compare((LLP_Struct_Ex *)llp->origin_addr);
    llp_free((LLP_Struct_Ex *)llp->origin_addr);

    return 1;
}

__attribute__((interrupt)) void DMA_IRQHandler(void)
{
    uint8_t block_int_flag = 0, transfer_int_flag = 0;
    transfer_int_flag = DMA_Get_Transfer_Interrupt_Status(DMA);
    block_int_flag = DMA_Get_Block_Interrupt_Status(DMA);

    if (block_int_flag & DMA_CHANNEL0_INT_FLAG) 
    {
        dma_blk = TRUE;
        DMA_Clear_Block_Interrupt_Cmd(DMA, DMA_CHANNEL0);
        printf("DMA_Block_Int_Status\r\n");
    }

    if (transfer_int_flag & DMA_CHANNEL0_INT_FLAG) 
    {
        dma_tfr = TRUE;
        DMA_Clear_Transfer_Interrupt_Cmd(DMA, DMA_CHANNEL0);
        printf("DMA_Transfer_Int_Status\r\n");
    }
}
