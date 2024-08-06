
#include "feature_tools.h"
#include "math.h"
#include <stdio.h>
#include <string.h>

#undef PLATFORM_RSIC_V_N307
#define PLATFORM_WIN

#define FBANK_HARD_FROM_AHB
#define USE_HARD_FBANK

#ifdef PLATFORM_RSIC_V_N307
#ifdef FBANK_HARD_FROM_AHB
#include "fbank_config.h"
static int32_t fbank_hard_buffer[_NFFT] = {0};
static uint32_t fbank_hard_buffer_u[_NFFT] = {0};
static uint32_t fbank_hard_out[_NFFT] = {0};
static int16_t indata_tmp=0;
#else
#include "witin_hw_fft_config.h"
#endif
static int16_t rfft_buf_hw[_NFFT] = {0};
#endif
#include "witin_math_lib.h"

static int16_t samples[_WIN_SIZE] = {0};
static int32_t rfft_buf[_NFFT] = {0};
static int16_t rfft_buf_16[_NFFT] = {0};
static uint32_t spectrum_buffer[_NFFT / 2 + 1] = {0};
static uint16_t spectrum_buffer_16[_NFFT / 2 + 1] = {0};
static int32_t mel_out[40*2] = {0};
/*
  usage: do pre-emphasis
  para@ input : S16Q15
  para@ output: S16Q15
*/
static void preemphasis(int16_t *input, int32_t *output, int len) {
	uint16_t pre_emphasis = 0xF852; //0x7C28;//0.97
	int i;
	int32_t val;
	short temp, last_data;
	// pre-emphasis S16Q15 = (S16Q15*U16Q16)>>16
	// y[t] = x[t] - 0.97*x[t-1]
	last_data = input[0];
	output[0] = input[0];
	for (i = 1; i < len; i++) {
		val = last_data;
		temp = input[i];
		val = (val * pre_emphasis) >> 16;
		output[i] = temp - val;
		last_data = temp;
	}
}

static int index = 0;
static void preemphasis_short2(int16_t *input, uint32_t *output, int len) {
	int32_t pre_emphasis = 31785;
	int i;
	int32_t val;
	int temp, last_data;

	last_data = input[index];
	output[0] = input[index];
	for (i = index + 1; i < len; i++) {
		val = last_data;
		temp = input[i];
		val = (val * pre_emphasis) >> 15;
		output[i - index] = temp - val;
		last_data = temp;
	}

	for (i = 0; i < index; i++) {
		val = last_data;
		temp = input[i];
		val = (val * pre_emphasis) >> 15;
		output[len - index + i] = temp - val;
		last_data = temp;
	}

}

static short preemphasis_short(int16_t *input, int16_t *output, int len) {
	uint16_t pre_emphasis = 0xF852; //0x7C28;//0.97
	int i;
	int32_t val;
	int16_t max = 0;
	int16_t min = 0;
	short temp, last_data;
	// pre-emphasis S16Q15 = (S16Q15*U16Q16)>>16
	// y[t] = x[t] - 0.97*x[t-1]
	last_data = input[0];
	output[0] = input[0];
	for (i = 1; i < len; i++) {
		val = last_data;
		temp = input[i];
		val = (val * pre_emphasis) >> 16;
		output[i] = temp - val;
		last_data = temp;
	}
        return  0;
}

//20220513 yyp
static void preemphasis_short_scale_tmp(int16_t *input, int32_t *output, int len, int scale,int16_t indata_tmp) {
	uint16_t pre_emphasis = 0xF852;//65535;//0xF852; //0x7C28;//0.97
	int i;
	int32_t val;
	//short temp, last_data;
	int32_t temp_out = 0;

        val      = (indata_tmp * pre_emphasis) >> 16;
        temp_out = scale*(*input - val);
        if(temp_out < -32768) temp_out = -32768;
        if(temp_out > 32767) temp_out = 32767;
        *output++= (uint32_t)temp_out;

	for (i = 1; i < len; i++)
        {
		val      = (*input++ * pre_emphasis) >> 16;
		temp_out = scale*(*input - val);
		if(temp_out < -32768) temp_out = -32768;
		if(temp_out > 32767) temp_out = 32767;
		*output++= (uint32_t)temp_out;
	}
}

static short preemphasis_short_scale(int16_t *input, int16_t *output, int len, int scale) {
	uint16_t pre_emphasis = 0xF852; //0x7C28;//0.97
	int i;
	int32_t val;
	short temp, last_data;
	int32_t temp_out = 0;
	// pre-emphasis S16Q15 = (S16Q15*U16Q16)>>16
	// y[t] = x[t] - 0.97*x[t-1]
	last_data = input[0];
	output[0] = input[0];
	for (i = 1; i < len; i++) {
		val = last_data;
		temp = input[i];
		val = (val * pre_emphasis) >> 16;
		temp_out = scale * (temp - val);
		if(temp_out < -32768) temp_out = -32768;
		if(temp_out > 32767) temp_out = 32767;
		output[i] = (short)temp_out;
		last_data = temp;
	}
}

/*
  usage:

  para@ input : S16Q15
  para@ output: S16Q15
  para@ win    : U16Q16 povey_win
*/
static void add_win(int32_t *input, int32_t *output, int len, uint16_t *win) {
	int i;
	for (i = 0; i < len; i++) {
		(*output++) = *(input++) * (*win++);
	}
}

#if defined(PLATFORM_RSIC_V_N307)
static void add_win_int16(int16_t *input, int16_t *output, int len, const int16_t *win, short shift_add) {
	int i;
	short winShift = (14 - shift_add);
	for (i = 0; i < (len >> 1); i++) {

		uint32_t input_value = *((uint32_t *)input + i);
		uint32_t input_value2 = *((uint32_t *)win + i);

		int value1;
		__asm volatile(
			"smbb16 t0, %1, %2;"
			"smtt16 t1, %1, %2;"
			"sra t0, t0, %3;"
			"sra t1, t1, %3;"
			"pkbb16 %0, t1, t0;"
			: "=r"(value1)
			: "r"(input_value), "r"(input_value2), "r"(winShift)
			: "t0", "t1");
		*((uint32_t *)(output + 2 * i)) = value1;
	}
}
#else
 static void add_win_int16(int16_t* input, int16_t* output, int len, const int16_t* win, short shift_add) {
     int i;
     short winShift = (14 - shift_add);
      for (i = 0;i < len; i++) {
        (*output++) = *(input++) * (*win++) >>winShift;
    }
}
#endif
/*
  usage:

  para@ input : S16Q15
  para@ output: S16Q6    512 real[0] real[256] real[1] imag[1] real[2] imag[2] …… real[255] imag[255]

  note: input data will be covered
*/
//float comp[_NFFT*2];

int32_t comp_r_q31_out[_NFFT * 2];
#if defined(PLATFORM_WIN) || defined(PLATFORM_ARM)
arm_rfft_instance_q31 S;
#endif
void fft_init(void) {

#ifdef PLATFORM_RSIC_V_N307
#ifdef FBANK_HARD_FROM_AHB
#else
	witin_hw_fft_init();
#endif
#else
	arm_rfft_init_q31(&S, 512, 0, 1);
#endif
}

#if defined(PLATFORM_WIN) || defined(PLATFORM_ARM)
void _asr_frame_rfft_512(int32_t *input, int32_t *output) {
	/* fixed 32bit fft */
	arm_rfft_q31(&S, input, comp_r_q31_out);
	for (int i = 0; i < _NFFT; i++) {
		output[i] = comp_r_q31_out[i] >> 7;
	}
}
#endif
/*
  usage: sqrt(real^2+imag^2)

  para@ input : S16Q6  512 real[0] real[256] real[1] imag[1] real[2] imag[2] …… real[255] imag[255]
  para@ output: U16Q6

*/

static void _asr_create_magnitude(int *input, uint32_t *output) {
	int i;
	float real;
	float imag;
	float out = 0;
	float var_real, var_imag;
	//FFT512 S16Q6
	real = (float)input[0];
	imag = (float)input[1];

	//var_real = ((int32_t)real)*((int32_t)real) ;//S64Q12 = S16Q6*S16Q6
	//output[0]   = sqrt(var_real);
	var_imag = imag * imag;
	uint32_t half_NFFT = _NFFT / 2;
#ifdef PLATFORM_RSIC_V_N307
	output[half_NFFT] = sqrt_convert_memory(var_imag);
#else
	output[half_NFFT] = sqrt(var_imag);
#endif
	for (i = 0; i < half_NFFT; i++) {
		real = (float)*(input++);
		imag = (float)*(input++);
		var_real = real * real; //U64Q12
		var_imag = imag * imag; //imag*imag;//U64Q12
#ifdef PLATFORM_WIN
		output[i] = sqrt(var_real + var_imag); //U16Q6
#else
		float out = 0;
#ifdef PLATFORM_ARM
		within_arm_sqrt_f32(var_real + var_imag, &out);
#else
#ifdef PLATFORM_RSIC_V_N307
		out = sqrt_convert_memory(var_real + var_imag);
#endif
#endif
		output[i] = (uint32_t)out;
#endif
	}
}

static void _asr_create_magnitude_16(int16_t *input, uint16_t *output) {
	int i;
	int16_t real;
	int16_t imag;
	uint16_t out = 0;
	uint32_t var_real, var_imag;
	//FFT512 S16Q6
	real = input[0];
	imag = input[1];
	//var_real = ((int32_t)real)*((int32_t)real) ;//S64Q12 = S16Q6*S16Q6
	//output[0]   = sqrt(var_real);
	var_imag = imag * imag;
	uint32_t half_NFFT = _NFFT / 2;
	output[half_NFFT] = sqrt_convert_memory((float)var_imag);
	for (i = 0; i < half_NFFT; i++) {
		real = *(input++);
		imag = *(input++);
		var_real = real * real; //U64Q12
		var_imag = imag * imag; //imag*imag;//U64Q12
#ifdef PLATFORM_WIN
		output[i] = sqrt(var_real + var_imag); //U16Q6
#else
		out = sqrt_convert_memory((float)(var_real + var_imag));
		output[i] = (uint16_t)out;
#endif
	}
}

#define TAB_LEN 118
static int32_t tab_in[TAB_LEN] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 15, 17, 19, 22, 25, 28, 32, 36, 40, 46, 52, 59, 66, 75, 85, 96, 109, 124, 140, 158, 180, 203, 230, 261, 296, 335, 379, 430, 487, 552, 625,
	709, 803, 910, 1031, 1168, 1323, 1499, 1699, 1925, 2181, 2472, 2801, 3174, 3596, 4075, 4617, 5232, 5929, 6718, 7613, 8626, 9775, 11076, 12551, 14222, 16115, 18261, 20692, 23448,
	26569, 30107, 34116, 38658, 43805, 49638, 56247, 63736, 72223, 81839, 92735, 105083, 119074, 134929, 152894, 173252, 196320, 222460, 252080, 285644, 323677, 366774, 415609,
	470947, 533653, 604708, 685224, 776460, 879845, 996994, 1129743, 1280166, 1450618, 1643766, 1862630, 2110637, 2391665, 2710111, 3070958, 3479851, 3943188, 4468217,
	5063154, 5737305, 6501218, 7366845};
static uint8_t tab_out[TAB_LEN] = {0, 6, 9, 11, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
	55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
	103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};

static int32_t FastSearch(int32_t value) // 二分法查表
{
	int low, high, mid, mid1;
	low = 0;
	high = TAB_LEN - 1;
	if (value < 0)
		return high;
	while (low <= high) {
		mid = (low + high) / 2;
		mid1 = mid + 1;
		if (mid1 >= (TAB_LEN - 1))
			return TAB_LEN - 1;
		if ((tab_in[mid] <= value) && (value < tab_in[mid1]))
			return mid;
		else if (value < tab_in[mid])
			high = mid;
		else if (tab_in[mid1] <= value)
			low = mid1;
	}
	return mid;
}

static uint8_t get_log_from_tab(int32_t input) {
	//out = (uint8_t)(log(input)*8 + 0.5) //查表过程实现了这一计算过程
	int idx = FastSearch(input);
	return tab_out[idx];
}

/*
  usage: creat fbank (logE)

  para@ input : U16Q6
  para@ output: U8Q4
  para@ cfg    : fbank_w
*/
static void _asr_create_py_fbank(uint32_t *input, uint8_t *output, const fbank_cfg_t *cfg) {
	//    int f,i;
	//    uint64_t val_64;//U64Q6
	double acc_64; //U64Q22
				   //    float acc_fp32,_fbank_fp32;
	float acc_fp32;

	for (int i = 0; i < _NUM_MEL_BINS; i++) {
		acc_64 = 0;
		for (int j = cfg[i].start; j < cfg[i].end; j++) {
			acc_64 += (uint64_t)input[j] * cfg[i].melfiter[j - cfg[i].start];
		}
		//acc_fp32 = acc_64/128.0;//2^7, acc_64 converted to Q15
		acc_fp32 = acc_64 / 65536; //改成65536后，和python版本已经非常接近
		//_fbank_fp32 = log(acc_fp32);
		//output[i] = (uint8_t)(_fbank_fp32 * 8 + 0.5);
		output[i] = get_log_from_tab((int32_t)acc_fp32); //log计算过程改为查表法
	}
}

static void _asr_create_py_fbank_16(uint16_t *input, uint8_t *output, const fbank_cfg_t *cfg, short shift_add) {
	uint32_t acc_32; //U64Q22
	short fbank_shift = shift_add + 8;
	for (int i = 0; i < _NUM_MEL_BINS; i++) {
		acc_32 = 0;
		for (int j = cfg[i].start; j < cfg[i].end; j++) {
			acc_32 += (uint32_t)(input[j] * cfg[i].melfiter[j - cfg[i].start]);
		}
#ifdef PLATFORM_RSIC_V_N307
		output[i] = get_log_from_tab(acc_32 >> fbank_shift) << 1;
#else
		output[i] = get_log_from_tab(acc_32 >> fbank_shift);
#endif
	}
}
const uint32_t winsize_sub_updateSize = _WIN_SIZE - _UPDATE_SIZE;
const uint32_t sizeof_int16_plus_winsize_sub_update = sizeof(int16_t) * (_WIN_SIZE - _UPDATE_SIZE);
const uint32_t sizeofint16_updatesize = sizeof(int16_t) * _UPDATE_SIZE;
const uint32_t sizeofint32_nfft_sub_winsize_sub_1 = (_NFFT - _WIN_SIZE - 1) * sizeof(int32_t);


void update_sample(void *dst, void *src, int len) {
	int *psrc = (int *)src;
	int *pdst = (int *)dst;
	for (int i = 0; i < (len >> 1); ++i) {
		pdst[i] = psrc[i];
	}
}

void insert_array(int16_t *out_a) {
	int16_t *p = samples + index;

	update_sample(p, out_a, _UPDATE_SIZE / 2);

	int x = (index + _UPDATE_SIZE / 2) % _WIN_SIZE;
	out_a += _UPDATE_SIZE / 2;
	p = samples + x;

	update_sample(p, out_a, _UPDATE_SIZE / 2);
	index = (index + _UPDATE_SIZE) % _WIN_SIZE;
}

void audio_buffer_fif0(int16_t *inData) {
	int16_t *p = samples;
	int16_t *P_mv = samples + (_UPDATE_SIZE);
	int16_t *p_set = samples + (SUB_WINDOW0);
	update_sample(p, P_mv, SUB_WINDOW0);
	update_sample(p_set, inData, _UPDATE_SIZE);
}

extern int fbank_c_process(int16_t *audio1,uint8_t *out);


void get_fbank(int16_t *in, uint8_t *out, void (*callback)(int, void*)) {
   //return;//0.27
#ifdef PLATFORM_RSIC_V_N307

#ifdef FBANK_HARD_FROM_AHB

#if defined(USE_HARD_C_FBANK)
    audio_buffer_fif0(in);
    short temp = preemphasis_short_scale(samples, rfft_buf_16, _WIN_SIZE, 4);
    fbank_c_process(rfft_buf_16,out);
#elif defined(USE_HARD_FBANK)
    //0.05
    uint16_t i;
    //memcpy(fbank_hard_buffer_u, &fbank_hard_buffer_u[_UPDATE_SIZE],SUB_WINDOW0_INT_SIZE);
    preemphasis_short_scale_tmp(in, &fbank_hard_buffer_u[SUB_WINDOW0], _UPDATE_SIZE, 4,indata_tmp);
    indata_tmp=in[_UPDATE_SIZE-1];
    //preemphasis_short_scale(in,fbank_hard_buffer_u,400,4);
    if(callback) callback(1, "preemphasis");
#define ALL_HARD 0
#if ALL_HARD
    #define L_SHIFT_BITS 0
    fbank_calculate(fbank_hard_buffer_u,out);

//        fbank_calculate_0516(fbank_hard_buffer_u, (uint32_t *)mel_out);
//        for (int i = 0; i < 40; i++)
//        {
//              int32_t log_in = mel_out[i*2]<<8;
                //out[i] = get_log_from_tab(log_in);
//        }
#else
#define L_SHIFT_BITS 6
    fbank_calculate_win_fft(fbank_hard_buffer_u, (uint32_t *)rfft_buf);
    if(callback) callback(2, "win_fft");

    for (i = 0; i < _NFFT; i++) {
        if(rfft_buf[i] > 33554431)           rfft_buf[i] = 2147483584;
        else if(rfft_buf[i] < -33554431)     rfft_buf[i] = -2147483584;
        else rfft_buf[i] = rfft_buf[i]<< L_SHIFT_BITS;
    }
    /*printf("---- fft res\r\n");
    for (i = 0; i < _NFFT; i++) {
        printf("%d ",rfft_buf[i]);
    }printf("\r\n");*/

    fbank_calculate_sqrt_mel((uint32_t *)rfft_buf,(uint32_t *)mel_out);
    if(callback) callback(3, "sqrt_mel");

    for (i = 0; i < 40; i++)
    {
            int32_t log_in = mel_out[i]<<4;
            *out++= get_log_from_tab(log_in);
    }
#endif
#else
    audio_buffer_fif0(in);
    preemphasis_short_scale(samples, rfft_buf_16, _WIN_SIZE, 1);
    for (int i = 0; i < _WIN_SIZE; i++) {
            fbank_hard_buffer[i] = (int32_t)rfft_buf_16[i] ;
    }
    add_win(fbank_hard_buffer, rfft_buf, _WIN_SIZE, (uint16_t *)povey_win);
    for (int i = 0; i < (_NFFT - _WIN_SIZE); i++) {
            rfft_buf[_WIN_SIZE + i] =(uint32_t) 0;
    }
    fft_calculate(rfft_buf, fbank_hard_out);
    for(int i=0; i < _NFFT; i++) {
            rfft_buf[i] = ((int32_t)fbank_hard_out[i]) >> 7;
    }
    _asr_create_magnitude(rfft_buf, spectrum_buffer);
    _asr_create_py_fbank(spectrum_buffer, out, FBANK_FILTERS);
#endif
#else
    insert_array(testAudio);
    short max_value = preemphasis_short2(samples, rfft_buf_16, _WIN_SIZE);

    int shift_add = 0;
    if (max_value < 8192 && max_value > 0) {
            shift_add = log2f(8192 / max_value);
    }
    add_win_int16(rfft_buf_16, rfft_buf_hw, _WIN_SIZE, povey_win_signed, shift_add);
    for (int i = 0; i < (_NFFT - _WIN_SIZE - 1); i++) {
            rfft_buf_hw[_WIN_SIZE + i] = 0;
    }
    witin_hw_fft_process2((uint32_t *)rfft_buf_hw, spectrum_buffer_16);
    pu_stage1();
    _asr_create_py_fbank_16(spectrum_buffer_16, out, FBANK_FILTERS, shift_add);
#endif
#else
    memcpy(samples, samples + _UPDATE_SIZE, sizeof_int16_plus_winsize_sub_update);
    memcpy(samples + winsize_sub_updateSize, in, sizeofint16_updatesize);
    preemphasis(samples, rfft_buf, _WIN_SIZE);
    add_win(rfft_buf, rfft_buf, _WIN_SIZE, (uint16_t *)povey_win);
    memset(&rfft_buf[_WIN_SIZE - 1], 0, sizeofint32_nfft_sub_winsize_sub_1);
    _asr_frame_rfft_512(rfft_buf, rfft_buf);
    _asr_create_magnitude(rfft_buf, spectrum_buffer);
    _asr_create_py_fbank(spectrum_buffer, out, FBANK_FILTERS);
#endif
}

#if 0
///*
//  test for feature_tools
//*/
//#include <string.h>
const int16_t audio_u16[960] = {2914,4961,1740,2976,2806,2119,-367,260,-82,-826,-2523,-2224,-3047,-3154,-4142,-4608,-4234,-1059,2129,-2716,-6216,-7663,-640,327,-1715,-3456,-1885,-1058,-916,2411,4306,3131,2617,4747,5026,4147,3403,5125,7624,6741,3748,2486,5955,7638,6773,4907,5944,5719,4096,2969,4654,3862,1441,594,2211,1417,-2128,-1758,388,457,-885,-2484,-1933,-2427,-2982,-3389,-3142,-5565,-5915,-7270,-6177,-7753,-8678,-8996,-8747,-10941,-7314,-4574,-8844,-12791,-11932,-5200,-4355,-5713,-7065,-6471,-5640,-5064,-2108,-282,-867,-1896,-448,835,1527,-728,1701,5666,5640,1033,-239,5562,6036,4232,2745,4018,3366,1192,767,2907,1401,-841,-359,1325,-867,-3156,-2008,1176,1503,-1749,-3549,-2296,-1756,-2929,-3873,-3343,-4262,-5630,-6397,-4727,-5833,-5233,-7339,-6127,-9270,-4179,-2893,-6066,-10502,-8855,-1364,-1607,-3839,-5821,-2718,-1339,-147,1960,2988,1543,2178,4627,5692,4619,1815,6387,9051,8079,3641,4944,9085,9296,7364,7010,8462,7444,6461,6381,7998,5726,4208,3919,5687,3843,2341,4050,6069,4389,1083,1876,3896,3778,1577,1016,1644,-140,-1939,-2251,-1996,-2806,-3717,-4458,-5433,-6980,180,-2383,-7009,-10603,-5114,-1037,-3473,-5271,-5494,-2676,-2399,-1161,-116,263,-286,1941,3010,2371,809,680,5089,6626,5579,2559,6049,7714,6846,4467,5193,6750,5891,3661,4398,4976,2905,1360,1677,3049,1198,687,1900,2491,-30,-2271,94,215,-906,-3209,-2336,-3455,-4271,-6334,-4266,-5516,-6835,-8558,-8574,-10251,-5684,-2567,-8050,-11438,-11496,-3907,-4265,-6087,-7281,-5221,-3778,-3037,-566,55,-549,166,3276,2769,2598,1706,4457,6818,6296,2898,2583,8143,7185,5268,4013,6601,5748,3495,2264,3411,2141,799,205,1444,723,-1074,-359,524,55,-2869,-3990,-1920,-1825,-4096,-5911,-5015,-5627,-6227,-7045,-5927,-8005,-8057,-9802,-8168,-10014,-3262,-4857,-8844,-12338,-9196,-2098,-3213,-4539,-5390,-2127,-2254,-1881,444,2762,2725,3714,5106,5090,4982,2810,8636,10717,9486,4544,7664,10839,9843,7840,9381,11028,8917,6289,7175,9009,7183,6290,6162,7286,5479,3730,4600,6570,5555,2064,3145,3822,2696,-306,143,959,503,-1836,-1491,-1283,-2538,-4680,-3683,-5610,-2971,2229,-5220,-8002,-10589,-662,-716,-3147,-4502,-3123,-1069,-2018,507,2243,1672,879,3489,3458,3540,1561,4270,8008,6406,3691,1427,8092,8564,7079,5219,6479,5913,4548,2156,4082,3623,1739,732,1692,1306,-1801,-1522,470,1395,-1725,-3941,-1173,-1402,-3142,-4678,-4013,-5530,-6326,-7932,-5953,-8565,-8962,-11361,-8459,-11809,-6917,-3205,-9818,-12624,-14564,-3964,-4413,-6209,-9296,-6460,-4504,-4798,-2201,249,497,-411,1482,805,2087,93,4354,8013,7784,2922,1756,7596,7525,5657,2935,5225,4219,2052,191,3584,2691,876,-1139,714,1,-2740,-1752,664,818,-4036,-5654,-3696,-2644,-4388,-4509,-2729,-3887,-5286,-6522,-3849,-6634,-5597,-8139,-5895,-9071,-2762,-1600,-7687,-9775,-8268,1173,-838,-2364,-4839,-971,488,1114,2620,4309,3931,2970,4643,4772,5879,3034,7691,9927,9302,4205,6517,11761,10597,8039,6958,9515,8156,6358,5695,8902,6750,4669,3864,5666,4076,2391,3525,5839,4672,521,864,2715,2423,-161,-22,592,-600,-2478,-3145,-2149,-4640,-5092,-7523,-5675,-9200,-987,-3211,-7646,-11453,-8787,-212,-1543,-3431,-6497,-2930,-2789,-1796,-1179,725,-176,946,1482,2422,2419,623,6278,8165,7088,2506,4312,8012,6911,3808,4621,6678,4876,2266,2686,5578,3780,1786,1415,3784,994,-760,-605,1530,150,-2627,-2009,-398,-1106,-3149,-1799,-1042,-3652,-5270,-5159,-4128,-5743,-7614,-8705,-7688,-10882,-3950,-6912,-10571,-14295,-10003,-2179,-3969,-5805,-8893,-4496,-4613,-4256,-1694,-147,-1524,148,682,1143,703,210,5492,6135,4998,647,4171,6849,6308,4176,4559,5754,3821,2007,2494,5218,3662,1994,879,2143,-291,-1124,-766,1998,330,-2559,-2323,-708,-1971,-3881,-2784,-2272,-4785,-7076,-6329,-5982,-7319,-8976,-8396,-7490,-11097,-3066,-5123,-7581,-12475,-8472,-425,-2944,-5031,-7346,-2535,-2195,-2397,-31,1951,1338,2323,2851,5255,4777,3570,9117,11468,9358,3031,6240,11012,10915,7912,8599,10703,8186,5554,6792,9888,7717,5720,4748,7220,3672,1885,2981,6057,3225,148,640,3147,2562,615,1376,1945,-528,-2338,-2818,-2108,-5006,-4537,-7484,-5748,-8644,-2676,-1756,-7252,-9449,-9049,530,-2085,-4088,-7225,-3596,-2046,-2318,-697,1563,519,79,2583,4116,4930,2167,6480,8599,7181,2066,4709,10312,8995,6604,6958,9700,6997,5222,5162,7448,4597,2709,1859,3501,1335,-560,317,2997,918,-2771,-2240,-135,-858,-3175,-2951,-3408,-5612,-7474,-7873,-6917,-8798,-9686,-12296,-10225,-14906,-7924,-5788,-10960,-15179,-15775,-5528,-5782,-8195,-11566,-7658,-5909,-6483,-5134,-1915,-1782,-1523,36,1628,2317,-856,4604,6945,6161,785,1795,7185,7406,4242,3954,7506,6779,4158,3942,7049,4862,3287,1759,4164,2773,173,389,3613,2886,131,219,2493,2216,-263,16,734,-1709,-4078,-2812,-1408,-3766,-5508,-8185,-4920,-9078,-3207,-722,-4958,-9078,-10713,-1187,-736,-2800,-6236,-2899,-773,-1439,-679,3243,4364,4123,4798,5919,6500,2949,7375,11338,12531,7720,7047,11678,11569,9279,7876,10931,10530,6998,5734,8478,7663,5464,4097,6484,4465,984,1447,5022,5412,1947,573,1920,1641,-555,-1584,-636,-2374,-4615,-5453,-4984,-6514,-8138,-9796,-6519,-10254,-8207,-3127,-6329,-10367,-14780,-4660,-1377,-3743,-7392,-6042,-3202,-3535,-1858,1193,2492,1600,2563,4053,4469,1068,4262,9185,10803,6560,4333,9387,9974,8292,7543,10050,9443,6168,3687,5761,6389,4159,2120,3422,2270,-1233,-1154,2307,2845,-695,-2288,-898,-1482,-4209,-4138,-2970,-3884,-6681,-8238,-8443,-9983,-10408,-12150,-9923,-14412,-11691};
const int16_t audio1[512] = {0,0,-5,0,-9,10,-2,5,-7,3,-3,8,7,-5,-70,10,-2033,280,17684,-8578,-15153,-3698,-3274,18809,17902,-15412,-16404,-1659,-480,17505,16817,-17007,-17640,845,2108,16138,15382,-18166,-18611,3354,4572,14574,13719,-18979,-19268,5758,6906,12820,11885,-19480,-19618,8015,9082,10916,9924,-19684,-19678,10103,11077,8905,7871,-19607,-19470,11999,12872,6826,5771,-19274,-19015,13690,14456,4712,3653,-18705,-18343,15170,15828,2598,1550,-17932,-17476,16431,16978,513,-512,-16976,-16441,17475,17917,-1519,-2508,-15871,-15270,18308,18648,-3477,-4422,-14638,-13983,18936,19179,-5342,-6237,-13307,-12611,19374,19525,-7102,-7938,-11901,-11176,19630,19694,-8745,-9522,-10440,-9699,19722,19707,-10265,-10977,-8950,-8199,19657,19576,-11658,-12306,-7446,-6697,19462,19320,-12922,-13505,-5949,-5206,19146,18948,-14056,-14578,-4468,-3740,18727,18486,-15068,-15526,-3023,-2313,18223,17940,-15956,-16356,-1616,-934,17644,17332,-16728,-17073,-263,392,17007,16673,-17392,-17683,1031,1656,16327,15975,-17952,-18197,2262,2852,15618,15253,-18418,-18621,3426,3980,14887,14517,-18800,-18961,4517,5037,14147,13775,-19105,-19229,5538,6021,13407,13040,-19339,-19434,6487,6934,12676,12318,-19514,-19583,7363,7776,11964,11614,-19639,-19684,8170,8546,11273,10939,-19715,-19740,8905,9247,10613,10297,-19759,-19767,9574,9883,9988,9689,-19769,-19765,10176,10454,9401,9124,-19757,-19746,10717,10964,8858,8604,-19730,-19710,11196,11414,8362,8130,-19689,-19664,11617,11807,7912,7706,-19639,-19614,11983,12145,7514,7336,-19589,-19564,12295,12433,7168,7015,-19539,-19516,12556,12667,6877,6752,-19493,-19474,12768,12856,6640,6542,-19454,-19439,12931,12996,6459,6390,-19425,-19413,13048,13090,6335,6294,-19407,-19402,13120,13139,6269,6257,-19400,-19400,13145,13139,6259,6276,-19403,-19412,13125,13097,6307,6352,-19421,-19433,13060,13009,6410,6484,-19448,-19465,12949,12876,6570,6673,-19486,-19508,12790,12694,6790,6919,-19533,-19558,12585,12464,7063,7220,-19585,-19613,12329,12183,7390,7575,-19641,-19671,12022,11849,7772,7982,-19697,-19724,11661,11461,8205,8441,-19751,-19774,11245,11015,8688,8947,-19793,-19811,10770,10509,9219,9501,-19824,-19834,10235,9943,9794,10097,-19836,-19832,9635,9311,10410,10732,-19823,-19802,8969,8611,11063,11401,-19775,-19740,8238,7845,11748,12100,-19690,-19631,7434,7005,12458,12822,-19557,-19473,6559,6094,13190,13562,-19372,-19256,5610,5107,13936,14309,-19120,-18970,4589,4050,14685,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
//const int16_t audio[400] = { 30,97,-12,50,-37,17,-73,-37,-62,-84,-49,-85,-51,-43,-41,-41,-1,-24,4,-33,12,-28,-39,-10,-84,-35,-83,-125,-63,-137,-140,-72,-145,-96,-54,-96,9,-15,-5,57,9,55,67,63,95,92,111,103,185,82,207,154,111,199,68,116,115,-19,134,-49,44,15,-51,58,-12,0,84,32,72,91,60,84,47,17,51,-46,-59,2,-171,-49,-99,-139,-71,-51,-158,21,-68,-46,31,-21,-18,69,-73,80,-37,1,43,-49,57,-30,22,1,-10,22,-20,-20,34,-71,28,-43,-23,-33,-37,-38,-17,-81,1,-76,-38,-9,-84,71,-57,89,55,47,146,97,102,150,102,69,160,0,104,20,41,28,2,93,0,77,60,75,22,128,-21,49,-6,-124,-1,-181,-95,-94,-151,-115,-8,-201,-8,-54,-139,4,-98,-94,-37,-89,-109,17,-108,-28,61,-70,54,62,22,69,80,78,57,147,29,115,65,42,44,17,18,1,-5,37,-12,93,68,69,173,43,133,85,15,18,-28,-85,-72,-71,-95,-82,5,-72,50,19,75,54,98,107,56,129,37,101,43,56,-4,56,-42,-38,50,-111,4,6,-104,25,-71,-49,-66,-120,-80,-185,-152,-165,-171,-173,-103,-123,-90,-16,-59,26,-59,37,-78,-34,-30,-108,-31,-61,-28,-67,37,-52,14,-28,-10,-17,-72,-11,-44,-117,10,-66,-111,39,-129,9,-76,-24,-50,-16,0,-29,88,-3,129,50,114,90,88,98,74,58,93,20,82,88,55,144,69,159,130,140,165,206,137,227,173,174,163,156,68,120,27,-29,61,-123,31,-124,24,-115,2,-36,-55,0,-64,-21,-69,-17,-88,4,-93,33,-99,-5,-19,-116,-18,-95,-93,-66,-95,-66,-59,-41,-19,-40,34,-33,-30,36,-79,-29,-36,-102,-23,-85,-85,-30,-91,-74,-44,-62,-82,31,-69,43,25,19,78,-20,79,-38,-8,-19,-69,-49,-76,-43,-39,-70,54,-58,60,29,41,78,49,27,95,20,55,125,5,134,85,56,102,62,1,42,14,-53,4,-33, };
////below are the result of kaldi
////9.224103 9.159233 9.254093 10.58372 11.564 10.52631 9.10636 9.302777 10.62268 9.463505
////8.102886 9.864748 9.7728 9.516592 10.39833 9.382740 9.83540 9.298097 9.499686 10.06837
////10.60263 10.68849 11.29363 11.75509 11.62502 11.91234 12.45695 12.6987 12.04651 12.58335
////13.04155 12.50391 11.97835 11.26131 11.47991 11.29177 11.58101 12.11927 12.22719 12.52815
const uint32_t fbank_wdata[512] = {
    0x00000000, 0x00000000, 0xfffffffb, 0x00000000, 0xfffffff7, 0x0000000a, 0xfffffffe, 0x00000005, 0xfffffff9, 0x00000003, 0xfffffffd, 0x00000008, 0x00000007, 0xfffffffb, 0xffffffba, 0x0000000a, 0xfffff80f, 0x00000118, 0x00004514, 0xffffde7e, 0xffffc4cf, 0xfffff18e, 0xfffff336, 0x00004979, 0x000045ee, 0xffffc3cc, 0xffffbfec, 0xfffff985, 0xfffffe20, 0x00004461, 0x000041b1, 0xffffbd91, 0xffffbb18, 0x0000034d, 0x0000083c, 0x00003f0a, 0x00003c16, 0xffffb90a, 0xffffb74d, 0x00000d1a, 0x000011dc, 0x000038ee, 0x00003597, 0xffffb5dd, 0xffffb4bc, 0x0000167e, 0x00001afa, 0x00003214, 0x00002e6d, 0xffffb3e8, 0xffffb35e, 0x00001f4f, 0x0000237a, 0x00002aa4, 0x000026c4, 0xffffb31c, 0xffffb322, 0x00002777, 0x00002b45, 0x000022c9, 0x00001ebf, 0xffffb369, 0xffffb3f2, 0x00002edf, 0x00003248, 0x00001aaa, 0x0000168b, 0xffffb4b6, 0xffffb5b9, 0x0000357a, 0x00003878, 0x00001268, 0x00000e45, 0xffffb6ef, 0xffffb859, 0x00003b42, 0x00003dd4, 0x00000a26, 0x0000060e, 0xffffb9f4, 0xffffbbbc, 0x0000402f, 0x00004252, 0x00000201, 0xfffffe00, 0xffffbdb0, 0xffffbfc7, 0x00004443, 0x000045fd, 0xfffffa11, 0xfffff634, 0xffffc201, 0xffffc45a, 0x00004784, 0x000048d8, 0xfffff26b, 0xffffeeba, 0xffffc6d2, 0xffffc961, 0x000049f8, 0x00004aeb, 0xffffeb22, 0xffffe7a3, 0xffffcc05, 0xffffcebd, 0x00004bae, 0x00004c45, 0xffffe442, 0xffffe0fe, 0xffffd183, 0xffffd458, 0x00004cae, 0x00004cee, 0xffffddd7, 0xffffdace, 0xffffd738, 0xffffda1d, 0x00004d0a, 0x00004cfb, 0xffffd7e7, 0xffffd51f, 0xffffdd0a, 0xffffdff9, 0x00004cc9, 0x00004c78, 0xffffd276, 0xffffcfee, 0xffffe2ea, 0xffffe5d7, 0x00004c06, 0x00004b78, 0xffffcd86, 0xffffcb3f, 0xffffe8c3, 0xffffebaa, 0x00004aca, 0x00004a04, 0xffffc918, 0xffffc70e, 0xffffee8c, 0xfffff164, 0x00004927, 0x00004836, 0xffffc524, 0xffffc35a, 0xfffff431, 0xfffff6f7, 0x0000472f, 0x00004614, 0xffffc1ac, 0xffffc01c, 0xfffff9b0, 0xfffffc5a, 0x000044ec, 0x000043b4, 0xffffbea8, 0xffffbd4f, 0xfffffef9, 0x00000188, 0x0000426f, 0x00004121, 0xffffbc10, 0xffffbaed, 0x00000407, 0x00000678, 0x00003fc7, 0x00003e67, 0xffffb9e0, 0xffffb8eb, 0x000008d6, 0x00000b24, 0x00003d02, 0x00003b95, 0xffffb80e, 0xffffb743, 0x00000d62, 0x00000f8c, 0x00003a27, 0x000038b5, 0xffffb690, 0xffffb5ef, 0x000011a5, 0x000013ad, 0x00003743, 0x000035cf, 0xffffb55f, 0xffffb4e3, 0x000015a2, 0x00001785, 0x0000345f, 0x000032f0, 0xffffb475, 0xffffb416, 0x00001957, 0x00001b16, 0x00003184, 0x0000301e, 0xffffb3c6, 0xffffb381, 0x00001cc3, 0x00001e60, 0x00002ebc, 0x00002d5e, 0xffffb349, 0xffffb31c, 0x00001fea, 0x00002162, 0x00002c09, 0x00002abb, 0xffffb2fd, 0xffffb2e4, 0x000022c9, 0x0000241f, 0x00002975, 0x00002839, 0xffffb2d1, 0xffffb2c9, 0x00002566, 0x0000269b, 0x00002704, 0x000025d9, 0xffffb2c7, 0xffffb2cb, 0x000027c0, 0x000028d6, 0x000024b9, 0x000023a4, 0xffffb2d3, 0xffffb2de, 0x000029dd, 0x00002ad4, 0x0000229a, 0x0000219c, 0xffffb2ee, 0xffffb302, 0x00002bbc, 0x00002c96, 0x000020aa, 0x00001fc2, 0xffffb317, 0xffffb330, 0x00002d61, 0x00002e1f, 0x00001ee8, 0x00001e1a, 0xffffb349, 0xffffb362, 0x00002ecf, 0x00002f71, 0x00001d5a, 0x00001ca8, 0xffffb37b, 0xffffb394, 0x00003007, 0x00003091, 0x00001c00, 0x00001b67, 0xffffb3ad, 0xffffb3c4, 0x0000310c, 0x0000317b, 0x00001add, 0x00001a60, 0xffffb3db, 0xffffb3ee, 0x000031e0, 0x00003238, 0x000019f0, 0x0000198e, 0xffffb402, 0xffffb411, 0x00003283, 0x000032c4, 0x0000193b, 0x000018f6, 0xffffb41f, 0xffffb42b, 0x000032f8, 0x00003322, 0x000018bf, 0x00001896, 0xffffb431, 0xffffb436, 0x00003340, 0x00003353, 0x0000187d, 0x00001871, 0xffffb438, 0xffffb438, 0x00003359, 0x00003353, 0x00001873, 0x00001884, 0xffffb435, 0xffffb42c, 0x00003345, 0x00003329, 0x000018a3, 0x000018d0, 0xffffb423, 0xffffb417, 0x00003304, 0x000032d1, 0x0000190a, 0x00001954, 0xffffb408, 0xffffb3f7, 0x00003295, 0x0000324c, 0x000019aa, 0x00001a11, 0xffffb3e2, 0xffffb3cc, 0x000031f6, 0x00003196, 0x00001a86, 0x00001b07, 0xffffb3b3, 0xffffb39a, 0x00003129, 0x000030b0, 0x00001b97, 0x00001c34, 0xffffb37f, 0xffffb363, 0x00003029, 0x00002f97, 0x00001cde, 0x00001d97, 0xffffb347, 0xffffb329, 0x00002ef6, 0x00002e49, 0x00001e5c, 0x00001f2e, 0xffffb30f, 0xffffb2f4, 0x00002d8d, 0x00002cc5, 0x0000200d, 0x000020f9, 0xffffb2d9, 0xffffb2c2, 0x00002bed, 0x00002b07, 0x000021f0, 0x000022f3, 0xffffb2af, 0xffffb29d, 0x00002a12, 0x0000290d, 0x00002403, 0x0000251d, 0xffffb290, 0xffffb286, 0x000027fb, 0x000026d7, 0x00002642, 0x00002771, 0xffffb284, 0xffffb288, 0x000025a3, 0x0000245f, 0x000028aa, 0x000029ec, 0xffffb291, 0xffffb2a6, 0x00002309, 0x000021a3, 0x00002b37, 0x00002c89, 0xffffb2c1, 0xffffb2e4, 0x0000202e, 0x00001ea5, 0x00002de4, 0x00002f44, 0xffffb316, 0xffffb351, 0x00001d0a, 0x00001b5d, 0x000030aa, 0x00003216, 0xffffb39b, 0xffffb3ef, 0x0000199f, 0x000017ce, 0x00003386, 0x000034fa, 0xffffb454, 0xffffb4c8, 0x000015ea, 0x000013f3, 0x00003670, 0x000037e5, 0xffffb550, 0xffffb5e6, 0x000011ed, 0x00000fd2, 0x0000395d, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

};
const uint32_t fbank_rdata[10] = {
    0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x51404040, 0x42517576, 0x40404040, 0x57766440, 0x40404040};


const int32_t testData1[512] = {2914,2135,-3072,1289,-80,-602,-2422,616,-334,-746,-1721,224,-889,-198,-1082,-590,236,3048,3157,-4781,-3581,-1633,6794,948,-2032,-1792,1468,771,111,3300,1968,-1045,-420,2209,422,-728,-619,1825,2653,-654,-2790,-1149,3544,1862,-635,-1662,1185,-46,-1451,-1004,1775,-652,-2305,-803,1635,-727,-3502,307,2094,81,-1328,-1625,477,-551,-627,-496,146,-2517,-516,-1532,875,-1761,-1157,-578,-20,-2456,3299,2521,-4407,-4212,476,6375,690,-1488,-1523,383,637,407,2805,1763,-593,-1055,1392,1270,718,-2209,2408,4017,144,-4437,-1241,5794,641,-1622,-1360,1356,-531,-2073,-389,2164,-1418,-2199,457,1674,-2152,-2315,1054,3124,363,-3206,-1852,1147,472,-1225,-1031,414,-1019,-1495,-935,1479,-1247,426,-2262,992,-3326,4813,1161,-3259,-4617,1332,7226,-283,-2280,-2097,2929,1298,1152,2103,1087,-1355,682,2515,1204,-902,-2665,4627,2856,-700,-4195,1413,4290,484,-1653,-133,1663,-764,-759,114,1809,-2032,-1346,-162,1886,-1673,-1386,1780,2141,-1497,-3174,826,2077,-1,-2087,-513,659,-1734,-1803,-370,188,-869,-995,-852,-1108,-1709,6951,-2557,-4697,-3804,5171,3924,-2467,-1902,-381,2654,197,1167,1011,376,-541,2219,1128,-548,-1490,-104,4430,1690,-848,-2852,3567,1847,-636,-2173,861,1713,-656,-2053,847,710,-1921,-1457,358,1423,-1759,-475,1234,648,-2446,-2241,2297,124,-1114,-2330,777,-1189,-919,-2191,1878,-1377,-1484,-1928,-272,-1934,4260,2947,-5560,-3629,-401,7245,-475,-1949,-1376,1842,1287,628,2380,605,-602,699,3115,-408,-87,-814,2803,2495,-317,-3209,-228,5638,-713,-1701,-1096,2709,-654,-2080,-1126,1215,-1167,-1277,-570,1246,-677,-1775,683,873,-453,-2922,-1207,1951,38,-2325,-1937,719,-762,-768,-1004,907,-2255,-292,-1986,1340,-2091,6452,-1692,-4132,-3759,2772,6823,-1177,-1422,-987,3102,-190,306,2269,2332,46,1071,1504,138,45,-2022,5911,2341,-909,-4657,3257,3405,-670,-1707,1777,1929,-1780,-2360,1075,2050,-1555,-677,61,1309,-1588,-1584,982,2108,-817,-3324,1143,772,-1011,-2921,440,821,-427,-2323,290,164,-1293,-2218,857,-2037,2471,5111,-7382,-2938,-2827,9610,-73,-2452,-1449,1244,1961,-981,2465,1752,-503,-742,2637,74,186,-1872,2756,3867,-1361,-2522,-2153,6708,715,-1228,-1647,1417,-371,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void test_feature_tools(void)
{

#ifdef PLATFORM_RSIC_V_N307
	int16_t windowed_buffer[_NFFT];
	fft_init();
	memset(windowed_buffer, 0, sizeof(windowed_buffer));
	memcpy(windowed_buffer, audio1, _WIN_SIZE * sizeof(int16_t));
	uint8_t fbank_buffer[_NUM_MEL_BINS];
#ifdef FBANK_HARD_FROM_AHB
#if defined(USE_HARD_C_FBANK)

	fbank_c_process(windowed_buffer,fbank_buffer);
#elif defined(USE_HARD_FBANK)
	memset(fbank_hard_buffer_u, 0, sizeof(uint32_t) * _NFFT);
	for (int i = 0; i < _WIN_SIZE; i++) {
		fbank_hard_buffer_u[i] = (uint32_t)(windowed_buffer[i]);
	}
	fbank_calculate(fbank_hard_buffer_u, (uint32_t *)fbank_buffer);
#else
short temp = preemphasis_short(windowed_buffer, rfft_buf_16, _WIN_SIZE);

	for (int i = 0; i < _WIN_SIZE; i++) {
		fbank_hard_buffer[i] = rfft_buf_16[i];
		printf("%d,",rfft_buf_hw[i]);
	}
	add_win(fbank_hard_buffer, rfft_buf, _WIN_SIZE, povey_win);


	for (int i = 0; i < (_NFFT - _WIN_SIZE); i++) {
		rfft_buf[_WIN_SIZE + i] =(uint32_t) 0;
		printf("0,");
	}
	printf("\n");

	fft_calculate(rfft_buf, fbank_hard_out);
	for(int i=0; i < _NFFT; i++) {
		rfft_buf[i] = ((int32_t)fbank_hard_out[i]) >> 7;
	}
	_asr_create_magnitude(rfft_buf, spectrum_buffer);
	_asr_create_py_fbank(spectrum_buffer, fbank_buffer, FBANK_FILTERS);
#endif


#else

	int shift_add = 0;
	if (max_value < 8192 && max_value > 0) {
		shift_add = log2f(8192 / max_value);
	}
	add_win_int16(rfft_buf_16, rfft_buf_hw, _WIN_SIZE, povey_win_signed, shift_add);
	witin_hw_fft_process2((uint32_t *)rfft_buf_hw, spectrum_buffer_16);
	_asr_create_py_fbank_16(spectrum_buffer_16, fbank_buffer, FBANK_FILTERS, shift_add);
#endif
	printf("---------------- test fbank --------------------\n");
	for (int i = 0; i < _NUM_MEL_BINS; i++) {
		printf("%d ", fbank_buffer[i]);
	}
	printf("\n");

	// =========================== 正确结果 =============================
	//74 73 74 85 93 84 73 74 85 76 65 79 78 76 83 75 79 74 76 81 85 86 90 94 93 95 100 102 96 101 104 100 96 90 92 90 93 97 98 100

#else

	int16_t windowed_buffer[_NFFT];
	fft_init();
	memset(windowed_buffer, 0, sizeof(windowed_buffer));
	memcpy(windowed_buffer, audio_u16, _WIN_SIZE * sizeof(int16_t));
	uint8_t fbank_buffer[_NUM_MEL_BINS];
	preemphasis(windowed_buffer, rfft_buf, _WIN_SIZE);

	for (int i = 0; i < 400; i++)
		rfft_buf[i] = (int32_t)testData1[i];
	add_win(rfft_buf, rfft_buf, _WIN_SIZE, (uint16_t *)povey_win);
	memset(&rfft_buf[_WIN_SIZE - 1], 0, sizeofint32_nfft_sub_winsize_sub_1);
	_asr_frame_rfft_512(rfft_buf, rfft_buf);
	_asr_create_magnitude(rfft_buf, spectrum_buffer);
	printf("spectrum_buffer_16 out:\n");
	for (int i = 0; i < _NFFT; i++) {
		printf("%d ", spectrum_buffer[i]);
	}
	printf("\n");
	_asr_create_py_fbank(spectrum_buffer, fbank_buffer, FBANK_FILTERS);

	printf("---------------- test fbank --------------------\n");
	for (int i = 0; i < _NUM_MEL_BINS; i++) {
		printf("%d ", fbank_buffer[i]);
	}
	printf("\n");

	// =========================== 正确结果 =============================
	//74 73 74 85 93 84 73 74 85 76 65 79 78 76 83 75 79 74 76 81 85 86 90 94 93 95 100 102 96 101 104 100 96 90 92 90 93 97 98 100
#endif
}

#ifdef PLATFORM_RSIC_V_N307
static int32_t fft_inpt[512] = {0, 1309, -7336, -18256, 23790, 53400, -37960, -46452, 12495, 0, -12166, 31651, 7104, 27120, -44573, -69120, -30832, 239120, 209328, -288512, -292136, 143350, 451963, -46215, -389436, -478413, 611380, 288424, -296640, -471870, 49932, -287140, 667224, 136563, -956620, -265290, 360576, 864600, -501054, 77157, -250236, -102377, 668058, 855270, -428327, -476828, 651398, 23260, -120340, -472796, 629846, 398100, -944679, -719865, 1759703, 194675, -724270, -316980, -472439, 502080, 257775, 1111131, -1537735, -129843, 2509188, -2414404, -418677, 408080, -542724, -341536, 458241, -490534, -523825, 720874, -617136, -508599, 741090, -1989931, -333775, 1360476, -3091632, -841402, -1271118, -1434324, -1516648, -1979344, -1835262, -1354230, -1223480, -777000, -663033, -480990, -748857, -1123734, -469602, -204210, 1242900, 1890810, 1633184, 1511664, 1641555, 3363815, 3744900, 3148356, 883522, 622304, 2598552, 5100672, 6209896, 3998106, 2764889, 1794648, 1392666, 1365344, 603792, 1481958, 1893892, 2180353, 1618128, 226985, -1283576, -2545620, -2756657, -2452216, -761456, 240100, -1114235, -1661478, -3006385, -1838863, -1803960, -2626884, -2902440, -2822490, -361991, -364721, -682357, -1903356, -798720, -589820, 917796, 2771952, 2899630, 2257624, 886608, 2118766, 3758432, 5247990, 4086648, 1940788, 2123800, 4097623, 3887407, 2857827, 703428, 2474220, 3196584, 1903200, -1194980, -1500450, 241120, 665896, -668657, -2685364, -3002230, -1906562, -2407392, -2973504, -2983776, -1808730, -2377698, -3263832, -4595642, -4103905, -1836048, -2793164, -2736692, -1914000, -2110350, -384558, -1413038, -772308, -902748, -581382, 1100036, 1166598, 713977, 1104932, 1822212, 1759158, 1434906, 2154405, 522720, 1177002, 1112310, 1505695, 1047872, 327565, 851851, -196602, -720874, -1113959, -1048208, -1833776, -1767555, -1832040, -1634725, -2025540, -2741970, -3456819, -2671314, -1692054, -2469848, -3699699, -3953471, -2458904, -1873342, -2385834, -2445642, -1862641, -1345953, -1279000, -382800, -445508, -190443, 189936, 1641562, 1322034, 2636172, 4630254, 4989600, 3294586, 805324, 61728, 2152570, 6249540, 7384751, 6625783, 3874304, 2772880, -9782934, 477992, -713700, -1598292, -471280, 937904, 349938, -464168, -1385112, 57400, 627902, 624349, -169290, -617056, -613327, -664956, -881024, -1750720, -1521856, -647856, -482580, -372736, -581581, -472401, 312618, 1189399, 1077678, 305520, 505170, 801760, 546689, 837845, 684138, 1162680, 624260, 1570503, 2640848, 3504225, 2499336, 45842, -317779, 1168648, 1735383, -704704, -3617721, -3622752, -1749347, -1350464, -3297144, -3672763, -1468692, 1169396, 1195470, -905556, -194470, 1920700, 3110424, 2509083, 1145915, 328311, 1367696, 1810704, 1470630, 241675, -578595, -1140462, -561867, -1139565, -2212554, -2241683, -1771560, -581153, -872726, -1243242, -960564, -400624, 731224, 746091, -108568, -266520, 261630, 770250, 881615, 494060, 121095, 450984, 139524, -227750, -691207, -1200155, -832494, -166992, -244848, -558236, -954079, -589279, -129843, 90455, -194007, -189035, 83680, 244365, 348678, 77050, 104825, -43629, -70575, 13691, 106160, -51416, -49768, -192544, -209340, -213389, -335947, -62682, -120744, -116184, -74456, -285984, -231471, -147852, -15720, -165264, -43020, 54664, -39018, 0, -29300, 94316, 68159, 19776, 139560, 152845, 122670, 106904, 113760, 108867, 54900, -8427, -7728, 11760, 6405, 52029, 51840, 35351, 12204, -17760, 5105, 7821, 7997, -2975, -13746, -12410, -6141, -2196, -3136, -2520, -510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -93, 11};
static int32_t fft_buf[512] = {0};
void test_witin_hw_fft() {
#ifdef FBANK_HARD_FROM_AHB
	printf("---->> test_witin_hw_fft <<---- \r\n");
	for (int i = 0; i < 512; i++)
		fft_inpt[i] = i * 10;

	fft_calculate(fft_inpt, fft_buf);
	for (int i = 0; i < 512; i++) {
		printf("%d ", fft_buf[i]);
	}
	printf("\n\n");
#else
	printf("---->> test_witin_hw_fft <<---- \r\n");
	for (int i = 0; i < 512; i++)
		fft_buf[i] = fft_inpt[i] >> 15;

	witin_hw_fft_process((uint32_t *)fft_buf, (uint32_t *)fft_buf);
	for (int i = 0; i < 512; i++) {
		printf("%d ", fft_buf[i] << 8);
	}
	printf("\n\n");
	/*
    c out:-36,0,207,-140,-156,-369,-818,671,1301,280,-260,-753,-75,109,-220,-505,-666,575,241,476,786,911,1612,-2271,-3530,-608,1134,3043,924,-1601,-99,264,-403,-658,117,534,-375,-237,266,91,-6,573,-57,-917,489,750,-1010,-649,1014,561,-705,-232,382,-29,-67,207,7,-156,217,-138,-451,64,337,-43,-408,208,508,-198,-464,218,421,-222,-328,241,372,-302,-439,157,287,-13,-170,58,184,-52,-113,-25,68,81,4,-251,-153,248,39,-195,-2,371,167,-326,-76,118,-22,-247,-366,372,698,43,-332,-338,183,-66,-645,-32,317,602,241,-252,181,-48,-416,-522,-119,777,462,-309,-206,46,225,-408,-744,349,646,173,-211,-93,419,-151,-723,-214,466,600,-92,-463,96,167,-205,-213,53,322,78,-321,-257,457,638,-396,-572,13,164,-126,-336,332,499,-3,-299,-248,90,226,-73,-176,-42,298,208,-150,18,165,212,-429,-411,-52,-94,99,-136,347,522,-87,-321,-286,-268,143,57,589,612,-173,-172,-208,40,-49,114,141,-138,-298,347,15,-612,51,680,-308,-700,170,111,-64,338,272,-264,-542,-170,38,-312,384,207,-139,-299,496,495,61,255,-141,-430,-258,453,526,-12,-581,-6,-38,-491,58,410,274,-126,-246,-55,160,182,112,37,-169,128,-4,-122,-86,153,-214,-356,52,81,-43,-267,179,276,83,-117,-8,250,6,-202,-213,65,209,-77,-222,-18,276,58,-202,-14,184,66,-195,-172,61,27,-2,-140,225,297,34,-53,4,324,-10,-46,-271,-14,-120,-211,-97,-9,47,-275,-41,103,255,-124,-71,138,325,135,-246,-33,185,157,-220,-85,56,34,-221,-234,150,103,-3,-105,145,302,33,-63,-176,184,-34,-244,-355,-167,140,-290,-9,20,462,188,17,161,183,310,-299,-148,-103,-37,-258,-362,187,144,109,-101,152,324,54,12,-140,107,-167,-312,-115,38,195,-111,-70,129,303,105,-277,12,87,-64,-188,-64,42,-99,-58,-133,259,233,-29,-102,103,260,-96,-201,-48,132,60,-63,-26,187,-29,-201,-163,85,108,-199,-176,-33,276,44,-6,128,175,160,-259,-81,40,12,-275,-327,150,106,71,-149,187,324,105,69,-112,160,-158,-268,-167,91,43,-338,-41,186,291,17,-204,-93,130,104,37,82,-4,3,-228,-184,149,83,-39,-88,119,219,-47,-204,-31,196,70,-80,-83,136,-13,-156,-135,43,33,-187,-87,-43,172,-65,12,111,321,205,-242,-67,102,115,-191,-171,115,217,-97,-252,7,238,78,-109,-126,134,-28,-284,-113,135,185,-156,-126,90,207,0,-145,20,179,93,-256,-196,161,138,-95,-151,111,140,-58,-122,114,226,-102,
    hw out:-512,-256,0,-256,-256,-256,-1024,768,1024,256,-512,-768,-256,0,-256,-512,-768,512,0,512,768,768,1536,-2304,-3584,-512,1024,3072,768,-1536,-256,256,-512,-768,0,512,-512,-256,0,0,0,512,-256,-1024,512,768,-1024,-768,1024,512,-768,-256,256,0,-256,256,0,-256,256,-256,-512,0,256,0,-512,0,512,-256,-512,256,256,-256,-512,256,256,-256,-512,0,256,0,-256,0,0,0,-256,0,0,0,0,-256,-256,256,0,-256,0,256,0,-512,-256,0,0,-256,-512,256,512,0,-512,-512,0,-256,-768,0,256,512,256,-256,0,0,-512,-512,-256,768,256,-256,-256,0,0,-512,-768,256,512,256,-256,-256,256,-256,-768,-256,256,512,-256,-512,0,256,-256,-256,0,256,0,-256,-256,512,512,-512,-768,0,0,-256,-256,256,512,0,-256,-256,0,256,-256,-256,-256,256,256,-256,0,0,256,-512,-512,0,-256,0,-256,256,512,0,-512,-256,-256,0,0,512,512,-256,-256,-256,0,-256,0,0,-256,-256,256,0,-768,0,512,-512,-768,0,0,-256,256,256,-256,-512,-256,0,-256,256,256,-256,-256,512,512,0,256,-256,-512,-256,256,512,0,-768,0,-256,-512,0,256,256,-256,-256,-256,0,0,0,0,-256,0,0,-256,-256,0,-256,-512,0,0,-256,-256,256,256,0,-256,0,256,0,-256,-256,0,0,-256,-256,0,256,0,-256,0,0,0,-256,-256,0,0,0,-256,0,256,0,0,0,256,-256,0,-256,0,-256,-256,-256,0,0,-256,0,0,256,-256,0,0,256,0,-256,0,0,0,-256,-256,0,0,-256,-256,0,0,0,-256,0,256,0,-256,-256,256,-256,-256,-512,-256,0,-256,0,0,256,0,0,0,0,256,-512,-256,-256,0,-256,-512,0,0,0,-256,0,256,0,0,-256,0,-256,-512,-256,0,0,-256,0,0,256,0,-512,0,0,-256,-256,-256,0,-256,-256,-256,256,256,-256,-256,0,256,-256,-256,-256,0,0,-256,0,0,0,-256,-256,0,0,-256,-256,0,256,0,0,0,0,0,-256,-256,0,0,-256,-512,0,0,0,-256,0,256,0,0,-256,0,-256,-256,-256,0,0,-512,0,256,256,0,-256,-256,0,0,0,0,0,0,-256,-256,0,0,-256,-256,0,0,-256,-256,-256,0,0,-256,-256,0,-256,-256,-256,0,0,-256,-256,-256,0,-256,0,0,256,0,-256,-256,0,0,-256,-256,0,256,-256,-256,0,256,0,-256,-256,0,0,-512,-256,0,0,-256,-256,0,0,0,-256,0,0,0,-256,-256,0,0,-256,-256,0,0,0,-256,0,0,-256,
    */
#endif
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void _asr_frame_rfft(int16_t* input, int16_t* output, int len)
//{
//    uint16_t pre_emphasis = 0xF852;//0x7C28;//0.97
//    int i;
//    int32_t val;
//    short temp,last_data;
//    int i_end = len-1;
//    // pre-emphasis S16Q15 = (S16Q15*U16Q16)>>16
//    last_data = input[0];
//    for (i = 1;i < len;i++) {
//        val = last_data;
//        temp = input[i];
//        //// y[t] = x[t] - 0.97*x[t-1]
//        val = (val * pre_emphasis) >> 16;
//        input[i] = temp - val;
//        last_data = temp;
//    }
//    //extracts a windowed frame of waveform
//    //S16Q15 = (S16Q15*U16Q16)>>16
//    input[0] = 0;
//    input[i_end] = 0;
//    for (i = 1;i < i_end;i++) {
//    // y[t] = x[t] * window[t]
//        val = input[i];
//        val = (val * povey_win[i]) >> 16;
//        input[i] = val;
//    }
//    // RFFT512
//    // * Input: S16Q15
//    // * Output:S16Q6
//    rfft_512_q15_simd(input, output);
//
//}

#endif
