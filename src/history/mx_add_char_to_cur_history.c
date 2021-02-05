#include "../../inc/ush.h"

// заміняє те, що лежить в поточній команді історії на потону команду 
// й повертає те, що лежало до цього
char *mx_add_char_to_cur_history(t_input *input, int *flag, t_ush *ush, char *temp) {
    // якщо значення поточної команди в історії пусте
    if (ush->history->data != NULL) {
        // якщо наступна команда не існує й temp ще не ініціалізований
        if (ush->history->next != NULL && *flag == 0) {
            *flag = 1;
            mx_strdel(&temp); // очищаємо temp
            temp = mx_strdup(ush->history->data); // й ініціалізуємо його
        }
        mx_strdel(&ush->history->data); // очищаємо вміст поточної команди в історії 
    }
    ush->history->data = mx_strdup(input->command); // й ініціалізуємо поточною командою
    
    //printf("\nadd_history:data: %s\n",ush->history->data);
    //printf("\nadd_history:temp: %s\n",temp);

    return temp; // повертаємо те, що лежало в історії до цього
}

