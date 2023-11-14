#include "shell.h"

/**
 * get_env_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: structure of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */

char *get_env_key(char *key, program_data *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{
		if (_strcmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			return (data->env[i] + key_len + 1);
		}
	}
	return (NULL);
}

/**
 * set_env_key - overwrites the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: structure of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if success.
 */

int set_env_key(char *key, char *value, program_data *data)
{
	int i, key_len = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{
		if (_strcmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			is_new_key = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = str_concat(_strdup(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * rm_env_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */

int rm_env_key(char *key, program_data *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{
		if (_strcmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			free(data->env[i]);
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * print_environ - prints the current environment
 * @data: structure for the program's data
 * Return: nothing
 */

void print_environ(program_data *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		bazzy_print(data->env[j]);
		bazzy_print("\n");
	}
}
