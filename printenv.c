#include "main.h"

/**
* _print_env - prints the environment built in
* Return: nothing
*/

void _print_env(void)
{
int i = 0;
int j = 0;

while (environ[i])
{
while (environ[i][j])
{
putchar(environ[i][j]);
j++;
}
if (j != 0)
putchar('\n');
i++;
}
}
