#ifndef  __BIN_LOADER__
#define __BIN_LOADER__

#ifdef __cplusplus
extern "C"
{
#endif

// get json start addr
unsigned char* get_json_addr(unsigned char* binPrt);

// get raw data start addr
unsigned char* get_raw_addr(unsigned char* binPtr);

// json len
int get_json_len(unsigned char* binPrt);

// raw len
int get_raw_len(unsigned char* binPrt);

// total len = json_len + rawlen
int get_total_len(unsigned char* binPrt);

void remove_offset_to_model(unsigned char *data_start);


#ifdef __cplusplus
}
#endif

#endif