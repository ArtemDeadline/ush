#include "../../inc/ush.h"

// стрілка вправо
static void mx_right_arrow (t_input *input) {
    if (input->coursor_position < input->len) {
        mx_printstr("\033[C"); // \033[#С передвинути курсор вправо на # стовпчиків
        input->coursor_position++;
    }
}

// стрілка вліво
static void mx_left_arrow (t_input *input) {
    if (input->coursor_position > 0) {
        mx_printstr("\033[D"); // \033[#D передвинути курсор вліво на # стовпчиків
        input->coursor_position--;
    }
}

//стрілка вгору
static void mx_up_arrow (t_input *input, t_ush *ush) {
    //якщо існує попередня команда
    if (ush->history->prev != NULL && strlen(ush->history->prev->data) > 0) {
        ush->history = ush->history->prev; // то ми поточну команду ініціалізуємо пепередньою
        mx_strdel(&input->command); // очищаємо поточну команду
        mx_clear_str(); // очищаємо рядок
        mx_printstr("u$h> "); 
        if (ush->history->data != NULL) { // якщо попередня команда в історії не пуста
            input->command = mx_strdup(ush->history->data); // то переносимо її в поточну команду
            mx_printstr(input->command); // виводимо її в термінал
        }
        input->coursor_position = mx_strlen(input->command); // записуємо поточну позицію курсора
        input->len = mx_strlen(input->command); // записуємо довжину команди
    }
}

// стрілка вниз
static void mx_down_arrow (t_input *input, t_ush *ush) {
    if (ush->history->next != NULL) { // якщо це не остання команда в історії
        ush->history = ush->history->next; // ми переходимо до наступної
        mx_strdel(&input->command); // й видаляємо те, що зараз лежить в інпуті
        mx_clear_str(); // очищаємо рядок
        mx_printstr("u$h> "); 
        if (ush->history->data != NULL) { // якщо наступна команда в історії не пуста
            input->command = mx_strdup(ush->history->data); //  то переносимо наступну команду в поточну
            mx_printstr(input->command); // виводимоо її в термінал
        }
        input->coursor_position = mx_strlen(input->command); // записуємо поточну позицію курсора
        input->len = mx_strlen(input->command); // записуємо довжину команди
    }
}

// обробка стрілок
void mx_parse_non_ascii_char(t_input *input, t_ush *ush) {
    if (input->input_ch == 27) {
        if (input->input_ch_arr[2] == MX_RIGHT_ARROW)
            mx_right_arrow(input);
        else if (input->input_ch_arr[2] == MX_LEFT_ARROW)
            mx_left_arrow(input);
        else if (input->input_ch_arr[2] == MX_UP_ARROW )
            mx_up_arrow(input, ush);
        else if (input->input_ch_arr[2] == MX_DOWN_ARROW)
            mx_down_arrow(input, ush);
    }
}
