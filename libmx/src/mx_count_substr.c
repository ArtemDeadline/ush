#include "../inc/libmx.h"


int mx_count_substr(const char *str, const char *sub) {
    if (str == NULL || sub == NULL)
        return -1;
    if (*sub == '\0')
        return 0;
    int count_substr = 0;
    char *str_copy = (char *)str;

    while((str_copy = mx_delete_first_needle(str_copy, sub)) != NULL) {
        count_substr++;
        
    }
    return count_substr;
}
