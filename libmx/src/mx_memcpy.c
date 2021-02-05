#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n){
    unsigned char *ptr = (unsigned char *)dst;
    unsigned char *ptr1 = (unsigned char *)src;
    for(size_t i = 0; i < n; i++) {
        *ptr++ = *ptr1++;
    }

    return dst;
}
