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

struct FileInfo {
    int is_atty;
    int is_open_read;
};
typedef void (*builtin_func)(char **args);

struct builtin {
    char *name;
    builtin_func func;
};
typedef struct KeyValuePair {
    char *key;
    char *value;
    struct KeyValuePair *next;
} KeyValuePair;

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
#define MAX_LINE_LENGTH 1024


#define HASH_TABLE_SIZE 100

KeyValuePair *hash_table[HASH_TABLE_SIZE];
struct FileInfo _file_table[_NFILE];
FILE *file;

void prompt(void);
void print_kide(const char *message);
int my_getline(char **line, size_t *buffer);
void free_memory(char **argv);
void remove_newline(char *str);
void execute_process(const char *command, const char *path);
void print_tokens(const char *command);
void copy_string(char *dest, const char *src);
void custom_exit(int status);
int is_atty(int fd);
int is_open_read(int fd);
int is_interactive_mode(void);
char *search_executable(const char *command, const char *path);
void builtin_exit(char **args);
void builtin_env(char **args);
void builtin_setenv(char **args);
void builtin_unsetenv(char **args);
unsigned int hash_function(const char *key);
void hash_table_put(const char *key, const char *value);
void print_all_aliases();
void builtin_alias(char *argv[]);
void my_redirection(char *command, char *output_file, char *error_file);
char *replace_variable(char *command, const char *variable, const char *value) ‘
void run_pipeline(char *command);
int run_shell_from_file(char *filename) ;

#endif
