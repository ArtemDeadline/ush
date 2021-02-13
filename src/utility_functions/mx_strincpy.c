#include "../../inc/ush.h"

char *mx_strincpy(char *dst, const char *src, int first, int end) {
    int i = first;
    int j = 0;

    while (src[i] && i != end) {
        //printf("dst[%d] vs src[%d] : %c vs %c\n", i, j, dst[j], src[i]);
        dst[j] = src[i];
        i++;
        j++;
    }
    return dst;
    //printf("DST: %s\n", dst);
}
