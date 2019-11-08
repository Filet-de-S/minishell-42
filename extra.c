#include "minishft.h"

int		err_msg(int st, char *info)
{
	write(2, "msh: ", 5);
	if (st == 1)
		write(2, "Cannot allocate memory\n", 23);
	else
	{
		write(2, info, ft_strlen(info));
		if (st == 2)
			write(2, ": Command not found\n", 20);
		else if (st == 3)
        	write(2, ": No such file or directory\n", 28);
		else if (st == 4)
			write(2, ": Permission denied\n", 20);
		else
			write(2, ": Can't fork\n", 13);
	}
	return (0);
}

int		get_env(void)
{
	int		i;
	char 	**tmp;
	int		err;
	
	i = -1;
	err = 0;
	while (environ[++i])
		;
	if (!(tmp = (char**)malloc(sizeof(char*) * i)) && !err_msg(1, NULL))
		err = -1;
	else
	{
		i = -1;
		while (environ[++i])
			if (!(tmp[i] = ft_strdup(environ[i])) && !err_msg(1, NULL) && (err = -1))
				break;
	}
	(err == -1) ? ft_strdl(tmp) : (environ = tmp);
	if (err == -1)
		return (-1);
	return (0);
}

char	*split_count(char *env, char needle, int **last)
{
	char *path;

	if (!(path = ft_strsplit(env, ':')) && !err_msg(1, NULL))
		return (NULL);
	if (*last[0] != 0)
		while (path[++(*last[0])])
			;
	return (path);
}
