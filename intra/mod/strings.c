/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <kkatelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:01:07 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/12/18 18:08:01 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishft.h"

char	*last_obj(char **path, char *needle, int *next)
{
	char *bin_p;

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
	return (NULL);
}

char	*search_obj(char **path, char *needle, int *next, int *l)
{
	char	*bin_p;

	while (path[*next])
	{
		if (!(bin_p = ft_strjoin(path[*next], needle)) &&
			!err_msg(1, NULL))
			return (NULL);
		if (!access(bin_p, X_OK))
			return (bin_p);
		ft_strdel(&bin_p);
		++(*next);
	}
	*next = 0;
	bin_p = last_obj(path, needle, next);
	if ((l[1] == 0 || l[1] == -1) && (l[1] = -1))
		bin_p == NULL ? err_msg(2, needle) : err_msg(4, bin_p);
	else
	{
		bin_p == NULL ? err_msg(4, "can't malloc cmd name") : err_msg(4, bin_p);
		exit(1);
	}
	ft_strdel(&bin_p);
	return (NULL);
}

char	*env_value(char *igla)
{
	int			i;
	int			j;
	char		*tmp;
	extern char **environ;

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
	if (ft_strcmp(igla, tmp))
		ft_strdel(&tmp);
	if (environ[i] == 0 || !(environ[i] + j))
		return (NULL);
	return (environ[i] + j);
}

int		repl_str(char **to_replace, char *var, int st, int l)
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
