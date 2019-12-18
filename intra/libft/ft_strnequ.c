/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:06:31 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/14 21:26:58 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	if (n > 0 && s1 == s2)
		return (1);
	if (s1 && s2)
		while (*s1 && *s2 && *s1++ == *s2++ && i++ < n)
			if (n == i || (!s1 && !s2))
				return (1);
	return (0);
}
