/*
* aw_device.c
*
* Copyright (c) 2021 AWINIC Technology CO., LTD
*
* Author: <zhaolei@awinic.com>
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

#include "aw883xx_base.h"
#include "aw883xx_device.h"
#include "aw_profile_process.h"

#define AW_DEV_SYSST_CHECK_MAX		(10)

static unsigned int g_fade_in_time = AW_1_MS;
static unsigned int g_fade_out_time = AW_1_MS;


#ifdef AW_MONITOR
extern int aw883xx_monitor_init(void *dev);
extern void aw883xx_monitor_start(void *dev);
extern void aw883xx_monitor_stop(void *dev);
extern void aw883xx_monitor_deinit(void *dev);
extern int aw883xx_monitor_work_func(void *dev);
extern void aw883xx_monitor_set_handle(void *dev);

void aw883xx_dev_get_monitor_func(struct aw_device *aw_dev)
{
	aw_dev->ops.aw_monitor_init = aw883xx_monitor_init;
	aw_dev->ops.aw_monitor_start = aw883xx_monitor_start;
	aw_dev->ops.aw_monitor_stop = aw883xx_monitor_stop;
	aw_dev->ops.aw_monitor_deinit = aw883xx_monitor_deinit;
	aw_dev->ops.aw_monitor_work_func = aw883xx_monitor_work_func;
	aw_dev->ops.aw_monitor_set_handle = aw883xx_monitor_set_handle;
}

#else
void aw883xx_dev_get_monitor_func(struct aw_device *aw_dev)
{
	aw_dev->ops.aw_monitor_init = NULL;
	aw_dev->ops.aw_monitor_start = NULL;
	aw_dev->ops.aw_monitor_stop = NULL;
	aw_dev->ops.aw_monitor_deinit = NULL;
	aw_dev->ops.aw_monitor_work_func = NULL;
	aw_dev->ops.aw_monitor_work_func = NULL;
	aw_dev->ops.aw_monitor_set_handle = NULL;
}
#endif


int aw883xx_dev_check_prof(uint32_t dev, struct aw_prof_info *prof_info)
{
	struct aw_prof_desc *prof_desc = NULL;
	int i = 0;
	int j = 0;

	if (prof_info == NULL) {
		aw_dev_err(dev, "prof_info is NULL");
		return -EINVAL;
	}

	if (prof_info->count <= 0) {
		aw_dev_err(dev, "prof count :%d unsupported", prof_info->count);
		return -EINVAL;
	}

	prof_desc = prof_info->prof_desc;
	for (i = 0; i < prof_info->count; i++) {
		if (prof_desc == NULL) {
			aw_dev_err(dev, "invalid prof_desc");
			return -EINVAL;
		}

		if (prof_desc->sec_desc->len <= 0) {
			aw_dev_err(dev, "prof len:%d unsupported", prof_desc->sec_desc->len);
			return -EINVAL;
		}

		if (prof_desc->sec_desc->data == NULL) {
			aw_dev_err(dev, "prof data is NULL");
			return -EINVAL;
		}
	}


	for (i = 0; i < prof_info->count; i++) {
		for (j = i + 1; j < prof_info->count; j++) {
			if (strncmp(prof_info->prof_desc[i].name, prof_info->prof_desc[j].name, AW_PROF_NAME_MAX) == 0) {
				aw_dev_err(dev, "prof_desc pos[%d] and prof_desc pos[%d] conflict with prof_name[%s]",
						i, j, prof_info->prof_desc[j].name);
				return -EINVAL;
			}
		}
	}

	aw_dev_info(dev, "aw_dev_check_prof success");

	return 0;
}

struct aw_sec_data_desc *aw883xx_dev_get_prof_data_byname(struct aw_device *aw_dev, char *prof_name, int data_type)
{
	struct aw_sec_data_desc *sec_data = NULL;
	struct aw_prof_desc *prof_desc = NULL;
	struct aw_prof_info *prof_info = aw_dev->prof_info;
	int i = 0;

	if (data_type >= AW_DATA_TYPE_MAX) {
		aw_dev_err(aw_dev->dev, "unsupport data type id [%d]", data_type);
		return NULL;
	}

	for (i = 0; i < prof_info->count; i++) {
		if (strncmp(prof_name, prof_info->prof_desc[i].name, AW_PROF_NAME_MAX) == 0) {
			prof_desc = &aw_dev->prof_info->prof_desc[i];
			sec_data = &prof_desc->sec_desc[data_type];
			aw_dev_dbg(aw_dev->dev, "get prof[%s] data len[%d]",
								prof_desc->name, sec_data->len);
			return sec_data;
		}
	}

	aw_dev_err(aw_dev->dev, "not found prof_name[%s]", prof_name);
	return NULL;
}

static int aw_dev_check_profile_name(struct aw_device *aw_dev, const char *prof_name)
{
	int i =0;
	struct aw_prof_info *prof_info = aw_dev->prof_info;

	for (i = 0; i < prof_info->count; i++) {
		if (strncmp(prof_name, prof_info->prof_desc[i].name, AW_PROF_NAME_MAX) == 0){
			return 0;
		}
	}
	aw_dev_err(aw_dev->dev, "not found prof_name[%s]", prof_name);
	return -EINVAL;
}

int aw883xx_dev_set_profile_name(struct aw_device *aw_dev, const char *prof_name)
{
	if (aw_dev_check_profile_name(aw_dev, prof_name)) {
		return -EINVAL;
	} else {
		strncpy(aw_dev->set_prof_name, prof_name, AW_PROF_NAME_MAX - 1);
		aw_dev_info(aw_dev->dev, "set prof_name[%s]", aw_dev->set_prof_name);
	}
	return 0;
}

char *aw883xx_dev_get_profile_name(struct aw_device *aw_dev)
{
	return aw_dev->set_prof_name;
}

static int aw_dev_prof_init(struct aw_device *aw_dev, struct aw_init_info *init_info)
{
	int i =0;
	const char *first_prof_name = NULL;
	/*find profile*/
	for (i = 0; i < init_info->mix_chip_count; i++) {
		if (init_info->prof_info[i].chip_id == aw_dev->chip_id) {
			aw_dev->prof_info = &init_info->prof_info[i];
			first_prof_name = init_info->prof_info[i].prof_desc[0].name;
			strncpy(aw_dev->first_prof_name, first_prof_name, AW_PROF_NAME_MAX);
			aw_dev_info(aw_dev->dev, "first prof_name[%s]", aw_dev->first_prof_name);
			return 0;
		}
	}

	aw_dev_err(aw_dev->dev, "no supported profile");
	return -EINVAL;
}

/*****************************awinic device*************************************/
int aw883xx_dev_reg_dump(struct aw_device *aw_dev)
{
	int reg_num = aw_dev->ops.aw_get_reg_num();
	uint8_t i = 0;
	uint16_t reg_val = 0;

	for (i = 0; i < reg_num; i++) {
		if (aw_dev->ops.aw_check_rd_access(i)) {
			aw_dev->ops.aw_reg_read(aw_dev, i, &reg_val);
			aw_dev_info(aw_dev->dev, "read: reg = 0x%02x, val = 0x%04x",
				i, reg_val);
		}
	}
	return 0;
}

static int aw_dev_dsp_data_order(struct aw_device *aw_dev,
				uint8_t *data, uint32_t data_len)
{
	int i = 0;
	uint8_t tmp_val = 0;

	aw_dev_dbg(aw_dev->dev, "enter");
	if (data_len % 2 != 0) {
		aw_dev_dbg(aw_dev->dev, "data_len:%d unsupported", data_len);
		return -EINVAL;
	}
	for (i = 0; i < data_len; i += 2) {
		tmp_val = data[i];
		data[i] = data[i + 1];
		data[i + 1] = tmp_val;
	}
	return 0;
}

static void aw_dev_fade_in(struct aw_device *aw_dev)
{
	int i = 0;
	struct aw_volume_desc *desc = &aw_dev->volume_desc;
	int fade_step = aw_dev->fade_step;

	if (!aw_dev->fade_en) {
		return;
	}

	if (fade_step == 0 || g_fade_in_time == 0) {
		aw_dev->ops.aw_set_volume(aw_dev, desc->init_volume);
		return;
	}
	/*volume up*/
	for (i = desc->mute_volume; i >= desc->init_volume; i -= fade_step) {
		aw_dev->ops.aw_set_volume(aw_dev, i);
		AW_MS_DELAY(g_fade_in_time);
	}
	if (i != desc->init_volume) {
		aw_dev->ops.aw_set_volume(aw_dev, desc->init_volume);
	}
}

static void aw_dev_fade_out(struct aw_device *aw_dev)
{
	int i = 0;
	uint16_t start_volume = 0;
	struct aw_volume_desc *desc = &aw_dev->volume_desc;
	int fade_step = aw_dev->fade_step;

	if (!aw_dev->fade_en) {
		return;
	}

	if (fade_step == 0 || g_fade_out_time == 0) {
		aw_dev->ops.aw_set_volume(aw_dev, desc->mute_volume);
		return;
	}

	aw_dev->ops.aw_get_volume(aw_dev, &start_volume);
	i = start_volume;
	for (i = start_volume; i <= desc->mute_volume; i += fade_step) {
		aw_dev->ops.aw_set_volume(aw_dev, i);
		AW_MS_DELAY(g_fade_out_time);
	}
	if (i != desc->mute_volume) {
		aw_dev->ops.aw_set_volume(aw_dev, desc->mute_volume);
		AW_MS_DELAY(g_fade_out_time);
	}
}

#ifdef AW_FADE
int aw883xx_dev_get_fade_vol_step(struct aw_device *aw_dev)
{
	return aw_dev->fade_step;
}

void aw883xx_dev_set_fade_vol_step(struct aw_device *aw_dev, unsigned int step)
{
	aw_dev->fade_step = step;
}

void aw883xx_dev_get_fade_time(unsigned int *time, bool fade_in)
{
	if (fade_in) {
		*time = g_fade_in_time;
	} else {
		*time = g_fade_out_time;
	}
}

void aw883xx_dev_set_fade_time(unsigned int time, bool fade_in)
{
	if (fade_in) {
		g_fade_in_time = time;
	} else {
		g_fade_out_time = time;
	}
}
#endif

#ifdef AW_VOLUME
void aw883xx_dev_get_init_volume(struct aw_device *aw_dev, uint32_t *volume)
{
	struct aw_volume_desc *desc = &aw_dev->volume_desc;

	*volume =  desc->init_volume;
}

int aw883xx_dev_set_init_volume(struct aw_device *aw_dev, uint32_t volume)
{
	struct aw_volume_desc *desc = &aw_dev->volume_desc;

	if (volume > desc->mute_volume) {
		aw_dev_err(aw_dev->dev, "unsupported volume:%d", volume);
		return -EINVAL;
	}

	desc->init_volume = volume;
	aw_dev->ops.aw_set_volume(aw_dev, desc->init_volume);
	return 0;
}
#endif

#ifdef AW_IRQ
void aw883xx_dev_interrupt_clear(struct aw_device *aw_dev)
{
	uint16_t reg_val;

	aw_dev->ops.aw_i2c_read(aw_dev, aw_dev->sysst_desc.reg, &reg_val);
	aw_dev_info(aw_dev->dev,"reg SYSST=0x%x", reg_val);
	aw_dev->ops.aw_i2c_read(aw_dev, aw_dev->int_desc.st_reg, &reg_val);
	aw_dev_info(aw_dev->dev,"reg SYSINT=0x%x", reg_val);
	aw_dev->ops.aw_i2c_read(aw_dev, aw_dev->int_desc.mask_reg, &reg_val);
	aw_dev_info(aw_dev->dev,"reg SYSINTM=0x%x", reg_val);
}
#endif

void aw883xx_dev_soft_reset(struct aw_device *aw_dev)
{
	struct aw_soft_rst *reset = &aw_dev->soft_rst;

	aw_dev->ops.aw_i2c_write(aw_dev, reset->reg, reset->reg_value);
	aw_dev_info(aw_dev->dev, "soft reset done");
}

static uint64_t aw_dev_dsp_crc32_reflect(uint64_t ref, uint8_t ch)
{
	int i;
	uint64_t value = 0;

	for (i = 1; i < (ch + 1); i++) {
		if (ref & 1) {
			value |= 1 << (ch - i);
		}
		ref >>= 1;
	}
	return value;
}

static uint32_t aw_dev_calc_dsp_cfg_crc32(uint8_t *buf, uint32_t len)
{
	uint8_t i;
	uint32_t crc = 0xffffffff;

	while (len--) {
		for (i = 1; i != 0; i <<= 1) {
			if ((crc & 0x80000000) != 0) {
				crc <<= 1;
				crc ^= 0x1EDC6F41;
			} else {
				crc <<= 1;
			}

			if ((*buf & i) != 0) {
				crc ^= 0x1EDC6F41;
			}
		}
		buf++;
	}

	return (aw_dev_dsp_crc32_reflect(crc, 32)^0xffffffff);
}

static int aw_dev_set_dsp_crc32(struct aw_device *aw_dev)
{
	uint32_t crc_value;
	uint32_t crc_data_len = 0;
	int ret = -1;
	struct crc_dsp_cfg *crc_dsp_cfg = &aw_dev->crc_dsp_cfg;
	struct aw_dsp_crc_desc *desc = &aw_dev->dsp_crc_desc;

	/*get crc data len*/
	crc_data_len = (desc->dsp_reg - aw_dev->dsp_mem_desc.dsp_cfg_base_addr) * 2;
	if (crc_data_len > crc_dsp_cfg->len) {
		aw_dev_err(aw_dev->dev, "crc data len :%d > cfg_data len:%d",
			crc_data_len, crc_dsp_cfg->len);
		return ret;
	}

	if (crc_data_len % 4 != 0) {
		aw_dev_err(aw_dev->dev, "The crc data len :%d unsupport", crc_data_len);
		return ret;
	}

	crc_value = aw_dev_calc_dsp_cfg_crc32(crc_dsp_cfg->data, crc_data_len);

	aw_dev_info(aw_dev->dev, "crc_value:0x%x", crc_value);
	ret = aw_dev->ops.aw_dsp_write(aw_dev, desc->dsp_reg, crc_value,
						desc->data_type);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "set dsp crc value failed");
		return ret;
	}

	return 0;
}

static int aw_dev_dsp_crc_check_enable(struct aw_device *aw_dev, bool flag)
{
	struct aw_dsp_crc_desc *dsp_crc_desc = &aw_dev->dsp_crc_desc;
	int ret = -1;

	aw_dev_info(aw_dev->dev, "enter,flag:%d", flag);
	if (flag) {
		ret = aw_dev->ops.aw_reg_write_bits(aw_dev, dsp_crc_desc->ctl_reg,
				dsp_crc_desc->ctl_mask, dsp_crc_desc->ctl_enable);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "enable dsp crc failed");
			return ret;
		}
	} else {
		ret = aw_dev->ops.aw_reg_write_bits(aw_dev, dsp_crc_desc->ctl_reg,
				dsp_crc_desc->ctl_mask, dsp_crc_desc->ctl_disable);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "close dsp crc failed");
			return ret;
		}
	}

	return 0;
}

static int aw_dev_dsp_st_check(struct aw_device *aw_dev)
{
	struct aw_sysst_desc *desc = &aw_dev->sysst_desc;
	int ret = -1;
	uint16_t reg_val = 0;
	int i;

	for (i = 0; i < AW_DSP_ST_CHECK_MAX; i++) {
		ret = aw_dev->ops.aw_reg_read(aw_dev, desc->reg, &reg_val);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "read reg0x%x failed", desc->reg);
			continue;
		}

		if ((reg_val & (~desc->dsp_mask)) != desc->dsp_check) {
			aw_dev_err(aw_dev->dev, "check dsp st fail,reg_val:0x%04x", reg_val);
			ret= -EINVAL;
			continue;
		} else {
			aw_dev_info(aw_dev->dev, "dsp st check ok, reg_val:0x%04x", reg_val);
			return 0;
		}
	}

	return ret;
}

static int aw_dev_dsp_crc32_check(struct aw_device *aw_dev)
{
	int ret = -1;

	if (aw_dev->dsp_cfg == AW_DEV_DSP_BYPASS) {
		aw_dev_info(aw_dev->dev, "dsp bypass");
		return 0;
	}

	ret = aw_dev_set_dsp_crc32(aw_dev);
	if (ret < 0) {
		aw_dev_info(aw_dev->dev, "set dsp crc32 failed");
		return ret;
	}

	aw_dev_dsp_crc_check_enable(aw_dev, true);

	/*dsp enable*/
	aw883xx_dev_dsp_enable(aw_dev, true);
	AW_MS_DELAY(AW_5_MS);

	ret = aw_dev_dsp_st_check(aw_dev);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "check crc32 fail");
		return ret;
	}

	aw_dev_dsp_crc_check_enable(aw_dev, false);
	aw_dev->dsp_crc_st = AW_DSP_CRC_OK;
	return 0;
}

static void aw_dev_pwd(struct aw_device *aw_dev, bool pwd)
{
	struct aw_pwd_desc *pwd_desc = &aw_dev->pwd_desc;

	aw_dev_dbg(aw_dev->dev, "enter");

	if (pwd) {
		aw_dev->ops.aw_reg_write_bits(aw_dev, pwd_desc->reg,
				pwd_desc->mask,
				pwd_desc->enable);
	} else {
		aw_dev->ops.aw_reg_write_bits(aw_dev, pwd_desc->reg,
				pwd_desc->mask,
				pwd_desc->disable);
	}
	aw_dev_info(aw_dev->dev, "done");
}

static void aw_dev_amppd(struct aw_device *aw_dev, bool amppd)
{
	struct aw_amppd_desc *amppd_desc = &aw_dev->amppd_desc;

	aw_dev_dbg(aw_dev->dev, "enter");
	if (amppd) {
		aw_dev->ops.aw_reg_write_bits(aw_dev, amppd_desc->reg,
				amppd_desc->mask,
				amppd_desc->enable);
	} else {
		aw_dev->ops.aw_reg_write_bits(aw_dev, amppd_desc->reg,
				amppd_desc->mask,
				amppd_desc->disable);
	}
	aw_dev_info(aw_dev->dev, "done");
}

static void aw_dev_mute(struct aw_device *aw_dev, bool mute)
{
	struct aw_mute_desc *mute_desc = &aw_dev->mute_desc;

	aw_dev_dbg(aw_dev->dev, "enter");
	if (mute || (aw_dev->cali_desc.cali_result == CALI_RESULT_ERROR)) {
		aw_dev_fade_out(aw_dev);
		aw_dev->ops.aw_reg_write_bits(aw_dev, mute_desc->reg,
				mute_desc->mask, mute_desc->enable);
	} else {
		aw_dev->ops.aw_reg_write_bits(aw_dev, mute_desc->reg,
				mute_desc->mask, mute_desc->disable);
		aw_dev_fade_in(aw_dev);
	}
	aw_dev_info(aw_dev->dev, "done");
}

int aw883xx_dev_get_hmute(struct aw_device *aw_dev)
{
	uint16_t reg_val = 0;
	int ret = -1;
	struct aw_mute_desc *desc = &aw_dev->mute_desc;

	aw_dev_dbg(aw_dev->dev, "enter");

	ret = aw_dev->ops.aw_reg_read(aw_dev, desc->reg, &reg_val);
	if (ret < 0) {
		return ret;
	}
	if (reg_val & (~desc->mask)) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}

static int aw_dev_get_icalk(struct aw_device *aw_dev, int16_t *icalk)
{
	int ret = -1;
	uint16_t reg_val = 0;
	uint16_t reg_icalk = 0;
	struct aw_vcalb_desc *desc = &aw_dev->vcalb_desc;

	ret = aw_dev->ops.aw_reg_read(aw_dev, desc->icalk_reg, &reg_val);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "reg read failed");
		return ret;
	}

	reg_icalk = reg_val & (~desc->icalk_reg_mask);

	if (reg_icalk & (~desc->icalk_sign_mask)) {
		reg_icalk = reg_icalk | desc->icalk_neg_mask;
	}
	*icalk = (int16_t)reg_icalk;

	return 0;
}

static int aw_dev_get_vcalk(struct aw_device *aw_dev, int16_t *vcalk)
{
	int ret = -1;
	uint16_t reg_val = 0;
	uint16_t reg_vcalk = 0;
	struct aw_vcalb_desc *desc = &aw_dev->vcalb_desc;

	ret = aw_dev->ops.aw_reg_read(aw_dev, desc->vcalk_reg, &reg_val);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "reg read failed");
		return ret;
	}

	reg_val = reg_val >> desc->vcalk_shift;

	reg_vcalk = (uint16_t)reg_val & (~desc->vcalk_reg_mask);

	if (reg_vcalk & (~desc->vcalk_sign_mask)) {
		reg_vcalk = reg_vcalk | desc->vcalk_neg_mask;
	}
	*vcalk = (int16_t)reg_vcalk;

	return 0;
}

static int aw_dev_get_vcalk_dac(struct aw_device *aw_dev, int16_t *vcalk)
{
	int ret = -1;
	uint16_t reg_val = 0;
	uint16_t reg_vcalk = 0;
	struct aw_vcalb_desc *desc = &aw_dev->vcalb_desc;

	ret = aw_dev->ops.aw_reg_read(aw_dev, desc->icalk_reg, &reg_val);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "reg read failed");
		return ret;
	}

	reg_vcalk = reg_val >> desc->vcalk_dac_shift;

	if (reg_vcalk & desc->vcalk_dac_mask) {
		reg_vcalk = reg_vcalk | desc->vcalk_dac_neg_mask;
	}
	*vcalk = (int16_t)reg_vcalk;

	return 0;
}

int aw883xx_dev_modify_dsp_cfg(struct aw_device *aw_dev,
			unsigned int addr, uint32_t dsp_data, unsigned char data_type)
{
	uint32_t addr_offset = 0;
	int len = 0;
	uint8_t temp_data[4] = { 0 };
	struct crc_dsp_cfg *crc_dsp_cfg = &aw_dev->crc_dsp_cfg;

	aw_dev_dbg(aw_dev->dev, "addr:0x%x, dsp_data:0x%x", addr, dsp_data);
	if (data_type == AW_DSP_16_DATA) {
		temp_data[0] = (uint8_t)(dsp_data & 0x00ff);
		temp_data[1] = (uint8_t)((dsp_data & 0xff00) >> 8);
		len = 2;
	} else if (data_type == AW_DSP_32_DATA) {
		temp_data[0] = (uint8_t)(dsp_data & 0x000000ff);
		temp_data[1] = (uint8_t)((dsp_data & 0x0000ff00) >> 8);
		temp_data[2] = (uint8_t)((dsp_data & 0x00ff0000) >> 16);
		temp_data[3] = (uint8_t)((dsp_data & 0xff000000) >> 24);
		len = 4;
	} else {
		aw_dev_err(aw_dev->dev, "data type[%d] unsupported", data_type);
		return -EINVAL;
	}

	addr_offset = (addr - aw_dev->dsp_mem_desc.dsp_cfg_base_addr) * 2;
	if (addr_offset > crc_dsp_cfg->len) {
		aw_dev_err(aw_dev->dev, "addr_offset[%d] > crc_dsp_cfg->len[%d]",
				addr_offset, crc_dsp_cfg->len);
		return -EINVAL;
	}

	memcpy(crc_dsp_cfg->data + addr_offset, temp_data, len);
	return 0;
}

static int aw_dev_vsense_select(struct aw_device *aw_dev, int *vsense_select)
{
	int ret = -1;
	struct aw_vcalb_desc *desc = &aw_dev->vcalb_desc;
	uint16_t vsense_reg_val;

	ret = aw_dev->ops.aw_reg_read(aw_dev, desc->vcalb_vsense_reg, &vsense_reg_val);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "read vsense_reg_val failed");
		return ret;
	}
	aw_dev_dbg(aw_dev->dev, "vsense_reg = 0x%x", vsense_reg_val);

	if (vsense_reg_val & (~desc->vcalk_vdsel_mask)) {
		*vsense_select = AW_DEV_VDSEL_VSENSE;
		aw_dev_info(aw_dev->dev, "vsense outside");
		return 0;
	}

	*vsense_select = AW_DEV_VDSEL_DAC;
	aw_dev_info(aw_dev->dev, "vsense inside");
	return 0;
}

static int aw_dev_set_vcalb(struct aw_device *aw_dev)
{
	int ret = -1;
	uint32_t reg_val = 0;
	int vcalb;
	int icalk;
	int vcalk;
	int16_t icalk_val = 0;
	int16_t vcalk_val = 0;
	struct aw_vcalb_desc *desc = &aw_dev->vcalb_desc;
	uint32_t vcalb_adj;
	int vsense_select = -1;

	ret = aw_dev->ops.aw_dsp_read(aw_dev, desc->vcalb_dsp_reg, &vcalb_adj, desc->data_type);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "read vcalb_adj failed");
		return ret;
	}

	ret = aw_dev_vsense_select(aw_dev, &vsense_select);
	aw_dev_dbg(aw_dev->dev, "vsense_select = %d", vsense_select);
	if (ret < 0) {
		return ret;
	}

	ret = aw_dev_get_icalk(aw_dev, &icalk_val);
	icalk = desc->cabl_base_value + desc->icalk_value_factor * icalk_val;

	if (vsense_select == AW_DEV_VDSEL_VSENSE) {
		ret = aw_dev_get_vcalk(aw_dev, &vcalk_val);
		vcalk = desc->cabl_base_value + desc->vcalk_value_factor * vcalk_val;
		vcalb = desc->vcal_factor * desc->vscal_factor /
			desc->iscal_factor * icalk / vcalk * vcalb_adj;

		aw_dev_dbg(aw_dev->dev, "vcalk_factor=%d, vscal_factor=%d, icalk=%d, vcalk=%d",
				desc->vcalk_value_factor, desc->vscal_factor, icalk, vcalk);
	} else if (vsense_select == AW_DEV_VDSEL_DAC) {
		ret = aw_dev_get_vcalk_dac(aw_dev, &vcalk_val);
		vcalk = desc->cabl_base_value + desc->vcalk_value_factor_vsense_in * vcalk_val;
		vcalb = desc->vcal_factor * desc->vscal_factor_vsense_in /
			desc->iscal_factor * icalk / vcalk * vcalb_adj;

		aw_dev_dbg(aw_dev->dev, "vcalk_dac_factor=%d, vscal_dac_factor=%d, icalk=%d, vcalk=%d",
				desc->vcalk_value_factor_vsense_in, desc->vscal_factor_vsense_in, icalk, vcalk);
	} else {
		aw_dev_err(aw_dev->dev, "unsupport vsense status");
		return -EINVAL;
	}

	if ((vcalk == 0) || (desc->iscal_factor == 0)) {
		aw_dev_err(aw_dev->dev, "vcalk:%d or desc->iscal_factor:%d unsupported",
			vcalk, desc->iscal_factor);
		return -EINVAL;
	}

	vcalb = vcalb >> aw_dev->vcalb_desc.vcalb_adj_shift;
	reg_val = (uint32_t)vcalb;

	aw_dev_dbg(aw_dev->dev, "vcalb=%d, reg_val=0x%x, vcalb_adj =0x%x", vcalb, reg_val, vcalb_adj);

	ret = aw_dev->ops.aw_dsp_write(aw_dev, desc->vcalb_dsp_reg, reg_val, desc->data_type);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "write vcalb failed");
		return ret;
	}

	ret = aw883xx_dev_modify_dsp_cfg(aw_dev, desc->vcalb_dsp_reg,
					(uint32_t)reg_val, desc->data_type);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "modify dsp cfg failed");
		return ret;
	}

	aw_dev_info(aw_dev->dev, "done");

	return 0;
}

int aw883xx_dev_get_int_status(struct aw_device *aw_dev, uint16_t *int_status)
{
	int ret = -1;
	uint16_t reg_val = 0;

	ret = aw_dev->ops.aw_reg_read(aw_dev, aw_dev->int_desc.st_reg, &reg_val);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "read interrupt reg fail, ret=%d", ret);
	} else {
		*int_status = reg_val;
	}

	aw_dev_dbg(aw_dev->dev, "read interrupt reg = 0x%04x", *int_status);
	return ret;
}

void aw883xx_dev_clear_int_status(struct aw_device *aw_dev)
{
	uint16_t int_status = 0;

	/*read int status and clear*/
	aw883xx_dev_get_int_status(aw_dev, &int_status);
	/*make sure int status is clear*/
	aw883xx_dev_get_int_status(aw_dev, &int_status);
	aw_dev_info(aw_dev->dev, "done");
}

int aw883xx_dev_get_iis_status(struct aw_device *aw_dev)
{
	int ret = -1;
	uint16_t reg_val = 0;
	struct aw_sysst_desc *desc = &aw_dev->sysst_desc;

	aw_dev_dbg(aw_dev->dev, "enter");

	aw_dev->ops.aw_reg_read(aw_dev, desc->reg, &reg_val);
	if ((reg_val & desc->pll_check) == desc->pll_check) {
		ret = 0;
	} else {
		aw_dev_err(aw_dev->dev, "check pll lock fail,reg_val:0x%04x", reg_val);
	}
	return ret;
}


static int aw_dev_mode1_pll_check(struct aw_device *aw_dev)
{
	int ret = -1;
	uint16_t i = 0;

	for (i = 0; i < AW_DEV_SYSST_CHECK_MAX; i++) {
		ret = aw883xx_dev_get_iis_status(aw_dev);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "mode1 iis signal check error");
			AW_MS_DELAY(AW_2_MS);
		} else {
			return 0;
		}
	}

	return ret;
}

static int aw_dev_mode2_pll_check(struct aw_device *aw_dev)
{
	int ret = -1;
	uint16_t i = 0;
	uint16_t reg_val = 0;
	struct aw_cco_mux_desc *cco_mux_desc = &aw_dev->cco_mux_desc;

	aw_dev->ops.aw_reg_read(aw_dev, cco_mux_desc->reg, &reg_val);
	reg_val &= (~cco_mux_desc->mask);
	if (reg_val == cco_mux_desc->divider) {
		aw_dev_dbg(aw_dev->dev, "CCO_MUX is already divider");
		return ret;
	}

	/* change mode2 */
	aw_dev->ops.aw_reg_write_bits(aw_dev, cco_mux_desc->reg,
		cco_mux_desc->mask, cco_mux_desc->divider);

	for (i = 0; i < AW_DEV_SYSST_CHECK_MAX; i++) {
		ret = aw883xx_dev_get_iis_status(aw_dev);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "mode2 iis signal check error");
			AW_MS_DELAY(AW_2_MS);
		} else {
			break;
		}
	}

	/* change mode1*/
	aw_dev->ops.aw_reg_write_bits(aw_dev, cco_mux_desc->reg,
		cco_mux_desc->mask, cco_mux_desc->bypass);

	if (ret == 0) {
		AW_MS_DELAY(AW_2_MS);
		for (i = 0; i < AW_DEV_SYSST_CHECK_MAX; i++) {
			ret = aw_dev_mode1_pll_check(aw_dev);
			if (ret < 0) {
				aw_dev_err(aw_dev->dev, "mode2 switch to mode1, iis signal check error");
				AW_MS_DELAY(AW_2_MS);
			} else {
				break;
			}
		}
	}

	return ret;
}

int aw883xx_dev_syspll_check(struct aw_device *aw_dev)
{
	int ret = -1;

	ret = aw_dev_mode1_pll_check(aw_dev);
	if (ret < 0) {
		aw_dev_info(aw_dev->dev, "mode1 check iis failed try switch to mode2 check");
		ret = aw_dev_mode2_pll_check(aw_dev);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "mode2 check iis failed");
			return ret;
		}
	}

	return ret;
}

int aw883xx_dev_sysst_check(struct aw_device *aw_dev)
{
	int ret = -1;
	unsigned char i;
	uint16_t reg_val = 0;
	struct aw_sysst_desc *desc = &aw_dev->sysst_desc;

	for (i = 0; i < AW_DEV_SYSST_CHECK_MAX; i++) {
		aw_dev->ops.aw_reg_read(aw_dev, desc->reg, &reg_val);
		if (((reg_val & (~desc->st_mask)) & desc->st_check) == desc->st_check) {
			ret = 0;
			break;
		} else {
			aw_dev_dbg(aw_dev->dev, "check fail, cnt=%d, reg_val=0x%04x",
				i, reg_val);
			AW_MS_DELAY(AW_2_MS);
		}
	}
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "check fail");
	}
	return ret;
}

static int aw_dev_get_monitor_sysint_st(struct aw_device *aw_dev)
{
	int ret = 0;
	struct aw_int_desc *desc = &aw_dev->int_desc;

	if ((desc->intst_mask) & (desc->sysint_st)) {
		aw_dev_err(aw_dev->dev,
			"monitor check fail:0x%04x", desc->sysint_st);
		ret = -EINVAL;
	}
	desc->sysint_st = 0;

	return ret;
}

static int aw_dev_sysint_check(struct aw_device *aw_dev)
{
	int ret = 0;
	uint16_t reg_val = 0;
	struct aw_int_desc *desc = &aw_dev->int_desc;

	aw883xx_dev_get_int_status(aw_dev, &reg_val);

	if (reg_val & (desc->intst_mask)) {
		aw_dev_err(aw_dev->dev, "pa stop check fail:0x%04x", reg_val);
		ret = -EINVAL;
	}

	return ret;
}

static void aw_dev_get_cur_mode_st(struct aw_device *aw_dev)
{
	uint16_t reg_val;
	struct aw_profctrl_desc *profctrl_desc = &aw_dev->profctrl_desc;

	aw_dev->ops.aw_reg_read(aw_dev, aw_dev->pwd_desc.reg, &reg_val);

	if ((reg_val & (~profctrl_desc->mask)) == profctrl_desc->rcv_mode_val) {
		profctrl_desc->cur_mode = AW_RCV_MODE;
	} else {
		profctrl_desc->cur_mode = AW_NOT_RCV_MODE;
	}
}

int aw883xx_dev_set_intmask(struct aw_device *aw_dev, bool flag)
{
	int ret = -1;
	struct aw_int_desc *desc = &aw_dev->int_desc;

	if (flag) {
		ret = aw_dev->ops.aw_reg_write(aw_dev, desc->mask_reg,
					desc->int_mask);
	} else {
		ret = aw_dev->ops.aw_reg_write(aw_dev, desc->mask_reg,
					desc->mask_default);
	}

	aw_dev_info(aw_dev->dev, "done");
	return ret;
}

void aw883xx_dev_dsp_enable(struct aw_device *aw_dev, bool dsp)
{
	int ret = -1;
	struct aw_dsp_en_desc *desc = &aw_dev->dsp_en_desc;

	if (dsp) {
		ret = aw_dev->ops.aw_reg_write_bits(aw_dev, desc->reg,
					desc->mask, desc->enable);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "enable dsp failed");
		}
	} else {
		ret = aw_dev->ops.aw_reg_write_bits(aw_dev, desc->reg,
					desc->mask, desc->disable);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "disable dsp failed");
		}
	}

	aw_dev_info(aw_dev->dev, "done");
}

static int aw_dev_get_dsp_config(struct aw_device *aw_dev, unsigned char *dsp_cfg)
{
	int ret = -1;
	uint16_t reg_val = 0;
	struct aw_dsp_en_desc *desc = &aw_dev->dsp_en_desc;

	ret = aw_dev->ops.aw_reg_read(aw_dev, desc->reg, &reg_val);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "reg read failed");
		return ret;
	}

	if (reg_val & (~desc->mask)) {
		*dsp_cfg = AW_DEV_DSP_BYPASS;
	} else {
		*dsp_cfg = AW_DEV_DSP_WORK;
	}
	aw_dev_info(aw_dev->dev, "done");

	return 0;
}

static void aw_dev_memclk_select(struct aw_device *aw_dev, unsigned char flag)
{
	struct aw_memclk_desc *desc = &aw_dev->memclk_desc;
	int ret = -1;

	if (flag == AW_DEV_MEMCLK_PLL) {
		ret = aw_dev->ops.aw_reg_write_bits(aw_dev, desc->reg,
					desc->mask, desc->mcu_hclk);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "memclk select pll failed");
		}
	} else if (flag == AW_DEV_MEMCLK_OSC) {
		ret = aw_dev->ops.aw_reg_write_bits(aw_dev, desc->reg,
					desc->mask, desc->osc_clk);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "memclk select OSC failed");
		}
	} else {
		aw_dev_err(aw_dev->dev, "unknown memclk config, flag=0x%x", flag);
	}

	aw_dev_info(aw_dev->dev, "done");
}

int aw883xx_dev_get_dsp_status(struct aw_device *aw_dev)
{
	int ret = -1;
	uint16_t reg_val = 0;
	struct aw_watch_dog_desc *desc = &aw_dev->watch_dog_desc;

	aw_dev_info(aw_dev->dev, "enter");

	aw_dev->ops.aw_reg_read(aw_dev, desc->reg, &reg_val);
	if (reg_val & (~desc->mask)) {
		ret = 0;
	}
	return ret;
}

static int aw_dev_get_vmax(struct aw_device *aw_dev, unsigned int *vmax)
{
	int ret = -1;
	struct aw_vmax_desc *desc = &aw_dev->vmax_desc;

	ret = aw_dev->ops.aw_dsp_read(aw_dev, desc->dsp_reg, vmax, desc->data_type);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "get vmax failed");
		return ret;
	}

	return 0;
}

static int aw_dev_get_cali_f0_delay(struct aw_device *aw_dev)
{
	struct aw_cali_delay_desc *desc = &aw_dev->cali_delay_desc;
	uint32_t cali_delay = 0;
	int ret = -1;

	ret = aw_dev->ops.aw_dsp_read(aw_dev,
			desc->dsp_reg, &cali_delay, desc->data_type);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "read cali delay failed, ret=%d", ret);
		return ret;
	}

	desc->delay = AW_CALI_DELAY_CACL(cali_delay);
	aw_dev_info(aw_dev->dev, "read cali delay: %d ms", desc->delay);

	return 0;
}

/******************************************************
 *
 * aw_dev update cfg
 *
 ******************************************************/

/*pwd enable update reg*/

static int aw_dev_reg_container_update(struct aw_device *aw_dev,
				const uint8_t *data, uint32_t len)
{
	int i;
	int ret = -1;
	uint8_t reg_addr = 0;
	uint16_t reg_val = 0;
	uint16_t read_val;
	struct aw_int_desc *int_desc = &aw_dev->int_desc;
	uint16_t *reg_data = NULL;
	int data_len;

	aw_dev_dbg(aw_dev->dev, "enter");
	reg_data = (uint16_t *)data;
	data_len = len >> 1;

	if (data_len % 2 != 0) {
		aw_dev_err(aw_dev->dev, "data len:%d unsupported",
				data_len);
		return -EINVAL;
	}

	for (i = 0; i < data_len; i += 2) {
		reg_addr = reg_data[i];
		reg_val = reg_data[i + 1];
		aw_dev_dbg(aw_dev->dev, "reg = 0x%02x, val = 0x%04x",
				reg_addr, reg_val);
		if (reg_addr == int_desc->mask_reg) {
			int_desc->int_mask = reg_val;
			reg_val = int_desc->mask_default;
		}
		if (reg_addr == aw_dev->mute_desc.reg) {
			aw_dev->ops.aw_reg_read(aw_dev, reg_addr, &read_val);
			read_val &= (~aw_dev->mute_desc.mask);
			reg_val &= aw_dev->mute_desc.mask;
			reg_val |= read_val;
		}
		if (reg_addr == aw_dev->dsp_crc_desc.ctl_reg) {
			reg_val &= aw_dev->dsp_crc_desc.ctl_mask;
		}

		ret = aw_dev->ops.aw_reg_write(aw_dev, reg_addr, reg_val);
		if (ret < 0) {
			break;
		}
	}

	aw_dev_get_cur_mode_st(aw_dev);

	aw_dev->ops.aw_get_volume(aw_dev, (uint16_t *)&aw_dev->volume_desc.init_volume);

	/*keep min volume*/
	if (aw_dev->fade_en) {
		aw_dev->ops.aw_set_volume(aw_dev, aw_dev->volume_desc.mute_volume);
	}
	aw_dev_get_dsp_config(aw_dev, &aw_dev->dsp_cfg);

	aw_dev_dbg(aw_dev->dev, "exit");

	return ret;
}


static int aw_dev_reg_update(struct aw_device *aw_dev)
{
	struct aw_sec_data_desc *reg_data = NULL;
	reg_data = aw883xx_dev_get_prof_data_byname(aw_dev, aw_dev->set_prof_name, AW_DATA_TYPE_REG);

	if (reg_data == NULL){
		aw_dev_err(aw_dev->dev, "reg data is null");
		return -EINVAL;
	}

	aw_dev_reg_container_update(aw_dev, reg_data->data, reg_data->len);

	aw_dev_dbg(aw_dev->dev, "reg len:%d", reg_data->len);

	return 0;
}

static int aw_dev_dsp_container_update(struct aw_device *aw_dev,
			const uint8_t *dsp_data, uint32_t len, uint16_t base)
{
	int i;
	struct aw_dsp_mem_desc *dsp_mem_desc = &aw_dev->dsp_mem_desc;
	uint8_t *data = NULL;
	data = (uint8_t *)dsp_data;

#ifdef AW_DSP_I2C_WRITES
	uint32_t tmp_len = 0;
#else
	uint16_t reg_val = 0;
#endif

	aw_dev_dbg(aw_dev->dev, "enter");
	aw_mutex_lock();
#ifdef AW_DSP_I2C_WRITES
	/* i2c writes */
	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_madd_reg, base);

	for (i = 0; i < len; i += AW_MAX_RAM_WRITE_BYTE_SIZE) {
		if ((len - i) < AW_MAX_RAM_WRITE_BYTE_SIZE) {
			tmp_len = len - i;
		} else {
			tmp_len = AW_MAX_RAM_WRITE_BYTE_SIZE;
		}
		aw_dev->ops.aw_i2c_writes(aw_dev, dsp_mem_desc->dsp_mdat_reg,
					&data[i], tmp_len);
	}

#else
	/* i2c write */
	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_madd_reg, base);

	for (i = 0; i < len; i += 2) {
		reg_val = (data[i] << 8) + data[i + 1];
		aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_mdat_reg,
					reg_val);
	}
#endif

	aw_mutex_unlock();
	aw_dev_dbg(aw_dev->dev, "exit");

	return 0;
}

static int aw_dev_dsp_fw_update(struct aw_device *aw_dev)
{
	struct aw_dsp_mem_desc *dsp_mem_desc = &aw_dev->dsp_mem_desc;
	struct aw_sec_data_desc *dsp_fw_data = NULL;

	dsp_fw_data = aw883xx_dev_get_prof_data_byname(aw_dev, aw_dev->set_prof_name, AW_DATA_TYPE_DSP_FW);

	if (dsp_fw_data == NULL) {
		aw_dev_err(aw_dev->dev, "dsp firmware data is null");
		return -EINVAL;
	}

	aw_dev_dsp_container_update(aw_dev, dsp_fw_data->data,
					dsp_fw_data->len, dsp_mem_desc->dsp_fw_base_addr);
	aw_dev->dsp_fw_len = dsp_fw_data->len;
	aw_dev_dbg(aw_dev->dev, "dsp firmware len:%d", dsp_fw_data->len);

	return 0;
}

static int aw_dev_copy_to_crc_dsp_cfg(struct aw_device *aw_dev,
			const uint8_t *data, uint32_t size)
{
	struct crc_dsp_cfg *crc_dsp_cfg = &aw_dev->crc_dsp_cfg;
	int ret = -1;

	aw_dev_dbg(aw_dev->dev, "enter");

	if (crc_dsp_cfg->data == NULL) {
		crc_dsp_cfg->data = pvPortMalloc(size);
		if (!crc_dsp_cfg->data) {
			aw_dev_err(aw_dev->dev, "error allocating memory");
			return -ENOMEM;
		}
		crc_dsp_cfg->len = size;
	} else if (crc_dsp_cfg->len < size) {
		vPortFree(crc_dsp_cfg->data);
		crc_dsp_cfg->data = NULL;
		crc_dsp_cfg->data = pvPortMalloc(size);
		if (!crc_dsp_cfg->data) {
			aw_dev_err(aw_dev->dev, "error allocating memory");
		}
	}

	memcpy(crc_dsp_cfg->data, data ,size);
	ret = aw_dev_dsp_data_order(aw_dev, crc_dsp_cfg->data, size);
	if (ret < 0) {
		return ret;
	}
	return 0;
}

static int aw_dev_dsp_cfg_update(struct aw_device *aw_dev)
{
	struct aw_dsp_mem_desc *dsp_mem_desc = &aw_dev->dsp_mem_desc;
	struct aw_sec_data_desc *dsp_cfg_data = NULL;
	int ret = -1;

	dsp_cfg_data = aw883xx_dev_get_prof_data_byname(aw_dev, aw_dev->set_prof_name, AW_DATA_TYPE_DSP_CFG);

	if (dsp_cfg_data == NULL) {
		aw_dev_err(aw_dev->dev, "dsp config data is null");
		return -EINVAL;
	}

	aw_dev_dsp_container_update(aw_dev,
			dsp_cfg_data->data, dsp_cfg_data->len, dsp_mem_desc->dsp_cfg_base_addr);
	aw_dev->dsp_cfg_len = dsp_cfg_data->len;
	aw_dev_dbg(aw_dev->dev, "dsp config len:%d", dsp_cfg_data->len);

	ret = aw_dev_copy_to_crc_dsp_cfg(aw_dev, dsp_cfg_data->data, dsp_cfg_data->len);
	if (ret < 0) {
			return ret;
	}
	aw_dev_set_vcalb(aw_dev);
#ifdef AW_CALIB
	aw883xx_cali_svc_get_ra((void *)aw_dev);
	aw_dev_get_cali_f0_delay(aw_dev);
#endif

#ifdef AW_MONITOR
	if (aw_dev->ops.aw_get_hw_mon_st) {
		ret = aw_dev->ops.aw_get_hw_mon_st(aw_dev,
				&aw_dev->monitor_desc.hw_mon_en,
				&aw_dev->monitor_desc.hw_temp_flag);
		if (ret < 0) {
			return ret;
		}
	}
#endif

	ret = aw_dev_get_vmax(aw_dev, &aw_dev->vmax_desc.init_vmax);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "get vmax failed");
		return ret;
	} else {
		aw_dev_info(aw_dev->dev, "get init vmax:0x%x",
					aw_dev->vmax_desc.init_vmax);
	}

	aw_dev->dsp_crc_st = AW_DSP_CRC_NA;

	return 0;
}

static int aw_dev_sram_check(struct aw_device *aw_dev)//fyy
{
	int ret = -1;
	uint16_t reg_val = 0;
	struct aw_dsp_mem_desc *dsp_mem_desc = &aw_dev->dsp_mem_desc;

	aw_mutex_lock();
	/*check the odd bits of reg 0x40*/
	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_madd_reg,
					AW_DSP_ODD_NUM_BIT_TEST);
	aw_dev->ops.aw_i2c_read(aw_dev, dsp_mem_desc->dsp_madd_reg, &reg_val);
	if (AW_DSP_ODD_NUM_BIT_TEST != reg_val) {
		aw_dev_err(aw_dev->dev, "check reg 0x40 odd bit failed, read[0x%x] does not match write[0x%x]",
				reg_val, AW_DSP_ODD_NUM_BIT_TEST);
		goto error;
	}

	/*check the even bits of reg 0x40*/
	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_madd_reg,
					AW_DSP_EVEN_NUM_BIT_TEST);
	aw_dev->ops.aw_i2c_read(aw_dev, dsp_mem_desc->dsp_madd_reg, &reg_val);
	if (AW_DSP_EVEN_NUM_BIT_TEST != reg_val) {
		aw_dev_err(aw_dev->dev, "check reg 0x40 even bit failed, read[0x%x] does not match write[0x%x]",
				reg_val, AW_DSP_EVEN_NUM_BIT_TEST);
		goto error;
	}

	/*check dsp_fw_base_addr*/
	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_madd_reg,
					dsp_mem_desc->dsp_fw_base_addr);
	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_mdat_reg,
					AW_DSP_EVEN_NUM_BIT_TEST);

	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_madd_reg,
					dsp_mem_desc->dsp_fw_base_addr);
	aw_dev->ops.aw_i2c_read(aw_dev, dsp_mem_desc->dsp_mdat_reg, &reg_val);
	if (AW_DSP_EVEN_NUM_BIT_TEST != reg_val) {
		aw_dev_err(aw_dev->dev, "check dsp fw addr failed, read[0x%x] does not match write[0x%x]",
						reg_val, AW_DSP_EVEN_NUM_BIT_TEST);
		goto error;
	}

	/*check dsp_cfg_base_addr*/
	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_madd_reg,
					dsp_mem_desc->dsp_cfg_base_addr);
	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_mdat_reg,
					AW_DSP_ODD_NUM_BIT_TEST);

	aw_dev->ops.aw_i2c_write(aw_dev, dsp_mem_desc->dsp_madd_reg,
					dsp_mem_desc->dsp_cfg_base_addr);
	aw_dev->ops.aw_i2c_read(aw_dev, dsp_mem_desc->dsp_mdat_reg, &reg_val);
	if (AW_DSP_ODD_NUM_BIT_TEST != reg_val) {
		aw_dev_err(aw_dev->dev, "check dsp cfg failed, read[0x%x] does not match write[0x%x]",
						reg_val, AW_DSP_ODD_NUM_BIT_TEST);
		goto error;
	}
	aw_mutex_unlock();
	return 0;

error:
	aw_mutex_unlock();
	return ret;
}

int aw883xx_dev_fw_update(struct aw_device *aw_dev, bool up_dsp_fw_en, bool force_up_en)
{
	int ret = -1;

	aw_dev_info(aw_dev->dev, "enter ");

	if ((strncmp(aw_dev->cur_prof_name, aw_dev->set_prof_name, AW_PROF_NAME_MAX) == 0) &&
			(force_up_en == AW_FORCE_UPDATE_OFF)) {
		aw_dev_info(aw_dev->dev, "scene no change, not update");
		return 0;
	}

	/*update reg*/
	ret = aw_dev_reg_update(aw_dev);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "update reg failed");
		return ret;
	}

	aw_dev_mute(aw_dev, true);

	if (aw_dev->dsp_cfg == AW_DEV_DSP_WORK) {
		aw883xx_dev_dsp_enable(aw_dev, false);
	}

	aw_dev_memclk_select(aw_dev, AW_DEV_MEMCLK_OSC);

	if (up_dsp_fw_en) {
		ret = aw_dev_sram_check(aw_dev);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "check sram failed");
			goto error;
		}

		/*update dsp firmware*/
		ret = aw_dev_dsp_fw_update(aw_dev);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "update dsp fw failed");
			goto error;
		}
	}

	/*update dsp config*/
	ret = aw_dev_dsp_cfg_update(aw_dev);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "update dsp cfg failed");
		goto error;
	}

	aw_dev_memclk_select(aw_dev, AW_DEV_MEMCLK_PLL);

	strncpy(aw_dev->cur_prof_name, aw_dev->set_prof_name, AW_PROF_NAME_MAX);

	aw_dev_info(aw_dev->dev, "load [%s] done", aw_dev->cur_prof_name);
	return 0;

error:
	aw_dev_memclk_select(aw_dev, AW_DEV_MEMCLK_PLL);

	return ret;
}

static int aw883xx_dev_dsp_check(struct aw_device *aw_dev)
{
	int ret = -1;
	uint16_t i = 0;

	aw_dev_dbg(aw_dev->dev, "enter");

	if (aw_dev->dsp_cfg == AW_DEV_DSP_BYPASS) {
		aw_dev_dbg(aw_dev->dev, "dsp bypass");
		return 0;
	} else if (aw_dev->dsp_cfg == AW_DEV_DSP_WORK) {
		for (i = 0; i < AW_DEV_DSP_CHECK_MAX; i++) {
			aw883xx_dev_dsp_enable(aw_dev, false);
			aw883xx_dev_dsp_enable(aw_dev, true);
			AW_MS_DELAY(AW_1_MS);
			ret = aw883xx_dev_get_dsp_status(aw_dev);
			if (ret < 0) {
				aw_dev_err(aw_dev->dev, "dsp wdt status error=%d", ret);
				AW_MS_DELAY(AW_2_MS);
			} else {
				return 0;
			}
		}
	} else {
		aw_dev_err(aw_dev->dev, "unknown dsp cfg=%d", aw_dev->dsp_cfg);
		return -EINVAL;
	}

	return -EINVAL;
}

static int aw_dev_set_cfg_f0_fs(struct aw_device *aw_dev)
{
	uint32_t f0_fs = 0;
	struct aw_cfgf0_fs_desc *cfgf0_fs_desc = &aw_dev->cfgf0_fs_desc;
	int ret = -1;

	if (aw_dev->ops.aw_set_cfg_f0_fs) {
		aw_dev->ops.aw_set_cfg_f0_fs(aw_dev, &f0_fs);
		ret = aw883xx_dev_modify_dsp_cfg(aw_dev, cfgf0_fs_desc->dsp_reg,
					f0_fs, cfgf0_fs_desc->data_type);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "modify dsp cfg failed");
			return ret;
		}
	}
	return 0;
}

#ifdef AW_CALIB
static void aw_dev_cali_re_update(struct aw_device *aw_dev)
{
	if (AW_ERRO_CALI_RE_VALUE != aw_dev->cali_desc.cali_re) {
		aw883xx_cali_svc_set_cali_re_to_dsp((void *)aw_dev);
	} else {
		aw_dev_err(aw_dev->dev, "cali_re:%d is error, no set",
				aw_dev->cali_desc.cali_re);
	}
}
#endif

int aw883xx_device_start(struct aw_device *aw_dev)
{
	int ret = -1;

	aw_dev_info(aw_dev->dev, "enter");

	if (aw_dev->status == AW_DEV_PW_ON) {
		aw_dev_info(aw_dev->dev, "already power on");
		return 0;
	}

	/*power on*/
	aw_dev_pwd(aw_dev, false);
	AW_MS_DELAY(AW_2_MS);

	ret = aw883xx_dev_syspll_check(aw_dev);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "pll check failed cannot start");
		aw883xx_dev_reg_dump(aw_dev);
		goto pll_check_fail;
	}

	/*amppd on*/
	aw_dev_amppd(aw_dev, false);
	AW_MS_DELAY(AW_1_MS);

	/*check i2s status*/
	ret = aw883xx_dev_sysst_check(aw_dev);
	if (ret < 0) {
		/*check failed*/
		aw883xx_dev_reg_dump(aw_dev);
		goto sysst_check_fail;
	}

	if (aw_dev->dsp_cfg == AW_DEV_DSP_WORK) {
		/*dsp bypass*/
		aw883xx_dev_dsp_enable(aw_dev, false);
		if (aw_dev->ops.aw_dsp_fw_check) {
			ret = aw_dev->ops.aw_dsp_fw_check(aw_dev);
			if (ret < 0) {
				aw883xx_dev_reg_dump(aw_dev);
				goto dsp_fw_check_fail;
			}
		}

		aw_dev_set_cfg_f0_fs(aw_dev);
#ifdef AW_CALIB
		aw_dev_cali_re_update(aw_dev);
#endif
		if (aw_dev->dsp_crc_st != AW_DSP_CRC_OK) {
			ret = aw_dev_dsp_crc32_check(aw_dev);
			if (ret < 0) {
				aw_dev_err(aw_dev->dev, "dsp crc check failed");
				aw883xx_dev_reg_dump(aw_dev);
				goto crc_check_fail;
			}
		}

		ret = aw883xx_dev_dsp_check(aw_dev);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "check dsp status failed");
			aw883xx_dev_reg_dump(aw_dev);
			goto dsp_check_fail;
		}
	} else {
		aw_dev_dbg(aw_dev->dev, "start pa with dsp bypass");
	}

	/*enable tx feedback*/
	if (aw_dev->ops.aw_i2s_tx_enable) {
		aw_dev->ops.aw_i2s_tx_enable(aw_dev, true);
	}

	/*close mute*/
	aw_dev_mute(aw_dev, false);

	/*clear inturrupt*/
	aw883xx_dev_clear_int_status(aw_dev);
	/*set inturrupt mask*/
	aw883xx_dev_set_intmask(aw_dev, true);

	if (aw_dev->ops.aw_monitor_start) {
		aw_dev->ops.aw_monitor_start((void *)aw_dev);
	}

	aw_dev->status = AW_DEV_PW_ON;

	aw_dev_info(aw_dev->dev, "done");

	return 0;

dsp_check_fail:
crc_check_fail:
	aw883xx_dev_dsp_enable(aw_dev, false);
dsp_fw_check_fail:
sysst_check_fail:
	/*clear interrupt*/
	aw883xx_dev_clear_int_status(aw_dev);
	aw_dev_amppd(aw_dev, true);
pll_check_fail:
	aw_dev_pwd(aw_dev, true);
	aw_dev->status = AW_DEV_PW_OFF;
	return ret;
}

int aw883xx_device_stop(struct aw_device *aw_dev)
{
	int int_st = 0;
	int monitor_int_st = 0;

	aw_dev_info(aw_dev->dev, "enter");

	if (aw_dev->status == AW_DEV_PW_OFF) {
		aw_dev_info(aw_dev->dev, "already power off");
		return 0;
	}

	aw_dev->status = AW_DEV_PW_OFF;

	if (aw_dev->ops.aw_monitor_stop) {
		aw_dev->ops.aw_monitor_stop((void *)aw_dev);
	}

	/*set mute*/
	aw_dev_mute(aw_dev, true);
	AW_MS_DELAY(AW_4_MS);

	/*close tx feedback*/
	if (aw_dev->ops.aw_i2s_tx_enable) {
		aw_dev->ops.aw_i2s_tx_enable(aw_dev, false);
	}
	AW_MS_DELAY(AW_1_MS);

	/*set defaut int mask*/
	aw883xx_dev_set_intmask(aw_dev, false);

	/*check sysint state*/
	int_st = aw_dev_sysint_check(aw_dev);

	/*close dsp*/
	aw883xx_dev_dsp_enable(aw_dev, false);

	/*enable amppd*/
	aw_dev_amppd(aw_dev, true);

	/*check monitor process sysint state*/
	monitor_int_st = aw_dev_get_monitor_sysint_st(aw_dev);

	if (int_st < 0 || monitor_int_st < 0) {
		/*system status anomaly*/
		aw_dev_memclk_select(aw_dev, AW_DEV_MEMCLK_OSC);
		aw_dev_dsp_cfg_update(aw_dev);
		aw_dev_dsp_fw_update(aw_dev);
		aw_dev_memclk_select(aw_dev, AW_DEV_MEMCLK_PLL);
	}

	/*set power down*/
	aw_dev_pwd(aw_dev, true);

	aw_dev_info(aw_dev->dev, "done");
	return 0;
}

static int aw_device_init(struct aw_device *aw_dev)
{
	int ret = -1;

	if (aw_dev == NULL) {
		aw_pr_err("aw_dev is NULL");
		return -ENOMEM;
	}

	strncpy(aw_dev->cur_prof_name, aw_dev->first_prof_name, AW_PROF_NAME_MAX);
	strncpy(aw_dev->set_prof_name, aw_dev->first_prof_name, AW_PROF_NAME_MAX);

	ret = aw883xx_dev_fw_update(aw_dev, AW_FORCE_UPDATE_ON,
			AW_DSP_FW_UPDATE_ON);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "fw update failed");
		return ret;
	}

	aw883xx_dev_set_intmask(aw_dev, false);

	/*set mute*/
	aw_dev_mute(aw_dev, true);

	/*close tx feedback*/
	if (aw_dev->ops.aw_i2s_tx_enable) {
		aw_dev->ops.aw_i2s_tx_enable(aw_dev, false);
	}
	AW_MS_DELAY(AW_1_MS);

	/*enable amppd*/
	aw_dev_amppd(aw_dev, true);
	/*close dsp*/
	aw883xx_dev_dsp_enable(aw_dev, false);
	/*set power down*/
	aw_dev_pwd(aw_dev, true);

	aw_dev_info(aw_dev->dev, "init done");

	return 0;
}

int aw883xx_device_probe(struct aw_device *aw_dev, struct aw_init_info *init_info)
{
	int ret = -1;

	ret = aw_dev_prof_init(aw_dev, init_info);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "prof init failed");
		return ret;
	}

	aw883xx_dev_get_monitor_func(aw_dev);

	if(aw_dev->ops.aw_monitor_init) {
		ret = aw_dev->ops.aw_monitor_init((void *)aw_dev);
		if (ret < 0) {
			aw_dev_err(aw_dev->dev, "monitor init failed");
			return ret;
		}
	}

	ret = aw_device_init(aw_dev);
	if (ret < 0) {
		aw_dev_err(aw_dev->dev, "dev init failed");
		return ret;
	}

	return 0;
}

