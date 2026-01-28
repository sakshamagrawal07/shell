#ifndef SHELL_H
#define SHELL_H

typedef enum
{
    REDIR_OUT,        // >
    REDIR_OUT_APPEND, // >>
    REDIR_ERR,        // 2>
    REDIR_ERR_APPEND  // 2>>
} RedirType;

typedef struct
{
    RedirType type;
    char *file;
} Redirection;

typedef struct Command
{
    char **args;    // command + arguments
    int is_builtin; // 1 if builtin
    // char *input_file;         // < file
    // char *output_file;    // > or 1> file
    // char *error_file;     // 2> file
    // int append;           // >> flag
    struct Command *next; // next command in pipe
    Redirection *redirs;
    int redir_count;
} Command;

#endif