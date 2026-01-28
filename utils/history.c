#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"

char *shell_history_list[MAX_HISTORY];
int shell_history_count = 0;
int shell_history_last_written = 0;

void add_shell_history(const char *line)
{
    if (shell_history_count >= MAX_HISTORY)
        return;

    shell_history_list[shell_history_count++] = strdup(line);
}

void load_history_from_file(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        perror("history");
        return;
    }

    char line[1024];

    while (fgets(line, sizeof(line), fp))
    {
        // remove newline
        line[strcspn(line, "\n")] = 0;

        // skip empty lines
        if (line[0] == '\0')
            continue;

        add_shell_history(line);
    }

    fclose(fp);
}

void write_history_to_file(const char *path)
{
    FILE *fp = fopen(path, "w");
    if (!fp)
    {
        perror("history");
        return;
    }

    for (int i = 0; i < shell_history_count; i++)
    {
        fprintf(fp, "%s\n", shell_history_list[i]);
    }

    fclose(fp);
}

void append_history_to_file(const char *path)
{
    FILE *fp = fopen(path, "a");
    if (!fp)
    {
        perror("history");
        return;
    }

    for (int i = shell_history_last_written; i < shell_history_count; i++)
    {
        fprintf(fp, "%s\n", shell_history_list[i]);
    }

    shell_history_last_written = shell_history_count;

    fclose(fp);
}

void init_history_from_env()
{
    char *histfile = getenv("HISTFILE");

    if (histfile && histfile[0] != '\0')
    {
        load_history_from_file(histfile);
    }

    shell_history_last_written = shell_history_count;
}

void write_history_to_env()
{
    char *histfile = getenv("HISTFILE");

    if (histfile && histfile[0] != '\0')
    {
        write_history_to_file(histfile);
    }
}

void append_history_to_env()
{
    char *histfile = getenv("HISTFILE");

    if (histfile && histfile[0] != '\0')
    {
        append_history_to_file(histfile);
    }
}