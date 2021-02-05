#include "../inc/libmx.h"
void mx_print_strarr(char **arr, const char *delim) {
    if (arr == NULL || arr[0] == NULL || delim == NULL)
        return;

    mx_printstr(*arr++);
    while(*arr != NULL) {
        mx_printstr(delim);
        mx_printstr(*arr++);
        
    }
    mx_printchar('\n');
}
