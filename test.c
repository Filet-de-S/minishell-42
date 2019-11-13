#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    write(2, "Cannot allocate memory\n", 23);

}