#include "../../inc/ush.h"

static void path_symlink(char **arg) {
    char buf[1024]; // стандартный буфер
    ssize_t len = 0;

    if ((len = readlink(*arg, buf, 1024)) == -1)
        perror("readlink"); // битая ссылки или пустая
    buf[len] = '\0';
    mx_strdel(arg); //очистка строки
    if (buf[0] != '.') // кур дир
        *arg = mx_strjoin("/", buf); // к ссылке добавить 
    else
        *arg = mx_strdup(buf);// копи дир
}

int mx_check_symlink(char **arg, int flag, int link) { // указаный файл это ссылка ?
    struct stat *st = (struct stat *) malloc(sizeof (struct stat)); // выделене памяти 
    int is_link = 0; // это булл переменная, панятна ? 

    lstat(*arg, st); // считывание состояния файла 
    if ((st->st_mode & S_IFMT) == S_IFLNK) {
        is_link = 1; // это ссылка 
        if (flag == link) // если есть флаг  -L, использовать -L
            path_symlink(arg); 
    }
    if (st != NULL) {
        free(st); // освободить структуру
        st = NULL;
    }
    return is_link;// вернуть 1- это ссылка 0 - это не ссылка
}

