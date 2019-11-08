#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int	main() {
	char *s;
	
	if (!(s = malloc(SIZE_MAX)))
		perror("");
	
}