#ifndef UTILS_UTLS_H
#define UTILS_UTLS_H

#define MAX_HISTORY 1000

// utils/history.c
extern char *shell_history_list[MAX_HISTORY];
extern int shell_history_count;
extern int shell_history_last_written;

void add_shell_history(const char *line);
void init_history_from_env();
void write_history_to_env();
void append_history_to_env();

void load_history_from_file(const char *path);
void write_history_to_file(const char *path);
void append_history_to_file(const char *path);

// in files.c
int is_exec_in_path(const char *cmd, char *result_path);
void ensure_parent_dir(const char *path);

// autocomplete.c
char **builtin_completion(const char *text, int start, int end);

#endif
