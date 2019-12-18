/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <kkatelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:37:02 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/12/18 16:52:40 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		sl(const char *s, char c, int a)
{
	size_t i;
	size_t r;

	r = 0;
	i = -1;
	if (a == 0)
	{
		while (s[++i])
		{
			while (s[i] != c && s[i++])
				if (s[i] == c || s[i] == '\0')
					r++;
			if ((i - 1 == ((size_t)-1)) || s[i - 1] == '\0')
				break ;
		}
	}
	else
		while (s[++i])
			while (s[i] != c && s[i++])
			{
				r++;
				if (s[i] == c || s[i] == '\0')
					return (r);
			}
	return (r);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**b;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s || !(b = (char**)malloc(sizeof(char*) * (sl(s, c, 0) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			k = 0;
			if (!(b[j] = ft_strnew(sl(s + i, c, 1))) && !ft_strdl(b))
				return (NULL);
			while (s[i] && s[i] != c)
				b[j][k++] = s[i++];
			j++;
		}
		else
			i++;
	}
	b[j] = NULL;
	return (b);
}
