#ifndef SIMPLE_SHELL_SHELL_H
#define SIMPLE_SHELL_SHELL_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 1024


/**
 * A shell_info_t struct contains information about the shell.
 */
typedef struct shell_info {
    int argc;
    char **argv;
    char line[MAXLINE];
	char **lines;
    char **args;
	char **env;
} shell_info_t;


shell_info_t *init_shell_info(char **env, const char *path, int argc, char **argv);

void free_shell_info(shell_info_t *info);

void parse_line(shell_info_t *info);

size_t getline_(shell_info_t *info);

void execute_command(shell_info_t *info);

void shell_loop(shell_info_t *info);

/* string.c */
void trim(char *str);


#endif
