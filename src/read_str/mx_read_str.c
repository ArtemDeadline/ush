#include "../../inc/ush.h"

// функція створення пустої структури вхідного рядка
static t_input *init_input() {
    t_input *input = (t_input *) malloc(sizeof (t_input));

    input->len = 0;
    input->command = mx_strnew(1);
    input->ctrl_c = 0;
    input->coursor_position = 0;
    input->input_ch = '\0';
    input->input_ch_arr = (char *)&input->input_ch;
    return input;
}

// зчитування вхідного рядка з терміналу
static char * mx_parse_char(t_input *input, int *flag, t_ush *ush, char *str) {
    int k = 0;
    int i = mx_get_input_char(input); // зчитуємо символ з терміналу
    //printf("%d\n\n", input->input_ch);
    // цикл, щоб по-символьно зчитувати рядок 
    while (k < i) {
        input->input_ch = input->input_ch_arr[k];
        if (input->input_ch <= 127 && input->input_ch != 27) {
            str = mx_add_ascii_char(input, ush); // додаємо ASCII символ в рядок
            if (ush->exit_status != -1)
                break;
        }
        else {
            *flag = 0;
            mx_parse_non_ascii_char(input, ush); // // додаємо не ASCII символ в рядок
        }
        if (input->input_ch < 32) // всі інші символи призводять до завершення зчитування
            break;
        k++;
    }
    return str;
}

// функція для зчитування вхідного рядку з терміналу
static char *mx_read_terminal_line(struct termios savetty, t_ush *ush) {
    char *str = NULL;
    char *temp = NULL;
    int flag = 0;
    t_input *input = init_input();  // ініціалізація структури, 
                                    // що відповідає за вхідний рядок

    input->savetty = savetty;
    input->term_width = mx_get_terminal_width(); // установлення ширину терміналу
    
    // \r meant moving the print head back to the start of line
    // \r означає переміщення друкуючої головки на початок рядку
    // input->ctrl_c - змінна, яка відповідає за за сигнал CTRL+C
    while (input->input_ch != '\r' && input->ctrl_c != 1 && input->term_width != 0) {

        str = mx_parse_char(input, &flag, ush, str); // зчитування рядка
        if (ush->exit_status != -1) // перевірка на коректність роботи і сигнали
            break;
        if (input->len > 0)
            temp = mx_add_char_to_cur_history(input, &flag, ush, temp); // доповнення поточної команди в історію
    }

    if (ush->history->next != NULL) // якщо поточна команда не остання
        mx_sort_history(ush, temp); // відсортувати історію
    
    mx_free_step(input, temp);      // звільнити пам'ять, яка використовувалася
                                    // під час цього зчитування
    
    mx_printstr("\n");
    return str;
}

// функція зчитування з терміналу рядка
// та його запис в string
char *mx_read_str(t_ush *ush) {

    char *str = NULL; // змінна, в яку буде записуватися вхідний рядок
    struct termios savetty; // оголошення змінної, тип якої struct termios, 
                            // який використовують для роботи з терміналом
    size_t bufsize = 32; // розмір буферу
    char *buffer = NULL; // буфер

    if (!isatty(0)) { // перевіряє, чи вдалося відкрити термінал для зчитування
        getline(&buffer, &bufsize, stdin); // stdin - позначає, що треба відкрити потік для зчитування саме з ТЕРМІНАЛУ
        str = mx_strndup(buffer, mx_strlen(buffer) - 1); // виділення пам'яті для буферу
        ush->exit_non_term = 1; // змінна,  що позначає, що помилок не виникло й виходити з терміналу поки що не треба (TERMINATE = CTRL + C)
        mx_strdel(&buffer); // видалення буферу
    }
    else {
        mx_printstr("u$h> ");
        mx_set_non_canonic(&savetty); // установалюємо флаги, які можуть бути
        str = mx_read_terminal_line(savetty, ush); // зчитуємо рядок з терміналу
        mx_set_canonic(savetty); // установлюємо значення для struct termios
    }
    if (ush->history->data != NULL)
        ush->history = mx_add_command_to_history(ush->history); // додання поточної команди в історію
    return str;
}
