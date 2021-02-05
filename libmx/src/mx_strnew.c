#include "../inc/libmx.h"

char* mx_strnew(const int size) {
    char *str = (char*)malloc(sizeof(char) * (size+1));

    for(int i = 0; i <= size; i++)
        str[i] = '\0';

    return str;
}
