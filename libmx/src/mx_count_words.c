#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    if (str == NULL) return -1;
    if (*str == '\0') return 0;

    int count = 0;
    if (*str == c)
        count--;
    while (*str) {
        if (*str == c && *(str - 1) != c)
            count++;
        str++;
    }
    if (*(str - 1) != c)
        count++;

    return count;
}
