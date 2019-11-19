#include "minishft.h"

int 	in_exit()
{
	ft_putstr("exit\n");
	exit(1);
}

int		cool_cd(char **tmp)
{
	char	*t;

	if ((t = ft_strjoin("OLDPWD=", *tmp)) == NULL && !err_msg(1, *tmp))
	{
		ft_strdel(tmp);
		return (-1);
	}
	ft_strdel(tmp);
	if ((in_setenv(t, 0, NULL)) == -1 && !err_msg(1, *tmp))
	{
		ft_strdel(&t);
		return (-1);
	}
	ft_strdel(&t);
	return (1);
}

int		real_cd(char *path)
{
	char *err;
	char *tmp;

	if ((tmp = getcwd(NULL, 0)) == NULL)
	{
		if ((err = ft_strjoin("msh: cd: ", path)) == NULL)
			return (-1);
		err_msg(5, err);
		ft_strdel(&err);
		return (-1);
	}
	if (chdir(path) == -1)
	{
		if ((err = ft_strjoin("msh: cd: ", path)) == NULL)
			return (-1);
		if ((tmp = ft_strjoin(err, "can't chdir")) == NULL && !ft_strdel(&err))
			return (-1);
		ft_putendl_fd(tmp, 2);
		ft_strdel(&err);
		ft_strdel(&tmp);
		return (-1);
	}
	return (cool_cd(&tmp));
}

int		exec_cd(char *path)
{
	char	*err;
	DIR		*dir;

	if (access(path, F_OK))
	{
		if ((err = ft_strjoin("cd: ", path)) == NULL)
			return (-1);
		err_msg(3, err);
		ft_strdel(&err);
		return (-1);
	}
	else if ((dir = opendir(path)) == NULL)
	{
		if ((err = ft_strjoin("cd: ", path)) == NULL)
			return (-1);
		err_msg(4, err);
		ft_strdel(&err);
		return (-1);
	}
	closedir(dir);
	return(real_cd(path));
}

int		in_cd(char **cmd_run)
{
	char	*path;

	path = cmd_run[1];
	if (!cmd_run[1])
	{
		if ((path = env_value("HOME=")) == NULL)
		{
			ft_putendl("msh: cd: HOME not set");
			return(-1);
		}
	}
	else if (!ft_strcmp(cmd_run[1], "-"))
	{
		if ((path = env_value("OLDPWD=")) == NULL)
		{
			ft_putendl("msh: cd: OLDPWD not set");
			return(-1);
		}
	}
	return (exec_cd(path));
}