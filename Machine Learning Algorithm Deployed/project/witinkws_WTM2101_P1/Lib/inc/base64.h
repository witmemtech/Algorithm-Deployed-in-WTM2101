#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>

// in : buffer of "raw" binary to be encoded.
// in_len : number of bytes to be encoded.
// out : pointer to buffer with enough memory, user is responsible for memory allocation, receives null-terminated string
// returns size of output including null byte
unsigned int b64_encode(const unsigned char* in, unsigned char* out, unsigned int in_len);

// in : buffer of base64 string to be decoded.
// in_len : number of bytes to be decoded.
// out : pointer to buffer with enough memory, user is responsible for memory allocation, receives "raw" binary
// returns size of output excluding null byte
unsigned int b64_decode(const unsigned char* in, unsigned char* out, unsigned int in_len);


#ifdef __cplusplus
}
#endif