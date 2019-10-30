#ifndef MINISHFT_H
# define MINISHFT_H
# include "libft.h"
# include <dirent.h>

char	*search_obj(char *env_path, char *needle, int next);
int     err_msg(int stat, char *info);


#endif