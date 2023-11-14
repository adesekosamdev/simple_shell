#include "shell.h"

/**
 * prompt_loop - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: program data
 */

void prompt_loop(char *prompt, program_data *data)
{
	int error_code = 0;
	int string_len = 0;

	while (++(data->exec_count))
	{
		bazzy_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_vars(data);
			tokenize(data);
			if (data->tokens[0])
			{
				error_code = execute_cmd(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_req_data(data);
		}
	}
}
