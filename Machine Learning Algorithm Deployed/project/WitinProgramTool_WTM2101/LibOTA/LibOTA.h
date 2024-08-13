// LibOTA.h  v1.4.0.0

// Return version of this library
int wtmnpu_library_version();

// Run initialization for OTA program, return success/fail result. (1~1.5 min)
// Bootloader and osc_trim refreshed as specified. Please use correct data.
// args: bootloader -- bootloader, uint32_t bootloader[1024]
//       osc_trim -- clock trim code, uint16_t osc_trim[4] = {osc24m_coarse, osc24m_fine, osc320k_coarse, osc320k_fine}   
// return:   0 (success), 
//          -1 (osc_trim out of range),
//           1 (init scale out of range), 
//           2 (write trim data fail), 
//           3 (init scale out of range && write trim data fail), 
//           4 (write bootloader fail), 
//           5 (write bootloader fail, init scale out of range), 
//           6 (write bootloader fail, write trim data fail), 
//           7 (write bootloader fail, write trim data fail, init scale out of range), 
// Note: This function erases network
int wtmnpu_init(uint32_t* bootloader, uint16_t* osc_trim);

// Write bootloader and osc_trim, return success/fail result. (~10 sec)
// Bootloader and osc_trim refreshed as specified. Please use correct data.
// args: bootloader -- bootloader, uint32_t bootloader[1024]
//       osc_trim -- clock trim code, uint16_t osc_trim[4] = {osc24m_coarse, osc24m_fine, osc320k_coarse, osc320k_fine}   
// return:   0 (success), 
//          -1 (osc_trim out of range),
//           2 (write trim data fail), 
//           4 (write bootloader fail), 
//           6 (write bootloader fail, write trim data fail), 
// Note: This function erases network
int wtmnpu_init_boot(uint32_t* bootloader, uint16_t* osc_trim);

// OTA program neural network onto WTM2101 NPU. return success/fail
// All data received from UART/SPI
// args: none
// return:   0 (success), 
//          -1 (data error),
//          -2 (memory 1 alloc error),
//          -3 (memory 2 alloc error), 
//          -5 (write bootloader/trim fail), 
//          -6 (accuracy below expectation, only if standard.txt exists), 
int wtmnpu_program_ota();

// OTA check neural network programed before. return success/fail
// All data received from UART/SPI
// args: none
// return:   0 (success), 
//          -1 (data error),
//          -2 (memory 1 alloc error),
//          -3 (memory 2 alloc error), 
//          -5 (write bootloader/trim fail), 
//          -6 (accuracy below expectation, only if standard.txt exists), 
int wtmnpu_check_ota();

// Save bootloader name in WTM2101 NPU. return success/fail
// args: name -- bootloader name (char name[8], must be 8 characters)
// return:   0 (success), 
//           1 (fail),
int wtmnpu_writebootname(char* name);

// Read bootloader data from WTM2101 NPU, return 0 (without CRC check)
// args: boot_data -- array to store bootloader data, uint32_t boot_data[1024]
// return:  0 (without CRC check)
// Note: the last 4 numbers in boot_data is osc_trim (not the same as in original bootloader)
int NPU_READ_BOOT(uint32_t* boot_data);

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

// Store trim code in WTM2101 NPU flash and return success/fail.
// args: trim_data -- array where correct trim data stored. uint16_t trim_data[256]
// return:  0 (success)
//          1 (fail)
// Note: This function may damage the NN on the chip, should only be used together with ota init or program.
int NPU_WRITE_TRIM(uint16_t* npu_data);

// Calibrate internal clock using external 32k clock. Return correct trim code and success/fail
// args: osc_trim -- array to store trim code for internal clock. uint16_t osc_trim[4] = {osc24m_coarse, osc24m_fine, osc320k_coarse, osc320k_fine} 
// return:  0 (success)
//          1 (fail, trim code out of range)
int OSC_Calibration(uint16_t* osc_trim);

// Configure internal clock to 144MHz using trim code. Return success/fail
// args: osc24m coarse -- osc 24M coarse tuning code
//       osc24m fine -- osc 24M fine tuning code
// return:  0 (success)
//          1 (fail, trim code out of range)
int CLK144M_Start(uint8_t osc24m_coarse, uint8_t osc24m_fine);

// Return layer number of the programed network
int wtmnpu_get_layernum();

// Return accuracy statistics
// args: array -- array to store accuracy data
// return: 0 (array alloc pass)
//         1 (array alloc fail)
int wtmnpu_statistic(float* array);
