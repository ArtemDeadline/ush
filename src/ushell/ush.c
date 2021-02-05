#include "../../inc/ush.h"

// функція, яка передається в якості другого параметру
// для сигналу SIGINT, який перебиває програму
// і в цей момент створюється новий рядок
static void sigint(){
    mx_printstr("\n");
}

// echo dir
// TAB
int main(int argc, char **argv){
    
    // створення структури
    t_ush *ush = NULL;

    if (argc > 1) { //якщо кількість аргументів більше одного (окрім "./ush" ще є аргументи)
        fprintf(stderr, "ush: can't open input file: %s\n", argv[1]); // видаємо повідомлення про помилку
        exit(127);
    }

    ush = mx_create_ush(argv); // створюємо й ініціалізуємо структуру ush

    mx_set_shell_environ(); // ініціалізуємо деякі змінні оточення

    while (true) { // запускаємо цикл, в якому будемо обробляти вхідні рядки

        // 2  SIGINT  terminate process    interrupt program
        signal(SIGINT, sigint);

        // 18 SIGTSTP stop process stop signal generated from keyboard
        signal(SIGTSTP, SIG_IGN);

        
        ush->command = mx_read_str(ush); // зчитування поточного рядка


        t_queue **queue = mx_parse_str(ush); // записуємо команди з рядку в порядку виконання
        
        if(queue != NULL){
            ush->return_value = mx_execute_str(queue, ush); // виконуємо команди
            free(queue);
        }
        mx_strdel(&ush->command);

        if (ush->exit_status != -1 || ush->exit_non_term == 1){
            //mx_printchar('\n');
            break;
        }

    }

    mx_free_ush(ush);
    if (ush->exit_status != -1){
        exit(ush->exit_status);
    }
    return ush->return_value;
}
