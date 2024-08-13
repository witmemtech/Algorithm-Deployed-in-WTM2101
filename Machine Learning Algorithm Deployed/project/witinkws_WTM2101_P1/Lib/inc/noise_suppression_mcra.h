#ifndef _NOISE_SUPPRESSION_MCRA_H_
#define _NOISE_SUPPRESSION_MCRA_H_

#ifdef __cplusplus
extern "C" {
#endif

#define NS_MCRA_MAG_LEN 128
#define NS_MCRA_EPS 1e-7f

typedef struct NsMcraParam_ {
    float alpha_s;
    float delta;
    float alpha_p;
    float alpha_d;
    int refresh_len;
    float floor;
    float mask_nn_th;
    float mask_nn_I;
    float mask_ns_min;
    float a_low;
    float a_high;
    float res;
} NsMcraParam;

typedef struct NsMcraHandle_ {
    float vad[NS_MCRA_MAG_LEN];
    float lambda_d[NS_MCRA_MAG_LEN];
    float Scur[NS_MCRA_MAG_LEN];
    float Smin[NS_MCRA_MAG_LEN];
    float Stmp[NS_MCRA_MAG_LEN];
    float Sr[NS_MCRA_MAG_LEN];
    float phat[NS_MCRA_MAG_LEN];
    float alpha_d_t[NS_MCRA_MAG_LEN];
    float sub_speech[NS_MCRA_MAG_LEN];
    float mask_smooth[NS_MCRA_MAG_LEN];
    NsMcraParam ns_param;
} NsMcraHandle;

int noise_suppress_mcra_init(NsMcraHandle *self);
int noise_suppress_mcra_set_param(NsMcraHandle *self, float nn_denoise_level, float a_low);
int noise_suppress_mcra_process(NsMcraHandle* self, float* power, float* mask_nn, int frame_idx, float* mask_ns);

#ifdef __cplusplus
}
#endif

#endif
