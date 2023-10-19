#include "main.h"

/**
 * rem_comment - removes comments from the input
 *
 * @input: string
 * Return: input with no comments
 */
char *rem_comment(char *input)
{
	int a, up_to;

	up_to = 0;
	for (a = 0; input[a]; a++)
	{
		if (input[a] == '#')
		{
			if (a == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[a - 1] == ' ' || input[a - 1] == '\t' || input[a - 1] == ';')
				up_to = a;
		}
	}

	if (up_to != 0)
	{
		input = _rlocate(input, a, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

/**
 * loop - Loops the shell
 * @datastruc: input
 *
 * Return: no return.
 */
void loop(data_shell *datastruc)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = rem_comment(input);
			if (input == NULL)
				continue;

			if (synerr_check(datastruc, input) == 1)
			{
				datastruc->status = 2;
				free(input);
				continue;
			}
			input = var_replace(input, datastruc);
			loop = split_com(datastruc, input);
			datastruc->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * ext_shell - exit shell
 *
 * @datastruc: data structure
 * Return: 0.
 */
int ext_shell(data_shell *datastruc)
{
	unsigned int ustatus;
	int is_digit;
	int str_length;
	int big_number;

	if (datastruc->args[1] != NULL)
	{
		ustatus = _atoi(datastruc->args[1]);
		is_digit = _isnum(datastruc->args[1]);
		str_length = _strlength(datastruc->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_length > 10 || big_number)
		{
			get_err(datastruc, 2);
			datastruc->status = 2;
			return (1);
		}
		datastruc->status = (ustatus % 256);
	}
	return (0);
}
