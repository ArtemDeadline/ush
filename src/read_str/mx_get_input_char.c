#include "../../inc/ush.h"

// повертає розмір вхідного рядка в байтах
int mx_get_input_char(t_input *input) {

    int size = 0;

    size = read(0, &input->input_ch, 4);

    return size;
    
}
