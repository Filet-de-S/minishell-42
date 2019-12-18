/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:11:11 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/11 14:11:20 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;
	size_t b;

	i = 0;
	b = 0;
	while (s[i])
	{
		if (s[i] == ((unsigned char)c))
			b = i;
		i++;
	}
	if (s[b] == ((unsigned char)c))
		return (&((char *)s)[b]);
	else if (!(s[i]) && s[i] == ((unsigned char)c))
		return (&((char *)s)[i]);
	return (NULL);
}
