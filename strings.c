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

char	*search_obj(char *env_path, char *needle, int *next, int **last)
{
	char	*path;
	char	*bin_p;

	if (!(path = ft_strsplit(env_path, ':')) && !err_msg(1, NULL))
		return (NULL);
	if (*last[0] != 0)
		while (path[++(*last[0])])
			;
	while (path[*next])
	{
		if (!(bin_p = ft_strjoin(path[*next], needle)) && !err_msg(1, NULL) && !ft_strdl(path))
			return (NULL);
		if (!access(bin_p, F_OK) && !ft_strdl(path))
			return (bin_p);
		(*next)++;
	}
	if (*last[1] == 0)
		*last[1] = -1;
	else
		*last = -2;
	return (NULL);
}

char	*env_path(char *needle)
{
	size_t	i;
	char	*path;
	int		j;

	i = -1;
	j = 0;
	while(environ[++i])
		if (ft_strstr(environ[i], needle) != NULL)
			break;
	if (environ[i] == 0)
		return (NULL);
	while (environ[i][j] != '=')
		j++;
	j++;
	path = (char *)environ[i][j];
	return (path);
}

int		is_builtin(char *cmd, char **cmd_run)
{
	if (!ft_strcmp(cmd, "echo"))
		return (in_echo(cmd_run));
	else if (!ft_strcmp(cmd, "cd"))
		return(in_cd(cmd_run));
	else if (!ft_strcmp(cmd, "setenv"))
		return(in_setenv(cmd_run));
	else if (!ft_strcmp(cmd, "unsetenv"))
		return(in_unsetenv(cmd_run));
	else if (!ft_strcmp(cmd, "env"))
		return(in_env(cmd_run));
	else if (!ft_strcmp(cmd, "exit"))
		return(in_exit(cmd_run));
	return (-2); //no built-in
}

