#include "main.h"

/**
 * get_sigint - handles the Ctrl+C (SIGINT) signal in the prompt
 * @sig: the signal number
 * Return: void
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n(: ", 4);
}

/**
 * get_help - retrieves help messages for shell commands
 * @dsh: pointer to the data structure
 * Return: 0 on code success
 */
int get_help(sh_data *dsh)
{
	if (dsh->tokenargs[1] == 0)
		gen_help_info();
	else if (str_cmp(dsh->tokenargs[1], "setenv") == 0)
		setenv_help_info();
	else if (str_cmp(dsh->tokenargs[1], "env") == 0)
		env_help_info();
	else if (str_cmp(dsh->tokenargs[1], "unsetenv") == 0)
		unsetenv_help_info();
	else if (str_cmp(dsh->tokenargs[1], "help") == 0)
		help_info();
	else if (str_cmp(dsh->tokenargs[1], "exit") == 0)
		exit_help_info();
	else if (str_cmp(dsh->tokenargs[1], "cd") == 0)
		cd_help_info();
	else if (str_cmp(dsh->tokenargs[1], "alias") == 0)
		alias_help_info();
	else
		write(STDERR_FILENO, dsh->tokenargs[0],
			str_len(dsh->tokenargs[0]));
	dsh->state = 0;
	return (1);
}

/**
 * get_error - calls the error message function based on the error code
 * @dsh: pointer to the data structure
 * @err_val: error value
 * Return: error code
 */
int get_error(sh_data *dsh, int err_val)
{
	char *error = NULL;

	switch (err_val)
	{
		case -1:
			error = env_err_msg(dsh);
			break;
		case 126:
			error = path126_err_msg(dsh);
			break;
		case 127:
			error = cmd_not_found(dsh);
			break;
		case 2:
			if (str_cmp("exit", dsh->tokenargs[0]) == 0)
				error = sh_exit_err(dsh);
			else if (str_cmp("cd", dsh->tokenargs[0]) == 0)
				error = cd_cmd_err(dsh);
			break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, str_len(error));
		free(error);
	}
	dsh->state = err_val;
	return (err_val);
}

/**
 * get_builtin - retrieves a pointer to the built-in function
 * @cmd: command name (string)
 * Return: pointer to the built-in function
 */
int (*get_builtin(char *cmd))(sh_data *)
{
	builtin_t builtin[] = {
		{ "env", print_env },
		{ "exit", sh_exit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_sh},
		{ "help", get_help },
		{ NULL, NULL }
	};
	int x;

	for (x = 0 ; builtin[x].name ; x++)
	{
		if (str_cmp(builtin[x].name, cmd) == 0)
			break;
	}
	return (builtin[x].f);
}
