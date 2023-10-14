#include "main.h"

/**
 * print_env - prints the environment variables
 * @dsh: pointer to the data structure
 * Return: 0 on code success
 */
int print_env(sh_data *dsh)
{
	int x, y;

	for (x = 0 ; dsh->env_vars[x] ; x++)
	{
		for (y = 0 ; dsh->env_vars[x][y] ; y++)
			;
		write(STDOUT_FILENO, dsh->env_vars[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	dsh->state = 0;
	return (0);
}

/**
 * _getenv - gets the environment variable
 * @name: name of the environment variable to be found
 * @env_vars: pointer to the array of environment variables
 * Return: value of the environment variable
 */
char *_getenv(const char *name, char **env_vars)
{
	int x, envpos = 0;
	char *penv;

	penv = NULL;

	for (x = 0 ; env_vars[x] ; x++)
	{
		envpos = cmp_env_var(env_vars[x], name);
		if (envpos)
		{
			penv = env_vars[x];
			break;
		}
	}
	return (penv + envpos);
}

/**
 * set_env - sets an environment variable
 * @name: name of environment variable to be set
 * @val: value to assign to the environment variable
 * @dsh: pointer to the data structure
 * Return: void
 */
void set_env(char *name, char *val, sh_data *dsh)
{
	int x;
	char *cpenv, *nenv;

	for (x = 0 ; dsh->env_vars[x] ; x++)
	{
		cpenv = str_dup(dsh->env_vars[x]);
		nenv = str_tok(cpenv, "=");
		if (str_cmp(nenv, name) == 0)
		{
			free(dsh->env_vars[x]);
			dsh->env_vars[x] = cpy_env_info(nenv, val);
			free(cpenv);
			return;
		}
		free(cpenv);
	}
	dsh->env_vars = realloc_dp(dsh->env_vars, x, sizeof(char *) * (x + 2));
	dsh->env_vars[x] = cpy_env_info(name, val);
	dsh->env_vars[x + 1] = NULL;
}

/**
 * _unsetenv - deletes an environment variable
 * @dsh: pointer to the data structure
 * Return: 0 on code success
 */
int _unsetenv(sh_data *dsh)
{
	char **reall_env;
	char *cpenv, *nenv;
	int x, y, z;

	if (dsh->tokenargs[1] == NULL)
	{
		get_error(dsh, -1);
		return (1);
	}
	z = -1;
	for (x = 0 ; dsh->env_vars[x] ; x++)
	{
		cpenv = str_dup(dsh->env_vars[x]);
		nenv = str_tok(cpenv, "=");
		if (str_cmp(nenv, dsh->tokenargs[1]) == 0)
		{
			z = x;
		}
		free(cpenv);
	}
	if (z == -1)
	{
		get_error(dsh, -1);
		return (1);
	}
	reall_env = malloc(sizeof(char *) * (x));
	for (x = y = 0 ; dsh->env_vars[x] ; x++)
	{
		if (x != z)
		{
			reall_env[y] = dsh->env_vars[x];
			y++;
		}
	}
	reall_env[y] = NULL;
	free(dsh->env_vars[z]);
	free(dsh->env_vars);
	dsh->env_vars = reall_env;
	return (0);
}
