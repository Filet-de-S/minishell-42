#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int	main() {
	struct passwd *p;

//	if((p = getpwuid(geteuid())) == NULL)
	if((p = getpwuid(geteuid())) == NULL)
		perror("erka: ");
	else
	{
	printf("  pw_name  : %s\n",       p->pw_name);
    printf("  pw_uid   : %d\n", (int) p->pw_uid);
    printf("  pw_gid   : %d\n", (int) p->pw_gid);
    printf("  pw_dir   : %s\n",       p->pw_dir);
    printf("  pw_shell : %s\n",       p->pw_shell);
    printf("  pw_pass : %s\n",       p->pw_passwd);
    printf("  pw_*pw_gecos; : %d\n",       p->pw_fields);


	}
	
}