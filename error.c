#include "main.h"

/**
 * stradd_cd - adding message for cd error
 *
 * @datastruc: data structure
 * @msg: message
 * @err: message output for error
 * @ver_str: counting lines
 * Return: error message
 */
char *stradd_cd(data_shell *datastruc, char *msg, char *err, char *ver_str)
{
	char *illegal_flag;

	_strcopy(err, datasruc->av[0]);
	_stradd(err, ": ");
	_stradd(err, ver_str);
	_stradd(err, ": ");
	_stradd(err, datastruc->args[0]);
	_stradd(err, msg);
	if (datastruc->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datastruc->args[1][1];
		illegal_flag[2] = '\0';
		_stradd(err, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_stradd(err, datastruc->args[1]);
	}

	_stradd(err, "\n");
	_stradd(err, "\0");
	return (err);
}

/**
 * cd_error - error message for cd command
 * @datastruc: data structure
 * Return: Error message
 */
char *cd_error(data_shell *datastruc)
{
	int length, length_id;
	char *err, *ver_str, *msg;

	ver_str = aux_intstr(datastruc->counter);
	if (datastruc->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		length_id = 2;
	}
	else
	{
		msg = ": cannot cd to ";
		length_id = _strlength(datastruc->args[1]);
	}

	length = _strlength(datastruc->av[0]) + _strlength(datadth->args[0]);
	length += _strlength(ver_str) + _strlenghth(msg) + length_id + 5;
	err = malloc(sizeof(char) * (length + 1));

	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}

	err =  stradd_cd(datastruc, msg, err, ver_str);

	free(ver_str);

	return (err);
}

/**
 * no_error - no error message
 * @datastruc: data structure
 * Return: Error message
 */
char *no_error(data_shell *datastruc)
{
	int length;
	char *err;
	char *ver_str;

	ver_str = aux_intstr(datastruc->counter);
	length = _strlength(datastruc->av[0]) + _strlength(ver_str);
	length += _strlength(datastruc->args[0]) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	_strcopy(err, datastruc->av[0]);
	_stradd(err, ": ");
	_stradd(err, ver_str);
	_stradd(err, ": ");
	_stradd(err, datastruc->args[0]);
	_stradd(err, ": not found\n");
	_stradd(err, "\0");
	free(ver_str);
	return (err);
}

/**
 * err_exit_shell - generic error message for exit in get_exit
 * @datastruc: data structure
 *
 * Return: Error message
 */
char *err_exit_shell(data_shell *datastruc)
{
	int length;
	char *err;
	char *ver_str;

	ver_str = aux_intstr(datastruc->counter);
	length = _strlength(datastruc->av[0]) + _strlength(ver_str);
	length += _strlength(datastruc->args[0]) + _strlength(datastruc->args[1]) + 23;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcopy(err, datastruc->av[0]);
	_stradd(err, ": ");
	_stradd(err, ver_str);
	_stradd(err, ": ");
	_stradd(err, datastruc->args[0]);
	_stradd(err, ": Illegal number: ");
	_stradd(err, datastruc->args[1]);
	_stradd(err, "\n\0");
	free(ver_str);

	return (err);
}

/**
 * err_envn - environment error message.
 * @datastruc: data structure
 * Return: error message.
 */
char *err_envn(data_shell *datastruc)
{
	int length;
	char *err;
	char *ver_str;
	char *msg;

	ver_str = aux_intstr(datastruc->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlength(datastruc->av[0]) + _strlength(ver_str);
	length += _strlength(datastruc->args[0]) + _strlength(msg) + 4;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}

	_strcopy(err, datastruc->av[0]);
	_stradd(err, ": ");
	_stradd(err, ver_str);
	_stradd(err, ": ");
	_stradd(err, datastruc->args[0]);
	_stradd(err, msg);
	_stradd(err, "\0");
	free(ver_str);

	return (err);
}

/**
 * err_path_126 - path error.
 * @datastruc: data structure.
 *
 * Return: string error.
 */
char *err_path_126(data_shell *datastruc)
{
	int length;
	char *ver_str;
	char *err;

	ver_str = aux_intstr(datastruc->counter);
	length = _strlength(datastruc->av[0]) + _strlength(ver_str);
	length += _strlength(datastruc->args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	_strcopy(err, datastruc->av[0]);
	_stradd(err, ": ");
	_stradd(err, ver_str);
	_stradd(err, ": ");
	_stradd(err, datastruc->args[0]);
	_stradd(err, ": Permission denied\n");
	_stradd(err, "\0");
	free(ver_str);
	return (err);
}

/**
 * get_err - syntax error
 * @datastruc: data structure
 * @errval: error value
 * Return: error
 */
int get_err(data_shell *datastruc, int errval)
{
	char *err;

	switch (errval)
	{
	case -1:
		err = error_envn(datastruc);
		break;
	case 126:
		err = error_path_126(datastruc);
		break;
	case 127:
		err = error_not_found(datastruc);
		break;
	case 2:
		if (_strcompare("exit", datastruc->args[0]) == 0)
			err = ext_shell(datastruc);
		else if (_strcompare("cd", datastruc->args[0]) == 0)
			err = error_get_cd(datastruc);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, error, _strlength(err));
		free(err);
	}

	datastruc->status = errval;
	return (errval);
}
