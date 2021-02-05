#include "../../inc/ush.h"

// підрахунок кількості операцій && or ||
int mx_count_queue_operation(const char *arr) {
    
    int counter = 0; // лічильник

    if (arr) { // якщо масив не пустий
        // то поки не дійдемо до кінця 
        for (int i = 0; arr[i + 1] != '\0'; i++) {
            // перевіряємо на наявність &&
            if (arr[i] == '&' && arr[i + 1] == '&')
                counter++;
            // і на наявність ||
            if (arr[i] == '|' && arr[i + 1] == '|')
                counter++;
        }
    }
    return counter;
}
