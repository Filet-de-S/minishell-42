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
	size_t i;

	i = -1;
	while(environ[++i])
	{
		//strstr(environ, needle);
		// if ok return(i);
	}
	return (-1);
	//index in environ with PATH
}

int		child_action(int *pid, int *wpid, int *status, char **cmd_run)
{
	char *objpath;

	if ((objpath = obj_path(cmd_run[0])) == NULL && !err_msg("nobj", cmd_run[0]))
		return (-1);
	*pid = fork();
	if (*pid == 0)
	{
		if (execve(objpath, cmd_run, environ))
			perror("execve....: ");
		exit(-1);
	}
	else if (*pid < 0)
	{
		perror("pid < 0 forkiiing:: ");
	}
	else
	{
		
	}
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
		if ((cmd_run = ft_strsplit(to_run[i], ' ')) == NULL && !err_msg("mem", NULL))
			return(1);
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
		if ((get_next_line(0, &to_parse) == -1 && !err_msg("mem", NULL)) || to_parse == NULL)
			continue;
		if ((to_run = ft_strsplit(to_parse, ';')) != NULL)
			status = exec_sh(to_run);
		else
			err_msg("mem", NULL);
		ft_strdl(to_run);
		ft_strdel(to_parse);
	}
	//SIGNAL CATCH
	return (0);
}
