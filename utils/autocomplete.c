#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../builtins/builtin.h"

// ---------- helper: check if already in list ----------
static int exists_in_list(char **list, const char *name, int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i], name) == 0)
            return 1;
    }
    return 0;
}

// ---------- generator ----------
static char *command_generator(const char *text, int state)
{
    static char **matches = NULL;
    static int match_count = 0;
    static int index = 0;

    if (!state) {
        // reset
        index = 0;
        match_count = 0;

        if (matches) {
            for (int i = 0; matches[i]; i++)
                free(matches[i]);
            free(matches);
        }

        matches = malloc(sizeof(char *) * 1024);

        int len = strlen(text);

        // 1) builtins
        for (int i = 0; BUILTIN_COMMANDS[i]; i++) {
            if (strncmp(BUILTIN_COMMANDS[i], text, len) == 0) {
                matches[match_count++] = strdup(BUILTIN_COMMANDS[i]);
            }
        }

        // 2) PATH executables
        char *path = getenv("PATH");
        if (path) {
            char *copy = strdup(path);
            char *dir = strtok(copy, ":");

            while (dir) {
                DIR *d = opendir(dir);
                if (d) {
                    struct dirent *entry;
                    while ((entry = readdir(d))) {
                        if (strncmp(entry->d_name, text, len) == 0) {
                            char fullpath[1024];
                            snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, entry->d_name);

                            if (access(fullpath, X_OK) == 0) {
                                if (!exists_in_list(matches, entry->d_name, match_count)) {
                                    matches[match_count++] = strdup(entry->d_name);
                                }
                            }
                        }
                    }
                    closedir(d);
                }
                dir = strtok(NULL, ":");
            }

            free(copy);
        }

        matches[match_count] = NULL;
    }

    if (matches && matches[index]) {
        return strdup(matches[index++]); // readline adds space automatically
    }

    return NULL;
}

// ---------- completion entry point ----------
char **builtin_completion(const char *text, int start, int end)
{
    (void)end;

    // only complete command name (first word)
    if (start != 0)
        return NULL;

    return rl_completion_matches(text, command_generator);
}
