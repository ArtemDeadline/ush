#include "../inc/libmx.h"
void mx_printerr(char *error) {
    write(2, error, mx_strlen(error));
}
