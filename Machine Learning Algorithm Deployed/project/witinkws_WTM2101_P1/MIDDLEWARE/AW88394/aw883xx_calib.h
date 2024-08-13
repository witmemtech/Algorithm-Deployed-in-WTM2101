#ifndef __AWINIC_CALIBRATION_H__
#define __AWINIC_CALIBRATION_H__

#include "stdint.h"
#include "aw883xx_base.h"

#define AW_CALI_STORE_EXAMPLE
#define AW_ERRO_CALI_RE_VALUE (0)
#define AW_ERRO_CALI_F0_VALUE (2600)

#define AW_CALI_RE_DEFAULT_TIMER (3000)
#define MSGS_SIZE (512)
#define RESERVED_SIZE (252)


#define AW_CALI_ALL_DEV (0xFFFFFFFF)

#define AW_CALI_RE_MAX (15000)
#define AW_CALI_RE_MIN (4000)
#define AW_CALI_CFG_NUM (4)
#define AW_CALI_F0_DATA_NUM (4)
#define AW_CALI_READ_CNT_MAX (8)
#define AW_CALI_DATA_SUM_RM (2)
#define AW_DSP_RE_TO_SHOW_RE(re, shift) (((re) * (1000)) >> (shift))
#define AW_SHOW_RE_TO_DSP_RE(re, shift)  (((re) << shift) / (1000))
#define AW_CALI_F0_TIME (5 * 1000)
#define F0_READ_CNT_MAX (5)
#define AW_FS_CFG_MAX	(11)
#define AW_DEV_CH_MAX	(16)
#define AW_DEV_RE_RANGE	(RE_RANGE_NUM * AW_DEV_CH_MAX)
#define AW_TE_CACL_VALUE(te, coil_alpha) (int32_t)(((int32_t)te << 18) / (coil_alpha))
#define AW_RE_REALTIME_VALUE(re_cacl, te_cacl) ((re_cacl) + (int32_t)((int64_t)((te_cacl) * (re_cacl)) >> 14))

enum {
	CALI_CHECK_DISABLE = 0,
	CALI_CHECK_ENABLE = 1,
};

enum {
	CALI_RESULT_NONE = 0,
	CALI_RESULT_NORMAL = 1,
	CALI_RESULT_ERROR = -1,
};

enum {
	CALI_OPS_HMUTE = 0X0001,
	CALI_OPS_NOISE = 0X0002,
};

enum {
	CALI_TYPE_RE = 0,
	CALI_TYPE_F0,
};

enum {
	GET_RE_TYPE = 0,
	GET_F0_TYPE,
	GET_Q_TYPE,
};

enum {
	RE_MIN_FLAG = 0,
	RE_MAX_FLAG = 1,
	RE_RANGE_NUM = 2,
};

struct re_data {
	uint32_t re_range[2];
};

struct cali_cfg {
	uint32_t data[AW_CALI_CFG_NUM];
};

struct aw_cali_desc {
	bool status;
	struct cali_cfg cali_cfg;
	uint16_t store_vol;
	uint32_t cali_re;	/*cali value*/
	uint32_t re;
	uint32_t f0;
	uint32_t q;
	uint32_t ra;
	int8_t cali_result;
	unsigned char cali_check_st;
};

bool aw883xx_cali_svc_get_cali_status(struct aw_cali_desc *cali_desc);
int aw883xx_cali_svc_set_cali_re_to_dsp(void *dev);
int aw883xx_cali_svc_get_ra(void *dev);

int aw883xx_dev_cali_re(void *dev, aw_single_t is_single);
int aw883xx_dev_cali_f0_q(void *dev, aw_single_t is_single);
int aw883xx_dev_cali_re_f0(void *dev, aw_single_t is_single);

int aw883xx_dev_get_re_range(void *dev, aw_single_t is_single, uint32_t *range_buf);
int aw883xx_dev_get_r0(void *dev, aw_single_t is_single, uint32_t *r0_data);
int aw883xx_dev_get_f0(void *dev, aw_single_t is_single, uint32_t *f0);
int aw883xx_dev_get_te(void *dev, aw_single_t is_single, int32_t *te_data);

int aw883xx_dev_cali_f0_show(void *dev, aw_single_t is_single, uint32_t *f0);
int aw883xx_dev_cali_q_show(void *dev, aw_single_t is_single, uint32_t *q);
int aw883xx_dev_cali_re_show(void *dev, aw_single_t is_single, uint32_t *re);
int aw883xx_dev_cali_re_store(void *dev, aw_single_t is_single, uint32_t *set_re);
int aw883xx_dev_read_re_from_dsp(void *dev, uint32_t *re);

int aw883xx_dev_cali_time_store(uint32_t time);
void aw883xx_dev_cali_time_show(uint32_t *time);

#endif


