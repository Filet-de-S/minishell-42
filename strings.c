#include "minishft.h"

char	*search_obj(char *env_path, char *needle, int *next, int *last)
{
	char	*path;
	char	*bin_p;

	if (!(path = ft_strsplit(env_path, ':')) && !err_msg(1, NULL))
		return (NULL);
	if (*last != 0)
		while (path[++(*last)])
			;
	while (path[*next])
	{
		if (!(bin_p = ft_strjoin(path[*next], needle)) && !err_msg(1, NULL) && !ft_strdl(path))
			return (NULL);
		if (!access(bin_p, F_OK) && !ft_strdl(path))
			return (bin_p);
		(*next)++;
	}
	return (NULL);
}

char	*env_path(void)
{
	size_t	i;
	char	*path;
	int		j;

	i = -1;
	j = 0;
	while(environ[++i])
		if (ft_strstr(environ[i], "PATH") != NULL)
			break;
	if (environ[i] == 0)
		return (NULL);
	while (environ[i][j] != '/')
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