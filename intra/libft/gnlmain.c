#include <stdio.h>
#include <fcntl.h>
#include "includes/libft.h"
/*
int	main(int ac, char **av)
{
	int fd;
	int hz;
	char *line;

	if (ac < 2)
	{
		printf("usage: add file to read");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		printf("open() failed\n");
		return (1);
	}

	fd = 1;

	while ((hz = get_next_char(fd, &line)) > 0)
	{
		ft_putstr(line);
		ft_putstr("\n");
		free(line);
	}

	if (close(fd) == -1)
	{
		printf("close() failed\n");
		return (1);
	}
	return (0);
}
*/
