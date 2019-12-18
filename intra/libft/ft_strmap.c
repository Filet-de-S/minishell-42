/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 18:47:17 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/15 21:16:16 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*b;
	size_t	i;

	if (!s || !(b = ft_strnew(ft_strlen(s))) || !f)
		return (NULL);
	i = 0;
	while (*s)
		b[i++] = (*f)(*s++);
	return (b);
}
