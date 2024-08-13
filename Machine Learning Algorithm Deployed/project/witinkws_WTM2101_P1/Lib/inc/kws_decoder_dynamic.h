#ifndef  KWS_DECODER_DYNAMIC
#define KWS_DECODER_DYNAMIC

#define ENABLE_DYNAMIC_WORD (1) // 动态词开关。如果没有动态词，应设置为0，以减少不必要计算

bool check_dynamic_words(uint8_t* tok_words, uint8_t tok_word_len); //检查是否匹配了动态词
char* get_dynamic_chinese_result(); // 获取动态词的汉字结果

#endif // ! KWS_DECODER_DYNAMIC
