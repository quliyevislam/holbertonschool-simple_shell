#include "main.h"

char *get_path(void)
{
	char **env = environ;
	char *path = NULL;

	if (env == NULL)
		return (NULL);
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
