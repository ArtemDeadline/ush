#include "../../inc/ush.h"
//ЗАВЕРШЕНИЕ РАБОТЫ ПРОЦЕССА 
int mx_exit(char **inp, int *exit_status) { //выполнение команды  exit
    int return_ = 0;

    if (mx_count_arr_el(inp) == 1) //если размер массива равен 1, срабатывает exit
        *exit_status = 0;
    else if (mx_atoi(inp[1]) == -2147483648 && mx_count_arr_el(inp) == 2) { //условие сравние 2 эл. inp 
        fprintf(stderr, "ush: exit: %s: numeric argument required\n", inp[1]); //вывод сообщения об ошибке
        return_ = 1; //возвращение
    }
    else if (mx_count_arr_el(inp) == 2) //если размер массива равен 2, exit-у присваивается 2 эл. inp
        *exit_status = mx_atoi(inp[1]);
    else {
        fprintf(stderr, "ush: exit: too many arguments\n"); // если ни одно условие не подходит, выводится сообщение об ошибке
        return_ = 1; //возвращение
    }
    return return_; 
}
