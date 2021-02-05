#include "../inc/libmx.h"

char* mx_strdup(const char *str) {
    char *str_copy = mx_strnew(mx_strlen(str));

    mx_strcpy(str_copy, str);

    return str_copy;
}

