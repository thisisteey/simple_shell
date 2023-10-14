#include "main.h"

/**
 * ret_line - assigns the line variable for the 'get_line' fucntion
 * @lnptr: pointer to the buffer that stores the input string
 * @lnsize: size of the lnptr buffer
 * @buf: string that is assigned to lnptr
 * @bsize: size of the buffer
 * Return: void
 */
void ret_line(char **lnptr, size_t *lnsize, char *buf, size_t bsize)
{
	if (*lnptr == NULL)
	{
		if (bsize > BUFFSIZE)
			*lnsize = bsize;
		else
			*lnsize = BUFFSIZE;
		*lnptr = buf;
	}
	else if (*lnsize < bsize)
	{
		if (bsize > BUFFSIZE)
			*lnsize =  bsize;
		else
			*lnsize = BUFFSIZE;
		*lnptr = buf;
	}
	else
	{
		str_cpy(*lnptr, buf);
		free(buf);
	}
}

/**
 * get_line - reads input from a stream
 * @lnptr: pointer to the buffer that stores the input
 * @lnsize: pointer to the size of lnptr
 * @stream: stream to read from
 * Return: the number of byter read from the input
 */
ssize_t get_line(char **lnptr, size_t *lnsize, FILE *stream)
{
	int x;
	static ssize_t str;
	ssize_t byt;
	char *buf;
	char nchar = 'z';

	if (str == 0)
		fflush(stream);
	else
		return (-1);
	str = 0;
	buf = malloc(sizeof(char) * BUFFSIZE);
	if (buf == 0)
		return (-1);
	while (nchar != '\n')
	{
		x = read(STDIN_FILENO, &nchar, 1);
		if (x == -1 || (x == 0 && str == 0))
		{
			free(buf);
			return (-1);
		}
		if (x == 0 && str != 0)
		{
			str++;
			break;
		}
		if (str >= BUFFSIZE)
			buf = re_alloc(buf, str, str + 1);
		buf[str] = nchar;
		str++;
	}
	buf[str] = '\0';
	ret_line(lnptr, lnsize, buf, str);
	byt = str;
	if (x != 0)
		str = 0;
	return (byt);
}
