#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
extern char **environ;
char *get_path(void);
char *search_path_for_command(char *command, int *status);
int fork_and_execute(char **argv);
char **string_to_words_array(char *line, int *status);
void print_env(void);
#endif
