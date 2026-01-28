#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int shell_pwd(char **args) {
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    printf("%s\n", cwd);

    return 0;
}