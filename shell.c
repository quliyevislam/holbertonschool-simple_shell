#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "main.h"

void fork_and_execute(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, environ);
	}
	else
	{
		wait(&status);
	}
}

char **string_to_words_array(char *line)
{
	char *line_copy = NULL;
	char **argv = NULL;
	char *arg = NULL;
	size_t argc = 0;
	size_t i = 0;

	line_copy = strdup(line);
	arg = strtok(line_copy, " \n");
	while (arg)
	{
		argc++;
		arg = strtok(NULL, " \n");
	}
	free(line_copy);

	if (argc == 0)
	{
		return (NULL);
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	arg = strtok(line, " \n");
	for (i = 0; i < argc; i++)
	{
		*(argv + i) = arg;
		arg = strtok(NULL, " \n");
	}
	argv[i] = NULL;
	return (argv);
}

int main(void)
{
	char *line = NULL;
	char **argv = NULL;
	size_t buffer_length = 0;
	ssize_t input_length = 0;

	while (1)
	{
		line = NULL;
		argv = NULL;
		input_length = getline(&line, &buffer_length, stdin);

		if (input_length == -1)
		{
			free(line);
			break;
		}
		argv = string_to_words_array(line);
		if (argv == NULL)
		{
			free(argv);
			free(line);
			continue;
		}
		fork_and_execute(argv);

		free(argv);
		free(line);
	}
	return (0);
}
