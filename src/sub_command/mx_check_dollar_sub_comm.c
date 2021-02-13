#include "../../inc/ush.h"

// пошук початку й кінця змінних потипу $(...)
void static mx_find_sub_comm(t_com_sub *com_sub, char **data, int i, bool * dollar_start, int * dollar_sub) {
    if ((*data)[i] == '$' && (*data)[i + 1] == '(' && (*data)[i-1] != '\\') {
        
        
        if (!(*dollar_start)) {
            com_sub->back_first++;
            com_sub->back_first_index = i;
            *dollar_start = true;
            //printf("\nBACK_FIRST: %d\n", i);
        }
        else
        {
            //printf("\n\ndollar: DOLLAR_SUB++\n\n");
            (*dollar_sub)++;
        }
        
        //printf("\nSTART DOLLAR SUB COMMAND: i: %i | dol: %d\n", i, *dollar_sub);
    }
    if (*dollar_start && (*data)[i] == ')' && (*data)[i-1] != '\\') {
        //printf("\n0:END DOLLAR SUB COMMAND: i: %i | dol: %d\n", i, *dollar_sub);
        if(*dollar_sub == 0) {
            com_sub->back_end++;
            com_sub->back_end_index = i;
            *dollar_start = false;
        }
        else{
            (*dollar_sub)--;
        }
        //printf("\n1:END DOLLAR SUB COMMAND: i: %i | dol: %d\n", i, *dollar_sub);
    }
}

static void insert_com_sub(t_com_sub *c, char **data, t_ush *ush) {
    // temp_str ініціалізується тим, що знаходиться всередині ()
    //printf("\nINSERT:DATA: %s\n", *data);
    //printf("\nFIRST BACK: %d. END BACK: %d.\n", c->back_first_index, c->back_end_index);
    if((*data)[c->back_first_index] == '$'){
        c->temp_str = mx_strindup(*data,c->back_first_index + 2, c->back_end_index);
    }
    else
        c->temp_str = mx_strdup(*data);
    //printf("\nsubstitution command: |%s|\n",c->temp_str);
    // виконуємо команду, яка була всередині дужок.
    c->status = mx_execute(ush, c->temp_str, 1, &c->cout_execute);
    //printf("\nc->cout_execute: %s\n", c->cout_execute);
    c->temp_join = mx_strjoin("$(", c->temp_str);
    mx_strdel(&c->temp_str);
    c->temp_str = mx_strjoin(c->temp_join, ")");
}

//
int mx_check_dollar_sub_comm(char **data, t_com_sub *c, t_ush *ush, int i, bool *dollar_start, int *dollar_sub) {

    // пошук початку й кінця субрядку $(...)
    mx_find_sub_comm(c, data, i, dollar_start, dollar_sub);
    //printf("back %d: we have start at %d and end at %d\n", *dollar_start, c->back_first_index, c->back_end_index);
    // якщо індекс першої появи $ менше індексу останньої появи )  



    if (c->back_first_index < c->back_end_index && !(*dollar_start)) {

        bool check_other_sub_comm = false;
        // перевірка на вкладені команди
        
        //printf("\nCHECK_OTHER_SUB_COMMAND: ");
        for(int p = c->back_first_index+2; p < c->back_end_index; p++){
            //printf("|%c|", (*data)[p]);
            if((*data)[p] == '$' && (*data)[p-1] != '\\' && (*data)[p+1] == '(')
                check_other_sub_comm = true;
            if((*data)[p] == '`' && (*data)[p-1] != '\\')
                check_other_sub_comm = true;
            if(check_other_sub_comm)
                break;
        }
        //mx_printchar('\n');

        //char *inside_comm = strndup( &( (*data)[c->back_first_index+2] ), c->back_end_index - c->back_first_index - 1);
        char *inside_comm = strndup(&(*data)[c->back_first_index+2],  strlen(&(*data)[c->back_first_index+2]) - 1);
        //printf( "\nINSIDE COMMAND: |%s|\n",  inside_comm);
        //printf("CHECKING: FIRST %c | BACK %c \n", (*data)[c->back_first_index+2], (*data)[c->back_end_index]);

        if(check_other_sub_comm){
            //printf("\n\n\nDATA: %s\n\n\n", *data);
            //printf("CHECKING: FIRST %c | BACK %c \n", (*data)[c->back_first_index+2], (*data)[c->back_end_index]);
            char *inside_sub_comm = strndup( &( (*data)[c->back_first_index+2] ), strlen(&(*data)[c->back_first_index+2])-1);
            //printf("INSIDE_SUB_COMM: %s\n\n\n", inside_sub_comm);
            //char *inside_sub_comm = strndup(&(*data)[c->back_first_index],  strlen(&(*data)[c->back_first_index+2]));
            //printf("\nfirst : %d, end: %d\n", c->back_first_index, c->back_end_index);
            mx_check_sub_comm(&inside_comm, ush);
            //printf( "\nCHANGED COMMAND: |%s|\n",  inside_comm);
            //printf("|-| Replace in |%s| substr |%s| on |%s|\n", *data, inside_sub_comm, inside_comm);
            //inside_sub_comm = mx_replace_substr(inside_sub_comm);
            *data = mx_replace_substr(*data, inside_sub_comm, inside_comm);
            //printf( "|-| replaced_original: %s\n",  *data);
            //printf( "\n-----------CHANGED COMMAND: |%s|\n",  );
            char* parsed_inside_comm = mx_strjoin(mx_strjoin("$(",inside_comm), ")");
            c->back_first_index = 0;
            c->back_end_index = mx_strlen(parsed_inside_comm)-1;
            //mx_check_last_space(&parsed_inside_comm);
            insert_com_sub(c, &parsed_inside_comm, ush);
            //printf( "\n-----------CHANGED COMMAND: |%s|\n",  inside_comm);
            /*printf("Replace in |%s| substr |%s| on |%s|\n", *data, c->temp_str, c->cout_execute);
            if(c->cout_execute == NULL)
                *data = mx_replace_substr(*data, c->temp_str, "");
            else
                *data = mx_replace_substr(*data, c->temp_str, c->cout_execute);
            printf( "\nreplaced_original: %s\n",  *data);*/

            //mx_strdel(&inside_comm);
            //mx_strdel(&inside_sub_comm);
        }
        else
        {
            /*char* parsed_inside_comm = mx_strjoin(mx_strjoin("$(",*data), ")");
            c->back_first_index = 0;
            c->back_end_index = mx_strlen(parsed_inside_comm)-1;*/
            //printf("\nELSE\n");
            //mx_check_last_space(data);
            insert_com_sub(c, data, ush);
        }
        
        
            

            //printf( "\nCOUT_EXECUTE: %s\n",  c->cout_execute);
            //printf( "\nINSIDE COMMAND: %s\n",  c->temp_str);
            //printf( "\noriginal: %s\n",  *data);
            //printf("Replace in |%s| substr |%s| on |%s|\n", *data, c->temp_str, c->cout_execute);
            mx_check_last_space(&c->cout_execute);
            if(c->cout_execute == NULL)
                *data = mx_replace_substr(*data, c->temp_str, "");
            else
                *data = mx_replace_substr(*data, c->temp_str, c->cout_execute);
            //printf( "\nreplaced_original: %s\n",  *data);
        
        //printf("Зайшли в back if!\n");
        // отримання виводу команди, що була в дужках
        
        //printf("\nc->status: %d\n", c->status);
        // якщо все пройшло добре, то ми замінюємо $(...) на вивід в терміналі
        /*if (c->status == 0 && strlen(c->cout_execute) > 0){
            c->temp_data = mx_replace_substr(*data, c->temp_str, c->cout_execute);
            //printf("\ndata: %s \ttemp_str(sub): %s\tcout_execute(replace): %s\n", *data, c->temp_str, c->cout_execute);
        }
        else if (strlen(c->cout_execute) > 0){ // інакше замінюємо пустим рядком
            c->temp_data = mx_replace_substr(*data, c->temp_str, "");
            //printf("\ndata: %s \ttemp_str(sub): %s\n", *data, c->temp_str);
        }*/
        //printf("\ntemp_data: %s\n", c->temp_data);
        // очищюємо пам'ять
        mx_free_sub_comm(c);
        if (c->temp_data != NULL) { 
            mx_strdel(data);
            *data = c->temp_data;
        }
        if(*data != NULL)
            return 1;
    }
    /*c->back_first_index = 0; 
    c->back_end_index = 0;*/
    return 0;
}
