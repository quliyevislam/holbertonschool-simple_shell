#ifndef _SHELL_
#define _SHELL_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int main(void);
char *hshell_readline(void);
char **hshell_splitline(char *line);
void hshell_exec(char **args);
int execbuiltincommands(char **u_tokens);
void _print_env(void);
int _atoi(char *s);



#endif
