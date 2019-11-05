#ifndef MINISHFT_H
# define MINISHFT_H
# include "libft.h"
# include <dirent.h>
extern char **environ;

char	*search_obj(char *env_path, char *needle, int *next, int **last);
int     err_msg(int stat, char *info);
char	*env_path(char *needle);
int		is_builtin(char *cmd, char **cmd_run);

#endif