#include "minishft.h"
extern char **environ;

int		err_msg(char *e, char *info)
{
	if (e == "mem")
		write(2, "msh: Cannot allocate memory\n", 28);
	else if (e == "nobj")
	{
		write(2, "msh: ", 5);
		write(2, info, ft_strlen(info));
		write(2, ": command not found\n";
	}
	return (0);
}

char	*obj_path(char *needle)
{
	size_t			i;
	char			*path;
	int				j;

	i = -1;
	j = 0;
	while(environ[++i])
		if (ft_strstr(environ[i], "PATH") != NULL)
			break;
	if (environ[i] == NULL)
		return (NULL);
	while (environ[i][j] != '/')
		j++;
	if ((path = search_obj(environ[i][j], needle) == NULL))
		return (NULL);
	return path;
}

int		child_action(int *pid, int *wpid, int *status, char **cmd_run)
{
	char *objpath;

	//get path of objBIN
	if ((objpath = obj_path(cmd_run[0])) == NULL)
		return (-1);
	*pid = fork();
	if (*pid == 0) //if child
	{
		if (execve(objpath, cmd_run, environ))
			perror("execve....: ");
		exit(-1);
	}
	else if (*pid < 0) //if fork problem
	{
		perror("pid < 0 forkiiing:: ");
	}
	else //if parent
	{
		
	}
	return (1);
}

int		exec_sh(char **to_run)
{
	char	**cmd_run;
	int		i;
	int		pid;
	int		wpid;
	int		status;

	i = -1;
	cmd_run = NULL;
	while(to_run[++i])
	{
		//split cmd and args by ` `
		if ((cmd_run = ft_strsplit(to_run[i], ' ')) == NULL && !err_msg("mem", NULL))
			return(1);
		//run cmd with all staff
		if ((child_action(&pid, &wpid, &status, cmd_run)) == -1 && !ft_strdl(cmd_run))
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
		if ((get_next_line(0, &to_parse) == -1 && !err_msg("mem", NULL)) || to_parse == NULL)
			continue;
		//split cmds by `;` and return 2d array
		if ((to_run = ft_strsplit(to_parse, ';')) != NULL)
			status = exec_sh(to_run); //and exec cmd one by one
		else
			err_msg("mem", NULL);
		ft_strdl(to_run);
		ft_strdel(to_parse);
	}
	//SIGNAL CATCH
	return (0);
}
