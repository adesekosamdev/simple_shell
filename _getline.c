#include "shell.h"

/**
 * _getline - reads a line from the prompt.
 * @data: structure for the program's data
 * Return: number of bytes read
 */

int _getline(program_data *data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t numof_bytes_read, i = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		i = 0;
		while (array_commands[i])
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
			i++;
		}

		numof_bytes_read = read(data->file_desc_cmd, &buffer, BUFFER_SIZE - 1);
		if (numof_bytes_read == 0)
			return (-1);

		i = 0;
		do {
			array_commands[i] = _strdup(_strtok(i ? NULL : buffer, "\n;"));
			i = check_log_opers(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}

	data->input_line = array_commands[0];
	i = 0;
	while (array_commands[i])
	{
		array_operators[i] = array_operators[i + 1];
		array_commands[i] = array_commands[i + 1];
		i++;
	}
	return (_strlen(data->input_line));
}
