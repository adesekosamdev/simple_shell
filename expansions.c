#include "shell.h"

/**
 * add_buffer - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */

int add_buffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = _strlen(buffer);

	i = 0;
	while (str_to_add[i])
	{
		buffer[length + i] = str_to_add[i];
		i++;
	}
	buffer[length + i] = '\0';
	return (length + i);
}

/**
 * expand_vars - expands variables
 * @data: a pointer to a struct of the program's data
 * Return: nothing, but sets errno.
 */

void expand_vars(program_data *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	add_buffer(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			num_to_string(errno, expansion, 10);
			add_buffer(line, expansion);
			add_buffer(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			num_to_string(getpid(), expansion, 10);
			add_buffer(line, expansion);
			add_buffer(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = get_env_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			add_buffer(expansion, line + i + j);
			temp ? add_buffer(line, temp) : 1;
			add_buffer(line, expansion);
		}
	if (!_strcmp(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = _strdup(line);
	}
}

/**
 * expand_alias - expands aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */

void expand_alias(program_data *data)
{
	int i, j, expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	add_buffer(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			add_buffer(expansion, line + i + j);
			line[i] = '\0';
			add_buffer(line, temp);
			line[_strlen(line)] = '\0';
			add_buffer(line, expansion);
			expanded = 1;
		}
		break;
	}
	if (expanded)
	{
		free(data->input_line);
		data->input_line = _strdup(line);
	}
}
