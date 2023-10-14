#include "main.h"

/**
 * add_sep - adds a separate node to the end of the linked list
 * @head: pointer to the head of the linked list
 * @sep: separator character to be added (; | &)
 * Return: address of the updated head of the linked list
 */
sep_t *add_sep(sep_t **head, char sep)
{
	sep_t *nnode, *tmp;

	nnode = malloc(sizeof(sep_t));
	if (nnode == NULL)
		return (NULL);
	nnode->separator = sep;
	nnode->nxt = NULL;
	tmp = *head;
	if (tmp == NULL)
	{
		*head = nnode;
	}
	else
	{
		while (tmp->nxt != NULL)
			tmp = tmp->nxt;
		tmp->nxt = nnode;
	}
	return (*head);
}

/**
 * add_cmdln - adds a command line node at the end of the linked list
 * @head: pointer to the head of the linked list
 * @ln: command line string to be added
 * Return: address of the updated head of the linked list
 */
cmdln_t *add_cmdln(cmdln_t **head, char *ln)
{
	cmdln_t *nnode, *tmp;

	nnode = malloc(sizeof(cmdln_t));
	if (nnode == NULL)
		return (NULL);
	nnode->line = ln;
	nnode->nxt = NULL;
	tmp = *head;
	if (tmp == NULL)
	{
		*head = nnode;
	}
	else
	{
		while (tmp->nxt != NULL)
			tmp = tmp->nxt;
		tmp->nxt = nnode;
	}
	return (*head);
}

/**
 * add_var - adds a variable at the end of the linked list
 * @head: pointer to the head of the linked list
 * @vlen: length of the variable
 * @val: value of the variable
 * @valen: length of the value
 * Return: address to the updated head of the linked list
 */
var_t *add_var(var_t **head, int vlen, char *val, int valen)
{
	var_t *nnode, *tmp;

	nnode = malloc(sizeof(var_t));
	if (nnode == NULL)
		return (NULL);
	nnode->var_len = vlen;
	nnode->value = val;
	nnode->val_len = valen;
	nnode->nxt = NULL;
	tmp = *head;
	if (tmp == NULL)
	{
		*head = nnode;
	}
	else
	{
		while (tmp->nxt != NULL)
			tmp = tmp->nxt;
		tmp->nxt = nnode;
	}
	return (*head);
}

/**
 * add_lst_nodes - add separators and command lines to the linked lists
 * @sep_head: pointer to the head of the separator linked list
 * @cmdln_head: pointer to the head of the command line linked list
 * @str: input string
 * Return: void
 */
void add_lst_nodes(sep_t **sep_head, cmdln_t **cmdln_head, char *str)
{
	int x;
	char *ln;

	str = char_swp(str, 0);
	for (x = 0 ; str[x] ; x++)
	{
		if (str[x] == ';')
			add_sep(sep_head, str[x]);
		if (str[x] == '|' || str[x] == '&')
		{
			add_sep(sep_head, str[x]);
			x++;
		}
	}
	ln = str_tok(str, ";|&");
	do {
		ln = char_swp(ln, 1);
		add_cmdln(cmdln_head, ln);
		ln = str_tok(NULL, ";|&");
	} while (ln != NULL);
}
