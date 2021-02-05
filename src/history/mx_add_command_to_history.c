#include "../../inc/ush.h"

// вставка команди всередину списку
t_dbl_list *mx_add_command_to_history(t_dbl_list *history) {
    t_dbl_list *temp, *p;

    temp = (t_dbl_list *) malloc(sizeof (t_dbl_list));
    //printf("\nНа що вказує history: %s\n", history->data);
    p = history->next; // зберігання вказівника на наступний вузол
    history->next = temp; // попередній вузол вказує на поточний
    temp->next = p; // створений вузол вказує на наступний
    temp->prev = history; // створений вузол вказує на попередній
    temp->data = NULL;
    if (p != NULL)
        p->prev = temp;
    return temp;
}
