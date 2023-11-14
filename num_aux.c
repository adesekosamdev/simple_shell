#include "shell.h"

/**
 * num_to_string - converts a long number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @base: base to convert number.
 * Return: Nothing.
 */

void num_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long num = number;
	char letters[] = {"0123456789abcdef"};

	if (num == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (num)
	{
		if (num < 0)
			string[index++] = letters[-(num % base)];
		else
			string[index++] = letters[num % base];
		num /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_rev(string);
}

/**
 * _atoi - converts an ascii string to an integer.
 * @s: pointer to string origin.
 * Return: int of string or 0.
 */

int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_chars - counts the coincidences of character in string.
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 * Return: int of string or 0.
 */

int count_chars(char *string, char *character)
{
	int i = 0, counter = 0;

	while (string[i] != '\0')
	{
		if (string[i] == character[0])
			counter++;
		i++;
	}
	return (counter);
}
