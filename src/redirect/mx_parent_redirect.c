#include "../../inc/ush.h"

// зчитування з терміналу виводу та помилок
void mx_parent_redirect(t_redirect *redirect, int *return_) {
    //printf("\nparent redirect ...\n");
    if (redirect->flag == 1){
        mx_read_from_pipe(redirect->_stdout, 1000, redirect->fd_stdout);
        //printf("\nwe are reading from pipe ...\n");
    }
    mx_read_from_pipe(redirect->_stderr, 1000, redirect->fd_stderr);
    if (mx_strlen(redirect->_stderr) != 0) {
        *return_ = 1;
        mx_printstr(redirect->_stderr);
    }
    //
}
