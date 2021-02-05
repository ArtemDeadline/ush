#include "../../inc/ush.h"


// очищення структури з даними про всі процеси
void mx_free_execute(t_redirect *redirect, char **input) {
    if (redirect != NULL) {
        mx_strdel(&redirect->_stderr);
        mx_strdel(&redirect->_stdout);
        free(redirect);
    }
    mx_free_void_arr((void **) input, mx_count_arr_el(input));
}

// створення й ініціалізація структури redirect
t_redirect *mx_create_redirect(int flag_redir) {
    // виділення пам'яті під структуру
    t_redirect *redirect = (t_redirect *)malloc(sizeof(t_redirect));
    redirect->_stderr = mx_strnew(1000); // виділення пам'яті під буфер помилок
    redirect->_stdout = mx_strnew(1000); // виділення пам'яті під буфер виводу з термінала
    redirect->flag = flag_redir; // ініціалізація флагу, чи потрібен редірект
    pipe(redirect->fd_return); // значення-результат закінчення роботи функції pipe (0 - добре, -1 - погано)
    pipe(redirect->fd_stdout); // збереження виводу терміналу 
    pipe(redirect->fd_stderr); // збереження виводу помилок в термінал
    return redirect;
}
/*
    Функція ріре() створює канал (об'єкт, що дозволяє непрямий потік даних) і виділяє пару
    файлових дескрипторів. Перший дескриптор під'єднується для зчитування кінця каналу; другий,
    щоб записати кінець каналу.

    Дані , записані до fieldes[1] з'являються в fieldes[0], тобто звідти їх можна прочитати.
    Це дозволяє передавати вивід одних програм іншим: ... . 

    Що власне нам і треба: наприклад, нам треба передати те, що виведе команда, яка знаходиться
    в $() і передати це як аргументи команді, всередині якої вона викликається.  

    The pipe() function creates a pipe (an object that allows unidirectional
     data flow) and allocates a pair of file descriptors.  The first descrip-tor descriptor
     tor connects to the read end of the pipe; the second connects to the
     write end.

     Data written to fildes[1] appears on (i.e., can be read from) fildes[0].
     This allows the output of one program to be sent to another program: the
     source's standard output is set up to be the write end of the pipe; the
     sink's standard input is set up to be the read end of the pipe.  The pipe
     itself persists until all of its associated descriptors are closed.
*/

// 18    SIGTSTP      stop process         stop signal generated from keyboard

