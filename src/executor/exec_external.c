#include "../../include/minishell.h"

static void wait_for_child(pid_t pid)
{
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        g_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_status = 128 + WTERMSIG(status);
}

void exec_external(t_cmd *cmd, t_minishell *data)
{
    pid_t pid;
    char *path;
    char **envp = env_to_tab(data->envp);
    pid = fork();
    if (pid < 0)
        error_fork();
    if (pid == 0)
    {
        if (set_redirection(cmd) == -1)
            return ;
        path = find_command_path(cmd->argv[0], envp);
        if (!path)
            error_command_not_found(cmd->argv[0]);
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
            error_is_directory(cmd->argv[0]);
        execve(path, cmd->argv, envp);
        perror("execve");
        exit(126);
    }
    else
        wait_for_child(pid);
    ft_free_split(envp);
}
