#include "../inc/libmx.h"
char *mx_strncpy(char *dst, const char *src, int len) {
    char *ptr_dst = dst;

    for (int i = 0; i < len &&  (*dst++ = *src++) != '\0'; i++)
        ;
    return ptr_dst;

}
