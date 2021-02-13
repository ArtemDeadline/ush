#include "../../inc/ush.h"

void escape_chars(int i, char *str, char *parse_str, int index) {
    if (str[i] == 'a')
        parse_str[index] = '\a';
    else if (str[i] == 'b')
        parse_str[index] = '\b';
    else if (str[i] == 't')
        parse_str[index] = '\t';
    else if (str[i] == 'n')
        parse_str[index] = '\n';
    else if (str[i] == 'v')
        parse_str[index] = '\v';
    else if (str[i] == 'f')
        parse_str[index] = '\f';
    else if (str[i] == 'r')
        parse_str[index] = '\r';
    else
        parse_str[index] = str[i];
}

int quot_error(char **parse_str, int *flag_n, int flag_quot) {
    if (flag_quot == -1) {
        *flag_n = -1;
        mx_strdel(parse_str);
        fprintf(stderr, "Odd number of quotes.\n");
        return -1;
    }
    return 0;
}
// баг: \ \ \ \ мають залишатися всередині лапок
char *fill_parsed_str(char *str, int *flag_n, int flag) {
    char *parse_str = mx_strnew(1000);
    int flag_quot = 1;
    int index = 0;
    bool single_flag = 0;
    bool double_citata =  0;

    //printf("\nflag: |%d|\n", flag);

    for (int i = 0; str[i] != '\0'; i++) {

        //printf("[%d]: %c\n", i, str[i]);
        
        if ( ((str[i] == '\'') || (str[i]== '\\'&& str[i+1] == '\'' )) 
        && single_flag == 1){
            flag_quot *= -1;
            single_flag  = !single_flag;
        }
        else if(str[i] == '\'' && str[i-1] != '\\' && single_flag == 0 && !double_citata){
            flag_quot *= -1;
            single_flag = !single_flag;
        }
        else if( ((str[i] == '\"' && str[i-1] != '\\') || (str[i] == '\"' && str[i-1] == '\\' &&  str[i-2] == '\\')) 
        && single_flag == 0){
            flag_quot *= -1;
            double_citata = !double_citata;
        }
        else if (flag == 1 && str[i] == '\\' && flag_quot == -1)
            escape_chars(++i, str, parse_str, index++);
        else if (str[i] == '\\' && flag_quot == 1)
            parse_str[index++] = str[++i];
        else
            parse_str[index++] = str[i];

    }
    parse_str[index] = '\0';
    if (quot_error(&parse_str, flag_n, flag_quot) == -1)
        *flag_n = -1;
    mx_strdel(&str);
    return parse_str;
}

static int echo_flag(char *arg, int *flag_n) {
    int flag = 1;

    for (int y = 1; y < mx_strlen(arg); y++) {
        if (arg[y] == 'e' && flag != 2)
            flag = 1;
        else if (arg[y] == 'E' || arg[y] == 'e')
            flag = 2;
        else if (arg[y] == 'n')
            *flag_n = 1;
        else {
            flag = -1;
            break;
        }
    }
    return flag;
}

char *mx_parse_echo(char **args, int *flag_n, char* temp) {
    int flag = 1;
    char *str = NULL;
    //printf("\noriginal: |%s|\n", temp);
    char * temp_str = mx_strdup(temp);
    char * start_temp_str = temp_str; // for deleting
    bool space = false;

    /*printf("\nTEMP: |%s|\n", temp_str);
    printf("ARGS\n");
    for(int i = 0; i < mx_count_arr_el(args); i++)
        printf("args[%d]: |%s|\n", i, args[i]);*/

    for (int i = 1; i < mx_count_arr_el(args); i++) {
        if (args[i][0] == '-' && str == NULL && flag != -1) {
            flag = echo_flag(args[i], flag_n);
            if (flag >= 0)
                continue;
        }
        temp_str = &temp_str[mx_get_substr_index(temp_str, args[i]) + 1];
        //printf("\nargs[i]: |%s|\n", args[i]);
        //printf("temp_str: |%s|\n", temp_str);
        //printf("last char: |%c|\n", temp_str[mx_strlen(args[i])]);
        if(temp_str[mx_strlen(args[i])-1] == ' ')
            space = true;

        if (str == NULL && mx_strcmp(args[i], "") != 0){
            str = strdup(args[i]);
            if(space)
                strcat(str, " ");
        }
        else if (mx_strcmp(args[i], "") != 0) {
            str = realloc(str, strlen(str) + strlen(args[i]) + 2);
            
            strcat(str, args[i]);
            if(space)
                strcat(str, " ");
        }
        temp_str = &temp_str[mx_strlen(args[i])-1];
        //printf("1:temp_str: |%s|\n", temp_str);
        //printf("str: |%s|\n", str);
        space = false;
    }
    free(start_temp_str);
    start_temp_str = NULL;
    //printf("\nSTR1: |%s|\n",str);
    if (str != NULL)
        str = fill_parsed_str(str, flag_n, flag);

    //printf("\nSTR2: |%s|\n",str);
    return str;
}
