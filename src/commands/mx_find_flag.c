#include "../../inc/ush.h"
//ПОИСК ФЛАГОВ
int mx_find_flag(char *flags, char *arg) { //выполнение команды
    int flag = 0;
//ЦИКЛЫ ДЛЯ ПОСИМВОЛЬНОГО СРАВНЕНИЯ ФЛАГОВ И СТРОКИ
    for (int i = 0; i < (int)strlen(flags); i++) { 
        for (int y = 1; y < (int)strlen(arg); y++) {
            if (arg[y] == flags[i]) { // условие если сивол равен флагу
                if (i + 1 > flag)
                    flag = i + 1;
                break;
            }
        }
    }
    return flag;
}
