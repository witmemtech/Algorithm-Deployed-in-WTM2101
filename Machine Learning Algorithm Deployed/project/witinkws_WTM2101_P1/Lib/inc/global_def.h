// created by ����ͬ
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


// ��ѡ�����汾�ţ�ֻ��ѡ��һ���汾��
// V0 ������ϵİ汾
// V1 �ǵ�һ���Ż���汾
// V1_LOWPOWER ��V1�Ż��汾
// V2 ά�������tokens����ֻ֧��FST_EXPERT_WORDS
// V2_1 ־���Ż������ĵ�
// V2_2 �޸�V2_1 bug���򻯴��룬��python�����ϸ�һ��
//#define USE_DECODER_V0
//#define USE_DECODER_V1
//#define USE_DECODER_V1_LOWPOWER
//#define USE_DECODER_V2
//#define USE_DECODER_V2_1
#define USE_DECODER_V2_2


// HCLG ���phones���
//#define FST_EXPERT_PHONES
// HCLG ���word���
#define FST_EXPERT_WORDS 

#endif // ! GLOBAL_H
