#include "main.h"

/**
 * _stradd - add two strings
 * @dest: destination of copied strings
 * @source: source of strings
 * Return: dest
 */
char *_stradd(char *dest, const char *source)
{
	int a;
	int b;

	for (a = 0; dest[a] != '\0'; a++)
		;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[a] = src[b];
		b++;
	}

	dest[a] = '\0';
	return (dest);
}
/**
 * _strcopy - Copies string 
 * @dest: destination of strings
 * @source: source of strings
 * Return: dest.
 */
char *_strcopy(char *dest, char *source)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}
/**
 * _strcompare - compares two strings.
 * @str1: string 1
 * @str2: string 2
 * Return: Always 0.
 */
int _strcompare(char *str1, char *str2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}
/**
 * _strchar - character in a string,
 * @str: string.
 * @c: character.
 * Return: c.
 */
char *_strchar(char *str, char c)
{
	unsigned int i = 0;

	for (; *(str + i) != '\0'; i++)
		if (*(str + i) == c)
			return (str + i);
	if (*(str + i) == c)
		return (str + i);
	return ('\0');
}
/**
 * _strlps - length of prefix substring.
 * @str: string.
 * @acpt: bytes.
 * Return: number of accepted bytes.
 */
int _strlps(char *str, char *acpt)
{
	int i, j, bool;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(acpt + j) != '\0'; j++)
		{
			if (*(str + i) == *(acpt + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}

/**
 * _strdp - duplicates string
 * @str: string
 * Return: duplicated string
 */
char *_strdp(const char *str)
{
	char *new;
	size_t len;

	len = _strlength(str);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcopy(new, str, len + 1);
	return (new);
}

/**
 * _strlength - Returns string length.
 * @str: string
 * Return: Always 0.
 */
int _strlength(const char *str)
{
	int len;

	for (len = 0; str[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * compare_schar - compares characters of strings
 * @str: string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int compare_schar(char str[], const char *delim)
{
	unsigned int a, b, c;

	for (a = 0, c = 0; str[a]; a++)
	{
		for (b = 0; delim[b]; b++)
		{
			if (str[a] == delim[b])
			{
				c++;
				break;
			}
		}
	}
	if (a == c)
		return (1);
	return (0);
}

/**
 * _strsplt - splits a string by some delimiter.
 * @str: string.
 * @delim: delimiter.
 *
 * Return: splitted string.
 */
char *_strsplt(char str[], const char *delim)
{
	static char *spltd, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (compare_schar(str, delim))
			return (NULL);
		spltd = str; 
		i = _strlength(str);
		str_end = &str[i]; 
	}
	str_start = spltd;
	if (str_start == str_end) 
		return (NULL);

	for (bool = 0; *spltd; spltd++)
	{
		if (spltd != str_start)
			if (*spltd && *(spltd - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*spltd == delim[i])
			{
				*spltd = '\0';
				if (spltd == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *spltd) 
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}

/**
 * _isnum - identifies if inputed string is a number
 * @str: string
 * Return: 1 if string is a number, 0 otherwise.
 */
int _isnum(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}

/**
 * str_rev - reverses a string.
 * @str: string.
 * Return: no return.
 */
void str_rev(char *str)
{
	int count = 0, i, j;
	char *s, temp;

	while (count >= 0)
	{
		if (str[count] == '\0')
			break;
		count++;
	}
	s = str;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(s + j);
			*(s + j) = *(s + (j - 1));
			*(s + (j - 1)) = temp;
		}
	}
}
