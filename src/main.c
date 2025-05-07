#include "../include/minishell.h"

int g_status;

t_cmd *fake_parse_input(void)
{
    t_cmd *cmd1 = malloc(sizeof(t_cmd));
    t_cmd *cmd2 = malloc(sizeof(t_cmd));

    // Commande 1 : ls
    cmd1->argv = malloc(sizeof(char *) * 2);
    cmd1->argv[0] = ft_strdup("true");
    cmd1->argv[1] = NULL;
    cmd1->isfirst = 1;
    cmd1->islast = 0;
	cmd1->infile = NULL;
	cmd1->outfile = NULL;
    cmd1->next = cmd2;

    // Commande 2 : grep .c
    cmd2->argv = malloc(sizeof(char *) * 2);
    cmd2->argv[0] = ft_strdup("false");
    // cmd2->argv[1] = ft_strdup("home");
    cmd2->argv[1] = NULL;
    cmd2->isfirst = 0;
    cmd2->islast = 1;
	cmd2->infile = NULL;
	cmd2->outfile = NULL;
    cmd2->next = NULL;

    return cmd1;
}


t_cmd	*parse_input(char *line)
{
	t_cmd *cmd;
	char **args;
	
	args = ft_split(line, ' ');
	if (!args || !args[0])
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = args;
	cmd->infile = NULL;
	cmd->outfile = NULL; 
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}
void f()
{
	system("lsof -c minishell");
}

int main(int argc, char **argv, char **envp)
{
	// atexit(f);
	t_minishell data;
	t_env_var *env;
	(void)argc;
	(void)argv;
	init_env(&env, envp);
	data.envp = env;
	while (1)
	{
		char *line = readline("minishell$ ");
		if (!line)
			break ; // Ctrl+D = exit
		if (*line)
			add_history(line);
		data.cmd_list = parse_input(line);
		free(line);
		// data.cmd_list = fake_parse_input();
		if (data.cmd_list)
			execute_cmds(&data);
		clear_cmd_list(&data.cmd_list);
	}
	close_fds_except_std();
	free_env(data.envp);
	return (g_status);
}
