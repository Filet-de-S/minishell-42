/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:55:06 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/20 16:28:28 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *b;
	t_list *st;
	t_list *t;

	t = lst;
	if (!lst || !f || !(b = f(ft_lstnew(t->content, t->content_size))))
		return (NULL);
	st = b;
	t = t->next;
	while (t)
	{
		if (!(b->next = f(ft_lstnew(t->content, t->content_size))))
		{
			while (b)
			{
				st = b->next;
				free(b);
				b->next = st;
			}
			return (NULL);
		}
		b = b->next;
		t = t->next;
	}
	return (st);
}
