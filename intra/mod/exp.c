/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <kkatelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:00:56 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/12/18 17:04:33 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishft.h"

int		dollar_exp(int *i, char **to_replace)
{
	char	*var;
	char	*value;
	char	*tmp;
	int		j;
	int		t;

	j = 0;
	t = *i;
	tmp = *to_replace;
	while (tmp[(*i)] != ' ' && tmp[(*i)++])
		j++;
	if ((var = ft_strsub(*to_replace, t + 1, (size_t)j - 1)) == NULL)
		return (-1);
	value = env_value(var);
	ft_strdel(&var);
	if ((*i = repl_str(to_replace, value, t, j)) == -1)
		return (-1);
	*i = (*i == -2) ? (t - 1) : t;
	return (0);
}

int		tilda_else(struct passwd *user, char **value, char **replac, char **v)
{
	if ((user = getpwnam(*v)) != NULL)
		*value = user->pw_dir;
	else
	{
		if ((*replac)[0] == 'c' && (*replac)[1] == 'd' && (*replac)[2] == ' ')
		{
			if (!(*value = ft_strjoin("cd: ~", *v)) && !err_msg(1, NULL))
				;
			else
				err_msg(3, *value);
			ft_strdel(value);
			ft_strdel(v);
			return (-1);
		}
		ft_strdel(v);
		return (0);
	}
	return (1);
}

int		tilda_exp(int *i, char **rs, int j, int t)
{
	char			*var;
	char			*v;
	struct passwd	*user;

	while ((*rs)[(*i)] != '\0' && ((*rs)[(*i)] != ' ' && (*rs)[(*i)++] != '/'))
		j++;
	var = NULL;
	if (j > 1 && (var = ft_strsub(*rs, t + 1, (size_t)j - 1)) == NULL)
		return (-1);
	if (!(v = 0) && j == 1)
	{
		if ((v = env_value("HOME=")) == NULL)
		{
			if ((user = getpwuid(geteuid())) != NULL)
				v = user->pw_dir;
			else if (!err_msg(1, NULL))
				return (-1);
		}
	}
	else if ((tilda_else(user = NULL, &v, rs, &var)) == -1)
		return (-1);
	if (!ft_strdel(&var) && v && ((j = repl_str(rs, v, t, j)) == -1 || j == 0))
		return (j);
	*i = t;
	return (1);
}

int		replace_exp(char **to_replace)
{
	int i;

	i = -1;
	while ((*to_replace)[++i])
	{
		if (((*to_replace)[i] == '$') &&
			(!((*to_replace)[i + 1]) || (*to_replace)[i + 1] == ' '))
			continue;
		if ((*to_replace)[i] == '$' && dollar_exp(&i, to_replace) == -1)
			return (-1);
		i = (i < 0 ? 0 : i);
		if ((*to_replace)[i] == '~' && tilda_exp(&i, to_replace, 0, i) == -1)
			return (-1);
		i = (i < 0 ? 0 : i);
	}
	return (0);
}
