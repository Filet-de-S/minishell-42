#include "minishft.h"
extern char **environ;

int		err_msg(int st, char *info)
{
	if (st == 1)
		write(2, "msh: Cannot allocate memory\n", 28);
	else
	{
		write(2, "msh: ", 5);
		write(2, info, ft_strlen(info));
		st == 2 ? write(2, ": command not found\n", 20) :
        write(2, ": No such file or directory\n", 20);
	}
	return (0);
}

char	*env_path(void)
{
	size_t	i;
	char	*path;
	int		j;

	i = -1;
	j = 0;
	while(environ[++i])
		if (ft_strstr(environ[i], "PATH") != NULL)
			break;
	if (environ[i] == 0)
		return (NULL);
	while (environ[i][j] != '/')
		j++;
	path = (char *)environ[i][j];
	return (path);
}

int		child_action(char *path_env, char **cmd_run, char *needle, int next)
{
	int		pid;
	int		wpid;
    int     *status;
    char    *path;

    //search bin if (first symbol is'/' then error
	needle[0] == '/' ? (path = needle) : (path = search_obj(path_env, needle, next));
	if (!path)
        return (NULL);
	pid = fork();
	if (pid == 0) //if child
	{
		if ((status = execve(path, cmd_run, environ)) == ;
		needle[0] == '/' ? return(1); : return (child_action(path_env, cmd_run, ++next));

			//if execve == PERM DENIED – save error, and in case there is no further obj, print error
			// struct? 
		//perror of first name of path
		printf("Chaochao %d\n", next);
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
			return (-1); // no path (no env)
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
