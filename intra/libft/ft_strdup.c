/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:52:38 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/21 20:32:51 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*b;
	size_t	i;

	i = ft_strlen(s1);
	if (i + 1 == 0)
		return (NULL);
	b = (char*)malloc(sizeof(char) * (i + 1));
	if (b == NULL)
		return (NULL);
	b[i] = '\0';
	i = -1;
	while (s1[++i])
		b[i] = s1[i];
	return (b);
}
