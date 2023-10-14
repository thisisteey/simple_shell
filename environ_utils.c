#include "main.h"

/**
 * cmp_env_var - compares environment varibale names with the name passed
 * @envname: name of the environment variable
 * @name: name passed for comparison
 * Return: 0 on code success
 */
int cmp_env_var(const char *envname, const char *name)
{
	int x;

	for (x = 0 ; envname[x] != '=' ; x++)
	{
		if (envname[x] != name[x])
		{
			return (0);
		}
	}
	return (x + 1);
}

/**
 * cpy_env_info - copies information to create a new variable
 * @name: name of the environment variable
 * @val: value of the environment variable
 * Return: new environment variable
 */
char *cpy_env_info(char *name, char *val)
{
	char *newenv;
	int lname, lval, lent;

	lname = str_len(name);
	lval = str_len(val);
	lent = lname + lval + 2;
	newenv = malloc(sizeof(char) * (lent));
	str_cpy(newenv, name);
	str_cat(newenv, "=");
	str_cat(newenv, val);
	str_cat(newenv, "\0");

	return (newenv);
}

/**
 * _setenv - sets the value of an environment variable or create
 * a new one if it doesn't already exist
 * @dsh: pointer to the data structure
 * Return: 0 on code success
 */
int _setenv(sh_data *dsh)
{
	if (dsh->tokenargs[1] == NULL || dsh->tokenargs[2] == NULL)
	{
		get_error(dsh, -1);
		return (1);
	}
	set_env(dsh->tokenargs[1], dsh->tokenargs[2], dsh);
	return (0);
}
