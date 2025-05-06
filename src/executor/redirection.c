#include "../../include/minishell.h"

int set_redirection(t_cmd *cmd)
{
    if (cmd->infile)
    {
        int fd_in = open(cmd->infile, O_RDONLY);
        if (fd_in < 0)
        {
            printf("error in oppening file\n");
            return (-1);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if (cmd->outfile)
    {
        int flags;
        if (cmd->append)
            flags = O_CREAT | O_WRONLY | O_APPEND;
        else 
            flags = O_CREAT | O_WRONLY | O_TRUNC;
        int fd_out = open(cmd->outfile, flags, 0644);
        if (fd_out < 0)
        {
            printf("error in oppening file\n");
            return (-1);   
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
    return (0);        
}

void restore_fd(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}
