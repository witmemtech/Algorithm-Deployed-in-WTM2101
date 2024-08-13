#include "stdint.h"
#include "witin_math_lib.h"
//#include "kws_integrate.h"

#ifdef PLATFORM_RSIC_V_N307
#include "nmsis_gcc.h"
#endif


#include <math.h>
void within_arm_sqrt_f32( float in, float* pOut){
	if (in >= 0.0f)
	{
#if (__FPU_USED == 1) && defined ( __CC_ARM   )
      *pOut = __sqrtf(in);
#else
      *pOut = sqrtf(in);
#endif
	}
	else
	{
	  *pOut = 0.0f;
	}
}

/**
  @brief         Core Real IFFT process
  @param[in]     pSrc      points to input buffer
  @param[in]     fftLen    length of FFT
  @param[in]     pATable   points to twiddle Coef A buffer
  @param[in]     pBTable   points to twiddle Coef B buffer
  @param[out]    pDst      points to output buffer
  @param[in]     modifier  twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table
  @return        none
 */

float sqrt_convert_memory(float x)
 {
   unsigned int i = *(unsigned int*) &x; 
   // adjust bias
   i  += 127 << 23;
   // approximation of square root
   i >>= 1; 
   return *(float*) &i;
 }

float InvSqrt(float value_0)
{
	float x = value_0;
	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x*(1.5f - xhalf*x*x);
	return 1/x;
}

#ifdef PLATFORM_RSIC_V_N307
void __attribute__((optimize("-O1"))) witin_vec_int16xint16_shift15_to_int16(int *dest, int *src1, int *src2, int len) {
	__ASM volatile(
	  "addi t0,%0,0;"
	  "addi t1,%1,0;"
	  "addi t2,%2,0;"
	  "addi t3,%3,0;"
	  "witin_vec_int16xint16_shift15_to_int1_loop1:  "
	  "lw t4, 0(t1);"
	  "lw t5, 0(t2);"
	  "KHM16 t6,t4,t5;"
	  "sw t6, 0(t0);"
	  "addi t0, t0, 4;"
	  "addi t1, t1, 4;"
	  "addi t2, t2, 4;"

	  "addi  t3,t3,-1;"
	  "bgtz t3,witin_vec_int16xint16_shift15_to_int1_loop1;"
	  : 
	  : "r"(dest),"r"(src1), "r"(src2), "r"(len)
	  : "t0","t1","t2","t3","t4","t5","t6"
	  );

 }


int8_t  __attribute__((optimize("-O1"))) witin_vec_int8_getMax(int *src1, int len) {
	int result = 0;
	__ASM volatile(
	  "sub t0,t0,t0;"
	  "addi t1,%1,0;"
	  "addi t2,%2,0;"
	  "addi t3,t0,-126;"
	  "witin_vec_int8_getMax_loop:;"
	  "lw t4, 0(t1);"
	  "SMAX8 t3,t4,t3;"
	  "addi t1, t1, 4;"
	  "addi  t2,t2,-1;"
	  "bgtz t2,witin_vec_int8_getMax_loop;"
	  "SRLI  t6,t3,16;"
	  "SMAX8 t4,t3,t6;"  // low 16bit
	  "SRLI  t6,t4,8;"
	  "SMAX8 t0,t4,t6;"  // low 8 bit
	  "ANDI  t4,t0,0xff;"
	  "addi %0, t4, 0;"
	  : "=r"(result)
	  : "r"(src1), "r"(len)
	  : "t0","t1","t2","t3","t4","t5","t6"
	  );
	 return (int8_t)result ;
 }
#endif

void arm_split_rifft_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pATable,
  const q31_t * pBTable,
        q31_t * pDst,
        uint32_t modifier)
{       
        q31_t outR, outI;                              /* Temporary variables for output */
  const q31_t *pCoefA, *pCoefB;                        /* Temporary pointers for twiddle factors */
        q31_t CoefA1, CoefA2, CoefB1;                  /* Temporary variables for twiddle coefficients */
        q31_t *pIn1 = &pSrc[0], *pIn2 = &pSrc[2 * fftLen + 1];

  pCoefA = &pATable[0];
  pCoefB = &pBTable[0];

  while (fftLen > 0U)
  {
     /*
       outR = (  pIn[2 * i]             * pATable[2 * i]
               + pIn[2 * i + 1]         * pATable[2 * i + 1]
               + pIn[2 * n - 2 * i]     * pBTable[2 * i]
               - pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);

       outI = (  pIn[2 * i + 1]         * pATable[2 * i]
               - pIn[2 * i]             * pATable[2 * i + 1]
               - pIn[2 * n - 2 * i]     * pBTable[2 * i + 1]
               - pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);
      */

     CoefA1 = *pCoefA++;
     CoefA2 = *pCoefA;

     /* outR = (pIn[2 * i] * pATable[2 * i] */
     mult_32x32_keep32_R (outR, *pIn1, CoefA1);

     /* - pIn[2 * i] * pATable[2 * i + 1] */
     mult_32x32_keep32_R (outI, *pIn1++, -CoefA2);

     /* pIn[2 * i + 1] * pATable[2 * i + 1] */
     multAcc_32x32_keep32_R (outR, *pIn1, CoefA2);

     /* pIn[2 * i + 1] * pATable[2 * i] */
     multAcc_32x32_keep32_R (outI, *pIn1++, CoefA1);

     /* pIn[2 * n - 2 * i] * pBTable[2 * i] */
     multAcc_32x32_keep32_R (outR, *pIn2, CoefA2);
     CoefB1 = *pCoefB;

     /* pIn[2 * n - 2 * i] * pBTable[2 * i + 1] */
     multSub_32x32_keep32_R (outI, *pIn2--, CoefB1);

     /* pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1] */
     multAcc_32x32_keep32_R (outR, *pIn2, CoefB1);

     /* pIn[2 * n - 2 * i + 1] * pBTable[2 * i] */
     multAcc_32x32_keep32_R (outI, *pIn2--, CoefA2);

     /* write output */
     *pDst++ = outR;
     *pDst++ = outI;

     /* update coefficient pointer */
     pCoefB = pCoefB + (modifier * 2);
     pCoefA = pCoefA + (modifier * 2 - 1);
     /* Decrement loop count */
     fftLen--;
  }

}

/**
  @brief         Core function for the Q31 CIFFT butterfly process.
  @param[in,out] pSrc             points to the in-place buffer of Q31 data type.
  @param[in]     fftLen           length of the FFT.
  @param[in]     pCoef            points to twiddle coefficient buffer.
  @param[in]     twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.
  @return        none
 */

/*
 * Radix-4 IFFT algorithm used is :
 *
 * CIFFT uses same twiddle coefficients as CFFT Function
 *  x[k] = x[n] + (j)k * x[n + fftLen/4] + (-1)k * x[n+fftLen/2] + (-j)k * x[n+3*fftLen/4]
 *
 *
 * IFFT is implemented with following changes in equations from FFT
 *
 * Input real and imaginary data:
 * x(n) = xa + j * ya
 * x(n+N/4 ) = xb + j * yb
 * x(n+N/2 ) = xc + j * yc
 * x(n+3N 4) = xd + j * yd
 *
 *
 * Output real and imaginary data:
 * x(4r) = xa'+ j * ya'
 * x(4r+1) = xb'+ j * yb'
 * x(4r+2) = xc'+ j * yc'
 * x(4r+3) = xd'+ j * yd'
 *
 *
 * Twiddle factors for radix-4 IFFT:
 * Wn = co1 + j * (si1)
 * W2n = co2 + j * (si2)
 * W3n = co3 + j * (si3)
 
 * The real and imaginary output values for the radix-4 butterfly are
 * xa' = xa + xb + xc + xd
 * ya' = ya + yb + yc + yd
 * xb' = (xa-yb-xc+yd)* co1 - (ya+xb-yc-xd)* (si1)
 * yb' = (ya+xb-yc-xd)* co1 + (xa-yb-xc+yd)* (si1)
 * xc' = (xa-xb+xc-xd)* co2 - (ya-yb+yc-yd)* (si2)
 * yc' = (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2)
 * xd' = (xa+yb-xc-yd)* co3 - (ya-xb-yc+xd)* (si3)
 * yd' = (ya-xb-yc+xd)* co3 + (xa+yb-xc-yd)* (si3)
 *
 */

void arm_radix4_butterfly_inverse_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef,
        uint32_t twidCoefModifier)
{
        uint32_t n1, n2, ia1, ia2, ia3, i0, i1, i2, i3, j, k;
        q31_t t1, t2, r1, r2, s1, s2, co1, co2, co3, si1, si2, si3;
        q31_t xa, xb, xc, xd;
        q31_t ya, yb, yc, yd;
        q31_t xa_out, xb_out, xc_out, xd_out;
        q31_t ya_out, yb_out, yc_out, yd_out;
        
        q31_t *ptr1;

  /* input is be 1.31(q31) format for all FFT sizes */
  /* Total process is divided into three stages */
  /* process first stage, middle stages, & last stage */

  /* Start of first stage process */

  /* Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;
  /* n2 = fftLen/4 */
  n2 >>= 2U;
  i0 = 0U;
  ia1 = 0U;

  j = n2;

  do
  {
    /* input is in 1.31(q31) format and provide 4 guard bits for the input */

    /*  index calculation for the input as, */
    /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2U], pSrc[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Butterfly implementation */
    /* xa + xc */
    r1 = (pSrc[2U * i0] >> 4U) + (pSrc[2U * i2] >> 4U);
    /* xa - xc */
    r2 = (pSrc[2U * i0] >> 4U) - (pSrc[2U * i2] >> 4U);

    /* xb + xd */
    t1 = (pSrc[2U * i1] >> 4U) + (pSrc[2U * i3] >> 4U);

    /* ya + yc */
    s1 = (pSrc[(2U * i0) + 1U] >> 4U) + (pSrc[(2U * i2) + 1U] >> 4U);
    /* ya - yc */
    s2 = (pSrc[(2U * i0) + 1U] >> 4U) - (pSrc[(2U * i2) + 1U] >> 4U);

    /* xa' = xa + xb + xc + xd */
    pSrc[2U * i0] = (r1 + t1);
    /* (xa + xc) - (xb + xd) */
    r1 = r1 - t1;
    /* yb + yd */
    t2 = (pSrc[(2U * i1) + 1U] >> 4U) + (pSrc[(2U * i3) + 1U] >> 4U);
    /* ya' = ya + yb + yc + yd */
    pSrc[(2U * i0) + 1U] = (s1 + t2);

    /* (ya + yc) - (yb + yd) */
    s1 = s1 - t2;

    /* yb - yd */
    t1 = (pSrc[(2U * i1) + 1U] >> 4U) - (pSrc[(2U * i3) + 1U] >> 4U);
    /* xb - xd */
    t2 = (pSrc[2U * i1] >> 4U) - (pSrc[2U * i3] >> 4U);

    /*  index calculation for the coefficients */
    ia2 = 2U * ia1;
    co2 = pCoef[ia2 * 2U];
    si2 = pCoef[(ia2 * 2U) + 1U];

    /* xc' = (xa-xb+xc-xd)co2 - (ya-yb+yc-yd)(si2) */
    pSrc[2U * i1] = (((int32_t) (((q63_t) r1 * co2) >> 32)) -
                     ((int32_t) (((q63_t) s1 * si2) >> 32))) << 1U;

    /* yc' = (ya-yb+yc-yd)co2 + (xa-xb+xc-xd)(si2) */
    pSrc[2U * i1 + 1U] = (((int32_t) (((q63_t) s1 * co2) >> 32)) +
                          ((int32_t) (((q63_t) r1 * si2) >> 32))) << 1U;

    /* (xa - xc) - (yb - yd) */
    r1 = r2 - t1;
    /* (xa - xc) + (yb - yd) */
    r2 = r2 + t1;

    /* (ya - yc) + (xb - xd) */
    s1 = s2 + t2;
    /* (ya - yc) - (xb - xd) */
    s2 = s2 - t2;

    co1 = pCoef[ia1 * 2U];
    si1 = pCoef[(ia1 * 2U) + 1U];

    /* xb' = (xa+yb-xc-yd)co1 - (ya-xb-yc+xd)(si1) */
    pSrc[2U * i2] = (((int32_t) (((q63_t) r1 * co1) >> 32)) -
                     ((int32_t) (((q63_t) s1 * si1) >> 32))) << 1U;

    /* yb' = (ya-xb-yc+xd)co1 + (xa+yb-xc-yd)(si1) */
    pSrc[(2U * i2) + 1U] = (((int32_t) (((q63_t) s1 * co1) >> 32)) +
                            ((int32_t) (((q63_t) r1 * si1) >> 32))) << 1U;

    /*  index calculation for the coefficients */
    ia3 = 3U * ia1;
    co3 = pCoef[ia3 * 2U];
    si3 = pCoef[(ia3 * 2U) + 1U];

    /* xd' = (xa-yb-xc+yd)co3 - (ya+xb-yc-xd)(si3) */
    pSrc[2U * i3] = (((int32_t) (((q63_t) r2 * co3) >> 32)) -
                     ((int32_t) (((q63_t) s2 * si3) >> 32))) << 1U;

    /* yd' = (ya+xb-yc-xd)co3 + (xa-yb-xc+yd)(si3) */
    pSrc[(2U * i3) + 1U] = (((int32_t) (((q63_t) s2 * co3) >> 32)) +
                            ((int32_t) (((q63_t) r2 * si3) >> 32))) << 1U;

    /*  Twiddle coefficients index modifier */
    ia1 = ia1 + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1U;

  } while (--j);

  /* data is in 5.27(q27) format */
  /* each stage provides two down scaling of the input */


  /* Start of Middle stages process */

  twidCoefModifier <<= 2U;

  /*  Calculation of second stage to excluding last stage */
  for (k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    /*  Initializations for the first stage */
    n1 = n2;
    n2 >>= 2U;
    ia1 = 0U;

    for (j = 0; j <= (n2 - 1U); j++)
    {
      /*  index calculation for the coefficients */
      ia2 = ia1 + ia1;
      ia3 = ia2 + ia1;
      co1 = pCoef[(ia1 * 2U)];
      si1 = pCoef[(ia1 * 2U) + 1U];
      co2 = pCoef[(ia2 * 2U)];
      si2 = pCoef[(ia2 * 2U) + 1U];
      co3 = pCoef[(ia3 * 2U)];
      si3 = pCoef[(ia3 * 2U) + 1U];
      /*  Twiddle coefficients index modifier */
      ia1 = ia1 + twidCoefModifier;

      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2U], pSrc[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Butterfly implementation */
        /* xa + xc */
        r1 = pSrc[2U * i0] + pSrc[2U * i2];
        /* xa - xc */
        r2 = pSrc[2U * i0] - pSrc[2U * i2];

        /* ya + yc */
        s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];
        /* ya - yc */
        s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

        /* xb + xd */
        t1 = pSrc[2U * i1] + pSrc[2U * i3];

        /* xa' = xa + xb + xc + xd */
        pSrc[2U * i0] = (r1 + t1) >> 2U;
        /* xa + xc -(xb + xd) */
        r1 = r1 - t1;
        /* yb + yd */
        t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];
        /* ya' = ya + yb + yc + yd */
        pSrc[(2U * i0) + 1U] = (s1 + t2) >> 2U;

        /* (ya + yc) - (yb + yd) */
        s1 = s1 - t2;

        /* (yb - yd) */
        t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];
        /* (xb - xd) */
        t2 = pSrc[2U * i1] - pSrc[2U * i3];

        /* xc' = (xa-xb+xc-xd)co2 - (ya-yb+yc-yd)(si2) */
        pSrc[2U * i1] = (((int32_t) (((q63_t) r1 * co2) >> 32U)) -
                         ((int32_t) (((q63_t) s1 * si2) >> 32U))) >> 1U;

        /* yc' = (ya-yb+yc-yd)co2 + (xa-xb+xc-xd)(si2) */
        pSrc[(2U * i1) + 1U] = (((int32_t) (((q63_t) s1 * co2) >> 32U)) +
                                ((int32_t) (((q63_t) r1 * si2) >> 32U))) >> 1U;

        /* (xa - xc) - (yb - yd) */
        r1 = r2 - t1;
        /* (xa - xc) + (yb - yd) */
        r2 = r2 + t1;

        /* (ya - yc) +  (xb - xd) */
        s1 = s2 + t2;
        /* (ya - yc) -  (xb - xd) */
        s2 = s2 - t2;

        /* xb' = (xa+yb-xc-yd)co1 - (ya-xb-yc+xd)(si1) */
        pSrc[2U * i2] = (((int32_t) (((q63_t) r1 * co1) >> 32)) -
                         ((int32_t) (((q63_t) s1 * si1) >> 32))) >> 1U;

        /* yb' = (ya-xb-yc+xd)co1 + (xa+yb-xc-yd)(si1) */
        pSrc[(2U * i2) + 1U] = (((int32_t) (((q63_t) s1 * co1) >> 32)) +
                                ((int32_t) (((q63_t) r1 * si1) >> 32))) >> 1U;

        /* xd' = (xa-yb-xc+yd)co3 - (ya+xb-yc-xd)(si3) */
        pSrc[(2U * i3)] = (((int32_t) (((q63_t) r2 * co3) >> 32)) -
                           ((int32_t) (((q63_t) s2 * si3) >> 32))) >> 1U;

        /* yd' = (ya+xb-yc-xd)co3 + (xa-yb-xc+yd)(si3) */
        pSrc[(2U * i3) + 1U] = (((int32_t) (((q63_t) s2 * co3) >> 32)) +
                                ((int32_t) (((q63_t) r2 * si3) >> 32))) >> 1U;
      }
    }
    twidCoefModifier <<= 2U;
  }

  /* End of Middle stages process */

  /* data is in 11.21(q21) format for the 1024 point as there are 3 middle stages */
  /* data is in 9.23(q23) format for the 256 point as there are 2 middle stages */
  /* data is in 7.25(q25) format for the 64 point as there are 1 middle stage */
  /* data is in 5.27(q27) format for the 16 point as there are no middle stages */


  /* Start of last stage process */


  /*  Initializations for the last stage */
  j = fftLen >> 2;
  ptr1 = &pSrc[0];

  /*  Calculations of last stage */
  do
  {
    /* Read xa (real), ya(imag) input */
    xa = *ptr1++;
    ya = *ptr1++;

    /* Read xb (real), yb(imag) input */
    xb = *ptr1++;
    yb = *ptr1++;

    /* Read xc (real), yc(imag) input */
    xc = *ptr1++;
    yc = *ptr1++;

    /* Read xc (real), yc(imag) input */
    xd = *ptr1++;
    yd = *ptr1++;

    /* xa' = xa + xb + xc + xd */
    xa_out = xa + xb + xc + xd;

    /* ya' = ya + yb + yc + yd */
    ya_out = ya + yb + yc + yd;

    /* pointer updation for writing */
    ptr1 = ptr1 - 8U;

    /* writing xa' and ya' */
    *ptr1++ = xa_out;
    *ptr1++ = ya_out;

    xc_out = (xa - xb + xc - xd);
    yc_out = (ya - yb + yc - yd);

    /* writing xc' and yc' */
    *ptr1++ = xc_out;
    *ptr1++ = yc_out;

    xb_out = (xa - yb - xc + yd);
    yb_out = (ya + xb - yc - xd);

    /* writing xb' and yb' */
    *ptr1++ = xb_out;
    *ptr1++ = yb_out;

    xd_out = (xa + yb - xc - yd);
    yd_out = (ya - xb - yc + xd);

    /* writing xd' and yd' */
    *ptr1++ = xd_out;
    *ptr1++ = yd_out;

  } while (--j);

  /* output is in 11.21(q21) format for the 1024 point */
  /* output is in 9.23(q23) format for the 256 point */
  /* output is in 7.25(q25) format for the 64 point */
  /* output is in 5.27(q27) format for the 16 point */

  /* End of last stage process */
}

void arm_cfft_radix4by2_inverse_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef)
{
  uint32_t i, l;
  uint32_t n2;
  q31_t xt, yt, cosVal, sinVal;
  q31_t p0, p1;

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     cosVal = pCoef[2 * i];
     sinVal = pCoef[2 * i + 1];

     l = i + n2;

     xt =          (pSrc[2 * i] >> 2U) - (pSrc[2 * l] >> 2U);
     pSrc[2 * i] = (pSrc[2 * i] >> 2U) + (pSrc[2 * l] >> 2U);

     yt =              (pSrc[2 * i + 1] >> 2U) - (pSrc[2 * l + 1] >> 2U);
     pSrc[2 * i + 1] = (pSrc[2 * l + 1] >> 2U) + (pSrc[2 * i + 1] >> 2U);

     mult_32x32_keep32_R(p0, xt, cosVal);
     mult_32x32_keep32_R(p1, yt, cosVal);
     multSub_32x32_keep32_R(p0, yt, sinVal);
     multAcc_32x32_keep32_R(p1, xt, sinVal);

     pSrc[2 * l]     = p0 << 1U;
     pSrc[2 * l + 1] = p1 << 1U;
  }

  /* first col */
  arm_radix4_butterfly_inverse_q31( pSrc,          n2, (q31_t*)pCoef, 2U);

  /* second col */
  arm_radix4_butterfly_inverse_q31( pSrc + fftLen, n2, (q31_t*)pCoef, 2U);

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     p0 = pSrc[4 * i + 0];
     p1 = pSrc[4 * i + 1];
     xt = pSrc[4 * i + 2];
     yt = pSrc[4 * i + 3];

     p0 <<= 1U;
     p1 <<= 1U;
     xt <<= 1U;
     yt <<= 1U;

     pSrc[4 * i + 0] = p0;
     pSrc[4 * i + 1] = p1;
     pSrc[4 * i + 2] = xt;
     pSrc[4 * i + 3] = yt;
  }
}

/**
  @} end of ComplexFFT group
 */

/*
 * Radix-4 FFT algorithm used is :
 *
 * Input real and imaginary data:
 * x(n) = xa + j * ya
 * x(n+N/4 ) = xb + j * yb
 * x(n+N/2 ) = xc + j * yc
 * x(n+3N 4) = xd + j * yd
 *
 *
 * Output real and imaginary data:
 * x(4r) = xa'+ j * ya'
 * x(4r+1) = xb'+ j * yb'
 * x(4r+2) = xc'+ j * yc'
 * x(4r+3) = xd'+ j * yd'
 *
 *
 * Twiddle factors for radix-4 FFT:
 * Wn = co1 + j * (- si1)
 * W2n = co2 + j * (- si2)
 * W3n = co3 + j * (- si3)
 *
 *  Butterfly implementation:
 * xa' = xa + xb + xc + xd
 * ya' = ya + yb + yc + yd
 * xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1)
 * yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1)
 * xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2)
 * yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2)
 * xd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3)
 * yd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3)
 *
 */

/**
  @brief         Core function for the Q31 CFFT butterfly process.
  @param[in,out] pSrc             points to the in-place buffer of Q31 data type.
  @param[in]     fftLen           length of the FFT.
  @param[in]     pCoef            points to twiddle coefficient buffer.
  @param[in]     twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.
  @return        none
 */

void arm_radix4_butterfly_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef,
        uint32_t twidCoefModifier)
{
        uint32_t n1, n2, ia1, ia2, ia3, i0, i1, i2, i3, j, k;
        q31_t t1, t2, r1, r2, s1, s2, co1, co2, co3, si1, si2, si3;
        
        q31_t xa, xb, xc, xd;
        q31_t ya, yb, yc, yd;
        q31_t xa_out, xb_out, xc_out, xd_out;
        q31_t ya_out, yb_out, yc_out, yd_out;
        
        q31_t *ptr1;

  /* Total process is divided into three stages */

  /* process first stage, middle stages, & last stage */


  /* start of first stage process */

  /*  Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;
  /* n2 = fftLen/4 */
  n2 >>= 2U;
  i0 = 0U;
  ia1 = 0U;

  j = n2;

  /*  Calculation of first stage */
  do
  {
    /*  index calculation for the input as, */
    /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2U], pSrc[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /* input is in 1.31(q31) format and provide 4 guard bits for the input */

    /*  Butterfly implementation */
    /* xa + xc */
    r1 = (pSrc[(2U * i0)] >> 4U) + (pSrc[(2U * i2)] >> 4U);
    /* xa - xc */
    r2 = (pSrc[(2U * i0)] >> 4U) - (pSrc[(2U * i2)] >> 4U);

    /* xb + xd */
    t1 = (pSrc[(2U * i1)] >> 4U) + (pSrc[(2U * i3)] >> 4U);

    /* ya + yc */
    s1 = (pSrc[(2U * i0) + 1U] >> 4U) + (pSrc[(2U * i2) + 1U] >> 4U);
    /* ya - yc */
    s2 = (pSrc[(2U * i0) + 1U] >> 4U) - (pSrc[(2U * i2) + 1U] >> 4U);

    /* xa' = xa + xb + xc + xd */
    pSrc[2U * i0] = (r1 + t1);
    /* (xa + xc) - (xb + xd) */
    r1 = r1 - t1;
    /* yb + yd */
    t2 = (pSrc[(2U * i1) + 1U] >> 4U) + (pSrc[(2U * i3) + 1U] >> 4U);

    /* ya' = ya + yb + yc + yd */
    pSrc[(2U * i0) + 1U] = (s1 + t2);

    /* (ya + yc) - (yb + yd) */
    s1 = s1 - t2;

    /* yb - yd */
    t1 = (pSrc[(2U * i1) + 1U] >> 4U) - (pSrc[(2U * i3) + 1U] >> 4U);
    /* xb - xd */
    t2 = (pSrc[(2U * i1)] >> 4U) - (pSrc[(2U * i3)] >> 4U);

    /*  index calculation for the coefficients */
    ia2 = 2U * ia1;
    co2 = pCoef[(ia2 * 2U)];
    si2 = pCoef[(ia2 * 2U) + 1U];

    /* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */
    pSrc[2U * i1] = (((int32_t) (((q63_t) r1 * co2) >> 32)) +
                     ((int32_t) (((q63_t) s1 * si2) >> 32))) << 1U;

    /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */
    pSrc[(2U * i1) + 1U] = (((int32_t) (((q63_t) s1 * co2) >> 32)) -
                            ((int32_t) (((q63_t) r1 * si2) >> 32))) << 1U;

    /* (xa - xc) + (yb - yd) */
    r1 = r2 + t1;
    /* (xa - xc) - (yb - yd) */
    r2 = r2 - t1;

    /* (ya - yc) - (xb - xd) */
    s1 = s2 - t2;
    /* (ya - yc) + (xb - xd) */
    s2 = s2 + t2;

    co1 = pCoef[(ia1 * 2U)];
    si1 = pCoef[(ia1 * 2U) + 1U];

    /* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */
    pSrc[2U * i2] = (((int32_t) (((q63_t) r1 * co1) >> 32)) +
                     ((int32_t) (((q63_t) s1 * si1) >> 32))) << 1U;

    /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */
    pSrc[(2U * i2) + 1U] = (((int32_t) (((q63_t) s1 * co1) >> 32)) -
                            ((int32_t) (((q63_t) r1 * si1) >> 32))) << 1U;

    /*  index calculation for the coefficients */
    ia3 = 3U * ia1;
    co3 = pCoef[(ia3 * 2U)];
    si3 = pCoef[(ia3 * 2U) + 1U];

    /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */
    pSrc[2U * i3] = (((int32_t) (((q63_t) r2 * co3) >> 32)) +
                     ((int32_t) (((q63_t) s2 * si3) >> 32))) << 1U;

    /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */
    pSrc[(2U * i3) + 1U] = (((int32_t) (((q63_t) s2 * co3) >> 32)) -
                            ((int32_t) (((q63_t) r2 * si3) >> 32))) << 1U;

    /*  Twiddle coefficients index modifier */
    ia1 = ia1 + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1U;

  } while (--j);

  /* end of first stage process */

  /* data is in 5.27(q27) format */


  /* start of Middle stages process */


  /* each stage in middle stages provides two down scaling of the input */

  twidCoefModifier <<= 2U;


  for (k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    /*  Initializations for the first stage */
    n1 = n2;
    n2 >>= 2U;
    ia1 = 0U;

    /*  Calculation of first stage */
    for (j = 0U; j <= (n2 - 1U); j++)
    {
      /*  index calculation for the coefficients */
      ia2 = ia1 + ia1;
      ia3 = ia2 + ia1;
      co1 = pCoef[(ia1 * 2U)];
      si1 = pCoef[(ia1 * 2U) + 1U];
      co2 = pCoef[(ia2 * 2U)];
      si2 = pCoef[(ia2 * 2U) + 1U];
      co3 = pCoef[(ia3 * 2U)];
      si3 = pCoef[(ia3 * 2U) + 1U];
      /*  Twiddle coefficients index modifier */
      ia1 = ia1 + twidCoefModifier;

      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2U], pSrc[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Butterfly implementation */
        /* xa + xc */
        r1 = pSrc[2U * i0] + pSrc[2U * i2];
        /* xa - xc */
        r2 = pSrc[2U * i0] - pSrc[2U * i2];

        /* ya + yc */
        s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];
        /* ya - yc */
        s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

        /* xb + xd */
        t1 = pSrc[2U * i1] + pSrc[2U * i3];

        /* xa' = xa + xb + xc + xd */
        pSrc[2U * i0] = (r1 + t1) >> 2U;
        /* xa + xc -(xb + xd) */
        r1 = r1 - t1;

        /* yb + yd */
        t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];
        /* ya' = ya + yb + yc + yd */
        pSrc[(2U * i0) + 1U] = (s1 + t2) >> 2U;

        /* (ya + yc) - (yb + yd) */
        s1 = s1 - t2;

        /* (yb - yd) */
        t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];
        /* (xb - xd) */
        t2 = pSrc[2U * i1] - pSrc[2U * i3];

        /* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */
        pSrc[2U * i1] = (((int32_t) (((q63_t) r1 * co2) >> 32)) +
                         ((int32_t) (((q63_t) s1 * si2) >> 32))) >> 1U;

        /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */
        pSrc[(2U * i1) + 1U] = (((int32_t) (((q63_t) s1 * co2) >> 32)) -
                                ((int32_t) (((q63_t) r1 * si2) >> 32))) >> 1U;

        /* (xa - xc) + (yb - yd) */
        r1 = r2 + t1;
        /* (xa - xc) - (yb - yd) */
        r2 = r2 - t1;

        /* (ya - yc) -  (xb - xd) */
        s1 = s2 - t2;
        /* (ya - yc) +  (xb - xd) */
        s2 = s2 + t2;

        /* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */
        pSrc[2U * i2] = (((int32_t) (((q63_t) r1 * co1) >> 32)) +
                         ((int32_t) (((q63_t) s1 * si1) >> 32))) >> 1U;

        /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */
        pSrc[(2U * i2) + 1U] = (((int32_t) (((q63_t) s1 * co1) >> 32)) -
                                ((int32_t) (((q63_t) r1 * si1) >> 32))) >> 1U;

        /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */
        pSrc[2U * i3] = (((int32_t) (((q63_t) r2 * co3) >> 32)) +
                         ((int32_t) (((q63_t) s2 * si3) >> 32))) >> 1U;

        /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */
        pSrc[(2U * i3) + 1U] = (((int32_t) (((q63_t) s2 * co3) >> 32)) -
                                ((int32_t) (((q63_t) r2 * si3) >> 32))) >> 1U;
      }
    }
    twidCoefModifier <<= 2U;
  }

  /* End of Middle stages process */

  /* data is in 11.21(q21) format for the 1024 point as there are 3 middle stages */
  /* data is in 9.23(q23) format for the 256 point as there are 2 middle stages */
  /* data is in 7.25(q25) format for the 64 point as there are 1 middle stage */
  /* data is in 5.27(q27) format for the 16 point as there are no middle stages */


  /* start of Last stage process */
  /*  Initializations for the last stage */
  j = fftLen >> 2;
  ptr1 = &pSrc[0];

  /*  Calculations of last stage */
  do
  {
    /* Read xa (real), ya(imag) input */
    xa = *ptr1++;
    ya = *ptr1++;

    /* Read xb (real), yb(imag) input */
    xb = *ptr1++;
    yb = *ptr1++;

    /* Read xc (real), yc(imag) input */
    xc = *ptr1++;
    yc = *ptr1++;

    /* Read xc (real), yc(imag) input */
    xd = *ptr1++;
    yd = *ptr1++;

    /* xa' = xa + xb + xc + xd */
    xa_out = xa + xb + xc + xd;

    /* ya' = ya + yb + yc + yd */
    ya_out = ya + yb + yc + yd;

    /* pointer updation for writing */
    ptr1 = ptr1 - 8U;

    /* writing xa' and ya' */
    *ptr1++ = xa_out;
    *ptr1++ = ya_out;

    xc_out = (xa - xb + xc - xd);
    yc_out = (ya - yb + yc - yd);

    /* writing xc' and yc' */
    *ptr1++ = xc_out;
    *ptr1++ = yc_out;

    xb_out = (xa + yb - xc - yd);
    yb_out = (ya - xb - yc + xd);

    /* writing xb' and yb' */
    *ptr1++ = xb_out;
    *ptr1++ = yb_out;

    xd_out = (xa - yb - xc + yd);
    yd_out = (ya + xb - yc - xd);

    /* writing xd' and yd' */
    *ptr1++ = xd_out;
    *ptr1++ = yd_out;


  } while (--j);

  /* output is in 11.21(q21) format for the 1024 point */
  /* output is in 9.23(q23) format for the 256 point */
  /* output is in 7.25(q25) format for the 64 point */
  /* output is in 5.27(q27) format for the 16 point */

  /* End of last stage process */

}

/**
  @} end of ComplexFFT group
 */

void arm_cfft_radix4by2_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef)
{
        uint32_t i, l;
        uint32_t n2;
        q31_t xt, yt, cosVal, sinVal;
        q31_t p0, p1;

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     cosVal = pCoef[2 * i];
     sinVal = pCoef[2 * i + 1];

     l = i + n2;

     xt =          (pSrc[2 * i] >> 2U) - (pSrc[2 * l] >> 2U);
     pSrc[2 * i] = (pSrc[2 * i] >> 2U) + (pSrc[2 * l] >> 2U);

     yt =              (pSrc[2 * i + 1] >> 2U) - (pSrc[2 * l + 1] >> 2U);
     pSrc[2 * i + 1] = (pSrc[2 * l + 1] >> 2U) + (pSrc[2 * i + 1] >> 2U);

     mult_32x32_keep32_R(p0, xt, cosVal);
     mult_32x32_keep32_R(p1, yt, cosVal);
     multAcc_32x32_keep32_R(p0, yt, sinVal);
     multSub_32x32_keep32_R(p1, xt, sinVal);

     pSrc[2 * l]     = p0 << 1;
     pSrc[2 * l + 1] = p1 << 1;
  }

  /* first col */
  arm_radix4_butterfly_q31 (pSrc,          n2, (q31_t*)pCoef, 2U);

  /* second col */
  arm_radix4_butterfly_q31 (pSrc + fftLen, n2, (q31_t*)pCoef, 2U);

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     p0 = pSrc[4 * i + 0];
     p1 = pSrc[4 * i + 1];
     xt = pSrc[4 * i + 2];
     yt = pSrc[4 * i + 3];

     p0 <<= 1U;
     p1 <<= 1U;
     xt <<= 1U;
     yt <<= 1U;

     pSrc[4 * i + 0] = p0;
     pSrc[4 * i + 1] = p1;
     pSrc[4 * i + 2] = xt;
     pSrc[4 * i + 3] = yt;
  }

}

/**
  @brief         In-place 32 bit reversal function.
  @param[in,out] pSrc        points to in-place buffer of unknown 32-bit data type
  @param[in]     bitRevLen   bit reversal table length
  @param[in]     pBitRevTab  points to bit reversal table
  @return        none
*/

void arm_bitreversal_32(
        uint32_t *pSrc, 
  const uint16_t bitRevLen, 
  const uint16_t *pBitRevTab)
{
  uint32_t a, b, i, tmp;

  for (i = 0; i < bitRevLen; )
  {
     a = pBitRevTab[i    ] >> 2;
     b = pBitRevTab[i + 1] >> 2;

     //real
     tmp = pSrc[a];
     pSrc[a] = pSrc[b];
     pSrc[b] = tmp;

     //complex
     tmp = pSrc[a+1];
     pSrc[a+1] = pSrc[b+1];
     pSrc[b+1] = tmp;

    i += 2;
  }
}


/**
  @ingroup groupTransforms
 */

/**
  @addtogroup ComplexFFT
  @{
 */

/**
  @brief         Processing function for the Q31 complex FFT.
  @param[in]     S               points to an instance of the fixed-point CFFT structure
  @param[in,out] p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place
  @param[in]     ifftFlag       flag that selects transform direction
                   - value = 0: forward transform
                   - value = 1: inverse transform
  @param[in]     bitReverseFlag flag that enables / disables bit reversal of output
                   - value = 0: disables bit reversal of output
                   - value = 1: enables bit reversal of output
  @return        none
 */

void arm_cfft_q31(
  const arm_cfft_instance_q31 * S,
        q31_t * p1,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
  uint32_t L = S->fftLen;

  if (ifftFlag == 1U)
  {
     switch (L)
     {
     case 16:
     case 64:
     case 256:
     case 1024:
     case 4096:
       arm_radix4_butterfly_inverse_q31 ( p1, L, (q31_t*)S->pTwiddle, 1 );
       break;

     case 32:
     case 128:
     case 512:
     case 2048:
	  //WitinKwsLog("do not support!!!\n");
       break;
     }
  }
  else
  {
     switch (L)
     {
     case 16:
     case 64:
     case 256:
     case 1024:
     case 4096:
       arm_radix4_butterfly_q31 ( p1, L, (q31_t*)S->pTwiddle, 1 );
       break;

     case 32:
     case 128:
     case 512:
     case 2048:
       //WitinKwsLog("do not support!!!\n");
       break;
     }
  }

  if ( bitReverseFlag )
    arm_bitreversal_32 ((uint32_t*) p1, S->bitRevLength, S->pBitRevTable);
}

/**
  @} end of RealFFT group
 */

/**
  @brief         Core Real FFT process
  @param[in]     pSrc      points to input buffer
  @param[in]     fftLen    length of FFT
  @param[in]     pATable   points to twiddle Coef A buffer
  @param[in]     pBTable   points to twiddle Coef B buffer
  @param[out]    pDst      points to output buffer
  @param[in]     modifier  twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table
  @return        none
 */

void arm_split_rfft_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pATable,
  const q31_t * pBTable,
        q31_t * pDst,
        uint32_t modifier)
{
        uint32_t i;                                    /* Loop Counter */
        q31_t outR, outI;                              /* Temporary variables for output */
  const q31_t *pCoefA, *pCoefB;                        /* Temporary pointers for twiddle factors */
        q31_t CoefA1, CoefA2, CoefB1;                  /* Temporary variables for twiddle coefficients */
        q31_t *pOut1 = &pDst[2], *pOut2 = &pDst[4 * fftLen - 1];
        q31_t *pIn1 =  &pSrc[2], *pIn2 =  &pSrc[2 * fftLen - 1];

  /* Init coefficient pointers */
  pCoefA = &pATable[0];
  pCoefB = &pBTable[0];

  i = fftLen - 1U;

  while (i > 0U)
  {
     /*
       outR = (  pSrc[2 * i]             * pATable[2 * i]
               - pSrc[2 * i + 1]         * pATable[2 * i + 1]
               + pSrc[2 * n - 2 * i]     * pBTable[2 * i]
               + pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);

       outI = (  pIn[2 * i + 1]         * pATable[2 * i]
               + pIn[2 * i]             * pATable[2 * i + 1]
               + pIn[2 * n - 2 * i]     * pBTable[2 * i + 1]
               - pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);
      */
     CoefA1 = *pCoefA++;
     CoefA2 = *pCoefA++;


     /* outR = (pSrc[2 * i] * pATable[2 * i] */
     mult_32x32_keep32_R (outR, *pIn1, CoefA1);

     /* outI = pIn[2 * i] * pATable[2 * i + 1] */
     mult_32x32_keep32_R (outI, *pIn1++, CoefA2);

     /* - pSrc[2 * i + 1] * pATable[2 * i + 1] */
     multSub_32x32_keep32_R (outR, *pIn1, CoefA2);

     /* (pIn[2 * i + 1] * pATable[2 * i] */
     multAcc_32x32_keep32_R (outI, *pIn1++, CoefA1);

     /* pSrc[2 * n - 2 * i] * pBTable[2 * i]  */
     multSub_32x32_keep32_R (outR, *pIn2, CoefA2);
     CoefB1 = *pCoefB++;

     /* pIn[2 * n - 2 * i] * pBTable[2 * i + 1] */
     multSub_32x32_keep32_R (outI, *pIn2--, CoefB1);

     /* pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1] */
     multAcc_32x32_keep32_R (outR, *pIn2, CoefB1);

     /* pIn[2 * n - 2 * i + 1] * pBTable[2 * i] */
     multSub_32x32_keep32_R (outI, *pIn2--, CoefA2);
	 

     /* write output */
     *pOut1++ = outR;
     *pOut1++ = outI;

     /* write complex conjugate output */
     *pOut2-- = -outI;
     *pOut2-- = outR;

     /* Decrement loop count */
     i--;
  }

  pDst[2 * fftLen]     = (pSrc[0] - pSrc[1]) >> 1U;
  pDst[2 * fftLen + 1] = 0;

  pDst[0] = (pSrc[0] + pSrc[1]) >> 1U;
  pDst[1] = 0;
}

/**
  @addtogroup RealFFT
  @{
 */

/**
  @brief         Processing function for the Q31 RFFT/RIFFT.
  @param[in]     S     points to an instance of the Q31 RFFT/RIFFT structure
  @param[in]     pSrc  points to input buffer
  @param[out]    pDst  points to output buffer
  @return        none

  @par           Input an output formats
                   Internally input is downscaled by 2 for every stage to avoid saturations inside CFFT/CIFFT process.
                   Hence the output format is different for different RFFT sizes.
                   The input and output formats for different RFFT sizes and number of bits to upscale are mentioned in the tables below for RFFT and RIFFT:
  @par
                   \image html RFFTQ31.gif "Input and Output Formats for Q31 RFFT"
  @par
                   \image html RIFFTQ31.gif "Input and Output Formats for Q31 RIFFT"
 */

void arm_rfft_q31(
  const arm_rfft_instance_q31 * S,
        q31_t * pSrc,
        q31_t * pDst)
{
  const arm_cfft_instance_q31 *S_CFFT = S->pCfft;
        uint32_t L2 = S->fftLenReal >> 1U;

  /* Calculation of RIFFT of input */
  if (S->ifftFlagR == 1U)
  {
	  //WitinKwsLog("do not support ifft due to table size modify, please modify code !!!\n");
  }
  else
  {
     /* Calculation of RFFT of input */

     /* Complex FFT process */
     arm_cfft_q31 (S_CFFT, pSrc, S->ifftFlagR, S->bitReverseFlagR);

     /*  Real FFT core process */
     arm_split_rfft_q31 (pSrc, L2, S->pTwiddleAReal, S->pTwiddleBReal, pDst, S->twidCoefRModifier);
  }
}

/**
  @addtogroup RealFFT
  @{
 */

/**
  @brief         Initialization function for the Q31 RFFT/RIFFT.
  @param[in,out] S              points to an instance of the Q31 RFFT/RIFFT structure
  @param[in]     fftLenReal     length of the FFT
  @param[in]     ifftFlagR      flag that selects transform direction
                   - value = 0: forward transform
                   - value = 1: inverse transform
  @param[in]     bitReverseFlag flag that enables / disables bit reversal of output
                   - value = 0: disables bit reversal of output
                   - value = 1: enables bit reversal of output
  @return        execution status
                   - \ref ARM_MATH_SUCCESS        : Operation successful
                   - \ref ARM_MATH_ARGUMENT_ERROR : <code>fftLenReal</code> is not a supported length

  @par           Details
                   The parameter <code>fftLenReal</code> specifies length of RFFT/RIFFT Process.
                   Supported FFT Lengths are 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192.
  @par
                   The parameter <code>ifftFlagR</code> controls whether a forward or inverse transform is computed.
                   Set(=1) ifftFlagR to calculate RIFFT, otherwise RFFT is calculated.
  @par
                   The parameter <code>bitReverseFlag</code> controls whether output is in normal order or bit reversed order.
                   Set(=1) bitReverseFlag for output to be in normal order otherwise output is in bit reversed order.
  @par
                   This function also initializes Twiddle factor table.
*/

arm_status arm_rfft_init_q31(
    arm_rfft_instance_q31 * S,
    uint32_t fftLenReal,
    uint32_t ifftFlagR,
    uint32_t bitReverseFlag)
{
    /*  Initialise the default arm status */
    arm_status status = ARM_MATH_SUCCESS;

    /*  Initialize the Real FFT length */
    S->fftLenReal = (uint16_t) fftLenReal;

    /*  Initialize the Twiddle coefficientA pointer */
    S->pTwiddleAReal = (q31_t *) realCoefAQ31;

    /*  Initialize the Twiddle coefficientB pointer */
    S->pTwiddleBReal = (q31_t *) realCoefBQ31;

    /*  Initialize the Flag for selection of RFFT or RIFFT */
    S->ifftFlagR = (uint8_t) ifftFlagR;

    /*  Initialize the Flag for calculation Bit reversal or not */
    S->bitReverseFlagR = (uint8_t) bitReverseFlag;

    /*  Initialization of coef modifier depending on the FFT length */
    switch (S->fftLenReal)
    {
    case 512U:
        S->twidCoefRModifier = 16U;
        S->pCfft = &arm_cfft_sR_q31_len256;
        break;

    default:
        /*  Reporting argument error if rfftSize is not valid value */
        status = ARM_MATH_ARGUMENT_ERROR;
        break;
    }

    /* return the status of RFFT Init function */
    return (status);
}

/**
  @par
  Generation fixed-point realCoefAQ31 array in Q31 format:
  @par
  n = 4096
  <pre>for (i = 0; i < n; i++)
  {
     pATable[2 * i]     = 0.5 * ( 1.0 - sin (2 * PI / (double) (2 * n) * (double) i));
     pATable[2 * i + 1] = 0.5 * (-1.0 * cos (2 * PI / (double) (2 * n) * (double) i));
  }</pre>
  @par
  Convert to fixed point Q31 format
      round(pATable[i] * pow(2, 31))
*/
const q31_t realCoefAQ31[510] = {
(q31_t)0x3f36f170, (q31_t)0xc0013bd3, (q31_t)0x3e6deaa1, (q31_t)0xc004ef3f, (q31_t)0x3da4f351, 
 (q31_t)0xc00b1a20, (q31_t)0x3cdc1342, (q31_t)0xc013bc39, (q31_t)0x3c135231, (q31_t)0xc01ed535, (q31_t)0x3b4ab7db, 
 (q31_t)0xc02c64a6, (q31_t)0x3a824bfd, (q31_t)0xc03c6a07, (q31_t)0x39ba1651, (q31_t)0xc04ee4b8, (q31_t)0x38f21e8e, 
 (q31_t)0xc063d405, (q31_t)0x382a6c6a, (q31_t)0xc07b371e, (q31_t)0x37630799, (q31_t)0xc0950d1d, (q31_t)0x369bf7c9, 
 (q31_t)0xc0b15502, (q31_t)0x35d544a7, (q31_t)0xc0d00db6, (q31_t)0x350ef5de, (q31_t)0xc0f1360b, (q31_t)0x34491311, 
 (q31_t)0xc114ccb9, (q31_t)0x3383a3e2, (q31_t)0xc13ad060, (q31_t)0x32beafed, (q31_t)0xc1633f8a, (q31_t)0x31fa3ecb, 
 (q31_t)0xc18e18a7, (q31_t)0x3136580d, (q31_t)0xc1bb5a11, (q31_t)0x30730342, (q31_t)0xc1eb0209, (q31_t)0x2fb047f2, 
 (q31_t)0xc21d0eb8, (q31_t)0x2eee2d9d, (q31_t)0xc2517e31, (q31_t)0x2e2cbbc1, (q31_t)0xc2884e6e, (q31_t)0x2d6bf9d1, 
 (q31_t)0xc2c17d52, (q31_t)0x2cabef3d, (q31_t)0xc2fd08a9, (q31_t)0x2beca36c, (q31_t)0xc33aee27, (q31_t)0x2b2e1dbe, 
 (q31_t)0xc37b2b6a, (q31_t)0x2a70658a, (q31_t)0xc3bdbdf6, (q31_t)0x29b38223, (q31_t)0xc402a33c, (q31_t)0x28f77acf, 
 (q31_t)0xc449d892, (q31_t)0x283c56cf, (q31_t)0xc4935b3c, (q31_t)0x27821d59, (q31_t)0xc4df2862, (q31_t)0x26c8d59c, 
 (q31_t)0xc52d3d18, (q31_t)0x261086bc, (q31_t)0xc57d965d, (q31_t)0x255937d5, (q31_t)0xc5d03118, (q31_t)0x24a2eff6, 
 (q31_t)0xc6250a18, (q31_t)0x23edb628, (q31_t)0xc67c1e18, (q31_t)0x23399167, (q31_t)0xc6d569be, (q31_t)0x228688a4, 
 (q31_t)0xc730e997, (q31_t)0x21d4a2c8, (q31_t)0xc78e9a1d, (q31_t)0x2123e6ad, (q31_t)0xc7ee77b3, (q31_t)0x20745b24, 
 (q31_t)0xc8507ea7, (q31_t)0x1fc606f1, (q31_t)0xc8b4ab32, (q31_t)0x1f18f0ce, (q31_t)0xc91af976, (q31_t)0x1e6d1f65, 
 (q31_t)0xc9836582, (q31_t)0x1dc29958, (q31_t)0xc9edeb50, (q31_t)0x1d196538, (q31_t)0xca5a86c4, (q31_t)0x1c71898d, 
 (q31_t)0xcac933ae, (q31_t)0x1bcb0cce, (q31_t)0xcb39edca, (q31_t)0x1b25f566, (q31_t)0xcbacb0bf, (q31_t)0x1a8249b4, 
 (q31_t)0xcc217822, (q31_t)0x19e01006, (q31_t)0xcc983f70, (q31_t)0x193f4e9e, (q31_t)0xcd110216, (q31_t)0x18a00bae, 
 (q31_t)0xcd8bbb6d, (q31_t)0x18024d59, (q31_t)0xce0866b8, (q31_t)0x176619b6, (q31_t)0xce86ff2a, (q31_t)0x16cb76c9, 
 (q31_t)0xcf077fe1, (q31_t)0x16326a88, (q31_t)0xcf89e3e8, (q31_t)0x159afadb, (q31_t)0xd00e2639, (q31_t)0x15052d97, 
 (q31_t)0xd09441bb, (q31_t)0x14710883, (q31_t)0xd11c3142, (q31_t)0x13de9156, (q31_t)0xd1a5ef90, (q31_t)0x134dcdb4, 
 (q31_t)0xd2317756, (q31_t)0x12bec333, (q31_t)0xd2bec333, (q31_t)0x12317756, (q31_t)0xd34dcdb4, (q31_t)0x11a5ef90, 
 (q31_t)0xd3de9156, (q31_t)0x111c3142, (q31_t)0xd4710883, (q31_t)0x109441bb, (q31_t)0xd5052d97, (q31_t)0x100e2639, 
 (q31_t)0xd59afadb, (q31_t)0xf89e3e8, (q31_t)0xd6326a88, (q31_t)0xf077fe1, (q31_t)0xd6cb76c9, (q31_t)0xe86ff2a, 
 (q31_t)0xd76619b6, (q31_t)0xe0866b8, (q31_t)0xd8024d59, (q31_t)0xd8bbb6d, (q31_t)0xd8a00bae, (q31_t)0xd110216, 
 (q31_t)0xd93f4e9e, (q31_t)0xc983f70, (q31_t)0xd9e01006, (q31_t)0xc217822, (q31_t)0xda8249b4, (q31_t)0xbacb0bf, 
 (q31_t)0xdb25f566, (q31_t)0xb39edca, (q31_t)0xdbcb0cce, (q31_t)0xac933ae, (q31_t)0xdc71898d, (q31_t)0xa5a86c4, 
 (q31_t)0xdd196538, (q31_t)0x9edeb50, (q31_t)0xddc29958, (q31_t)0x9836582, (q31_t)0xde6d1f65, (q31_t)0x91af976, 
 (q31_t)0xdf18f0ce, (q31_t)0x8b4ab32, (q31_t)0xdfc606f1, (q31_t)0x8507ea7, (q31_t)0xe0745b24, (q31_t)0x7ee77b3, 
 (q31_t)0xe123e6ad, (q31_t)0x78e9a1d, (q31_t)0xe1d4a2c8, (q31_t)0x730e997, (q31_t)0xe28688a4, (q31_t)0x6d569be, 
 (q31_t)0xe3399167, (q31_t)0x67c1e18, (q31_t)0xe3edb628, (q31_t)0x6250a18, (q31_t)0xe4a2eff6, (q31_t)0x5d03118, 
 (q31_t)0xe55937d5, (q31_t)0x57d965d, (q31_t)0xe61086bc, (q31_t)0x52d3d18, (q31_t)0xe6c8d59c, (q31_t)0x4df2862, 
 (q31_t)0xe7821d59, (q31_t)0x4935b3c, (q31_t)0xe83c56cf, (q31_t)0x449d892, (q31_t)0xe8f77acf, (q31_t)0x402a33c, 
 (q31_t)0xe9b38223, (q31_t)0x3bdbdf6, (q31_t)0xea70658a, (q31_t)0x37b2b6a, (q31_t)0xeb2e1dbe, (q31_t)0x33aee27, 
 (q31_t)0xebeca36c, (q31_t)0x2fd08a9, (q31_t)0xecabef3d, (q31_t)0x2c17d52, (q31_t)0xed6bf9d1, (q31_t)0x2884e6e, 
 (q31_t)0xee2cbbc1, (q31_t)0x2517e31, (q31_t)0xeeee2d9d, (q31_t)0x21d0eb8, (q31_t)0xefb047f2, (q31_t)0x1eb0209, 
 (q31_t)0xf0730342, (q31_t)0x1bb5a11, (q31_t)0xf136580d, (q31_t)0x18e18a7, (q31_t)0xf1fa3ecb, (q31_t)0x1633f8a, 
 (q31_t)0xf2beafed, (q31_t)0x13ad060, (q31_t)0xf383a3e2, (q31_t)0x114ccb9, (q31_t)0xf4491311, (q31_t)0xf1360b, 
 (q31_t)0xf50ef5de, (q31_t)0xd00db6, (q31_t)0xf5d544a7, (q31_t)0xb15502, (q31_t)0xf69bf7c9, (q31_t)0x950d1d, 
 (q31_t)0xf7630799, (q31_t)0x7b371e, (q31_t)0xf82a6c6a, (q31_t)0x63d405, (q31_t)0xf8f21e8e, (q31_t)0x4ee4b8, 
 (q31_t)0xf9ba1651, (q31_t)0x3c6a07, (q31_t)0xfa824bfd, (q31_t)0x2c64a6, (q31_t)0xfb4ab7db, (q31_t)0x1ed535, 
 (q31_t)0xfc135231, (q31_t)0x13bc39, (q31_t)0xfcdc1342, (q31_t)0xb1a20, (q31_t)0xfda4f351, (q31_t)0x4ef3f, 
 (q31_t)0xfe6deaa1, (q31_t)0x13bd3, (q31_t)0xff36f170, (q31_t)0x0, (q31_t)0x0, (q31_t)0x13bd3, 
 (q31_t)0xc90e90, (q31_t)0x4ef3f, (q31_t)0x192155f, (q31_t)0xb1a20, (q31_t)0x25b0caf, (q31_t)0x13bc39, 
 (q31_t)0x323ecbe, (q31_t)0x1ed535, (q31_t)0x3ecadcf, (q31_t)0x2c64a6, (q31_t)0x4b54825, (q31_t)0x3c6a07, 
 (q31_t)0x57db403, (q31_t)0x4ee4b8, (q31_t)0x645e9af, (q31_t)0x63d405, (q31_t)0x70de172, (q31_t)0x7b371e, 
 (q31_t)0x7d59396, (q31_t)0x950d1d, (q31_t)0x89cf867, (q31_t)0xb15502, (q31_t)0x9640837, (q31_t)0xd00db6, 
 (q31_t)0xa2abb59, (q31_t)0xf1360b, (q31_t)0xaf10a22, (q31_t)0x114ccb9, (q31_t)0xbb6ecef, (q31_t)0x13ad060, 
 (q31_t)0xc7c5c1e, (q31_t)0x1633f8a, (q31_t)0xd415013, (q31_t)0x18e18a7, (q31_t)0xe05c135, (q31_t)0x1bb5a11, 
 (q31_t)0xec9a7f3, (q31_t)0x1eb0209, (q31_t)0xf8cfcbe, (q31_t)0x21d0eb8, (q31_t)0x104fb80e, (q31_t)0x2517e31, 
 (q31_t)0x1111d263, (q31_t)0x2884e6e, (q31_t)0x11d3443f, (q31_t)0x2c17d52, (q31_t)0x1294062f, (q31_t)0x2fd08a9, 
 (q31_t)0x135410c3, (q31_t)0x33aee27, (q31_t)0x14135c94, (q31_t)0x37b2b6a, (q31_t)0x14d1e242, (q31_t)0x3bdbdf6, 
 (q31_t)0x158f9a76, (q31_t)0x402a33c, (q31_t)0x164c7ddd, (q31_t)0x449d892, (q31_t)0x17088531, (q31_t)0x4935b3c, 
 (q31_t)0x17c3a931, (q31_t)0x4df2862, (q31_t)0x187de2a7, (q31_t)0x52d3d18, (q31_t)0x19372a64, (q31_t)0x57d965d, 
 (q31_t)0x19ef7944, (q31_t)0x5d03118, (q31_t)0x1aa6c82b, (q31_t)0x6250a18, (q31_t)0x1b5d100a, (q31_t)0x67c1e18, 
 (q31_t)0x1c1249d8, (q31_t)0x6d569be, (q31_t)0x1cc66e99, (q31_t)0x730e997, (q31_t)0x1d79775c, (q31_t)0x78e9a1d, 
 (q31_t)0x1e2b5d38, (q31_t)0x7ee77b3, (q31_t)0x1edc1953, (q31_t)0x8507ea7, (q31_t)0x1f8ba4dc, (q31_t)0x8b4ab32, 
 (q31_t)0x2039f90f, (q31_t)0x91af976, (q31_t)0x20e70f32, (q31_t)0x9836582, (q31_t)0x2192e09b, (q31_t)0x9edeb50, 
 (q31_t)0x223d66a8, (q31_t)0xa5a86c4, (q31_t)0x22e69ac8, (q31_t)0xac933ae, (q31_t)0x238e7673, (q31_t)0xb39edca, 
 (q31_t)0x2434f332, (q31_t)0xbacb0bf, (q31_t)0x24da0a9a, (q31_t)0xc217822, (q31_t)0x257db64c, (q31_t)0xc983f70, 
 (q31_t)0x261feffa, (q31_t)0xd110216, (q31_t)0x26c0b162, (q31_t)0xd8bbb6d, (q31_t)0x275ff452, (q31_t)0xe0866b8, 
 (q31_t)0x27fdb2a7, (q31_t)0xe86ff2a, (q31_t)0x2899e64a, (q31_t)0xf077fe1, (q31_t)0x29348937, (q31_t)0xf89e3e8, 
 (q31_t)0x29cd9578, (q31_t)0x100e2639, (q31_t)0x2a650525, (q31_t)0x109441bb, (q31_t)0x2afad269, (q31_t)0x111c3142, 
 (q31_t)0x2b8ef77d, (q31_t)0x11a5ef90, (q31_t)0x2c216eaa, (q31_t)0x12317756, (q31_t)0x2cb2324c, (q31_t)0x12bec333, 
 (q31_t)0x2d413ccd, (q31_t)0x134dcdb4, (q31_t)0x2dce88aa, (q31_t)0x13de9156, (q31_t)0x2e5a1070, (q31_t)0x14710883, 
 (q31_t)0x2ee3cebe, (q31_t)0x15052d97, (q31_t)0x2f6bbe45, (q31_t)0x159afadb, (q31_t)0x2ff1d9c7, (q31_t)0x16326a88, 
 (q31_t)0x30761c18, (q31_t)0x16cb76c9, (q31_t)0x30f8801f, (q31_t)0x176619b6, (q31_t)0x317900d6, (q31_t)0x18024d59, 
 (q31_t)0x31f79948, (q31_t)0x18a00bae, (q31_t)0x32744493, (q31_t)0x193f4e9e, (q31_t)0x32eefdea, (q31_t)0x19e01006, 
 (q31_t)0x3367c090, (q31_t)0x1a8249b4, (q31_t)0x33de87de, (q31_t)0x1b25f566, (q31_t)0x34534f41, (q31_t)0x1bcb0cce, 
 (q31_t)0x34c61236, (q31_t)0x1c71898d, (q31_t)0x3536cc52, (q31_t)0x1d196538, (q31_t)0x35a5793c, (q31_t)0x1dc29958, 
 (q31_t)0x361214b0, (q31_t)0x1e6d1f65, (q31_t)0x367c9a7e, (q31_t)0x1f18f0ce, (q31_t)0x36e5068a, (q31_t)0x1fc606f1, 
 (q31_t)0x374b54ce, (q31_t)0x20745b24, (q31_t)0x37af8159, (q31_t)0x2123e6ad, (q31_t)0x3811884d, (q31_t)0x21d4a2c8, 
 (q31_t)0x387165e3, (q31_t)0x228688a4, (q31_t)0x38cf1669, (q31_t)0x23399167, (q31_t)0x392a9642, (q31_t)0x23edb628, 
 (q31_t)0x3983e1e8, (q31_t)0x24a2eff6, (q31_t)0x39daf5e8, (q31_t)0x255937d5, (q31_t)0x3a2fcee8, (q31_t)0x261086bc, 
 (q31_t)0x3a8269a3, (q31_t)0x26c8d59c, (q31_t)0x3ad2c2e8, (q31_t)0x27821d59, (q31_t)0x3b20d79e, (q31_t)0x283c56cf, 
 (q31_t)0x3b6ca4c4, (q31_t)0x28f77acf, (q31_t)0x3bb6276e, (q31_t)0x29b38223, (q31_t)0x3bfd5cc4, (q31_t)0x2a70658a, 
 (q31_t)0x3c42420a, (q31_t)0x2b2e1dbe, (q31_t)0x3c84d496, (q31_t)0x2beca36c, (q31_t)0x3cc511d9, (q31_t)0x2cabef3d, 
 (q31_t)0x3d02f757, (q31_t)0x2d6bf9d1, (q31_t)0x3d3e82ae, (q31_t)0x2e2cbbc1, (q31_t)0x3d77b192, (q31_t)0x2eee2d9d, 
 (q31_t)0x3dae81cf, (q31_t)0x2fb047f2, (q31_t)0x3de2f148, (q31_t)0x30730342, (q31_t)0x3e14fdf7, (q31_t)0x3136580d, 
 (q31_t)0x3e44a5ef, (q31_t)0x31fa3ecb, (q31_t)0x3e71e759, (q31_t)0x32beafed, (q31_t)0x3e9cc076, (q31_t)0x3383a3e2, 
 (q31_t)0x3ec52fa0, (q31_t)0x34491311, (q31_t)0x3eeb3347, (q31_t)0x350ef5de, (q31_t)0x3f0ec9f5, (q31_t)0x35d544a7, 
 (q31_t)0x3f2ff24a, (q31_t)0x369bf7c9, (q31_t)0x3f4eaafe, (q31_t)0x37630799, (q31_t)0x3f6af2e3, (q31_t)0x382a6c6a, 
 (q31_t)0x3f84c8e2, (q31_t)0x38f21e8e, (q31_t)0x3f9c2bfb, (q31_t)0x39ba1651, (q31_t)0x3fb11b48, (q31_t)0x3a824bfd, 
 (q31_t)0x3fc395f9, (q31_t)0x3b4ab7db, (q31_t)0x3fd39b5a, (q31_t)0x3c135231, (q31_t)0x3fe12acb, (q31_t)0x3cdc1342, 
 (q31_t)0x3fec43c7, (q31_t)0x3da4f351, (q31_t)0x3ff4e5e0, (q31_t)0x3e6deaa1, (q31_t)0x3ffb10c1, (q31_t)0x3f36f170, 
 (q31_t)0x3ffec42d
};

/**
  @par
  Generation of realCoefBQ31 array:
  @par
   n = 4096
  <pre>for (i = 0; i < n; i++)
  {
     pBTable[2 * i]     = 0.5 * (1.0 + sin (2 * PI / (double) (2 * n) * (double) i));
     pBTable[2 * i + 1] = 0.5 * (1.0 * cos (2 * PI / (double) (2 * n) * (double) i));
  } </pre>
  @par
  Convert to fixed point Q31 format
      round(pBTable[i] * pow(2, 31))
 */

const q31_t realCoefBQ31[255] = {
    0x40c90e90, 0x4192155f, 0x425b0caf, 0x4323ecbe, 0x43ecadcf, 
 0x44b54825, 0x457db403, 0x4645e9af, 0x470de172, 0x47d59396, 0x489cf867, 
 0x49640837, 0x4a2abb59, 0x4af10a22, 0x4bb6ecef, 0x4c7c5c1e, 0x4d415013, 
 0x4e05c135, 0x4ec9a7f3, 0x4f8cfcbe, 0x504fb80e, 0x5111d263, 0x51d3443f, 
 0x5294062f, 0x535410c3, 0x54135c94, 0x54d1e242, 0x558f9a76, 0x564c7ddd, 
 0x57088531, 0x57c3a931, 0x587de2a7, 0x59372a64, 0x59ef7944, 0x5aa6c82b, 
 0x5b5d100a, 0x5c1249d8, 0x5cc66e99, 0x5d79775c, 0x5e2b5d38, 0x5edc1953, 
 0x5f8ba4dc, 0x6039f90f, 0x60e70f32, 0x6192e09b, 0x623d66a8, 0x62e69ac8, 
 0x638e7673, 0x6434f332, 0x64da0a9a, 0x657db64c, 0x661feffa, 0x66c0b162, 
 0x675ff452, 0x67fdb2a7, 0x6899e64a, 0x69348937, 0x69cd9578, 0x6a650525, 
 0x6afad269, 0x6b8ef77d, 0x6c216eaa, 0x6cb2324c, 0x6d413ccd, 0x6dce88aa, 
 0x6e5a1070, 0x6ee3cebe, 0x6f6bbe45, 0x6ff1d9c7, 0x70761c18, 0x70f8801f, 
 0x717900d6, 0x71f79948, 0x72744493, 0x72eefdea, 0x7367c090, 0x73de87de, 
 0x74534f41, 0x74c61236, 0x7536cc52, 0x75a5793c, 0x761214b0, 0x767c9a7e, 
 0x76e5068a, 0x774b54ce, 0x77af8159, 0x7811884d, 0x787165e3, 0x78cf1669, 
 0x792a9642, 0x7983e1e8, 0x79daf5e8, 0x7a2fcee8, 0x7a8269a3, 0x7ad2c2e8, 
 0x7b20d79e, 0x7b6ca4c4, 0x7bb6276e, 0x7bfd5cc4, 0x7c42420a, 0x7c84d496, 
 0x7cc511d9, 0x7d02f757, 0x7d3e82ae, 0x7d77b192, 0x7dae81cf, 0x7de2f148, 
 0x7e14fdf7, 0x7e44a5ef, 0x7e71e759, 0x7e9cc076, 0x7ec52fa0, 0x7eeb3347, 
 0x7f0ec9f5, 0x7f2ff24a, 0x7f4eaafe, 0x7f6af2e3, 0x7f84c8e2, 0x7f9c2bfb, 
 0x7fb11b48, 0x7fc395f9, 0x7fd39b5a, 0x7fe12acb, 0x7fec43c7, 0x7ff4e5e0, 
 0x7ffb10c1, 0x7ffec42d, 0x7fffffff, 0x7ffec42d, 0x7ffb10c1, 0x7ff4e5e0, 
 0x7fec43c7, 0x7fe12acb, 0x7fd39b5a, 0x7fc395f9, 0x7fb11b48, 0x7f9c2bfb, 
 0x7f84c8e2, 0x7f6af2e3, 0x7f4eaafe, 0x7f2ff24a, 0x7f0ec9f5, 0x7eeb3347, 
 0x7ec52fa0, 0x7e9cc076, 0x7e71e759, 0x7e44a5ef, 0x7e14fdf7, 0x7de2f148, 
 0x7dae81cf, 0x7d77b192, 0x7d3e82ae, 0x7d02f757, 0x7cc511d9, 0x7c84d496, 
 0x7c42420a, 0x7bfd5cc4, 0x7bb6276e, 0x7b6ca4c4, 0x7b20d79e, 0x7ad2c2e8, 
 0x7a8269a3, 0x7a2fcee8, 0x79daf5e8, 0x7983e1e8, 0x792a9642, 0x78cf1669, 
 0x787165e3, 0x7811884d, 0x77af8159, 0x774b54ce, 0x76e5068a, 0x767c9a7e, 
 0x761214b0, 0x75a5793c, 0x7536cc52, 0x74c61236, 0x74534f41, 0x73de87de, 
 0x7367c090, 0x72eefdea, 0x72744493, 0x71f79948, 0x717900d6, 0x70f8801f, 
 0x70761c18, 0x6ff1d9c7, 0x6f6bbe45, 0x6ee3cebe, 0x6e5a1070, 0x6dce88aa, 
 0x6d413ccd, 0x6cb2324c, 0x6c216eaa, 0x6b8ef77d, 0x6afad269, 0x6a650525, 
 0x69cd9578, 0x69348937, 0x6899e64a, 0x67fdb2a7, 0x675ff452, 0x66c0b162, 
 0x661feffa, 0x657db64c, 0x64da0a9a, 0x6434f332, 0x638e7673, 0x62e69ac8, 
 0x623d66a8, 0x6192e09b, 0x60e70f32, 0x6039f90f, 0x5f8ba4dc, 0x5edc1953, 
 0x5e2b5d38, 0x5d79775c, 0x5cc66e99, 0x5c1249d8, 0x5b5d100a, 0x5aa6c82b, 
 0x59ef7944, 0x59372a64, 0x587de2a7, 0x57c3a931, 0x57088531, 0x564c7ddd, 
 0x558f9a76, 0x54d1e242, 0x54135c94, 0x535410c3, 0x5294062f, 0x51d3443f, 
 0x5111d263, 0x504fb80e, 0x4f8cfcbe, 0x4ec9a7f3, 0x4e05c135, 0x4d415013, 
 0x4c7c5c1e, 0x4bb6ecef, 0x4af10a22, 0x4a2abb59, 0x49640837, 0x489cf867, 
 0x47d59396, 0x470de172, 0x4645e9af, 0x457db403, 0x44b54825, 0x43ecadcf, 
 0x4323ecbe, 0x425b0caf, 0x4192155f, 0x40c90e90,
};


/**
  @par
  Example code for Q31 Twiddle factors Generation::
  @par
  <pre>for (i = 0; i< 3N/4; i++)
  {
     twiddleCoefQ31[2*i]   = cos(i * 2*PI/(float)N);
     twiddleCoefQ31[2*i+1] = sin(i * 2*PI/(float)N);
  } </pre>
  @par
  where N = 256, PI = 3.14159265358979
  @par
  Cos and Sin values are interleaved fashion
  @par
  Convert Floating point to Q31(Fixed point 1.31):
 	round(twiddleCoefQ31(i) * pow(2, 31))
 
 */
const q31_t twiddleCoef_256_q31[384] = {
	(q31_t)0x7FFFFFFF, (q31_t)0x00000000, (q31_t)0x7FF62182,
	(q31_t)0x03242ABF, (q31_t)0x7FD8878D, (q31_t)0x0647D97C,
	(q31_t)0x7FA736B4, (q31_t)0x096A9049, (q31_t)0x7F62368F,
	(q31_t)0x0C8BD35E, (q31_t)0x7F0991C3, (q31_t)0x0FAB272B,
	(q31_t)0x7E9D55FC, (q31_t)0x12C8106E, (q31_t)0x7E1D93E9,
	(q31_t)0x15E21444, (q31_t)0x7D8A5F3F, (q31_t)0x18F8B83C,
	(q31_t)0x7CE3CEB1, (q31_t)0x1C0B826A, (q31_t)0x7C29FBEE,
	(q31_t)0x1F19F97B, (q31_t)0x7B5D039D, (q31_t)0x2223A4C5,
	(q31_t)0x7A7D055B, (q31_t)0x25280C5D, (q31_t)0x798A23B1,
	(q31_t)0x2826B928, (q31_t)0x78848413, (q31_t)0x2B1F34EB,
	(q31_t)0x776C4EDB, (q31_t)0x2E110A62, (q31_t)0x7641AF3C,
	(q31_t)0x30FBC54D, (q31_t)0x7504D345, (q31_t)0x33DEF287,
	(q31_t)0x73B5EBD0, (q31_t)0x36BA2013, (q31_t)0x72552C84,
	(q31_t)0x398CDD32, (q31_t)0x70E2CBC6, (q31_t)0x3C56BA70,
	(q31_t)0x6F5F02B1, (q31_t)0x3F1749B7, (q31_t)0x6DCA0D14,
	(q31_t)0x41CE1E64, (q31_t)0x6C242960, (q31_t)0x447ACD50,
	(q31_t)0x6A6D98A4, (q31_t)0x471CECE6, (q31_t)0x68A69E81,
	(q31_t)0x49B41533, (q31_t)0x66CF811F, (q31_t)0x4C3FDFF3,
	(q31_t)0x64E88926, (q31_t)0x4EBFE8A4, (q31_t)0x62F201AC,
	(q31_t)0x5133CC94, (q31_t)0x60EC3830, (q31_t)0x539B2AEF,
	(q31_t)0x5ED77C89, (q31_t)0x55F5A4D2, (q31_t)0x5CB420DF,
	(q31_t)0x5842DD54, (q31_t)0x5A82799A, (q31_t)0x5A82799A,
	(q31_t)0x5842DD54, (q31_t)0x5CB420DF, (q31_t)0x55F5A4D2,
	(q31_t)0x5ED77C89, (q31_t)0x539B2AEF, (q31_t)0x60EC3830,
	(q31_t)0x5133CC94, (q31_t)0x62F201AC, (q31_t)0x4EBFE8A4,
	(q31_t)0x64E88926, (q31_t)0x4C3FDFF3, (q31_t)0x66CF811F,
	(q31_t)0x49B41533, (q31_t)0x68A69E81, (q31_t)0x471CECE6,
	(q31_t)0x6A6D98A4, (q31_t)0x447ACD50, (q31_t)0x6C242960,
	(q31_t)0x41CE1E64, (q31_t)0x6DCA0D14, (q31_t)0x3F1749B7,
	(q31_t)0x6F5F02B1, (q31_t)0x3C56BA70, (q31_t)0x70E2CBC6,
	(q31_t)0x398CDD32, (q31_t)0x72552C84, (q31_t)0x36BA2013,
	(q31_t)0x73B5EBD0, (q31_t)0x33DEF287, (q31_t)0x7504D345,
	(q31_t)0x30FBC54D, (q31_t)0x7641AF3C, (q31_t)0x2E110A62,
	(q31_t)0x776C4EDB, (q31_t)0x2B1F34EB, (q31_t)0x78848413,
	(q31_t)0x2826B928, (q31_t)0x798A23B1, (q31_t)0x25280C5D,
	(q31_t)0x7A7D055B, (q31_t)0x2223A4C5, (q31_t)0x7B5D039D,
	(q31_t)0x1F19F97B, (q31_t)0x7C29FBEE, (q31_t)0x1C0B826A,
	(q31_t)0x7CE3CEB1, (q31_t)0x18F8B83C, (q31_t)0x7D8A5F3F,
	(q31_t)0x15E21444, (q31_t)0x7E1D93E9, (q31_t)0x12C8106E,
	(q31_t)0x7E9D55FC, (q31_t)0x0FAB272B, (q31_t)0x7F0991C3,
	(q31_t)0x0C8BD35E, (q31_t)0x7F62368F, (q31_t)0x096A9049,
	(q31_t)0x7FA736B4, (q31_t)0x0647D97C, (q31_t)0x7FD8878D,
	(q31_t)0x03242ABF, (q31_t)0x7FF62182, (q31_t)0x00000000,
	(q31_t)0x7FFFFFFF, (q31_t)0xFCDBD541, (q31_t)0x7FF62182,
	(q31_t)0xF9B82683, (q31_t)0x7FD8878D, (q31_t)0xF6956FB6,
	(q31_t)0x7FA736B4, (q31_t)0xF3742CA1, (q31_t)0x7F62368F,
	(q31_t)0xF054D8D4, (q31_t)0x7F0991C3, (q31_t)0xED37EF91,
	(q31_t)0x7E9D55FC, (q31_t)0xEA1DEBBB, (q31_t)0x7E1D93E9,
	(q31_t)0xE70747C3, (q31_t)0x7D8A5F3F, (q31_t)0xE3F47D95,
	(q31_t)0x7CE3CEB1, (q31_t)0xE0E60684, (q31_t)0x7C29FBEE,
	(q31_t)0xDDDC5B3A, (q31_t)0x7B5D039D, (q31_t)0xDAD7F3A2,
	(q31_t)0x7A7D055B, (q31_t)0xD7D946D7, (q31_t)0x798A23B1,
	(q31_t)0xD4E0CB14, (q31_t)0x78848413, (q31_t)0xD1EEF59E,
	(q31_t)0x776C4EDB, (q31_t)0xCF043AB2, (q31_t)0x7641AF3C,
	(q31_t)0xCC210D78, (q31_t)0x7504D345, (q31_t)0xC945DFEC,
	(q31_t)0x73B5EBD0, (q31_t)0xC67322CD, (q31_t)0x72552C84,
	(q31_t)0xC3A9458F, (q31_t)0x70E2CBC6, (q31_t)0xC0E8B648,
	(q31_t)0x6F5F02B1, (q31_t)0xBE31E19B, (q31_t)0x6DCA0D14,
	(q31_t)0xBB8532AF, (q31_t)0x6C242960, (q31_t)0xB8E31319,
	(q31_t)0x6A6D98A4, (q31_t)0xB64BEACC, (q31_t)0x68A69E81,
	(q31_t)0xB3C0200C, (q31_t)0x66CF811F, (q31_t)0xB140175B,
	(q31_t)0x64E88926, (q31_t)0xAECC336B, (q31_t)0x62F201AC,
	(q31_t)0xAC64D510, (q31_t)0x60EC3830, (q31_t)0xAA0A5B2D,
	(q31_t)0x5ED77C89, (q31_t)0xA7BD22AB, (q31_t)0x5CB420DF,
	(q31_t)0xA57D8666, (q31_t)0x5A82799A, (q31_t)0xA34BDF20,
	(q31_t)0x5842DD54, (q31_t)0xA1288376, (q31_t)0x55F5A4D2,
	(q31_t)0x9F13C7D0, (q31_t)0x539B2AEF, (q31_t)0x9D0DFE53,
	(q31_t)0x5133CC94, (q31_t)0x9B1776D9, (q31_t)0x4EBFE8A4,
	(q31_t)0x99307EE0, (q31_t)0x4C3FDFF3, (q31_t)0x9759617E,
	(q31_t)0x49B41533, (q31_t)0x9592675B, (q31_t)0x471CECE6,
	(q31_t)0x93DBD69F, (q31_t)0x447ACD50, (q31_t)0x9235F2EB,
	(q31_t)0x41CE1E64, (q31_t)0x90A0FD4E, (q31_t)0x3F1749B7,
	(q31_t)0x8F1D343A, (q31_t)0x3C56BA70, (q31_t)0x8DAAD37B,
	(q31_t)0x398CDD32, (q31_t)0x8C4A142F, (q31_t)0x36BA2013,
	(q31_t)0x8AFB2CBA, (q31_t)0x33DEF287, (q31_t)0x89BE50C3,
	(q31_t)0x30FBC54D, (q31_t)0x8893B124, (q31_t)0x2E110A62,
	(q31_t)0x877B7BEC, (q31_t)0x2B1F34EB, (q31_t)0x8675DC4E,
	(q31_t)0x2826B928, (q31_t)0x8582FAA4, (q31_t)0x25280C5D,
	(q31_t)0x84A2FC62, (q31_t)0x2223A4C5, (q31_t)0x83D60411,
	(q31_t)0x1F19F97B, (q31_t)0x831C314E, (q31_t)0x1C0B826A,
	(q31_t)0x8275A0C0, (q31_t)0x18F8B83C, (q31_t)0x81E26C16,
	(q31_t)0x15E21444, (q31_t)0x8162AA03, (q31_t)0x12C8106E,
	(q31_t)0x80F66E3C, (q31_t)0x0FAB272B, (q31_t)0x809DC970,
	(q31_t)0x0C8BD35E, (q31_t)0x8058C94C, (q31_t)0x096A9049,
	(q31_t)0x80277872, (q31_t)0x0647D97C, (q31_t)0x8009DE7D,
	(q31_t)0x03242ABF, (q31_t)0x80000000, (q31_t)0x00000000,
	(q31_t)0x8009DE7D, (q31_t)0xFCDBD541, (q31_t)0x80277872,
	(q31_t)0xF9B82683, (q31_t)0x8058C94C, (q31_t)0xF6956FB6,
	(q31_t)0x809DC970, (q31_t)0xF3742CA1, (q31_t)0x80F66E3C,
	(q31_t)0xF054D8D4, (q31_t)0x8162AA03, (q31_t)0xED37EF91,
	(q31_t)0x81E26C16, (q31_t)0xEA1DEBBB, (q31_t)0x8275A0C0,
	(q31_t)0xE70747C3, (q31_t)0x831C314E, (q31_t)0xE3F47D95,
	(q31_t)0x83D60411, (q31_t)0xE0E60684, (q31_t)0x84A2FC62,
	(q31_t)0xDDDC5B3A, (q31_t)0x8582FAA4, (q31_t)0xDAD7F3A2,
	(q31_t)0x8675DC4E, (q31_t)0xD7D946D7, (q31_t)0x877B7BEC,
	(q31_t)0xD4E0CB14, (q31_t)0x8893B124, (q31_t)0xD1EEF59E,
	(q31_t)0x89BE50C3, (q31_t)0xCF043AB2, (q31_t)0x8AFB2CBA,
	(q31_t)0xCC210D78, (q31_t)0x8C4A142F, (q31_t)0xC945DFEC,
	(q31_t)0x8DAAD37B, (q31_t)0xC67322CD, (q31_t)0x8F1D343A,
	(q31_t)0xC3A9458F, (q31_t)0x90A0FD4E, (q31_t)0xC0E8B648,
	(q31_t)0x9235F2EB, (q31_t)0xBE31E19B, (q31_t)0x93DBD69F,
	(q31_t)0xBB8532AF, (q31_t)0x9592675B, (q31_t)0xB8E31319,
	(q31_t)0x9759617E, (q31_t)0xB64BEACC, (q31_t)0x99307EE0,
	(q31_t)0xB3C0200C, (q31_t)0x9B1776D9, (q31_t)0xB140175B,
	(q31_t)0x9D0DFE53, (q31_t)0xAECC336B, (q31_t)0x9F13C7D0,
	(q31_t)0xAC64D510, (q31_t)0xA1288376, (q31_t)0xAA0A5B2D,
	(q31_t)0xA34BDF20, (q31_t)0xA7BD22AB, (q31_t)0xA57D8666,
	(q31_t)0xA57D8666, (q31_t)0xA7BD22AB, (q31_t)0xA34BDF20,
	(q31_t)0xAA0A5B2D, (q31_t)0xA1288376, (q31_t)0xAC64D510,
	(q31_t)0x9F13C7D0, (q31_t)0xAECC336B, (q31_t)0x9D0DFE53,
	(q31_t)0xB140175B, (q31_t)0x9B1776D9, (q31_t)0xB3C0200C,
	(q31_t)0x99307EE0, (q31_t)0xB64BEACC, (q31_t)0x9759617E,
	(q31_t)0xB8E31319, (q31_t)0x9592675B, (q31_t)0xBB8532AF,
	(q31_t)0x93DBD69F, (q31_t)0xBE31E19B, (q31_t)0x9235F2EB,
	(q31_t)0xC0E8B648, (q31_t)0x90A0FD4E, (q31_t)0xC3A9458F,
	(q31_t)0x8F1D343A, (q31_t)0xC67322CD, (q31_t)0x8DAAD37B,
	(q31_t)0xC945DFEC, (q31_t)0x8C4A142F, (q31_t)0xCC210D78,
	(q31_t)0x8AFB2CBA, (q31_t)0xCF043AB2, (q31_t)0x89BE50C3,
	(q31_t)0xD1EEF59E, (q31_t)0x8893B124, (q31_t)0xD4E0CB14,
	(q31_t)0x877B7BEC, (q31_t)0xD7D946D7, (q31_t)0x8675DC4E,
	(q31_t)0xDAD7F3A2, (q31_t)0x8582FAA4, (q31_t)0xDDDC5B3A,
	(q31_t)0x84A2FC62, (q31_t)0xE0E60684, (q31_t)0x83D60411,
	(q31_t)0xE3F47D95, (q31_t)0x831C314E, (q31_t)0xE70747C3,
	(q31_t)0x8275A0C0, (q31_t)0xEA1DEBBB, (q31_t)0x81E26C16,
	(q31_t)0xED37EF91, (q31_t)0x8162AA03, (q31_t)0xF054D8D4,
	(q31_t)0x80F66E3C, (q31_t)0xF3742CA1, (q31_t)0x809DC970,
	(q31_t)0xF6956FB6, (q31_t)0x8058C94C, (q31_t)0xF9B82683,
	(q31_t)0x80277872, (q31_t)0xFCDBD541, (q31_t)0x8009DE7D
};

const uint16_t armBitRevIndexTable_fixed_256[ARMBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH] =
{
   /* radix 4, size 240 */
   8,1024, 16,512, 24,1536, 32,256, 40,1280, 48,768, 56,1792, 64,128, 72,1152, 80,640,
   88,1664, 96,384, 104,1408, 112,896, 120,1920, 136,1088, 144,576, 152,1600, 160,320,
   168,1344, 176,832, 184,1856, 200,1216, 208,704, 216,1728, 224,448, 232,1472, 240,960,
   248,1984, 264,1056, 272,544, 280,1568, 296,1312, 304,800, 312,1824, 328,1184, 336,672,
   344,1696, 352,416, 360,1440, 368,928, 376,1952, 392,1120, 400,608, 408,1632, 424,1376,
   432,864, 440,1888, 456,1248, 464,736, 472,1760, 488,1504, 496,992, 504,2016, 520,1040,
   536,1552, 552,1296, 560,784, 568,1808, 584,1168, 592,656, 600,1680, 616,1424, 624,912,
   632,1936, 648,1104, 664,1616, 680,1360, 688,848, 696,1872, 712,1232, 728,1744, 744,1488,
   752,976, 760,2000, 776,1072, 792,1584, 808,1328, 824,1840, 840,1200, 856,1712, 872,1456,
   880,944, 888,1968, 904,1136, 920,1648, 936,1392, 952,1904, 968,1264, 984,1776, 1000,1520,
   1016,2032, 1048,1544, 1064,1288, 1080,1800, 1096,1160, 1112,1672, 1128,1416, 1144,1928,
   1176,1608, 1192,1352, 1208,1864, 1240,1736, 1256,1480, 1272,1992, 1304,1576, 1336,1832,
   1368,1704, 1384,1448, 1400,1960, 1432,1640, 1464,1896, 1496,1768, 1528,2024, 1592,1816,
   1624,1688, 1656,1944, 1720,1880, 1784,2008, 1912,1976
};

const arm_cfft_instance_q31 arm_cfft_sR_q31_len256 = {
  256, twiddleCoef_256_q31, armBitRevIndexTable_fixed_256, ARMBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH
};
