#include "shell.h"

/**
 * builtin_exit - exit point of the program with the status
 * @data: structure for the program's data
 * Return: zero if success, or other number if declared in the arguments
 */

int builtin_exit(program_data *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		i = 0;
		while (data->tokens[1][i])
		{
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
			i++;
		}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - changes the current directory
 * @data: structure for the program's data
 * Return: zero if success, or other number if declared in the arguments
 */

int builtin_cd(program_data *data)
{
	char *home_dir = get_env_key("HOME", data), *old_dir = NULL;
	char old_dir_[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (_strcmp(data->tokens[1], "-", 0))
		{
			old_dir = get_env_key("OLDPWD", data);
			if (old_dir)
				error_code = set_working_directory(data, old_dir);
			bazzy_print(get_env_key("PWD", data));
			bazzy_print("\n");

			return (error_code);
		}
		else
		{
			return (set_working_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(old_dir_, 128);

		return (set_working_directory(data, home_dir));
	}
	return (0);
}

/**
 * set_working_directory - sets the working directory
 * @data: structure for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if success, or other number if its declared in the arguments
 */

int set_working_directory(program_data *data, char *new_dir)
{
	char old_dir_[128] = {0};
	int error_code = 0;

	getcwd(old_dir_, 128);

	if (!_strcmp(old_dir_, new_dir, 0))
	{
		error_code = chdir(new_dir);
		if (error_code == -1)
		{
			errno = 2;
			return (3);
		}
		set_env_key("PWD", new_dir, data);
	}
	set_env_key("OLDPWD", old_dir_, data);
	return (0);
}

/**
 * builtin_alias - adds, removes or show aliases
 * @data: structure for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */

int builtin_alias(program_data *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (count_chars(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}

/**
 * builtin_help - shows the environment where the shell currently runs
 * @data: structure for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */

int builtin_help(program_data *data)
{
	int i, length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		bazzy_print(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->first_cmd);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;

	i = 0;
	while (messages[i])
	{
		length = _strlen(data->tokens[1]);
		if (_strcmp(data->tokens[1], messages[i], length))
		{
			bazzy_print(messages[i] + length + 1);
			return (1);
		}
		i++;
	}
	errno = EINVAL;
	perror(data->first_cmd);
	return (0);
}
