#include "main.h"

/**
 * str_int - string to integer
 * @s: string
 * Return: 0 if string has no number, else -1
 */
int str_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * error_msg - error msg
 * @struct: structure
 * @errstr: error in string
 * Return: 0 if string has no number, else -1
 */
void error_msg(struct_t *struct, char *errstr)
{
	_eputs(struct->fname);
	_eputs(": ");
	print_d(struct->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(struct->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * dec_int - decimal integer in base 10
 * @input: input
 * @fd: filedescriptor
 *
 * Return: characters
 */
int dec_int(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * con_numb - convert number
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *con_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_com - remove the instance of #
 * @buf: string to modify
 *
 * Return: 0;
 */
void rem_com(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
