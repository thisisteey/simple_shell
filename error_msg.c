#include "main.h"

/**
 * cd_cmd_err - generates error message for the cd command
 * @dsh: pointer to the data structure
 * Return: pointer to the generated error message
 */
char *cd_cmd_err(sh_data *dsh)
{
	int lent, len_id;
	char *error, *cmd_ctr, *errmsg;

	cmd_ctr = _sprintf(dsh->linenum);
	if (dsh->tokenargs[1][0] == '-')
	{
		errmsg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		errmsg = ": can't cd to ";
		len_id = str_len(dsh->tokenargs[1]);
	}
	lent = str_len(dsh->argv[0]) + str_len(dsh->tokenargs[0]);
	lent += str_len(cmd_ctr) + str_len(errmsg) + len_id + 5;
	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(cmd_ctr);
		return (NULL);
	}
	error = concatcd_err(dsh, errmsg, error, cmd_ctr);
	free(cmd_ctr);
	return (error);
}

/**
 * cmd_not_found - generates a generic error message for a command not found
 * @dsh: pointer to the data structure
 * Return: pointer to the generated error message
 */
char *cmd_not_found(sh_data *dsh)
{
	int lent;
	char *error, *cmd_ctr;

	cmd_ctr = _sprintf(dsh->linenum);
	lent = str_len(dsh->argv[0]) + str_len(cmd_ctr);
	lent += str_len(dsh->tokenargs[0]) + 16;
	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(error);
		free(cmd_ctr);
		return (NULL);
	}
	str_cpy(error, dsh->argv[0]);
	str_cat(error, ": ");
	str_cat(error, cmd_ctr);
	str_cat(error, ": ");
	str_cat(error, dsh->tokenargs[0]);
	str_cat(error, ": not found\n");
	str_cat(error, "\0");
	free(cmd_ctr);
	return (error);
}

/**
 * sh_exit_err - generates a generic error message for shell exit error
 * @dsh: pointer to the data structure
 * Return: pointer to the generated error message
 */
char *sh_exit_err(sh_data *dsh)
{
	int lent;
	char *error, *cmd_ctr;

	cmd_ctr = _sprintf(dsh->linenum);
	lent = str_len(dsh->argv[0]) + str_len(cmd_ctr);
	lent += str_len(dsh->tokenargs[0]) + str_len(dsh->tokenargs[1]) + 23;
	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(cmd_ctr);
		return (NULL);
	}
	str_cpy(error, dsh->argv[0]);
	str_cat(error, ": ");
	str_cat(error, cmd_ctr);
	str_cat(error, ": ");
	str_cat(error, dsh->tokenargs[0]);
	str_cat(error, ": Illegal number: ");
	str_cat(error, dsh->tokenargs[1]);
	str_cat(error, "\n\0");
	free(cmd_ctr);
	return (error);
}

/**
 * env_err_msg - generates error message for 'env'command
 * @dsh: pointer to the data structure
 * Return: error message
 */
char *env_err_msg(sh_data *dsh)
{
	int lent;
	char *error, *cmd_ctr, *errmsg;

	cmd_ctr = _sprintf(dsh->linenum);
	errmsg = ": Unable to add/remove from environment\n";
	lent = str_len(dsh->argv[0]) + str_len(cmd_ctr);
	lent += str_len(dsh->tokenargs[0]) + str_len(errmsg) + 4;
	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(error);
		free(cmd_ctr);
		return (NULL);
	}
	str_cpy(error, dsh->argv[0]);
	str_cat(error, ": ");
	str_cat(error, cmd_ctr);
	str_cat(error, ": ");
	str_cat(error, dsh->tokenargs[0]);
	str_cat(error, errmsg);
	str_cat(error, "\0");
	free(cmd_ctr);

	return (error);
}

/**
 * path126_err_msg - generates error message for the 'path' command
 * @dsh: pointer to the data structure
 * Return: error message
 */
char *path126_err_msg(sh_data *dsh)
{
	int lent;
	char *cmd_ctr, *error;

	cmd_ctr = _sprintf(dsh->linenum);
	lent = str_len(dsh->argv[0]) + str_len(cmd_ctr);
	lent += str_len(dsh->tokenargs[0]) + 24;
	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(error);
		free(cmd_ctr);
		return (NULL);
	}
	str_cpy(error, dsh->argv[0]);
	str_cat(error, ": ");
	str_cat(error, cmd_ctr);
	str_cat(error, ": ");
	str_cat(error, dsh->tokenargs[0]);
	str_cat(error, ": Permission denied\n");
	str_cat(error, "\0");
	free(cmd_ctr);
	return (error);
}
