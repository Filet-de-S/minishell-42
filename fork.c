#include <stdio.h>
#include <string.h>
#include <unistd.h>
extern char **environ;


int	main() {
	for (int i = 0; environ[i] != 0; i++) {
		printf("%s\n", environ[i]);
	}
}
