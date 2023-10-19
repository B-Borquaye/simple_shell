#include "main.h"

/**
 * sigint - crtl + c prompt
 * @sig: Signal
 */
void sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
