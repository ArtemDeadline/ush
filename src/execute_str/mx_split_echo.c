#include "../../inc/ush.h"

char ** mx_strsplit_echo(char * src, char delimiter){
    char **result=NULL;
    char *src_ptr = src;

    // змінні для ідентифікації одинарної цитати
    bool bstart1 = false;
    int start1 = 0; 
    int end1 = 0;
    // змінні для ідентифікації подвійної цитати
    bool bstart2 = false;
    int start2 = 0; 
    int end2 = 0;
    // лічильник слів
    int counter = 0; // лічильник слів
    // змінні для ідентифікації нецитатних рядків
    int start3 = -1;
    int end3 = 0;


    for(int i = 0; i < mx_strlen(src); i++){
        
        // перевірка на одинарну цитату
        if( ((src_ptr[i] == '\'' && src_ptr[i-1] != '\\') || (src_ptr[i] == '\'' && src_ptr[i-1] == '\\' &&  src_ptr[i-2] == '\\'))
        && bstart1 == false && bstart2 != true){
            bstart1 = true;
        }
        else if(src_ptr[i] == '\'' && bstart1 == true && bstart2 != true){
            counter++;
            bstart1 = false;
        }

        // перевірка на подвійну цитату
        if( ((src_ptr[i] == '\"' && src_ptr[i-1] != '\\') || (src_ptr[i] == '\"' && src_ptr[i-1] == '\\' &&  src_ptr[i-2] == '\\'))
         && bstart2 == false && bstart1 != true){
            bstart2 = true;
        }
        else if( ((src_ptr[i] == '\"' && src_ptr[i-1] != '\\') || (src_ptr[i] == '\"' && src_ptr[i-1] == '\\' &&  src_ptr[i-2] == '\\'))
        && bstart2 == true && bstart1 != true){
            counter++;
            bstart2 = false;
        }

        // перевірка на нецитатність
        if(bstart1 == false && bstart2 == false && start3 == -1 && 
        ((src_ptr[i] != delimiter && src_ptr[i] != '\'' && src_ptr[i] != '\"') 
        || (src_ptr[i] == delimiter && src_ptr[i] == '\'' && src_ptr[i] == '\"' && src_ptr[i-1] == '\\'))) {
            start3 = i;
        }
        if(bstart1 == false && bstart2 == false && start3 != -1 && 
        (((src_ptr[i+1] == '\'' || src_ptr[i+1] == '\"') && src_ptr[i] != '\\') || src_ptr[i+1] == '\0')){
            end3 = i;
            if(end3 != start3){
                char * temp = mx_strndup(&(src[start3]), end3 - start3+1);
                counter += mx_count_arr_el(mx_split_by_space(temp, delimiter));
                free(temp);
                temp = NULL;
            }
            else{
                counter++;
            }
            start3 = -1;
        }


        if( (bstart1 || bstart2 ) && src_ptr[i+1] == '\0'){
            counter++;
        }
    }

    bstart1 = false;
    bstart2 = false;

    result = (char **) malloc((counter+1) * sizeof(char*));

    for(int i = 0, j = 0; i < mx_strlen(src) && j < counter; i++){

        // пошук та вставка одинарної цитати
        if( ((src_ptr[i] == '\'' && src_ptr[i-1] != '\\') || (src_ptr[i] == '\'' && src_ptr[i-1] == '\\' &&  src_ptr[i-2] == '\\'))
        && bstart1 == false && bstart2 != true){
            bstart1 = true;
            start1 = i;
        }
        else if(src_ptr[i] == '\'' 
        && bstart1 == true && bstart2 != true){
            bstart1 = false;
            end1 = i;
            result[j] = strndup(&(src_ptr[start1]), end1 - start1+1);
            j++;
        }

        // пошук та вставка двійної цитати
        if( ((src_ptr[i] == '\"' && src_ptr[i-1] != '\\') || (src_ptr[i] == '\"' && src_ptr[i-1] == '\\' &&  src_ptr[i-2] == '\\'))
        && bstart2 == false && bstart1 != true){
            bstart2 = true;
            start2 = i;
        }
        else if( ((src_ptr[i] == '\"' && src_ptr[i-1] != '\\') || (src_ptr[i] == '\"' && src_ptr[i-1] == '\\' &&  src_ptr[i-2] == '\\'))
        && bstart2 == true && bstart1 != true){
            bstart2 = false;
            end2 =i;
            result[j] = strndup(&(src_ptr[start2]), end2 - start2+1);
            j++;
        }

        // пошук та вставка простого рядку 
        if(bstart1 == false && bstart2 == false && start3 == -1 && 
        ((src_ptr[i] != delimiter && src_ptr[i] != '\'' && src_ptr[i] != '\"') 
        || (src_ptr[i] == delimiter && src_ptr[i] == '\'' && src_ptr[i] == '\"' && src_ptr[i-1] == '\\'))) {
            start3 = i;
        }
        if(bstart1 == false && bstart2 == false && start3 != -1 && 
        (((src_ptr[i+1] == '\'' || src_ptr[i+1] == '\"') && src_ptr[i] != '\\') || src_ptr[i+1] == '\0')){
            end3 = i;
            if(end3 != start3){
                char ** temp = mx_split_by_space(mx_strndup(&(src[start3]), end3 - start3+1), delimiter);
                for(int k = 0; k < mx_count_arr_el(temp); k++, j++){
                    result[j] = mx_strndup(temp[k], mx_strlen(temp[k]));
                }
                mx_free_void_arr((void **) temp, mx_count_arr_el(temp));
            }
            else{
                result[j] = mx_strndup(&(src[i]),1);
                j++;
            }
            start3 = -1;
        }


        if (bstart1 && src[i+1] == '\0'){
            if(start1 != i)
                result[j] = mx_strndup(&(src[start1]), i - start1 + 1);
            else
                result[j] = mx_strndup(&(src[i]),1);
            j++;
        }

        if (bstart2 && src[i+1] == '\0'){
            if(start2 != i)
                result[j] = mx_strndup(&(src[start2]), i - start2 + 1);
            else
                result[j] = mx_strndup(&(src[i]),1);
            j++;
        }

    }
    result[counter] = NULL;

    return result;
}

