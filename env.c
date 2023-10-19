#include "main.h"

/**
 * compare_env - comparing passed env names
 * 
 * @namenv: environment variable name
 * @name: name passed
 *
 * Return: if not equal, return 0 else another value.
 */
int compare_env(const char *namenv, const char *name)
{
	int i;

	for (i = 0; namenv[i] != '='; i++)
	{
		if (namenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenvn - environment variable
 * @name: environment variable name
 * @_envn: environment variable
 *
 * Return: if found, return environment variable value else return NULL.
 */
char *_getenvn(const char *name, char **_envn)
{
	char *ptr_envn;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_envn = NULL;
	mov = 0;
	/* Comparing env variables */
	/* envn is declared in the header file */
	for (i = 0; _envn[i]; i++)
	{
		/* If name and envn are equal */
		mov = compare_env(_envn[i], name);
		if (mov)
		{
			ptr_envn = _envn[i];
			break;
		}
	}

	return (ptr_envn + mov);
}

/**
 * _envn - evironment variables
 *
 * @datastruc: data structure.
 * Return: 1.
 */
int _envn(data_shell *datastruc)
{
	int i, j;

	for (i = 0; datastruc->_envn[i]; i++)
	{

		for (j = 0; datastruc->_envn[i][j]; j++)
			;

		write(STDOUT_FILENO, datastruc->_envn[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datastruc->status = 0;

	return (1);
}

/**
 * cpy_info - copies information
 * @name: name 
 * @val: value
 *
 * Return: environment or alias.
 */
char *cpy_info(char *name, char *val)
{
	char *new;
	int length_name, length_value, length;

	length_name = _strlength(name);
	length_value = _strlength(val);
	length = length_name + length_value + 2;
	new = malloc(sizeof(char) * (length));
	_strcopy(new, name);
	_stradd(new, "=");
	_stradd(new, val);
	_stradd(new, "\0");

	return (new);
}

/**
 * set_envn - this sets environment variable
 *
 * @name: environment variable name
 * @val: environment variable value
 * @datastruc: data structure
 * Return: no return
 */
void set_envn(char *name, char *val, data_shell *datastruc)
{
	int i;
	char *var_envn, *name_envn;

	for (i = 0; datastruc->_environ[i]; i++)
	{
		var_envn = _strdp(datastruc->_envn[i]);
		name_envn = _strsplt(var_env, "=");
		if (_strcompare(name_envn, name) == 0)
		{
			free(datastruc->_envn[i]);
			datastruc->_envn[i] = cpy_info(name_envn, val);
			free(var_envn);
			return;
		}
		free(var_env);
	}

	datastruc->_envn = _rlocatedp(datastruc->_envn, i, sizeof(char *) * (i + 2));
	datastruc->_envn[i] = cpy_info(name, val);
	datastruc->_envn[i + 1] = NULL;
}

/**
 * _setenvn - compares passed environment name.
 * @datastruc: data of env name and value.
 *
 * Return: 1.
 */
int _setenvn(data_shell *datastruc)
{

	if (datastruc->args[1] == NULL || datastruc->args[2] == NULL)
	{
		get_err(datastruc, -1);
		return (1);
	}

	set_envn(datastruc->args[1], datastruc->args[2], datastruc);

	return (1);
}

/**
 * del_setenvn - delete environment variable
 *
 * @datastruc: data structure
 *
 * Return: 1.
 */
int del_setenvn(data_shell *datastruc)
{
	char **rlocate_envn;
	char *var_envn, *name_envn;
	int i, j, k;

	if (datastruc->args[1] == NULL)
	{
		get_err(datastruc, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datastruc->_envn[i]; i++)
	{
		var_envn = _strdp(datastruc->_envn[i]);
		name_envn = _strsplt(var_envn, "=");
		if (_strcompare(name_envn, datastruc->args[1]) == 0)
		{
			k = i;
		}
		free(var_envn);
	}
	if (k == -1)
	{
		get_err(datastruc, -1);
		return (1);
	}
	rlocate_envn = malloc(sizeof(char *) * (i));
	for (i = j = 0; datastruc->_envn[i]; i++)
	{
		if (i != k)
		{
			rlocate_envn[j] = datastruc->_envn[i];
			j++;
		}
	}
	rlocate_envn[j] = NULL;
	free(datastruc->_envn[k]);
	free(datastruc->_envn);
	datastruc->_envn = rlocate_envn;
	return (1);
}
