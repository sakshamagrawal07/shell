#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shell.h"

void add_redirection(Command *cmd, RedirType type, char *file)
{
    cmd->redirs = realloc(cmd->redirs, sizeof(Redirection) * (cmd->redir_count + 1));

    cmd->redirs[cmd->redir_count].type = type;
    cmd->redirs[cmd->redir_count].file = strdup(file);

    cmd->redir_count++;
}

Command *parse_command(char **tokens)
{
    Command *head = NULL, *tail = NULL;
    int i = 0;

    while (tokens[i])
    {
        // printf("tokens %d : %s\n",i,tokens[i]);
        Command *cmd = calloc(1, sizeof(Command));

        int cap = 8;
        int argc = 0;
        cmd->args = malloc(sizeof(char *) * cap);

        while (tokens[i] && strcmp(tokens[i], "|") != 0)
        {
            // stdout overwrite > or 1>
            if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], "1>") == 0)
            {
                if (tokens[i + 1])
                {
                    add_redirection(cmd, REDIR_OUT, tokens[++i]);
                    i++;
                }
                continue;
            }

            // stdout append >>
            if (strcmp(tokens[i], ">>") == 0 || strcmp(tokens[i], "1>>") == 0)
            {
                if (tokens[i + 1])
                {
                    add_redirection(cmd, REDIR_OUT_APPEND, tokens[++i]);
                    i++;
                }
                continue;
            }

            // stderr overwrite 2>
            if (strcmp(tokens[i], "2>") == 0)
            {
                if (tokens[i + 1])
                {
                    add_redirection(cmd, REDIR_ERR, tokens[++i]);
                    i++;
                }
                continue;
            }

            // stderr append 2>>
            if (strcmp(tokens[i], "2>>") == 0)
            {
                if (tokens[i + 1])
                {
                    add_redirection(cmd, REDIR_ERR_APPEND, tokens[++i]);
                    i++;
                }
                continue;
            }

            if (argc + 1 >= cap)
            {
                cap *= 2;
                cmd->args = realloc(cmd->args, sizeof(char *) * cap);
            }

            cmd->args[argc++] = strdup(tokens[i++]);
        }

        cmd->args[argc] = NULL;

        if (!head)
            head = cmd;
        else
            tail->next = cmd;

        tail = cmd;

        if (tokens[i] && strcmp(tokens[i], "|") == 0)
            i++;
    }

    return head;
}