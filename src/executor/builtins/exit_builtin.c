#include "../../../include/minishell.h"

static int is_numeric(const char *str)
{
    int i;

    if (!str)
        return(0);
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while(str[i])
    {
        if (!ft_isdigit(str[i]))
            return(0);
        i++;
    }
    return(1);
}

void exec_exit(char **argv)
{
    long exit_code;

    write(2, "exit\n", 5);
    if (!argv[1])
        exit(g_status);
    if (!is_numeric(argv[1]))
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
