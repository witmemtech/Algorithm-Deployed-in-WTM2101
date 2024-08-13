#ifndef __AWINIC_DEVICE_FILE_H__
#define __AWINIC_DEVICE_FILE_H__


#include "aw883xx_base.h"
#include "aw883xx_init.h"
#include "aw_profile_process.h"
#include "aw883xx_calib.h"

#ifdef AW_MONITOR
#include "aw883xx_monitor.h"
#endif

#define AW_DEV_DEFAULT_CH			(0)
#define AW_DEV_I2S_CHECK_MAX	(5)
#define AW_DEV_DSP_CHECK_MAX	(5)
#define AW_PROF_NAME_MAX 			(50)

/********************************************
 *
 * DSP I2C WRITES
 *
 *******************************************/
#define AW_DSP_I2C_WRITES
#define AW_MAX_RAM_WRITE_BYTE_SIZE	(128)
#define AW_DSP_ODD_NUM_BIT_TEST		(0x5555)
#define AW_DSP_EVEN_NUM_BIT_TEST	(0xAAAA)
#define AW_DSP_ST_CHECK_MAX		(2)
#define AW_FADE_IN_OUT_DEFAULT		(0)
#define AW_REG_NONE		(0xFF)
#define AW_CALI_DELAY_CACL(value) ((value * 32) / 48)

enum {
	AW_1_MS = 1,
	AW_2_MS = 2,
	AW_3_MS = 3,
	AW_4_MS = 4,
	AW_5_MS = 5,
	AW_10_MS = 10,
	AW_30_MS = 30,
};

struct aw_device;

enum {
	AW_DEV_VDSEL_DAC = 0,
	AW_DEV_VDSEL_VSENSE = 1,
};

enum {
	AW_DSP_CRC_NA = 0,
	AW_DSP_CRC_OK = 1,
};

enum {
	AW_DSP_CRC_DISABLE = 0,
	AW_DSP_CRC_ENABLE = 1,
};

enum {
	AW_DSP_FW_UPDATE_OFF = 0,
	AW_DSP_FW_UPDATE_ON = 1,
};

enum {
	AW_FORCE_UPDATE_OFF = 0,
	AW_FORCE_UPDATE_ON = 1,
};

enum {
	AW_1000_US = 1000,
	AW_2000_US = 2000,
	AW_3000_US = 3000,
	AW_4000_US = 4000,
	AW_5000_US = 5000,
	AW_10000_US = 10000,
};

enum {
	AW_DEV_TYPE_OK = 0,
	AW_DEV_TYPE_NONE = 1,
};


enum AW_DEV_STATUS {
	AW_DEV_PW_OFF = 0,
	AW_DEV_PW_ON,
};

enum AW_DEV_FW_STATUS {
	AW_DEV_FW_FAILED = 0,
	AW_DEV_FW_OK,
};

enum AW_DEV_MEMCLK {
	AW_DEV_MEMCLK_OSC = 0,
	AW_DEV_MEMCLK_PLL = 1,
};

enum AW_DEV_DSP_CFG {
	AW_DEV_DSP_WORK = 0,
	AW_DEV_DSP_BYPASS = 1,
};

enum {
	AW_DSP_16_DATA = 0,
	AW_DSP_32_DATA = 1,
};

enum aw_platform {
	AW_QCOM = 0,
	AW_MTK = 1,
	AW_SPRD = 2,
};

enum {
	AW_NOT_RCV_MODE = 0,
	AW_RCV_MODE = 1,
};

struct aw_device_ops {
	int (*aw_i2c_writes)(struct aw_device *aw_dev, uint8_t reg_addr, uint8_t *buf, uint16_t len);
	int (*aw_i2c_write)(struct aw_device *aw_dev, uint8_t reg_addr, uint16_t reg_data);
	int (*aw_i2c_read)(struct aw_device *aw_dev, uint8_t reg_addr, uint16_t *reg_data);

	int (*aw_reg_write)(struct aw_device *aw_dev, uint8_t reg_addr, uint16_t reg_data);
	int (*aw_reg_read)(struct aw_device *aw_dev, uint8_t reg_addr, uint16_t *reg_data);
	int (*aw_reg_write_bits)(struct aw_device *aw_dev, uint8_t reg_addr, uint16_t mask, uint16_t reg_data);

	int (*aw_dsp_write)(struct aw_device *aw_dev, uint16_t dsp_addr, uint32_t reg_data, uint8_t data_type);
	int (*aw_dsp_read)(struct aw_device *aw_dev, uint16_t dsp_addr, uint32_t *dsp_data, uint8_t data_type);
	int (*aw_dsp_write_bits)(struct aw_device *aw_dev, uint16_t dsp_addr, uint16_t mask, uint16_t dsp_data);

	int (*aw_set_volume)(struct aw_device *aw_dev, uint16_t value);
	int (*aw_get_volume)(struct aw_device *aw_dev, uint16_t *value);
	unsigned int (*aw_reg_val_to_db)(unsigned int value);

	void (*aw_i2s_tx_enable)(struct aw_device *aw_dev, bool flag);
	int (*aw_get_dev_num)(void);

	bool (*aw_check_wr_access)(int reg);
	bool (*aw_check_rd_access)(int reg);
	int (*aw_get_reg_num)(void);
	int (*aw_get_version)(char *buf, int size);
	int (*aw_read_dsp_pid)(struct aw_device *aw_dev);
	int (*aw_get_hw_mon_st)(struct aw_device *aw_dev, bool *is_enable, uint8_t *temp_flag);
	int (*aw_cali_svc_get_iv_st)(struct aw_device *aw_dev);
	void (*aw_set_cfg_f0_fs)(struct aw_device *aw_dev, uint32_t *f0_fs);
	int (*aw_dsp_fw_check)(struct aw_device *aw_dev);
	int (*aw_monitor_init)(void *dev);
	void (*aw_monitor_start)(void *dev);
	void (*aw_monitor_stop)(void *dev);
	void (*aw_monitor_deinit)(void *dev);
	int (*aw_monitor_work_func)(void *dev);
	void (*aw_monitor_set_handle) (void *dev);
};

struct aw_int_desc {
	unsigned int mask_reg;			/*interrupt mask reg*/
	unsigned int st_reg;			/*interrupt status reg*/
	unsigned int mask_default;		/*default mask close all*/
	unsigned int int_mask;			/*set mask*/
	unsigned int intst_mask;		/*interrupt check mask*/
	uint16_t sysint_st;			/*interrupt reg status*/
};

struct aw_pwd_desc {
	unsigned int reg;
	unsigned int mask;
	unsigned int enable;
	unsigned int disable;
};

struct aw_vcalb_desc {
	unsigned int icalk_reg;
	unsigned int icalk_reg_mask;
	unsigned int icalk_sign_mask;
	unsigned int icalk_neg_mask;
	int icalk_value_factor;

	unsigned int vcalk_reg;
	unsigned int vcalk_reg_mask;
	unsigned int vcalk_sign_mask;
	unsigned int vcalk_neg_mask;
	unsigned int vcalk_shift;
	int vcalk_value_factor;

	unsigned int vcalb_dsp_reg;
	unsigned char data_type;
	int cabl_base_value;
	int vcal_factor;
	int vscal_factor;
	int iscal_factor;

	unsigned int vcalb_adj_shift;

	unsigned int vcalb_vsense_reg;
	int vscal_factor_vsense_in;
	int vcalk_value_factor_vsense_in;
	unsigned int vcalk_dac_shift;
	unsigned int vcalk_dac_mask;
	unsigned int vcalk_dac_neg_mask;
	unsigned int vcalk_vdsel_mask;
};

struct aw_mute_desc {
	unsigned int reg;
	unsigned int mask;
	unsigned int enable;
	unsigned int disable;
};

struct aw_sysst_desc {
	unsigned int reg;
	unsigned int st_check;
	unsigned int st_mask;
	unsigned int pll_check;
	unsigned int dsp_check;
	unsigned int dsp_mask;
};

struct aw_profctrl_desc {
	unsigned int reg;
	unsigned int mask;
	unsigned int rcv_mode_val;
	unsigned int cur_mode;
};

struct aw_volume_desc {
	unsigned int reg;
	unsigned int mask;
	unsigned int shift;
	int init_volume;
	int mute_volume;
};

struct aw_dsp_en_desc {
	unsigned int reg;
	unsigned int mask;
	unsigned int enable;
	unsigned int disable;
};

struct aw_memclk_desc {
	unsigned int reg;
	unsigned int mask;
	unsigned int mcu_hclk;
	unsigned int osc_clk;
};

struct aw_watch_dog_desc {
	unsigned int reg;
	unsigned int mask;
};

struct aw_dsp_mem_desc {
	unsigned int dsp_madd_reg;
	unsigned int dsp_mdat_reg;
	unsigned int dsp_fw_base_addr;
	unsigned int dsp_cfg_base_addr;
};

struct aw_voltage_desc {
	unsigned int reg;
	unsigned int vbat_range;
	unsigned int int_bit;
};

struct aw_temperature_desc {
	unsigned int reg;
	unsigned int sign_mask;
	unsigned int neg_mask;
};

struct aw_ipeak_desc {
	unsigned int reg;
	unsigned int mask;
};

struct aw_vmax_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
	unsigned int init_vmax;
};

struct aw_soft_rst {
	uint8_t reg;
	uint16_t reg_value;
};

struct crc_dsp_cfg {
	uint32_t len;
	unsigned char *data;

};

struct aw_cali_cfg_desc {
	unsigned int actampth_reg;
	unsigned char actampth_data_type;

	unsigned int noiseampth_reg;
	unsigned char noiseampth_data_type;

	unsigned int ustepn_reg;
	unsigned char ustepn_data_type;

	unsigned int alphan_reg;
	unsigned int alphan_data_type;
};

struct aw_dsp_vol_desc {
	unsigned int reg;
	unsigned int mute_st;
	unsigned int noise_st;
	unsigned int mask;
};

struct aw_amppd_desc {
	unsigned int reg;
	unsigned int mask;
	unsigned int enable;
	unsigned int disable;
};

struct aw_f0_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
	unsigned int shift;
};

struct aw_cfgf0_fs_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
};

struct aw_q_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
	unsigned int shift;
};

struct aw_ra_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
};

struct aw_noise_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
	unsigned int mask;
};

struct aw_ste_re_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
	unsigned int shift;
};

struct aw_adpz_re_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
	unsigned int shift;
};

struct aw_adpz_t0_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
	uint16_t coilalpha_reg;
	unsigned char coil_type;
};

struct aw_spkr_temp_desc {
	unsigned int reg;
};

struct aw_dsp_crc_desc {
	unsigned int ctl_reg;
	unsigned int ctl_mask;
	unsigned int ctl_enable;
	unsigned int ctl_disable;

	unsigned int dsp_reg;
	unsigned char data_type;
};

struct aw_cco_mux_desc {
	unsigned int reg;
	unsigned int mask;
	unsigned int divider;
	unsigned int bypass;
};

struct aw_hw_temp_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
};

struct aw_re_range_desc {
	uint32_t re_min;
	uint32_t re_max;
};

struct aw_cali_delay_desc {
	unsigned int dsp_reg;
	unsigned char data_type;
	unsigned int delay;
};

struct aw_dsp_st {
	unsigned int dsp_reg_s1;
	unsigned int dsp_reg_e1;

	unsigned int dsp_reg_s2;
	unsigned int dsp_reg_e2;
};

struct aw_container {
	int len;
	uint8_t data[];
};

struct aw_device {
	int status;
	char cur_prof_name[AW_PROF_NAME_MAX];				/*current profile name*/
	char set_prof_name[AW_PROF_NAME_MAX];				/*set profile name*/
	char first_prof_name[AW_PROF_NAME_MAX];			/*first profile name in aw_prof_desc*/
	unsigned char dsp_crc_st;
	unsigned int chip_id;
	aw_dev_index_t dev;
	unsigned int fade_step;
	void *private_data;
	aw_fade_en_t fade_en;
	unsigned char dsp_cfg;
	uint32_t dsp_fw_len;
	uint32_t dsp_cfg_len;
	uint8_t fw_status;	/*load cfg status*/

	struct aw_prof_info *prof_info;
	struct crc_dsp_cfg crc_dsp_cfg;

	struct aw_int_desc int_desc;
	struct aw_pwd_desc pwd_desc;
	struct aw_mute_desc mute_desc;
	struct aw_vcalb_desc vcalb_desc;
	struct aw_sysst_desc sysst_desc;
	struct aw_profctrl_desc profctrl_desc;
	struct aw_volume_desc volume_desc;
	struct aw_dsp_en_desc dsp_en_desc;
	struct aw_memclk_desc memclk_desc;
	struct aw_watch_dog_desc watch_dog_desc;
	struct aw_dsp_mem_desc dsp_mem_desc;
	struct aw_voltage_desc voltage_desc;
	struct aw_temperature_desc temp_desc;
	struct aw_vmax_desc vmax_desc;
	struct aw_ipeak_desc ipeak_desc;
	struct aw_soft_rst soft_rst;
	struct aw_cali_cfg_desc cali_cfg_desc;
	struct aw_ra_desc ra_desc;
	struct aw_dsp_vol_desc dsp_vol_desc;
	struct aw_noise_desc noise_desc;
	struct aw_f0_desc f0_desc;
	struct aw_cfgf0_fs_desc cfgf0_fs_desc;
	struct aw_q_desc q_desc;
	struct aw_ste_re_desc ste_re_desc;
	struct aw_adpz_re_desc adpz_re_desc;
	struct aw_adpz_t0_desc t0_desc;
	struct aw_amppd_desc amppd_desc;
	struct aw_spkr_temp_desc spkr_temp_desc;
	struct aw_dsp_crc_desc dsp_crc_desc;
	struct aw_cco_mux_desc cco_mux_desc;
	struct aw_hw_temp_desc hw_temp_desc;

	struct aw_cali_desc cali_desc;
#ifdef AW_MONITOR
	struct aw_monitor_desc monitor_desc;
#endif
	struct aw_re_range_desc re_range;
	struct aw_cali_delay_desc cali_delay_desc;
	struct aw_dsp_st dsp_st_desc;

	struct aw_device_ops ops;
};


int aw883xx_device_start(struct aw_device *aw_dev);
int aw883xx_device_stop(struct aw_device *aw_dev);
int aw883xx_dev_fw_update(struct aw_device *aw_dev, bool up_dsp_fw_en, bool force_up_en);
int aw883xx_dev_get_int_status(struct aw_device *aw_dev, uint16_t *int_status);
int aw883xx_dev_set_intmask(struct aw_device *aw_dev, bool flag);
void aw883xx_dev_clear_int_status(struct aw_device *aw_dev);
void aw883xx_dev_interrupt_clear(struct aw_device *aw_dev);
int aw883xx_device_probe(struct aw_device *aw_dev, struct aw_init_info *init_info);
int aw883xx_dev_syspll_check(struct aw_device *aw_dev);
int aw883xx_dev_get_dsp_status(struct aw_device *aw_dev);
void aw883xx_dev_set_fade_vol_step(struct aw_device *aw_dev, unsigned int step);
int aw883xx_dev_get_fade_vol_step(struct aw_device *aw_dev);
void aw883xx_dev_get_fade_time(unsigned int *time, bool fade_in);
void aw883xx_dev_set_fade_time(unsigned int time, bool fade_in);
int aw883xx_dev_get_hmute(struct aw_device *aw_dev);
int aw883xx_dev_sysst_check(struct aw_device *aw_dev);
void aw883xx_dev_dsp_enable(struct aw_device *aw_dev, bool dsp);
int aw883xx_dev_modify_dsp_cfg(struct aw_device *aw_dev,
			unsigned int addr, uint32_t dsp_data, unsigned char data_type);

void aw883xx_dev_soft_reset(struct aw_device *aw_dev);
void aw883xx_dev_get_init_volume(struct aw_device *aw_dev, uint32_t *volume);
int aw883xx_dev_set_init_volume(struct aw_device *aw_dev, uint32_t volume);
int aw883xx_dev_reg_dump(struct aw_device *aw_dev);
int aw883xx_dev_get_iis_status(struct aw_device *aw_dev);

int aw883xx_dev_check_prof(uint32_t dev_index, struct aw_prof_info *prof_info);
int aw883xx_dev_set_profile_name(struct aw_device *aw_dev, const char *prof_name);
char *aw883xx_dev_get_profile_name(struct aw_device *aw_dev);
struct aw_sec_data_desc *aw883xx_dev_get_prof_data_byname(struct aw_device *aw_dev, char *prof_name, int data_type);

#endif

