/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sfstrjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <kkatelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:49:49 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/12/18 16:53:30 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sfstrjoin(char **s1, char const *s2)
{
	char	*b;
	size_t	i;
	size_t	s;

	if (!s1 || !s2 || !(b = ft_strnew(ft_strlen(*s1) + ft_strlen(s2))))
		return (NULL);
	i = -1;
	s = 0;
	while (s1[0][++i])
		b[i] = s1[0][i];
	while (s2[s])
		b[i++] = s2[s++];
	b[i] = '\0';
	ft_strdel(s1);
	return (b);
}
