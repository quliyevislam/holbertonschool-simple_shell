
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

void set(char *buffer, char ***argv)
{
	size_t count = 0;
	size_t i;
	char *arg;
	char *copy = strdup(buffer);
	
	arg = strtok(copy, " \n");
	
	for (count = 0; arg; count++)
		arg = strtok(NULL, " \n");

	free(copy);

	*argv = malloc(sizeof(char *) * (count + 1));

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
	
	if (argv[0] == NULL)
		return;

	pid = fork();

	if(pid == 0)
		execve(argv[0], argv, environ);
	else
		wait(NULL);
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

		set(buffer, &argv);
		execute(argv);

		free(argv);
		free(buffer);
	}

	free(buffer);
	return (0);
}
