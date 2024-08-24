#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;


char *get_path(void)
{
        char **env = environ;
        char *path = NULL;

        while (*env != NULL)
        {
                if (strncmp(*env, "PATH=", 5) == 0)
                {
                        path = *env + 5;
                        return (path);
                }

                env++;
        }
        return (NULL);
}



char *get_full_path(char *arg)
{

        char *PATH;
        char *dir;
        char *full_path;

        if (get_path() == NULL)
        {
                printf("path not foun\n");
                return (NULL);
        }

        PATH = strdup(get_path());

        if (access(arg, F_OK) == 0)
        {
                full_path = malloc(strlen(arg) + 1);
                strcpy(full_path, arg);
                free(PATH);
                return (full_path);
        }

        dir = strtok(PATH, ":");

        while (dir)
        {
                full_path = malloc(strlen(dir) + strlen(arg) + 2);

                strcpy(full_path, dir);
                strcat(full_path, "/");
                strcat(full_path, arg);

                if (access(full_path, F_OK) == 0)
                {
                        free(PATH);
                        return (full_path);
                }
                free(full_path);
                dir = strtok(NULL, ":");
        }

	fprintf(stderr, "./hsh: 1: %s: not found\n", arg);
        free(PATH);
	exit(127);
        return (NULL);
}



void set_argv(char *buffer, char ***argv)
{
	size_t argc;
	size_t i;
	char *arg;
	char *copy = strdup(buffer);
	
	arg = strtok(copy, " \n");
	
	for (argc = 0; arg; argc++)
		arg = strtok(NULL, " \n");

	free(copy);

	*argv = malloc(sizeof(char *) * (argc + 1));

	arg = strtok(buffer, " \n");

	for(i = 0; arg; i++)
	{
		(*argv)[i] = arg;
		arg = strtok(NULL, " \n");
	}

		(*argv)[i]= NULL;
}

void execute(char **argv)
{
	pid_t pid;
	char *command;
	
	if (argv[0] == NULL)
		return;
	
	command = get_full_path(argv[0]);

	if (command == NULL)
		return;

	pid = fork();

	if(pid == 0)
		execve(command, argv, environ);
	else
	{
		wait(NULL);
		free(command);
	}
}

int main(void)
{
	char *buffer;
	char **argv;
	size_t size;
	ssize_t read;

	while (1)
	{
		buffer = NULL;
		size = 0;
		read = getline(&buffer, &size, stdin);
	
		if (read == -1)
			break;

		set_argv(buffer, &argv);
		execute(argv);

		free(argv);
		free(buffer);
	}

	free(buffer);

	return (0);
}
