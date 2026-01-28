#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "../builtins/builtin.h"
#include "../include/shell.h"

void execute_pipeline(Command *cmd)
{
    int prev_fd = -1;
    int pipefd[2];
    pid_t pid;

    Command *curr = cmd;

    while (curr)
    {
        int has_next = (curr->next != NULL);

        if (has_next)
        {
            if (pipe(pipefd) < 0)
            {
                perror("pipe");
                return;
            }
        }

        pid = fork();

        if (pid == 0)
        {
            // ===== CHILD PROCESS =====

            // input from previous pipe
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // output to next pipe
            if (has_next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }

            // BUILTIN INSIDE PIPELINE
            if (is_builtin(curr->args[0]))
            {
                run_builtin(curr->args);
                exit(0);
            }

            // EXTERNAL COMMAND
            execvp(curr->args[0], curr->args);
            perror(curr->args[0]);
            exit(1);
        }
        else if (pid < 0)
        {
            perror("fork");
            return;
        }

        // ===== PARENT PROCESS =====

        if (prev_fd != -1)
            close(prev_fd);

        if (has_next)
        {
            close(pipefd[1]);     // parent closes write end
            prev_fd = pipefd[0];  // next command reads from here
        }

        curr = curr->next;
    }

    // wait for all children
    while (wait(NULL) > 0);
}
