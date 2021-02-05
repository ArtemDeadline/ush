#include "../../inc/ush.h"

// перенесення даних з поточного терміналу в поточний процес
void mx_child_redirect(t_redirect *redirect) {
    signal(SIGTSTP, SIG_DFL);
    //printf("\nhi child redirect\n");
    if (redirect->flag == 1) {
        //printf("\nhi reading from terminal\n");
        // копіюємо з поточного терміналу вивід в поточний процес
        if (dup2(redirect->fd_stdout[1], 1) == -1){
            perror("dup2");
            //printf("\nbye reading from terminal\n");
        }
        //printf("\nstdout: %d\n", redirect->fd_stdout[1]);
        close(redirect->fd_stdout[0]);
    }
    // копіюємо з поточного терміналу вивід помилок в поточний процес
    if (dup2(redirect->fd_stderr[1], 2) == -1)
        perror("dup2");
    close(redirect->fd_stderr[1]);
}
