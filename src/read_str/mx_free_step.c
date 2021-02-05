#include "../../inc/ush.h"

// очищення змінних стосовно поточного вхідного рядку
void mx_free_step(t_input *input, char *temp) {
    mx_strdel(&temp);
    if (input != NULL) {
        mx_strdel(&input->command);
        free(input);
    }
}
