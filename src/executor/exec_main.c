#include "../../include/minishell.h"

static void error_redirection(t_cmd *cmd, int stdin_backup, int stdout_backup)
{
    if (set_redirection(cmd) == -1)
    {
        restore_fd(stdin_backup, stdout_backup);
        return;
    }
}

void execute_cmds(t_minishell *data)
{
    t_cmd *cmd;
    if (!data || !(cmd = data->cmd_list))
        return ;
    if (!cmd->next)
    {
        if (is_builtin(cmd->argv[0]) && ft_strcmp(cmd->argv[0], "exit") == 0)
        {
            exec_exit(&cmd->argv[0]);
            return;
        }
        if (is_builtin(cmd->argv[0]))
        {
            int stdin_backup = dup(STDIN_FILENO);
            int stdout_backup = dup(STDOUT_FILENO);
            error_redirection(cmd, stdin_backup, stdout_backup);
            exec_builtin(cmd, data);
            restore_fd(stdin_backup, stdout_backup);
        }
        else
            exec_external(cmd, data);
        return;
    }
    execute_pipeline(cmd, data);
}
