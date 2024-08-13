#ifndef _AW883xx_H_
#define _AW883xx_H_

#include "aw883xx_device.h"
#include "aw883xx_base.h"


#define AW_GET_32_DATA(w, x, y, z) \
		((uint32_t)((((uint8_t)w) << 24) | (((uint8_t)x) << 16) | (((uint8_t)y) << 8) | ((uint8_t)z)))
#define AW_GET_16_DATA(x, y) \
		((uint16_t)((((uint8_t)x) << 8) | (uint8_t)y))

#define MAX_I2C_BUFFER_SIZE		(65536)
#define AW883XX_READ_MSG_NUM		(2)

#define AW_I2C_RETRIES			(5)
#define AW_I2C_RETRY_DELAY		(5)/* 5ms */

#define AW_READ_CHIPID_RETRY_DELAY	(5)/* 5ms */
#define AW_START_RETRIES		(5)

#define AW883XX_FLAG_START_ON_MUTE	(1 << 0)
#define AW883XX_FLAG_SKIP_INTERRUPTS	(1 << 1)

#define AW883XX_I2S_CHECK_MAX		(5)

#define AW883XX_SYSST_CHECK_MAX		(10)

#define AW883XX_BIN_TYPE_NUM		(3)
#define AW883XX_LOAD_FW_DELAY_TIME	(3000)
#define AW883XX_START_WORK_DELAY_MS	(0)


#define AW883XX_DSP_16_DATA_MASK	(0x0000ffff)

#define AW_GET_IV_CNT_MAX		(6)
#define AW_KCONTROL_NUM			(2)
#define AW_HW_MONITOR_DELAY		(1000)




#define AW883xx_CHIP_ID_REG		(0x00)
#define AW883xx_I2C_READ_MSG_NUM	(2)
#define AW_START_RETRIES		(5)
#define AW883xx_SOFT_RESET_VALUE	(0x55aa)

#define AW_I2C_RETRIES			(5)	/* 5 times */
#define AW_I2C_RETRY_DELAY		(5)	/* 5 ms */

#define AW_NAME_BUF_MAX			(50)


typedef enum {
  AW_START= 0,
  AW_STOP = 1,
} aw_ctrl_t;

typedef enum {
  AW_HW_IRQ_HANDLE_OFF,
  AW_HW_IRQ_HANDLE_ON,
} aw_hw_irq_handle_t;

typedef enum {
  AW_FADE_OUT,
  AW_FADE_IN,
} aw_fade_dir_t;

enum aw883xx_chipid {
	PID_2049_ID = 0x2049,//fyy
};

enum aw883xx_int_type {
	INT_TYPE_NONE = 0,
	INT_TYPE_UVLO = 0x1,
	INT_TYPE_BSTOC = 0x2,
	INT_TYPE_OCDI = 0x4,
	INT_TYPE_OTHI = 0x8,
};

enum {
	AW_BSTCFG_DISABLE = 0,
	AW_BSTCFG_ENABLE,
};

enum {
	AW_SYNC_START = 0,
	AW_ASYNC_START,
};

enum {
	AW_STREAM_CLOSE = 0,
	AW_STREAM_OPEN,
};

enum aw_re_range {
	AW_RE_MIN = 1000,
	AW_RE_MAX = 40000,
};

typedef enum {
	AW_PIN_RESET = 0,
	AW_PIN_SET,
} aw_pinstate;

enum {
	AW_INTERNAL_TEMP = 0,
	AW_EXTERNAL_TEMP = 1,
};

typedef enum {
	AW_DSP_WORK = 0,
	AW_DSP_BYPASS = 1,
} aw_dsp_ctrl_t;

/********************************************
 * struct aw883xx
 *******************************************/
struct aw883xx {
	struct aw_device *aw_pa;
	unsigned int chip_id;
	struct aw_init_info *init_info;

	aw_dev_index_t dev;
	unsigned char i2c_addr;

	aw_phase_sync_t phase_sync;
	uint32_t allow_pw;
	uint8_t pstream;
	uint8_t i2c_log_en;

	aw_hw_irq_handle_t irq_handle;

	int (*i2c_read_func)(uint16_t dev_addr, uint8_t reg_addr,
				uint8_t *pdata, uint16_t len);
	int (*i2c_write_func)(uint16_t dev_addr, uint8_t reg_addr,
				uint8_t *pdata, uint16_t len);
	void (*reset_gpio_ctl)(bool PinState);
};


int aw883xx_i2c_writes(struct aw883xx *aw883xx,
		uint8_t reg_addr, uint8_t *buf, uint16_t len);
int aw883xx_i2c_write(struct aw883xx *aw883xx,
		uint8_t reg_addr, uint16_t reg_data);
int aw883xx_reg_write(struct aw883xx *aw883xx,
		uint8_t reg_addr, uint16_t reg_data);
int aw883xx_i2c_read(struct aw883xx *aw883xx,
			uint8_t reg_addr, uint16_t *reg_data);
int aw883xx_reg_read(struct aw883xx *aw883xx,
		uint8_t reg_addr, uint16_t *reg_data);
int aw883xx_reg_write_bits(struct aw883xx *aw883xx,
		uint8_t reg_addr, uint16_t mask, uint16_t reg_data);
int aw883xx_dsp_write(struct aw883xx *aw883xx,
		uint16_t dsp_addr, uint32_t dsp_data, uint8_t data_type);
int aw883xx_dsp_read(struct aw883xx *aw883xx,
		uint16_t dsp_addr, uint32_t *dsp_data, uint8_t data_type);
int aw883xx_get_dev_num(void);
struct aw883xx *aw883xx_get_dev(uint8_t dev);
int aw883xx_get_version(char *buf, int size);

int aw883xx_hw_reset_by_index(aw_dev_index_t dev);
int aw883xx_soft_reset(aw_dev_index_t dev);
int aw883xx_reg_show(aw_dev_index_t dev);
int aw883xx_reg_store(aw_dev_index_t dev, uint8_t reg_addr, uint16_t reg_data);
int aw883xx_dsp_info_show(aw_dev_index_t dev);

int aw883xx_set_fade_time(aw_fade_dir_t fade_dir, uint32_t time);
int aw883xx_get_fade_time(aw_fade_dir_t fade_dir, uint32_t *time);
int aw883xx_get_fade_step(aw_dev_index_t dev, uint32_t *step);
int aw883xx_set_fade_step(aw_dev_index_t dev, uint32_t step);
int aw883xx_get_volume(aw_dev_index_t dev, uint32_t *volume);
int aw883xx_set_volume(aw_dev_index_t dev,  uint32_t volume);

int aw883xx_set_profile_byname(aw_dev_index_t dev, char *name);
int aw883xx_ctrl_state(aw_dev_index_t dev, aw_ctrl_t aw_ctrl);
int aw883xx_smartpa_init(void *aw_info);
void aw883xx_smartpa_deinit(aw_dev_index_t dev);
int aw883xx_dsp_bypass_ctrl(aw_dev_index_t dev, aw_dsp_ctrl_t dsp_ctrl);

aw_hw_irq_handle_t aw883xx_get_hw_irq_status(aw_dev_index_t dev);
void aw883xx_irq_handler(aw_dev_index_t dev);
void aw883xx_irq_trigger(aw_dev_index_t dev);

void aw883xx_monitor_work(aw_dev_index_t dev);
void aw883xx_monitor_set_status(aw_dev_index_t dev);

int aw883xx_cali_re(aw_dev_index_t dev, aw_single_t is_single, uint32_t *re);
int aw883xx_cali_f0(aw_dev_index_t dev, aw_single_t is_single, uint32_t *f0);
int aw883xx_cali_f0_q(aw_dev_index_t dev, aw_single_t is_single, uint32_t *f0, uint32_t *q);
int aw883xx_cali_re_f0(aw_dev_index_t dev, aw_single_t is_single, uint32_t *re, uint32_t *f0);

int aw883xx_get_re_range(aw_dev_index_t dev, aw_single_t is_single, uint32_t *range_buf);
int aw883xx_get_r0(aw_dev_index_t dev, aw_single_t is_single, uint32_t *r0_data);
int aw883xx_get_f0(aw_dev_index_t dev, aw_single_t is_single, uint32_t *f0_data);
int aw883xx_get_te(aw_dev_index_t dev, aw_single_t is_single, int32_t *te_data);

int aw883xx_cali_re_store(aw_dev_index_t dev, aw_single_t is_single, uint32_t *set_re);
int aw883xx_read_re_from_dsp(aw_dev_index_t dev, uint32_t *re);

int aw883xx_cali_time_show(uint32_t *time);
int aw883xx_cali_time_store(uint32_t time);

#endif

