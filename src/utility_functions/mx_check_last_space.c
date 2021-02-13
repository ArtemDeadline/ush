#include "../../inc/ush.h"

void mx_check_last_space(char ** str){
    bool last = false;
    char * ptr = "\0";

    if(mx_get_substr_index(*str, "\\") != -1){
            ptr = &((*str)[mx_get_substr_index(*str, "\\")]);
            /*printf("\n0:ENTER: |%s|\n", str);
            printf("0:ENTER: |%c|\n", str[mx_get_substr_index(str, "\\")]);*/
            last = true;
        }
    while(*ptr != '\0' && mx_get_substr_index(*str, "\\") != -1){
        //printf("%c\n", *ptr);
        if(*ptr == ' ' && last)
            last = true;
        else if(*ptr == '\\' && *(ptr+1) == ' '){
            last = true;
            ptr++;
        }
        else{
            last = false;
        }
        ptr++;
    }
    if((*str)[mx_get_substr_index(*str, "\\")+1] == ' ' && last){
        *str = mx_strtrim(*str);
        *str = mx_strjoin(*str, " ");
        //printf("1:ENTER: |%s|\n", str);
    }
    else{
        *str = mx_strtrim(*str);
        //printf("\n2:ENTER: |%s|\n", str);
    }

}
