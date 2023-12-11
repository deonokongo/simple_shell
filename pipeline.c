#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * run_pipeline - Runs a pipeline of shell commands.
 * @command: The command string containing the pipeline.
 */
void run_pipeline(char *command)
{
	int pipe_fds[2];
	while (*command != '\0')
  {
	  if (pipe(pipe_fds) == -1) 
	  {
		  perror("pipe");
		  exit(EXIT_FAILURE);
	  }
	  pid_t child_pid = fork();
	  
	  if (child_pid == 0)
	  {
		  close(pipe_fds[0]);
		  dup2(pipe_fds[1], STDOUT_FILENO);
		  close(pipe_fds[1]);
		  
		  if (is_builtin(command))
		  {
			  char *args[MAX_ARGS];
			  int arg_count = 0;
			  char *token = strtok(command, " ");
			  
			  while (token != NULL && arg_count < MAX_ARGS - 1)
			  {
				  args[arg_count++] = token;
				  token = strtok(NULL, " ");
			  }
			  args[arg_count] = NULL;
			  execute_builtin(args);
		  }
		  else
		  {
			  execute_process(command, "");
		  }
		  exit(EXIT_SUCCESS);
	  }
	  else if (child_pid > 0)
	  {
		  close(pipe_fds[1]);
		  waitpid(child_pid, NULL, 0);
		  close(pipe_fds[0]);
	  }
	  else
	  {
		  perror("fork");
		  exit(EXIT_FAILURE);
	  }
	  while (*command != '\0' && *command != '|')
	  {
		  command++;
	  }
	  if (*command == '|')
	  {
		  command++;
	  }
  }
}
