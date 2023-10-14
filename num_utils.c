#include "main.h"

/**
 * _intdigits - get the length of a number
 * @num: number to determine its length
 * Return: length of the given number
 */
int _intdigits(int num)
{
	unsigned int x;
	int lent = 1;

	if (num < 0)
	{
		lent++;
		x = num * -1;
	}
	else
	{
		x = num;
	}
	while (x > 9)
	{
		lent++;
		x = x / 10;
	}
	return (lent);
}

/**
 * _sprintf - converts an integer to a string
 * @num: number to be converted to a string
 * Return: dynamically allocated string representing the number
 */
char *_sprintf(int num)
{
	unsigned int x;
	int lent = _intdigits(num);
	char *buff;

	buff = malloc(sizeof(char) * (lent + 1));
	if (buff == 0)
		return (NULL);
	*(buff + lent) = '\0';
	if (num < 0)
	{
		x = num * -1;
		buff[0] = '-';
	}
	else
	{
		x = num;
	}
	lent--;
	do {
		*(buff + lent) = (x % 10) + '0';
		x = x / 10;
		lent--;
	}
	while (x > 0)
		;
	return (buff);
}

/**
 * ch_atoi - converts a string to an integer
 * @str: string to be converted
 * Return: integer value extracted from the string
 */
int ch_atoi(char *str)
{
	unsigned int cc = 0, dc = 0, res = 0, sign = 1, mul = 1, idx;

	while (*(str + cc) != '\0')
	{
		if (dc > 0 && (*(str + cc) < 48 || *(str + cc) > 57))
			break;
		if (*(str + cc) == '-')
			sign *= -1;
		if ((*(str + cc) >= 48) && (*(str + cc) <= 57))
		{
			if (dc > 0)
				mul *= 10;
			dc++;
		}
		cc++;
	}
	for (idx = cc - dc ; idx < cc ; idx++)
	{
		res = res + ((*(str + idx) - 48) * mul);
		mul /= 10;
	}
	return (res * sign);
}
