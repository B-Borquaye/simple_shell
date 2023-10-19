#include "main.h"

/**
 * rep_char - counts repeated chars
 *
 * @input: string
 * @i: index
 * Return: repetitions
 */
int rep_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (rep_char(input - 1, i + 1));

	return (i);
}

/**
 * synerr_find - finds syntax errors
 *
 * @input: string
 * @i: index
 * @lchar: last character
 * Return: index of error, otherwise 0
 */
int synerr_find(char *input, int i, char lchar)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (synerr_find(input + 1, i + 1, last));

	if (*input == ';')
		if (lchar == '|' || lchar == '&' || lchar == ';')
			return (i);

	if (*input == '|')
	{
		if (lchar == ';' || lchar == '&')
			return (i);

		if (lchar == '|')
		{
			count = rep_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (lchar == ';' || lchar == '|')
			return (i);

		if (lchar == '&')
		{
			count = rep_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (synerr_find(input + 1, i + 1, *input));
}

/**
 * fchar_index - finds index of the first character
 *
 * @input: string
 * @i: index
 * Return: 1 if there is an error, otherwise 0 
 */
int fchar_index(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * synerr_print - prints when a syntax error is found
 *
 * @datastruc: data structure
 * @input: string
 * @i: index of the error
 * @bool: msg control
 * Return: no return
 */
void synerr_print(data_shell *datastruc, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": syntax error: \"";
	msg3 = "\" unknown error\n";
	counter = aux_intstr(datastruc->counter);
	length = _strlength(datastruc->av[0]) + _strlength(counter);
	length += _strlength(msg) + _strlength(msg2) + _strlength(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcopy(error, datastruc->av[0]);
	_stradd(error, ": ");
	_stradd(error, counter);
	_stradd(error, msg2);
	_stradd(error, msg);
	_stradd(error, msg3);
	_stradd(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * synerr_check - checks for syntax error 
 *
 * @datastruc: data structure
 * @input: string
 * Return: 1 if there is an error, otherwise 0
 */
int synerr_check(data_shell *datastruc, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = fchar_index(input, &begin);
	if (f_char == -1)
	{
		synerr_print(datastruc, input, begin, 0);
		return (1);
	}

	i = synerr_find(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		synerr_print(datastruc, input, begin + i, 1);
		return (1);
	}

	return (0);
}
