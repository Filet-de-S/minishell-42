/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:23:53 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/15 15:43:01 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		m;
	char	*b;
	long	cn;
	int		neg;

	neg = 0;
	m = 1;
	cn = n;
	if (n < 0)
		neg++;
	while (n /= 10)
		m++;
	if (!(b = ft_strnew(m + neg)))
		return (NULL);
	if (cn < 0 && (cn = -cn))
		b[0] = '-';
	while (m--)
	{
		b[m + neg] = cn % 10 + '0';
		cn = cn / 10;
	}
	return (b);
}
