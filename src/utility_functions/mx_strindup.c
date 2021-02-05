#include "../../inc/ush.h"

char *mx_strindup(const char *data, int first, int end) {
    char *new = NULL;

    if (!data)
        return NULL;
    new = mx_strnew(end - first);
    return mx_strincpy(new, data, first, end);
}
