#include "main.h"

/**
 * main - entry point
 *
 * Return: nothing.
 */

int main(void)
{
	char *line;
	char **tokens;

	while (true)

	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = hshell_readline();
		tokens = hshell_splitline(line);

		if (tokens[0] != NULL)
		{
			hshell_exec(tokens);
		}
		free(tokens);
		free(line);

	}
}
