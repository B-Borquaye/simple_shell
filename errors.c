#include "main.h"

/**
 * input_str- input string
 * @str: string
 *
 * Return: Nothing
 */
void input_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		input_str(str[i]);
		i++;
	}
}

/**
 * char_std - character to stderr
 * @c: character
 *
 * Return: 1 if correct, else -1.
 */
int char_std(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * char_fd - character to fd
 * @c: character
 * @fd: filedescriptor
 *
 * Return: 1 if correct, else -1.
 */
int char_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * str_fd - input string
 * @str: string
 * @fd: filedescriptor
 *
 * Return: chars
 */
int str_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += str_fd(*str++, fd);
	}
	return (i);
}
