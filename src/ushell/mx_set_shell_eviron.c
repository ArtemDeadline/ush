#include "../../inc/ush.h"

void mx_set_shell_environ(void) {
    char *shlv = MX_SHLVL();
    char *shlvl = mx_itoa(mx_atoi(shlv) + 1);
    extern char **environ;
    char cwd[PATH_MAX];

    if (getenv("HOME") == NULL)
        setenv("HOME", MX_HOME(), 1);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        setenv("PWD", cwd, 1);
    if (getenv("OLDPWD") == NULL)
        setenv("OLDPWD", MX_PWD(), 1);
    if (getenv("PATH") == NULL)
        setenv("PATH", MX_PATH(), 1);
    if (getenv("SHLVL") == NULL)
        setenv("SHLVL", "1", 1);
    else
        setenv("SHLVL", shlvl, 1);
    setenv("_", "/usr/bin/env", 1);
    mx_strdel(&shlvl);
    mx_strdel(&shlv);
}
