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

void free_last_command(shell_info_t *pInfo);

/* string.c */
void trim(char *str);
char **split_string(char *str, char *delim);
int strlen_(const char *str);

/* env */
char *get_env_var(shell_info_t *pInfo, const char *string);

/* path */
char **get_path_dirs(shell_info_t *info);
int path_exists(char *path);

/* mem */
char **realloc_char_ptr(char **ptr, size_t newSize);
void *memcpy_(void *dest, const void *src, size_t n);

/* utils */
int isspace_(int c);
#endif
