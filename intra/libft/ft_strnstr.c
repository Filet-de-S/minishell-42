/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:11:01 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/18 15:03:43 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t b;
	size_t n;
	size_t s;

	n = 0;
	b = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[b] && b < len)
	{
		if (haystack[b] == needle[n])
		{
			i = b;
			s = b;
			while (haystack[s] == needle[n++] && s++ < len)
				if (!(needle[n]))
					return (&((char *)haystack)[i]);
			n = 0;
		}
		b++;
	}
	return (NULL);
}
