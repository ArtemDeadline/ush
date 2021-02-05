#include "../../inc/ush.h"

// з рядку s видаляємо рядок str_join
static char *mx_replace(const char *s, char *str_join) {
    int leng_s = mx_strlen(s);
    int leng_str_join = mx_strlen(str_join);
    char *name = NULL;
    int i = 0;
    int j = leng_str_join;
    name = mx_strnew(leng_s - leng_str_join);
    while (s[j]) {
        name[i] = s[j];
        i++;
        j++;
    }
    name[i] = '\0';
    return name;
}

// повертає двовимірний масив, 1-им елементом є str_rep (сама команда), 2-им - NULL
static char **one_if(char *str_rep) {
    char **result = NULL;
    result = (char**) malloc(sizeof(char*) * (2));
    result[0] = mx_strdup(str_rep);
    result[1] = NULL;
    mx_strdel(&str_rep);
    return result;
}

// повертає команду й те, що залишилося після неї 
static char **two_if(char *str_rep, char *c) {
    // тут краще на прикладі пояснити
    // str_rep = "cd Desktop&&cd ush" і с = "&&"
    char **result = (char**) malloc(sizeof(char*) * (3));
    int leng = mx_get_substr_index(str_rep, c); // індекс першого входження в str_rep субрядку с = 10
    char *temp_str = mx_strndup(str_rep, leng); // записуєм в temp_str leng символів з str_rep
    //тобто temp_str = "cd Desktop"
    char *str_replace = mx_strndup(str_rep, leng + 2); // записуєм в str_replace leng+2 символів з str_rep
    // тобто str_replace = "cd Desktop&&"
    char *str_trim = NULL;
    result[0] = temp_str; // перший елемент результату - команда, яку ми вирізали "cd Desktop"
    str_trim = mx_replace(str_rep, str_replace); // видаляємо з str_rep рядок str_replace
    // тобто str_trim = "cd ush"
    result[1] = mx_strtrim(str_trim); // тобто другий елемент результату - інші команди, що залишилися справа
    result[2] = NULL;
    // звільняємо всю іншу пам'ять
    mx_strdel(&str_replace);
    mx_strdel(&str_trim);
    return result;
}

// функція поділу рядку s по деліметру c
char **mx_strsplit_one(const char *s, char *c) {
    char **result = NULL;
    char *str_rep = NULL;
    // видалення пробілів біля операторів && і || в s рядку
    //printf("BEFORE REPLACE LOGIC OPERAND: %s\n", s);
    str_rep = mx_replace_operator((char *)s);
    //printf("REPLACE LOGIC OPERAND: %s\n", str_rep);

    // якщо в рядку немає && і ||
    if (mx_count_queue_operation(str_rep) == 0)
        result = one_if(str_rep); // повертаємо лише команду
    else
        result = two_if(str_rep, c); // повертає команду й рядок з іншими, що залишилися справа від неї
    mx_strdel(&str_rep); // очищення пам'яті
    return result;
}

