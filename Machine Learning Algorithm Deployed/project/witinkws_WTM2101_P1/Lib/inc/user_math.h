#ifndef USER_MATH_H
#define USER_MATH_H

#include <stdint.h>

#include <riscv_common_tables.h>

extern const uint16_t riscvBitRevIndexTable64[];
extern const float32_t twiddleCoef_64[];
extern const float32_t twiddleCoef_rfft_128[];

extern const uint16_t riscvBitRevIndexTable128[];
extern const float32_t twiddleCoef_128[];
extern const float32_t twiddleCoef_rfft_256[];

extern const uint16_t riscvBitRevIndexTable256[];
extern const float32_t twiddleCoef_256[];
extern const float32_t twiddleCoef_rfft_512[];


riscv_rfft_fast_instance_f32 rfft128_inst = {
    .Sint = {
        .fftLen         = 64,
        .pTwiddle       = (float32_t *)twiddleCoef_64,
        .pBitRevTable   = (uint16_t *)riscvBitRevIndexTable64,
        .bitRevLength   = RISCVBITREVINDEXTABLE_64_TABLE_LENGTH,
    },
    .fftLenRFFT     = 128,
    .pTwiddleRFFT   = (float32_t *)twiddleCoef_rfft_128,
};

/*riscv_rfft_fast_instance_f32 rfft256_inst = {
    .Sint = {
        .fftLen         = 128,
        .pTwiddle       = (float32_t *)twiddleCoef_128,
        .pBitRevTable   = (uint16_t *)riscvBitRevIndexTable128,
        .bitRevLength   = RISCVBITREVINDEXTABLE_128_TABLE_LENGTH,
    },
    .fftLenRFFT     = 256,
    .pTwiddleRFFT   = (float32_t *)twiddleCoef_rfft_256,
};

riscv_rfft_fast_instance_f32 rfft512_inst = {
    .Sint = {
        .fftLen         = 256,
        .pTwiddle       = (float32_t *)twiddleCoef_256,
        .pBitRevTable   = (uint16_t *)riscvBitRevIndexTable256,
        .bitRevLength   = RISCVBITREVINDEXTABLE_256_TABLE_LENGTH,
    },
    .fftLenRFFT     = 512,
    .pTwiddleRFFT   = (float32_t *)twiddleCoef_rfft_512,
};*/




void riscv_rfft_fast_f32(
  riscv_rfft_fast_instance_f32 * S,
  float32_t * p,
  float32_t * pOut,
  uint8_t ifftFlag);


#endif // !USER_MATH_H
