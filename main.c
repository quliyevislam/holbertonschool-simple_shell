#include "main.h"

int main(void)
{
	char *line = NULL;
	char **argv = NULL;
	size_t buffer_length = 0;
	ssize_t input_length = 0;
	int status = 0;

	while (1)
	{
		line = NULL, argv = NULL;
		input_length = getline(&line, &buffer_length, stdin);
		if (input_length == -1)
		{
			free(line);
			break;
		}
		argv = string_to_words_array(line, &status);
		if (argv == NULL)
		{
			free(argv), free(line);
			continue;
		}
		if (strcmp(argv[0], "env") == 0)
		{
			print_env(), free(line), free(argv);
			continue;
		}
		if (strcmp(argv[0], "exit") == 0)
		{
			free(argv), free(line);
			break;
		}
		argv[0] = search_path_for_command(argv[0], &status);
		if (argv[0] == NULL)
		{
			free(argv), free(line);
			continue;
		}
		status = fork_and_execute(argv), free(argv[0]), free(argv), free(line);
	}
	exit(status);
}
