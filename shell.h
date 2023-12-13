#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "hash_table.h"

struct FileInfo {
  int is_atty;
  int is_open_read;
};

typedef void (*builtin_func)(char **);

struct builtin {
  const char *name;
  builtin_func func;
};

void builtin_exit(char **args);
void builtin_env(char **args);
void builtin_setenv(char **args);
void builtin_unsetenv(char **args);

struct builtin builtins[] = {
  {"exit", builtin_exit},
  {"env", builtin_env},
  {"setenv", builtin_setenv},
  {"unsetenv", builtin_unsetenv},
  {NULL, NULL}
};

#define MAX_TOKENS 256
#define _NFILE 1024
#define BUFFER_SIZE 1024
#define MAX_ARGS 64
#define MAX_COMMANDS 10
#define MAX_LINE_LENGTH 1024
#define HASH_TABLE_SIZE 100

KeyValuePair *alias_table[HASH_TABLE_SIZE];

struct FileInfo _file_table[_NFILE];
FILE *file;


char *prompt(void);
void print_kide(const char *message);
char *my_strtok(char *str, char *delimiter);
int my_fprintf(FILE *stream, const char *format, ...);
int my_getline(char **line, size_t *buffer);
void free_memory(char **argv, char *line, char *found_path);
void remove_newline(char *str);
void execute_command(const char *command);
void execute_process(const char *command, const char *path);
void print_tokens(const char *command);
void copy_string(char *dest, const char *src, size_t max_len);
void custom_exit(int status);
int is_atty(int fd);
int is_open_read(int fd);
int is_interactive_mode(void);
char *search_executable(const char *command, const char *path);
unsigned int hash_function(const char *key);
void hash_table_put(const char *key, const char *value);
void my_redirection(char *command, char *output_file, char *error_file);
char *replace_variable(char *command, const char *variable, const char *value);
void run_pipeline(char *command);
int is_builtin(const char *command);
void execute_builtin(char **args);
int run_shell_from_file(char *filename);
int change_directory(const char *new_dir);
void print_current_directory(void);
void builtin_cd(char **args);
int *create_pipe(void);
void run_single_command(char *command, int write_fd);
void run_pipeline(char *command);
void print_aliases(void);
void print_alias_not_found(const char *alias_name);
void update_alias_table(const char *definition);
int split_pipeline(const char *command, char *commands[MAX_COMMANDS]);
void handle_alias_command(char *argv[]);

#endif

