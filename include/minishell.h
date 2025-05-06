#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
#include <stdbool.h>
# include <readline/readline.h>
#include <sys/stat.h>
#include "../Libft/libft.h"

extern int g_status;

struct stat st;

typedef struct s_token_node
{
	int					type;
	char				*value;
	bool				flag;
	int					fd_hrd;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_cmd
{
	char				**argv;
	char				*infile;
	char				*outfile;
    int                 append;
	bool				isfirst;
	bool				islast;
	t_token_node		*red;
	struct s_cmd		*next;
}	t_cmd;


typedef struct s_env_var
{
	char			*cle;
	char			*value;
	struct s_env_var	*next;
}	t_env_var;

// Structure principale du minishell
typedef struct s_minishell {
    t_env_var    *envp;     // Copie de l'environnement
    t_cmd   *cmd_list;  // Liste chaînée de commandes
} t_minishell;


void        init_env(t_env_var **debut_env, char **env);
int         is_builtin(char *cmd);
void        execute_cmds(t_minishell *data);
void        exec_builtin(t_cmd *cmd, t_minishell *data);
void        exec_pwd(void);
void        exec_echo(char **argv);
void        builtin_env(t_env_var *env);
void        exec_cd(char **argv, t_env_var *envp);
int         env_size(t_env_var *env);
void        exec_export(char **argv, t_env_var *envp);
void        exec_exit(char **argv);
void	    lstadd_back_env(t_env_var **lst, t_env_var *new_node);
bool        check_varname(const char *arg);
void        exec_unset(t_env_var **env, char **argv);
char        *get_env_value(t_env_var *env, const char *key);
t_env_var	*add_new_env(char *cle, char *value);
void        clear_cmd_list(t_cmd **cmd_list);
char        **env_to_tab(t_env_var *env);
void        restore_fd(int saved_stdin, int saved_stdout);
int         set_redirection(t_cmd *cmd);
char        **env_to_tab(t_env_var *env);
char        **get_path_directories(char **env);
char        *get_full_path_from_paths(char *command, char **paths);
void        ft_free_split(char **split);
char        *find_command_path(const char *command, char **env);
void		exec_external(t_cmd *cmd, t_minishell *data);
void		execute_pipeline(t_cmd *cmd, t_minishell *data);
void		close_fds_except_std(void);
void		free_env(t_env_var *env);

//Errors

void error_command_not_found(const char *cmd);
void error_permission_denied(const char *cmd);
void error_no_such_file(const char *cmd);
void error_fork(void);
void error_general(const char *msg);
void error_open_file(const char *filename);

#endif
