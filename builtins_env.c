#include "shell.h"

/**
 * builtin_env - shows the environment where the shell runs
 * @data: structure for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */

int builtin_env(program_data *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		i = 0;
		while (data->tokens[1][i])
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = _strdup(get_env_key(cpname, data));
				if (var_copy != NULL)
					set_env_key(cpname, data->tokens[1] + i + 1, data);
				print_environ(data);
				if (get_env_key(cpname, data) == NULL)
				{
					bazzy_print(data->tokens[1]);
					bazzy_print("\n");
				}
				else
				{
					set_env_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
			i++;
		}
		errno = 2;
		perror(data->first_cmd);
		errno = 127;
	}
	return (0);
}

/**
 * set_builtin_env - set builtin environment
 * @data: structure for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */

int set_builtin_env(program_data *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->first_cmd);
		return (5);
	}
	set_env_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * unset_builtin_env - unset builtin environment
 * @data: structure for the program's data'
 * Return: zero if success, or other number if its declared in the arguments
 */

int unset_builtin_env(program_data *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->first_cmd);
		return (5);
	}
	rm_env_key(data->tokens[1], data);

	return (0);
}
