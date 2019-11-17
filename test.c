#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

void    func(char **test) {
    printf("dline = %d\n", strlen(*test));
    for (int i = 0; i < strlen(*test); ++i) {
        printf("i = %d %c\n", i, (*test)[i]);
    }
    free(*test);
    if ((*test = strdup("asd")) == NULL)
        printf("NULLLLLLL");
    printf("1.5 test from func: %s\n", *test);
}

int main() {
    char a[80];
    bzero(a, 80);
    strcpy(a, "\033[1;35masd");
    printf("%s\n, %d", a, strlen(a));


//    char **test = (char**)malloc(sizeof(char*) * 2);
//    test[1] = 0;
//    test[0] = strdup("koniawk");
//    printf("1 test[0] %s\n", test[0]);
//    func(&test[0]);
//    //printf("2 test[1] %s\n", test[1]);
//    printf("2 test[0] %s\n", test[0]);
 }