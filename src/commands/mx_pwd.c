#include "../../inc/ush.h"

static void cd_err(char c, int *flag) { //функция проверки на правильность ввода флагов
    if (c != '\0') 
        fprintf(stderr, MX_PWD_ERR, c); //вывод о неправильности ввода флагов из директивы
    else
        fprintf(stderr, "pwd: too many arguments\n");
    *flag = 3;
}

static void parse_pwd(char **args, int *flag) { //функция анализа pwd
    int len = mx_count_arr_el(args); //получение размера запросов к файлу 

    for (int i = 1, stop = 0; i < len; i++) {
        if (mx_strcmp(args[i], "--") == 0) //проверка на заверешние флагов 
            stop = 3;
        if (stop == 0 && args[i][0] == '-') { //поиск флагов
            for (int y =1; y < mx_strlen(args[i]); y++) {
                if (args[i][y] != 'L' && args[i][y] != 'P') {//сравнивание флагов L and P, если ни одного из флагов нету происходит остановка программы
                    cd_err(args[i][y], flag);
                    break;
                }
            }
            if (*flag == 3) //остановка программы при наличии 3-х флагов
                break;
            if((*flag = mx_find_flag("LP", args[i])) > 0) //сравнение 2-х флугов записаных вместе 
                continue; //возвращение к началу цикла
        }
        else
            cd_err('\0', flag);
    }
}

//ВЫВОД РАБОЧИХ КАТАЛОГОВ
int mx_pwd(char **args, t_ush *ush) { //выполнение команды pwd
    int flag = 0; //флаг
    char *position = NULL; //символ
    int is_link = 0; //full

    parse_pwd(args, &flag); //анализируем pwd
    if (flag != 2)
        position = mx_strdup(ush->pwd_l);
    else {
        position = MX_PWD(); //получаем символьную строку с нашей директивы
        is_link = mx_check_symlink(&position, flag, 2);
    }
    if (flag != 3) { //условие с проверкой флага
        mx_printstr(position);
        mx_printchar('\n');
    }
    else {
        mx_strdel(&position);
        return 1;
    }
    mx_strdel(&position);
    return 0;
}
