#include "../inc/libmx.h"
void mx_print_charerr(char error) {
    write(2, &error, 1);
}
