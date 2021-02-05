#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    unsigned char *ptr = (unsigned char*)s;

    for(size_t i = n - 1; i > 0; i--) {
        if (ptr[i] == c)
            return &ptr[i];
    }
    return NULL;
}
