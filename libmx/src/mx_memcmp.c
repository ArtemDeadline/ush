#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
      unsigned char *ptr = (unsigned char *)s1;
    unsigned char *ptr1 = (unsigned char *)s2;

    for (size_t i = 0; i < n; i++,ptr++, ptr1++ ) {
        if (*ptr != *ptr1)
            return *ptr - *ptr1;
    }

    return 0;
}
