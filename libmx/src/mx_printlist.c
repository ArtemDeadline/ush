#include "../inc/libmx.h"

void mx_printlist(t_list *head) {
    while(head != NULL) {
        mx_printstr(head->data);
        head = head->next;
    }
}
