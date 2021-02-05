#include "../../inc/ush.h"

// сортування історії
void mx_sort_history(t_ush *ush, char *temp) {

    char *p = mx_strdup(ush->history->data); // записуємо поточну команду в історії в змінну

    mx_strdel(&ush->history->data); // очищуємо поточну команду в історії

    ush->history->data = mx_strdup(temp); // записуємо в поточну команду temp

    while (ush->history->next != NULL) // якщо наступна команда існує
        ush->history = ush->history->next; // записуємо її в поточну
    ush->history->data = p; // а в значення записуємо саму команду
}
