#include "main.h"
/**
* execbuiltincommands - executes a builtin command
* @u_tokens: ..
* Return: 1 if theres a built-in commands, otherwise 0
*/

int execbuiltincommands(char **u_tokens)
{
int i = 0;
char *listbuiltincmds[] = { "exit", "env" };
while (listbuiltincmds[i])
{
if (strcmp(u_tokens[0], listbuiltincmds[i]) == 0)
{
switch (i)
{
case 0:
__attribute__ ((fallthrough));
case 1:
_print_env();
return (1);
default:
break;
}
}
i++;
}
return (0);
}
