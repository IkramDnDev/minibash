#include "../include/minishell.h"

int g_status;

// t_cmd *fake_parse_input(void)
// {
//     t_cmd *cmd1 = malloc(sizeof(t_cmd));
//     t_cmd *cmd2 = malloc(sizeof(t_cmd));

//     // Commande 1 : ls
//     cmd1->argv = malloc(sizeof(char *) * 2);
//     cmd1->argv[0] = ft_strdup("true");
//     cmd1->argv[1] = NULL;
//     cmd1->isfirst = 1;
//     cmd1->islast = 0;
// 	cmd1->infile = NULL;
// 	cmd1->outfile = NULL;
//     cmd1->next = cmd2;

//     // Commande 2 : grep .c
//     cmd2->argv = malloc(sizeof(char *) * 2);
//     cmd2->argv[0] = ft_strdup("false");
//     // cmd2->argv[1] = ft_strdup("home");
//     cmd2->argv[1] = NULL;
//     cmd2->isfirst = 0;
//     cmd2->islast = 1;
// 	cmd2->infile = NULL;
// 	cmd2->outfile = NULL;
//     cmd2->next = NULL;

//     return cmd1;
// }


// t_cmd	*parse_input(char *line)
// {
// 	t_cmd *cmd;
// 	char **args;
	
// 	args = ft_split(line, ' ');
// 	if (!args || !args[0])
// 		return (NULL);
// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->argv = args;
// 	cmd->infile = NULL;
// 	cmd->outfile = NULL;
// 	cmd->red->type = REDIRECT_IN;
// 	cmd->red->value = "outfile.txt";
// 	cmd->append = 0;
// 	cmd->next = NULL;
// 	return (cmd);
// }


static t_token_node *new_redir(int type, char *value)
{
	t_token_node *node = malloc(sizeof(t_token_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = strdup(value);
	node->flag = false;
	node->fd_hrd = -1;
	node->next = NULL;
	return node;
}

static void add_redir(t_cmd *cmd, t_token_node *redir)
{
	t_token_node *tmp = cmd->red;
	if (!tmp)
		cmd->red = redir;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

static t_cmd *new_cmd()
{
	t_cmd *cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->isfirst = false;
	cmd->islast = false;
	cmd->argv = NULL;
	cmd->red = NULL;
	cmd->next = NULL;
	return cmd;
}

t_cmd *parse_input(char *line)
{
	t_cmd *head = NULL;
	t_cmd *curr = NULL;
	char **tokens = ft_split(line, ' ');
	int i = 0, argc = 0;
	char *argv[100]; // temporaire, mieux d'allouer dynamiquement

	if (!tokens)
		return (NULL);

	head = new_cmd();
	if (!head)
		return (NULL);
	curr = head;

	while (tokens[i])
	{
		if (strcmp(tokens[i], "|") == 0)
		{
			argv[argc] = NULL;
			curr->argv = malloc(sizeof(char *) * (argc + 1));
			for (int j = 0; j < argc; j++)
				curr->argv[j] = strdup(argv[j]);
			curr->argv[argc] = NULL;
			argc = 0;

			t_cmd *next = new_cmd();
			curr->next = next;
			curr = next;
		}
		else if (strcmp(tokens[i], ">") == 0 && tokens[i + 1])
			add_redir(curr, new_redir(REDIRECT_OUT, tokens[++i]));
		else if (strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
			add_redir(curr, new_redir(REDIRECT_APPEND, tokens[++i]));
		else if (strcmp(tokens[i], "<") == 0 && tokens[i + 1])
			add_redir(curr, new_redir(REDIRECT_IN, tokens[++i]));
		else
			argv[argc++] = tokens[i];
		i++;
	}

	// Copier les derniers arguments
	if (argc > 0 && curr)
	{
		argv[argc] = NULL;
		curr->argv = malloc(sizeof(char *) * (argc + 1));
		for (int j = 0; j < argc; j++)
			curr->argv[j] = strdup(argv[j]);
		curr->argv[argc] = NULL;
	}

	// Marquer isfirst / islast
	t_cmd *tmp = head;
	if (tmp)
		tmp->isfirst = true;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->islast = true;

	// Free tokens
	for (i = 0; tokens[i]; i++)
		free(tokens[i]);
	free(tokens);

	return head;
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
