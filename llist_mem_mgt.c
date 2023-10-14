#include "main.h"

/**
 * free_sep - frees the separator list and its nodes
 * @head: pointer to the head of the linked list
 * Return: void
 */
void free_sep(sep_t **head)
{
	sep_t *tmp;
	sep_t *node;

	if (head != NULL)
	{
		node = *head;
		while ((tmp = node) != NULL)
		{
			node = node->nxt;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * free_cmdln - frees the command line list and its nodes
 * @head: pointer to the head of the linked list
 * Return: void
 */
void free_cmdln(cmdln_t **head)
{
	cmdln_t *tmp;
	cmdln_t *node;

	if (head != NULL)
	{
		node = *head;
		while ((tmp = node) != NULL)
		{
			node = node->nxt;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * free_var - frees the variable list and its nodes
 * @head: pointer to the head of the linked list
 * Return: void
 */
void free_var(var_t **head)
{
	var_t *tmp;
	var_t *node;

	if (head != NULL)
	{
		node = *head;
		while ((tmp = node) != NULL)
		{
			node = node->nxt;
			free(tmp);
		}
		*head = NULL;
	}
}
