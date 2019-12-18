/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <kkatelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:00:52 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/12/18 18:09:09 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishft.h"

int		in_echo(char **cmd_run)
{
	int		i;

	i = 1;
	if (cmd_run[1] && !ft_strcmp("-n", cmd_run[1]))
	{
		while (cmd_run[++i])
		{
			ft_putstr(cmd_run[i]);
			write(1, " ", 1);
		}
	}
	else
	{
		while (cmd_run[i])
		{
			ft_putstr(cmd_run[i++]);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (1);
}

int		in_setenv(char *cmd_run, int i, char *needle)
{
	extern char **environ;
	char		tmp[80];

	i = -1;
	ft_bzero(&tmp, 80);
	while (cmd_run[++i] && cmd_run[i] != '=')
		tmp[i] = cmd_run[i];
	if ((tmp[i] = cmd_run[i]) != '=')
		return (-1);
	if ((needle = env_value(tmp)) == NULL)
	{
		if (ft_get_env(cmd_run, 0, NULL, 0) == -1)
			return (-1);
	}
	else
	{
		i = -1;
		while (environ[++i])
			if (!ft_strncmp(environ[i], tmp, ft_strlen(tmp)))
				break ;
		free(environ[i]);
		if ((environ[i] = ft_strdup(cmd_run)) == NULL)
			return (-1);
	}
	return (1);
}

int		in_unsetenv(char **cmd_run, int num, char **environ)
{
	int		i;
	char	tmp[80];

	if (!cmd_run[num])
		return (1);
	i = -1;
	while (cmd_run[num][++i])
		tmp[i] = cmd_run[num][i];
	ft_strcpy(&tmp[i], "=\0");
	i = -1;
	while (environ[++i])
	{
		if (environ[i][0] != cmd_run[num][0])
			continue;
		if (!ft_strncmp(tmp, environ[i], ft_strlen(tmp)))
			break ;
	}
	if (environ[i])
	{
		ft_strdel(&environ[i]);
		environ[i] = environ[i + 1];
		while (environ[++i])
			environ[i] = environ[i + 1];
	}
	return (in_unsetenv(cmd_run, ++num, environ));
}

int		in_env(char **environ)
{
	int i;

	i = 0;
	while (environ[i])
		ft_putendl(environ[i++]);
	return (1);
}

int		is_builtin(char *cmd, char **cmd_run)
{
	extern char	**environ;
	struct stat	buf;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (lstat(cmd, &buf) && !err_msg(3, cmd))
			return (-1);
		if (S_ISDIR(buf.st_mode) && !err_msg(6, cmd))
			return (-1);
		return (-2);
	}
	if (!ft_strcmp(cmd, "echo"))
		return (in_echo(cmd_run));
	else if (!ft_strcmp(cmd, "cd"))
		return (in_cd(cmd_run));
	else if (!ft_strcmp(cmd, "setenv"))
		return (in_setenv(cmd_run[1], 0, NULL));
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (in_unsetenv(cmd_run, 1, environ));
	else if (!ft_strcmp(cmd, "env"))
		return (in_env(environ));
	else if (!ft_strcmp(cmd, "exit"))
		return (in_exit());
	return (-2);
}
