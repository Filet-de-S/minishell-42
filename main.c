#include "minishft.h"

int		err_msg(int st, char *info)
{
	write(2, "msh: ", 5);
	if (st == 1)
		write(2, "Cannot allocate memory\n", 23);
	else
	{
		write(2, info, ft_strlen(info));
		if (st == 2)
			write(2, ": command not found\n", 20);
		else if (st == 3)
        	write(2, ": No such file or directory\n", 20);
		else if (st == 4)
			write(2, ": Permsission denied\n", 21);
		else
			write(2, ": can't fork\n", 13);
	}
	return (0);
}

int		child_action(char *path_env, char **cmd_run, char *cmd, int next)
{
	pid_t	pid;
	pid_t	wpid;
    int     status;
	int		last;
    char    *cmd_path;

	//run if built-in
	if ((status = is_builtin(cmd)) > 0)
		return (status);
    //search bin if (first symbol is '/' then error
	last = -1;
	cmd[0] == '/' ? (cmd_path = cmd) : (cmd_path = search_obj(path_env, cmd, next, &last));
	if (!cmd_path)
		return (-1);
	pid = fork();
	if (pid == 0) //if child
	{
		execve(cmd_path, cmd_run, environ);
		if (next == last)
		{
			cmd_path = search_obj(path_env, cmd, 0, 0);
			if (!cmd_path)
				err_msg(4, "");
			else
				err_msg(4, cmd_path);
		}
		else if (last == -1)
			err_msg(4, cmd_path);
		exit(1);
	}
	else if (pid < 0) //if fork problem
		err_msg(5, cmd_path);
	else //if parent
	{
		waitpid()
	}
	return (1);
}

int		exec_sh(char **to_run)
{
	char	**cmd_run;
	int		i;
	int		status;
	char 	*path_env;

	i = -1;
	cmd_run = NULL;
	while(to_run[++i])
	{
		//split cmd and args by ` `
		if ((cmd_run = ft_strsplit(to_run[i], ' ')) == NULL && !err_msg(1, NULL))
			return(1);
		//get path of objBIN
		if ((path_env = env_path()) == NULL && cmd_run[0][0] != '/' &&
		    access(cmd_run[0], F_OK) && !err_msg(3, "env"))
			return (-1); // no path (no env), (2) doesn't start with '/', (3) file is not in this dir 
		//run cmd with all staff
		if ((child_action(path_env, cmd_run, cmd_run[0], 0)) == -1 && !ft_strdl(cmd_run))
			return (1);
		ft_strdl(cmd_run);
	}
	return (1);
}

int		main(int ac, char **av)
{
	int		status;
	char	*to_parse;
	char	**to_run;
	int		gnl;
	
	status = 1;
	to_parse = NULL;
	to_run = NULL;
	gnl = 0;
	while (status)
	{
		write(1, "{*__*} > ", 9);
		//lets get a full cmd line
		if ((get_next_line(0, &to_parse) == -1 && !err_msg(1, NULL)) || to_parse == NULL)
			continue;
		//split cmds by `;` and return 2d array
		if ((to_run = ft_strsplit(to_parse, ';')) != NULL)
			status = exec_sh(to_run); //and exec cmd one by one
		else
			err_msg(1, NULL);
		ft_strdl(to_run);
		ft_strdel(to_parse);
	}
	//SIGNAL CATCH
	return (0);
}
