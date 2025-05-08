#include "../../include/minishell.h"

int set_redirection(t_cmd *cmd)
{
    t_token_node *red = cmd->red;
    int fd;

    while (red)
    {
        if (red->type == REDIRECT_IN)
        {
            fd = open(red->value, O_RDONLY);
            if (fd < 0)
                return (perror(red->value), -1);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (red->type == REDIRECT_OUT)
        {
            fd = open(red->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd < 0)
                return (perror(red->value), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (red->type == REDIRECT_APPEND)
        {
            fd = open(red->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd < 0)
                return (perror(red->value), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        red = red->next;
    }    return (0);
}

void restore_fd(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}
