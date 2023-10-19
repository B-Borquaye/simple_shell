#include "main.h"

/**
 * aux_hlp_envn - Environment help tips
 * Return: no return
 */
void aux_hlp_envn(void)
{
	char *hlp = "envn: envn [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "Print the shell environment.\n";
	write(STDOUT_FILENO, hlp, _strlength(hlp));

}
/**
 * aux_hlp_setenvn - setenvn help tips
 * Return: no return
 */
void aux_hlp_setenvn(void)
{

	char *hlp = "setenvn: setenvn (const char *name, const char *value,";

	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "int replace)\n\t";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "New environment definition\n";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
}
/**
 * aux_hlp_delsetenvn - delsetenvn help tips
 * Return: no return
 */
void aux_hlp_delsetenvn(void)
{
	char *hlp = "delsetenvn: delsetenvn (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlength(hlp));
	hlp = "Remove entry made in environment\n";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
}


/**
 * aux_hlp_gen - help tips
 * Return: no return
 */
void aux_hlp_general(void)
{
	char *hlp = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "Defined commands.Type 'hlp' for list";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "Type 'hlp name' to get info about the function 'name'.\n\n ";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "[dir]\nexit: exit [n]\n  envn: envn [option] [name=value] [command ";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "[args]]\n  setenvn: setenvn [variable] [value]\n  delsetenvn: ";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "delsetenvn [variable]\n";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
}
/**
 * aux_hlp_exit - Help exit tips
 * Return: no return
 */
void aux_hlp_exit(void)
{
	char *hlp = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "Exits shell with a status of N. If N is ommitted, exit";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "status of last command executed\n";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
}

/**
 * aux_hlp - Help information.
 * Return: no return
 */
void aux_hlp(void)
{
	char *hlp = "hlp: hlp [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "\tShows information about commands.\n ";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "Shows brief commands.\n";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
}
/**
 * aux_hlp_alias - alias help information.
 * Return: no return
 */
void aux_hlp_alias(void)
{
	char *hlp = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "\tDisplay all alias.\n ";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
}
/**
 * aux_hlp_cd - alias help information.
 * Return: no return
 */
void aux_hlp_cd(void)
{
	char *hlp = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, hlp, _strlength(hlp));
	hlp = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, hlp, _strlength(hlp));
}

/**
 * get_hlp - help tips
 * @datastruc: data structure
 * Return: 0
*/
int get_hlp(data_shell *datastruc)
{

	if (datastruc->args[1] == 0)
		aux_hlp_gen();
	else if (_strcompare(datastruc->args[1], "setenvn") == 0)
		aux_hlp_setenvn();
	else if (_strcompare(datastruc->args[1], "envn") == 0)
		aux_hlp_envn();
	else if (_strcompare(datastruc->args[1], "delsetenvn") == 0)
		aux_hlp_delsetenvn();
	else if (_strcompare(datastruc->args[1], "help") == 0)
		aux_hlp();
	else if (_strcompare(datastruc->args[1], "exit") == 0)
		aux_hlp_ext();
	else if (_strcompare(datastruc->args[1], "cd") == 0)
		aux_hlp_cd();
	else if (_strcompare(datastruc->args[1], "alias") == 0)
		aux_hlp_alias();
	else
		write(STDERR_FILENO, datastruc->args[0],
		      _strlength(datastruc->args[0]));

	datastruc->status = 0;
	return (1);
}
