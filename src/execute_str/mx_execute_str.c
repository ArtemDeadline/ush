#include "../../inc/ush.h"

static void case_or(t_queue **queue, int i) {
    mx_pop_front_queue(&queue[i]);
    while (queue[i] != NULL && queue[i]->operator == '|')
        mx_pop_front_queue(&queue[i]);
    if (queue[i] != NULL)
        mx_pop_front_queue(&queue[i]);
}

//видалення всіх команд, які вимагають успішного завершення попередньої
static void case_and_status_1(t_queue **queue, int i) {
    mx_pop_front_queue(&queue[i]);
    while (queue[i] != NULL && (queue[i]->operator == '&'
            || queue[i]->operator == '0')) {
        mx_pop_front_queue(&queue[i]);
    }
}

// перевірка на пустий рядок
static bool check_is_str(char *data) {
    char *temp = mx_strdup(data);
    bool status = false;

    if (mx_strlen(temp) != 0)
        status = true;
    mx_strdel(&temp);
    return status;
}

int mx_execute_str(t_queue **queue, t_ush *ush) {

    int status = 0;

    // проходимо по черзі й оробляємо кожну команду
    for (int i = 0; queue[i] != NULL; i++) {

        // допоки дана команда не стане пустою
        while (queue[i] != NULL) {

            
            // пошук і виконання вкладених команд
            mx_check_sub_comm(&queue[i]->data, ush);
            
            // перевірка на пустий рядок
            if (check_is_str(queue[i]->data) == true)
                status = mx_execute(ush, queue[i]->data, 0, NULL); // виконання команди з поверненням статусу завершення команди
            // якщо виконання команди зафейлилось - виходимо з програми
            if (ush->exit_status != -1) {
                mx_pop_front_queue(&queue[i]);
                return status;
            }
            // якщо виконання команди пройшло успішно й наступна команда вимагає цього, то просто скіпаємо поточну
            if (status == 0 && queue[i]->operator == '&') {
                mx_pop_front_queue(&queue[i]);
                continue;
            } // якщо просто не вдалося виконати, а наступна команда вимагає виконання, то скіпаємо наступні команди допоки умова переходу не зміниться
            else if (status == 1 && queue[i]->operator == '&') {
                case_and_status_1(queue, i);
                continue;
            } // якщо вдалося виконати, а наступна команда виконується в разі фейлу, то скіпаємо наступні команди з такою ж умовою
            else if (queue[i]->operator == '|' && status == 0) {
                case_or(queue, i);
                continue;
            }
            else // якщо неає ніяких умов, просто видаляємо команду з черги
                mx_pop_front_queue(&queue[i]);

        }

    }
    // повертаємо кінцевий статус виконання всіх команд
    return status;

}
