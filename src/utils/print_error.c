#include "../../include/minishell.h"

void error_command_not_found(const char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found\n", 2);
    g_status = 127;
    exit(g_status);
}

/* 126: permission denied */
void error_permission_denied(const char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(" Permission denied\n", 2);
    g_status = 126;
    exit(g_status);
}

/* 127: no such file or directory */
void error_no_such_file(const char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(" No such file or directory\n", 2);
    g_status = 127;
    exit(g_status);
}
/* 126: is a directory */
void error_is_directory(const char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": is a directory\n", 2);
    exit(126);
}

/* 1: fork error */
void error_fork(void)
{
    perror("minishell: fork");
    g_status = 1;
    exit(g_status);
}

/* 1: general error (default) */
void error_general(const char *msg)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(msg, 2);
    g_status = 1;
    exit(g_status);
}

/* 1: redirection file open error */
void error_open_file(const char *filename)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(filename, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errno), 2);
    g_status = 1;
}
/* 1: error export */
void error_export(const char *cmd)
{
    printf("minishell: export: `%s': not a valid identifier\n", cmd);
    g_status = 1;
}
