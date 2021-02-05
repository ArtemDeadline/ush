#include "../../inc/ush.h"

// вивід даних в термінал
void mx_write_to_pipe(char *str, int *fd) {
    //printf("\nwriting to pipe ...\n");
    close(fd[0]);
    write(fd[1], str, strlen(str));
    close(fd[1]);
}

// зчитування даних з терміналу
void mx_read_from_pipe(char *str, int len, int *fd) {
    //printf("\nreading from pipe ...\n");
    close(fd[1]);
    read(fd[0], str, len);
    close(fd[0]);
}

