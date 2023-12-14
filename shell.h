#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void display_prompt(void);
void get_input_command(char *command, size_t size);
void kide_print(const char *message);
void execute_command(const char *command);

#endif
