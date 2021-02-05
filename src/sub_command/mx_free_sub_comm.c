#include "../../inc/ush.h"

// очищення пам'яті для вкладених команд
void mx_free_sub_comm(t_com_sub *com_sub) {
    if (com_sub != NULL) {
        mx_strdel(&com_sub->temp_join);
        mx_strdel(&com_sub->temp_str);
        mx_strdel(&com_sub->cout_execute);
    }
}
