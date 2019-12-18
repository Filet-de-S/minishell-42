/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:49:17 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/16 21:27:20 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *n;

	if (!alst || !del)
		return ;
	n = *alst;
	while (*alst)
	{
		n = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = n;
	}
	*alst = NULL;
}
