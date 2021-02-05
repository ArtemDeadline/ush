#include "../../inc/ush.h"
 //функция для получения name and value
static void change_export(char *arg, int len_n, char *name, char *value) { 
    int i = 0;

    for (i = 0; arg[i] != '='; i++) // запись 
        name[i] = arg[i];
    for (i = 0; arg[len_n + i + 1] != '\0'; i++)
        value[i] = arg[len_n + i + 1];
}
//УСТАНОВКА ЗНАЧЕНИЙ ПЕРЕМЕННЫХ ОКРУЖЕНИЯ  
int mx_export(char **args) { //выполнение команды export
    char *name = NULL; //имя
    char *value = NULL; //значение
    int len_n = 0; // длина имени 
    int len_v = 0; // длина значения

    for (int y = 1; y < mx_count_arr_el(args); y++) { // цикл работающий пока длинна мас. аргументов 
        len_n = mx_get_char_index(args[y], '=');
        if (len_n != -1) {
            len_v = mx_strlen(args[y]) - len_n - 1;
            name = mx_strnew(len_n);
            value = mx_strnew(len_v);
            change_export(args[y], len_n, name, value);
            setenv(name, value, 1); // установка name and value в env
            mx_strdel(&name); // очистка памяти имени
            mx_strdel(&value); // очистка памяти значения
        }
    }
    return 0;
}
// функция сброса
int mx_unset(char **args) { 
    for (int y = 1; y < mx_count_arr_el(args); y++) {
        unsetenv(args[y]); //удаление значения
    }
    return 0;
}


