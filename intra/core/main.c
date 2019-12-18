/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <kkatelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:41:20 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/12/18 18:05:39 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishft.h"

int		g_sign;

char	*child_prepare(char **cmd_run, char **path_env, int *last, int *next)
{
	char *cmd_path;

	if (cmd_run[0][0] == '/' || (cmd_run[0][0] == '.' && cmd_run[0][1] == '/'))
	{
		if (access((cmd_run[0]), F_OK) && !err_msg(3, cmd_run[0]))
			return (NULL);
		if ((cmd_path = ft_strdup(cmd_run[0])) == NULL && !err_msg(1, NULL))
			return (NULL);
		return (cmd_path);
	}
	else if ((cmd_path = search_obj(path_env, cmd_run[0], next, last)) == NULL)
		return (NULL);
	last[1] = 1;
	if (last[0] < 0)
		while (path_env[++last[0]])
			;
	return (cmd_path);
}

int		child_action(char **path_env, char **cmd_run, int *last, int next)
{
	pid_t		pid;
	char		*cmd_path;
	extern char **environ;

	if ((cmd_path = child_prepare(cmd_run, path_env, last, &next)) == NULL)
		return (-1);
	pid = fork();
	if ((g_sign = 1) && pid == 0 && execve(cmd_path, cmd_run, environ))
	{
		if (last[0] == -1)
			err_msg(4, cmd_path);
		else if (!ft_strdel(&cmd_path) && last[0] == next)
			(cmd_path = search_obj(path_env, cmd_run[0], 0, last)) == NULL ?
				err_msg(4, "couldn't malloc cmd name") : err_msg(4, cmd_path);
		else if ((last[2] = 1))
			child_action(path_env, cmd_run, last, ++next);
		exit(1);
	}
	else if (pid < 0)
		err_msg(5, cmd_path);
	else if (waitpid(pid, NULL, 0) == -1)
		write(2, "msh: waitpid error *_*\n", 23);
	if (!ft_strdel(&cmd_path) && last[2] == 1)
		exit(1);
	return (1);
}

int		replace_prerun(char **path_env, char **to_run, char ***cmd_rn)
{
	int cond;

	if (replace_exp(&(*to_run)) == -1)
		return (-1);
	if ((*cmd_rn = ft_strsplitwhites((*to_run))) == NULL && !err_msg(1, NULL))
		return (-1);
	else if (!((*cmd_rn)[0]) && !ft_strdl(*cmd_rn))
		return (1);
	if ((cond = is_builtin((*cmd_rn)[0], *cmd_rn)) != -2 && !ft_strdl(*cmd_rn))
	{
		if (cond == -1)
			return (-1);
		return (2);
	}
	if (!path_env && access((*cmd_rn)[0], F_OK) && !err_msg(2, (*cmd_rn)[0])
		&& !ft_strdl(*cmd_rn))
		return (-1);
	return (3);
}

int		exec_sh(char **to_run, int j, char **path_env, int i)
{
	char	**cmd_run;
	int		l[3];

	i = -1;
	cmd_run = NULL;
	path_env = complete_path();
	while (to_run[++i])
	{
		if (((l[0] = replace_prerun(path_env, &to_run[i], &cmd_run)) == -1
			|| l[0] == 1) && !ft_strdl(path_env))
			return (l[0]);
		else if (l[0] == 2)
			continue;
		l[0] = -1;
		l[1] = 0;
		l[2] = 0;
		if ((j = child_action(path_env, cmd_run, l, 0)) == -1 &&
			!ft_strdl(cmd_run) && !ft_strdl(path_env) && !(g_sign = 0))
			return (-1);
		g_sign = 0;
		ft_strdl(cmd_run);
	}
	ft_strdl(path_env);
	return (1);
}

int		main(void)
{
	char	*to_parse;
	char	**to_run;

	signal(SIGINT, parent_trap);
	g_sign = 0;
	to_run = NULL;
	if (ft_get_env(NULL, 0, NULL, 0) == -1)
		exit(1);
	while (1)
	{
		write(1, "\033[1;35m{*__*} > \033[0m", 20);
		if ((get_next_line(0, &to_parse) == -1 && !err_msg(1, NULL))
			|| to_parse == NULL)
			continue;
		if ((to_run = ft_strsplit(to_parse, ';')) != NULL)
			exec_sh(to_run, 0, NULL, 0);
		else
			err_msg(1, NULL);
		ft_strdl(to_run);
		ft_strdel(&to_parse);
	}
	return (0);
}
