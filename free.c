#include "shell.h"

/**
 * free_pointer_array - frees each pointer to an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */

void free_pointer_array(char **array)
{
	int i;

	if (array != NULL)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}

		free(array);
		array = NULL;
	}
}

/**
 * free_req_data - frees the required fields for each loop
 * @data: structure of the program's data
 * Return: Nothing
 */

void free_req_data(program_data *data)
{
	if (data->tokens)
		free_pointer_array(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->first_cmd)
		free(data->first_cmd);

	data->input_line = NULL;
	data->first_cmd = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - frees all field of data
 * @data: structure of the program's data
 * Return: Nothing
 */

void free_all_data(program_data *data)
{
	if (data->file_desc_cmd != 0)
	{
		if (close(data->file_desc_cmd))
			perror(data->exec_name);
	}
	free_req_data(data);
	free_pointer_array(data->env);
	free_pointer_array(data->alias_list);
}
