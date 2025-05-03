#include "main.h"


char **string_to_words_array(char *line, int *status)
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

	(void)status;
	return (argv);
}
