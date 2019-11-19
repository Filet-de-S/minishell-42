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
		*next = 0;
		bin_p = search_obj(path, needle, next, l);
		bin_p == NULL ? err_msg(4, "can't malloc cmd name") : err_msg(4, bin_p);
		ft_strdel(&bin_p);
		exit(1);
	}
	return (NULL);
}

char	*env_value(char *igla)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	if (igla == NULL)
		return (NULL);
	tmp = igla;
	if (igla[ft_strlen(igla) - 1] != '=' && !(tmp = ft_strjoin(igla, "="))
		&& !err_msg(1, NULL))
		return (NULL);
	j = ft_strlen(tmp);
	while (environ[++i])
		if (environ[i][0] == tmp[0] && !ft_strncmp(environ[i], tmp, j))
			break ;
	if (environ[i] == 0 || !(environ[i] + j))
		return (NULL);
	return (environ[i] + j);
}

int		repl_string(char **to_replace, char *var, int st, int l)
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
	if (!var)
		return (-2);
	return (0);
}

char	**complete_path(void)
{
	char	**p;
	char	*tmp;
	int		i;

	if ((tmp = env_value("PATH=")) == NULL)
		return (NULL);
	if ((p = ft_strsplit(tmp, ':')) == NULL && !err_msg(1, NULL))
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
