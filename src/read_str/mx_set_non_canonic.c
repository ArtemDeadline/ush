#include "../../inc/ush.h"

/* 
       TCSANOW
              the change occurs immediately.

       TCSADRAIN
              the change occurs after all output written to fd has been
              transmitted.  This option should be used when changing
              parameters that affect output.

       TCSAFLUSH
              the change occurs after all output written to the object
              referred by fd has been transmitted, and all input that
              has been received but not read will be discarded before
              the change is made.
*/

void mx_set_canonic(struct termios savetty) { 
    tcsetattr (STDIN_FILENO, TCSANOW, &savetty); // ініціалізація структури termios 
}

// встановлення флагів для struct termios
void mx_set_non_canonic(struct termios *savetty) {
    struct termios tty;
    
    tcgetattr (0, &tty); // отримати поля структури
    *savetty = tty;

    /* -------------- позначення різних флагів (налаштувань) -------------- */
        // tcflag_t c_iflag;      /* input modes  налаштування зчитування */ 
        // tcflag_t c_oflag;      /* output modes налаштування виводу */
        // tcflag_t c_cflag;      /* control modes налаштування контролю */
        // tcflag_t c_lflag;      /* local modes локальні налаштування */
        // cc_t     c_cc[NCCS];   /* special characters  спеціальні символи */
    /*----------------------------------------------------------------------*/

    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                     | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_cflag &= ~(CSIZE | PARENB);
    tty.c_cflag |= CS8;
    tty.c_iflag &= IGNCR;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VERASE] = 127;
    tcsetattr (0, TCSAFLUSH, &tty);
}
