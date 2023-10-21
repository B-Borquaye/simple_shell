#include "main.h"

/**
 * sh_loop - shell loop
 * @struct: structure
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error, or error code
 */
int sh_loop(struct_t *struct, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(struct);
		if (interactive(struct))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(struct);
		if (r != -1)
		{
			set_info(struct, av);
			builtin_ret = find_builtin(struct);
			if (builtin_ret == -1)
				find_cmd(struct);
		}
		else if (interactive(struct))
			_putchar('\n');
		free_info(struct, 0);
	}
	write_history(struct);
	free_info(struct, 1);
	if (!interactive(struct) && struct->status)
		exit(struct->status);
	if (builtin_ret == -2)
	{
		if (struct->err_num == -1)
			exit(struct->status);
		exit(struct->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @struct: structure
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(struct_t *struct)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_compare(struct->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @struct: structure
 *
 * Return: void
 */
void find_cmd(struct_t *struct)
{
	char *path = NULL;
	int i, k;

	struct->path = struct->argv[0];
	if (struct->linecount_flag == 1)
	{
		struct->line_count++;
		struct->linecount_flag = 0;
	}
	for (i = 0, k = 0; struct->arg[i]; i++)
		if (!c_delim(struct->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(struct, _getenv(struct, "PATH="), struct->argv[0]);
	if (path)
	{
		struct->path = path;
		fork_cmd(struct);
	}
	else
	{
		if ((interactive(struct) || _getenv(struct, "PATH=")
			|| struct->argv[0][0] == '/') && is_cmd(struct, struct->argv[0]))
			fork_cmd(struct);
		else if (*(struct->arg) != '\n')
		{
			struct->status = 127;
			print_error(struct, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @struct: struct
 *
 * Return: void
 */
void fork_cmd(struct_t *struct)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(struct->path, struct->argv, get_environ(struct)) == -1)
		{
			free_info(struct, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(struct->status));
		if (WIFEXITED(struct->status))
		{
			struct->status = WEXITSTATUS(struct->status);
			if (struct->status == 126)
				print_error(struct, "Permission denied\n");
		}
	}
}
