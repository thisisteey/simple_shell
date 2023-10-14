#include "main.h"

/**
 * read_input - reads the input string from the standard input
 * @is_eof: pointer to store the return value of the get_line function
 * Return: pointer to the input string
 */
char *read_input(int *is_eof)
{
	char *str = NULL;
	size_t bufsize = 0;

	*is_eof = get_line(&str, &bufsize, stdin);
	return (str);
}

/**
 * char_swp - swaps | and & for non-printed characters
 * @str: input string to be modified
 * @swap: type of swap (0 or 1)
 * Return: pointer to the modified input string
 */
char *char_swp(char *str, int swap)
{
	int x;

	if (swap == 0)
	{
		for (x = 0 ; str[x] ; x++)
		{
			if (str[x] == '|')
			{
				if (str[x + 1] != '|')
					str[x] = 16;
				else
					x++;
			}
			if (str[x] == '&')
			{
				if (str[x + 1] != '&')
					str[x] = 12;
				else
					x++;
			}
		}
	}
	else
	{
		for (x = 0 ; str[x] ; x++)
		{
			str[x] = (str[x] == 16 ? '|' : str[x]);
			str[x] = (str[x] == 12 ? '&' : str[x]);
		}
	}
	return (str);
}

/**
 * strip_comms - deletes comments from the input string
 * @str: input string to delete from
 * Return: modified input string without comments
 */
char *strip_comms(char *str)
{
	int x, num = 0;

	for (x = 0 ; str[x] ; x++)
	{
		if (str[x] == '#')
		{
			if (x == 0)
			{
				free(str);
				return (NULL);
			}
			if (str[x - 1] == ' ' || str[x - 1] == '\t' || str[x - 1] == ';')
				num = x;
		}
	}
	if (num != 0)
	{
		str = re_alloc(str, x, num + 1);
		str[num] = '\0';
	}
	return (str);
}

/**
 * div_cmdln - split and execute command lines based on separators
 * @dsh: pointer to the data structure
 * @str: input string containing commands
 * Return: 0 to exit loop, or 1 to continue
 */
int div_cmdln(sh_data *dsh, char *str)
{
	sep_t *sep_head, *sep_list;
	cmdln_t *cmdln_head, *cmdln_list;
	int idx;

	sep_head = NULL;
	cmdln_head = NULL;
	add_lst_nodes(&sep_head, &cmdln_head, str);
	sep_list = sep_head;
	cmdln_list = cmdln_head;

	while (cmdln_list != NULL)
	{
		dsh->cmdline = cmdln_list->line;
		dsh->tokenargs = tok_input(dsh->cmdline);
		idx = exec_cmd(dsh);
		free(dsh->tokenargs);
		if (idx == 0)
			break;
		nxt_list(&sep_list, &cmdln_list, dsh);
		if (cmdln_list != NULL)
			cmdln_list = cmdln_list->nxt;
	}
	free_sep(&sep_head);
	free_cmdln(&cmdln_head);
	if (idx == 0)
		return (0);
	return (1);
}

/**
 * tok_input - tokenize the input string
 * @str: input string to be tokenized
 * Return: an array of strings where each element has a token
 */
char **tok_input(char *str)
{
	size_t bsize, idx;
	char **toks;
	char *token;

	bsize = TOKEN_SIZE;
	toks = malloc(sizeof(char *) * (bsize));
	if (toks == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = str_tok(str, TOKEN_DELIMITERS);
	toks[0] = token;
	for (idx = 1 ; token != NULL ; idx++)
	{
		if (idx == bsize)
		{
			bsize += TOKEN_SIZE;
			toks = realloc_dp(toks, idx, sizeof(char *) * bsize);
			if (toks == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = str_tok(NULL, TOKEN_DELIMITERS);
		toks[idx] = token;
	}
	return (toks);
}
