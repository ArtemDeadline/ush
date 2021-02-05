#include "../../inc/ush.h"

void free_pids(t_pid *pids) {
    t_pid *temp = NULL;

    if (pids != NULL) {
        while (pids->prev != NULL) {
            temp = pids;
            pids = pids->prev;
            mx_strdel(&temp->str);
            free(temp);
        }
        mx_strdel(&pids->str);
        free(pids);
    }
}
