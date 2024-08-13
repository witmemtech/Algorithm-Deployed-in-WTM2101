#ifndef __AW883XX_INIT_H__
#define __AW883XX_INIT_H__


#include "aw_profile_process.h"

#define AW_MIXER_CHIP_MAX		(8)

struct aw_init_info {
	aw_dev_index_t dev;
	unsigned char i2c_addr;
	aw_phase_sync_t phase_sync;	/*Enable phase synchronization flag, default is 0, not enabled*/
	aw_fade_en_t fade_en;
	unsigned int re_min;
	unsigned int re_max;
	unsigned char cali_check_st;

	unsigned char mix_chip_count;	/*Number of mixed chips, usually is 1*/
	struct aw_prof_info *prof_info;	/*Chip configuration parameters*/

	int (*i2c_read_func)(uint16_t dev_addr, uint8_t reg_addr,
				uint8_t *pdata, uint16_t len);
	int (*i2c_write_func)(uint16_t dev_addr, uint8_t reg_addr,
				uint8_t *pdata, uint16_t len);
	void (*reset_gpio_ctl)(bool PinState);

	int (*dev_init_ops[AW_MIXER_CHIP_MAX])(void *aw883xx);
};

#endif
