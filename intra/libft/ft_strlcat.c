/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:10:04 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/12 15:06:14 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t ll;

	ll = ft_strlen(dst) + ft_strlen(src);
	i = 0;
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	while (*dst)
		dst++;
	while (*src && i < size - (ll - ft_strlen(src - i)) - 1)
	{
		i++;
		*dst++ = *src++;
	}
	*dst = '\0';
	return (ll);
}
