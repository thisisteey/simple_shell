#include "main.h"

/**
 * exec_shell - main loop of the shell
 * @dsh: pointer to the data structure
 * Return: void
 */
void exec_shell(sh_data *dsh)
{
	int is_eof, loop = 1;
	char *input;

	while (loop == 1)
	{
		write(STDIN_FILENO, "(: ", 3);
		input = read_input(&is_eof);
		if (is_eof != -1)
		{
			input = strip_comms(input);
			if (input == NULL)
				continue;
			if (chck_syn_err(dsh, input) == 1)
			{
				dsh->state = 2;
				free(input);
				continue;
			}
			input = repvars_Instr(input, dsh);
			loop = div_cmdln(dsh, input);
			dsh->linenum += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * nxt_list - moves to the next command line stores in the lists
 * @sep_list: pointer to the separator list
 * @cmdln_list: pointer to the command line list
 * @dsh: pointer to the data structure
 * Return: void
 */
void nxt_list(sep_t **sep_list, cmdln_t **cmdln_list, sh_data *dsh)
{
	int loop = 1;
	sep_t *sep;
	cmdln_t *cmdln;

	sep = *sep_list;
	cmdln = *cmdln_list;

	while (sep != NULL && loop)
	{
		if (dsh->state == 0)
		{
			if (sep->separator == '&' || sep->separator == ';')
				loop = 0;
			if (sep->separator == '|')
				cmdln = cmdln->nxt, sep = sep->nxt;
		}
		else
		{
			if (sep->separator == '|' || sep->separator == ';')
				loop = 0;
			if (sep->separator == '&')
				cmdln = cmdln->nxt, sep = sep->nxt;
		}
		if (sep != NULL && !loop)
			sep = sep->nxt;
	}
	*sep_list = sep;
	*cmdln_list = cmdln;
}

/**
 * check_cdir - checks if ':' is in the current directory path
 * @path: pointer to a char array representing the directory path
 * @idx: pointer to an integer index
 * Return: 0 on code success
 */
int check_cdir(char *path, int *idx)
{
	if (path[*idx] == ':')
		return (0);
	while (path[*idx] != ':' && path[*idx])
	{
		*idx += 1;
	}
	if (path[*idx])
		*idx += 1;
	return (1);
}

/**
 * check_exec - determines if a file is executable
 * @dsh: pointer to the data structure
 * Return: the number of characters in the file name
 */
int check_exec(sh_data *dsh)
{
	struct stat st;
	int x;
	char *str;

	str = dsh->tokenargs[0];
	for (x = 0 ; str[x] ; x++)
	{
		if (str[x] == '.')
		{
			if (str[x + 1] == '.')
				return (0);
			if (str[x + 1] == '/')
				continue;
			else
				break;
		}
		else if (str[x] == '/' && x != 0)
		{
			if (str[x + 1] == '.')
				continue;
			x++;
			break;
		}
		else
			break;
	}
	if (x == 0)
		return (0);
	if (stat(str + x, &st) == 0)
	{
		return (x);
	}
	get_error(dsh, 127);
	return (-1);
}

/**
 * check_perms - verifies if the user has permissions to access a directory
 * @dir: destination directory to check permissions
 * @dsh: pointer to the data structure
 * Return: 0 on code success
 */
int check_perms(char *dir, sh_data *dsh)
{
	if (dir == NULL)
	{
		get_error(dsh, 127);
		return (1);
	}
	if (str_cmp(dsh->tokenargs[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(dsh, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(dsh->tokenargs[0], X_OK) == -1)
		{
			get_error(dsh, 126);
			return (1);
		}
	}
	return (0);
}
