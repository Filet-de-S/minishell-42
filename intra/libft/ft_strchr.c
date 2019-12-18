/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:09:41 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/28 20:57:08 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == ((unsigned char)c))
			return ((char*)s + i);
	}
	if (!(s[i]) && s[i] == ((unsigned char)c))
		return ((char*)s + i);
	return (NULL);
}
