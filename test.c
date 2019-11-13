#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

void f(int *i)
{
    i[0] = 3;
    i[1] = 0;
}

int	main() {
	int i[2];
    i[0] = 1;
	i[1] = 2;
	f(i);
	printf("i[0] = %d\n i[1] = %d\n", i[0], i[1]);
}