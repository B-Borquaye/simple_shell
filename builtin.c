#include "main.h"

/**
 * get_btin - builtin commands
 * @cmd: command
 * Return: builtin command fucntion
 */
int (*get_btin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "envn", _envn },
		{ "exit", exit_shell },
		{ "setenvn", _setenvn },
		{ "delsetenv", del_setenvn },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcompare(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

/**
 * exect_line - builtin and commands
 * @datastruc: data arguments
 * Return: 1.
 */
int exect_line(data_shell *datastruc)
{
	int (*builtin)(data_shell *datastruc);

	if (datastruc->args[0] == NULL)
		return (1);

	builtin = get_btin(datastruc->args[0]);

	if (builtin != NULL)
		return (builtin(datastruc));

	return (exect_cmd(datastruc));
}
