#include "../../inc/ush.h"

char ** mx_split_by_space(char *s, char delimiter){
    int count = 1; 
    int len = mx_strlen(s);
    //printf("\nINPUT STR: |%s|\n", s);
    for(int i = 0; i < len; i++){
        if(s[i] == delimiter && s[i-1] != '\\' && s[i+1] != delimiter && s[i+1] != '\0')
            count++;
    } 

    char ** result = (char**) malloc(count*sizeof(char*) + 1);

    int k = 0;
    int start_index = -1;

    for(int i = 0; i < len && k < count; i++){
        for(int i = 0; i < len; i++){
            if(s[i] == delimiter && s[i-1] != '\\' && start_index != -2){
                result[k] = mx_strndup(&(s[start_index+1]), i - start_index-1);
                k++;
                if(s[i+1] != delimiter && s[i+1] != '\0'){
                    //printf("\nnorm space: %d\n", i);
                    start_index = i;
                }
                else
                    start_index = -2;
                
            }
            if(start_index == -2 && s[i+1] != delimiter && s[i+1] != '\0'){
                //printf("\nnorm space: %d\n", i);
                start_index = i;
            }
            if(start_index != i && start_index != -2 && s[i+1] == '\0'){
                if(i - start_index > 1)
                    result[k] = mx_strndup(&(s[start_index+1]), i - start_index);
                else
                    result[k] = mx_strndup(&(s[start_index+1]), 1);
                k++;
                start_index = -1;
            }
        } 
    }
    result[count] = NULL;
    /*printf("\nCOUNT: %d\nCOUNT_ARR_EL: %d\nSTR_SPLIT_BY SPACE:\n", count, mx_count_arr_el(result));
    for (int i = 0; i < mx_count_arr_el(result); i++){
        printf("|%s|\n", result[i]);
    }*/

    return result;
}
