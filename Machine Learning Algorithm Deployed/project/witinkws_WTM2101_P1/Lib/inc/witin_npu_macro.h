#ifndef __WITIN_NPU_MACRO__
#define __WITIN_NPU_MACRO__


#ifndef USE_NPU_DIFF
#define USE_NPU_DIFF               (1)
#endif

#ifndef USE_CONV_2D_SPLIT
#define USE_CONV_2D_SPLIT          (1)
#endif

#ifndef USE_CONV_2D
#define USE_CONV_2D                (1)
#endif

#ifndef USE_ALL_ROUND
#define USE_ALL_ROUND              (1)
#endif

#ifndef USE_EVENT_RAM_INIT
#define USE_EVENT_RAM_INIT         (1)
#endif

#ifndef USE_EVENT_CUSTOM_COPY
#define USE_EVENT_CUSTOM_COPY      (1)
#endif

#ifndef USE_EVENT_CUSTOM_CLEAN
#define USE_EVENT_CUSTOM_CLEAN     (0)
#endif

#ifndef USE_EVENT_CUSTOM_ADD
#define USE_EVENT_CUSTOM_ADD       (0)
#endif

#ifndef USE_EVENT_CUSTOM_MUL
#define USE_EVENT_CUSTOM_MUL       (0)
#endif

#ifndef USE_EVENT_CUSTOM_PN
#define USE_EVENT_CUSTOM_PN        (0)
#endif

#ifndef USE_EVENT_CUSTOM_CONCAT
#define USE_EVENT_CUSTOM_CONCAT    (0)
#endif

#ifndef USE_EVENT_CUSTOM_ACTIVATE
#define USE_EVENT_CUSTOM_ACTIVATE  (0)
#endif

#ifndef USE_EVENT_CUSTOM_POOLING
#define USE_EVENT_CUSTOM_POOLING   (0)
#endif

#endif