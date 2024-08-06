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
#define USE_EVENT_CUSTOM_CLEAN     (1)
#endif

#ifndef USE_EVENT_CUSTOM_ADD
#define USE_EVENT_CUSTOM_ADD       (1)
#endif

#ifndef USE_EVENT_CUSTOM_MUL
#define USE_EVENT_CUSTOM_MUL       (1)
#endif

#ifndef USE_EVENT_CUSTOM_PN
#define USE_EVENT_CUSTOM_PN        (1)
#endif

#ifndef USE_EVENT_CUSTOM_CONCAT
#define USE_EVENT_CUSTOM_CONCAT    (1)
#endif

#ifndef USE_EVENT_CUSTOM_ACTIVATE
#define USE_EVENT_CUSTOM_ACTIVATE  (1)
#endif

#ifndef USE_EVENT_CUSTOM_POOLING
#define USE_EVENT_CUSTOM_POOLING   (1)
#endif

#ifndef USE_EVENT_CUSTOM_NORMALIZATION
#define USE_EVENT_CUSTOM_NORMALIZATION  (1)
#endif

#ifndef USE_EVENT_GROUP_NORM
#define USE_EVENT_GROUP_NORM       (1)
#endif

#ifndef NEED_FREE_SPACE  //if need free malloc space
#define NEED_FREE_SPACE           (0)
#endif

#endif