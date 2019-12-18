/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:44:14 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/30 14:37:28 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *b;

	if (!(b = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		b->content = NULL;
		b->content_size = 0;
	}
	else
	{
		if (!(b->content = malloc(content_size)))
		{
			free(b);
			b = 0;
			return (NULL);
		}
		ft_memcpy(b->content, content, content_size);
		b->content_size = content_size;
	}
	b->next = NULL;
	return (b);
}
