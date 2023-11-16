#include "shell.h"

/**
 * _strlen - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */

int _strlen(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * _strcmp - Compare two strings
 * @string1: String one, or the shorter
 * @string2: String two, or the longer
 * @number: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */

int _strcmp(char *string1, char *string2, int number)
{
	int checker;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (_strlen(string1) != _strlen(string2))
			return (0);
		for (checker = 0; string1[checker]; checker++)
		{
			if (string1[checker] != string2[checker])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (checker = 0; checker < number ; checker++)
		{
			if (string1[checker] != string2[checker])
			return (0);
		}
		return (1);
	}
}

/**
 * _strdup - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */

char *_strdup(char *string)
{
	char *duplicate;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = _strlen(string) + 1;

	duplicate = malloc(sizeof(char) * length);

	if (duplicate == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		duplicate[i] = string[i];
	}
	return (duplicate);
}

/**
 * str_rev - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */

void str_rev(char *string)
{

	int i = 0, length = _strlen(string) - 1;
	char temp;

	while (i < length)
	{
		temp = string[i];
		string[i++] = string[length];
		string[length--] = temp;
	}
}

/**
 * str_concat - concatenates two strings.
 * @string1: String to be concatenated.
 * @string2: String to be concatenated.
 * Return: a pointer to the array
 */

char *str_concat(char *string1, char *string2)
{
	char *duplicate;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = _strlen(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = _strlen(string2);

	duplicate = malloc(sizeof(char) * (length1 + length2 + 1));
	if (duplicate == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (length1 = 0; string1[length1] != '\0'; length1++)
		duplicate[length1] = string1[length1];
	free(string1);

	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		duplicate[length1] = string2[length2];
		length1++;
	}
	duplicate[length1] = '\0';
	return (duplicate);
}
