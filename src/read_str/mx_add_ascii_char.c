#include "../../inc/ush.h"

// обробка виходу з терміналу
static void events (t_input *input, int *exit_status) {
    if (input->input_ch == 4) { // CTRL+Z
        mx_set_canonic(input->savetty);
        *exit_status = 1;
    }
    else if (input->input_ch == 3) // CTRL+C
        input->ctrl_c = 1;
}

// додання в рядок символу ASCII
char *mx_add_ascii_char(t_input *input, t_ush *ush) {
    char *str = NULL;

    // \r meant moving the print head back to the start of line
    // \r означає переміщення друкуючої головки на початок рядку
    // \t переміщує позицію друку до наступної позиції горизонтальної табуляції.
    // те саме що й tab
    if (input->input_ch != '\r'  && input->input_ch != '\t'
        && input->input_ch < 32) {
        events(input, &ush->exit_status); // обробка виходу з терміналу
    }
    else {
        str = mx_fill_char_to_command(input); // заповнення поля command структури input
    }
    return str;
}
