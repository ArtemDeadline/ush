#include "../inc/libmx.h"

char* mx_del_extra_spaces(const char *str) {
    char *strim_str = mx_strtrim(str);
    int len = mx_strlen(strim_str);
    int new_len = 0;

    for(int i =0 ; i < len - 1; i++) {
        if (!mx_whitespace(strim_str[i]) ||  !mx_whitespace(strim_str[i+1])) {
            new_len++;
        
        }
    }
    char *new_str = mx_strnew(new_len);
     for(int i =0, j = 0; i < len; i++) {
        if (!mx_whitespace(strim_str[i]) ||  !mx_whitespace(strim_str[i+1])) {
            new_str[j] = strim_str[i];
            j++;
        }
    }

    free(strim_str);
    return new_str;
}


