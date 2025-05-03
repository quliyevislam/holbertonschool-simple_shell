#include "main.h"

int fork_and_execute(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		status = execve(argv[0], argv, environ);
	}
	else
	{
		wait(&status);
		return (WEXITSTATUS(status));
	}
	return (status);
}
