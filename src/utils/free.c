#include "../../include/minishell.h"

void clear_cmd_list(t_cmd **cmd_list)
{
    t_cmd *tmp;
    int i;

    if (!cmd_list || !*cmd_list)
        return;

    while (*cmd_list)
    {
        tmp = (*cmd_list)->next;
        if ((*cmd_list)->argv)
        {
            i = 0;
            while ((*cmd_list)->argv[i])
            {
                free((*cmd_list)->argv[i]);
                i++;
            }
            free((*cmd_list)->argv);
        }
        
        free(*cmd_list);
        *cmd_list = tmp;
    }
}
void free_env(t_env_var *env)
{
    t_env_var *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->cle);
        free(env->value);
        free(env);
        env = tmp;
    }
}

void	close_fds_except_std(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}
void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
