#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int	main() {
	int i;
	if (opendir("/Users/kkatelyn/minishell/libft") == NULL)
		printf("OK");
}