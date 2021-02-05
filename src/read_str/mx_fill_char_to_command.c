#include "../../inc/ush.h"

static void mx_case_backspace(t_input *input) {
    input->coursor_position--;
    input->len--;
    mx_clear_str();
    if (input->term_width > input->len + 8) // обробка зайвої довжини
        mx_printstr("u$h> ");
    mx_delete_char(input, input->coursor_position); // заповнення команди в структурі
    if (input->term_width > input->len + 8) { 
        mx_printstr(input->command);
        if (input->coursor_position != input->len)
            mx_move_coursor(input->len - input->coursor_position, "D"); // переміщення крусору
    }
}

// функцiя вставлення символу в рядок
static void mx_fill_char(t_input *input){
    if (input->coursor_position != input->len) // якщо це це ще не кінець рядку
        mx_insert_char(input, input->input_ch, input->coursor_position); // додання символу
    else if (input->command != NULL) { // додаємо символ в кінець
        input->command = realloc(input->command, input->len + 2);
        input->command[input->len] = (char) input->input_ch;
        input->command[input->len + 1] = '\0';
    }
    else { // виділення пам'яті
        input->command = mx_strnew(1000); 
        input->command[input->len] = (char) input->input_ch;
    }
    input->len++;
    input->coursor_position++;
    if (input->coursor_position != input->len) {
        mx_clear_str();
        mx_printstr("u$h> ");
        mx_printstr(input->command);
        mx_move_coursor(input->len - input->coursor_position, "D");
    }
    else
        mx_printchar((char) input->input_ch);
}


static void mx_case_default(t_input *input) {
    if (input->len + 8 > input->term_width) {  // обробка довжини
        mx_printerr("\nush: input string is too long");
        input->term_width = 0;
    }
    else {  // якщо все коректно, то нарешті додання символу
        mx_fill_char(input);
    }
}

// зчитування символу й додання його в str
char *mx_fill_char_to_command(t_input *input) {
    char *str = NULL;
    switch (input->input_ch) {
        case MX_BACKSPACE: // обробка пробілу 
            if (input->coursor_position > 0)
                mx_case_backspace(input);
            break;
        case MX_ENTER: // обробка закінчення зчитування
            str = mx_strtrim(input->command);
            break;
        case MX_TAB: // обробка TAB
            break;
        default: // додання символу
            mx_case_default(input);
            break;
    }

    return  str;
}

