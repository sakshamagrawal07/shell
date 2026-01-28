#include <stdio.h>

int shell_echo(char **args) {
    for (int i = 1; args[i]; i++) {
        printf("%s", args[i]);
        if(args[i+1]) {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}
