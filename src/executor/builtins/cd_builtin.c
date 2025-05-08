#include "../../../include/minishell.h"

static void	update_env_value(t_env_var *env, char *key, char *value)
{
	while (env)
	{
		if (strcmp(env->cle, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

void	exec_cd(char **argv, t_env_var *envp)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];
	char	*target_dir;

	if (!argv[1])
	{
		target_dir = get_env_value_char(envp, "HOME");
		if (!target_dir)
		{
			printf("minishell: cd: HOME not set\n");
			g_status = 1;
			return ;
		}
	}
	else
		target_dir = argv[1];
	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		perror("minishell: getcwd");
		g_status = 1;
		return ;
	}
	if (chdir(target_dir) != 0)
	{
		printf("minishell: cd: %s: %s\n", target_dir, strerror(errno));
		g_status = 1;
		return ;
	}
	if (!getcwd(newpwd, sizeof(newpwd)))
	{
		perror("minishell: getcwd");
		g_status = 1;
		return ;
	}
	update_env_value(envp, "OLDPWD", oldpwd);
	update_env_value(envp, "PWD", newpwd);
	g_status = 0;
}
