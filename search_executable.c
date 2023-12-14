/**
 * search_executable - Search for an executable file in the specified path.
 * @command: The command to search for.
 * @path: The path to search for the command.
 * Return: A dynamically allocated string containing the full path to the
 *         executable if found, or NULL if not found.
 */
char *search_executable(const char *command, const char *path)
{
        char *token;
        char *path_copy = malloc(strlen(path) + 1);

        if (path_copy == NULL)
        {
                perror("malloc");
                exit(EXIT_FAILURE);
        }

        copy_string(path_copy, path, strlen(path) + 1);
        token = my_strtok(path_copy, ':');

        while (token != NULL)
        {
                char *found_path = malloc(strlen(token) + strlen(command) + 2);

                if (found_path == NULL)
                {
                        perror("malloc");
                        exit(EXIT_FAILURE);
                }

                snprintf(found_path, MAX_PATH, "%s/%s", token, command);

                if (access(found_path, X_OK) == 0)
                {
                        free(path_copy);
                        return found_path;
                }
         return found_path;
                }

                free(found_path);
                token = my_strtok(NULL, ':');
        }

        free(path_copy);
        return (NULL);
}

