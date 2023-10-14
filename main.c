#include "main.h"

/**
 * init_data - initializes the data struct and populates it with initial values
 * @dsh: pointer to the data structure
 * @av: argument vector (an array of strings)
 * Return: void
 */
void init_data(sh_data *dsh, char **av)
{
	unsigned int x;

	dsh->argv = av;
	dsh->cmdline = NULL;
	dsh->tokenargs = NULL;
	dsh->state = 0;
	dsh->linenum = 1;

	for (x = 0 ; environ[x] ; x++)
		;
	dsh->env_vars = malloc(sizeof(char *) * (x + 1));
	for (x = 0 ; environ[x] ; x++)
	{
		dsh->env_vars[x] = str_dup(environ[x]);
	}
	dsh->env_vars[x] = NULL;
	dsh->pid = _sprintf(getpid());
}

/**
 * free_data - frees the data structure and associated resources
 * @dsh: pointer to the data structure
 * Return: void
 */
void free_data(sh_data *dsh)
{
	unsigned int x;

	for (x = 0; dsh->env_vars[x] ; x++)
	{
		free(dsh->env_vars[x]);
	}
	free(dsh->env_vars);
	free(dsh->pid);
}

/**
 * main- entry point of the program
 * @ac: argument count (number of command-line arguments)
 * @av: argument vector (array of command-line argument strings)
 * Return: 0 on code success
 */
int main(int ac, char **av)
{
	sh_data dsh;
	(void) ac;

	signal(SIGINT, get_sigint);
	init_data(&dsh, av);
	exec_shell(&dsh);
	free_data(&dsh);

	if (dsh.state < 0)
		return (255);
	return (dsh.state);
}
