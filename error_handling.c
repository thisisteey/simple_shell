#include "main.h"

/**
 * find_syn_err - detecting syntax error in the string
 * @str: input string to be checked
 * @idx: index that is checked in the string
 * @lschar: last characterthat is processed in the string
 * Return: index where error is found
 */
int find_syn_err(char *str, int idx, char lschar)
{
	int num = 0;

	if (*str == '\0')
		return (0);
	if (*str == ' ' || *str == '\t')
		return (find_syn_err(str + 1, idx + 1, lschar));
	if (*str == ';')
	{
		if (lschar == '|' || lschar == '&' || lschar == ';')
			return (idx);
	}
	if (*str == '|')
	{
		if (lschar == ';' || lschar == '&')
			return (idx);
		if (lschar == '|')
		{
			num = cnt_rep_char(str, 0);
			if (num == 0 || num > 1)
				return (idx);
		}
	}
	if (*str == '&')
	{
		if (lschar == ';' || lschar == '|')
			return (idx);
		if (lschar == '&')
		{
			num = cnt_rep_char(str, 0);
			if (num == 0 || num > 1)
				return (idx);
		}
	}
	return (find_syn_err(str + 1, idx + 1, *str));
}

/**
 * print_syn_err - prints error message when a syntax error is found
 * @dsh: data structure containing shell-related information
 * @str: input string to be checked
 * @idx: index where syntax error will be detected
 * @ctrlerr: control flag for error message
 * Return: void
 */
void print_syn_err(sh_data *dsh, char *str, int idx, int ctrlerr)
{
	char *errmsg, *emsg, *msgerr, *error, *counter;
	int lent;

	if (str[idx] == ';')
	{
		if (ctrlerr == 0)
			errmsg = (str[idx + 1] == ';' ? ";;" : ";");
		else
			errmsg = (str[idx - 1] == ';' ? ";;" : ";");
	}
	if (str[idx] == '|')
		errmsg = (str[idx + 1] == '|' ? "||" : "|");
	if (str[idx] == '&')
		errmsg = (str[idx + 1] == '&' ? "&&" : "&");
	emsg = ": Syntax error: \"";
	msgerr = "\" unexpected\n";
	counter = _sprintf(dsh->linenum);
	lent = str_len(dsh->argv[0]) + str_len(counter);
	lent += str_len(errmsg) + str_len(emsg) + str_len(msgerr) + 2;

	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	str_cpy(error, dsh->argv[0]);
	str_cat(error, ": ");
	str_cat(error, counter);
	str_cat(error, emsg);
	str_cat(error, errmsg);
	str_cat(error, msgerr);
	str_cat(error, "\0");

	write(STDERR_FILENO, error, lent);
	free(error);
	free(counter);
}

/**
 * chck_syn_err - intermidiate function to find and print the syntax error
 * @dsh: pointer to the data structure
 * @str: input string to be checked
 * Return: 1 if syntax error is detected, 0 if not
 */
int chck_syn_err(sh_data *dsh, char *str)
{
	int idx = 0;
	int fchar = 0;
	int x = 0;

	fchar = fst_char_index(str, &idx);
	if (fchar == -1)
	{
		print_syn_err(dsh, str, idx, 0);
		return (1);
	}
	x = find_syn_err(str + idx, 0, *(str + idx));
	if (x != 0)
	{
		print_syn_err(dsh, str, idx + x, 1);
		return (1);
	}
	return (0);
}

/**
 * concatcd_err - concatenates the messages for a 'cd' error
 * @dsh: pointer to the data structure
 * @errmsg: message to print
 * @error: output error message
 * @cmd_ctr: counter lines as a string
 * Return: error message
 */
char *concatcd_err(sh_data *dsh, char *errmsg, char *error, char *cmd_ctr)
{
	char *opt;

	str_cpy(error, dsh->argv[0]);
	str_cat(error, ": ");
	str_cat(error, cmd_ctr);
	str_cat(error, ": ");
	str_cat(error, dsh->tokenargs[0]);
	str_cat(error, errmsg);
	if (dsh->tokenargs[1][0] == '-')
	{
		opt = malloc(3);
		opt[0] = '-';
		opt[1] = dsh->tokenargs[1][1];
		opt[2] = '\0';
		str_cat(error, opt);
		free(opt);
	}
	else
	{
		str_cat(error, dsh->tokenargs[1]);
	}
	str_cat(error, "\n");
	str_cat(error, "\0");
	return (error);
}
