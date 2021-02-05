#include "../inc/libmx.h"

void mx_del_strarr(char ***arr) {
   char **ptr  = *arr;

    while(*ptr != NULL) {
        mx_strdel(ptr);
        ptr++;
    }

    free(*arr);
    *arr = NULL;
}
