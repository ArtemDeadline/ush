#include "../inc/libmx.h"
char *mx_strcat(char *restrict s1, const char *restrict s2) {
    char *ptr_s1 = s1;

    while(*s1)
        s1++;

    while((*s1++ = *s2++) != '\0') 
        ;

    return ptr_s1;
}
