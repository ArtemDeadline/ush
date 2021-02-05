#include "../../inc/ush.h"

int mx_echo(char **args, char *temp) {
    int flag = 0;
    //printf("\n0:ECHO:input_str: %s\n", temp);
    char *str = mx_parse_echo(args, &flag, temp);
    //printf("\n1:ECHO:input_str: %s\n", temp);
    if (str != NULL)
        mx_printstr(str);
    if (flag == 0)
        mx_printchar('\n');
    else if (flag == -1)
        return 1;
    //printf("\nECHO:STR: %s\n", str);
    mx_strdel(&str);
    return 0;
}
