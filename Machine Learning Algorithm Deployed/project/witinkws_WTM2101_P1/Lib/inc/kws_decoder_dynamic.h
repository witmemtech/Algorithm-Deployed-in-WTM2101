#ifndef  KWS_DECODER_DYNAMIC
#define KWS_DECODER_DYNAMIC

#define ENABLE_DYNAMIC_WORD (1) // ��̬�ʿ��ء����û�ж�̬�ʣ�Ӧ����Ϊ0���Լ��ٲ���Ҫ����

bool check_dynamic_words(uint8_t* tok_words, uint8_t tok_word_len); //����Ƿ�ƥ���˶�̬��
char* get_dynamic_chinese_result(); // ��ȡ��̬�ʵĺ��ֽ��

#endif // ! KWS_DECODER_DYNAMIC
