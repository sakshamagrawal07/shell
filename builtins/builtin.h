#ifndef BUILTIN_H
#define BUILTIN_H

extern const char *BUILTIN_COMMANDS[];

extern const int BUILTIN_COMMANDS_COUNT;

// builtins/*
int shell_echo(char **args);
int shell_type(char **args);
int shell_pwd(char **args);
int shell_cd(char **args);
int shell_exit(char **args);
int shell_history(char **args);

// builtin.c
int is_builtin(char *cmd);
int run_builtin(char **args);

#endif