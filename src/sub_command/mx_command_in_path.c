#include "../../inc/ush.h"
// пошук шляху до команди серед системних команд, які лежать в $PATH
static char *check_in_path(char *command, char **path) {
    char *command_p = NULL;
    // у циклі проходимо директорії з $PATH
    for (int i = 0; i < mx_count_arr_el(path); i++) {
        // виділяємо пам'ять під шлях і назву команди
        command_p = mx_strnew(mx_strlen(command) + mx_strlen(path[i]) + 1);
        // спочатку копіюємо одну з директорій
        mx_strcpy(command_p, path[i]);
        // потім до не додаємо /
        command_p = mx_strcat(command_p, "/");
        // і додаємо саму команду
        command_p = mx_strcat(command_p, command);
        // якщо існує такий файл, то виходимо передаючи цей шлях
        if (mx_file_exist(command_p))
            break;
        // інакше очищаємо змінну зі шляхом
        mx_strdel(&command_p);
    }
    return command_p;
}

char *mx_command_in_path(char *comm, char *str_path) {
    char **path = NULL; // шляхи, які лежать в $PATH
    char *command_p = NULL; // шлях до виконуваної функції, якщо він є
    int paths = 0; // кількість директорій в $PATH
    int i = 0; // лічильник
    // якщо змінна оточення PATH не пуста
    if (str_path != NULL) {
        path = mx_strsplit(str_path, ':'); // ділимо її по двоточкам
        paths = mx_count_arr_el(path); // рахуємо кількість директорій
        if (strstr(str_path, "PATH=") != NULL) {
            // перезаписуємо всі шляхи без /usr/
            for (; i < mx_strlen(path[0]) - 5; i++)
                path[0][i] = path[0][i + 5];
            path[0][i] = '\0';
        }
        // якщо команда не містить '/', то перевіряємо в її директоріях, які перед цим знайшли
        if (mx_strcmp(comm, "/") != 0 && mx_get_char_index(comm, '/') == -1)
            command_p = check_in_path(comm, path); // повертає шлях, якщо команда існує або 0 у зворотньому випадку
        mx_free_void_arr((void **) path, paths);
    }
    if (command_p == NULL) // якщо команди не існує, то повертаємо просто перший аргумент
        command_p = mx_strdup(comm);
    return command_p;
}
