#include "minishft.h"

int		dollar_exp(int *i, char **to_replace)
{
	char	*var;
	char	*value;
	char    *tmp;
	int		j;
	int		t;

	j = 0;
	t = *i;
	tmp = *to_replace;
	while (tmp[(*i)] != ' ' && tmp[(*i)++])
		j++;
	if ((var = ft_strsub(*to_replace, t + 1, (size_t)j - 1)) == NULL)
	    return (-1);
	value = env_value(var);
	ft_strdel(&var);
	if ((*i = replace_string(to_replace, value, t, j)) == -1)
		return (-1);
	*i = (*i == -2) ? (t - 1) : t;
	return (0);
}

int		tilda_else(struct passwd *user, char **value, char **replace, char **var)
{
    if ((user = getpwnam(*var)) != NULL)
        *value = user->pw_dir;
    else
    {
        if ((*replace)[0] == 'c' && (*replace)[1] == 'd' && (*replace)[2] == ' ')
        {
            if (!(*value = ft_strjoin("cd: ~", *var)) && !err_msg(1, NULL))
                ;
            else
                err_msg(3, *value);
            ft_strdel(value);
            ft_strdel(var);
            return (-1);
        }
        // if echo or else, just continue, as echo ~asddad => ~asddad
        ft_strdel(var);
        return (0);
    }
    return (1);
}

int		tilda_exp(int *i, char **replace, int j, int t)
{
	char			*var;
	char			*value;
	struct passwd	*user;

	while ((*replace)[(*i)] != '\0' && ((*replace)[(*i)] != ' ' && (*replace)[(*i)++] != '/'))
		j++;
	var = NULL;
    value = NULL;
    if (j > 1 && (var = ft_strsub(*replace, t + 1, (size_t)j - 1)) == NULL)
		return (-1);
	if (j == 1)
	{
		if ((value = env_value("HOME=")) == NULL)
		{
			if ((user = getpwuid(geteuid())) != NULL)
				value = user->pw_dir;
			else if (!err_msg(1, NULL))
				return (-1);
		}
	}
	else if ((tilda_else(user = NULL, &value, replace, &var)) == -1)
		return (-1);
	ft_strdel(&var);
	if (value)
	    if ((j = replace_string(replace, value, t, j)) == -1 || j == 0)
	    	return (j);
	*i = t;
    return (1);
}

int		 replace_exp(char **to_replace)
{
    int		i;

    i = -1;
    while ((*to_replace)[++i])
    {
        if (((*to_replace)[i] == '$') &&
            (!((*to_replace)[i + 1]) || (*to_replace)[i + 1] == ' '))
            continue;
        if ((*to_replace)[i] == '$' && dollar_exp(&i, to_replace) == -1)
            return (-1);
        if ((*to_replace)[i] == '~' && tilda_exp(&i, to_replace, 0, i) == -1)
            return (-1);
    }
    return (0);
}
