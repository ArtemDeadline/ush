#include "../inc/libmx.h"

char * mx_str_tolower(char * str){
    char * result = mx_strdup(str);
    for (int i = 0; i < mx_strlen(str); i++)
        result[i] = mx_tolower(str[i]);
    return result;
}
