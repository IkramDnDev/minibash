#include "../../include/minishell.h"

t_env_var *add_new_env(char *key, char *value)
{
    t_env_var *new = malloc(sizeof(t_env_var));
    if (!new)
        return (NULL);
    new->cle = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
    new->next = NULL;
    return (new);
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
