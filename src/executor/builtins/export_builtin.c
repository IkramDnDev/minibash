#include "../../../include/minishell.h"

bool check_varname(const char *arg)
{
    int i;

    i = 0;
    if (!arg || !arg[0])
        return(false);
    if (!ft_isalpha(arg[0]) && arg[0] != '_')
        return(false);
    while(arg[i] && arg[i] != '=')
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return(false);
        i++;
    }
    return(true);
}

static void sort_env_tab(char **tab)
{
    int i;
    int j;
    char *tmp;
    
    i = 0;
    while(tab[i])
    {
        j = 0;
        while(tab[j + 1])
        {
            if (ft_strcmp(tab[j], tab[j + 1]) > 0)
            {
                tmp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = tmp;
            }
            j++;
        }
    i++;
    }
}



static void print_sorted_env(t_env_var *env)
{
    int i;
    char **tab;

    tab = env_to_tab(env);
    sort_env_tab(tab);
    if (!tab)
        return ;
    i = 0;
    while (tab[i])
    {
        printf("declare -x %s\n", tab[i]);
        free(tab[i]);
        i++;
    }
    free(tab);
}
static void set_env_value(t_env_var **env, char *key, char *value)
{
    t_env_var *tmp = *env;
    while (tmp)
    {
        if (ft_strcmp(tmp->cle, key) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return ;
        }
        tmp = tmp->next;
    }
    t_env_var *new_var = add_new_env(key, value);
    lstadd_back_env(env, new_var);
}

void exec_export(char **argv, t_env_var *envp)
{
    int i;
    int equal_sign;
    char *key;
    char *value;

    i = 1;
    if (!argv[1])
    {
        print_sorted_env(envp);
        return ;
    }
    while (argv[i])
    {
        if (!check_varname(argv[i]))
        {
            printf("minishell: export: `%s': not a valid identifier\n", argv[i]);
            g_status = 1;
            return ;
        }
        else
        {
            equal_sign = ft_strchr(argv[i], '=') - argv[i];
            if (equal_sign >= 0)
            {
                key = ft_substr(argv[i], 0, equal_sign);
                value = ft_substr(argv[i], equal_sign + 1, ft_strlen(argv[i]) - (equal_sign - 1));
                set_env_value(&envp, key, value);
                free(key);
                free(value);
            }
        }
        i++;
    }
    g_status = 0;
}
