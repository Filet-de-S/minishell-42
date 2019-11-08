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
	if (environ[i] == 0 || !path)
		return (NULL);
	i = 0;
	while (path[i] != '=')
		i++;
	i++;
	return(&path[i]);
}

int		replace_string(char **to_replace, char *var, int st, int l)
{
	char	*str;
	int		i;
	int		dl;

	i = 0;
	dl = ft_strlen(var) + ft_strlen(*to_replace) - l;
	if ((str = ft_strnew(dl)) == NULL)
		return (-1);
	while (*to_replace[i] < st)
		str[i] = to_replace[i++];
	dl = 0;
	while (dl < ft_strlen(var))
		str[i++] = var[dl++];
	dl = st + l;
	while (*to_replace[dl])
		str[i++] = to_replace[dl++];
	ft_strdel(to_replace);
	to_replace = str;
	return (0);
}
