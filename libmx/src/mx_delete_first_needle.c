#include "../inc/libmx.h"

char *mx_delete_first_needle(const char *haystack, const char *needle) {
    int len_needle = mx_strlen(needle);

    for(int i = 0; *haystack; haystack++) {
        if(*haystack == needle[i]) 
            i++;
        else
            i = 0;
        if (i == len_needle)
            return (char*)++haystack;

    }

    return NULL;
}
