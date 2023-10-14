#include "main.h"

/**
 * check_env_vars - checks if the typed variable is an environment variable
 * @head: pointer to the head of the varaible linked list
 * @str: input string to be checked
 * @dsh: pointer to the data structure
 * Return: void
 */
void check_env_vars(var_t **head, char *str, sh_data *dsh)
{
	int loop, ch, x, lval;
	char **venv;

	venv = dsh->env_vars;

	for (loop = 0 ; venv[loop] ; loop++)
	{
		for (x = 1, ch = 0 ; venv[loop][ch] ; ch++)
		{
			if (venv[loop][ch] == '=')
			{
				lval = str_len(venv[loop] + ch + 1);
				add_var(head, x, venv[loop] + ch + 1, lval);
				return;
			}
			if (str[x] == venv[loop][ch])
				x++;
			else
				break;
		}
	}
	for (x = 0 ; str[x] ; x++)
	{
		if (str[x] == ' ' || str[x] == '\t' || str[x] == ';' || str[x] == '\n')
			break;
	}
	add_var(head, x, NULL, 0);
}

/**
 * proc_sp_vars - process special variables ($$ and $?)
 * @head: pointer to the head of the variable linked list
 * @str: input string to be checked
 * @lst: last status of the shell
 * @dsh: pointer to the data structure
 * Return: number of characters processed
 */
int proc_sp_vars(var_t **head, char *str, char *lst, sh_data *dsh)
{
	int x, lentst, lentpd;

	lentst = str_len(lst);
	lentpd = str_len(dsh->pid);

	for (x = 0 ; str[x] ; x++)
	{
		if (str[x] == '$')
		{
			if (str[x + 1] == '?')
				add_var(head, 2, lst, lentst), x++;
			else if (str[x + 1] == '$')
				add_var(head, 2, dsh->pid, lentpd), x++;
			else if (str[x + 1] == '\n')
				add_var(head, 0, NULL, 0);
			else if (str[x + 1] == '\0')
				add_var(head, 0, NULL, 0);
			else if (str[x + 1] == ' ')
				add_var(head, 0, NULL, 0);
			else if (str[x + 1] == '\t')
				add_var(head, 0, NULL, 0);
			else if (str[x + 1] == ';')
				add_var(head, 0, NULL, 0);
			else
				check_env_vars(head, str + x, dsh);
		}
	}
	return (x);
}

/**
 * sub_strvars - replaces substrings in a string with variables
 * @head: pointer to the head of the variable linked list
 * @str: main input string
 * @nstr: new input string with replacements
 * @nlent: length of the new input string
 * Return: pointer to the new inputn string with replacements
 */
char *sub_strvars(var_t **head, char *str, char *nstr, int nlent)
{
	int x, y, z;
	var_t *idx;

	idx = *head;

	for (y = x = 0 ; x < nlent ; x++)
	{
		if (str[y] == '$')
		{
			if (!(idx->var_len) && !(idx->val_len))
			{
				nstr[x] = str[y];
				y++;
			}
			else if (idx->var_len && !(idx->val_len))
			{
				for (z = 0 ; z < idx->var_len ; z++)
					y++;
				x--;
			}
			else
			{
				for (z = 0 ; z < idx->val_len ; z++)
				{
					nstr[x] = idx->value[z];
					x++;
				}
				y += (idx->var_len);
				x--;
			}
			idx = idx->nxt;
		}
		else
		{
			nstr[x] = str[y];
			y++;
		}
	}
	return (nstr);
}

/**
 * repvars_Instr - replaces variables in the input string
 * @str: input string with varibales to be replaced
 * @dsh: pointer to the data structure
 * Return: pointer to the replaced string
 */
char *repvars_Instr(char *str, sh_data *dsh)
{
	var_t *head, *idx;
	char *cond, *nstr;
	int olent, nlent;

	cond = _sprintf(dsh->state);
	head = NULL;
	olent = proc_sp_vars(&head, str, cond, dsh);

	if (head == NULL)
	{
		free(cond);
		return (str);
	}
	idx = head;
	nlent = 0;
	while (idx != NULL)
	{
		nlent += (idx->val_len - idx->var_len);
		idx = idx->nxt;
	}
	nlent += olent;
	nstr = malloc(sizeof(char) * (nlent + 1));
	nstr[nlent] = '\0';
	nstr = sub_strvars(&head, str, nstr, nlent);

	free(str);
	free(cond);
	free_var(&head);
	return (nstr);
}

/**
 * _execvp - locates a command in the system's PATH
 * @cmd: the command to locate
 * @env_vars: the environment variable
 * Return: the full path of the command
 */
char *_execvp(char *cmd, char **env_vars)
{
	char *path, *ptrp, *tokp, *dir;
	int ldir, lcmd, x;
	struct stat st;

	path = _getenv("PATH", env_vars);
	if (path)
	{
		ptrp = str_dup(path);
		lcmd = str_len(cmd);
		tokp = str_tok(ptrp, ":");
		x = 0;
		while (tokp != NULL)
		{
			if (check_cdir(path, &x))
				if (stat(cmd, &st) == 0)
					return (cmd);

			ldir = str_len(tokp);
			dir = malloc(ldir + lcmd + 2);
			str_cpy(dir, tokp);
			str_cat(dir, "/");
			str_cat(dir, cmd);
			str_cat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptrp);
				return (dir);
			}
			free(dir);
			tokp = str_tok(NULL, ":");
		}
		free(ptrp);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
