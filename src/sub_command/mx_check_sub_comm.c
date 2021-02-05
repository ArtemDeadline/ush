#include "../../inc/ush.h"

void mx_check_sub_comm(char **data, t_ush *ush) {
    // echo "$(echo -n "Ave, Caesar"), $(echo -n "morituri te salutant\!")"
    // echo $(echo `echo $(echo HELLO DARNESS)`)
    // echo $(echo `echo $(echo "HELLO      DARNESS")`)
    // echo $(echo 1lvlv $(echo 2lvl $(echo 3lvl$(echo Hello my dear friend)3lvl) 2lvl) 1lvl)
    // створення обробника команди та його ініціалізація дефолтними значеннями
    t_com_sub *com_sub = mx_create_com_sub();
    int exit = 0;
    bool grave_start = false;
    bool dollar_start = false;
    int dollar_sub = 0;
    //printf("\n_________________________________________________________________________________________________\nStart check sub command in |%s|\n_________________________________________________________________________________________________\n", *data);
    //printf("\n\n\n\n\n\n\t--------- mx_check_sub_comm---------\t\n\n\n\n\n\n");
    // цикл для посимвольної обробки команди | пошук вкладених команд
    for (int i = 0; (*data)[i] != '\0'; i++) {
        
        //printf("CHECK (*data)[%d]: %c\n", i, (*data)[i]);
        //printf("\nCheck |%c|, dollar_start: %d, grave_start: %d, dollar_sub: %d\n", (*data)[i], dollar_start, grave_start, dollar_sub);
        //printf("Check result: |%c|, dollar_start: %d, grave_start: %d, dollar_sub: %d\nback_first: %d, back_end: %d, grave_first: %d, grave_end: %d\n", (*data)[i], dollar_start, grave_start, dollar_sub, com_sub->back_first_index, com_sub->back_end_index, com_sub->space_first_index, com_sub->space_end_index);
        if(!dollar_start && mx_check_grave_sub_comm(data, com_sub, ush, i, &grave_start, &dollar_sub) == 1) {
            exit = 1;
            break;
        }
        if(!grave_start && mx_check_dollar_sub_comm(data, com_sub, ush, i, &dollar_start, &dollar_sub) == 1) {
            exit = 1;
            
            //printf("\n\n\n\n\nnew data %s \n\n\n\n\n\n", *data);
            break;
        }
        //printf("\n");
        /*if(i > 100)
            break;*/
        //printf("Check result: |%c|, dollar_start: %d, grave_start: %d, dollar_sub: %d\nback_first: %d, back_end: %d, grave_first: %d, grave_end: %d\n", (*data)[i], dollar_start, grave_start, dollar_sub, com_sub->back_first_index, com_sub->back_end_index, com_sub->space_first_index, com_sub->space_end_index);
    }

    if (com_sub != NULL)
        free(com_sub);
    if (exit == 1)
        mx_check_sub_comm(data, ush);

}
