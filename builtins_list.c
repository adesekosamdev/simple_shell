#include "shell.h"

/**
 * builtins_list - searches for a match and executes the associated builtin
 * @data: structure for the program's data
 * Return: the return value of the function executed is there is a match
 * otherwise returns -1.
 **/

int builtins_list(program_data *data)
{
	int checker;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", set_builtin_env},
		{"unsetenv", unset_builtin_env},
		{NULL, NULL}
	};

	for (checker = 0; options[checker].builtin != NULL; checker++)
	{
		if (_strcmp(options[checker].builtin, data->first_cmd, 0))
		{
			return (options[checker].function(data));
		}
	}
	return (-1);
}
