#include "../../inc/ush.h"

// знаходження індексу першої появи sub в str 
static int get_flag_index(const char *str, const char *sub) {
    
    int len_str = 0; // довжина рядка
    int len_sub = 0; // довжина шуканого рядка

    // перевірка на NULL 
    if (!str || !sub)
        return -2;
    
    // заповнення довжин
    len_str = mx_strlen(str); 
    len_sub = mx_strlen(sub);

    // цикл для посимвольного порівняння 
    for (int i = 0; i <= len_str - len_sub; i++)
        if (!mx_strncmp(&str[i], sub, len_sub)) // й знаходження першого співпадіння
            return i; // повернення індексу першої появи шуканого рядку в str 

    return INT_MAX; // якщо шуканого рядку немає в str, то повертаємо INT_MAX
}

static char *push_back_queue(char *logic, char *temp, t_queue **arr_queue) {
    
    char **arr_str = NULL;

    arr_str = mx_strsplit_one(temp, logic); // поділити рядок по логічному операнду

    /*printf("SPLIT BY LOGIC OPERAND\n");
    for (int i = 0; i < mx_count_arr_el(arr_str); i++){
        printf("%s\n", arr_str[i]);
    }*/

    mx_push_back_queue(arr_queue, arr_str[0], logic[0]); // додаємо команду в кінець черги
    
    mx_strdel(&temp);
    
    temp = mx_strdup(arr_str[1]); // повертаємо всі інші команди, що залишилися

    mx_free_void_arr((void **)arr_str, mx_count_arr_el(arr_str));

    return temp;
}

// функція для вставлення команди в чергу
void mx_insert_to_queue(char *arr, t_queue **arr_queue) {

    // підрахунок && і ||
    int count = mx_count_queue_operation(arr);
    int and = 0; // лічильник &&
    int or = 0; // лічильник ||

    char *temp = mx_strdup(arr);

    // цикл для заповнення черги команд
    for (int j = 0; j <= count; j++) {
            and = get_flag_index(temp, "&&"); // індекс першої появи &&
            or = get_flag_index(temp, "||");  // індекс першої появи ||
            // "arr = "(cd Desktop && cd ush) || cd uls""
            if ((and >= 0) && (and < or)) // якщо && зустрічається раніше, ніж ||
                temp = push_back_queue("&&", temp, arr_queue); // додати команду, що перед &&
            else if ((or >= 0) && (or < and )) // якщо || зустрічається раніше, ніж &&
                temp = push_back_queue("||", temp, arr_queue); // додати команду, що перед ||
            else if (and == INT_MAX && or == INT_MAX) { // якщо немає ні &&, ні ||
                if (temp == NULL) // якщо більше немає команд
                    temp = mx_strdup(arr); // то присвоюємо початкове значення (весь рядок)
                mx_push_back_queue(arr_queue, temp, '0'); //  
            }
    }
    
    mx_strdel(&temp);

}
