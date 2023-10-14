#include "main.h"

/**
 * str_dup - duplicates a string in heap memory
 * @str: pointer to the original string
 * Return: pointer to the duplicated string
 */
char *str_dup(const char *str)
{
	char *dupstr;
	size_t lent;

	lent = str_len(str);
	dupstr = malloc(sizeof(char) * (lent + 1));
	if (!dupstr)
		return (NULL);
	cpy_mem(dupstr, str, lent + 1);
	return (dupstr);
}

/**
 * str_rev - reverses a string in-place
 * @str: input string to be reversed
 * Return: void
 */
void str_rev(char *str)
{
	int x, y;
	int lent = 0;
	char *nstr, tmp;

	while (lent >= 0)
	{
		if (str[lent] == '\0')
			break;
		lent++;
	}
	nstr = str;
	for (x = 0 ; x < (lent - 1) ; x++)
	{
		for (y = x + 1 ; y > 0 ; y--)
		{
			tmp = *(nstr + y);
			*(nstr + y) = *(nstr + (y - 1));
			*(nstr + (y - 1)) = tmp;
		}
	}
}

/**
 * str_spn - calculates the length of a prefix substring
 * @str: intial string to be checked
 * @chr: the set of character to match in the prefix
 * Return: number of character at the start of @str that are in @chr
 */
int str_spn(char *str, char *chr)
{
	int x, y, byt;

	for (x = 0 ; str[x] != '\0' ; x++)
	{
		byt = 1;
		for (y = 0 ; chr[y] != '\0' ; y++)
		{
			if (str[x] == chr[y])
			{
				byt = 0;
				break;
			}
		}
		if (byt == 1)
			break;
	}
	return (x);
}

/**
 * str_tok - splits a string into tokens by some delimiters
 * @str: input string to be splitted
 * @delim: delimeters to use
 * Return: pointer to the next token
 */
char *str_tok(char str[], const char *delim)
{
	static char *currpos, *end_str;
	char *start_str;
	unsigned int x, byt;

	if (str != NULL)
	{
		if (char_cmp(str, delim))
			return (NULL);
		currpos = str;
		x = str_len(str);
		end_str = &str[x];
	}
	start_str = currpos;
	if (start_str == end_str)
		return (NULL);
	for (byt = 0 ; *currpos ; currpos++)
	{
		if (currpos != start_str)
			if (*currpos && *(currpos - 1) == '\0')
				break;
		for (x = 0 ; delim[x] ; x++)
		{
			if (*currpos == delim[x])
			{
				*currpos = '\0';
				if (currpos == start_str)
					start_str++;
				break;
			}
		}
		if (byt == 0 && *currpos)
			byt = 1;
	}
	if (byt == 0)
		return (NULL);
	return (start_str);
}
