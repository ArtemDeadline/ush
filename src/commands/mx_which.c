#include "../../inc/ush.h"

static int is_comm_rw(char *str) { //функц. зарезерв слов
    char reserved_words[][7] = {"!", "{", "}", "time", "export"}; // объявлены зарезервированые слова/символы

    for (int i = 0; i < 5; i++) { //цикл проверки количества зарезерв. слов 
        //printf("RESERVED WORDS: |%s| vs |%s| = %d\n", str, reserved_words[i], strcmp(str, reserved_words[i]) == 0);
        if (strcmp(str, reserved_words[i]) == 0)
            return 1;
    }
    return -1;
}
//ФУНКЦИЯ ПРОВЕРКИ ВСТРОЕННЫХ ФУНКЦИЙ
static void check_builtin(char *input, int *ret_flag, int flag) {
    char *tmp = NULL; //создание временной переменной

    tmp = mx_command_in_path(input, MX_PATH()); //запись пути файла во временною переменною
    if (mx_is_builtin_command(tmp) != 0 && mx_is_builtin_command(tmp) != 5 && mx_is_builtin_command(tmp) != 3) { 
        printf("%s: shell built-in command\n", input); // путь к команде которую ищем отсутсвует так как она системная
        if (flag == 2 && strcmp(tmp, input) != 0 && flag != 1) //если они разные вывод пути
            printf("%s\n", tmp);
    }
    else if (strcmp(tmp, input) != 0) { 
        if (flag != 1)
            printf("%s\n", tmp);
    }
    else{
        fprintf(stderr, "%s not found\n", input);
        *ret_flag = 1;
    }
    mx_strdel(&tmp); //очистка временной памяти
}
//берет список имен команд и ищет путь к каждому исполняемому файлу, 
//который был бы запущен, если бы эти команды действительно были вызваны
static void check_command(char *input, int *ret_flag, int flag) { //функция проверки команд
    char **path = NULL; // создание переменной path

    if (is_comm_rw(input) == 1) // проверка на зарезирвиронное слово/символ (1 - совпадние есть/ -1 - зарезервированные слова не найдены)
        printf("%s: shell reserved word\n", input); // вывод ошибки
    else if (mx_get_char_index(input, '/') != -1) { //условие на совпадение символа (-1 - совпадние есть/ индекс совпадения - зарезервированные слова не найдены)
        path = mx_strsplit(MX_PATH(), ':'); // разделение строки ввода на элементы
        for (int y = 0; y < mx_count_arr_el(path); y++) { // цикл количетсво элиментов
            if (mx_get_substr_index(input, path[y]) != -1 && mx_file_exist(input)) { // проверка на совпадение и поиск файлов в директории
                if (flag != 1)
                    printf("%s\n", input); // вывод найденого элемента 
                *ret_flag = 0;
                break;
            }
            *ret_flag = 1;
        }
        mx_free_void_arr((void**)path, mx_count_arr_el(path)); // освобождение пути
    }
    else
        check_builtin(input, ret_flag, flag);
}

static int check_flag(char *input, int *flag) { //функция проверки флагов
    for (int y = 1; y < mx_strlen(input); y++) {
        if (input[y] == 's' && *flag != 2) //сравние флага s 
            *flag = 1;
        else if (input[y] == 'a') // сравнивание ввода флага a
            *flag = 2;
        else {
            fprintf(stderr, MX_WHICH_US, input[y]); //выводиться сообщение об ошибках
            return 1;
        }
    }
    return 0;
}

int mx_which(char **input) { //выполнение команды which
    int flag = 0; //флаг
    int ret_flag = 0;

    if (mx_count_arr_el(input) == 1) {
        fprintf(stderr, "usage: which [-as] program ...\n"); //сообщение об ошибке
        return 1;
    }
    for (int i = 1; i < mx_count_arr_el(input); i++) {
        if (strcmp(input[i], "--") == 0) //проверка на заверешение флагов
            flag = 3;
        else if (input[i][0] == '-' && flag < 3) { // поиск флагов
            if ((ret_flag = check_flag(input[i], &flag)) == 0) 
                continue;
        }
        check_command(input[i], &ret_flag, flag); 
    }
    return ret_flag;
}


