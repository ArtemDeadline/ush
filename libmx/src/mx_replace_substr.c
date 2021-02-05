#include "../inc/libmx.h"
//Ururururu ru tassssssssss
//len - n*ru + n*tas

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == NULL || sub == NULL || replace == NULL)
        return NULL;
    int len_str = mx_strlen(str);
    int len_sub = mx_strlen(sub);
    int len_replace = mx_strlen(replace);
    int count_sub = mx_count_substr(str, sub);

    int len_new_str = len_str - count_sub * len_sub + count_sub * len_replace;

    char *new_str = mx_strnew(len_new_str);
    char *ptr_new_str = new_str;

    bool substr = false;
    
    /*printf("\nREPLACE: %s\n", replace);
    printf("\nSUB: %s\n", sub);
    printf("\nLEN_SUB: %d\n", len_sub);
    printf("\nLEN_REPLACE: %d\n", len_replace);*/

    for(int i = 0; *str; str++) {
        if(*str == sub[i] && i == 0 && !substr) {
            //printf("\nREAL CHECK: %c vs %c\n", *str, sub[i]);
            for(int j = i; j < len_sub; j++){
                //printf("\nCOMPARE: str[%d] == sub[%d] -> %c == %c\n", j, j, str[j], sub[j]);
                if(str[j] == sub[j])
                    substr =true;
                else{
                    substr = false;
                    break;
                }
                //printf("RESULT OF COMARING: i = %d, substr = %d\n", i, substr);
            }
            if(!substr){
                i = 0;
                //printf("insert: %c\n", *str);
                *new_str++ = *str;
            }
            else 
                i++;
        }
        else if(*str == sub[i] && substr)
            i++;
        else {
            i = 0;
            //printf("insert: %c\n", *str);
            *new_str++ = *str;
        }
        if (i == len_sub) {
            for(int j = 0; j < len_replace; j++) {
                //printf("insert: %c\n", replace[j]);
                *new_str++ = replace[j];
            }
            i = 0;
            substr = false;
        }
    }
    //printf("\nREPLACE: %s\n", ptr_new_str);
    return ptr_new_str;

}
