#include "main.h"

/**
 * currdir - checks ":" in current directory.
 * @path: character pointer.
 * @i: index.
 * Return: if path is found in cd, retun 1 else 0.
 */
int currdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _loccmd - command location
 * @cmd: name of command
 * @_envn: environment variable
 * Return: location of the command.
 */
char *_loccmd(char *cmd, char **_envn)
{
	char *path, *ptr_path, *tok_path, *dir;
	int length_dir, length_cmd, i;
	struct stat st;

	path = _getenvn("PATH", _envn);
	if (path)
	{
		ptr_path = _strdp(path);
		length_cmd = _strlength(cmd);
		tok_path = _strsplt(ptr_path, ":");
		i = 0;
		while (tok_path != NULL)
		{
			if (currdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			length_dir = _strlength(tok_path);
			dir = malloc(length_dir + length_cmd + 2);
			_strcopy(dir, tok_path);
			_stradd(dir, "/");
			_stradd(dir, cmd);
			_stradd(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			tok_path = _strsplt(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * execut - executable
 * @datastruc: data structure
 * Return: if not executable, return 0 else other number
 */
int execut(data_shell *datastruc)
{
	struct stat st;
	int i;
	char *input;

	input = datastruc->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_err(datastruc, 127);
	return (-1);
}

/**
 * check_cmd - checks user access
 * @dir: directory
 * @datastruc: data structure
 * Return: if error occurs, return 1 else 0
 */
int check_cmd(char *dir, data_shell *datastruc)
{
	if (dir == NULL)
	{
		get_err(datastruc, 127);
		return (1);
	}

	if (_strcompare(datastruc->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_err(datastruc, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datastruc->args[0], X_OK) == -1)
		{
			get_err(datastruc, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exect_cmd - executes commands
 * @datastruc: data arguments and inputs
 * Return: 1.
 */
int exect_cmd(data_shell *datastruc)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = execut(datastruc);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _loccmd(datastruc->args[0], datastruc->_envn);
		if (check_cmd(dir, datastruc) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _loccmd(datastruc->args[0], datastruc->_envn);
		else
			dir = datasturc->args[0];
		execve(dir + exec, datastruc->args, datastruc->_envn);
	}
	else if (pd < 0)
	{
		perr(datastruc->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datastruc->status = state / 256;
	return (1);
}
