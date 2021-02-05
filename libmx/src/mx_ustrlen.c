#include "../inc/libmx.h"
int mx_ustrlen(const unsigned char *s) {
    int strlen = 0;

    while(*s++ != '\0')
        strlen++;
    
    return strlen;
}
