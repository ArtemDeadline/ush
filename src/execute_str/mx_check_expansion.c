#include "../../inc/ush.h"


static char *dollar_change(int len, char **input) {
    char *variable = NULL;

    if ((*input)[1] == '{' && (*input)[len - 1] == '}') {
        variable = mx_strnew(len - 1);
        for (int y = 2, x = 0; y < len - 1; y++, x++)
            variable[x] = (*input)[y];
        variable[len - 3] = '=';
        variable[len - 2] = '\0';
    }
    else {
        variable = mx_strnew(len + 1);
        for (int y = 1, x = 0; y < len; y++, x++)
            variable[x] = (*input)[y];
        variable[len - 1] = '=';
        variable[len] = '\0';
    }
    return variable;
}

static void insert_str(char **in, int j, char *var, char* replace) {
    extern char **environ;
    char * value = mx_strndup(&(environ[j][mx_strlen(var)]), mx_strlen(environ[j]) - mx_strlen(var) + 1);

    //printf("\nREPLACE: %s\n", replace);
    //printf("\nVALUE: %s\n", value);

    *in = mx_replace_substr(*in, replace, value);
   
    //printf("\n*inp: %s\n", *in);
}

static void dollar_check(char **in, bool end_element) {
    char *var = NULL;
    extern char **environ;
    int flag = 0;
    int start_end = 0;
    //printf("\nDOLLAR_CHECK: %s\n", *in);
    int index = 0;
    char * ptr_to_input = *in;
    while(*ptr_to_input != '$'){
        //printf("\nWHILE: %c\tindex: %d\n", *ptr_to_input, index);
        index++;
        ptr_to_input++;
        /*for(int j = 0; j < 10000000; j++){
            printf("");
        }*/
    }
    //printf("\nINDEX: %d\n", index);
    int i = index;
    for(; i < mx_strlen(*in) && start_end != 2; i++){
        if((*in)[i] == '{' || (*in)[i] == '}')
            start_end++;        
        //printf("in[%d]: %c\t start_end: %d\n", i, (*in)[i], start_end);

        /*for(int j = 0; j < 10000000; j++){
            printf("");
        }*/

    }
    int len = i - index;
    //printf("\nlen: %d\n", len);
    //printf("\nDOLLAR_CHECK #2: %s\n", ptr_to_input);
    //printf("\nstr: %s; len: %d\n", ptr_to_input, len);
    char * temp = mx_strndup(ptr_to_input, len);
    //printf("\nTEMP: %s\n", temp);
    var = dollar_change(i - index, &temp);
    //printf("\nVAR: %s\n", var);
    for (int j = 0; environ[j]!= NULL; j++) {
        //printf("\nENVIRON[%d]: %s\n", j, environ[j]);
        
        if (strstr(mx_str_tolower(environ[j]), mx_str_tolower(var)) != NULL && mx_tolower(environ[j][0]) == mx_tolower(var[0])) {
            //printf("\nENVIRON[j]: %s\n", environ[j]);
            flag = 1;
            insert_str(in, j, var, temp);
            break;
        }
    }
    //printf("\nin before: %s\n", *in);
    if(!end_element){
        if (flag == 0) {
            mx_strdel(in);
            (*in) = mx_strdup("");
        }
    }
    else{
        *in = mx_replace_substr(*in, temp, "");
    }
    //printf("\nin after: %s\n", *in);
    
    mx_strdel(&var);
    mx_strdel(&temp);
}

//  перевірка на всякі розширення
char **mx_check_expansion(char **str_input, int ret_val) {
    int len = 0;
    char **input = mx_strsplit_echo(*str_input, ' ');
    //printf("\ninput before expansion:\n");
    /*for (int i = 0; i < mx_count_arr_el(input); i++){
        //printf("|%s|\n", input[i]);
    }*/
    for (int i = 0; i <= mx_count_arr_el(input); i++) {
        bool check = true;
        bool tilde = false;
        char **temp = NULL;
        bool end_element = false;
        if( i != mx_count_arr_el(input))
            temp = &(input[i]);
        else{
            temp = str_input;
            end_element = true;
        }
        //printf("\n1:CHECK_EXPANSION\nCHECK SEGMENTATION FAULT:1\n");
        while(check){
            check = false;
            //printf("\nINPUT[%d]: |%s|\n", i, *temp);
            //printf("\nINDEX: |%d|\n", mx_get_substr_index(*temp, "$"));
            if (mx_get_substr_index(*temp, "$?") >= 0) {
                //printf("\nDOLLAR_QUESTION CHECK\n");
                mx_strdel(&(*temp));
                *temp = mx_itoa(ret_val);
                check=true;
            }
            //int tilda_index = mx_get_substr_index(*temp, "~");
            //printf("\ntilda INDEX: %d\n", tilda_index);
            if (!tilde && mx_get_substr_index(*temp, "~") >= 0){
                //printf("\nTILDA CHECK\n");
                mx_tilde_check(temp);
                tilde = true;
                check = true;
            }
            len = mx_strlen(*temp);
            int dollar_index = mx_get_substr_index(*temp, "$");
            //printf("\nDOLLAR INDEX: %d\n", dollar_index);
            if (dollar_index >= 0 && (*temp)[dollar_index-1] != '\\'){
                //printf("\nDOLLAR CHECK\n");
                dollar_check(&(*temp), end_element);
                check = true;
            }
            //printf("\nCHECK: %d\n", check);
            //printf("\nPARSED_INPUT[%d]: |%s|\n", i, *temp);
        }
        //printf("\n2:CHECK_EXPANSION\nCHECK SEGMENTATION FAULT:2\n");
    }
    //printf("\ninput after expansion:\n");
    /*for (int i = 0; i < mx_count_arr_el(input); i++){
        printf("|%s|\n", input[i]);
    }*/
    //printf("\nstr_input after expansion: %s\n", *str_input);
    return input;
}

// touch \'\"\$\(\\\)\`file\ name
