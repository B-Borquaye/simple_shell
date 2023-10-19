#include "main.h"

/**
 * free_data - frees data structure
 *
 * @datastruc: data structure
 * Return: no return
 */
void free_data(data_shell *datastruc)
{
	unsigned int i;

	for (i = 0; datastruc->_environ[i]; i++)
	{
		free(datastruc->_environ[i]);
	}

	free(datastruc->_environ);
	free(datastruc->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @datastruc: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *datastruc, char **av)
{
	unsigned int i;

	datastruc->av = av;
	datastruc->input = NULL;
	datastruc->args = NULL;
	datastruc->status = 0;
	datastruc->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datastruc->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datastruc->_environ[i] = _strdp(environ[i]);
	}

	datastruc->_environ[i] = NULL;
	datastruc->pid = aux_intstr(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datastruc;
	(void) ac;

	signal(SIGINT, sigint);
	set_data(&datastruc, av);
	loop(&datastruc);
	free_data(&datastruc);
	if (datastruc.status < 0)
		return (255);
	return (datastruc.status);
}
