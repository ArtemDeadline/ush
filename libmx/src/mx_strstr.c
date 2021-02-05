#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int len_needle = mx_strlen(needle);
    if (!len_needle)
        return (char*)haystack;

    for(int i = 0; *haystack; haystack++) {
        if(*haystack == needle[i]) 
            i++;
        else
            i = 0;
            
        if (i == len_needle)
            return (char*)++haystack - i;

    }

    return NULL;
}
