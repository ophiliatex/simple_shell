#ifndef SIMPLE_SHELL_SHELL_H
#define SIMPLE_SHELL_SHELL_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 1024

typedef struct node
{
	char *data;
	struct node *next;
} node_t;

typedef struct list
{
	node_t *head;
	node_t *tail;
	size_t size;
} list_t;

/**
 * A shell_info_t struct contains information about the shell.
 */
typedef struct shell_info
{
	int argc;
	char **argv;
	char line[MAXLINE];
	char **args;
	char **envp;
	char *fp;
	list_t *env;
	int status;
} shell_info_t;

/* list */
list_t *init_list(void);

void free_list(list_t *list);

void add_node(list_t *list, char *data);


char **list_to_array(list_t *list);

shell_info_t *init_shell_info(char **env, const char *path, int argc,
							  char **argv);

void free_shell_info(shell_info_t *info);

void parse_line(shell_info_t *info);

size_t getline_(shell_info_t *info);

void execute_command(shell_info_t *info);

void shell_loop(shell_info_t *info);

void free_last_command(shell_info_t *pInfo);

void handle_cmd(shell_info_t *info);

/* string.c */
void trim(char *str);
char **split_string(char *str, char *delim);
int strlen_(const char *str);
int count_words(const char *str, const char *delim, int numwords);
int is_delim(char i, const char *delim);
int strcmp_(const char *s1, const char *s2);
int strncmp_(const char *s1, const char *s2, size_t n);
char *strcat_(char *dest, const char *src);
char *strcpy_(char *dest, const char *src);
char *strdup_(const char *s);
char *itoa_(int num);
int atoi_(const char *str);

void print_error(shell_info_t *info,int fd, char *message, char *index);


/* env */
char *get_env_var(shell_info_t *info, char *var);

void set_env(shell_info_t *info, char *var, char *value);

void unset_env(shell_info_t *info, char *var);

void print_env(shell_info_t *info);


int handle_env(shell_info_t *info);

/* path */
char **get_path_dirs(shell_info_t *info);
int path_exists(char *path);
void get_path(shell_info_t *info);
void check_env_dirs(shell_info_t *info, char **path_dirs);
int check_current_dir(shell_info_t *info);

/* mem */
char **realloc_char_ptr(char **ptr, size_t newSize);
char *realloc_(char *ptr, size_t newSize, size_t oldSize);
void *memcpy_(void *dest, const void *src, size_t n);
void free_char_ptr(char **ptr);

/* utils */
int isspace_(int c);

/* io */
void printf_(char *str, int fd);

/* builtins */
int handle_inbuilt(shell_info_t *info);
int isint(const char *string);
int handle_exit(shell_info_t *info);

/* env_inbuilt */
int handle_print_env(shell_info_t *info);
int handle_set_env(shell_info_t *info);
int handle_unset_env(shell_info_t *info);


#endif
