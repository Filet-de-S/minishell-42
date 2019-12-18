/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:11:23 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/12 21:52:00 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t b;
	size_t n;
	size_t s;

	n = 0;
	b = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[b])
	{
		if (haystack[b] == needle[n])
		{
			i = b;
			s = b;
			while (haystack[s++] == needle[n++])
				if (!(needle[n]))
					return (&((char *)haystack)[i]);
			n = 0;
		}
		b++;
	}
	return (NULL);
}
