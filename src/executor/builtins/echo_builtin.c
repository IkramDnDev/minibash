#include "../../../include/minishell.h"

bool	is_n_option(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
void	exec_echo(char **argv)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	while (argv[i] && is_n_option(argv[i]))
	{
		new_line = false;
		i++;
	}
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "$?") == 0)
			printf("%d", g_status);
		else
			printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	g_status = 0;
}
