#include "../inc/libmx.h"
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n){
    unsigned char *ptr = (unsigned char *)dst;
    unsigned char *ptr1 = (unsigned char *)src;
    for(size_t i = 0; i < n ; i++) {
         if(*ptr1 == c) {
            *ptr = *ptr1;
            break;
        }
        *ptr++ = *ptr1++;
       
    }

    return dst;
}
