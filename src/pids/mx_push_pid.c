#include "../../inc/ush.h"

// переводимо на задній план процесів знову
void mx_push_pid(pid_t pid, t_ush **ush) {
    if ((*ush)->pids != NULL) {
        t_pid *temp = (t_pid *)malloc(sizeof(t_pid));
        temp->index = (*ush)->pids->index + 1;
        temp->num = pid;
        temp->prev=NULL;
        temp->str = mx_strdup((*ush)->str_input);
        temp->next = (*ush)->pids;
        (*ush)->pids = temp;
    }
    else
    {
        (*ush)->pids = (t_pid *) malloc(sizeof (t_pid));
        (*ush)->pids->num = pid;
        (*ush)->pids->index = 1;
        (*ush)->pids->str = mx_strdup((*ush)->str_input);
        (*ush)->pids->prev = NULL;
        (*ush)->pids->next = NULL;
    }
}
