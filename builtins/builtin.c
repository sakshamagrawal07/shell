#include <string.h>
#include "builtin.h"

const char *BUILTIN_COMMANDS[] = {
    "echo",
    "type",
    "pwd",
    "cd",
    "history",
    "exit",
    NULL
};

const int BUILTIN_COMMANDS_COUNT = 6;

int is_builtin(char *cmd) {
    for(int i=0;i<BUILTIN_COMMANDS_COUNT;i++) {
        if(strcmp(cmd, BUILTIN_COMMANDS[i]) == 0) return 1;
    }
    return 0;
    // return (!strcmp(cmd, "echo") ||
    //         !strcmp(cmd, "type") ||
    //         !strcmp(cmd, "pwd") ||
    //         !strcmp(cmd, "cd") ||
    //         !strcmp(cmd, "history") ||
    //         !strcmp(cmd, "exit"));
}

int run_builtin(char **args) {
    if (!strcmp(args[0], "echo")) return shell_echo(args);
    if (!strcmp(args[0], "type")) return shell_type(args);
    if (!strcmp(args[0], "pwd")) return shell_pwd(args);
    if (!strcmp(args[0], "cd")) return shell_cd(args);
    if (!strcmp(args[0], "history")) return shell_history(args);
    if (!strcmp(args[0], "exit")) return shell_exit(args);
    return 0;
}
