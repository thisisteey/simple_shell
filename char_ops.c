#include "main.h"

/**
 * is_digit - determines if the input string is a number
 * @str: input string to check
 * Return: 1 if its a string, or 0 if not
 */
int is_digit(const char *str)
{
	unsigned int x;

	for (x = 0 ; str[x] ; x++)
	{
		if (str[x] < '0' || str[x] > '9')
			return (0);
	}
	return (1);
}

/**
 * char_cmp - compares characters of a string with a delimeter string
 * @str: input string to compare
 * @delim: delimeter string for comparison
 * Return: 1 if the character match, or 0 if not
 */
int char_cmp(char str[], const char *delim)
{
	unsigned int x, y, z;

	for (x = 0, z = 0 ; str[x] ; x++)
	{
		for (y = 0 ; delim[y] ; y++)
		{
			if (str[x] == delim[y])
			{
				z++;
				break;
			}
		}
	}
	if (x == z)
		return (1);
	return (0);
}

/**
 * cnt_rep_char - count the repetitions of a character in a string
 * @str: input string to be counted
 * @idx: index within the string
 * Return: the number of consecutive repition of the character
 */
int cnt_rep_char(char *str, int idx)
{
	if (*(str - 1) == *str)
		return (cnt_rep_char(str - 1, idx + 1));
	return (idx);
}

/**
 * fst_char_index - finds the index of the first non-whitespace character
 * @str: the input string to be checked
 * @idx: pointer to the index to be updated
 * Return: 1 if there is an error, 0 if not
 */
int fst_char_index(char *str, int *idx)
{
	for (*idx = 0 ; str[*idx] ; *idx += 1)
	{
		if (str[*idx] == ' ' || str[*idx] == '\t')
			continue;
		if (str[*idx] == ';' || str[*idx] == '|' || str[*idx] == '&')
			return (-1);
		break;
	}
	return (0);
}
