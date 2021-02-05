#include "../../inc/ush.h"

t_dbl_list *delete_elem(t_dbl_list *lst) {
    t_dbl_list *prev = lst->prev; // узел, предшествующий lst
    t_dbl_list *next = lst->next; // узел, следующий за lst
    if (prev != NULL)
        prev->next = lst->next; // переставляем указатель
    if (next != NULL)
        next->prev = lst->prev; // переставляем указатель
    mx_strdel(&lst->data);
    free(lst); // освобождаем память удаляемого элемента
    return(prev);
}
