#include "../../inc/ush.h"

// видалення пробілів біля оператору
char *mx_replace_operator(char *s) {

    char *temp = mx_strdup(s);
    char *temp_two = NULL;
    /*printf("MX_REPLACE_OPERATOR_TRIM_TEMP: %s\n", temp);
    printf("SUBSTR_INDEX: %d\n", mx_get_substr_index(temp," && "));
    printf("REPLACE_SUBSTR: %s\n", mx_replace_substr(temp, " && ", "&&"));*/
    if (mx_get_substr_index(temp," && ")  >= 0) // якщо в рядку є &&
        temp_two = mx_replace_substr(temp, " && ", "&&"); // видаляємо пробіли біля них
    else if (mx_get_substr_index(temp," || ")  >= 0) // якщо в рядку є ||
        temp_two = mx_replace_substr(temp, " || ", "||"); // видаляємо пробіли біля них
    else
        temp_two = mx_strdup(temp); // інакше просто повертаємо вхідний рядок

    mx_strdel(&temp); // звільянємо непотрібну пам'ять
    
    return temp_two;
}

