#include "../../../include/minishell.h"

void unset_var(t_env_var **env, const char *var)
{
    t_env_var *current = *env;
    t_env_var *prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->cle, var) == 0)
        {
            if (prev == NULL)
                *env = current->next;
            else
                prev->next = current->next;
            free(current->cle);
            free(current->value);
            free(current);
            return ;
        }
        prev = current;
        current = current->next;
    } 
}

void exec_unset(t_env_var **env, char **argv)
{
    int i;

    i = 1;

    while (argv[i])
    {
        if (!check_varname(argv[i]))
            printf("minishell: unset: `%s': not a valid identifier\n", argv[i]);
        else
            unset_var(env, argv[i]);
        i++;
    }
    g_status = 0;
}
