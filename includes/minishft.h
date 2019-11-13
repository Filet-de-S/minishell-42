#ifndef MINISHFT_H
# define MINISHFT_H
# include "libft.h"
# include <dirent.h>
# include <pwd.h>

extern char **environ;

char	*search_obj(char *env_path, char *needle, int *next, int *last);
int     err_msg(int stat, char *info);
char	*env_value(char *needle);
int		is_builtin(char *cmd, char **cmd_run);
int		replace_exp(char **to_parse);
char	*split_count(char *env, char needle, int *last);
int		replace_string(char **to_replace, char *var, int st, int l);
int		in_cd(char **cmd_run);
int 	in_exit(void);
int		in_setenv(char **cmd_run, int i, char *needle);
int		ft_get_env(char *needle, int i);


#endif