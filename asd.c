#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
extern char **environ;

int	 main()
{
	write(2, "", 0);
}