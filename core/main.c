#include "minishft.h"

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
	pid_t	pid;
	char	*cmd_path;

	if ((cmd_path = child_prepare(cmd_run, path_env, last, &next)) == NULL)
		return (-1);
	pid = fork();
	if (pid == 0 && execve(cmd_path, cmd_run, environ))
	{
		if (last[0] == -1)//if bin is not from search_obj
			err_msg(4, cmd_path);
		else if (last[0] == next) //all bins are searched
			(cmd_path = search_obj(path_env, cmd_run[0], 0, last)) == NULL ?
				err_msg(4, "couldn't malloc cmd name") : err_msg(4, cmd_path);
		else// if (next != last && last != -1)
			child_action(path_env, cmd_run, last, ++next);
		exit(1);
	}
	else if (pid < 0) //if fork problem
		err_msg(5, cmd_path);
	else if(waitpid(pid, NULL, 0) == -1)// if parent
		write(2, "msh: waitpid error *_*\n", 23);
	ft_strdel(&cmd_path);
	return (1);
}

int		replace_prerun(char **path_env, char ***to_run, char ***cmd_run, int i)
{
	int cond;

	if (replace_exp(to_run[i]) == -1)
		return (-1);
	//split cmd and args by ` `
	if ((*cmd_run = ft_strsplit((*to_run)[i], ' ')) == NULL && !err_msg(1, NULL))
		return(-1);
	else if (!((*cmd_run)[0]) && !ft_strdl(*cmd_run))
		return (1);
	//run if built-in
	if ((cond = is_builtin((*cmd_run)[0], *cmd_run)) != -2 && !ft_strdl(*cmd_run))
	{
		if (cond == -1)
			return (-1);
		return (2);
	}
	if (!path_env && access((*cmd_run)[0], F_OK) && !err_msg(3, (*cmd_run)[0])
		&& !ft_strdl(*cmd_run))
		return (-1);
	return (3);
}

int		exec_sh(char **to_run, int j, char **path_env, int i)
{
	char	**cmd_run;
	int		l[2];

	i = -1;
	cmd_run = NULL;
	path_env = complete_path();
	while(to_run[++i])
	{
		if ((l[0] = replace_prerun(path_env, &to_run, &cmd_run, i)) == -1
			|| l[0] == 1)
			return (l[0]);
		else if (l[0] == 2)
			continue;
		l[0] = -1;
		l[1] = 0;
		// run cmd with all staff
		if ((j = child_action(path_env, cmd_run, l, 0)) == -1 && !ft_strdl(cmd_run) &&
			!ft_strdl(path_env))
			return (-1);
		ft_strdl(cmd_run);
	}
	ft_strdl(path_env);
	return (1);
}

int		main(void)
{
	char	*to_parse;
	char	**to_run;

	to_run = NULL;
	if (ft_get_env(NULL, 0, NULL, 0) == -1)
		exit(1);
	while (1)
	{
		write(1, "\033[1;35m{*__*} > \033[0m", 20);
		//lets get a full cmd line
		if ((get_next_line(0, &to_parse) == -1 && !err_msg(1, NULL))
			|| to_parse == NULL)
			continue;
		//split cmds by `;` and return 2d array
		if ((to_run = ft_strsplit(to_parse, ';')) != NULL)
			exec_sh(to_run, 0, NULL, 0); //and exec cmd one by one
		else
			err_msg(1, NULL);
		ft_strdl(to_run);
		ft_strdel(&to_parse);
	}
	//SIGNAL CATCH
	return (1);
}
