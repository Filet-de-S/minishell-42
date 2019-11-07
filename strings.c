#include "minishft.h"

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
	if (needle == NULL)
		return (NULL);
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

int		replace_symbols(char **to_replace)
{
	int		i;
	char	*var;
	int		j;
	int		t;

	j = 0;
	i = -1;
	while (to_replace[++i])
		if (to_replace[i] == '$')
		{
			t = i + 1;
			while (to_replace[++i] != ' ' && to_replace[i])
				j++;
			if (j)
				if ((var = env_path(ft_strsub(to_replace, t, (size_t)j))) == NULL
					&& !ft_strdel(&var))
					return (-1);
			if (replace_string(to_replace, var, t - 1, j) == -1 &&
				!ft_strdel(&var))
				return (-1);
			i = t - 1;
		}
}

int		replace_string(char **to_replace, char *var, int t, int j)
{

}

//unset HOME
//cd ~ -- ALL Is OK