#include "main.h"

/**
 * str_len - calculates the length of a string
 * @str: pointer to the string
 * Return: length of the string
 */
int str_len(const char *str)
{
	int lent;

	for (lent = 0 ; str[lent] != '\0' ; lent++)
	{
	}
	return (lent);
}

/**
 * str_cat - concatenates two strings
 * @dst: pointer to the destination string
 * @src: pointer to the source string to be appended
 * Return: pointer to the destination string after concatenation
 */
char *str_cat(char *dst, const char *src)
{
	int x = 0;
	int y = 0;

	while (dst[x] != '\0')
	{
		x++;
	}
	while (src[y] != '\0')
	{
		dst[x] = src[y];
		x++;
		y++;
	}
	dst[x] = '\0';
	return (dst);
}

/**
 * str_cmp - compares two strings
 * @str1: pointer to the first string
 * @str2: pointer to the second string
 * Return: 0 on code success
 */
int str_cmp(char *str1, char *str2)
{
	int x = 0;

	while (str1[x] == str2[x] && str1[x] != '\0')
	{
		x++;
	}
	if (str1[x] > str2[x])
		return (1);
	if (str1[x] < str2[x])
		return (-1);
	return (0);
}

/**
 * str_cpy - copies a string from source to destination
 * @dst: pointer to the destination string
 * @src: pointer to the source string to be copied
 * Return: pointer to the destination string after copying
 */
char *str_cpy(char *dst, char *src)
{
	size_t x;

	for (x = 0 ; src[x] != '\0' ; x++)
	{
		dst[x] = src[x];
	}
	dst[x] = '\0';
	return (dst);
}

/**
 * str_chr - locates the first occurence of a character in a string
 * @str: pointer to the string to search
 * @chr: the character to locate
 * Return: pointer to the first occurence of @chr in @str
 */
char *str_chr(char *str, char chr)
{
	unsigned int x = 0;

	for (; *(str + x) != '\0' ; x++)
	{
		if (*(str + x) == chr)
		{
			return (str + x);
		}
	}
	if (*(str + x) == chr)
		return (str + x);
	return ("\0");
}
