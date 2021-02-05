#include "../inc/libmx.h"

char* mx_strcpy(char *dst, const char* src) {
    char *ptr_dst = dst;

    while((*dst++ = *src++) != '\0') 
        ;

    return ptr_dst;
}
