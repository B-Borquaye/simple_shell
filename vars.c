#include "main.h"

/**
 * chain_del - chain delimeter
 * @struct: structure
 * @buf: buffer
 * @p: current position
 *
 * Return: chain delimeter if 1, else 0 
 */
int chain_del(struct_t *struct, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		struct->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		struct->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		struct->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chk_chain - checks chain status
 * @struct: structure
 * @buf: buffer
 * @p: current position
 * @i: starting position
 * @len: length
 *
 * Return: Void
 */
void chk_chain(struct_t *struct, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (struct->cmd_buf_type == CMD_AND)
	{
		if (struct->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (struct->cmd_buf_type == CMD_OR)
	{
		if (!struct->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * rep_alias - replace alias
 * @struct: structure
 *
 * Return: if replaced return 1, else 0
 */
int rep_alias(struct_t *struct)
{
	int i;
	list_t *alias_node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		alias_node = node_starts_with(struct->alias, struct->argv[0], '=');
		if (!alias_node)
			return (0);
		free(struct->argv[0]);
		p = _strchr(alias_node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		struct->argv[0] = p;
	}
	return (1);
}

/**
 * rep_var - replace variable
 * @struct: structure
 *
 * Return: 1 if replaced, else 0
 */
int rep_var(struct_t *struct)
{
	int i = 0;
	list_t *alias_node;

	for (i = 0; struct->argv[i]; i++)
	{
		if (struct->argv[i][0] != '$' || !struct->argv[i][1])
			continue;

		if (!_strcmp(struct->argv[i], "$?"))
		{
			rep_str(&(struct->argv[i]),
				_strdup(convert_number(struct->status, 10, 0)));
			continue;
		}
		if (!_strcmp(struct->argv[i], "$$"))
		{
			rep_str(&(struct->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		alias_node = node_starts_with(struct->env, &struct->argv[i][1], '=');
		if (alias_node)
		{
			rep_str(&(struct->argv[i]),
				_strdup(_strchr(alias_node->str, '=') + 1));
			continue;
		}
		rep_str(&struct->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * rep_str - replace string
 * @old: old string
 * @new: new string
 *
 * Return: if replaced return 1, else 0
 */
int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
