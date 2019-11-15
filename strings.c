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

char	*env_value(char *igla)
{
	size_t	i;
	char	*path;

	i = -1;
	if (igla == NULL)
		return (NULL);
	while (environ[++i])
		if (environ[i][0] == igla[0] && (path = ft_strstr(environ[i], igla)) != NULL
		 && !ft_strncmp(path, igla, ft_strlen(igla)))
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
    while (++i < st)
		str[i] = (*to_replace)[i];
	dl = 0;
	if (var != NULL)
		while (var[dl])
			str[i++] = var[dl++];
	dl = st + l;
	while ((*to_replace)[dl])
		str[i++] = (*to_replace)[dl++];
	ft_strdel(&(*to_replace));
	*to_replace = str;
	return (0);
}

char    **complete_path(char *path)
{
    char    **p;
    char    *tmp;
    int     i;

    if ((p = ft_strsplit(path, ':')) == NULL && !err_msg(1, NULL))
        return (NULL);
    i = 0;
    while (p[i])
    {
        if ((tmp = ft_strjoin(p[i], "/")) == NULL && !err_msg(1, NULL) &&
            !ft_strdl(p))
            return (NULL);
        ft_strdel(&p[i]);
        p[i++] = tmp;
    }
    return (p);
}