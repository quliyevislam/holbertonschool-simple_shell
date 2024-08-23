#include "main.h"

/**
 * _feof - thefunctin name
 *
 * @stream: file stream
 *
 * Return: 1 or 0
 */
int _feof(FILE *stream)
{
	return (stream->_flags & _IO_EOF_SEEN);
}


/**
 * hshell_readline - uses getline to read a line
 *
 * Return: the line
 */
char *hshell_readline(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (_feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(line);
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}
