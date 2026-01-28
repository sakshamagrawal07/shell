#include <stdlib.h>
#include <stdio.h>
#include "builtin.h"

int shell_exit(char **args) {
    int status = 0;

    // Handle: exit <code>
    if (args[1] != NULL) {
        status = atoi(args[1]);  // convert string to int
    }

    // TODO: future cleanup (history, jobs, memory, etc.)

    exit(status);
}
