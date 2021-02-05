#include "../../inc/ush.h"

void mx_swap_pids(t_ush *ush) {
    char **input = mx_strsplit(ush->str_input, ' ');
    t_pid *temp = NULL;

    //printf("\n1:parent_id: %d\tcur_id before changing: %d\tfuture_id: %d\n", ush->parent_pid, ush->curr_pid, ush->pids->num);
    if (mx_strcmp(input[0], "fg") == 0 && ush->pids != NULL) {
        mx_strdel(&ush->str_input);
        ush->curr_pid = ush->pids->num;
        ush->str_input = mx_strdup(ush->pids->str);
        temp = ush->pids;
        ush->pids = ush->pids->prev;
        mx_strdel(&temp->str);
        free(temp);
    }
    //printf("\n2: parent_id: %d\tcur_id after changing: %d\n", ush->parent_pid, ush->curr_pid);

    mx_free_void_arr((void **) input, mx_count_arr_el(input));
}
