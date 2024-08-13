#ifndef __AW_PROFILE_PROCESS_H__
#define __AW_PROFILE_PROCESS_H__

#include "aw883xx_base.h"

#define AW_PROF_NAME_MAX	(50)

/*******************awinic audio parse acf***********************/

enum profile_data_type {
	AW_DATA_TYPE_REG = 0,
	AW_DATA_TYPE_DSP_CFG,
	AW_DATA_TYPE_DSP_FW,
	AW_DATA_TYPE_MAX,
};

struct aw_monitor_data_desc {
	uint32_t len;
	const unsigned char *data;
};

struct aw_sec_data_desc {
	uint32_t len;
	const unsigned char *data;
};

struct aw_prof_desc {
	char name [AW_PROF_NAME_MAX];
	struct aw_sec_data_desc sec_desc[AW_DATA_TYPE_MAX];
};

struct aw_prof_info {
	uint32_t chip_id;		/*The ID corresponding to the chip*/
	uint32_t count;			/*profile count*/
	struct aw_prof_desc *prof_desc;/*Describes the configuration of each scenario*/
	struct aw_monitor_data_desc *monitor_data;
};

#endif
