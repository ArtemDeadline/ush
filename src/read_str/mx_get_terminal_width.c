#include "../../inc/ush.h"

// функція перевірки доступу до termcap бази та повернення ширини терміналу"со" 
int mx_get_terminal_width(void) {
    if (tgetent(NULL, "xterm-256color") < 0) {
        fprintf(stderr, "ush: Could not access the termcap data base.\n");
        exit(1);
    }
    return tgetnum("co");
}
