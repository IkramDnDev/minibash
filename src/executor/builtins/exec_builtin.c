
#include "../../../include/minishell.h"


void builtin_env(t_env_var *env)
{
    while (env)
    {
        if (env->value)
        {
            printf("%s=%s\n", env->cle, env->value);
        }
        env = env->next;
    }
    g_status = 0;
}


void exec_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("pwd");
        g_status = 1;
        return;
    }
    printf("%s\n", cwd);
    g_status = 0;
}

void exec_builtin(t_cmd *cmd, t_minishell *data)
{
    if (!(ft_strcmp(cmd->argv[0] ,"echo")) || !(ft_strcmp(cmd->argv[0] ,"ECHO"))) //redirection
        exec_echo(cmd->argv);
    else if (!ft_strcmp(cmd->argv[0], "cd"))
        exec_cd(cmd->argv, data->envp);
    else if (!ft_strcmp(cmd->argv[0], "exit"))
        exec_exit(cmd->argv);
    if (!(ft_strcmp(cmd->argv[0], "pwd")) || !(ft_strcmp(cmd->argv[0], "PWD")))
        exec_pwd();
    else if (!(ft_strcmp(cmd->argv[0], "env")) || !(ft_strcmp(cmd->argv[0], "ENV"))) //redirection
        builtin_env(data->envp);
    else if (!ft_strcmp(cmd->argv[0], "export")) //redirection
        exec_export(cmd->argv, data->envp);
    else if (!ft_strcmp(cmd->argv[0], "unset"))
        exec_unset(&data->envp, cmd->argv);
}
