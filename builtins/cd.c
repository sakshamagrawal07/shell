#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int shell_cd(char **args) {
    char *path;

    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        // cd with no args → go to HOME
        path = getenv("HOME");
        if (path == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
    } else {
        path = args[1];
    }

    if (chdir(path) == -1) {
        printf("cd: %s: No such file or directory\n", path);
        return 1;
    }

    return 0;
}