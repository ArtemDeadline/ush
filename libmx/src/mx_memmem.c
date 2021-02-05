#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len){
    unsigned char *ptr = (unsigned char*)big;
    unsigned char *ptr1 = (unsigned char*)little;

    for(size_t i = 0; i < big_len; i++){
        if(ptr[i] == ptr1[0]){
            for(size_t j = 0; j < little_len; j++){
                if(ptr[i+j] != ptr1[j])
                    break;
                if(ptr1[j+1] =='\0')
                   return &ptr[i];
            }
        }
    }

    return NULL;
}
