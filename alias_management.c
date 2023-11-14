#include "shell.h"

/**
 * print_alias - print aliases
 * @data: structure for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if success, or other number if declared in the arguments
 */

int print_alias(program_data *data, char *alias)
{
	int i, j, len_alias;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		len_alias = _strlen(alias);
		i = 0;
		while ( data->alias_list[i])
		{
			if (!alias || (_strcmp(data->alias_list[i], alias, len_alias)
				&&	data->alias_list[i][len_alias] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				add_buffer(buffer, "'");
				add_buffer(buffer, data->alias_list[i] + j + 1);
				add_buffer(buffer, "'\n");
				bazzy_print(buffer);
			}
			i++;
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: structure for the program's data
 * @name: name of the requested alias.
 * Return: zero if success, or other number if its declared in the arguments
 */

char *get_alias(program_data *data, char *name)
{
	int i, len_alias;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	len_alias = _strlen(name);

	i = 0;
	while ( data->alias_list[i])
	{
		if (_strcmp(name, data->alias_list[i], len_alias) &&
			data->alias_list[i][len_alias] == '=')
		{
			return (data->alias_list[i] + len_alias + 1);
		}
		i++;
	}
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: structure for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */

int set_alias(char *alias_string, program_data *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	for (j = 0; data->alias_list[j]; j++)
		if (_strcmp(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}

	if (temp)
	{
		add_buffer(buffer, "=");
		add_buffer(buffer, temp);
		data->alias_list[j] = _strdup(buffer);
	}
	else
		data->alias_list[j] = _strdup(alias_string);
	return (0);
}
