#include "../../inc/ush.h"

void mx_env_error(t_env *env, char **args, int i) {
    if (mx_file_exist(args[i]) != 1) // если файла нет -- ошибка
        fprintf(stderr, "env: %s: No such file or directory\n", args[i]); // --хозяен! а файла то нет! --какнет?  --да вот так ! читай!
    else if (mx_file_exist(args[i]) == 1) // файл есть, но открытие невозможно
        fprintf(stderr, "env: %s: Permission denied\n", args[i]); // недостаточно прав
    mx_free_env(env); // очистка 
}
