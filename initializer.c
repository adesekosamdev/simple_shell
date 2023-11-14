#include "shell.h"

/**
 * init_data - initializes the data structure
 * with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */

void init_data(program_data *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->exec_name = argv[0];
	data->input_line = NULL;
	data->first_cmd = NULL;
	data->exec_count = 0;
	if (argc == 1)
		data->file_desc_cmd = STDIN_FILENO;
	else
	{
		data->file_desc_cmd = open(argv[1], O_RDONLY);
		if (data->file_desc_cmd == -1)
		{
			_print_err(data->exec_name);
			_print_err(": 0: Can't open ");
			_print_err(argv[1]);
			_print_err("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = _strdup(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
