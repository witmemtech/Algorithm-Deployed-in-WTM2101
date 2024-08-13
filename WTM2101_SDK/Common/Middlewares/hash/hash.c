#include "hash.h"

unsigned int wslhash_rs(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char  *)_str;
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash = hash * a + (*str);
        a = a * b;
    }

    return hash;
}
/* End Of RS Hash Function */


unsigned int wslhash_js(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    unsigned int hash = 1315423911;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}
/* End Of JS Hash Function */


unsigned int wslhash_pjw(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}
/* End Of  P. J. Weinberger Hash Function */


unsigned int wslhash_elf(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash = (hash << 4) + (*str);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }

    return hash;
}
/* End Of ELF Hash Function */


unsigned int wslhash_bkd(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}
/* End Of BKDR Hash Function */


unsigned int wslhash_sdbm(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}
/* End Of SDBM Hash Function */


unsigned int wslhash_djb(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    unsigned int hash = 5381;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}
/* End Of DJB Hash Function */


unsigned int wslhash_dek(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    unsigned int hash = len;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }
    return hash;
}
/* End Of DEK Hash Function */


unsigned int wslhash_bp(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    unsigned int hash = 0;
    unsigned int i = 0;
    for (i = 0; i < len; str++, i++)
    {
        hash = hash << 7 ^ (*str);
    }

    return hash;
}
/* End Of BP Hash Function */


unsigned int wslhash_fnv(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash *= fnv_prime;
        hash ^= (*str);
    }

    return hash;
}
/* End Of FNV Hash Function */


unsigned int wslhash_ap(void* _str, unsigned int len)
{
    unsigned char * str = (unsigned char *)_str;
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++)
    {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
            (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
}
/* End Of AP Hash Function */
