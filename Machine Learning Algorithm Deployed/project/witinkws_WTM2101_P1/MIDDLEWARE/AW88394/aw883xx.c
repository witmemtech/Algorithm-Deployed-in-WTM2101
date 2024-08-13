/*
* aw883xx.c
*
* Copyright (c) 2021 AWINIC Technology CO., LTD
*
* Author: <zhaolei@awinic.com>
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "heap.h"

#include "aw883xx.h"
#include "aw883xx_base.h"
#include "aw883xx_device.h"
#include "aw883xx_init.h"
#include "aw883xx_calib.h"
#include "bb04p1_hal.h"

#define AW883XX_DRIVER_VERSION  "v0.2.0"
#define AW883xx_I2C_NAME "aw883xx_smartpa"

#define AW_READ_CHIPID_RETRIES		5	/* 5 times */


unsigned int g_aw883xx_dev_cnt = 0;
struct aw883xx *g_aw883xx[AW_DEV_MAX];


/******************************************************
 *
 * aw883xx i2c write/read
 *
 ******************************************************/
int aw883xx_i2c_writes(struct aw883xx *aw883xx,
	uint8_t reg_addr, uint8_t *buf, uint16_t len)
{
	int ret = -1;

	ret = aw883xx->i2c_write_func(aw883xx->i2c_addr, reg_addr, buf, len);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error");
	}
	return ret;
}

static int aw883xx_i2c_reads(struct aw883xx *aw883xx,
	uint8_t reg_addr, uint8_t *data_buf, uint16_t data_len)
{
	int ret = -1;
        //printf("AWERROR8 \n\r");
	ret = aw883xx->i2c_read_func(aw883xx->i2c_addr, reg_addr, data_buf, data_len);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c read error");
	}
	return ret;
}

int aw883xx_i2c_write(struct aw883xx *aw883xx,
		uint8_t reg_addr, uint16_t reg_data)
{
	int ret = -1;
	uint8_t cnt = 0;
	uint8_t buf[2] = {0};

	buf[0] = (reg_data & 0xff00) >> 8;
	buf[1] = (reg_data & 0x00ff) >> 0;

	while (cnt < AW_I2C_RETRIES) {
		ret = aw883xx_i2c_writes(aw883xx, reg_addr, buf, 2);
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "i2c_write cnt=%d error=%d",
				cnt, ret);
		} else {
			break;
		}
		cnt++;
	}

	if (aw883xx->i2c_log_en) {
		aw_dev_info(aw883xx->dev, "write: reg = 0x%02x, val = 0x%04x",
			reg_addr, reg_data);
	}

	return ret;
}

int aw883xx_i2c_read(struct aw883xx *aw883xx, uint8_t reg_addr, uint16_t *reg_data)
{
	int ret = -1;
	uint8_t cnt = 0;
	uint8_t buf[2] = {0};

	while (cnt < AW_I2C_RETRIES) {
        //printf("AWERROR7 \n\r");
		ret = aw883xx_i2c_reads(aw883xx, reg_addr, buf, 2);
                //printf("AWERROR9 %d \n\r",ret);
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "i2c_read cnt=%d error=%d",
				cnt, ret);
		} else {
			*reg_data = (buf[0] << 8) | (buf[1] << 0);
			break;
		}
		cnt++;
	}

	if (aw883xx->i2c_log_en) {
		aw_dev_info(aw883xx->dev, "read: reg = 0x%02x, val = 0x%04x",
			reg_addr, *reg_data);
	}

	return ret;
}

static int aw883xx_i2c_write_bits(struct aw883xx *aw883xx,
				uint8_t reg_addr, uint16_t mask,
				uint16_t reg_data)
{
	int ret = -1;
	uint16_t reg_val = 0;

	ret = aw883xx_i2c_read(aw883xx, reg_addr, &reg_val);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c read error, ret=%d", ret);
		return ret;
	}
	reg_val &= mask;
	reg_val |= reg_data & (~mask);
	ret = aw883xx_i2c_write(aw883xx, reg_addr, reg_val);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c read error, ret=%d", ret);
		return ret;
	}

	return 0;
}

int aw883xx_reg_write(struct aw883xx *aw883xx,
			uint8_t reg_addr, uint16_t reg_data)
{
	int ret = -1;

	aw_mutex_lock();
	ret = aw883xx_i2c_write(aw883xx, reg_addr, reg_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev,
			"write fail, reg = 0x%02x, val = 0x%04x, ret=%d",
			reg_addr, reg_data, ret);
	}
	aw_mutex_unlock();

	return ret;
}

int aw883xx_reg_read(struct aw883xx *aw883xx,
			uint8_t reg_addr, uint16_t *reg_data)
{
	int ret = -1;

	aw_mutex_lock();
	ret = aw883xx_i2c_read(aw883xx, reg_addr, reg_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev,
			"read fail: reg = 0x%02x, val = 0x%04x, ret=%d",
			reg_addr, *reg_data, ret);
	}
	aw_mutex_unlock();

	return ret;
}

int aw883xx_reg_write_bits(struct aw883xx *aw883xx,
			uint8_t reg_addr, uint16_t mask, uint16_t reg_data)
{
	int ret = -1;

	aw_mutex_lock();
	ret = aw883xx_i2c_write_bits(aw883xx, reg_addr, mask, reg_data);

	if (ret < 0) {
		aw_dev_err(aw883xx->dev,
			"aw883xx_reg_write_bits fail, ret=%d", ret);
	}
	aw_mutex_unlock();

	return ret;
}

static int aw883xx_dsp_write_16bit(struct aw883xx *aw883xx,
		uint16_t dsp_addr, uint32_t dsp_data)
{
	int ret = -1;
	struct aw_dsp_mem_desc *desc = &aw883xx->aw_pa->dsp_mem_desc;

	ret = aw883xx_i2c_write(aw883xx, desc->dsp_madd_reg, dsp_addr);

	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error, ret=%d", ret);
		return ret;
	}

	ret = aw883xx_i2c_write(aw883xx, desc->dsp_mdat_reg, (uint16_t)dsp_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error, ret=%d", ret);
		return ret;
	}

	return 0;
}

static int aw883xx_dsp_write_32bit(struct aw883xx *aw883xx,
		uint16_t dsp_addr, uint32_t dsp_data)
{
	int ret = -1;
	uint16_t temp_data = 0;
	struct aw_dsp_mem_desc *desc = &aw883xx->aw_pa->dsp_mem_desc;

	ret = aw883xx_i2c_write(aw883xx, desc->dsp_madd_reg, dsp_addr);

	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error, ret=%d", ret);
		return ret;
	}

	temp_data = dsp_data & AW883XX_DSP_16_DATA_MASK;
	ret = aw883xx_i2c_write(aw883xx, desc->dsp_mdat_reg, temp_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error, ret=%d", ret);
		return ret;
	}

	temp_data = dsp_data >> 16;
	ret = aw883xx_i2c_write(aw883xx, desc->dsp_mdat_reg, temp_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error, ret=%d", ret);
		return ret;
	}

	return 0;
}

/******************************************************
 * aw883xx clear dsp chip select state
 ******************************************************/
int aw883xx_get_version(char *buf, int size)
{
	if (size > strlen(AW883XX_DRIVER_VERSION)) {
		memcpy(buf, AW883XX_DRIVER_VERSION, strlen(AW883XX_DRIVER_VERSION));
		return strlen(AW883XX_DRIVER_VERSION);
	} else {
		return -ENOMEM;
	}
}

static void aw883xx_clear_dsp_sel_st(struct aw883xx *aw883xx)
{
	uint16_t reg_value;
	uint8_t reg = aw883xx->aw_pa->soft_rst.reg;

	aw883xx_i2c_read(aw883xx, reg, &reg_value);
}

int aw883xx_dsp_write(struct aw883xx *aw883xx,
		uint16_t dsp_addr, uint32_t dsp_data, uint8_t data_type)
{
	int ret = -1;

	aw_mutex_lock();
	if (data_type == AW_DSP_16_DATA) {
		ret = aw883xx_dsp_write_16bit(aw883xx, dsp_addr, dsp_data);
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "write dsp_addr[0x%04x] 16 bit dsp_data[%04x] failed",
					(uint32_t)dsp_addr, dsp_data);
			goto exit;
		}
	} else if (data_type == AW_DSP_32_DATA) {
		ret =  aw883xx_dsp_write_32bit(aw883xx, dsp_addr, dsp_data);
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "write dsp_addr[0x%04x] 32 bit dsp_data[%08x] failed",
					(uint32_t)dsp_addr, dsp_data);
			goto exit;
		}
	} else {
		aw_dev_err(aw883xx->dev, "data type[%d] unsupported", data_type);
		ret = -EINVAL;
		goto exit;
	}

exit:
	aw883xx_clear_dsp_sel_st(aw883xx);
	aw_mutex_unlock();

	return ret;
}


static int aw883xx_dsp_read_16bit(struct aw883xx *aw883xx,
		uint16_t dsp_addr, uint32_t *dsp_data)
{
	int ret = -1;
	uint16_t temp_data = 0;
	struct aw_dsp_mem_desc *desc = &aw883xx->aw_pa->dsp_mem_desc;

	ret = aw883xx_i2c_write(aw883xx, desc->dsp_madd_reg, dsp_addr);

	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error, ret=%d", ret);
		return ret;
	}

	ret = aw883xx_i2c_read(aw883xx, desc->dsp_mdat_reg, &temp_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error, ret=%d", ret);
		return ret;
	}

	*dsp_data = temp_data;

	return 0;
}

static int aw883xx_dsp_read_32bit(struct aw883xx *aw883xx,
		uint16_t dsp_addr, uint32_t *dsp_data)
{
	int ret = -1;
	uint16_t temp_data = 0;
	struct aw_dsp_mem_desc *desc = &aw883xx->aw_pa->dsp_mem_desc;

	/*write dsp addr*/
	ret = aw883xx_i2c_write(aw883xx, desc->dsp_madd_reg, dsp_addr);

	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c write error, ret=%d", ret);
		return ret;
	}

	/*get Low 16 bit data*/
	ret = aw883xx_i2c_read(aw883xx, desc->dsp_mdat_reg, &temp_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c read error, ret=%d", ret);
		return ret;
	}

	*dsp_data = temp_data;

	/*get high 16 bit data*/
	ret = aw883xx_i2c_read(aw883xx, desc->dsp_mdat_reg, &temp_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "i2c read error, ret=%d", ret);
		return ret;
	}
	*dsp_data |= (temp_data << 16);

	return 0;
}

int aw883xx_dsp_read(struct aw883xx *aw883xx,
		uint16_t dsp_addr, uint32_t *dsp_data, uint8_t data_type)
{
	int ret = -1;

	aw_mutex_lock();
	if (data_type == AW_DSP_16_DATA) {
		ret = aw883xx_dsp_read_16bit(aw883xx, dsp_addr, dsp_data);
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "read dsp_addr[0x%04x] 16 bit dsp_data[%04x] failed",
					(uint32_t)dsp_addr, *dsp_data);
			goto exit;
		}
	} else if (data_type == AW_DSP_32_DATA) {
		ret = aw883xx_dsp_read_32bit(aw883xx, dsp_addr, dsp_data);
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "read dsp_addr[0x%04x] 32 bit dsp_data[%08x] failed",
					(uint32_t)dsp_addr, *dsp_data);
			goto exit;
		}
	} else {
		aw_dev_err(aw883xx->dev, "data type[%d] unsupported", data_type);
		ret = -EINVAL;
		goto exit;
	}

exit:
	aw883xx_clear_dsp_sel_st(aw883xx);
	aw_mutex_unlock();

	return ret;
}

/******************************************************
 * aw883xx interface
 ******************************************************/
int aw883xx_get_dev_num(void)
{
	return g_aw883xx_dev_cnt;
}

struct aw883xx *aw883xx_get_dev(uint8_t dev)
{
	return g_aw883xx[dev];
}

static void aw883xx_start_pa(struct aw883xx *aw883xx)
{
	int ret = -1;
	int i;
	aw_dev_info(aw883xx->dev, "enter");

	if (aw883xx->allow_pw == false) {
		aw_dev_info(aw883xx->dev, "dev can not allow power");
		return;
	}

	if (aw883xx->pstream == AW_STREAM_CLOSE) {
		aw_dev_info(aw883xx->dev, "pstream is close");
		return;
	}

	for (i = 0; i < AW_START_RETRIES; i++) {
		ret = aw883xx_device_start(aw883xx->aw_pa);
		if (ret) {
			aw_dev_err(aw883xx->dev, "start failed");
			ret = aw883xx_dev_fw_update(aw883xx->aw_pa, AW_DSP_FW_UPDATE_ON, true);
			if (ret < 0) {
				aw_dev_err(aw883xx->dev, "fw update failed");
				continue;
			}
		} else {
			aw_dev_info(aw883xx->dev, "start success");
			break;
		}
	}
}

static void aw883xx_start(struct aw883xx *aw883xx)
{
	int ret = -1;
	int i;
	bool sync_start = 0;

	aw_dev_info(aw883xx->dev,"enter");

	if (aw883xx->aw_pa->fw_status == AW_DEV_FW_OK) {
		if (aw883xx->allow_pw == false) {
			aw_dev_info(aw883xx->dev, "dev can not allow power");
			return;
		}

		if (aw883xx->aw_pa->status == AW_DEV_PW_ON) {
			aw_dev_info(aw883xx->dev, "pa already start");
			return;
		}

		for (i = 0; i < AW_START_RETRIES; i++) {
			ret = aw883xx_dev_fw_update(aw883xx->aw_pa, AW_DSP_FW_UPDATE_OFF,
						aw883xx->phase_sync);
			if (ret < 0) {
				aw_dev_err(aw883xx->dev, "fw update failed");
				continue;
			} else {
				if (sync_start == AW_SYNC_START) {
					aw883xx_start_pa(aw883xx);
				}
				return;
			}
		}
	}
}

static void aw883xx_stop_pa(struct aw883xx *aw883xx)
{
	aw883xx_device_stop(aw883xx->aw_pa);
}


static int aw883xx_hw_reset(struct aw883xx *aw883xx)
{
	aw_dev_info(aw883xx->dev, "enter");
       
        printf("aw883xx->reset_gpio_ctl = %p \n\r",aw883xx->reset_gpio_ctl);
        printf("aw883xx->i2c_read_func  = %p \n\r",aw883xx->i2c_read_func);
        printf("aw883xx->i2c_write_func = %p \n\r",aw883xx->i2c_write_func);
	//aw883xx->reset_gpio_ctl(AW_PIN_RESET);
	//aw_dev_info(aw883xx->dev, "gpio_ctl=%d", AW_PIN_RESET);
	system_delay_ms(1);
	//aw883xx->reset_gpio_ctl(AW_PIN_SET);
	//aw_dev_info(aw883xx->dev, "gpio_ctl=%d", AW_PIN_SET);
	system_delay_ms(2);

	return 0;
}

#ifdef AW_DEBUG
int aw883xx_hw_reset_by_index(aw_dev_index_t dev)
{
	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx_hw_reset(g_aw883xx[dev]);

	return 0;
}


int aw883xx_soft_reset(aw_dev_index_t dev)
{
	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx_dev_soft_reset(g_aw883xx[dev]->aw_pa);

	return 0;
}


int aw883xx_reg_store(aw_dev_index_t dev, uint8_t reg_addr, uint16_t reg_data)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_err("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_err("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	aw883xx_i2c_write(aw883xx, reg_addr, reg_data);

	return 0;
}

int aw883xx_reg_show(aw_dev_index_t dev)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	aw883xx_dev_reg_dump(aw883xx->aw_pa);

	return 0;
}

static int aw883xx_dsp_log_info(struct aw883xx *aw883xx, unsigned int base_addr,
				uint32_t data_len, char *format)
{
	uint16_t reg_val = 0;
	char *dsp_reg_info = NULL;
	uint32_t dsp_info_len = 0;
	int i;

	dsp_reg_info = pvPortMalloc(AW_NAME_BUF_MAX);
	if (dsp_reg_info == NULL) {
		aw_dev_err(aw883xx->dev, "dsp_reg_info calloc failed");
		return -1;
	}

	aw_mutex_lock();
	aw883xx_i2c_write(aw883xx, aw883xx->aw_pa->dsp_mem_desc.dsp_madd_reg, base_addr);

	for (i = 0; i < data_len; i+=2) {
		aw883xx_i2c_read(aw883xx, aw883xx->aw_pa->dsp_mem_desc.dsp_mdat_reg, &reg_val);
		dsp_info_len += snprintf(dsp_reg_info + dsp_info_len, AW_NAME_BUF_MAX - dsp_info_len,
				"%02x,%02x,", (reg_val >> 0) & 0xff,
						(reg_val >> 8) & 0xff);
		if ((i / 2 + 1) % 8 == 0) {
			aw_dev_info(aw883xx->dev, "%s: %s", format, dsp_reg_info);
			dsp_info_len = 0;
			memset(dsp_reg_info, 0, AW_NAME_BUF_MAX);
		}

		if (((data_len) % 8 != 0) &&
			(i == (data_len - 2))) {
			aw_dev_info(aw883xx->dev, "%s: %s", format, dsp_reg_info);
			dsp_info_len = 0;
			memset(dsp_reg_info, 0, AW_NAME_BUF_MAX);
		}
	}

	dsp_info_len = 0;
	memset(dsp_reg_info, 0, AW_NAME_BUF_MAX);
	vPortFree(dsp_reg_info);
	dsp_reg_info = NULL;
	aw_mutex_unlock();

	return 0;
}

int aw883xx_dsp_info_show(aw_dev_index_t dev)
{
	struct aw883xx *aw883xx = NULL;
	uint32_t data_len;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	if (aw883xx->aw_pa->dsp_cfg == AW_DEV_DSP_BYPASS) {
		aw_dev_info(aw883xx->dev, "dsp bypass");
	} else {
		aw_dev_info(aw883xx->dev, "dsp working");
		ret = aw883xx_dev_get_iis_status(aw883xx->aw_pa);
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "No I2S signal");
			return -EINVAL;
		}

		aw_dev_info(aw883xx->dev, "dsp_firmware_len:%d", aw883xx->aw_pa->dsp_fw_len);
		ret = aw883xx_dsp_log_info(aw883xx, aw883xx->aw_pa->dsp_mem_desc.dsp_fw_base_addr,
			aw883xx->aw_pa->dsp_fw_len, "dsp_fw");
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "dsp_fw display failed");
			return -EINVAL;
		}

		aw_dev_info(aw883xx->dev, "dsp_config_len:%d", aw883xx->aw_pa->dsp_cfg_len);
		ret = aw883xx_dsp_log_info(aw883xx, aw883xx->aw_pa->dsp_mem_desc.dsp_cfg_base_addr,
			aw883xx->aw_pa->dsp_cfg_len, "dsp_config");
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "dsp_config display failed");
			return -EINVAL;
		}

		aw_dev_info(aw883xx->dev, "dsp_config:0x8180-0x83fc");
		data_len = 2 * (aw883xx->aw_pa->dsp_st_desc.dsp_reg_e1 -
			aw883xx->aw_pa->dsp_st_desc.dsp_reg_s1);
		ret = aw883xx_dsp_log_info(aw883xx, aw883xx->aw_pa->dsp_st_desc.dsp_reg_s1,
			data_len, "dsp_st");
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "dsp_config:0x8180-0x83fc display failed");
			return -EINVAL;
		}

		aw_dev_info(aw883xx->dev, "dsp_config:0x9c00-0x9c5c");
		data_len = 2 * (aw883xx->aw_pa->dsp_st_desc.dsp_reg_e2 -
			aw883xx->aw_pa->dsp_st_desc.dsp_reg_s2);
		ret = aw883xx_dsp_log_info(aw883xx, aw883xx->aw_pa->dsp_st_desc.dsp_reg_s2,
			data_len , "dsp_st");
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "dsp_config:0x9c00-0x9c5c display failed");
			return -EINVAL;
		}
	}

	return 0;
}
#endif

#ifdef AW_FADE
int aw883xx_set_fade_step(aw_dev_index_t dev, uint32_t step)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];
	aw883xx_dev_set_fade_vol_step(aw883xx->aw_pa, step);

	aw_dev_info(aw883xx->dev, "set step %d DB Done", step);

	return 0;
}

int aw883xx_get_fade_step(aw_dev_index_t dev, uint32_t *step)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_err("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if ((g_aw883xx[dev] == NULL) || (step == NULL)) {
		aw_pr_err("g_aw883xx[%d] is NULL or step is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	*step = aw883xx_dev_get_fade_vol_step(aw883xx->aw_pa);
	aw_dev_info(aw883xx->dev, "get step %d Done", *step);

	return 0;
}

int aw883xx_set_fade_time(aw_fade_dir_t fade_dir, uint32_t time)
{
	aw883xx_dev_set_fade_time(time, fade_dir);

	return 0;
}

int aw883xx_get_fade_time(aw_fade_dir_t fade_dir, uint32_t *time)
{
	if (time == NULL) {
		aw_pr_err("time is NULL");
		return -EINVAL;
	}

	aw883xx_dev_get_fade_time(time, fade_dir);

	return 0;
}
#endif

#ifdef AW_VOLUME
int aw883xx_get_volume(aw_dev_index_t dev, uint32_t *volume)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_err("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if ((g_aw883xx[dev] == NULL) || (volume == NULL)) {
		aw_pr_err("g_aw883xx[%d] is NULL or volume is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	aw883xx_dev_get_init_volume(aw883xx->aw_pa, volume);

	aw_dev_info(aw883xx->dev, "get volume %d", *volume);

	return 0;
}

int aw883xx_set_volume(aw_dev_index_t dev, uint32_t volume)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_err("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_err("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_set_init_volume(aw883xx->aw_pa, volume);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "set volume failed");
		return ret;
	}

	aw_dev_info(aw883xx->dev, "set volume %d", volume);

	return 0;
}
#endif

int aw883xx_ctrl_state(aw_dev_index_t dev, aw_ctrl_t aw_ctrl)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_err("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_err("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	if (aw_ctrl) {
		aw883xx->pstream = AW_STREAM_CLOSE;
		aw883xx_stop_pa(aw883xx);
	} else {
		aw883xx->pstream = AW_STREAM_OPEN;
		aw883xx_start(aw883xx);
	}

	return 0;
}

int aw883xx_set_profile_byname(aw_dev_index_t dev, char *prof_name)
{
	int ret = -1;
	char *cur_name = NULL;
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_err("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_err("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	cur_name = aw883xx_dev_get_profile_name(aw883xx->aw_pa);
	if (strncmp(cur_name, prof_name, AW_PROF_NAME_MAX) == 0) {
		aw_dev_info(aw883xx->dev, "profile no change");
		return 0;
	}

	ret = aw883xx_dev_set_profile_name(aw883xx->aw_pa, prof_name);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "set profile [%s] failed", prof_name);
		return -EINVAL;
	}

	aw_dev_info(aw883xx->dev, "set prof name %s", prof_name);

	return 0;
}

static int aw883xx_check_init_info(struct aw_init_info *init_info)
{
	int ret = -1;

	/*check dev index*/
	if (init_info->dev >= AW_DEV_MAX) {
		aw_pr_err("unsupported dev:%d", init_info->dev);
		return -EINVAL;
	}

	/*check i2c funtion*/
	if ((init_info->i2c_read_func == NULL) ||
		(init_info->i2c_write_func == NULL)) {
		aw_dev_err(init_info->dev, "i2c funtion is NULL");
		return -EINVAL;
	}

	ret = aw883xx_dev_check_prof(init_info->dev, init_info->prof_info);
	if (ret < 0) {
		aw_dev_err(init_info->dev, "check prof failed");
		return ret;
	}

	return 0;
}

static struct aw883xx *aw883xx_malloc_init(struct aw_init_info *init_info)
{
	struct aw883xx *aw883xx = pvPortMalloc(sizeof(struct aw883xx));
	if (aw883xx == NULL) {
		aw_dev_err(init_info->dev, "calloc aw883xx failed.");
		return NULL;
	}

	aw883xx->init_info = init_info;
	aw883xx->aw_pa = NULL;
	aw883xx->dev = init_info->dev;
	aw883xx->i2c_addr = init_info->i2c_addr;
	aw883xx->i2c_read_func = init_info->i2c_read_func;
	aw883xx->i2c_write_func = init_info->i2c_write_func;

	if (init_info->phase_sync) {
		aw883xx->phase_sync = init_info->phase_sync;
	} else {
		aw883xx->phase_sync = AW_PHASE_SYNC_DISABLE;
	}

	if (init_info->reset_gpio_ctl) {
		aw883xx->reset_gpio_ctl = init_info->reset_gpio_ctl;
	} else {
		aw883xx->reset_gpio_ctl = NULL;
	}

	aw883xx->allow_pw = true;
	aw883xx->i2c_log_en = false;

	return aw883xx;
}

static int aw883xx_read_chipid(struct aw883xx *aw883xx)
{
	int ret = -1;
	unsigned int cnt = 0;
	uint16_t reg_value = 0;
   
	while (cnt < AW_READ_CHIPID_RETRIES) {
                //printf("AWERROR6 \n\r");
		ret = aw883xx_i2c_read(aw883xx, AW883xx_CHIP_ID_REG, &reg_value);
                
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "failed to read REG_ID: %d", ret);
			return -EIO;
		}
		switch (reg_value) {
		case PID_2049_ID: {
			aw_dev_info(aw883xx->dev, "aw883xx 2049 detected");
			aw883xx->chip_id = reg_value;
			return 0;
		}
		default:
			aw_dev_info(aw883xx->dev, "unsupported device revision (0x%x)",
							reg_value);
			break;
		}
		cnt++;

		AW_MS_DELAY(AW_READ_CHIPID_RETRY_DELAY);
	}

	return -EINVAL;
}

static int aw883xx_init(struct aw883xx *aw883xx)
{
	int i = 0;
	int ret;
	struct aw_init_info *init_info = aw883xx->init_info;

	for (i = 0; i < init_info->mix_chip_count; i++) {
		aw_dev_dbg(aw883xx->dev, "%d enter", i);
		if (init_info->dev_init_ops[i] == NULL) {
			aw_dev_err(aw883xx->dev, "init_info->dev_init_ops[%d] is null", i);
			return -EINVAL;
		}

		ret = init_info->dev_init_ops[i]((void *)aw883xx);
		if (ret < 0) {
			aw_dev_dbg(aw883xx->dev, "%d enter", i);
			continue;
		} else {
			aw_dev_dbg(aw883xx->dev, "%d init success", i);
			break;
		}
	}

	return ret;
}

int aw883xx_smartpa_init(void *aw_info)
{
	int ret = -1;
	struct aw_init_info *aw_init_info = NULL;
	struct aw883xx *aw883xx = NULL;

	aw_pr_info("enter");

	if (aw_info == NULL) {
		aw_pr_err("aw_info is NULL");
		return -ENOMEM;
	}
     
	aw_init_info = (struct aw_init_info *)aw_info;
    
	ret = aw883xx_check_init_info(aw_init_info);
	if (ret < 0) {
            printf("aw883xx_check_init_info err\r\n");
            return ret;
	}
   
	aw883xx = aw883xx_malloc_init(aw_init_info);
	if (aw883xx == NULL) {
		aw_dev_err(aw_init_info->dev, "malloc aw883xx failed");
		return -ENOMEM;
	}
     
	/* hardware reset */
	//aw883xx_hw_reset(aw883xx);
      
	/* aw883xx chip id */
	ret = aw883xx_read_chipid(aw883xx);
     
	if (ret < 0) {
            printf("aw883xx_read_chipid failed ret=%d", ret);
            aw_dev_err(aw_init_info->dev, "aw883xx_read_chipid failed ret=%d", ret);
            goto read_chip_failed;
	}

	/*aw pa init*/
	ret = aw883xx_init(aw883xx);
	if (ret) {
            printf("aw883xx_init ERR %d", ret);
            goto init_failed;
	}

	aw883xx->aw_pa->status = AW_DEV_PW_OFF;
	aw883xx->aw_pa->fw_status = AW_DEV_FW_OK;

	if (aw_init_info->fade_en) {
		aw883xx->aw_pa->fade_en = aw_init_info->fade_en;
	} else {
		aw883xx->aw_pa->fade_en = AW_FADE_DISABLE;
	}

	if (aw_init_info->re_min) {
		aw883xx->aw_pa->re_range.re_min = aw_init_info->re_min;
	} else {
		aw883xx->aw_pa->re_range.re_min = AW_RE_MIN;
	}

	if (aw_init_info->re_max) {
		aw883xx->aw_pa->re_range.re_max = aw_init_info->re_max;
	} else {
		aw883xx->aw_pa->re_range.re_max = AW_RE_MAX;
	}

	if (aw_init_info->cali_check_st) {
		aw883xx->aw_pa->cali_desc.cali_check_st = aw_init_info->cali_check_st;
	} else {
		aw883xx->aw_pa->cali_desc.cali_check_st = CALI_CHECK_DISABLE;
	}
	aw883xx->aw_pa->cali_desc.cali_result = CALI_RESULT_NONE;

	g_aw883xx[aw_init_info->dev] = aw883xx;
	g_aw883xx_dev_cnt++;
	aw_dev_info(aw_init_info->dev, "dev:%d init success",
				aw_init_info->dev);

	return 0;

init_failed:
read_chip_failed:
	vPortFree(aw883xx);
	aw883xx = NULL;
	return ret;
}


void aw883xx_smartpa_deinit(aw_dev_index_t dev)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev_index:%d", dev);
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
	}

	aw883xx = g_aw883xx[dev];

	if (aw883xx->aw_pa->ops.aw_monitor_deinit) {
		aw883xx->aw_pa->ops.aw_monitor_deinit((void *)aw883xx->aw_pa);
	}

	if (aw883xx->aw_pa->crc_dsp_cfg.data != NULL) {
		aw883xx->aw_pa->crc_dsp_cfg.len = 0;
		vPortFree(aw883xx->aw_pa->crc_dsp_cfg.data);
		aw883xx->aw_pa->crc_dsp_cfg.data = NULL;
	}

	if (aw883xx->aw_pa != NULL) {
		vPortFree(aw883xx->aw_pa);
		aw883xx->aw_pa = NULL;
	}

	if (aw883xx != NULL) {
		vPortFree(aw883xx);
		aw883xx = NULL;
	}
}

int aw883xx_dsp_bypass_ctrl(aw_dev_index_t dev, aw_dsp_ctrl_t dsp_ctrl)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_err("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_err("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	if (dsp_ctrl) {
		aw883xx->aw_pa->dsp_cfg = AW_DEV_DSP_BYPASS;
	} else {
		aw883xx->aw_pa->dsp_cfg = AW_DEV_DSP_WORK;
	}

	return 0;
}

/***************************************************************************
 *aw883xx irq
 ***************************************************************************/
#ifdef AW_IRQ

aw_hw_irq_handle_t aw883xx_get_hw_irq_status(aw_dev_index_t dev)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
	}

	aw883xx = g_aw883xx[dev];
	aw_dev_info(aw883xx->dev, "irq_handle=%d", aw883xx->irq_handle);
	return aw883xx->irq_handle;
}

void aw883xx_irq_handler(aw_dev_index_t dev)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return;
	}

		aw883xx = g_aw883xx[dev];

	if (aw883xx->irq_handle == AW_HW_IRQ_HANDLE_ON){
		/*awinic:Add operations after interrupt triggering*/
		aw883xx_dev_interrupt_clear(aw883xx->aw_pa);
		aw883xx->irq_handle = AW_HW_IRQ_HANDLE_OFF;
		aw_dev_info(aw883xx->dev, "irq_handle=%d",aw883xx->irq_handle);
	}
}

void aw883xx_irq_trigger(aw_dev_index_t dev)
{
	struct aw883xx *aw883xx = NULL;
	//uint16_t reg_value;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return;
	}

	aw883xx = g_aw883xx[dev];

	aw883xx->irq_handle = AW_HW_IRQ_HANDLE_ON;
	aw_dev_info(aw883xx->dev, "irq_handle=%d",aw883xx->irq_handle);
}
#endif

/***********************************************************************
 * aw883xx monitor
 ***********************************************************************/
#ifdef AW_MONITOR

void aw883xx_monitor_work(aw_dev_index_t dev)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return;
	}

	aw883xx = g_aw883xx[dev];

	if (aw883xx->aw_pa->ops.aw_monitor_work_func) {
		aw883xx->aw_pa->ops.aw_monitor_work_func((void *)aw883xx->aw_pa);
	}
}

void aw883xx_monitor_set_status(aw_dev_index_t dev)
{
	struct aw883xx *aw883xx = NULL;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return;
	}

	aw883xx = g_aw883xx[dev];

	if (aw883xx->aw_pa->ops.aw_monitor_set_handle) {
		aw883xx->aw_pa->ops.aw_monitor_set_handle((void *)aw883xx->aw_pa);
	}
}
#endif

/***********************************************************************
 * aw883xx cali
 ***********************************************************************/
#ifdef AW_CALIB
int aw883xx_cali_re(aw_dev_index_t dev, aw_single_t is_single, uint32_t *re)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_cali_re((void *)aw883xx->aw_pa, is_single);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali re failed");
	}

	ret = aw883xx_dev_cali_re_show((void *)aw883xx->aw_pa, is_single, re);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali re show failed");
	}

	return ret;
}

int aw883xx_cali_f0(aw_dev_index_t dev, aw_single_t is_single, uint32_t *f0)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_cali_f0_q((void *)aw883xx->aw_pa, is_single);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali f0 failed");
	}

	ret = aw883xx_dev_cali_f0_show((void *)aw883xx->aw_pa, is_single, f0);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali f0 show failed");
	}

	return ret;
}

int aw883xx_cali_f0_q(aw_dev_index_t dev, aw_single_t is_single, uint32_t *f0, uint32_t *q)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_cali_f0_q((void *)aw883xx->aw_pa, is_single);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali f0 failed");
	}

	ret = aw883xx_dev_cali_f0_show((void *)aw883xx->aw_pa, is_single, f0);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali f0 show failed");
	}

	ret = aw883xx_dev_cali_q_show((void *)aw883xx->aw_pa, is_single, q);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali q show failed");
	}

	return ret;
}

int aw883xx_cali_re_f0(aw_dev_index_t dev, aw_single_t is_single, uint32_t *re, uint32_t *f0)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_cali_re_f0((void *)aw883xx->aw_pa, is_single);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali re_f0 failed");
	}

	ret = aw883xx_dev_cali_re_show((void *)aw883xx->aw_pa, is_single, re);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali re show failed");
	}

	ret = aw883xx_dev_cali_f0_show((void *)aw883xx->aw_pa, is_single, f0);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali f0 show failed");
	}

	return ret;
}

int aw883xx_get_re_range(aw_dev_index_t dev, aw_single_t is_single, uint32_t *range_buf)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_get_re_range((void *)aw883xx->aw_pa, is_single, range_buf);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "get re range failed");
	}
	return ret;
}


int aw883xx_get_r0(aw_dev_index_t dev, aw_single_t is_single, uint32_t *r0_data)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_get_r0((void *)aw883xx->aw_pa, is_single, r0_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "get r0 failed");
	}
	return ret;
}

int aw883xx_get_f0(aw_dev_index_t dev, aw_single_t is_single, uint32_t *f0_data)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_get_f0((void *)aw883xx->aw_pa, is_single, f0_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "get r0 failed");
	}
	return ret;
}


int aw883xx_get_te(aw_dev_index_t dev, aw_single_t is_single, int32_t *te_data)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_get_te((void *)aw883xx->aw_pa, is_single, te_data);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "get te failed");
	}
	return ret;
}

int aw883xx_cali_re_store(aw_dev_index_t dev, aw_single_t is_single, uint32_t *set_re)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	ret = aw883xx_dev_cali_re_store((void *)aw883xx->aw_pa, is_single, set_re);
	if (ret < 0) {
		aw_dev_err(aw883xx->dev, "cali re store failed");
	}
	return ret;
}

int aw883xx_read_re_from_dsp(aw_dev_index_t dev, uint32_t *re)
{
	struct aw883xx *aw883xx = NULL;
	int ret = -1;

	if (dev >= AW_DEV_MAX) {
		aw_pr_info("unsupported dev:%d", dev);
		return -EINVAL;
	}

	if (g_aw883xx[dev] == NULL) {
		aw_pr_info("g_aw883xx[%d] is NULL", dev);
		return -EINVAL;
	}

	aw883xx = g_aw883xx[dev];

	if (aw883xx->pstream == AW_STREAM_OPEN) {
		ret = aw883xx_dev_read_re_from_dsp((void *)aw883xx->aw_pa, re);
		if (ret < 0) {
			aw_dev_err(aw883xx->dev, "read re from dsp failed");
		}
	} else {
		aw_dev_err(aw883xx->dev, "PA not work, please work and retry");
	}
	return ret;
}

int aw883xx_cali_time_show(uint32_t *time)
{
	if (time == NULL) {
		aw_pr_err("time is NULL");
		return -EINVAL;
	}
	aw883xx_dev_cali_time_show(time);
	return 0;
}

int aw883xx_cali_time_store(uint32_t time)
{
	int ret = -1;
	ret = aw883xx_dev_cali_time_store(time);
	if (ret < 0) {
		aw_pr_err("set cali_time failed");
		return -EINVAL;
	}
	return 0;
}
#endif
