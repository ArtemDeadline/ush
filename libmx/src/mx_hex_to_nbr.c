#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long n = 0;
    int len = 0;
    const char *ptr_hex = hex;
    unsigned long base = 1;
    
    while(*ptr_hex++ != '\0') 
        len++;
    
    for(int i = 1; i <= len; i++, base*=16) {
        if (hex[len - i] >= 'A' && hex[len - i] <= 'F') 
            n += (hex[len - i] - 55) * base;

        if (hex[len - i] >= '0' && hex[len - i] <= '9')
            n += (hex[len - i] - 48) * base;

        if (hex[len - i] >= 'a' && hex[len - i] <= 'f') 
            n += (hex[len - i] - 87) * base;
    }
    return n;
}
