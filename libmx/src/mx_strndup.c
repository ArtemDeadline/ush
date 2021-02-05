#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *str = NULL;
    size_t len = mx_strlen(s1);
    
    if (len > n)
        len = n;

    str = mx_strnew((int)len);
    return mx_strncpy(str, s1, n);

}
