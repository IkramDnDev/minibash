#include "../../include/minishell.h"

t_env_var	*add_new_env(char *cle, char *value)
{
	t_env_var	*new_node;

	new_node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_node)
		return (NULL);
	new_node->cle = ft_strdup(cle);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}


void	lstadd_back_env(t_env_var **lst, t_env_var *new_node)
{
	t_env_var	*last;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

void	init_env(t_env_var **debut_env, char **env)
{
	int		i;
	int		j;
	char	*cle;
	char	*value;

	i = 0;
	while (env[i])
	{
		j = 0;
		while(env[i][j] && env[i][j] != '=')
				j++;
		cle = ft_substr(env[i], 0, j);
		value = ft_substr(env[i], j + 1, (ft_strlen(env[i]) - (j + 1)));
		i++;
		lstadd_back_env(debut_env, add_new_env(cle, value));
		free(cle);
		free(value);
	}
}
