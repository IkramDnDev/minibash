#include "../../include/minishell.h"

void exec_external(t_cmd *cmd, t_minishell *data)
{
    pid_t pid;
    char *path;
    int status;
    char **envp = env_to_tab(data->envp);
    pid = fork();
    if (pid < 0)
        error_fork();
    if (pid == 0)
    {
        if (set_redirection(cmd) == -1)
        {
            g_status = 1;
            return ;
        }
        path = find_command_path(cmd->argv[0], envp);
        if (!path)
            error_command_not_found(cmd->argv[0]);
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd->argv[0], 2);
            ft_putstr_fd(": is a directory\n", 2);
            exit(126);
        }
        execve(path, cmd->argv, envp);
        perror("execve");
        exit(126);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_status = 128 + WTERMSIG(status);
    }
    ft_free_split(envp);
}
