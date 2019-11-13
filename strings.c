#include "minishft.h"

char	*search_obj(char **path, char *needle, int *next, int *l)
{
	char	*bin_p;

	while (path[*next])
	{
		if (!(bin_p = ft_strjoin(path[*next], needle)) &&
			!err_msg(1, NULL))
			return (NULL);
		if (!access(bin_p, F_OK))
			return (bin_p);
		ft_strdel(&bin_p);
		++(*next);
	}
	//  PATH is empty for bin and it;s parent
	if ((l[1] == 0 || l[1] == -1) && !err_msg(2, needle)) // ? why l[1] == -1 ?
		l[1] = -1;
	else
	{
		bin_p = search_obj(path, needle, 0, l);
        bin_p == NULL ? err_msg(4, "couldn't malloc cmd name") : err_msg(4, bin_p);
		ft_strdel(&bin_p);
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
	size_t	dl;

	if (var != NULL)
		dl = ft_strlen(var) + ft_strlen(*to_replace) - l;
	else
		dl = ft_strlen(*to_replace) - l;
	if ((str = ft_strnew(dl)) == NULL)
		return (-1);
    i = -1;
    while (*to_replace[++i] < st)
		str[i] = *to_replace[i];
	dl = 0;
	if (var != NULL)
		while (dl < ft_strlen(var))
			str[i++] = var[dl++];
	dl = st + l;
	while (*to_replace[dl])
		str[i++] = *to_replace[dl++];
	ft_strdel(to_replace);
	*to_replace = str;
	return (0);
}
