// LibNPU.h  v1.4.0.0

// Return version of this library
int wtmnpu_library_version();

// Read trim data from WTM2101 NPU, return CRC result
// args: trim_data -- array to store trim data, uint16_t trim_data[256]
// return:  0 (pass)
//          1 (section 1 (clock and voltage related) pass， section 2 (npu program related, set during init) fail)
//          2 (section 1 fail, section 2 pass)
//          3 (section 1 fail, section 2 fail)
int NPU_READ_TRIM(uint16_t* trim_data);

// Use trim code from npu_data[256], trim DVDD1.1v, and return trim code validity.
// args: trim_data -- array where correct trim data stored. uint16_t trim_data[256]
// return:  0 (all valid)
//          1 (clock trim valid, voltage trim invalid (not critical))
//          2 (all invalid)
int NPU_USE_TRIM(uint16_t* trim_data);

// Configure NPU for inference (NPU Clock at 6*N MHz).
void NPU_INFER_CONFIG_6N_MHz(int N);

// Initial set for inference
void wnpu_infer_init(void);

// power-up for inference
void pu_stage(void);

// power-down for power-saving
void pd_stage(void);

// set clock divsion for npu
void witin_npu_set_clk_div(uint8_t clk_div);

// soft reset npu and set npu clock with (extern int npu_div_num)
void witin_soft_reset(void);

// write analog config in array format
void wnpu_write_analog_config(const unsigned short *config, unsigned int num);

// Set DVDD to 1p1v, and trim it if trim code avaliable
void TRIM_DVDD_1p1v();

// Set DVDD to 0p9v, and trim it if trim code avaliable
void TRIM_DVDD_0p9v();








