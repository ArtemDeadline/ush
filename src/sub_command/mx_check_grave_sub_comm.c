#include "../../inc/ush.h"

void static mx_find_sub_comm(t_com_sub *com_sub, char **data, int i,  bool * grave_start, int * dollar_sub) {

    //printf("|%c|\t{%d}\t[%d]\n", (*data)[i], com_sub->space, *dollar_sub);
    if ((*data)[i] == '$' && (*data)[i + 1] == '(' && (*data)[i-1] != '\\' && *grave_start) {
            (*dollar_sub)++;
            //printf("\n\ngrave: DOLLAR_SUB++\n\n");
            //printf("\nSTART DOLLAR SUB COMMAND: i: %i | dol: %d\n", i, *dollar_sub);
    }
    if ((*data)[i] == ')' && (*data)[i-1] != '\\' && *grave_start) {
            (*dollar_sub)--;
        //printf("\nEND DOLLAR SUB COMMAND: i: %i | dol: %d\n", i, *dollar_sub);
    }
    //printf("\nTeah2\n");
    if ((*data)[i] == '`' && (*data)[i-1] != '\\' && com_sub->space == 0 && *dollar_sub == 0) {
        //printf("\nYeah\n");
        *grave_start = true;
        com_sub->space++;
        com_sub->space_first_index = i;
        //printf("\nSTART ` sub comm: %d\n", i);
    } else if ((*data)[i] == '`' && (*data)[i-1] != '\\' && com_sub->space == 1 && *dollar_sub == 0) {
        //printf("\nYeahoo\n");
        *grave_start = false;
        com_sub->space++;
        com_sub->space_end_index = i;
        //printf("\nEND ` sub comm: %d\n", i);
    }
        //printf("\nTeah3\n");

}

static void insert_com_sub(t_com_sub *c, char **data, t_ush *ush) {
    //printf("Check grave_first: %d, grave_end: %d\n", c->space_first_index, c->space_end_index);

    if((*data)[c->space_first_index] == '`')
        c->temp_str = mx_strindup(*data, c->space_first_index + 1, c->space_end_index);
    else
        c->temp_str = mx_strdup(*data);
    //printf("\nTEMP_STR: %s\n", c->temp_str);
    c->status = mx_execute(ush, c->temp_str, 1, &c->cout_execute);
    //printf("\nTEMP_STR: %s\n", c->cout_execute);
    c->temp_join = mx_strjoin("`", c->temp_str);
    mx_strdel(&c->temp_str);
    c->temp_str = mx_strjoin(c->temp_join, "`");
}

static bool is_space_fail(t_com_sub *c, int i)  {
    if (c->space_first_index == i -1 && c->space_end_index == i) {
        c->space_first_index = 0;
        c->space_end_index = 0;
        return true;
    }
    return false;
}

// пошук вкладених команд, які написані всередині є `
int mx_check_grave_sub_comm(char **data, t_com_sub *c, t_ush *ush, int i, bool * grave_start, int *dollar_sub) {
    //printf("\nSAY 'NO' TO SEGMENTATION FAULT!\n");
    mx_find_sub_comm(c, data, i, grave_start, dollar_sub);
    
    /*mx_printstr("`true: ");
    mx_printchar((*data)[i]);
    mx_printchar('\n');*/
    // пошук вкладеної команди
    //printf("space: we have start at %d and end at %d\n", c->space_first_index, c->space_end_index);



    if (c->space_first_index < c->space_end_index && !(*grave_start)) {
        //printf("Зайшли в space if!\n");

        if(is_space_fail(c, i) == true)
            return 0;

        bool check_other_sub_comm = false;
                // перевірка на вкладені команди
                
                //printf("\nCHECK_OTHER_SUB_COMMAND: ");
                for(int p = c->space_first_index+1; p < c->space_end_index; p++){
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
                char *inside_comm = strndup(&(*data)[c->space_first_index+1],  strlen(&(*data)[c->space_first_index+1]) - 1);
                //printf( "\nINSIDE COMMAND: |%s|\n",  inside_comm);
                //printf("CHECKING: FIRST %c | BACK %c \n", (*data)[c->space_first_index+1], (*data)[c->space_end_index]);

                if(check_other_sub_comm){
                    //printf("\n\n\nDATA: %s\n", *data);
                    //printf("CHECKING: FIRST %c | BACK %c \n", (*data)[c->back_first_index+2], (*data)[c->back_end_index]);
                    char *inside_sub_comm = strndup( &( (*data)[c->space_first_index+1] ), strlen(&(*data)[c->space_first_index+1])-1);
                    //printf("INSIDE_SUB_COMM: %s\n\n\n", inside_sub_comm);
                    //char *inside_sub_comm = strndup(&(*data)[c->back_first_index],  strlen(&(*data)[c->back_first_index+2]));
                    //printf("\nfirst : %d, end: %d\n", c->back_first_index, c->back_end_index);
                    mx_check_sub_comm(&inside_comm, ush);
                    /*printf( "\nCHANGED COMMAND: |%s|\n",  inside_comm);
                    printf("|-| Replace in |%s| substr |%s| on |%s|\n", *data, inside_sub_comm, inside_comm);*/
                    //inside_sub_comm = mx_replace_substr(inside_sub_comm);
                    *data = mx_replace_substr(*data, inside_sub_comm, inside_comm);
                    //printf( "|-| replaced_original: %s\n",  *data);
                    //printf( "\n-----------CHANGED COMMAND: |%s|\n",  );
                    char* parsed_inside_comm = mx_strjoin(mx_strjoin("`",inside_comm), "`");
                    c->space_first_index = 0;
                    c->space_end_index = mx_strlen(parsed_inside_comm)-1;
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
                    insert_com_sub(c, data, ush);
                }
                
                
                    

                    /*printf( "\nCOUT_EXECUTE: %s\n",  c->cout_execute);
                    printf( "\nINSIDE COMMAND: %s\n",  c->temp_str);
                    printf( "\noriginal: %s\n",  *data);
                    printf("Replace in |%s| substr |%s| on |%s|\n", *data, c->temp_str, c->cout_execute);*/
                    mx_check_last_space(&c->cout_execute);
                    if(c->cout_execute == NULL)
                        *data = mx_replace_substr(*data, c->temp_str, "");
                    else
                        *data = mx_replace_substr(*data, c->temp_str, c->cout_execute);


                
                /*insert_com_sub(c, data, ush);
                if (c->status == 0 && strlen(c->cout_execute) > 0)
                    c->temp_data = mx_replace_substr(*data, c->temp_str, c->cout_execute);
                else if (strlen(c->cout_execute) > 0)
                    c->temp_data = mx_replace_substr(*data, c->temp_str, "");*/
                mx_free_sub_comm(c);
                //printf("\nTEMP_DATA %s", c->temp_data);
                //printf("REPLACING WAS FINISHED\n");
                if (c->temp_data != NULL) {
                    mx_strdel(data);
                    *data = c->temp_data;
                    return 1;
                }
                if(*data != NULL)
                    return 1;
                /*c->space_first_index = 0; 
                c->space_end_index = 0;*/
                //printf("\n\n\n\nCHECK SUB COMMAND: back_first: %d, back_end: %d, grave_first: %d, grave_end: %d\n\n\n\n\n", c->back_first_index, c->back_end_index, c->space_first_index, c->space_end_index);
    }
    return 0;
}
