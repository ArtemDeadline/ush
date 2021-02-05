#include "../../inc/ush.h"

// додання в кінець черги вузлу з команди й операції
void mx_push_back_queue(t_queue **queue, char *data, char operation) {
    // створення нового вузлу
    t_queue *back_list = mx_create_queue(data, operation);
    t_queue *temp = NULL;
    // якщо черга пуста, просто ставимо цю команду першою
    if (*queue == NULL)
        *queue = back_list;
    else {
        // інакше створюємо вказівник на початок черги
        temp = *queue;
        // щоб завдяки ньому дійти до кінця черги
        while (temp->next != NULL)
            temp = temp->next;
        // й додати в кінець черги цю команду
        temp->next = back_list;
    }
}

// розглянемо на прикладі
// наприклад, ввели рядок
// cd Desktop && cd ush || echo "OK"

/* отримаємо такі вузли:
    data: "cd Desktop" operation: "&"
    data: "cd ush"     operation: "|"
    data: "echo "OK""  operation: "0"
*/

