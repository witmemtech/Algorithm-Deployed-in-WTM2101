#ifndef FEATURE_TOOLS_H
#define FEATURE_TOOLS_H


#include <stdint.h>

#define _NFFT          512
#define _WIN_SIZE      400
#define _UPDATE_SIZE     160
#define _UPDATE_SHORT_SIZE     320//_UPDATE_SIZE*2
#define _NUM_MEL_BINS  40
#define FFT_SUB_WINDOW_INT_LEN 448  //(_NFFT-_WIN_SIZE)*4
#define SUB_WINDOW0          240   //_WIN_SIZE - _UPDATE_SIZE
#define SUB_WINDOW0_INT_SIZE       960   //SUB_WINDOW0*4
#define SUB_WINDOW0_SHORT_SIZE     480   //SUB_WINDOW0*2

typedef struct fbank_cfg {
    uint16_t start;
    uint16_t end;
    uint16_t* melfiter;
}fbank_cfg_t;

extern const fbank_cfg_t FBANK_FILTERS[_NUM_MEL_BINS];
extern const unsigned short povey_win[_WIN_SIZE];
extern const short povey_win_signed[_WIN_SIZE];
void fft_init(void);

void get_fbank(int16_t *in, uint8_t *out, void (*callback)(int, void*));

#endif

