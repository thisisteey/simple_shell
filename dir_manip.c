#include "main.h"

/**
 * cd_dot - changes to the parent directory
 * @dsh: pointer to the data structure
 * Return: void
 */
void cd_dot(sh_data *dsh)
{
	char pwd[PATH_MAX];
	char *dir, *cpwd, *tokpwd;

	getcwd(pwd, sizeof(pwd));
	cpwd = str_dup(pwd);
	set_env("OLDPWD", cpwd, dsh);
	dir = dsh->tokenargs[1];
	if (str_cmp(".", dir) == 0)
	{
		set_env("PWD", cpwd, dsh);
		free(cpwd);
		return;
	}
	if (str_cmp("/", cpwd) == 0)
	{
		free(cpwd);
		return;
	}
	tokpwd = cpwd;
	str_rev(tokpwd);
	tokpwd = str_tok(tokpwd, "/");
	if (tokpwd != NULL)
	{
		tokpwd = str_tok(NULL, "\0");
		if (tokpwd != NULL)
			str_rev(tokpwd);
	}
	if (tokpwd != NULL)
	{
		chdir(tokpwd);
		set_env("PWD", tokpwd, dsh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", dsh);
	}
	dsh->state = 0;
	free(cpwd);
}

/**
 * cd_path - changes to a specified directory
 * @dsh: pointer to the data structure
 * Return: void
 */
void cd_path(sh_data *dsh)
{
	char pwd[PATH_MAX];
	char *dir, *cpwd, *cdir;

	getcwd(pwd, sizeof(pwd));
	dir = dsh->tokenargs[1];
	if (chdir(dir) == -1)
	{
		get_error(dsh, 2);
		return;
	}
	cpwd = str_dup(pwd);
	set_env("OLDPWD", cpwd, dsh);
	cdir = str_dup(dir);
	set_env("PWD", cdir, dsh);
	free(cpwd);
	free(cdir);
	dsh->state = 0;
	chdir(dir);
}

/**
 * cd_dash - changes to previous directory
 * @dsh: pointer to the data structure
 * Return: void
 */
void cd_dash(sh_data *dsh)
{
	char pwd[PATH_MAX];
	char *ppwd, *opwd, *cpwd, *copwd;

	getcwd(pwd, sizeof(pwd));
	cpwd = str_dup(pwd);
	opwd = _getenv("OLPWD", dsh->env_vars);
	if (opwd == NULL)
		copwd = cpwd;
	else
		copwd = str_dup(opwd);
	set_env("OLDPWD", cpwd, dsh);
	if (chdir(copwd) == -1)
		set_env("PWD", cpwd, dsh);
	else
		set_env("PWD", copwd, dsh);
	ppwd = _getenv("PWD", dsh->env_vars);
	write(STDOUT_FILENO, ppwd, str_len(ppwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cpwd);
	if (opwd)
		free(copwd);
	dsh->state = 0;
	chdir(ppwd);
}

/**
 * cd_tilde - changes to home directory 
 * @dsh: pointer to the data structure
 * Return: void
 */
void cd_tilde(sh_data *dsh)
{
	char pwd[PATH_MAX];
	char *ppwd, *home;

	getcwd(pwd, sizeof(pwd));
	ppwd = str_dup(pwd);
	home = _getenv("HOME", dsh->env_vars);
	if (home == NULL)
	{
		set_env("OLDPWD", ppwd, dsh);
		free(ppwd);
		return;
	}
	if (chdir(home) == -1)
	{
		get_error(dsh, 2);
		free(ppwd);
		return;
	}
	set_env("OLDPWD", ppwd, dsh);
	set_env("PWD", home, dsh);
	free(ppwd);
	dsh->state = 0;
}

/**
 * cd_sh - chnages the current directory based on user input
 * @dsh: pointer to the data structure
 * Return: 1 on success
 */
int cd_sh(sh_data *dsh)
{
	char *dir;
	int ispath, istilde, isddash;

	dir = dsh->tokenargs[1];
	if (dir != NULL)
	{
		ispath = str_cmp("$HOME", dir);
		istilde = str_cmp("~", dir);
		isddash = str_cmp("--", dir);
	}
	if (dir == NULL || ispath || istilde || isddash)
	{
		cd_tilde(dsh);
		return (1);
	}
	if (str_cmp("-", dir) == 0)
	{
		cd_dash(dsh);
		return (1);
	}
	if (str_cmp(".", dir) == 0 || str_cmp("..", dir) == 0)
	{
		cd_dot(dsh);
		return (1);
	}
	cd_path(dsh);
	return (1);
}
