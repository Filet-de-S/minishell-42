#include "minishft.h"

char	*search_obj(char *env_path, char *needle, int next)
{
	char	*path;
	char	*bin_p;

	if (!(path = ft_strsplit(env_path, ':')) && !err_msg(1, NULL))
		return (NULL);
	while (path[next])
	{
		if (!(bin_p = ft_strjoin(path[next], needle)) && !err_msg(1, NULL) && !ft_strdl(path))
			return (NULL);
		if (!access(bin_p, F_OK) && !ft_strdl(path))
			return (bin_p);
	}
	return (NULL);
}