#include "minishft.h"

char	*search_obj(char *env_path, char *needle, int *next, int **l)
{
	char	*path;
	char	*bin_p;

	if (!(path = split_count(env_path, ':', l)))
		return (NULL);
	while (path[*next])
	{
		if (!(bin_p = ft_strjoin(path[*next], needle)) && 
			!err_msg(1, NULL) && !ft_strdel(&path))
			return (NULL);
		if (!access(bin_p, F_OK) && !ft_strdl(&path))
			return (bin_p);
		ft_strdel(&bin_p);
		(*next)++;
	}
	// if path's dir is not ended and malloc error and it's parent
	//    or PATH is empty for bin and it;s parent
	ft_strdl(&path);
	if ((*l[1] == 0 || *l[1] == -1) && !err_msg(2, bin_p) && !ft_strdel(&bin_p))
		*l[1] = -1;
	else
	{
		path = search_obj(env_path, needle, 0, 0);
		path == NULL ? err_msg(4, "couldn't malloc cmd name") : err_msg(4, path);
		exit(1);
	}
	return (NULL);
}

char	*env_value(char *needle)
{
	size_t	i;
	char	*path;

	i = -1;
	if (needle == NULL)
		return (NULL);
	while(environ[++i])
		if ((path = ft_strstr(environ[i], needle)) != NULL)
			break;
	if (environ[i] == 0 || path)
		return (NULL);
	i = 0;
	while (path[i] != '=')
		i++;
	i++;
	return(&path[i]);
}

int		is_builtin(char *cmd, char **cmd_run)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (-2);
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

int		replace_symbols(char **to_replace)
{
	int		i;
	int		t;

	i = -1;
	while (*to_replace[++i])
	{
		if ((*to_replace[i] == '$') && 
			(!(*to_replace[i + 1]) || *to_replace[i + 1] == ' '))
			continue;
		if (*to_replace[i] == '$' && dollar_exp(&i, to_replace) == -1)
			return (-1);		
		if (*to_replace[i] == '~' && tilda_exp(&i, to_replace) == -1)
			return (-1);
	}
}

int		dollar_exp(int *i, char **to_replace)
{
	char	*var;
	char	*value;
	int		j;
	int		t;

	j = 0;
	t = *i + 1;
	while (*to_replace[++(*i)] != ' ' && *to_replace[(*i)])
		j++;
	if ((var = ft_strsub(to_replace, t, (size_t)j)) == NULL)
			return (-1);
	value = env_value(var);
	ft_strdel(&var);
	if (replace_string(to_replace, value, t - 1, j) == -1)
		return (-1);
	*i = t - 1;
}

int		replace_string(char **to_replace, char *var, int st, int l)
{
	char	*left;
	char	*start;
	int		i;
	int		dl;

	if ((start = ft_strsub(*to_replace, 0, st)) == NULL)
		return (-1);
	if ((left = ft_strsub(*to_replace, st + l, ft_strlen(*to_replace) - st + l))
	 == NULL && !ft_strdel(start))
	 	return (-1);
	ft_strdel(to_replace);
	dl = ft_strlen(start) + ft_strlen(var) + ft_strlen(left);
	if ((to_replace = ft_strnew(dl)) == NULL && !ft_strdel(&left) &&
		!ft_strdel(&start))
		return (-1);
	i = 0;
	while (start[i])
		*to_replace[i] = start[i++];
	dl = 0;
	while (var[dl])
		*to_replace[i++] = var[dl++];
	dl = 0;
	while (left[dl])
		*to_replace[i++] = left[dl++];
	ft_strdel(&left);
	ft_strdel(&start);
}

//unset HOME
//cd ~ -- ALL Is OK