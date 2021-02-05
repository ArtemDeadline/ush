#include "../../inc/ush.h"

int mx_fg(t_ush * ush){
  int w_st;
  
  //printf("\nCHECK 1\n");
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  //printf("\n1: fg: check null\n");
    if(ush->pids == NULL){
        printf("fg: no current job\n");
        return 1;
    }
    else
        ush->curr_pid = ush->pids->num;
  //printf("\n1: fg: check null\n");

  //printf("\nwait: fg: parent_id: %d, curr_id: %d\n",ush->parent_pid, ush->curr_pid);
  tcsetpgrp(1, ush->curr_pid);
  kill(ush->curr_pid,SIGCONT);
  //printf("\nwait: fg: parent_id: %d, curr_id: %d\n",ush->parent_pid, tcgetpgrp(1));
  waitpid(ush->curr_pid, &w_st, WUNTRACED);
    if(w_st == 0){
            mx_pop_front_pid(&(ush->pids));
            //printf("\nkill %d: status: %d\n", ush->curr_pid, w_st);
            kill(ush->curr_pid,SIGKILL);
    }
    else{

        //printf("\nCHECK 2\n");
        //printf("\nstatus: %d\n", w_st);

        if(w_st == 18) {
            mx_pop_front_pid(&(ush->pids));
            //mx_printstr("TESTSTASRASDEASDASD\n\n\n\n\n\n\n\n");
        }
    
    }
    //printf("\n%d\n", w_st);
    //printf("\nQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
    //printf("\n0: fg: parent_id: %d, lider_id: %d\n",ush->parent_pid, tcgetpgrp(1));
    //print_all_pids(ush->pids);
    tcsetpgrp(1, ush->parent_pid);
    //printf("\n1: fg: parent_id: %d, lider_id: %d\n",ush->parent_pid, tcgetpgrp(1));
    //printf("\n1: fg: parent_id: %d, par_curr_id: %d\n", ush->parent_pid, ush->curr_pid);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    return 1;
}
