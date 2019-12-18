/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:33:39 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/18 20:17:23 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*b;
	size_t	i;
	size_t	is;
	size_t	st;
	size_t	e;

	if (!s)
		return (NULL);
	is = 0;
	i = 0;
	while (s[i] && (s[i] == '\n' || s[i] == '\t' || s[i] == ' '))
		i++;
	st = i;
	while (s[i++])
		is++;
	i--;
	while (s[--i] && (s[i] == '\n' || s[i] == '\t' || s[i] == ' '))
		is--;
	if ((!(*s) || i + 1 == 0) && (b = ft_strnew(0)))
		return (b);
	if (!(b = ft_strnew(is)))
		return (NULL);
	while ((e = i) == i && st <= e)
		*b++ = s[st++];
	return (b - is);
}
