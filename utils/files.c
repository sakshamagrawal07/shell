#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <errno.h>


int is_exec_in_path(const char *cmd, char *result_path) {
    char *path_env = getenv("PATH");
    if (!path_env) return 0;

    char *path_copy = strdup(path_env);  // don't modify original PATH
    char *dir = strtok(path_copy, ":");

    while (dir != NULL) {
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);

        // Check if file exists and is executable
        if (access(full_path, X_OK) == 0) {
            if (result_path) {
                strcpy(result_path, full_path);
            }
            free(path_copy);
            return 1; // found executable
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return 0; // not found
}

void ensure_parent_dir(const char *path) {
    char tmp[1024];
    strncpy(tmp, path, sizeof(tmp));
    tmp[sizeof(tmp) - 1] = '\0';

    // Remove filename, keep directory path
    char *p = strrchr(tmp, '/');
    if (!p) return;   // no directory in path
    *p = '\0';        // truncate at last '/'

    // Create directories recursively
    char *dir = tmp;
    for (char *q = tmp + 1; *q; q++) {
        if (*q == '/') {
            *q = '\0';
            mkdir(dir, 0755); // ignore errors (already exists)
            *q = '/';
        }
    }
    mkdir(dir, 0755); // final directory
}
