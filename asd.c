#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
extern char **environ;

int	 main()
{
	pid_t	pid = fork();
	char *a = "a.out";
	if (pid == 0) //if child
	{
		int status = execve("/usr/local/sbin/a.out", &a, environ);

			//if execve == PERM DENIED – save error, and in case there is no further obj, print error
			// struct? 
		//perror of first name of path
		printf("im CHILD Chaochao %d\n", status);
		exit(-1);
	}
	else if (pid < 0) //if fork problem
	{
		perror("pid < 0 forkiiing:: ");
	}
	else //if paren
	{
		pid_t wpid = waitpid(pid, NULL, 0);
		printf("im parent %d\n", wpid);
	}
}