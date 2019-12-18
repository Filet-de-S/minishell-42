/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <kkatelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 10:48:14 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/11/07 20:30:00 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*glist(t_list **left, int fd)
{
	t_list	*tmp;

	tmp = *left;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!(tmp->content = malloc(sizeof(1))))
		return (NULL);
	ft_memcpy(tmp->content, "", 1);
	tmp->content_size = fd;
	tmp->next = NULL;
	ft_lstadd(left, tmp);
	return (tmp);
}

static int		fun(t_list **tmp, char ***line)
{
	size_t	i;
	char	*t1;

	if (!(i = 0) && (!(*tmp)->content))
		return (0);
	while (((char*)(*tmp)->content)[i] && ((char*)(*tmp)->content)[i] != '\n')
		i++;
	if (((char*)(*tmp)->content)[i] != '\n')
		return (0);
	CHECK(**line = ft_strsub((*tmp)->content, 0, i));
	if (((char*)(*tmp)->content)[++i])
	{
		CHECK(t1 = ft_strdup((*tmp)->content + i));
		free((*tmp)->content);
		(*tmp)->content = t1;
	}
	else
	{
		free((*tmp)->content);
		(*tmp)->content = NULL;
	}
	return (1);
}

static int		cic(char **bu, size_t a, t_list **tmp, char **line)
{
	char *tc;

	if ((a + 1) == 0)
		return (-1);
	(*bu)[a] = '\0';
	if (!(*tmp)->content)
	{
		CHECK((*tmp)->content = malloc(sizeof(1)));
		ft_memcpy((*tmp)->content, "", 1);
	}
	SFJN(tc, (*tmp)->content, *bu);
	if ((a = fun(tmp, &line)) != 0)
	{
		free(*bu);
		return ((a + 1) == 0 ? -1 : 1);
	}
	return (0);
}

static int		delme(t_list **left, t_list **tmp, char ***line)
{
	t_list *tmp1;

	**line = ft_strdup((*tmp)->content);
	free((*tmp)->content);
	(*tmp)->content = NULL;
	tmp1 = *left;
	while (tmp1)
	{
		if (tmp1->content)
			break ;
		tmp1 = tmp1->next;
	}
	if (!tmp1)
	{
		free(tmp1);
		tmp1 = NULL;
	}
	return (1);
}

int				get_next_char(const int fd, char **line)
{
	static t_list	*left;
	t_list			*tmp;
	char			*bu;
	size_t			a;

	if (fd < 0 || !line || !(bu = ft_strnew(BUFF_SIZE)))
		return (-1);
	CHECK(tmp = glist(&left, fd));
	if ((a = fun(&tmp, &line)) != 0)
	{
		free(bu);
		return ((a + 1) == 0 ? -1 : 1);
	}
	while ((a = read(1, bu, 1)) != 0)
	{
		write(1, &(*bu), 1);
		if ((a = cic(&bu, a, &tmp, line)) != 0)
			return ((a + 1) == 0 ? -1 : 1);
	}
	free(bu);
	if (tmp->content)
		return ((a = delme(&left, &tmp, &line)));
	return (0);
}
