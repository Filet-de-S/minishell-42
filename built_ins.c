#include "minishft.h"

int		is_builtin(char *cmd, char **cmd_run)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (-2);
	if (!ft_strcmp(cmd, "echo"))
		return (in_echo(cmd_run));
	else if (!ft_strcmp(cmd, "cd"))
		return(in_cd(cmd_run));
	else if (!ft_strcmp(cmd, "setenv"))
		return(in_setenv(cmd_run));
	else if (!ft_strcmp(cmd, "unsetenv"))
		return(in_unsetenv(cmd_run));
	else if (!ft_strcmp(cmd, "env"))
		return(in_env(cmd_run));
	else if (!ft_strcmp(cmd, "exit"))
		return(in_exit(cmd_run));
	return (-2); //no built-in
}

int		in_echo(char **cmd_run)
{
	char *out; 

	while 
	//parse for $variable 
	//echo "$PWD         '$PWD'"
	///Users/kkatelyn         '/Users/kkatelyn'
	// echo '$PWD'
	// $PWD
	// -n flag, that's it
	
}
