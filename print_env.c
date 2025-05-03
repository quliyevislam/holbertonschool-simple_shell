#include "main.h"

void print_env(void)
{
	size_t i = 0;

	for (i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
}
