// created by 杨西同
// 2019.12.3
#ifndef  GLOBAL_H
#define GLOBAL_H


#if defined(PLATFORM_WIN) || defined(PLATFORM_ARM) || defined(PLATFORM_RSIC_V_N307) 
// OK
#else
#error No platform is defined. you should define a platform in Preprocessor, such as PLATFORM_WIN,PLATFORM_ARM,PLATFORM_RSIC_V_N307
#endif

#include <stdint.h>

typedef unsigned char bool;
#define true (1)
#define false (0)


// 请选择解码版本号，只能选择一个版本。
// V0 是最古老的版本
// V1 是第一次优化后版本
// V1_LOWPOWER 是V1优化版本
// V2 维护有序的tokens链表，只支持FST_EXPERT_WORDS
// V2_1 志明优化，功耗低
// V2_2 修复V2_1 bug，简化代码，和python工程严格一致
//#define USE_DECODER_V0
//#define USE_DECODER_V1
//#define USE_DECODER_V1_LOWPOWER
//#define USE_DECODER_V2
//#define USE_DECODER_V2_1
#define USE_DECODER_V2_2


// HCLG 输出phones序号
//#define FST_EXPERT_PHONES
// HCLG 输出word序号
#define FST_EXPERT_WORDS 

#endif // ! GLOBAL_H
