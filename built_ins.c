#include "minishft.h"

int		in_echo(char **cmd_run)
{
	int		i;

	i = 1;
	if (!ft_strcmp("-e", cmd_run[1]))
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
	return(1);
}

int		in_setenv(char *cmd_run, int i, char *needle)
{
	char	tmp[80];

	i = -1;
	ft_bzero(&tmp, 80);
	while (cmd_run[++i] && cmd_run[i] != '=')
		tmp[i] = cmd_run[i];
	if (cmd_run[i] != '=')
		return (-1);
	if ((needle = env_value(tmp)) == NULL)
	{
		if (ft_get_env(needle, 0) == -1)
			return (-1);
	}
	else
	{
		i = -1;
		while (environ[++i])
			if ((needle = ft_strstr(environ[i], tmp)) != NULL)
				break;
		free(environ[i]);
		if ((environ[i] = ft_strdup(cmd_run)) == NULL)
			return (-1);
	}
	return(1);
}

int		in_unsetenv(char **cmd_run, int num)
{
	char	*tofree;
	int		i;

	if (!cmd_run[num])
		return (1);
	i = -1;
	while (environ[++i])
		if ((tofree = ft_strstr(environ[i], cmd_run[num])) != NULL)
			break;
	while (environ[i])
	{
		ft_strdel(&environ[i]);
		environ[i] = environ[i + 1];
		i++;
	}
	return (in_unsetenv(cmd_run, ++num));
}

int		in_env(void)
{
	int i;

	i = 0;
	while (environ[i])
		ft_putendl(environ[i++]);
	return (1);
}

int		is_builtin(char *cmd, char **cmd_run)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (-2);
	if (!ft_strcmp(cmd, "echo"))
		return (in_echo(cmd_run));
	else if (!ft_strcmp(cmd, "cd"))
		return(in_cd(cmd_run));
	else if (!ft_strcmp(cmd, "setenv"))
		return(in_setenv(cmd_run[1], 0, NULL));
	else if (!ft_strcmp(cmd, "unsetenv"))
		return(in_unsetenv(cmd_run, 1));
	else if (!ft_strcmp(cmd, "env"))
		return(in_env());
	else if (!ft_strcmp(cmd, "exit"))
		return(in_exit());
	return (-2); //no built-in
}

	//parse for $variable 
	//echo "$PWD         '$PWD'"
	///Users/kkatelyn         '/Users/kkatelyn'
	// echo '$PWD'
	// $PWD
	// -n flag, that's it
	
