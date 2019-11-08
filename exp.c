#include "minishft.h"

int		replace_exp(char **to_replace)
{
	int		i;
	int		t;

	i = -1;
	while (*to_replace[++i])
	{
		if ((*to_replace[i] == '$') && 
			(!(*to_replace[i + 1]) || *to_replace[i + 1] == ' '))
			continue;
		if (*to_replace[i] == '$' && dollar_exp(&i, to_replace) == -1)
			return (-1);		
		if (*to_replace[i] == '~' && tilda_exp(&i, to_replace) == -1)
			return (-1);
	}
	return (0);
}

int		dollar_exp(int *i, char **to_replace)
{
	char	*var;
	char	*value;
	int		j;
	int		t;

	j = 0;
	t = *i;
	while (*to_replace[(*i)] != ' ' && *to_replace[(*i)++])
		j++;
	if ((var = ft_strsub(*to_replace, t + 1, (size_t)j - 1)) == NULL)
			return (-1);
	value = env_value(var);
	ft_strdel(&var);
	if (replace_string(to_replace, value, t, j) == -1)
		return (-1);
	*i = t;
	return (0);
}

int		tilda_exp(int *i, char **replace)
{
	char			*var;
	char			*value;
	int				j;
	int				t;
	struct passwd	*user;

	j = 0;
	t = *i;
	user = NULL;
	while (*replace[(*i)] != ' ' && *replace[(*i)] != '/' && *replace[(*i)++])
		j++;
	if (j > 1 && (var = ft_strsub(*replace, t, (size_t)j)) == NULL)
		return (-1);
	if (j == 1)
	{
		if ((value = env_value("HOME")) == NULL)
		{
			if ((user = getpwuid(geteuid())) != NULL)
				value = user->pw_dir;
			else
			{
				err_msg(1, NULL);
				return (-1);
			}
		}
		// j = (value = ~)
		//its you ; go home homie $HOME or   if ((p = getpwuid(uid = geteuid())) == NULL)
		// ~/asdadsada/dir
	}
	else
	{
		//var = ~'........'
		if ((user = getpwnam(&var[1])) != NULL)
			value = user->pw_dir;
		else
		{
			if (*replace[0] == 'c' && *replace[1] == 'd' && *replace == ' ')
			{
				if (!(value = ft_strjoin("cd: ", var)) && !err_msg(1, NULL))
					;
				else
					err_msg(3, value);
				ft_strdel(&value);
				ft_strdel(&var);
				return (-1);
			}
			// if echo or else, just continue, as echo ~asddad => ~asddad
			ft_strdel(&var);
			return (0);
		}
	}
	ft_strdel(&var);
	if (replace_string(replace, value, t, j) == -1)
		return (-1);
	*i = t;
}