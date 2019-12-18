/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:03:45 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/15 21:16:31 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*b;

	if (!s || !(b = ft_strnew(ft_strlen(s))) || !f)
		return (NULL);
	i = -1;
	while (s[++i])
		b[i] = (*f)(i, s[i]);
	return (b);
}
