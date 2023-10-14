#include "main.h"

/**
 * sh_exit - exits the shell
 * @dsh: pointer to the data structure
 * Return: 0 on success
 */
int sh_exit(sh_data *dsh)
{
	unsigned int exit_st;
	int dig, slent, num;

	if (dsh->tokenargs[1] != NULL)
	{
		exit_st = ch_atoi(dsh->tokenargs[1]);
		dig = is_digit(dsh->tokenargs[1]);
		slent = str_len(dsh->tokenargs[1]);
		num = exit_st > (unsigned int) INT_MAX;

		if (!dig || slent > 10 || num)
		{
			get_error(dsh, 2);
			dsh->state = 2;
			return (1);
		}
		dsh->state = (exit_st % 256);
	}
	return (0);
}

/**
 * proc_cmdln - executes command lines
 * @dsh: pointer to the data structure
 * Return: 1 on code success
 */
int proc_cmdln(sh_data *dsh)
{
	pid_t pd;
	pid_t wpd;
	int st = 0;
	int exec;
	char *dir;
	(void) wpd;

	exec = check_exec(dsh);
	if (exec == -1)
		return (-1);
	if (exec == 0)
	{
		dir = _execvp(dsh->tokenargs[0], dsh->env_vars);
		if (check_perms(dir, dsh) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _execvp(dsh->tokenargs[0], dsh->env_vars);
		else
			dir = dsh->tokenargs[0];
		execve(dir + exec, dsh->tokenargs, dsh->env_vars);
	}
	else if (pd < 0)
	{
		perror(dsh->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &st, WUNTRACED);
		} while (!WIFEXITED(st) && !WIFSIGNALED(st));
	}
	dsh->state = st / 256;
	return (1);
}

/**
 * exec_cmd - execute builtins and commands
 * @dsh: pointer to the data structure
 * Return: 0 on code success
 */
int exec_cmd(sh_data *dsh)
{
	int (*builtin)(sh_data *dsh);

	if (dsh->tokenargs[0] == NULL)
		return (0);
	builtin = get_builtin(dsh->tokenargs[0]);
	if (builtin != NULL)
		return (builtin(dsh));
	return (proc_cmdln(dsh));
}
