/*
 * Copyright (C) 2010-2018 Arm Limited or its affiliates. All rights reserved.
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* ----------------------------------------------------------------------
 * Project:      NMSIS NN Library
 * Title:        riscv_fully_connected_q15_opt.c
 * Description:  Q15 opt fully-connected layer function
 *
 * $Date:        17. January 2018
 * $Revision:    V.1.0.0
 *
 * Target Processor: RISC-V Cores
 *
 * -------------------------------------------------------------------- */

#include "riscv_math.h"
#include "riscv_nnfunctions.h"

/**
 *  @ingroup groupNN
 */

/**
 * @addtogroup FC
 * @{
 */

  /**
   * @brief Q15 opt fully-connected layer function
   * @param[in]       pV          pointer to input vector
   * @param[in]       pM          pointer to matrix weights
   * @param[in]       dim_vec     length of the vector
   * @param[in]       num_of_rows number of rows in weight matrix
   * @param[in]       bias_shift  amount of left-shift for bias
   * @param[in]       out_shift   amount of right-shift for output
   * @param[in]       bias        pointer to bias
   * @param[in,out]   pOut        pointer to output vector
   * @param[in,out]   vec_buffer  pointer to buffer space for input
   * @return     The function returns <code>RISCV_MATH_SUCCESS</code>
   *
   *
   * @details
   *
   * <b>Buffer size:</b>
   *
   * vec_buffer size: 0
   *
   *  Here we use only one pointer to read 4 rows in the weight
   *  matrix. So if the original matrix looks like this:
   *
   *  | a11 | a12 | a13 |
   *
   *  | a21 | a22 | a23 |
   *
   *  | a31 | a32 | a33 |
   *
   *  | a41 | a42 | a43 |
   *
   *  | a51 | a52 | a53 |
   *
   *  | a61 | a62 | a63 |
   *
   *  We operates on multiple-of-4 rows, so the first four rows becomes
   *
   *  | a11 | a12 | a21 | a22 | a31 | a32 | a41 | a42 |
   *
   *  | a13 | a23 | a33 | a43 |
   *
   *  Remaining rows are kept the same original order.
   *
   *  So the stored weight matrix looks like this:
   *
   *
   *  | a11 | a12 | a21 | a22 | a31 | a32 | a41 | a42 |
   *
   *  | a13 | a23 | a33 | a43 | a51 | a52 | a53 | a61 |
   *
   *  | a62 | a63 |
   */

riscv_status
riscv_fully_connected_q15_opt(const q15_t * pV,
                            const q15_t * pM,
                            const uint16_t dim_vec,
                            const uint16_t num_of_rows,
                            const uint16_t bias_shift,
                            const uint16_t out_shift, 
                            const q15_t * bias, 
                            q15_t * pOut, 
                            q15_t * vec_buffer)
{

#if defined (RISCV_MATH_DSP)
    /* Run the following code for RISC-V Core with DSP enabled */

    const q15_t *pB = pM;
    q15_t    *pO = pOut;
    const q15_t *pBias = bias;
    const q15_t *pA = pV;

    uint16_t  rowCnt = num_of_rows >> 2;

    while (rowCnt)
    {
        q31_t     sum =  ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift);
        q31_t     sum2 = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift); 
        q31_t     sum3 = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift); 
        q31_t     sum4 = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift); 

        uint16_t  colCnt = dim_vec >> 1;

        pA = pV;

#ifdef USE_INTRINSIC

        while (colCnt)
        {
            q31_t     inM11, inM12, inM13, inM14;
            q31_t     inV;

            inV = *__SIMD32(pA)++;
            inM11 = *__SIMD32(pB)++;
            sum = __RV_KMADA(sum , inV, inM11);
            inM12 = *__SIMD32(pB)++;
            sum2 = __RV_KMADA(sum2, inV, inM12);
            inM13 = *__SIMD32(pB)++;
            sum3 = __RV_KMADA(sum3, inV, inM13);
            inM14 = *__SIMD32(pB)++;
            sum4 = __RV_KMADA(sum4, inV, inM14);
            colCnt--;
        }

#else

        /*
         * register needed:
         * loop counter: colCnt
         * accumulators: sum, sum2, sum3, sum4
         * pointers: pB, pA
         * weight data: inM11, inM12, inM13, inM14
         * activation data: inV
         */

        asm volatile ("COL_LOOP_%=:\n"
                      "ldr.w r4, [%[pA]], #4\n"
                      "ldr.w r0, [%[pB]], #16\n"
                      "smlad %[sum], r4, r0, %[sum]\n"
                      "ldr.w r1, [%[pB] , #-12]\n"
                      "smlad %[sum2], r4, r1, %[sum2]\n"
                      "ldr.w r2, [%[pB] , #-8]\n"
                      "smlad %[sum3], r4, r2, %[sum3]\n"
                      "ldr.w r3, [%[pB] , #-4]\n"
                      "smlad %[sum4], r4, r3, %[sum4]\n"
                      "subs %[colCnt], #1\n"
                      "bne COL_LOOP_%=\n":[sum] "+r"(sum),
                      [sum2] "+r"(sum2),[sum3] "+r"(sum3),
                      [sum4] "+r"(sum4),[pB] "+r"(pB),[pA] "+r"(pA):[colCnt] "r"(colCnt):"r0", "r1", "r2", "r3", "r4");

#endif                          /* USE_INTRINSIC */

        colCnt = dim_vec & 0x1;
        while (colCnt)
        {

            q15_t     inV = *pA++;
            q15_t     inM = *pB++;
            q15_t     inM2 = *pB++;
            q15_t     inM3 = *pB++;
            q15_t     inM4 = *pB++;

            sum += inV * inM;
            sum2 += inV * inM2;
            sum3 += inV * inM3;
            sum4 += inV * inM4;
            colCnt--;
        }                       /* while over colCnt */
        *pO++ = (q15_t) (__SSAT((sum >> out_shift), 16));
        *pO++ = (q15_t) (__SSAT((sum2 >> out_shift), 16));
        *pO++ = (q15_t) (__SSAT((sum3 >> out_shift), 16));
        *pO++ = (q15_t) (__SSAT((sum4 >> out_shift), 16));

        /* adjust the pointers and counters */
        rowCnt--;
    }

    /* left-over part of the rows */
    rowCnt = num_of_rows & 0x3;

    while (rowCnt)
    {


        pA = pV;
        q31_t     sum = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift);
        uint16_t  colCnt = dim_vec >> 2;
#if __RISCV_XLEN == 64
        // q63_t     sum = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift);
        // uint16_t  colCnt = dim_vec >> 3;
        q63_t sum64 = 0;
        while (colCnt)
        {
            q63_t     inV1, inV2, inM1, inM2;

            inM1 = *__SIMD64(pB)++;
            inV1 = *__SIMD64(pA)++;
            sum64 = __RV_KMADA(sum64, inV1, inM1);

            // inM2 = *__SIMD64(pB)++;
            // inV2 = *__SIMD64(pA)++;
            // sum = __RV_SMALDA(sum, inV2, inM2);
         
           // q31_t   inB1 = *__SIMD32(pB)++;
           // q31_t   inA1 = *__SIMD32(pA)++;
            //sum = __RV_KMAR64(sum, inB1, inA1);
            colCnt--;
        }
    sum = sum + (q31_t)(sum64 & 0xFFFFFFFF) + (q31_t)((sum64 & 0xFFFFFFFF00000000)>>32);

        /* left-over of the vector */
        // colCnt = dim_vec & 0x7;
#else
//original should be q63_t?

        while (colCnt)
        {
            q31_t     inV1, inV2, inM1, inM2;

            inM1 = *__SIMD32(pB)++;
            inV1 = *__SIMD32(pA)++;
            sum = __RV_KMADA(sum, inV1, inM1);

            inM2 = *__SIMD32(pB)++;
            inV2 = *__SIMD32(pA)++;
            sum = __RV_KMADA(sum, inV2, inM2);
         
           // q31_t   inB1 = *__SIMD32(pB)++;
           // q31_t   inA1 = *__SIMD32(pA)++;
            //sum = __RV_KMAR64(sum, inB1, inA1);
            colCnt--;
        }

#endif /* __RISCV_XLEN == 64 */
        /* left-over of the vector */
        colCnt = dim_vec & 0x3;
        while (colCnt)
        {
            q15_t     inV = *pA++;
            q15_t     inM = *pB++;    
            sum += inV * inM;
            colCnt--;
        }

        *pO++ = (q15_t) (__SSAT((sum >> out_shift), 16));

        rowCnt--;
    }

#else
    /* Run the following code as reference implementation for RISC-V Core without DSP */
    uint16_t  rowCnt = num_of_rows >> 2;
    const q15_t *pB = pM;
    const q15_t *pA;
    q15_t    *pO = pOut;
    const q15_t *pBias = bias;

    while (rowCnt)
    {
        q31_t     sum =  ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift);
        q31_t     sum2 = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift);
        q31_t     sum3 = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift);
        q31_t     sum4 = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift);

        uint16_t  colCnt = dim_vec >> 1;

        pA = pV;
        while (colCnt)
        {
            q15_t     inA1 = *pA++;
            q15_t     inA2 = *pA++;

            q15_t     inB1 = *pB++;
            q15_t     inB2 = *pB++;
            sum += inA1 * inB1 + inA2 * inB2;

            inB1 = *pB++;
            inB2 = *pB++;
            sum2 += inA1 * inB1 + inA2 * inB2;

            inB1 = *pB++;
            inB2 = *pB++;
            sum3 += inA1 * inB1 + inA2 * inB2;

            inB1 = *pB++;
            inB2 = *pB++;
            sum4 += inA1 * inB1 + inA2 * inB2;

            colCnt--;
        }
        colCnt = dim_vec & 0x1;
        while (colCnt)
        {
            q15_t     inA = *pA++;
            q15_t     inB = *pB++;
            sum += inA * inB;
            inB = *pB++;
            sum2 += inA * inB;
            inB = *pB++;
            sum3 += inA * inB;
            inB = *pB++;
            sum4 += inA * inB;
            colCnt--;
        }
        *pO++ = (q15_t) __SSAT((sum >> out_shift), 16);
        *pO++ = (q15_t) __SSAT((sum2 >> out_shift), 16);
        *pO++ = (q15_t) __SSAT((sum3 >> out_shift), 16);
        *pO++ = (q15_t) __SSAT((sum4 >> out_shift), 16);

        rowCnt--;
    }
    rowCnt = num_of_rows & 0x3;

    while (rowCnt)
    {
        int       ip_out = ((q31_t)(*pBias++) << bias_shift) + NN_ROUND(out_shift);
        int       j;

        pA = pV;
        for (j = 0; j < dim_vec; j++)
        {
            q15_t     inA = *pA++;
            q15_t     inB = *pB++;
            ip_out += inA * inB;
        }
        *pO++ = (q15_t) __SSAT((ip_out >> out_shift), 16);

        rowCnt--;
    }

#endif                          /* RISCV_MATH_DSP */

    /* Return to RISCV_MATH_SUCCESS */
    return (RISCV_MATH_SUCCESS);

}

/**
 * @} end of FC group
 */
