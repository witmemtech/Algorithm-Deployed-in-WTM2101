#ifndef __WITIN_ARM_LIB_H__
#define __WITIN_ARM_LIB_H__

#include <stdio.h>
#include <stdint.h>

typedef float float32_t;
typedef int32_t q31_t;
typedef int64_t q63_t;

/**
* @brief Instance structure for the fixed-point CFFT/CIFFT function.
*/
typedef struct
{
	  uint16_t fftLen;                   /**< length of the FFT. */
const q31_t *pTwiddle;             /**< points to the Twiddle factor table. */
const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
	  uint16_t bitRevLength;             /**< bit reversal table length. */
} arm_cfft_instance_q31;
  
/**
* @brief Instance structure for the Q31 RFFT/RIFFT function.
*/
typedef struct
{
	  uint32_t fftLenReal;                        /**< length of the real FFT. */
	  uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
	  uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
	  uint32_t twidCoefRModifier;                 /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
const q31_t *pTwiddleAReal;                       /**< points to the real twiddle factor table. */
const q31_t *pTwiddleBReal;                       /**< points to the imag twiddle factor table. */
const arm_cfft_instance_q31 *pCfft;         /**< points to the complex FFT instance. */
} arm_rfft_instance_q31;

extern void within_arm_sqrt_f32( float in, float* pOut);

#ifdef PLATFORM_RSIC_V_N307
void __attribute__((optimize("-O1"))) witin_vec_int16xint16_shift15_to_int16(int *dest, int *src1, int *src2, int len);
int8_t  __attribute__((optimize("-O1"))) witin_vec_int8_getMax(int *src1, int len);

#endif

float InvSqrt(float value_0);

float sqrt_convert_memory(float x);

/* SMMLAR */
#define multAcc_32x32_keep32_R(a, x, y) \
    a = (q31_t) (((((q63_t) a) << 32) + ((q63_t) x * y) + 0x80000000LL ) >> 32)

/* SMMLSR */
#define multSub_32x32_keep32_R(a, x, y) \
    a = (q31_t) (((((q63_t) a) << 32) - ((q63_t) x * y) + 0x80000000LL ) >> 32)

/* SMMULR */
#define mult_32x32_keep32_R(a, x, y) \
    a = (q31_t) (((q63_t) x * y + 0x80000000LL ) >> 32)

/* SMMLA */
#define multAcc_32x32_keep32(a, x, y) \
    a += (q31_t) (((q63_t) x * y) >> 32)

/* SMMLS */
#define multSub_32x32_keep32(a, x, y) \
    a -= (q31_t) (((q63_t) x * y) >> 32)

/* SMMUL */
#define mult_32x32_keep32(a, x, y) \
    a = (q31_t) (((q63_t) x * y ) >> 32)
	
#define ARMBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH ((uint16_t)240)

typedef enum
{
	ARM_MATH_SUCCESS        =  0,        /**< No error */
	ARM_MATH_ARGUMENT_ERROR = -1,        /**< One or more arguments are incorrect */
	ARM_MATH_LENGTH_ERROR   = -2,        /**< Length of data buffer is incorrect */
	ARM_MATH_SIZE_MISMATCH  = -3,        /**< Size of matrices is not compatible with the operation */
	ARM_MATH_NANINF         = -4,        /**< Not-a-number (NaN) or infinity is generated */
	ARM_MATH_SINGULAR       = -5,        /**< Input matrix is singular and cannot be inverted */
	ARM_MATH_TEST_FAILURE   = -6         /**< Test Failed */
} arm_status;


extern const q31_t realCoefAQ31[510];
extern const q31_t realCoefBQ31[255];
extern const q31_t twiddleCoef_512_q31[768];

extern const arm_cfft_instance_q31 arm_cfft_sR_q31_len256;

extern arm_status arm_rfft_init_q31(
    arm_rfft_instance_q31 * S,
    uint32_t fftLenReal,
    uint32_t ifftFlagR,
    uint32_t bitReverseFlag);

extern void arm_rfft_q31(
  const arm_rfft_instance_q31 * S,
        q31_t * pSrc,
        q31_t * pDst);
#endif

