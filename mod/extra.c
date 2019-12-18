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
		else if (st == 6)
			write(2, ": is a directory\n", 17);
		else
			write(2, ": Can't fork\n", 13);
	}
	return (0);
}

int		ft_get_env(char *needle, int i, char **tmp, int err)
{
	static int fl;

	i = -1;
	while (environ[++i])
		;
	(needle != NULL) ? i++ : i;
	if (!(tmp = (char**)malloc(sizeof(char*) * (i + 1))) && !err_msg(1, NULL))
		err = -1;
	else
	{
		i = -1;
		while (environ[++i])
			if (!(tmp[i] = ft_strdup(environ[i])) && !err_msg(1, NULL) && --err)
				break;
		if (err != -1 && needle && !(tmp[i++] = ft_strdup(needle)))
			err = -1;
	}
	if (err == -1 && !ft_strdl(tmp))
		return (-1);
	tmp[i] = 0;
	if (fl++ != 0)
		ft_strdl(environ);
	environ = tmp;
	return (0);
}

void parent_trap(int sig)
{
    if (sig == SIGINT && g_sign == 0)
        write(1, "\n\033[1;35m{*__*} > \033[0m", 21);
}