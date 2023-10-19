#include "main.h"

/**
 * env_check - checks if the variable is an environment variable
 * @h: head of linked list
 * @in: input
 * @data: data structure
 * Return: no return
 */
void env_check(r_variable **h, char *in, data_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlength(_envr[row] + chr + 1);
				add_rvariable_end(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvariable_end(h, j, NULL, 0);
}

/**
 * var_check - check if variable is $$ or $?
 * @h: head of linked list
 * @in: input
 * @st: last status of Shell
 * @data: data structure
 * Return: no return
 */
int var_check(r_variable **h, char *in, char *st, data_shell *data)
{
	int i, lst, lpd;

	lst = _strlength(st);
	lpd = _strlength(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvariable_end(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_rvariable_end(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvariable_end(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvariable_end(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvariable_end(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvariable_end(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvariable_end(h, 0, NULL, 0);
			else
				env_check(h, in + i, data);
		}
	}

	return (i);
}

/**
 * input_replace - replaces string into variables
 * @head: head of the linked list
 * @input: input string
 * @new_input: new string
 * @nlen: new length
 * Return: replaced string
 */
char *input_replace(r_variable **head, char *input, char *new_input, int nlen)
{
	r_variable *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * var_replace - calls functions to replace string into vars
 * @input: input
 * @datastruc: data structure
 * Return: replaced string
 */
char *var_replace(char *input, data_shell *datastruc)
{
	r_variable *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datastruc->status);
	head = NULL;

	olen = check_vars(&head, input, status, datastruc);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = input_replace(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvariable_list(&head);

	return (new_input);
}
