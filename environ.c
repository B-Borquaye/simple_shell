#include "main.h"

/**
 * curr_env - current environment
 * @struct: Structure
 * 
 * Return: 0
 */
int curr_env(struct_t *struct)
{
	print_list_str(struct->env);
	return (0);
}

/**
 * _getenv - environment variable
 * @struct: Structure
 * @name: environment name
 *
 * Return: value
 */
char *_getenv(struct_t *struct, const char *name)
{
	list_t *alias_node = struct->env;
	char *p;

	while (alias_node)
	{
		p = starts_with(alias_node->str, name);
		if (p && *p)
			return (p);
		alias_node = alias_node->next;
	}
	return (NULL);
}

/**
 * ini_env - Initialize environment variable
 * 
 * @struct: Structure
 * 
 *  Return: Always 0
 */
int ini_env(struct_t *struct)
{
	if (struct->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(struct, struct->argv[1], struct->argv[2]))
		return (0);
	return (1);
}

/**
 * rm_env - Remove environment variable
 * @struct: Structure
 * 
 *  Return: 0
 */
int rm_env(struct_t *struct)
{
	int i;

	if (struct->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= struct->argc; i++)
		rm_env(struct, struct->argv[i]);

	return (0);
}

/**
 * env_list - environment linked list
 * @struct: Structure
 * 
 * Return: 0
 */
int env_list(struct_t *struct)
{
	list_t *alias_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&alias_node, environ[i], 0);
	struct->env = alias_node;
	return (0);
}
