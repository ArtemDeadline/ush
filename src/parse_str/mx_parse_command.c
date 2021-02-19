#include "../../inc/ush.h"

t_queue **mx_parse_command(char *command) {

    char **arr = mx_strsplit(command, ';'); // ділимо команди по ; 
    int size = mx_count_arr_el(arr); // кількість команд
    // виділення пам'яті під чергу 
    t_queue **arr_queue = (t_queue **)malloc(sizeof(t_queue *) * (size + 1));

    /*printf("SPLIT BY ;\n");
    for (int i = 0; i < mx_count_arr_el(arr); i++){
        printf("%s\n", arr[i]);
    }*/

    // цикл для заповнення черги
    for (int i = 0; i < size; i++) {
        arr_queue[i] = NULL;
        //mx_check_last_space(&arr[i]);
        mx_insert_to_queue(arr[i], &arr_queue[i]);
    }
    mx_free_void_arr((void **)arr, size);
   
    arr_queue[size] = NULL;
   
    return arr_queue;
}

// якщо ввели, наприклад, такий рядок
// pwd ; ls -a ; cd Desktop && cd ush || echo "OK
// то
/* отримаємо чергу:
    data: "cd "pwd"     operation: "0"
    data: "ls -a"       operation: "0"
    data: "cd Desktop"  operation: "&"
    data: "cd ush"      operation: "|"
    data: "echo "OK""   operation: "0"
*/

