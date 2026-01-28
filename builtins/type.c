#include <stdio.h>
#include <limits.h>
#include "builtin.h"
#include "../utils/utils.h"

int shell_type(char **args)
{
    if (args[1] == NULL) {
        printf("type: missing operand\n");
        return 1;
    }

    char result_path[PATH_MAX];  // allocate buffer

    // Check builtin
    if (is_builtin(args[1])) {
        printf("%s is a shell builtin\n", args[1]);
        return 0;
    }

    // Check external command in PATH
    if (is_exec_in_path(args[1], result_path)) {
        printf("%s is %s\n", args[1], result_path);
        return 0;
    }

    // Not found
    printf("%s: not found\n", args[1]);
    return 1;
}
