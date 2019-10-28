#include "minishft.h"


char	*search_obj(char **env_path, char *needle)
{
	char	*path;
	int		i;
	char	*bin_p;

	if (!(path = ft_strsplit(*env_path, ':')) && !err_msg("mem", NULL))
		return (NULL);
	i = -1;
	while (path[++i])
	{
		if (!(bin_p = ft_strjoin(path[i], needle)) && !err_msg("mem, NULL"))
			return (NULL);
		if (!access(bin_p, F_OK))
	}
	// if (!(d = opendir(path)))
		// perror("cant open dir::sHH.."); //fix and find errors for MANUAL;
	if pa!err_msg("nobj", cmd_run[0]
}