#include "minishft.h"

char    *child_prepare(char **cmd_run, char **path_env, int *last, int *next)
{

	char *cmd_path;

	if (cmd_run[0][0] == '/' || (cmd_run[0][0] == '.' && cmd_run[0][1] == '/'))
	{
		if (access((cmd_path = cmd_run[0]), F_OK) && !err_msg(3, cmd_path))
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
    char    *cmd_path;

	//run if built-in
	if ((pid = is_builtin(cmd_run[0], cmd_run)) != -2)
		return ((int)pid);
    //search bin
	if ((cmd_path = child_prepare(cmd_run, path_env, last, &next)) == NULL)
		return (-1);
	pid = fork();
	// !!! free cmd_path !!!!!
	if (pid == 0 && execve(cmd_path, cmd_run, environ)) //if child
	{
		if (last[0] == -1) // if bin is not from search_obj
			err_msg(4, cmd_path);
		else if (last[0] == next)
			(cmd_path = search_obj(path_env, cmd_run[0], 0, last)) == NULL ?
				err_msg(4, "couldn't malloc cmd name") : err_msg(4, cmd_path);
		else// if (next != last && last != -1)
			child_action(path_env, cmd_run, last, ++next);
		ft_strdel(&cmd_path);
		exit(1);
	}
	else if (pid < 0) //if fork problem
		err_msg(5, cmd_path);
	else if(waitpid(pid, NULL, 0) == -1)// if parent
		write(2, "msh: waitpid error *_*\n", 23);
    ft_strdel(&cmd_path);
    return (1);
}

int		exec_sh(char **to_run, int j, char *env)
{
	char	**cmd_run;
	int		i;
	char 	**path_env;
	int		last[2];

	i = -1;
	while(to_run[++i])
	{
		last[0] = -1;
		last[1] = 0;
		if (replace_exp(&to_run[i]) == -1)
			return (-1);
		//split cmd and args by ` `
		if ((cmd_run = ft_strsplit(to_run[i], ' ')) == NULL && !err_msg(1, NULL))
			return(-1);
		//get path of objBIN
		if ((env = env_value("PATH")) == NULL && !ft_strdl(cmd_run) &&
			access(cmd_run[0], F_OK) && !err_msg(3, "env"))
			return (-1); // no path (no env), (2) doesn't start with '/', (3) file is not in this dir
		if ((path_env = complete_path(env)) == NULL && !ft_strdl(cmd_run))
            return (-1);
		// run cmd with all staff
		if ((j = child_action(path_env, cmd_run, last, 0)) == -1 && !ft_strdl(cmd_run) &&
			!ft_strdl(path_env))
			return (-1);
		ft_strdl(cmd_run);
		ft_strdl(path_env);
		if (j == -5)
			return (-5);
	}
	return (1);
}

int		main(void)
{
	int		status;
	char	*to_parse;
	char	**to_run;

	status = 1;
	to_run = NULL;
	if (ft_get_env(NULL, 0, NULL, 0) == -1)
		exit(1);
	while (status != -5)
	{
		write(1, "{*__*} > ", 9);
		//lets get a full cmd line
		if ((get_next_line(0, &to_parse) == -1 && !err_msg(1, NULL)) || to_parse == NULL)
			continue;
		//split cmds by `;` and return 2d array
		if ((to_run = ft_strsplit(to_parse, ';')) != NULL)
			status = exec_sh(to_run, 0, NULL); //and exec cmd one by one
		else
			err_msg(1, NULL);
		ft_strdl(to_run);
		ft_strdel(&to_parse);
	}
	//SIGNAL CATCH
	exit(1);
}
