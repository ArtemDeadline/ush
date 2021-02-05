#include "../../inc/ush.h"
//ОПРЕДЕЛЕНИЕ СУЩЕСТВОВАНИЯ ФАЙЛА
int mx_file_exist(char *path) { // выполнение команды
    struct stat *st = (struct stat*) malloc(sizeof (struct stat)); // выделение памяти
    int flag = 0;

    if ((lstat(path, st) != -1)) // получение данных о файле
        flag = 1;
    if (st != NULL) { // если данных нет
        free(st);
        st = NULL;
    }
    return flag;
}
