#include "main.h"

/**
 * repeat - shell occurs more than once
 * @struct: structure
 *
 * Return: 1 if repeats, else 0
 */
int repeat(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * c_delim - checks delimeter
 * @c: character
 * @delim: string delimeter
 * Return: 1 if true, 0 if false
 */
int c_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * c_alpha - checks character with alphabets
 *@c: character
 *Return: if c is an alphabet, return 1 else 0
 */

int c_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *str_int - turns string to integer
 *@s: string
 *Return: if string has no number, return 0 else otherwise
 */

int str_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
