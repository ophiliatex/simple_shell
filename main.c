#include "shell.h"

/**
 * main - The entry point of the program
 * @argc: the number of arguments passed to the program
 * @argv: the arguments passed to the program
 * @env: the environment variables
 *
 * Description:
 * Return: The sum of the two parameters
 */
int main(int argc, char *argv[], char *env[])
{
	shell_info_t *info = init_shell_info(env, argv[0], argc, argv);
	int status;

	shell_loop(info);

	status = info->status;

	free_shell_info(info);

	return (status);
}
