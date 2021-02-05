#include "../../inc/ush.h"

static char *current_ush_path(char **commands){

    char *pwd = MX_PWD();
    char *ush_path = NULL;

    if (mx_strstr(commands[0], "./"))
        ush_path = mx_replace_substr(commands[0], ".", pwd);
    else
        ush_path = mx_strdup(commands[0]);
    mx_strdel(&pwd);
    return ush_path;
}

static t_dbl_list * mx_create_history_list(){
    
    //двозв'язний список, в якому зберігатиметься історія команд

    t_dbl_list * lst = (t_dbl_list*) malloc (sizeof(t_dbl_list));

    lst->data = NULL;
    lst->next = NULL;
    lst->prev = NULL;

    return lst;

}

t_ush* mx_create_ush(char **argv) {
    
    t_ush *ush = (t_ush *) malloc(sizeof(t_ush));

    ush->parent_pid = getpid();
    //printf("PARENT ID %d, parent group %d\n",ush->parent_pid,getpgrp());
    ush->command = NULL;
    ush->history = NULL;
    ush->exit_status = -1;
    ush->return_value = 0;
    ush->exit_non_term = 0;
    ush->pids = NULL;
    ush->str_input = NULL;
    ush->ush_path = current_ush_path(argv);
    ush->history = mx_create_history_list();
    ush->pwd_l = MX_PWD();

    return ush;

}
