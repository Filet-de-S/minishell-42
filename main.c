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
			write(2, ": Command not found\n", 20);
		else if (st == 3)
        	write(2, ": No such file or directory\n", 28);
		else if (st == 4)
			write(2, ": Permission denied\n", 20);
		else
			write(2, ": Can't fork\n", 13);
	}
	return (0);
}

int		child_action(char *path_env, char **cmd_run, int **last, int next)
{
	pid_t	pid;
    int     status;
    char    *cmd_path;

	//run if built-in
	if ((cmd_run[0][0] != '/' && (cmd_run[0][0] != '.')) && 
		(status = is_builtin(cmd_run[0], cmd_run)) >= -1)
		return (status);
    //search bin if (first symbol is '/' then error

	if (cmd_run[0][0] == '/' || (cmd_run[0][0] == '.' && cmd_run[0][1] == '/'))
	{
		if (access((cmd_path = cmd_run[0]), F_OK) && !err_msg(3, cmd_path))
			return (-1);
	}
	else if ((cmd_path = search_obj(path_env, cmd_run[0], &next, &last)) == NULL)
	{
		// if path's dir is not ended and malloc error and it's parent
		//    or PATH is empty for bin and it;s parent
		if (*last[1] == 0 || (*last[1] == -1 && !err_msg(2, cmd_path)))
			return (-1);
		else
		{
			cmd_path = search_obj(path_env, cmd_run[0], 0, 0);
			cmd_path == NULL ? err_msg(4, "couldn't malloc cmd name") : err_msg(4, cmd_path);
			ft_strdel(&cmd_path);
			exit(1);
		}
	}
	pid = fork();
	*last[1]++;
	if (pid == 0) //if child
	{
		execve(cmd_path, cmd_run, environ);
		if (*last[0] == -1) // if bin is not from search_obj
			err_msg(4, cmd_path);
		else// if (next != last && last != -1)
			child_action(path_env, cmd_run, last, ++next);
		exit(1);
	}
	else if (pid < 0) //if fork problem
		err_msg(5, cmd_path);
	//if parent
	else if(waitpid(pid, NULL, 0) == -1)
		write(2, "msh: waitpid error *_*\n", 23);
	return (1);
}

int		exec_sh(char **to_run)
{
	char	**cmd_run;
	int		i;
	int		status;
	char 	*path_env;
	int		last[2];

	i = -1;
	cmd_run = NULL;
	while(to_run[++i])
	{
		last[0] = -1;
		last[1] = 0;
		//split cmd and args by ` `
		if ((cmd_run = ft_strsplit(to_run[i], ' ')) == NULL && !err_msg(1, NULL))
			return(1);
		//get path of objBIN
		if ((path_env = env_path("PATH")) == NULL && cmd_run[0][0] != '/' &&
		    access(cmd_run[0], F_OK) && !err_msg(3, "env"))
			return (-1); // no path (no env), (2) doesn't start with '/', (3) file is not in this dir 
		//run cmd with all staff
		if ((child_action(path_env, cmd_run, last, 0)) == -1 && !ft_strdl(cmd_run))
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
	
	status = 1;
	to_parse = NULL;
	to_run = NULL;
	if (get_env() == -1)
		exit(1);
	while (status)
	{
		write(1, "{*__*} > ", 9);
		//lets get a full cmd line
		if ((get_next_char(1, &to_parse) == -1 && !err_msg(1, NULL)) || to_parse == NULL)
			continue;
		//split cmds by `;` and return 2d array
		if (replace_symbols(&to_parse) != -1 &&
			(to_run = ft_strsplit(to_parse, ';')) != NULL)
			status = exec_sh(to_run); //and exec cmd one by one
		else
			err_msg(1, NULL);
		ft_strdl(to_run);
		ft_strdel(to_parse);
	}
	//SIGNAL CATCH
	return (0);
}
