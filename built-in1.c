#include "main.h"

/**
 * cmd_hist - shows the history list
 *
 * @struct: Structure
 * 
 *  Return: 0
 */
int cmd_hist(struct_t *struct)
{
	print_list(struct->history);
	return (0);
}

/**
 * s_alias - alias to string
 * @struct: structructure
 * @str: string
 *
 * Return: 0 if correct, else return 1
 */
int s_alias(struct_t *struct, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(struct->alias),
		get_node_index(struct->alias, node_starts_with(struct->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * alias_str - alias to string
 * @struct: structure
 * @str: string 
 *
 * Return: 0 if correct, else return 1
 */
int alias_str(struct_t *struct, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (s_alias(struct, str));

	s_alias(struct, str);
	return (add_node_end(&(struct->alias), str, 0) == NULL);
}

/**
 * p_alias - prints alias string
 * @alias_node: alias node
 *
 * Return: 0 if correct, else return 1
 */
int p_alias(list_t *alias_node)
{
	char *p = NULL, *a = NULL;

	if (alias_node)
	{
		p = _strchr(alias_node->str, '=');
		for (a = alias_node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * blt_alias - alias builtin
 * @struct: Structure 
 * 
 * Return: Always 0
 */
int blt_alias(struct_t *struct)
{
	int i = 0;
	char *p = NULL;
	list_t *alias_node = NULL;

	if (struct->argc == 1)
	{
		alias_node = struct->alias;
		while (alias_node)
		{
			p_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; struct->argv[i]; i++)
	{
		p = _strchr(struct->argv[i], '=');
		if (p)
			alias_str(struct, struct->argv[i]);
		else
			print_alias(node_starts_with(struct->alias, struct->argv[i], '='));
	}

	return (0);
}
