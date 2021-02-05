#include "../../inc/ush.h"

static void child_not_builtin(int *ret_val, char **input, char *command_p) {
    DIR *dp = NULL;
    extern char **environ;
    if ((dp = opendir(command_p)) != NULL) {
        fprintf(stderr, "ush: %s: is a directory\n", input[0]);
        *ret_val = 1;
        closedir(dp);
    }
    else if (mx_file_exist(command_p)) {

        //printf("\nbefore execve\n");
        //printf("\ncommand path: %s, input: %s\n", command_p, input[0]);
        /*printf("\nSTR_SPLIT:\n");
        for (int i = 0; i < mx_count_arr_el(input); i++){
            printf("|%s|\n", input[i]);
        }*/
        for (int i = 0; i < mx_count_arr_el(input); i++){
            input[i] = fill_parsed_str(input[i], 0, 0);
        }
        /*printf("\nSTR_SPLIT_PARSED:\n");
        for (int i = 0; i < mx_count_arr_el(input); i++){
            printf("|%s|\n", input[i]);
        }*/
        int exec = execve(command_p, input, environ);
        //printf("\after execve\n");


        if (exec == -1 && errno == EACCES) {
            fprintf(stderr, "ush: Permission denied:%s\n", input[0]);
            *ret_val = 1;
        }
    }
    else {
        fprintf(stderr, "ush: %s: command not found\n", input[0]);
        *ret_val = 1;
    }
}

static void child_free(char *command_p, int *fd, int ret_val) {
    char *ret = NULL;

    ret = mx_itoa(ret_val);
    mx_write_to_pipe(ret, fd);
    mx_strdel(&ret);
    mx_strdel(&command_p);
}

void mx_child_execute(int *ret, char **inp, t_redirect *red, t_ush *ush) {
    //printf("\nI'm child\n");
    /*printf("\nCOMMAND: %s\n", inp[0]);
    printf("\nSTR_SPLIT:\n");
        for (int i = 0; i < mx_count_arr_el(inp); i++){
            printf("|%s|\n", inp[i]);
    }
    for (int i = 0; i < mx_count_arr_el(inp); i++){
        inp[i] = fill_parsed_str(inp[i], 0, 0);
    }
    mx_parse_echo(&(inp[0]), 0, inp[0]);
    printf("\nCOMMAND: %s\n", inp[0]);
    printf("\nSTR_SPLIT_PARSED:\n");
        for (int i = 0; i < mx_count_arr_el(inp); i++){
            printf("|%s|\n", inp[i]);
    }*/
    char *com_p = mx_command_in_path(inp[0], getenv("PATH"));
    int command = mx_is_builtin_command(com_p);

    //printf("\nCHILD_EXECUTE:COMMAND: |%d|\n", command);

    mx_child_redirect(red);
    if (command == 2)
        *ret = mx_pwd(inp, ush);
    else if (command == 3)
        *ret = mx_env(inp, ush);
    else if (command == 8)
        *ret = mx_which(inp);
    else if (command == 9)
        *ret = mx_echo(inp, ush->str_input);
    else if (command == 10)
        *ret = mx_fg(ush);
    else if (command == 0 || command == 4) {
        if (mx_strcmp(com_p, "ush") == 0 || mx_strcmp(com_p, "./ush") == 0) {
            mx_strdel(&inp[0]);
            inp[0] = mx_strdup(ush->ush_path);
        }
        //printf("\ncheck not builtin\n");
        child_not_builtin(ret, inp, com_p);
        //printf("\ncheck not builtin\n");

    }
    child_free(com_p, red->fd_return, *ret);

    //printf("\n0: child_execute: parent_id: %d, child_curr_id: %d\n",ush->parent_pid, tcgetpgrp(1));
    tcsetpgrp(1,ush->parent_pid);
    //printf("\n1: child_execute: parent_id: %d, child_curr_id: %d\n",ush->parent_pid, tcgetpgrp(1));

    exit(0);
}

