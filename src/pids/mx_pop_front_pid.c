#include "../../inc/ush.h"

void mx_pop_front_pid(t_pid ** pids){

    //printf("\npop the front process %d \n", (*pids)->num);

    t_pid * temp = (*pids)->next;
    mx_strdel(&((*pids)->str));
    free(*pids);
    *pids = temp;

}
