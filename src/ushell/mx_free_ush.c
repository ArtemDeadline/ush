#include "../../inc/ush.h"

void mx_free_ush(t_ush *ush) {
    if (ush != NULL) {
        while (ush->history->next != NULL)
            ush->history = ush->history->next;
        while (ush->history != NULL)
            ush->history = delete_elem(ush->history);
        mx_strdel(&ush->ush_path);
        mx_strdel(&ush->pwd_l);
        free_pids(ush->pids);
        free(ush);
    }
}
