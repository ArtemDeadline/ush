#include "../../inc/ush.h"

void mx_setenv_ush(char *arg, t_ush *ush) {
    if (mx_strlen(arg) != 1 && arg[mx_strlen(arg) - 1] == '/')
        arg[mx_strlen(arg) - 1] = '\0';
    if (mx_strcmp(arg, ush->pwd_l) != 0) {
        mx_strdel(&ush->pwd_l);
        ush->pwd_l = mx_strdup(arg);
    }
    setenv("PWD", arg, 1); // системная функция установки в env  значение pwd
}

static void oldpwd(t_ush *ush) {
    mx_setenv_ush(MX_OLDPWD(), ush);
    setenv("OLDPWD", ush->pwd_l, 1);
}

static int handle_path(char *path, int flag, t_ush *ush) {
    int ret = 0; // возврат значене 0 - ве хорошо, ошибок нет. 1 -  ошибка функция не выпполнена успешно
    char *tmp = mx_strdup(path); // создание временного пути в нуль-терминированной строке   
    int link = mx_check_symlink(&tmp, flag, 1); // создание ссылки

    if (flag == 2 && link == 1) {
        fprintf(stderr, "cd: not a directory: %s\n", path); // сообщение об том что ппереданный ссылка указывает на что-то? но не на  dir 
        ret = 1; // ошибка
    }
    else if (mx_strcmp(tmp, "-") == 0) { // проверка на отсутствие флагов
        if (MX_OLDPWD() != NULL) // если предыдущая папка не указана,указывает
            oldpwd(ush); //собственно указывает пред. ссылку
        else {
            fprintf(stderr, "ush: cd: OLDPWD not set\n"); // ошибка не установленной преддыдущей папки 
            ret = 1; //ошибка
        }
    }
    else
        ret = mx_make_path(tmp, ush, flag); // создание папки (0 - успешно/ 1- папка не создана )
    mx_strdel(&tmp);
    return ret;
}

static void stay_here(t_ush *ush) { //переход в dir и сохранение предыдущей dir 
    char *arg = MX_HOME();

    setenv("OLDPWD", ush->pwd_l, 1); // установить в системе Unix пременную OLDPWD
    mx_setenv_ush(arg, ush); //установить текущую папку в PWD
    mx_strdel(&arg); // очистка arg
}

int mx_cd(char **args, t_ush *ush) { // выплнение команды "cd"
    int stop = 0;
    int len = mx_count_arr_el(args); // получение размера запросов у cd к пути/флагу
    int flag = 0;

    /*printf("\nARGS_SPLIT:\n");
    for (int i = 0; i < mx_count_arr_el(args); i++){
        printf("|%s|\n", args[i]);
    }*/
    for (int i = 0; i < mx_count_arr_el(args); i++){
        args[i] = fill_parsed_str(args[i], 0, 0);
    }
    /*printf("\nARGS_SPLIT_PARSED:\n");
    for (int i = 0; i < mx_count_arr_el(args); i++){
        printf("|%s|\n", args[i]);
    }*/

    if (len == 1 || (mx_strcmp(args[1], "--") == 0 && len == 2))
        stay_here(ush); //перейти в запрошеную dir
    else {
        for (int i = 1; i < len; i++) {
            if (mx_strcmp(args[i], "--") == 0) { // проверка на полное назване и отсечение их в случае нахождения
                stop = 3;
                continue;
            }
            if (stop == 0 && args[i][0] == '-') { // поиск флагов и выполнение их
                if ((flag = mx_find_flag("Ps", args[i])) > 0)
                    continue;
            }
            return handle_path(args[i], flag, ush);
        }
    }
    return 0;
}
