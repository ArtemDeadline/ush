#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    if(str == NULL)
        return NULL;

    while(mx_whitespace(*str))
        str++;
    
    int str_len = mx_strlen(str);
    int i = 0;

    for(i = str_len - 1; mx_whitespace(str[i]); i--) {

    }
    char *new_str = mx_strndup(str, ++i);

    return new_str;
    
}
