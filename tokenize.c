#include "shell.h"

/**
 * tokenize - separates a string using a designated delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */

void tokenize(program_data *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = _strlen(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input_line[i] == delimiter[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->exec_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = _strdup(_strtok(data->input_line, delimiter));
	data->first_cmd = _strdup(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = _strdup(_strtok(NULL, delimiter));
	}
}
