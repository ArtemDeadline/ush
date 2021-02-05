#include "../../inc/ush.h"

// очищення рядку
void mx_clear_str() {
    write(STDOUT_FILENO, "\033[2K", 4); // очищення рядку
    mx_printstr("\033[G"); // повернення курсору назад
}
