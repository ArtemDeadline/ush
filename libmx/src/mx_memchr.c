#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n){
    unsigned char *ptr = (unsigned char*)s;
    for (size_t i = 0; i < n; i++) {
        if(*ptr == c)
            return ptr;
        ptr++;
    }
    return NULL;
}
