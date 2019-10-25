#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	 main()
{
	for (int i = 0; i < 2; i++)
	{
		fork();
		printf("%d: myPID is: %d\n", i, (int)getpid());
	}
	sleep(1);
	printf("\n------>myPID is: %d\n", (int)getpid());
}
