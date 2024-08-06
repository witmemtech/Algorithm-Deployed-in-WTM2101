#ifndef __WITIN_NPU_INTERFACE__
#define __WITIN_NPU_INTERFACE__
#include "witin_type.h"


extern void witin_log(WITIN_LOG_LEVEL_t level, const char *format, ...);

extern void witin_npu_init();
extern void witin_npu_change_clock();

extern int process_write_input_data_common(int8_t *buffer, int len, int memType, int addr);

extern int process_read_output_data_common(int8_t *buffer, int len, int memType, int addr);

extern void witin_npu_analog_seg_averge_num(int num);

extern int process_net_flow_allround(int net_index, int flow_index, int init_round, int max_round);

extern int process_net_flow_single_round(int net_index, int flow_index, int init_round, int max_round, int round_config_start);

extern int process_net_flow(int netIndex, int initFlow, int maxFlow);

extern int process_net( int netIndex) ;

extern int init_when_not_from_flow0(int net_index, int flow_start);

extern void witin_backup_net( int net_index);

extern void witin_resume_net( int net_index);

extern void witin_reset_net(int net_index, int adc_time);

extern int witin_npu_simple_power_up(void);

extern void self_fast_copy(int8_t* dest,  int8_t *src, int len);

extern int witin_backup_0_or_set_1_regfile(char *buffer, int len, int flag);

extern void witin_clear_all_sram();

extern int witin_clear_dma_buffer(int start, int len);

extern int witin_clear_regfile(int start, int len);

extern char *witin_get_dma_buffer_addr(void);

extern void witin_npu_wakeup(void);
#endif
