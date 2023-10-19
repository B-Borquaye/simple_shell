#include "main.h"

/**
 * _memcopy - copies information.
 * @destptr: destination pointer.
 * @srcptr: source pointer.
 * @size: pointer size.
 *
 * Return: no return.
 */
void _memcopy(void *destptr, const void *srcptr, unsigned int size)
{
	char *char_srcptr = (char *)srcptr;
	char *char_destptr = (char *)destptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_destptr[i] = char_srcptr[i];
}

/**
 * _rlocate - reallocates memory.
 * @ptr: memory pointer.
 * @size1: pointer allocated size.
 * @size2: new memory block size.
 *
 * Return: ptr.
 * return ptr, if size2 == size1.
 * return NULL, if malloc fails.
 */
void *_rlocate(void *ptr, unsigned int size1, unsigned int size2)
{
	void *destptr;

	if (ptr == NULL)
		return (malloc(size2));

	if (size2 == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (size2 == size1)
		return (ptr);

	destptr = malloc(size2);
	if (destptr == NULL)
		return (NULL);

	if (size2 < size1)
		_memcopy(destptr, srcptr, size2);
	else
		_memcpy(destptr, srcptr, size1);

	free(ptr);
	return (destptr);
}

/**
 * _rlocatedp - reallocates double memory pointer.
 * @ptr: double memory pointer.
 * @size1: pointer allocated size.
 * @size2: new memory block size.
 *
 * Return: ptr.
 * return ptr, if size2 == size1.
 * return NULL, if malloc fails.
 */
char **_rlocatedp(char **ptr, unsigned int size1, unsigned int size2)
{
	char **destptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * size2));

	if (size2 == size1)
		return (ptr);

	destptr = malloc(sizeof(char *) * size2);
	if (destptr == NULL)
		return (NULL);

	for (i = 0; i < size1; i++)
		destptr[i] = ptr[i];

	free(ptr);

	return (destptr);
}
