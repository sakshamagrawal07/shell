#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../executor/execute.h"
#include "../utils/utils.h"

void init_readline()
{
    rl_attempted_completion_function = builtin_completion;
}

void shell_loop()
{
    init_history_from_env();

    init_readline();

    while (1)
    {
        char *input = readline("$ ");

        if (!input) {
            printf("\n");
            break;
        }

        if (*input) {
            add_history(input);        // readline history (up and down arrow)
            add_shell_history(input);  // your shell history builtin
        }

        char **tokens = tokenize(input);
        Command *cmd = parse_command(tokens);

        if(strcmp(cmd->args[0],"exit") == 0) break;

        if (cmd->next)
            execute_pipeline(cmd);
        else
            execute(cmd);

        free(input);
    }

    write_history_to_env();
}
