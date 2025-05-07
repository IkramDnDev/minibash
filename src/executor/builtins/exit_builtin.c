#include "../../../include/minishell.h"

static int	long_value(const char *str)
{
	int					i = 0;
	int					sign = 1;
	unsigned long long	num = 0;
	unsigned long long	limit;

	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		num = num * 10 + (str[i] - '0');
        if (sign == 1)
            limit = (unsigned long long)LONG_MAX;
        else
            limit = (unsigned long long)LONG_MAX + 1;
		if (num > limit)
			return (0);
		i++;
	}
	return (1);
}

void exec_exit(char **argv)
{
    long exit_code;

    write(2, "exit\n", 5);
    if (!argv[1])
        exit(g_status); 
    if (!long_value(argv[1]))
    {
        printf("minishell: exit: %s: numeric argument required\n", argv[1]);
        exit(255);
    }
    if (argv[2])
    {
        printf("minishell: exit: too many arguments\n");
        g_status = 1;
        return ;
    }
    exit_code = ft_atol(argv[1]);
    exit(exit_code % 256);
}
