#include "minishft.h"

char	*search_obj(char *env_path, char *needle, int next, int *last)
{
	char	*path;
	char	*bin_p;

	if (!(path = ft_strsplit(env_path, ':')) && !err_msg(1, NULL))
		return (NULL);
	if (*last != 0)
		while (path[++(*last)])
			;
	if (path[next])
	{
		if (!(bin_p = ft_strjoin(path[next], needle)) && !err_msg(1, NULL) && !ft_strdl(path))
			return (NULL);
		if (!access(bin_p, F_OK) && !ft_strdl(path))
			return (bin_p);
	}
	return (NULL);
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
