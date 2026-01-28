#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"

int shell_history(char **args)
{

    // history -r <file>
    if (args[1] && strcmp(args[1], "-r") == 0 && args[2])
    {
        load_history_from_file(args[2]);
        return 0;
    }

    // history -w <file>
    if (args[1] && strcmp(args[1], "-w") == 0 && args[2])
    {
        write_history_to_file(args[2]);
        return 0;
    }

    // history -a <file>
    if (args[1] && strcmp(args[1], "-a") == 0 && args[2])
    {
        append_history_to_file(args[2]);
        return 0;
    }

    // history [n]
    int count;

    if (args[1] == NULL)
    {
        count = shell_history_count;
    }
    else
    {
        count = atoi(args[1]);
        if (count <= 0)
            count = shell_history_count;
    }

    if (count > shell_history_count)
        count = shell_history_count;

    int start = shell_history_count - count;

    for (int i = start; i < shell_history_count; i++)
    {
        printf("%5d  %s\n", i + 1, shell_history_list[i]);
    }

    return 0;
}