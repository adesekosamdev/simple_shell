#include "shell.h"

/**
* check_log_opers - checks and split for && and || logic operators
* @array_commands: array of the commands.
* @i: index in the array of commands to be checked
* @array_operators: array of the logical operators for each previous command
* Return: index of the last command in the array_commands.
*/

int check_log_opers(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int j;

	for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
	{
		if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		{
			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = _strdup(array_commands[i]);
			array_commands[i + 1] = _strdup(temp + j + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{
			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = _strdup(array_commands[i]);
			array_commands[i + 1] = _strdup(temp + j + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
