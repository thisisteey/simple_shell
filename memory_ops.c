#include "main.h"

/**
 * cpy_mem - copies data from one memory location to another
 * @dst: destination memory location to copy to
 * @src: source memory location to copy from
 * @size: size number of bytes to copy
 * Return: void
 */
void cpy_mem(void *dst, const void *src, unsigned int size)
{
	char *char_dst = (char *)dst;
	const char *char_src = (const char *)src;
	unsigned int x;

	for (x = 0 ; x < size ; x++)
		char_dst[x] = char_src[x];
}

/**
 * re_alloc - reallocates memory for a block of data
 * @p: pointer to the memory block to be reallocated
 * @prev_sz: bytes size of the previously allocated space
 * @new_sz: new bytes size of the memory block
 * Return: pointer to the newly allocated memory block
 */
void *re_alloc(void *p, unsigned int prev_sz, unsigned int new_sz)
{
	void *newp = NULL;

	if (p == NULL)
		return (malloc(new_sz));
	if (new_sz == 0)
	{
		free(p);
		return (NULL);
	}
	if (new_sz == prev_sz)
		return (p);
	newp = malloc(new_sz);
	if (newp == NULL)
		return (NULL);
	if (new_sz < prev_sz)
		cpy_mem(newp, p, new_sz);
	else
		cpy_mem(newp, p, prev_sz);
	free(p);
	return (newp);
}

/**
 * realloc_dp - reallocates memory for an array of pointers (double pointers)
 * @p: double pointer to the array of pointers
 * @prev_sz: previous size in bytes of the allocated array
 * @new_sz: new size in bytes of the updated array
 * Return: pointer to the newly allocated array of pointers
 */
char **realloc_dp(char **p, unsigned int prev_sz, unsigned int new_sz)
{
	char **newp;
	unsigned int x;

	if (p == NULL)
		return (malloc(sizeof(char *) * new_sz));
	if (new_sz == prev_sz)
		return (p);
	newp = malloc(sizeof(char *) * new_sz);
	if (newp == NULL)
		return (NULL);
	for (x = 0 ; x < prev_sz ; x++)
		newp[x] = p[x];
	free(p);
	return (newp);
}
