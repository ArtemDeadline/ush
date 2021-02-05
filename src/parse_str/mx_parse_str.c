#include "../../inc/ush.h"

t_queue** mx_parse_str(t_ush *ush) {

    // черга даних і операторів
    t_queue **queue = NULL;


    // якщо ми зчитали не пусту команду
    if (ush->command != NULL && strlen(ush->command) > 0) {
        queue = mx_parse_command(ush->command); // то записуємо команди в queue
                                                // в тому порядку, в якому вони мають 
                                                // виконуватися
        //ush->return_value = mx_push_execute_queue(queue, ush); // тепер виконуємо ці команди
        //free(queue);
    }
    //printf("\n6: str: |%s|\n", ush->command);
    //mx_strdel(&ush->command);
    return queue;
}
