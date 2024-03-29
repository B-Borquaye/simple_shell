#include "main.h"

/**
 * str_length - string length
 * @s: string
 *
 * Return: integer length of string
 */
int str_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * str_compare - compare strangs.
 * @s1: strang 1
 * @s2: strang 2
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int str_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * strt - starts with haystack
 * @haystack: search with string
 * @needle: find substring
 *
 * Return: next char of haystack or NULL
 */
char *strt(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * str_add - adds two strings
 * @dest: destination
 * @src: source 
 *
 * Return: pointer to destination buffer
 */
char *str_add(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
