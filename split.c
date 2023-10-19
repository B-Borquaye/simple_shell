#include "main.h"

/**
 * char_swap - swaps | and & for non-printed chars
 * @input: string
 * @bool: type of swap
 * Return: swapped string
 */
char *char_swap(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodes - adds separators and commands to lists
 *
 * @head_sep: head of separator list
 * @head_com: head of command list
 * @input: string
 * Return: no return
 */
void add_nodes(sep_list **head_sep, line_list **head_com, char *input)
{
	int i;
	char *line;

	input = char_swap(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_separator_end(head_sep, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_separator_end(head_sep, input[i]);
			i++;
		}
	}

	line = _strsplt(input, ";|&");
	do {
		line = char_swap(line, 1);
		add_separator_end(head_com, line);
		line = __strsplt(NULL, ";|&");
	} while (line != NULL);

}

/**
 * next_com - go to the next command
 * @list_sep: separator list
 * @list_com: command list
 * @datastruc: data structure
 * Return: no return
 */
void next_com(list_sept **list_sep, line_list **list_com, data_shell *datastruc)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_sep;
	ls_l = *list_com;

	while (ls_s != NULL && loop_sep)
	{
		if (datastruc->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_sep = ls_s;
	*list_com = ls_l;
}

/**
 * split_com - split commands according to the separators
 * @datastruc: data structure
 * @input: string
 * Return: 0 to exit and 1 to continue
 */
int split_com(data_shell *datastruc, char *input)
{

	sep_list *head_sep, *list_sep;
	line_list *head_com, *list_com;
	int loop;

	head_sep = NULL;
	head_com = NULL;

	add_nodes(&head_sep, &head_com, input);

	list_sep = head_sep;
	list_com = head_com;

	while (list_l != NULL)
	{
		datastruc->input = list_com->line;
		datastruc->args = split_input(datastruc->input);
		loop = exect_line(datastruc);
		free(datastruc->args);

		if (loop == 0)
			break;

		next_com(&list_sep, &list_com, datastruc);

		if (list_com != NULL)
			list_com = list_com->next;
	}

	free_separator_list(&head_sep);
	free_line_list(&head_com);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_input - splits input string
 * @input: string.
 * Return: splitted string.
 */
char **split_input(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strsplt(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _rlocatedp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strsplt(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
