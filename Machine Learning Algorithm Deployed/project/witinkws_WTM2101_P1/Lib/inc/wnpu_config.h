#ifndef _WNPU_CONFIG_H_
#define _WNPU_CONFIG_H_

#include <stdint.h>
//type
typedef int (*LOG_FUNC_T)(const char *, ...);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef  enum NPU_STATE{
    NPU_ENABEL = 1,
    NPU_DISABLE = -1,
} NPU_STATE_T;

void wnpu_set_log_func(LOG_FUNC_T func);

void DELAY_MS(int ms);

void DELAY_US(int us);

void pu_stage();

void pd_stage();

int wnpu_set_npu_colck_gate(int state);

void write_sigmoid_tab(const unsigned int *tab);

void write_sigmoid_tab_char(const unsigned char *tab, unsigned int len);

void write_tanh_tab(const unsigned int *tab);

void write_tanh_tab_char(const unsigned char *tab, unsigned int len);

void wnpu_write_analog_config(const unsigned short *config, unsigned int num);

void wnpu_write_round_config(const unsigned int *config, unsigned int len, unsigned short addr);

void wnpu_read_round_config(unsigned int *config, unsigned int len, unsigned short addr);

void wnpu_set_round_addr(unsigned short addr);

void wnpu_write_system_config(const unsigned short *config, unsigned int len);

void wnpu_back_system_config(unsigned short *config, unsigned int len);

int wnpu_chip_test(void);

void wnpu_clear_sram(void);

void wnpu_write_sram(signed char *data, unsigned short addr, int len);

void wnpu_read_sram(signed char *data, unsigned short addr, int len);

void wnpu_enable_fifo_mode(unsigned short en, unsigned short depth);

void wnpu_send_feature(unsigned char *feature, unsigned short addr, unsigned int feat_dim);

void wnpu_set_round(unsigned short addr);

void wnpu_start_infer(unsigned short max_round, unsigned short init_round);

void wnpu_start_infer_lowpower(unsigned short max_round, unsigned short init_round,void (*npuParallelCallback)(void), int isDmaWfi);

int wnpu_get_status(void);

int wnpu_wait_pause(void);

void wnpu_infer_continue(void);

void wnpu_get_infer_result(signed char *label, unsigned short addr, unsigned int lab_num);

void wnpu_dma_ctrl_config(unsigned int src, unsigned short dst, unsigned short len);

void wnpu_dma_ctrl_query(unsigned short src, unsigned int dst, unsigned short len);

void wnpu_dma_ctrl_cnn(unsigned short instr_addr, unsigned short param_addr, unsigned int mem_addr);

void wnpu_dma_ctrl_reset(void);

void wnpu_dma_ctrl_go(void);

int  wnpu_dma_ctrl_wait(void);

void wnpu_dma_clean_interrupt(void);

void wnpu_data_npu2soc(uint16_t regfile_addr, void* soc_mem_addr, uint32_t data_size, int isDmaWfi);

void wnpu_data_soc2npu(void* soc_mem_addr, uint16_t regfile_addr, uint32_t data_size, int isDmaWfi);

void wnpu_dma_init(void) ;

void wnpu_wfi_prepare(void) ;

void wnpu_wfi_wait(void);

void wnpu_wfi_cleanup(void);

void wnpu_irq_init(void);

// use dma or not
void wnpu_set_dma_enable(NPU_STATE_T enable);

NPU_STATE_T wnpu_get_dma_state();

#define NPU_CLK_OFF 0
#define NPU_CLK_ON 1



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _WNPU_CONFIG_H_