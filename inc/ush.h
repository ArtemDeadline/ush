#ifndef USH_H
#define USH_H

#include "../inc/libmx.h"
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <termcap.h>
#include <time.h>
#include <pwd.h>
#include <curses.h>
#include <term.h>

#define MX_HOME() (mx_getenv("HOME"))
#define MX_PATH() (mx_getenv("PATH"))
#define MX_SHLVL() (mx_getenv("SHLVL"))
#define MX_PWD() (mx_getenv("PWD"))
#define MX_OLDPWD() (mx_getenv("OLDPWD"))

#define MX_RIGHT_ARROW 67
#define MX_LEFT_ARROW 68
#define MX_UP_ARROW 65
#define MX_DOWN_ARROW 66
#define MX_ENTER 13
#define MX_BACKSPACE 127
#define MX_TAB 9

#define MX_ENV_US "env: option requires an argument -- %c\nusage: env [-i] \
[-P utilpath] [-u name]\n           \
[name=value ...] [utility [argument ...]]\n"
#define MX_ENV_IL "env: illegal option -- %c\nusage: env [-iv] [-P utilpath] \
[-u name]\n           [name=value ...] [utility [argument ...]]\n"
#define MX_PWD_ERR "ush: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n"
#define MX_WHICH_US "which: illegal option -- \
%c\nusage: which [-as] program ...\n"

// Структури
typedef struct s_input t_input;
typedef struct s_ush t_ush;
typedef struct s_env t_env;
typedef struct s_dbl_list t_dbl_list;
typedef struct s_com_sub t_com_sub;
typedef struct s_queue t_queue;
typedef struct s_pid t_pid;
typedef struct s_redirect t_redirect;


struct s_input {
    int ctrl_c;
    unsigned char input_ch;
    char *input_ch_arr;
    int len;
    int term_width;
    int coursor_position;
    char *command;
    struct termios savetty;
};

struct  s_env {
    int flag;
    char *comm;
    char *comm_args;
    char **env_var;
};

struct s_dbl_list {
    t_dbl_list *next;
    t_dbl_list *prev;
    char *data;
};

// основна структура 
struct s_ush {
    char *command;          // команда
    t_dbl_list *history;    // історія команд
    char *ush_path;         // значення змінної PATH
    int return_value;       // статус виконаної роботи
    int exit_status;        // змінна, яка відповідає за закінчення роботи з Терміналом
    t_pid *pids;            // список процесів
    char *str_input;        // вхідний рядок
    int exit_non_term;      // вихід без переривань
    pid_t parent_pid;       // айді нашого терміналу
    int curr_pid;           // айді поточного процесу 
    char *pwd_l;            // поточна директорія, яка була встановлена останньою
    char *pwd;              // поточна директорія
};

struct s_com_sub {
    int back_first;
    int back_first_index;
    int back_end;
    int back_end_index;
    int space;
    int space_first_index;
    int space_end_index;
    char *temp_str;
    char *temp_data;
    char *cout_execute;
    char *temp_join;
    int status;
};

struct s_queue {
    char *data;
    char operator;
    struct s_queue *next;
};

struct s_pid {
    int num; // айді процесу
    int index; // номер по порядку в списку процесів
    char *str; // назва процесу
    struct s_pid *next; // наступний процес в черзі
    struct s_pid *prev; // попередні процес в черзі
};
struct s_redirect {
    int fd_return[2];
    int fd_stdout[2];
    int fd_stderr[2];
    int flag;
    char *_stdout;
    char *_stderr;
};



// Ініціалізація
t_ush* mx_create_ush(char **argv);
void mx_set_shell_environ(void);
char *mx_getenv(char *var);

// Зчитування вхідного рядка
char *mx_read_str(t_ush *ush);
void mx_set_non_canonic(struct termios *savetty);
int mx_get_terminal_width(void);
int mx_get_input_char(t_input *input);

char *mx_add_ascii_char(t_input *input, t_ush *ush);
char *mx_fill_char_to_command(t_input *input);
void mx_clear_str();
void mx_delete_char(t_input *input, int index);
void mx_move_coursor(int num_of_moves, char *side);
void mx_insert_char(t_input *input, char sym, int index);

void mx_parse_non_ascii_char(t_input *input, t_ush *ush);

char *mx_add_char_to_cur_history(t_input *input, int *flag, t_ush *ush, char *temp);
void mx_sort_history(t_ush *ush, char *temp);
void mx_free_step(t_input *input, char *temp);
t_dbl_list *mx_add_command_to_history(t_dbl_list *history);

void mx_set_canonic(struct termios savetty);


// Обробка вхідного рядка
t_queue** mx_parse_str(t_ush *ush);
t_queue **mx_parse_command(char *command);
char *mx_parse_echo(char **args, int *flag_n, char *temp);
void mx_insert_to_queue(char *arr, t_queue **arr_queue);
int mx_count_queue_operation(const char *arr);
void mx_push_back_queue(t_queue **queue, char *data, char operation);
t_queue *mx_create_queue(char *data, char operation);
void mx_pop_front_queue(t_queue **head);

char **mx_strsplit_one(const char *s, char *c);
char *mx_replace_operator(char *s);
char ** mx_strsplit_echo(char *src, char delimiter);

// Виконання вхідного рядка
int mx_execute_str(t_queue **queue, t_ush *ush);
void mx_check_sub_comm(char **data, t_ush *ush);
int mx_check_grave_sub_comm(char **data, t_com_sub *c, t_ush *ush, int i, bool * grave_start, int *dollar_sub, bool * qoute, int * qoute_number, int **qoute_array);
void mx_free_sub_comm(t_com_sub *com_sub);
int mx_check_dollar_sub_comm(char **data, t_com_sub *c, t_ush *ush, int i, bool *dollar_start, int *dollar_sub, bool * qoute, int * qoute_number, int **qoute_array);
t_com_sub* mx_create_com_sub();

int mx_execute(t_ush *ush, char *str_input, int flag_redir, char **str_red);
char **mx_check_expansion(char **str_input, int ret_val);
void mx_tilde_check(char **input);
void mx_child_execute(int *ret, char **inp, t_redirect *red, t_ush *ush);

t_redirect *mx_create_redirect(int flag_redir);
void mx_parent_redirect(t_redirect *redirect, int *return_);
void mx_child_redirect(t_redirect *redirect);
void mx_free_execute(t_redirect *redirect, char **input);
void mx_write_to_pipe(char *str, int *fd);
void mx_read_from_pipe(char *str, int len, int *fd);

char *mx_command_in_path(char *comm, char *str_path);
int mx_file_exist(char *path);
int mx_is_builtin_command(char *command);
void mx_free_ush(t_ush *ush);


int mx_check_symlink(char **arg, int flag, int link);
void mx_env_error(t_env *env, char **args, int i);
int mx_execute_env_flags (t_env *env, char **args, int i, int *env_index);
t_env *mx_parse_env_args(char **args, t_ush *ush);
int mx_find_flag(char *flags, char *arg);
void mx_free_env(t_env *env);
int mx_make_path(char *path, t_ush *ush, int flag);
void mx_setenv_ush(char *arg, t_ush *ush);

char *mx_strincpy(char *dst, const char *src, int first, int end);
char *mx_strindup(const char *data, int first, int end);

// Команди
int mx_pwd(char **args, t_ush *ush);
int mx_cd(char **args, t_ush *ush);
int mx_env(char **args, t_ush *ush);
int mx_export(char **args);
int mx_unset(char **args);
int mx_exit(char **inp, int *exit_status);
int mx_echo(char **args, char *temp);
int mx_which(char **input);
int mx_fg(t_ush * ush);


// Робота з процесами
void mx_pop_front_pid(t_pid ** pids);
void mx_push_pid(pid_t pid, t_ush **ush);
void mx_swap_pids(t_ush *ush);


// util
char ** mx_split_by_space(char *s, char delimiter);
char *fill_parsed_str(char *str, int *flag_n, int flag);
int quot_error(char **parse_str, int *flag_n, int flag_quot);
void escape_chars(int i, char *str, char *parse_str, int index);
void free_pids(t_pid *pids);
t_dbl_list *delete_elem(t_dbl_list *lst);
void mx_check_last_space(char ** input);

#endif
