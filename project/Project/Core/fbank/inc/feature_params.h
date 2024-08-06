#ifndef _FEATURE_PARAMS_H_
#define _FEATURE_PARAMS_H_

#include <stdint.h>

#define _NFFT          512
#define _WIN_SIZE      400
#define SHIFT_SIZE         160
#define _NUM_MEL_BINS  40

typedef struct fbank_cfg {
    uint16_t start;
    uint16_t end;
    uint16_t* melfiter;
}fbank_cfg_t;

extern const fbank_cfg_t FBANK_FILTERS[_NUM_MEL_BINS];
extern const unsigned short povey_win[_WIN_SIZE];
extern const short povey_win_signed[_WIN_SIZE];

#endif

