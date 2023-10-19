#include "main.h"

/**
 * cd_dotdot - change directory above current directory
 *
 * @datastruc: data structure
 *
 * Return: no return
 */
void cd_dotdot(data_shell *datastruc)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strsplt_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdp(pwd);
	set_envn("OLDPWD", cp_pwd, datastruc);
	dir = datastruc->args[1];
	if (_strcompare(".", dir) == 0)
	{
		set_envn("PWD", cp_pwd, datastruc);
		free(cp_pwd);
		return;
	}
	if (_strcompare("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strsplt_pwd = cp_pwd;
	rev_string(cp_strsplt_pwd);
	cp_strsplt_pwd = _strsplt(cp_strsplt_pwd, "/");
	if (cp_strsplt_pwd != NULL)
	{
		cp_strsplt_pwd = _strsplt(NULL, "\0");

		if (cp_strsplt_pwd != NULL)
			rev_string(cp_strsplt_pwd);
	}
	if (cp_strsplt_pwd != NULL)
	{
		chdir(cp_strsplt_pwd);
		set_envn("PWD", cp_strsplt_pwd, datastruc);
	}
	else
	{
		chdir("/");
		set_envn("PWD", "/", datastruc);
	}
	datastruc->status = 0;
	free(cp_pwd);
}

/**
 * user_cd - user changes directory
 *
 * @datastruc: data structure
 * Return: no return
 */
void user_cd(data_shell *datastruc)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datastruc->args[1];
	if (chdir(dir) == -1)
	{
		get_err(datastruc, 2);
		return;
	}

	cp_pwd = _strdp(pwd);
	set_envn("OLDPWD", cp_pwd, datastruc);

	cp_dir = _strdp(dir);
	set_envn("PWD", cp_dir, datastruc);

	free(cp_pwd);
	free(cp_dir);

	datastruc->status = 0;

	chdir(dir);
}

/**
 * pre_cd - change back to previous directory
 *
 * @datastruc: data structure
 * Return: no return
 */
void pre_cd(data_shell *datastruc)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdp(pwd);

	p_oldpwd = _getenvn("OLDPWD", datastruc->_envn);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdp(p_oldpwd);

	set_envn("OLDPWD", cp_pwd, datastruc);

	if (chdir(cp_oldpwd) == -1)
		set_envn("PWD", cp_pwd, datastruc);
	else
		set_envn("PWD", cp_oldpwd, datastruc);

	p_pwd = _getenvn("PWD", datastruc->_envn);

	write(STDOUT_FILENO, p_pwd, _strlength(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datastruc->status = 0;

	chdir(p_pwd);
}

/**
 * cd_homedir - changes to home directory
 *
 * @datastruc: data structure
 * Return: no return
 */
void cd_homedir(data_shell *datastruc)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdp(pwd);

	home = _getenvn("HOME", datastruc->_envn);

	if (home == NULL)
	{
		set_envn("OLDPWD", p_pwd, datastruc);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_err(datastruc, 2);
		free(p_pwd);
		return;
	}

	set_envn("OLDPWD", p_pwd, datastruc);
	set_envn("PWD", home, datastruc);
	free(p_pwd);
	datastruc->status = 0;
}

/**
 * shell_cd - changes current dir
 *
 * @datastruc: data struc
 * Return: 1
 */
int shell_cd(data_shell *datastruc)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datastruc->args[1];

	if (dir != NULL)
	{
		ishome = _strcompare("$HOME", dir);
		ishome2 = _strcompare("~", dir);
		isddash = _strcompare("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_home(datastruc);
		return (1);
	}

	if (_strcompare("-", dir) == 0)
	{
		pre_cd(datastruc);
		return (1);
	}

	if (_strcompare(".", dir) == 0 || _strcompare("..", dir) == 0)
	{
		cd_dotdot(datastruc);
		return (1);
	}

	user_cd(datastruc);

	return (1);
}
