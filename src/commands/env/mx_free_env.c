#include "../../../inc/ush.h"
//ОЧИСТКА
void mx_free_env(t_env *env) { // выполенение команды
    if (env != NULL) { //условие 
        mx_del_strarr(&env->env_var); // записать данные структур env в env_var
        mx_strdel(&env->comm_args); // записать данные структур env в comm_args
        mx_strdel(&env->comm); // записать данные структур env в comm
        free(env); // очистка входящей структуры env
    }
}
