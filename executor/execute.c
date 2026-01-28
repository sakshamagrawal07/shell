#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../include/shell.h"
#include "../builtins/builtin.h"
#include "../utils/utils.h"

typedef struct
{
    int fd;
    int saved_fd;
} FDBackup;

static int apply_redirections(Command *cmd, FDBackup *backups)
{
    int count = 0;

    for (int i = 0; i < cmd->redir_count; i++)
    {
        Redirection *r = &cmd->redirs[i];

        int target_fd;
        int flags = O_CREAT | O_WRONLY;
        mode_t mode = 0644;

        switch (r->type)
        {
        case REDIR_OUT:
            target_fd = STDOUT_FILENO;
            flags |= O_TRUNC;
            break;

        case REDIR_OUT_APPEND:
            target_fd = STDOUT_FILENO;
            flags |= O_APPEND;
            break;

        case REDIR_ERR:
            target_fd = STDERR_FILENO;
            flags |= O_TRUNC;
            break;

        case REDIR_ERR_APPEND:
            target_fd = STDERR_FILENO;
            flags |= O_APPEND;
            break;

        default:
            continue;
        }

        ensure_parent_dir(r->file);

        int fd = open(r->file, flags, mode);
        if (fd < 0)
        {
            perror("open");
            return -1;
        }

        backups[count].fd = target_fd;
        backups[count].saved_fd = dup(target_fd);

        dup2(fd, target_fd);
        close(fd);

        count++;
    }

    return count;
}

static void restore_redirections(FDBackup *backups, int count)
{
    for (int i = 0; i < count; i++)
    {
        dup2(backups[i].saved_fd, backups[i].fd);
        close(backups[i].saved_fd);
    }
}

void execute(Command *cmd)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return;

    FDBackup backups[10]; // supports up to 10 redirections
    int backup_count = apply_redirections(cmd, backups);

    // ===== BUILTINS =====
    if (is_builtin(cmd->args[0]))
    {
        run_builtin(cmd->args);
        restore_redirections(backups, backup_count);
        return;
    }

    // ===== EXTERNAL COMMANDS =====
    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(cmd->args[0], cmd->args);
        fprintf(stderr, "%s: command not found\n", cmd->args[0]);
        _exit(1);
    }

    wait(NULL);
    restore_redirections(backups, backup_count);
}
