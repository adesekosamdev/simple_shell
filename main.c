#include "shell.h"

/**
 * main - starting point of program
 * initializes the variables of the program
 * @argc: number of arguments received from the command line
 * @argv: arguments received from the command line
 * @env: environment variable
 * Return: zero (0) on success.
 */

int main(int argc, char *argv[], char *env[])
{
	program_data new_data_structure = {NULL}, *data = &new_data_structure;
	char *prompt = "";

	init_data(data, argc, argv, env);

	signal(SIGINT, ctrl_c_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_WORD;
	}
	errno = 0;
	prompt_loop(prompt, data);
	return (0);
}
