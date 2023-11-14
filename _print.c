#include "shell.h"

/**
 * bazzy_print - writes a array of chars in the standard output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */

int bazzy_print(char *string)
{
	return (write(STDOUT_FILENO, string, _strlen(string)));
}

/**
 * _print_err - writes a array of chars in the standard error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */

int _print_err(char *string)
{
	return (write(STDERR_FILENO, string, _strlen(string)));
}

/**
 * _print_error - writes a array of chars in the standard error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */

int _print_error(int errorcode, program_data *data)
{
	char n_as_string[10] = {'\0'};

	num_to_string((long) data->exec_count, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_print_err(data->exec_name);
		_print_err(": ");
		_print_err(n_as_string);
		_print_err(": ");
		_print_err(data->tokens[0]);
		if (errorcode == 2)
			_print_err(": Illegal number: ");
		else
			_print_err(": can't cd to ");
		_print_err(data->tokens[1]);
		_print_err("\n");
	}
	else if (errorcode == 127)
	{
		_print_err(data->exec_name);
		_print_err(": ");
		_print_err(n_as_string);
		_print_err(": ");
		_print_err(data->first_cmd);
		_print_err(": not found\n");
	}
	else if (errorcode == 126)
	{
		_print_err(data->exec_name);
		_print_err(": ");
		_print_err(n_as_string);
		_print_err(": ");
		_print_err(data->first_cmd);
		_print_err(": Permission denied\n");
	}
	return (0);
}
