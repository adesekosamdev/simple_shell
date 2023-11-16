#include "shell.h"

/**
 * execute_cmd - executes a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If success returns zero, otherwise, return -1.
 */

int execute_cmd(program_data *data)
{
	int get_val = 0, status;
	pid_t pidd;

	get_val = builtins_list(data);
	if (get_val != -1)
		return (get_val);

	get_val = find_program(data);
	if (get_val)
	{
		return (get_val);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->first_cmd);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			get_val = execve(data->tokens[0], data->tokens, data->env);
			if (get_val == -1)
				perror(data->first_cmd), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
