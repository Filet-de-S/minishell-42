/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:41:21 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/18 20:16:57 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *n;

	n = NULL;
	if (size + 1 == 0)
		return (NULL);
	if (!(n = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(n, 0, size + 1);
	return (n);
}
