/** Define to Prevent Recursive Inclusion */
#ifndef _BSP_FFT_H
#define _BSP_FFT_H

#ifdef  __cplusplus
extern "C" {
#endif
	
/** Includes */		
#include "fbank.h"

#define BSP_FFT_INTERRUPT_LEVEL 3

/**
* @brief  fft calculation
* @param  data_write: the source data to write into the fft sram
* @param  data_read: the result data to read from the fft sram
* @retval void
*/
extern void fft_calculate(uint32_t *data_write,uint32_t *data_read);
extern void fft_calculate_part1(uint32_t* data_write);
extern void fft_calculate_part2(uint32_t* data_read);

/**
* @brief  ifft calculation
* @param  data_write: the source data to write into the fft sram
* @param  data_read: the result data to read from the fft sram
* @retval void
*/
extern void ifft_calculate(uint32_t *data_write,uint32_t *data_read);
extern void ifft_calculate_part1(uint32_t* data_write);
extern void ifft_calculate_part2(uint32_t* data_read);

/**
* @brief  fank calculation
* @param  data_write: the source data to write into the fft sram
* @param  data_read: the result data to read from the fft sram
* @retval void
*/
extern void fbank_calculate(uint32_t *data_write,uint32_t *data_read);


extern void fbank_calculate_win_fft(uint32_t *data_write,uint32_t *data_read);
extern void fbank_calculate_sqrt_mel_log(uint32_t *data_write,uint32_t *data_read);
extern void fbank_calculate_sqrt_mel(uint32_t *data_write,uint32_t *data_read);
/**
  * @}
  */
	
#ifdef __cplusplus
}
#endif

#endif  
