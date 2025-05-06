#include "../../include/minishell.h"

static void close_unused_fds(int prev_fd, int pipefd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

static void wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_status = 128 + WTERMSIG(status);
	}
}

static void handle_child(t_cmd *cmd, int prev_fd, int pipefd[2], t_minishell *data, char **envp)
{
    char *path;
    if (!cmd->isfirst)
        dup2(prev_fd, STDIN_FILENO);
    if (!cmd->islast)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
    }
    close_unused_fds(prev_fd, pipefd);
    if (set_redirection(cmd) == -1)
        exit(1);
    if (is_builtin(cmd->argv[0]))
    {
        exec_builtin(cmd, data);
        exit(g_status);
    }
    path = find_command_path(cmd->argv[0], envp);
    if (!path)
        error_command_not_found(cmd->argv[0]);
    execve(path, cmd->argv, envp);
    perror("execve");
    exit(127);
}

void execute_pipeline(t_cmd *cmd, t_minishell *data)
{
    int pipefd[2];
    int prev_fd;
    pid_t pid;
    char **envp;

    envp = env_to_tab(data->envp);
    prev_fd = -1;
    while (cmd)
    {
        if (!cmd->islast && pipe(pipefd) == -1)
            return(perror("pipe")), exit(1);
        pid = fork();
        if (pid == 0)
            handle_child(cmd, prev_fd, pipefd, data, envp);
        else if (pid < 0)
            error_fork();
        if (!cmd->isfirst)
            close(prev_fd);
        if (!cmd->islast)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        else
            prev_fd = -1;
        cmd = cmd->next;
    }
    wait_for_children();
    ft_free_split(envp);
}


