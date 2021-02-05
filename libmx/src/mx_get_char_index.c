#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (str == NULL)
        return -2;

    for(int index = 0; *str; str++, index++) {
        if(*str == c)
            return index;
    } 
    
    return -1;        
}
