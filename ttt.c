#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int f() {
	pid_t i = fork();
	if (i == 0) {
		printf("imchild\n");
		return(i);
	}
	else if(i < 0)
		printf("pid < 0\n");
	else
	{
		if(waitpid(i, NULL, 0) == -1)
			printf("WAIT ERROR \n");
		printf("PAPA TYT\n");
		return(i);
	}
	return (i);
}

int main() {
	char *s = malloc(44444);
	int i = f();
	if (i == 0)
	{
		printf("childEXIIIIIT\n");
		free(s);
		exit (1);
	}
	else
	{
		printf("BATYA SPIT\n");
        free(s);
        exit (1);
	}
}
// setenv PATH=/Users/kkatelyn/minishell/perm1:/Users/kkatelyn/minishell/perm2:/Users/kkatelyn/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki