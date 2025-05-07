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
        if (arg[i] == '+' && arg[i + 1] == '=')
            return (true);
        if (arg[i] == '=')
            return (true);
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

static bool is_append_export(const char *arg)
{
	int i = 0;
	while (arg[i] && !(arg[i] == '+' && arg[i + 1] == '='))
		i++;
	return (arg[i] == '+' && arg[i + 1] == '=');
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

static void handle_append_expand(const char *cmd, char *key, char *value, t_env_var *envp)
{
    t_env_var *var;
    char *new_value;
    int key_len;

    key_len = ft_strchr(cmd, '+')  - cmd;
    key = ft_substr(cmd, 0, key_len);
    value = ft_substr(cmd, key_len + 2, ft_strlen(cmd) - key_len - 2);
    var = get_env_value(envp, key);
    if (var)
    {
        new_value = ft_strjoin(var->value, value);
        set_env_value(&envp, key, new_value);
        free(new_value);
    }
    else
        set_env_value(&envp, key, value);
    free(key);
    free(value);
}

static void handle_export_with_value(const char *cmd, char *key, char *value, t_env_var *envp)
{
    int equal_sign;
    equal_sign = ft_strchr(cmd, '=') - cmd;
    key = ft_substr(cmd, 0, equal_sign);
    value = ft_substr(cmd, equal_sign + 1, ft_strlen(cmd) - (equal_sign - 1));
    set_env_value(&envp, key, value);
    free(key);
    free(value);
}

void handle_empty_value(char *cmd, t_env_var *envp)
{
    t_env_var *var;
    if (!get_env_value(envp, cmd))
    {
        var = add_new_env(cmd, NULL);
        lstadd_back_env(&envp, var);
    }
}

void exec_export(char **argv, t_env_var *envp)
{
    int i;
    char *key;
    char *value;

    i = 1;
    key = NULL;
    value = NULL;
    if (!argv[1])
    {
        print_sorted_env(envp);
        return ;
    }
    while (argv[i])
    {
        if (!check_varname(argv[i]))
        {
            error_export(argv[i]);
            return ;
        }
        if (!ft_strchr(argv[i], '='))
            handle_empty_value(argv[i], envp);
        if (is_append_export(argv[i]))
            handle_append_expand(argv[i], key, value, envp);
        else if (ft_strchr(argv[i], '='))
            handle_export_with_value(argv[i], key, value, envp);
        i++;
    }
    g_status = 0;
}
