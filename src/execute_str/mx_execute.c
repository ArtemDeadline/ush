#include "../../inc/ush.h"

static int par_exec_command(char **input, t_ush *ush, pid_t pid) {

    char *command_p = mx_command_in_path(input[0], MX_PATH());
    int command = mx_is_builtin_command(command_p);
    int ret_val = 0;

    ush->curr_pid = pid;
    if (command == 1)
        ret_val = mx_cd(input, ush);
    else if (command == 5)
        ret_val = mx_export(input);
    else if (command == 6)
        ret_val = mx_unset(input);
    else if (command == 7)
        ret_val = mx_exit(input, &ush->exit_status);
    mx_strdel(&command_p);
    return ret_val;

}

static void check_for_redir(int *ret, int *fd, t_redirect *red, t_ush *ush, pid_t pid) {
    char *ret_str = mx_strnew(1);
    int status = 0;
    mx_swap_pids(ush); // виведення бекграудних процесів на передній план
    //print_all_pids(ush->pids);
    waitpid(ush->curr_pid, &status, WUNTRACED); // чекаємо поки процес завершиться
    
    //printf("\nprocess %d: status: %d\n", ush->pids->num, status);

    if(WIFEXITED(status)){
        //printf("\nkill %d: status: %d\n", ush->pids->num, status);

        //kill(ush->pids->num,SIGTERM);

        //mx_set_shell_environ();
        
        *ret = WEXITSTATUS(status);
    }
    else{
        //printf("\nkill %d: status: %d\n", ush->pids->num, status);
        if(WIFSIGNALED(status)){
            //printf("\nkill %d: status: %d\n", ush->pids->num, status);
            //mx_set_shell_environ();
            //mx_printchar('\n');
            *ret = WTERMSIG(status);
        }
        //printf("\nkill %d: status: %d\n", ush->pids->num, status);

    }
    if(!WIFSTOPPED(status)) {
            mx_read_from_pipe(ret_str, 1, fd); // зчитуємо з терміналу
            mx_parent_redirect(red, ret); // зчитування виводу та помилок з терміналу
    }
    if(WIFSTOPPED(status)) { // CTRL+Z
        tcsetpgrp(1,ush->parent_pid);
        mx_push_pid(pid, &ush); // пекидування процесу на задній план
        //printf("SSASA ++  %d,XX ___ %d",ush->parent_pid, tcgetpgrp(1));
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        *ret = 146;
        printf("\nush: suspended  %s\n", ush->str_input);
    }
    else if (mx_atoi(ret_str) == 1 || *ret == 1){ // зчитування значення статусу
        *ret = 1;
    }
    else{
        *ret = 0;
    }
    mx_strdel(&ret_str);
}

// виконати команду
int mx_execute(t_ush *ush, char *str_input, int flag_redir, char **str_red) {

    mx_check_last_space(&str_input);
    //printf("EXECUTE\ninput_str: |%s|\n", str_input);
    //ush->curr_pid = ush->pids->num;
    // process_id
    char **input = mx_check_expansion(&str_input, ush->return_value);
    //printf("\n0: execute: parent_id: %d, par_curr_id: %d\n", ush->parent_pid, ush->curr_pid);
    //printf("\n0: execute: parent_id: %d, lider_id: %d\n", ush->parent_pid, tcgetpgrp(1));
    

    if(strcmp(input[0],"fg") == 0){
        //printf("\t|-Start fg-|\t");
        //printf("\n0: execute: parent_id: %d, par_lid_id: %d\n",ush->parent_pid, tcgetpgrp(1));
        //print_all_pids(ush->pids);
        mx_fg(ush);
        tcsetpgrp(1, ush->parent_pid);
        return 1;
    }
    //printf("\nfg wasn't launched\n");
    pid_t pid;
    // значення статусу викоонання команди
    int return_ = 0;
    // перевірка на розширення
    t_redirect *redirect = mx_create_redirect(flag_redir);
    ush->str_input = str_input;
    //print_all_pids(ush->pids);
    // створення нового процесу
    /*printf("STR_INPUT: |%s|\nSTR_SPLIT:\n", str_input);
    for (int i = 0; i < mx_count_arr_el(input); i++){
        printf("|%s|\n", input[i]);
    }*/

    /*printf("STR_INPUT: %s\nSTR_SPLIT:\n", str_input);
    for (int i = 0; i < mx_count_arr_el(input); i++){
        printf("|%s|\n", input[i]);
    }*/

    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    //printf("\nfork\n");
    pid = fork();
    if (pid != 0) { // тіло для батьківського процесу
        //printf("\n0: execute: parent_id: %d, par_curr_id: %d\n",ush->parent_pid, tcgetpgrp(1));
        // перевіряємо, чи існує така системна функція (якщо так, то буде шлях, до цієї команди, NULL - у зворотньому випадку)
        return_ = par_exec_command(input, ush, pid);
        check_for_redir(&return_, redirect->fd_return, redirect, ush, pid); // перевірка на процеси
        tcsetpgrp(1, ush->parent_pid);
    }
    else {// код  для дочірнього процесу
        setpgid(getpid(), getpid());
        tcsetpgrp(1, getpid());
        //printf("\nCHILD_JOB\n");
        //printf("\n1: execute: parent_id: %d, child_curr_id: %d\n",ush->parent_pid, tcgetpgrp(1));
        mx_child_execute(&return_, input, redirect, ush); // якщо зі сторонніми процесамии все добре виконуємо поточний похідний процес
        //printf("\n1: execute: parent_id: %d, change_curr_id: %d\n",ush->parent_pid, tcgetpgrp(1));
    }
    //printf("\nHAT PROCESS id: %d\t\n", pid);
    //printf("\nEXECUTE:STROUT: %s\n", redirect->_stdout);
    if (redirect->_stdout != NULL && flag_redir == 1) {
        if (redirect->_stdout[mx_strlen(redirect->_stdout) - 1] == '\n')
            redirect->_stdout[mx_strlen(redirect->_stdout) - 1] = '\0';
        *str_red = mx_strdup(redirect->_stdout);// повертаємо вивід з терміналу
    }
    //printf("\nEXECUTE:STR_READ: %s\n", *str_red);
    /*printf("\n\tFINISH EXECUTE\n");
    printf("\nSSASA BATA++  %d,XX ___ %d\n",ush->parent_pid, tcgetpgrp(1));
    print_all_pids(ush->pids);*/
    mx_free_execute(redirect, input);
    return return_;
}
